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
//#define _MSVIF_C_

//
#if 0 //if build VIF lib, please enable the header file include.
#include "drvGlobal.h"
#include "MsVIF.h"
#include "MsVIF_Customer.h"
#include "Tuner.h"
#endif

#include "asmCPU.h"

VIFInitialIn xdata VIFInitialIn_inst;
void msVifCrKpKiAdjust(WORD VifCrKpKiAdjustSample, WORD VifCrKpKiAdjustDelay);
void msVifCrKpKiSwitch(DWORD LfFfMaxDiff, DWORD LfFfMaxInstDiff, BYTE VifCrKpKiAdjustThr1, BYTE VifCrKpKiAdjustThr2, BYTE VifCrKpKiAdjustThr3);
#define VIF_Delay1ms(x)                MAsm_CPU_DelayMs(x)
#define VIF_Delay1us(x)                  MAsm_CPU_DelayUs(x)
#define HALVIFDBG_BIT       0x101006L  // Bit 4~7
//==================================================
// VIF version
code unsigned char VIF_Version[] =
{
    DASH, DASH, CHIP_TYPE, DASH, VIF_VERSION1, VIF_VERSION2, VIF_VERSION3, DASH,
    DAY1, DAY2, MON1, MON2, YEAR1, YEAR2, DASH,
    P4_CHANGE_LIST_NUM1, P4_CHANGE_LIST_NUM2, P4_CHANGE_LIST_NUM3, P4_CHANGE_LIST_NUM4, P4_CHANGE_LIST_NUM5, P4_CHANGE_LIST_NUM6, P4_CHANGE_LIST_NUM7, P4_CHANGE_LIST_NUM8
};
//==================================================

code RegUnitType VIF_GDE_PEAKING_1dB[]=
{
    {SOS21_C0_L,0xc1},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x87},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x08},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x3f},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0x70},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_2dB[]=
{
    {SOS21_C0_L,0xa4},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x8e},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x12},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x5c},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0x60},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_3dB[]=
{
    {SOS21_C0_L,0xc1},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x87},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x1c},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x3f},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0x5d},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_4dB[]=
{
    {SOS21_C0_L,0xc1},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x87},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x28},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x3f},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0x51},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_3dB_VSB[]=
{
    {SOS21_C0_L,0xf5},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x23},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x07},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x0b},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0xd5},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_4dB_VSB[]=
{
    {SOS21_C0_L,0xf5},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x23},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x0a},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x0b},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0xd2},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_5dB_VSB[]=
{
    {SOS21_C0_L,0xf5},  // SOS21 peaking
    {SOS21_C0_H,0x02},
    {SOS21_C1_L,0x23},
    {SOS21_C1_H,0x06},
    {SOS21_C2_L,0x0e},
    {SOS21_C2_H,0x02},
    {SOS21_C3_L,0x0b},
    {SOS21_C3_H,0x05},
    {SOS21_C4_L,0xcf},
    {SOS21_C4_H,0x01},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_PEAKING_NULL[]=
{
    {SOS21_C0_L,0x00},  // SOS21
    {SOS21_C0_H,0x00},
    {SOS21_C1_L,0x00},
    {SOS21_C1_H,0x00},
    {SOS21_C2_L,0x00},
    {SOS21_C2_H,0x00},
    {SOS21_C3_L,0x00},
    {SOS21_C3_H,0x00},
    {SOS21_C4_L,0x00},
    {SOS21_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_YCDelay_VSB[]=
{
    {SOS22_C0_L,0x15},  // SOS22 Y/C delay
    {SOS22_C0_H,0x02},
    {SOS22_C1_L,0x84},
    {SOS22_C1_H,0x06},
    {SOS22_C2_L,0x7c},
    {SOS22_C2_H,0x01},
    {SOS22_C3_L,0xeb},
    {SOS22_C3_H,0x05},
    {SOS22_C4_L,0x00},
    {SOS22_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_YCDelay_NULL[]=
{
    {SOS22_C0_L,0x00},  // SOS22
    {SOS22_C0_H,0x00},
    {SOS22_C1_L,0x00},
    {SOS22_C1_H,0x00},
    {SOS22_C2_L,0x00},
    {SOS22_C2_H,0x00},
    {SOS22_C3_L,0x00},
    {SOS22_C3_H,0x00},
    {SOS22_C4_L,0x00},
    {SOS22_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_Low_R[]=
{
    {SOS31_C0_L,0xcc},  // SOS31
    {SOS31_C0_H,0x00},
    {SOS31_C1_L,0x6c},
    {SOS31_C1_H,0x07},
    {SOS31_C2_L,0x94},
    {SOS31_C2_H,0x00},
    {SOS31_C3_L,0x34},
    {SOS31_C3_H,0x07},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0xb4},  // SOS32
    {SOS32_C0_H,0x02},
    {SOS32_C1_L,0xf8},
    {SOS32_C1_H,0x06},
    {SOS32_C2_L,0x08},
    {SOS32_C2_H,0x01},
    {SOS32_C3_L,0x4c},
    {SOS32_C3_H,0x05},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_Low_L[]=
{
    {SOS31_C0_L,0x3c},  // SOS31
    {SOS31_C0_H,0x02},
    {SOS31_C1_L,0xb8},
    {SOS31_C1_H,0x06},
    {SOS31_C2_L,0x48},
    {SOS31_C2_H,0x01},
    {SOS31_C3_L,0xc4},
    {SOS31_C3_H,0x05},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0xd9},  // SOS32
    {SOS32_C0_H,0x02},
    {SOS32_C1_L,0xf7},
    {SOS32_C1_H,0x06},
    {SOS32_C2_L,0x0a},
    {SOS32_C2_H,0x01},
    {SOS32_C3_L,0x28},
    {SOS32_C3_H,0x05},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_High_R[]=
{
    {SOS31_C0_L,0xcc},  // SOS31
    {SOS31_C0_H,0x00},
    {SOS31_C1_L,0x6c},
    {SOS31_C1_H,0x07},
    {SOS31_C2_L,0x94},
    {SOS31_C2_H,0x00},
    {SOS31_C3_L,0x34},
    {SOS31_C3_H,0x07},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0xc7},  // SOS32
    {SOS32_C0_H,0x02},
    {SOS32_C1_L,0xd8},
    {SOS32_C1_H,0x06},
    {SOS32_C2_L,0x28},
    {SOS32_C2_H,0x01},
    {SOS32_C3_L,0x39},
    {SOS32_C3_H,0x05},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_High_L[]=
{
    {SOS31_C0_L,0xcc},  // SOS31
    {SOS31_C0_H,0x00},
    {SOS31_C1_L,0x6c},
    {SOS31_C1_H,0x07},
    {SOS31_C2_L,0x94},
    {SOS31_C2_H,0x00},
    {SOS31_C3_L,0x34},
    {SOS31_C3_H,0x07},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0xb0},  // SOS32
    {SOS32_C0_H,0x02},
    {SOS32_C1_L,0x13},
    {SOS32_C1_H,0x07},
    {SOS32_C2_L,0xed},
    {SOS32_C2_H,0x00},
    {SOS32_C3_L,0x50},
    {SOS32_C3_H,0x05},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_VSB_LG[]=
{
    {SOS31_C0_L,0xab},  // SOS31
    {SOS31_C0_H,0x02},
    {SOS31_C1_L,0x9b},
    {SOS31_C1_H,0x06},
    {SOS31_C2_L,0x65},
    {SOS31_C2_H,0x01},
    {SOS31_C3_L,0x55},
    {SOS31_C3_H,0x05},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0xe1},  // SOS32
    {SOS32_C0_H,0x02},
    {SOS32_C1_L,0xf7},
    {SOS32_C1_H,0x06},
    {SOS32_C2_L,0x0a},
    {SOS32_C2_H,0x01},
    {SOS32_C3_L,0x1f},
    {SOS32_C3_H,0x05},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_VSB_Philips[]=
{
    {SOS31_C0_L,0x9f},  // SOS31
    {SOS31_C0_H,0x02},
    {SOS31_C1_L,0xa8},
    {SOS31_C1_H,0x06},
    {SOS31_C2_L,0x58},
    {SOS31_C2_H,0x01},
    {SOS31_C3_L,0x62},
    {SOS31_C3_H,0x05},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0xcd},  // SOS32
    {SOS32_C0_H,0x02},
    {SOS32_C1_L,0x05},
    {SOS32_C1_H,0x07},
    {SOS32_C2_L,0xfb},
    {SOS32_C2_H,0x00},
    {SOS32_C3_L,0x33},
    {SOS32_C3_H,0x05},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
code RegUnitType VIF_GDE_GroupDelay_NULL[]=
{
    {SOS31_C0_L,0x00},  // SOS31
    {SOS31_C0_H,0x00},
    {SOS31_C1_L,0x00},
    {SOS31_C1_H,0x00},
    {SOS31_C2_L,0x00},
    {SOS31_C2_H,0x00},
    {SOS31_C3_L,0x00},
    {SOS31_C3_H,0x00},
    {SOS31_C4_L,0x00},
    {SOS31_C4_H,0x02},
    {SOS32_C0_L,0x00},  // SOS32
    {SOS32_C0_H,0x00},
    {SOS32_C1_L,0x00},
    {SOS32_C1_H,0x00},
    {SOS32_C2_L,0x00},
    {SOS32_C2_H,0x00},
    {SOS32_C3_L,0x00},
    {SOS32_C3_H,0x00},
    {SOS32_C4_L,0x00},
    {SOS32_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};

// #if (IF_BASE_FREQ == IF_FREQ_45_75 || IF_BASE_FREQ == IF_FREQ_38_90)
code RegUnitType VIF_PAL_BG_A2[]=
{
    {N_A1_C0_L,0x24}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0xa8},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x36}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x95},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // PAL B/G A2
};
code RegUnitType VIF_SECAM_L_NICAM[]=
{
    {N_A1_C0_L,0x68}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x60},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x3e}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x8d},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // SECAM L NICAM
};
code RegUnitType VIF_SECAM_LL_NICAM[]=
{
    {N_A1_C0_L,0x7f}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x48},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x59}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x70},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // SECAM L' NICAM
};
code RegUnitType VIF_PAL_I_NICAM[]=
{
    {N_A1_C0_L,0x49}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x82},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x6b}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x5d},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // PAL I NICAM
};
code RegUnitType VIF_SECAM_DK1_A2[]=
{
    {N_A1_C0_L,0x68}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x60},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x5a}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x70},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // SECAM D/K1 A2
};
code RegUnitType VIF_PAL_DK2_A2[]=
{
    {N_A1_C0_L,0x68}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x60},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x76}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x51},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // PAL D/K2 A2
};
code RegUnitType VIF_SECAM_DK3_A2[]=
{
    {N_A1_C0_L,0x68}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x60},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x36}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x95},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // SECAM D/K3 A2
};
// #else // (IF_BASE_FREQ == IF_FREQ_38_00)
code RegUnitType VIF_PAL_BG_A2_FREQ_38_00[]=
{
    {N_A1_C0_L,0x0c}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0xc2},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x20}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0xad},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // PAL B/G A2
};
code RegUnitType VIF_PAL_I_NICAM_FREQ_38_00[]=
{
    {N_A1_C0_L,0x33}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x98},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x59}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x70},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // PAL I NICAM
};
code RegUnitType VIF_SECAM_DK1_A2_FREQ_38_00[]=
{
    {N_A1_C0_L,0x56}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x74},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x46}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x85},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // SECAM D/K1 A2
};
code RegUnitType VIF_PAL_DK2_A2_FREQ_38_00[]=
{
    {N_A1_C0_L,0x56}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x74},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x65}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x64},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // PAL D/K2 A2
};
code RegUnitType VIF_SECAM_DK3_A2_FREQ_38_00[]=
{
    {N_A1_C0_L,0x56}, // Notch_A1
    {N_A1_C0_H,0x03},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x74},
    {N_A1_C2_H,0x04},
    {N_A2_C0_L,0x20}, // Notch_A2
    {N_A2_C0_H,0x03},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0xad},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // SECAM D/K3 A2
};
// #endif
code RegUnitType VIF_GDE_BG_NOTCH[]=
{
    {N_A3_C0_L,0xb4}, // Notch_A3
    {N_A3_C0_H,0x02},
    {N_A3_C1_L,0x1e},
    {N_A3_C1_H,0x06},
    {N_A3_C2_L,0x37},
    {N_A3_C2_H,0x05},
    {N_A4_C0_L,0x9b}, // Notch_A4
    {N_A4_C0_H,0x02},
    {N_A4_C1_L,0x1e},
    {N_A4_C1_H,0x06},
    {N_A4_C2_L,0x51},
    {N_A4_C2_H,0x05},
    {_END_OF_TBL_,0x00}, // PAL B/G A2
};

