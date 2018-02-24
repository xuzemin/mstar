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

#ifndef MAPP_UI_MENUFUNC_ATSC_H
#define MAPP_UI_MENUFUNC_ATSC_H


#include "MApp_VChip.h"
#include "MApp_Scan_ATSC.h"
#include "MApp_Audio.h"


#ifdef MAPP_UI_MENUFUNC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define FAC_PWD_VALUE    (2580)
#define EXPERT_PWD_VALUE (1977)
#define SSC_PWD_VALUE    (9527)
#define SERVICE_PWD_VALUE (1470)

typedef enum
{
    PWD_TYPE_NONE   = 0x00,
    PWD_TYPE_FAC    = 0x01,
    PWD_TYPE_SSC    = 0x02,
    PWD_TYPE_EXPERT = 0x03,
    PWD_TYPE_SERVICE = 0x04,
} PWD_TYPE;

typedef enum
{
    ADC_AUTO_FAIL_STATUS,
    ADC_AUTO_SUCCESS_STATUS,
    ADC_AUTO_IDLE_STATUS,
} EN_ADC_AUTO_STATUS;

typedef enum
{
    MS_UART_TYPE_MIN,
    MS_UART_TYPE_HK = MS_UART_TYPE_MIN,
    MS_UART_TYPE_AEON,
    MS_UART_TYPE_VDEC,
    MS_UART_TYPE_NONE,
    MS_UART_TYPE_MAX = MS_UART_TYPE_NONE
} EN_MS_UART_TYPE;

typedef enum
{
    CAPTIONMENU_FG_COLOR_DEFAULT =0,
    CAPTIONMENU_FG_COLOR_WHITE,
    CAPTIONMENU_FG_COLOR_BLACK,
    CAPTIONMENU_FG_COLOR_RED,
    CAPTIONMENU_FG_COLOR_GREEN,
    CAPTIONMENU_FG_COLOR_BLUE,
    CAPTIONMENU_FG_COLOR_YELLOW,
    CAPTIONMENU_FG_COLOR_MAGENTA,
    CAPTIONMENU_FG_COLOR_CYAN,
    CAPTIONMENU_FG_COLOR_NUM,
} EN_CAPTIONMENU_FG_COLOR_TYPE;

typedef enum
{
    CAPTIONMENU_BG_COLOR_DEFAULT =0,
    CAPTIONMENU_BG_COLOR_BLACK,
    CAPTIONMENU_BG_COLOR_WHITE,
    CAPTIONMENU_BG_COLOR_RED,
    CAPTIONMENU_BG_COLOR_GREEN,
    CAPTIONMENU_BG_COLOR_BLUE,
    CAPTIONMENU_BG_COLOR_YELLOW,
    CAPTIONMENU_BG_COLOR_MAGENTA,
    CAPTIONMENU_BG_COLOR_CYAN,
    CAPTIONMENU_BG_COLOR_NUM,
} EN_CAPTIONMENU_BG_COLOR_TYPE;

typedef enum
{
    CAPTIONMENU_WINDOW_COLOR_DEFAULT =0,
    CAPTIONMENU_WINDOW_COLOR_WHITE,
    CAPTIONMENU_WINDOW_COLOR_BLACK,
    CAPTIONMENU_WINDOW_COLOR_RED,
    CAPTIONMENU_WINDOW_COLOR_GREEN,
    CAPTIONMENU_WINDOW_COLOR_BLUE,
    CAPTIONMENU_WINDOW_COLOR_YELLOW,
    CAPTIONMENU_WINDOW_COLOR_MAGENTA,
    CAPTIONMENU_WINDOW_COLOR_CYAN,
    CAPTIONMENU_WINDOW_COLOR_NUM,
} EN_CAPTIONMENU_WINDOW_COLOR_TYPE;

typedef enum
{
    CAPTIONMENU_FG_OPACITY_DEFAULT =0,
    CAPTIONMENU_FG_OPACITY_SOLID,
    CAPTIONMENU_FG_OPACITY_FLASHING,
    CAPTIONMENU_FG_OPACITY_TRANSLUCENT,
    CAPTIONMENU_FG_OPACITY_TRANSPARENT,
    CAPTIONMENU_FG_OPACITY_NUM,
} EN_CAPTIONMENU_FG_OPACITY_TYPE;

