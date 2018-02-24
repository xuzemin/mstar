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
#ifndef _PANEL_H_
#define _PANEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Board.h"
#include "apiPNL.h"

#undef INTERFACE
#define INTERFACE extern

#ifndef ENABLE_TCON
    #define ENABLE_TCON         0
#endif

#ifndef ENABLE_TCON_2014 // TCon table is in bin file
    #define ENABLE_TCON_2014    0
#endif

#ifndef ENABLE_TCON_VER_20
    #define ENABLE_TCON_VER_20  0
#endif

#ifndef ENABLE_DAC_OUT
    #define ENABLE_DAC_OUT      0
#endif

#ifndef ENABLE_OVERDRIVE
    #define ENABLE_OVERDRIVE    0
#endif

#ifndef ENABLE_TTL_PANEL
    #define ENABLE_TTL_PANEL    1//0 //gchen @ 20171208
#endif

/*
#ifndef ENABLE_SUPPORT_PNL_SXGA_AU17_EN05
    #define ENABLE_SUPPORT_PNL_SXGA_AU17_EN05   0
#endif

#ifndef ENABLE_SUPPORT_PNL_LVDS_1080P30
    #define ENABLE_SUPPORT_PNL_LVDS_1080P30   0
#endif
*/

#ifndef ENABLE_SUPPORT_PNL_LC320DXJ
    #define ENABLE_SUPPORT_PNL_LC320DXJ   0
#endif

#define SUPPORT_NEW_PANEL_INTERFACE     1

#ifndef ENABLE_VX1_CONVERTER_BOARD
    #define ENABLE_VX1_CONVERTER_BOARD  0
#endif


#ifndef ENABLE_PANEL_BIN
    #define ENABLE_PANEL_BIN            0
#endif

#if (SUPPORT_VX1_OUTPUT) && (ENABLE_PANEL_BIN)
    #error " PANEL BIN DOES NOT SUPPORT VX1 NOW "
#endif


typedef enum
{
    PANEL_RES_MIN               = 0,

    PNL_FULLHD_SEC_LE32A        = PANEL_RES_MIN,

    // FOR NORMAL LVDS PANEL
    PNL_SXGA_AU17_EN05          = 1,        // 1280*1024, PNL_SXGA_AU17_EN05
    PNL_WXGA_AU20_T200XW02      = 2,        // 1366*768, PNL_WXGA_AU20_T200XW02,
    PNL_WXGA_PLUS_CMO190_M190A1 = 3,        // 1440*900, PNL_WXGA_PLUS_CMO190_M190A1
    PNL_WSXGA_AU22_M201EW01     = 4,        // 1680*1050, PNL_WSXGA_AU22_M201EW01,
    PNL_FULLHD_CMO216_H1L01     = 5,        // 1920*1080, PNL_FULLHD_CMO216_H1L01

    PNL_WUXGA_CMO260_J2         = 6,        // 1920*1200, PNL_WUXGA_CMO260_J2
    PNL_WXGA_AU20_T200XW02_LGD,             // 1366*768, PNL_AU20_T200XW02_WXGA,

#if(ENABLE_SUPPORT_PNL_LC320DXJ)
    PNL_LC320DXJ,
#endif

    PNL_LVDS_1080P30,

#if(ENABLE_TTL_PANEL)
    PNL_TTL_480P,
    PNL_TTL_720P,
    PNL_TTL_1080P,
#endif

#if( ENABLE_DAC_OUT )
    // FOR DAC/HDMI TX OUTPUT
    DACOUT_480I,            // JUST FOR U3 DAC OUTPUT 480I TIMING USAGE
    DACOUT_480P,            // JUST FOR U3 DAC OUTPUT 480P TIMING USAGE
    DACOUT_576I,            // JUST FOR U3 DAC OUTPUT 576I TIMING USAGE
    DACOUT_576P,            // JUST FOR U3 DAC OUTPUT 576P TIMING USAGE
    DACOUT_720P_50,         // JUST FOR U3 DAC OUTPUT 720P TIMING USAGE
    DACOUT_720P_60,         // JUST FOR U3 DAC OUTPUT 720P TIMING USAGE
    DACOUT_1080I_50,        // JUST FOR U3 DAC OUTPUT 1080I TIMING USAGE
    DACOUT_1080I_60,        // JUST FOR U3 DAC OUTPUT 1080I TIMING USAGE
    DACOUT_1080P_50,        // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_1080P_60,        // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
#endif

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
    MFC_DEFAULT,
    MFC120_FULLHD_CMO216_H1L01 = MFC_DEFAULT,
    MFC60_FULLHD_CMO216_H1L01,
#endif

#if( ENABLE_TCON||ENABLE_TCON_2014 )
    TCON_PNL_7626_T3200B_Y400_SD_BOE_HV320WHB,
    TCON_PNL_FULLHD,
    TCON_PNL_WXGA,
    TCON_PNL_FULLHD_SHARP_LK400D3GA60K,
    TCON_PNL_WXGA_IPS32_AX080A076G_Panasonic,
    TCON_PNL_WXGA_IPS32_Panasonic_For_CUS144,
    TCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense,
    TCON_PNL_WXGA_PM058OX1_MINILVDS,
    TCON_PNL_SVGA_PD050SX1_TTL,
    TCON_PNL_XGA_PD0035VX2_TTL,
    TCON_PNL_WXGA_BOE_HV320WXC,
    TCON_PNL_FullHD_Amtran_Demo,
    TCON_PNL_FULLHD_AUO_T420HW09,
    TCON_PNL_FULLHD_BOE_HV430FHB,
    TCON_PNL_CSOT_TRIGATE_32,
    TCON_PNL_CSOT_V390HZ1,
    TCON_PNL_CMO_V390HJ1,
#endif

#if SUPPORT_VX1_OUTPUT
    PNL_INX_M280DGJ_L30_Vx1_4K2K_60HZ_1Division,
    PNL_CSOT_MT5461D01_Vx1_4K2K_60HZ_2Division,
    PNL_INX_V650DK1_KS2_IN8922_Vx1_4K2K_60HZ_1Division,
    PNL_INX_V500DK2_KS1_IN8903_Vx1_4K2K_60HZ_1Division,
    PNL_INX_V500DK2_KS1_IN8903_Vx1_FHD_60HZ_1Division,
#endif
#if(HDMITX_4030_ENABLE==ENABLE)
    PNL_HDMITX_VB1_4K2K_60P_MS,
    PNL_HDMITX_VB1_4K2K_30P_MS,
    PNL_HDMITX_VB1_FHD_60P_MS,
#endif
    PNL_RES_MAX_NUM,
}PANEL_RESOLUTION_TYPE;

