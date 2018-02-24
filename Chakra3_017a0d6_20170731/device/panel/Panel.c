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
#ifndef _PANEL_C_
#define _PANEL_C_

#include "Board.h"
#include "drvGlobal.h"
#include "msAPI_Timer.h"

#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "apiPNL.h"
#include "Panel.h"
#include "drvPWM.h"
#include "msAPI_Mode.h"
#include "MApp_GlobalSettingSt.h"
#include "drvGPIO.h"
#include "datatype.h"
#include "MApp_XC_PQ.h"
#include "drvIIC.h"

#include "Utl.h"


#if ENABLE_TCON
// include TCON table.
#include "pnl_tcon_tbl.h"
#include "MApp_GlobalVar.h"
#endif

#include "SW_Config.h"
#if(ENABLE_MFC_6M30)
#include "drvUrsa6M30.h"
#elif (ENABLE_MFC_6M20)  //
#include "drvUrsaMFCAPI.h"
#elif(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif
#include "MApp_Scaler.h"

#if ENABLE_PANEL_BIN
#include "BinInfo.h"
#include "SysInit.h"
#include "msAPI_BDMA.h"
#include "msAPI_APEngine.h"
#include "MApp_RestoreToDefault.h"
#endif

#if ENABLE_TCON_2014
#include "msAPI_TCON.h"
#endif
#define DBG_PANEL(x)                        //x
#define USE_PANEL_DEFINE                    1
#define PANEL_DUMMY                         0

#define PANEL_ON_SEQ(x)         //x

/***************************************************************************************/

PANEL_RESOLUTION_TYPE g_PNL_TypeSel             =   PANEL_DEFAULT_TYPE_SEL;

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA) && ENABLE_3D_PROCESS )
  #if ( (DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_IDX_IN8903_Simple_)     \
      ||(DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_IDX_IN8903_PQ_Optimize_))
    PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K2K        =   PNL_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division;
    PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K1K        =   PNL_RES_MAX_NUM;
    PANEL_RESOLUTION_TYPE g_PNL_TypeSel_FHD         =   PNL_INX_V500DK2_KS1_IN8903_Vx1_FHD_60HZ_1Division;
  #else //if(DEFAULT_3D_BEHAVIOR_SEL == _EN_3D_BEHAVIOR_IDX_All_Passive_)
    PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K2K        =   PANEL_DEFAULT_TYPE_SEL;
    PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K1K        =   PNL_RES_MAX_NUM;
    PANEL_RESOLUTION_TYPE g_PNL_TypeSel_FHD         =   PANEL_DEFAULT_TYPE_SEL;
  #endif
#else
  PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K2K        =   PANEL_DEFAULT_TYPE_SEL;
  PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K1K        =   PNL_RES_MAX_NUM;
  PANEL_RESOLUTION_TYPE g_PNL_TypeSel_FHD         =   PANEL_DEFAULT_TYPE_SEL;
#endif


MS_U8 g_u8TransientBacklight = 0;


static U32 g_PNL_u32PanelVcc_TurnOn_Time = 0;
static U32 g_PNL_u32LvdsSignal_TurnOn_Time = 0;
static U32 g_PNL_u32Backlight_TurnOn_Time = 0;


/***************************************************************************************/
/********** Panel Table **********/
/***************************************************************************************/

