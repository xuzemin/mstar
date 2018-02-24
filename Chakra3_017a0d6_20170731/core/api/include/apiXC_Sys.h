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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file   apiXC_Sys.h
/// @brief  Scaler API layer Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_SYS_H_
#define _API_XC_SYS_H_

#ifdef _API_XC_SYS_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include "apiXC.h"
#include "drvTVEncoder.h"

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

// Turn on this option can speed up boot time
#define ENABLE_HDMI_FIRST_HDP_BEFORE_SRC_CHANGE 1

// XC HW auto set DisableInputsource when no signal
//#ifndef HW_AUTO_NO_SIGNAL
//    #define HW_AUTO_NO_SIGNAL           DISABLE
//#endif

// XC HW auto set DisableInputsource when no signal
#ifndef HW_AUTO_DISABLE_INPUTSOURCE_WHEN_NO_SIGNAL
    #define HW_AUTO_DISABLE_INPUTSOURCE_WHEN_NO_SIGNAL      DISABLE
#endif

// XC HW auto set DisableInputsource when no signal
#ifndef HW_AUTO_DISABLE_INPUTSOURCE_WHEN_HDMI_AVMUTE
    #define HW_AUTO_DISABLE_INPUTSOURCE_WHEN_HDMI_AVMUTE    DISABLE
#endif


//---------------------------------------------------------
// HPD delay
//#define HDMI_HPD_DELAY                  (700)
//#define HDMI_HPD_SOURCE_SWITCH_DELAY    (430)

#define HDMI_HPD_DELAY__HPD_LOW_TO_CLK_LOW      (100)
#define HDMI_HPD_DELAY__RESET_TO_CLK_HIGH       (300)
#define HDMI_HPD_DELAY__CLK_HIGH_TO_HPD_HIGH    (100)


//---------------------------------------------------------

#define INVALID_PQ_SRC_TYPE             (0xFFFF)

#define PC_MODE_TIMING_MONITOR_PERIOD   5   // ms

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

// 20141225: Refine this structure for reduce DB_GEN PcModeSetting size
/// PC ADC Mode setting type
typedef struct
{
    // program
    U16 u16HorizontalStart;     ///< horizontal start
    U16 u16VerticalStart;       ///< vertical start
    U16 u16HorizontalTotal;     ///< ADC horizontal total
    U16 u16Phase;               ///< ADC phase

    // from mode table
    U16 u16DefaultHStart;       ///< default horizontal start
    U16 u16DefaultVStart;       ///< default Vertical start
    U16 u16DefaultHTotal;       ///< default horizontal total

    U8 u8ModeIndex;             ///< mode index
    U8 u8Resolution;
    U8 u8SyncStatus;            ///< sync status
    U8 u8AutoSign;              ///< Already after auto tuned or not
} MS_PCADC_MODESETTING_TYPE;

INTERFACE MS_PCADC_MODESETTING_TYPE g_PcadcModeSetting[MAX_WINDOW];
INTERFACE U8 g_u8PcUserModeRamIndex[MAX_WINDOW];

