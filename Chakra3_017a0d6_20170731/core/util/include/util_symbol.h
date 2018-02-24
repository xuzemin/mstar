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
#ifndef _UTIL_SYMBOL__HH__
#define _UTIL_SYMBOL__HH__
/*msAPI_Debug.c is used to exchange software symbols with MSTV_TOOL*/
typedef enum
{
    SYMBOL_MVD_VOL_INFO_BASE,
    SYMBOL_MVD_FRAME_INFO_BASE,
    SYMBOL_MVD_FRAME_AVAILABLE,
    SYMBOL_GOP_FB0_STARTADR,          //for GE use
    SYMBOL_GOP_FB0_WIDTH,
    SYMBOL_GOP_FB0_HEIGHT,
    SYMBOL_GOP_FB0_PITCH,
    SYMBOL_GOP_FB0_FORMAT,
     SYMBOL_GOP_FB0_STRING,
    SYMBOL_GOP_FB1_STARTADR,
    SYMBOL_GOP_FB1_WIDTH,
    SYMBOL_GOP_FB1_HEIGHT,
    SYMBOL_GOP_FB1_PITCH,
    SYMBOL_GOP_FB1_FORMAT,
     SYMBOL_GOP_FB1_STRING,
    SYMBOL_GOP_FB2_STARTADR,
    SYMBOL_GOP_FB2_WIDTH,
    SYMBOL_GOP_FB2_HEIGHT,
    SYMBOL_GOP_FB2_PITCH,
    SYMBOL_GOP_FB2_FORMAT,
     SYMBOL_GOP_FB2_STRING,
    SYMBOL_GOP_FB3_STARTADR,
    SYMBOL_GOP_FB3_WIDTH,
    SYMBOL_GOP_FB3_HEIGHT,
    SYMBOL_GOP_FB3_PITCH,
    SYMBOL_GOP_FB3_FORMAT,
     SYMBOL_GOP_FB3_STRING,
    SYMBOL_GOP_FB4_STARTADR,
    SYMBOL_GOP_FB4_WIDTH,
    SYMBOL_GOP_FB4_HEIGHT,
    SYMBOL_GOP_FB4_PITCH,
    SYMBOL_GOP_FB4_FORMAT,
     SYMBOL_GOP_FB4_STRING,
    SYMBOL_GOP_FB5_STARTADR,
    SYMBOL_GOP_FB5_WIDTH,
    SYMBOL_GOP_FB5_HEIGHT,
    SYMBOL_GOP_FB5_PITCH,
    SYMBOL_GOP_FB5_FORMAT,
     SYMBOL_GOP_FB5_STRING,
    SYMBOL_GOP_FB6_STARTADR,
    SYMBOL_GOP_FB6_WIDTH,
    SYMBOL_GOP_FB6_HEIGHT,
    SYMBOL_GOP_FB6_PITCH,
    SYMBOL_GOP_FB6_FORMAT,
     SYMBOL_GOP_FB6_STRING,
    SYMBOL_GOP_FB7_STARTADR,
    SYMBOL_GOP_FB7_WIDTH,
    SYMBOL_GOP_FB7_HEIGHT,
    SYMBOL_GOP_FB7_PITCH,
    SYMBOL_GOP_FB7_FORMAT,
     SYMBOL_GOP_FB7_STRING,
    SYMBOL_GOP_FB8_STARTADR,
    SYMBOL_GOP_FB8_WIDTH,
    SYMBOL_GOP_FB8_HEIGHT,
    SYMBOL_GOP_FB8_PITCH,
    SYMBOL_GOP_FB8_FORMAT,
     SYMBOL_GOP_FB8_STRING,
    SYMBOL_GOP_FB9_STARTADR,
    SYMBOL_GOP_FB9_WIDTH,
    SYMBOL_GOP_FB9_HEIGHT,
    SYMBOL_GOP_FB9_PITCH,
    SYMBOL_GOP_FB9_FORMAT,
     SYMBOL_GOP_FB9_STRING,
    SYMBOL_GOP_FB10_STARTADR,
    SYMBOL_GOP_FB10_WIDTH,
    SYMBOL_GOP_FB10_HEIGHT,
    SYMBOL_GOP_FB10_PITCH,
    SYMBOL_GOP_FB10_FORMAT,
     SYMBOL_GOP_FB10_STRING,
    SYMBOL_GOP_FB11_STARTADR,
    SYMBOL_GOP_FB11_WIDTH,
    SYMBOL_GOP_FB11_HEIGHT,
    SYMBOL_GOP_FB11_PITCH,
    SYMBOL_GOP_FB11_FORMAT,
     SYMBOL_GOP_FB11_STRING,
    SYMBOL_GOP_FB12_STARTADR,
    SYMBOL_GOP_FB12_WIDTH,
    SYMBOL_GOP_FB12_HEIGHT,
    SYMBOL_GOP_FB12_PITCH,
    SYMBOL_GOP_FB12_FORMAT,
     SYMBOL_GOP_FB12_STRING,
    SYMBOL_GOP_FB13_STARTADR,
    SYMBOL_GOP_FB13_WIDTH,
    SYMBOL_GOP_FB13_HEIGHT,
    SYMBOL_GOP_FB13_PITCH,
    SYMBOL_GOP_FB13_FORMAT,
     SYMBOL_GOP_FB13_STRING,
    SYMBOL_GOP_FB14_STARTADR,
    SYMBOL_GOP_FB14_WIDTH,
    SYMBOL_GOP_FB14_HEIGHT,
    SYMBOL_GOP_FB14_PITCH,
    SYMBOL_GOP_FB14_FORMAT,
     SYMBOL_GOP_FB14_STRING,
    SYMBOL_GOP_FB15_STARTADR,
    SYMBOL_GOP_FB15_WIDTH,
    SYMBOL_GOP_FB15_HEIGHT,
    SYMBOL_GOP_FB15_PITCH,
    SYMBOL_GOP_FB15_FORMAT,
     SYMBOL_GOP_FB15_STRING,
    SYMBOL_LAST
}DEBUG_SYMBOL;

void Util_InitSymbolTBL(void);
BOOLEAN Util_AddSymbol(DEBUG_SYMBOL symbol, U32 value);
#endif