// #if (IF_BASE_FREQ == IF_FREQ_45_75)
code RegUnitType VIF_NTSC_MN_A2_FREQ_45_75[]=
{
    {N_A1_C0_L,0xb7}, // Notch_A1
    {N_A1_C0_H,0x02},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x1c},
    {N_A1_C2_H,0x05},
    {N_A2_C0_L,0xcd}, // Notch_A2
    {N_A2_C0_H,0x02},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x06},
    {N_A2_C2_H,0x05},
    {_END_OF_TBL_,0x00}, // NTSC M/N A2
};
// #elif (IF_BASE_FREQ == IF_FREQ_38_90)
code RegUnitType VIF_NTSC_MN_A2[]=
{
    {N_A1_C0_L,0xcf}, // Notch_A1
    {N_A1_C0_H,0x02},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x03},
    {N_A1_C2_H,0x05},
    {N_A2_C0_L,0xe4}, // Notch_A2
    {N_A2_C0_H,0x02},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0xed},
    {N_A2_C2_H,0x04},
    {_END_OF_TBL_,0x00}, // NTSC M/N A2
};
code RegUnitType VIF_NOTCH_SOS11[]=
{
    {SOS11_C0_L,0xcf}, // SOS11
    {SOS11_C0_H,0x02},
    {SOS11_C1_L,0x3c},
    {SOS11_C1_H,0x06},
    {SOS11_C2_L,0x00},
    {SOS11_C2_H,0x02},
    {SOS11_C3_L,0x03},
    {SOS11_C3_H,0x05},
    {SOS11_C4_L,0x00},
    {SOS11_C4_H,0x02},
    {_END_OF_TBL_,0x00},
};
// #else // (IF_BASE_FREQ == IF_FREQ_38_00)
code RegUnitType VIF_NTSC_MN_A2_FREQ_38_00[]=
{
    {N_A1_C0_L,0xb2}, // Notch_A1
    {N_A1_C0_H,0x02},
    {N_A1_C1_L,0x3c},
    {N_A1_C1_H,0x06},
    {N_A1_C2_L,0x21},
    {N_A1_C2_H,0x05},
    {N_A2_C0_L,0xc8}, // Notch_A2
    {N_A2_C0_H,0x02},
    {N_A2_C1_L,0x3c},
    {N_A2_C1_H,0x06},
    {N_A2_C2_L,0x0b},
    {N_A2_C2_H,0x05},
    {_END_OF_TBL_,0x00}, // NTSC M/N A2
};
// #endif

void msVIFversion(void)
{
    // VIF version
    printf("\r\n[VIF Version]: ");
    printf("%s",VIF_Version);
    printf("\r\n");
}

#if FORCE_SWITCH_BANK
void msVIFSetBypassVIF(BOOL bVal)
{
    g_bBypassVIF = bVal;
}

BOOL msVIFCheckBypassVIF(void)
{
    return g_bBypassVIF;
}

void msVifSwitch2VifBank(void)
{
    // change PM
    msWriteByte(0x100000L, 0x10);
    msWriteByte(0x100001L, 0x00);
    // switch to VIF <-> DVBC
    msWriteByte(0x1002C0L, 0x01);
    msWriteByte(0x1002C1L, 0x00);
}
#endif

void msWriteRegsTbl(MS_VIF_REG_TYPE *pRegTable)
{
    U16 u16Dummy;
    U32 u32Address;
    U8  u8Value;

    u16Dummy = 2000;

    do
    {
        u32Address = pRegTable->u32Address;
        u8Value = pRegTable->u8Value;
        if (u32Address == 0xFFFF)  // check end of table
            break;
        MDrv_WriteByte(u32Address, u8Value);
        pRegTable++;
    } while (--u16Dummy > 0);
}

void msVifAdcInitial(void)
{
#if FORCE_SWITCH_BANK
    // this global variable should be controlled by HK
    msVIFSetBypassVIF(FALSE);
    if (msVIFCheckBypassVIF()) return;
#endif

    // CVBS DAC output
    msWriteByte(0x10258CL, 0xC0);  // [7] enable CVBS DAC out
    msWriteByte(0x10258DL, 0x80);  // DAC output level, [7:4]gain, [3:0]offset
    msWriteByte(0x102570L, 0x5C);
    msWriteByte(0x102572L, 0x0B);
    msWriteByte(0x102573L, 0x0B);
    msWriteByte(0x102574L, 0x00);
    msWriteByte(0x102575L, 0x00);
    msWriteByte(0x102576L, 0x00);
    msWriteByte(0x102577L, 0x00);
    msWriteByte(0x102578L, 0x5C);
    msWriteByte(0x10257AL, 0x0B);
    msWriteByte(0x10257BL, 0x0B);
    msWriteByte(0x10257CL, 0x00);
    msWriteByte(0x10257DL, 0x00);
    msWriteByte(0x10257EL, 0x00);
    msWriteByte(0x10257FL, 0x00);
//    msWriteByte(0x102CB0L, 0x00);   // switch DAGC sram
//    msWriteByte(0x102CB1L, 0x01);
    msWriteByteMask(0x102CB1L, 0x01,_BIT0); //berlin 20091013
#if FORCE_SWITCH_BANK
    // switch to VIF bank
    msVifSwitch2VifBank();
#else
    msWriteByte(0x100000L, 0x10);
    msWriteByte(0x100001L, 0x00);
    msWriteByte(0x1002C0L, 0x01);
    msWriteByte(0x1002C1L, 0x00);
#endif

    // AU_TOP
    msWriteByte(0x100E66L, 0x02);	// MPLL multiplier = XTAL*0x24h/2=216MHz
    msWriteByte(0x100E67L, 0x09);
    msWriteByte(0x100E68L, 0x02);	// MPLL enable
    msWriteByte(0x100E69L, 0x00);
    msWriteByte(0x100E6AL, 0x40);   // power on MPLL path in vif_adc_top
    msWriteByte(0x100E6BL, 0x00);
    msWriteByte(0x100E00L, 0xFF);	// all pwr = 1
    msWriteByte(0x100E01L, 0xFF);
    msWriteByte(0x100E02L, 0x14);
    msWriteByte(0x100E03L, 0x90);
    msWriteByte(0x100E40L, 0x00);	// ADC power down off
    msWriteByte(0x100E41L, 0x00);
    msWriteByte(0x100E70L, 0x06);
    msWriteByte(0x100E71L, 0x00);
    msWriteByte(0x100E72L, 0x06);
    msWriteByte(0x100E73L, 0x0C);
    msWriteByte(0x100E14L, 0x55);  // VIF TAGC PADs output enable Key : h'aa55
    msWriteByte(0x100E15L, 0xAA);
    
    msWriteByte(0x100E54L, 0x00);    
    msWriteByte(0x100E55L, 0x00);    
    msWriteByte(0x100E56L, 0x00);    
    msWriteByte(0x100E57L, 0x00);    
    msWriteByte(0x100E5CL, 0x01);    
    msWriteByte(0x100E5DL, 0x00);    
    msWriteByte(0x100E60L, 0x00);    
    msWriteByte(0x100E61L, 0x07);    

    //Set IF Min Gain
    msWriteByteMask(0x101E0BL, 0x02, 0x03);  // RF AGC enable IF AGC enable
    msWriteBit(0x1002A2L, 1, _BIT5);   // enable VIF-IF PWM
    msWriteByte(0x1002A6L, 0x00); //reg_vif_if_agc_manual_7_0
    msWriteByte(0x1002A8L, 0x00); //reg_vif_if_agc_manual_15_8
}

void msVifLpfCalibration(void)
{
    BYTE ucCount = 3;

#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    while(ucCount--)
    {
        msWriteBit(VIF_RN_TUNE, 0, _BIT5);  // reset
        VIF_Delay1ms(1);
        msWriteBit(VIF_RN_TUNE, 1, _BIT5);
        VIF_Delay1ms(1);
        if (_bit5_(msReadByte(VIF_STOPCAL_TUNE)))
            break;
    }
}

BOOL msVifVcoCalibration(void)
{
    BYTE ucCount1 = 2;
    BYTE ucCount2 = 20;

#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    while (ucCount1--)
    {
        msWriteBit(VIF_CAL_START, 1, _BIT7); //  VCO band calibration start

        while (ucCount2--)
        {
            VIF_Delay1us(1);

            if (_bit6_(msReadByte(VIF_CAL_FINISH)))
            {
                if (_bit7_(msReadByte(VIF_VCOCAL_FAIL)))
                    break;
                if (_bit6_(msReadByte(VIF_VCTRL_OVER)))
                    break;
                if (_bit5_(msReadByte(VIF_VCTRL_UNDER)))
                    break;
                if (!_bit4_(msReadByte(VIF_LOCK)))
                    break;
                else
                    return 1;
            }
        }
    }
    return 0;
}

