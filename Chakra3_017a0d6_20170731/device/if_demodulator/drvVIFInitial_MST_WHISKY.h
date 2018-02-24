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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _DRVVIFINITIAL_MST_EDEN_H_
#define _DRVVIFINITIAL_MST_EDEN_H_
#include "Tuner.h"
/*------------------------------------------------*/
/*  For Asia area (China & East South Asia),      */
/*  please enable this for non-standard signal !! */
/*------------------------------------------------*/

#define VIF_ASIA_SIGNAL_OPTION	        1                   // for Asia non-standard singal

#ifndef VIF_TUNER_TYPE
#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#endif

#define VIF_IF_BASE_FREQ                IF_BASE_FREQ        // IF base frequency
#define VIF_TUNER_STEP_SIZE   	        TN_FREQ_STEP        // Tuner frequency step size

#ifndef VIF_SAW_ARCH
#if (VIF_TUNER_TYPE == 0)
#define VIF_SAW_ARCH                    3                   // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF)
#else
#define VIF_SAW_ARCH                    2                   // silicon tuner
#endif
#endif

#if(VIF_SAW_ARCH == 1 || VIF_SAW_ARCH==2)       // [3:0], Take Over Point (TOP) adjustment (range 0~15)
#define VIF_TOP              	        3  		            // [3:0], Take Over Point (TOP) adjustment (range 0~15)
#elif(VIF_SAW_ARCH == 0)
#define VIF_TOP              	        3  		            // [3:0], Take Over Point (TOP) adjustment (range 0~15)
#else
#define VIF_TOP              	        3  		            // [3:0], Take Over Point (TOP) adjustment (range 0~15)
#endif

#define VIF_TUNER_INTERNAL_RF_AGC      0                  // 0: Not Use,1: Use
#define VIF_VGA_MAXIMUM   	 	        0x7000              // [15:0], VGA Maximum value

#if(VIF_TUNER_INTERNAL_RF_AGC == 1)
#define VIF_VGA_MINIMUM   	 	        0x6000              // [15:0], VGA Minimum value
#else
#define VIF_VGA_MINIMUM   	 	        0x8000              // [15:0], VGA Minimum value
#endif

#define GAIN_DISTRIBUTION_THR 	        (VIF_VGA_MAXIMUM - 0x600)              // [15:0], AGC vga threshold of gain distribution
#define VIF_AGC_VGA_BASE                (GAIN_DISTRIBUTION_THR>>7)                // [7:0], AGC vga base
#define VIF_AGC_VGA_OFFS                0x40                // [7:0], AGC vga offset

#if(VIF_SAW_ARCH == 1 || VIF_SAW_ARCH==2)
#define VIF_AGC_REF_NEGATIVE   	        0x70                // [7:0], AGC reference level for negative modulation
#elif(VIF_SAW_ARCH == 0)
#define VIF_AGC_REF_NEGATIVE   	        0x60                // [7:0], AGC reference level for negative modulation
#else
#define VIF_AGC_REF_NEGATIVE   	        0x60                // [7:0], AGC reference level for negative modulation
#endif

#if(VIF_SAW_ARCH == 3 || VIF_SAW_ARCH == 5)
#define VIF_AGC_REF_POSITIVE   	        0x15                // [7:0], AGC reference level for positive modulation
#else
#define VIF_AGC_REF_POSITIVE   	        0x19                // [7:0], AGC reference level for positive modulation
#endif

#define VIF_DAGC1_REF   	            0x26                // [5:0], DAGC1 reference level
#define VIF_DAGC2_REF   	            0x26                // [5:0], DAGC2 reference level

#if(VIF_SAW_ARCH == 1 || VIF_SAW_ARCH==2)
#define VIF_DAGC1_GAIN_OV   	        0x1800              // [13:0], DAGC1 gain for positive modulation  //marco 20090918
#define VIF_DAGC2_GAIN_OV   	        0x1800              // [13:0], DAGC2 gain for positive modulation  //marco 20090918
#elif(VIF_SAW_ARCH == 0)
#define VIF_DAGC1_GAIN_OV   	        0x1000              // [13:0], DAGC1 gain for positive modulation
#define VIF_DAGC2_GAIN_OV   	        0x1000              // [13:0], DAGC2 gain for positive modulation
#else
#define VIF_DAGC1_GAIN_OV   	        0x1800              // [13:0], DAGC1 gain for positive modulation
#define VIF_DAGC2_GAIN_OV   	        0x1800              // [13:0], DAGC2 gain for positive modulation
#endif

