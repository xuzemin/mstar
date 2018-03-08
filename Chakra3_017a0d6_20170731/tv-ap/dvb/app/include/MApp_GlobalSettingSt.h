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

#ifndef MAPP_GLOBALSETTINGST_H
#define MAPP_GLOBALSETTINGST_H

/********************************************************************************/
/*                              Include files                                   */
/********************************************************************************/
#include "Board.h"
#include "datatype.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "apiXC_Cus.h"
#include "apiPNL.h"
#include "Panel.h"
#include "msAPI_Global.h"
//#include "msAPI_Tuner.h"
#include "msAPI_Mode.h"
#include "msAPI_Power.h"
#if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
#include "drvAUDIO_if.h"
#endif

#if ((BRAZIL_CC)|| (ATSC_CC == ATV_CC))
#include "msAPI_cc_sysinfo.h"
#endif
#include "msAPI_MW_GlobalSt.h"
#include "msAPI_FreqTableCommon.h"
#include "MApp_GlobalSettingSt_Common.h"

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "mapp_si.h"
#endif

#if (ENABLE_CI)
#include "msAPI_CI.h"
#endif
#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
#include "drvUrsa6M30.h"
#endif
#if (ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif

#include "MApp_UiMediaPlayer_Define.h"//DRM


#include "MApp_GlobalSettingSt_tv.h"

#if (ENABLE_ATSC)
#include "MApp_GlobalSettingSt_ATSC.h"
#endif

#if(ENABLE_FM_RADIO)
#include "MApp_Radio_DB.h"
#endif


/********************************************************************************/
/*                                 Macro                                        */
/********************************************************************************/
#ifdef INTERFACE
#undef INTERFACE
#endif

#ifdef _MAPP_GLOBAL_SETTING_C_
    #define INTERFACE
#else
    #define INTERFACE extern
#endif


//--------------------------------------------------------------------------------

/* Move to msAPI_Global.h
#if (DVB_T_C_DIFF_DB || ENABLE_T_C_COMBO)
  #if(ENABLE_S2)
    #define IsDVBCInUse()   (((!IsS2InUse())&&(stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType == EN_DVB_C_TYPE)) ? 1 :0)
  #else
    #define IsDVBCInUse()   ((stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType == EN_DVB_C_TYPE) ? 1 :0)
  #endif
#else
    #define IsDVBCInUse()   0
#endif
*/

//--------------------------------------------------------------------------------


#define MAX_STD_MODE_NUM                (MD_STD_MODE_MAX_INDEX)
#define MAX_USER_MODE_NUM               10//20
#define MAX_MODE_NUM                    (MAX_STD_MODE_NUM+MAX_USER_MODE_NUM)

#define MIN_STD_COMPO_NUM               (YPBPR_MD_START)
#define MAX_STD_COMPO_NUM               (YPBPR_MD_END)


#define MENU_LANGUAGE_FONT_ENGX2        (1)

#if(UI_SKIN_SEL== UI_SKIN_1366X768X565)
#define SCREEN_SAVER_FRAME_WIDTH        300
#define SCREEN_SAVER_FRAME_HEIGHT       100
#elif(UI_SKIN_SEL== UI_SKIN_1920X1080X565)
#define SCREEN_SAVER_FRAME_WIDTH        421
#define SCREEN_SAVER_FRAME_HEIGHT       140
#else
#define SCREEN_SAVER_FRAME_WIDTH        300
#define SCREEN_SAVER_FRAME_HEIGHT       100
#endif

//#if (ENABLE_PIP)
#define SUB_SCREEN_SAVER_FRAME_WIDTH    200
#define SUB_SCREEN_SAVER_FRAME_HEIGHT   60

#define SCREEN_SAVER_PIP_FRAME_WIDTH    347
#define SCREEN_SAVER_PIP_FRAME_HEIGHT   195
//#endif

#define MS_COLOR_TEMP_COUNT 4

#define URSA_SSC_ENABLE     0


#ifdef DISABLE_COMPONENT_VBI
#define IsVBISrcInUse()        (!IsVgaInUse() && !IsHDMIInUse() && !IsStorageInUse() && !IsYPbPrInUse())
#else
#define IsVBISrcInUse()        (!IsVgaInUse() && !IsHDMIInUse() && !IsStorageInUse() )
#endif

#if ENABLE_GAMMA_ADJUST
#define GAMMA_ADJUST_NUM    11 //5%,10%,20%,30%,40%,50%,60%,70%,80%,90%,100%
#endif
//--------------------------------------------------------------------------------

typedef U16 TypCheckSum;

//#define ATTR_PACK __attribute__ ((__packed__))


/********************************************************************************/
/*                                 Enum                                         */
/********************************************************************************/
//DVB Source information
typedef enum
{
//#if ENABLE_S2
    UI_INPUT_SOURCE_S2,
//#endif

//#if ENABLE_ATSC
    UI_INPUT_SOURCE_ATSC,
//#endif

//#if ENABLE_DVBT
    UI_INPUT_SOURCE_DVBT,
//#endif

//#if ENABLE_DVBC
    UI_INPUT_SOURCE_DVBC,
//#endif

//#if ENABLE_ISDBT
    UI_INPUT_SOURCE_ISDBT,
//#endif

//#if ENABLE_DTMB
    UI_INPUT_SOURCE_DTMB,
//#endif


    UI_INPUT_SOURCE_ATV,


#if (INPUT_SCART_VIDEO_COUNT >= 1)
        UI_INPUT_SOURCE_SCART,
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 2)
        UI_INPUT_SOURCE_SCART2,
#endif

#if (INPUT_YPBPR_VIDEO_COUNT>=1)
        UI_INPUT_SOURCE_COMPONENT,      // VIDEO - YPbPr
#endif

#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
        UI_INPUT_SOURCE_COMPONENT2,
#endif

        UI_INPUT_SOURCE_RGB,            // PC - VGA

#if (INPUT_HDMI_VIDEO_COUNT >= 1)
        UI_INPUT_SOURCE_HDMI,           // HDMI
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 2)
        UI_INPUT_SOURCE_HDMI2,
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 3)
        UI_INPUT_SOURCE_HDMI3,
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 4)
        UI_INPUT_SOURCE_HDMI4,
#endif

        UI_INPUT_SOURCE_HDMI_END,

#if (INPUT_AV_VIDEO_COUNT >= 1)
        UI_INPUT_SOURCE_AV = UI_INPUT_SOURCE_HDMI_END,      // VIDEO - CVBS
#endif

#if (INPUT_AV_VIDEO_COUNT >= 2)
        UI_INPUT_SOURCE_AV2,
#endif

#if (INPUT_AV_VIDEO_COUNT >= 3)
        UI_INPUT_SOURCE_AV3,
#endif

#if (INPUT_SV_VIDEO_COUNT >= 1)
        UI_INPUT_SOURCE_SVIDEO,
#endif

#if ((INPUT_SV_VIDEO_COUNT >= 2))
        UI_INPUT_SOURCE_SVIDEO2,
#endif

#if (ENABLE_DMP || BLOADER)
        UI_INPUT_SOURCE_DMP,
#endif
#if (ENABLE_FM_RADIO)
        UI_INPUT_SOURCE_FMRADIO,
#endif

#if GAME_ENABLE
        UI_INPUT_SOURCE_GAME,
#endif

    UI_INPUT_SOURCE_NONE,
    UI_INPUT_SOURCE_NUM = UI_INPUT_SOURCE_NONE,
} E_UI_INPUT_SOURCE;

#if 1 // Refine by Daniel

#define SERVICE_TYPE_INVALIDE   E_SERVICETYPE_INVALID
#define SERVICE_TYPE_DTV        E_SERVICETYPE_DTV
#define SERVICE_TYPE_RADIO      E_SERVICETYPE_RADIO
#define SERVICE_TYPE_ATV        E_SERVICETYPE_ATV
#define SERVICE_TYPE_DATA       E_SERVICETYPE_DATA
#define SERVICE_TYPE_TV         E_SERVICETYPE_UNITED_TV
#define EN_SERVICE_TYPE         MEMBER_SERVICETYPE

#else
typedef enum
{
    SERVICE_TYPE_INVALIDE = E_SERVICETYPE_INVALID,
    SERVICE_TYPE_DTV      = E_SERVICETYPE_DTV,
    SERVICE_TYPE_RADIO    = E_SERVICETYPE_RADIO,
    SERVICE_TYPE_ATV      = E_SERVICETYPE_ATV,
  #if NORDIG_FUNC //for Nordig Spec v2.0
    SERVICE_TYPE_DATA     = E_SERVICETYPE_DATA,
  #endif
    SERVICE_TYPE_TV       = E_SERVICETYPE_UNITED_TV,
} EN_SERVICE_TYPE;
#endif

//>>wht121101_1
typedef enum
{
    EN_OSD_TIME_5=1,
    EN_OSD_TIME_10,
    EN_OSD_TIME_15,
    EN_OSD_TIME_ALWAYS,
    EN_OSD_TIME_NUM
}EN_OSD_TIME;

//>>wht121101_1
typedef enum
{
    EN_FRONT_DESKTOP = 1,
    EN_FRONT_CEILING,
    EN_REAR_DESKTOP,
    EN_REAR_CEILING,
    EN_PROJECTION_TYPE_NUM
}EN_PROJECTION_TYPE;
//<<wht121101_1

// Why relative to chip?
#if 0
    ( (UI_SKIN_SEL == UI_SKIN_960X540X565)   \
  && ( (CHIP_FAMILY_TYPE != CHIP_FAMILY_MILAN)  \
     &&(CHIP_FAMILY_TYPE != CHIP_FAMILY_MARLON) \
     &&(CHIP_FAMILY_TYPE != CHIP_FAMILY_WHISKY) \
     ) \
   )

typedef enum _EN_MENU_LANGUAGE
{
    LANGUAGE_CZECH,       //Minimum of OSD menu, Audio, and Subtitle Language
    LANGUAGE_DANISH,
    LANGUAGE_GERMAN,
    LANGUAGE_ENGLISH,
    LANGUAGE_SPANISH,
    LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
    LANGUAGE_RUSSIAN,
    LANGUAGE_ROMANIAN,
   
#if 1 //smc.chy 2011/02/25  use 
    LANGUAGE_ARABIC,
    LANGUAGE_HEBREW,
    LANGUAGE_KURDISH,
    LANGUAGE_PARSI,
    LANGUAGE_THAI,
#else
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
#endif
    LANGUAGE_SLOVAK,
#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    LANGUAGE_CHINESE,
    LANGUAGE_MENU_MAX = LANGUAGE_CHINESE,        // OSD Menu Language Maximum
#else
    LANGUAGE_MENU_MAX = LANGUAGE_SLOVAK,        // OSD Menu Language Maximum
#endif
    LANGUAGE_GAELIC,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,
    LANGUAGE_AUDIO_MAX_EU = LANGUAGE_IRISH,      // Audio Language Europe Maximum
    LANGUAGE_KOREAN,
    LANGUAGE_JAPAN,
    LANGUAGE_HINDI,
    LANGUAGE_MAORI,
    LANGUAGE_MANDARIN,
    LANGUAGE_CANTONESE,
    LANGUAGE_AUDIO_MAX_NZ = LANGUAGE_CANTONESE,      // Audio Language New Zealannd Maximum
    LANGUAGE_TURKISH,
    LANGUAGE_NETHERLANDS,

#if 1 //smc.chy 2011/02/25
     LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    
#else
    LANGUAGE_ARABIC,
    LANGUAGE_HEBREW,
    LANGUAGE_KURDISH,
    LANGUAGE_PARSI,
    LANGUAGE_THAI,
#endif
    LANGUAGE_QAA,
    LANGUAGE_UND,     //Italy CI Certificate
    LANGUAGE_UNKNOWN, //move to hear to avoid haveing same value as spanish.
    LANGUAGE_AUDIO1,
    LANGUAGE_AUDIO2,
    LANGUAGE_AUDIO3,
    LANGUAGE_AUDIO4,
    LANGUAGE_AUDIO5,
    LANGUAGE_AUDIO6,
    LANGUAGE_ENGX2 = MENU_LANGUAGE_FONT_ENGX2,
    LANGUAGE_NONE = 0xFF,
} EN_LANGUAGE;