// For API
void msVifSetIfFreq(IfFrequencyType ucIfFreq)
{
#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    // cvbs output
    msWriteBit(VIFDAC_ENABLE, 1, _BIT3);                // enable vifdac

    // for China descrambler box
    if (VIFInitialIn_inst.ChinaDescramblerBox == 1)
    {
        msWriteByteMask(VIFDAC_OUT_SEL, 0x04, 0x07);    // 0: cvbs output; 4: debug bus
        msWriteBit(DEBUG2_EN, 1, _BIT7);                // select debug2 data
        msWriteByte(DEBUG_PORT, 0x8A);			        // select CVBS output after IMAGE_REJ1
        msWriteByteMask(DEBUG_MODULE, 0x00, 0x0F);      // select filter debug bus
    } else {
        msWriteByteMask(VIFDAC_OUT_SEL, 0x00, 0x07);    // 0: cvbs output; 4: debug bus
    }

    // LPF calibration
    msWriteByte(VIF_FCAL_DIV, 0x08);                    // Filter calibration clock divider(/N, from 2 to 63)
    msWriteByte(VIF_TUNEC, 0x12);                       // Fine tuning filter center frequency
    msVifLpfCalibration();

    // IF frequency
    msWriteBit(VIF_PLL_MSEL, 0, _BIT5);                 // bypass feedback divider re-sync function
    msWriteBit(VSYNC_VD_MASK, 0, _BIT0);                // enable VCO closed loop calibration

    switch(ucIfFreq)
    {
        case IF_FREQ_3395:
            msWriteByteMask(VIF_PLL_N, 0x2B, 0x3F);     // N
            msWriteBit(VIF_PLL_FBBYP, 1, _BIT7);        // bypass divid-by-2 in feedback divider
            msWriteBit(VIF_PLL_RSEL, 0, _BIT7);         // reference divider
            msWriteBit(VIF_PLL_RDIV, 0, _BIT6);         // PLL reference divider
            msWriteByteMask(VIF_PLL_M, 0x03, 0x0F);     // M
            msWriteBit(VIF_PLL_PBYP, 0, _BIT5);         // divid-by-2 in post divider
            break;
        case IF_FREQ_3800:
            msWriteByteMask(VIF_PLL_N, 0x2F, 0x3F);     // N
            msWriteBit(VIF_PLL_FBBYP, 1, _BIT7);        // bypass divid-by-2 in feedback divider
            msWriteBit(VIF_PLL_RSEL, 0, _BIT7);         // reference divider
            msWriteBit(VIF_PLL_RDIV, 0, _BIT6);         // PLL reference divider
            msWriteByteMask(VIF_PLL_M, 0x05, 0x0F);     // M
            msWriteBit(VIF_PLL_PBYP, 0, _BIT5);         // divid-by-2 in post divider
            break;
        case IF_FREQ_3890:
            msWriteByteMask(VIF_PLL_N, 0x31, 0x3F);     // N
            msWriteBit(VIF_PLL_FBBYP, 1, _BIT7);        // bypass divid-by-2 in feedback divider
            msWriteBit(VIF_PLL_RSEL, 0, _BIT7);         // reference divider
            msWriteBit(VIF_PLL_RDIV, 0, _BIT6);         // PLL reference divider
            msWriteByteMask(VIF_PLL_M, 0x05, 0x0F);     // M
            msWriteBit(VIF_PLL_PBYP, 0, _BIT5);         // divid-by-2 in post divider
            break;
        case IF_FREQ_3950:
            msWriteByteMask(VIF_PLL_N, 0x31, 0x3F);     // N
            msWriteBit(VIF_PLL_FBBYP, 1, _BIT7);        // bypass divid-by-2 in feedback divider
            msWriteBit(VIF_PLL_RSEL, 0, _BIT7);         // reference divider
            msWriteBit(VIF_PLL_RDIV, 0, _BIT6);         // PLL reference divider
            msWriteByteMask(VIF_PLL_M, 0x05, 0x0F);     // M
            msWriteBit(VIF_PLL_PBYP, 0, _BIT5);         // divid-by-2 in post divider
            break;
        case IF_FREQ_4575:
            msWriteByteMask(VIF_PLL_N, 0x30, 0x3F);     // N
            msWriteBit(VIF_PLL_FBBYP, 1, _BIT7);        // bypass divid-by-2 in feedback divider
            msWriteBit(VIF_PLL_RSEL, 0, _BIT7);         // reference divider
            msWriteBit(VIF_PLL_RDIV, 0, _BIT6);         // PLL reference divider
            msWriteByteMask(VIF_PLL_M, 0x04, 0x0F);     // M
            msWriteBit(VIF_PLL_PBYP, 0, _BIT5);         // divid-by-2 in post divider
            break;
        case IF_FREQ_5875:
            msWriteByteMask(VIF_PLL_N, 0x31, 0x3F);     // N
            msWriteBit(VIF_PLL_FBBYP, 1, _BIT7);        // bypass divid-by-2 in feedback divider
            msWriteBit(VIF_PLL_RSEL, 0, _BIT7);         // reference divider
            msWriteBit(VIF_PLL_RDIV, 0, _BIT6);         // PLL reference divider
            msWriteByteMask(VIF_PLL_M, 0x03, 0x0F);     // M
            msWriteBit(VIF_PLL_PBYP, 0, _BIT5);         // divid-by-2 in post divider
            break;
        default:
            break;
    }

    // VCO calibration
    msVifVcoCalibration();

    // TAGC
    msWriteBit(VIF_TAGC_PWR, 1, _BIT6);                 // TAGC power on
    msWriteBit(VIF_TAGC_ODMODE, 0, _BIT7);				// 0: 1mA current sink output; 1: open-drain voltage output
    msWriteBit(TAGC_SEL_SECONDER, 1, _BIT6);	        // 0: 1st order, 1: 2nd order
    msWriteBit(TAGC_DITHER_EN, 1, _BIT7);	            // dither disable
    msWriteBit(TAGC_POLARITY, 0, _BIT4);                // TAGC polarity 0: negative logic
    msWriteBit(OREN_TAGC, 0, _BIT5);		            // TAGC 0: BB control; 1: I2C control
    msWriteBit(OREN_PGA1_V, 0, _BIT3);                  // Video PGA1 0: BB control; 1: I2C control
    msWriteBit(OREN_PGA2_V, 0, _BIT2);                  // Video PGA2 0: BB control; 1: I2C control
    msWriteBit(OREN_PGA1_S, 0, _BIT1);                  // Audio PGA1 0: BB control; 1: I2C control
    msWriteBit(OREN_PGA2_S, 0, _BIT0);                  // Audio PGA2 0: BB control; 1: I2C control
}

void msVifGroupDelayFilter(BYTE VifPeakingFilter, BYTE VifYcDelayFilter, BYTE VifGroupDelayFilter)
{
#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    if (VifPeakingFilter == 0x00) {
        msWriteRegsTbl(VIF_GDE_PEAKING_NULL);
    } else if (VifPeakingFilter == 0x01) {
        msWriteRegsTbl(VIF_GDE_PEAKING_1dB);
    } else if (VifPeakingFilter == 0x02) {
        msWriteRegsTbl(VIF_GDE_PEAKING_2dB);
    } else if (VifPeakingFilter == 0x03) {
        msWriteRegsTbl(VIF_GDE_PEAKING_3dB);
    } else if (VifPeakingFilter == 0x04) {
        msWriteRegsTbl(VIF_GDE_PEAKING_4dB);
    } else if (VifPeakingFilter == 0x05) {
        msWriteRegsTbl(VIF_GDE_PEAKING_3dB_VSB);
    } else if (VifPeakingFilter == 0x06) {
        msWriteRegsTbl(VIF_GDE_PEAKING_4dB_VSB);
    } else if (VifPeakingFilter == 0x07) {
        msWriteRegsTbl(VIF_GDE_PEAKING_5dB_VSB);
    } else if (VifPeakingFilter == 0x80) {
        msWriteByte(SOS21_C0_L, VIFInitialIn_inst.VifSos21FilterC0);    // SOS21 (user define)
        msWriteByteMask(SOS21_C0_H, VIFInitialIn_inst.VifSos21FilterC0>>8, 0x07);
        msWriteByte(SOS21_C1_L, VIFInitialIn_inst.VifSos21FilterC1);
        msWriteByteMask(SOS21_C1_H, VIFInitialIn_inst.VifSos21FilterC1>>8, 0x07);
        msWriteByte(SOS21_C2_L, VIFInitialIn_inst.VifSos21FilterC2);
        msWriteByteMask(SOS21_C2_H, VIFInitialIn_inst.VifSos21FilterC2>>8, 0x07);
        msWriteByte(SOS21_C3_L, VIFInitialIn_inst.VifSos21FilterC3);
        msWriteByteMask(SOS21_C3_H, VIFInitialIn_inst.VifSos21FilterC3>>8, 0x07);
        msWriteByte(SOS21_C4_L, VIFInitialIn_inst.VifSos21FilterC4);
        msWriteByteMask(SOS21_C4_H, VIFInitialIn_inst.VifSos21FilterC4>>8, 0x07);
    }

    if (VifYcDelayFilter == 0x00) {
        msWriteRegsTbl(VIF_GDE_YCDelay_NULL);
    } else if (VifYcDelayFilter == 0x01) {
        msWriteRegsTbl(VIF_GDE_YCDelay_VSB);
    } else if (VifYcDelayFilter == 0x80) {
        msWriteByte(SOS22_C0_L, VIFInitialIn_inst.VifSos22FilterC0);    // SOS22 (user define)
        msWriteByteMask(SOS22_C0_H, VIFInitialIn_inst.VifSos22FilterC0>>8, 0x07);
        msWriteByte(SOS22_C1_L, VIFInitialIn_inst.VifSos22FilterC1);
        msWriteByteMask(SOS22_C1_H, VIFInitialIn_inst.VifSos22FilterC1>>8, 0x07);
        msWriteByte(SOS22_C2_L, VIFInitialIn_inst.VifSos22FilterC2);
        msWriteByteMask(SOS22_C2_H, VIFInitialIn_inst.VifSos22FilterC2>>8, 0x07);
        msWriteByte(SOS22_C3_L, VIFInitialIn_inst.VifSos22FilterC3);
        msWriteByteMask(SOS22_C3_H, VIFInitialIn_inst.VifSos22FilterC3>>8, 0x07);
        msWriteByte(SOS22_C4_L, VIFInitialIn_inst.VifSos22FilterC4);
        msWriteByteMask(SOS22_C4_H, VIFInitialIn_inst.VifSos22FilterC4>>8, 0x07);
    }

    if (VifGroupDelayFilter == 0x00) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_NULL);
    } else if (VifGroupDelayFilter == 0x01) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_VSB_LG);
    } else if (VifGroupDelayFilter == 0x02) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_VSB_Philips);
    } else if (VifGroupDelayFilter == 0x03) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_Low_R);
    } else if (VifGroupDelayFilter == 0x04) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_Low_L);
    } else if (VifGroupDelayFilter == 0x05) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_High_R);
    } else if (VifGroupDelayFilter == 0x06) {
        msWriteRegsTbl(VIF_GDE_GroupDelay_High_L);
    } else if (VifGroupDelayFilter == 0x80) {
        msWriteByte(SOS31_C0_L, VIFInitialIn_inst.VifSos31FilterC0);    // SOS31 (user define)
        msWriteByteMask(SOS31_C0_H, VIFInitialIn_inst.VifSos31FilterC0>>8, 0x07);
        msWriteByte(SOS31_C1_L, VIFInitialIn_inst.VifSos31FilterC1);
        msWriteByteMask(SOS31_C1_H, VIFInitialIn_inst.VifSos31FilterC1>>8, 0x07);
        msWriteByte(SOS31_C2_L, VIFInitialIn_inst.VifSos31FilterC2);
        msWriteByteMask(SOS31_C2_H, VIFInitialIn_inst.VifSos31FilterC2>>8, 0x07);
        msWriteByte(SOS31_C3_L, VIFInitialIn_inst.VifSos31FilterC3);
        msWriteByteMask(SOS31_C3_H, VIFInitialIn_inst.VifSos31FilterC3>>8, 0x07);
        msWriteByte(SOS31_C4_L, VIFInitialIn_inst.VifSos31FilterC4);
        msWriteByteMask(SOS31_C4_H, VIFInitialIn_inst.VifSos31FilterC4>>8, 0x07);
        msWriteByte(SOS32_C0_L, VIFInitialIn_inst.VifSos32FilterC0);    // SOS32 (user define)
        msWriteByteMask(SOS32_C0_H, VIFInitialIn_inst.VifSos32FilterC0>>8, 0x07);
        msWriteByte(SOS32_C1_L, VIFInitialIn_inst.VifSos32FilterC1);
        msWriteByteMask(SOS32_C1_H, VIFInitialIn_inst.VifSos32FilterC1>>8, 0x07);
        msWriteByte(SOS32_C2_L, VIFInitialIn_inst.VifSos32FilterC2);
        msWriteByteMask(SOS32_C2_H, VIFInitialIn_inst.VifSos32FilterC2>>8, 0x07);
        msWriteByte(SOS32_C3_L, VIFInitialIn_inst.VifSos32FilterC3);
        msWriteByteMask(SOS32_C3_H, VIFInitialIn_inst.VifSos32FilterC3>>8, 0x07);
        msWriteByte(SOS32_C4_L, VIFInitialIn_inst.VifSos32FilterC4);
        msWriteByteMask(SOS32_C4_H, VIFInitialIn_inst.VifSos32FilterC4>>8, 0x07);
    }
}

