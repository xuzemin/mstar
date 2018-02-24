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


#ifdef __BIDI_TEXT__

#ifndef __MSAPI_MLE_TEXT_ARABIC_PRIV_H__
#define __MSAPI_MLE_TEXT_ARABIC_PRIV_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"

/******************************/
/*        DEFINITION          */
/******************************/
/* Arabic ROW definition */
#define TEXT_ARABIC_ROW        0x06 /* Arabic row */
#define TEXT_ARABIC_FORM_B_ROW 0xFE /* Arabic presentation forms-B row */
#define TEXT_ARABIC_FORM_A_ROW 0xFB /* Arabic presentation forms-A row */

/* COL ranges definition in Arabic row */
#define TEXT_ARABIC_HAMZA_CHAR 0x21 /* HAMZA char is 0x06 0x21 | always in PL so not converted */
#define TEXT_ARABIC_GHAIN_CHAR 0x3A /* GHAIN char is 0x06 0x3A */
#define TEXT_ARABIC_FEH_CHAR   0x41 /* FEH   char is 0x06 0x41 */
#define TEXT_ARABIC_YEH_CHAR   0x4A /* YEH   char is 0x06 0x4A */
#define TEXT_ARABIC_WASLA_CHAR 0x71 /* WASLA char is 0x06 0x71 | always in PL so not converted */

#define TEXT_ARABIC_INDIC_DIGIT_ZERO     0x60 /* Arabic-indic digit zero is 0x06 0x60 */
#define TEXT_ARABIC_INDIC_DIGIT_NINE     0x69 /* Arabic-indic digit nine is 0x06 0x69 */
#define TEXT_ARABIC_INDIC_DIGIT_ASTERISK 0x6D /* Arabic-indic asterisk   is 0x06 0x6D */

/* For concatenation */
#define TEXT_ARABIC_LAM_CHAR_PL              0xDD /* LAM (PL) char is 0xFE 0xDD can be concatened  with: */
#define TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL 0x81 /* - ALEF with MADDA ABOVE (PL) is 0xFE 0x81  */
#define TEXT_ARABIC_ALEF_HAMZA_ABOVE_CHAR_PL 0x83 /* - ALEF with HAMZA ABOVE (PL) is 0xFE 0x83  */
#define TEXT_ARABIC_ALEF_HAMZA_BELOW_CHAR_PL 0x87 /* - ALEF with HAMZA BELOW (PL) is 0xFE 0x87  */
#define TEXT_ARABIC_ALEF_CHAR_PL             0x8D /* - ALEF                  (PL) is 0xFE 0x8D  */
#define TEXT_ARABIC_ALFB_WASLA_CHAR_PL       0x50 /* - ALFB with WASLA (PL) is 0xFB 0x50  */

#define TEXT_ARABIC_LIG_LAM_ALEF_MADDA_ABOVE_CHAR_PL 0xF5 /* - ligature LAM with ALEF with MADDA ABOVE (PL) is 0xFE 0xF5  */
#define TEXT_ARABIC_LIG_LAM_ALEF_HAMZA_ABOVE_CHAR_PL 0xF7 /* - ligature LAM with ALEF with HAMZA ABOVE (PL) is 0xFE 0xF7  */
#define TEXT_ARABIC_LIG_LAM_ALEF_HAMZA_BELOW_CHAR_PL 0xF9 /* - ligature LAM with ALEF with HAMZA BELOW (PL) is 0xFE 0xF9  */
#define TEXT_ARABIC_LIG_LAM_ALEF_CHAR_PL             0xFB /* - ligature LAM with ALEF                  (PL) is 0xFE 0xFB  */

#define TEXT_GET_ROW(_CHAR_) ((U8)(_CHAR_ >> 8))
#define TEXT_GET_COL(_CHAR_) ((U8)(_CHAR_ & 0x00FF))
#define TEXT_SET_ROW(_CHAR_, _ROW_) (_CHAR_ = (U16)((_CHAR_ & 0x00FF) + ((U16)(_ROW_) << 8)))
#define TEXT_SET_COL(_CHAR_, _COL_) (_CHAR_ = (U16)((_CHAR_ & 0xFF00) + ((U16)(_COL_) & 0x00FF)))
#define TEXT_SET_CHAR(_ROW_, _COL_) ((((U16)(_ROW_)) << 8) + ((U16)(_COL_)))

#define TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT( _CHAR_ ) ((TEXT_GET_COL(_CHAR_) == 0x71) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0x77) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x79) && (TEXT_GET_COL(_CHAR_) <= 0x7B)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x7E) && (TEXT_GET_COL(_CHAR_) <= 0x80)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x83) && (TEXT_GET_COL(_CHAR_) <= 0x84)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x86) && (TEXT_GET_COL(_CHAR_) <= 0x88)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x8C) && (TEXT_GET_COL(_CHAR_) <= 0x8E)) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0x91) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0x98) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xA4) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xA6) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xA9) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xAD) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xAF) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xB1) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xB3) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xBA) && (TEXT_GET_COL(_CHAR_) <= 0xBB)) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xBE) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xC0) && (TEXT_GET_COL(_CHAR_) <= 0xC1)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xC5) && (TEXT_GET_COL(_CHAR_) <= 0xC9)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xCB) && (TEXT_GET_COL(_CHAR_) <= 0xCC)) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xD0) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xD2) && (TEXT_GET_COL(_CHAR_) <= 0xD3)))

