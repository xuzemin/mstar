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
// Copyright (c) 2008 MStar Semiconductor, Inc.
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
// File Name: DevNtp7414sCustom_new.h
// Description: NTP I2S Audio Amplifier
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_TAS5747s_H__
#define __DRV_TAS5747s_H__

#include "datatype.h"


// ***************************************************************************
// ************************* START OF REGISTER TYPES *************************
// ***************************************************************************
//----------------------------------------------------------------------------
// Control register bit field structure definitions
//----------------------------------------------------------------------------

// Register address
#define TAS5747s_MASTER_CLOCK_FREQUENCY_CTRL     0x00
//#define TAS5747s_SYSTEM_STATUS                   0x01
#define TAS5747s_SOFT_RESET_CTRL                 0x02
#define TAS5747s_SOFT_MUTE_SPEED_CTRL            0x03
#define TAS5747s_MASTER_VOL_PWM_SWITCH           0x04
#define TAS5747s_CHANNEL1_VOLUME                 0x06
#define TAS5747s_CHANNEL2_VOLUME                 0x07
#define TAS5747s_PRESCALER_VALUE_CTRL            0x08
//#define TAS5747s_OPERATION_CTRL                  0x09
#define TAS5747s_FUNC_CTRL                       0x0A
#define TAS5747s_IC_DELAY                        0x0B
#define TAS5747s_IC_DELAY2                       0x0C
#define TAS5747s_IC_DELAY3                       0x0D
#define TAS5747s_IC_DELAY4                       0x0E

#define TAS5747s_MODULATION_LIMITE               0x10
#define TAS5747s_HP_GAIN                         0x12
#define TAS5747s_HP_ENABLE                       0x13
#define TAS5747s_LEGACY_SYSCTL2                  0x15
#define TAS5747s_AUTO_TRIM_SETTING               0x1B
#define TAS5747s_DPEQ_CHECKSUM                   0x23
#define TAS5747s_PEQ_CHECKSUM                    0x28
//#define TAS5747s_DRC_CTRL_0                      0x2A
//#define TAS5747s_DRC_CTRL_1                      0x2B
//#define TAS5747s_DRC_CTRL_2                      0x2C
//#define TAS5747s_DRC_CTRL_3                      0x2D
//#define TAS5747s_DRC_CTRL_4                      0x2E
//#define TAS5747s_DRC_CTRL_5                      0x2F

//#define TAS5747s_PWM_MASK_CTRL_1                 0x33
//#define TAS5747s_PWM_MASK_CTRL_2                 0x34
//#define TAS5747s_PWM_MASK_CTRL_3                 0x35
//#define TAS5747s_PWM_MASK_CTRL_4                 0x36
//#define TAS5747s_PWM_CTRL                        0x3A

//#define TAS5747s_DPEQ_CTRL_0                     0x3C
//#define TAS5747s_DPEQ_CTRL_1                     0x3D
//#define TAS5747s_DPEQ_CTRL_2                     0x3E
//#define TAS5747s_DPEQ_CTRL_3                     0x3F
//#define TAS5747s_DPEQ_CTRL_4                     0x18
//#define TAS5747s_DPEQ_CTRL_5                     0x19

//#define TAS5747s_PWM_D_BTL_MODE_CTRL_0           0x40
//#define TAS5747s_PWM_D_BTL_MODE_CTRL_1           0x41
//#define TAS5747s_PWM_D_BTL_MODE_CTRL_2           0x42
//#define TAS5747s_MOD_INDEX_NS_TYPE_CTRL          0x45
//#define TAS5747s_ASRC_CTRL                       0x47
#define TAS5747s_OUTPUT_POST_SCALE               0x4D

//#define TAS5747s_MONITOR                         0x5F

//#define TAS5747s_DC_PROTECTION_CTRL_0            0x60
//#define TAS5747s_DC_PROTECTION_CTRL_1            0x61
//#define TAS5747s_DC_PROTECTION_CTRL_2            0x62
//#define TAS5747s_DC_PROTECTION_CTRL_3            0x63
//#define TAS5747s_DC_PROTECTION_CTRL_4            0x64
//#define TAS5747s_DC_PROTECTION_CTRL_5            0x65
//#define TAS5747s_DC_PROTECTION_CTRL_6            0x66
//#define TAS5747s_DC_PROTECTION_CTRL_7            0x67
//#define TAS5747s_DC_PROTECTION_CTRL_8            0x68
//#define TAS5747s_DC_PROTECTION_CTRL_9            0x69
//#define TAS5747s_DC_PROTECTION_CTRL_10           0x6A

//#define TAS5747s_PEQ_CHECKSUM_HH           0x63
//#define TAS5747s_PEQ_CHECKSUM_H            0x64
//#define TAS5747s_PEQ_CHECKSUM_M            0x65
//#define TAS5747s_PEQ_CHECKSUM_L            0x66

//#define TAS5747s_DRC_CHECKSUM_HH          0x67
//#define TAS5747s_DRC_CHECKSUM_H            0x68
//#define TAS5747s_DRC_CHECKSUM_M            0x69
//#define TAS5747s_DRC_CHECKSUM_L             0x6A

//#define TAS5747s_POP_CTRL_0                      0x6C
//#define TAS5747s_POP_CTRL_1                      0x6D
//#define TAS5747s_POP_CTRL_2                      0x6E
//#define TAS5747s_POP_CTRL_3                      0x6F

//#define TAS5747s_SYSTEM_ERROR_STATUS            0x70     // USE Audio AMP/Woofer Loopback Test. TAS5747ss IC
//#define TAS5747s_I2S_GLITCH_FILTER               0x72
#define TAS5747s_BIQUAD_FILTER_CTRL_3            0x7E

#define TAS5747s_CHIP_ID                         0x25

//#define  BIT_PEQ_CHECKSUM        0x40
//#define  BIT_PEQ_ENABLE             0x20

//-------------------------------------------------------------------------
// Register maps enum
//-------------------------------------------------------------------------

#define BOOL        BOOLEAN

BOOL DevTas5747sByteWrite(U8 bSubAddr, U8 bData);
BYTE DevTas5747sByteRead(U8 bSubAddr);
void DevTas5747sBurstWrite(U8 bSubAddr, U8* bData);
void DevTas5747sBurstRead(U8 bSubAddr, U8* bData);

void drvTAS5747s_SW_Init(void);
void drvTAS5747s_EnablePEQ(BOOLEAN bEnable);
void drvTAS5747s_SoftMute(BOOLEAN bMute);
void drvTAS5747s_SetAmpScale(U8  u8Scale);
void drvTAS5747s_SetAmpVolume(U8  u8Vol);
extern void drvTAS5747s_GetPeqCheckSum(U8*  pCheckSum);
void drvTAS5747s_SetAmpClock(U8 bSampleRate);
void _TAS5747s_WritePeqTable(void);

#endif // __DRV_TAS5747s_H__