typedef enum
{
    CAPTIONMENU_BG_OPACITY_DEFAULT =0,
    CAPTIONMENU_BG_OPACITY_SOLID,
    CAPTIONMENU_BG_OPACITY_FLASHING,
    CAPTIONMENU_BG_OPACITY_TRANSLUCENT,
    CAPTIONMENU_BG_OPACITY_TRANSPARENT,
    CAPTIONMENU_BG_OPACITY_NUM,
} EN_CAPTIONMENU_BG_OPACITY_TYPE;

typedef enum
{
    CAPTIONMENU_WINDOW_OPACITY_DEFAULT =0,
    CAPTIONMENU_WINDOW_OPACITY_SOLID,
    CAPTIONMENU_WINDOW_OPACITY_FLASHING,
    CAPTIONMENU_WINDOW_OPACITY_TRANSLUCENT,
    CAPTIONMENU_WINDOW_OPACITY_TRANSPARENT,
    CAPTIONMENU_WINDOW_OPACITY_NUM,
} EN_CAPTIONMENU_WINDOW_OPACITY_TYPE;

typedef enum
{
    CAPTIONMENU_FONT_SIZE_DEFAULT,
    CAPTIONMENU_FONT_SIZE_NORMAL =1,
    CAPTIONMENU_FONT_SIZE_LARGE,
    CAPTIONMENU_FONT_SIZE_SMALL,
    CAPTIONMENU_FONT_SIZE_NUM,
} EN_CAPTIONMENU_FONT_SIZE;


#if (PARSING_CC_FONTEDGE)
typedef enum
{
    CAPTIONMENU_FONT_EDGESTYLE_DEFAULT =0,
    CAPTIONMENU_FONT_EDGESTYLE_NONE,
    CAPTIONMENU_FONT_EDGESTYLE_RAISED,
    CAPTIONMENU_FONT_EDGESTYLE_DEPRESSED,
    CAPTIONMENU_FONT_EDGESTYLE_UNIFORM,
    CAPTIONMENU_FONT_EDGESTYLE_LEFTDROPSHADOW,
    CAPTIONMENU_FONT_EDGESTYLE_RIGHTDROPSHADOW,
    CAPTIONMENU_FONT_EDGESTYLE_NUM,
} EN_CAPTIONMENU_FONT_EDGESTYLE;

typedef enum
{
    CAPTIONMENU_FONT_EDGECOLOR_DEFAULT =0,
    CAPTIONMENU_FONT_EDGECOLOR_BLACK,
    CAPTIONMENU_FONT_EDGECOLOR_WHITE,
    CAPTIONMENU_FONT_EDGECOLOR_RED,
    CAPTIONMENU_FONT_EDGECOLOR_GREEN,
    CAPTIONMENU_FONT_EDGECOLOR_BLUE,
    CAPTIONMENU_FONT_EDGECOLOR_YELLOW,
    CAPTIONMENU_FONT_EDGECOLOR_MAGENTA,
    CAPTIONMENU_FONT_EDGECOLOR_CYAN,
    CAPTIONMENU_FONT_EDGECOLOR_NUM,
} EN_CAPTIONMENU_FONT_EDGECOLOR;
#endif

typedef enum
{
    CAPTIONMENU_FONT_STYLE_DEFAULT =0,
    CAPTIONMENU_FONT_STYLE_0,
    CAPTIONMENU_FONT_STYLE_1,
    CAPTIONMENU_FONT_STYLE_2,
    CAPTIONMENU_FONT_STYLE_3,
    CAPTIONMENU_FONT_STYLE_4,
    CAPTIONMENU_FONT_STYLE_5,
    CAPTIONMENU_FONT_STYLE_6,
    CAPTIONMENU_FONT_STYLE_7,
    CAPTIONMENU_FONT_STYLE_NUM,
} EN_CAPTIONMENU_FONT_STYLE;

INTERFACE U16 MApp_UiMenuFunc_DecIncValue(BOOLEAN action, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step);
INTERFACE U16 MApp_UiMenuFunc_DecIncValue_Cycle(BOOLEAN action, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step);
//#if (MirrorEnable == ENABLE)
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryImageRotate(BOOLEAN action);
//#endif

// Power off
INTERFACE BOOLEAN MApp_UiMenuFunc_PowerOff(void);

