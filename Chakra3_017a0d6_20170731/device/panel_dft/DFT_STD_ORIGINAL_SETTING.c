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
#if ENABLE_DLC


#if DLC_PARAMETER_ALGORITHM_MODE   //for NEW DLC ALGORITHM

#include "New_NoOS_DLC.c"

#else //for OLD DLC ALGORITHM

static MS_U8 tLumaCurve[16] =
//    { 0x06, 0x0F, 0x1E, 0x2D, 0x41, 0x59, 0x6D, 0x7B, 0x8B, 0x9A, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
//    { 0x06, 0x12, 0x23, 0x37, 0x4B, 0x5A, 0x6C, 0x7C, 0x8D, 0x9B, 0xAA, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
//	{ 0x05, 0x10, 0x1C, 0x2D, 0x42, 0x5A, 0x6D, 0x7F, 0x8D, 0x9A, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
    { 0x05, 0x0D, 0x18, 0x29, 0x40, 0x5A, 0x76, 0x88, 0x94, 0x9F, 0xA9, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 }; // for A5

static MS_U8 tLumaCurve2_a[16] =
//    { 0x06, 0x13, 0x21, 0x32, 0x43, 0x56, 0x66, 0x76, 0x85, 0x95, 0xA4, 0xB5, 0xC5, 0xD8, 0xE8, 0xF8 };
//    { 0x03, 0x0F, 0x23, 0x39, 0x4F, 0x5F, 0x71, 0x81, 0x8F, 0x9A, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
//	{ 0x05, 0x11, 0x1D, 0x2A, 0x3B, 0x4D, 0x60, 0x73, 0x85, 0x97, 0xA7, 0xB7, 0xC8, 0xD8, 0xE8, 0xF8 };
    { 0x04, 0x0E, 0x1F, 0x32, 0x45, 0x56, 0x66, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC8, 0xD8, 0xE8, 0xF8 }; // for A5

static MS_U8 tLumaCurve2_b[16] =
//    { 0x04, 0x1C, 0x32, 0x43, 0x53, 0x61, 0x70, 0x7C, 0x8A, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
//    { 0x0D, 0x25, 0x38, 0x48, 0x59, 0x65, 0x70, 0x7C, 0x8A, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
//	{ 0x06, 0x24, 0x3B, 0x4B, 0x59, 0x65, 0x70, 0x7C, 0x8A, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 };
    { 0x03, 0x16, 0x2D, 0x43, 0x55, 0x62, 0x6D, 0x79, 0x89, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8 }; // for A5

static MS_U8 tDlcSlopLimit[17] =
    {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x50, 0x60, 0x60, 0x60, 0x60 };
    //{ 0x88, 0x90, 0x93, 0x92, 0x8E, 0x89, 0x84, 0x80, 0x7E, 0x7D, 0x7E, 0x81, 0x85, 0x88, 0x8B, 0x8C, 0x8A };
    
#endif



#endif // #if ENABLE_DLC

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

#include "Gamma12BIT_256.c" // include Gamma Talbe
//====================================================================================