#if 1//(SUPPORT_NEW_PANEL_INTERFACE)
typedef struct
{
    PanelType stOldPanelTypeFromUtopia;
    MS_U16 u16PanelMaxDCLK;
    MS_U16 u16PanelDCLK;
    MS_U16 u16PanelMinDCLK;
    APIPNL_LINK_EXT_TYPE enLinkExtType;
}ST_PANEL_NEW_PANELTYPE;
#endif


//#define PANEL_RES_FULL_HD       PNL_FULLHD_CMO216_H1L01

#if ( ENABLE_TCON_2014 )

  #if( CHIP_FAMILY_EDEN == CHIP_FAMILY_TYPE )
    #define PANEL_DEFAULT_TYPE_SEL      TCON_PNL_WXGA_IPS32_Panasonic_For_CUS144
    #define BIN_ID_TCON                 BIN_ID_TCON_WXGA_IPS32_Panasonic_For_CUS144

  #elif( CHIP_FAMILY_NASA == CHIP_FAMILY_TYPE )
    #define PANEL_DEFAULT_TYPE_SEL      TCON_PNL_7626_T3200B_Y400_SD_BOE_HV320WHB
    #define BIN_ID_TCON                 BIN_ID_TCON_TEST

  #elif( CHIP_FAMILY_MARLON == CHIP_FAMILY_TYPE )
    #define PANEL_DEFAULT_TYPE_SEL      TCON_PNL_FULLHD_BOE_HV430FHB //TCON_PNL_WXGA_IPS32_Panasonic_For_CUS144

    #if ENABLE_TCON_VER_20
        #define BIN_ID_TCON             BIN_ID_TCON_TEST_20
    #else
        #define BIN_ID_TCON             BIN_ID_TCON_FULLHD_BOE_HV430FHB //TCON_Marlon_new216_MST269F_Socketboard
    #endif

  #else
    #define PANEL_DEFAULT_TYPE_SEL      TCON_PNL_WXGA_IPS32_Panasonic_For_CUS144
    #error "No TCon bin"
  #endif

#elif ENABLE_TCON
    #define PANEL_DEFAULT_TYPE_SEL      TCON_PNL_CSOT_TRIGATE_32

