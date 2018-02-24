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


#ifndef _TDQG9_601A_H_
#define _TDQG9_601A_H_

#ifdef TDQG9_601A_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define TN_FREQ_STEP                FREQ_STEP_62_5KHz//FREQ_STEP_62_5KHz//FREQ_STEP_50KHz//FREQ_STEP_31_25KHz

#define _TUNER_I2C_ID               0xC0

#define VHF_LOWMIN_FREQ             47000L    // KHz
#define VHF_LOWMAX_FREQ             153000L    // KHz
#define VHF_HIGHMIN_FREQ            153000L    // KHz
#define VHF_HIGHMAX_FREQ            430000L    // KHz
#define UHF_MIN_FREQ                430000L    // KHz
#define UHF_MAX_FREQ                862000L    // KHz

#define TUNER_IF_FREQ_KHz           38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz   33950L    // KHz


#define TN_FREQ_SS_INVERSE_625      16   // 1/0.0625
#define TN_RSA_RSB_625              0x06
#define TN_FREQ_SS_625              62.5  // kHz

#define TN_FREQ_SS_50               50  // kHz
#define TN_FREQ_SS_INVERSE_50       20   // 1/0.05
#define TN_RSA_RSB_50               0


#define TN_LOW_BAND                 0x51
#define TN_MID_BAND                 0x52
#define TN_HIGH_BAND                0x54
#define TN_IF_I2C_ADDR              0x86
#define TN_PROG_I2C_ADDR            0xC2
//****************************************************************************
// Public functions.
//****************************************************************************

#define IF_OUT_LEVEL_PLUS_9_dBM     (7<<3)
#define IF_OUT_LEVEL_PLUS_7_dBM     (6<<3)
#define IF_OUT_LEVEL_PLUS_5_dBM     (5<<3)
#define IF_OUT_LEVEL_PLUS_3_dBM     (4<<3)
#define IF_OUT_LEVEL_PLUS_1_dBM     (3<<3)
#define IF_OUT_LEVEL_MINUS_1_dBM    (2<<3)
#define IF_OUT_LEVEL_MINUS_3_dBM    (1<<3)
#define IF_OUT_LEVEL_Disable        (0<<3)



#define CHARGE_PUMP_150uA           0x60
#define CHARGE_PUMP_350uA           0xA0
#define CHARGE_PUMP_700uA           0xE0
#define CHARGE_PUMP_1200uA          0x00

#define BAND_WIDTH_SWITH_8M         0x04
#define BAND_WIDTH_SWITH_7M         0x00

#define BAND_SWITCH_UHF             0x08
#define BAND_SWITCH_VHF_HIGH        0x02
#define BAND_SWITCH_VHF_LOW         0x01


INTERFACE void devTunerInit(void);
INTERFACE void devTunerSetAntenna(BOOLEAN bIsCATV);
INTERFACE void devTunerSetFreqStep(FREQSTEP eFreqStep);
INTERFACE void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);

#undef INTERFACE
#endif