#define VIF_CR_LOCK_THR                 0x020               // [9:0], Lock threshold of CR
#define VIF_CR_THR                      0x0500              // [13:0], CR threshold
#define VIF_CR_LOCK_NUM                 0x08000             // [19:0], lock number of CR
#define VIF_CR_UNLOCK_NUM               0x04000             // [19:0], Unlock number of CR
#define VIF_CR_PD_ERR_MAX               0x3FFF              // [13:0], Maximum phase error of CR
#define VIF_CR_LOCK_LEAKY_SEL           1                   // 0: lock leaky factor (2^-16); 1: squared lock leaky factor
#define VIF_CR_PD_X2                    1                   // 0: lock 0 degree; 1: lock 0 or 180 degree

#if (VIF_ASIA_SIGNAL_OPTION == 1)
#define VIF_CR_KF1   	                0x03                // [3:0], Hardware frequency detection parameter 1 of CR
#define VIF_CR_KP1   	                0x03                // [3:0], Hardware proportional loop filter parameter 1 of CR
#define VIF_CR_KI1   	                0x03                // [3:0], Hardware integral loop filter parameter 1 of CR
#define VIF_CR_KP2   	                0x06                // [3:0], Hardware proportional loop filter parameter 2 of CR
#define VIF_CR_KI2   	                0x05                // [3:0], Hardware integral loop filter parameter 2 of CR
#define VIF_CR_KP   	                0x06                // [3:0], Software proportional loop filter parameter of CR
#define VIF_CR_KI   	                0x09                // [3:0], Software integral loop filter parameter of CR
#define VIF_CR_LPF_SEL                  1                   // 0: LPF1; 1: LPF2
#define VIF_CR_PD_MODE_SEL              0                   // CR PD mode select
#define VIF_CR_KP_KI_ADJUST             1                   // 0: CR Kp/Ki adjust OFF; 1: CR Kp/Ki adjust ON
#define VIF_CR_KP_KI_ADJUST_GEAR        2		            // number of gears for auto adjust, only 1, 2 is valid
#define VIF_CR_KP_KI_ADJUST_THR1        0x05                // [7:0] CR Kp/Ki adjust threshold 1
#define VIF_CR_KP_KI_ADJUST_THR2        0x10                // [7:0] CR Kp/Ki adjust threshold 2
#define VIF_CR_KP_KI_ADJUST_THR3        0x03                // [7:0] CR Kp/Ki adjust threshold 3
#else
#define VIF_CR_KF1   	                0x08                // [3:0], Hardware frequency detection parameter 1 of CR
#define VIF_CR_KP1   	                0x04                // [3:0], Hardware proportional loop filter parameter 1 of CR
#define VIF_CR_KI1   	                0x05                // [3:0], Hardware integral loop filter parameter 1 of CR
#define VIF_CR_KP2   	                0x05                // [3:0], Hardware proportional loop filter parameter 2 of CR
#define VIF_CR_KI2   	                0x07                // [3:0], Hardware integral loop filter parameter 2 of CR
#define VIF_CR_KP   	                0x05                // [3:0], Software proportional loop filter parameter of CR
#define VIF_CR_KI   	                0x08                // [3:0], Software integral loop filter parameter of CR
#define VIF_CR_LPF_SEL                  1                   // 0: LPF1; 1: LPF2
#define VIF_CR_PD_MODE_SEL              1                   // CR PD mode select
#define VIF_CR_KP_KI_ADJUST             0                   // 0: CR Kp/Ki adjust OFF; 1: CR Kp/Ki adjust ON
#define VIF_CR_KP_KI_ADJUST_GEAR        2		            // number of gears for auto adjust, only 1, 2 is valid
#define VIF_CR_KP_KI_ADJUST_THR1        0x05                // [7:0] CR Kp/Ki adjust threshold 1
#define VIF_CR_KP_KI_ADJUST_THR2        0x10                // [7:0] CR Kp/Ki adjust threshold 2
#define VIF_CR_KP_KI_ADJUST_THR3        0x03                // [7:0] CR Kp/Ki adjust threshold 3
#endif