// For API
void msVifSetSoundSystem(VIFSoundSystem ucSoundSystem)
{
#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    g_ucVifSoundSystemType = ucSoundSystem;

    switch(ucSoundSystem)
    {
        case VIF_SOUND_BG:
            if ((VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) || (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90)) {
                msWriteRegsTbl(VIF_PAL_BG_A2);
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteRegsTbl(VIF_PAL_BG_A2_FREQ_38_00);
            }
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterBG, VIFInitialIn_inst.VifYcDelayFilterBG, VIFInitialIn_inst.VifGroupDelayFilterBG);
            msWriteRegsTbl(VIF_GDE_BG_NOTCH);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 0, _BIT1);                  // A_LPF_BG not bypass
            msWriteBit(BYPASS_N_A3, 0, _BIT5);                      // A3 notch not bypass
            msWriteBit(BYPASS_N_A4, 0, _BIT6);                      // A4 notch not bypass
            break;

        case VIF_SOUND_I:
            if ((VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) || (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90)) {
                msWriteRegsTbl(VIF_PAL_I_NICAM);
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteRegsTbl(VIF_PAL_I_NICAM_FREQ_38_00);
            }
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterI, VIFInitialIn_inst.VifYcDelayFilterI, VIFInitialIn_inst.VifGroupDelayFilterI);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        case VIF_SOUND_DK1:
            if ((VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) || (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90)) {
                msWriteRegsTbl(VIF_SECAM_DK1_A2);
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteRegsTbl(VIF_SECAM_DK1_A2_FREQ_38_00);
            }
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterDK, VIFInitialIn_inst.VifYcDelayFilterDK, VIFInitialIn_inst.VifGroupDelayFilterDK);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        case VIF_SOUND_DK2:
            if ((VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) || (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90)) {
                msWriteRegsTbl(VIF_PAL_DK2_A2);
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteRegsTbl(VIF_PAL_DK2_A2_FREQ_38_00);
            }
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterDK, VIFInitialIn_inst.VifYcDelayFilterDK, VIFInitialIn_inst.VifGroupDelayFilterDK);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        case VIF_SOUND_DK3:
            if ((VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) || (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90)) {
                msWriteRegsTbl(VIF_SECAM_DK3_A2);
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteRegsTbl(VIF_SECAM_DK3_A2_FREQ_38_00);
            }
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterDK, VIFInitialIn_inst.VifYcDelayFilterDK, VIFInitialIn_inst.VifGroupDelayFilterDK);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        case VIF_SOUND_L:
            msWriteRegsTbl(VIF_SECAM_L_NICAM);
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterL, VIFInitialIn_inst.VifYcDelayFilterL, VIFInitialIn_inst.VifGroupDelayFilterL);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        case VIF_SOUND_LL:
            msWriteRegsTbl(VIF_SECAM_LL_NICAM);
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterLL, VIFInitialIn_inst.VifYcDelayFilterLL, VIFInitialIn_inst.VifGroupDelayFilterLL);
            msWriteBit(BYPASS_SOS11, 1, _BIT0);                     // SOS11 notch bypass
            msWriteBit(ACI_REJ_NTSC, 0, _BIT6);                     // ACI_REJ_NTSC = 0 (PAL)
            msWriteBit(A_LPF_BG_SEL, 0, _BIT6);                     // A_LPF_BG_SEL = 0 (PAL)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 1, _BIT5);             // CO_A_REJ_NTSC bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        case VIF_SOUND_MN:
            if (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) {
                msWriteRegsTbl(VIF_NTSC_MN_A2_FREQ_45_75);
                msWriteBit(BYPASS_SOS11, 1, _BIT0);                 // SOS11 notch bypass
            } else if (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90) {
                msWriteRegsTbl(VIF_NTSC_MN_A2);
                msWriteRegsTbl(VIF_NOTCH_SOS11);
                msWriteBit(BYPASS_SOS11, 0, _BIT0);                 // SOS11 notch not bypass
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteRegsTbl(VIF_NTSC_MN_A2_FREQ_38_00);
                msWriteBit(BYPASS_SOS11, 1, _BIT0);                 // SOS11 notch bypass
            }
            msVifGroupDelayFilter(VIFInitialIn_inst.VifPeakingFilterMN, VIFInitialIn_inst.VifYcDelayFilterMN, VIFInitialIn_inst.VifGroupDelayFilterMN);
            msWriteBit(ACI_REJ_NTSC, 1, _BIT6);                     // ACI_REJ_NTSC = 1 (NTSC)
            msWriteBit(A_LPF_BG_SEL, 1, _BIT6);                     // A_LPF_BG_SEL = 1 (NTSC)
            msWriteBit(BYPASS_CO_A_REJ_NTSC, 0, _BIT5);             // CO_A_REJ_NTSC not bypass
            msWriteBit(BYPASS_A_LPF_BG, 1, _BIT1);                  // A_LPF_BG bypass
            msWriteBit(BYPASS_N_A3, 1, _BIT5);                      // A3 notch bypass
            msWriteBit(BYPASS_N_A4, 1, _BIT6);                      // A4 notch bypass
            break;

        default:
            break;
    }
}

// For API
void msVifTopAdjust(void)
{
#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    if(VIFInitialIn_inst.VifTop > 10)
    {
        msWriteByteMask(AGC_PGA2_MIN, VIFInitialIn_inst.VifTop-10, 0x1F);   // pga2 min
	msWriteByteMask(AGC_PGA2_OV, VIFInitialIn_inst.VifTop-10, 0x1F);
	msWriteByteMask(AGC_PGA1_MIN, 10, 0x0F); 			                // pga1 min
	msWriteByteMask(AGC_PGA1_OV, 10, 0x0F);
	msWriteByteMask(AGC_GAIN_OREN, 0x03, 0x03);
	msWriteByteMask(AGC_GAIN_OREN, 0x00, 0x03);
    } else {
        msWriteByteMask(AGC_PGA2_MIN, 0, 0x1F); 			                // pga2 min
        msWriteByteMask(AGC_PGA2_OV, 0, 0x1F);
        msWriteByteMask(AGC_PGA1_MIN, VIFInitialIn_inst.VifTop, 0x0F); 	    // pga1 min
        msWriteByteMask(AGC_PGA1_OV, VIFInitialIn_inst.VifTop, 0x0F);
        msWriteByteMask(AGC_GAIN_OREN, 0x03, 0x03);
        msWriteByteMask(AGC_GAIN_OREN, 0x00, 0x03);
    }
}

void msVifDynamicTopAdjust(void)
{
    BYTE mean256, agc_pga1, agc_pga2, ref, diff;
    WORD vga;

#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    vga = msRead2Bytes(AGC_VGA);
    agc_pga1 = msReadByte(AGC_PGA1C) & 0x0F;
    agc_pga2 = msReadByte(AGC_PGA2C) & 0x1F;
    mean256 = msReadByte(AGC_MEAN256);              // AGC mean256
    ref = msReadByte(AGC_REF);                      // AGC ref

    if (g_bCheckModulationType == 0) {
        diff = 0x15;                                // negative modulation
    } else {
        diff = 0x0A;                                // positive modulation
    }

    if ((vga == VIFInitialIn_inst.VifVgaMinimum) && (mean256 >= (ref+diff)) && ((agc_pga2+agc_pga1) == VIFInitialIn_inst.VifTop))
    {
        msWriteByteMask(AGC_PGA2_MIN, 0x00, 0x1F);  // pga2 min
        msWriteByteMask(AGC_PGA1_MIN, VIFInitialIn_inst.VifDynamicTopMin, 0x0F); 	// pga1 min
    } else if (((agc_pga2+agc_pga1) < VIFInitialIn_inst.VifTop) && ((vga >= 0xF000) || (vga <= VIFInitialIn_inst.VifVgaMaximum))) {
        msVifTopAdjust();
    }
}

