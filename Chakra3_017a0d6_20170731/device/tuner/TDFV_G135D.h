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

/******************************************************************************
 Copyright (c) 2004 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: TDFV_G135D.c
 [Date]:        9-Jun-2008
 [Comment]:
   TV tuner header file.
 [Reversion History]:
*******************************************************************************/

#ifndef _TDFV_G135D_H_
#define _TDFV_G135D_H_


#ifdef TDFV_G135D_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//****************************************************************************
// Public attributes.
//****************************************************************************

//??
#define _TUNER_I2C_ID       0xC2

#define VHF_LOWMIN_FREQ     45250L  // KHz
#define VHF_LOWMAX_FREQ     147000L//140250L // KHz
#define VHF_HIGHMIN_FREQ    147250L // KHz
#define VHF_HIGHMAX_FREQ    431000L//423250L // KHz
#define UHF_MIN_FREQ        431250L // KHz
#define UHF_MAX_FREQ        863250L//855250L // KHz

#define TUNER_IF_FREQ_KHz           38900L  // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz   33900L  // KHz


// XTOUT output buffer and mode setting                 T2 T1 T0
#define _CB1_T_XTOUT_BUFFER_OFF     0x00    //  0    0    0
#define _CB1_T_XTOUT_BUFFER_ON      0x08    //  0    0    1
#define _CB1_T_CP_OFF                   0x10    //  0    1    0
#define _CB1_T_ALBC_ON_OFF          0x18    //  0    1    1
#define _CB1_T_TM_FREQ_DIV              0x20    //  1    0    0
#define _CB1_T_TM_FREQ_COMP         0x28    //  1    0    1
#define _CB1_T_CP_SINKING_CURRENT       0x30    //  1    1    0     : default
#define _CB1_T_CP_SOURCING_CURRENT      0x38    //  1    1    1

// Charge pump current                  CP2 CP1 CP0
#define _CB2_CP_38uA            0x00    //  0   0   0
#define _CB2_CP_54uA            0x20    //  0   0   1
#define _CB2_CP_83uA            0x40    //  0   1   0
#define _CB2_CP_122uA       0x60    //  0   1   1
#define _CB2_CP_163uA       0x80    //  1   0   0
#define _CB2_CP_254uA       0xA0    //  1   0   1
#define _CB2_CP_400uA       0xC0    //  1   1   0
#define _CB2_CP_580uA       0xE0    //  1   1   1   : default

// Reference divider ratios                             R2 R1 R0
#define _CB1_FREQ_STEP_62p5KHz      0x00    //  0   0   0
#define _CB1_FREQ_STEP_142p86KHz        0x01    //  0   0   1
#define _CB1_FREQ_STEP_166p67KHz        0x02    //  0   1   0
#define _CB1_FREQ_STEP_50KHz            0x03    //  0   1   1
#define _CB1_FREQ_STEP_125KHz           0x04    //  1   0   0

// Conrtol Byte1 Exclusive Bit set
#define _CB1_MSB_BIT        0x80

// Test and AGC Bit
#define _CB1_TEST_SEL       0x40
#define _CB1_AGC_SEL            0x00    // default

// Band selection   //<NHK_070801_135D_Setting>
#define _CB2_BAND_SWITCH_UHF                    0x1C//0x18
#define _CB2_BAND_SWITCH_VHF_HIGH           0x06//0x02
#define _CB2_BAND_SWITCH_VHF_LOW            0x05//0x01

// AGC time constant
#define _CB1_ATC_220nA_2s_150nF         0x00    // default
#define _CB1_ATC_9uA_50ms_150nF         0x08

// AGC take-over point                                      //  AL2 AL1 AL0
#define _CB1_IF_OUTPUT_LEVEL_124dBuV            0x00    //  0   0   0
#define _CB1_IF_OUTPUT_LEVEL_121dBuV            0x01    //  0   0   1
#define _CB1_IF_OUTPUT_LEVEL_118dBuV            0x02    //  0   1   0
#define _CB1_IF_OUTPUT_LEVEL_115dBuV            0x03    //  0   1   1
#define _CB1_IF_OUTPUT_LEVEL_112dBuV            0x04    //  1   0   0
#define _CB1_IF_OUTPUT_LEVEL_109dBuV            0x05    //  1   0   1   : default
#define _CB1_IF_OUTPUT_LEVEL_DISABLED           0x06    //  1   1   0
#define _CB1_IF_OUTPUT_DETECT_DISABLED          0x07    //  1   1   1

//****************************************************************************
// Public functions.
//****************************************************************************

INTERFACE void devTunerInit( void );
INTERFACE void devTunerSetFreqStep( FREQSTEP eFreqStep );
INTERFACE void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);

#undef INTERFACE
#endif
