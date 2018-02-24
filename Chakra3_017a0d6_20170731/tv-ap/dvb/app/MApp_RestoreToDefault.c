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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_RESTORETODEFAULT_C

//*************************************************************************
//              Include files
//*************************************************************************
#include <string.h>

#include "Board.h"
#include "MsTypes.h"
#include "Panel.h"
#include "datatype.h"
#include "apiXC.h"

#include "DemoFineTune.h"
#include "QualityEx_Default.h"

#include "drvPQ.h"
#include "drvpower_if.h"
#include "apiGOP.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Ace.h"
#include "apiXC_Auto.h"
#if ENABLE_DBC
#include "apiXC_Sys.h"
#endif

#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_Flash.h"
#include "msAPI_Mode.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_audio.h"

#if(ENABLE_CEC)
#include "msAPI_CEC.h"
#endif

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_Scaler.h"
#include "MApp_DataBase.h"
#include "MApp_Scan.h"
#include "MApp_InputSource.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_ATVProc.h"
#include "MApp_UiMenuDef.h"
#include "MApp_SaveData.h"
#include "MApp_Audio.h"

#if (ENABLE_EWS)
#include "MApp_EWS.h"
#endif


#if ENABLE_PVR
#include "MApp_UiPvr.h"
#endif

#if ENABLE_CI
#include "msAPI_CI.h"
#endif
#if ENABLE_VD_PACH_IN_CHINA
#include "drvVIFInitial_MST.h"
#include "msAPI_VD.h"
#endif
#include "msAPI_FreqTableDTV.h"
#if ENABLE_OAD
#include "MApp_OAD.h"
#endif
#if(ENABLE_PIP)
#include "MApp_PIP.h"
#endif
#if(ENABLE_ATSC)
    #include "msAPI_Timer.h"
    #include "MApp_VChip.h"
#endif
#include "MApp_Main.h"

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#endif

#if ENABLE_FM_RADIO
#include "MApp_Radio.h"
#endif

//*************************************************************************
//              Local Definition
//*************************************************************************
#define DYNAMIC_BACKLIGHT           100
#define DYNAMIC_CONTRAST            60
#define DYNAMIC_BRIGHTNESS          55
#define DYNAMIC_SATURATION          60
#define DYNAMIC_SHARPNESS           60
#define DYNAMIC_HUE                 50
#define DYNAMIC_COLOR_TEMP  MS_COLOR_TEMP_MEDIUM

#define STANDARD_CONTRAST           50
#define STANDARD_BRIGHTNESS         50//48
#define STANDARD_SATURATION         50
#define STANDARD_SHARPNESS          50
#define STANDARD_HUE                50
#define STANDARD_COLOR_TEMP MS_COLOR_TEMP_MEDIUM
//HDMI STANARD
#define STANDARD_HDMI_BACKLIGHT     100
#define STANDARD_HDMI_CONTRAST      50
#define STANDARD_HDMI_BRIGHTNESS    50//48
#define STANDARD_HDMI_SATURATION    50//48
#define STANDARD_HDMI_SHARPNESS    50
#define STANDARD_HDMI_HUE           50
#define STANDARD_COLOR_HDMI_TEMP MS_COLOR_TEMP_MEDIUM
//AV STANDARD
#define STANDARD_AV_BACKLIGHT       100
#define STANDARD_AV_CONTRAST        50
#define STANDARD_AV_BRIGHTNESS      50//48
#define STANDARD_AV_SATURATION      50//48
#define STANDARD_AV_SHARPNESS       50
#define STANDARD_AV_HUE             50
#define STANDARD_COLOR_AV_TEMP MS_COLOR_TEMP_MEDIUM
//YPBPR STANDARD
#define STANDARD_YPBPR_BACKLIGHT    100
#define STANDARD_YPBPR_CONTRAST     50
#define STANDARD_YPBPR_BRIGHTNESS   50//48
#define STANDARD_YPBPR_SATURATION   50
#define STANDARD_YPBPR_SHARPNESS    50
#define STANDARD_YPBPR_HUE          50
#define STANDARD_COLOR_YPBPR_TEMP MS_COLOR_TEMP_MEDIUM
//ATV PAL STANDARD
#define STANDARD_ATV_BACKLIGHT      100
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)        // GEM_SYNC_0815
#define STANDARD_ATV_CONTRAST       82//PQ for Gemini
#define STANDARD_ATV_BRIGHTNESS     50//48//PQ for Gemini
#define STANDARD_ATV_SATURATION     55//PQ for Gemini
#else
#define STANDARD_ATV_CONTRAST       50
#define STANDARD_ATV_BRIGHTNESS     50//48
#define STANDARD_ATV_SATURATION     50
#endif
#define STANDARD_ATV_SHARPNESS      50
#define STANDARD_ATV_HUE            50
#define STANDARD_COLOR_ATV_TEMP MS_COLOR_TEMP_MEDIUM
//SV STANDARD
#define STANDARD_SV_BACKLIGHT       100
#define STANDARD_SV_CONTRAST        50
#define STANDARD_SV_BRIGHTNESS      50//48
#define STANDARD_SV_SATURATION      50
#define STANDARD_SV_SHARPNESS       50
#define STANDARD_SV_HUE             50
#define STANDARD_COLOR_SV_TEMP MS_COLOR_TEMP_MEDIUM

#define MILD_BACKLIGHT              100
#define MILD_CONTRAST               45
#define MILD_BRIGHTNESS             45
#define MILD_SATURATION             45
#define MILD_SHARPNESS              50
#define MILD_HUE                    50
#define MILD_COLOR_TEMP     MS_COLOR_TEMP_MEDIUM//XX_COLOR_TEMP_WARM


//*************************************************************************
//              Local variables
//*************************************************************************
#define USE_CUS_DEFAULT_ADC FALSE
#if USE_CUS_DEFAULT_ADC
static code APIXC_AdcGainOffsetSetting tADCSetting[ADC_SET_NUMS] =
{
    {
         INIT_ADC_RGB_RED_GAIN,
         INIT_ADC_RGB_GREEN_GAIN,
         INIT_ADC_RGB_BLUE_GAIN,

         INIT_ADC_RGB_RED_OFFSET,
         INIT_ADC_RGB_GREEN_OFFSET,
         INIT_ADC_RGB_BLUE_OFFSET,
    }, // VGA

    {
        INIT_ADC_YPBPR_RED_GAIN_SD,
        INIT_ADC_YPBPR_GREEN_GAIN_SD,
        INIT_ADC_YPBPR_BLUE_GAIN_SD,

        INIT_ADC_YPBPR_RED_OFFSET,
        INIT_ADC_YPBPR_GREEN_OFFSET,
        INIT_ADC_YPBPR_BLUE_OFFSET,

    }, // YPBPR_SD

    {
        INIT_ADC_YPBPR_RED_GAIN_HD,
        INIT_ADC_YPBPR_GREEN_GAIN_HD,
        INIT_ADC_YPBPR_BLUE_GAIN_HD,

        INIT_ADC_YPBPR_RED_OFFSET,
        INIT_ADC_YPBPR_GREEN_OFFSET,
        INIT_ADC_YPBPR_BLUE_OFFSET,

    }, // YPBPR_HD
    {
         INIT_ADC_RGB_RED_GAIN,
         INIT_ADC_RGB_GREEN_GAIN,
         INIT_ADC_RGB_BLUE_GAIN,

         INIT_ADC_RGB_RED_OFFSET,
         INIT_ADC_RGB_GREEN_OFFSET,
         INIT_ADC_RGB_BLUE_OFFSET,
    }, // SCART
};
#endif

//////////////////////////////////////////////////////////////////////////////////////////
// Default Sound Mode Setting
///////////////////////////////////////////////////////////////////////////////////////////
static code stSoundModeSeting astDefaultSoundModeSeting[EN_SoundMode_Num] =
{
    /*
         To use simple sound mode setting, let SIMPLE_EQ_SETTING = 1.
         Simple sound mode setting can only set bass & treble.
    */
    #define SIMPLE_EQ_SETTING 1

    //bass,treble,u8120HZ,u8200HZ,u8500HZ,u8_1_dot_2_KHZ,u8_3KHZ,u8_7_dot_5_KHZ,u812KHZ,Usermode

    //Standard,
    {50,
      50,
      SOUND_MODE_STANDARD_BAND1,
      SOUND_MODE_STANDARD_BAND2,
      SOUND_MODE_STANDARD_BAND3,
      SOUND_MODE_STANDARD_BAND4,
      SOUND_MODE_STANDARD_BAND5,
     // SOUND_MODE_STANDARD_BAND6,
     // SOUND_MODE_STANDARD_BAND7,
      FALSE, 0, AUD_MODE_LR
    },
    //Music
    {75,
      75,
      #if (SIMPLE_EQ_SETTING == 0)
      SOUND_MODE_MUSIC_BAND1,
      SOUND_MODE_MUSIC_BAND2,
      SOUND_MODE_MUSIC_BAND3,
      SOUND_MODE_MUSIC_BAND4,
      SOUND_MODE_MUSIC_BAND5,
      //SOUND_MODE_MUSIC_BAND6,
      //SOUND_MODE_MUSIC_BAND7,
      FALSE, 0, AUD_MODE_LR
      #else
      SOUND_MODE_STANDARD_BAND1,
      SOUND_MODE_STANDARD_BAND2,
      SOUND_MODE_STANDARD_BAND3,
      SOUND_MODE_STANDARD_BAND4,
      SOUND_MODE_STANDARD_BAND5,
     // SOUND_MODE_STANDARD_BAND6,
     // SOUND_MODE_STANDARD_BAND7,
      FALSE, 0, AUD_MODE_LR
      #endif
     },
     //Move
    {80, //90,
      75,
      #if SIMPLE_EQ_SETTING == 0
      SOUND_MODE_MOVIE_BAND1,
      SOUND_MODE_MOVIE_BAND2,
      SOUND_MODE_MOVIE_BAND3,
      SOUND_MODE_MOVIE_BAND4,
      SOUND_MODE_MOVIE_BAND5,
     // SOUND_MODE_MOVIE_BAND6,
      //SOUND_MODE_MOVIE_BAND7,
      FALSE, 0, AUD_MODE_LR
      #else
      SOUND_MODE_STANDARD_BAND1,
      SOUND_MODE_STANDARD_BAND2,
      SOUND_MODE_STANDARD_BAND3,
      SOUND_MODE_STANDARD_BAND4,
      SOUND_MODE_STANDARD_BAND5,
     // SOUND_MODE_STANDARD_BAND6,
     // SOUND_MODE_STANDARD_BAND7,
      FALSE, 0, AUD_MODE_LR
      #endif

    },
    //Sports
    {35,
      35,
      #if SIMPLE_EQ_SETTING == 0
      SOUND_MODE_SPORTS_BAND1,
      SOUND_MODE_SPORTS_BAND2,
      SOUND_MODE_SPORTS_BAND3,
      SOUND_MODE_SPORTS_BAND4,
      SOUND_MODE_SPORTS_BAND5,
     // SOUND_MODE_SPORTS_BAND6,
     // SOUND_MODE_SPORTS_BAND7,
      FALSE, 0, AUD_MODE_LR
      #else
      SOUND_MODE_STANDARD_BAND1,
      SOUND_MODE_STANDARD_BAND2,
      SOUND_MODE_STANDARD_BAND3,
      SOUND_MODE_STANDARD_BAND4,
      SOUND_MODE_STANDARD_BAND5,
     // SOUND_MODE_STANDARD_BAND6,
     // SOUND_MODE_STANDARD_BAND7,
      FALSE, 0, AUD_MODE_LR
      #endif
      },
      //User
      {50,
      50,
      SOUND_MODE_STANDARD_BAND1,
      SOUND_MODE_STANDARD_BAND2,
      SOUND_MODE_STANDARD_BAND3,
      SOUND_MODE_STANDARD_BAND4,
      SOUND_MODE_STANDARD_BAND5,
     // SOUND_MODE_STANDARD_BAND6,
     // SOUND_MODE_STANDARD_BAND7,
      FALSE, 0, AUD_MODE_LR
      },
};