// For ScreenMute
typedef enum
{
    E_SCREEN_MUTE_INIT          = 0,

    E_SCREEN_MUTE_TEMPORARY     = BIT0, // For timer
    E_SCREEN_MUTE_RATING        = BIT1,
    E_SCREEN_MUTE_FREERUN       = BIT2,
    E_SCREEN_MUTE_CHANNEL       = BIT3,
    E_SCREEN_MUTE_BLOCK         = BIT4,
    E_SCREEN_MUTE_MHEG5         = BIT5,
    E_SCREEN_MUTE_HDMI_AVMUTE   = BIT6,       ///< lock some input such as change to AV always mute
    E_SCREEN_MUTE_BY_UI         = BIT7, // For OSD/UI/User/ ATSC-InputLock

    E_SCREEN_MUTE_BY_SCALER_FPLL = BIT8, // For scaler framelock

#if( ENABLE_ATSC )
    E_SCREEN_MUTE_BY_VCHIP      = BIT9, // For VChip
#endif
#if( ENABLE_EWS )
    E_SCREEN_MUTE_BY_EWS        = BIT10, // For EWS
#endif

    E_SCREEN_MUTE_BY_VDEC       = BIT11,

#if ( ENABLE_AUDIO_ONLY_CUSTOMERMODE )
    E_SCREEN_MUTE_BY_AUDIO_ONLY = BIT12,
#endif

    E_SCREEN_MUTE_BY_MM         = BIT13,

#if ( ENABLE_FM_RADIO )
    E_SCREEN_MUTE_BY_FMRADIO = BIT14,
#endif

#if ( ENABLE_PVR )
    E_SCREEN_MUTE_BY_PVR    = BIT15,
#endif


    E_SCREEN_MUTE_BY_SET_WIN    = BIT16,
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    E_SCREEN_MUTE_BY_LIVE_PIN_EVENT    = BIT17,
    E_SCREEN_MUTE_BY_PLAYBACK_PIN_EVENT    = BIT18,
#endif
}E_SCREEN_MUTE_STATUS;

/// White Pattern Color
typedef enum
{
    TEST_COLOR_OFF,         ///< OFF
    TEST_COLOR_WHITE,       ///< White
    TEST_COLOR_RED,         ///< Red
    TEST_COLOR_GREEN,       ///< Green
    TEST_COLOR_BLUE,        ///< Blue
    TEST_COLOR_BLACK,       ///< Black
    //TEST_COLOR_PATT,
    TEST_COLOR_NUM,         ///< Color pattern Number
} EN_TEST_COLOR;

typedef enum
{
    E_VE_MUTE_INIT  = 0x00,
    E_VE_MUTE_GEN   = 0x01,        // mute VE for general purpose
    E_VE_MUTE_BLOCK = 0x02,        // mute VE for block
    E_VE_MUTE_RATING = 0x04,       // mute VE for rating
    E_VE_MUTE_CI_PLUS = 0x08,      // mute VE for CI+
    E_VE_MUTE_INVALID = 0xFF,      // Invalid VE mute state for init
}E_VE_MUTE_STATUS;

typedef enum
{
    E_XC_PQ_3D_NR_OFF,
    E_XC_PQ_3D_NR_LOW,
    E_XC_PQ_3D_NR_MID,
    E_XC_PQ_3D_NR_HIGH,
    E_XC_PQ_3D_NR_AUTO,
    E_XC_PQ_3D_NR_DEFAULT,
    E_XC_PQ_3D_NR_NUM = E_XC_PQ_3D_NR_AUTO,
}E_XC_PQ_3D_NR;


typedef enum
{
    E_DAC_RES_720x480I_60Hz = 0,
    E_DAC_RES_720x480P_60Hz,
    E_DAC_RES_720x576I_50Hz,
    E_DAC_RES_720x576P_50Hz,
    E_DAC_RES_1280x720P_50Hz,
    E_DAC_RES_1280x720P_60Hz,
    E_DAC_RES_1920x1080I_50Hz,
    E_DAC_RES_1920x1080I_60Hz,
    E_DAC_RES_1920x1080P_50Hz,
    E_DAC_RES_1920x1080P_60Hz,
}E_DAC_OUTPUT_TIMING_TYPE;



#if ENABLE_DBC

