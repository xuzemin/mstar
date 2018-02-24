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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_TVSETTING_H
#define MSAPI_TVSETTING_H

#include "drvMVOP.h"
#include "apiVDEC.h"
#include "apiXC.h"
#include "MApp_GlobalSettingSt.h"
#ifdef MSAPI_TVSETTING_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define TVSETTING_DEBUG 1//kk test default:0
#if TVSETTING_DEBUG
#define SHOW_TVSETTING_INFO(x)      \
{                               \
    printf("[TvSetting]");          \
    printf x;                   \
    printf("\n");               \
}
#else
#define SHOW_TVSETTING_INFO(x)
#endif


#define SHOW_TVSETTING_ERROE(x)       \
{                               \
    printf("[Error][TvSetting]");   \
    printf x;                   \
    printf("\n");               \
}


#define VCP_GetVCPFeature               0x01
#define VCP_SetVCPFeature               0x03
#define VCP_GetTimingRequest            0x07
#define VCP_SaveCurrentSetting          0x0C

#define VCP_GetVCPPage                  0xC4
#define VCP_GetPagedVCP                 0xC6
#define VCP_SetPagedVCP                 0xC8
#define VCP_CapabilitiesRequest         0xF3
#define VCP_AppTest                     0xB1

#define VCP_NewControlValue             0x02
#define VCP_ALL_Reset                   0x04
#define VCP_Bri_Con_Reset               0x05
#define VCP_Geometry_Reset              0x06
#define VCP_Color_Reset                 0x08
#define VCP_TV_Function_Reset           0x0A

#define VCP_COLOR_TEMP_INC              0x0B
#define VCP_COLOR_TEMP_REQ              0x0C

#define VCP_ADJ_Clock                   0x0E
#define VCP_ADJ_Brightness              0x10
#define VCP_ADJ_Contrast                0x12
#define VCP_Select_Color_Preset         0x14
#define VCP_ADJ_Red_Gain                0x16
#define VCP_ADJ_Green_Gain              0x18
#define VCP_ADJ_Blue_Gain               0x1A
#define VCP_Auto_Setup                  0x1E
#define VCP_ADJ_HorizontalPos           0x20
#define VCP_ADJ_VerticalPos             0x30
// for SkyHDI
#define VCP_SCALER_SET_WINDOW   0x31

#define VCP_ADJ_OSD_HorizontalPos       0x38
#define VCP_ADJ_OSD_VerticalPos         0x39
#define VCP_DefaultColorChange          0x3B

#define VCP_ADJ_Phase                   0x3E
////////////////////////////////////////////////////////
#define VCP_ATV_AUTO_SCAN                   0x51
#define VCP_ATV_MANUL_SCAN               0x52
#define VCP_ATV_SET_SCAN_STATE                  0x53
#define VCP_ATV_SET_AFC                      0x55
#define VCP_ATV_SET_FINETUNE           0x56
#define VCP_ATV_GET_TUNE_INFO   0x57
#define VCP_ADJ_TV_Set_ChannelNumber    0x58
#define VCP_ADJ_GET_PICTURE_SETTING    0x5A
#define VCP_ADJ_GET_AUDIO_SETTING      0x5B
#define VCP_ATV_MANUL_SAVE_INFO    0x5C
#define VCP_ADJ_MANUL_CHANGE_CHANNEL   0x5E
#define  VCP_GET_SCAN_STATE  0x5F
///////////////////////////////////////////////////////
#define VCP_ChangeInputSource           0x60
#define VCP_ADJ_AudioVolume             0x62
#define VCP_ADJ_Set_AudioChannel           0x63
#define VCP_ADJ_Get_AudioChannel     0x64
#define VCP_Offset_Red                  0x6C
#define VCP_Offset_Green                0x6E
#define VCP_Offset_Blue                 0x70

