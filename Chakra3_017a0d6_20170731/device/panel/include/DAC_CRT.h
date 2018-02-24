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

#ifndef __DAC_CRT_H
#define __DAC_CRT_H

#ifdef _DAC_CRT_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include "Board.h"

//////////////////////////////////////////////
// DAC output
//////////////////////////////////////////////
#define PANEL_DAC_OUTPUT

#define PANEL_DAC_INTERLACE     0
#define PANEL_DAC_I1440_MODE    0
#define PANEL_DAC_INV_FIELD     0

#define PANEL_DAC_SVM           _PNL_FUNC_EN_

///////////////////////////////////////////////
// Common setting
///////////////////////////////////////////////
#define PANEL_NAME      "DAC CRT"

///////////////////////////////////////////////
// Enable function
///////////////////////////////////////////////
#define _PNL_FUNC_EN_           -1 // 0 = disable

#define PANEL_DITHER            0 // 8/6 bits panel

#define PANEL_TTL               _PNL_FUNC_EN_
#define PANEL_TCON              0
#define PANEL_LVDS              0
#define PANEL_RSDS              0

#define PANEL_DUAL_PORT         0
#define PANEL_SWAP_PORT         0
#define PANEL_SWAP_ODD_ML       0
#define PANEL_SWAP_EVEN_ML      0
#define PANEL_SWAP_ODD_RB       0
#define PANEL_SWAP_EVEN_RB      0

#define PANEL_SWAP_LVDS_POL     0
#define PANEL_SWAP_LVDS_CH      0

#define PANEL_LVDS_TI_MODE      0

#define PANEL_DCLK_DELAY        0x08
#define PANEL_INV_DE            0
#define PANEL_INV_DCLK          0
#define PANEL_INV_HSYNC         0
#define PANEL_INV_VSYNC         0

// Lock Y line
#define PANEL_LOCK_Y_LINE       0

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
#define PANEL_DCLK_CURRENT          0x01 // DCLK current
#define PANEL_DE_CURRENT            0x01 // DE signal current
#define PANEL_ODD_DATA_CURRENT      0x01 // odd data current
#define PANEL_EVEN_DATA_CURRENT     0x01 // even data current

#define PANEL_ON_TIMING1            0 // time between panel & data while turn on power
#define PANEL_ON_TIMING2            0 // time between data & back light while turn on power
#define PANEL_OFF_TIMING1           0  // time between back light & data while turn off power
#define PANEL_OFF_TIMING2           0  // time between data & panel while turn off power

#define PANEL_DAC_INTERLACE_BIT     BIT0
#define PANEL_DAC_INV_FIELD_BIT     BIT1
#define PANEL_DAC_SHIFT_RIGHT_BIT   BIT2
#define PANEL_DAC_I1440_MODE_BIT    BIT4

#define PANEL_REDUCE_DE_SIZE_BIT    BIT0
#define PANEL_DOUBLE_OSD_X_BIT      BIT1
#define PANEL_DOUBLE_OSD_Y_BIT      BIT2

#define PANEL_REDUCE_DE_SIZE        8

INTERFACE U8 g_u8CRT_OutTimingSel;
#if 0 //non-used
INTERFACE U8 g_u8PreCRT_OutTimingSel;
INTERFACE U8 g_u8MultiHsync;
#endif

////////////////////////////////////////////////////
// Panel select definition
////////////////////////////////////////////////////
// timing stucture
typedef struct _PanelDataType
{
    U16 DEVstart; // vertical DE start
    U8 HsyncShiftOffset;//use for interlace out
    U8 HSyncWidth; // HSync width
    U16 HSyncBackPorch; // HSync back porch
    U16 VSyncWidth; // VSync Width
    U16 VSyncBackPorch; // VSync back porch
    U16 DeWidth; // DE width
    U16 DeHeight; // DE height
    U16 HTotal; // horizontal total
    U16 VTotal; // vertical total
    U32 OuputDClk; // output clock
    U8  OutputCtrl; // output flag
    U8  ExtendFlag; // extend flag
}PanelDataType;

typedef struct _ScanType
{
    U16 wHt;
    U16 wVt;
    U16 wHtotal;
    U16 wVtotal;
    U16 wVend;
    U8  ucHshift;
    U8  ucX;
    U8  ucY;
}ScanType;

// output timing selection
typedef enum _PanelSelectType
{
    DAC_FOR_PAL_3375K,
    DAC_FOR_NTSC_3375K,
    DAC_FOR_VGA_3375K,
    DAC_FOR_YPBPR_3375K,
//    DAC_FOR_1080_3375K,
    DAC_FOR_PAL_3375K_75I,
    DAC_FOR_NTSC_3375K_90I,
    DAC_FOR_PAL_3375K_100I,
    DAC_FOR_NTSC_3375K_120I,
    DAC_FOR_NTSC_3375K_60I,
#ifdef  MULTI_HSYNC
    DAC_FOR_PAL_315K,
    DAC_FOR_NTSC_315K,
    DAC_FOR_VGA_315K,
    DAC_FOR_720P_315K,
    DAC_FOR_1080_315K,
    DAC_FOR_PAL_315K_100I,
    DAC_FOR_NTSC_315K_120I,

    DAC_FOR_PAL_375K,
    DAC_FOR_NTSC_375K,
    DAC_FOR_VGA_375K,
    DAC_FOR_720P_375K,
    DAC_FOR_1080_375K,
    DAC_FOR_PAL_375K_100I,
    DAC_FOR_NTSC_375K_120I,
#endif
    DAC_UNKNOWN,
    PANEL_SELECT_NUMS
}PanelSelectType;