// Picture Menu
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjPictureMode(BOOLEAN action);
#if (ENABLE_HDMI_4K_2K&&ENABLE_6M40_4KX2K_PROCESS)
INTERFACE void MApp_Picture_Setting_6M40_SetPictureMode (void);
#endif
INTERFACE U16 MApp_UiMenuFunc_GetPictureContrastValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPictureContrast(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustPictureContrast(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetPictureBrightnessValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPictureBrightness(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustPictureBrightness(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetPictureSharpnessValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPictureSharpness(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustPictureSharpness(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetPictureHueValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPictureHue(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustPictureHue(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetPictureColorValue(void);
#if(ATSC_READY)
INTERFACE U16 MApp_UiMenuFunc_GetColorTempVolue(EN_COLORTEMP_VALUE colorTempValue);
#endif
INTERFACE U16 MApp_UiMenuFunc_GetRColorValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetGColorValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetBColorValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPictureSaturation(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustPictureSaturation(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustOption3DNR(BOOLEAN action);

//Backlight
void MApp_UiMenuFunc_AdjustBacklightPWM(BOOLEAN bEnable);
U16 MApp_UiMenuFunc_GetPictureBacklightValue(void);


//DLC
U16 MApp_UiMenuFunc_GetDLCValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustDLC(BOOLEAN action);
//colot range
BOOLEAN MApp_UiMenuFunc_AdjustColorRange(BOOLEAN action);

//Power on mode
U16 MApp_UiMenuFunc_FactoryGetPowerOnModeValue(void);
BOOLEAN MApp_UiMenuFunc_FactoryAdjustPowerOnModeOnOff(BOOLEAN action);

//Over Scan
#if (ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION)
BOOLEAN MApp_UiMenuFunc_AdjustOverScan(void);
S16 MApp_UiMenuFunc_FactoryGetOverScanHPosValue(void);
S16 MApp_UiMenuFunc_FactoryGetOverScanHSizeValue(void);
S16 MApp_UiMenuFunc_FactoryGetOverScanVPosValue(void);
S16 MApp_UiMenuFunc_FactoryGetOverScanVSizeValue(void);
BOOLEAN MApp_UiMenuFunc_FactoryAdjustOverScanHPosValue(BOOLEAN action);
BOOLEAN MApp_UiMenuFunc_FactoryAdjustOverScanHSizeValue(BOOLEAN action);
BOOLEAN MApp_UiMenuFunc_FactoryAdjustOverScanVPosValue(BOOLEAN action);
BOOLEAN MApp_UiMenuFunc_FactoryAdjustOverScanVSizeValue(BOOLEAN action);
#endif
S8 MApp_ZUI_ACT_DecIncS8Value(BOOLEAN bInc, S8 s8Value, S8 s8MinValue, S8 s8MaxValue, U8 u8Step);

//Curve Setting
#if  ENABLE_NONLINEAR_CURVE
INTERFACE void MApp_UiMenuFunc_FactoryAdjustCurveOSD0(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustCurveOSD25(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustCurveOSD50(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustCurveOSD75(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustCurveOSD100(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustModeCurve(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustVolumeCurve(BOOLEAN action);
INTERFACE EN_MS_NONLINEAR_CURVE MApp_UiMenuFunc_FactoryGetCurveItem(void);
INTERFACE U8 MApp_UiMenuFunc_FactoryGetCurveOSD0(void);
INTERFACE U8 MApp_UiMenuFunc_FactoryGetCurveOSD25(void);
INTERFACE U8 MApp_UiMenuFunc_FactoryGetCurveOSD50(void);
INTERFACE U8 MApp_UiMenuFunc_FactoryGetCurveOSD75(void);
INTERFACE U8 MApp_UiMenuFunc_FactoryGetCurveOSD100(void);
INTERFACE void MApp_UiMenuFunc_FactorySetCurveModeDefault(void);
#endif
#if(ATSC_READY)
//Aging mode
#if  ENABLE_FACTORY_AGING_MODE
INTERFACE void AgingModMonitor(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAgingMode(BOOLEAN action);
#endif
#endif
// adc auto
INTERFACE U32 u32AgingModeTime;
//INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryADCAutoDefault(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryADCAuto(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryADCAutoValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCInputSource(BOOLEAN action);

// Audio Menu
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjAudioMode(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjAudioLanguage(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioSurroundSystem(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAVC(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetAudio150HzValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio150Hz(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetAudio500HzValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio500Hz(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetAudio1000HzValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio1000Hz(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetAudio2000HzValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio2000Hz(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetAudio4000HzValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio4000Hz(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetAudioBassValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioBass(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetAudioTrebleValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioTreble(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetAudioBalanceValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioBalance(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustDigitalAudioSelect( BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAccessibility( BOOLEAN action);
#if(ENABLE_ATSC_VIDEO_DESC)
INTERFACE BOOLEAN MApp_UiMenuFunc_SelectVideoDescription(void);
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioLanguage( BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPrimartAudioPmt( BOOLEAN action);

#if (ENABLE_UI_SPDIF_SETTING==1)
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioSPDIFMode( BOOLEAN action );
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioOnly(BOOLEAN action);

INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudioSurround(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetAudioSurroundValue(void);
#if(ATSC_READY)
#if (ENABLE_AUDIO_SURROUND_VSPK==ENABLE)
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio_VSPK_Wide(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio_VSPK_Surround(BOOLEAN action);
#endif

#if (ENABLE_AUDIO_SURROUND_SRS==ENABLE)
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio_SRS_Clarity(BOOLEAN action);
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio_SRS_TruXT(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio_SRS_TruBass(BOOLEAN action);
#endif
#if (ENABLE_AUDIO_SURROUND_BBE==ENABLE)
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustAudio_BBE_Bbe(BOOLEAN action);
#endif
#endif
#if HDMI_DVI_AUDIO_MODE_CONFIG
INTERFACE BOOLEAN MApp_UiMenuFunc_ChangeHdmiDviAudioMode(BOOLEAN action);
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjHotkeyAudioLanguage(BOOLEAN action);
#if ENABLE_3D_PROCESS
INTERFACE BOOLEAN MApp_UiMenuFunc_Adj3DType(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_Adj3DDetectMode(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_Adj3DLRMode(BOOLEAN action);
#endif
//Time menu
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeSleep(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeZone(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeDST(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeFormat(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeAutoSync(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeClockSetting(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_EnterClockSetting( void );
INTERFACE BOOLEAN MApp_UiMenuFunc_SaveClockSetting( void );
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeClockSetting_Year(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeClockSetting_Month(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeClockSetting_Day(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeClockSetting_Hour(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeClockSetting_Min(BOOLEAN action);

//WakeUp menu
INTERFACE ST_TIME g_MsDateWakeUpSetting;
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjWakeUpTimeSleep(BOOLEAN action);
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjWakeUpTimeZone(BOOLEAN action);
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjWakeUpTimeDST(BOOLEAN action);
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjWakeUpTimeFormat();
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjWakeUpTimeAutoSync(BOOLEAN action);
//INTERFACE BOOLEAN MApp_UiMenuFunc_AdjWakeUpTimeClockSetting(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_EnterWakeUpClockSetting( void );
INTERFACE BOOLEAN MApp_UiMenuFunc_SaveWakeUpClockSetting( void );
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Year(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Month(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Day(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Hour(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Min(BOOLEAN action);
#if(ATSC_READY)
#if ENABLE_SYSTEM_WAKEUP_UI
INTERFACE BOOLEAN MApp_UiMenuFunc_EnterWakeUp( void );
INTERFACE BOOLEAN MApp_UiMenuFunc_ExitWakeUp( void );
#endif
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjHotKey_SleepTimer(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjSystemLockMode(void);
#if ENABLE_UNRATED_LOCK
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjUnRatedLockMode(void);
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_GetRRT_OptionDescription(U8 u8DimensionIdx, U8 u8OptionIdx);
INTERFACE BOOLEAN MApp_UiMenuFunc_ToggleRRT_DimensionValues(U8 u8ValueIndex);
INTERFACE BOOLEAN MApp_UiMenuFunc_ResetRatingTable(void);
INTERFACE void MApp_UiMenuFunc_SaveCurrentRegion5Ratings(void);

#if 0
INTERFACE void MApp_UiMenuFunc_VChip_CompareRating(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_NONE_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_Y_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_Y7_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_G_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_ALL(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_Y7_FV(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_V(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_V(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_V(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_S(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_S(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_S(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_L(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_L(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_L(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_D(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_D(void);
#endif

// Option Menu
INTERFACE U16 MApp_UiMenuFunc_GetOptionLanguageValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustOptionLanguage(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetOptionTransparencyValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustOptionTransparency(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustOptionOsdTimeOut(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetOptionColorModeValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustOptionColorMode(BOOLEAN action);

INTERFACE U16 MApp_UiMenuFunc_GetOptionScaleModeValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustOptionScaleMode(BOOLEAN action);

INTERFACE BOOLEAN MApp_UiMenuFunc_RestoreToDefault(U16 u16KeepSetting);

INTERFACE U16 MApp_UiMenuFunc_GetPcHPosValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPcHPos(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetPcVPosValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPcVPos(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetPcClockValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPcClock(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetPcPhaseValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetPcPhaseRealValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustPcPhase(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_ExecAutoTune(void);

INTERFACE U16 MApp_UiMenuFunc_GetCCModeValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCMode(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCBasicValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCBasic(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCAdvanceValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCAdvance(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_CCGetUserCmd(void);

INTERFACE U16 MApp_UiMenuFunc_GetCCOptionModeValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCOptionMode(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCFontStyleValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCFontStyle(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCFontSizeValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCFontSize(BOOLEAN action);
#if (PARSING_CC_FONTEDGE)
INTERFACE U16 MApp_UiMenuFunc_GetCCFontEdgeStyleValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCFontEdgeStyle(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCFontEdgeColorValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCFontEdgeColor(BOOLEAN action);
#endif
INTERFACE U16 MApp_UiMenuFunc_GetCCFGColorValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCFGColor(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCBGColorValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCBGColor(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCWindowColorValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCWindowColor(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCFGOpacityValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCFGOpacity(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCBGOpacityValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCBGOpacity(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_GetCCWindowOpacityValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustCCWindowOpacity(BOOLEAN action);

// Channel Menu
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjChannelAntenna(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjChannelCableSystem(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetAutoScan(void);
//INTERFACE BOOLEAN MApp_UiMenuFunc_SetAutoScanDigital(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetAutoScanAnalog(void);
INTERFACE EN_SCAN_CHANNEL_TYPE MApp_UiMenuFunc_GetScanChannelType(void);
INTERFACE EN_TUNE2RF_SUB_STATE MApp_UiMenuFunc_GetScanSubState(void);
INTERFACE U16 MApp_UiMenuFunc_GetScanPercentageValue(void);
//INTERFACE BOOLEAN MApp_UiMenuFunc_ExecuteAutoScan(void);

INTERFACE U16 MApp_UiMenuFunc_GetScanCHNumber(void);
INTERFACE U16 MApp_UiMenuFunc_GetScanCHFound(void);
INTERFACE U16 MApp_UiMenuFunc_GetScanAnalogCHFound(void);
INTERFACE U16 MApp_UiMenuFunc_GetScanDigitalCHFound(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjChannelNO(BOOLEAN action);

INTERFACE void MApp_UiMenuFunc_ProNameEdit_GetString(U8* u8str );
INTERFACE BOOL MApp_UiMenuFunc_ProNameEdit_SetString(U8* u8str );
INTERFACE void MApp_UiMenuFunc_ProNameEditInit ( void );
INTERFACE void MApp_UiMenuFunc_ProNameEdit_AdjustChar(BOOLEAN action,U8 u8Index);
INTERFACE void MApp_UiMenuFunc_ProNameEdit_Save(void);

INTERFACE BOOLEAN MApp_UiMenuFunc_ShowHide(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_Favorite(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FavList(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_MainList(void);

// Input Source switch function
INTERFACE BOOLEAN MApp_UiMenuFunc_InputSourceSwitch(E_UI_INPUT_SOURCE selectinputSource);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputSource(BOOLEAN action);

// Runtime Status Menu function
INTERFACE U8 g_u8RuntimeStatusPasswordCount;
// Factory Menu function
INTERFACE PWD_TYPE MApp_UiMenuFunc_CalFactoryPassword(U8 u8KeyNumber);
INTERFACE U16 MApp_UiMenuFunc_GetADCRedGainValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetADCGreenGainValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetADCBlueGainValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetADCRedOffsetValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetADCGreenOffsetValue(void);
INTERFACE U16 MApp_UiMenuFunc_GetADCBlueOffsetValue(void);

INTERFACE BOOLEAN MApp_UiMenuFunc_ADCAutoWhiteBalance(BOOLEAN factorymode);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCRedGain(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCGreenGain(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCBlueGain(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCRedOffset(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCGreenOffset(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustADCBlueOffset(BOOLEAN action);

// Audio Volume Control
INTERFACE U16 MApp_UiMenuFunc_GetAudioVolumeValue(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AudioVolumeConfig(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AudioVolumeInit(void);

// Program number string
INTERFACE void MApp_UiMenuFunc_ConvertProgramNumber2Str (MS_VIRTUAL_CHANNEL_NUM *pstVirtualChNum, U8 *pu8Str);
INTERFACE void MApp_UiMenuFunc_ConvertTempChannelProgramNumber2Str (MS_VIRTUAL_CHANNEL_NUM *pstVirtualChNum, U8 *pu8Str);

INTERFACE BOOLEAN MApp_UiMenuFunc_EventInfoSignalUpdate(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_IsCCEnable(void);

INTERFACE BOOLEAN MApp_UiMenuFunc_CheckInputLock(void);

// Factory Setting Functions..................
#if ENABLE_INPUT_LOCK
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockTV(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockAV(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockSV(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockYPbPr(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockSCART(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockHDMI(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustInputLockPC(void);
#endif

INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustDebugMode(BOOLEAN action);
INTERFACE void MApp_UiMenuFunc_FactoryAdjustBurningMode(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustWhitePattern(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryInitMaceColorMode(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustMaceColorMode(BOOLEAN action);
#if(ATSC_READY)
#ifdef USE_USER_COLOR_TEMPETURE
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustColorTempRed(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustColorTempGreen(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_AdjustColorTempBlue(BOOLEAN action);
#endif
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustColorTempRedGain(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustColorTempGreenGain(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustColorTempBlueGain(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustColorTempRedOffset(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustColorTempGreenOffset(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustColorTempBlueOffset(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjPictureMode(BOOLEAN action);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryInitPictureMode(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactorySaveSettings(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryRestoreToDefault(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryShipmentSetting(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryAdjustDLCOnOff(BOOLEAN action);

#if 0//ENABLE_SSC
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustMIUSscEnable( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustMIUSscSpan( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustMIUSscStep( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustLVDSSscEnable( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustLVDSSscSpan( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustLVDSSscStep( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustMIUSscSpanByHz( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustMIUSscStepByPercentage( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustLVDSSscSpanByHz( BOOLEAN action );
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryMenu_AdjustLVDSSscStepByPercentage( BOOLEAN action );
#endif

INTERFACE void MApp_ReturnResolution(U8 *strBuffer);
INTERFACE BOOLEAN MApp_UiMenuFunc_SetAudio_Language(U8 u8Index);


INTERFACE U32 MApp_UiMenuFunc_GetOsdTimeOut(void);

#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
INTERFACE void MApp_UiMenuFunc_EnterAudioOnlyMode( void );
INTERFACE void MApp_UiMenuFunc_ExitAudioOnlyMode( void );
#endif
#if EN_INPUT_LABEL_EDIT
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_Saving(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_Presents_Init(void);

INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_SetCustomLabel(U8* tempStr);
INTERFACE void MApp_UiMenuFunc_InputLabel_GetCustomLabel(U8* tempStr);
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_AdjustChar(BOOLEAN action,U8 u8Index);

INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_AdjPresentType(BOOLEAN action);
INTERFACE EN_INPUT_LABEL_PRESENT_TYPE MApp_UiMenuFunc_InputLabel_GetPresentType(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_Init (E_UI_INPUT_SOURCE UIInputSourceType);
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_Restore(void);
#if ENABLE_CEC
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_CEC_Restore(E_UI_INPUT_SOURCE UIInputSourceType);
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_SetInputSource(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_InputLabel_AdjInputSource(BOOLEAN action);
INTERFACE E_UI_INPUT_SOURCE MApp_UiMenuFunc_InputLabel_GetInputSource(void);
#endif
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryDemodInfo(void);
INTERFACE BOOLEAN MApp_UiMenuFunc_FactoryTunerCW_Test(BOOLEAN action);
INTERFACE U16 MApp_UiMenuFunc_DecIncATSCLanguage_Cycle(BOOLEAN action, U16 u16Value);

INTERFACE U16 g_u16FactoryPassword;
INTERFACE U8 g_u8FactoryPasswordCount;
INTERFACE U8 g_u8UiWakeUpOnOffFlag;
INTERFACE U8 g_u8UiWakeUpTime[2];
#if ENABLE_ATSC_TTS
INTERFACE void MApp_UiMenuFunc_SetTTSVolume(U8 u8Volume);
INTERFACE void MApp_UiMenuFunc_SetTTSPitch(U8 u8Pitch);
INTERFACE void MApp_UiMenuFunc_SetTTSSpeed(U8 u8Speed);
#endif

#ifndef CHAN_NUM_SEPERATOR
#define CHAN_NUM_SEPERATOR CHAR_DOT//CHAR_MINUS
#endif

#undef INTERFACE
#endif