#else

typedef enum _EN_MENU_LANGUAGE
{
    LANGUAGE_CZECH,       //Minimum of OSD menu, Audio, and Subtitle Language
    LANGUAGE_DANISH,
    LANGUAGE_GERMAN,
    LANGUAGE_ENGLISH,
    LANGUAGE_SPANISH,
    LANGUAGE_GREEK,
    LANGUAGE_FRENCH,
    LANGUAGE_KOREA,
    LANGUAGE_CROATIAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_HUNGARIAN,
    LANGUAGE_DUTCH,
    LANGUAGE_NORWEGIAN,
    LANGUAGE_POLISH,
    LANGUAGE_PORTUGUESE,
    LANGUAGE_RUSSIAN,
    LANGUAGE_ROMANIAN,
    LANGUAGE_SLOVENIAN,
    LANGUAGE_SERBIAN,
    LANGUAGE_FINNISH,
    LANGUAGE_SWEDISH,
    LANGUAGE_BULGARIAN,
    LANGUAGE_SLOVAK,
    LANGUAGE_THAI,
    LANGUAGE_CHINESE,
    LANGUAGE_CHINESE_TRAD,
    LANGUAGE_HINDI,
    LANGUAGE_INDONESIA,
    LANGUAGE_MALAYSIA,
    LANGUAGE_ARABIC,
    LANGUAGE_VIETNAM,
    LANGUAGE_GHANA,
    LANGUAGE_URDU,
    LANGUAGE_TELUGU,
    LANGUAGE_TAMIL,
    LANGUAGE_MARATHI,
    LANGUAGE_BENGALI,
    LANGUAGE_ASSAMESE,
    LANGUAGE_GUJARATI,
    LANGUAGE_KANNADA,
    LANGUAGE_MALAYALAM,
    LANGUAGE_PUNJABI,
    LANGUAGE_UYGHUR,
    LANGUAGE_KHMER,
    LANGUAGE_LAO,
    LANGUAGE_MYANMAR,
    LANGUAGE_SWAHILI,

    LANGUAGE_GAELIC,
    LANGUAGE_AKAN,
    LANGUAGE_EWE,
    LANGUAGE_TWI,
    LANGUAGE_NZEMA,
    LANGUAGE_HAUSA,
    LANGUAGE_KASEM,
    LANGUAGE_WELSH,
    LANGUAGE_IRISH,
    LANGUAGE_KOREAN,
    LANGUAGE_JAPAN,
    LANGUAGE_MAORI,
    LANGUAGE_MANDARIN,
    LANGUAGE_CANTONESE,
    LANGUAGE_TURKISH,
    LANGUAGE_NETHERLANDS,
    LANGUAGE_GALLEGAN,
    LANGUAGE_BASQUE,
    LANGUAGE_LUXEMBOURGISH,
    LANGUAGE_ICELANDIC,
    LANGUAGE_LATVIAN,
    LANGUAGE_ESTONIAN,
    LANGUAGE_LITHUANIAN,
    LANGUAGE_UKRANIAN,
    LANGUAGE_BELARUSIAN,
    LANGUAGE_SPANISH_CAT,
    LANGUAGE_SAMI,
    LANGUAGE_HEBREW,
    LANGUAGE_KURDISH,
    LANGUAGE_PARSI,
    LANGUAGE_QAA,
    LANGUAGE_QAB,
    LANGUAGE_QAC,
    LANGUAGE_SGA,
    LANGUAGE_MAX = LANGUAGE_SGA,

    LANGUAGE_UND,     //Italy CI Certificate
    LANGUAGE_UNKNOWN, //move to hear to avoid haveing same value as spanish.
    LANGUAGE_AUDIO1,
    LANGUAGE_AUDIO2,
    LANGUAGE_AUDIO3,
    LANGUAGE_AUDIO4,
    LANGUAGE_AUDIO5,
    LANGUAGE_AUDIO6,
    LANGUAGE_ENGX2 = MENU_LANGUAGE_FONT_ENGX2,
    LANGUAGE_NONE = 0xFF,
} EN_LANGUAGE;

#define ENABLE_DISPLAY_EXT_LANGUAGE
#define ENABLE_LANGUAGE_TAMIL

#endif

#define LANGUAGE_SUBTITLE_MAX_EU LANGUAGE_MAX   // Subtitle Language Europe Maximum
#define LANGUAGE_SUBTITLE_MAX_NZ LANGUAGE_MAX   // Subtitle Language New Zealannd Maximum

#if (ENABLE_DVB_TAIWAN_APP&&CHINESE_BIG5_FONT_ENABLE)
#define LANGUAGE_DEFAULT LANGUAGE_CHINESE
#else
#define LANGUAGE_DEFAULT LANGUAGE_ENGLISH
#endif



#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
typedef enum _EN_OSD_CERTIFICATION_SETTING
{
    OSD_CERTIFICATION_OTHER                 ,//= E_OTHER,
    OSD_CERTIFICATION_UNITYMEDIA            ,//= E_UNITYMEDIA,
    OSD_CERTIFICATION_ZIGGO                 ,//= E_ZIGGO,
    OSD_CERTIFICATION_NUMS,
} EN_OSD_CERTIFICATION_SETTING;

typedef enum _EN_OSD_UNITYMEDIA_COUNTRY_SETTING
{
    OSD_UNITYMEDIA_COUNTRY_GERMANY         = OSD_COUNTRY_GERMANY,
    OSD_UNITYMEDIA_COUNTRY_NUMS,
}EN_OSD_UNITYMEDIA_COUNTRY_SETTING;

typedef enum _EN_OSD_ZIGGO_COUNTRY_SETTING
{
    OSD_ZIGGO_COUNTRY_NETHERLANDS         = OSD_COUNTRY_NETHERLANDS,
    OSD_ZIGGO_COUNTRY_NUMS,
}EN_OSD_ZIGGO_COUNTRY_SETTING;

#endif

//Tune Type Index
typedef enum _EN_OSD_TUNE_TYPE_SETTING
{
    OSD_TUNE_TYPE_DTV_PLUS_ATV,
    OSD_TUNE_TYPE_DTV_ONLY,
    OSD_TUNE_TYPE_ATV_ONLY,
    OSD_TUNE_TYPE_NUMS
}EN_OSD_TUNE_TYPE_SETTING;

//DVBC Scan Type Index
//#if ENABLE_T_C_COMBO
typedef enum _EN_OSD_DVBC_SCAN_TYPE
{
    OSD_DVBC_TYPE_FULL,
    OSD_DVBC_TYPE_NETWOEKSCAN,
    OSD_DVBC_TYPE_NUMS
}EN_OSD_DVBC_SCAN_TYPE;
//#endif

// ADC setting index
typedef enum _AdcSetIndexType
{
    ADC_SET_VGA,
    ADC_SET_YPBPR_SD,
    ADC_SET_YPBPR_HD,
    ADC_SET_SCART_RGB,
    ADC_SET_NUMS
}E_ADC_SET_INDEX;


typedef enum
{
    CH_TYPE_DTV,
    CH_TYPE_ATV,
    CH_TYPE_NUMS
} EN_CH_TYPE;


typedef enum
{
    SCAN_TYPE_AUTO,     // DVBT/DTMB/DVBC
    SCAN_TYPE_MANUAL,
#if(ENABLE_S2)
    S2_SCAN_TYPE_AUTO,
    S2_SCAN_TYPE_MANUAL,
    S2_SCAN_TYPE_BLIND,
    S2_SCAN_TYPE_NETWORK,
#if(ENABLE_S2_FAST_SCAN)
    S2_SCAN_TYPE_FAST,
#endif
#endif
#if ENABLE_DVBC
    SCAN_TYPE_NETWORK,
#endif
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    SCAN_TYPE_UPDATE_MUX,
#endif
    SCAN_TYPE_NUM
} EN_SCAN_TYPE;


typedef enum
{
    ATV_MAN_SCAN_TYPE_ONECH,
    ATV_MAN_SCAN_TYPE_CHNUM,
} EN_ATV_MAN_SCAN_TYPE;


typedef enum
{
    ATV_MAN_SCAN_UP,
    ATV_MAN_SCAN_DOWN,
} EN_ATV_MAN_SCAN_DIR;

typedef enum
{
    FM_SCAN_TYPE_ONECH,
    FM_SCAN_TYPE_ALL,
} EN_FM_SCAN_TYPE;

typedef enum
{
    EN_E5_KeyLock_Off,
    EN_E5_KeyLock_On,
    EN_E5_KeyLock_Num
} EN_MENU_E5_KeyLock;

typedef enum
{
    CLEAR_VCH_DB,
    CLEAR_VCH_DB_AND_SET_FACTORY_VCH,
}EN_VCH_DB_CLEAR_TYPE;

typedef enum
{
    MS_COLOR_TEMP_MIN,
    MS_COLOR_TEMP_COOL = MS_COLOR_TEMP_MIN,
    MS_COLOR_TEMP_MEDIUM,
    MS_COLOR_TEMP_WARM,
#if(MS_COLOR_TEMP_COUNT ==4)
    MS_COLOR_TEMP_USER,
#endif
    MS_COLOR_TEMP_MAX = MS_COLOR_TEMP_USER
} EN_MS_COLOR_TEMP;

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
typedef enum
{
    EN_MFC_Demo_On,
    EN_MFC_Demo_Top,
    EN_MFC_Demo_Down,
    EN_MFC_Demo_Left,
    EN_MFC_Demo_Right,
    EN_MFC_Demo_Off,
    EN_MFC_Demo_Num, // EN_MFC_Demo Max
    EN_MFC_Demo_Def = EN_MFC_Demo_Off
}EN_MFC_DEMO;

typedef enum
{
    EN_MFC_Strength_Off,
    EN_MFC_Strength_Weak,
    EN_MFC_Strength_Normal,
    EN_MFC_Strength_Strong,
    EN_MFC_Strength_Num, // EN_MFC_Strength Max
    EN_MFC_Strength_Def = EN_MFC_Strength_Off,
}EN_MFC_Strength;
#endif