// For API
void msVifInitial(void)
{
#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    msWriteByteMask(VIF_SOFT_RSTZ, 0x00, 0x7F);                     // VIF software reset
    msWriteBit(CLAMPGAIN_RSTZ, 0, _BIT0);                           // clampgain software reset
    msWriteBit(VSYNC_RSTZ, 0, _BIT0);                               // vsync software reset

    g_ucVifStatusStep = VIF_START;

    if ((g_ucVifSoundSystemType == VIF_SOUND_L) || (g_ucVifSoundSystemType == VIF_SOUND_LL))
    {
        g_bCheckModulationType = 1;     // positive modulation
        g_bCheckIFFreq = (g_ucVifSoundSystemType == VIF_SOUND_L) ? 0 : 1;   // 0: 38.9 MHz; 1: 33.9 MHz
    } else {
        g_bCheckModulationType = 0;     // negative modulation
        g_bCheckIFFreq = 0;             // 38.9 MHz
    }

    if (g_bCheckModulationType == 1)
    {
        msWriteByteMask(MODULATION_TYPE, 0x0F, 0x0F);               // positive modulation
    } else {
        msWriteByteMask(MODULATION_TYPE, 0x00, 0x0F);               // negative modulation
    }

    // AGC
    if (g_bCheckModulationType == 1)
    {
	    msWriteByte(AGC_PEAK_CNT_L, 0x00);                          // AGC peak cnt
	    msWriteByteMask(AGC_PEAK_CNT_H, 0x0B, 0x0F);
	    msWriteByte(AGC_REF, VIFInitialIn_inst.VifAgcRefPositive);  // AGC ref
    } else {
	    msWriteByte(AGC_PEAK_CNT_L, 0x00);                          // AGC peak cnt
	    msWriteByteMask(AGC_PEAK_CNT_H, 0x0C, 0x0F);
	    msWriteByte(AGC_REF, VIFInitialIn_inst.VifAgcRefNegative);  // AGC ref
    }
    msWriteByteMask(AGC_MEAN_SEL, _BIT2, _BIT2|_BIT3);              // mean16
    msWriteByte(AGC_LINE_CNT_L, 0x01);                              // AGC line cnt = 1
    msWriteByte(AGC_LINE_CNT_H, 0x00);
    msWriteByteMask(AGC_K, 0x02, _BIT0|_BIT1|_BIT2);                // k
    msWriteByteMask(AGC_GAIN_OREN, 0x00, 0x03);
    msWriteByte(AGC_VGA_MAX_L, VIFInitialIn_inst.VifVgaMaximum);    // vga max
    msWriteByte(AGC_VGA_MAX_H, VIFInitialIn_inst.VifVgaMaximum>>8);
    msWriteByte(AGC_VGA_MIN_L, VIFInitialIn_inst.VifVgaMinimum);    // vga min
    msWriteByte(AGC_VGA_MIN_H, VIFInitialIn_inst.VifVgaMinimum>>8);
    msWriteBit(AGC_IN_SEL, 1, _BIT1);                               // AGC input 0: from LPF1; 1: from LPF0

    // AGC gain distribution
    msWriteBit(AGC_DBB_VVGA_SEL, 1, _BIT3);                         // Vga gain from internal vga gain
    msWriteBit(AGC_DBB_AVGA_SEL, 1, _BIT4);                         // Avga gain from internal vga gain
    msWriteByte(AGC_VGA_THR, VIFInitialIn_inst.VifVgaMaximum);      // vga threshold
    msWriteByte(AGC_VGA_THR+1, (VIFInitialIn_inst.VifVgaMaximum - 0x1000)>>8);
    msWriteByte(AGC_VGA_BASE, (VIFInitialIn_inst.VifAgcVgaBase - 0x14));     // vga base
    msWriteByte(AGC_VGA_OFFS, VIFInitialIn_inst.VifAgcVgaOffs);     // vga offset

    msWriteBit(AGC_ENABLE, 1, _BIT0);	                            // AGC enable

    // CR
    msWriteByte(CR_DL_A, 0x16);	            	    	            // CR audio delay line
    msWriteByte(CR_PD_ERR_MAX_L, 0xFF);	                            // CR pd error max
    msWriteByteMask(CR_PD_ERR_MAX_H, 0x3F, 0x3F);
    msWriteByte(CR_NOTCH_A1_L, 0x41);	            	            // CR notch filter coefficient
    msWriteByte(CR_NOTCH_A1_H, 0x0C);
    msWriteByte(CR_NOTCH_A2_L, 0xE9);	            	            // CR notch filter coefficient
    msWriteByte(CR_NOTCH_A2_H, 0x0B);
    msWriteByte(CR_NOTCH_B1_L, 0x58);	            	            // CR notch filter coefficient
    msWriteByte(CR_NOTCH_B1_H, 0x00);
    msWriteBit(CR_ANCO_SEL, 1, _BIT0);	            	            // audio nco select
    msWriteByteMask(CR_KF1_HW, VIFInitialIn_inst.VifCrKf1, 0x0F);   // kf1 hardware mode
    msWriteByteMask(CR_KP1_HW, VIFInitialIn_inst.VifCrKp1, 0x0F);   // kp1 hardware mode
    msWriteByteMask(CR_KI1_HW, VIFInitialIn_inst.VifCrKi1<<4, 0xF0);// ki1 hardware mode
    msWriteByteMask(CR_KP2_HW, VIFInitialIn_inst.VifCrKp2, 0x0F);   // kp2 hardware mode
    msWriteByteMask(CR_KI2_HW, VIFInitialIn_inst.VifCrKi2<<4, 0xF0);// ki2 hardware mode
    msWriteByteMask(CR_KF_SW, 0x00, 0x0F);                          // kf software mode
    msWriteByteMask(CR_KP_SW, 0x00, 0x0F);                          // kp software mode
    msWriteByteMask(CR_KI_SW, 0x00, 0xF0);                          // ki software mode
    msWriteBit(CR_K_SEL, 1, _BIT6);	          			            // kp,ki,kf

    msWriteBit(VNCO_INV_OREN, 0, _BIT1);
    if (VIFInitialIn_inst.VifCrPdModeSel == 0)                      // 0: imaginary part; 1: cordic
        msWriteBit(CR_LPF_SEL, 0, _BIT4);                           // CR LPF 0: LPF1; 1: LPF2
    else
    msWriteBit(CR_LPF_SEL, VIFInitialIn_inst.VifCrLpfSel, _BIT4);   // CR LPF 0: LPF1; 1: LPF2
    msWriteBit(CR_PD_MODE, VIFInitialIn_inst.VifCrPdModeSel, _BIT1);// 0: imaginary part; 1: cordic
    msWriteBit(LOCK_LEAKY_FF_SEL, VIFInitialIn_inst.VifCrLockLeakySel, _BIT0);
    msWriteBit(CR_PD_X2, VIFInitialIn_inst.VifCrPdX2, _BIT2);       // CR X2 0: lock 0 degree; 1: lock 0 or 180 degree
    msWriteByte(CR_LOCK_TH_L, VIFInitialIn_inst.VifCrLockThr);      // CR lock threshold
    msWriteByteMask(CR_LOCK_TH_H, VIFInitialIn_inst.VifCrLockThr>>8, 0x03);
    msWriteByte(CR_UNLOCK_NUM, 0x00);                               // CR unlock num
    msWriteByte(CR_UNLOCK_NUM+1, 0x40);
    msWriteByteMask(CR_UNLOCK_NUM+2, 0x00, 0x0F);
    msWriteByte(CR_LOCK_NUM, VIFInitialIn_inst.VifCrLockNum);       // CR lock num
    msWriteByte(CR_LOCK_NUM+1, VIFInitialIn_inst.VifCrLockNum>>8);
    msWriteByteMask(CR_LOCK_NUM+2, VIFInitialIn_inst.VifCrLockNum>>16, 0x0F);
    msWriteByte(CR_CODIC_TH, VIFInitialIn_inst.VifCrThr);           // CR cordic threshold
    msWriteByteMask(CR_CODIC_TH+1, VIFInitialIn_inst.VifCrThr>>8, 0x3F);

    if (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_45_75) {
        msWriteByte(CR_RATE, 0xC7);                                 // cr_rate for 9.75 MHz
        msWriteByte(CR_RATE+1, 0x71);
        msWriteByteMask(CR_RATE+2, 0x0E, 0x1F);
    } else {
        if (g_bCheckIFFreq == 0) {
            if (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_90) {
                msWriteByte(CR_RATE, 0xF7);                         // cr_rate for 9.5 MHz
                msWriteByte(CR_RATE+1, 0x12);
                msWriteByteMask(CR_RATE+2, 0x0E, 0x1F);
            } else { // (VIFInitialIn_inst.VifIfBaseFreq == IF_FREQ_38_00)
                msWriteByte(CR_RATE, 0xBE);                         // cr_rate for 9.8 MHz
                msWriteByte(CR_RATE+1, 0x84);
                msWriteByteMask(CR_RATE+2, 0x0E, 0x1F);
            }
        } else {                                                    // SECAM L'
            msWriteByte(CR_RATE, 0x42);                             // cr_rate for 9.1 MHz
            msWriteByte(CR_RATE+1, 0x7B);
            msWriteByteMask(CR_RATE+2, 0x0D, 0x1F);
        }
    }

    // tuner step size
    if (VIFInitialIn_inst.VifTunerStepSize == FREQ_STEP_62_5KHz)    // 62.5KHz
    {
        if (g_bCheckIFFreq == 0) {
            msWriteByte(CR_FOE_SCAL_FACTOR_L, 0xB3);                // foe scaling factor
            msWriteByteMask(CR_FOE_SCAL_FACTOR_H, 0x02, 0x0F);
        } else {                                                    // SECAM L'
            msWriteByte(CR_FOE_SCAL_FACTOR_L, 0x4D);                // foe scaling factor
            msWriteByteMask(CR_FOE_SCAL_FACTOR_H, 0x0D, 0x0F);
        }
    }
    else if (VIFInitialIn_inst.VifTunerStepSize == FREQ_STEP_50KHz) // 50KHz
    {
        if (g_bCheckIFFreq == 0) {
            msWriteByte(CR_FOE_SCAL_FACTOR_L, 0x60);                // foe scaling factor
            msWriteByteMask(CR_FOE_SCAL_FACTOR_H, 0x03, 0x0F);
        } else {                                                    // SECAM L'
            msWriteByte(CR_FOE_SCAL_FACTOR_L, 0xA0);                // foe scaling factor
            msWriteByteMask(CR_FOE_SCAL_FACTOR_H, 0x0C, 0x0F);
        }
    }

    // Filter
    if (VIFInitialIn_inst.VifFlatSaw == 1)
    {
        msWriteBit(DEBUG_V_A, 1, _BIT5);                            // single ADC
        msWriteByteMask(ACI_REJ_NTSC_SEL, _BIT4, _BIT4|_BIT5);      // 0: aci_rej_out; 1: nyq_slp_out1; 2: nyq_slp_out2; 3: mixer_out_i
        msWriteBit(BYPASS_CO_A_REJ, 0, _BIT4);                      // CO_A_REJ not bypass
    } else {
        msWriteBit(DEBUG_V_A, 0, _BIT5);                            // dual ADC
        msWriteByteMask(ACI_REJ_NTSC_SEL, 0x00, _BIT4|_BIT5);       // 0: aci_rej_out; 1: nyq_slp_out1; 2: nyq_slp_out2; 3: mixer_out_i
        msWriteBit(BYPASS_CO_A_REJ, 1, _BIT4);                      // CO_A_REJ bypass
    }
    msWriteBit(A_BP_OUT_X2, 1, _BIT7);                              // A_BP output x2
    msWriteBit(A_DAGC_SEL, 1, _BIT7);                               // 0: input from a_sos; 1: input from a_lpf_up
    msWriteBit(BYPASS_A_NOTCH, 1, _BIT6);                           // A_NOTCH bypass
    msWriteBit(BYPASS_A_SOS, 1, _BIT7);                             // A_SOS bypass
    msWriteBit(BYPASS_SOS12, 1, _BIT1);                             // SOS12 bypass
    msWriteBit(BYPASS_SOS21, 0, _BIT2);                             // SOS21 not bypass
    msWriteBit(BYPASS_SOS22, 0, _BIT3);                             // SOS22 not bypass
    msWriteBit(BYPASS_SOS31, 0, _BIT4);             	            // SOS31 not bypass
    msWriteBit(BYPASS_SOS32, 0, _BIT5);             	            // SOS32 not bypass

    // AAGC
    msWriteByteMask(AAGC_MEAN_MAX, 0x30, 0x7F);                     // AAGC mean max
    msWriteByteMask(AAGC_MEAN_MIN, 0x26, 0x7F);                     // AAGC mean min
    if (g_bCheckModulationType == 1)
    {
    	msWriteByte(AAGC_CNT, 0xFF);					            // AAGC counter
    	msWriteByte(AAGC_CNT+1, 0xFF);
    	msWriteByteMask(AAGC_CNT+2, 0x1F, 0x1F);
		msWriteByte(AAGC_DEC, 0xFF);					            // AAGC decimation
    } else {
        msWriteByte(AAGC_CNT, 0xFF);                                // AAGC counter
    	msWriteByte(AAGC_CNT+1, 0x3F);
    	msWriteByteMask(AAGC_CNT+2, 0x00, 0x1F);
		msWriteByte(AAGC_DEC, 0x00);					            // AAGC decimation
    }
    msWriteBit(AAGC_ENABLE, 0, _BIT0);                              // AAGC disable

    // DAGC1
    if (_bit1_(VIFInitialIn_inst.VifDelayReduce)) {
        msWriteBit(DAGC1_DL_BYPASS, 1, _BIT3);                      // DAGC1 delay line bypass
    } else {
        msWriteBit(DAGC1_DL_BYPASS, 0, _BIT3);                      // DAGC1 delay line not bypass
    }
    msWriteBit(DAGC1_BYPASS, 0, _BIT1);                             // DAGC1 not bypass

    msWriteBit(DAGC1_OREN, 1, _BIT6);	                            // DAGC1 gain_overwrite = 1
    msWriteBit(DAGC1_OREN, 0, _BIT6);	                            // DAGC1 gain_overwrite = 0

    msWriteBit(DAGC1_GAIN0_FB_EN, 0, _BIT2);	                    // DAGC1 gain_update = 1

    if (g_bCheckModulationType == 1)
    {
	    msWriteByteMask(DAGC1_REF, 0x0B, 0x3F);		                // DAGC1 ref
	    msWriteByteMask(DAGC1_RATIO, 0x03, 0x07);		            // DAGC1 ratio
	    msWriteByte(DAGC1_PEAK_CNT_L, 0x00);	    	            // DAGC1 peak cnt
	    msWriteByteMask(DAGC1_PEAK_CNT_H, 0x0B, 0x0F);
        msWriteByte(DAGC1_GAIN_OVERWRITE_L, VIFInitialIn_inst.VifDagc1GainOv);
        msWriteByteMask(DAGC1_GAIN_OVERWRITE_H, VIFInitialIn_inst.VifDagc1GainOv>>8, 0x3F);
    } else {
	    msWriteByteMask(DAGC1_REF, VIFInitialIn_inst.VifDagc1Ref, 0x3F);    // DAGC1 ref
	    msWriteByteMask(DAGC1_RATIO, 0x00, 0x07);		            // DAGC1 ratio
	    msWriteByte(DAGC1_PEAK_CNT_L, 0x00);	                    // DAGC1 peak cnt
	    msWriteByteMask(DAGC1_PEAK_CNT_H, 0x0C, 0x0F);
    }
    msWriteBit(DAGC1_ENABLE, 1, _BIT0);                             // DAGC1 enable

    // DAGC2
    if (_bit2_(VIFInitialIn_inst.VifDelayReduce)) {
        msWriteBit(DAGC2_DL_BYPASS, 1, _BIT3);                      // DAGC2 delay line bypass
    } else {
        msWriteBit(DAGC2_DL_BYPASS, 0, _BIT3);                      // DAGC2 delay line not bypass
    }
    msWriteBit(DAGC2_BYPASS, 0, _BIT1);                             // DAGC2 not bypass

    msWriteBit(DAGC2_OREN, 1, _BIT6);	                            // DAGC2 gain_overwrite = 1
    msWriteBit(DAGC2_OREN, 0, _BIT6);	                            // DAGC2 gain_overwrite = 0

    msWriteBit(DAGC2_GAIN0_FB_EN, 0, _BIT2);	                    // DAGC2 gain_update = 1

    if (g_bCheckModulationType == 1)
    {
        msWriteByteMask(DAGC2_REF, 0x0B, 0x3F);		                // DAGC2 ref
        msWriteByteMask(DAGC2_RATIO, 0x03, 0x07);		            // DAGC2 ratio
        msWriteByte(DAGC2_PEAK_CNT_L, 0x00);	                    // DAGC2 peak cnt
        msWriteByteMask(DAGC2_PEAK_CNT_H, 0x0B, 0x0F);
        msWriteByte(DAGC2_GAIN_OVERWRITE_L, VIFInitialIn_inst.VifDagc2GainOv);
        msWriteByteMask(DAGC2_GAIN_OVERWRITE_H, VIFInitialIn_inst.VifDagc2GainOv>>8, 0x3F);
    } else {
        msWriteByteMask(DAGC2_REF, VIFInitialIn_inst.VifDagc2Ref, 0x3F);    // DAGC2 ref
        msWriteByteMask(DAGC2_RATIO, 0x00, 0x07);		            // DAGC2 ratio
        msWriteByte(DAGC2_PEAK_CNT_L, 0x00);	    	            // DAGC2 peak cnt
        msWriteByteMask(DAGC2_PEAK_CNT_H, 0x0C, 0x0F);
    }
    msWriteBit(DAGC2_ENABLE, 1, _BIT0);                             // DAGC2 enable

	// clampgain
    if (g_bCheckModulationType == 1) {
        msWriteByte(CLAMPGAIN_CLAMP_OVERWRITE, VIFInitialIn_inst.VifClampgainClampOvPositive);  // clampgain clamp overwrite value
        msWriteByteMask(CLAMPGAIN_CLAMP_OVERWRITE+1, VIFInitialIn_inst.VifClampgainClampOvPositive>>8, 0x07);
        msWriteByte(CLAMPGAIN_GAIN_OVERWRITE, VIFInitialIn_inst.VifClampgainGainOvPositive);    // clampgain gain overwrite value
        msWriteByteMask(CLAMPGAIN_GAIN_OVERWRITE+1, VIFInitialIn_inst.VifClampgainGainOvPositive>>8, 0x07);
    } else {
        msWriteByte(CLAMPGAIN_CLAMP_OVERWRITE, VIFInitialIn_inst.VifClampgainClampOvNegative);  // clampgain clamp overwrite value
        msWriteByteMask(CLAMPGAIN_CLAMP_OVERWRITE+1, VIFInitialIn_inst.VifClampgainClampOvNegative>>8, 0x07);
        msWriteByte(CLAMPGAIN_GAIN_OVERWRITE, VIFInitialIn_inst.VifClampgainGainOvNegative);    // clampgain gain overwrite value
        msWriteByteMask(CLAMPGAIN_GAIN_OVERWRITE+1, VIFInitialIn_inst.VifClampgainGainOvNegative>>8, 0x07);
    }
    msWriteBit(CLAMPGAIN_BYPASS, 0, _BIT1);				                                        // clampgain not bypass
    msWriteBit(CLAMPGAIN_SEL, VIFInitialIn_inst.VifClampgainClampSel, _BIT3);                   // 0: clamp select sync bottom; 1: clamp select porch
    msWriteByte(CLAMPGAIN_SYNCBOTT_REF, VIFInitialIn_inst.VifClampgainSyncbottRef);	            // porch or syncbottom ref
    msWriteByte(CLAMPGAIN_SYNCHEIGHT_REF, VIFInitialIn_inst.VifClampgainSyncheightRef);         // syncheight ref
    msWriteByteMask(CLAMPGAIN_KC, VIFInitialIn_inst.VifClampgainKc, 0x07);			            // kc
    msWriteByteMask(CLAMPGAIN_KG, VIFInitialIn_inst.VifClampgainKg<<4, 0x70);			        // kg
    msWriteByte(CLAMPGAIN_PORCH_CNT, VIFInitialIn_inst.VifClampgainPorchCnt);                   // clampgain porch cnt for NTSC
    msWriteByteMask(CLAMPGAIN_PORCH_CNT+1, VIFInitialIn_inst.VifClampgainPorchCnt>>8, 0x01);
    msWriteByte(CLAMPGAIN_CLAMP_MIN, VIFInitialIn_inst.VifClampgainClampMin);                   // clampgain clamp min
    msWriteByte(CLAMPGAIN_CLAMP_MAX, VIFInitialIn_inst.VifClampgainClampMax);                   // clampgain clamp max
    msWriteByte(CLAMPGAIN_GAIN_MIN, VIFInitialIn_inst.VifClampgainGainMin);                     // clampgain gain min
    msWriteByte(CLAMPGAIN_GAIN_MAX, VIFInitialIn_inst.VifClampgainGainMax);                     // clampgain gain max
    msWriteBit(CLAMPGAIN_CLAMP_OREN, VIFInitialIn_inst.VifClampgainClampOren, _BIT0);           // clampgain clamp overwrite enable
    msWriteBit(CLAMPGAIN_CLAMP_OREN, VIFInitialIn_inst.VifClampgainGainOren, _BIT1);            // clampgain gain overwrite enable
    msWriteBit(CLAMPGAIN_EN, 1, _BIT2);					                                        // clampgain enable

    // vsync
    msWriteBit(VSYNC_ENABLE, 1, _BIT1);                             // vsync enable

    // ADAGC
    if (g_bCheckModulationType == 1) {
        msWriteBit(ADAGC_BYPASS, 1, _BIT1);                         // ADAGC bypass
        msWriteByteMask(ADAGC_K, 0x00, 0x07);			            // ADAGC k
        msWriteBit(ADAGC_ENABLE, 0, _BIT0);                         // ADAGC disable
    } else {
        msWriteBit(ADAGC_BYPASS, 0, _BIT1);                         // ADAGC not bypass
        msWriteByteMask(ADAGC_K, 0x04, 0x07);			            // ADAGC k
        msWriteBit(ADAGC_ENABLE, 1, _BIT0);                         // ADAGC enable
    }

    msWriteByteMask(VIF_SOFT_RSTZ, 0x7F, 0x7F);                     // VIF software reset
    msWriteBit(CLAMPGAIN_RSTZ, 1, _BIT0);                           // clampgain software reset
    msWriteBit(VSYNC_RSTZ, 1, _BIT0);                               // vsync software reset

    // TOP
    msVifTopAdjust();

    // version control
    msWriteByte(FIRMWARE_VERSION_L, 0x12);                          // 18/01/10
    msWriteByte(FIRMWARE_VERSION_H, 0x1A);                          // firmware version control
}