////////////////////////////////////////////////////
// Panel power sequence
////////////////////////////////////////////////////
INTERFACE U16 msAPI_PnlCrtGetDeVStart(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtGetHSyncShift(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtGetHSyncWidth(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetHSyncBackPorch(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetVSyncWidth(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetVSyncBackPorch(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetDeWidth(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetDeHeight(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetHTotal(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetVTotal(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetHStart(PanelSelectType PnlSel);
INTERFACE U32 msAPI_PnlCrtGetOuputDClk(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtGetOutputCtrl(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtExtendFlag(PanelSelectType PnlSel);

INTERFACE U16 msAPI_PnlCrtGetScanHt(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetScanVt(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetScanHtotal(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetScanVtotal(PanelSelectType PnlSel);
INTERFACE U16 msAPI_PnlCrtGetScanVend(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtGetScanHshift(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtGetScanX(PanelSelectType PnlSel);
INTERFACE U8  msAPI_PnlCrtGetScanY(PanelSelectType PnlSel);

#define PANEL_HSYNC_SHIFT       msAPI_PnlCrtGetHSyncShift(g_u8CRT_OutTimingSel)
#define PANEL_HSYNC_WIDTH       msAPI_PnlCrtGetHSyncWidth(g_u8CRT_OutTimingSel)
#define PANEL_HSYNC_BACK_PORCH  msAPI_PnlCrtGetHSyncBackPorch(g_u8CRT_OutTimingSel)
#define PANEL_VSYNC_WIDTH       msAPI_PnlCrtGetVSyncWidth(g_u8CRT_OutTimingSel)
#define PANEL_VSYNC_BACK_PORCH  msAPI_PnlCrtGetVSyncBackPorch(g_u8CRT_OutTimingSel)

#if (ISCANENABLE)
#define PANEL_HSTART            msAPI_PnlCrtGetHStart(g_u8CRT_OutTimingSel)
#else
#define PANEL_HSTART            (PANEL_HSYNC_WIDTH+PANEL_HSYNC_BACK_PORCH)
#endif
#define PANEL_VSTART            (PANEL_VSYNC_WIDTH+PANEL_VSYNC_BACK_PORCH)
#define PANEL_WIDTH             msAPI_PnlCrtGetDeWidth(g_u8CRT_OutTimingSel)
#define PANEL_HEIGHT            msAPI_PnlCrtGetDeHeight(g_u8CRT_OutTimingSel)
#define PANEL_HTOTAL            msAPI_PnlCrtGetHTotal(g_u8CRT_OutTimingSel)
#define PANEL_VTOTAL            msAPI_PnlCrtGetVTotal(g_u8CRT_OutTimingSel)

#define PANEL_DCLK              msAPI_PnlCrtGetOuputDClk(g_u8CRT_OutTimingSel)
#define PANEL_MAX_DCLK          PANEL_DCLK
#define PANEL_MIN_DCLK          PANEL_DCLK
#define PANEL_MAX_HTOTAL        PANEL_HTOTAL
#define PANEL_MIN_HTOTAL        PANEL_VTOTAL
#define PANEL_MAX_VTOTAL        PANEL_VTOTAL
#define PANEL_MIN_VTOTAL        PANEL_VTOTAL

#define PANEL_FLAG              msAPI_PnlCrtGetOutputCtrl(g_u8CRT_OutTimingSel)
#define PANEL_EXTEND_FLAG       msAPI_PnlCrtExtendFlag(g_u8CRT_OutTimingSel)

////////////////////////////////////////////////////////////////////////
// Output timing selection
////////////////////////////////////////////////////////////////////////
#define DEFAULT_PANEL_SELECT        DAC_FOR_VGA_3375K//DAC_FOR_RESET
/*
#define DEFAULT_PANEL_PC            DAC_FOR_VGA_3375K
#define DEFAULT_PANEL_VIDEO_60      DAC_FOR_NTSC_3375K
#define DEFAULT_PANEL_VIDEO_50      DAC_FOR_PAL_3375K
#define DEFAULT_PANEL_YUV           DAC_FOR_PAL_3375K
#define DEFAULT_PANEL_VIDEO_120i    DAC_FOR_NTSC_3375K_120I
#define DEFAULT_PANEL_VIDEO_100i    DAC_FOR_PAL_3375K_100I
*/

/////////////////////////////////////////////////////////////
// Define color init value
/////////////////////////////////////////////////////////////

#define INIT_PC_BRI             0x80
#define INIT_PC_CON             0x80
#define INIT_PC_SHARP            0x18

#define INIT_TV_BRI             0x7A//0x80
#define INIT_TV_CON                  136//128
#define INIT_TV_HUE                  50
#define INIT_TV_SAT                  144//128
#define INIT_TV_SHARP                0x20

#define INIT_VIDEO_CB           0x80
#define INIT_VIDEO_CR           0x80

#define INIT_VIDEO_BRI          0x7A//0x80
#define INIT_VIDEO_CON          136//128
#define INIT_VIDEO_HUE          50
#define INIT_VIDEO_SAT          144//128
#define INIT_VIDEO_SHARP        0x20

#define INIT_VIDEO_MATRIX_R     135
#define INIT_VIDEO_MATRIX_G     128
#define INIT_VIDEO_MATRIX_B     135

#define INIT_YPBPR_BRI          0x7c//0x80
#define INIT_YPBPR_CON          137//0x80
#define INIT_YPBPR_HUE          50
#define INIT_YPBPR_SAT          130//0x80
#define INIT_YPBPR_SHARP        0x14

#define INIT_MSVD_COMB_CONTRAST     0x80
#define INIT_MSVD_COMB_BRIGHTNESS   0x88
#define INIT_MSVD_COMB_SATURATION   0xC6

///////////////////////////////////////////
// ACE init value
///////////////////////////////////////////

// For HDTV(Tuner) input
#define INIT_HDTV_MWE_CTRL            0x06 // BK5_10
#define INIT_HDTV_MWE_H_START_L       0x20 // BK5_11
#define INIT_HDTV_MWE_H_START_H       0x01 // BK5_12
#define INIT_HDTV_MWE_H_END_L         0xE8 // BK5_13
#define INIT_HDTV_MWE_H_END_H         0x03 // BK5_14
#define INIT_HDTV_MWE_V_START_L       0x64 // BK5_15
#define INIT_HDTV_MWE_V_START_H       0x00 // BK5_16
#define INIT_HDTV_MWE_V_END_L         0x9C // BK5_17
#define INIT_HDTV_MWE_V_END_H         0x02 // BK5_18
#define INIT_HDTV_MWE_Y_CTRL          0x00 // BK5_19
#define INIT_HDTV_MWE_FCC_CTRL        0x00 // BK5_1A
#define INIT_HDTV_MWE_Y_CORE_CTRL     0x00 // BK5_1B
#define INIT_HDTV_MWE_C_CORE_CTRL     0x00 // BK5_1C
#define INIT_HDTV_MWE_BRI             0xE8 // BK5_1F

#define INIT_HDTV_ICE_CTRL            0x70 // BK5_30
#define INIT_HDTV_ICE_DFRGE_R         0x20 // BK5_31
#define INIT_HDTV_ICE_DFRGE_G         0x28 // BK5_32
#define INIT_HDTV_ICE_DFRGE_B         0x20 // BK5_33
#define INIT_HDTV_ICE_ACTRGE_R        0x20 // BK5_34
#define INIT_HDTV_ICE_ACTRGE_G        0x28 // BK5_35
#define INIT_HDTV_ICE_ACTRGE_B        0x20 // BK5_36
#define INIT_HDTV_ICE_ACTRGE_C        0x19 // BK5_37
#define INIT_HDTV_ICE_ACTRGE_M        0x29 // BK5_38
#define INIT_HDTV_ICE_ACTRGE_Y        0x19 // BK5_39
#define INIT_HDTV_ICE_SAT_R           0x04 // BK5_3A
#define INIT_HDTV_ICE_SAT_G           0x08 // BK5_3B
#define INIT_HDTV_ICE_SAT_B           0x10 // BK5_3C
#define INIT_HDTV_ICE_SAT_C           0x08 // BK5_3D
#define INIT_HDTV_ICE_SAT_M           0x08 // BK5_3E
#define INIT_HDTV_ICE_SAT_Y           0x0C // BK5_3F
#define INIT_HDTV_ICE_HUE_R           0x48 // BK5_40
#define INIT_HDTV_ICE_HUE_G           0x00 // BK5_41
#define INIT_HDTV_ICE_HUE_B           0x00 // BK5_42
#define INIT_HDTV_ICE_HUE_C           0x00 // BK5_43
#define INIT_HDTV_ICE_HUE_M           0x00 // BK5_44
#define INIT_HDTV_ICE_HUE_Y           0x00 // BK5_45
#define INIT_HDTV_ICE_BRI_R           0x00 // BK5_46
#define INIT_HDTV_ICE_BRI_G           0x00 // BK5_47
#define INIT_HDTV_ICE_BRI_B           0x00 // BK5_48
#define INIT_HDTV_ICE_BRI_C           0x00 // BK5_49
#define INIT_HDTV_ICE_BRI_M           0x00 // BK5_4A
#define INIT_HDTV_ICE_BRI_Y           0x00 // BK5_4B
#define INIT_HDTV_WT_TH_L             0x00 // BK5_4C
#define INIT_HDTV_WT_TH_H             0x00 // BK5_4D

#define INIT_HDTV_FCC_CB_1T           0x73 // BK5_56
#define INIT_HDTV_FCC_CR_1T           0xA1 // BK5_57
#define INIT_HDTV_FCC_CB_2T           0x6E // BK5_58
#define INIT_HDTV_FCC_CR_2T           0xAC // BK5_59
#define INIT_HDTV_FCC_CB_3T           0xA5 // BK5_5A
#define INIT_HDTV_FCC_CR_3T           0x69 // BK5_5B
#define INIT_HDTV_FCC_CB_4T           0x5A // BK5_5C
#define INIT_HDTV_FCC_CR_4T           0x9A // BK5_5D
#define INIT_HDTV_FCC_CB_5T           0x5A // BK5_5E
#define INIT_HDTV_FCC_CR_5T           0x75 // BK5_5F
#define INIT_HDTV_FCC_CB_6T           0xB0 // BK5_60
#define INIT_HDTV_FCC_CR_6T           0x48 // BK5_61
#define INIT_HDTV_FCC_CB_7T           0x64 // BK5_62
#define INIT_HDTV_FCC_CR_7T           0xC8 // BK5_63
#define INIT_HDTV_FCC_CB_8T           0x80 // BK5_64
#define INIT_HDTV_FCC_CR_8T           0x80 // BK5_65
#define INIT_HDTV_WHITE_STOP          0x88 // BK5_66
#define INIT_HDTV_BLACK_STOP          0x84 // BK5_67

#define INIT_HDTV_FCC_WIN1            0xB2 // BK5_68
#define INIT_HDTV_FCC_WIN2            0xBA // BK5_69
#define INIT_HDTV_FCC_WIN3            0xFB // BK5_6A
#define INIT_HDTV_FCC_WIN4            0x73 // BK5_6B
#define INIT_HDTV_FCC_WIN5            0xFB // BK5_6C
#define INIT_HDTV_FCC_WIN6            0xFB // BK5_6D
#define INIT_HDTV_FCC_WIN7            0xFF // BK5_6E
#define INIT_HDTV_FCC_WIN8            0x6A // BK5_6F
#define INIT_HDTV_FCC_WIN9            0x00 // BK5_70

#define INIT_HDTV_FCC_Y_TH            0xFF // BK5_71
#define INIT_HDTV_FCC_K1K2            0x60 // BK5_72
#define INIT_HDTV_FCC_K3K4            0x88 // BK5_73
#define INIT_HDTV_FCC_K5K6            0xC8 // BK5_74
#define INIT_HDTV_FCC_K7K8            0x85 // BK5_75
#define INIT_HDTV_FCC_CTRL            0x00 // BK5_76
#define INIT_HDTV_APP_CTRL            0x7E // BK5_77
#define INIT_HDTV_PEAK_BAND1          0x20 // BK5_78
#define INIT_HDTV_PEAK_BAND2          0x60 // BK5_79
#define INIT_HDTV_LTI                 0xB0 // BK5_7A
#define INIT_HDTV_TERM_SEL            0xE4 // BK5_7B
#define INIT_HDTV_CORING              0x52 // BK5_7C
#define INIT_HDTV_CTI                 0x98 // BK5_7D
#define INIT_HDTV_VIP_Y_CTRL          0x01 // BK5_7E
#define INIT_HDTV_WHITE_START         0xA0 // BK5_7F
#define INIT_HDTV_BLACK_START         0x40 // BK5_80
#define INIT_HDTV_EGE_BAND1_POS       0x20 // BK5_81
#define INIT_HDTV_EGE_BAND1_NEG       0x20 // BK5_82
#define INIT_HDTV_EGE_BAND2_POS       0x0C // BK5_83
#define INIT_HDTV_EGE_BAND2_NEG       0x04 // BK5_84
#define INIT_HDTV_Y_BRI               0xFA // BK5_85
#define INIT_HDTV_EGE_LTI_POS         0x02 // BK5_86
#define INIT_HDTV_EGE_LTI_NEG         0x02 // BK5_87
#define INIT_HDTV_YC_LPF              0xBC // BK5_88

#define INIT_HDTV_Y_CORING_CTRL       0x33 // BK5_8A
#define INIT_HDTV_C_CORING_CTRL       0x43 // BK5_8B
#define INIT_HDTV_CORING_TBL1         0xDF // BK5_8C
#define INIT_HDTV_CORING_TBL2         0x9B // BK5_8D
#define INIT_HDTV_CORING_TBL3         0x36 // BK5_8E
#define INIT_HDTV_CORING_TBL4         0x01 // BK5_8F

#define INIT_HDTV_MAIN_HIS_HST        0x00 // BK5_90
#define INIT_HDTV_MAIN_HIS_HED        0x00 // BK5_91
#define INIT_HDTV_MAIN_HIS_VST        0x00 // BK5_92
#define INIT_HDTV_MAIN_HIS_VED        0x00 // BK5_93
#define INIT_HDTV_MAIN_WIN_MN_PX      0x00 // BK5_94
#define INIT_HDTV_MAIN_WIN_MX_PX      0xD7 // BK5_95
#define INIT_HDTV_HIS_WEIGHT_L        0x00 // BK5_96
#define INIT_HDTV_HIS_WEIGHT_H        0x25 // BK5_97
#define INIT_HDTV_HIS_HANDSHAKE       0xCE // BK5_98
#define INIT_HDTV_HIS_CF_ADDR         0x11 // BK5_99
#define INIT_HDTV_HIS_CF_DATA         0x07 // BK5_9A
#define INIT_HDTV_DLC_INC_CTRL        0x00 // BK5_9B

#define INIT_HDTV_VPK_CTRL            0x83 // BK5_A0
#define INIT_HDTV_VPK_STEP1           0x11 // BK5_A1
#define INIT_HDTV_VPK_STEP2           0x21 // BK5_A2
#define INIT_HDTV_VPK_VER_TH          0x04 // BK5_A3
#define INIT_HDTV_VPK_HOR_TH          0x04 // BK5_A4
#define INIT_HDTV_VPK_DIA_TH          0x04 // BK5_A5
#define INIT_HDTV_VPK_CORING          0x21 // BK5_A6
#define INIT_HDTV_VPK_OVERSHOOT       0xFF // BK5_A7
#define INIT_HDTV_VPK_UNDERSHOOT      0xFF // BK5_A8
#define INIT_HDTV_VPK_USER_ADJ        0x02 // BK5_A9
#define INIT_HDTV_VPK_VER_LUT_ADDR    0x00 // BK5_AA
#define INIT_HDTV_VPK_VER_LUT_DATA    0x3F // BK5_AB
#define INIT_HDTV_VPK_HOR_LUT_ADDR    0x00 // BK5_AC
#define INIT_HDTV_VPK_HOR_LUT_DATA    0x3F // BK5_AD
#define INIT_HDTV_VPK_DIA_LUT_ADDR    0x00 // BK5_AE
#define INIT_HDTV_VPK_DIA_LUT_DATA    0x3F // BK5_AF

#define INIT_HDTV_SNR_CTRL            0x39 // BK5_B0
#define INIT_HDTV_GAUSS_THRD          0x03 // BK5_B1
#define INIT_HDTV_FLESH_SLPE          0x08 // BK5_B2
#define INIT_HDTV_FLESH_CB_U          0x7D // BK5_B3
#define INIT_HDTV_FLESH_CR_U          0x9B // BK5_B4
#define INIT_HDTV_FLESH_CB_D          0x69 // BK5_B5
#define INIT_HDTV_FLESH_CR_D          0x87 // BK5_B6
#define INIT_HDTV_GREEN_SLPE          0x08 // BK5_B7
#define INIT_HDTV_GREEN_CB_U          0x7A // BK5_B8
#define INIT_HDTV_GREEN_CR_U          0x85 // BK5_B9
#define INIT_HDTV_GREEN_CB_D          0x3A // BK5_BA
#define INIT_HDTV_GREEN_CR_D          0x55 // BK5_BB

#define INIT_HDTV_SNR_TABLE_0         0xFF // BK5_C0
#define INIT_HDTV_SNR_TABLE_1         0xFF // BK5_C1
#define INIT_HDTV_SNR_TABLE_2         0xFA // BK5_C2
#define INIT_HDTV_SNR_TABLE_3         0xA6 // BK5_C3
#define INIT_HDTV_SNR_TABLE_4         0x43 // BK5_C4
#define INIT_HDTV_SNR_TABLE_5         0x32 // BK5_C5
#define INIT_HDTV_SNR_TABLE_6         0x00 // BK5_C6
#define INIT_HDTV_SNR_TABLE_7         0x00 // BK5_C7

// For TV(Tuner) input
#define INIT_TV_MWE_CTRL            0x06 // BK5_10
#define INIT_TV_MWE_H_START_L       0x20 // BK5_11
#define INIT_TV_MWE_H_START_H       0x01 // BK5_12
#define INIT_TV_MWE_H_END_L         0xE8 // BK5_13
#define INIT_TV_MWE_H_END_H         0x03 // BK5_14
#define INIT_TV_MWE_V_START_L       0x64 // BK5_15
#define INIT_TV_MWE_V_START_H       0x00 // BK5_16
#define INIT_TV_MWE_V_END_L         0x9C // BK5_17
#define INIT_TV_MWE_V_END_H         0x02 // BK5_18
#define INIT_TV_MWE_Y_CTRL          0x00 // BK5_19
#define INIT_TV_MWE_FCC_CTRL        0x00 // BK5_1A
#define INIT_TV_MWE_Y_CORE_CTRL     0x00 // BK5_1B
#define INIT_TV_MWE_C_CORE_CTRL     0x00 // BK5_1C
#define INIT_TV_MWE_BRI             0xE8 // BK5_1F

#define INIT_TV_ICE_CTRL            0x70 // BK5_30
#define INIT_TV_ICE_DFRGE_R         0x20 // BK5_31
#define INIT_TV_ICE_DFRGE_G         0x28 // BK5_32
#define INIT_TV_ICE_DFRGE_B         0x20 // BK5_33
#define INIT_TV_ICE_ACTRGE_R        0x20 // BK5_34
#define INIT_TV_ICE_ACTRGE_G        0x28 // BK5_35
#define INIT_TV_ICE_ACTRGE_B        0x20 // BK5_36
#define INIT_TV_ICE_ACTRGE_C        0x19 // BK5_37
#define INIT_TV_ICE_ACTRGE_M        0x29 // BK5_38
#define INIT_TV_ICE_ACTRGE_Y        0x19 // BK5_39
#define INIT_TV_ICE_SAT_R           0x00 // BK5_3A
#define INIT_TV_ICE_SAT_G           0x00 // BK5_3B
#define INIT_TV_ICE_SAT_B           0x00 // BK5_3C
#define INIT_TV_ICE_SAT_C           0x00 // BK5_3D
#define INIT_TV_ICE_SAT_M           0x08 // BK5_3E
#define INIT_TV_ICE_SAT_Y           0x00 // BK5_3F
#define INIT_TV_ICE_HUE_R           0x44 // BK5_40
#define INIT_TV_ICE_HUE_G           0x50 // BK5_41
#define INIT_TV_ICE_HUE_B           0x00 // BK5_42
#define INIT_TV_ICE_HUE_C           0x00 // BK5_43
#define INIT_TV_ICE_HUE_M           0x44 // BK5_44
#define INIT_TV_ICE_HUE_Y           0x00 // BK5_45
#define INIT_TV_ICE_BRI_R           0x00 // BK5_46
#define INIT_TV_ICE_BRI_G           0x00 // BK5_47
#define INIT_TV_ICE_BRI_B           0x00 // BK5_48
#define INIT_TV_ICE_BRI_C           0x00 // BK5_49
#define INIT_TV_ICE_BRI_M           0x00 // BK5_4A
#define INIT_TV_ICE_BRI_Y           0x00 // BK5_4B
#define INIT_TV_WT_TH_L             0x00 // BK5_4C
#define INIT_TV_WT_TH_H             0x00 // BK5_4D

#define INIT_TV_FCC_CB_1T           0x73 // BK5_56
#define INIT_TV_FCC_CR_1T           0xA1 // BK5_57
#define INIT_TV_FCC_CB_2T           0x6E // BK5_58
#define INIT_TV_FCC_CR_2T           0xAC // BK5_59
#define INIT_TV_FCC_CB_3T           0xA5 // BK5_5A
#define INIT_TV_FCC_CR_3T           0x69 // BK5_5B
#define INIT_TV_FCC_CB_4T           0x5A // BK5_5C
#define INIT_TV_FCC_CR_4T           0x9A // BK5_5D
#define INIT_TV_FCC_CB_5T           0x5A // BK5_5E
#define INIT_TV_FCC_CR_5T           0x75 // BK5_5F
#define INIT_TV_FCC_CB_6T           0xB0 // BK5_60
#define INIT_TV_FCC_CR_6T           0x48 // BK5_61
#define INIT_TV_FCC_CB_7T           0x64 // BK5_62
#define INIT_TV_FCC_CR_7T           0xC8 // BK5_63
#define INIT_TV_FCC_CB_8T           0x80 // BK5_64
#define INIT_TV_FCC_CR_8T           0x80 // BK5_65
#define INIT_TV_WHITE_STOP          0x88 // BK5_66
#define INIT_TV_BLACK_STOP          0xA2 // BK5_67

#define INIT_TV_FCC_WIN1            0xB2 // BK5_68
#define INIT_TV_FCC_WIN2            0xBA // BK5_69
#define INIT_TV_FCC_WIN3            0xFB // BK5_6A
#define INIT_TV_FCC_WIN4            0x73 // BK5_6B
#define INIT_TV_FCC_WIN5            0xFB // BK5_6C
#define INIT_TV_FCC_WIN6            0xFB // BK5_6D
#define INIT_TV_FCC_WIN7            0xFF // BK5_6E
#define INIT_TV_FCC_WIN8            0x6A // BK5_6F
#define INIT_TV_FCC_WIN9            0x00 // BK5_70

#define INIT_TV_FCC_Y_TH            0xFF // BK5_71
#define INIT_TV_FCC_K1K2            0x60 // BK5_72
#define INIT_TV_FCC_K3K4            0x88 // BK5_73
#define INIT_TV_FCC_K5K6            0xC8 // BK5_74
#define INIT_TV_FCC_K7K8            0x85 // BK5_75
#define INIT_TV_FCC_CTRL            0x40 // BK5_76
#define INIT_TV_APP_CTRL            0x76 // BK5_77
#define INIT_TV_PEAK_BAND1          0x20 // BK5_78
#define INIT_TV_PEAK_BAND2          0x60 // BK5_79
#define INIT_TV_LTI                 0xB0 // BK5_7A
#define INIT_TV_TERM_SEL            0xE4 // BK5_7B
#define INIT_TV_CORING              0x43 // BK5_7C
#define INIT_TV_CTI                 0x4C // BK5_7D
#define INIT_TV_VIP_Y_CTRL          0x01 // BK5_7E
#define INIT_TV_WHITE_START         0xA0 // BK5_7F
#define INIT_TV_BLACK_START         0x40 // BK5_80
#define INIT_TV_EGE_BAND1_POS       0x20 // BK5_81
#define INIT_TV_EGE_BAND1_NEG       0x20 // BK5_82
#define INIT_TV_EGE_BAND2_POS       0x0C // BK5_83
#define INIT_TV_EGE_BAND2_NEG       0x04 // BK5_84
#define INIT_TV_Y_BRI               0x03 // BK5_85
#define INIT_TV_EGE_LTI_POS         0x02 // BK5_86
#define INIT_TV_EGE_LTI_NEG         0x02 // BK5_87
#define INIT_TV_YC_LPF              0xFC // BK5_88

#define INIT_TV_Y_CORING_CTRL       0x47 // BK5_8A
#define INIT_TV_C_CORING_CTRL       0x36 // BK5_8B
#define INIT_TV_CORING_TBL1         0xDF // BK5_8C
#define INIT_TV_CORING_TBL2         0x9B // BK5_8D
#define INIT_TV_CORING_TBL3         0x36 // BK5_8E
#define INIT_TV_CORING_TBL4         0x01 // BK5_8F

#define INIT_TV_MAIN_HIS_HST        0x00 // BK5_90
#define INIT_TV_MAIN_HIS_HED        0x00 // BK5_91
#define INIT_TV_MAIN_HIS_VST        0x00 // BK5_92
#define INIT_TV_MAIN_HIS_VED        0x00 // BK5_93
#define INIT_TV_MAIN_WIN_MN_PX      0x00 // BK5_94
#define INIT_TV_MAIN_WIN_MX_PX      0xD7 // BK5_95
#define INIT_TV_HIS_WEIGHT_L        0x00 // BK5_96
#define INIT_TV_HIS_WEIGHT_H        0x25 // BK5_97
#define INIT_TV_HIS_HANDSHAKE       0xCE // BK5_98
#define INIT_TV_HIS_CF_ADDR         0x11 // BK5_99
#define INIT_TV_HIS_CF_DATA         0x07 // BK5_9A
#define INIT_TV_DLC_INC_CTRL        0x00 // BK5_9B

#define INIT_TV_VPK_CTRL            0x8b // BK5_A0
#define INIT_TV_VPK_STEP1           0x11 // BK5_A1
#define INIT_TV_VPK_STEP2           0x21 // BK5_A2
#define INIT_TV_VPK_VER_TH          0x04 // BK5_A3
#define INIT_TV_VPK_HOR_TH          0x04 // BK5_A4
#define INIT_TV_VPK_DIA_TH          0x04 // BK5_A5
#define INIT_TV_VPK_CORING          0x21 // BK5_A6
#define INIT_TV_VPK_OVERSHOOT       0xFF // BK5_A7
#define INIT_TV_VPK_UNDERSHOOT      0xFF // BK5_A8
#define INIT_TV_VPK_USER_ADJ        0x02 // BK5_A9
#define INIT_TV_VPK_VER_LUT_ADDR    0x00 // BK5_AA
#define INIT_TV_VPK_VER_LUT_DATA    0x3F // BK5_AB
#define INIT_TV_VPK_HOR_LUT_ADDR    0x00 // BK5_AC
#define INIT_TV_VPK_HOR_LUT_DATA    0x3F // BK5_AD
#define INIT_TV_VPK_DIA_LUT_ADDR    0x00 // BK5_AE
#define INIT_TV_VPK_DIA_LUT_DATA    0x3F // BK5_AF

#define INIT_TV_SNR_CTRL            0x37 // BK5_B0
#define INIT_TV_GAUSS_THRD          0x08 // BK5_B1
#define INIT_TV_FLESH_SLPE          0x08 // BK5_B2
#define INIT_TV_FLESH_CB_U          0x7D // BK5_B3
#define INIT_TV_FLESH_CR_U          0x9B // BK5_B4
#define INIT_TV_FLESH_CB_D          0x69 // BK5_B5
#define INIT_TV_FLESH_CR_D          0x87 // BK5_B6
#define INIT_TV_GREEN_SLPE          0x08 // BK5_B7
#define INIT_TV_GREEN_CB_U          0x7A // BK5_B8
#define INIT_TV_GREEN_CR_U          0x85 // BK5_B9
#define INIT_TV_GREEN_CB_D          0x3A // BK5_BA
#define INIT_TV_GREEN_CR_D          0x55 // BK5_BB

#define INIT_TV_SNR_TABLE_0         0xE5 // BK5_C0
#define INIT_TV_SNR_TABLE_1         0xC5 // BK5_C1
#define INIT_TV_SNR_TABLE_2         0x7A // BK5_C2
#define INIT_TV_SNR_TABLE_3         0x32 // BK5_C3
#define INIT_TV_SNR_TABLE_4         0x11 // BK5_C4
#define INIT_TV_SNR_TABLE_5         0x01 // BK5_C5
#define INIT_TV_SNR_TABLE_6         0x00 // BK5_C6
#define INIT_TV_SNR_TABLE_7         0x00 // BK5_C7

// For VIDEO(CVBS) input
#define INIT_VIDEO_MWE_CTRL         0x06 // BK5_10
#define INIT_VIDEO_MWE_H_START_L    0x20 // BK5_11
#define INIT_VIDEO_MWE_H_START_H    0x01 // BK5_12
#define INIT_VIDEO_MWE_H_END_L      0xE8 // BK5_13
#define INIT_VIDEO_MWE_H_END_H      0x03 // BK5_14
#define INIT_VIDEO_MWE_V_START_L    0x64 // BK5_15
#define INIT_VIDEO_MWE_V_START_H    0x00 // BK5_16
#define INIT_VIDEO_MWE_V_END_L      0x9C // BK5_17
#define INIT_VIDEO_MWE_V_END_H      0x02 // BK5_18
#define INIT_VIDEO_MWE_Y_CTRL       0x00 // BK5_19
#define INIT_VIDEO_MWE_FCC_CTRL     0x00 // BK5_1A
#define INIT_VIDEO_MWE_Y_CORE_CTRL  0x00 // BK5_1B
#define INIT_VIDEO_MWE_C_CORE_CTRL  0x00 // BK5_1C
#define INIT_VIDEO_MWE_BRI          0xE8 // BK5_1F

#define INIT_VIDEO_ICE_CTRL         0x70 // BK5_30
#define INIT_VIDEO_ICE_DFRGE_R      0x20 // BK5_31
#define INIT_VIDEO_ICE_DFRGE_G      0x28 // BK5_32
#define INIT_VIDEO_ICE_DFRGE_B      0x20 // BK5_33
#define INIT_VIDEO_ICE_ACTRGE_R     0x20 // BK5_34
#define INIT_VIDEO_ICE_ACTRGE_G     0x28 // BK5_35
#define INIT_VIDEO_ICE_ACTRGE_B     0x20 // BK5_36
#define INIT_VIDEO_ICE_ACTRGE_C     0x19 // BK5_37
#define INIT_VIDEO_ICE_ACTRGE_M     0x29 // BK5_38
#define INIT_VIDEO_ICE_ACTRGE_Y     0x19 // BK5_39

#define INIT_VIDEO_ICE_SAT_R        0x08 // BK5_3A
#define INIT_VIDEO_ICE_SAT_G        0x04 // BK5_3B
#define INIT_VIDEO_ICE_SAT_B        0x08 // BK5_3C
#define INIT_VIDEO_ICE_SAT_C        0x00 // BK5_3D
#define INIT_VIDEO_ICE_SAT_M        0x08 // BK5_3E
#define INIT_VIDEO_ICE_SAT_Y        0x08 // BK5_3F
#define INIT_VIDEO_ICE_HUE_R        0x02 // BK5_40
#define INIT_VIDEO_ICE_HUE_G        0x00 // BK5_41
#define INIT_VIDEO_ICE_HUE_B        0x20 // BK5_42
#define INIT_VIDEO_ICE_HUE_C        0x10 // BK5_43
#define INIT_VIDEO_ICE_HUE_M        0x44 // BK5_44
#define INIT_VIDEO_ICE_HUE_Y        0x00 // BK5_45
#define INIT_VIDEO_ICE_BRI_R        0x10 // BK5_46
#define INIT_VIDEO_ICE_BRI_G        0x00 // BK5_47
#define INIT_VIDEO_ICE_BRI_B        0x10 // BK5_48
#define INIT_VIDEO_ICE_BRI_C        0x00 // BK5_49
#define INIT_VIDEO_ICE_BRI_M        0x00 // BK5_4A
#define INIT_VIDEO_ICE_BRI_Y        0x00 // BK5_4B
#define INIT_VIDEO_WT_TH_L          0x00 // BK5_4C
#define INIT_VIDEO_WT_TH_H          0x00 // BK5_4D

#define INIT_VIDEO_FCC_CB_1T        0x73 // BK5_56
#define INIT_VIDEO_FCC_CR_1T        0xA1 // BK5_57
#define INIT_VIDEO_FCC_CB_2T        0x6E // BK5_58
#define INIT_VIDEO_FCC_CR_2T        0xAC // BK5_59
#define INIT_VIDEO_FCC_CB_3T        0xA5 // BK5_5A
#define INIT_VIDEO_FCC_CR_3T        0x69 // BK5_5B
#define INIT_VIDEO_FCC_CB_4T        0x5A // BK5_5C
#define INIT_VIDEO_FCC_CR_4T        0x9A // BK5_5D
#define INIT_VIDEO_FCC_CB_5T        0x5A // BK5_5E
#define INIT_VIDEO_FCC_CR_5T        0x75 // BK5_5F
#define INIT_VIDEO_FCC_CB_6T        0xB0 // BK5_60
#define INIT_VIDEO_FCC_CR_6T        0x48 // BK5_61
#define INIT_VIDEO_FCC_CB_7T        0x64 // BK5_62
#define INIT_VIDEO_FCC_CR_7T        0xC8 // BK5_63
#define INIT_VIDEO_FCC_CB_8T        0x80 // BK5_64
#define INIT_VIDEO_FCC_CR_8T        0x80 // BK5_65
#define INIT_VIDEO_WHITE_STOP       0x88 // BK5_66
#define INIT_VIDEO_BLACK_STOP       0x98 // BK5_67
#define INIT_VIDEO_FCC_WIN1         0xB2 // BK5_68
#define INIT_VIDEO_FCC_WIN2         0xBA // BK5_69
#define INIT_VIDEO_FCC_WIN3         0xFB // BK5_6A
#define INIT_VIDEO_FCC_WIN4         0x73 // BK5_6B
#define INIT_VIDEO_FCC_WIN5         0xFB // BK5_6C
#define INIT_VIDEO_FCC_WIN6         0xFB // BK5_6D
#define INIT_VIDEO_FCC_WIN7         0xFF // BK5_6E
#define INIT_VIDEO_FCC_WIN8         0x6A // BK5_6F
#define INIT_VIDEO_FCC_WIN9         0x00 // BK5_70
#define INIT_VIDEO_FCC_Y_TH         0xFF // BK5_71
#define INIT_VIDEO_FCC_K1K2         0x60 // BK5_72
#define INIT_VIDEO_FCC_K3K4         0x88 // BK5_73
#define INIT_VIDEO_FCC_K5K6         0xC8 // BK5_74
#define INIT_VIDEO_FCC_K7K8         0x85 // BK5_75
#define INIT_VIDEO_FCC_CTRL         0x48 // BK5_76
#define INIT_VIDEO_APP_CTRL         0x76 // BK5_77
#define INIT_VIDEO_PEAK_BAND1       0x20 // BK5_78
#define INIT_VIDEO_PEAK_BAND2       0x60 // BK5_79
#define INIT_VIDEO_LTI              0xB0 // BK5_7A
#define INIT_VIDEO_TERM_SEL         0xE4 // BK5_7B
#define INIT_VIDEO_CORING           0x32 // BK5_7C
#define INIT_VIDEO_CTI              0x58 // BK5_7D
#define INIT_VIDEO_VIP_Y_CTRL       0x01 // BK5_7E
#define INIT_VIDEO_WHITE_START      0xA0 // BK5_7F
#define INIT_VIDEO_BLACK_START      0x40 // BK5_80

#define INIT_VIDEO_EGE_BAND1_POS    0x10 // BK5_81
#define INIT_VIDEO_EGE_BAND1_NEG    0x10 // BK5_82
#define INIT_VIDEO_EGE_BAND2_POS    0x00 // BK5_83
#define INIT_VIDEO_EGE_BAND2_NEG    0x00 // BK5_84

#define INIT_VIDEO_Y_BRI            0x06 // BK5_85

#define INIT_VIDEO_EGE_LTI_POS      0x00 // BK5_86
#define INIT_VIDEO_EGE_LTI_NEG      0x00 // BK5_87
#define INIT_VIDEO_YC_LPF           0xFC // BK5_88

#define INIT_VIDEO_Y_CORING_CTRL    0x47 // BK5_8A
#define INIT_VIDEO_C_CORING_CTRL    0x36 // BK5_8B
#define INIT_VIDEO_CORING_TBL1      0xDF // BK5_8C
#define INIT_VIDEO_CORING_TBL2      0x9B // BK5_8D
#define INIT_VIDEO_CORING_TBL3      0x36 // BK5_8E
#define INIT_VIDEO_CORING_TBL4      0x01 // BK5_8F

#define INIT_VIDEO_MAIN_HIS_HST     0x00 // BK5_90
#define INIT_VIDEO_MAIN_HIS_HED     0x00 // BK5_91
#define INIT_VIDEO_MAIN_HIS_VST     0x00 // BK5_92
#define INIT_VIDEO_MAIN_HIS_VED     0x00 // BK5_93
#define INIT_VIDEO_MAIN_WIN_MN_PX   0x00 // BK5_94
#define INIT_VIDEO_MAIN_WIN_MX_PX   0xD7 // BK5_95
#define INIT_VIDEO_HIS_WEIGHT_L     0x00 // BK5_96
#define INIT_VIDEO_HIS_WEIGHT_H     0x25 // BK5_97
#define INIT_VIDEO_HIS_HANDSHAKE    0xCE // BK5_98
#define INIT_VIDEO_HIS_CF_ADDR      0x11 // BK5_99
#define INIT_VIDEO_HIS_CF_DATA      0x07 // BK5_9A
#define INIT_VIDEO_DLC_INC_CTRL     0x00 // BK5_9B

#define INIT_VIDEO_VPK_CTRL         0x8B // BK5_A0
#define INIT_VIDEO_VPK_STEP1        0x11 // BK5_A1
#define INIT_VIDEO_VPK_STEP2        0x21 // BK5_A2
#define INIT_VIDEO_VPK_VER_TH       0x04 // BK5_A3
#define INIT_VIDEO_VPK_HOR_TH       0x04 // BK5_A4
#define INIT_VIDEO_VPK_DIA_TH       0x04 // BK5_A5
#define INIT_VIDEO_VPK_CORING       0x21 // BK5_A6
#define INIT_VIDEO_VPK_OVERSHOOT    0xFF // BK5_A7
#define INIT_VIDEO_VPK_UNDERSHOOT   0xFF // BK5_A8
#define INIT_VIDEO_VPK_USER_ADJ     0x0C // BK5_A9
#define INIT_VIDEO_VPK_VER_LUT_ADDR 0x00 // BK5_AA
#define INIT_VIDEO_VPK_VER_LUT_DATA 0x3F // BK5_AB
#define INIT_VIDEO_VPK_HOR_LUT_ADDR 0x00 // BK5_AC
#define INIT_VIDEO_VPK_HOR_LUT_DATA 0x3F // BK5_AD
#define INIT_VIDEO_VPK_DIA_LUT_ADDR 0x00 // BK5_AE
#define INIT_VIDEO_VPK_DIA_LUT_DATA 0x3F // BK5_AF

#define INIT_VIDEO_SNR_CTRL         0x17 // BK5_B0
#define INIT_VIDEO_GAUSS_THRD       0x08 // BK5_B1
#define INIT_VIDEO_FLESH_SLPE       0x08 // BK5_B2
#define INIT_VIDEO_FLESH_CB_U       0x7D // BK5_B3
#define INIT_VIDEO_FLESH_CR_U       0x9B // BK5_B4
#define INIT_VIDEO_FLESH_CB_D       0x69 // BK5_B5
#define INIT_VIDEO_FLESH_CR_D       0x87 // BK5_B6
#define INIT_VIDEO_GREEN_SLPE       0x08 // BK5_B7
#define INIT_VIDEO_GREEN_CB_U       0x7A // BK5_B8
#define INIT_VIDEO_GREEN_CR_U       0x85 // BK5_B9
#define INIT_VIDEO_GREEN_CB_D       0x3A // BK5_BA
#define INIT_VIDEO_GREEN_CR_D       0x55 // BK5_BB

#define INIT_VIDEO_SNR_TABLE_0      0x95 // BK5_C0
#define INIT_VIDEO_SNR_TABLE_1      0x72 // BK5_C1
#define INIT_VIDEO_SNR_TABLE_2      0x43 // BK5_C2
#define INIT_VIDEO_SNR_TABLE_3      0x32 // BK5_C3
#define INIT_VIDEO_SNR_TABLE_4      0x11 // BK5_C4
#define INIT_VIDEO_SNR_TABLE_5      0x01 // BK5_C5
#define INIT_VIDEO_SNR_TABLE_6      0x00 // BK5_C6
#define INIT_VIDEO_SNR_TABLE_7      0x00 // BK5_C7

// For VIDEO(S-VIDEO) input
#define INIT_SVIDEO_MWE_CTRL         0x06 // BK5_10
#define INIT_SVIDEO_MWE_H_START_L    0x20 // BK5_11
#define INIT_SVIDEO_MWE_H_START_H    0x01 // BK5_12
#define INIT_SVIDEO_MWE_H_END_L      0xE8 // BK5_13
#define INIT_SVIDEO_MWE_H_END_H      0x03 // BK5_14
#define INIT_SVIDEO_MWE_V_START_L    0x64 // BK5_15
#define INIT_SVIDEO_MWE_V_START_H    0x00 // BK5_16
#define INIT_SVIDEO_MWE_V_END_L      0x9C // BK5_17
#define INIT_SVIDEO_MWE_V_END_H      0x02 // BK5_18
#define INIT_SVIDEO_MWE_Y_CTRL       0x00 // BK5_19
#define INIT_SVIDEO_MWE_FCC_CTRL     0x00 // BK5_1A
#define INIT_SVIDEO_MWE_Y_CORE_CTRL  0x00 // BK5_1B
#define INIT_SVIDEO_MWE_C_CORE_CTRL  0x00 // BK5_1C
#define INIT_SVIDEO_MWE_BRI          0xE8 // BK5_1F

#define INIT_SVIDEO_ICE_CTRL         0x70 // BK5_30
#define INIT_SVIDEO_ICE_DFRGE_R      0x20 // BK5_31
#define INIT_SVIDEO_ICE_DFRGE_G      0x28 // BK5_32
#define INIT_SVIDEO_ICE_DFRGE_B      0x20 // BK5_33
#define INIT_SVIDEO_ICE_ACTRGE_R     0x20 // BK5_34
#define INIT_SVIDEO_ICE_ACTRGE_G     0x28 // BK5_35
#define INIT_SVIDEO_ICE_ACTRGE_B     0x20 // BK5_36
#define INIT_SVIDEO_ICE_ACTRGE_C     0x19 // BK5_37
#define INIT_SVIDEO_ICE_ACTRGE_M     0x29 // BK5_38
#define INIT_SVIDEO_ICE_ACTRGE_Y     0x19 // BK5_39

#define INIT_SVIDEO_ICE_SAT_R        0x08 // BK5_3A
#define INIT_SVIDEO_ICE_SAT_G        0x04 // BK5_3B
#define INIT_SVIDEO_ICE_SAT_B        0x08 // BK5_3C
#define INIT_SVIDEO_ICE_SAT_C        0x00 // BK5_3D
#define INIT_SVIDEO_ICE_SAT_M        0x08 // BK5_3E
#define INIT_SVIDEO_ICE_SAT_Y        0x08 // BK5_3F
#define INIT_SVIDEO_ICE_HUE_R        0x02 // BK5_40
#define INIT_SVIDEO_ICE_HUE_G        0x00 // BK5_41
#define INIT_SVIDEO_ICE_HUE_B        0x20 // BK5_42
#define INIT_SVIDEO_ICE_HUE_C        0x10 // BK5_43
#define INIT_SVIDEO_ICE_HUE_M        0x44 // BK5_44
#define INIT_SVIDEO_ICE_HUE_Y        0x00 // BK5_45
#define INIT_SVIDEO_ICE_BRI_R        0x10 // BK5_46
#define INIT_SVIDEO_ICE_BRI_G        0x00 // BK5_47
#define INIT_SVIDEO_ICE_BRI_B        0x10 // BK5_48
#define INIT_SVIDEO_ICE_BRI_C        0x00 // BK5_49
#define INIT_SVIDEO_ICE_BRI_M        0x00 // BK5_4A
#define INIT_SVIDEO_ICE_BRI_Y        0x00 // BK5_4B

#define INIT_SVIDEO_WT_TH_L          0x00 // BK5_4C
#define INIT_SVIDEO_WT_TH_H          0x00 // BK5_4D

#define INIT_SVIDEO_FCC_CB_1T        0x73 // BK5_56
#define INIT_SVIDEO_FCC_CR_1T        0xA1 // BK5_57
#define INIT_SVIDEO_FCC_CB_2T        0x6E // BK5_58
#define INIT_SVIDEO_FCC_CR_2T        0xAC // BK5_59
#define INIT_SVIDEO_FCC_CB_3T        0xA5 // BK5_5A
#define INIT_SVIDEO_FCC_CR_3T        0x69 // BK5_5B
#define INIT_SVIDEO_FCC_CB_4T        0x5A // BK5_5C
#define INIT_SVIDEO_FCC_CR_4T        0x9A // BK5_5D
#define INIT_SVIDEO_FCC_CB_5T        0x5A // BK5_5E
#define INIT_SVIDEO_FCC_CR_5T        0x75 // BK5_5F
#define INIT_SVIDEO_FCC_CB_6T        0xB0 // BK5_60
#define INIT_SVIDEO_FCC_CR_6T        0x48 // BK5_61
#define INIT_SVIDEO_FCC_CB_7T        0x64 // BK5_62
#define INIT_SVIDEO_FCC_CR_7T        0xC8 // BK5_63
#define INIT_SVIDEO_FCC_CB_8T        0x80 // BK5_64
#define INIT_SVIDEO_FCC_CR_8T        0x80 // BK5_65
#define INIT_SVIDEO_WHITE_STOP       0x88 // BK5_66
#define INIT_SVIDEO_BLACK_STOP       0x98 // BK5_67
#define INIT_SVIDEO_FCC_WIN1         0xB2 // BK5_68
#define INIT_SVIDEO_FCC_WIN2         0xBA // BK5_69
#define INIT_SVIDEO_FCC_WIN3         0xFB // BK5_6A
#define INIT_SVIDEO_FCC_WIN4         0x73 // BK5_6B
#define INIT_SVIDEO_FCC_WIN5         0xFB // BK5_6C
#define INIT_SVIDEO_FCC_WIN6         0xFB // BK5_6D
#define INIT_SVIDEO_FCC_WIN7         0xFF // BK5_6E
#define INIT_SVIDEO_FCC_WIN8         0x6A // BK5_6F
#define INIT_SVIDEO_FCC_WIN9         0x00 // BK5_70
#define INIT_SVIDEO_FCC_Y_TH         0xFF // BK5_71
#define INIT_SVIDEO_FCC_K1K2         0x60 // BK5_72
#define INIT_SVIDEO_FCC_K3K4         0x88 // BK5_73
#define INIT_SVIDEO_FCC_K5K6         0xC8 // BK5_74
#define INIT_SVIDEO_FCC_K7K8         0x85 // BK5_75
#define INIT_SVIDEO_FCC_CTRL         0x48 // BK5_76
#define INIT_SVIDEO_APP_CTRL         0x76 // BK5_77
#define INIT_SVIDEO_PEAK_BAND1       0x20 // BK5_78
#define INIT_SVIDEO_PEAK_BAND2       0x60 // BK5_79
#define INIT_SVIDEO_LTI              0xB0 // BK5_7A
#define INIT_SVIDEO_TERM_SEL         0xE4 // BK5_7B
#define INIT_SVIDEO_CORING           0x32 // BK5_7C
#define INIT_SVIDEO_CTI              0x58 // BK5_7D
#define INIT_SVIDEO_VIP_Y_CTRL       0x01 // BK5_7E
#define INIT_SVIDEO_WHITE_START      0xA0 // BK5_7F
#define INIT_SVIDEO_BLACK_START      0x40 // BK5_80

#define INIT_SVIDEO_EGE_BAND1_POS    0x10 // BK5_81
#define INIT_SVIDEO_EGE_BAND1_NEG    0x10 // BK5_82
#define INIT_SVIDEO_EGE_BAND2_POS    0x00 // BK5_83
#define INIT_SVIDEO_EGE_BAND2_NEG    0x00 // BK5_84

#define INIT_SVIDEO_Y_BRI            0x06 // BK5_85

#define INIT_SVIDEO_EGE_LTI_POS      0x00 // BK5_86
#define INIT_SVIDEO_EGE_LTI_NEG      0x00 // BK5_87
#define INIT_SVIDEO_YC_LPF           0xFC // BK5_88

#define INIT_SVIDEO_Y_CORING_CTRL    0x23 // BK5_8A
#define INIT_SVIDEO_C_CORING_CTRL    0x36 // BK5_8B
#define INIT_SVIDEO_CORING_TBL1      0xDF // BK5_8C
#define INIT_SVIDEO_CORING_TBL2      0x9B // BK5_8D
#define INIT_SVIDEO_CORING_TBL3      0x36 // BK5_8E
#define INIT_SVIDEO_CORING_TBL4      0x01 // BK5_8F

#define INIT_SVIDEO_MAIN_HIS_HST     0x00 // BK5_90
#define INIT_SVIDEO_MAIN_HIS_HED     0x00 // BK5_91
#define INIT_SVIDEO_MAIN_HIS_VST     0x00 // BK5_92
#define INIT_SVIDEO_MAIN_HIS_VED     0x00 // BK5_93
#define INIT_SVIDEO_MAIN_WIN_MN_PX   0x00 // BK5_94
#define INIT_SVIDEO_MAIN_WIN_MX_PX   0xD7 // BK5_95
#define INIT_SVIDEO_HIS_WEIGHT_L     0x00 // BK5_96
#define INIT_SVIDEO_HIS_WEIGHT_H     0x25 // BK5_97
#define INIT_SVIDEO_HIS_HANDSHAKE    0xCE // BK5_98
#define INIT_SVIDEO_HIS_CF_ADDR      0x11 // BK5_99
#define INIT_SVIDEO_HIS_CF_DATA      0x07 // BK5_9A
#define INIT_SVIDEO_DLC_INC_CTRL     0x00 // BK5_9B

#define INIT_SVIDEO_VPK_CTRL         0x8B // BK5_A0
#define INIT_SVIDEO_VPK_STEP1        0x11 // BK5_A1
#define INIT_SVIDEO_VPK_STEP2        0x21 // BK5_A2
#define INIT_SVIDEO_VPK_VER_TH       0x04 // BK5_A3
#define INIT_SVIDEO_VPK_HOR_TH       0x04 // BK5_A4
#define INIT_SVIDEO_VPK_DIA_TH       0x04 // BK5_A5
#define INIT_SVIDEO_VPK_CORING       0x10 // BK5_A6
#define INIT_SVIDEO_VPK_OVERSHOOT    0xFF // BK5_A7
#define INIT_SVIDEO_VPK_UNDERSHOOT   0xFF // BK5_A8
#define INIT_SVIDEO_VPK_USER_ADJ     0x0C // BK5_A9
#define INIT_SVIDEO_VPK_VER_LUT_ADDR 0x00 // BK5_AA
#define INIT_SVIDEO_VPK_VER_LUT_DATA 0x3F // BK5_AB
#define INIT_SVIDEO_VPK_HOR_LUT_ADDR 0x00 // BK5_AC
#define INIT_SVIDEO_VPK_HOR_LUT_DATA 0x3F // BK5_AD
#define INIT_SVIDEO_VPK_DIA_LUT_ADDR 0x00 // BK5_AE
#define INIT_SVIDEO_VPK_DIA_LUT_DATA 0x3F // BK5_AF

#define INIT_SVIDEO_SNR_CTRL         0x17 // BK5_B0
#define INIT_SVIDEO_GAUSS_THRD       0x08 // BK5_B1
#define INIT_SVIDEO_FLESH_SLPE       0x08 // BK5_B2
#define INIT_SVIDEO_FLESH_CB_U       0x7D // BK5_B3
#define INIT_SVIDEO_FLESH_CR_U       0x9B // BK5_B4
#define INIT_SVIDEO_FLESH_CB_D       0x69 // BK5_B5
#define INIT_SVIDEO_FLESH_CR_D       0x87 // BK5_B6
#define INIT_SVIDEO_GREEN_SLPE       0x08 // BK5_B7
#define INIT_SVIDEO_GREEN_CB_U       0x7A // BK5_B8
#define INIT_SVIDEO_GREEN_CR_U       0x85 // BK5_B9
#define INIT_SVIDEO_GREEN_CB_D       0x3A // BK5_BA
#define INIT_SVIDEO_GREEN_CR_D       0x55 // BK5_BB

#define INIT_SVIDEO_SNR_TABLE_0      0x95 // BK5_C0
#define INIT_SVIDEO_SNR_TABLE_1      0x72 // BK5_C1
#define INIT_SVIDEO_SNR_TABLE_2      0x43 // BK5_C2
#define INIT_SVIDEO_SNR_TABLE_3      0x32 // BK5_C3
#define INIT_SVIDEO_SNR_TABLE_4      0x11 // BK5_C4
#define INIT_SVIDEO_SNR_TABLE_5      0x01 // BK5_C5
#define INIT_SVIDEO_SNR_TABLE_6      0x00 // BK5_C6
#define INIT_SVIDEO_SNR_TABLE_7      0x00 // BK5_C7

// For YPbPr input
#define INIT_YPBPR_MWE_CTRL         INIT_VIDEO_MWE_CTRL // BK5_10
#define INIT_YPBPR_MWE_H_START_L    INIT_VIDEO_MWE_H_START_L // BK5_11
#define INIT_YPBPR_MWE_H_START_H    INIT_VIDEO_MWE_H_START_H // BK5_12
#define INIT_YPBPR_MWE_H_END_L        INIT_VIDEO_MWE_H_END_L // BK5_13
#define INIT_YPBPR_MWE_H_END_H        INIT_VIDEO_MWE_H_END_H // BK5_14
#define INIT_YPBPR_MWE_V_START_L    INIT_VIDEO_MWE_V_START_L // BK5_15
#define INIT_YPBPR_MWE_V_START_H    INIT_VIDEO_MWE_V_START_H // BK5_16
#define INIT_YPBPR_MWE_V_END_L        INIT_VIDEO_MWE_V_END_L // BK5_17
#define INIT_YPBPR_MWE_V_END_H        INIT_VIDEO_MWE_V_END_H // BK5_18
#define INIT_YPBPR_MWE_Y_CTRL        INIT_VIDEO_MWE_Y_CTRL // BK5_19
#define INIT_YPBPR_MWE_FCC_CTRL     INIT_VIDEO_MWE_FCC_CTRL // BK5_1A
#define INIT_YPBPR_MWE_Y_CORE_CTRL    INIT_VIDEO_MWE_Y_CORE_CTRL // BK5_1B
#define INIT_YPBPR_MWE_C_CORE_CTRL    INIT_VIDEO_MWE_C_CORE_CTRL // BK5_1C
#define INIT_YPBPR_MWE_BRI            INIT_VIDEO_MWE_BRI // BK5_1F

#define INIT_YPBPR_ICE_CTRL         INIT_VIDEO_ICE_CTRL // BK5_30
#define INIT_YPBPR_ICE_DFRGE_R        INIT_VIDEO_ICE_DFRGE_R // BK5_31
#define INIT_YPBPR_ICE_DFRGE_G        INIT_VIDEO_ICE_DFRGE_G // BK5_32
#define INIT_YPBPR_ICE_DFRGE_B        INIT_VIDEO_ICE_DFRGE_B // BK5_33
#define INIT_YPBPR_ICE_ACTRGE_R     INIT_VIDEO_ICE_ACTRGE_R // BK5_34
#define INIT_YPBPR_ICE_ACTRGE_G     INIT_VIDEO_ICE_ACTRGE_G // BK5_35
#define INIT_YPBPR_ICE_ACTRGE_B     INIT_VIDEO_ICE_ACTRGE_B // BK5_36
#define INIT_YPBPR_ICE_ACTRGE_C     INIT_VIDEO_ICE_ACTRGE_C // BK5_37
#define INIT_YPBPR_ICE_ACTRGE_M     INIT_VIDEO_ICE_ACTRGE_M // BK5_38
#define INIT_YPBPR_ICE_ACTRGE_Y     INIT_VIDEO_ICE_ACTRGE_Y // BK5_39

#define INIT_YPBPR_ICE_SAT_R        0x00// BK5_3A
#define INIT_YPBPR_ICE_SAT_G        0x00// BK5_3B
#define INIT_YPBPR_ICE_SAT_B        0x08// BK5_3C
#define INIT_YPBPR_ICE_SAT_C        0x04// BK5_3D
#define INIT_YPBPR_ICE_SAT_M        0x00// BK5_3E
#define INIT_YPBPR_ICE_SAT_Y        0x00// BK5_3F
#define INIT_YPBPR_ICE_HUE_R        0x44// BK5_40
#define INIT_YPBPR_ICE_HUE_G        0x60// BK5_41
#define INIT_YPBPR_ICE_HUE_B        0x00// BK5_42
#define INIT_YPBPR_ICE_HUE_C        0x10// BK5_43
#define INIT_YPBPR_ICE_HUE_M        0x00// BK5_44
#define INIT_YPBPR_ICE_HUE_Y        0x00// BK5_45
#define INIT_YPBPR_ICE_BRI_R        0x10// BK5_46
#define INIT_YPBPR_ICE_BRI_G        0x04// BK5_47
#define INIT_YPBPR_ICE_BRI_B        0x00// BK5_48
#define INIT_YPBPR_ICE_BRI_C        0x04// BK5_49
#define INIT_YPBPR_ICE_BRI_M        0x04// BK5_4A
#define INIT_YPBPR_ICE_BRI_Y        0x04// BK5_4B
#define INIT_YPBPR_WT_TH_L            INIT_VIDEO_WT_TH_L // BK5_4C
#define INIT_YPBPR_WT_TH_H            INIT_VIDEO_WT_TH_H // BK5_4D

#define INIT_YPBPR_FCC_CB_1T        INIT_VIDEO_FCC_CB_1T // BK5_56
#define INIT_YPBPR_FCC_CR_1T        INIT_VIDEO_FCC_CR_1T // BK5_57
#define INIT_YPBPR_FCC_CB_2T        INIT_VIDEO_FCC_CB_2T // BK5_58
#define INIT_YPBPR_FCC_CR_2T        INIT_VIDEO_FCC_CR_2T // BK5_59
#define INIT_YPBPR_FCC_CB_3T        INIT_VIDEO_FCC_CB_3T // BK5_5A
#define INIT_YPBPR_FCC_CR_3T        INIT_VIDEO_FCC_CR_3T // BK5_5B
#define INIT_YPBPR_FCC_CB_4T        INIT_VIDEO_FCC_CB_4T // BK5_5C
#define INIT_YPBPR_FCC_CR_4T        INIT_VIDEO_FCC_CR_4T // BK5_5D
#define INIT_YPBPR_FCC_CB_5T        INIT_VIDEO_FCC_CB_5T // BK5_5E
#define INIT_YPBPR_FCC_CR_5T        INIT_VIDEO_FCC_CR_5T // BK5_5F
#define INIT_YPBPR_FCC_CB_6T        INIT_VIDEO_FCC_CB_6T // BK5_60
#define INIT_YPBPR_FCC_CR_6T        INIT_VIDEO_FCC_CR_6T // BK5_61
#define INIT_YPBPR_FCC_CB_7T        INIT_VIDEO_FCC_CB_7T // BK5_62
#define INIT_YPBPR_FCC_CR_7T        INIT_VIDEO_FCC_CR_7T // BK5_63
#define INIT_YPBPR_FCC_CB_8T        INIT_VIDEO_FCC_CB_8T // BK5_64
#define INIT_YPBPR_FCC_CR_8T        INIT_VIDEO_FCC_CR_8T // BK5_65
#define INIT_YPBPR_WHITE_STOP        INIT_VIDEO_WHITE_STOP // BK5_66
#define INIT_YPBPR_BLACK_STOP        0x84//INIT_VIDEO_BLACK_STOP // BK5_67

#define INIT_YPBPR_FCC_WIN1         INIT_VIDEO_FCC_WIN1 // BK5_68
#define INIT_YPBPR_FCC_WIN2         INIT_VIDEO_FCC_WIN2 // BK5_69
#define INIT_YPBPR_FCC_WIN3         INIT_VIDEO_FCC_WIN3 // BK5_6A
#define INIT_YPBPR_FCC_WIN4         INIT_VIDEO_FCC_WIN4 // BK5_6B
#define INIT_YPBPR_FCC_WIN5         INIT_VIDEO_FCC_WIN5 // BK5_6C
#define INIT_YPBPR_FCC_WIN6         INIT_VIDEO_FCC_WIN6 // BK5_6D
#define INIT_YPBPR_FCC_WIN7         INIT_VIDEO_FCC_WIN7 // BK5_6E
#define INIT_YPBPR_FCC_WIN8         INIT_VIDEO_FCC_WIN8 // BK5_6F
#define INIT_YPBPR_FCC_WIN9         INIT_VIDEO_FCC_WIN9 // BK5_70
#define INIT_YPBPR_FCC_Y_TH         INIT_VIDEO_FCC_Y_TH // BK5_71
#define INIT_YPBPR_FCC_K1K2         0x20//INIT_VIDEO_FCC_K1K2 // BK5_72
#define INIT_YPBPR_FCC_K3K4         INIT_VIDEO_FCC_K3K4 // BK5_73
#define INIT_YPBPR_FCC_K5K6         INIT_VIDEO_FCC_K5K6 // BK5_74
#define INIT_YPBPR_FCC_K7K8         INIT_VIDEO_FCC_K7K8 // BK5_75
#define INIT_YPBPR_FCC_CTRL         0x49//INIT_VIDEO_FCC_CTRL // BK5_76
#define INIT_YPBPR_APP_CTRL         0x7C// INIT_VIDEO_APP_CTRL // BK5_77

#define INIT_YPBPR_PEAK_BAND1        0x20 //INIT_VIDEO_PEAK_BAND1 // BK5_78
#define INIT_YPBPR_PEAK_BAND2        0x60 //INIT_VIDEO_PEAK_BAND2 // BK5_79
#define INIT_YPBPR_LTI                0xB0//INIT_VIDEO_LTI // BK5_7A
#define INIT_YPBPR_TERM_SEL         0xE4//INIT_VIDEO_TERM_SEL // BK5_7B
#define INIT_YPBPR_CORING            0x32//INIT_VIDEO_CORING // BK5_7C
#define INIT_YPBPR_CTI                0xDC//INIT_VIDEO_CTI // BK5_7D
#define INIT_YPBPR_VIP_Y_CTRL        0x01//INIT_VIDEO_VIP_Y_CTRL // BK5_7E
#define INIT_YPBPR_WHITE_START        0x80//INIT_VIDEO_WHITE_START // BK5_7F
#define INIT_YPBPR_BLACK_START        0x40//INIT_VIDEO_BLACK_START // BK5_80
#define INIT_YPBPR_EGE_BAND1_POS    0x70 // INIT_VIDEO_EGE_BAND1_POS // BK5_81
#define INIT_YPBPR_EGE_BAND1_NEG    0x20//INIT_VIDEO_EGE_BAND1_NEG // BK5_82
#define INIT_YPBPR_EGE_BAND2_POS    0x70//INIT_VIDEO_EGE_BAND2_POS // BK5_83
#define INIT_YPBPR_EGE_BAND2_NEG    0x40//INIT_VIDEO_EGE_BAND2_NEG // BK5_84
#define INIT_YPBPR_Y_BRI            0x06//INIT_VIDEO_Y_BRI // BK5_85
#define INIT_YPBPR_EGE_LTI_POS        0x02//INIT_VIDEO_EGE_LTI_POS // BK5_86
#define INIT_YPBPR_EGE_LTI_NEG        0x02//INIT_VIDEO_EGE_LTI_NEG // BK5_87
#define INIT_YPBPR_YC_LPF            0xFC//INIT_VIDEO_YC_LPF // BK5_88
#define INIT_YPBPR_Y_CORING_CTRL    0x27//INIT_VIDEO_Y_CORING_CTRL // BK5_8A
#define INIT_YPBPR_C_CORING_CTRL    0x36//INIT_VIDEO_C_CORING_CTRL // BK5_8B
#define INIT_YPBPR_CORING_TBL1        INIT_VIDEO_CORING_TBL1 // BK5_8C
#define INIT_YPBPR_CORING_TBL2        INIT_VIDEO_CORING_TBL2 // BK5_8D
#define INIT_YPBPR_CORING_TBL3        INIT_VIDEO_CORING_TBL3 // BK5_8E
#define INIT_YPBPR_CORING_TBL4        INIT_VIDEO_CORING_TBL4 // BK5_8F

#define INIT_YPBPR_MAIN_HIS_HST     INIT_VIDEO_MAIN_HIS_HST // BK5_90
#define INIT_YPBPR_MAIN_HIS_HED     INIT_VIDEO_MAIN_HIS_HED // BK5_91
#define INIT_YPBPR_MAIN_HIS_VST     INIT_VIDEO_MAIN_HIS_VST // BK5_92
#define INIT_YPBPR_MAIN_HIS_VED     INIT_VIDEO_MAIN_HIS_VED // BK5_93
#define INIT_YPBPR_MAIN_WIN_MN_PX    INIT_VIDEO_MAIN_WIN_MN_PX // BK5_94
#define INIT_YPBPR_MAIN_WIN_MX_PX    INIT_VIDEO_MAIN_WIN_MX_PX // BK5_95
#define INIT_YPBPR_HIS_WEIGHT_L     INIT_VIDEO_HIS_WEIGHT_L // BK5_96
#define INIT_YPBPR_HIS_WEIGHT_H     INIT_VIDEO_HIS_WEIGHT_H // BK5_97
#define INIT_YPBPR_HIS_HANDSHAKE    INIT_VIDEO_HIS_HANDSHAKE // BK5_98
#define INIT_YPBPR_HIS_CF_ADDR        INIT_VIDEO_HIS_CF_ADDR // BK5_99
#define INIT_YPBPR_HIS_CF_DATA        INIT_VIDEO_HIS_CF_DATA // BK5_9A
#define INIT_YPBPR_DLC_INC_CTRL     INIT_VIDEO_DLC_INC_CTRL // BK5_9B

#define INIT_YPBPR_VPK_CTRL         0x8B//INIT_VIDEO_VPK_CTRL // BK5_A0
#define INIT_YPBPR_VPK_STEP1        INIT_VIDEO_VPK_STEP1 // BK5_A1
#define INIT_YPBPR_VPK_STEP2        INIT_VIDEO_VPK_STEP2 // BK5_A2
#define INIT_YPBPR_VPK_VER_TH        INIT_VIDEO_VPK_VER_TH // BK5_A3
#define INIT_YPBPR_VPK_HOR_TH        INIT_VIDEO_VPK_HOR_TH // BK5_A4
#define INIT_YPBPR_VPK_DIA_TH        INIT_VIDEO_VPK_DIA_TH // BK5_A5
#define INIT_YPBPR_VPK_CORING        0x21//INIT_VIDEO_VPK_CORING // BK5_A6
#define INIT_YPBPR_VPK_OVERSHOOT    INIT_VIDEO_VPK_OVERSHOOT    // BK5_A7
#define INIT_YPBPR_VPK_UNDERSHOOT    INIT_VIDEO_VPK_UNDERSHOOT    // BK5_A8
#define INIT_YPBPR_VPK_USER_ADJ     0X04//INIT_VIDEO_VPK_USER_ADJ        // BK5_A9
#define INIT_YPBPR_VPK_VER_LUT_ADDR INIT_VIDEO_VPK_VER_LUT_ADDR // BK5_AA
#define INIT_YPBPR_VPK_VER_LUT_DATA INIT_VIDEO_VPK_VER_LUT_DATA // BK5_AB
#define INIT_YPBPR_VPK_HOR_LUT_ADDR INIT_VIDEO_VPK_HOR_LUT_ADDR // BK5_AC
#define INIT_YPBPR_VPK_HOR_LUT_DATA INIT_VIDEO_VPK_HOR_LUT_DATA // BK5_AD
#define INIT_YPBPR_VPK_DIA_LUT_ADDR INIT_VIDEO_VPK_DIA_LUT_ADDR // BK5_AE
#define INIT_YPBPR_VPK_DIA_LUT_DATA INIT_VIDEO_VPK_DIA_LUT_DATA // BK5_AF


#define INIT_YPBPR_SNR_CTRL         0x17//INIT_VIDEO_SNR_CTRL    // BK5_B0
#define INIT_YPBPR_GAUSS_THRD       0x08//INIT_VIDEO_GAUSS_THRD    // BK5_B1
#define INIT_YPBPR_FLESH_SLPE       INIT_VIDEO_FLESH_SLPE    // BK5_B2
#define INIT_YPBPR_FLESH_CB_U       INIT_VIDEO_FLESH_CB_U    // BK5_B3
#define INIT_YPBPR_FLESH_CR_U       INIT_VIDEO_FLESH_CR_U    // BK5_B4
#define INIT_YPBPR_FLESH_CB_D       INIT_VIDEO_FLESH_CB_D    // BK5_B5
#define INIT_YPBPR_FLESH_CR_D       INIT_VIDEO_FLESH_CR_D    // BK5_B6
#define INIT_YPBPR_GREEN_SLPE       INIT_VIDEO_GREEN_SLPE    // BK5_B7
#define INIT_YPBPR_GREEN_CB_U       INIT_VIDEO_GREEN_CB_U    // BK5_B8
#define INIT_YPBPR_GREEN_CR_U       INIT_VIDEO_GREEN_CR_U    // BK5_B9
#define INIT_YPBPR_GREEN_CB_D       INIT_VIDEO_GREEN_CB_D    // BK5_BA
#define INIT_YPBPR_GREEN_CR_D       INIT_VIDEO_GREEN_CR_D    // BK5_BB

#define INIT_YPBPR_SNR_TABLE_0      0xD5//INIT_VIDEO_SNR_TABLE_0    // BK5_C0
#define INIT_YPBPR_SNR_TABLE_1      0xB2//INIT_VIDEO_SNR_TABLE_1    // BK5_C1
#define INIT_YPBPR_SNR_TABLE_2      0x63//INIT_VIDEO_SNR_TABLE_2    // BK5_C2
#define INIT_YPBPR_SNR_TABLE_3      0x24//INIT_VIDEO_SNR_TABLE_3    // BK5_C3
#define INIT_YPBPR_SNR_TABLE_4      0x11//INIT_VIDEO_SNR_TABLE_4    // BK5_C4
#define INIT_YPBPR_SNR_TABLE_5      0x01//INIT_VIDEO_SNR_TABLE_5    // BK5_C5
#define INIT_YPBPR_SNR_TABLE_6      INIT_VIDEO_SNR_TABLE_6    // BK5_C6
#define INIT_YPBPR_SNR_TABLE_7      INIT_VIDEO_SNR_TABLE_7    // BK5_C7

/////////////////////////////////////////////////////////////////////
// Color temp RGB
/////////////////////////////////////////////////////////////////////

#define INIT_PC_COLOR_TEMP_NORMAL_R        0x70
#define INIT_PC_COLOR_TEMP_NORMAL_G        0x6E
#define INIT_PC_COLOR_TEMP_NORMAL_B        0x80

#define INIT_PC_COLOR_TEMP_WARM_R        0x7A
#define INIT_PC_COLOR_TEMP_WARM_G        0x76
#define INIT_PC_COLOR_TEMP_WARM_B        0x78

#define INIT_PC_COLOR_TEMP_COOL_R        0x6E
#define INIT_PC_COLOR_TEMP_COOL_G        0x68
#define INIT_PC_COLOR_TEMP_COOL_B        0x80

#define INIT_PC_COLOR_TEMP_SRGB_R        0x80
#define INIT_PC_COLOR_TEMP_SRGB_G        0x80
#define INIT_PC_COLOR_TEMP_SRGB_B        0x80


#define INIT_VIDEO_COLOR_TEMP_COOL_R    0x80
#define INIT_VIDEO_COLOR_TEMP_COOL_G    0x80
#define INIT_VIDEO_COLOR_TEMP_COOL_B    0x80

#define INIT_VIDEO_COLOR_TEMP_NORMAL_R    0x75
#define INIT_VIDEO_COLOR_TEMP_NORMAL_G    0x74
#define INIT_VIDEO_COLOR_TEMP_NORMAL_B    0x80

#define INIT_VIDEO_COLOR_TEMP_WARM_R    0x79
#define INIT_VIDEO_COLOR_TEMP_WARM_G    0x76
#define INIT_VIDEO_COLOR_TEMP_WARM_B    0x78

#define INIT_VIDEO_COLOR_TEMP_USER_R    0x80
#define INIT_VIDEO_COLOR_TEMP_USER_G    0x80
#define INIT_VIDEO_COLOR_TEMP_USER_B    0x80

#if ENABLE_PRECISE_RGBBRIGHTNESS
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B      (0x80<<3)

#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R    (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G    (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B    (0x80<<3)

#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B      (0x80<<3)

#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_R      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_G      (0x80<<3)
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_B      (0x80<<3)
#else
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B    0x80

#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B    0x80

#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B    0x80

#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_R    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_G    0x80
#define INIT_VIDEO_COLOR_BRIGHTNESS_USER_B    0x80
#endif

///////////////////////////////////////////////////////////////////////
// Init ADC for YPbPr
///////////////////////////////////////////////////////////////////////
#define INIT_ADC_YPBPR_RED_OFFSET       ~0x80
#define INIT_ADC_YPBPR_GREEN_OFFSET     ~0x80
#define INIT_ADC_YPBPR_BLUE_OFFSET      ~0x80
#define INIT_ADC_YPBPR_RED_GAIN         ~0x7E
#define INIT_ADC_YPBPR_GREEN_GAIN       ~0xC5
#define INIT_ADC_YPBPR_BLUE_GAIN        ~0x76

//#define PANEL_DIMMING_CTL                0x80
#define PANEL_DIMMING_CTL                0x3f
#define PANEL_MAX_PWM_DIM                0xE6
#define PANEL_MIN_PWM_DIM                0x20

INTERFACE code MS_REG_TYPE astVIDEO_ACE_Setting[];
INTERFACE code MS_REG_TYPE astTV_ACE_Setting[];
INTERFACE code MS_REG_TYPE astYPBPR_ACE_Setting[];
INTERFACE code MS_REG_TYPE astDTV_ACE_Setting[];
INTERFACE code MS_REG_TYPE astHDTV_ACE_Setting[];
INTERFACE code MS_REG_TYPE astSDTV_ACE_Setting[] ;

#undef INTERFACE
#endif // __DAC_CRT_H

