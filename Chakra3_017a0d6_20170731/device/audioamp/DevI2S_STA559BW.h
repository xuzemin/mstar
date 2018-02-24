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
/******************************************************************************
 Copyright (c) 2006 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DevI2S_STA559BW.h
 [Date]:        11-July-2006
 [Comment]:
   I2S STA559 header file.
 [Reversion History]:
*******************************************************************************/

#ifndef _DEV_STA559BW_
#define _DEV_STA559BW_

#define STA559BW_ADDR						0x38

#define STA559BW_REG_A                     0x00
#define STA559BW_REG_B                     0x05
#define STA559BW_REG_C                     0x07
#define STA559BW_REG_D                     0x08
#define STA559BW_REG_E                     0x09

#define USE_2p1_MODE     					0	//  1：2.1声道   0：  2.0声道
/***********************************************************************************
              Channel volume  gain
   range from 0xFF to 0xED ,	Hard channel mute
   range from 0xEC to 0x60 ,  gain :	-80 DB  to 0 DB  (0.5DB per step)
   range from 0x5F to 0x00 ,  gain :	+0.5 DB to +48 DB (0.5DB per step)
************************************************************************************/
#define Volume_Output_Power_is_3W			0x40
#define Volume_Output_Power_is_8W			0x38
#if (USE_2p1_MODE)
#define Volume_Output_Power             	Volume_Output_Power_is_8W
#else
#define Volume_Output_Power             	Volume_Output_Power_is_8W
#endif
#define SubWoofer_Output_Power          	0x60
/***********************************************************************************
//     系统输入IIS采样采样频率（sample rates）
The STA559BW supports sample rates of 32 KHz, 44.1 KHz, 48 KHz, 88.2 KHz, 96 KHz,
176.4 KHz, and 192 KHz. Therefore the internal clock is:
● 32.768 MHz for 32 KHz
● 45.1584 MHz for 44.1 KHz, 88.2 KHz, and 176.4 KHz
● 49.152 MHz for 48 KHz, 96 KHz, and 192 KHz

internal colock 						input sample rate							Reg_ConfigA
32.768 Mhz									32 KHz										0x61
45.1584 MHz									44.1 KHz									0x61
45.1584 MHz									88.2 KHz									0x63
45.1584 MHz									176.4 KHz									0x64
49.152 MHz                    				48 KHz										0x61
49.152 MHz                    				96 KHz										0x63
49.152 MHz                    				192 KHz										0x64
************************************************************************************/
#define SYSTEM_IIS_Sample_Rate 				0x63
/***********************************************************************************
//     占用一个I/O
************************************************************************************/
#define STA559BW_ResetPin_H      Audio_Amplifier_ON()   // 根据使用使用的状态更改////
#define STA559BW_ResetPin_L      Audio_Amplifier_OFF()  // 根据使用使用的状态更改//

#ifdef AUDIO_AMP
    #define  AUDIO_EXT
#else
    #define  AUDIO_EXT  extern
#endif

AUDIO_EXT void STA559BW_Initial(void);
AUDIO_EXT void STA335BW_Mute(BOOLEAN Enable);

//******************************************************************************

#endif
