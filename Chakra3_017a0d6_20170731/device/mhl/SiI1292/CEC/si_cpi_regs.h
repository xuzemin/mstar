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
//!file     si_cpi_regs.h
//!brief    SiI9387 Device CPI Registers Manifest Constants.
//
// No part of this work may be reproduced, modified, distributed, 
// transmitted, transcribed, or translated into any language or computer 
// format, in any form or by any means without written permission of 
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2007-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/
#ifndef __SI_CPI_REGS_H__
#define __SI_CPI_REGS_H__

//------------------------------------------------------------------------------
// NOTE: Register addresses are 16 bit values with page and offset combined.
//
// Examples:  0x005 = page 0, offset 0x05
//            0x1B6 = page 1, offset 0xB6
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Registers in Page 8
//------------------------------------------------------------------------------

#define REG_CEC_DEBUG_2             0x886

#define	REG_CEC_DEBUG_3             0x887
#define BIT_SNOOP_EN                        0x01
#define BIT_FLUSH_TX_FIFO                   0x80

#define REG_CEC_TX_INIT             0x888
#define BIT_SEND_POLL                       0x80

#define REG_CEC_TX_DEST             0x889

#define REG_CEC_CONFIG_CPI          0x88E

#define REG_CEC_TX_COMMAND          0x88F
#define REG_CEC_TX_OPERAND_0        0x890

#define REG_CEC_TRANSMIT_DATA       0x89F
#define	BIT_TX_BFR_ACCESS                   0x40
#define	BIT_TX_AUTO_CALC                    0x20
#define	BIT_TRANSMIT_CMD                    0x10

#define REG_CEC_CAPTURE_ID0         0x8A2

#define REG_CEC_INT_ENABLE_0        0x8A4
#define BIT_TX_FIFO_FULL                    0x20

#define REG_CEC_INT_ENABLE_1        0x8A5
#define BIT_RX_FIFO_OVERRUN                 0x08

// 0xA6 CPI Interrupt Status Register (R/W)
#define REG_CEC_INT_STATUS_0        0x8A6
#define BIT_CEC_LINE_STATE                  0x80
#define BIT_TX_BUFFER_FULL                  0x40
#define BIT_TX_MESSAGE_SENT                 0x20
#define BIT_TX_HOTPLUG                      0x10
#define BIT_POWER_STAT_CHANGE               0x08
#define BIT_TX_FIFO_EMPTY                   0x04
#define BIT_RX_MSG_RECEIVED                 0x02
#define BIT_CMD_RECEIVED                    0x01

// 0xA7 CPI Interrupt Status Register (R/W)
#define REG_CEC_INT_STATUS_1        0x8A7
#define BIT_RX_FIFO_OVERRUN                 0x08
#define BIT_SHORT_PULSE_DET                 0x04
#define BIT_FRAME_RETRANSM_OV               0x02
#define BIT_START_IRREGULAR                 0x01

#define REG_CEC_RX_CONTROL          0x8AC
// CEC  CEC_RX_CONTROL bits
#define BIT_CLR_RX_FIFO_CUR         0x01
#define BIT_CLR_RX_FIFO_ALL         0x02

#define REG_CEC_RX_COUNT            0x8AD
#define BIT_MSG_ERROR               0x80


#define REG_CEC_RX_CMD_HEADER       0x8AE
#define REG_CEC_RX_OPCODE           0x8AF
#define REG_CEC_RX_OPERAND_0        0x8B0


#define REG_CEC_RX_COUNT            0x8AD

#define CEC_OP_ABORT_0              0x8C0
#define CEC_OP_ABORT_31             0x8DF


#endif  // __SI_CPI_REGS_H__