typedef enum //anvi cec
{
    EN_E4_HDMICEC_Off,
    EN_E4_HDMICEC_On,
    EN_E4_HDMICEC_Num
} EN_MENU_E4_HMDICEC;

typedef enum
{
    PICTURE_MIN,
    PICTURE_DYNAMIC = PICTURE_MIN,
    PICTURE_NORMAL,
    PICTURE_MILD,
    PICTURE_USER,
    #if PICTURE_USER_2
    PICTURE_USER2,
    #endif
    PICTURE_NUMS
} EN_MS_PICTURE;

#if (ENABLE_HDR)
typedef enum
{
    EN_HDR_MIN,
    EN_HDR_OFF = EN_HDR_MIN,
    EN_HDR_AUTO,
    EN_HDR_LOW,
    EN_HDR_MIDDLE,
    EN_HDR_HIGH,
    EN_HDR_REF,
    EN_HDR_NUMS = EN_HDR_REF,
}EN_MS_HDR;
#endif

#if ENABLE_GAMMA_ADJUST
typedef enum
{
  MS_GAMMAADJUST_MIN,
  MS_GAMMAADJUST_5 = MS_GAMMAADJUST_MIN,  //5%
  MS_GAMMAADJUST_10,                      //10%
  MS_GAMMAADJUST_20,                      //20%
  MS_GAMMAADJUST_30,                      //30%
  MS_GAMMAADJUST_40,                      //40%
  MS_GAMMAADJUST_50,                      //50%
  MS_GAMMAADJUST_60,                      //60%
  MS_GAMMAADJUST_70,                      //70%
  MS_GAMMAADJUST_80,                      //80%
  MS_GAMMAADJUST_90,                      //90%
  MS_GAMMAADJUST_100,                     //100%
  MS_GAMMAADJUST_MAX = MS_GAMMAADJUST_100,
} EN_MS_GAMMA_ADJUST;
#endif

typedef enum
{
    MS_BLACK_LEVEL_MIN,
    MS_BLACK_LEVEL_AUTO = MS_BLACK_LEVEL_MIN,
    MS_BLACK_LEVEL_LOW ,
    MS_BLACK_LEVEL_HIGH,
    MS_BLACK_LEVEL_NUM
} EN_MS_BLACK_LEVEL;


//#if (ENABLE_PIP)
typedef enum
{
    EN_PIP_MODE_OFF,
    EN_PIP_MODE_PIP,
    EN_PIP_MODE_POP,
    EN_PIP_MODE_POP_FULL,
    EN_PIP_MODE_MAX = EN_PIP_MODE_POP_FULL,
} EN_PIP_MODE;

typedef enum
{
    EN_PIP_SIZE_SMALL,
    EN_PIP_SIZE_MEDIUM,
    EN_PIP_SIZE_LARGE,
    EN_PIP_SIZE_INVALID,
} EN_PIP_SIZE;

typedef enum
{
    EN_PIP_SOUND_SRC_MAIN,
    EN_PIP_SOUND_SRC_SUB,
    EN_PIP_SOUND_SRC_INVALID,
} EN_PIP_SOUND_SRC;

typedef enum
{
    EN_PIP_POSITION_LEFT_TOP,
    EN_PIP_POSITION_RIGHT_TOP,
    EN_PIP_POSITION_LEFT_BOTTOM,
    EN_PIP_POSITION_RIGHT_BOTTOM,
    //EN_PIP_POSITION_USER,             /* We do not support user-defined position */
    EN_PIP_POSITION_INVALID,
} EN_PIP_POSITION;
//#endif
#if (ENABLE_SW_CH_FREEZE_SCREEN)
typedef enum
{
    ATV_SWITCH_CH_BLACK_SCREEN,
    ATV_SWITCH_CH_FREEZE_SCREEN,
    ATV_SWITCH_CH_NUMS,
    ATV_SWITCH_CH_DEFAULT=ATV_SWITCH_CH_BLACK_SCREEN,
} EN_ATV_SWITCH_CH_MODE;
#endif

#if ENABLE_DESIGN_POWER_ON_MODE
typedef enum
{
    POWERON_MODE_SAVE,
    POWERON_MODE_OFF,
    POWERON_MODE_ON,
    POWERON_MODE_NUMS
}POWERON_MODE_TYPE;
#endif

#if  ENABLE_3D_PROCESS
typedef enum
{
    EN_3D_BYPASS        = 0,   //2D
    EN_3D_FRAME_PACKING = 1,
    EN_3D_SIDE_BY_SIDE  = 2,
    EN_3D_TOP_BOTTOM    = 3,
    EN_3D_LINE_ALTERNATIVE = 4,
    EN_3D_FRAME_ALTERNATIVE = 5,
    EN_3D_2DConvertTo3D = 6,
    //EN_3D_SENSIO,
    EN_3D_FRAME_L       = 7,  //For L only (3D to 2D)
    EN_3D_TYPE_NUM
} EN_3D_TYPE;
#if 0
typedef enum
{
    EN_3D_TO_2D_OFF,
    EN_3D_TO_2D_FRAME_PARKING,
    EN_3D_TO_2D_SIDE_BY_SIDE,
    EN_3D_TO_2D_TOP_BOTTOM,
    EN_3D_TO_2D_LINE_BY_LINE,
    EN_3D_TO_2D_FRAME_ALTERNATIVE,
    EN_3D_TO_2D_TYPE_NUM
} EN_3D_TO_2D_TYPE;
#else
typedef enum
{
    EN_3D_TO_2D_OFF,
    EN_3D_TO_2D_ON,
    EN_3D_TO_2D_TYPE_NUM
} EN_3D_TO_2D_TYPE;
#endif
typedef enum
{
    EN_3D_DETECT_AUTO,
    EN_3D_DETECT_MANUAL,
    EN_3D_DETECT_NUM
} EN_3D_DETECT_MODE;
typedef enum
{
    EN_3D_LR_L,
    EN_3D_LR_R,
    EN_3D_LR_NUM
} EN_3D_LR_MODE;

typedef enum
{
    EN_3D_HSHIFT_WEAK,
    EN_3D_HSHIFT_MID,
    EN_3D_HSHIFT_STRONG,
    EN_3D_HSHIFT_NUM
} EN_3D_HSHIFT_MODE;

typedef enum
{
    EN_3D_VIEW_POINT_WEAK,
    EN_3D_VIEW_POINT_MID,
    EN_3D_VIEW_POINT_STRONG,
    EN_3D_VIEW_POINT_NUM
} EN_3D_VIEW_POINT_MODE;

#if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
typedef enum
{
    EN_6M30_MIRROR_ON,
    EN_6M30_MIRROR_OFF,
    EN_6M30_MIRROR_NUM
} EN_6M30_MIRROR_MODE;
#endif
#endif

/********************************************************************************/
/*                              Structure Type                                  */
/********************************************************************************/
/*
    The BBE, SRS, VDS and VSPK mode number is mapped to
    En_DVB_advsndType enumeration in drvAudioProcessor.h
*/
typedef enum
{
    #define SURROUND_SYSTEM_TYPE_MASK 0x07
    SURROUND_SYSTEM_OFF = 0x00,

    #define BBE_MODE_BIT 0x10        //BBE : 0 , Viva : 1
    #define BBE_MODE 0
    #define VIVA_MODE 1
    SURROUND_SYSTEM_BBE = 0x01,

    #define DIALOG_CLARITY_BIT 0x10  //enable : 1 , disable : 0
    #define TRUBASS_BIT 0x20         //enable : 1 , disable : 0
    SURROUND_SYSTEM_SRS = 0x02,

    SURROUND_SYSTEM_VDS = 0x03,

    #define WIDE_MODE_BIT 0x10       // reference : 0 , wind : 1
    #define SURROUND_MODE_BIT 0x20   // movie : 0 , music : 1
    #define WIDE_MODE 1
    #define REFERENCE_MODE 0
    #define SURROUND_MODE_MOVIE 0
    #define SURROUND_MODE_MUSIC 1
    SURROUND_SYSTEM_VSPK = 0x04,

    SURROUND_SYSTEM_SURROUNDMAX = 0x05,
   #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
    SURROUND_SYSTEM_DBX = 0x06,
   #endif

    SURROUND_SYSTEM_NUMS,
} EN_SURROUND_SYSTEM_TYPE;

typedef struct
{
    U8 Bass;
    U8 Treble;
    U8 u8120HZ;//120HZ
    U8 u8500HZ; //500HZ
    U8 u8_1_dot_5_KHZ;///1.5KHZ
    U8 u8_5KHZ;//5KHZ
    U8 u810KHZ; //10KHZ
    BOOLEAN UserMode;
    U8 Balance;
    EN_AUD_MODE      enSoundAudioChannel;
} stSoundModeSeting;

#define ST_AUDIO_PEQ stGenSetting.g_SoundSetting.astSoundPEqSetting
typedef struct
{
    U16 u16_Fo1Value;
    //U16 u16_Fo1_2Value;
    U16 u16_Fo2Value;
    //U16 u16_Fo2_2Value;
    U16 u16_Fo3Value;
    //U16 u16_Fo3_2Value;
    U8 u8_Gain1Value;
    U8 u8_Gain2Value;
    U8 u8_Gain3Value;
    U8 u8_Q1Value;
    U8 u8_Q2Value;
    U8 u8_Q3Value;
    U8 u8_PEQOnOff;
} stSoundPEqSetting;

typedef struct _SoundSettingType
{
    U16    soundSettingCS; // check sum <<checksum should be put at top of the struct, do not move it to other place>>

    /* ========================
        Sound Mode Enumeration
        ======================== */
    EN_SOUND_MODE     SoundMode;

    /* ========================
        The settings for each sound mode
        ======================== */
    stSoundModeSeting astSoundModeSetting[SOUND_MODE_NUM];
     /* ========================
        Surround Sound Mode
        ======================== */
    EN_SURROUND_SYSTEM_TYPE SurroundSoundMode;

    EN_SURROUND_TYPE  Surround;
    BOOLEAN           bEnableAVC;
    U8                Volume;
    #ifdef PRI_FACTORY
    U8                NLVolume1;
    U8                NLVolume25;
    U8                NLVolume50;
    U8                NLVolume100;
    #endif
    U8                Balance;
    U8                Primary_Flag;
    U8                enSoundAudioLan1;  //EN_LANGUAGE
    U8                enSoundAudioLan2;  //EN_LANGUAGE
    U8 MUTE_Flag;     // for ATSC_TRUNK
    EN_AUD_MODE       enSoundAudioChannel;
    BOOLEAN           bEnableAD;
    U8 ADVolume;
    EN_SOUND_AD_OUTPUT ADOutput;
    /* ========================
    The settings for PEQ
    ======================== */
    stSoundPEqSetting  astSoundPEqSetting;

} stUserSoundSettingType;

typedef struct
{
    U8 u8Backlight;             //backlilght
    U8 u8Contrast;              // contrast
    U8 u8Brightness;            // brightness
    U8 u8Saturation;            // Saturation
    U8 u8Sharpness;             // Sharpness
    U8 u8Hue;
    EN_MS_COLOR_TEMP eColorTemp; // color temperature
    U8 PicUserMode;
} T_MS_PICTURE;  //T_MS_PICTURE