#define VIF_DYNAMIC_TOP_ADJUST          0                   // 0: Dynamic TOP adjust OFF; 1: Dynamic TOP adjust ON
#define VIF_DYNAMIC_TOP_MIN    	        0  		            // [3:0], minimum TOP for Dynamic TOP adjust (range 0~10)
#define VIF_AM_HUM_DETECTION            0                   // 0: not adjust AGC reference level; 1: adjust AGC reference level
#define VIF_CLAMPGAIN_CLAMP_SEL         1                   // 0: clamp select sync bottom; 1: clamp select porch
#define VIF_CLAMPGAIN_SYNCBOTT_REF      0x78                // [7:0], Porch or syncbottom reference level
#define VIF_CLAMPGAIN_SYNCHEIGHT_REF    0x68                // [7:0], Syncheight reference level
#define VIF_CLAMPGAIN_KC                0x07                // [2:0], Clamp loop filter parameter
#define VIF_CLAMPGAIN_KG                0x07                // [2:0], Gain loop filter parameter
#define VIF_CLAMPGAIN_CLAMP_OREN        1                   // 0: clamp overwrite disable; 1: clamp overwrite enable
#define VIF_CLAMPGAIN_GAIN_OREN         1                   // 0: gain overwrite disable; 1: gain overwrite enable
#define VIF_CLAMPGAIN_CLAMP_OV_NEGATIVE 0x750               // [10:0], Clamp overwrite value for negative modulation
#define VIF_CLAMPGAIN_CLAMP_OV_POSITIVE 0x5F0               // [10:0], Clamp overwrite value for positive modulation

#if(VIF_SAW_ARCH == 1 || VIF_SAW_ARCH==2)
#define VIF_CLAMPGAIN_GAIN_OV_NEGATIVE  0x600               // [10:0], Gain overwrite value for negative modulation
#define VIF_CLAMPGAIN_GAIN_OV_POSITIVE  0x650               // [10:0], Gain overwrite value for positive modulation
#elif(VIF_SAW_ARCH == 0)
#define VIF_CLAMPGAIN_GAIN_OV_NEGATIVE  0x5F0               // [10:0], Gain overwrite value for negative modulation
#define VIF_CLAMPGAIN_GAIN_OV_POSITIVE  0x4F0               // [10:0], Gain overwrite value for positive modulation
#elif(VIF_SAW_ARCH == 5)
#define VIF_CLAMPGAIN_GAIN_OV_NEGATIVE  0x6B0               // [10:0], Gain overwrite value for negative modulation
#define VIF_CLAMPGAIN_GAIN_OV_POSITIVE  0x300               // [10:0], Gain overwrite value for positive modulation
#else
#define VIF_CLAMPGAIN_GAIN_OV_NEGATIVE  0x6B0               // [10:0], Gain overwrite value for negative modulation
#define VIF_CLAMPGAIN_GAIN_OV_POSITIVE  0x650               // [10:0], Gain overwrite value for positive modulation
#endif

