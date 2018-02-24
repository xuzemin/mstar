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
//***************************************************************************
//!file     si_1292regs.h
//!brief    SiI1292 Device Register Manifest Constants.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2007-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __SI_1292REGS_H__
#define __SI_1292REGS_H__


#define SET_BITS    0xFF
#define CLEAR_BITS  0x00

//------------------------------------------------------------------------------
// NOTE: Register addresses are 16 bit values with page and offset combined.
//
// Examples:  0x005 = page 0, offset 0x05
//            0x1B6 = page 1, offset 0xB6
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Registers in Page 0  (0xD0)
//------------------------------------------------------------------------------

#define REG_DEV_IDL_RX          0x002
#define REG_DEV_IDH_RX          0x003
#define REG_DEV_REV             0x004



// Software Reset Register
#define REG_SRST                0x005
#define BIT_SWRST_AUTO                  0x10    // Auto SW Reset
#define BIT_SWRST                       0x01
#define BIT_CBUS_RST					0x04
#define BIT_CEC_RST						0x08


// System Status Register
#define REG_STATE            	0x006
#define BIT_SCDT                        0x01
#define BIT_CKDT                        0x02
#define BIT_HPD							0x04
#define BIT_PWR5V                       0x08
#define BIT_V5DET						0x10
#define BIT_MHL_STRAP					0x20

// System Status Register 2
#define REG_STATE2				0x007

// System Control 1 Register
#define REG_SYS_CTRL1			0x008
#define BIT_RX_CLK						0x02
#define BIT_HDMI_MODE					0x80

// Interrupt State Register
#define REG_INTR_STATE			0x043
#define BIT_INTR						0x01

// Interrupt Status Register
#define REG_INTR1				0x04C
#define INT_CBUS						0x01					
#define INT_RPWR						0x02
#define INT_HPD							0x08
#define INT_CKDT						0x10
#define INT_RSEN						0x20
#define INT_SCDT						0x40
#define INT_CBUS_CON					0x80

// Interrupt Mask
#define REG_INTR1_MASK			0x04D

//Interrupt 2 Status and Mask Register
#define REG_INTR2_STATUS_MASK	0x04E
#define INT_V5DET						0x01
#define MASK_V5DET						0x02

// TMDS Tx Control Register
#define REG_TMDS_Tx					0x047

// TMDS Tx SW Control 1 Register
#define REG_TX_SWING1			0x051
#define BIT_SWCTRL_EN					0x80

// Rx Control5 Register
#define REG_RX_CTRL5			0x070
#define BIT_HDMI_RX_EN					0x80

// CBUS DISC OVR Register
#define REG_CBUS_DISC_OVR		0x073
#define BIT_STRAP_MHL_EN				0x01
#define BIT_STRAP_MHL_OVR				0x02

// Rx MISC Register
#define REG_RX_MISC				0x07A
#define BIT_HPD_RSEN_ENABLE				0x04
#define BIT_5VDET_OVR					0x08
#define BIT_PSCTRL_OEN					0x10
#define BIT_PSCTRL_OUT					0x20
#define BIT_PSCTRL_AUTO					0x80

// GPIO CTRL Register
#define REG_GPIO_CTRL			0x07F
#define BIT_GPIO0_OUTPUT_DISABLE		0x01
#define BIT_GPIO0_INPUT					0x40

// DDC Switch Register
#define REG_DDC_SW_CTRL			0x084
#define BIT_I2C_DDC_SW_EN				0x01

// OTP Revision Register
#define REG_OTP_REV				0x086
#define MASK_OTP_REV					0x0F

// DDC
#define REG_DDC_L1				0x984
// Jin: REG_DDC_PAH = REG_DDC_L1+ 10 + L1 + L2
// REG_DDC_L2 = REG_DDC_L1 + 1 + L1


#endif  // __SI_1292REGS_H__

