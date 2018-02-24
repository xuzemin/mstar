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
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_FONT_H
#define MAPP_FONT_H

#include "datatype.h"
#include "msAPI_Font.h"

#ifdef MAPP_LOADFONT_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


//=================================================================
//                            Macro
//=================================================================
// Font width and height defined below are for reference only.
// Their actual values are kept in the font binary files
#define MS_CHAR_WIDTH          16
#define MS_CHAR_HEIGHT         22
#define MS_CHAR_WIDTHX2        32
#define MS_CHAR_HEIGHTX2       40

//Move to msAPI_Font.h
/////////////////////////////////////
#if 0
#if DYNAMIC_VECTOR_FONT_ENABLE
#define MAX_FONTTABLE_NUM_OSD  5 //LANGUAGE_NUM
#define FONT_DYNAMIC_MVF_EXT   4 //dynamic size
#else
#define MAX_FONTTABLE_NUM_OSD  5 //LANGUAGE_NUM
#endif

#define FONT_0        0 //35pt
#define FONT_1        1 //30pt
#define FONT_2        2 //26pt

#if (ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_BRAZIL_APP)
#define FONT_BIG5   3
#else
#define FONT_CHINESE   3
#endif
#define FONT_EXT_BEGIN  6
#define FONT_MULTILANG_BEGIN    9

#if (ENABLE_ARABIC_OSD)
    #define FONT_ARABIC_0   10
    #define FONT_ARABIC_1   11
    #define FONT_ARABIC_2   12
    #define FONT_ARABIC_50  13
#endif

#if (ENABLE_THAI_OSD)
    #define FONT_THAI_0     14
    #define FONT_THAI_1     15
    #define FONT_THAI_2     16
    #define FONT_THAI_50    17
#endif
#endif
////////////////////////////////////////////

#if (ATSC_CC != ATV_CC)
  #if (BRAZIL_CC)
      #define MAX_FONTTABLE_NUM_CC         2//one is for brazil cc, and the other is for atv cc
  #else
    #if (KOREAN_CC_ENABLE)
     #define MAX_FONTTABLE_NUM_CC         6
     #else
      #define MAX_FONTTABLE_NUM_CC         24
     #endif
  #endif
#else
    #define MAX_FONTTABLE_NUM_CC         1
#endif

//==============================================================================
/*                            Structure Type                                      */
//==============================================================================

//Move to msAPI_Font.h
/////////////////////////////////////
#if 0
INTERFACE FONT Font[MAX_FONTTABLE_NUM_OSD];
INTERFACE U16  FontHandleIndex[MAX_FONTTABLE_NUM_OSD];
#endif
////////////////////////////////////////////

INTERFACE void MApp_LoadFont(U8 u8StepID);
INTERFACE void MApp_LoadFont_SetVecFontInfo(LOADFONT_STRUCT* strfont, U8 u8Begin, U8 u8End);
INTERFACE void MApp_LoadFont_SetBMPFontInfo(LOADFONT_PAIR* fontpair, U8 u8num);




INTERFACE BOOLEAN MApp_LoadFont_CC(void);
INTERFACE void MApp_LoadFont_CC_Init(void);
INTERFACE BOOLEAN MApp_LoadAll_Font_CC(void);

#undef INTERFACE
#endif