typedef enum
{
    DCR_FINETUNE_BRIGHTNESS,
    DCR_FINETUNE_CONTRAST
} EN_DCR_FINETUNE_ITEM;

  #ifndef DCR_CONTRAST_HDMI1
    #define DCR_CONTRAST_HDMI1      0x80
  #endif
  #ifndef DCR_BRIGHTNESS_HDMI1
    #define DCR_BRIGHTNESS_HDMI1    0x80
  #endif
  #ifndef DCR_CONTRAST_DTV
    #define DCR_CONTRAST_DTV        0x80
  #endif
  #ifndef DCR_BRIGHTNESS_DTV
    #define DCR_BRIGHTNESS_DTV      0x80
  #endif
  #ifndef DCR_CONTRAST_VGA
    #define DCR_CONTRAST_VGA        0x80
  #endif
  #ifndef DCR_BRIGHTNESS_VGA
    #define DCR_BRIGHTNESS_VGA      0x80
  #endif
  #ifndef DCR_CONTRAST_YPBPR
    #define DCR_CONTRAST_YPBPR      0x80
  #endif
  #ifndef DCR_BRIGHTNESS_YPBPR
    #define DCR_BRIGHTNESS_YPBPR    0x80
  #endif
  #ifndef DCR_CONTRAST_TV
    #define DCR_CONTRAST_TV         0x80
  #endif
  #ifndef DCR_BRIGHTNESS_TV
    #define DCR_BRIGHTNESS_TV       0x80
  #endif
  #ifndef DCR_CONTRAST_CVBS
    #define DCR_CONTRAST_CVBS       0x80
  #endif
  #ifndef DCR_BRIGHTNESS_CVBS
    #define DCR_BRIGHTNESS_CVBS     0x80
  #endif
  #ifndef DCR_CONTRAST_SVIDEO
    #define DCR_CONTRAST_SVIDEO     0x80
  #endif
  #ifndef DCR_BRIGHTNESS_SVIDEO
    #define DCR_BRIGHTNESS_SVIDEO   0x80
  #endif



#define DBC_MAX_VIDEO_DBC          55     // 0 ~ 255
#define DBC_MID_VIDEO_DBC          30     // 0 ~ 255
#define DBC_MIN_VIDEO_DBC          10     // 0 ~ 255
#define DBC_MAX_PWM                254    // 0 ~ 255
#define DBC_BACKLIGHT_THRES        66     // % percentage, 0 ~ 100
#define DBC_MIN_PWM                0      // 0 ~ 255
//#define DBC_Y_GAIN_H               0x40   // Hex: 0x00 ~ 0x7F, default: 0x40
#define DBC_Y_GAIN_M               0x48   // Hex: 0x00 ~ 0x7F, default: 0x40
#define DBC_Y_GAIN_L               0x50   // Hex: 0x00 ~ 0x7F, default: 0x40
//#define DBC_C_GAIN_H               0x40   // Hex: 0x00 ~ 0x7F, default: 0x40
#define DBC_C_GAIN_M               0x48   // Hex: 0x00 ~ 0x7F, default: 0x40
#define DBC_C_GAIN_L               0x50   // Hex: 0x00 ~ 0x7F, default: 0x40
#define DBC_ALPHA_BLENDING_CURRENT 60     // 0 ~ 100
#define DBC_AVG_DELTA              8      // 0 ~ 30
#define DBC_FAST_ALPHABLENDING     32     // 1 ~ 32
#define DBC_LOOP_DLY_H             4      // 0 ~ 30
#define DBC_LOOP_DLY_MH            6      // 0 ~ 30
#define DBC_LOOP_DLY_ML            2      // 0 ~ 30
#define DBC_LOOP_DLY_L             2      // 0 ~ 30

#endif

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
INTERFACE BOOLEAN g_bEnableDLC;
INTERFACE MS_U16 U16PQSrcType;



// Blue screen & screen mute
#define DEFAULT_SCREEN_UNMUTE_TIME      (400) // (200)
#define SCREEN_UNMUTE_TIME__SRC_MHL     (300)


#if (ENABLE_SW_CH_FREEZE_SCREEN)
#define DEFAULT_SCREEN_FREEZE_TIME  (1200)
INTERFACE void msAPI_Scaler_SetFreezeScreen( BOOLEAN bEnable, U16 u16ScreenUnMuteTime, SCALER_WIN eWindow);
#endif

/******************************************************************************/
///-This function will enable/diable free run screen
///@param bEnable \b IN: enable/disable blue screen
///-False: Disable
///-TRUE: Enable
///@param u8Color \b IN: the color setting
///-  0: Black
///-  1: White
///-  2: Blue
/******************************************************************************/

#define ENABLE_DEBUG_BULE_SCREEN    0