#define VIF_CLAMPGAIN_CLAMP_MIN         0x80                // [7:0], Clamp minimum value
#define VIF_CLAMPGAIN_CLAMP_MAX         0x00                // [7:0], Clamp maximum value
#define VIF_CLAMPGAIN_GAIN_MIN          0x40                // [7:0], Gain minimum value
#define VIF_CLAMPGAIN_GAIN_MAX          0xFF                // [7:0], Gain maximum value
#define VIF_CLAMPGAIN_PORCH_CNT         0x0C8               // [8:0], Porch counter
#define VIF_PEAKING_FILTER_B_VHF_L              0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_B_VHF_L           1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_B_VHF_L        2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_GH_VHF_L           0                    // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_GH_VHF_L          1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_GH_VHF_L       2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_DK_VHF_L           5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_DK_VHF_L          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_DK_VHF_L       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_I_VHF_L            5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_I_VHF_L           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_I_VHF_L        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_L_VHF_L            0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_L_VHF_L           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_L_VHF_L        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_LL_VHF_L           0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_LL_VHF_L          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_LL_VHF_L       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_MN_VHF_L           0x80                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_MN_VHF_L          0x80                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_MN_VHF_L       0x80                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_B_VHF_H            0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_B_VHF_H           1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_B_VHF_H        2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_GH_VHF_H           0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_GH_VHF_H          1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_GH_VHF_H       2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_DK_VHF_H           5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_DK_VHF_H          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_DK_VHF_H       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_I_VHF_H            5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_I_VHF_H           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_I_VHF_H        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_L_VHF_H            0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_L_VHF_H           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_L_VHF_H        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_LL_VHF_H           0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_LL_VHF_H          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_LL_VHF_H       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_MN_VHF_H           3                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_MN_VHF_H          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_MN_VHF_H       6                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_B_UHF            6                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_B_UHF           1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_B_UHF        2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_GH_UHF           6                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_GH_UHF          1                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_GH_UHF       2                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_DK_UHF           5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_DK_UHF          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_DK_UHF       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_I_UHF            5                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_I_UHF           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_I_UHF        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_L_UHF            0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_L_UHF           0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_L_UHF        0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_LL_UHF           0                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_LL_UHF          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_LL_UHF       0                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define VIF_PEAKING_FILTER_MN_UHF           3                   // [7:0], 0: (null) peaking filter; 1: 1dB peaking filter; 2: 2dB peaking filter; 3: 3dB peaking filter; 4: 4dB peaking filter; 5: (VSB) 3dB peaking filter; 6: (VSB) 4dB peaking filter; 7: (VSB) 5dB peaking filter; 0x80: User define SOS21 filter
#define VIF_YC_DELAY_FILTER_MN_UHF          0                   // [7:0], 0: (null) Y/C delay filter; 1: (VSB) Y/C delay filter; 0x80: User define SOS22 filter
#define VIF_GROUP_DELAY_FILTER_MN_UHF       6                   // [7:0], 0: (null) group delay filter; 1: (VSB) group delay filter (LG); 2: (VSB) group delay filter (Philips); 3: (Low_R) group delay filter; 4: (Low_L) group delay filter; 5: (High_R) group delay filter; 6: (High_L) group delay filter; 0x80: User define SOS31/SOS32 filters
#define CHINA_DESCRAMBLER_BOX               0                   // Use descrambler box in China; 0:not use; 1:IMAGE_IIR(0x99); 2:IMAGE_REJ1(0x8A); 3:ACI_REJ(0x89); 4:MIXER_OUT_I(0x86); 5:IMAGE_REJ2(0x8b)
#define VIF_DELAY_REDUCE                    0x00                // [7:0], [0]: reduce filter delay; [1]: reduce DAGC1 delay; [2]: reduce DAGC2 delay;
#define VIF_OVER_MODULATION                 0                   // Support heavy 200% overmodulation when PD_mode = 1
#define VIF_OM_DETECTOR                     0                   //  Switch PD_mode from 0 to 1 to support >100%
#define VIF_ACI_DETECTOR                    0                   // (Not used) 0:Not detect ACI ; 1:detect ACI
#define VIF_ACI_AGC_REF                     0x30                // (Not used) AGC reference level for ACI
#define VIF_ACIDET_THR1                     0x16                // (Not used) Upper threshold for N-1 ACI
#define VIF_ACIDET_THR2                     0x0A                // (Not used) Bottom threshold for N-1 ACI
#define VIF_ACIDET_THR3                     0x08                // (Not used) Upper threshold for N+1 ACI
#define VIF_ACIDET_THR4                     0x03                // (Not used) Bottom threshold for N+1 ACI
#define VIF_ADC_OVERFLOW_AGC_REF            0x20                // AGC reference level for serious ACI
#define VIF_SERIOUS_ACI_DETECTION		    0                   // No SAW serious ACI detect enable
#define VIF_CHANEL_SCAN_AGC_REF             0x60                // No SAW AGC reference level for channel scan
#if(FRONTEND_TUNER_TYPE==RAFAEL_R828_TUNER)
#define VIF_SOS21_FILTER_C0             0x02E0              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C1             0x068F              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C2             0x01E1              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C3             0x0520              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C4             0x0190              // [10:0], User define coefficient of SOS21 filter

#elif(FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
#define VIF_SOS21_FILTER_C0             0x02E0              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C1             0x068F              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C2             0x01E1              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C3             0x0520              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C4             0x0190
#elif(FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
#define VIF_SOS21_FILTER_C0             0x02E0              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C1             0x068F              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C2             0x01E1              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C3             0x0520              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C4             0x0190
#else
#define VIF_SOS21_FILTER_C0             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C1             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C2             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C3             0x0000              // [10:0], User define coefficient of SOS21 filter
#define VIF_SOS21_FILTER_C4             0x0200              // [10:0], User define coefficient of SOS21 filter
#endif
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

