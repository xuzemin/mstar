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
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
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
 Copyright (c) 2009 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DTZ0W302.h
 [Date]:        30-Aug-2009
 [Comment]:
   CHENGDU XUGUANG's tuner subroutine
 [Reversion History]:
*******************************************************************************/


#ifndef DTZ0W302_H
#define DTZ0W302_H


#define _TUNER_I2C_ID        0xC0


#define VHF_LOWMIN_FREQ        49000L    // KHz
#define VHF_LOWMAX_FREQ        152250L//164000L    // KHz
#define VHF_HIGHMIN_FREQ    157000L//160250L//164000L    // KHz
#define VHF_HIGHMAX_FREQ    424250L//444000L    // KHz
#define UHF_MIN_FREQ        432250L//444000L    // KHz
#define UHF_MAX_FREQ        861250L    // KHz

#define TUNER_IF_FREQ_KHz            38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz    33950L    // KHz
#define TUNER_DMB_IF_FREQ_KHz            36125L//36130L    // KHz

#define TN_FREQ_SS_INVERSE_625          16   // 1/0.0625
#define TN_RSA_RSB_625                  0x06
#define TN_FREQ_SS_625                  62.5  // kHz

#define TN_FREQ_SS_50                  50  // kHz
#define TN_FREQ_SS_INVERSE_50         20   // 1/0.05
#define TN_RSA_RSB_50                  0




#define TN_LOW_BAND     0x51
#define TN_MID_BAND     0x52
#define TN_HIGH_BAND    0x54
#define TN_IF_I2C_ADDR      0x86
#define TN_PROG_I2C_ADDR    0xC2

#define IF_OUT_LEVEL_120        0
#define IF_OUT_LEVEL_118        1
#define IF_OUT_LEVEL_116        2
#define IF_OUT_LEVEL_114        3
#define IF_OUT_LEVEL_112        4
#define IF_OUT_LEVEL_110        5
#define IF_OUT_LEVEL_107        6
#define IF_OUT_LEVEL_104        7


#define CHARGE_PUMP_155uA         (0<<5)
#define CHARGE_PUMP_330uA         (1<<5)
#define CHARGE_PUMP_690uA         (2<<5)
#define CHARGE_PUMP_1450uA        (3<<5)


#define TN_DIG_7M_LOW_BAND         0x0d
#define TN_DIG_7M_MID_BAND         0x4e
#define TN_DIG_7M_HIGH_BAND        0x88

#define TN_DIG_8M_LOW_BAND         0x05
#define TN_DIG_8M_MID_BAND         0x46
#define TN_DIG_8M_HIGH_BAND        0x80

//****************************************************************************
// Public functions.
//****************************************************************************

void devTunerInit(void);
void devTunerSetFreqStep(FREQSTEP eFreqStep);
void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);


#endif

