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

/**
 * @file msAPI_MLE_font_base.h
 *
 */
#ifndef __MSAPI_MLE_FONT_BASE_H__
#define __MSAPI_MLE_FONT_BASE_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_graphic_forward.h"

/******************************/
/*        DEFINITION          */
/******************************/
#define MAX_VECTOR_FONT_NUM 10
#define MAX_CODE_COUNT      20
#define OUTLINE_PIXEL       1
//Font types
#define FONT_TYPE_NORMAL    0x00000000
#define FONT_TYPE_OUTLINE   0x00000001
#define FONT_TYPE_UNDERLINE 0x00000002
#define FONT_TYPE_EXPAND1   0x00000004

typedef U32 FontType_t; //normal / outline / underline / expand1

#define FONT_CONTROL_ZWNJ 0x200C
#define FONT_CONTROL_ZWJ  0x200D

#define EMPTY_CHAR(ch) (ch==0x0A || ch==0x0D)

/**
* Flags in Font
*/
enum
{
    FONT_FLAG_START = 0,
    FONT_FLAG_NO_CONVERT_RTL = FONT_FLAG_START,
    FONT_FLAG_SUPPORT_MULTI_LINE,
    FONT_FLAG_END
};

/**
* Flag Mask
*/
#define FONT_MASK_NO_CONVERT_RTL                (1<<FONT_FLAG_NO_CONVERT_RTL)
#define FONT_MASK_SUPPORT_MULTI_LINE            (1<<FONT_FLAG_SUPPORT_MULTI_LINE)

/**
* Macro to get flag value
*/
#define FONT_IS_NO_CONVERT_RTL(_nFlags) \
    (BOOLEAN)((_nFlags&FONT_MASK_NO_CONVERT_RTL)>>FONT_FLAG_NO_CONVERT_RTL)
#define FONT_IS_SUPPORT_MULTI_LINE(_nFlags) \
    (BOOLEAN)((_nFlags&FONT_MASK_SUPPORT_MULTI_LINE)>>FONT_FLAG_SUPPORT_MULTI_LINE)

/**
* Macro to Set flag value
*/
#define FONT_SET_NO_CONVERT_RTL(_nFlags, _b) \
    _nFlags = (_nFlags&(~FONT_MASK_NO_CONVERT_RTL))|(((U32)_b)<<FONT_FLAG_NO_CONVERT_RTL)
#define FONT_SET_SUPPORT_MULTI_LINE(_nFlags, _b) \
    _nFlags = (_nFlags&(~FONT_MASK_SUPPORT_MULTI_LINE))|(((U32)_b)<<FONT_FLAG_SUPPORT_MULTI_LINE)


/* Font create functions */
#ifdef __FEATURE_VECTOR_FONT__

/* if u32BufferSize  < minimum buffer size, set buffer size as minimum 
   else if  u32BufferSize > defualt buffer size, set buffer size as default */
BOOLEAN msAPI_MLE_FONTBASE_IsVectorFontExist(void);
BOOLEAN msAPI_MLE_FONTBASE_IsVectorFontCombineBitmap(void);
MLE_Ret msAPI_MLE_FONTBASE_ZoomVectorFont(float ZoomFactor);
MLE_Ret msAPI_MLE_FONTBASE_VectorFontChangeFontFromCus(U32 nFontId, U32 u32FontSize);
#endif


#endif /* __MSAPI_MLE_FONT_BASE_H__ */
