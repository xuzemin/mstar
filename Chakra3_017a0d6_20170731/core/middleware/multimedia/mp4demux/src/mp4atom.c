////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "mp4atom.h"
#include "mp4def.h"
#include "mp4util.h"
#include "mp4file.h"
#include "mvc_demuxer.h"

MP4ATOM *CreateAtom(void *ctx, const char *type)
{
    MP4ATOM *pAtom;
    int i;

    pAtom = (MP4ATOM*) mdxalloc(ctx, sizeof(MP4ATOM));
    if (!pAtom)
    {
        MP4_DBG_MSG("[MuxDmx] Create atom fail\n");
        return NULL;
    }
    memset(pAtom, 0, sizeof(MP4ATOM));

    {
        assert(strlen(type) <= 4);
        memcpy(pAtom->m_type, type, 5);

        for (i = 0; i < 4; i++)
            pAtom->m_type[i] = tolower(pAtom->m_type[i]);

        MP4_DBG_MSG("[MuxDmx] Create %s\n", type);
    }

    return pAtom;
}

static void MP4AtomFreeProperty(void *ctx, MP4ATOM *pAtom)
{
    if (pAtom->m_pProperties)
    {
        mdxfree(ctx, pAtom->m_pProperties);
    }

    pAtom->m_pProperties = 0;
}

void MP4AtomFreeChild(void *ctx, MP4ATOMARRAY *pArray)
{
    MP4ATOM *pItem;

    pItem = pArray->m_pBegin;
    while (pItem)
    {
        MP4ATOM *pNext = pItem->m_pNextAtom;
        MP4AtomFree(ctx, pItem);
        pItem = pNext;
    }
    pArray->m_totalnum = 0;
    pArray->m_pBegin = pArray->m_pTail = 0;
}

void MP4AtomFree(void *ctx, MP4ATOM *pAtom)
{
    mvc_callback_st *callback = &pAtom->m_pFile->callback;

    if (pAtom->m_pProperties)
        MP4AtomFreeProperty(ctx, pAtom);
    if (pAtom->m_aux)
        mdxfree(ctx, pAtom->m_aux);
    if (pAtom->m_aux_ext)
        callback->freep(callback->context, &pAtom->m_aux_ext);

    MP4AtomFreeChild(ctx, &pAtom->m_pChildAtoms);

    mdxfree(ctx, pAtom);
}

static const char *MP4NameFirstMatches(const char *s1, const char *s2)
{
    if (*s1 == '\0') {
        return 0;
    }

    while (1)
    {
        if (*s1 == '\0' && (*s2 == '\0' || *s2 == '.'))
            break;

        if (*s1 != *s2) {
            return 0;
        }
        s1++;
        s2++;
    }
    return s2;
}

MP4ATOM *MP4AtomFindAtom(MP4ATOM *pAtom, const char *name)
{
    MP4ATOM *pItem = MP4AtomArrayEnumBegin(&pAtom->m_pChildAtoms);

    assert(name && name[0]);

    while (pItem)
    {
        const char *next = MP4NameFirstMatches(pItem->m_type, name);

        if (next)
        {
            if (*next == '\0') {
                return pItem;
            }
            return MP4AtomFindAtom(pItem, next + 1);
        }
        pItem = MP4AtomArrayEnumNext(&pAtom->m_pChildAtoms, pItem);
    }
    return NULL;
}