ST_PANEL_NEW_PANELTYPE stPanel_FULLHD_SEC32_LE32A =
{
    {
        "SEC_LE32A",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,            //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;          //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //0x0010,       //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,   //0x87,     //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,    //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;          //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPanel_SXGA_AU17_EN05 =
{
   {
        "SXGA_AU17_EN05",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        1,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;        //PANEL_EVEN_DATA_CURRENT    // even data current

        10,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        250,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        100,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        24,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        38,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+24,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH-1)
        2+38,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1024,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1800,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1688,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1664,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2047,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1066,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL
        1035,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        140,        //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        108,        //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        100,        //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,        //m_ucDimmingCtl
        0xFF,        //m_ucMaxPWMVal;
        0x50,         //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_4_3,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x277F44,
       0x1C3655,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    140,        //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    108,        //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    100,        //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};//


ST_PANEL_NEW_PANELTYPE stPanel_WXGA_AU20_T200XW02 =
{
    {
        "WXGA_AU20_T200XW02",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        34,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        4+34,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,//1430,  //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        806ul,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        789,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x20ea0e,
       0x167109,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPanel_WXGA_AU20_T200XW02_LGD=
{
    {
        "WXGA_AU20_T200XW02_LGD",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,  // LGD                  // shall swap if

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1^PANEL_SWAP_LVDS_POL,  // LGD

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        34,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        4+34,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,//1430,  //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        806ul,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        789,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x20ea0e,
       0x167109,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPanel_WXGAP_CMO_M190A1=
{
    {

        "WXGAP_CMO_M190A1",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,            //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        150,            //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        104,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        24,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        3,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        6,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        104+24,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        3+6,            //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1440,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        900,            //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1920,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1760,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1520,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1050,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        950,            //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        910,            //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        112,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        100,     //DWORD m_dwPanelDCLK;          //PANEL_DCLK
        80,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0000,//0x0010,        //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x0000,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x68,       //m_ucDimmingCtl
        0xDD,                //m_ucMaxPWMVal;
        0x20,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x315F15,
       0x2343EB,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    112,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    100,     //DWORD m_dwPanelDCLK;          //PANEL_DCLK
    80,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPanel_WSXGA_AU22_M201EW01=
{
    {
        "WSXGA_AU22_M201EW01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        8,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        16+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        2+8,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1680,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1050,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2000,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1840,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1780,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1195,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1080,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1060,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (150),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (119),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (110),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x23E80F,
       0x1A54D8,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (150),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (119),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (110),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPanel_FullHD_CMO216_H1L01=
{
    {
        "FullHD_CMO216_H1L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
#if ((MS_BOARD_TYPE_SEL == BD_MST074B_10AGS))
        320,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
#else
        300,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
#endif
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

    #if(CHAKRA3_AUTO_TEST)
        // For auto test PC
        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,        //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        36,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+36,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
    #else
        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
    #endif

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
    #if(CHAKRA3_AUTO_TEST)
        // For auto test PC
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL
    #else
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
    #endif
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

    #if(CHAKRA3_AUTO_TEST)
        // For auto test PC
        (159),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (139),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    #else
        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    #endif

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x20EA0E,    // MS_U32 m_dwPanelMaxSET;  ///<  define PANEL_MAX_SET
       0x181568,    // MS_U32 m_dwPanelMinSET;    ///<  define PANEL_MIN_SET

    #if(CHAKRA3_AUTO_TEST)
        // For auto test PC
        E_PNL_CHG_DCLK, // APIPNL_OUT_TIMING_MODE m_ucOutTimingMode;   ///<Define which panel output timing change mode is used to change VFreq for same panel
    #else
        E_PNL_CHG_VTOTAL, // APIPNL_OUT_TIMING_MODE m_ucOutTimingMode;   ///<Define which panel output timing change mode is used to change VFreq for same panel
    #endif
        1,///<  PAFRC mixed with noise dither disable
    },

    #if(CHAKRA3_AUTO_TEST)
        // For auto test PC
        (159),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (139),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    #else
        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    #endif
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPanel_WUXGA_CMO_260J2=
{
    {
        "CMO260J2_WUXGA",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT
        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        600,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        300,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        26,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        6+26,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1200,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2159,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2141,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2060,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1245,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1235,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1209,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (170),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (158),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        100,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x015E,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x7D,       //m_ucDimmingCtl

        0xFF,        //m_ucMaxPWMVal;
        0x00,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x173BCE,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (170),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (158),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

#if(ENABLE_SUPPORT_PNL_LC320DXJ)
ST_PANEL_NEW_PANELTYPE stPanel_LC320DXJ=
{
    {
        "LC320DXJ",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        34,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        4+34,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1776ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1528ul,//1430,  //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1456ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1008,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        790ul,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        788,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x20ea0e,
       0x167109,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care

};
#endif

ST_PANEL_NEW_PANELTYPE stPanelFullHD_1080P30=
{
    {
        "FullHD_1080P30",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
    	 1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (82),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (75),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (60),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
	TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit m_ucOutputFormatBitMode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x20EA0E,
       0x150000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (82),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (75),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (60),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

#if(ENABLE_TTL_PANEL)
ST_PANEL_NEW_PANELTYPE stPNL_TTL_480P=
#if 0 //gchen @ 20171208
{
    { // 480P
        "TTL_480P60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,  // 1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        60,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        100,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        50,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        50,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        62,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        32,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        30,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        122,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        36,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        908,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        858,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        838,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        545,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        525,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        500,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (38),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        ((((DWORD)858*525*60)/1000000)),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK        (15),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_4_3,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_HTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (38),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    ((((DWORD)858*525*60)/1000000)),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (15),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};
#else
{
    { // 480P
        "WVGA_854x480_JABIL_TTL",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        1,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current

        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        80,//5,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH //gchen @ 20170727 timing
        24,//28,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH //gchen @ 20170727 timing

        10,//6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH  //gchen @ 20170727 timing
        3,//14,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH //gchen @ 20170727 timing

        80+24,//5+28,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        10+3,//6+14,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        854,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1044,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1044,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1044,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        500,//550,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        500,//526,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        500,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (32),//(34),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK //gchen @ 20170727 timing
        (32),//(33),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK //gchen @ 20170727 timing
        (32),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (32),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (32),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (32),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};
#endif

ST_PANEL_NEW_PANELTYPE stPNL_TTL_720P=
{
    {
        "TTL_720P60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,  // 1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        100,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        20,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        20,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        32,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        20,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        260,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        25,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,      //WORD m_wPanelWidth;               //PANEL_WIDTH
        720,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1650,      //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1650,      //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1650,      //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        750,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        750,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        750,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (82),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        ((((DWORD)1650*750*60)/1000000)),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (50),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_4_3,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_HTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (82),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    ((((DWORD)1650*750*60)/1000000)),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (50),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stPNL_TTL_1080P=
{
    {
        "TTL_1080P60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,  // 1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,      //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,      //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,      //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,      //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,        //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        100,       //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        20,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        20,        //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,        //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        104,       //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,         //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        28,        //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        148,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        36,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,      //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,      //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2300,      //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,      //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2100,      //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1139,      //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125,      //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (160),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        148.5,     //((((DWORD)2200*1125*60)/1000000)),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_4_3,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_HTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (160),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    148.5,     //((((DWORD)2200*1125*60)/1000000)),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};
#endif

#if( ENABLE_DAC_OUT )

ST_PANEL_NEW_PANELTYPE stDACOUT480I_60=
{
    {//Dac Out for U3 bringup
        "DACOUT_480I_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        124,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        114,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        3,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        15,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        124+114,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        3+15,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        858 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        858,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        858 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        525 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        525,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        525 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (858*525*60)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (858*525*60)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (858*525*60)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x2CD3FE,
       0x1ED4C4,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (858*525*60)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (858*525*60)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (858*525*60)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT480P_60=
{
    {//Dac Out for U3 bringup
        "DACOUT_480P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,
        //1,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        62,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        60,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        30,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        62+60,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        6+30,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        858 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        858,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        858 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        525 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        525,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        525 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (858*525*60)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (858*525*60)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (858*525*60)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB

       0,          //   double clock
       0x73FBDE,
       0x3555E9,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (858*525*60)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (858*525*60)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (858*525*60)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT576I_50=
{
    {//Dac Out for U3 bringup
        "DACOUT_576I_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,
        //1,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        126,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        138,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        3,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        19,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        126+138,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        3+19,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        576,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        864 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        864,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        864 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        625 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        625,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        625 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (864*625*50)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (864*625*50)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (864*625*50)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB

       0,          //   double clock
       0x2CE213,
       0x1EDB6D,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (864*625*50)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (864*625*50)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (864*625*50)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT576P_50=
{
    {//Dac Out for U3 bringup
        "DACOUT_576P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        //1,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        64,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        68,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        39,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        64+68,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+39,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        576,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        864 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        864,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        864 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        625 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        625,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        625 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (864*625*50)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (864*625*50)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (864*625*50)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB

       0,          //   double clock
       0x742B06,
       0x355FE0,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (864*625*50)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (864*625*50)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (864*625*50)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT720P_60=
{
    {//Dac Out for U3 bringup
        "DACOUT_720P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        220,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        20,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        40+220,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+20,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        720,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1650 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1650,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1650 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        750 + 100,      //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        750,            //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        750 - 100,      //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (1650*750*60)/1000000 + 10,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (1650*750*60)/1000000,          //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (1650*750*60)/1000000 - 10,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1EBCB1,
       0x1770C0,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (1650*750*60)/1000000 + 10,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (1650*750*60)/1000000,          //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (1650*750*60)/1000000 - 10,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT720P_50=
{
    {//Dac Out for U3 bringup
        "DACOUT_720P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        220,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        20,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        40+220,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+20,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        720,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1980 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1980,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1980 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        750 + 100,      //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        750,            //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        750 - 100,      //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (1980*750*50)/1000000 + 10,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (1980*750*50)/1000000,          //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (1980*750*50)/1000000 - 10,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1EBCB1,
       0x1770C0,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (1980*750*50)/1000000 + 10,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (1980*750*50)/1000000,          //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (1980*750*50)/1000000 - 10,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT1080I_50=
{
    {//Dac Out for U3 bringup
        "DACOUT_1080I_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        15,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+15,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2640 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2640,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2640 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2640*1125*50)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2640*1125*50)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2640*1125*50)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (2640*1125*50)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (2640*1125*50)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (2640*1125*50)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT1080I_60=
{
    {//Dac Out for U3 bringup
        "DACOUT_1080I_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        15,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+15,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2200 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2200 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2200*1125*60)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2200*1125*60)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2200*1125*60)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (2200*1125*60)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (2200*1125*60)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (2200*1125*60)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT1080P_50=
{
    {//Dac Out for U3 bringup
        "DACOUT_1080P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        36,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+36,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2640 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2640,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2640 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2640*1125*50)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2640*1125*50)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2640*1125*50)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (2640*1125*50)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (2640*1125*50)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (2640*1125*50)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stDACOUT1080P_60=
{
    {//Dac Out for U3 bringup
        "DACOUT_1080P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        36,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        5+36,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2200 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2200 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2200*1125*60)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2200*1125*60)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2200*1125*60)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (2200*1125*60)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (2200*1125*60)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (2200*1125*60)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};
#endif

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
ST_PANEL_NEW_PANELTYPE stMFCFullHD120_CMO216_H1L01=
{
    {
        "URSA120_CMO216H1_L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MFC,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stMFCFullHD60_CMO216_H1L01=
{
    {
        "URSA60_CMO216H1_L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MFC,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};
#endif

#if( ENABLE_TCON||ENABLE_TCON_2014 )
ST_PANEL_NEW_PANELTYPE stTCON_PNL_7626_T3200B_Y400_SD_BOE_HV320WHB=
{
     {
        "7668-T3200B-Y000",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_1CH_6P_8BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        50,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        200,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        32,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        0x04,       //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH           // //TCON VSYNC start
        0x20,       //BYTE m_ucPanelBackPorch;           //PANEL_VSYNC_BACK_PORCH          //TCONVSYNC   width

        64,         //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        34,         //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2000ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,//1560ul,//1624ul,     //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1450ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        806,//806,//810,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        778,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        93,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        68,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,       //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFE,
       0x000001,
       E_PNL_CHG_DCLK,//E_PNL_CHG_VTOTAL,//E_PNL_CHG_DCLK,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCONFullHD=
{
    {
        "tTCONFullHD",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MINILVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
	    1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE


        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        16,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        16+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1135,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

	    TI_10BIT_MODE,             //10bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_HTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCONWXGA=
{
    {
        "tTCONWXGA",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MINILVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        34,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        4+34,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,//1430,  //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        806ul,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        789,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x20ea0e,
       0x167109,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCONFullHD_SHARP_LK400D3GA60K=
{
    {
        "tTCONFullHD_SHARP_LK400D3GA60K",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MINILVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
	    1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE


        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        31,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        16,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0, //16+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1100,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

	    TI_10BIT_MODE,             //10bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_HTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_WXGA_IPS32_AX080A076G_Panasonic=
{
    {
        "WXGA_IPS32_AX080A076G",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MINILVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH           // //TCON VSYNC start
        1,         //BYTE m_ucPanelBackPorch;           //PANEL_VSYNC_BACK_PORCH          //TCONVSYNC   width
        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x15,//0x25,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1576,       //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        826,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        789,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,       //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x212f78+0x5000,
       0x212f78-0x5000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_HS_LVDS,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_WXGA_IPS32_Panasonic_For_Funai=
{
    {
        "WXGA_IPS32_Panasonic_For_Funai",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH           // //TCON VSYNC start
        1,         //BYTE m_ucPanelBackPorch;           //PANEL_VSYNC_BACK_PORCH          //TCONVSYNC   width
        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x15,//0x25,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1576,       //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        826,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        789,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,       //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x212f78+0x5000,
       0x212f78-0x5000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense=
{
    {
        "WXGA_IPS_ALPHA_AH080A016G",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_2CH_3P_6BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        32,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        16+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        20,         //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,     //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        806ul,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        806ul,      //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock

       0x2EA378+0x100000,
       0x2EA378-0x100000,

       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_6BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_WXGA_PM058OX1_MINILVDS=
{
    {
        "TCON_PNL_WXGA_PM058OX1_MINILVDS",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_1CH_6P_6BIT,//LINK_TTL  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16, //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40, //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4, //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16, //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        16+40, //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        20, //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280, //WORD m_wPanelWidth;               //PANEL_WIDTH
        768, //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1736, //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1736, //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1736, //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1350, //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1041, //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1000, //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (150), //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (120), //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120), //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,//E_PNL_ASPECT_RATIO_4_3, //
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,//   E_PNL_CHG_DCLK, // E_PNL_CHG_VTOTAL
       1,///<  PAFRC mixed with noise dither disable
    },
    (150), //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (120), //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120), //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_1CH_6P_6BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_SVGA_PD050SX1_TTL=
{
    {
        "SVGA_PD050_TTL_TCON",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_TTL_TCON,//LINK_TTL  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,       //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4,  //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16, //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        16+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        20,//3+6,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        800,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        600,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1064,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1056,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1056,// 920,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        800,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        632,//525,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        632,//604,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (45),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (40),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (35),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,//E_PNL_ASPECT_RATIO_4_3, //
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,//   E_PNL_CHG_DCLK, // E_PNL_CHG_VTOTAL
       1,///<  PAFRC mixed with noise dither disable
    },
    (45),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (40),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (35),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_TTL_TCON,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

//TCON_PNL_XGA_PD0035VX2_TTL
ST_PANEL_NEW_PANELTYPE stTCON_PNL_XGA_PD0035VX2_TTL=
{
    {
        "XGA_PD0035VX2_TTL",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,              //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_TTL_TCON,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16, //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40, //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4, //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16, //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        16+40, //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        20, //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        640, //WORD m_wPanelWidth;               //PANEL_WIDTH
        480, //WORD m_wPanelHeight;              //PANEL_HEIGHT

        800, //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        800, //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        800, //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        640, //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        523, //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        520, //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (40), //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (25), //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (25), //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,//E_PNL_ASPECT_RATIO_4_3, //
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,//   E_PNL_CHG_DCLK, // E_PNL_CHG_VTOTAL
       1,///<  PAFRC mixed with noise dither disable
    },
    (40), //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (25), //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (25), //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_TTL_TCON,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_WXGA_BOE_HV320WXC=
{
    {
        "WXGA_BOE_HV320WXC",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_1CH_6P_8BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        200,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        32,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        0x04,       //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH           // //TCON VSYNC start
        0x1D,       //BYTE m_ucPanelBackPorch;           //PANEL_VSYNC_BACK_PORCH          //TCONVSYNC   width

        64,         //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        34,         //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1368,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1776ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1624ul,     //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1624ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        900,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        810,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        810,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        93,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        68,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,       //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFE,
       0x000001,
       E_PNL_CHG_DCLK,
       1,///<  PAFRC mixed with noise dither disable
    },
    93,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    68,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_1CH_6P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_FullHD_Amtran_Demo=
{
    {
        "FullHD_Amtran_Demo",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_2CH_6P_8BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        0x70,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x00,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920ul,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080ul,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360ul,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200ul,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020ul,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200ul,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125ul,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125ul,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_6P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};


ST_PANEL_NEW_PANELTYPE stTCON_PNL_FULLHD_AUO_T420HW09=
{
    {
        "FullHD_AUO_T420HW09",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_2CH_3P_8BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        11,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        0x70,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x00,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2650,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2340,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1480,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_DCLK,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_FULLHD_BOE_HV430FHB=
{
    {
        "FullHD_AUO_T420HW09",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_2CH_3P_8BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        11,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        0x70,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x00,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2650,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2340,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1480,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_DCLK,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_CSOT_TRIGATE_32=
{
    {
        "CSOT_TRIGATE_32",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        200,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        32,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,       //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH           // //TCON VSYNC start
        34,       //BYTE m_ucPanelVsyncBackPorch;           //PANEL_VSYNC_BACK_PORCH          //TCONVSYNC   width

        64,         //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        36,         //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1776ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,     //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1560ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        900,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        838,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL
        838,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        93,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        68,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,       //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_10BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0xFFFFFE,
       0x000001,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    93,         //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    78,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    68,         //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_1CH_6P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_CSOT_V390HZ1=
{
    {
        "tTCON_PNL_CSOT_V390HZ1",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        17,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        0x70,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x00,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2650,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2340,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1480,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

ST_PANEL_NEW_PANELTYPE stTCON_PNL_CMO_V390HJ1=
{
    {
        "tTCON_PNL_CMO_V390HJ1",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        17,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        0x6E,       //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x00,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1922,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2650,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2340,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1480,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

#endif // #if ENABLE_TCON

#if SUPPORT_VX1_OUTPUT
#if (SUPPORT_NEW_PANEL_INTERFACE)
ST_PANEL_NEW_PANELTYPE stPanel_INX_M280DGJ_L30_Vx1_4K2K_60HZ_1Division =
#else
PanelType  tPanel_INX_M280DGJ_L30_Vx1_4K2K_60HZ_1Division[] =
#endif
{
    {
        "Panel_INX_M280DGJ_L30_Vx1_4K2K_60HZ_1Division",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

        PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1^PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        30,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        96,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        30+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        2+96,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
        3840,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        2160,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        4500,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        4400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        4300,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2360,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        2260,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        2160,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
        (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x175CE8,//m_dwPanelMaxSET
       0x16FCE8,//m_dwPanelMinSET
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    #if (SUPPORT_NEW_PANEL_INTERFACE)
    (620),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (594),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (580),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_VBY1_10BIT_8LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
    #endif
};

#if (SUPPORT_NEW_PANEL_INTERFACE)
ST_PANEL_NEW_PANELTYPE stPanel_CSOT_MT5461D01_Vx1_4K2K_60HZ_2Division =
#else
PanelType  tPanel_CSOT_MT5461D01_Vx1_4K2K_60HZ_2Division[] =
#endif
{
    {
        "Panel_CSOT_MT5461D01_Vx1_4K2K_60HZ_2Division",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1^PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        30,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        96,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        30+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        2+96,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
        3840,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        2160,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        5760,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        4400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        4240,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2450,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        2260,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        2172,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
        (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x175CE8,//m_dwPanelMaxSET
       0x16FCE8,//m_dwPanelMinSET
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    #if (SUPPORT_NEW_PANEL_INTERFACE)
    (628),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (594),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (480),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_VBY1_10BIT_8LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
    #endif
};

#if (SUPPORT_NEW_PANEL_INTERFACE)
ST_PANEL_NEW_PANELTYPE stPanel_INX_V650DK1_KS2_IN8922_Vx1_4K2K_60HZ_1Division =
#else
PanelType  tPanel_INX_V650DK1_KS2_IN8922_Vx1_4K2K_60HZ_1Division[] =
#endif
{
    {
        "Panel_INX_V650DK1_KS2_IN8922_Vx1_4K2K_60HZ_1Division",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1^PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        30,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        96,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        30+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        2+96,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
        3840,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        2160,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        4800,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        4400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        4240,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2350,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        2250,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL
        2208,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
        (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x175CE8,//m_dwPanelMaxSET
       0x16FCE8,//m_dwPanelMinSET
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    #if (SUPPORT_NEW_PANEL_INTERFACE)
    (624),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (594),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (560),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_VBY1_10BIT_8LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
    #endif
};

#if (SUPPORT_NEW_PANEL_INTERFACE)
ST_PANEL_NEW_PANELTYPE stPanel_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division =
#else
PanelType  tPanel_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division[] =
#endif
{
    {
        "Panel_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1^PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        30,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        96,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        30+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        2+96,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
        3840,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        2160,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        4800,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        4400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        4240,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2350,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        2250,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL
        2208,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
        (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x175CE8,//m_dwPanelMaxSET
       0x16FCE8,//m_dwPanelMinSET
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    #if (SUPPORT_NEW_PANEL_INTERFACE)
    (624),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (594),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (560),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_VBY1_10BIT_8LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
    #endif
};

#if (SUPPORT_NEW_PANEL_INTERFACE)
ST_PANEL_NEW_PANELTYPE stPanel_INX_V500DK2_KS1_IN8903_Vx1_FHD_60HZ_1Division =
#else
PanelType  tPanel_INX_V500DK2_KS1_IN8903_Vx1_FHD_60HZ_1Division[] =
#endif
{
    {
        "Panel_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1^PANEL_SWAP_LVDS_POL,

        PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2680,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2120,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1395,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL
        1104,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
        (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x175B75,//m_dwPanelMaxSET
       0x16FB75,//m_dwPanelMinSET
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
    #if SUPPORT_NEW_PANEL_INTERFACE
    (624/4),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (594/4),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (560/4),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_VBY1_10BIT_2LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
    #endif
};
#endif
#if( HDMITX_4030_ENABLE ==ENABLE)

    #if (SUPPORT_NEW_PANEL_INTERFACE)
    ST_PANEL_NEW_PANELTYPE stPanel_HDMITX_VB1_4K2K_60P_MS  =
    #else
    PanelType   tPanel_HDMITX_VB1_4K2K_60P_MS[] =
    #endif
    {
        {
            "stPanel_HDMITX_VB1_4K2K_60P_MS",//m_pPanelName
            //////////////////////////////////////////////
            // Panel output
            //////////////////////////////////////////////
            0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
            LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

            0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

           0,// PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                            // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

            0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
            0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
            0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
            0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

            1^PANEL_SWAP_LVDS_POL,

            PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
            1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
            0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
            0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
            0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
            0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
            0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
            0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

            ///////////////////////////////////////////////
            // Output tmming setting
            ///////////////////////////////////////////////
            // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
            0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
            0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
            0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
            0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

            30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
            200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
            220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
            10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

            88,//30,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
            296,//80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

           10,/////2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
            72,//96,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

            88+296,//30+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
            10+72,//////2+96,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
            3840,       //WORD m_wPanelWidth;               //PANEL_WIDTH
            2160,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

            4660,//4500,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
            4400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
            4020,//4300,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

            2350,//2360,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
            2250,       //  2250,  //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation//modified by Weng 2015.09.16
            2150,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
            (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
           (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
            (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

            0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
            0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

            0x6D,       //m_ucDimmingCtl

            255,        //m_ucMaxPWMVal;
            0x20,//63,  //m_ucMinPWMVal;
            0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
            E_PNL_ASPECT_RATIO_WIDE,
            //
            //  Board related params.
            //
           0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
           TI_8BIT_MODE,               //8bit ti bit mode
           OUTPUT_10BIT_MODE,          //10bit ti bit mode
           0,          //   PANEL_SWAP_ODD_RG
           0,          //   PANEL_SWAP_EVEN_RG
           0,          //   PANEL_SWAP_ODD_GB
           0,          //   PANEL_SWAP_EVEN_GB
           1,          //   double clock
           #if 0//modified by Weng 2015.09.16
    	   0x175CE8,//m_dwPanelMaxSET
           0x16FCE8,//m_dwPanelMinSET
    	   #else
           0x1755d1,//0x175CE8,//m_dwPanelMaxSET
           0x1735d1,//0x16FCE8,//m_dwPanelMinSET
           #endif
    	   #if 0//modified by Weng 2015.09.16
    	   E_PNL_CHG_VTOTAL,
    	   #else
          E_PNL_CHG_DCLK,//
           #endif
           1,///<  PAFRC mixed with noise dither disable
        },
        #if (SUPPORT_NEW_PANEL_INTERFACE)
    	#if 0//modified by Weng 2015.09.16
        (620),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (594),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (580),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    	#else
        (610),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (600),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (590),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
        #endif
        LINK_VBY1_10BIT_8LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
        #endif
    };

    #if (SUPPORT_NEW_PANEL_INTERFACE)
    ST_PANEL_NEW_PANELTYPE stPanel_HDMITX_VB1_4K2K_30P_MS  =
    #else
    PanelType   tPanel_HDMITX_VB1_4K2K_30P_MS[] =
    #endif
    {
        {
            "stPanel_HDMITX_VB1_4K2K_30P_MS",//m_pPanelName
            //////////////////////////////////////////////
            // Panel output
            //////////////////////////////////////////////
            0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
            LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

            0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT   in Vx1 outout case, 0: 1-Division, 1: 2-Divison

           0,// PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                            // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

            0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
            0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
            0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
            0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

            1^PANEL_SWAP_LVDS_POL,

            PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
            1^ PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
            0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
            0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
            0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
            0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
            0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
            0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

            ///////////////////////////////////////////////
            // Output tmming setting
            ///////////////////////////////////////////////
            // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
            0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
            0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
            0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
            0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

            30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
            200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
            220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
            10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

            88,//30,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
            296,//80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

           10,/////2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
            72,//96,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

            88+296,//30+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
            10+72,//////2+96,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
            3840,       //WORD m_wPanelWidth;               //PANEL_WIDTH
            2160,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

            4660,//4500,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
            4400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
            4020,//4300,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

            2350,//2360,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
            2250,       //  2250,  //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation//modified by Weng 2015.09.16
            2150,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL
            (162),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
            (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
           (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

            0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
            0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

            0x6D,       //m_ucDimmingCtl

            255,        //m_ucMaxPWMVal;
            0x20,//63,  //m_ucMinPWMVal;
            0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
            E_PNL_ASPECT_RATIO_WIDE,
            //
            //  Board related params.
            //
           0xFF0, //(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
           TI_8BIT_MODE,               //8bit ti bit mode
           OUTPUT_10BIT_MODE,          //10bit ti bit mode
           0,          //   PANEL_SWAP_ODD_RG
           0,          //   PANEL_SWAP_EVEN_RG
           0,          //   PANEL_SWAP_ODD_GB
           0,          //   PANEL_SWAP_EVEN_GB
           1,          //   double clock
           #if 0//modified by Weng 2015.09.16
    	   0x175CE8,//m_dwPanelMaxSET
           0x16FCE8,//m_dwPanelMinSET
    	   #else
           0x1755d1,//0x175CE8,//m_dwPanelMaxSET
           0x1735d1,//0x16FCE8,//m_dwPanelMinSET
           #endif
    	   #if 0//modified by Weng 2015.09.16
    	   E_PNL_CHG_VTOTAL,
    	   #else
          E_PNL_CHG_DCLK,//
           #endif
           1,///<  PAFRC mixed with noise dither disable
        },
        #if (SUPPORT_NEW_PANEL_INTERFACE)
    	#if 0//modified by Weng 2015.09.16
        (620),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (594),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (580),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    	#else
        (310),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (300),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (290),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
        #endif
        LINK_VBY1_10BIT_4LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
        #endif
    };

#if (SUPPORT_NEW_PANEL_INTERFACE)
    ST_PANEL_NEW_PANELTYPE stPanel_HDMITX_VB1_FHD_60P_MS  =
#else
    PanelType   tPanel_HDMITX_VB1_FHD_60P_MS[] =
#endif
    {
        {
            "stPanel_HDMITX_VB1_FHD_60P_MS",//m_pPanelName
            //////////////////////////////////////////////
            // Panel output
            //////////////////////////////////////////////
            0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
            LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

            0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT
            0,                    // shall swap if
                                                            // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

            0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
            0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
            0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
            0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

            PANEL_SWAP_LVDS_POL,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL

            PANEL_SWAP_LVDS_CH,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
            PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        	0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

            0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
            0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
            0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
            0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
            0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

            ///////////////////////////////////////////////
            // Output tmming setting
            ///////////////////////////////////////////////
            // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
            0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
            0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
            0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
            0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

            30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
            200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
            220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
            10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

            44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
            148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

            5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
            36,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

            192,//32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
            41,//8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

            1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
            1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

            2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
            2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
            2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

            1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
            1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
            1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

            (159),//(164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
            (149),//(150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
            (139),//(120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

            0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
            0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

            0x6D,       //m_ucDimmingCtl

            255,        //m_ucMaxPWMVal;
            0x20,//63,  //m_ucMinPWMVal;
            0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
            E_PNL_ASPECT_RATIO_WIDE,
            //
            //  Board related params.
            //
           (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
    	   TI_8BIT_MODE,               //8bit ti bit mode
           OUTPUT_10BIT_MODE,          //10bit m_ucOutputFormatBitMode
           0,          //   PANEL_SWAP_ODD_RG
           0,          //   PANEL_SWAP_EVEN_RG
           0,          //   PANEL_SWAP_ODD_GB
           0,          //   PANEL_SWAP_EVEN_GB
           1,          //   double clock
           0x18451D,//0x20EA0E,
           0X16451D,//0x181568,
           E_PNL_CHG_DCLK,
           1,///<  PAFRC mixed with noise dither disable
        },
    #if (SUPPORT_NEW_PANEL_INTERFACE)
    (159),//(164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (149),//(150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (139),//(120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_VBY1_10BIT_2LANE,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
    #endif
};

#endif


ST_PANEL_NEW_PANELTYPE* stPanelIndexTbl[] =
{
    &stPanel_FULLHD_SEC32_LE32A,      // 1920*1200, PNL_FULLHD_SEC_LE32A
    &stPanel_SXGA_AU17_EN05,          // 1280*1024, PNL_SXGA_AU17_EN05
    &stPanel_WXGA_AU20_T200XW02,      // 1366*768 , PNL_WXGA_AU20_T200XW02,
    &stPanel_WXGAP_CMO_M190A1,        // 1440*900 , PNL_WXGA_PLUS_CMO190_M190A1
    &stPanel_WSXGA_AU22_M201EW01,     // 1680*1050, PNL_WSXGA_AU22_M201EW01,
    &stPanel_FullHD_CMO216_H1L01,     // 1920*1080, PNL_FULLHD_CMO216_H1L01

    &stPanel_WUXGA_CMO_260J2,         // 1920*1200, PNL_WUXGA_CMO260_J2
    &stPanel_WXGA_AU20_T200XW02_LGD,  // 1366*768 , PNL_AU20_T200XW02_WXGA,

#if(ENABLE_SUPPORT_PNL_LC320DXJ)
    &stPanel_LC320DXJ,                // 1366*768 , PNL_LC320DXJ
#endif

    &stPanelFullHD_1080P30,  // 1920*1080@30

#if(ENABLE_TTL_PANEL)
    &stPNL_TTL_480P,
    &stPNL_TTL_720P,
    &stPNL_TTL_1080P,
#endif

#if( ENABLE_DAC_OUT )
    &stDACOUT480I_60,                 // DAC 720*480
    &stDACOUT480P_60,                 // DAC 720*480
    &stDACOUT576I_50,                 // DAC 720*576
    &stDACOUT576P_50,                 // DAC 720*576
    &stDACOUT720P_50,                 // DAC 1280*720
    &stDACOUT720P_60,                 // DAC 1280*720
    &stDACOUT1080I_50,                // DAC 1920*1080I 50MHz
    &stDACOUT1080I_60,                // DAC 1920*1080I 60MHz
    &stDACOUT1080P_50,                // DAC 1920*1080P 50MHz
    &stDACOUT1080P_60,                // DAC 1920*1080P 60MHz
#endif

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
    &stMFCFullHD120_CMO216_H1L01,         // 1920x1080
    &stMFCFullHD60_CMO216_H1L01,          // 1920x1080
#endif


#if( ENABLE_TCON||ENABLE_TCON_2014)
    &stTCON_PNL_7626_T3200B_Y400_SD_BOE_HV320WHB,
    &stTCONFullHD,
    &stTCONWXGA,
    &stTCONFullHD_SHARP_LK400D3GA60K,
    &stTCON_PNL_WXGA_IPS32_AX080A076G_Panasonic,
    &stTCON_PNL_WXGA_IPS32_Panasonic_For_Funai,
    &stTCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense,
    &stTCON_PNL_WXGA_PM058OX1_MINILVDS,
    &stTCON_PNL_SVGA_PD050SX1_TTL,
    &stTCON_PNL_XGA_PD0035VX2_TTL,
    &stTCON_PNL_WXGA_BOE_HV320WXC,
    &stTCON_PNL_FullHD_Amtran_Demo,
    &stTCON_PNL_FULLHD_AUO_T420HW09,
    &stTCON_PNL_FULLHD_BOE_HV430FHB,
    &stTCON_PNL_CSOT_TRIGATE_32,
    &stTCON_PNL_CSOT_V390HZ1,
    &stTCON_PNL_CMO_V390HJ1,
#endif

  #if SUPPORT_VX1_OUTPUT
    &stPanel_INX_M280DGJ_L30_Vx1_4K2K_60HZ_1Division,
    &stPanel_CSOT_MT5461D01_Vx1_4K2K_60HZ_2Division,
    &stPanel_INX_V650DK1_KS2_IN8922_Vx1_4K2K_60HZ_1Division,
    &stPanel_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division,
    &stPanel_INX_V500DK2_KS1_IN8903_Vx1_FHD_60HZ_1Division,
  #endif
#if( HDMITX_4030_ENABLE ==ENABLE)
    &stPanel_HDMITX_VB1_4K2K_60P_MS,
    &stPanel_HDMITX_VB1_4K2K_30P_MS,
    & stPanel_HDMITX_VB1_FHD_60P_MS ,
#endif
};

/***************************************************************************************/
#define PNL_TBL_DBG(x)      (x)

void MApp_Print_ST_PANEL_NEW_PANELTYPE_Variable(ST_PANEL_NEW_PANELTYPE *stPnlTblTmp)
{
    PNL_TBL_DBG( printf("\e[31;1m >> %s(%d) \33[m \n", __FUNCTION__, sizeof(ST_PANEL_NEW_PANELTYPE)) );

    PNL_TBL_DBG( printf("[Panel]                   : %s\n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_pPanelName) );
    PNL_TBL_DBG( printf("[m_bPanelDither]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelDither) );
    PNL_TBL_DBG( printf("[m_ePanelLinkType]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ePanelLinkType) );
    PNL_TBL_DBG( printf("[m_bPanelDualPort]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelDualPort) );
    PNL_TBL_DBG( printf("[m_bPanelSwapPort]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapPort) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_ML]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapOdd_ML) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_ML]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapEven_ML) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_RB]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapOdd_RB) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_RB]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapEven_RB) );
    PNL_TBL_DBG( printf("[m_bPanelSwapLVDS_POL]    : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapLVDS_POL) );
    PNL_TBL_DBG( printf("[m_bPanelSwapLVDS_CH]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapLVDS_CH) );
    PNL_TBL_DBG( printf("[m_bPanelPDP10BIT]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelPDP10BIT) );
    PNL_TBL_DBG( printf("[m_bPanelLVDS_TI_MODE]    : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelLVDS_TI_MODE) );
    PNL_TBL_DBG( printf("[m_ucPanelDCLKDelay]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelDCLKDelay) );
    PNL_TBL_DBG( printf("[m_bPanelInvDCLK]         : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelInvDCLK) );
    PNL_TBL_DBG( printf("[m_bPanelInvDE]           : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelInvDE) );
    PNL_TBL_DBG( printf("[m_bPanelInvHSync]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelInvHSync) );
    PNL_TBL_DBG( printf("[m_bPanelInvVSync]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelInvVSync) );
    PNL_TBL_DBG( printf("[m_ucPanelDCKLCurrent]    : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelDCKLCurrent) );
    PNL_TBL_DBG( printf("[m_ucPanelDECurrent]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelDECurrent) );
    PNL_TBL_DBG( printf("[m_ucPanelODDDataCurrent] : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelODDDataCurrent) );
    PNL_TBL_DBG( printf("[m_ucPanelEvenDataCurrent]: %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelEvenDataCurrent) );
    PNL_TBL_DBG( printf("[m_bPanelOnTiming1]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelOnTiming1) );
    PNL_TBL_DBG( printf("[m_bPanelOnTiming2]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelOnTiming2) );
    PNL_TBL_DBG( printf("[m_bPanelOffTiming1]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelOffTiming1) );
    PNL_TBL_DBG( printf("[m_bPanelOffTiming2]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelOffTiming2) );
    PNL_TBL_DBG( printf("[m_ucPanelHSyncWidth]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelHSyncWidth) );
    PNL_TBL_DBG( printf("[m_ucPanelHSyncBackPorch] : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelHSyncBackPorch) );
    PNL_TBL_DBG( printf("[m_ucPanelVSyncWidth]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelVSyncWidth) );
    PNL_TBL_DBG( printf("[m_ucPanelVBackPorch]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelVBackPorch) );
    PNL_TBL_DBG( printf("[m_bPanelHStart]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelHStart) );
    PNL_TBL_DBG( printf("[m_bPanelVStart]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelVStart) );
    PNL_TBL_DBG( printf("[m_bPanelWidth]           : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelWidth) );
    PNL_TBL_DBG( printf("[m_bPanelHeight]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelHeight) );
    PNL_TBL_DBG( printf("[m_bPanelMaxHTotal]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelMaxHTotal) );
    PNL_TBL_DBG( printf("[m_bPanelHTotal]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelHTotal) );
    PNL_TBL_DBG( printf("[m_bPanelMinHTotal]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelMinHTotal) );
    PNL_TBL_DBG( printf("[m_bPanelMaxVTotal]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelMaxVTotal) );
    PNL_TBL_DBG( printf("[m_bPanelVTotal]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelVTotal) );
    PNL_TBL_DBG( printf("[m_bPanelMinVTotal]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wPanelMinVTotal) );
    PNL_TBL_DBG( printf("[m_dwPanelMaxDCLK]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_dwPanelMaxDCLK) );
    PNL_TBL_DBG( printf("[m_dwPanelDCLK]           : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_dwPanelDCLK) );
    PNL_TBL_DBG( printf("[m_dwPanelMinDCLK]        : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_dwPanelMinDCLK) );
    PNL_TBL_DBG( printf("[m_bSpreadSpectrumStep]   : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wSpreadSpectrumStep) );
    PNL_TBL_DBG( printf("[m_bSpreadSpectrumSpan]   : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_wSpreadSpectrumSpan) );
    PNL_TBL_DBG( printf("[m_ucDimmingCtl]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucDimmingCtl) );
    PNL_TBL_DBG( printf("[m_ucMaxPWMVal]           : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucMaxPWMVal) );
    PNL_TBL_DBG( printf("[m_ucMinPWMVal]           : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucMinPWMVal) );
    PNL_TBL_DBG( printf("[m_bPanelDeinterMode]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelDeinterMode) );
    PNL_TBL_DBG( printf("[m_ucPanelAspectRatio]    : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucPanelAspectRatio) );
    PNL_TBL_DBG( printf("[m_bLVDSTxSwapValue]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_u16LVDSTxSwapValue) );
    PNL_TBL_DBG( printf("[m_ucTiBitMode]           : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucTiBitMode) );
    PNL_TBL_DBG( printf("[m_ucOutputFormatBitMode] : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucOutputFormatBitMode) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_RG]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapOdd_RG) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_RG]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapEven_RG) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_GB]      : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapOdd_GB) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_GB]     : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelSwapEven_GB) );
    PNL_TBL_DBG( printf("[m_bPanelDoubleClk]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelDoubleClk) );
    PNL_TBL_DBG( printf("[m_bPanelMaxSET]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_dwPanelMaxSET) );
    PNL_TBL_DBG( printf("[m_bPanelMinSET]          : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_dwPanelMinSET) );
    PNL_TBL_DBG( printf("[m_ucOutTimingMode]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_ucOutTimingMode) );
    PNL_TBL_DBG( printf("[m_bPanelNoiseDith]       : %X \n", stPnlTblTmp->stOldPanelTypeFromUtopia.m_bPanelNoiseDith) );
    PNL_TBL_DBG( printf("[u8PanelMaxDCLK]          : %X \n", stPnlTblTmp->u16PanelMaxDCLK) );
    PNL_TBL_DBG( printf("[u8PanelDCLK]             : %X \n", stPnlTblTmp->u16PanelMaxDCLK) );
    PNL_TBL_DBG( printf("[u8PanelMinDCLK]          : %X \n", stPnlTblTmp->u16PanelDCLK) );
    PNL_TBL_DBG( printf("[enLinkExtType]           : %X \n", stPnlTblTmp->enLinkExtType) );

    PNL_TBL_DBG( printf(" \n") );
}

/***************************************************************************************/

#if ENABLE_PANEL_BIN

MS_U8  m_bPanelName[PANEL_BIN_PNLTBL_NAME_SIZE];
ST_PANEL_BIN_STRUCT stPanelBinStruct;
ST_PANEL_NEW_PANELTYPE stPanelBinTbl;

BOOLEAN MApi_PanelParameter_DMA_Bin(void)
{
    BININFO BinInfo;
    BOOLEAN bResult;

    printf("\e[31;1m [*%d]: %s \33[m \n", __LINE__, __FUNCTION__);

    BinInfo.B_ID = BIN_ID_PANEL;

    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);

    printf("\e[31;1m Panel bin = %x, %lx, %lx, %bd \33[m \n",
         BinInfo.B_ID,  BinInfo.B_FAddr,  BinInfo.B_Len, (U16)BinInfo.B_IsComp);

    if (SUCCESS == MDrv_DMA_LoadBin(&BinInfo, _PA2VA(POOL_BUFFER_ADR), 0, 0) )
    {
        printf("\n Load Panel bin pass!\n");
    }
    else
    {
        printf("\n Load Panel bin fail!\n");
        return FALSE;
    }

    U8* pPanelParam;
    static const U8 tHeadChar[PANEL_BIN_HEADER_MSTAR_SIZE] = {"MStarsemi PanelBin"};
    static U32 u32Version = 0;
    static U32 u32CrcInBin = 0;
    U8  uc;

    pPanelParam = PA2KSEG0(POOL_BUFFER_ADR);

    for (uc=PANEL_BIN_HEADER_START; uc<PANEL_BIN_HEADER_MSTAR_SIZE; uc++)
    {
        if (tHeadChar[uc]=='\0')
            break;

        //printf("[%x-%x] ", *(pPanelParam+uc), tHeadChar[uc]);
        //printf("[%c-%c] \n", *(pPanelParam+uc), tHeadChar[uc]);

        if (*(pPanelParam+uc) != tHeadChar[uc])
        {
            printf("\n\e[31;1m Get Header fail! \33[m \n");
            return FALSE;
        }
    }


    if ( *(pPanelParam+PANEL_BIN_HEADER_VERSION_START) == 'V' )
    {
        for (uc=1; uc<(PANEL_BIN_HEADER_SIZE_VERSION); uc++)
        {
            u32Version = u32Version << 8;
            u32Version += (*(pPanelParam+PANEL_BIN_HEADER_VERSION_START+uc));

            //printf("[%x] u32Version = %X \n", *(pPanelParam+PANEL_BIN_HEADER_VERSION_START+uc), u32Version);
        }

        stPanelBinStruct.u32Version = u32Version;
    }
    else
    {
        printf("\n Get Version fail!\n");
        return FALSE;
    }
    printf(" u32Version = %X \n", stPanelBinStruct.u32Version);


    if ( *(pPanelParam+PANEL_BIN_HEADER_TABLE_START) == 'T' )
    {
        stPanelBinStruct.u8PnlTblNum = (*(pPanelParam+PANEL_BIN_HEADER_TABLE_START+1));

        printf(" Table Num = %X \n", stPanelBinStruct.u8PnlTblNum);
    }
    else
    {
        printf("\n Get Table Num fail!\n");
    }

//    for (uc=0; uc<PANEL_BIN_HEADER_CRC_SIZE; uc++)
    {
        u32CrcInBin =  (*(pPanelParam+PANEL_BIN_HEADER_CRC_START+0))        +
                      ((*(pPanelParam+PANEL_BIN_HEADER_CRC_START+1)) >> 8)  +
                      ((*(pPanelParam+PANEL_BIN_HEADER_CRC_START+2)) >> 16) +
                      ((*(pPanelParam+PANEL_BIN_HEADER_CRC_START+3)) >> 24);

        //printf("[%x] u32CrcInBin = %X \n", *(pPanelParam+PANEL_BIN_HEADER_CRC_START+uc), u32CrcInBin);
    }
    stPanelBinStruct.u32CrcChecksum = u32CrcInBin;
    printf(" u32CrcInBin = %X \n", u32CrcInBin);

    stPanelBinStruct.pPanelTblParam = pPanelParam + PANEL_BIN_TABLE_START;
    printf("\n Panel Parameter Load %s \n", ((bResult)?("Correct"):("Fail")));

    return bResult;
}

BOOLEAN MApi_PanelParameter_LoadTable(U8 u8PanelIndex)
{
    printf("\e[31;1m >> %s(%X) \33[m \n", __FUNCTION__, u8PanelIndex);

    U8* pPanelTblParam;

  #if 0 // debug
    U8  i, j;
    for (i=0; i<stPanelBinStruct.u8PnlTblNum; i++)
    {
        pPanelTblParam = stPanelBinStruct.pPanelTblParam + (i*PANEL_BIN_TABLE_SIZE);

        printf("Start Addr of Tbl[%d]: %x (offset: %x) \n", i, pPanelTblParam, PANEL_PARAM_ADR);

        for (j=0; j<PANEL_BIN_TABLE_SIZE; j++)
        {
            printf("0x%02X, ", *(pPanelTblParam+j) );
            if (((j + 1) % 16) == 0)
            {
                printf("\n");
            }
        }
    }
  #endif

    pPanelTblParam = stPanelBinStruct.pPanelTblParam + (u8PanelIndex*PANEL_BIN_TABLE_SIZE);

    memcpy(&stPanelBinStruct.stPanelTbl, pPanelTblParam, PANEL_BIN_TABLE_SIZE);

    MApp_Print_PanelBin_Variable();

    // parsing table into structure

    memcpy(m_bPanelName,
           stPanelBinStruct.stPanelTbl.m_pPanelName, PANEL_BIN_PNLTBL_NAME_SIZE);
    stPanelBinTbl.stOldPanelTypeFromUtopia.m_pPanelName = (char *)m_bPanelName;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelDither =
            stPanelBinStruct.stPanelTbl.m_bPanelDither;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ePanelLinkType = (APIPNL_LINK_TYPE)
            stPanelBinStruct.stPanelTbl.m_ePanelLinkType;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelDualPort =
            stPanelBinStruct.stPanelTbl.m_bPanelDualPort;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapPort =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapPort^PANEL_CONNECTOR_SWAP_PORT;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapOdd_ML =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_ML;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapEven_ML =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_ML;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapOdd_RB =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_RB;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapEven_RB =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_RB;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapLVDS_POL =
            PANEL_SWAP_LVDS_POL;//stPanelBinStruct.stPanelTbl.m_bPanelSwapLVDS_POL;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapLVDS_CH =
            PANEL_SWAP_LVDS_CH;//stPanelBinStruct.stPanelTbl.m_bPanelSwapLVDS_CH;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelPDP10BIT =
            PANEL_PDP_10BIT;//stPanelBinStruct.stPanelTbl.m_bPanelPDP10BIT;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelLVDS_TI_MODE =
            stPanelBinStruct.stPanelTbl.m_bPanelLVDS_TI_MODE;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelDCLKDelay =
            stPanelBinStruct.stPanelTbl.m_ucPanelDCLKDelay;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelInvDCLK =
            stPanelBinStruct.stPanelTbl.m_bPanelInvDCLK;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelInvDE =
            stPanelBinStruct.stPanelTbl.m_bPanelInvDE;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelInvHSync =
            stPanelBinStruct.stPanelTbl.m_bPanelInvHSync;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelInvVSync =
            stPanelBinStruct.stPanelTbl.m_bPanelInvVSync;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelDCKLCurrent =
            stPanelBinStruct.stPanelTbl.m_ucPanelDCKLCurrent;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelDECurrent =
            stPanelBinStruct.stPanelTbl.m_ucPanelDECurrent;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelODDDataCurrent =
            stPanelBinStruct.stPanelTbl.m_ucPanelODDDataCurrent;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelEvenDataCurrent =
            stPanelBinStruct.stPanelTbl.m_ucPanelEvenDataCurrent;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelOnTiming1 =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelOnTiming1_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelOnTiming1_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelOnTiming2 =
            (WORD) ( stPanelBinStruct.stPanelTbl.m_bPanelOnTiming2_L
                   | stPanelBinStruct.stPanelTbl.m_bPanelOnTiming2_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelOffTiming1 =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelOffTiming1_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelOffTiming1_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelOffTiming2 =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelOffTiming2_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelOffTiming2_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelHSyncWidth =
            stPanelBinStruct.stPanelTbl.m_ucPanelHSyncWidth;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelHSyncBackPorch =
            stPanelBinStruct.stPanelTbl.m_ucPanelHSyncBackPorch;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelVSyncWidth =
            stPanelBinStruct.stPanelTbl.m_ucPanelVSyncWidth;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelVBackPorch =
            stPanelBinStruct.stPanelTbl.m_ucPanelVBackPorch;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelHStart =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelHStart_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelHStart_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelVStart =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelVStart_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelVStart_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelWidth =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelWidth_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelWidth_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelHeight =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelHeight_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelHeight_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelMaxHTotal =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelMaxHTotal_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelMaxHTotal_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelHTotal =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelHTotal_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelHTotal_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelMinHTotal =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelMinHTotal_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelMinHTotal_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelMaxVTotal =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelMinHTotal_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelMinHTotal_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelVTotal =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelVTotal_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelVTotal_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wPanelMinVTotal =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bPanelMaxVTotal_L
                   |stPanelBinStruct.stPanelTbl.m_bPanelMaxVTotal_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_dwPanelMaxDCLK =
            stPanelBinStruct.stPanelTbl.m_dwPanelMaxDCLK;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_dwPanelDCLK =
            stPanelBinStruct.stPanelTbl.m_dwPanelDCLK;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_dwPanelMinDCLK =
            stPanelBinStruct.stPanelTbl.m_dwPanelMinDCLK;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wSpreadSpectrumStep =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumStep_L
                   |stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumStep_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_wSpreadSpectrumSpan =
            (WORD) (stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumSpan_L
                   |stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumSpan_H << 8);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucDimmingCtl =
            stPanelBinStruct.stPanelTbl.m_ucDimmingCtl;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucMaxPWMVal =
            stPanelBinStruct.stPanelTbl.m_ucMaxPWMVal;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucMinPWMVal =
            stPanelBinStruct.stPanelTbl.m_ucMinPWMVal;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelDeinterMode =
            stPanelBinStruct.stPanelTbl.m_bPanelDeinterMode;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucPanelAspectRatio = (E_PNL_ASPECT_RATIO)
            stPanelBinStruct.stPanelTbl.m_ucPanelAspectRatio;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_u16LVDSTxSwapValue =
            (WORD) ((LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L);

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucTiBitMode = (APIPNL_TIBITMODE)
            stPanelBinStruct.stPanelTbl.m_ucTiBitMode;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucOutputFormatBitMode = (APIPNL_OUTPUTFORMAT_BITMODE)
            stPanelBinStruct.stPanelTbl.m_ucOutputFormatBitMode;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapOdd_RG =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_RG;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapEven_RG =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_RG;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapOdd_GB =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_GB;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapEven_GB =
            stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_GB;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelDoubleClk =
            stPanelBinStruct.stPanelTbl.m_bPanelDoubleClk;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_dwPanelMaxSET =
            (DWORD) ( stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_LL
                    | stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_LH << 8
                    | stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_HL << 16
                    | stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_HH << 24 );

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_dwPanelMinSET =
            (DWORD) ( stPanelBinStruct.stPanelTbl.m_bPanelMinSET_LL
                    | stPanelBinStruct.stPanelTbl.m_bPanelMinSET_LH << 8
                    | stPanelBinStruct.stPanelTbl.m_bPanelMinSET_HL << 16
                    | stPanelBinStruct.stPanelTbl.m_bPanelMinSET_HH << 24 );

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucOutTimingMode = (APIPNL_OUT_TIMING_MODE)
            stPanelBinStruct.stPanelTbl.m_ucOutTimingMode;

    stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelNoiseDith =
            stPanelBinStruct.stPanelTbl.m_bPanelNoiseDith;


    stPanelBinTbl.u16PanelMaxDCLK =
            (WORD) (stPanelBinStruct.stPanelTbl.u8PanelMaxDCLK_L
                   |stPanelBinStruct.stPanelTbl.u8PanelMaxDCLK_H << 8);

    stPanelBinTbl.u16PanelDCLK =
            (WORD) (stPanelBinStruct.stPanelTbl.u8PanelDCLK_L
                   |stPanelBinStruct.stPanelTbl.u8PanelDCLK_H << 8);

    stPanelBinTbl.u16PanelMinDCLK =
            (WORD) (stPanelBinStruct.stPanelTbl.u8PanelDCLK_L
                   |stPanelBinStruct.stPanelTbl.u8PanelDCLK_H << 8);

    stPanelBinTbl.enLinkExtType = (APIPNL_LINK_EXT_TYPE)
            stPanelBinStruct.stPanelTbl.enLinkExtType;

    MApp_PanelParameter_UpdateFromFactory();

//    MApp_Print_ST_PANEL_NEW_PANELTYPE_Variable(&stPanel_FullHD_CMO216_H1L01);

    MApp_Print_ST_PANEL_NEW_PANELTYPE_Variable(&stPanelBinTbl);

    return TRUE;
}

void MApp_PanelParameter_UpdateFromFactory(void)
{
    U8 u8PanelBinIndex = G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex;
    printf("\e[31;1m MApp_PanelParameter_UpdateFromFactory(%d) =  \33[m \n", u8PanelBinIndex);

    PNL_TBL_DBG( printf("~ u32CrcChecksum                : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.u32CrcChecksum) );

    if ( G_FACTORY_SETTING.stFacPnlSetting.u32CrcChecksum !=
         stPanelBinStruct.u32CrcChecksum )
    {
        printf(" PanelBin CRC/Checksum not matched \n");
        MApp_DataBase_RestoreDefault_FactoryPnlSetting();
    }
    G_FACTORY_SETTING.stFacPnlSetting.u32CrcChecksum = stPanelBinStruct.u32CrcChecksum;

    if ( G_FACTORY_SETTING.stFacPnlSetting.u32Version !=
         stPanelBinStruct.u32Version )
    {
        printf(" PanelBin Version not matched \n");
        MApp_DataBase_RestoreDefault_FactoryPnlSetting();
    }
    G_FACTORY_SETTING.stFacPnlSetting.u32Version = stPanelBinStruct.u32Version;

    PNL_TBL_DBG( printf("~ bUpdated                : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.bUpdated) );
    PNL_TBL_DBG( printf("~ u8PanelBinIndex         : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex) );
    PNL_TBL_DBG( printf("~ m_bPanelDualPort        : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort) );
    PNL_TBL_DBG( printf("~ m_bPanelSwapPort        : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort) );
    PNL_TBL_DBG( printf("~ m_bPanelLVDS_TI_MODE    : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE) );
    PNL_TBL_DBG( printf("~ m_ucTiBitMode           : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode) );
    PNL_TBL_DBG( printf("~ m_ucOutputFormatBitMode : %X \n",
                G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode) );

    if ( G_FACTORY_SETTING.stFacPnlSetting.bUpdated[u8PanelBinIndex] )
    {
        stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelDualPort =
            G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort[u8PanelBinIndex];

        stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapPort =
            G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort[u8PanelBinIndex];

        stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelLVDS_TI_MODE =
            G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE[u8PanelBinIndex];

        stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucTiBitMode = (APIPNL_TIBITMODE)
            G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode[u8PanelBinIndex];

        stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucOutputFormatBitMode = (APIPNL_OUTPUTFORMAT_BITMODE)
            G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode[u8PanelBinIndex];
    }
    else
    {
        G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort[u8PanelBinIndex] =
            stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelDualPort;

        G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort[u8PanelBinIndex] =
            stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelSwapPort;

        G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE[u8PanelBinIndex] =
            stPanelBinTbl.stOldPanelTypeFromUtopia.m_bPanelLVDS_TI_MODE;

        G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode[u8PanelBinIndex] =
            stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucTiBitMode;

        G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode[u8PanelBinIndex] =
            stPanelBinTbl.stOldPanelTypeFromUtopia.m_ucOutputFormatBitMode;
    }
}


void MApp_Print_PanelBin_Variable(void)
{
    PNL_TBL_DBG( printf("\e[31;1m >> %s(%d) \33[m \n", __FUNCTION__, sizeof(PanelBinType)) );

    PNL_TBL_DBG( printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n") );
    PNL_TBL_DBG( printf(" ~~~~~~~~ value from Panel bin ~~~~~~~~ \n") );
    PNL_TBL_DBG( printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n") );

    PNL_TBL_DBG( printf("[Panel]                   : %s\n", stPanelBinStruct.stPanelTbl.m_pPanelName) );
    PNL_TBL_DBG( printf("[m_bPanelDither]          : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelDither) );
    PNL_TBL_DBG( printf("[m_ePanelLinkType]        : %X \n", stPanelBinStruct.stPanelTbl.m_ePanelLinkType) );
    PNL_TBL_DBG( printf("[m_bPanelDualPort]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelDualPort) );
    PNL_TBL_DBG( printf("[m_bPanelSwapPort]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapPort) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_ML]      : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_ML) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_ML]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_ML) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_RB]      : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_RB) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_RB]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_RB) );
    PNL_TBL_DBG( printf("[m_bPanelSwapLVDS_POL]    : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapLVDS_POL) );
    PNL_TBL_DBG( printf("[m_bPanelSwapLVDS_CH]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapLVDS_CH) );
    PNL_TBL_DBG( printf("[m_bPanelPDP10BIT]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelPDP10BIT) );
    PNL_TBL_DBG( printf("[m_bPanelLVDS_TI_MODE]    : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelLVDS_TI_MODE) );
    PNL_TBL_DBG( printf("[m_ucPanelDCLKDelay]      : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelDCLKDelay) );
    PNL_TBL_DBG( printf("[m_bPanelInvDCLK]         : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelInvDCLK) );
    PNL_TBL_DBG( printf("[m_bPanelInvDE]           : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelInvDE) );
    PNL_TBL_DBG( printf("[m_bPanelInvHSync]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelInvHSync) );
    PNL_TBL_DBG( printf("[m_bPanelInvVSync]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelInvVSync) );
    PNL_TBL_DBG( printf("[m_ucPanelDCKLCurrent]    : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelDCKLCurrent) );
    PNL_TBL_DBG( printf("[m_ucPanelDECurrent]      : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelDECurrent) );
    PNL_TBL_DBG( printf("[m_ucPanelODDDataCurrent] : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelODDDataCurrent) );
    PNL_TBL_DBG( printf("[m_ucPanelEvenDataCurrent]: %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelEvenDataCurrent) );
    PNL_TBL_DBG( printf("[m_bPanelOnTiming1_L]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOnTiming1_L) );
    PNL_TBL_DBG( printf("[m_bPanelOnTiming1_H]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOnTiming1_H) );
    PNL_TBL_DBG( printf("[m_bPanelOnTiming2_L]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOnTiming2_L) );
    PNL_TBL_DBG( printf("[m_bPanelOnTiming2_H]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOnTiming2_H) );
    PNL_TBL_DBG( printf("[m_bPanelOffTiming1_L]    : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOffTiming1_L) );
    PNL_TBL_DBG( printf("[m_bPanelOffTiming1_H]    : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOffTiming1_H) );
    PNL_TBL_DBG( printf("[m_bPanelOffTiming2_L]    : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOffTiming2_L) );
    PNL_TBL_DBG( printf("[m_bPanelOffTiming2_H]    : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelOffTiming2_H) );
    PNL_TBL_DBG( printf("[m_ucPanelHSyncWidth]     : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelHSyncWidth) );
    PNL_TBL_DBG( printf("[m_ucPanelHSyncBackPorch] : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelHSyncBackPorch) );
    PNL_TBL_DBG( printf("[m_ucPanelVSyncWidth]     : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelVSyncWidth) );
    PNL_TBL_DBG( printf("[m_ucPanelVBackPorch]     : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelVBackPorch) );
    PNL_TBL_DBG( printf("[m_bPanelHStart_L]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelHStart_L) );
    PNL_TBL_DBG( printf("[m_bPanelHStart_H]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelHStart_H) );
    PNL_TBL_DBG( printf("[m_bPanelVStart_L]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelVStart_L) );
    PNL_TBL_DBG( printf("[m_bPanelVStart_H]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelVStart_H) );
    PNL_TBL_DBG( printf("[m_bPanelWidth_L]         : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelWidth_L) );
    PNL_TBL_DBG( printf("[m_bPanelWidth_H]         : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelWidth_H) );
    PNL_TBL_DBG( printf("[m_bPanelHeight_L]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelHeight_L) );
    PNL_TBL_DBG( printf("[m_bPanelHeight_H]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelHeight_H) );
    PNL_TBL_DBG( printf("[m_bPanelMaxHTotal_L]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxHTotal_L) );
    PNL_TBL_DBG( printf("[m_bPanelMaxHTotal_H]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxHTotal_H) );
    PNL_TBL_DBG( printf("[m_bPanelHTotal_L]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelHTotal_L) );
    PNL_TBL_DBG( printf("[m_bPanelHTotal_H]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelHTotal_H) );
    PNL_TBL_DBG( printf("[m_bPanelMinHTotal_L]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinHTotal_L) );
    PNL_TBL_DBG( printf("[m_bPanelMinHTotal_H]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinHTotal_H) );
    PNL_TBL_DBG( printf("[m_bPanelMaxVTotal_L]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxVTotal_L) );
    PNL_TBL_DBG( printf("[m_bPanelMaxVTotal_H]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxVTotal_H) );
    PNL_TBL_DBG( printf("[m_bPanelVTotal_L]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelVTotal_L) );
    PNL_TBL_DBG( printf("[m_bPanelVTotal_H]        : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelVTotal_H) );
    PNL_TBL_DBG( printf("[m_bPanelMinVTotal_L]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinVTotal_L) );
    PNL_TBL_DBG( printf("[m_bPanelMinVTotal_H]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinVTotal_H) );
    PNL_TBL_DBG( printf("[m_dwPanelMaxDCLK]        : %X \n", stPanelBinStruct.stPanelTbl.m_dwPanelMaxDCLK) );
    PNL_TBL_DBG( printf("[m_dwPanelDCLK]           : %X \n", stPanelBinStruct.stPanelTbl.m_dwPanelDCLK) );
    PNL_TBL_DBG( printf("[m_dwPanelMinDCLK]        : %X \n", stPanelBinStruct.stPanelTbl.m_dwPanelMinDCLK) );
    PNL_TBL_DBG( printf("[m_bSpreadSpectrumStep_L] : %X \n", stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumStep_L) );
    PNL_TBL_DBG( printf("[m_bSpreadSpectrumStep_H] : %X \n", stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumStep_H) );
    PNL_TBL_DBG( printf("[m_bSpreadSpectrumSpan_L] : %X \n", stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumSpan_L) );
    PNL_TBL_DBG( printf("[m_bSpreadSpectrumSpan_H] : %X \n", stPanelBinStruct.stPanelTbl.m_bSpreadSpectrumSpan_H) );
    PNL_TBL_DBG( printf("[m_ucDimmingCtl]          : %X \n", stPanelBinStruct.stPanelTbl.m_ucDimmingCtl) );
    PNL_TBL_DBG( printf("[m_ucMaxPWMVal]           : %X \n", stPanelBinStruct.stPanelTbl.m_ucMaxPWMVal) );
    PNL_TBL_DBG( printf("[m_ucMinPWMVal]           : %X \n", stPanelBinStruct.stPanelTbl.m_ucMinPWMVal) );
    PNL_TBL_DBG( printf("[m_bPanelDeinterMode]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelDeinterMode) );
    PNL_TBL_DBG( printf("[m_ucPanelAspectRatio]    : %X \n", stPanelBinStruct.stPanelTbl.m_ucPanelAspectRatio) );
    PNL_TBL_DBG( printf("[m_bLVDSTxSwapValue_L]    : %X \n", stPanelBinStruct.stPanelTbl.m_bLVDSTxSwapValue_L) );
    PNL_TBL_DBG( printf("[m_bLVDSTxSwapValue_H]    : %X \n", stPanelBinStruct.stPanelTbl.m_bLVDSTxSwapValue_H) );
    PNL_TBL_DBG( printf("[m_ucTiBitMode]           : %X \n", stPanelBinStruct.stPanelTbl.m_ucTiBitMode) );
    PNL_TBL_DBG( printf("[m_ucOutputFormatBitMode] : %X \n", stPanelBinStruct.stPanelTbl.m_ucOutputFormatBitMode) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_RG]      : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_RG) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_RG]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_RG) );
    PNL_TBL_DBG( printf("[m_bPanelSwapOdd_GB]      : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapOdd_GB) );
    PNL_TBL_DBG( printf("[m_bPanelSwapEven_GB]     : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelSwapEven_GB) );
    PNL_TBL_DBG( printf("[m_bPanelDoubleClk]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelDoubleClk) );
    PNL_TBL_DBG( printf("[m_bPanelMaxSET_LL]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_LL) );
    PNL_TBL_DBG( printf("[m_bPanelMaxSET_LH]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_LH) );
    PNL_TBL_DBG( printf("[m_bPanelMaxSET_HL]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_HL) );
    PNL_TBL_DBG( printf("[m_bPanelMaxSET_HH]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMaxSET_HH) );
    PNL_TBL_DBG( printf("[m_bPanelMinSET_LL]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinSET_LL) );
    PNL_TBL_DBG( printf("[m_bPanelMinSET_LH]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinSET_LH) );
    PNL_TBL_DBG( printf("[m_bPanelMinSET_HL]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinSET_HL) );
    PNL_TBL_DBG( printf("[m_bPanelMinSET_HH]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelMinSET_HH) );
    PNL_TBL_DBG( printf("[m_ucOutTimingMode]       : %X \n", stPanelBinStruct.stPanelTbl.m_ucOutTimingMode) );
    PNL_TBL_DBG( printf("[m_bPanelNoiseDith]       : %X \n", stPanelBinStruct.stPanelTbl.m_bPanelNoiseDith) );
    PNL_TBL_DBG( printf("[u8PanelMaxDCLK_L]        : %X \n", stPanelBinStruct.stPanelTbl.u8PanelMaxDCLK_L) );
    PNL_TBL_DBG( printf("[u8PanelMaxDCLK_H]        : %X \n", stPanelBinStruct.stPanelTbl.u8PanelMaxDCLK_H) );
    PNL_TBL_DBG( printf("[u8PanelDCLK_L]           : %X \n", stPanelBinStruct.stPanelTbl.u8PanelDCLK_L) );
    PNL_TBL_DBG( printf("[u8PanelDCLK_H]           : %X \n", stPanelBinStruct.stPanelTbl.u8PanelDCLK_H) );
    PNL_TBL_DBG( printf("[u8PanelMinDCLK_L]        : %X \n", stPanelBinStruct.stPanelTbl.u8PanelMinDCLK_L) );
    PNL_TBL_DBG( printf("[u8PanelMinDCLK_H]        : %X \n", stPanelBinStruct.stPanelTbl.u8PanelMinDCLK_H) );
    PNL_TBL_DBG( printf("[enLinkExtType]           : %X \n", stPanelBinStruct.stPanelTbl.enLinkExtType) );

    PNL_TBL_DBG( printf(" \n") );
}

U8 MApp_Get_PanelBin_TableNum(void)
{
    return stPanelBinStruct.u8PnlTblNum;
}
#endif

/***************************************************************************************/


PanelType * MApi_XC_GetPanelSpec(PANEL_RESOLUTION_TYPE enResolutionType)
{
  #if ENABLE_PANEL_BIN
    return &(stPanelBinTbl.stOldPanelTypeFromUtopia);
    UNUSED(enResolutionType);
  #else
    // For TV case, the DE Vstart must be large than 8 for PDP pixel shift
    if (stPanelIndexTbl[(MS_U8)enResolutionType] != NULL)
    {
        if ( stPanelIndexTbl[(MS_U8)enResolutionType]->stOldPanelTypeFromUtopia.m_wPanelVStart < 8)
            stPanelIndexTbl[(MS_U8)enResolutionType]->stOldPanelTypeFromUtopia.m_wPanelVStart = 8;
    }

    return &(stPanelIndexTbl[(MS_U8)enResolutionType]->stOldPanelTypeFromUtopia);
  #endif
}

void MApi_XC_SetPanelExtType(PANEL_RESOLUTION_TYPE enResolutionType)
{
    APIPNL_LINK_EXT_TYPE ePanelLinkType;

    if ( devPanel_IsEXT(enResolutionType) )
    {
      #if ENABLE_PANEL_BIN
        ePanelLinkType = stPanelBinTbl.enLinkExtType;
      #else
        ePanelLinkType = stPanelIndexTbl[(MS_U8)enResolutionType]->enLinkExtType;
      #endif

        MApi_PNL_SetLPLLTypeExt(ePanelLinkType);
        printf("%s, %d, u16PanelExternLinkType =%u\n", __FUNCTION__, __LINE__, ePanelLinkType);
    }

    UNUSED(enResolutionType);
}

PANEL_RESOLUTION_TYPE MApi_PNL_Get_CurPanelType(void)
{
    //PRINT_CURRENT_LINE();
    //printf("Cur panel=%u\n", g_PNL_TypeSel);
    return g_PNL_TypeSel;
}

MS_U16  devPanel_WIDTH(void)
{
    return g_IPanel.Width();
}

MS_U16  devPanel_HEIGHT(void)
{
    return g_IPanel.Height();
}

BOOLEAN devPanel_FullHD(void)
{
    if ( ( g_IPanel.Width() == 1920 ) && ( g_IPanel.Height() == 1080 ) )
        return TRUE;

    return FALSE;
}

/******************************************************************************/
///Get the panel type is TTL or not
/******************************************************************************/

BOOLEAN devPanel_IsTTL(PANEL_RESOLUTION_TYPE enResolutionType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.stOldPanelTypeFromUtopia.m_ePanelLinkType == LINK_TTL);
    UNUSED(enResolutionType);
  #else
    return (stPanelIndexTbl[(MS_U8)enResolutionType]->stOldPanelTypeFromUtopia.m_ePanelLinkType == LINK_TTL);
  #endif
}

BOOLEAN devPanel_IsEXT(PANEL_RESOLUTION_TYPE enResolutionType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.stOldPanelTypeFromUtopia.m_ePanelLinkType == LINK_EXT);
    UNUSED(enResolutionType);
  #else
    return (stPanelIndexTbl[(MS_U8)enResolutionType]->stOldPanelTypeFromUtopia.m_ePanelLinkType == LINK_EXT);
  #endif
}

BOOLEAN devPanel_IsVx1(PANEL_RESOLUTION_TYPE enResolutionType)
{
#if SUPPORT_VX1_OUTPUT
    if((stPanelIndexTbl[(MS_U8)enResolutionType]->stOldPanelTypeFromUtopia.m_ePanelLinkType == LINK_EXT)
        &&((stPanelIndexTbl[(MS_U8)enResolutionType]->enLinkExtType >= LINK_VBY1_10BIT_4LANE)
            && (stPanelIndexTbl[(MS_U8)enResolutionType]->enLinkExtType <= LINK_VBY1_8BIT_8LANE))
        )
    {
        return TRUE;
    }
    else
#else
    UNUSED(enResolutionType);
#endif
    {
        return FALSE;
    }
}

#if 0 // no used
PANEL_RESOLUTION_TYPE MApi_XC_GetPanelSpecByName(char *pInputString)
{
    U8 i = 0;

    for(; i<PNL_RES_MAX_NUM ; i++ )
    {
        if ( 0 == strcmp( stPanelIndexTbl[i]->stOldPanelTypeFromUtopia.m_pPanelName, pInputString))
            return (PANEL_RESOLUTION_TYPE)i;
    }
    return PANEL_DEFAULT_TYPE_SEL;
}
#endif

const char* MApi_PNL_Get_PanelName(PANEL_RESOLUTION_TYPE ePanelResType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.stOldPanelTypeFromUtopia.m_pPanelName);
    UNUSED(ePanelResType);
  #else
    return (stPanelIndexTbl[ePanelResType]->stOldPanelTypeFromUtopia.m_pPanelName);
  #endif
}

APIPNL_LINK_TYPE MApi_PNL_Get_PanelLinkType(PANEL_RESOLUTION_TYPE ePanelResType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.stOldPanelTypeFromUtopia.m_ePanelLinkType);
    UNUSED(ePanelResType);
  #else
    return (stPanelIndexTbl[ePanelResType]->stOldPanelTypeFromUtopia.m_ePanelLinkType);
  #endif
}

MS_U16 MApi_PNL_Get_PanelTypicalDclk(PANEL_RESOLUTION_TYPE ePanelResType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.u16PanelDCLK);
    UNUSED(ePanelResType);
  #else
    return (stPanelIndexTbl[ePanelResType]->u16PanelDCLK);
  #endif
}

MS_U16 MApi_PNL_Get_PanelDClkMax(PANEL_RESOLUTION_TYPE ePanelResType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.u16PanelMaxDCLK);
    UNUSED(ePanelResType);
  #else
    return (stPanelIndexTbl[ePanelResType]->u16PanelMaxDCLK);
  #endif
}

MS_U16 MApi_PNL_Get_PanelDClkMin(PANEL_RESOLUTION_TYPE ePanelResType)
{
  #if ENABLE_PANEL_BIN
    return (stPanelBinTbl.u16PanelMinDCLK);
    UNUSED(ePanelResType);
  #else
    return (stPanelIndexTbl[ePanelResType]->u16PanelMinDCLK);
  #endif
}

BOOLEAN MApi_PNL_PanelIndexTableValidCheck(void)
{
    MS_U8 u8PanelTableSize = sizeof(stPanelIndexTbl)/sizeof(ST_PANEL_NEW_PANELTYPE*);
    MS_U8 u8PanelIndexEnumNumber = PNL_RES_MAX_NUM;

    if(u8PanelTableSize != u8PanelIndexEnumNumber)
    {
        printf("\n\n\r !!! In %s, PanelTableSize=%d, PanelIndexEnumNumber=%d, mismatch! Maybe causing some error", __FUNCTION__, u8PanelTableSize, u8PanelIndexEnumNumber);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

//--------
// panel
//--------
//static void _msAPI_Scaler_SetPanelVCC(MS_BOOL bEnable)
void MApi_PNL_Set_PanelVCC(MS_BOOL bEnable)
{
    #ifdef BENCH_CODE_USAGE
    return;
    #endif

    //PRINT_CURRENT_LINE();
    PANEL_ON_SEQ( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
    PANEL_ON_SEQ( printf("MApi_PNL_Set_PanelVCC(bEnable=%u) at %u %s\n", bEnable, MsOS_GetSystemTime(), ANSI_COLOR_OFF_STR ); );

    if( bEnable )
    {
        PANEL_CTL_On();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus |= PANEL_POWER_VCC;
        g_PNL_u32PanelVcc_TurnOn_Time = MsOS_GetSystemTime();
    }
    else
    {
        PANEL_CTL_Off();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus &= ~PANEL_POWER_VCC;
        g_PNL_u32PanelVcc_TurnOn_Time = 0;
    }
}

#if (CONFIG_3D_HWLVDSLRFLAG)
void PNL_Set3D_HWLVDSLRFlag(void)
{
    MS_PNL_HW_LVDSResInfo lvdsresinfo;
    lvdsresinfo.bEnable = 1;
    lvdsresinfo.u16channel = 0x03; // channel A: BIT0, channel B: BIT1,
    lvdsresinfo.u32pair = 0x18; // pair 0: BIT0, pair 1: BIT1, pair 2: BIT2, pair 3: BIT3, pair 4: BIT4, etc ...

    MApi_PNL_HWLVDSReservedtoLRFlag(lvdsresinfo);
}
#endif

void MApi_PNL_En(MS_BOOL bPanelOn )
{
    //MS_U32 delayTime;
    //PRINT_CURRENT_LINE();

    PANEL_ON_SEQ( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
    PANEL_ON_SEQ( printf("MApi_PNL_En(bPanelOn=%u) at %u %s\n", bPanelOn, MsOS_GetSystemTime(), ANSI_COLOR_OFF_STR ); );

    if(bPanelOn)
    {
        /* Enable VCC */
        MApi_PNL_Set_PanelVCC(bPanelOn);

        //delayTime = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_1);//_getPanelOnTiming1();
        //MsOS_DelayTask(delayTime);

        PANEL_ON_SEQ( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
        PANEL_ON_SEQ( printf("LVDS data=1 at %u %s\n", MsOS_GetSystemTime(), ANSI_COLOR_OFF_STR ); );

        TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_PANEL);

      #if(ENABLE_TCON == 0 && ENABLE_TCON_2014 == 0) //
        MApi_PNL_PreInit(E_PNL_CLK_DATA); // enable LVDS output
        MApi_PNL_SetOutput(E_APIPNL_OUTPUT_CLK_DATA);// enable LVDS output
      #endif

        g_IPanel.Enable(bPanelOn);

   #if( ENABLE_TCON_2014 && (ENABLE_TCON_VER_20==0) )
        msAPI_TCON_LoadTable(TCON_TBL_2D);
    #endif

        TIMER_SET_DELAY_ID_END();

        g_PNL_u32LvdsSignal_TurnOn_Time = MsOS_GetSystemTime();

    #if (XC_MLOAD_INIT_AFTER_PANEL_ENABLE)
        MApi_XC_Sys_Init_MLoad();
    #endif


        #if (ENABLE_MFC_6M20)
        MDrv_Ursa_LVDS_Output(bPanelOn);
        #endif
        #if(ENABLE_MFC_6M30)
        MDrv_Ursa_6M30_VIDEO_Enalbe(DISABLE);
        #endif
        #if (ENABLE_6M40_4KX2K_PROCESS)
        MDrv_Ursa_6M40_LVDS_Enalbe(ENABLE);
        #endif

    }
    else
    {
    #if(ENABLE_TCON) // for TCON: Standby power consumption, too slow (1 minutes)
        if(g_bTCONPowerOnFlag == FALSE)
        {
            MDrv_WriteByte(0x103200, 0x00);
            MDrv_Write2Byte(0x1032DA, 0x0000); // Bank1032_6D=0x0000
            MDrv_Write2Byte(0x1032DC, 0x0000); // Bank1032_6E=0x0000
            MDrv_Write2Byte(0x103202, 0x8000); // Bank1032_01=0x8000
            MDrv_Write2Byte(0x103204, 0x0000); // Bank1032_02=0x0000
            MDrv_Write2Byte(0x103206, 0x0000); // Bank1032_03=0x0000
            MDrv_Write2Byte(0x103208, 0x0000); // Bank1032_04=0x0000
            MDrv_Write2Byte(0x103000, 0x0000); // Bank1030_00=0x0000
            MDrv_Write2Byte(0x1030C2, 0x3FFF); // Bank1030_61=0x3FFF
        }
    #endif

        #if (ENABLE_MFC_6M20)
        MDrv_Ursa_LVDS_Output(bPanelOn);
        #endif
        #if(ENABLE_MFC_6M30)
        MDrv_Ursa_6M30_VIDEO_Enalbe(ENABLE);
        #endif
        #if (ENABLE_6M40_4KX2K_PROCESS)
        MDrv_Ursa_6M40_LVDS_Enalbe(DISABLE);
        #endif

        TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_PANEL);

        g_IPanel.Enable(bPanelOn);

        //MsOS_DelayTask(20);
    #if(ENABLE_TCON == 0 && ENABLE_TCON_2014 == 0)
        MApi_PNL_PreInit(E_PNL_NO_OUTPUT); //disable LVDS output and LVDS pin is low level
        MApi_PNL_SetOutput(E_APIPNL_OUTPUT_NO_OUTPUT);// disable LVDS output and LVDS pin is low level
    #endif

        TIMER_SET_DELAY_ID_END();

        g_PNL_u32LvdsSignal_TurnOn_Time = 0;

        /* enable/disable VCC */
        MApi_PNL_Set_PanelVCC(bPanelOn);

    }

  #if (MS_BOARD_TYPE_SEL == BD_MST186E_D01A_S_NASA)
  {//for LVDS PAD_G_ODD[6], PAD_G_ODD[7] swapping
    MS_U8 u8RegVal;
    u8RegVal = MDrv_ReadByte(0x103200);
    MDrv_WriteByte(0x103200,0);
    MDrv_WriteRegBit(0x1032E6,1,BIT6);
    MDrv_WriteByte(0x103200,u8RegVal);
  }
  #endif

}// Added it by coverity_554

/******************************************************************************/
///Enable/Disable Panel backlight
///@param bEnable \b IN:
///- TRUE: Enable
///- FALSE: Disable
/******************************************************************************/
#define MAX_BACKLIGHT    100
void MApi_PNL_SetInverter(MS_BOOL bEnable)
{
  #ifdef BENCH_CODE_USAGE
    return;
  #endif

    //PRINT_CURRENT_LINE();
    PANEL_ON_SEQ( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
    PANEL_ON_SEQ( printf("MApi_PNL_SetInverter(bPanelOn=%u) at %u %s\n", bEnable, MsOS_GetSystemTime(), ANSI_COLOR_OFF_STR ); );

    if(bEnable)
    {
        g_PNL_u32Backlight_TurnOn_Time = MsOS_GetSystemTime();
        INV_CTL_On();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus |= PANEL_POWER_LIGHT_ON;
    }
    else
    {
        g_PNL_u32Backlight_TurnOn_Time = 0;
        INV_CTL_Off();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus &= ~PANEL_POWER_LIGHT_ON;
    }
}

U8 MApi_PNL_Cal_PWMValue(void)
{
    U8 u8PWM_Value = 0x80;

#if( BLOADER )
    //g_u8TransientBacklight = 100;
    u8PWM_Value = g_IPanel.DimCtrl(E_APIPNL_DIMMING_MAX);
#else
    //g_u8TransientBacklight = MIN(MAX_BACKLIGHT, MAX_BACKLIGHT);

  #if 0//(ENABLE_BACKLIGHT_ADJUST)
    g_u8TransientBacklight = ST_PICTURE.u8Backlight;
  #endif

    u8PWM_Value = msAPI_Mode_PictureBackLightN100toReallyValue( ST_PICTURE.u8Backlight );

  #if(BACKLIGHT_INVERSE)
    u8PWM_Value = Panel_BackLight_Invese(u8PWM_Value);
  #endif
#endif

    return u8PWM_Value;
}

void MApi_PNL_WaitSystemTime(U32 u32SysTime)
{
    U32 u32WaitStart = MsOS_GetSystemTime();

    printf("MApi_PNL_WaitSystemTime(): %u -> %u\n", u32WaitStart, u32SysTime);

    // Wait time up...
    while(1)
    {
        if( MsOS_GetSystemTime() >= u32SysTime )
        {
            break;
        }

        //printf("z");
        //printf("{%u}", MsOS_GetSystemTime());
        //msAPI_Timer_Delayms(5);

        if( msAPI_Timer_DiffTime_2(u32WaitStart, MsOS_GetSystemTime()) >= 1000 )
        {
            break;
        }
    }
}

void MApi_PNL_SetBackLight(MS_BOOL bEnable)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    //PRINT_CURRENT_LINE();
    PANEL_ON_SEQ( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
    PANEL_ON_SEQ( printf("MApi_PNL_SetBackLight(bPanelOn=%u) at %u %s\n", bEnable, MsOS_GetSystemTime(), ANSI_COLOR_OFF_STR ); );

    if ( bEnable )
    {
        if( 0 == g_PNL_u32Backlight_TurnOn_Time ) // Backlight not turn on yet, should turn on
        {
            U16 u16BeforeBacklightOnDelay = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_2);

        #if 1 // Use new method
            ////printf("u16BeforeBacklightOnDelay=%u\n", u16BeforeBacklightOnDelay);
            printf("g_PNL_u32LvdsSignal_TurnOn_Time=%u\n", g_PNL_u32LvdsSignal_TurnOn_Time );

            // Cal what  time should turn on backlight
            U32 u32TimeToTurnOnBacklight = g_PNL_u32LvdsSignal_TurnOn_Time + u16BeforeBacklightOnDelay;
            //printf("u32TimeToTurnOnBacklight=%u\n", u32TimeToTurnOnBacklight );

            // Wait time up...
            MApi_PNL_WaitSystemTime(u32TimeToTurnOnBacklight);
        #else
            msAPI_Timer_Delayms( u16BeforeBacklightOnDelay );
        #endif

            // Backlight-Vcc On
            PANEL_ON_SEQ( msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW); );
            PANEL_ON_SEQ( printf("Backlight On at %u %s\n", MsOS_GetSystemTime(), ANSI_COLOR_OFF_STR ); );
            MApi_PNL_SetInverter(ENABLE);

        }

        // Set PWM
    #if(!LD_ENABLE)
        U8 u8PWM_Value = MApi_PNL_Cal_PWMValue();
        printf("u8PWM_Value=%u\n", u8PWM_Value);
        //Panel_Backlight_PWM_ADJ(u8PWM_Value); //gchen @ 20171226 //disable panel pwm
    #endif

    #if 0 //desable by jp for reduce boot time
        U8 i;
        i = 0;
        msAPI_Scaler_SetPanelBacklight(ENABLE);
        msAPI_Timer_Delayms( 10 );
        Panel_Backlight_Max_Current(PANEL_DIMMING_CTL);

        g_bIsSoftStartValid = TRUE;

        while ( g_bIsSoftStartValid == TRUE )
        {
            if ( g_u8TransientBacklight < MAX_BACKLIGHT )
            {
                g_u8TransientBacklight += 5;
            }

            g_u8TransientBacklight = MIN(g_u8TransientBacklight, MAX_BACKLIGHT);

            msAPI_Scaler_SetBacklight( msAPI_Mode_PictureBackLightN100toReallyValue( g_u8TransientBacklight ));

            msAPI_Timer_Delayms( 10 );
            if ( g_u8TransientBacklight == MAX_BACKLIGHT )
            {
                g_bIsSoftStartValid = FALSE;

            }
        }
    #endif
    }
    else
    {
    #if(!LD_ENABLE)
        // PWM-Dimming = 0
        //Panel_Backlight_PWM_ADJ(0); //gchen @ 20171226 //disable panel pwm
    #endif

        msAPI_Timer_Delayms_2( 5, E_DELAY_ID_PANEL_SET_BACKLIGHT_OFF );

        // Vcc off
        MApi_PNL_SetInverter(DISABLE);
    }

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

/******************************************************************************/
/// Register GPIO related method in g_IPanel
///@param bEnable \b IN:
///- TRUE: Enable
///- FALSE: Disable
/******************************************************************************/
void msAPI_GPIO_RegisterGPIOMethods(XC_PNL_OBJ* panel_interface)
{
    panel_interface->TurnBackLightOn = MApi_PNL_SetInverter;
}


#if (0)
#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 )
   #if (MS_BOARD_TYPE_SEL == BD_MST087A_D01A_S)
      #define PNL_ON_STAGE1 PAD_NC,0,GPIO_NONE
      #define PNL_ON_STAGE2 PAD_NC,0,GPIO_NONE
      #define PNL_ON_STAGE3 PAD_NC,0,GPIO_NONE
   #else
      #define PNL_ON_STAGE1 PAD_NC,0,GPIO_NONE
      #define PNL_ON_STAGE2 PAD_NC,0,GPIO_NONE
      #define PNL_ON_STAGE3 PAD_NC,0,GPIO_NONE
   #endif
#else
      #define PNL_ON_STAGE1 PAD_NC,0,GPIO_NONE
      #define PNL_ON_STAGE2 PAD_NC,0,GPIO_NONE
      #define PNL_ON_STAGE3 PAD_NC,0,GPIO_NONE
#endif

#define __PNL_PIN(ball,delay,level) ball,delay,level
#define PNL_PIN(pin)  __PNL_PIN(pin)

typedef struct
{
  U16 ball_num;
  U16 delay_time;
  U8 level;
} PNL_Ctrl;

PNL_Ctrl g_PanelCtrlFlow[]=
{
  { PNL_PIN(PNL_ON_STAGE1) },
  { PNL_PIN(PNL_ON_STAGE2) },
  { PNL_PIN(PNL_ON_STAGE3) },
};

void MApi_PNL_STAGE1(void)
{
    if(g_PanelCtrlFlow[0].ball_num != PAD_NC)
    {
        if(g_PanelCtrlFlow[0].level == GPIO_OUT_LOW)
            mdrv_gpio_set_low(g_PanelCtrlFlow[0].ball_num);
        else if(g_PanelCtrlFlow[0].level == GPIO_OUT_HIGH)
            mdrv_gpio_set_high(g_PanelCtrlFlow[0].ball_num);
        else
            printf("MApi_PNL_STAGE1 failed in GPIO type error!\r\n");
    }


}

void MApi_PNL_STAGE2(void)
{
    if(g_PanelCtrlFlow[1].ball_num != PAD_NC)
    {
        if(g_PanelCtrlFlow[1].level == GPIO_OUT_LOW)
            mdrv_gpio_set_low(g_PanelCtrlFlow[0].ball_num);
        else if(g_PanelCtrlFlow[1].level == GPIO_OUT_HIGH)
            mdrv_gpio_set_high(g_PanelCtrlFlow[0].ball_num);
        else
            printf("MApi_PNL_STAGE2 failed in GPIO type error!\r\n");
    }


}

void MApi_PNL_STAGE3(void)
{
    if(g_PanelCtrlFlow[2].ball_num != PAD_NC)
    {
        if(g_PanelCtrlFlow[2].level == GPIO_OUT_LOW)
            mdrv_gpio_set_low(g_PanelCtrlFlow[0].ball_num);
        else if(g_PanelCtrlFlow[2].level == GPIO_OUT_HIGH)
            mdrv_gpio_set_high(g_PanelCtrlFlow[0].ball_num);
        else
            printf("MApi_PNL_STAGE3 failed in GPIO type error!\r\n");
    }

}
#endif

#if ENABLE_VX1_CONVERTER_BOARD

#define _DEBUG_VX1_CONVERTER_BOARD_INIT_    (0)

#ifndef _CONVERTER_BOARD_IIC_SEL_
#define _CONVERTER_BOARD_IIC_SEL_           (E_I2C_BUS_DDCD0)
#endif

BOOLEAN MApi_PNL_Converter_Board_Init(void)
{
    BOOLEAN bRet = TRUE;
    U16 U16SlaveID=0;
    U8 u8ChipAddr = 0x40;

    U8 u8Cmd_1[7] = {0x09, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00};
    U8 u8Cmd_2[7] = {0x19, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00};

  #if _DEBUG_VX1_CONVERTER_BOARD_INIT_
    U8* u8Buf;
  #endif

    U16SlaveID |= (U16)((_CONVERTER_BOARD_IIC_SEL_<<8)|u8ChipAddr);

  #if (_DEBUG_VX1_CONVERTER_BOARD_INIT_)
    u8Buf = u8Cmd_1;
    printf("\n### MDrv_IN8903_3D_CMD_DataWrite( %02x, %02x, %02x, %02x, %02x, %02x, %02x)\n", *u8Buf, *(u8Buf+1), *(u8Buf+2), *(u8Buf+3), *(u8Buf+4), *(u8Buf+5), *(u8Buf+6));
  #endif

    bRet = MDrv_IIC_WriteBytes(U16SlaveID, 0, NULL, 7, u8Cmd_1);

    if( bRet == 0 )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Converter_Board i2c 1 failed!\n");
        return FALSE;
    }

    MsOS_DelayTask(20);

  #if (_DEBUG_VX1_CONVERTER_BOARD_INIT_)
    u8Buf = u8Cmd_2;
    printf("### MDrv_IN8903_3D_CMD_DataWrite( %02x, %02x, %02x, %02x, %02x, %02x, %02x)\n", *u8Buf, *(u8Buf+1), *(u8Buf+2), *(u8Buf+3), *(u8Buf+4), *(u8Buf+5), *(u8Buf+6));
    printf("### Converter board init result = %d\n", bRet);
  #endif

    bRet = MDrv_IIC_WriteBytes(U16SlaveID, 0, NULL, 7, u8Cmd_2);

    if( bRet == 0 )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Converter_Board i2c 2 failed!\n");
        return FALSE;
    }

    return TRUE;
}
#endif // #if ENABLE_VX1_CONVERTER_BOARD


//******************************************************************************

#undef _PANEL_C_

#endif // #ifndef _PANEL_C_

