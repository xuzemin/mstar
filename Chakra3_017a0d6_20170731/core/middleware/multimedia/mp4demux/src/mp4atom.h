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


#ifndef MP4ATOM_H
#define MP4ATOM_H

#include "mp4def.h"

#define STRINGIFY(x)    #x
#define STTS_A    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x74\x00\x73\x00\x5f\x00\x61\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stts_a.tmp (unicode)
#define STTS_V    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x74\x00\x73\x00\x5f\x00\x76\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stts_v.tmp (unicode)

#define STSC_A    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x73\x00\x63\x00\x5f\x00\x61\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stsc_a.tmp (unicode)
#define STSC_V    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x73\x00\x63\x00\x5f\x00\x76\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stsc_v.tmp (unicode)

#define STSZ_A    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x73\x00\x7a\x00\x5f\x00\x61\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stsz_a.tmp (unicode)
#define STSZ_V    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x73\x00\x7a\x00\x5f\x00\x76\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stsz_v.tmp (unicode)

#define STCO_A    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x63\x00\x6f\x00\x5f\x00\x61\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stco_a.tmp (unicode)
#define STCO_V    STRINGIFY(\x2f\x00\x43\x00\x41\x00\x52\x00\x44\x00\x2f\x00\x73\x00\x74\x00\x63\x00\x6f\x00\x5f\x00\x76\x00\x2e\x00\x74\x00\x6d\x00\x70\x00\x00\x00)             // /CARD/stco_v.tmp (unicode)

#define AMR_VENDOR          0x4d537472 //MStr //0x4d535452 //MSTR //0x6861726b//hark
#define H263_VENDOR         0x4d537472 //MStr //0x4d535452 //MSTR //0x6861726b//hark
#define H263_VENDOR_MSTR    0x4d537472 //MStr //0x4d535452 //MSTR //0x6861726b//hark
#define H263_VENDOR_FFMP    0x46464d50 //FFMP //0x46464d50

#define MUX_BUF_ADDR     REC_3GPP_GetStack(MUX_BUF)
#define MUX_BUF_SIZE     REC_3GPP_GetStackSize(MUX_BUF)
#define LBC_BUF_ADDR     REC_3GPP_GetStack(LBC_BUF)
#define LBC_BUF_SIZE     REC_3GPP_GetStackSize(LBC_BUF)
#define I2S_BUF_ADDR     REC_3GPP_GetStack(I2S_BUF)
#define I2S_BUF_SIZE     REC_3GPP_GetStackSize(I2S_BUF)

#define MP4_MAX_ATOM_DEPTH  8
struct tagMP4PropertyArray;
struct tagMP4File;
struct tagMP4Property;
struct tagATOM;

typedef struct tagMP4ATOMARRAY
{
    uint32_t           m_totalnum;
    struct tagATOM     *m_pBegin;
    struct tagATOM     *m_pTail;
} MP4ATOMARRAY, *PMP4ATOMARRAY;

typedef struct tagATOM {
    struct tagMP4File   *m_pFile;
    FILE_POS            m_start;
    FILE_POS            m_end;
    FILE_POS            m_size;
    char                m_type[5];
    uint8_t             m_level;

    struct tagMP4ATOMARRAY      m_pChildAtoms;
    void                        *m_pProperties;
    void                        *m_aux;     // memory from mp4 demuxer heap
    void                        *m_aux_ext; // memory from callback malloc

    struct tagATOM      *m_pNextAtom;   // next atom address in the atom array
} MP4ATOM, *PMP4ATOM;

#if defined(MP4REC_DEFER_EN)
typedef struct tagMP4PurgedAtom
{
    U32 m_AtomSize;
    U32 *m_pAtomtable;
    U8  m_SplitNum;
    U32 *m_pSplitInfo;
} MP4PURGEDATOM, *PMP4PURGEDATOM;
#endif // MP4REC_DEFER_EN

//-----------------------------------------------------------------------------
// for demuxer
//-----------------------------------------------------------------------------
// Atom API
MP4ATOM *CreateAtom(void *ctx, const char *type);
void MP4AtomFree(void *ctx, MP4ATOM *pAtom);
void MP4AtomFreeChild(void *ctx, MP4ATOMARRAY *pArray);
MP4ATOM* MP4AtomFindAtom(MP4ATOM *pAtom, const char* name);

// Atom array
uint8_t MP4AtomArrayAdd(MP4ATOMARRAY *pArray, MP4ATOM *pAtom);
uint8_t MP4AtomArrayFree(MP4ATOMARRAY *pArray);

#define MP4AtomArrayEnumBegin(pArray)       ((pArray)->m_pBegin)
#define MP4AtomArrayEnumNext(pArray, pItem) ((pItem)->m_pNextAtom)

// Atom read
int MP4AtomRead(void *ctx, MP4ATOM *pAtom);
int MP4AtomReadAtomHeader(struct tagMP4File *pFile, uint64_t *dataSize, char type[5]);

#endif /* MP4ATOM_H */
