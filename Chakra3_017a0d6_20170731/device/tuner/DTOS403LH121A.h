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
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DevTuner.h
 [Date]:        30-Jun-2008
 [Comment]:
   TV tuner header file.
 [Reversion History]:
*******************************************************************************/

#ifndef _DTOS403LH121A_H_
#define _DTOS403LH121A_H_

#ifdef DTOS403LH121A_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


//#ifdef TN_FREQ_STEP
//#undef TN_FREQ_STEP
//#endif
#define I2CGROUPSEL 0x0200  // 0x0200 :Group 2
#define TUNER_I2C_WRITE_ADDR   0xC2  //Address selection pin is NC, so ADB=0xC2
#define TUNER_I2C_READ_ADDR   0xC3

#define TUNER_ATV_TN_FREQ_STEP      FREQ_STEP_50KHz// FREQ_STEP_50KHz
#define TUNER_DTV_TN_FREQ_STEP       FREQ_STEP_166_67KHz//FREQ_STEP_166_67KHz //FREQ_STEP_62_5KHz

//Bit Location of registers
//Control Byte
#define CP_BITLOC_STARTFROM 6
#define T2T1_BITLOC_STARTFROM 4
#define T0_BITLOC_STARTFROM 3
#define RSARSB_BITLOC_STARTFROM 1
//AB
#define AL2_0_BITLOC_STARTFROM 4
#define AGC_TC_BITLOC_STARTFROM 7



//IF Bandwidth of SAW filter
#define IF_8M_INTERNAL_SAW_FILTER_BW 0x04  //bit2:1 8MHz  0: 7MHz

//Used for ATV PAL
#define VHF_LOWMIN_FREQ        48250L    // KHz  PAL:48250
#define VHF_LOWMAX_FREQ        168250L    // KHz  PAL:168250
#define VHF_HIGHMIN_FREQ    175250L    // KHz PAL:175250
#define VHF_HIGHMAX_FREQ    463250L    // KHz PAL:463250
#define UHF_MIN_FREQ        471250L    // KHz  PAL: 471250
#define UHF_MAX_FREQ        863250L    // KHz PAL:863250

//Used for DTV (MHz)
#define DTV_VHF_LOWMIN_FREQ        50.5L
#define DTV_VHF_LOWMAX_FREQ        170.5L
#define DTV_VHF_HIGHMIN_FREQ    177.5L
#define DTV_VHF_HIGHMAX_FREQ    466L
#define DTV_UHF_MIN_FREQ        474L
#define DTV_UHF_MAX_FREQ        858L

//IF Frequency output
#define TUNER_IF_FREQ_KHz            38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz    33950L    // KHz
#define DIGITAL_TUNER_IF    36.167L

#define DIVIDER_RATIO_50KHz     0x00
#define DIVIDER_RATIO_31_25KHz  0x01
#define DIVIDER_RATIO_166_67KHz  0x02
#define DIVIDER_RATIO_62_5KHz   0x03
#define DIVIDER_RATIO_125KHz   0x0C
#define DIVIDER_RATIO_142_86KHz   0x0D

#define DTOS403_EXTENDED_MODE 0x03
#define DTOS403_NORMAL_MODE 0x00

#define NM_FREQ_BOUNDRY   1000

#define EXTMODE_FREQ_BOUNDRY1 121.5L
#define EXTMODE_FREQ_BOUNDRY2 142.5L
#define EXTMODE_FREQ_BOUNDRY3 177.5L
#define EXTMODE_FREQ_BOUNDRY4 322L
#define EXTMODE_FREQ_BOUNDRY5 422L
#define EXTMODE_FREQ_BOUNDRY6 474L
#define EXTMODE_FREQ_BOUNDRY7 714L
#define EXTMODE_FREQ_BOUNDRY8 810L