// SubColor Setting
typedef struct
{
    U16 u16SubColorDataCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U8 u8SubBrightness;            // brightness
    U8 u8SubContrast;              // contrast
} T_MS_SUB_COLOR;

/// Color temperture
typedef struct
{
#if ENABLE_PRECISE_RGBBRIGHTNESS
    U16 cRedOffset;   ///< red offset
    U16 cGreenOffset; ///< green offset
    U16 cBlueOffset;  ///< blue offset
#else
    U8 cRedOffset;   ///< red offset
    U8 cGreenOffset; ///< green offset
    U8 cBlueOffset;  ///< blue offset
#endif
    U8 cRedColor;   ///< red color
    U8 cGreenColor; ///< green color
    U8 cBlueColor;  ///< blue color

    U8 cRedScaleValue;   ///< scale 100 value of red color
    U8 cGreenScaleValue; ///< scale 100 value of green color
    U8 cBlueScaleValue;  ///< scale 100 value of blue color
} T_MS_COLOR_TEMP;

#if ENABLE_GAMMA_ADJUST
typedef struct
{
     U16 u16GammaAdjustCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>
     U8 u8Gain;
     U8 u8RedColor;
     U8 u8GreenColor;
     U8 u8BlueColor;
     U8 GammaAdjOSDValue[3][GAMMA_ADJUST_NUM]; //save UI setting
}stUserGammaSetting;
#endif

typedef struct
{
    U16 wVideoDataCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    EN_MS_PICTURE ePicture;
    T_MS_PICTURE astPicture[PICTURE_NUMS];    //24Byte

    T_MS_NR_MODE eNRMode;
    EN_MS_BLACK_LEVEL bBlackLevel;

    EN_MENU_AspectRatio eAspectRatio;
} T_MS_VIDEO;

typedef struct
{
    U16 wWhiteBalanceDataCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    T_MS_COLOR_TEMP astColorTemp[MS_COLOR_TEMP_COUNT];    //24Byte
} T_MS_WHITEBALANCE;


//////////////////////////////////////////////////////////////////////////////////////////
//  Network Menu Setting Structure Type
//////////////////////////////////////////////////////////////////////////////////////////
#if 0 // Remove useless code
typedef struct
{
    U8 u8Network_Flag;

    U8 u8Net_Addr_Class_A;//Dec value
    U8 u8Net_Addr_Class_B;//Dec value
    U8 u8Net_Addr_Class_C;//Dec value
    U8 u8Net_Addr_Class_D;//Dec value

}MS_NET_ADDRESS;

typedef struct
{
    U8 u8Network_SetFlag;  //0:Not Used;1:Used

    U8 u8MANUFACTURE_ID_1;//Hex value
    U8 u8MANUFACTURE_ID_2;//Hex value
    U8 u8MANUFACTURE_ID_3;//Hex value
    U8 u8NETWORK_CARD_ID_1;//Hex value
    U8 u8NETWORK_CARD_ID_2;//Hex value
    U8 u8NETWORK_CARD_ID_3;//Hex value
} MS_MAC_ADDRESS;

#define NUM_OF_ID_PASSWORD_CHAR (16)
typedef struct
{
    U8 u8ID[NUM_OF_ID_PASSWORD_CHAR];
    U8 u8Password[NUM_OF_ID_PASSWORD_CHAR];
} MS_ID_PASSWORD;

typedef enum
{
    EN_NET_CLOSE,
    EN_NET_DHCP,
    EN_NET_STATIC
}EN_NET_CONFIG_MODE;

typedef struct
{
    #ifdef NETWORK_CONFIG_CHINA
    BOOLEAN bNet_Config_mode;
    #else
    EN_NET_CONFIG_MODE Net_Config_mode;         // 0: auto, 1: Manual
    #endif
    BOOLEAN bProxyMode;         // 0: off Proxy, 1: using Proxy
    MS_NET_ADDRESS g_NetIP;
    MS_NET_ADDRESS g_NetNetmask;
    MS_NET_ADDRESS g_NetGateway;
    MS_NET_ADDRESS g_NetDNS;
    MS_MAC_ADDRESS g_NetMacAddress;

    MS_ID_PASSWORD g_Wifi_ID_PSW;
    MS_ID_PASSWORD g_ADLS_ID_PSW;

    U8 stuff;
    U16 stuff2;
}MS_NETWORK;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//  Scan Menu Setting Structure Type
//////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    U16 ScanMenuSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U8 u8RFChannelNumber;
    U8 u8PreRFChannelNumber;

// ------------ 8 bits -----------
    U8 u8VideoStandard      : 4;
    U8 u8ScanType           : 3; // 0=SCAN_TYPE_AUTO,1=SCAN_TYPE_MANUAL,2=SCAN_TYPE_NETWORK
    U8 u8Antenna            : 1; // 0=ANT_CATV, 1=ANT_AIR

// ------------ 8 bits -----------
    U8 u8VideoSystem_Brazil : 3;
    U8 u8ATVMediumType      : 2;
    U8 u8SoundSystem        : 3;

// ------------ 8 bits -----------
    U8 u8BandWidth          : 2;
#if 1//( ENABLE_T_C_COMBO )
    U8 u8DVBCTvConnectionType:2; //0=DVB-T,1=DVB-C
                                 //0=DTMB, 1=DVB-C for DVB-C plus DTMB system.
#endif
    U8 u8ChType             : 1;
    U8 u8LSystem            : 1;
    U8 u8ATVManScanType     : 1;
    U8 u8ATVManScanDir      : 1;

// ------------ 8 bits -----------

#if (ENABLE_ATSC) //NeedCheck
    U8 u8CableSystem:2;       //0=STD, 1=IRC, 2=HRC, 3=AUTO
#endif
} MS_SCANMENU_SETTING;

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
typedef enum
{
    MFC_Off,
    MFC_Horizantal,
    MFC_Vertical,
    //MFC_On,
    MFC_Num,
} EN_MFC_Type;
#endif

typedef enum
{
    EN_INPUT_LABEL_None,
    EN_INPUT_LABEL_VCR,
    EN_INPUT_LABEL_DVD,
    EN_INPUT_LABEL_PC,
    EN_INPUT_LABEL_GAME,
    EN_INPUT_LABEL_SET_TOP_BOX,
    EN_INPUT_LABEL_Satellite,
    EN_INPUT_LABEL_Num,
} EN_MENU_INPUT_LABEL_NAME;

typedef enum
{
   EN_COLOR_RANGE_0_255,
   EN_COLOR_RANGE_16_235,
   EN_COLOR_RANGE_AUTO,
} EN_COLOR_RANGE_SETTING;

#if HDMI_DVI_AUDIO_MODE_CONFIG
typedef enum
{
    EN_HDMI_DVI_AUDIOMODE_AUTO,
    EN_HDMI_DVI_AUDIOMODE_DIGTAL,
    EN_HDMI_DVI_AUDIOMODE_ANALOG,
    EN_HDMI_DVI_AUDIOMODE_NUM,
} EN_HDMI_DVI_AUDIOMODE;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//  System Setting Structure Type
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    TypCheckSum SystemSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    E_UI_INPUT_SOURCE enUiInputSourceType;   // input source selection
    E_UI_INPUT_SOURCE enUiPrevInputSourceType;   // Previous input source selection
  #if(!DVB_T_C_DIFF_DB)
    E_UI_INPUT_SOURCE enDBProgramSourceType;
  #endif
    EN_LANGUAGE Language; // OSD language
    EN_LANGUAGE  SubtitleDefaultLanguage;
    EN_LANGUAGE  SubtitleDefaultLanguage_2;
    EN_LANGUAGE  Last_Select_HotKey_SubtitleLanguage;


    //EN_MENU_E5_KeyLock      g_enKeyLock;
    U8 NextNewRamIndex;        // User new mode RAM index

    //MS_NETWORK g_Network;         // network configuration selection
	U8 u8Backlight;
    EN_COLOR_RANGE_SETTING enCOLORRANGE;
    EN_COLOR_RANGE_SETTING enAUTOCOLORRANGE;

    BOOLEAN g_MirrorEnable;


    #if (ENABLE_TCON_BIN_IN_DB)
    U8 TconBinInDB;
    U32 TconBinSize;
    #endif

#if ENABLE_OFFLINE_SIGNAL_DETECTION
    AISEnumType bAIS;
#endif

#if ENABLE_PVR
    U32 u32PVR_RecordMaxTime;      //second, the max record time of free record
    U8 u8PVR_IsRecordAllChannel;   //0:off  1:record all channel
#endif

    //-------------------------------------------------------

#if (ENABLE_DMP || BLOADER)
    U8 UsrLogo:2;  //    2:User logo 1:default logo 0:off
    U8 u8UsrLogoCnt:2;  // total number of user logo
    U8 u8UsrLogoIdx:2;  //  current user logo
    U8 UsrPowerOnMusic:2;  //   2:User poweron music 1:default poweron music 0:off
#endif

#if (ENABLE_MAINPAGE_EFFECT)
    U8 fEnableOsdAnimation:2;       // 0=Off, 1= On
#endif

#if HDMI_DVI_AUDIO_MODE_CONFIG
    EN_HDMI_DVI_AUDIOMODE fEnableHdmiDviAudioModeConfig:2;
#endif

    //-------------------------------------------------------
    U8 fDynamicContrast : 1;          // 0=Off, 1= On
    U8 fDynamicBacklight : 1;         // 0=Off, 1= On
    U8 fFilmMode : 1;                 // 0=Off, 1= On

    U8 fDCR:1;                      // 0 = Off, 1 = On
    U8 fSCARTInputSel : 1;          // 0=EN_SCART_SEL_AV, 1= EN_SCART_SEL_SV
    U8 fSPDIFMODE:1;                // 0=PCM, 1= AUTO
    U8 fSUBLANG_FLAG:1;             // 0=Primary, 1=Secondary

    U8 f5VAntennaPower:1;           // 0=Off, 1= On
    U8 fSoftwareUpdate:1;           // 0=Off, 1= On
    U8 fAutoVolume:1;               // 0=Off, 1= On
    U8 fHardOfHearing:1;            // 0=Off, 1= On
    U8 fBackgroundDownload:1;       // 0=Off, 1= On
    U8 fEnableSubTitle:1;           // 0=Off, 1= On
    U8 fEnableTTXSubTitle:1;        // 0=Off, 1= On
    U8 fSubTitleOn:1;               // 0=Off, 1= On menu setting
    U8 fEpop:1;                      // 0=Off, 1= On
	U8 Reserved2 : 1;

#if ENABLE_OAD
    U8 bOADActiveStandbyMode:1;
#endif

#if (ASTRA_HD_ENABLE)
     U8 u8ServiceListID;