#elif (HDMITX_4030_ENABLE==ENABLE)
    #define PANEL_DEFAULT_TYPE_SEL      PNL_HDMITX_VB1_4K2K_60P_MS// PNL_HDMITX_VB1_FHD_60P_MS//NL_HDMITX_VB1_4K2K_30P_MS//PNL_HDMITX_VB1_4K2K_60P_MS

#elif( SUPPORT_VX1_OUTPUT )
    #define PANEL_DEFAULT_TYPE_SEL      PNL_INX_M280DGJ_L30_Vx1_4K2K_60HZ_1Division

#else

    #define PANEL_DEFAULT_TYPE_SEL      PNL_TTL_480P //PNL_FULLHD_CMO216_H1L01 //gchen @ 20171208 //V56

#endif

//-------------------------------------------------------------------------------------------

#define PANEL_SMALL_PQ_SELECT       5     // according to PANEL_CURRENT_TYPE_SEL is PANEL_RES_FULL_HD.

//===============================================================================

//#define PANEL_POWER_VCC              0x01
//#define PANEL_POWER_LIGHT_ON         0x02
//#define PANEL_POWER_BLUESCREEN       0x04
//#define PANEL_POWER_FREEZESCREEN     0x08

////////////////////////////////////////////////////
//      global variable
////////////////////////////////////////////////////

INTERFACE PANEL_RESOLUTION_TYPE g_PNL_TypeSel;
INTERFACE PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K2K;
INTERFACE PANEL_RESOLUTION_TYPE g_PNL_TypeSel_4K1K;
INTERFACE PANEL_RESOLUTION_TYPE g_PNL_TypeSel_FHD;


////////////////////////////////////////////////////
//      Functions
////////////////////////////////////////////////////

/*
*       old function, need to take it out later.
*/

#define PANEL_WIDTH         (g_IPanel.Width())
#define PANEL_HEIGHT        (g_IPanel.Height())
#define PANEL_ASPECT_RATIO  (g_IPanel.AspectRatio())
#define PANEL_DIMMING_CTL   (g_IPanel.DimCtrl(E_APIPNL_DIMMING_CURRENT))

#define devPanel_Get_VSYNC_BACK_PORCH(void) (g_IPanel.VSynBackPorch())
#define devPanel_Get_HSYNC_BACK_PORCH(void) (g_IPanel.HSynWidth() + g_IPanel.HSynBackPorch())

PANEL_RESOLUTION_TYPE MApi_PNL_Get_CurPanelType(void);

INTERFACE MS_U16  devPanel_WIDTH(void);
INTERFACE MS_U16  devPanel_HEIGHT(void);
INTERFACE BOOLEAN devPanel_FullHD(void);

INTERFACE BOOLEAN devPanel_IsTTL(PANEL_RESOLUTION_TYPE u8ResolutionType);
INTERFACE BOOLEAN devPanel_IsEXT(PANEL_RESOLUTION_TYPE u8ResolutionType);
INTERFACE BOOLEAN devPanel_IsVx1(PANEL_RESOLUTION_TYPE enResolutionType);

/*
*   below are customized functions,
*
*
*
*/
INTERFACE void MApi_PNL_En(MS_BOOL bPanelOn );
INTERFACE void MApi_PNL_SetBackLight(MS_BOOL bEnable);
INTERFACE void MApi_PNL_Set_PanelVCC(MS_BOOL bEnable);

/*
*   Get PanelType by a given panel index.
*
*   used it with MApi_PNL_Init to initialzed a panel.
*/
INTERFACE PanelType* MApi_XC_GetPanelSpec(PANEL_RESOLUTION_TYPE u8ResolutionType);

/*
* @brief Get PanelType by a given panel name.
* @param pInputString          IN: input string name, please refer to the first member of PanelType
*/
//INTERFACE PANEL_RESOLUTION_TYPE MApi_XC_GetPanelSpecByName(char *pInputString);

const char* MApi_PNL_Get_PanelName(PANEL_RESOLUTION_TYPE ePanelResType);

APIPNL_LINK_TYPE MApi_PNL_Get_PanelLinkType(PANEL_RESOLUTION_TYPE ePanelResType);
MS_U16 MApi_PNL_Get_PanelTypicalDclk(PANEL_RESOLUTION_TYPE ePanelResType);
MS_U16 MApi_PNL_Get_PanelDClkMax(PANEL_RESOLUTION_TYPE ePanelResType);
MS_U16 MApi_PNL_Get_PanelDClkMin(PANEL_RESOLUTION_TYPE ePanelResType);