#if (VIF_TUNER_TYPE == 0)
#define VIF_CR_RATE_B                   0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x00000000          // [21:0], CR_RATE for 7.02 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x00000000          // [21:0], CR_RATE for 1.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#else
#if (FRONTEND_TUNER_TYPE==NXP_TDA18273_TUNER)
#define VIF_CR_RATE_B                   0x00097B42          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x00080000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000A25ED          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000ABDA1          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x00080000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x0001DA12          // [21:0], CR_RATE for 7.02 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x00080000          // [21:0], CR_RATE for 1.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#elif (FRONTEND_TUNER_TYPE==NXP_TDA18274_TUNER)
#define VIF_CR_RATE_B                   0x00097B42          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x00080000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000A25ED          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000ABDA1          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x00080000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x0001DA12          // [21:0], CR_RATE for 7.02 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x00080000          // [21:0], CR_RATE for 1.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#elif (FRONTEND_TUNER_TYPE==NXP_TDA18275_TUNER)
#define VIF_CR_RATE_B                   0x000A5ED0 // 4.15+2.25M   // [21:0], CR_RATE for 6.4 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x000A5ED0//4+2.75M       // [21:0], CR_RATE for 6.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000BDA12//4.1+2.75M   // [21:0], CR_RATE for 7.85 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000B1C71//4.5+2.75M          // [21:0], CR_RATE for 7.25 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x000A0000// 4+2.75M   // [21:0], CR_RATE for 6.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x0001DA12//4+2.75M  // [21:0], CR_RATE for 1.25 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                1                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x0008E38E//3.65+1.75M  // [21:0], CR_RATE for 5.4 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#elif((FRONTEND_TUNER_TYPE==SILAB_2158_TUNER)||(FRONTEND_TUNER_TYPE==SILAB_2190B_TUNER))
#define VIF_CR_RATE_B                   0x000A5ED1 // 4.75M + 2.25M   // [21:0], CR_RATE for 7.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                       // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x000A5ED1 // 4.25M + 2.75M       // [21:0], CR_RATE for 7.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000BDA13 // 5.25M + 2.75M   // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000B1C72 // 4.75M + 2.75M          // [21:0], CR_RATE for 7.5 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x000BDA13 // 5.25M + 2.75M   // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x000BDA13 // 5.25M + 2.75M  // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x0008E38E // 4.25 + 1.75M  // [21:0], CR_RATE for 6.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#elif (FRONTEND_TUNER_TYPE == RAFAEL_R828_TUNER)
#define VIF_CR_RATE_B                   0x00092F68//0x00024079          // [21:0], CR_RATE for 6.2 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x0009C71C//0x00024079          // [21:0], CR_RATE for 6.6 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000AD097//0x000A25ED     // [21:0], CR_RATE for 7.3 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000AD097//0x00024079          // [21:0], CR_RATE for 7.3 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x000A5ED0//0x00024079          // [21:0], CR_RATE for 6.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x0001F49F          // [21:0], CR_RATE for 1.25 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                1                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x00078E38          // [21:0], CR_RATE for 5.1 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#elif (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
// Analog picture carrier
#define ATV_VC_MN  6750L
#define ATV_VC_B   7250L
#define ATV_VC_GH  7750L
#define ATV_VC_I   7750L
#define ATV_VC_DK  7750L
#define ATV_VC_L   7750L
#define ATV_VC_LL  2250L

#define VIF_CR_RATE_B                   (DWORD)(ATV_VC_B*4194304.0/43200.0+0.5)          // [21:0], CR_RATE for 6.2 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  (DWORD)(ATV_VC_GH*4194304.0/43200.0+0.5)          // [21:0], CR_RATE for 6.6 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  (DWORD)(ATV_VC_DK*4194304.0/43200.0+0.5)     // [21:0], CR_RATE for 7.3 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   (DWORD)(ATV_VC_I*4194304.0/43200.0+0.5)          // [21:0], CR_RATE for 7.3 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   (DWORD)(ATV_VC_L*4194304.0/43200.0+0.5)          // [21:0], CR_RATE for 6.75 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  (DWORD)(ATV_VC_LL*4194304.0/43200.0+0.5)          // [21:0], CR_RATE for 1.25 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                1                   // Video carrier position; 0: high side; 1:low side
//NTSC M 5.8MHZ
#define VIF_CR_RATE_MN                  (DWORD)(ATV_VC_MN*4194304.0/43200.0+0.5) // [21:0], CR_RATE for 5.1 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#else  //move setting to tuner side
#ifndef VIF_CR_RATE_B
#define VIF_CR_RATE_B                   0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_B
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#endif
#ifndef VIF_CR_RATE_GH
#define VIF_CR_RATE_GH                  0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_GH
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#endif
#ifndef VIF_CR_RATE_DK
#define VIF_CR_RATE_DK                  0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_DK
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#endif
#ifndef VIF_CR_RATE_I
#define VIF_CR_RATE_I                   0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_I
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#endif
#ifndef VIF_CR_RATE_L
#define VIF_CR_RATE_L                   0x00000000          // [21:0], CR_RATE for 1.52 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_L
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#endif
#ifndef VIF_CR_RATE_LL
#define VIF_CR_RATE_LL                  0x00000000          // [21:0], CR_RATE for 7.02 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_LL
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#endif
#ifndef VIF_CR_RATE_MN
#define VIF_CR_RATE_MN                  0x00000000          // [21:0], CR_RATE for 1.75 MHz, HEX((xxx/43.2) * (2^22))
#endif
#ifndef VIF_CR_INVERT_MN
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#endif

#endif
#endif

#endif //_DRVVIFINITIAL_MST_Eden_H_