//////////////////////////////////////////////////////////////////////////////////////////
// Default Time Data
///////////////////////////////////////////////////////////////////////////////////////////
static code MS_TIME stDefaultTimeData =
{
    0, //wTimeDataCS;

    DEFAULT_D_ONTIME_CH,//cOnTimerChannel;
    0,//u16OffTimer_Info_Hour;
    0,//u16OffTimer_Info_Min;
    12,//u16OnTimer_Info_Hour;
    0,//u32ElapsedTimeCnt++;
    0, // s32Offset_Time
#if ENABLE_ISDBT_NO_DVB
    TIMEZONE_BRASILIA,
    EN_Clock_TimeZone_18,
#else
    TIMEZONE_CANARY,
    EN_Clock_TimeZone_24,
#endif
    EN_ClockMode_Auto,
    EN_Time_OffTimer_Off,
    EN_Time_OnTimer_Off,



#if ENABLE_ATSC
    EN_Time_OnTimer_Source_ATSC,
#elif ENABLE_DVBT
    EN_Time_OnTimer_Source_DVBT,

#elif ENABLE_DVBC
    EN_Time_OnTimer_Source_DVBC,

#elif ENABLE_DVBS
    EN_Time_OnTimer_Source_S2,

#elif ENABLE_DTMB
    EN_Time_OnTimer_Source_DTMB,

#elif ENABLE_ISDBT
    EN_Time_OnTimer_Source_ISDBT,
  #else
    EN_Time_OnTimer_Source_ATV,
  #endif

    EN_Time_AutoOff_Off,
    STATE_AUTOSLEEP_NEVER,
    30,//cOnTimerVolume;
    0, //u16OnTimer_Info_Min;
    0, //NVRAM_g_u8TimeInfo_Flag
};

