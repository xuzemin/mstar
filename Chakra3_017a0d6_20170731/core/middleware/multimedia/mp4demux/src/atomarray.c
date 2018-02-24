////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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


#include "mp4atom.h"

uint8_t MP4AtomArrayAdd(MP4ATOMARRAY *pArray, MP4ATOM *pNewAtom)
{
    MP4ATOM *pTail = 0;

    if (!pArray)
        return false;

    pTail = pArray->m_pTail;

    if (!pTail)
        pArray->m_pBegin = pNewAtom;    // is the first one added item
    else
        pTail->m_pNextAtom = pNewAtom;

    pArray->m_pTail = pNewAtom;
    pArray->m_totalnum++;

    return true;
}
