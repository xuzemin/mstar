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
/*------------------------------------------------*/
/*  For asia area (China & East South asia),      */
/*  please enable this for non-standard signal !! */
/*------------------------------------------------*/

#define VIF_ASIA_SIGNAL_OPTION          1                   //for Asia non-standard singal

#ifndef VIF_TOP
#define VIF_TOP                         0                   // [3:0], Take Over Point (TOP) adjustment (range 0~15)
#endif
#define VIF_IF_BASE_FREQ                IF_BASE_FREQ        // IF base frequency
#define VIF_TUNER_STEP_SIZE             TN_FREQ_STEP        // Tuner frequency step size
#define VIF_FLAT_SAW                    0                   // 0: Dual SAW; 1: Single SAW
#define VIF_VGA_MAXIMUM                 0x7000              // [15:0], VGA Maximum value
#define VIF_VGA_MINIMUM                 0x8000              // [15:0], VGA Minimum value
#define GAIN_DISTRIBUTION_THR           0x6A00              // [15:0], AGC vga threshold of gain distribution
#define VIF_AGC_VGA_BASE                (GAIN_DISTRIBUTION_THR>>7)                // [7:0], AGC vga base
#define VIF_AGC_VGA_OFFS                0x58                // [7:0], AGC vga offset
#define VIF_AGC_REF_NEGATIVE            0x60                // [7:0], AGC reference level for negative modulation
#define VIF_AGC_REF_POSITIVE            0x19                // [7:0], AGC reference level for positive modulation
#define VIF_DAGC1_REF                   0x26                // [5:0], DAGC1 reference level
#define VIF_DAGC2_REF                   0x26                // [5:0], DAGC2 reference level
#define VIF_DAGC1_GAIN_OV               0x1000              // [13:0], DAGC1 gain for positive modulation
#define VIF_DAGC2_GAIN_OV               0x1000              // [13:0], DAGC2 gain for positive modulation
#define VIF_CR_LOCK_THR                 0x020               // [9:0], Lock threshold of CR
#define VIF_CR_THR                      0x0500              // [13:0], CR threshold
#define VIF_CR_LOCK_NUM                 0x08000             // [19:0], lock number of CR
#define VIF_CR_UNLOCK_NUM               0x04000             // [19:0], Unlock number of CR
#define VIF_CR_PD_ERR_MAX               0x3FFF              // [13:0], Maximum phase error of CR
#define VIF_CR_LOCK_LEAKY_SEL           1                   // 0: lock leaky factor (2^-16); 1: squared lock leaky factor
#define VIF_CR_PD_X2                    1                   // 0: lock 0 degree; 1: lock 0 or 180 degree
#if (VIF_ASIA_SIGNAL_OPTION == 1)
#define VIF_CR_KF1                      0x03                // [3:0], Hardware frequency detection parameter 1 of CR
#define VIF_CR_KP1                      0x03                // [3:0], Hardware proportional loop filter parameter 1 of CR
#define VIF_CR_KI1                      0x03                // [3:0], Hardware integral loop filter parameter 1 of CR
#define VIF_CR_KP2                      0x06                // [3:0], Hardware proportional loop filter parameter 2 of CR
#define VIF_CR_KI2                      0x05                // [3:0], Hardware integral loop filter parameter 2 of CR
#define VIF_CR_KP                       0x06                // [3:0], Software proportional loop filter parameter of CR
#define VIF_CR_KI                       0x09                // [3:0], Software integral loop filter parameter of CR
#define VIF_CR_LPF_SEL                  1                   // 0: LPF1; 1: LPF2
#define VIF_CR_PD_MODE_SEL              0                   // CR PD mode select
#define VIF_CR_KP_KI_ADJUST             1                   // 0: CR Kp/Ki adjust OFF; 1: CR Kp/Ki adjust ON
#define VIF_CR_KP_KI_ADJUST_GEAR        2            // number of gears for auto adjust, only 1, 2 is valid
#define VIF_CR_KP_KI_ADJUST_THR1        0x05                // [7:0] CR Kp/Ki adjust threshold 1
#define VIF_CR_KP_KI_ADJUST_THR2        0x0A                // [7:0] CR Kp/Ki adjust threshold 2
#define VIF_CR_KP_KI_ADJUST_THR3        0x03                // [7:0] CR Kp/Ki adjust threshold 3
#else
#define VIF_CR_KF1                      0x08                // [3:0], Hardware frequency detection parameter 1 of CR
#define VIF_CR_KP1                      0x04                // [3:0], Hardware proportional loop filter parameter 1 of CR
#define VIF_CR_KI1                      0x05                // [3:0], Hardware integral loop filter parameter 1 of CR
#define VIF_CR_KP2                      0x05                // [3:0], Hardware proportional loop filter parameter 2 of CR
#define VIF_CR_KI2                      0x07                // [3:0], Hardware integral loop filter parameter 2 of CR
#define VIF_CR_KP                       0x05                // [3:0], Software proportional loop filter parameter of CR
#define VIF_CR_KI                       0x08                // [3:0], Software integral loop filter parameter of CR
#define VIF_CR_LPF_SEL                  1                   // 0: LPF1; 1: LPF2
#define VIF_CR_PD_MODE_SEL              1                   // CR PD mode select
#define VIF_CR_KP_KI_ADJUST             0                   // 0: CR Kp/Ki adjust OFF; 1: CR Kp/Ki adjust ON
#define VIF_CR_KP_KI_ADJUST_GEAR        2                   // number of gears for auto adjust, only 1, 2 is valid
#define VIF_CR_KP_KI_ADJUST_THR1        0x05                // [7:0] CR Kp/Ki adjust threshold 1
#define VIF_CR_KP_KI_ADJUST_THR2        0x0A                // [7:0] CR Kp/Ki adjust threshold 2
#define VIF_CR_KP_KI_ADJUST_THR3        0x03                // [7:0] CR Kp/Ki adjust threshold 3
#endif
#define VIF_DYNAMIC_TOP_ADJUST          0                   // 0: Dynamic TOP adjust OFF; 1: Dynamic TOP adjust ON
#define VIF_DYNAMIC_TOP_MIN             0                   // [3:0], minimum TOP for Dynamic TOP adjust (range 0~10)
#define VIF_AM_HUM_DETECTION            0                   // 0: not adjust AGC reference level; 1: adjust AGC reference level
#define VIF_CLAMPGAIN_CLAMP_SEL         1                   // 0: clamp select sync bottom; 1: clamp select porch
#define VIF_CLAMPGAIN_SYNCBOTT_REF      0x78                // [7:0], Porch or syncbottom reference level
#define VIF_CLAMPGAIN_SYNCHEIGHT_REF    0x68                // [7:0], Syncheight reference level
#define VIF_CLAMPGAIN_KC                0x07                // [2:0], Clamp loop filter parameter
#define VIF_CLAMPGAIN_KG                0x07                // [2:0], Gain loop filter parameter
#define VIF_CLAMPGAIN_CLAMP_OREN        1                   // 0: clamp overwrite disable; 1: clamp overwrite enable
#define VIF_CLAMPGAIN_GAIN_OREN         1                   // 0: gain overwrite disable; 1: gain overwrite enable
#define VIF_CLAMPGAIN_CLAMP_OV_NEGATIVE 0x750               // [10:0], Clamp overwrite value for negative modulation
#define VIF_CLAMPGAIN_GAIN_OV_NEGATIVE  0x600               // [10:0], Gain overwrite value for negative modulation
#define VIF_CLAMPGAIN_CLAMP_OV_POSITIVE 0x5F0               // [10:0], Clamp overwrite value for positive modulation
#define VIF_CLAMPGAIN_GAIN_OV_POSITIVE  0x5F0               // [10:0], Gain overwrite value for positive modulation
#define VIF_CLAMPGAIN_CLAMP_MIN         0x80                // [7:0], Clamp minimum value
#define VIF_CLAMPGAIN_CLAMP_MAX         0x00                // [7:0], Clamp maximum value
#define VIF_CLAMPGAIN_GAIN_MIN          0x40                // [7:0], Gain minimum value
#define VIF_CLAMPGAIN_GAIN_MAX          0xFF                // [7:0], Gain maximum value
#define VIF_CLAMPGAIN_PORCH_CNT         0x0C8               // [8:0], Porch counter
#define VIF_PEAKING_FILTER_BG           5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_BG          1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_BG       2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_DK           5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_DK          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_DK       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_I            5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_I           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_I        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_L            0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_L           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_L        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_LL           0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_LL          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_LL       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_MN           3                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_MN          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_MN       6                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define CHINA_DESCRAMBLER_BOX           0                   // Use descrambler box in China; 0: not use; 1: use
#define VIF_DELAY_REDUCE                0x01                // [7:0], [0]: reduce filter delay; [1]: reduce DAGC1 delay; [2]: reduce DAGC2 delay;
#define VIF_OVER_MODULATION             0                   // Support non-standard overmodulation for negative modulation
#define VIF_SOS21_FILTER_C0             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C1             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C2             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C3             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C4             0x0200              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS22_FILTER_C0             0x0000              // [10:0], User define coefficient of SOS22 filter
#define VIF_SOS22_FILTER_C1             0x0000              // [10:0], User define coefficient of SOS22 filter
#define VIF_SOS22_FILTER_C2             0x0000              // [10:0], User define coefficient of SOS22 filter
#define VIF_SOS22_FILTER_C3             0x0000              // [10:0], User define coefficient of SOS22 filter
#define VIF_SOS22_FILTER_C4             0x0200              // [10:0], User define coefficient of SOS22 filter
#define VIF_SOS31_FILTER_C0             0x0000              // [10:0], User define coefficient of SOS31 filter
#define VIF_SOS31_FILTER_C1             0x0000              // [10:0], User define coefficient of SOS31 filter
#define VIF_SOS31_FILTER_C2             0x0000              // [10:0], User define coefficient of SOS31 filter
#define VIF_SOS31_FILTER_C3             0x0000              // [10:0], User define coefficient of SOS31 filter
#define VIF_SOS31_FILTER_C4             0x0200              // [10:0], User define coefficient of SOS31 filter
#define VIF_SOS32_FILTER_C0             0x0000              // [10:0], User define coefficient of SOS32 filter
#define VIF_SOS32_FILTER_C1             0x0000              // [10:0], User define coefficient of SOS32 filter
#define VIF_SOS32_FILTER_C2             0x0000              // [10:0], User define coefficient of SOS32 filter
#define VIF_SOS32_FILTER_C3             0x0000              // [10:0], User define coefficient of SOS32 filter
#define VIF_SOS32_FILTER_C4             0x0200              // [10:0], User define coefficient of SOS32 filter