// For API
void msVifHandler(BOOL bVifDbbAcq)
{
    BYTE afc_foe;
    BYTE mean16;
    BYTE agc_pga2;
    WORD agc_vga;
    BYTE dagc1_var;

#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    switch(g_ucVifStatusStep)
    {
        case VIF_START:
        case VIF_AGC_STATUS:
            mean16 = msReadByte(AGC_MEAN16);                        // AGC mean16
            agc_pga2 = msReadByte(AGC_PGA2C) & 0x1F;
            agc_vga = msRead2Bytes(AGC_VGA);
            if (g_bCheckModulationType == 0)
            {
    	        if (((mean16 < AGC_MEAN16_UPBOUND) && (mean16 > AGC_MEAN16_LOWBOUND)) || (agc_pga2 == 0x1F) || (agc_vga == VIFInitialIn_inst.VifVgaMinimum))
                {
                    msWriteByte(AGC_LINE_CNT_L, 0x04);              // AGC line cnt = 4
                    msWriteByte(AGC_LINE_CNT_H, 0x00);

    		    msWriteBit(CR_K_SEL, 0, _BIT6);	                // kp1,ki1,kf1; kp2,ki2,kf2

                    g_ucVifStatusStep = VIF_AFC_STATUS;
            	}
            } else {
                if (((mean16 < AGC_MEAN16_UPBOUND_SECAM) && (mean16 > AGC_MEAN16_LOWBOUND_SECAM)) || (agc_pga2 == 0x1F) || (agc_vga == VIFInitialIn_inst.VifVgaMinimum))
                {
                    msWriteByte(AGC_LINE_CNT_L, 0x04);              // AGC line cnt = 4
                    msWriteByte(AGC_LINE_CNT_H, 0x00);

    		    msWriteBit(CR_K_SEL, 0, _BIT6);	                // kp1,ki1,kf1,kp2,ki2,kf2

                    g_ucVifStatusStep = VIF_AFC_STATUS;
                }
            }
            break;

        case VIF_AFC_STATUS:
	        if (_bit0_(msReadByte(CR_LOCK_STATUS)))
	        {
	            // AGC
	            msWriteByte(AGC_VGA_THR, VIFInitialIn_inst.GainDistributionThr);    // vga threshold
                    msWriteByte(AGC_VGA_THR+1, VIFInitialIn_inst.GainDistributionThr>>8);
                    msWriteByte(AGC_VGA_BASE, VIFInitialIn_inst.VifAgcVgaBase);         // vga base

                    // AAGC
                    msWriteBit(AAGC_ENABLE, 1, _BIT0);                  // AAGC enable

                    // DAGC
                    if (g_bCheckModulationType == 1) {
                        msWriteBit(DAGC1_OREN, 1, _BIT6);	            // DAGC1 gain_overwrite = 1
                        msWriteBit(DAGC2_OREN, 1, _BIT6);	            // DAGC2 gain_overwrite = 1
                    }

                    g_ucVifStatusStep = VIF_AFC_STATUS2;
                } else {
                    msWriteBit(CR_LF_FF_RSTZ, 0, _BIT5);            // reset AFC integral part
                    msWriteBit(CR_LF_FF_RSTZ, 1, _BIT5);
        	}
            break;

        case VIF_AFC_STATUS2:
            afc_foe = msReadByte(CR_FOE);                           // AFC_FOE
            if ((afc_foe <= 0x04) || (afc_foe >= 0xFC))             // |AFC_FOE|<=4
            {
                if (bVifDbbAcq == 0)    // 0: not channel scan; 1: channel scan
                {
                    // AGC
                    msWriteByteMask(AGC_K, 0x04, _BIT0|_BIT1|_BIT2);// k
                    msWriteByte(AGC_LINE_CNT_L, 0x10);              // AGC line cnt = 16
                    msWriteByte(AGC_LINE_CNT_H, 0x00);

                    // CR
                    msWriteBit(CR_LPF_SEL, VIFInitialIn_inst.VifCrLpfSel, _BIT4);   // CR LPF 0: LPF1; 1: LPF2

                    g_bCrSeriousDrift = 0;
                    if (VIFInitialIn_inst.VifCrKpKiAdjust) {
                        g_VifCrKp = VIFInitialIn_inst.VifCrKp;
                        g_VifCrKi = VIFInitialIn_inst.VifCrKi;
                        g_VifCrLfFfMaxDiff = 0;
                        g_VifCrLfFfMaxInstDiff = 0;

                        msVifCrKpKiAdjust(250, 25);                 // CR auto detect 250 samples, 25x16us delay per sample
                        msVifCrKpKiSwitch(g_VifCrLfFfMaxDiff, g_VifCrLfFfMaxInstDiff, 0x28, 0x50, 0x15);      // thr1=13.183k, thr2=26.367k, thr3=6.921k

                        // for debug
                        if (msReadByte(HALVIFDBG_BIT) & 0x10)
                       {
            		       printf("\nMaxDiff = %x", (WORD)((g_VifCrLfFfMaxDiff&0xFFFF0000)>>16));
            		       printf(" %x\r\n", (WORD)(g_VifCrLfFfMaxDiff&0x0000FFFF));
			       printf("MaxInstDiff = %x", (WORD)((g_VifCrLfFfMaxInstDiff&0xFFFF0000)>>16));
			       printf(" %x\r\n", (WORD)(g_VifCrLfFfMaxInstDiff&0x0000FFFF));
                            printf("KP_1 = %x\r\n", (BYTE)g_VifCrKp);
			   }

                        g_VifCrLfFfMaxDiff = 0;
                        g_VifCrLfFfMaxInstDiff = 0;
                    } else {
                        msWriteByteMask(CR_KP_SW, VIFInitialIn_inst.VifCrKp, 0x0F);     // kp software mode
                        msWriteByteMask(CR_KI_SW, VIFInitialIn_inst.VifCrKi<<4, 0xF0);  // ki software mode
                    }
                    msWriteByteMask(CR_KF_SW, 0x00, 0x0F);                              // kf software mode
    		    msWriteBit(CR_K_SEL, 1, _BIT6);	                                    // kp,ki,kf
                    msWriteByte(CR_PD_ERR_MAX_L, VIFInitialIn_inst.VifCrPdErrMax);	    // CR pd error max
                    msWriteByteMask(CR_PD_ERR_MAX_H, VIFInitialIn_inst.VifCrPdErrMax>>8, 0x3F);
                    msWriteByte(CR_UNLOCK_NUM, VIFInitialIn_inst.VifCrUnlockNum);       // CR unlock num
                    msWriteByte(CR_UNLOCK_NUM+1, VIFInitialIn_inst.VifCrUnlockNum>>8);
                    msWriteByteMask(CR_UNLOCK_NUM+2, VIFInitialIn_inst.VifCrUnlockNum>>16, 0x0F);

                    // over modulation
                    if ((VIFInitialIn_inst.VifOverModulation == 1) && (g_bCheckModulationType == 0)) {
                        msWriteBit(VNCO_INV_OREN, 1, _BIT1);
                        msWriteBit(VNCO_INV_OV, 0, _BIT2);
                    }

                    g_ucVifStatusStep = VIF_STEADY_STATUS;
                }
            }

            if(!(_bit0_(msReadByte(CR_LOCK_STATUS)))) msVifInitial();
            break;

        case VIF_STEADY_STATUS:
            // Dynamic TOP adjust for strong signal
            if (VIFInitialIn_inst.VifDynamicTopAdjust) {
                msVifDynamicTopAdjust();
            }

            // AM hum detector
            agc_vga = msRead2Bytes(AGC_VGA);
            dagc1_var = msReadByte(DAGC1_VAR+1);
            if ((VIFInitialIn_inst.VifAmHumDetection == 1) && ((agc_vga > VIFInitialIn_inst.VifVgaMinimum) || (agc_vga < (VIFInitialIn_inst.GainDistributionThr - 0x1000))))
            {
                if ((dagc1_var >= 0x18) && (g_bCheckModulationType == 0)) {         // 20% AM modulation
                    msWriteByte(AGC_REF, 0x43);                                     // AGC ref
                } else if ((dagc1_var <= 0x05) && (g_bCheckModulationType == 0)) {  // 10% AM modulation
                    msWriteByte(AGC_REF, VIFInitialIn_inst.VifAgcRefNegative);      // AGC ref
                }
            }

            // AGC
            mean16 = msReadByte(AGC_MEAN16);                // AGC mean16
            if (g_bCheckModulationType == 0)
            {
    	        if ((mean16 < AGC_MEAN16_UPBOUND) && (mean16 > AGC_MEAN16_LOWBOUND))
                {
                    msWriteByteMask(AGC_K, 0x04, _BIT0|_BIT1|_BIT2);    // k
            	} else {
                    msWriteByteMask(AGC_K, 0x02, _BIT0|_BIT1|_BIT2);    // k
            	}
            }

            // CR monitor
            agc_pga2 = msReadByte(AGC_PGA2C) & 0x1F;
            if (agc_pga2 >= 0x0F) {
                msWriteByteMask(CR_KP_SW, (VIFInitialIn_inst.VifCrKp)+0x01, 0x0F);     // kp software mode
                msWriteByteMask(CR_KI_SW, (VIFInitialIn_inst.VifCrKi<<4)+0x10, 0xF0);  // ki software mode
            } else {
		if (VIFInitialIn_inst.VifCrKpKiAdjust) {
                    static BYTE xdata index = 0;
                    if (index < 50) {
                        msVifCrKpKiAdjust(50, 2);                               // CR auto detect
                        index++;
                    } else {
                        g_VifCrLfFfMaxDiff = g_VifCrLfFfMaxDiff/50;
		        g_VifCrLfFfMaxInstDiff = g_VifCrLfFfMaxInstDiff/50;
                        msVifCrKpKiSwitch(g_VifCrLfFfMaxDiff, g_VifCrLfFfMaxInstDiff, VIFInitialIn_inst.VifCrKpKiAdjustThr1, VIFInitialIn_inst.VifCrKpKiAdjustThr2, VIFInitialIn_inst.VifCrKpKiAdjustThr3);

                        // for debug
                        if (msReadByte(HALVIFDBG_BIT) & 0x20) 
                       {
            		      printf("\nMaxDiff = %x", (WORD)((g_VifCrLfFfMaxDiff&0xFFFF0000)>>16));
            		      printf(" %x\r\n", (WORD)(g_VifCrLfFfMaxDiff&0x0000FFFF));
			      printf("MaxInstDiff = %x", (WORD)((g_VifCrLfFfMaxInstDiff&0xFFFF0000)>>16));
			      printf(" %x\r\n", (WORD)(g_VifCrLfFfMaxInstDiff&0x0000FFFF));
                           printf("KP_2 = %x\r\n", (BYTE)g_VifCrKp);
		    	   }

	                g_VifCrLfFfMaxDiff = 0;
                        g_VifCrLfFfMaxInstDiff = 0;
	                index = 0;
                    }
		} else {
                    msWriteByteMask(CR_KP_SW, VIFInitialIn_inst.VifCrKp, 0x0F);     // kp software mode
                    msWriteByteMask(CR_KI_SW, VIFInitialIn_inst.VifCrKi<<4, 0xF0);  // ki software mode
                }
            }

            // CR
            if (VIFInitialIn_inst.VifCrPdModeSel == 1) {
                agc_vga = msRead2Bytes(AGC_VGA);
                agc_pga2 = msReadByte(AGC_PGA2C) & 0x1F;
                if ((agc_vga >= VIFInitialIn_inst.GainDistributionThr) && (agc_pga2 >= 0x0F)) {
                    msWriteBit(CR_LPF_SEL, 0, _BIT4);                                   // CR LPF 0: LPF1; 1: LPF2
                    msWriteBit(CR_PD_MODE, 0, _BIT1);                                   // 0: imaginary part; 1: cordic
            	} else {
                    if (g_bCrSeriousDrift == 0) {
                        msWriteBit(CR_LPF_SEL, VIFInitialIn_inst.VifCrLpfSel, _BIT4);   // CR LPF 0: LPF1; 1: LPF2
                	msWriteBit(CR_PD_MODE, VIFInitialIn_inst.VifCrPdModeSel, _BIT1);// 0: imaginary part; 1: cordic
                	msWriteByte(CR_CODIC_TH, VIFInitialIn_inst.VifCrThr);           // CR cordic threshold
                	msWriteByteMask(CR_CODIC_TH+1, VIFInitialIn_inst.VifCrThr>>8, 0x3F);
                    }
            	}
            }

            // clampgain
            if (VIFInitialIn_inst.VifClampgainClampOren == 0) {
                if (msReadByte(CLAMPGAIN_CLAMP+1) == VIFInitialIn_inst.VifClampgainClampMax)
                {
                    msWriteBit(CLAMPGAIN_RSTZ, 0, _BIT0);       // clampgain software reset
                    msWriteBit(CLAMPGAIN_RSTZ, 1, _BIT0);
                }
            }

            // over modulation
            if ((VIFInitialIn_inst.VifOverModulation == 1) && (msReadByte(DAGC1_GAIN+1) == 0x3F) && (g_bCheckModulationType == 0))
            {
                if (_bit2_(msReadByte(VNCO_INV_OV)) == 1) {
                    msWriteBit(VNCO_INV_OV, 0, _BIT2);
                } else {
                    msWriteBit(VNCO_INV_OV, 1, _BIT2);
                }
            }

            if(!(_bit0_(msReadByte(CR_LOCK_STATUS)))) {
                if (VIFInitialIn_inst.VifCrPdModeSel == 1){
                    // for serious carrier drift
                    g_bCrSeriousDrift = 1;
                    msWriteByte(CR_CODIC_TH, 0x00);             // CR cordic threshold
                    msWriteByteMask(CR_CODIC_TH+1, 0x00, 0x3F);
                    msWriteBit(CR_LPF_SEL, 0, _BIT4);           // CR LPF 0: LPF1; 1: LPF2

                    VIF_Delay1ms(5);
                }

                if(!(_bit0_(msReadByte(CR_LOCK_STATUS)))){
	            g_bCrSeriousDrift = 0;
	            msWriteByte(CR_CODIC_TH, VIFInitialIn_inst.VifCrThr);           // CR cordic threshold
	            msWriteByteMask(CR_CODIC_TH+1, VIFInitialIn_inst.VifCrThr>>8, 0x3F);
                    msWriteBit(CR_LPF_SEL, VIFInitialIn_inst.VifCrLpfSel, _BIT4);   // CR LPF 0: LPF1; 1: LPF2
                    VIF_Delay1ms(50);                                   // for Fluke 54200 50dBuV <-> 51dBuV switch
                    if(!(_bit0_(msReadByte(CR_LOCK_STATUS)))) {
                        msVifInitial();
                    }
                }
            }
            break;

        default:
            g_ucVifStatusStep++;
            break;
    }

    if ((g_ucVifSoundSystemType == VIF_SOUND_L) || (g_ucVifSoundSystemType == VIF_SOUND_LL)) {
        if (g_bCheckModulationType == 0) msVifInitial();
        if ((g_ucVifSoundSystemType == VIF_SOUND_L) && (g_bCheckIFFreq == 1)) msVifInitial();
        if ((g_ucVifSoundSystemType == VIF_SOUND_LL) && (g_bCheckIFFreq == 0)) msVifInitial();
    } else {
        if (g_bCheckModulationType == 1) msVifInitial();
    }
}

