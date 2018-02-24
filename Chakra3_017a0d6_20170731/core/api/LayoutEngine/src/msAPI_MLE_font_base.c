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

#ifndef __MSAPI_MLE_FONT_BASE_C__
#define __MSAPI_MLE_FONT_BASE_C__

/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_base.h"

#ifdef __THAI_FONT__
#include "msAPI_MLE_font_thai.h"
#endif //__THAI_FONT__

#ifdef __INDIC_FONT__
#include "msAPI_MLE_font_hindi_priv.h"
#endif

#ifdef __HEBREW_FONT__
#include "msAPI_MLE_font_hebrew.h"
#endif

#include "msAPI_MLE_font_latine.h"

#define _SUPPORT_FONT_CUS_

#include "msAPI_MLE_font_vector.h"

/******************************/
/*        DEFINITION          */
/******************************/
#define MAX_Font_PER_SET    10

#ifdef __BIDI_TEXT__
extern U16 msAPI_TextArabicGetNextCodes(const U16 *pInTxt, U32 nInLen, U32 nOffset, U32 nSubLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed, BOOLEAN bDispStr, U16 *pLastCode );
#endif //__BIDI_TEXT__

/******************************/
/*         VARIABLES          */
/******************************/

/******************************/
/*     INTERFACE FUNCTIONS        */
/******************************/

static BOOLEAN bFilterZeroWidthChar = TRUE;

void msAPI_MLE_FontBaseSetZeroWidthFilterStatus(BOOLEAN bFilter)
{
    bFilterZeroWidthChar = bFilter;
}

BOOLEAN msAPI_MLE_FontBaseIsControlChar(U32 U32Unicode)
{
    if ( bFilterZeroWidthChar )
    {
        if ( (U32Unicode == 0x200C) ||    // Zero Width Non-Joiner
            (U32Unicode == 0x200D) )    // Zero Width Joiner
        {
            return TRUE;
        }
    }

    if ( U32Unicode == 0xFEFF ||    // Zero Width No-Break Space
         U32Unicode == 0xFFFE ||    // Non-characters or used in byte order signature
         U32Unicode == 0xFFFF ||    // Non-characters
         U32Unicode == 0x2060 ||    // Word Joiner
         U32Unicode == 0x200B ||    // Zero Width Space
         U32Unicode == 0x2028 ||    // Line and Paragraph Separator
         U32Unicode == 0x2029 ||    // Line and Paragraph Separator
         U32Unicode == 0x034F ||    // Combining Grapheme joiner
         U32Unicode == 0x200E ||    // Left-to-Right Mark
         U32Unicode == 0x200F ||    // Right-to-Left Mark
         U32Unicode == 0x202A ||    // Left-to-Right Embedding
         U32Unicode == 0x202B ||    // Right-to-Left Embedding
         U32Unicode == 0x202C ||    // Pop Directional Formatting
         U32Unicode == 0x202D ||    // Left-to-Right Override
         U32Unicode == 0x202E ||    // Right-to-Left Override
         U32Unicode == 0x206A ||    // Deprecated Format Characters
         U32Unicode == 0x206B ||    // Deprecated Format Characters
         U32Unicode == 0x206C ||    // Deprecated Format Characters
         U32Unicode == 0x206D ||    // Deprecated Format Characters
         U32Unicode == 0x206E ||    // Deprecated Format Characters
         U32Unicode == 0x206F)  // Deprecated Format Characters
         return TRUE;

    return FALSE;
}

#if 0
U16 _msAPI_MLE_FontBaseIsSpaceChar(U32 U32Unicode)
{
    if ( U32Unicode == 0x00A0 ||    // NBSP
         U32Unicode == 0x2007 ||    // figure space
         U32Unicode == 0x202F ||    // narrow no-break space
         U32Unicode == 0x2060 ||    // word joiner
         U32Unicode == 0xFEFF)      // zero width no-break space
         return TRUE;

    return FALSE;
}
#endif

/******************************/
/*     GLOBAL FUNCTIONS       */
/******************************/
#if 0
MLE_Ret msAPI_FONTBASE_MeasureTextEx(FontBase_t *pIFont,
                                u32 nFontCate,                   // category
                                u32 nFontSize,
                                const u16 *pText,               // text buffer pointer
                                u32 Chars,                      // number of text character
                                u32 nOffset,
                                u32 nSubLen,                  // still number of text character
                                u32 nMaxWidth,
                                u32 *pFits,                     // [out]
                                u32 *pPixels,                   // [out]
                                u32 nType,
                                u32 bSkip,
                                _OutlineGlyphInfo_t **ppGInfos,   // NULL
                                u32 *pGlyphCnt,                 // NULL
                                boolean bDispStr)               // FALSE
{
    FontInfo sFontInf = {0};

    if ( NULL == pIFont || NULL == pText ||
            NULL == pFits || NULL == pPixels )
    {
        return MAE_RET_BAD_PARAM;
    }

    if ( (nOffset + nSubLen) > Chars )
    {
        return MAE_RET_BAD_PARAM;
    }

    sFontInf.nAscent = 0;
    sFontInf.nDescent = 0;
    sFontInf.nHeight = 0;
    sFontInf.nTag = 0;
    
    msAPI_MLE_FONTBASE_Vector_GetInfo(nFontSize, nType, &sFontInf);

    if ( FONT_IS_NO_CONVERT_RTL(sFontInf.nTag) )
    {
        bDispStr = FALSE;
    }

    if((s32)nMaxWidth < 0)
    {
        nMaxWidth = 0; // if nMaxWidth == 0, means nMaxWidth is not defined
    }

    return msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize,
                                       pText, Chars, nOffset, nSubLen, nMaxWidth, pFits,
                                       pPixels, nType, bSkip, bDispStr);
    
    return FONTBASE_Vector_MeasureText(pThis->fontInfo.FontSize,
                                       pu16TempStr, u32LineLen, 0, u32LineLen, 0, &u32LineLen,  &u32LineWidth,
                                       pThis->fontInfo.FontType, FALSE, bIsDisplayStr); 
}
#endif
#endif //__MSAPI_MLE_FONT_BASE_C__
