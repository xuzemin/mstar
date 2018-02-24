//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//

#ifndef __MLE_FONT_VECTOR_H__
#define __MLE_FONT_VECTOR_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "msAPI_MLE_font_base.h"
#include "msAPI_MLE_font_types.h"
#include "msAPI_MLE_font_forward.h"
#include "msAPI_OSD.h"

//For 2 gray level font, define MONO_FONT to 1. This is for I-8 OSD
//For 256 gray levell font, define MONO_FONT to 0. This is for ARGB1555 OSD
#define MONO_FONT   0

extern BOOLEAN msAPI_MLE_FontBaseIsControlChar(U32 u32Unicode);
extern void msAPI_MLE_FontBaseSetZeroWidthFilterStatus(BOOLEAN bFilter);

typedef struct
{
    S32  fontfrom;
    S32  faceIndex;
    S32  cmapIndex;
    const U8 *pGDEF;
    const U8 *pGPOS;
    const U8 *pGSUB;
    const U8 *pMort;
    const U8 *pKern;
    U16 u16UnitsPerEM; 
}TFont, *PFont;

typedef struct TTF_Bitmap_
{
    S32 rows;
    S32 width;
    S32 pitch;
    U8* buffer;
    S32 x;
    S32 y;
    S32 xadvance;
    S32 yadvance;
    S32 gidx;
    S32 s32PreGap;
    S32 s32PosGap;
    S32 s32ZeroWidth;
    S32 iOutLineWidth; //iOutLineWidth = 0 is mean that no outline
    S32 irows;
    S32 iwidth;
    S32 ipitch;
    U8* ibuffer;
} TTF_Bitmap;

typedef struct  TTF_BmpCacheInfo_
{
    S8 width;
    S8 left;
    S8 top;
    S8 xadvance;
    S8 yadvance;
} TTF_BmpCacheInfo;

typedef struct TTF_Vector_
{
    S32 x;
    S32 y;
} TTF_Vector;

typedef struct TTF_FaceInf_
{
    S32 ascender;
    S32 descender;
    S32 height;
    S32 yMax;
    S32 yScale;
} TTF_FaceInf;

void msAPI_MLE_SetMemoryNotEnoughFlag(BOOLEAN bFlag);
BOOLEAN msAPI_MLE_GetMemoryNotEnoughFlag(void);
///MLE_Ret msAPI_MLE_FONTBASE_VectorFontSetCategory(void);
///void msAPI_MLE_FONTBASE_VectorFontSetSizeMap( void );
void msAPI_MLE_FONTBASE_VectorFontSetExist(void);
///void msAPI_MLE_FONTBASE_VectorFontSetCombineBitmap(void);
///BOOLEAN msAPI_MLE_FONTBASE_VectorFontIsForceBitmapFont(U32 nFontCate);
void msAPI_MLE_FONTBASE_VectorFontInit( void );
void msAPI_MLE_FONTBASE_VectorFontUnInit( void );
void msAPI_MLE_FONTBASE_VectorFontFree( void );
void msAPI_MLE_FONTBASE_VectorFontReInit(U32 u32BufferSize);
U16 msAPI_MLE_FONTBASE_GetVectorFontSize( void );
///U16 FONTBASE_GetVectorMapFontSize( U32 u32Category ); 
U32 msAPI_MLE_FONTBASE_VectorFontGetGlyphId(U32 u32UcsCode);
MLE_Ret msAPI_MLE_FONTBASE_VectorFontGetTFGlyphInfAllocate(U32 u32GlyphId, TTF_Bitmap **pTTFBitmap);
void msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(TTF_Bitmap *pTFBitmap);
MLE_Ret msAPI_MLE_FONTBASE_VectorFontGetFaceInf( TTF_FaceInf *pFaceInf, U32 u32FontSize);

const U8* msAPI_MLE_FONTBASE_VectorFontGetGDEFTable( void );
const U8* msAPI_MLE_FONTBASE_VectorFontGetGPOSTable( void );
const U8* msAPI_MLE_FONTBASE_VectorFontGetGSUBTable( void );
//const U8* msAPI_MLE_FONTBASE_VectorFontGetKernTable( void );
//const U8* msAPI_MLE_FONTBASE_VectorFontGetMortTable( void );
U16 msAPI_MLE_FONTBASE_VectorFontGetUnitPerEM( void );
S32 msAPI_MLE_FONTBASE_VectorFontGetXScaleFactor( void );
S32 msAPI_MLE_FONTBASE_VectorFontGetYScaleFactor( void );
// vector font from sd card
MLE_Ret msAPI_MLE_FONTBASE_CreateVectorFont_FromFile(void);
MLE_Ret msAPI_MLE_FONTBASE_CreateVectorFont_FromMemory(const void* data, U32 size);
///MLE_Ret msAPI_MLE_FONTBASE_CreateVectorFont_FromCus( void );

MLE_Ret msAPI_MLE_FONTBASE_Vector_MeasureText(U32 nFontSize, 
                                    const U16 *pText,                    // text buffer pointer
                                    U32 nChars,                          // number of text character
                                    U32 nOffset,                         // 0
                                    U32 nSubLen,                         // still number of text character
                                    U32 nMaxWidth,
                                    U32 *pFits,                          // [out]
                                    U32 *pPixels,                        // [out]
                                    U32 nType,
                                    U32 bSkip,
                                    BOOLEAN bDispStr );                   // FALSE

MLE_Ret msAPI_MLE_FONTBASE_Vector_MeasureClippedText(U32 nFontSize, 
        const U16 *pText,                    // text buffer pointer
        U32 nChars,                          // number of text character
        U32 nOffset,                         // 0
        U32 nSubLen,                         // still number of text character
        U32 nMaxWidth,
        U32 *pFits,                          // [out]
        U32 *pPixels,                        // [out]
        U32 nType,
        U32 bSkip,
        BOOLEAN bDispStr );                   // FALSE
        
MLE_Ret msAPI_MLE_FONTBASE_Vector_DrawText(U32 FontSize,              // Size
                                 S32 xStart,                // start x
                                 S32 yStart,                // start y
                                 const U16 *pText,          // text buffer pointer
                                 U32 nChars,                // number of text character
                                 Rect_t *pCARect,           // Client area
                                 U32 nType,                  // Type
                                 OSDClrBtn *pclrBtn,
                                 BOOLEAN bFontMirror );

MLE_Ret msAPI_MLE_FONTBASE_Vector_GetInfo(U32 nFontSize,           // Font Size to query
        U32 Type,
        FontInfo *pinfo);

void msAPI_MLE_FONTBASE_Vector_InsertHindiCache(U32 u32Offset, U16* pau16Cluster, U16 u16ClusterLen, U16 *pu16OutCode, U16 u16OutCodeLen, U32 *pau32Consumed, U32 u32Features);
void* msAPI_MLE_FONTBASE_Vector_SearchHindiCache(U16 *pu16Cluster, U16 u16CluserSize, U32 u32Features, BOOLEAN *bKeyDuplicate);

#endif //__FEATURE_VECTOR_FONT__

#endif //__MLE_FONT_VECTOR_H__