#define VCP_ADJ_Zoom                    0x7C
#define VCP_ADJ_EFFECT                 0x81 ///////////////////////////////////////
#define VCP_ADJ_ScalingMode             0x86
#define VCP_ADJ_Sharpness               0x87
#define VCP_ADJ_TV_Saturation           0x8A
#define VCP_ADJ_TV_Channel              0x8B
#define VCP_ADJ_TV_Sharpness            0x8C
#define VCP_ADJ_TV_Mute                 0x8D
#define VCP_ADJ_TV_Contrast             0x8E
#define VCP_ADJ_TV_Audio_Treble         0x8F
#define VCP_ADJ_TV_Hue                  0x90
#define VCP_ADJ_TV_Audio_Bass           0x91
#define VCP_ADJ_TV_Black_Level          0x92
#define VCP_ADJ_TV_Audio_Balance        0x93
#define VCP_ADJ_TV_Audio_Stereo         0x94
#define VCP_ADJ_Window_Position_TL_X    0x95
#define VCP_ADJ_Window_Position_TL_Y    0x96

#define VCP_Window_OnOff                0xA4
#define VCP_Window_Select               0xA5
#define VCP_SyncType                    0xA8
#define VCP_H_FREQ                      0xAC
#define VCP_V_FREQ                      0xAE
#define VCP_DDCCI_Settings              0xB0
#define VCP_MonitorType                 0xB6
#define VCP_Usage_Time                  0xC0
#define VCP_EnableApp                   0xCD
#define VCP_ScalerType                  0xCB
#define VCP_FW_Version                  0xC9
#define VCP_OSD_Lock                    0xCA
#define VCP_ADJ_Language                0xCC
#define VCP_PowerMode                   0xD6
#define VCP_MCCS_Version                0xDF
#define VCP_ADJ_ControlLock             0xE3
#define VCP_ADJ_PipSize                 0xEA
#define VCP_ADJ_PipPosition             0xEB
#define VCP_ADJ_ColorEnhance            0xEC
#define VCP_ADJ_Audio_Src_Select        0xED
#define VCP_Auto_Level                  0xF0
#define VCP_Resolution_Notifier         0xF6
#define VCP_Query 0xF7
#define VCP_ATV_COLORSYS   0xF8
#define VCP_ATV_SOUNDRSYS 0xF9
//====================================

#define COLOR_TEMP_INC_STEP             100
#define     MAX_DATA_CONTENT 256

///////////////////////////////////////////////////
//inputsource
///////////////////////////////////////////////////
typedef enum
{
TV_UI_INPUT_SOURCE_LAST = 0,			// keep last input source
TV_UI_INPUT_SOURCE_DTV,				// VIDEO - DTV Tuner
TV_UI_INPUT_SOURCE_ATV,				// VIDEO - TV Tuner
TV_UI_INPUT_SOURCE_AV,				// VIDEO - CVBS
TV_UI_INPUT_SOURCE_SVIDEO,			// VIDEO - Y/C
TV_UI_INPUT_SOURCE_COMPONENT,		// VIDEO - YPbPr
TV_UI_INPUT_SOURCE_RGB,				// PC - VGA
TV_UI_INPUT_SOURCE_HDMI,			// HDMI
TV_UI_INPUT_SOURCE_MPLAYER,
TV_UI_INPUT_SOURCE_RSS,
TV_UI_INPUT_SOURCE_BT,
TV_UI_INPUT_SOURCE_KTV,
TV_UI_INPUT_SOURCE_NUMS
} EN_TV_UI_INPUT_SOURCE;
///////////////////////////////////////////////////
//NR_MODE
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//power_saveing _mode
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//color_System
///////////////////////////////////////////////////
typedef enum
{
    ATV_COLOR_AUTO,
    ATV_COLOR_PAL,
    ATV_COLOR_NTSC,
    ATV_COLOR_SECAM,
    ATV_COLOR_SYSTEM_NUMS
} EN_ATV_COLOR_SYSTEM;

///////////////////////////////////////////////////
//sound_system
///////////////////////////////////////////////////
typedef enum
{
    ATV_SOUND_DK,
    ATV_SOUND_BG,
    ATV_SOUND_I,
    ATV_SOUND_MN,
    ATV_SOUND_SYSTEM_NUMS,
 } EN_ATV_SOUND_SYSTEM;