#if ENABLE_DEBUG_BULE_SCREEN
INTERFACE void msAPI_Scaler_SetBlueScreen_2( BOOLEAN bEnable, U8 u8Color, U16 u16ScreenUnmuteTime, SCALER_WIN eWindow);

#define msAPI_Scaler_SetBlueScreen(  bEnable, u8Color, u16ScreenUnmuteTime, eWindow); do {          \
  printf("\n %u:%s:%s call msAPI_Scaler_SetBlueScreen()\n", __LINE__, __FILE__, __FUNCTION__ );    \
  msAPI_Scaler_SetBlueScreen_2(  bEnable, u8Color, u16ScreenUnmuteTime, eWindow);                   \
} while(0)

#else
INTERFACE void msAPI_Scaler_SetBlueScreen( BOOLEAN bEnable, U8 u8Color, U16 u16ScreenUnmuteTime, SCALER_WIN eWindow);
#endif

U8 MApi_XC_Sys_Get_BlueScreenStatus(SCALER_WIN eWindow);

void msAPI_XC_Sys_Set_DisableInput(BOOLEAN bEnable, SCALER_WIN eWindow);

//====================================================================================

#define ENABLE_DEBUG_SCREEN_MUTE    0

INTERFACE /*E_SCREEN_MUTE_STATUS*/U32 msAPI_Scaler_GetScreenMute( SCALER_WIN eWindow);
void msAPI_Scaler_PrintMuteClient(SCALER_WIN eWindow);


#if ENABLE_DEBUG_SCREEN_MUTE
  #define msAPI_Scaler_SetScreenMute(eScreenMute, bMuteEnable, u161ms, eWindow) do {              \
    printf("\n %lu:%s ", __LINE__, __FILE__);   printf("\n >> msAPI_Scaler_SetScreenMute");     \
    printf("(0x%x, %d, %d)", eScreenMute, bMuteEnable, u161ms);                                   \
    msAPI_Scaler_SetScreenMute2(eScreenMute, bMuteEnable, u161ms, eWindow);                     \
  } while(0)

#else
  #define msAPI_Scaler_SetScreenMute(eScreenMute, bMuteEnable, u161ms, eWindow) do {            \
    msAPI_Scaler_SetScreenMute2(eScreenMute, bMuteEnable, u161ms, eWindow);                   \
  } while(0)
#endif
INTERFACE void msAPI_Scaler_SetScreenMute2(E_SCREEN_MUTE_STATUS eScreenMute, BOOLEAN bMuteEnable, U16 u161ms, SCALER_WIN eWindow);

// White Pattern
/******************************************************************************/
/// -This function will set output test pattern
/// @param enColorOfPattern \b IN: Color pattern
/// - @see EN_TEST_COLOR
/// @param enInputSourceType \b IN: Indicate what's the current input source
/// - @see INPUT_SOURCE_TYPE_t
/// @param enVideoScreen \b IN: Carry the aspect ratio info
/// - @see EN_ASPECT_RATIO_TYPE
/******************************************************************************/
INTERFACE void msAPI_Scaler_SetTestPattern(INPUT_SOURCE_TYPE_t enInputSourceType, EN_TEST_COLOR enColorOfPattern);

// Position Control
/******************************************************************************/
///-Set H position for PC mode
///@param u16Position \b IN
///- H position
/******************************************************************************/
INTERFACE void MApi_XC_Set_PC_HPosition( U16 u16HPosition , SCALER_WIN eWindow);

/******************************************************************************/
///-Set H position for PC mode
///@param u16Position \b IN
///- V position
/******************************************************************************/
INTERFACE void MApi_XC_Set_PC_VPosition( U16 u16VPosition , SCALER_WIN eWindow);

/******************************************************************************/
///-Set V position for Ypbpr mode
///@param u16PrePosition \b IN
///@param u16NewPosition \b IN
///- V position
/******************************************************************************/
INTERFACE void MApi_XC_Set_Ypbpr_VPosition(U16 u16PrePosition, U16 u16NewPosition , SCALER_WIN eWindow);