#endif
	S8 KeyStoneValue;
	EN_PROJECTION_TYPE ProjectionType;//wht121101_1
	EN_OSD_TIME OsdDuration;
 #if (ENABLE_ATSC)
    U8 fFinishWizardMode:1;    // 0=Auto, 1=Manual
    //U8 fTimeDST:1;             // 0 = Off, 1 = On
    U8 fTimeDSTStatusControl:1;   // 0 = Off, 1 = On
    U8 fTimeAutoSync:1;        // 0 = Off, 1 = On
    U8 fTimeFormat:1;          // 0: 24-hour, 1: 12-hour
    U8 fBacklight:1;
    //U8 fPreSrcIsDvbs:1;
    //U8 Option3DNR:3;           // 0: off 1:weak 2: standard  3: strong 4: Auto

    //U8  u8NoSavedRRT;             // Move to
    //U8  u8IdxLastSavedRRT;
    U8 u8TimeZone;             // 0=GMT-12:00 ~ 24=GMT+00:00 ~ 48=GM+12:00
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    U16 u16MainListLastWatched;
#else
    U16 u16MainListLastWatched[ANT_TYPE_NUM];// last watched service # of Main List
#endif

     U16 Transparency;
  #if EN_INPUT_LABEL_EDIT
     EN_INPUT_LABEL_PRESENT_TYPE g_InputLablePresentType[UI_INPUT_SOURCE_NUM];
     U8 g_InputLableEdit[UI_INPUT_SOURCE_NUM][MAX_INPUTLLABEL_CHAR_NUM + 1];
     BOOLEAN bInputLabelAdjust[UI_INPUT_SOURCE_NUM];
  #endif

 #if ENABLE_ATSC_TTS
    BOOLEAN bTTSOn;
    U8 u8TTSVolume;
    U8 u8TTSPitch;
    U8 u8TTSSpeed;
 #endif

 #endif // ENABLE_ATSC
#if ENABLE_KEY_TO_SPEECH
    BOOLEAN bKTSOn;
#endif
#if (ENABLE_HDR)
    EN_MS_HDR enHdrSetting;
#endif

}__attribute__((__packed__)) MS_USER_SYSTEM_SETTING;

#ifdef ENABLE_DMP
typedef enum
{
    POWERON_LOGO_OFF,
    POWERON_LOGO_DEFAULT,
    POWERON_LOGO_USER,
    POWERON_LOGO_NUMS,
}LogoEnumType;

typedef enum
{
    POWERON_MUSIC_OFF,
    POWERON_MUSIC_DEFAULT,
    POWERON_MUSIC_USER,
    POWERON_MUSIC_NUMS,
}PowerOnMusicEnumType;
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    U16 vchipSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U8 u8BlockSysLockMode:1;
    U8 u8UnratedLoack:4;
    U8 u8VideoBlockMode:2;
    U8 u8BlockSysPWSetStatus:1;
    U8 u8ParentalControl:5;
    U8 u8EnterLockPage: 1;
    U8 u8MonitorParental:2;
    U16 u16BlockSysPassword;
} ATTR_PACK MS_BLOCKSYS_SETTING;

//////////////////////////////////////////////////////////////////////////////////////////
//  General Setting structure type
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    U16 SscSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    BOOLEAN SscMIUEnable;
    BOOLEAN SscLVDSEnale;
    U16 MIUSscSpanKHzx10;
    U16 MIUSscStepPercentagex100;
    U16 LVDSSscSpanKHzx10;
    U16 LVDSSscStepPercentagex100;
    U16 LVDSSwing;
    BOOLEAN SscUrsaMIU0Enable;
    BOOLEAN SscUrsaMIU1Enable;
    BOOLEAN SscUrsaLVDSEnable;
    U16 MIU0SscModulation;
    U16 MIU0SscPercentage;
    U16 MIU1SscModulation;
    U16 MIU1SscPercentage;
    U16 LVDSSscModulation;
    U16 LVDSSscPercentage;
    U16 PanelSwing;
} MS_SSC_SETTING;
//////////////////////////////////////////////////////////////////////////////////////////
//////////////CI Infomation STRUCT////////////////////////
#if ENABLE_CI
typedef struct
{
    U16 CISettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place

    BOOLEAN UCredential_Mode;
    BOOLEAN UPerformance_Monitor;
    U16 UResource_Manager;
    U16 UApplication_Information;
    U16 UConditional_Access_Support;
    U16 UHost_Control;
    U16 UDate_Time;
    U16 UMan_Machine_Interface;
    U16 ULow_Speed_Communication;
    U16 UContent_Control;
    U16 UHost_Language_Control;
    U16 UCAM_Upgrade;
    U16 UOperate_Profile;
    U16 USpecific_Application_Support;
    U16 UApplication_Man_Machine_Interface;
    U16 UProgram_Map_Table;
    U16 UHost_Service_Shunning;
    U16 UCanal_Ready_Authentication;
    U16 UDEFAULT;
}CI_SETTING;
#endif
/////////////////////////////////////////////////////////

#if (ENABLE_CI && ENABLE_CI_PLUS)
typedef struct
{
    U16 CIKeyCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U16 u16OpChannelIdex;
    U16 u16NormalChannelIndex;
    MEMBER_SERVICETYPE enNormalChannelSType;

    MS_CI_KEY_SETTING stKeySetting[CI_CC_KEY_NUM];
    U8  u8SystemMJDUTC[5];
    U8 u8CIFunctionDebugLevel[EN_CI_FUNCTION_DEBUG_COUNT];

    U8 u8OpIndex;
	U8 OpMenuRestartWhenChooseNo;
    U8 bInOpMenu:1;
    U8 Reserved0:7;

} MS_CI_PLUS_SETTING;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//  Nonlinear Setting structure type
//////////////////////////////////////////////////////////////////////////////////////////
#if (ENABLE_NONLINEAR_CURVE)
typedef enum
{
#if(ENABLE_PICTURE_NONLINEAR_CURVE)
    NONLINEAR_CURVE_CONTRAST,
    NONLINEAR_CURVE_BRIGHTNESS,
    NONLINEAR_CURVE_SATURATION,
    NONLINEAR_CURVE_SHARPNESS,
    NONLINEAR_CURVE_HUE,
    NONLINEAR_CURVE_BACKLIGHT,
#endif

#if(ENABLE_SOUND_NONLINEAR_CURVE)
    NONLINEAR_CURVE_VOLUME,
#endif

} EN_MS_NONLINEAR_CURVE;
#define PICTURE_CURVE_NUMS  6

typedef struct
{
    U8 u8OSD_0;
    U8 u8OSD_25;
    U8 u8OSD_50;
    U8 u8OSD_75;
    U8 u8OSD_100;
} T_MS_USER_NONLINEAR_CURVE, *P_MS_USER_NONLINEAR_CURVE;

typedef struct
{
    U16 NonLinearCurveSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

#if(ENABLE_PICTURE_NONLINEAR_CURVE)
  #if ENABLE_DTV
    T_MS_USER_NONLINEAR_CURVE DTVPictureCurve[PICTURE_CURVE_NUMS];
  #endif
    T_MS_USER_NONLINEAR_CURVE ATVPictureCurve[PICTURE_CURVE_NUMS];
    T_MS_USER_NONLINEAR_CURVE AVPictureCurve[PICTURE_CURVE_NUMS];
    T_MS_USER_NONLINEAR_CURVE SVPictureCurve[PICTURE_CURVE_NUMS];
    T_MS_USER_NONLINEAR_CURVE YPbPrPictureCurve[PICTURE_CURVE_NUMS];
    T_MS_USER_NONLINEAR_CURVE HDMIPictureCurve[PICTURE_CURVE_NUMS];
    T_MS_USER_NONLINEAR_CURVE PCPictureCurve[PICTURE_CURVE_NUMS];
    T_MS_USER_NONLINEAR_CURVE StoragePictureCurve[PICTURE_CURVE_NUMS];
#endif

#if(ENABLE_SOUND_NONLINEAR_CURVE)
  #if ENABLE_DTV
    T_MS_USER_NONLINEAR_CURVE DTVSoundCurve;
  #endif
    T_MS_USER_NONLINEAR_CURVE ATVSoundCurve;
    T_MS_USER_NONLINEAR_CURVE AVSoundCurve;
    T_MS_USER_NONLINEAR_CURVE StorageSoundCurve;
#endif
} MS_NONLINEAR_CURVE_SETTING;
#endif

typedef struct
{
    TypCheckSum     u16CheckSum;

    U8                  u8AFEC_D4;
    U8                  u8AFEC_D5_Bit10;
    U8                  u8AFEC_D8_Bit3210;

#if ENABLE_VD_PACH_IN_CHINA
    U8                  u8AFEC_D5_Bit2;////[2]When CF[2]=1, K1/K2 Default Value, K1=2E,K2=6A
    U8                  u8AFEC_D7_LOW_BOUND;//Color kill
    U8                  u8AFEC_D7_HIGH_BOUND;//Color kill
    U8                  u8AFEC_D9_Bit0;
    U8                  u8AFEC_A0; //only debug
    U8                  u8AFEC_A1;//only debug
    U8                  u8AFEC_A0A1_COUNT;
    U8                  u8AFEC_66_Bit76;//only debug
    U8                  u8AFEC_6E_Bit7654;//only debug
    U8                  u8AFEC_6E_Bit3210;//only debug
    U8                  u8AFEC_43;//auto or Fixed AGC
    U8                  u8AFEC_43_OPTION;
    U8                  u8AFEC_44;//AGC gain
    U8                  AUDIO_NR;
    U8                  PRESCALE;
    U8                  CF_2_ATV;
    U8                  CF_2_AV;
    U8             u8AFEC_CB;
    U16             Vif_CLAMPGAIN_GAIN_OV_NEGATIVE;
   // U8                  u8AFEC_258D;//cvbs OUT

    //-------VIF adjust----
    U8                  VifTop;
   // U8                  Vif_AGC_VGA_BASE ;
    U16                 Vif_VGA_MAXIMUM;
    U16                 Gain_DISTRIBUTION_THR;

    U8                  Vif_AGCREFNEGATIVE;
    BOOLEAN             Vif_ASIA_SIGNAL_OPTION;

    U8                  Vif_CR_KP1;
    U8                  Vif_CR_KI1;
    U8                  Vif_CR_KP2;
    U8                  Vif_CR_KI2;
    U8                  Vif_CR_KP;
    U8                  Vif_CR_KI;
    U16                 Vif_CR_LOCK_THR;
    U16                 Vif_CR_THR;
    U8                  Vif_DELAY_REDUCE;
    BOOLEAN             Vif_CR_KP_KI_ADJUST;
    U8                  China_DESCRAMBLER_BOX;
#if(CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER)
    U8                  Vif_PROGRAMMABLE_DELAY;
#endif
    BOOLEAN             Vif_OVER_MODULATION;
    U32                 u32VDPatchFlag;
    U16                 Vif_CLAMPGAIN_CLAMP_OV_NEGATIVE;
    U8             AUDIO_HIDEV; //0:OFF,1:ON BW_L1 /2:BW_L2/3:BW_L1
#endif

}__attribute__((__packed__))  StruFacVDSetting;

#if(ENABLE_UART_MSG_TO_USB)
typedef enum
{
    EN_FACTORY_USB_LOG_OFF,
    EN_FACTORY_USB_LOG_ON,
    EN_FACTORY_USB_LOG_NUM,
}EN_FACTORY_USB_LOG;
#endif