///////////////////////////////////////////////////
//Sound Setting
///////////////////////////////////////////////////
typedef enum
{
TV_AUDIO_CLASS_VOLUME,
TV_AUDIO_CLASS_TONE,
TV_AUDIO_CLASS_EFFECT,
TV_AUDIO_CLASS_NUMS
} EN_AP_AUDIO_CLASS;


typedef enum
{
TV_AUDIO_EFFECT_OFF,
TV_AUDIO_EFFECT_BBE,
TV_AUDIO_EFFECT_SRS,
TV_AUDIO_EFFECT_DOLBY,
TV_AUDIO_EFFECT_NUMS
} EN_AP_AUDIO_EFFECT;
///////////////////////////////////////////////////
//Picture_Setting
///////////////////////////////////////////////////
typedef enum
{
    TV_PICTURE_CONTRAST,//Contrast
    TV_PICTURE_BRIGHTNESS,//Brightness
    TV_PICTURE_HUE,//Hue
    TV_PICTURE_SATURATION,//Saturation
    TV_PICTURE_SHARPNESS,//Sharpness
} EN_TV_PICTURE_SETTING;

typedef enum
{
    TV_SCAN_INIT,
    TV_SCAN_PAUSE,
    TV_SCAN_END,
    TV_SCAN_STANDBY
}EN_TV_SCAN_STATE;

typedef enum
{
TV_AUDIO_CHANNEL_SPEAKER,
TV_AUDIO_CHANNEL_HEADPHONE,
TV_AUDIO_CHANNEL_MICROPHONE,
TV_AUDIO_CHANNEL_NUMS
} EN_AP_AUDIO_CHANNEL;

typedef enum
{
TV_POWER_SAVING_ACOFF,
TV_POWER_SAVING_DCOFF,
TV_POWER_SAVING_TVOFF,
TV_POWER_SAVING_DISPLAYOFF,
TV_POWER_SAVING_LIGHTOFF,
TV_POWER_SAVING_MODE_NUMS,
} EN_TV_POWER_SAVING_MODE;

typedef struct
{
     INPUT_SOURCE_TYPE_t inputsourceType;
     EN_TV_UI_INPUT_SOURCE eUIinputSource;

}Input_Source_To_TV_UI;





INTERFACE U8 GetUIInputSource(EN_TV_UI_INPUT_SOURCE enTv_inputsource );
INTERFACE void MApp_TVSetting_ChangeDataInputSource(E_DATA_INPUT_SOURCE eDataInputSource);
//INTERFACE void msAPI_TVSetting_Init(void);
//INTERFACE void msAPI_TVSetting_test(void);
INTERFACE bool msAPI_TVSetting_SendToAPPacket(U8* TVSetting);
INTERFACE void msAPI_TVSetting_Init( void );
INTERFACE bool msAPI_TVSetting_ChakraReceiveMsg (unsigned char * pu8InMsg, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize);

INTERFACE   void MApp_TVSetting_ChannelChange( BOOLEAN IsChannelPlus );
INTERFACE void msAPI_TVSetting_Adjvol(BOOLEAN IsincVol);
INTERFACE U8  MApp_TVSetting_GetSuroundFromEffect(U8 u8Effect);
INTERFACE void MApp_TVSetting_SetATVColorSystem(U8 u8colorSystem);
INTERFACE void MApp_TVSetting_SetATVSoundSystem(U8 u8SoundSystem);

INTERFACE void msAPI_Adjust_Audio_Treble(U8 Isup);
INTERFACE void msAPI_Adjust_Audio_Bass(U8 Isup);
INTERFACE void msAPI_Adjust_Audio_Balance(U8 Isup);

//INTERFACE void msAPI_TVSetting_SetAFC(U16 u16frequency);

INTERFACE U8 msAPI_TVSetting_getpercent(void);

INTERFACE void  MApp_TVSetting_Query(U8 ,U8* returnvalue);
#undef INTERFACE
#endif