/******************************************************************************/
///-Set H position for Ypbpr mode
///@param u16PrePosition \b IN
///@param u16NewPosition \b IN
///- H position
/******************************************************************************/
INTERFACE void MApi_XC_Set_Ypbpr_HPosition(U16 u16PrePosition, U16 u16NewPosition , SCALER_WIN eWindow);

// others
INTERFACE void msAPI_Scaler_SetSourceType(INPUT_SOURCE_TYPE_t enInputSourceType , SCALER_WIN eWindow);
INTERFACE void msAPI_ScalerFront_Init(void);

INTERFACE void msAPI_Scaler_ProgAnalogInputPort(void);

#define msAPI_Scaler_GetVerticalTotal    MDrv_SC_ip_get_verticaltotal
INTERFACE U16 msAPI_Scaler_GetVerticalTotal(SCALER_WIN eWindow);

// Recommend to use below API interface for VE HW related control NOT the MDrvxxx functions in AP layer.
// The purpose is to limit the VE HW functions under the control of MACRO 'ENABLE_VE'
INTERFACE void msAPI_Scaler_SetVE(INPUT_SOURCE_TYPE_t src,E_DEST_TYPE enOutputType);
INTERFACE void msAPI_Scaler_SetCVBSMute(BOOLEAN bEn , E_VE_MUTE_STATUS eMuteStatus, INPUT_SOURCE_TYPE_t enInputPortType,E_DEST_TYPE OutputPortType);
INTERFACE MS_BOOL msAPI_Scaler_ForceVE_BlackOutPut(MS_BOOL bEnable, INPUT_SOURCE_TYPE_t src, E_DEST_TYPE enOutputType, MS_VE_VIDEOSYS VideoSystem);
INTERFACE void msAPI_Scaler_SetAFDToVEWSS(BOOLEAN bEn, U8 u8AFD, U8 u8SrcARC);

INTERFACE void msAPI_VE_SetTtxBuffer(MS_U32 u32StartAddr, MS_U32 u32Size);
INTERFACE void msAPI_VE_SetOutputCtrl(PMS_VE_Output_Ctrl pOutputCtrl);
INTERFACE void msAPI_VE_SetBlackScreen(MS_BOOL bEn);
INTERFACE MS_BOOL msAPI_VE_GetTtxReadDoneStatus(void);
INTERFACE void msAPI_VE_Exit(void);

INTERFACE void msAPI_Scaler_IPAutoCoastHandler(void);

// Source is HD/SD
INTERFACE void MApi_XC_Sys_SetSrcIsHD(MS_BOOL bIsHd, SCALER_WIN eWindow);
INTERFACE MS_BOOL MApi_XC_Sys_IsSrcHD(SCALER_WIN eWindow);

// Init
INTERFACE void  MApi_XC_Sys_Init(void);
INTERFACE void  MApi_XC_Sys_HDMI_Init(void);

//------------------------------------------------------------------------------------------
INTERFACE void MApi_XC_Sys_SetHPD( MS_BOOL bEnable, E_MUX_INPUTPORT enInputPortType );
INTERFACE void MApi_XC_Sys_Do_HPD(INPUT_SOURCE_TYPE_t enInputSourceType);
INTERFACE void MApi_XC_Sys_SetHPD_ALL( MS_BOOL bEnable);
//------------------------------------------------------------------------------------------
void MApi_XC_HPD_Do_PowerOff(void);
void MApi_XC_HPD_Do_PowerOnInit(void);
#if(!SUPPORT_HDMI_IMM_SWITCH)
void MApi_XC_HPD_Do_ExitHDMI(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE);
void MApi_XC_HPD_Do_EnterHDMI(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE);
#endif
void MApi_XC_HPD_Do_Reset(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE);
#if(ENABLE_CEC)
void MApi_XC_HPD_Do_Reset_ForCECOnOff(void);
#endif
//========================================================================================

#if( ENABLE_CEC )
    #define ENABLE_HDMI_HPD_TASK    1//0
#else
    #define ENABLE_HDMI_HPD_TASK    1
#endif