void msVifCrKpKiAdjust(WORD VifCrKpKiAdjustSample, WORD VifCrKpKiAdjustDelay)
{
    WORD i, j;
    short  lf_ff, prev_lf_ff, max_lf_ff = 0, min_lf_ff = 0;
    WORD inst_lf_ff, max_delta;

#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

    prev_lf_ff = 0;
    max_delta = 0;

    for (i = 0; i < VifCrKpKiAdjustSample; i++) {           // sampling times
        msWriteBit(CR_LF_FF_LAT, 1, _BIT4);                 // latch CR loop-filter status
        lf_ff = msRead2Bytes(CR_LF_FF_RPT+2) & 0x1FFF;      // read CR_LF_FF MSB two bytes
        if (lf_ff & 0x1000) {
            lf_ff |= 0xE000;
        }
        msWriteBit(CR_LF_FF_LAT, 0, _BIT4);                 // latch CR loop-filter status

        if (i == 0) {
            max_lf_ff = lf_ff;                              // store MAX/MIN of lf_ff
            min_lf_ff = lf_ff;
        } else {
            max_lf_ff = (lf_ff > max_lf_ff) ? lf_ff : max_lf_ff;
            min_lf_ff = (lf_ff < min_lf_ff) ? lf_ff : min_lf_ff;
        }

        if (i != 0) {
            inst_lf_ff = (prev_lf_ff >= lf_ff) ? (prev_lf_ff - lf_ff) : (lf_ff - prev_lf_ff);   // store difference of lf_ff
            max_delta = (inst_lf_ff > max_delta) ? inst_lf_ff : max_delta;
        }
        prev_lf_ff = lf_ff;

        for (j = 0; j < VifCrKpKiAdjustDelay; j++) {
            VIF_Delay1us(1);                                     // actually delay 10us
        }
    }
    g_VifCrLfFfMaxDiff += (DWORD)(max_lf_ff - min_lf_ff);
    g_VifCrLfFfMaxInstDiff += (DWORD)max_delta;
}