#if(ENABLE_SCRIPT_EXECUTE)
typedef enum
{
    EN_FACTORY_EXECUTE_SCRIPT_OFF,
    EN_FACTORY_EXECUTE_SCRIPT_ON,
    EN_FACTORY_EXECUTE_SCRIPT_NUM,
}EN_FACTORY_EXECUTE_SCRIPT;
#endif
typedef struct
{
    U16 u16CheckSum;

#if ENABLE_FACTORY_INPUT_SOURCE_FUNCTION
    U16  u16_AV_Count;
    U16  u16_SV_Count;
    U16  u16_SCART_Count;
    U16  u16_COMPONENT_Count;
    U16  u16_HDMI_Count;
#endif

#if ENABLE_DESIGN_POWER_ON_MODE
    POWERON_MODE_TYPE   u8PowerOnMode;
#endif

#if (ENABLE_UART_MSG_TO_USB)
    EN_FACTORY_USB_LOG   eFactoryUSBLog;
#endif

#if (ENABLE_SCRIPT_EXECUTE)
    EN_FACTORY_EXECUTE_SCRIPT   eFactoryExecuteScript;
#endif
    U8 u8Test;

} StruFacMiscSetting;

#if ENABLE_PANEL_BIN
typedef struct
{
    U16 u16CheckSum;

    U8  u8PanelBinIndex;

    U32 u32Version;
    U32 u32CrcChecksum;

    BOOLEAN bUpdated[PANEL_BIN_MAX_SUPPORT_TABLE];
    U8 m_bPanelDualPort[PANEL_BIN_MAX_SUPPORT_TABLE];
    U8 m_bPanelSwapPort[PANEL_BIN_MAX_SUPPORT_TABLE];
    U8 m_bPanelLVDS_TI_MODE[PANEL_BIN_MAX_SUPPORT_TABLE];
    U8 m_ucTiBitMode[PANEL_BIN_MAX_SUPPORT_TABLE];
    U8 m_ucOutputFormatBitMode[PANEL_BIN_MAX_SUPPORT_TABLE];
} StruFacPnlSetting;
#endif




#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
typedef enum
{
    EN_WB_PATTERN_OFF,
    EN_WB_PATTERN_ON,
}EN_WB_TEST_PATTERN;

typedef struct
{
    U16 u16CheckSum;

    EN_WB_TEST_PATTERN enWBPattern;

    U8 u8WBPatternValue;

} StruFacWBTestPattern;
#endif

typedef struct
{
    TypCheckSum u16FactorySettignCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    MS_ADC_SETTING g_AdcSetting[ADC_SET_NUMS];

    T_MS_WHITEBALANCE g_astWhiteBalance[DATA_INPUT_SOURCE_NUM];

    T_MS_SUB_COLOR g_astSubColor[DATA_INPUT_SOURCE_NUM];

// Use new method to access

    StruFacVDSetting  stVDSetting;

    StruFacMiscSetting stFacMiscSetting;

  #if ENABLE_PANEL_BIN
    StruFacPnlSetting stFacPnlSetting;
#endif



#if ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    StruFacWBTestPattern stFacWBPatternSetting;
#endif

    U8 au8Dummy[100]; // Reserve for ...

} MS_FACTORY_SETTING;


//////////////////////////////////////////
//  PIP/POP Settings
//////////////////////////////////////////
#if (ENABLE_PIP)
struct  st_MS_PIP_SETTING
{
    U16                   PIPSetupInfoCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    EN_PIP_MODE            enPipMode;
    E_UI_INPUT_SOURCE      enSubInputSourceType;
    EN_PIP_SIZE            enPipSize;
    EN_PIP_POSITION        enPipPosition;
    BOOLEAN                bBolderEnable;
    EN_PIP_SOUND_SRC       enPipSoundSrc;
    //==Used in Factory Menu=========================
    U8                     u8BorderWidth; // 1 ~ 10
    BOOLEAN                bPipEnable;
    //===============================================
};

typedef struct st_MS_PIP_SETTING    MS_PIP_SETTING;
//================when  XC has 2 window and Factory  Menu pip flags is open, pip is supported==========================
#define IsPIPSupported() ((BOOLEAN)((MApi_XC_GetInfo()->u8MaxWindowNum > 1) && (stGenSetting.g_stPipSetting.bPipEnable)))
#endif

//////////////////////////////////////////
//  DRM
//////////////////////////////////////////
#if ENABLE_DRM
#define DIVX_REG_CODE_LEN                   10
#define DIVX_DEACT_CODE_LEN                 8
#define DIVX_KEY_LEN                        48

typedef enum
{
    E_DRM_INIT,
    E_DRM_SAVE,
    E_DRM_LOAD,
    E_DRM_CLEAR_MEMORY,
    E_DRM_CLEAR_MEMORY_DEMO,
}EN_DRM_OP_MODE;

typedef struct
{
    U16 VDplayerDRMInfoCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U8 u8RegistrationCode[DIVX_REG_CODE_LEN];
    U8 u8DeActivationCode[DIVX_DEACT_CODE_LEN];
    U8 u8DRM_Data[DIVX_KEY_LEN];

    U8 bIsKeyGenerated;
    U8 bIsActivated;
    U8 bIsDeactivated;

    U8 u8Reserved0[3];
} VDplayerDRMInfo;
#endif

typedef enum
{
    EN_POWER_DC_ON,
    EN_POWER_DC_OFF,
}EN_POWER_DC_ONOFF;

//////////////////////////////////////////
//  MM Last Memory Settings
//////////////////////////////////////////
#if (ENABLE_LAST_MEMORY==1)
typedef struct
{
    U32 EntryType;
    U32 FileLength;
    U32 EntryFileLength;
    U32 EntrySeconds;//since 1980/01/01/0/0/0
    U8 EntryID[8];
    U8 EntryID_Ext[8];
    U8 EnvironmentID;
    U8 FileSystemID;
    U8 EntryAttrib;
} LastMemoryFileEntry;

typedef struct
{
    U32 u32LastMemorySeekPosL;
    U32 u32LastMemorySeekPosH;
    U32 u32LastMemorySeekPTS;//ms
    U16 u16LastAudioTrack;
#if ENABLE_SUBTITLE_DMP
    U16 u16LastSubtitleTrack;
    BOOLEAN bSubtitleShow;
#endif
#if 0//ENABLE_DIVX_PLUS
    U8 u8LastTitle;
    U8 u8LastEdition;
    U8 u8LastChapter;
#endif
} stLastMemoryAttribute;

typedef struct
{
    stLastMemoryAttribute stLastMemAttribute;
    LastMemoryFileEntry fEntry;
} stLastMemoryInfo;

typedef struct _MS_MM_LASTMEMORY_SETTING
{
    U16 MmLastMemorySettignCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    stLastMemoryInfo m_LastMemoryInfo[LAST_MEMORY_FILENUMBER];
    U16 m_LastMemoryOrderTbl[LAST_MEMORY_FILENUMBER]; // start from 1,2,3.....
} MS_MM_LASTMEMORY_SETTING;
#endif

typedef struct
{
    EN_POWER_ON_MODE g_ucACorDCon;  // Power on status

    U16 wPM_WakeUpDevice;  // set PM Wake-up Devices
    U16 g_ucWakeUpDevice;   // check which Device to wake up PM
}POWER_GENSETTING;

//////////////////////////////////////////////////////////////////////////////////////////
//  General Setting structure type
//  NOTE: All components need to follow the checksum mechanism
//            all the struct containing checksum must put the checksum the first member of the struct
//////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    U16 u16CheckSum;


#if ENABLE_CEC
    BOOLEAN g_bHdmiCecMode:1;               // ENABLE : on  (Available all CEC function).
                                            // DISABLE: off (Disable all CEC function).

    BOOLEAN g_enHDMIARC:1;


    BOOLEAN g_bHdmiCecAutoTvOn:1;           // ENABLE : on  (TV wakes up from standby while receiving CEC wakeup command,
                                            // DISABLE: off (TV does not wake up from standby while receiving CEC wakeup command

    BOOLEAN g_bHdmiCecDeviceAutoStandby:1;  // ENABLE : on  (TV  should send <Standby> message).
                                            // DISABLE: off (TV should not send <Standby> message).

    BOOLEAN g_bHdmiCecDeviceControl:1;      // ENABLE : on  (RC Pass through function enables).
                                            // DISABLE: off (RC Pass through function disables).

    // TO DO. should be removed, since don't know how to use
    //U8 g_bHdmiCecSpeakerMode:1;  //DISABLE: Audio , ENABLE:TV

    U8 u8HDMIReserved:3;
#endif

#if(ENABLE_EDID_SWITCH)
    E_USER_HDMI_EDID_SEL aeHDMI_Edid_Sel[4];
#endif
} Stru_DB_HDMI_SETTING;

typedef struct
{
    TypCheckSum u16CheckSum;

    U8 u8Flag1;
    U8 u8Flag2;
    BOOLEAN bKeyLoggerEnable;

} MS_DEBUG_SETTING;

typedef struct
{
    TypCheckSum u16CheckSum;

    EN_POWER_DC_ONOFF bDCOnOff      : 1;

    BOOLEAN bRunInstallationGuide   : 1;

#if (ENABLE_EWS)
    U8 u8EWSLocationCode[5];
#endif
} ATTR_PACK MS_MISC_SETTING;

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
typedef struct
{
    TypCheckSum u16CheckSum;

    U8 enMEMCType;

    EN_6M30_MIRROR_MODE en6M30MirrorMode;

    U8 enMFCStrength;

} ATTR_PACK MS_DEV_MFC_SETTING;
#endif

typedef struct
{
    TypCheckSum u16CheckSum;

#if (ENABLE_DTV)
    MEMBER_COUNTRY  eCountry;
    U16 u16DTVRFChannelOrder;
    U16 u16DATARFChannelOrder;
    U16 u16RADIORFChannelOrder;
    MEMBER_SERVICETYPE eCurrentServiceType;
#endif

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    U16 u16CurDtvOrder_DVBC;
    U16 u16CurDtvDataOrder_DVBC;
    U16 u16CurDtvRadioOrder_DVBC;
    MEMBER_SERVICETYPE eCurrentServiceType_DVBC;
#endif

    U8 u8ATVProgramNumber;

#if (ENABLE_SW_CH_FREEZE_SCREEN)
    U8 u8SwitchMode;
#endif

#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM|| (TV_SYSTEM == TV_NTSC) )
    U8 u8ATVProgramNumber_CATV;
#endif

} ATTR_PACK MS_TV_SETTING;

#if(ENABLE_S2)
typedef struct
{
    TypCheckSum u16CheckSum;

    MS_U8             u8Location;
    DISH_LOCATION     stManualLocation;
    EN_SORT_TYPE      g_sort_type;

#if 1//(ENABLE_S2_CH_SWITCH)
    //MEMBER_SERVICETYPE g_serviceTypeS2;
    //WORD wCurOrderOfTVS2;
    //WORD wCurOrderOfRADIOS2;
    //WORD wCurOrderOfdataS2;

    MEMBER_SERVICETYPE eCurServiceType;
    U16 u16CurDtvOrder;
    U16 u16CurDtvDataOrder;
    U16 u16CurDtvRadioOrder;
#endif

} ATTR_PACK MS_DVBS_SETTING;
#endif