#if( ENABLE_HDMI_HPD_TASK )
typedef enum
{
    E_HPD_TASK_FOR_POWER_ON_INIT,
    E_HPD_TASK_FOR_CHANGE_SRC,
    E_HPD_TASK_FOR_EXIT_HDMI_HPD_LOW,
    E_HPD_TASK_FOR_HIGH_LOW_HIGH,

    E_HPD_TASK_FOR_LOW_TO_HIGH,
    //E_HPD_TASK_FOR_HIGH_TO_LOW, use E_HPD_TASK_FOR_EXIT_HDMI_HPD_LOW

} EnuHpdTaskMode;
void MApi_XC_HPD_Task_PowerOnInit(void);
void MApi_XC_HPD_Task_Start(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE, EnuHpdTaskMode enHpdTaskMode);
void MApi_XC_HPD_Task(void);
BOOL MApi_XC_HPD_Is_Task_Working(void);
#endif

//============================================================

INTERFACE void  MApi_XC_Sys_Periodic_Handler(SCALER_WIN eWindow, MS_BOOL bRealTimeMonitorOnly);
INTERFACE void  MApi_XC_Sys_PQ_SetNR(E_XC_PQ_3D_NR en3DNRType, SCALER_WIN eWindow);

// ACE related
INTERFACE void  MApi_XC_Sys_ACE_PatchDTGColorChecker(MS_U8 u8Mode);
#if ENABLE_PRECISE_RGBBRIGHTNESS
INTERFACE MS_U16 MApi_XC_Sys_ACE_transferRGB_Bri(MS_U16 u16Brightness, MS_U8 u8Brightnesstype);
#else
INTERFACE MS_U8 MApi_XC_Sys_ACE_transferRGB_Bri(MS_U8 u8Brightness, MS_U8 u8Brightnesstype);
#endif
INTERFACE MS_U8 MApi_XC_Sys_ACE_transfer_Bri(MS_U8 u8Brightness, MS_U8 u8Brightnesstype);

// DLC related
#if ENABLE_DBC
INTERFACE void MApi_XC_Sys_DLC_DBC_OnOff(MS_BOOL bEnable);
INTERFACE void MApi_XC_Sys_DLC_DBC_Handler(void);
INTERFACE void MApi_XC_Sys_DLC_DBC_YCGainInit(void);
#endif

// DAC related
INTERFACE void msAPI_Scaler_ChangeDacPanelType(E_DAC_OUTPUT_TIMING_TYPE eTiming);
INTERFACE void msAPI_Scaler_SetDacOutputMode(E_DAC_OUTPUT_TIMING_TYPE eTiming);
INTERFACE void msAPI_Scaler_ChangePanelType(U8 u8ResolutionType, SCALER_WIN eWindow);

//wrapper for PQ reduce BW
INTERFACE void MApi_XC_Sys_PQ_ReduceBW_ForOSD(MS_U8 PqWin, MS_BOOL bOSD_On);

typedef enum
{
    E_XC_DDC_INIT_ALL,
    E_XC_DDC_INIT_SRC_HDMI,
    E_XC_DDC_INIT_ALL_HDMI,
} EunXcInitDDCType;
INTERFACE void _MApi_XC_DDCRam_Init(EunXcInitDDCType eXcInitDDCType, U8 u8PortIndex);


void msAPI_XC_SendMailToFRC( U8 u8Cmd, U8 count, U8 p1, U8 p2, U8 p3, U8 p4, U8 p5, U8 p6, U8 p7, U8 p8);


#if 1//ENABLE_TCON
typedef enum
{
    E_PANEL_DIR_LEFT_RIGHT__UP_DOWN,
    E_PANEL_DIR_RIGHT_LEFT__UP_DOWN,
    E_PANEL_DIR_LEFT_RIGHT__DOWN_UP,
    E_PANEL_DIR_RIGHT_LEFT__DOWN_UP,
}EnuPanelDirection;
INTERFACE void MApi_XC_TCON_Panel_SetPanelDirection( EnuPanelDirection panelDirection );
#endif

void MApi_TCON_PNL_POWER_ENABLE(void);