BOOLEAN MApi_PNL_PanelIndexTableValidCheck(void);


/*
* @brief Set Panel Link Type by a given panel index.
* @param enResolutionType          IN: input is PANEL RESOLUTION TYPE
*/
INTERFACE void MApi_XC_SetPanelExtType(PANEL_RESOLUTION_TYPE enResolutionType);

#if (CONFIG_3D_HWLVDSLRFLAG)
INTERFACE void PNL_Set3D_HWLVDSLRFlag(void);
#endif
#if ENABLE_VX1_CONVERTER_BOARD
BOOLEAN MApi_PNL_Converter_Board_Init(void);
#endif



#if ENABLE_PANEL_BIN

#define PANEL_BIN_MAX_SUPPORT_TABLE         10  // temporary

#define PANEL_BIN_HEADER_SPACE_SIZE         1

#define PANEL_BIN_HEADER_START              0
#define PANEL_BIN_HEADER_MSTAR_SIZE         18

#define PANEL_BIN_HEADER_VERSION_START      (PANEL_BIN_HEADER_START + PANEL_BIN_HEADER_MSTAR_SIZE + PANEL_BIN_HEADER_SPACE_SIZE)
#define PANEL_BIN_HEADER_SIZE_VERSION       5

#define PANEL_BIN_HEADER_TABLE_START        (PANEL_BIN_HEADER_VERSION_START + PANEL_BIN_HEADER_SIZE_VERSION + PANEL_BIN_HEADER_SPACE_SIZE)
#define PANEL_BIN_HEADER_TABLE_SIZE         2

#define PANEL_BIN_HEADER_CRC_START          (PANEL_BIN_HEADER_TABLE_START + PANEL_BIN_HEADER_TABLE_SIZE + PANEL_BIN_HEADER_SPACE_SIZE)
#define PANEL_BIN_HEADER_CRC_SIZE           4

#define PANEL_BIN_HEADER_SIZE               32

#define PANEL_BIN_TABLE_START               (PANEL_BIN_HEADER_START + PANEL_BIN_HEADER_SIZE)
#define PANEL_BIN_TABLE_SIZE                (9 * 16)

#define PANEL_BIN_PNLTBL_NAME_SIZE          32