#if ENABLE_3D_PROCESS
typedef struct
{
    U16 u16CheckSum;
    EN_3D_TYPE    en3DType;
    EN_3D_TO_2D_TYPE en3DTo2DType;
    EN_3D_DETECT_MODE   en3DDetectMode;
    EN_3D_LR_MODE   en3DLRMode;
    EN_3D_HSHIFT_MODE en3DHShiftMode;
    EN_3D_VIEW_POINT_MODE en3DViewPointMode;
} Stru3DSetting;
#endif

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
typedef struct
{
    U16 u16CheckSum;

    stCaptionSetting_Type stCaptionSetting;

    EN_ATV_CAPTION_TYPE enATVCaptionType;

#if(BRAZIL_CC)
    EN_DTV_CAPTION_TYPE enDTVCaptionType;
#endif
} Stru_DB_CC_SETTING;
#endif

#if(ENABLE_DTV_EPG)

#define SIZE_EPG_MANUAL_TIMER_EVENT 2100

typedef struct
{
    U16 u16CheckSum;

    U8 au8EpgTimerSetting[SIZE_EPG_MANUAL_TIMER_EVENT];
    //MS_EPG_TIMER astMS_EPG_TIMER[EPG_TIMER_MAX_NUM];

} Stru_DB_MANUAL_EVENT;

#endif


//----VChip data moving
#if ((ATSC_CC != NO_CC))
#define VCHIP_TVRATING_ALL    BIT5
#define VCHIP_TVRATING_FV     BIT4
#define VCHIP_TVRATING_V      BIT3
#define VCHIP_TVRATING_S      BIT2
#define VCHIP_TVRATING_L      BIT1
#define VCHIP_TVRATING_D      BIT0
#define VCHIP_TVRATING_VSL    0x0E
#define VCHIP_TVRATING_VSLD   0x0F

typedef struct
{
    U8 Item_TV_NONE;
    U8 Item_TV_Y;
    U8 Item_TV_Y7;
    U8 Item_TV_G;
    U8 Item_TV_PG;
    U8 Item_TV_14;
    U8 Item_TV_MA;
} MS_VCHIP_TV_ITEM;

typedef struct
{
    U16 vchipSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U8 u8VChipLockMode:4;
    U8 u8UnRatedLock:4;

    U8 u8VChipReserved;
    U8 u8VChipMPAAItem;
    U8 u8VChipCEItem;
    U8 u8VChipCFItem;
    U16 u16VChipPassword;
    U8 u8InputBlockItem;
    MS_VCHIP_TV_ITEM stVChipTVItem;
} MS_VCHIP_SETTING;

typedef struct
{
    U8 u8EIA608Data1;
    U8 u8EIA608Data2;
    U8 RatingType;
    U8 RatingLevel;
    U8 TV_FVSLD;
    U8 MPAALevel;
    U8 CanEngLevel:4;
    U8 CanFreLevel:4;
#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
    U16 u8DimVal0;
    U16 u8DimVal1;
    U16 u8DimVal2;
    U16 u8DimVal3;
    U16 u8DimVal4;
    U16 u8DimVal5;
    U16 u8DimVal6;
    U16 u8DimVal7;
    U16 u8DimVal8;
    U16 u8DimVal9;
  #if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
    U16 u8DimVal10;
    U16 u8DimVal11;
    U16 u8DimVal12;
    U16 u8DimVal13;
    U16 u8DimVal14;
    U16 u8DimVal15;
    U16 u8DimVal16;
    U16 u8DimVal17;
    U16 u8DimVal18;
    U16 u8DimVal19;
    U16 u8DimVal20;
    U16 u8DimVal21;
    U16 u8DimVal22;
    U16 u8DimVal23;
    U16 u8DimVal24;
    U16 u8DimVal25;
    U16 u8DimVal26;
    U16 u8DimVal27;
    U16 u8DimVal28;
    U16 u8DimVal29;
    U16 u8DimVal30;
    U16 u8DimVal31;
    U16 u8DimVal32;
    U16 u8DimVal33;
    U16 u8DimVal34;
    U16 u8DimVal35;
    U16 u8DimVal36;
    U16 u8DimVal37;
    U16 u8DimVal38;
    U16 u8DimVal39;
    U16 u8DimVal40;
  #endif
#else
    U8 u8DimVal0:4;
    U8 u8DimVal1:4;
    U8 u8DimVal2:4;
    U8 u8DimVal3:4;
    U8 u8DimVal4:4;
    U8 u8DimVal5:4;
    U8 u8DimVal6:4;
    U8 u8DimVal7:4;
    U8 u8DimVal8:4;
    U8 u8DimVal9:4;
#endif
} MS_VCHIP_RATING_INFO;


#endif


#if( DB_PC_MODE_SAVE_TO_DB_GEN )
typedef struct
{
    U16 u16CheckSum;

    MS_PCADC_MODESETTING_TYPE astMsPcAdcModeSetting[MAX_MODE_NUM];

} Stru_DB_PcModeSetting;
#endif

typedef struct
{
    //////////////////////////////////////////////////////////////////////////////////////////
    // for General Setting version check, must put at top of this structure
    U8 u8VersionCheck;
    //////////////////////////////////////////////////////////////////////////////////////////

    MS_USER_SYSTEM_SETTING g_SysSetting;

    stUserSoundSettingType g_SoundSetting;

    T_MS_VIDEO g_astVideo[DATA_INPUT_SOURCE_NUM];

    MS_TIME g_Time;

    MS_SCANMENU_SETTING stScanMenuSetting;

    MS_BLOCKSYS_SETTING g_BlockSysSetting;

  #if ENABLE_SSC
    MS_SSC_SETTING g_SSCSetting;
  #endif

  #if (ENABLE_NONLINEAR_CURVE)
    MS_NONLINEAR_CURVE_SETTING g_NonLinearCurveSetting;
  #endif

  #if ENABLE_DRM
    VDplayerDRMInfo g_VDplayerDRMInfo;
  #endif

  #if (ENABLE_PIP)
    MS_PIP_SETTING g_stPipSetting;
  #endif

  #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    MS_ALL_NETWORKID_INFO g_Network_TS;
  #endif

#if ENABLE_CI_PLUS
    //MS_CI_PLUS_SETTING g_CIKeySetting;
    MS_CI_PLUS_SETTING stCIPlusSetting;
#endif

#if ENABLE_CI
    CI_SETTING g_CISetting;
#endif

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
    MS_MM_LASTMEMORY_SETTING g_MmLastMemorySetting;
#endif

    // ===== Use new method control save/load/init =====

    MS_TV_SETTING stTvSetting;

    Stru_DB_HDMI_SETTING stHDMISetting;

    MS_MISC_SETTING stMiscSetting;

    MS_DEBUG_SETTING stDebugSetting;

    // CloseCaption
#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
    Stru_DB_CC_SETTING stCCSetting;
#endif

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
    MS_DEV_MFC_SETTING stDevMfcSetting;
#endif

#if ENABLE_3D_PROCESS
    Stru3DSetting st3DSetting;
#endif

#if(ENABLE_DTV_EPG&&DB_MANUAL_EVENT_SAVE_IN_DB_GEN)
    Stru_DB_MANUAL_EVENT stManualEventSetting;
#endif

#if(ENABLE_S2)
    MS_DVBS_SETTING stDvbsSetting;
#endif

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
    Stru_DB_PcModeSetting stDBPcModeSetting;
#endif

//----VChip data moving
#if ((ENABLE_ATSC)||((ATSC_CC == ATV_CC))||ENABLE_ISDB_ATV_VCHIP)
#if(ENABLE_ATSC)

    stCaptionSetting_Type g_CaptionSetting;
#endif
    MS_VCHIP_SETTING g_VChipSetting;
#endif

#if(ENABLE_FM_RADIO)
    StuRadioSetting stRadioSetting;
#endif

#if ENABLE_GAMMA_ADJUST
    stUserGammaSetting g_GammaSetting;
#endif
    U8 au8Dummy[32]; // Reserve for ...

    //////////////////////////////////////////////////////////////////////////////////////////
    // for General Setting version check, must put at button of this structure
    U8 u8VersionCheckCom;
    //////////////////////////////////////////////////////////////////////////////////////////
} MS_GENSETTING;

typedef struct
{
    //MS_ADC_SETTING g_AdcSetting[ADC_SET_NUMS];
    //T_MS_VIDEO g_astVideo[DATA_INPUT_SOURCE_NUM];
    //T_MS_WHITEBALANCE g_astWhiteBalance[DATA_INPUT_SOURCE_NUM];
    //T_MS_SUB_COLOR g_astSubColor[DATA_INPUT_SOURCE_NUM];
}MS_GENSETTING_EXT;

typedef enum
{
	EN_GENSETTING_CLASS_SYS,
	EN_GENSETTING_CLASS_SOUND,
	EN_GENSETTING_CLASS_ASTVIDEO,

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
	EN_GENSETTING_CLASS_CAPTION,
#endif

	EN_GENSETTING_CLASS_TIME,
	EN_GENSETTING_CLASS_SCANMENU,
	EN_GENSETTING_CLASS_BLOCKSYS,
	EN_GENSETTING_CLASS_SSC,

#if (ENABLE_NONLINEAR_CURVE)
	EN_GENSETTING_CLASS_NONLINEAR_CURVE,
#endif

#if ENABLE_DRM
	EN_GENSETTING_CLASS_VDPLAYERDRM,
#endif

#if (ENABLE_PIP)
	EN_GENSETTING_CLASS_PIP,
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
	EN_GENSETTING_CLASS_NETWORK_TS,
#endif

#if ENABLE_CI_PLUS
	EN_GENSETTING_CLASS_CIKEY,
#endif

#if ENABLE_CI
	EN_GENSETTING_CLASS_CI,
#endif

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
	EN_GENSETTING_CLASS_MM_LASTMEMORY,
#endif

	EN_GENSETTING_CLASS_TV,
	EN_GENSETTING_CLASS_MISC,
	EN_GENSETTING_CLASS_DEBUG,

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
	EN_GENSETTING_CLASS_DEVMFC,
#endif

#if(ENABLE_S2)
	EN_GENSETTING_CLASS_DVBS,
#endif

	EN_GENSETTING_CLASS_MAX
}EN_GENSETTING_CLASS;

#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION

typedef struct
{
    WORD Checksum;
    U8   OverScanHRatio;
    S8   OverScanHposition;
    U8   OverScanVRatio;
    S8   OverScanVposition;
} MS_OVERSCAN_SETTING;

INTERFACE MS_OVERSCAN_SETTING g_OverScan;
#define G_OVERSCAN_HPOSITION    g_OverScan.OverScanHposition
#define G_OVERSCAN_VPOSITION    g_OverScan.OverScanVposition
#define G_OVERSCAN_HRatio    g_OverScan.OverScanHRatio
#define G_OVERSCAN_VRatio    g_OverScan.OverScanVRatio

