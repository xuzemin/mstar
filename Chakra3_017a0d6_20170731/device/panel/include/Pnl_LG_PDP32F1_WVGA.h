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

#ifndef __LPL22_WSXGA_H
#define __LPL22_WSXGA_H

///////////////////////////////////////////////
// Common setting
///////////////////////////////////////////////
#define PANEL_NAME          "LPL_LM220WE1"
#define PANEL_DOT_WIDTH     325.5       // unit: um
#define PANEL_DOT_HEIGHT    325.5       // unit: um

#define USE_PRIVATE_GAMMA_TABLE

///////////////////////////////////////////////
// Enable function
///////////////////////////////////////////////
#define _PNL_FUNC_EN_               -1 // 0 = disable

//////////////////////////////////////////////
// Panel output
//////////////////////////////////////////////
#define PANEL_DITHER                0 // 8/6 bits panel

#define PANEL_TTL                   0
#define PANEL_TCON                  0
#define PANEL_LVDS                  _PNL_FUNC_EN_
#define PANEL_RSDS            0

#define PANEL_DUAL_PORT             0//_PNL_FUNC_EN_
#define PANEL_SWAP_PORT             _PNL_FUNC_EN_
#define PANEL_SWAP_ODD_ML           0
#define PANEL_SWAP_EVEN_ML      0
#define PANEL_SWAP_ODD_RB           0
#define PANEL_SWAP_EVEN_RB      0

//#define PANEL_SWAP_LVDS_POL       1//3304 new board
//#define PANEL_SWAP_LVDS_CH        1//3304 new board
#define PANEL_SWAP_LVDS_POL         1//3303 old board
#define PANEL_SWAP_LVDS_CH          1//3303 old board

#define PANEL_LVDS_TI_MODE          0//_PNL_FUNC_EN_

#define PANEL_DCLK_DELAY            0x00
#define PANEL_INV_DCLK              0
#define PANEL_INV_DE                0
#define PANEL_INV_HSYNC         0
#define PANEL_INV_VSYNC         0

// Lock Y line
#define PANEL_LOCK_Y_LINE           4

#define PANEL_SYNC_MODE_1           0
#define DISABLE_SHORT_FRAME_TUNE    0
#define DISABLE_SHORT_LINE_TUNE 1

///////////////////////////////////////////////
// Aspect Ratio setting
///////////////////////////////////////////////

//
// Aspect ratio type
//
#define PANEL_ASPECT_RATIO_4_3     0
#define PANEL_ASPECT_RATIO_WIDE    1
#define PANEL_ASPECT_RATIO_OTHER   2

//
// Select aspect ratio
//
#define PANEL_ASPECT_RATIO  PANEL_ASPECT_RATIO_WIDE

///////////////////////////////////////////////
// Output tmming setting
///////////////////////////////////////////////
// driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
#define PANEL_DCLK_CURRENT          0x01 // DCLK current
#define PANEL_DE_CURRENT            0x01 // DE signal current
#define PANEL_ODD_DATA_CURRENT  0x01 // odd data current
#define PANEL_EVEN_DATA_CURRENT 0x01 // even data current

#if 1
#define PANEL_ON_TIMING1          30  // time between panel & data while turn on power
#define PANEL_ON_TIMING2          400 // time between data & back light while turn on power
#define PANEL_OFF_TIMING1         80  // time between back light & data while turn off power
#define PANEL_OFF_TIMING2         30  // time between data & panel while turn off power

#define PANEL_HSYNC_WIDTH         128//20
#define PANEL_HSYNC_BACK_PORCH    72//40

#define PANEL_VSYNC_WIDTH         2
#define PANEL_VSYNC_BACK_PORCH    33

#define PANEL_HSTART             ((U16)PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#define PANEL_VSTART             ((U16)PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
#define PANEL_WIDTH             852
#define PANEL_HEIGHT            480
#define PANEL_HTOTAL            1088
#define PANEL_VTOTAL            525//629

#define PANEL_MAX_HTOTAL        1200//1130
#define PANEL_MIN_HTOTAL        1080
#define PANEL_MAX_VTOTAL        577//655
#define PANEL_MIN_VTOTAL        518//618
#define PANEL_DCLK               (((U32)PANEL_HTOTAL*PANEL_VTOTAL*60)/1000000)
#define PANEL_MAX_DCLK          88
#define PANEL_MIN_DCLK          65

#else
#define PANEL_ON_TIMING1            20  // time between panel & data while turn on power
#define PANEL_ON_TIMING2            230 // time between data & back light while turn on power
#define PANEL_OFF_TIMING1           230  // time between back light & data while turn off power
#define PANEL_OFF_TIMING2           20  // time between data & panel while turn off power

#define PANEL_HSYNC_WIDTH           32
#define PANEL_HSYNC_BACK_PORCH      80

#define PANEL_VSYNC_WIDTH           6
#define PANEL_VSYNC_BACK_PORCH      21

#define PANEL_HSTART                (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#define PANEL_VSTART                (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
#define PANEL_WIDTH                 1680
#define PANEL_HEIGHT                1050
#define PANEL_HTOTAL                1840
#define PANEL_VTOTAL                1080

#define PANEL_MAX_VTOTAL            1300
#define PANEL_MIN_VTOTAL            1060

#define PANEL_MAX_HTOTAL            2000
#define PANEL_MIN_HTOTAL            1760
#define PANEL_DCLK                  (((DWORD)PANEL_HTOTAL*PANEL_VTOTAL*60)/1000000)
#define PANEL_MAX_DCLK              164
#define PANEL_MIN_DCLK              95
#endif

///////////////////////////////////////////////////////
// TCON setting for LVDS
///////////////////////////////////////////////////////
// PVS / FSYNC
#define PANEL_GPO9_VSTART           0x0007
#define PANEL_GPO9_VEND             0x0705
#define PANEL_GPO9_HSTART           0x0000
#define PANEL_GPO9_HEND             0x0000
#define PANEL_GPO9_CONTROL          0x07

// HSYNC
#define PANEL_GPOA_VSTART           0x0006
#define PANEL_GPOA_VEND             0x0408
#define PANEL_GPOA_HSTART           0x0000
#define PANEL_GPOA_HEND             0x0000
#define PANEL_GPOA_CONTROL          0x04

//////////////////////////////////
// SSC
// SET_SSC_SPAN value 0 -3ff
// SET_SSC_STEP value 0x800-7fff
//////////////////////////////////
#define SET_SSC_SPAN                0xC0
#define SET_SSC_STEP                0x19

#define PANEL_DIMMING_CTL           0x6D
#define PANEL_MAX_PWM_DIM           0xDD
#define PANEL_MIN_PWM_DIM           0x20

//------------------------------------------------------------------------------
// GAMMA
//------------------------------------------------------------------------------
#define GAMMA_LUT_12BIT DISABLE

#endif  // __CMO22_WSXGA_H