typedef struct
{
    MS_U8  m_pPanelName[PANEL_BIN_PNLTBL_NAME_SIZE];
    MS_U8  m_bPanelDither;
    MS_U8  m_ePanelLinkType;
    MS_U8  m_bPanelDualPort;
    MS_U8  m_bPanelSwapPort;
    MS_U8  m_bPanelSwapOdd_ML;
    MS_U8  m_bPanelSwapEven_ML;
    MS_U8  m_bPanelSwapOdd_RB;
    MS_U8  m_bPanelSwapEven_RB;
    MS_U8  m_bPanelSwapLVDS_POL;
    MS_U8  m_bPanelSwapLVDS_CH;
    MS_U8  m_bPanelPDP10BIT;
    MS_U8  m_bPanelLVDS_TI_MODE;
    MS_U8  m_ucPanelDCLKDelay;
    MS_U8  m_bPanelInvDCLK;
    MS_U8  m_bPanelInvDE;
    MS_U8  m_bPanelInvHSync;
    MS_U8  m_bPanelInvVSync;
    MS_U8  m_ucPanelDCKLCurrent;
    MS_U8  m_ucPanelDECurrent;
    MS_U8  m_ucPanelODDDataCurrent;
    MS_U8  m_ucPanelEvenDataCurrent;
    MS_U8  m_bPanelOnTiming1_L;
    MS_U8  m_bPanelOnTiming1_H;
    MS_U8  m_bPanelOnTiming2_L;
    MS_U8  m_bPanelOnTiming2_H;
    MS_U8  m_bPanelOffTiming1_L;
    MS_U8  m_bPanelOffTiming1_H;
    MS_U8  m_bPanelOffTiming2_L;
    MS_U8  m_bPanelOffTiming2_H;
    MS_U8  m_ucPanelHSyncWidth;
    MS_U8  m_ucPanelHSyncBackPorch;
    MS_U8  m_ucPanelVSyncWidth;
    MS_U8  m_ucPanelVBackPorch;
    MS_U8 m_bPanelHStart_L;
    MS_U8 m_bPanelHStart_H;
    MS_U8 m_bPanelVStart_L;
    MS_U8 m_bPanelVStart_H;
    MS_U8 m_bPanelWidth_L;
    MS_U8 m_bPanelWidth_H;
    MS_U8 m_bPanelHeight_L;
    MS_U8 m_bPanelHeight_H;
    MS_U8 m_bPanelMaxHTotal_L;
    MS_U8 m_bPanelMaxHTotal_H;
    MS_U8 m_bPanelHTotal_L;
    MS_U8 m_bPanelHTotal_H;
    MS_U8 m_bPanelMinHTotal_L;
    MS_U8 m_bPanelMinHTotal_H;
    MS_U8 m_bPanelMaxVTotal_L;
    MS_U8 m_bPanelMaxVTotal_H;
    MS_U8 m_bPanelVTotal_L;
    MS_U8 m_bPanelVTotal_H;
    MS_U8 m_bPanelMinVTotal_L;
    MS_U8 m_bPanelMinVTotal_H;
    MS_U8  m_dwPanelMaxDCLK;
    MS_U8  m_dwPanelDCLK;
    MS_U8  m_dwPanelMinDCLK;
    MS_U8  m_bSpreadSpectrumStep_L;
    MS_U8  m_bSpreadSpectrumStep_H;
    MS_U8  m_bSpreadSpectrumSpan_L;
    MS_U8  m_bSpreadSpectrumSpan_H;
    MS_U8  m_ucDimmingCtl;
    MS_U8  m_ucMaxPWMVal;
    MS_U8  m_ucMinPWMVal;
    MS_U8  m_bPanelDeinterMode;
    MS_U8  m_ucPanelAspectRatio;
    MS_U8  m_bLVDSTxSwapValue_L;
    MS_U8  m_bLVDSTxSwapValue_H;
    MS_U8  m_ucTiBitMode;
    MS_U8  m_ucOutputFormatBitMode;
    MS_U8  m_bPanelSwapOdd_RG;
    MS_U8  m_bPanelSwapEven_RG;
    MS_U8  m_bPanelSwapOdd_GB;
    MS_U8  m_bPanelSwapEven_GB;
    MS_U8  m_bPanelDoubleClk;
    MS_U8  m_bPanelMaxSET_LL;
    MS_U8  m_bPanelMaxSET_LH;
    MS_U8  m_bPanelMaxSET_HL;
    MS_U8  m_bPanelMaxSET_HH;
    MS_U8  m_bPanelMinSET_LL;
    MS_U8  m_bPanelMinSET_LH;
    MS_U8  m_bPanelMinSET_HL;
    MS_U8  m_bPanelMinSET_HH;
    MS_U8  m_ucOutTimingMode;
    MS_U8  m_bPanelNoiseDith;
    MS_U8  u8PanelMaxDCLK_L;
    MS_U8  u8PanelMaxDCLK_H;
    MS_U8  u8PanelDCLK_L;
    MS_U8  u8PanelDCLK_H;
    MS_U8  u8PanelMinDCLK_L;
    MS_U8  u8PanelMinDCLK_H;
    MS_U8  enLinkExtType;
} PanelBinType;

typedef struct
{
    U8  u8PnlTblNum;

    U32 u32Version;
    U32 u32CrcChecksum;

    U8* pPanelTblParam;

    //ST_PANEL_NEW_PANELTYPE stPanelTbl;
    PanelBinType stPanelTbl;
}ST_PANEL_BIN_STRUCT;


INTERFACE BOOLEAN MApi_PanelParameter_DMA_Bin(void);
INTERFACE BOOLEAN MApi_PanelParameter_LoadTable(U8 u8PanelIndex);
INTERFACE void MApp_PanelParameter_UpdateFromFactory(void);
INTERFACE void MApp_Print_PanelBin_Variable(void);
INTERFACE U8 MApp_Get_PanelBin_TableNum(void);

#endif


////////////////////////////////////////////////////
//      need to be refined
////////////////////////////////////////////////////

#ifndef PANEL_SYNC_MODE_1
#define PANEL_SYNC_MODE_1            0
#endif

#ifndef PANEL_ANALOG_TCON
#define PANEL_ANALOG_TCON           0
#endif

#ifndef ENABLE_DPWM_FUNCTION
#define ENABLE_DPWM_FUNCTION        0
#endif

#ifndef DPWM_BURST_MODE
#define DPWM_BURST_MODE             0
#endif

#ifndef DISABLE_SHORT_FRAME_TUNE
#define DISABLE_SHORT_FRAME_TUNE    1
#endif

#ifndef DISABLE_SHORT_LINE_TUNE
#define DISABLE_SHORT_LINE_TUNE     0
#endif