//This value will be set depend on UI initial value. It is not related with picture quality.
//This value will be set depend on UI initial value. It is not related with picture quality.
static T_MS_VIDEO code astDefaultVideoDataTbl[DATA_INPUT_SOURCE_NUM] =
{
#if ENABLE_DTV
    {// DTV
        0,//CS
        PICTURE_NORMAL, // default Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },

        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
    {// ATV
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_ATV_BACKLIGHT,
                STANDARD_ATV_CONTRAST,
                STANDARD_ATV_BRIGHTNESS,
                STANDARD_ATV_SATURATION,
                STANDARD_ATV_SHARPNESS,
                STANDARD_ATV_HUE,
                STANDARD_COLOR_ATV_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },

        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9

    },
#if (INPUT_AV_VIDEO_COUNT >= 1)
    {// VIDEO
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
             STANDARD_AV_BACKLIGHT,
                STANDARD_AV_CONTRAST,
                STANDARD_AV_BRIGHTNESS,
                STANDARD_AV_SATURATION,
                STANDARD_AV_SHARPNESS,
                STANDARD_AV_HUE,
                STANDARD_COLOR_AV_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 2)
    {// VIDEO2
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 3)
    {// VIDEO3
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 1)
    {// YPBPR
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_YPBPR_BACKLIGHT,
                STANDARD_YPBPR_CONTRAST,
                STANDARD_YPBPR_BRIGHTNESS,
                STANDARD_YPBPR_SATURATION,
                STANDARD_YPBPR_SHARPNESS,
                STANDARD_YPBPR_HUE,
                STANDARD_COLOR_YPBPR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    {// YPBPR
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode

            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
    {// RGB
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,  
                STANDARD_BRIGHTNESS, 
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9 //EN_AspectRatio_16X9,
    },
#if (INPUT_HDMI_VIDEO_COUNT > 0)
    {// HDMI1
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
             STANDARD_HDMI_BACKLIGHT,
                STANDARD_HDMI_CONTRAST+1,  //wht140604_1
                STANDARD_HDMI_BRIGHTNESS+3,//wht140604_1
                STANDARD_HDMI_SATURATION,
                STANDARD_HDMI_SHARPNESS,
                STANDARD_HDMI_HUE,
                STANDARD_COLOR_HDMI_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST+1, //wht140604_1
                STANDARD_BRIGHTNESS+3,//wht140604_1
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    {// HDMI2
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    {// HDMI3
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    {// HDMI4
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    {// SCART
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_SCART_VIDEO_COUNT >= 2)
    {// SCART2
        0,//CS
        PICTURE_NORMAL, // Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_SV_VIDEO_COUNT >= 1)
    {// S-VIDEO
        0,//CS
        PICTURE_NORMAL,// Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
          STANDARD_SV_BACKLIGHT,
             STANDARD_SV_CONTRAST,
             STANDARD_SV_BRIGHTNESS ,
             STANDARD_SV_SATURATION ,
             STANDARD_SV_SHARPNESS    ,
             STANDARD_SV_HUE   ,
             STANDARD_COLOR_SV_TEMP ,
             0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if (INPUT_SV_VIDEO_COUNT >= 2)
    {// S-VIDEO2
        0,//CS
        PICTURE_NORMAL,// Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },
        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9
    },
#endif
#if ENABLE_DMP
    {// Storage
        0,//CS
        PICTURE_NORMAL, // default Picture mode
        {
            {//Dynamic
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Standard
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//Mild
                MILD_BACKLIGHT,
                MILD_CONTRAST,
                MILD_BRIGHTNESS,
                MILD_SATURATION,
                MILD_SHARPNESS,
                MILD_HUE,
                MILD_COLOR_TEMP,
                0, //PicUserMode
            },
            {//USER
                STANDARD_BACKLIGHT,
                STANDARD_CONTRAST,
                STANDARD_BRIGHTNESS,
                STANDARD_SATURATION,
                STANDARD_SHARPNESS,
                STANDARD_HUE,
                STANDARD_COLOR_TEMP,
                0, //PicUserMode
            },
            #if PICTURE_USER_2
            {//USER2
                DYNAMIC_BACKLIGHT,
                DYNAMIC_CONTRAST,
                DYNAMIC_BRIGHTNESS,
                DYNAMIC_SATURATION,
                DYNAMIC_SHARPNESS,
                DYNAMIC_HUE,
                DYNAMIC_COLOR_TEMP,
                0, //PicUserMode
            },
            #endif
        },
        {
            MS_NR_MIDDLE,//MS_NR_AUTO,
            MS_MPEG_NR_LOW,
        },

        MS_BLACK_LEVEL_HIGH,
        EN_AspectRatio_16X9

    },
#endif
};

static T_MS_WHITEBALANCE code astDefaultWhiteBalanceDataTbl[DATA_INPUT_SOURCE_NUM] =
{
#if ENABLE_DTV
    {// DTV
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
    {// ATV
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#if (INPUT_AV_VIDEO_COUNT >= 1)
    {// VIDEO
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 2)
    {// VIDEO2
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 3)
    {// VIDEO3
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 1)
    {// YPBPR
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT == 2)
    {// YPBPR2
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif

    {// RGB
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },

#if (INPUT_HDMI_VIDEO_COUNT > 0)
    {// HDMI1
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    {// HDMI2
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    {// HDMI3
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    {// HDMI4
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_SCART_VIDEO_COUNT >= 1)
    {// SCART0
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_SCART_VIDEO_COUNT >= 2)
    {// SCART2
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_SV_VIDEO_COUNT >= 1)
    {// S-VIDEO
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if (INPUT_SV_VIDEO_COUNT >= 2)
    {// S-VIDEO2
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
#if ENABLE_DMP
    {// Storage
        0,//CS
        {
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_COOL_B,

                INIT_VIDEO_COLOR_TEMP_COOL_R,
                INIT_VIDEO_COLOR_TEMP_COOL_G,
                INIT_VIDEO_COLOR_TEMP_COOL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_NORMAL_B,

                INIT_VIDEO_COLOR_TEMP_NORMAL_R,
                INIT_VIDEO_COLOR_TEMP_NORMAL_G,
                INIT_VIDEO_COLOR_TEMP_NORMAL_B,

                0x32,
                0x32,
                0x32,
            },
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_WARM_B,

                INIT_VIDEO_COLOR_TEMP_WARM_R,
                INIT_VIDEO_COLOR_TEMP_WARM_G,
                INIT_VIDEO_COLOR_TEMP_WARM_B,

                0x32,
                0x32,
                0x32,
            },
        #if (MS_COLOR_TEMP_COUNT == 4)
            {
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
                INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

                INIT_VIDEO_COLOR_TEMP_USER_R,
                INIT_VIDEO_COLOR_TEMP_USER_G,
                INIT_VIDEO_COLOR_TEMP_USER_B,

                0x32,
                0x32,
                0x32,
            },
        #endif
        }
    },
#endif
};

#define INIT_SUB_BRIGHTNESS_DATA_DTV    128
#define INIT_SUB_CONTRAST_DATA_DTV      128

static T_MS_SUB_COLOR code astDefaultSubBriConTbl[DATA_INPUT_SOURCE_NUM] =
{
#if ENABLE_DTV
    {//DTV
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
    {//ATV
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#if (INPUT_AV_VIDEO_COUNT >= 1)
    {//AV
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 2)
    {//AV2
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_AV_VIDEO_COUNT >= 3)
    {//AV3
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 1)
    {//COMPONENT
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    {//COMPONENT2
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
    {//RGB
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },

#if (INPUT_HDMI_VIDEO_COUNT > 0)

    {//HDMI1
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    {//HDMI2
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    {//HDMI3
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    {//HDMI4
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    {//SCART
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 2)
    {//SCART2
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif

#if (INPUT_SV_VIDEO_COUNT >= 1)
    {//SVIDEO
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif

#if (INPUT_SV_VIDEO_COUNT >= 2)
    {//SVIDEO2
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif

#if ENABLE_DMP
    {//DTV
        0,  //u16SubColorDataCS;
        INIT_SUB_BRIGHTNESS_DATA_DTV,
        INIT_SUB_CONTRAST_DATA_DTV,
    },
#endif
};

#if (ENABLE_NONLINEAR_CURVE)
static code MS_NONLINEAR_CURVE_SETTING tNonLinearCurveSetting =
{
    0,       // check sum

#if(ENABLE_PICTURE_NONLINEAR_CURVE)
//NONLINEAR_CURVE_CONTRAST,
//NONLINEAR_CURVE_BRIGHTNESS,
//NONLINEAR_CURVE_SATURATION,
//NONLINEAR_CURVE_SHARPNESS,
//NONLINEAR_CURVE_HUE,
//NONLINEAR_CURVE_BACKLIGHT,
#if ENABLE_DTV
    // DTV
    {
        {80, 104, 128, 192, 255},   // Contrast
        {80, 104, 128, 153, 178},   // Brightness
        {0, 79, 158, 206, 255},   // Color
        {0, 13, 26, 44, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
#endif
    // TV
    {
        {80, 105, 130, 192, 255},   // Contrast
        {80, 103, 126, 152, 178},   // Brightness
        {0, 75, 158, 202, 255},   // Color
        {0, 12, 24, 43, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
    // AV
    {
        {80, 105, 129, 192, 255},   // Contrast
        {80, 103, 127, 152, 178},   // Brightness
        {0, 72, 160, 202, 255},   // Color
        {0, 12, 24, 43, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
    // SV
    {
        {80, 105, 129, 192, 255},   // Contrast
        {80, 103, 127, 152, 178},   // Brightness
        {0, 75, 150, 202, 255},   // Color
        {0, 12, 24, 43, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
    // YPbPr
    {
        {80, 104, 128, 192, 255},   // Contrast
        {80, 104, 128, 153, 178},   // Brightness
        {0, 79, 165, 206, 255},   // Color
        {0, 13, 26, 44, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
    // HDMI
    {
         {80, 104, 128, 192, 255},   // Contrast
        {80, 104, 128, 153, 178},   // Brightness
        {0, 79, 165, 206, 255},   // Color
        {0, 13, 26, 44, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
    // PC
    {
        {80, 104, 128, 192, 255},   // Contrast
        {80, 104, 128, 153, 178},   // Brightness
        {0, 70, 148, 197, 255},   // Color
        {0, 10, 20, 41, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},  //Backlight
    },
    // Storage
    {
        {80, 104, 128, 192, 255},   // Contrast
        {80, 104, 128, 153, 178},   // Brightness
        {0, 79, 158, 206, 255},   // Color
        {0, 13, 26, 44, 63},   // Sharpness
        {0, 25, 50, 75, 100},   // Tint
        {0, 25, 50, 75, 100},   //Backlight
    },
#endif

#if(ENABLE_SOUND_NONLINEAR_CURVE)
#if ENABLE_DTV
    // DTV
    {0, 25, 50, 75, 100},   // Volume
#endif
    // TV
    {0, 25, 50, 75, 100},   // Volume
    // AV
    {0, 25, 50, 75, 100},   // Volume
    // Storage
    {0, 25, 50, 75, 100},   // Volume
#endif
};
#endif


//*************************************************************************
//              Functions
//*************************************************************************

#if(ENABLE_ISDBT_AND_DVB)
EN_OSD_COUNTRY_SETTING MApp_DataBase_Get_Default_Country(void)
{
    if( IS_COUNTRY_USE_SBTVD() )
    {
        return OSD_COUNTRY_BRAZIL;
    }
    else
    {
        return OSD_COUNTRY_UK;
    }
}
#endif

void MApp_DataBase_RestoreDefault_By_Country(EN_OSD_COUNTRY_SETTING eOSD_Country)
{
    UNUSED(eOSD_Country);

    // todo:
}

//*************************************************************************
//Function name:        MApp_DataBase_RestoreDefaultSystem
//Passing parameter:    none
//Return parameter:     none
//Description:          Restore default system value to data base
//*************************************************************************
void MApp_DataBase_RestoreDefaultSystem(U16 u16KeepSetting)
{
#if(ENABLE_DTV == FALSE && ENABLE_ATV)
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_ATV);

#else

  #if ENABLE_ATSC
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATSC;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_ATSC);

  #elif ENABLE_DVBT
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_DVBT);

  #elif ENABLE_DVBC
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_DVBC);

  #elif ENABLE_DVBS
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_S2);

  #elif ENABLE_DTMB
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_DTMB);

  #elif ENABLE_ISDBT
    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
    MApp_InputSrc_Set_PrevUiInputSrcType(UI_INPUT_SOURCE_ISDBT);

  #endif
#endif

    if (!(RESTORE_KEEP_SYSTEM_LANGUAGE & u16KeepSetting))
    {
        SET_OSD_MENU_LANGUAGE(LANGUAGE_DEFAULT); // menu language
    }

    stGenSetting.g_SysSetting.NextNewRamIndex = 0; // user mode index

#if ENABLE_DTV
    if( IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING) )
    {
    #if ENABLE_SUBTITLE_SWITCH_MENU
        MENU_OPTION_SUBTITLE_ON = 1;
    #else
        stGenSetting.g_SysSetting.fEnableSubTitle = 1;
        stGenSetting.g_SysSetting.fEnableTTXSubTitle = 1;
    #endif
    }
    else
#endif
    {
    #if ENABLE_SUBTITLE_SWITCH_MENU
        MENU_OPTION_SUBTITLE_ON = 0;
    #else
        stGenSetting.g_SysSetting.fEnableSubTitle = 0;
        stGenSetting.g_SysSetting.fEnableTTXSubTitle = 0;
    #endif
    }

  #if HDMI_DVI_AUDIO_MODE_CONFIG
    stGenSetting.g_SysSetting.fEnableHdmiDviAudioModeConfig = EN_HDMI_DVI_AUDIOMODE_AUTO;
  #endif

    stGenSetting.g_SysSetting.SubtitleDefaultLanguage             = LANGUAGE_ENGLISH;
    stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2           = LANGUAGE_ENGLISH;
    stGenSetting.g_SysSetting.Last_Select_HotKey_SubtitleLanguage = LANGUAGE_ENGLISH;
    stGenSetting.g_SysSetting.fHardOfHearing = 0;

  #if (ENABLE_TCON_BIN_IN_DB)
    stGenSetting.g_SysSetting.TconBinInDB = FALSE;
    stGenSetting.g_SysSetting.TconBinSize = 0;
  #endif

  #if ENABLE_PVR
     stGenSetting.g_SysSetting.u32PVR_RecordMaxTime = PVR_CHECKFS_MAX_RECORD_TIME;      //second, the max record time of free record
     stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel = 0;   //0:off  1:record all channel
  #endif


  #if ENABLE_OFFLINE_SIGNAL_DETECTION
    stGenSetting.g_SysSetting.bAIS = AIS_OFF;
  #endif


  #if ENABLE_DBC
    stGenSetting.g_SysSetting.fDCR = 0;
    //MApi_XC_Sys_DLC_DBC_OnOff(stGenSetting.g_SysSetting.fDCR);
  #endif

    stGenSetting.g_SysSetting.fSCARTInputSel = EN_SCART_SEL_AV;
    stGenSetting.g_SysSetting.enCOLORRANGE= EN_COLOR_RANGE_AUTO;

#if ENABLE_DMP
    stGenSetting.g_SysSetting.UsrLogo = POWERON_LOGO_DEFAULT;
    stGenSetting.g_SysSetting.u8UsrLogoCnt= 0;
    stGenSetting.g_SysSetting.u8UsrLogoIdx = 0;
    stGenSetting.g_SysSetting.UsrPowerOnMusic = POWERON_MUSIC_DEFAULT;
#endif
    stGenSetting.g_SysSetting.g_MirrorEnable = FALSE;
	stGenSetting.g_SysSetting.ProjectionType= EN_FRONT_DESKTOP; //wht121101_1
	stGenSetting.g_SysSetting.KeyStoneValue = 0;  //xzm @ 20171222
	stGenSetting.g_SysSetting.OsdDuration = EN_OSD_TIME_ALWAYS;
	
#if ENABLE_OAD
    stGenSetting.g_SysSetting.bOADActiveStandbyMode = FALSE;
#endif

#if(ASTRA_HD_ENABLE)
    stGenSetting.g_SysSetting.u8ServiceListID = 0;
#endif


#if (ENABLE_ATSC)
    //U8 fFinishWizardMode:1;    // 0=Auto, 1=Manual
    stGenSetting.g_SysSetting.fFinishWizardMode = 0;
    //stGenSetting.g_SysSetting.fPreSrcIsDvbs = 0;

    if( !(RESTORE_KEEP_SYSTEM_TIME & u16KeepSetting) )
    {
        //U8 fTimeDST:1;             // 0 = Off, 1 = On
        //stGenSetting.g_SysSetting.fTimeDST        = DEFAULT_TIME_DST;

        //U8 u8TimeZone;             // 0=GMT-12:00 ~ 24=GMT+00:00 ~ 48=GM+12:00
        stGenSetting.g_SysSetting.u8TimeZone = 0;//DEFAULT_TIME_ZONE;

        //U8 fTimeAutoSync:1;        // 0 = Off, 1 = On
        stGenSetting.g_SysSetting.fTimeAutoSync = TIME_AUTO_SYNC_ON;
        stGenSetting.g_SysSetting.fTimeDSTStatusControl = 1;
    }

    //U8  u8NoSavedRRT;         // Move to RRT5
    //U8  u8IdxLastSavedRRT;

    //U16 u16MainListLastWatched[ANT_TYPE_NUM];// last watched service # of Main List
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    stGenSetting.g_SysSetting.u16MainListLastWatched = 0;
#else
    stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_CATV] = 0;
    stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_AIR] = 0;
#endif

    stGenSetting.g_SysSetting.Transparency = TRANSPARENCY_25_PERCENTAGE_VALUE; // OSD Blending

  #if EN_INPUT_LABEL_EDIT
     //EN_INPUT_LABEL_PRESENT_TYPE g_InputLablePresentType[UI_INPUT_SOURCE_NUM];
     memset( (U8*)&(stGenSetting.g_SysSetting.g_InputLablePresentType), 0, sizeof(stGenSetting.g_SysSetting.g_InputLablePresentType) );

     //U8 g_InputLableEdit[UI_INPUT_SOURCE_NUM][MAX_INPUTLLABEL_CHAR_NUM + 1];
     memset( (U8*)&(stGenSetting.g_SysSetting.g_InputLableEdit), 0, sizeof(stGenSetting.g_SysSetting.g_InputLableEdit) );

     //BOOLEAN bInputLabelAdjust[UI_INPUT_SOURCE_NUM];
     memset( (U8*)&(stGenSetting.g_SysSetting.bInputLabelAdjust), 0, sizeof(stGenSetting.g_SysSetting.bInputLabelAdjust) );
  #endif

  #if ENABLE_ATSC_TTS
    stGenSetting.g_SysSetting.bTTSOn =  TRUE;
    stGenSetting.g_SysSetting.u8TTSVolume = EN_VOICE_GUIDE_VOLUME_MEDIUM;
    stGenSetting.g_SysSetting.u8TTSPitch = EN_VOICE_GUIDE_PITCH_MEDIUM;
    stGenSetting.g_SysSetting.u8TTSSpeed = EN_VOICE_GUIDE_SPEED_NORMAL;
  #endif
#endif
#if ENABLE_KEY_TO_SPEECH
    stGenSetting.g_SysSetting.bKTSOn = FALSE;
#endif
}

#if(ENABLE_DTV)
extern U16 msAPI_DtvDB_Get_ProgramIndexTableArraySize(TypDtvDbSel eDtvDbSel);
#endif

void MApp_DataBase_RestoreDefault_TVSetting(void)
{
    //printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    stGenSetting.stTvSetting.u8ATVProgramNumber = MIN_ATVPROGRAM;

#if (ENABLE_SW_CH_FREEZE_SCREEN)
    stGenSetting.stTvSetting.u8SwitchMode =ATV_SWITCH_CH_FREEZE_SCREEN;
#endif

#if (ENABLE_DTV)
    stGenSetting.stTvSetting.eCountry = DEFAULT_COUNTRY;

    stGenSetting.stTvSetting.u16DTVRFChannelOrder = DEFAULT_CURRENT_ORDER_TV;
    stGenSetting.stTvSetting.u16DATARFChannelOrder = DEFAULT_CURRENT_ORDER_DATA(E_DTV_DB_SEL_DVBT);
    stGenSetting.stTvSetting.u16RADIORFChannelOrder = DEFAULT_CURRENT_ORDER_RADIO(E_DTV_DB_SEL_DVBT);
    stGenSetting.stTvSetting.eCurrentServiceType = DEFAULT_CURRENT_SERVICETYPE;
#endif

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    stGenSetting.stTvSetting.u16CurDtvOrder_DVBC = DEFAULT_CURRENT_ORDER_TV;
    stGenSetting.stTvSetting.u16CurDtvDataOrder_DVBC = DEFAULT_CURRENT_ORDER_DATA(E_DTV_DB_SEL_DVBC);
    stGenSetting.stTvSetting.u16CurDtvRadioOrder_DVBC = DEFAULT_CURRENT_ORDER_RADIO(E_DTV_DB_SEL_DVBC);
    stGenSetting.stTvSetting.eCurrentServiceType_DVBC = DEFAULT_CURRENT_SERVICETYPE;
#endif
}

void MApp_DataBase_RestoreDefaultADC(E_ADC_SET_INDEX eAdcIndex )
{
#if USE_CUS_DEFAULT_ADC
    if( eAdcIndex == ADC_SET_YPBPR_SD )
    {
        G_ADC_SETTING[ADC_SET_YPBPR_SD].stAdcGainOffsetSetting = tADCSetting[ADC_SET_YPBPR_SD];
    }
    else if( eAdcIndex == ADC_SET_YPBPR_HD )
    {
        G_ADC_SETTING[ADC_SET_YPBPR_HD].stAdcGainOffsetSetting = tADCSetting[ADC_SET_YPBPR_HD];
    }
    else if( eAdcIndex == ADC_SET_SCART_RGB )
    {
        G_ADC_SETTING[ADC_SET_SCART_RGB].stAdcGainOffsetSetting = tADCSetting[ADC_SET_SCART_RGB];
    }
    else
    {
        G_ADC_SETTING[ADC_SET_VGA].stAdcGainOffsetSetting = tADCSetting[ADC_SET_VGA];
    }
#else
    APIXC_AdcGainOffsetSetting Adc_GainOffset;

    if ( eAdcIndex == ADC_SET_YPBPR_SD || eAdcIndex == ADC_SET_YPBPR_HD )
    {
        // Get Ypbpr default setting
        MApi_XC_ADC_GetDefaultGainOffset(INPUT_SOURCE_YPBPR,&Adc_GainOffset);
    }
    else if(eAdcIndex == ADC_SET_SCART_RGB) // Scart-RGB
    {
        // Get RGB default setting
        MApi_XC_ADC_GetDefaultGainOffset(INPUT_SOURCE_SCART,&Adc_GainOffset);
    }
    else // VGA / Scart-RGB / Others
    {
        // Get RGB default setting
        MApi_XC_ADC_GetDefaultGainOffset(INPUT_SOURCE_VGA,&Adc_GainOffset);
    }

    memcpy(&(G_ADC_SETTING[eAdcIndex].stAdcGainOffsetSetting) , &Adc_GainOffset , sizeof(APIXC_AdcGainOffsetSetting) );

#endif

    G_ADC_SETTING[eAdcIndex].u8AdcCalOK = ADC_CAL_NONE;
#if ENABLE_HW_INTERNAL_ADC_CALIBRATION
    G_ADC_SETTING[eAdcIndex].u8CalibrationMode = E_XC_HW_CALIBRATION;
#else
    G_ADC_SETTING[eAdcIndex].u8CalibrationMode = E_XC_SW_CALIBRATION;
#endif

}
//*************************************************************************
//Function name:        MApp_DataBase_RestoreDefaultVideo
//Passing parameter:    none
//Return parameter:     none
//Description:          Restore default video value to data base
//*************************************************************************
void MApp_DataBase_RestoreDefaultVideo(E_DATA_INPUT_SOURCE enDataInputSource)
{
    U8 i;

    //printf("=============> MApp_DataBase_RestoreDefaultVideo\n");

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
        {
            G_VEDIO_SETTING[i] = astDefaultVideoDataTbl[i];
        }
    }
    else
    {
        G_VEDIO_SETTING[enDataInputSource] = astDefaultVideoDataTbl[enDataInputSource];
    }

    //reset Film mode
    //MDrv_PQ_SetFilmMode(PQ_MAIN_WINDOW, DEFAULT_ENABLE_CINEMA);
}

void MApp_DataBase_RestoreDefaultWhiteBalance(E_DATA_INPUT_SOURCE enDataInputSource)
{
    U8 i;

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
        {
            G_WHITE_BALANCE_SETTING[i] = astDefaultWhiteBalanceDataTbl[i];
        }
    }
    else
    {
        G_WHITE_BALANCE_SETTING[enDataInputSource] = astDefaultWhiteBalanceDataTbl[enDataInputSource];
    }
}

void MApp_DataBase_PictureResetWhiteBalance(E_DATA_INPUT_SOURCE enDataInputSource)
{
#if 1
    MApp_DataBase_RestoreDefaultWhiteBalance(enDataInputSource);
#else
    U8 i;
#if ENABLE_PRECISE_RGBBRIGHTNESS
    XC_ACE_color_temp_ex stColorTemp =
#else
    XC_ACE_color_temp stColorTemp =
#endif
    {
        INIT_VIDEO_COLOR_BRIGHTNESS_USER_R,
        INIT_VIDEO_COLOR_BRIGHTNESS_USER_G,
        INIT_VIDEO_COLOR_BRIGHTNESS_USER_B,

        INIT_VIDEO_COLOR_TEMP_USER_R,
        INIT_VIDEO_COLOR_TEMP_USER_G,
        INIT_VIDEO_COLOR_TEMP_USER_B,

        0,
        0,
        0,
    };  //24Byte

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
        {
            //G_WHITE_BALANCE_SETTING[i] = astDefaultWhiteBalanceDataTbl[i];
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cRedOffset       =  stColorTemp.cRedOffset;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cGreenOffset     =  stColorTemp.cGreenOffset;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cBlueOffset      =  stColorTemp.cBlueOffset;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cRedColor        =  stColorTemp.cRedColor;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cGreenColor      =  stColorTemp.cGreenColor;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cBlueColor       =  stColorTemp.cBlueColor;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cRedScaleValue   =  stColorTemp.cRedScaleValue;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cGreenScaleValue =  stColorTemp.cGreenScaleValue;
            G_WHITE_BALANCE_SETTING[i].astColorTemp[MS_COLOR_TEMP_MAX].cBlueScaleValue  =  stColorTemp.cBlueScaleValue;
        }
    }
    else
    {
        //G_WHITE_BALANCE_SETTING[enDataInputSource] = astDefaultWhiteBalanceDataTbl[enDataInputSource];
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cRedOffset       =  stColorTemp.cRedOffset;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cGreenOffset     =  stColorTemp.cGreenOffset;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cBlueOffset      =  stColorTemp.cBlueOffset;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cRedColor        =  stColorTemp.cRedColor;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cGreenColor      =  stColorTemp.cGreenColor;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cBlueColor       =  stColorTemp.cBlueColor;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cRedScaleValue   =  stColorTemp.cRedScaleValue;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cGreenScaleValue =  stColorTemp.cGreenScaleValue;
        G_WHITE_BALANCE_SETTING[enDataInputSource].astColorTemp[MS_COLOR_TEMP_MAX].cBlueScaleValue  =  stColorTemp.cBlueScaleValue;
    }
#endif
}

void MApp_DataBase_RestoreDefaultSubColor(E_DATA_INPUT_SOURCE enDataInputSource)
{
    U8 i;

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
        {
            G_SUB_COLOR_SETTING[i] = astDefaultSubBriConTbl[i];
        }
    }
    else
    {
        G_SUB_COLOR_SETTING[enDataInputSource] = astDefaultSubBriConTbl[enDataInputSource];
    }
}

//*************************************************************************
//Function name:        MApp_DataBase_RestoreDefaultAudio
//Passing parameter:    none
//Return parameter:     none
//Description:          Restore default audio value to data base
//*************************************************************************
void MApp_DataBase_RestoreDefaultAudio(BOOL bSetDriver)
{
    stGenSetting.g_SoundSetting.SoundMode = SOUND_MODE_STANDARD;

  #if ENABLE_CEC
    if (ARC_SUPPORT_PORT == 0)
        stGenSetting.g_SoundSetting.TVspeakerMode = TVspeaker_Mode_IntSpeaker;
    else
        stGenSetting.g_SoundSetting.TVspeakerMode = TVspeaker_Mode_ExtAmp;
  #endif

    /* Update the default sound mode. All default sound modes are stored in astDefaultSoundModeSeting*/
    memcpy(stGenSetting.g_SoundSetting.astSoundModeSetting, astDefaultSoundModeSeting, sizeof(astDefaultSoundModeSeting));

    g_u8AudLangSelected = SOUND_MTS_STEREO;
    stGenSetting.g_SoundSetting.bEnableAVC = DISABLE;
    stGenSetting.g_SoundSetting.Surround = SURROUND_MODE_MOUNTAIN;
    stGenSetting.g_SoundSetting.Volume = DEFAULT_VOLUME_SETTING;

#if(ENABLE_DVB_AUDIO_DESC) // set default AD value
    stGenSetting.g_SoundSetting.bEnableAD = DISABLE;
#endif

    stGenSetting.g_SoundSetting.ADVolume = DEFAULT_VOLUME_SETTING;
    stGenSetting.g_SoundSetting.ADOutput = AD_SPEAKER;
    stGenSetting.g_SoundSetting.Balance = DEFAULT_BALANCE_SETTING;
    stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
    stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
    stGenSetting.g_SoundSetting.SurroundSoundMode = SURROUND_SYSTEM_OFF;
  #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
    stGenSetting.g_SoundSetting.DBXTV_TotSonMode = E_TOTSON_ON;
    stGenSetting.g_SoundSetting.DBXTV_TotVolMode = E_TOTVOL_NORMAL;
    stGenSetting.g_SoundSetting.TotSurMode = E_TOTSUR_ON;
    MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x1F);
  #endif

    stGenSetting.g_SysSetting.fAutoVolume = DEFAULT_AUTO_VOLUME;
  #if (ENABLE_DTV)
    stGenSetting.g_SysSetting.fSPDIFMODE = 0;   // 0=PCM, 1= AUTO
  #else
    stGenSetting.g_SysSetting.fSPDIFMODE = 1;   // 0=PCM, 1= AUTO
  #endif


#if (ENABLE_ATSC)
    // EN_ADUIO_LAN      enSoundAudioLan;
    stGenSetting.g_SoundSetting.enSoundAudioLan = SOUND_AUDIO_LAN_ENGLISH;
    //EN_PRIMART_AUDIO_PARAMETER  enPrimartAudioPmt;
    stGenSetting.g_SoundSetting.enPrimartAudioPmt = SOUND_AUDIO_LANGUAGE;//SOUND_ACCESSIBILITY;

  #if(ENABLE_ATSC_VIDEO_DESC)
    //EN_VIDEO_DESCRIPTION_ITEM  enVideoDescription;
    stGenSetting.g_SoundSetting.enVideoDescription = EN_VIDEO_DESCRIPTION_ITEM_ON;
  #endif

    //EN_DAP_AUDIO_LANGUAGE   enDAPAudioLanguage;
    stGenSetting.g_SoundSetting.enDAPAudioLanguage = DAP_SOUND_LANGUAGE_ENGLISH;

    //EN_DIGITAL_AUDIO_SECLECTION      enSoundDigitalSelect;
    stGenSetting.g_SoundSetting.enSoundDigitalSelect = SOUND_AUDIO_DIGITAL_DEFAULT;

    //EN_ACCESSIBILITY    enAccessibility;
    stGenSetting.g_SoundSetting.enAccessibility = SOUND_MAIN_AUDIO;

    //EN_SOUND_MTS_TYPE Mts;
    stGenSetting.g_SoundSetting.Mts = SOUND_MTS_STEREO;
#endif


    // At this time, audio driver is not init yet!
    if( bSetDriver && MApp_Main_Is_PowerOnInitFinish() )
    {
        MApi_AUDIO_SetBalance(stGenSetting.g_SoundSetting.Balance);
        // add AVL function
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        MApi_AUDIO_EnableAutoVolume((BOOLEAN)stGenSetting.g_SysSetting.fAutoVolume);
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
	
	MApi_AUDIO_SetEq(E_EQUALIZER_BAND_1, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ);
    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_2, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ);
    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_3, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_5_KHZ);
    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_4, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_5KHZ);
    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_5, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u810KHZ);
}

void MApp_DataBase_RestoreDefaultScanMenu(void)
{
    //printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    //*************************************************************************
    // Restore default ScanMenuSetting
    //*************************************************************************
    stGenSetting.stScanMenuSetting.u8RFChannelNumber = DEFAULT_RF_CHANNEL;
    stGenSetting.stScanMenuSetting.u8ChType = CH_TYPE_DTV;
    stGenSetting.stScanMenuSetting.u8Antenna = ANT_AIR;
    stGenSetting.stScanMenuSetting.u8ATVManScanDir=ATV_MAN_SCAN_UP;
    stGenSetting.stScanMenuSetting.u8ATVManScanType=ATV_MAN_SCAN_TYPE_ONECH;
    stGenSetting.stScanMenuSetting.u8ATVMediumType=MEDIUM_AIR;
    stGenSetting.stScanMenuSetting.u8LSystem=FALSE;
    stGenSetting.stScanMenuSetting.u8ScanType=SCAN_TYPE_AUTO;
    stGenSetting.stScanMenuSetting.u8BandWidth = E_RF_CH_BAND_7MHz;

#if ENABLE_DTV
    msAPI_DFT_SetBandwidth(stGenSetting.stScanMenuSetting.u8BandWidth);
#endif

#if (ENABLE_DVBC )
    stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType=EN_DVB_T_TYPE;
    // msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
#endif

#if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
    stGenSetting.stScanMenuSetting.u8SoundSystem=EN_ATV_SystemType_M;
#elif (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    stGenSetting.stScanMenuSetting.u8SoundSystem=EN_ATV_SystemType_DK;
#else
    #if ENABLE_SBTVD_ATV_SYSTEM
    if(IS_SBTVD_APP)
    {
        stGenSetting.stScanMenuSetting.u8SoundSystem = EN_ATV_SystemType_M;
    }
    else
    #endif
    {
        stGenSetting.stScanMenuSetting.u8SoundSystem = EN_ATV_SystemType_DK;//EN_ATV_SystemType_BG;
    }
#endif

#if (ENABLE_ATSC) //NeedCheck
    //U8 u8CableSystem:2;       //0=STD, 1=IRC, 2=HRC, 3=AUTO
    stGenSetting.stScanMenuSetting.u8CableSystem = DEFAULT_CABLE_SYSTEM;
#endif

}

void MApp_DataBase_RestoreDefaultTime(void)
{
    stGenSetting.g_Time = stDefaultTimeData;

#if(ENABLE_ISDBT_AND_DVB)
    if( IS_COUNTRY_USE_SBTVD() )
    {
        stGenSetting.g_Time.enTimeZone = TIMEZONE_BRASILIA;
        stGenSetting.g_Time.en_Clock_TimeZone = EN_Clock_TimeZone_18;
    }
    else
    {
    }
#endif


#if ( ENABLE_RIKS_TV_IRD_SETTING )
    stGenSetting.g_Time.cAutoSleepSetting = STATE_AUTOSLEEP_4HOUR;
#endif  //ENABLE_RIKS_TV_IRD_SETTING

#if ENABLE_ATSC
    stGenSetting.g_Time.s32Offset_Time = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);
    // Should call here??
    msAPI_Timer_SetOffsetTime(stGenSetting.g_Time.s32Offset_Time);
#endif
}

#if ENABLE_GAMMA_ADJUST
void MApp_DataBase_RestoreDefaultGammaTable(void)
{
    U8 i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<GAMMA_ADJUST_NUM;j++)
        {
            stGenSetting.g_GammaSetting.GammaAdjOSDValue[i][j]=50;
        }
    }
    stGenSetting.g_GammaSetting.u8Gain= MS_GAMMAADJUST_MIN;
    stGenSetting.g_GammaSetting.u8RedColor= 50;
    stGenSetting.g_GammaSetting.u8GreenColor= 50;
    stGenSetting.g_GammaSetting.u8BlueColor= 50;

}
#endif

#if( ENABLE_ISDBT_AND_DVB )
U8 MApp_DataBase_Get_Default_LockSystem_Min(void)
{
    if( IS_COUNTRY_USE_SBTVD() )
        return 8;
    else
        return 3;
}
#endif

void App_DataBase_RestoreDefaultBlock(void)
{
    stGenSetting.g_BlockSysSetting.u8ParentalControl = EN_F4_LockSystem_Min;

    //stGenSetting.g_BlockSysSetting.u8ParentalControl = EN_F4_LockSystem_Max; //Mediaset 2.4.3 test 5.5 default needs 18.
}

void MApp_DataBase_RestoreDefaultSSC(void)
{
#if ENABLE_SSC
    stGenSetting.g_SSCSetting.SscMIUEnable = ENABLE;
    stGenSetting.g_SSCSetting.MIUSscSpanKHzx10= MIU_SSC_SPAN_DEFAULT;
    stGenSetting.g_SSCSetting.MIUSscStepPercentagex100= MIU_SSC_STEP_DEFAULT;
    stGenSetting.g_SSCSetting.SscLVDSEnale = ENABLE;
    stGenSetting.g_SSCSetting.LVDSSscSpanKHzx10= LVDS_SSC_SPAN_DEFAULT;
    stGenSetting.g_SSCSetting.LVDSSscStepPercentagex100= LVDS_SSC_STEP_DEFAULT;
    stGenSetting.g_SSCSetting.LVDSSwing= LVDS_SSC_SWING_DEFAULT;
#if URSA_SSC_ENABLE
    stGenSetting.g_SSCSetting.SscUrsaMIU0Enable=ENABLE;
    stGenSetting.g_SSCSetting.MIU0SscModulation=20;
    stGenSetting.g_SSCSetting.MIU0SscPercentage=0;
    stGenSetting.g_SSCSetting.SscUrsaMIU1Enable=ENABLE;
    stGenSetting.g_SSCSetting.MIU1SscModulation=20;
    stGenSetting.g_SSCSetting.MIU1SscPercentage=0;
    stGenSetting.g_SSCSetting.SscUrsaLVDSEnable=ENABLE;
    stGenSetting.g_SSCSetting.LVDSSscModulation=20;
    stGenSetting.g_SSCSetting.LVDSSscPercentage=0;
    stGenSetting.g_SSCSetting.PanelSwing=0;
#endif
#endif
}

#if (ENABLE_NONLINEAR_CURVE)
void MApp_DataBase_RestoreDefaultNonLinearCurve(void)
{
    stGenSetting.g_NonLinearCurveSetting = tNonLinearCurveSetting;
}
#endif

void MApp_DataBase_RestoreDefault_FactoryVDSetting(void)
{
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D4 = 0x00;

    //G_FACTORY_SETTING.stVDSetting.u8AFEC_D4 = 0x00;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D5_Bit10 = 0;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D8_Bit3210 = 0;
#if ENABLE_VD_PACH_IN_CHINA
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D4 =BK_AFEC_D4_DEFAULT;
    G_FACTORY_SETTING.stVDSetting.u32VDPatchFlag = MSVD_HTOTAL_TYPE|AVD_PATCH_FINE_TUNE_FH_DOT|AVD_PATCH_FINE_TUNE_COMB_F2|AVD_PATCH_FINE_TUNE_3D_COMB;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D5_Bit2    =0;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D8_Bit3210    =0x00;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D9_Bit0    =0;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_A0         =0x10;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_A1         =0x20;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_A0A1_COUNT =0;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_66_Bit76   =0;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_6E_Bit7654 =0x08;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_6E_Bit3210 =0x08;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_43=0x14;
    G_DESIGN_SETTING.stVDSetting.u8AFEC_43_OPTION = 1;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_44=0x90;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_CB=0x00;
    G_FACTORY_SETTING.stVDSetting.CF_2_ATV=1;
    G_FACTORY_SETTING.stVDSetting.CF_2_AV=0;
    G_FACTORY_SETTING.stVDSetting.Vif_CLAMPGAIN_GAIN_OV_NEGATIVE=VIF_CLAMPGAIN_GAIN_OV_NEGATIVE;
    G_FACTORY_SETTING.stVDSetting.AUDIO_NR=0;
    G_DESIGN_SETTING.stVDSetting.PRESCALE=0;
   // G_FACTORY_SETTING.stVDSetting.u8AFEC_258D=0;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D7_LOW_BOUND=VD_COLOR_KILL_LOW_BOUND;
    G_FACTORY_SETTING.stVDSetting.u8AFEC_D7_HIGH_BOUND=VD_COLOR_KILL_HIGH_BOUND;

//VIF setting
    G_FACTORY_SETTING.stVDSetting.VifTop=VIF_TOP;
    G_FACTORY_SETTING.stVDSetting.Vif_VGA_MAXIMUM=VIF_VGA_MAXIMUM;
    G_FACTORY_SETTING.stVDSetting.Gain_DISTRIBUTION_THR=GAIN_DISTRIBUTION_THR;
   // G_FACTORY_SETTING.stVDSetting.Vif_AGC_VGA_BASE=VIF_AGC_VGA_BASE;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KP1      =VIF_CR_KP1;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KI1      =VIF_CR_KI1;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KP2      =VIF_CR_KP2;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KI2      =VIF_CR_KI2;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KP       =VIF_CR_KP;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KI       =VIF_CR_KI;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_LOCK_THR =VIF_CR_LOCK_THR;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_THR      =VIF_CR_THR;
    G_FACTORY_SETTING.stVDSetting.Vif_CR_KP_KI_ADJUST=VIF_CR_KP_KI_ADJUST;
    G_FACTORY_SETTING.stVDSetting.China_DESCRAMBLER_BOX=50;
  #if(CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER)
    G_FACTORY_SETTING.stVDSetting.Vif_PROGRAMMABLE_DELAY=VIF_PROGRAMMABLE_DELAY;
  #endif
    G_FACTORY_SETTING.stVDSetting.Vif_DELAY_REDUCE    =VIF_DELAY_REDUCE;
    G_FACTORY_SETTING.stVDSetting.Vif_OVER_MODULATION =VIF_OVER_MODULATION;
    G_FACTORY_SETTING.stVDSetting.Vif_CLAMPGAIN_CLAMP_OV_NEGATIVE=VIF_CLAMPGAIN_CLAMP_OV_NEGATIVE;
    G_FACTORY_SETTING.stVDSetting.AUDIO_HIDEV=1;

    G_FACTORY_SETTING.stVDSetting.Vif_ASIA_SIGNAL_OPTION=VIF_ASIA_SIGNAL_OPTION;
    G_FACTORY_SETTING.stVDSetting.Vif_AGCREFNEGATIVE=VIF_CHANEL_SCAN_AGC_REF;
#endif
}

void MApp_DataBase_RestoreDefault_FactoryMiscSetting(void)
{
    G_FACTORY_SETTING.stFacMiscSetting.u8Test = 0;

#if ENABLE_DESIGN_POWER_ON_MODE
    G_FACTORY_SETTING.stFacMiscSetting.u8PowerOnMode = POWERON_MODE_ON ; // POWERON_MODE_SAVE;
#endif

#if ENABLE_FACTORY_INPUT_SOURCE_FUNCTION
    G_FACTORY_SETTING.stFacMiscSetting.u16_AV_Count = 1;
    G_FACTORY_SETTING.stFacMiscSetting.u16_SV_Count = 0;
    G_FACTORY_SETTING.stFacMiscSetting.u16_SCART_Count = 0;
    G_FACTORY_SETTING.stFacMiscSetting.u16_COMPONENT_Count = 1;
    G_FACTORY_SETTING.stFacMiscSetting.u16_HDMI_Count = 2;
#endif
#if (ENABLE_UART_MSG_TO_USB)
    G_FACTORY_SETTING.stFacMiscSetting.eFactoryUSBLog = EN_FACTORY_USB_LOG_OFF;
#endif

#if (ENABLE_SCRIPT_EXECUTE)
    G_FACTORY_SETTING.stFacMiscSetting.eFactoryExecuteScript = EN_FACTORY_EXECUTE_SCRIPT_OFF;
#endif
}

#if ENABLE_PANEL_BIN
void MApp_DataBase_RestoreDefault_FactoryPnlSetting(void)
{
    U8 i;

    //printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    G_FACTORY_SETTING.stFacPnlSetting.u8PanelBinIndex = 0;

    for (i=0; i<PANEL_BIN_MAX_SUPPORT_TABLE; i++)
    {
        G_FACTORY_SETTING.stFacPnlSetting.bUpdated[i] = 0;
        G_FACTORY_SETTING.stFacPnlSetting.m_bPanelDualPort[i] = 0;
        G_FACTORY_SETTING.stFacPnlSetting.m_bPanelSwapPort[i] = 0;
        G_FACTORY_SETTING.stFacPnlSetting.m_bPanelLVDS_TI_MODE[i] = 0;
        G_FACTORY_SETTING.stFacPnlSetting.m_ucTiBitMode[i] = 0;
        G_FACTORY_SETTING.stFacPnlSetting.m_ucOutputFormatBitMode[i] = 0;
    }
}
#endif

void MApp_DataBase_RestoreDefaultFactorySetting(void)
{
    //printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __FUNCTION__);

    memset( &(G_FACTORY_SETTING), 0, sizeof(MS_FACTORY_SETTING) );

    MApp_DataBase_RestoreDefault_FactoryVDSetting();
    MApp_DataBase_RestoreDefault_FactoryMiscSetting();
#if ENABLE_PANEL_BIN
    MApp_DataBase_RestoreDefault_FactoryPnlSetting();
#endif


    // Reset all ADC setting...
    MApp_SaveData_ADC_ResetAllSetting();

    // Reset all WB setting
    MApp_DataBase_RestoreDefaultWhiteBalance(DATA_INPUT_SOURCE_NUM);

    // Reset all sub color setting
    MApp_DataBase_RestoreDefaultSubColor(DATA_INPUT_SOURCE_NUM);
}

#if ENABLE_DRM
void MApp_Drm_RestoreDefaultSetupInfo(void)
{
    int i;
    for(i = 0; i < DIVX_REG_CODE_LEN; i++)
        stGenSetting.g_VDplayerDRMInfo.u8RegistrationCode[i] = 0;
    for(i = 0; i < DIVX_DEACT_CODE_LEN; i++)
        stGenSetting.g_VDplayerDRMInfo.u8DeActivationCode[i] = 0;
    for(i = 0; i < DIVX_KEY_LEN; i++)
        stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i] = 0;

    stGenSetting.g_VDplayerDRMInfo.bIsKeyGenerated = 0;
    stGenSetting.g_VDplayerDRMInfo.bIsActivated = 0;
    stGenSetting.g_VDplayerDRMInfo.bIsDeactivated = 0;
}
#endif

#if (ENABLE_PIP)
void MApp_DataBase_RestoreDefaultPIP(void)
{
    stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
    stGenSetting.g_stPipSetting.enSubInputSourceType = UI_INPUT_SOURCE_RGB;
    stGenSetting.g_stPipSetting.enPipSize = EN_PIP_SIZE_SMALL;
    stGenSetting.g_stPipSetting.enPipPosition = EN_PIP_POSITION_RIGHT_BOTTOM;
    stGenSetting.g_stPipSetting.bBolderEnable = FALSE;
    stGenSetting.g_stPipSetting.enPipSoundSrc = EN_PIP_SOUND_SRC_MAIN;
    stGenSetting.g_stPipSetting.u8BorderWidth = 0x01;
    stGenSetting.g_stPipSetting.bPipEnable = TRUE;
    stGenSetting.g_stPipSetting.PIPSetupInfoCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA );
}

#endif

void MApp_DataBase_RestoreDefault_MiscSetting(void)
{
    //printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    stGenSetting.stMiscSetting.bDCOnOff = EN_POWER_DC_ON;

#if (ENABLE_EWS)
    stGenSetting.stMiscSetting.u8EWSLocationCode[0] = 0;
    stGenSetting.stMiscSetting.u8EWSLocationCode[1] = 0;
    stGenSetting.stMiscSetting.u8EWSLocationCode[2] = 0;
    stGenSetting.stMiscSetting.u8EWSLocationCode[3] = 0;
    stGenSetting.stMiscSetting.u8EWSLocationCode[4] = 0;
    MApp_EWS_SetMsgCancelFlag(FALSE); //cancel EWS
    MApp_SI_SetLocationCode(stGenSetting.stMiscSetting.u8EWSLocationCode);
#endif
#if (ENABLE_DTV)
    stGenSetting.stMiscSetting.bRunInstallationGuide = TRUE;
#else
    stGenSetting.stMiscSetting.bRunInstallationGuide = FALSE;
#endif
}


#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
void MApp_DataBase_RestoreDefault_DevMfcSetting(void)
{
    stGenSetting.stDevMfcSetting.enMEMCType = EN_URSA_MFC_Off;

    stGenSetting.stDevMfcSetting.en6M30MirrorMode = EN_6M30_MIRROR_OFF;

    stGenSetting.stDevMfcSetting.enMFCStrength = EN_MFC_Strength_Normal;
}
#endif


#if(ENABLE_S2)
//extern Antenna_SatInfo const AntennaSatList_BuiltIn[];
Antenna_SatInfo const AntennaSatList_BuiltIn[] =
{
    //satellite , Band ,     Angle ,   satellite name,                 Start Idx,     End Idx,    SatIdx,  TP Num
    {KU_130_HOTBIRD_6_7A_8,            BAND_KU,  130,(MS_U8*)"HOTBIRD 6,7A,8"} ,//        3    107
    {KU_192_ASTRA_1H_1KR_1L_1M,    BAND_KU,  192,(MS_U8*)"ASTRA 1H,1KR,1L,1M"} ,//        5    85
    {KU_282_ASTRA_2A_2B_2D,           BAND_KU,  282,(MS_U8*)"ASTRA 2A,2B,2D"} ,//        7    90
    {KU_235_ASTRA_1E_1G_3A,            BAND_KU,  235,(MS_U8*)"ASTRA 1E,1G,3A"} ,//        7    90
    {KU_3530_NILESAT_101_10,           BAND_KU,  3530,(MS_U8*)"NILESAT 101, 10"} ,//    46    35
    {KU_70_EUTELSAT_W3A,                BAND_KU,  70,(MS_U8*)"EUTELSAT W3A"} ,//        1    18
    {KU_100_EUTELSAT_W1,                BAND_KU,  100,(MS_U8*)"EUTELSAT W1"} ,//        2    6
    {KU_260_BADR_2_3_4_EURO,        BAND_KU,  260,(MS_U8*)"BADR-2,3,4/EURO"} ,//        6    30
    {KU_360_EUTELSAT_SESAT,           BAND_KU,  360,(MS_U8*)"EUTELSAT SESAT"} ,//        9    9
    {KU_160_EUTELSAT_W2,                BAND_KU,  160,(MS_U8*)"EUTELSAT W2"} ,//        4    47
    {KU_400_EXPRESS_AM1,                BAND_KU,  400,(MS_U8*)"EXPRESS AM1"} ,//    11    5
    {KU_420_TURKSAT_2A_3A,             BAND_KU,  420,(MS_U8*)"TURKSAT 2A, 3A"} ,//    12    170
    {KU_620_INTELSAT_920,                BAND_KU,  620,(MS_U8*)"INTELSAT 902"} ,//    13    18
    {C_686_INTELSAT_7_10,                BAND_C,  686,(MS_U8*)"INTELSAT 7, 10"} ,//    14    53
    {KU_305_ARABSAT_2B,                  BAND_KU,  305,(MS_U8*)"ARABSAT 2B"} ,//        8    4
    {KU_390_HELLAS_SAT_2,                 BAND_KU,  390,(MS_U8*)"HELLAS SAT 2"} ,//    10    21
    {KU_765_TELSTAR_10,                   BAND_KU,  765,(MS_U8*)"TELSTAR 10"} ,//    15    32
    {C_765_TELSTAR_10,                     BAND_C,  765,(MS_U8*)"TELSTAR 10"} ,//    15    32
    {KU_785_THAICOM_2_5,                 BAND_KU,  785,(MS_U8*)"THAICOM 2,5"} ,//    16    45
    {C_785_THAICOM_2_5,                  BAND_C,  785,(MS_U8*)"THAICOM 2,5"} ,//    16    45
    {KU_830_INSAT_3B_4A,                 BAND_KU,   830,(MS_U8*)"INSAT 3B,4A"} ,//    17    12
    {KU_900_YAMAL_210,                           BAND_KU,   900,(MS_U8*)"YAMAL 201"} ,//    18    3
    {KU_950_NSS_6,                                  BAND_KU,   950,(MS_U8*)"NSS 6"} ,//    19    23
    {C_1005_ASIASAT_2,                             BAND_C,  1005,(MS_U8*)"ASIASAT 2"} ,//    20    37
    {KU_1005_ASIASAT_2,                           BAND_KU,  1005,(MS_U8*)"ASIASAT 2"} ,//    20    37
    {C_1055_ASIASAT_3S,                           BAND_C,  1055,(MS_U8*)"ASIASAT 3S"} ,//    21    50
    {KU_1055_ASIASAT_3S,                         BAND_KU,  1055,(MS_U8*)"ASIASAT 3S"} ,//    21    50
    {C_1155_CHINASAT_6B,                        BAND_C,  1155,(MS_U8*)"CHINASAT 6B"} ,//    22    44
    {C_1250_SINOSAT_3,                             BAND_C,  1250,(MS_U8*)"SINOSAT-3"} ,//    23    14
    {C_1340_APSTAR_6,                              BAND_C,  1340,(MS_U8*)"APSTAR 6"} ,//    24    11
    {KU_1340_APSTAR_6,                            BAND_KU,  1340,(MS_U8*)"APSTAR 6"} ,//    24    11
    {C_1660_INTELSAT_8,                           BAND_C,  1660,(MS_U8*)"INTELSAT 8"} ,//    25    19
    {KU_1660_INTELSAT_8,                         BAND_KU,  1660,(MS_U8*)"INTELSAT 8"} ,//    25    19
    {C_1690_INTELSAT_2,                           BAND_C,  1690,(MS_U8*)"INTELSAT 2"} ,//    26    10
    {KU_1690_INTELSAT_2,                         BAND_KU,  1690,(MS_U8*)"INTELSAT 2"} ,//    26    10
    {C_2330_HORIZONS_1,                         BAND_C, 2330,(MS_U8*)"HORIZONS 1"} ,//    28    2
    {KU_2330_HORIZONS_1,                       BAND_KU,2330,(MS_U8*)"HORIZONS 1"} ,//    28    2
    {KU_2370_GALAXY_10R,                        BAND_KU, 2370,(MS_U8*)"GALAXY 10R"} ,//    29    26
    {C_2370_GALAXY_10R,                          BAND_C, 2370,(MS_U8*)"GALAXY 10R"} ,//    29    26
    {C_2390_GALAXY_23,                            BAND_C, 2390,(MS_U8*)"GALAXY 23"} ,//    30    25
    {KU_2630_GALAXY_25,                          BAND_KU,2630,(MS_U8*)"GALAXY 25"} ,//    32    19
    {C_2650_GALAXY_3C,                           BAND_C, 2650,(MS_U8*)"GALAXY 3C"} ,//    33    37
    {KU_2650_GALAXY_3C,                         BAND_KU,2650,(MS_U8*)"GALAXY 3C"} ,//    33    37
    {C_2690_GALAXY_11,                            BAND_C, 2690,(MS_U8*)"GALAXY 11"} ,//    34    26
    {KU_2690_GALAXY_11,                          BAND_KU,2690,(MS_U8*)"GALAXY 11"} ,//    34    26
    {KU_3020_INTELSAT_9,                         BAND_KU,3020,(MS_U8*)"INTELSAT 9"} ,//    37    31
    {C_3020_INTELSAT_9,                           BAND_C, 3020,(MS_U8*)"INTELSAT 9"} ,//    37    31
    {KU_3070_INTELSAT_707,                      BAND_KU, 3070,(MS_U8*)"INTELSAT 707"} ,//    38    2
    {KU_3300_HISPASAT_1C_1D,                BAND_KU, 3300,(MS_U8*)"HISPASAT 1C, 1D"} ,//    39    31
    {KU_3325_INTELSAT_907,                     BAND_KU, 3325,(MS_U8*)"INTELSAT 907"} ,//    40    2
    {KU_3380_NSS_7,                                BAND_KU, 3380,(MS_U8*)"NSS 7"} ,//    41    5
    {KU_3450_TELSTAR_12,                        BAND_KU, 3450,(MS_U8*)"TELSTAR 12"} ,//    42    11
    {KU_3475_ATLANTIC_BIRD_1,              BAND_KU, 3475,(MS_U8*)"ATLANTIC BIRD 1"} ,//    43    16
    {KU_3490_EXPRESS_A3,                       BAND_KU, 3490,(MS_U8*)"EXPRESS A3"} ,//    44    1
    {KU_3520_ATLANTIC_BIRD_2,              BAND_KU, 3520,(MS_U8*)"ATLANTIC BIRD 2"} ,//    45    9
    {KU_3560_AMOS_2_3,                          BAND_KU, 3560,(MS_U8*)"AMOS 2,3"} ,//    47    29
    {KU_703_NSS_703,                              BAND_KU,  703,(MS_U8*)"NSS 703"} ,//    19    23
    {KU_1380_TELSTAR_18,                       BAND_KU,  1380,(MS_U8*)"TELSTAR 18"},//
};
#define TOTAL_BUILDIN_SATELLITE_NUMBER         (sizeof(AntennaSatList_BuiltIn)/sizeof(Antenna_SatInfo))            // (47)

void MApp_DataBase_RestoreDefaultSatlite(void)
{
    MS_U16 i;
    Antenna_SatInfo *pstSatInfo;
    MS_SAT_PARAM stSATParam;
    MS_U8 u8SATIdx = 0;

    MApi_DB_SAT_ResetAllSATTable();
    for(i=0;i<TOTAL_BUILDIN_SATELLITE_NUMBER;i++)
    {
        pstSatInfo = (Antenna_SatInfo *)&AntennaSatList_BuiltIn[i];
        // add the SAT
        memset(&stSATParam,0,sizeof(MS_SAT_PARAM));
        //printf("---%s---\n",pstSatInfo->pSatName);
        strcpy((char*)stSATParam.aSatName,(char*)(pstSatInfo->pSatName)); // @FIXME: garry.xin

        // printf("\n-------u8SATIdx=%2bx---%s---\n",u8SATIdx,stSATParam.aSatName);
        stSATParam.e0V12VOnOff = EN_0V12V_ONOFF_OFF;
        stSATParam.e22KOnOff = EN_22K_AUTO;
        stSATParam.eSwt10Port = EN_SWT_PORT_OFF;
        stSATParam.eLNBPwrOnOff = EN_LNBPWR_13OR18V;
        stSATParam.eLNBType = (MS_EN_LNBTYPE)(AntennaSatList_BuiltIn[i].u16Band);
        //  stSATParam.eSwt10Port = EN_SWT_PORT_OFF;
        stSATParam.eSwt11Port = EN_SWT_PORT_OFF;
        if(AntennaSatList_BuiltIn[i].u16Band)
        {
        stSATParam.u16HiLOF = 10600;
        stSATParam.u16LoLOF = 9750;
        }
        else
        {
        stSATParam.u16HiLOF = 5150;
        stSATParam.u16LoLOF = 5150;
        }
        stSATParam.u8Position = 0;
        stSATParam.u16Angle = pstSatInfo->u16Angle;
        //print_SATParam(&stSATParam);

        //SetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP, m_acDTVProgramTableMap, sizeof(m_acDTVProgramTableMap));
        if(TRUE!= MApi_DB_SAT_AddSAT(&u8SATIdx, &stSATParam))
        {
            printf("Add sat %s failed\n",pstSatInfo->pSatName);
            continue;
        }
        //printf("\n-------u8SATIdx=%2bx---%s---\n",u8SATIdx,stSATParam.aSatName);
    }
}

void MApp_DataBase_RestoreDefault_DvbsSetting(void)
{
    stGenSetting.stDvbsSetting.u8Location = 0;

    stGenSetting.stDvbsSetting.stManualLocation.MyLongitude = 0;
    stGenSetting.stDvbsSetting.stManualLocation.MyLatitude = 0;
    stGenSetting.stDvbsSetting.g_sort_type = EN_SORT_BY_DEFAULT;


#if 0//(ENABLE_S2_CH_SWITCH)
    stGenSetting.stDvbsSetting.g_serviceTypeS2 = E_SERVICETYPE_DTV;
    stGenSetting.stDvbsSetting.wCurOrderOfTVS2 = 1;
    stGenSetting.stDvbsSetting.wCurOrderOfRADIOS2 = 1;
    stGenSetting.stDvbsSetting.wCurOrderOfdataS2 = 1;
#endif

#if 1//( ENABLE_API_DTV_SYSTEM_2015 )
    stGenSetting.stDvbsSetting.eCurServiceType = E_SERVICETYPE_DTV;
    stGenSetting.stDvbsSetting.u16CurDtvOrder = S2_DEFAULT_CURRENT_ORDER_TV;
    stGenSetting.stDvbsSetting.u16CurDtvDataOrder = S2_DEFAULT_CURRENT_ORDER_DATA;
    stGenSetting.stDvbsSetting.u16CurDtvRadioOrder = S2_DEFAULT_CURRENT_ORDER_RADIO;
#endif
}

#endif

//*************************************************************************
//Function name:        MApp_DataBase_RestoreDefaultValue
//Passing parameter:    none
//Return parameter:     none
//Description:          Restore default value to data base
//*************************************************************************
void MApp_DataBase_RestoreDefaultValue(U16 u16KeepSetting)
{
    EN_LANGUAGE eLanguge = GET_OSD_MENU_LANGUAGE();

    printf("\e[31;1m >> %s(0x%X) \33[m \n", __FUNCTION__, u16KeepSetting);

    /* Set entire database to 0 */
    if (!(RESTORE_KEEP_SYSTEM_PASSWORD& u16KeepSetting))
        memset(&stGenSetting, 0, RM_SIZE_GENSET);

    // keep OSD language
    SET_OSD_MENU_LANGUAGE(eLanguge);

    /* Restore default database version and check byte */
    stGenSetting.u8VersionCheck = DEFAULT_DATABASE_VERSION;
    stGenSetting.u8VersionCheckCom = DEFAULT_DATABASE_VERSION_COM;


    //*************************************************************************
    // Restore default SystemSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultSystem(u16KeepSetting);


    // Restore Video setting
    MApp_DataBase_RestoreDefaultVideo(DATA_INPUT_SOURCE_NUM);


    //*************************************************************************
    // Restore default AudioSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultAudio(FALSE);


    //*************************************************************************
    // Restore default scan menu setting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultScanMenu();

    //*************************************************************************
    // Restore default TimeSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultTime();

    //*************************************************************************
    // Restore default TimeSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultSSC();
  #if ENABLE_GAMMA_ADJUST
    //*************************************************************************
    // Restore default Gamma Table
    //*************************************************************************
    MApp_DataBase_RestoreDefaultGammaTable();
  #endif
  #if (ENABLE_NONLINEAR_CURVE)
    //*************************************************************************
    // Restore default NonLinerCurveSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultNonLinearCurve();
  #endif

  #if (ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION)
    MApp_InitOverScanData();
  #endif

  #if (ENABLE_FM_RADIO)
    MApp_FMRadio_DB_RestoreToDefault();
  #endif

    //*************************************************************************
    // Restore default Block Settings
    //*************************************************************************
    App_DataBase_RestoreDefaultBlock();

  #if ENABLE_ATSC
    //*************************************************************************
    // Restore default Close Caption
    //*************************************************************************
    MApp_DataBase_RestoreDefault_CaptionSetting();
  #endif

  #if (ENABLE_PIP)
    //*************************************************************************
    // Restore default PIP Settings
    //*************************************************************************
    if(IsPIPSupported())
    {
        MApp_DataBase_RestoreDefaultPIP();
    }
  #endif
#if ENABLE_ATSC
    //*************************************************************************
    // Restore default VChip Setting
    //*************************************************************************
    if(!(RESTORE_KEEP_SYSTEM_PASSWORD& u16KeepSetting))
    {
        MApp_DataBase_RestoreDefault_VChip();
        //MApp_DataBase_RestoreDefaultVChipRegion5();
        MApp_VChipRegion5_Save();
    }
#endif


  #if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
    //*************************************************************************
    // Restore default MM Last Memory Settings
    //*************************************************************************
    MApp_DataBase_RestoreDefaultMmLastMemorySetting();
  #endif

  #if ENABLE_DRM
    MApp_LoadDrmSetting();
  #endif

#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
    g_AudioOnly = AUDIO_ONLY_OFF;
    u32MonitorAudioOnlyTimer =0;
    fEnableAudioOnlyFunc = DISABLE;
    if(g_AudioOnly == AUDIO_ONLY_ON)
    {
        g_AudioOnly = AUDIO_ONLY_OFF;
        //MApi_PNL_SetBackLight(ENABLE);
    }
#endif

    MApp_DataBase_RestoreDefault_MiscSetting();

    MApp_DataBase_RestoreDefault_HDMISetting();

    //Clear UI display date
    g_u8TimeInfo_Flag = 0;
}

//*************************************************************************
//Function name:        MApp_DataBase_RestoreUserSettingDefaultValue
//Passing parameter:    none
//Return parameter:     none
//Description:          Restore user default value to data base
//*************************************************************************
void MApp_DataBase_RestoreUserSettingDefaultValue(U16 u16KeepSetting)
{
    EN_LANGUAGE eLanguge = GET_OSD_MENU_LANGUAGE();

    //printf("\e[31;1m >> %s(0x%X) \33[m \n", __FUNCTION__, u16KeepSetting);

    /* Set entire database to 0 */
    if (!(RESTORE_KEEP_SYSTEM_PASSWORD & u16KeepSetting))
    {
        memset(&stGenSetting, 0, RM_SIZE_GENSET);
    }
    // keep OSD language
    SET_OSD_MENU_LANGUAGE(eLanguge);

    //*************************************************************************
    // Restore default SystemSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultSystem(u16KeepSetting);


    //*************************************************************************
    // Restore default AudioSetting
    //*************************************************************************
    MApp_DataBase_RestoreDefaultAudio(FALSE);

#if ENABLE_ATSC
    //*************************************************************************
    // Restore default Close Caption
    //*************************************************************************
    MApp_DataBase_RestoreDefault_CaptionSetting();
#endif
}

//*************************************************************************
//Function name:        MApp_DataBase_RestoreUserSettingDefault
//Passing parameter:    u8RestoreMask
//Return parameter:     none
//Description:          Restore user default value
//*************************************************************************
void MApp_DataBase_RestoreUserSettingDefault(U8 u8RestoreMask)
{
    //printf("\e[31;1m >> %s(0x%X) \33[m \n", __FUNCTION__, u8RestoreMask);

    if(u8RestoreMask&RESTORE_USERSETTING)
    {
        //reset general user setting structure
        MApp_ResetGenUserSetting();

    #if (ENABLE_DVB)
      #if(ENABLE_API_DTV_SYSTEM)
        msAPI_CM_ResetDTVDataManager(TRUE);
      #endif

      #if ENABLE_OAD
        MApp_OAD_ResetInfo();
      #endif
    #endif
        msAPI_ATV_ResetATVDataManager();

    #if ENABLE_ATSC
        MApp_DB_ATSC_ResetAllChData();
    #endif

    #if 1//(EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
        //store to flash immediately
        MApp_DB_SaveDataBase_RightNow(SAVE_DB_FLAG_DEFAULT);
    #endif
    }
}

void MApp_DataBase_RestoreFactoryDefault(U8 u8RestoreMask)
{
    //printf("\e[31;1m >> %s(0x%X) \33[m \n", __FUNCTION__, u8RestoreMask);

    if (u8RestoreMask&RESTORE_GENSETTING)
    {
    #if(ENABLE_CEC)
      #if (CEC_VERSION_USING == CEC_NEW_VERSION)
        msAPI_CEC_ActionForCecOff();
      #endif
    #endif

        //reset general setting structure
        MApp_InitGenSetting();
    }

    if (u8RestoreMask&RESTORE_DATABASE)
    {
        //reset 64K database
    #if(ENABLE_API_DTV_SYSTEM)
        msAPI_CM_ResetDTVDataManager(TRUE);
    #endif

        msAPI_ATV_ResetATVDataManager();

    #if ENABLE_ATSC
        MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
        MApp_DB_ATSC_ResetAllChData();
        MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
        MApp_DB_ATSC_ResetAllChData();
    #endif


    #if (ENABLE_PIP)
        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&&(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))&&IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
        {
            MApp_RestoreAllModeTable(SUB_WINDOW);
        }
        else
    #endif
        {
            MApp_RestoreAllModeTable(MAIN_WINDOW);
        }

        MApp_SaveData_InitGenSettingExt();

    #if (ENABLE_S2)
        MApp_DataBase_RestoreDefaultSatlite();
    #endif
    }

#if 1//(EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
    //store to flash immediately
    MApp_DB_SaveDataBase_RightNow(SAVE_DB_FLAG_DEFAULT);
#endif

}

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
void MApp_DataBase_RestoreDefaultNetworkInfo(void)
{
    U8 i,j;
    for(i=0;i<SI_MAX_NETWORK;i++)
    {
        stGenSetting.g_Network_TS.astNetworkInfo[i].u16Network_ID = 0;
        stGenSetting.g_Network_TS.astNetworkInfo[i].bInValidNetwork = FALSE;
        for (j=0;j<SI_MAX_TS_IN_NETWORK;j++)
        {
            memset(stGenSetting.g_Network_TS.astNetworkInfo[i].astTSRFList[j].au8RF, 0, sizeof(U8)*SI_MAX_FREQUENCY_LIST);
            memset(stGenSetting.g_Network_TS.astNetworkInfo[i].astTSRFList[j].awCell, 0, sizeof(U16)*SI_MAX_FREQUENCY_LIST);
            stGenSetting.g_Network_TS.astNetworkInfo[i].astTSRFList[j].wTransportStream_ID = INVALID_TS_ID;
        }
        stGenSetting.g_Network_TS.astNetworkInfo[i].bNewTS = 0;
        stGenSetting.g_Network_TS.astNetworkInfo[i].bNewService = 0;
    }
}
#endif

#if ENABLE_CI
void MApp_DataBase_RestoreDefault_CI(void)
{
    memset((void *)&stGenSetting.g_CISetting, 0, sizeof(CI_SETTING));
}
#endif

#if ENABLE_CI && ENABLE_CI_PLUS
void MApp_DataBase_RestoreDefault_CIPlus(void)
{
    memset((void *)&stGenSetting.stCIPlusSetting, 0, sizeof(MS_CI_PLUS_SETTING));

    stGenSetting.stCIPlusSetting.u16OpChannelIdex = 0;
    stGenSetting.stCIPlusSetting.u16NormalChannelIndex = 0;

    stGenSetting.stCIPlusSetting.bInOpMenu = FALSE;
    stGenSetting.stCIPlusSetting.u8OpIndex = 0;
	stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = FALSE;

}
#endif

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
void MApp_DataBase_RestoreDefaultMmLastMemorySetting(void)
{
    memset((void *)&(stGenSetting.g_MmLastMemorySetting), 0, sizeof(MS_MM_LASTMEMORY_SETTING));
}
#endif

void MApp_DataBase_RestoreDefault_DebugSetting(void)
{
    printf("MApp_DataBase_RestoreDefault_DebugSetting()\n");
    stGenSetting.stDebugSetting.u8Flag1 = 0;
    stGenSetting.stDebugSetting.u8Flag2 = 2;
    stGenSetting.stDebugSetting.bKeyLoggerEnable = DISABLE;
}

#if ENABLE_3D_PROCESS
void MApp_DataBase_RestoreDefault_3DSetting(void)
{
    stGenSetting.st3DSetting.en3DType = EN_3D_BYPASS;
    stGenSetting.st3DSetting.en3DTo2DType= EN_3D_TO_2D_OFF;
    stGenSetting.st3DSetting.en3DDetectMode = EN_3D_DETECT_AUTO;
    stGenSetting.st3DSetting.en3DLRMode = EN_3D_LR_L;
    stGenSetting.st3DSetting.en3DHShiftMode = EN_3D_HSHIFT_MID;
    stGenSetting.st3DSetting.en3DViewPointMode = EN_3D_VIEW_POINT_MID;
}
#endif

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
void MApp_DataBase_RestoreDefault_CloseCaptionSetting(void)
{
    memset( &(DB_CC_SETTING), 0, sizeof(Stru_DB_CC_SETTING));

    DB_CC_SETTING.stCaptionSetting.u8CaptionServiceModeDTV = CS_OFF;
    DB_CC_SETTING.stCaptionSetting.u8CaptionServiceModeATV = CS_OFF;
    DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode = CS_OFF;

    //DB_CC_SETTING.stCaptionSetting.u8CCMode = 0; // todo:
    //DB_CC_SETTING.stCaptionSetting.u8CSOptionMode = 0; // todo:

    DB_CC_SETTING.enATVCaptionType = ATV_CAPTION_TYPE_OFF;

#if(BRAZIL_CC)
    DB_CC_SETTING.enDTVCaptionType = DTV_CAPTION_OFF;
#endif

}
#endif


void MApp_DataBase_RestoreDefault_HDMISetting(void)
{
#if ENABLE_CEC
    stGenSetting.stHDMISetting.g_bHdmiCecMode = DISABLE;
    stGenSetting.stHDMISetting.g_enHDMIARC = ENABLE;
    stGenSetting.stHDMISetting.g_bHdmiCecAutoTvOn = ENABLE;
    stGenSetting.stHDMISetting.g_bHdmiCecDeviceAutoStandby = ENABLE;
    stGenSetting.stHDMISetting.g_bHdmiCecDeviceControl = ENABLE;
    //stGenSetting.stHDMISetting.g_bHdmiCecSpeakerMode = ENABLE;
#endif

#if(ENABLE_EDID_SWITCH)
    stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[0] = E_USER_HDMI_EDID_1p4;
    stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[1] = E_USER_HDMI_EDID_1p4;
    stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[2] = E_USER_HDMI_EDID_1p4;
    stGenSetting.stHDMISetting.aeHDMI_Edid_Sel[3] = E_USER_HDMI_EDID_1p4;
#endif

}

#if(ENABLE_DTV_EPG)
void MApp_DataBase_RestoreDefault_ManualEvent(void)
{
#if(DB_MANUAL_EVENT_SAVE_IN_DB_GEN)
    memset( &(stGenSetting.stManualEventSetting), 0, SIZE_EPG_MANUAL_TIMER_EVENT);
#else

#endif
}
#endif

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
void MApp_DataBase_RestoreDefault_PcModeSetting(void)
{
    MApp_RestoreAllModeTable(MAIN_WINDOW);
}
#endif

#if(ENABLE_ATSC)

void MApp_DataBase_RestoreDefault_CaptionSetting(void)
{
//*************************************************************************
// Restore default Caption Setting
//*************************************************************************
#if (PARSING_CC_AUTO708TO608)
    stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV = CS_SERVICE1;
    stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV = CS_CC1;
    stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CS_OFF;
#else
    stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV = CS_OFF;
    stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV = CS_OFF;
    stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CS_OFF;
#endif
    memset(&stGenSetting.g_CaptionSetting.astCaptionOptionMenu, 0, sizeof(stGenSetting.g_CaptionSetting.astCaptionOptionMenu));
    memset(&stGenSetting.g_CaptionSetting.astCaptionOptionCustom, 0xFF, sizeof(stCaptionSettingOption_Type));
    stGenSetting.g_CaptionSetting.u8CSOptionMode = CAPTIONMENU_OPTIONMODE_DEFAULT;
    stGenSetting.g_CaptionSetting.u8CCMode = CAPTIONMENU_MODE_OFF;
}

void MApp_DataBase_RestoreDefault_VChip(void)
{
    memset(&stGenSetting.g_VChipSetting, 0, sizeof(MS_VCHIP_SETTING));
    stGenSetting.g_VChipSetting.u16VChipPassword = 0;
    stGenSetting.g_VChipSetting.u8VChipLockMode = 0;
#if ENABLE_UNRATED_LOCK
    stGenSetting.g_VChipSetting.u8UnRatedLock = 0;
#endif

    stGenSetting.g_VChipSetting.u8InputBlockItem = 0;
    stGenSetting.g_VChipSetting.u8VChipMPAAItem = VCHIP_MPAARATING_NA;
    stGenSetting.g_VChipSetting.u8VChipCEItem = VCHIP_ENGRATING_EXEMPT;
    stGenSetting.g_VChipSetting.u8VChipCFItem = VCHIP_FRERATING_EXEMPT;


    MApp_DataBase_RestoreDefault_VChipRegion5();
}

void MApp_DataBase_RestoreDefault_VChipRegion5(void)
{
    //g_u8CurrentRRT_Dimension = 0;
    g_stDtvAtscInfo._u8CurrentRRT_Dimension = 0;
    //g_u8CurrentRRT_Option = 0;
    g_stDtvAtscInfo._u8CurrentRRT_Option = 0;

    memset(&stGenSettingVchipRegion5, 0, sizeof(MS_REGION5_RATING));

    //stGenSetting.g_SysSetting.u8NoSavedRRT = 0;
    //stGenSetting.g_SysSetting.u8IdxLastSavedRRT = 0;
    stGenSettingVchipRegion5.u8VersionNo=INVALID_VERSION_NUM;
    stGenSettingVchipRegion5.u8NoDimension = 0;
}
#endif


#undef MAPP_RESTORETODEFAULT_C