//TakeOver point
#define AL2to0_115dBuV 0x1  //0x0 and 0x01 are the same take-over point
#define AL2to0_112dBuV 0x2
#define AL2to0_109dBuV 0x3
#define AL2to0_106dBuV 0x4
#define AL2to0_103dBuV 0x5
#define AL2to0_ExternAGC 0x6
#define AL2to0_DisableAGCDector 0x7
#define RFAGC_TAKEOVER_MODE (AL2to0_106dBuV<<AL2_0_BITLOC_STARTFROM)

//RF AGC Time Constant
#define AGC_TC_DEFAULT 0x0
#define AGC_TC_SEARCH 0x1
#define RFAGC_TC_MODE (AGC_TC_DEFAULT<<AGC_TC_BITLOC_STARTFROM)

/* for ATV */
#if (TUNER_ATV_TN_FREQ_STEP == FREQ_STEP_31_25KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_31_25KHz
#elif (TUNER_ATV_TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TUNER_ATV_TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#elif (TUNER_ATV_TN_FREQ_STEP == FREQ_STEP_166_67KHz)
#define DIVIDER_RATIO  DIVIDER_RATIO_166_67KHz
#elif (TUNER_ATV_TN_FREQ_STEP == FREQ_STEP_125KHz)
#define DIVIDER_RATIO  DIVIDER_RATIO_125KHz
#elif(TUNER_ATV_TN_FREQ_STEP ==FREQ_STEP_142_86KHz )
#define DIVIDER_RATIO  DIVIDER_RATIO_142_86KHz
#endif

/* for DTV */
#if (TUNER_DTV_TN_FREQ_STEP == FREQ_STEP_31_25KHz)
#define DTOS403_MODE DTOS403_NORMAL_MODE
#define COEFF_INTEGER 32 //  1000/31.25
#define COEFF_FINETUNE 0
#define RSA_RSB 0x01  //Reference Divider Ratio
#elif (TUNER_DTV_TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DTOS403_MODE DTOS403_NORMAL_MODE
#define COEFF_INTEGER 20 //1000/50
#define COEFF_FINETUNE 0
#define RSA_RSB 0x00
#elif (TUNER_DTV_TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DTOS403_MODE DTOS403_EXTENDED_MODE
#define COEFF_INTEGER 16 //1000/62.5
#define COEFF_FINETUNE 0
#define RSA_RSB 0x03
#elif (TUNER_DTV_TN_FREQ_STEP == FREQ_STEP_166_67KHz)
#define DTOS403_MODE DTOS403_EXTENDED_MODE
#define COEFF_INTEGER 6  //  1000/166.67
#define COEFF_FINETUNE 0.5
#define RSA_RSB 0x02
#elif (TUNER_DTV_TN_FREQ_STEP == FREQ_STEP_125KHz)
#define DTOS403_MODE DTOS403_EXTENDED_MODE
#define COEFF_INTEGER 8  //  1000/125
#define COEFF_FINETUNE 0
#define RSA_RSB 0x00
#elif(TUNER_DTV_TN_FREQ_STEP ==FREQ_STEP_142_86KHz )
#define DTOS403_MODE DTOS403_EXTENDED_MODE
#define COEFF_INTEGER 6  //  1000/142.86
#define COEFF_FINETUNE 0.5
#define RSA_RSB 0x01
#endif

#define T0 0x0
#define OS 0x0  //Tunning Amplifier Control Bit, 0:Enable 1:Disable

#define CONTROL_BYTE_SETTING 0x80 | (DTOS403_MODE<<T2T1_BITLOC_STARTFROM) | \
                                                (T0 <<T0_BITLOC_STARTFROM) | \
                                                (RSA_RSB <<RSARSB_BITLOC_STARTFROM) |  \
                                                (OS)


//****************************************************************************
// Public functions.
//****************************************************************************
INTERFACE void devTunerInit(void);
INTERFACE void devTunerSetFreqStep(FREQSTEP eFreqStep);
INTERFACE void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);
INTERFACE void devTunerReadPLLReg( U8 *pRegData,U8 u8RegNum);

#undef INTERFACE
#endif

