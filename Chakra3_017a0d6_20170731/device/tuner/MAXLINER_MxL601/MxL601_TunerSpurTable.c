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
/*******************************************************************************
 *
 * FILE NAME          : MxL601_TunerSpurTable.cpp
 *
 * AUTHOR             : Dong Liu
 *
 * DATE CREATED       : 03/09/2013
 *
 * DESCRIPTION        : This file contains spur shift table that used in channel
 *                      tune procedure
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#include "MxL601_TunerSpurTable.h"
#include "MxL601_TunerCfg.h"

CHAN_DEPENDENT_SPUR_REGISTER_T MxL601_SPUR_REGISTER = 
{ 4, {DFE_RFLUT_SWP1_REG, DFE_RFLUT_DIV_MOD_REG, DFE_REFLUT_BYP_REG, DFE_REFSX_INT_MOD_REG} };

// Below lookup table of frequencies in different applications mode
// on which optimized channel tunning settings will be configured

// Table : 24
// NTSC XTAL=16MHz LIF
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_XTAL_16MHZ_LIF[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {57000000, 0x19, 0x39, 0x0, 0xD8},
  {111000000, 0x1C, 0x17, 0x20, 0xD7},
  {117000000, 0x1C, 0x17, 0x20, 0xDB},
  {177000000, 0x19, 0x39, 0x20, 0xD6},
  {219000000, 0x1C, 0x17, 0x20, 0xD7},
  {285000000, 0x1F, 0x3F, 0x20, 0xD7},
  {363000000, 0x1B, 0x3B, 0x20, 0xD8},
  {633000000, 0x1C, 0x17, 0x20, 0xDA},
  {651000000, 0x1C, 0x17, 0x20, 0xD4},
  {663000000, 0x1C, 0x17, 0x20, 0xD7},
  {771000000, 0x1C, 0x17, 0x20, 0xDA},
  {795000000, 0x1C, 0x17, 0x20, 0xD9},
  {813000000, 0x1C, 0x17, 0x20, 0xD5},
  {849000000, 0x1C, 0x17, 0x20, 0xD9},
  {867000000, 0x1C, 0x17, 0x20, 0xD7},
  {879000000, 0x1C, 0x17, 0x20, 0xD3},
  {0, 0, 0, 0, 0},
};


// Table : 25
// NTSC XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_XTAL_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {123000000, 0x19, 0x39, 0x20, 0x8D},
  {177000000, 0x1F, 0x3F, 0x20, 0x90},
  {231000000, 0x1D, 0x3D, 0x20, 0x90},
  {255000000, 0x19, 0x39, 0x20, 0x90},
  {699000000, 0x1A, 0x3A, 0x20, 0x90},
  {705000000, 0x19, 0x39, 0x20, 0x8F},
  {0, 0, 0, 0, 0},
};


// Table : 26
// NTSC HRC XTAL=16MHz
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_HRC_16MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {55750000, 0x19, 0x39, 0x20, 0xD8},
  {283765625, 0x1E, 0x3E, 0x20, 0xD8},
  {649781250, 0x1A, 0x3A, 0x20, 0xD8},
  {883794100, 0x1C, 0x17, 0x20, 0xD7},
  {0, 0, 0, 0, 0},
};


// Table : 27
// NTSC HRC XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_HRC_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {271765625, 0x1E, 0x3E, 0x20, 0x8F},
  {283765625, 0x1E, 0x3E, 0x20, 0x90},
  {0, 0, 0, 0, 0},
};


// Table : 28
// NTSC IRC XTAL=16MHz
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_IRC_16MHZ[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {111012500, 0x1C, 0x17, 0x20, 0xD7},
  {177012500, 0x1F, 0x3F, 0x20, 0xD8},
  {219012500, 0x1C, 0x17, 0x20, 0xD7},
  {285012500, 0x1F, 0x3F, 0x20, 0xD8},
  {363012500, 0x1B, 0x3B, 0x20, 0xD8},
  {663012500, 0x1C, 0x17, 0x20, 0xD7},
  {759012500, 0x1C, 0x17, 0x20, 0xD6},
  {813012500, 0x1C, 0x17, 0x20, 0xD5},
  {867012500, 0x1C, 0x17, 0x20, 0xD7},
  {0, 0, 0, 0, 0},
};


// Table : 29
// NTSC IRC XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_IRC_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {123015625, 0x19, 0x39, 0x20, 0x8D},
  {231015625, 0x15, 0x35, 0x20, 0x8E},
  {0, 0, 0, 0, 0},
};


// Table : 31
// PAL-B/G 7MHz XTAL=16MHz LIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_BG_7MHZ_LUT_XTAL_16MHZ_LIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {50500000, 0x1C, 0x17, 0x20, 0xDB},
  {57500000, 0x1C, 0x17, 0x20, 0xD5},
  {114500000, 0x1C, 0x17, 0x20, 0xDB},
  {219500000, 0x1C, 0x17, 0x20, 0xD7},
  {0, 0, 0, 0, 0},
};


// Table : 32
// PAL-B/G 7MHz XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T PAL_BG_7MHZ_LUT_XTAL_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {128500000, 0x1F, 0x3F, 0x20, 0x91},
  {149500000, 0x1B, 0x3B, 0x20, 0x8F},
  {0, 0, 0, 0, 0},
};


// Table : 33
// PAL-B/G 8MHz XTAL=16MHz LIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_BG_8MHZ_LUT_XTAL_16MHZ_LIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {378000000, 0x1A, 0x3A, 0x20, 0xD5},
  {418000000, 0x1E, 0x3E, 0x20, 0xD4},
  {594000000, 0x19, 0x39, 0x20, 0xDA},
  {634000000, 0x1D, 0x17, 0x20, 0xDA},
  {658000000, 0x1D, 0x17, 0x20, 0xD9},
  {770000000, 0x1D, 0x17, 0x20, 0xDA},
  {786000000, 0x1D, 0x17, 0x20, 0xD5},
  {794000000, 0x1D, 0x17, 0x20, 0xD9},
  {834000000, 0x1A, 0x3A, 0x20, 0xD5},
  {850000000, 0x1D, 0x17, 0x20, 0xD9},
  {0, 0, 0, 0, 0},
};


// Table : 34
// PAL-B/G 8MHz XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T PAL_BG_8MHZ_LUT_XTAL_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {314000000, 0x1F, 0x3F, 0x20, 0x93},
  {378000000, 0x1E, 0x3E, 0x20, 0x91},
  {386000000, 0x18, 0x38, 0x20, 0x8C},
  {418000000, 0x1B, 0x3B, 0x20, 0x91},
  {450000000, 0x1C, 0x3C, 0x20, 0x8E},
  {602000000, 0x19, 0x39, 0x20, 0x8F},
  {0, 0, 0, 0, 0},
};


// Table : 35
// PAL-D XTAL=16MHz LIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_D_LUT_XTAL_16MHZ_LIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {51000000, 0x1D, 0x17, 0x20, 0xDB},//Mstar Add for ATV disturb
  {52500000, 0x1D, 0x3A, 0x00, 0xD8},
  {58000000, 0x1D, 0x17, 0x20, 0xCD},
  {65000000, 0x1D, 0x17, 0x20, 0xDE},
  {88000000, 0x1D, 0x17, 0x20, 0xCF},//Mstar Add for ATV disturb
  {108000000, 0x1D, 0x17, 0x20, 0xCD},//Mstar Add for ATV disturb
  {116000000, 0x1D, 0x17, 0x20, 0xD6},
  {122000000, 0x1D, 0x17, 0x20, 0xCF},//Mstar Add for ATV disturb
  {227000000, 0x1A, 0x3A, 0x20, 0xDA},
  {241000000, 0x1D, 0x17, 0x20, 0xD0},//Mstar Add for ATV disturb
  {243000000, 0x1D, 0x17, 0x0, 0xD8},
  {690000000, 0x1D, 0x17, 0x20, 0xCE},	// add 690MHz
  {275000000, 0x1D, 0x17, 0x20, 0xD9},
  {290000000, 0x1D, 0x17, 0x20, 0xCE},//Mstar Add for ATV disturb
  {346000000, 0x1D, 0x17, 0x20, 0xD0},//Mstar Add for ATV disturb
  {365000000, 0x1D, 0x17, 0x20, 0xD7},
  {442000000, 0x1D, 0x17, 0x20, 0xCD},//Mstar Add for ATV disturb
  {554000000, 0x1D, 0x17, 0x20, 0xCD},//Mstar Add for ATV disturb
  {634000000, 0x1D, 0x17, 0x20, 0xDA},
  {658000000, 0x1D, 0x17, 0x20, 0xD9},
  {690000000, 0x1D, 0x17, 0x20, 0xCE},//Mstar Add for ATV disturb
  {770000000, 0x1D, 0x17, 0x20, 0xDA},
  {794000000, 0x1D, 0x17, 0x20, 0xD9},
  {850000000, 0x1D, 0x17, 0x20, 0xD9},
  {898000000, 0x1D, 0x3D, 0x20, 0xD5},
  {0, 0, 0, 0, 0},
};


// Table : 36
// PAL-D XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T PAL_D_LUT_XTAL_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {147000000, 0x1A, 0x3A, 0x20, 0x8E},
  {259000000, 0x1B, 0x3B, 0x20, 0x8D},
  {275000000, 0x1A, 0x3A, 0x20, 0x8E},
  {602000000, 0x1C, 0x3C, 0x20, 0x8E},
  {834000000, 0x1B, 0x3B, 0x20, 0x8E},
  {898000000, 0x1D, 0x3D, 0x20, 0x8E},
  {0, 0, 0, 0, 0},
};


// Table : 37
// PAL-I XTAL=16MHz LIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_I_LUT_XTAL_16MHZ_LIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {55000000, 0x1D, 0x17, 0x20, 0xCB},
  {80500000, 0x1A, 0x3A, 0x20, 0xE3},
  {186000000, 0x1D, 0x17, 0x0, 0xD8},
  {418000000, 0x1E, 0x3E, 0x20, 0xD5},
  {594000000, 0x19, 0x39, 0x20, 0xDA},
  {874000000, 0x1D, 0x17, 0x20, 0xD6},
  {898000000, 0x1D, 0x3D, 0x20, 0xD5},
  {0, 0, 0, 0, 0},
};


// Table : 38
// PAL-I XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T PAL_I_LUT_XTAL_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {152500000, 0x19, 0x39, 0x20, 0x90},
  {418000000, 0x1B, 0x3B, 0x20, 0x91},
  {458000000, 0x1A, 0x3A, 0x20, 0x90},
  {898000000, 0x1D, 0x3D, 0x20, 0x8E},
  {0, 0, 0, 0, 0},
};


// Table : 39
// SECAM L XTAL=16MHz
CHAN_DEPENDENT_FREQ_TABLE_T SECAM_L_LUT_XTAL_16MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {242750000, 0x1D, 0x17, 0x0, 0xD8},
  {346750000, 0x1B, 0x3B, 0x20, 0xD9},
  {0, 0, 0, 0, 0},
};


// Table : 40
// SECAM-L XTAL=24MHz
CHAN_DEPENDENT_FREQ_TABLE_T SECAM_L_LUT_XTAL_24MHZ[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0x90},
  {226750000, 0x19, 0x39, 0x20, 0x8F},
  {346750000, 0x1D, 0x3D, 0x20, 0x8F},
  {0, 0, 0, 0, 0},
};


// Table : 50
// PAL-D XTAL=16MHz HIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_D_LUT_XTAL_16MHZ_HIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {171000000, 0x1D, 0x17, 0x20, 0xD9},
  {179000000, 0x1D, 0x17, 0x20, 0xD3},
  {187000000, 0x1D, 0x17, 0x20, 0xDD},
  {227000000, 0x1D, 0x17, 0x20, 0xDB},
  {315000000, 0x1D, 0x17, 0x20, 0xD7},
  {339000000, 0x1D, 0x17, 0x20, 0xD5},
  {363000000, 0x1D, 0x17, 0x20, 0xDB},
  {387000000, 0x1D, 0x17, 0x20, 0xD6},
  {443000000, 0x1D, 0x17, 0x20, 0xDA},
  {522000000, 0x1D, 0x17, 0x20, 0xD7},
  {666000000, 0x1D, 0x17, 0x20, 0xD7},
  {738000000, 0x1D, 0x17, 0x20, 0xD7},
  {834000000, 0x1D, 0x17, 0x20, 0xDA},
  {0, 0, 0, 0, 0},
};


// Table : 51
// PAL-I XTAL=16MHz HIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_I_LUT_XTAL_16MHZ_HIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {48500000, 0x1D, 0x17, 0x20, 0xD7},
  {55000000, 0x1D, 0x17, 0x20, 0xC9},
  {64500000, 0x1D, 0x17, 0x20, 0xDE},
  {96500000, 0x1D, 0x17, 0x20, 0xD1},
  {120500000, 0x1D, 0x17, 0x20, 0xE0},
  {144500000, 0x1D, 0x17, 0x20, 0xDA},
  {178000000, 0x1D, 0x17, 0x20, 0xD6},
  {186000000, 0x1D, 0x17, 0x20, 0xDC},
  {226000000, 0x1D, 0x17, 0x20, 0xDB},
  {234000000, 0x1D, 0x17, 0x20, 0xD7},
  {306000000, 0x1D, 0x17, 0x20, 0xD7},
  {394000000, 0x1D, 0x17, 0x20, 0xD9},
  {410000000, 0x1D, 0x17, 0x20, 0xD7},
  {450000000, 0x1D, 0x17, 0x20, 0xD6},
  {522000000, 0x1D, 0x17, 0x20, 0xD7},
  {666000000, 0x1D, 0x17, 0x20, 0xD7},
  {738000000, 0x1D, 0x17, 0x20, 0xD7},
  {874000000, 0x1D, 0x17, 0x20, 0xD7},
  {882000000, 0x1D, 0x17, 0x20, 0xD7},
  {0, 0, 0, 0, 0},
};


// Table : 52
// PAL-BG XTAL=16MHz HIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_BG_7MHZ_LUT_XTAL_16MHZ_HIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {57500000, 0x1D, 0x17, 0x20, 0xD7},
  {191500000, 0x1D, 0x17, 0x20, 0xD5},
  {219500000, 0x1D, 0x17, 0x20, 0xD7},
  {240500000, 0x1D, 0x17, 0x20, 0xDB},
  {282500000, 0x1D, 0x17, 0x20, 0xDC},
  {296500000, 0x1D, 0x17, 0x20, 0xDC},
  {0, 0, 0, 0, 0},
};


// Table : 53
// PAL-BG XTAL=16MHz HIF
CHAN_DEPENDENT_FREQ_TABLE_T PAL_BG_8MHZ_LUT_XTAL_16MHZ_HIF[] = 
{ 
  {1, 0x1D, 0x17, 0x00, 0xD8},
  {306000000, 0x1D, 0x17, 0x20, 0xD9},
  {314000000, 0x1D, 0x17, 0x20, 0xD6},
  {450000000, 0x1D, 0x17, 0x20, 0xD7},
  {522000000, 0x1D, 0x17, 0x20, 0xD7},
  {666000000, 0x1D, 0x17, 0x20, 0xD7},
  {730000000, 0x1D, 0x17, 0x20, 0xD3},
  {738000000, 0x1D, 0x17, 0x20, 0xD7},
  {0, 0, 0, 0, 0},
};


// Table : 54
// NTSC XTAL=16MHz HIF
CHAN_DEPENDENT_FREQ_TABLE_T NTSC_FREQ_LUT_XTAL_16MHZ_HIF[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {99000000, 0x1C, 0x17, 0x20, 0xD7},
  {111000000, 0x1C, 0x17, 0x20, 0xD6},
  {219000000, 0x1C, 0x17, 0x20, 0xD7},
  {261000000, 0x1C, 0x17, 0x20, 0xD9},
  {333000000, 0x1C, 0x17, 0x20, 0xD9},
  {363000000, 0x1C, 0x17, 0x20, 0xDB},
  {387000000, 0x1C, 0x17, 0x20, 0xD9},
  {441000000, 0x1C, 0x17, 0x20, 0xD9},
  {447000000, 0x1C, 0x17, 0x20, 0xD6},
  {495000000, 0x1C, 0x17, 0x20, 0xD7},
  {549000000, 0x1C, 0x17, 0x20, 0xD7},
  {603000000, 0x1C, 0x17, 0x20, 0xD7},
  {663000000, 0x1C, 0x17, 0x20, 0xD6},
  {705000000, 0x1C, 0x17, 0x20, 0xD7},
  {735000000, 0x1C, 0x17, 0x20, 0xD7},
  {867000000, 0x1C, 0x17, 0x20, 0xD7},
  {0, 0, 0, 0, 0},
};


// Table : 60
// Digital Cable 6MHz
CHAN_DEPENDENT_FREQ_TABLE_T DIG_CABLE_FREQ_LUT_BW_6MHZ[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {0, 0, 0, 0, 0},
};


// Table : 61
// Digital Cable 8MHz
CHAN_DEPENDENT_FREQ_TABLE_T DIG_CABLE_FREQ_LUT_BW_8MHZ[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {0, 0, 0, 0, 0},
};


// Table : 62
// Digital Terestrial 6MHz
CHAN_DEPENDENT_FREQ_TABLE_T DIG_TERR_FREQ_LUT_BW_6MHZ[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {0, 0, 0, 0, 0},
};


// Table : 63
// Digital Terestrial 7MHz
CHAN_DEPENDENT_FREQ_TABLE_T DIG_TERR_FREQ_LUT_BW_7MHZ[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {0, 0, 0, 0, 0},
};


// Table : 64
// Digital Terestrial 8MHz
CHAN_DEPENDENT_FREQ_TABLE_T DIG_TERR_FREQ_LUT_BW_8MHZ[] = 
{ 
  {1, 0x1C, 0x17, 0x00, 0xD8},
  {0, 0, 0, 0, 0},
};

