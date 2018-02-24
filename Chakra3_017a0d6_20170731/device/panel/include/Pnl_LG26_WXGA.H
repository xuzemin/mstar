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

#ifndef __LG26_WXGA_H
#define __LG26_WXGA_H

///////////////////////////////////////////////
// Common setting
///////////////////////////////////////////////
#define PANEL_NAME      "LC260-W01"

///////////////////////////////////////////////
// Enable function
///////////////////////////////////////////////
#define _PNL_FUNC_EN_         -1 // 0 = disable

//////////////////////////////////////////////
// Panel output
//////////////////////////////////////////////
#define PANEL_DITHER          0 // 8/6 bits panel

#define PANEL_TTL             0
#define PANEL_TCON            0
#define PANEL_LVDS            _PNL_FUNC_EN_
#define PANEL_RSDS            0

#define PANEL_DUAL_PORT       0
#define PANEL_SWAP_PORT       0
#define PANEL_SWAP_ODD_ML     0
#define PANEL_SWAP_EVEN_ML    0
#define PANEL_SWAP_ODD_RB     0
#define PANEL_SWAP_EVEN_RB    0

#define PANEL_SWAP_LVDS_POL   0
#define PANEL_SWAP_LVDS_CH    0

#define PANEL_LVDS_TI_MODE    _PNL_FUNC_EN_

#define PANEL_DCLK_DELAY      0x00
#define PANEL_INV_DCLK        0
#define PANEL_INV_DE          0
#define PANEL_INV_HSYNC       0
#define PANEL_INV_VSYNC       0

// Lock Y line
#define PANEL_LOCK_Y_LINE           4

#define PANEL_SYNC_MODE_1           0
#define DISABLE_SHORT_FRAME_TUNE    0
#define DISABLE_SHORT_LINE_TUNE     1

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
#define PANEL_DCLK_CURRENT         0x01 // DCLK current
#define PANEL_DE_CURRENT           0x01 // DE signal current
#define PANEL_ODD_DATA_CURRENT     0x01 // odd data current
#define PANEL_EVEN_DATA_CURRENT    0x01 // even data current

#define PANEL_ON_TIMING1          30  // time between panel & data while turn on power
#define PANEL_ON_TIMING2          450 // time between data & back light while turn on power
#define PANEL_OFF_TIMING1         100  // time between back light & data while turn off power
#define PANEL_OFF_TIMING2         20  // time between data & panel while turn off power

#define PANEL_HSYNC_WIDTH         32
#define PANEL_HSYNC_BACK_PORCH    84

#define PANEL_VSYNC_WIDTH         2
#define PANEL_VSYNC_BACK_PORCH    38

#define PANEL_HSTART             ((U16)PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#define PANEL_VSTART             ((U16)PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
#define PANEL_WIDTH              (1366ul)
#define PANEL_HEIGHT             (768ul)
#define PANEL_HTOTAL             (1688ul)
#define PANEL_VTOTAL             (806ul)

#define PANEL_MAX_HTOTAL         (2000ul)
#define PANEL_MIN_HTOTAL         (1450ul)
#define PANEL_MAX_VTOTAL         (860ul)
#define PANEL_MIN_VTOTAL         (806ul)
#define PANEL_DCLK               (((U32)PANEL_HTOTAL*PANEL_VTOTAL*60)/1000000)
#define PANEL_MAX_DCLK           82
#define PANEL_MIN_DCLK           61

///////////////////////////////////////////////////////
// TCON setting for LVDS
///////////////////////////////////////////////////////
// PVS / FSYNC
#define PANEL_GPO9_VSTART        0x0007
#define PANEL_GPO9_VEND          0x0705
#define PANEL_GPO9_HSTART        0x0000
#define PANEL_GPO9_HEND          0x0000
#define PANEL_GPO9_CONTROL       0x07

// HSYNC
#define PANEL_GPOA_VSTART        0x0006
#define PANEL_GPOA_VEND          0x0408
#define PANEL_GPOA_HSTART        0x0000
#define PANEL_GPOA_HEND          0x0000
#define PANEL_GPOA_CONTROL       0x04

//////////////////////////////////
// SSC
// SET_SSC_SPAN value 0 -3ff
// SET_SSC_STEP value 0x800-7fff
//////////////////////////////////
#define SET_SSC_SPAN            0xEC
#define SET_SSC_STEP            0x19

#define PANEL_DIMMING_CTL               0x80
#define PANEL_MAX_PWM_DIM               0xe6
#define PANEL_MIN_PWM_DIM               0x20

//------------------------------------------------------------------------------
// GAMMA
//------------------------------------------------------------------------------
#define GAMMA_LUT_12BIT DISABLE

#endif  // __CMO22_WSXGA_H