#define TEXT_IS_ARABIC_ALPHA_FONTB_TO_CONVERT( _CHAR_ ) (((TEXT_GET_COL(_CHAR_) > TEXT_ARABIC_HAMZA_CHAR) && \
                                                      (TEXT_GET_COL(_CHAR_) <= TEXT_ARABIC_GHAIN_CHAR)) || \
                                                     ((TEXT_GET_COL(_CHAR_) >= TEXT_ARABIC_FEH_CHAR) && \
                                                                 (TEXT_GET_COL(_CHAR_) <= TEXT_ARABIC_YEH_CHAR)))

#define TEXT_IS_ARABIC_ALPHA_TO_CONVERT( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                                        (TEXT_IS_ARABIC_ALPHA_FONTB_TO_CONVERT(_CHAR_) || \
                                                         TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(_CHAR_)))

#define TEXT_IS_ARABIC_ALPHA_CHAR( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_FORM_B_ROW) || \
                                              ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                               ((TEXT_GET_COL(_CHAR_) < TEXT_ARABIC_INDIC_DIGIT_ZERO) || \
                                                (TEXT_GET_COL(_CHAR_) > TEXT_ARABIC_INDIC_DIGIT_ASTERISK))))

#define TEXT_IS_ARABIC_DIGIT_CHAR( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                             (TEXT_GET_COL(_CHAR_) >= TEXT_ARABIC_INDIC_DIGIT_ZERO) && \
                                             (TEXT_GET_COL(_CHAR_) <= TEXT_ARABIC_INDIC_DIGIT_ASTERISK))

#define TEXT_IS_ARABIC_COMPOSED_CHAR( _CHAR_ ) ( (TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                                      (((TEXT_GET_COL(_CHAR_) >= 0x10) && (TEXT_GET_COL(_CHAR_) <= 0x1A)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0x4B) && (TEXT_GET_COL(_CHAR_) <= 0x5E)) || \
                                                       (TEXT_GET_COL(_CHAR_) == 0x70) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xD6) && (TEXT_GET_COL(_CHAR_) <= 0xDC)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xDF) && (TEXT_GET_COL(_CHAR_) <= 0xE4)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xE7) && (TEXT_GET_COL(_CHAR_) <= 0xE8)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xEA) && (TEXT_GET_COL(_CHAR_) <= 0xED))) )

/* 4 possible positions in an arabic word: PL, PF, PI, PM */
#define TEXT_ARABIC_PL_POSITION 0 /* Isolated form */
#define TEXT_ARABIC_PF_POSITION 1 /* Final form */
#define TEXT_ARABIC_PI_POSITION 2 /* Initial form */
#define TEXT_ARABIC_PM_POSITION 3 /* medial form */

typedef struct
{
   U8 nPlChar;       /* correspondind COL value in row FE for PL position */
   BOOLEAN bForceEnd;     /* Indicates if the char force word end */
} Text_ArabicConvertTable_t;

typedef struct
{
   U8 nChar;
   U8 nPlPosition;
} Text_FEArabicConvertTable_t;

#define TEXT_ARABIC_FORCE_END(_COL_)  _tTextArabicConvertTable[_COL_-(TEXT_ARABIC_HAMZA_CHAR+1)].bForceEnd
#define TEXT_ARABIC_CONVERT2PL(_COL_) _tTextArabicConvertTable[_COL_-(TEXT_ARABIC_HAMZA_CHAR+1)].nPlChar

#define TEXT_ARABIC_FONTA_FORCE_END(_COL_)  _tTextArabicConvertFontATable[_COL_-(TEXT_ARABIC_WASLA_CHAR)].bForceEnd
#define TEXT_ARABIC_FONTA_CONVERT2PL(_COL_) _tTextArabicConvertFontATable[_COL_-(TEXT_ARABIC_WASLA_CHAR)].nPlChar
#define TEXT_FEARABIC_CONVERT2PL(_COL_) _tTextFEArabicConvertTable[_COL_-TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL].nChar
#define TEXT_FEARABIC_PL(_COL_) _tTextFEArabicConvertTable[_COL_-TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL].nPlPosition

#define TEXT_FBARABIC_FONTA_CONVERT2PL(_COL_) _tTextFBArabicConvertFontATable[_COL_-TEXT_ARABIC_ALFB_WASLA_CHAR_PL].nChar
#define TEXT_FBARABIC_FONTA_PL(_COL_) _tTextFBArabicConvertFontATable[_COL_-TEXT_ARABIC_ALFB_WASLA_CHAR_PL].nPlPosition

static U32 _msAPI_MLE_TextArabicConvertToDisplay( MLE_WChar *pString, U32 nStrLen );
static BOOLEAN _msAPI_MLE_TextArabicConvertFEFormat( MLE_WChar *pString, U32 nStrLen );
static BOOLEAN _msAPI_MLE_TextArabicConvertFEChar( MLE_WChar *pwChar, MLE_WChar *pPreChar, BOOLEAN *pInWord, BOOLEAN *pPreCharIsFirst );
static U32 _msAPI_MLE_TextArabicEFConcatenation( MLE_WChar *pEFString, U32 nStrLen );
static BOOLEAN _msAPI_MLE_TextArabicFEConcatenationNextChar( MLE_WChar *pEFChar, MLE_WChar nEFNextChar );
static BOOLEAN _msAPI_MLE_TextArabicConvertLastCodeType( const U16 nChar, U16 *pLastCodeType );

#endif //__MSAPI_MLE_TEXT_ARABIC_PRIV_H__

#endif //__BIDI_TEXT__