#ifndef SET_SSC_SPAN
#define SET_SSC_SPAN                0x00
#endif

#ifndef SET_SSC_STEP
#define SET_SSC_STEP                0x00
#endif

#ifndef PANEL_DOT_HEIGHT
#define PANEL_DOT_HEIGHT            100
#endif

#ifndef PANEL_DOT_WIDTH
#define PANEL_DOT_WIDTH            PANEL_DOT_HEIGHT
#endif

#ifndef CRT_INTERLACE_DOUBLOUT
#define CRT_INTERLACE_DOUBLOUT  0
#endif

#define WIDE_PANEL  0
#define _4_3_PANEL  1
#define OTHER_PANEL 2
#define _5_4_PANEL  3
#define _16_9_PANEL 4

////////////////////////////////////////////////////
// Panel common constant
////////////////////////////////////////////////////
#define PANEL_PWM_BRIGHT        1

////////////////////////////////////////////////////
// Panel power sequence
////////////////////////////////////////////////////
//Truman temp
//#define pnlSetFPVCCOn()     SetPinFpVcc()
//#define pnlSetFPVCCOff()    ClrPinFpVcc()

////////////////////////////////////////////////////
// Ouput Clock PLL
////////////////////////////////////////////////////

// Output clock = XTAL * MM * ((524288 * LM * K) / (SET * A))
//  where XTAL = external XTAL frequency
//        MM = PLL divider MM, SREG D2[4:0]
//        LM = PLL divider LM, SREG D3[4:0]
//        K = PLL divider K, SREG D4[4:3]
//        SET = PLL divider SET, SREG D5, D6, D7
//        A = PLL divider A, LVDS single channel = 7
//                           LVDS dual channel = 3.5
//                           RSDS/TTL = 4

//
//  TCON setting, not every panel have it,
//  so we add redundant define here to let compile ok
//
#ifndef SET_PTC_MODE1
#define SET_PTC_MODE1           0
#endif
#ifndef SET_PTC_MODE2
#define SET_PTC_MODE2           0
#endif
#ifndef SET_PTC_MODE3
#define SET_PTC_MODE3           0
#endif
#ifndef SET_FRP_TRAN
#define SET_FRP_TRAN            0
#endif
#ifndef SET_STH_START
#define SET_STH_START           0
#endif
#ifndef SET_STH_WIDTH
#define SET_STH_WIDTH           0
#endif
#ifndef SET_OEH_START
#define SET_OEH_START           0
#endif
#ifndef SET_OEH_WIDTH
#define SET_OEH_WIDTH           0
#endif
#ifndef SET_OEV_START
#define SET_OEV_START           0
#endif
#ifndef SET_OEV_WIDTH
#define SET_OEV_WIDTH           0
#endif
#ifndef SET_CKV_START
#define SET_CKV_START           0
#endif
#ifndef SET_CKV_START2
#define SET_CKV_START2          0
#endif
#ifndef SET_CKV_WIDTH
#define SET_CKV_WIDTH           0
#endif
#ifndef SET_STV_LINE_TH
#define SET_STV_LINE_TH         0
#endif
#ifndef SET_STV_START
#define SET_STV_START           0
#endif
#ifndef SET_STV_WIDTH
#define SET_STV_WIDTH           0
#endif
#ifndef SET_OEV2_START
#define SET_OEV2_START          0
#endif
#ifndef SET_OEV3_START
#define SET_OEV3_START          0
#endif
#ifndef SET_H_ST_DLY_L
#define SET_H_ST_DLY_L          0
#endif
#ifndef SET_H_ST_DLY_H
#define SET_H_ST_DLY_H          0
#endif
#ifndef SET_CLK_DLY_SYNC_OUT
#define SET_CLK_DLY_SYNC_OUT    0
#endif
#ifndef SET_CKV_END2
#define SET_CKV_END2            0
#endif
#ifndef SET_Q1H
#define SET_Q1H                 0
#endif
#ifndef SET_OEV2_WIDTH
#define SET_OEV2_WIDTH          0
#endif
#ifndef SET_OEV3_WIDTH
#define SET_OEV3_WIDTH          0
#endif
#ifndef SET_OEV_DELTA
#define SET_OEV_DELTA           0
#endif
// Every panel must have his own PanelFineTune()
// The function will be called after mode change successfully
//extern void PanelFineTune();

#undef INTERFACE

#ifdef __cplusplus
}
#endif



//******************************************************************************

#endif // #ifndef _PANEL_H_

