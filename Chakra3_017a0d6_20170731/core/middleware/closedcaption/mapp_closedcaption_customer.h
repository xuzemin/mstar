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

#ifndef MAPP_CLOSED_CAPTION_CUSTOMER_H
#define MAPP_CLOSED_CAPTION_CUSTOMER_H


#define CUSTOMER_BASE

#ifdef CUSTOMER_BASE

// dump cc log
#define CC_CONFIG_DUMP_DBG_MSG   FALSE

// cc timeout config
#define CC_CONFIG_608_TIMEOUT_CAPITON       16000
#define CC_CONFIG_708_TIMEOUT_CAPTION     20000
#define CC_CONFIG_608_TIMEOUT_TEXT    16000

// cc position config
#define CC_CONFIG_ATV_AXIS_XPOS   275
#if (KOREAN_CC_ENABLE)
  #define CC_CONFIG_ATV_AXIS_YPOS  250
#else
  #if ((CHIP_FAMILY_TYPE != CHIP_FAMILY_WHISKY)||((MEMORY_MAP > MMAP_32MB) && (UI_SKIN_SEL!=UI_SKIN_960X540X565) && (UI_SKIN_SEL!=UI_SKIN_960X540XI8)))
  #define CC_CONFIG_ATV_AXIS_YPOS  114
  #else
  #define CC_CONFIG_ATV_AXIS_YPOS   0
  #endif
#endif
#define CC_CONFIG_DTV_AXIS_XPOS     0
#define CC_CONFIG_DTV_AXIS_YPOS     0
#define CC_CONFIG_ROW_TOPRSVHEIGHT      0
#define CC_CONFIG_ROW_BTMRSVHEIGHT      0

//other config
#define CC_CONFIG_TRANSLUCENT    0x30
#define CC_CONFIG_INDENT_GAP 4  //must be even & higher than 2
#define CC_CONFIG_TEXT_ROWNO 15
#define CC_CONFIG_CHECK_PERIOD 0
#define CC_CONFIG_INPUT_USING157 FALSE
#define CC_CONFIG_PARSING_FONTEDGE 1

//sysinfo config
#define CC_CONFIG_fCCAttrEnableAutoSTAbyVideoFmt  TRUE
#define CC_CONFIG_fCCAttr_Parity_Error_Solid_Block_Flag     FALSE
#define CC_CONFIG_fCCAttr_EnableRrvBlK   TRUE
#if (KOREAN_CC_ENABLE)
#define CC_CONFIG_fCCAttrEnable24Fonts  FALSE
#else
#define CC_CONFIG_fCCAttrEnable24Fonts  TRUE
#endif
#define CC_CONFIG_fCCAttr_EnableSemiTransparentOnTextMode_Flag   FALSE
#define CC_CONFIG_fCCAttr_Packet_Dump_Flag  FALSE                    //For Dump CC Data.
#define CC_CONFIG_fCCAttrEnableGopZoom  FALSE
#define CC_CONFIG_fCCAttr_GOP_Use_FBPool2  FALSE
#define CC_CONFIG_fCCAttr_Support_Border_Opacity   FALSE
#define CC_CONFIG_fCCAttr_DLW_Call_GEngine   TRUE
#define CC_CONFIG_fCCAttr_Font_Indention_Flag   FALSE
#define CC_CONFIG_fCCAttr_Show_Window_Has_Text   FALSE
#define CC_CONFIG_fCCAttr_EnableWindowOptionSetting  FALSE
#define CC_CONFIG_fCCAttr_Support_Deep_Color   FALSE       //TRUE: 64 color palette; FALSE: 8 color palette
#define CC_CONFIG_Support_Caption_Preview  ENABLE
#define CC_CONFIG_fCCAttr_Wait_GFX_Flush_Queue  TRUE
#define CC_CONFIG_fCCAttr_Support_WindowBorder_Flag TRUE   //Control windowborder
#define CC_CONFIG_fCCAttr_Support_ATVAttrSet_Flag FALSE    //Control FG&BG color for ATV
#define CC_CONFIG_fCCAttr_Support_EdgeAttrSet_Flag TRUE   //Control edgetype for SEC
#define CC_CONFIG_fCCAttr_Support_OtherLanguage_Flag FALSE // Control CC language(chinese or other)
#define CC_CONFIG_fCCAttr_Expletive_Show_Flag TRUE  //Control SPA Texttag11!


//brazil cc config
#define CC_CONFIG_ENABLESVS     TRUE
#define CC_CONFIG_ENABLESHS     FALSE

#else // other customer /config
//other customer config


#endif //#ifdef CUSTOMER_BASE

#endif