U32 MApi_XC_Sys_Get_OutputVSyncCount(void);


#if 1//( DEBUG_XC_SYS_SYNC_STATUS )
void MApi_XC_Sys_Task(void);
#endif

void MApi_XC_PrintSyncStatus(void);

#if( CONTROL_DNR_BUF_RULE_2015 )
void MApi_XC_SetupFrameBuffer(void);
#endif

#if (ENABLE_DOLBY_BULLETIN24)
INTERFACE void MApi_XC_UpdateEDID(BOOLEAN bIsType2Edid, U8* pu8DdpSAD);
#endif

INTERFACE void MApi_XC_Sys_CheckFpllStatusTask(void);

INTERFACE U8 MApi_XC_Sys_Get_HDMIIndex(INPUT_SOURCE_TYPE_t enInputSourceType);

#if ENABLE_EDID_SWITCH
typedef enum
{
    E_USER_HDMI_EDID_1p4,
    E_USER_HDMI_EDID_2p0,
    E_USER_HDMI_EDID_AUTO,
    E_USER_HDMI_EDID_UNKNOWN,
} E_USER_HDMI_EDID_SEL;
INTERFACE E_USER_HDMI_EDID_SEL MApi_XC_Sys_Get_UserEdidSel(void);
INTERFACE E_USER_HDMI_EDID_SEL MApi_XC_Sys_Set_UserEdidSel(E_USER_HDMI_EDID_SEL eHDMI_Edid_Sel);

typedef enum
{
    XC_HDMI_EDID_1p4,
    XC_HDMI_EDID_2p0,
} EnuXcHdmiEdidSel;
INTERFACE void MApi_XC_Sys_Set_EdidSel(INPUT_SOURCE_TYPE_t enInputSourceType, EnuXcHdmiEdidSel eEdidSel );
INTERFACE void MApi_XC_Sys_Reload_Edid(INPUT_SOURCE_TYPE_t enInputSourceType, EnuXcHdmiEdidSel eEdidSel, BOOL bResetHPD);
#endif

INTERFACE void MApi_XC_Sys_CheckFrameCount(void);

INTERFACE BOOL MApi_XC_Sys_Is_SupportImmSwitch(void);
INTERFACE void MApi_XC_Sys_ResetDVIPort(INPUT_SOURCE_TYPE_t enINPUT_SOURCE_TYPE);


INTERFACE E_MUX_INPUTPORT _MApi_XC_HDMI_GetPortMapping(INPUT_SOURCE_TYPE_t eINPUT_SOURCE_TYPE);
INTERFACE void MApi_XC_Gamma_Set_Value(U8 u8Channel, U8 u8Addr, U16 u16Data );

void MApi_XC_Sys_CheckMuteStatus(void);

//BOOLEAN MApi_XC_HDMI_CheckTimingStable( SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t enInputSourceType, MS_WINDOW_TYPE *pstDEWin);

//====================================================================================
//void  MApi_XC_Mux_TriggerPathSyncEvent( INPUT_SOURCE_TYPE_t src , void* para);
#define MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(src, para)  do { \
    /*PRINT_CURRENT_LINE();  */ \
    MApi_XC_Mux_TriggerPathSyncEvent((src), (para));    \
} while(0)

//void MApi_XC_Mux_TriggerDestOnOffEvent( INPUT_SOURCE_TYPE_t src , void* para);
#define MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(src, para)    do {    \
    /*PRINT_CURRENT_LINE();  */ \
    MApi_XC_Mux_TriggerDestOnOffEvent((src), (para));    \
} while(0)

//MS_S16  MApi_XC_Mux_OnOffPeriodicHandler( INPUT_SOURCE_TYPE_t src, MS_BOOL bEnable);
#define MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(src, enable)    do {    \
    /*PRINT_CURRENT_LINE(); */  \
    MApi_XC_Mux_OnOffPeriodicHandler((src), (enable));    \
} while(0)

//====================================================================================

void MApi_XC_Sys_Init_MLoad(void);

//====================================================================================

#undef INTERFACE

#endif  // _API_XC_SYS_H_