void msVifCrKpKiSwitch(DWORD LfFfMaxDiff, DWORD LfFfMaxInstDiff, BYTE VifCrKpKiAdjustThr1, BYTE VifCrKpKiAdjustThr2, BYTE VifCrKpKiAdjustThr3)
{
#if FORCE_SWITCH_BANK
    if (msVIFCheckBypassVIF()) return;
    msVifSwitch2VifBank();
#endif

	/* algorithm
	if (GEAR=2)
	{
	    if (init_kpki = cur_kpki)
	    {
	        if (Big_Drift)
	            -2
	        else if (Little_drift)
	            -1
	    }
	    else if (init_kpki - cur_kpki==1)
	    {
	        if (Big_Drift)
	            -1
	    }
	}
	else if (GEAR=1)
	{
	    if (init_kpki = cur_kpki)
	    {
	         if (Little_drift)
	            -1
	    }
	}
	*/

        LfFfMaxInstDiff = LfFfMaxInstDiff;
        VifCrKpKiAdjustThr3 = VifCrKpKiAdjustThr3;

	// have 2 gear
	if (VIFInitialIn_inst.VifCrKpKiAdjustGear==2)
	{
		// have 2 space
		if (g_VifCrKp == VIFInitialIn_inst.VifCrKp)
		{
			// fit -2 condition
			if (LfFfMaxDiff > VifCrKpKiAdjustThr2)
			{
				//(Big_Drift)
				g_VifCrKp -= 2;
				g_VifCrKi -= 2;
			}
			else if ((VifCrKpKiAdjustThr2 >= LfFfMaxDiff) && (LfFfMaxDiff >= VifCrKpKiAdjustThr1))
			{
				//(Little_Drift)
				g_VifCrKp -= 1;
				g_VifCrKi -= 1;
			}
		}
		// have 1 space
		else if (g_VifCrKp == VIFInitialIn_inst.VifCrKp - 1)
		{
			// fit -1 condition
		   	if (LfFfMaxDiff > VifCrKpKiAdjustThr2)
			{
				//(Big_Drift)
				g_VifCrKp -= 1;
				g_VifCrKi -= 1;
			}
		}
	}
	// have 1 gear
	else if (VIFInitialIn_inst.VifCrKpKiAdjustGear==1)
	{
		// have 1 space
		if (VIFInitialIn_inst.VifCrKp == g_VifCrKp)
		{
                        // fit -1 condition
			if (LfFfMaxDiff >= VifCrKpKiAdjustThr1)
			{
				//(Little_drift)
				g_VifCrKp -= 1;
				g_VifCrKi -= 1;
			}
		}
	}

    msWriteByteMask(CR_KP_SW, g_VifCrKp, 0x0F);            // kp software mode
    msWriteByteMask(CR_KI_SW, g_VifCrKi<<4, 0xF0);         // ki software mode
}

#undef _MSVIF_C_