typedef enum
{
    EN_FACTORY_OverScan_TVNTSC,
    EN_FACTORY_OverScan_TVPAL,
    EN_FACTORY_OverScan_TVSECAM,
    EN_FACTORY_OverScan_TVNTSC443,
    EN_FACTORY_OverScan_TVPALM,
    EN_FACTORY_OverScan_TVPALN,
    EN_FACTORY_OverScan_AVNTSC,
    EN_FACTORY_OverScan_AVPAL,
    EN_FACTORY_OverScan_AVSECAM,
    EN_FACTORY_OverScan_AVNTSC443,
    EN_FACTORY_OverScan_AVPALM,
    EN_FACTORY_OverScan_AVPALN,
    EN_FACTORY_OverScan_SVNTSC,
    EN_FACTORY_OverScan_SVPAL,
    EN_FACTORY_OverScan_SVSECAM,
    EN_FACTORY_OverScan_SVNTSC443,
    EN_FACTORY_OverScan_SVPALM,
    EN_FACTORY_OverScan_SVPALN,
    EN_FACTORY_OverScan_SCARTRGB_NTSC,
    EN_FACTORY_OverScan_SCARTRGB_PAL,
    EN_FACTORY_OverScan_SCARTRGB_SECAM,
    EN_FACTORY_OverScan_SCARTRGB_NTSC443,
    EN_FACTORY_OverScan_SCARTRGB_PALM,
    EN_FACTORY_OverScan_SCARTRGB_PALN,
    EN_FACTORY_OverScan_HDMI480I,
    EN_FACTORY_OverScan_HDMI480P,
    EN_FACTORY_OverScan_HDMI1440_480I,
    EN_FACTORY_OverScan_HDMI1440_480P,
    EN_FACTORY_OverScan_HDMI576I,
    EN_FACTORY_OverScan_HDMI576P,
    EN_FACTORY_OverScan_HDMI1440_576I,
    EN_FACTORY_OverScan_HDMI1440_576P,
    EN_FACTORY_OverScan_HDMI720P,
    EN_FACTORY_OverScan_HDMI1080I,
    EN_FACTORY_OverScan_HDMI1080P,
    EN_FACTORY_OverScan_HDMIDefault,
    EN_FACTORY_OverScan_YPBPR480I,
    EN_FACTORY_OverScan_YPBPR480P,
    EN_FACTORY_OverScan_YPBPR576I,
    EN_FACTORY_OverScan_YPBPR576P,
    EN_FACTORY_OverScan_YPBPR720P50,
    EN_FACTORY_OverScan_YPBPR720P60,
    EN_FACTORY_OverScan_YPBPR1080I50,
    EN_FACTORY_OverScan_YPBPR1080I60,
#if (SUPPORT_EURO_HDTV)
    EN_FACTORY_OverScan_YPBPR1080I50EURO,
#endif
    EN_FACTORY_OverScan_YPBPR1080P24,
    EN_FACTORY_OverScan_YPBPR1080P25,
    EN_FACTORY_OverScan_YPBPR1080P30,
    EN_FACTORY_OverScan_YPBPR1080P50,
    EN_FACTORY_OverScan_YPBPR1080P60,

    EN_FACTORY_OverScan_DTV480I,
    EN_FACTORY_OverScan_DTVR480P,
    EN_FACTORY_OverScan_DTV576I,
    EN_FACTORY_OverScan_DTV576P,
    EN_FACTORY_OverScan_DTV720P,
    EN_FACTORY_OverScan_DTV1080I,
    EN_FACTORY_OverScan_DTV1080P,

    EN_FACTORY_OverScan_H264_DTV480I,
    EN_FACTORY_OverScan_H264_DTVR480P,
    EN_FACTORY_OverScan_H264_DTV576I,
    EN_FACTORY_OverScan_H264_DTV576P,
    EN_FACTORY_OverScan_H264_DTV720P,
    EN_FACTORY_OverScan_H264_DTV1080I,
    EN_FACTORY_OverScan_H264_DTV1080P,
    EN_FACTORY_OverScan_NUM
}EN_FACTORY_OVERSCAN;
#endif


/////////////////////////////////////////////////////////////////////////////////////////
//  Global Variables of CM
/////////////////////////////////////////////////////////////////////////////////////////
INTERFACE POWER_GENSETTING stPowerGenSetting;
INTERFACE MS_GENSETTING stGenSetting;
//INTERFACE MS_GENSETTING_EXT stGenSettingExt;

INTERFACE MS_FACTORY_SETTING g_stFactorySetting;


INTERFACE U8 g_u8AudLangSelected;
#if 1//(ENABLE_DVB_AUDIO_DESC)
INTERFACE U8 g_u8AdAudSelected;
#endif

INTERFACE EN_SCAN_TYPE g_enScanType;


//INTERFACE BOOLEAN fEnableLCN;
INTERFACE E_DATA_INPUT_SOURCE g_enDataInputSourceType[2];

#define MENU_TIMEZONE                       stGenSetting.g_Time.enTimeZone
#define GET_OSD_MENU_LANGUAGE()             (MApp_GetMenuLanguage())
#define GET_OSD_MENU_LANGUAGE_DTG()         (MApp_GetMenuLanguage_DTG())
#define GET_TIMEZONE_MENU_LANGUAGE_DTG()    (MApp_GetTimeZone_DTG())
#define GET_AUDIO_MENU_LANGUAGE_DTG()       (MApp_GetAudioLangMenuLanguage_DTG())
#define GET_SUB_MENU_LANGUAGE_DTG()         (MApp_GetSubLangMenuLanguage_DTG())
#define SET_OSD_MENU_LANGUAGE(x)            (MApp_SetMenuLanguage(x))
#define SET_TIME_MENU_ZONE(x)               (MApp_SetTimeZone(x))
#define SET_AUDIO_MENU_LANGUAGE(x)          (MApp_SetAudioLangMenuLanguage(x))
#define SET_SUB_MENU_LANGUAGE(x)            (MApp_SetSubLangMenuLanguage(x))

#define CMP_OSD_MENU_LANGUAGE(x)            (MApp_CmpMenuLanguage(x))
#define SUBTITLE_DEFAULT_LANGUAGE_1         (stGenSetting.g_SysSetting.SubtitleDefaultLanguage) //current menu language
#define SUBTITLE_DEFAULT_LANGUAGE_2         (stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2) //current menu language
#define MENU_OPTION_SUBTITLE_ON             (stGenSetting.g_SysSetting.fSubTitleOn) // menu option subtitle on/off setting
#define LAST_SECLECT_LANGUAGE               (stGenSetting.g_SysSetting.Last_Select_HotKey_SubtitleLanguage)
#define LAST_SECLECT_AUDIO_LANGUAGE         (EN_LANGUAGE)(stGenSetting.g_SoundSetting.enSoundAudioLan1) //current menu language
#if ENABLE_COUNTRY_SINGAPORE
#define SUBTITLE_MIN_PID_LANGUAGE           (MApp_TV_GetMinPidSubtitleLang())
#endif

#define UI_INPUT_SOURCE_TYPE                (stGenSetting.g_SysSetting.enUiInputSourceType)
#define UI_PREV_INPUT_SOURCE_TYPE           (stGenSetting.g_SysSetting.enUiPrevInputSourceType)
#if(!DVB_T_C_DIFF_DB)
#define DB_PROGRAM_SOURCE_TYPE               (stGenSetting.g_SysSetting.enDBProgramSourceType)
#endif

#if (ENABLE_PIP)
#define UI_SUB_INPUT_SOURCE_TYPE            (stGenSetting.g_stPipSetting.enSubInputSourceType)
#define UI_IS_AUDIO_SOURCE_IN(WIN)          ( ((stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_MAIN)&&(WIN==MAIN_WINDOW)) || \
                                            ((stGenSetting.g_stPipSetting.enPipSoundSrc==EN_PIP_SOUND_SRC_SUB)&&(WIN==SUB_WINDOW)) )
#endif
#define DATA_INPUT_SOURCE_TYPE(WIN)         g_enDataInputSourceType[WIN]  // 0 --> Main_Window ; 1 --> Sub Window



#define G_VEDIO_SETTING         (stGenSetting.g_astVideo)

#define ST_VIDEO                (G_VEDIO_SETTING[DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW)])
#define ST_PICTURE              ST_VIDEO.astPicture[ST_VIDEO.ePicture]

//#define ST_COLOR_TEMP                       ST_VIDEO.astColorTemp[ST_VIDEO.eColorTemp]

//------------------------------------------------------------------
#define G_FACTORY_SETTING       g_stFactorySetting
#define G_DESIGN_SETTING        G_FACTORY_SETTING

#define G_ADC_SETTING           ((G_FACTORY_SETTING).g_AdcSetting)

#define G_WHITE_BALANCE_SETTING ((G_FACTORY_SETTING).g_astWhiteBalance)
#define ST_WHITEBALANCE         (G_WHITE_BALANCE_SETTING[DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW)])
#define ST_COLOR_TEMP           (ST_WHITEBALANCE.astColorTemp[ST_PICTURE.eColorTemp])

#define G_SUB_COLOR_SETTING     ((G_FACTORY_SETTING).g_astSubColor)
#define ST_SUBCOLOR             (G_SUB_COLOR_SETTING[DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW)])
//------------------------------------------------------------------
#if(ENABLE_3D_PROCESS)
    #define DB_3D_SETTING       (stGenSetting.st3DSetting)
#endif

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
    #define DB_CC_SETTING       (stGenSetting.stCCSetting)
#endif

#define DB_HDMI_SETTING         (stGenSetting.stHDMISetting)

#if(ENABLE_CI_PLUS)
    #define DB_CI_PLUS_SETTING  (stGenSetting.stCIPlusSetting)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IS_COUNTRY_SUPPORT_CI(c)        ( (c==OSD_COUNTRY_BELGIUM)       ||  \
                                          (c==OSD_COUNTRY_FINLAND)       ||  \
                                          (c==OSD_COUNTRY_LUXEMBOURG)    ||  \
                                          (c==OSD_COUNTRY_NETHERLANDS)   ||  \
                                          (c==OSD_COUNTRY_SWEDEN)        ||  \
                                          (c==OSD_COUNTRY_UK) )
#define IS_EIT_COMPONENT_COUNTRY(c)     0 //(to do) it is NULL , please add the country
#define IS_DTG_COUNTRY(c)               ((c==OSD_COUNTRY_UK)||(c==OSD_COUNTRY_NEWZEALAND) )
#define IS_EPG_DISABLE_COUNTRY(c)       ( (c==OSD_COUNTRY_NEWZEALAND))
#define IS_EBOOK_COUNTRY(c)             ( (c==OSD_COUNTRY_FRANCE)            ||  \
                                          (c==OSD_COUNTRY_NETHERLANDS))
#define IS_NOT_MHEG5_COUNTRY(c)         ((c==OSD_COUNTRY_AUSTRALIA))

//=============================================================================
INTERFACE void MApp_GetGenSetting(EN_GENSETTING_CLASS eSettingClass, void **ppData);


#undef INTERFACE
#endif

