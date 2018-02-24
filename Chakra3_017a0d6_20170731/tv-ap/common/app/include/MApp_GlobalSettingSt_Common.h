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

#ifndef MAPP_GLOBALSETTINGSTCOMMON_H
#define MAPP_GLOBALSETTINGSTCOMMON_H

/********************************************************************************/
/*                              Include files                                   */
/********************************************************************************/
#include "Board.h"
#include "datatype.h"
#include "msAPI_Global.h"
#include "OSDcp_Bitmap_EnumIndex.h"

/********************************************************************************/
/*                                 Macro                                        */
/********************************************************************************/
#define PICTURE_USER_2  0
#define PASSWORD_SIZE   4
#define PICTURE_NATURAL_SPORTS_LIGHTNESS 0

#define ATTR_PACK __attribute__ ((packed))



#ifdef MAPP_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//#define MAX_BITMAP  E_ZUI_BMP_MAX
//INTERFACE BMPHANDLE Osdcp_bmpHandle[MAX_BITMAP];

#undef INTERFACE

/********************************************************************************/
/*                                 Enum                                         */
/********************************************************************************/
//Antenna
typedef enum
{
    ANT_CATV,
    ANT_AIR,
    ANT_TYPE_NUM
} EN_ANT_TYPE;
#if 0
typedef enum
{
    TIME_DST_OFF,
    TIME_DST_ON,
    TIME_DST_ITEM_NUM
} EN_TIME_DST_ITEM;
#endif
typedef enum _EN_SUBTITLE_DEFAULT_LANGUAGE
{
    SUBTITLE_DEFAULT_LANGUAGE_CZECH,      // 0
    SUBTITLE_DEFAULT_LANGUAGE_DANISH,     // 1
    SUBTITLE_DEFAULT_LANGUAGE_GERMAN,     // 2
    SUBTITLE_DEFAULT_LANGUAGE_ENGLISH,    // 3
    SUBTITLE_DEFAULT_LANGUAGE_SPANISH,    // 4
    SUBTITLE_DEFAULT_LANGUAGE_GREEK,      // 5
    SUBTITLE_DEFAULT_LANGUAGE_FRENCH,     // 6
    SUBTITLE_DEFAULT_LANGUAGE_CROATIAN,   // 7
    SUBTITLE_DEFAULT_LANGUAGE_ITALIAN,    // 8
    SUBTITLE_DEFAULT_LANGUAGE_HUNGARIAN,  // 9
    SUBTITLE_DEFAULT_LANGUAGE_DUTCH,      //10
    SUBTITLE_DEFAULT_LANGUAGE_NORWEGIAN,  //11
    SUBTITLE_DEFAULT_LANGUAGE_POLISH,     //12
    SUBTITLE_DEFAULT_LANGUAGE_PORTUGUESE, //13
    SUBTITLE_DEFAULT_LANGUAGE_RUSSIAN,    //14
    SUBTITLE_DEFAULT_LANGUAGE_ROMANIAN,   //15
    SUBTITLE_DEFAULT_LANGUAGE_SLOVENE,    //16
    SUBTITLE_DEFAULT_LANGUAGE_SERBIAN,    //17
    SUBTITLE_DEFAULT_LANGUAGE_FINNISH,    //18
    SUBTITLE_DEFAULT_LANGUAGE_SWEDISH,    //19
    SUBTITLE_DEFAULT_LANGUAGE_BULGARIAN,  //20
    SUBTITLE_DEFAULT_LANGUAGE_GAEILC,     //21
    SUBTITLE_DEFAULT_LANGUAGE_WELSH,      //22
    SUBTITLE_DEFAULT_LANGUAGE_UNDEFINED,  //23
    SUBTITLE_DEFAULT_LANGUAGE_IRISH,      //24
    SUBTITLE_DEFAULT_LANGUAGE_ARABIC,     //24
    SUBTITLE_DEFAULT_LANGUAGE_CATALAN,    //25
    SUBTITLE_DEFAULT_LANGUAGE_CZECH_2,    //26
    SUBTITLE_DEFAULT_LANGUAGE_GERMAN_2,   //27
    SUBTITLE_DEFAULT_LANGUAGE_GREEK_2,    //28
    SUBTITLE_DEFAULT_LANGUAGE_FRENCH_2,   //29
    SUBTITLE_DEFAULT_LANGUAGE_CROATIAN_2, //30
    SUBTITLE_DEFAULT_LANGUAGE_DUTCH_2,    //31
    SUBTITLE_DEFAULT_LANGUAGE_ROMANIAN_2, //32
    SUBTITLE_DEFAULT_LANGUAGE_GAEILC_2,   //33
    SUBTITLE_DEFAULT_LANGUAGE_WELSH_2,    //34
    SUBTITLE_DEFAULT_LANGUAGE_GAEILC_3,   //35

    SUBTITLE_DEFAULT_LANGUAGE_NUM,        // Language maximum
} EN_SUBTITLE_DEFAULT_LANGUAGE;


#if ENABLE_OFFLINE_SIGNAL_DETECTION
typedef enum
{
    AIS_OFF,
    AIS_SWITCH,
    AIS_DISPLAY,
    AIS_NUMS,
}AISEnumType;
#endif

typedef enum
{
    DATA_INPUT_SOURCE_MIN,

#if (ENABLE_DTV)
    DATA_INPUT_SOURCE_DTV = DATA_INPUT_SOURCE_MIN,
    DATA_INPUT_SOURCE_ATV,
#else
    DATA_INPUT_SOURCE_ATV = DATA_INPUT_SOURCE_MIN,
#endif

#if (INPUT_AV_VIDEO_COUNT >= 1)
    DATA_INPUT_SOURCE_AV,
#endif

#if (INPUT_AV_VIDEO_COUNT >= 2)
    DATA_INPUT_SOURCE_AV2,
#endif

#if (INPUT_AV_VIDEO_COUNT >= 3)
    DATA_INPUT_SOURCE_AV3,
#endif

#if (INPUT_YPBPR_VIDEO_COUNT >= 1)
    DATA_INPUT_SOURCE_COMPONENT,
#endif

#if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    DATA_INPUT_SOURCE_COMPONENT2,
#endif

    DATA_INPUT_SOURCE_RGB,

#if (INPUT_HDMI_VIDEO_COUNT >= 1)
    DATA_INPUT_SOURCE_HDMI,
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 2)
    DATA_INPUT_SOURCE_HDMI2,
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 3)
    DATA_INPUT_SOURCE_HDMI3,
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 4)
    DATA_INPUT_SOURCE_HDMI4,
#endif

#if (INPUT_SCART_VIDEO_COUNT >= 1)
    DATA_INPUT_SOURCE_SCART,
#endif

#if(INPUT_SCART_VIDEO_COUNT >= 2)
    DATA_INPUT_SOURCE_SCART2,
#endif

#if ((INPUT_SV_VIDEO_COUNT >= 1) ||(ENABLE_SCART_SVIDEO))
    DATA_INPUT_SOURCE_SVIDEO,
#endif

#if (INPUT_SV_VIDEO_COUNT >= 2)
    DATA_INPUT_SOURCE_SVIDEO2,
#endif

#if ((ENABLE_DMP) || (DISPLAY_LOGO) || (BLOADER))
    DATA_INPUT_SOURCE_STORAGE,
#endif
#if (ENABLE_FM_RADIO)
    DATA_INPUT_SOURCE_FMRADIO,
#endif

    DATA_INPUT_SOURCE_NUM,
    DATA_INPUT_SOURCE_NONE = DATA_INPUT_SOURCE_NUM,
} E_DATA_INPUT_SOURCE;

typedef enum
{
    MS_NR_MIN,
    // ------------------------------------
    MS_NR_OFF = MS_NR_MIN,
    MS_NR_LOW,
    MS_NR_MIDDLE,
    MS_NR_HIGH,
    MS_NR_AUTO,
    // ------------------------------------
    MS_NR_NUM,
	MS_NR_DEFAULT,
}EN_MS_NR;

typedef enum
{
    MS_MPEG_NR_MIN,
    // ------------------------------------
    MS_MPEG_NR_OFF = MS_MPEG_NR_MIN,
    MS_MPEG_NR_LOW,
    MS_MPEG_NR_MIDDLE,
    MS_MPEG_NR_HIGH,
    MS_MPEG_NR_DEFAULT,
    // ------------------------------------
    MS_MPEG_NR_NUM,
} EN_MS_MPEG_NR;

typedef enum
{
    AD_SPEAKER,
    AD_HEADPHONE,
    AD_BOTH,
} EN_SOUND_AD_OUTPUT;

typedef enum
{
    AUD_MODE_LR,
    AUD_MODE_LL,
    AUD_MODE_RR,
    AUD_MODE_NUM
} EN_AUD_MODE;

typedef enum
{
    SURROUND_MODE_MOUNTAIN,       //0
    SURROUND_MODE_CHAMPAIGN,      //1
    SURROUND_MODE_CITY,           //2
    SURROUND_MODE_THEATER,        //3
    SURROUND_MODE_NUM
} EN_SURROUND_TYPE;

//============ TIME ======================================================
typedef enum
{
    EN_ClockMode_Manual,
    EN_ClockMode_Auto,
    EN_ClockMode_Num
} EN_MENU_ClockMode;


typedef enum
{
    EN_Clock_TimeZone_0,  //GMT - 12:00
    EN_Clock_TimeZone_1,  //GMT - 11:30
    EN_Clock_TimeZone_2,  //GMT - 11:00
    EN_Clock_TimeZone_3,  //GMT - 10:30
    EN_Clock_TimeZone_4,  //GMT - 10:00
    EN_Clock_TimeZone_5,  //GMT - 09:30
    EN_Clock_TimeZone_6,  //GMT - 09:00
    EN_Clock_TimeZone_7,  //GMT - 08:30
    EN_Clock_TimeZone_8,  //GMT - 08:00
    EN_Clock_TimeZone_9,  //GMT - 07:30
    EN_Clock_TimeZone_10, //GMT - 07:00
    EN_Clock_TimeZone_11, //GMT - 06:30
    EN_Clock_TimeZone_12, //GMT - 06:00
    EN_Clock_TimeZone_13, //GMT - 05:30
    EN_Clock_TimeZone_14, //GMT - 05:00
    EN_Clock_TimeZone_15, //GMT - 04:30
    EN_Clock_TimeZone_16, //GMT - 04:00
    EN_Clock_TimeZone_17, //GMT - 03:30
    EN_Clock_TimeZone_18, //GMT - 03:00
    EN_Clock_TimeZone_19, //GMT - 02:30
    EN_Clock_TimeZone_20, //GMT - 02:00
    EN_Clock_TimeZone_21, //GMT - 01:30
    EN_Clock_TimeZone_22, //GMT - 01:00
    EN_Clock_TimeZone_23, //GMT - 00:30
    EN_Clock_TimeZone_24, //GMT + 00:00
    EN_Clock_TimeZone_25, //GMT + 00:30
    EN_Clock_TimeZone_26, //GMT + 01:00
    EN_Clock_TimeZone_27, //GMT + 01:30
    EN_Clock_TimeZone_28, //GMT + 02:00
    EN_Clock_TimeZone_29, //GMT + 02:30
    EN_Clock_TimeZone_30, //GMT + 03:00
    EN_Clock_TimeZone_31, //GMT + 03:30
    EN_Clock_TimeZone_32, //GMT + 04:00
    EN_Clock_TimeZone_33, //GMT + 04:30
    EN_Clock_TimeZone_34, //GMT + 05:00
    EN_Clock_TimeZone_35, //GMT + 05:30
    EN_Clock_TimeZone_36, //GMT + 06:00
    EN_Clock_TimeZone_37, //GMT + 06:30
    EN_Clock_TimeZone_38, //GMT + 07:00
    EN_Clock_TimeZone_39, //GMT + 07:30
    EN_Clock_TimeZone_40, //GMT + 08:00, -> Taipei, Beijing, Hong Kong
    EN_Clock_TimeZone_41, //GMT + 08:30
    EN_Clock_TimeZone_42, //GMT + 09:00
    EN_Clock_TimeZone_43, //GMT + 09:30
    EN_Clock_TimeZone_44, //GMT + 10:00
    EN_Clock_TimeZone_45, //GMT + 10:30
    EN_Clock_TimeZone_46, //GMT + 11:00
    EN_Clock_TimeZone_47, //GMT + 11:30
    EN_Clock_TimeZone_48, //GMT + 12:00
    EN_Clock_TimeZone_Num
} EN_MENU_Clock_TimeZone;

typedef enum
{
    EN_Time_OffTimer_Off,
    EN_Time_OffTimer_Once,
    EN_Time_OffTimer_Everyday,
    EN_Time_OffTimer_Mon2Fri,
    EN_Time_OffTimer_Mon2Sat,
    EN_Time_OffTimer_Sat2Sun,
    EN_Time_OffTimer_Sun,
    EN_Time_OffTimer_Num
} EN_MENU_TIME_OffTimer;

typedef enum
{
    EN_Time_OnTimer_Off,
    EN_Time_OnTimer_Once,
    EN_Time_OnTimer_Everyday,
    EN_Time_OnTimer_Mon2Fri,
    EN_Time_OnTimer_Mon2Sat,
    EN_Time_OnTimer_Sat2Sun,
    EN_Time_OnTimer_Sun,
    EN_Time_OnTimer_Num
} EN_MENU_TIME_OnTimer;

typedef enum
{
    EN_Time_OnTimer_Source_Min,

#if (ENABLE_ATSC)
    EN_Time_OnTimer_Source_ATSC ,
#else
    EN_Time_OnTimer_Source_ATV,
#endif
#if (ENABLE_DVBT)
    EN_Time_OnTimer_Source_DVBT,
#endif

#if (ENABLE_DVBC)
    EN_Time_OnTimer_Source_DVBC,
#endif

#if (ENABLE_S2)
        EN_Time_OnTimer_Source_S2,
#endif

#if (ENABLE_DTMB)
    EN_Time_OnTimer_Source_DTMB,
#endif

#if (ENABLE_ISDBT)
    EN_Time_OnTimer_Source_ISDBT,
#endif


#if 0//(ENABLE_ATSC)
    EN_Time_OnTimer_Source_ATSC_RADIO ,
#endif
#if (ENABLE_DVBT)
    EN_Time_OnTimer_Source_DVBT_RADIO ,
#endif

#if (ENABLE_DVBC)
    EN_Time_OnTimer_Source_DVBC_RADIO ,
#endif

#if (ENABLE_S2)
    EN_Time_OnTimer_Source_S2_RADIO ,
#endif

#if (ENABLE_DTMB)
    EN_Time_OnTimer_Source_DTMB_RADIO ,
#endif

#if (ENABLE_ISDBT)
    EN_Time_OnTimer_Source_ISDBT_RADIO ,
#endif


   // EN_Time_OnTimer_Source_RADIO,

    #if NORDIG_FUNC //for Nordig Spec v2.0
#if 0//(ENABLE_ATSC)
    EN_Time_OnTimer_Source_ATSC_DATA ,
#endif
#if (ENABLE_DVBT)
    EN_Time_OnTimer_Source_DVBT_DATA ,
#endif

#if (ENABLE_DVBC)
    EN_Time_OnTimer_Source_DVBC_DATA ,
#endif

#if (ENABLE_S2)
    EN_Time_OnTimer_Source_S2_DATA ,
#endif

#if (ENABLE_DTMB)
    EN_Time_OnTimer_Source_DTMB_DATA ,
#endif

#if (ENABLE_ISDBT)
    EN_Time_OnTimer_Source_ISDBT_DATA ,
#endif


    //EN_Time_OnTimer_Source_DATA,
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 1)
    EN_Time_OnTimer_Source_SCART,
    #endif

    #if (INPUT_SCART_VIDEO_COUNT >= 2)
    EN_Time_OnTimer_Source_SCART2,
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT>=1)
    EN_Time_OnTimer_Source_COMPONENT,      // VIDEO - YPbPr
    #endif

    #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
    EN_Time_OnTimer_Source_COMPONENT2,
    #endif

    EN_Time_OnTimer_Source_RGB,            // PC - VGA

    #if (INPUT_HDMI_VIDEO_COUNT >= 1)
    EN_Time_OnTimer_Source_HDMI,           // HDMI
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 2)
    EN_Time_OnTimer_Source_HDMI2,
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 3)
    EN_Time_OnTimer_Source_HDMI3,
    #endif

    #if (INPUT_HDMI_VIDEO_COUNT >= 4)
    EN_Time_OnTimer_Source_HDMI4,
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 1)
    EN_Time_OnTimer_Source_AV,             // VIDEO - CVBS
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 2)
    EN_Time_OnTimer_Source_AV2,
    #endif

    #if (INPUT_AV_VIDEO_COUNT >= 3)
    EN_Time_OnTimer_Source_AV3,
    #endif

    #if (INPUT_SV_VIDEO_COUNT >= 1)
    EN_Time_OnTimer_Source_SVIDEO,
    #endif

    #if ((INPUT_SV_VIDEO_COUNT >= 2))
    EN_Time_OnTimer_Source_SVIDEO2,
    #endif

    #if ENABLE_DMP
    EN_Time_OnTimer_Source_MPLAYER,
    //EN_Time_OnTimer_Source_DLNA, //must
 //   EN_Time_OnTimer_Source_NUM,
    #endif //#if ENABLE_DMP

    EN_Time_OnTimer_Source_Num,
} EN_MENU_TIME_OnTimer_Source;

typedef enum
{
    EN_Time_AutoOff_Off,
    EN_Time_AutoOff_On,
    EN_Time_AutoOff_Num
} EN_MENU_TIME_AutoOff;

typedef enum
{
    STATE_AUTOSLEEP_NEVER,
    STATE_AUTOSLEEP_4HOUR,
    STATE_AUTOSLEEP_6HOUR,
    STATE_AUTOSLEEP_8HOUR,
    STATE_AUTOSLEEP_NUM,
}EN_AUTOSLEEP_TIME_STATE;

#define EN_AUTOSLEEP_TIME_STATE_SETTING EN_AUTOSLEEP_TIME_STATE


typedef enum _EN_MENU_TIMEZONE
{
    TIMEZONE_GMT_Minus6_START,
    TIMEZONE_GMT_Minus6_END,

#if 1 //ENABLE_SBTVD_DTV_SYSTEM
    //GMT - 5
    TIMEZONE_GMT_Minus5_START,
    TIMEZONE_AM_WEST=TIMEZONE_GMT_Minus5_START,
    TIMEZONE_ACRE,
    TIMEZONE_GMT_Minus5_END=TIMEZONE_ACRE,

    //GMT - 4
    TIMEZONE_GMT_Minus4_START,
    TIMEZONE_M_GROSSO=TIMEZONE_GMT_Minus4_START,
    TIMEZONE_NORTH,
    TIMEZONE_GMT_Minus4_END=TIMEZONE_NORTH,

    //GMT - 3
    TIMEZONE_GMT_Minus3_START,
    TIMEZONE_BRASILIA=TIMEZONE_GMT_Minus3_START,
    TIMEZONE_NORTHEAST,
    TIMEZONE_GMT_Minus3_END=TIMEZONE_NORTHEAST,

    //GMT - 2
    TIMEZONE_GMT_Minus2_START,
    TIMEZONE_F_NORONHA=TIMEZONE_GMT_Minus2_START,
    TIMEZONE_GMT_Minus2_END=TIMEZONE_F_NORONHA,

#endif

    // GMT
    TIMEZONE_GMT_0_START,
    TIMEZONE_CANARY=TIMEZONE_GMT_0_START,
    TIMEZONE_LISBON,
    TIMEZONE_LONDON,
    TIMEZONE_RABAT,
	//TIMEZONE_DUBLIN,
	TIMEZONE_GMT_0_END=TIMEZONE_RABAT,

    // GMT + 1
    TIMEZONE_GMT_1_START,
    TIMEZONE_AMSTERDAM=TIMEZONE_GMT_1_START,
    TIMEZONE_BEOGRAD,
    TIMEZONE_BERLIN,
    TIMEZONE_BRUSSELS,
    TIMEZONE_BUDAPEST,
    TIMEZONE_COPENHAGEN,
    TIMEZONE_LIUBLJANA,
    TIMEZONE_LUXEMBOURG,
    TIMEZONE_MADRID,
    TIMEZONE_OSLO,
    TIMEZONE_PARIS,
    TIMEZONE_PRAGUE,
    TIMEZONE_BRATISLAVA,
    TIMEZONE_BERN,
    TIMEZONE_ROME,
    TIMEZONE_STOCKHOLM,
    TIMEZONE_WARSAW,
    TIMEZONE_VIENNA,
    TIMEZONE_ZAGREB,
    TIMEZONE_TUNIS,
    TIMEZONE_ALGIERS,
    TIMEZONE_GMT_1_END=TIMEZONE_ALGIERS,

    // GMT + 2
    TIMEZONE_GMT_2_START,
    TIMEZONE_ATHENS=TIMEZONE_GMT_2_START,
    TIMEZONE_BUCURESTI,
    TIMEZONE_HELSINKI,
    TIMEZONE_SOFIA,
    TIMEZONE_CAIRO,
    TIMEZONE_CAPE_TOWN,
    //TIMEZONE_ESTONIA,
    TIMEZONE_TURKEY,
    TIMEZONE_JERUSSLEM,
    TIMEZONE_GMT_2_END=TIMEZONE_JERUSSLEM,

    // GMT + 3
    TIMEZONE_GMT_3_START,
    TIMEZONE_MOSCOW=TIMEZONE_GMT_3_START,
    TIMEZONE_KUWAIT,
    TIMEZONE_DOHA,
    TIMEZONE_RIYADH,
    TIMEZONE_KENYA,
    TIMEZONE_MANAMA,
    TIMEZONE_GMT_3_END=TIMEZONE_MANAMA,

    // GMT + 3.5
    TIMEZONE_GMT_3Point5_START,
    TIMEZONE_TEHERAN=TIMEZONE_GMT_3Point5_START,
    TIMEZONE_GMT_3Point5_END=TIMEZONE_TEHERAN,

    // GMT + 4
    TIMEZONE_GMT_4_START,
    TIMEZONE_ABU_DHABI=TIMEZONE_GMT_4_START,
    TIMEZONE_MUSCAT,
    TIMEZONE_GMT_4_END=TIMEZONE_MUSCAT,

    // GMT + 6.5
    TIMEZONE_GMT_6Point5_START,
    TIMEZONE_MYANMAR=TIMEZONE_GMT_6Point5_START,
    TIMEZONE_GMT_6Point5_END=TIMEZONE_MYANMAR,

    //GMT + 7
    TIMEZONE_GMT_7_START,
    TIMEZONE_HCMC=TIMEZONE_GMT_7_START,
    TIMEZONE_BANGKOK,
    TIMEZONE_THAILAND,
    TIMEZONE_VIETNAM,
    TIMEZONE_INDONESIA_WEST,
    TIMEZONE_GMT_7_END=TIMEZONE_INDONESIA_WEST,

    //GMT + 8
    TIMEZONE_GMT_8_START,
    TIMEZONE_WA=TIMEZONE_GMT_8_START,
    TIMEZONE_KUALA_LUMPUR,
    TIMEZONE_INDONESIA_CENTER,
    TIMEZONE_SINGAPORE,
    TIMEZONE_BEIJING,
    TIMEZONE_GMT_8_END=TIMEZONE_BEIJING,

    // GMT + 9
    TIMEZONE_GMT_9_START,
    TIMEZONE_INDONESIA_EAST=TIMEZONE_GMT_9_START,
    TIMEZONE_GMT_9_END=TIMEZONE_INDONESIA_EAST,

    //GMT + 9.5
    TIMEZONE_GMT_9Point5_START,
    TIMEZONE_SA=TIMEZONE_GMT_9Point5_START,
    TIMEZONE_NT,
    TIMEZONE_GMT_9Point5_END=TIMEZONE_NT,

    //GMT + 10
    TIMEZONE_GMT_10_START,
    TIMEZONE_NSW=TIMEZONE_GMT_10_START,
    TIMEZONE_VIC,
    TIMEZONE_QLD,
    TIMEZONE_TAS,
    TIMEZONE_GMT_10_END=TIMEZONE_TAS,

    //GMT +  12
    TIMEZONE_GMT_12_START,
    TIMEZONE_NZST = TIMEZONE_GMT_12_START,
    TIMEZONE_GMT_12_END =TIMEZONE_NZST,

    //GMT - 1
    TIMEZONE_GMT_Minus1_START,
    TIMEZONE_AZORES=TIMEZONE_GMT_Minus1_START,
    TIMEZONE_GMT_Minus1_END=TIMEZONE_AZORES,

    TIMEZONE_NUM, //TIMEZONE MAX
} EN_MENU_TIMEZONE;

typedef enum
{
    SOUND_MODE_STANDARD,
    SOUND_MODE_MUSIC,
    SOUND_MODE_MOVIE,
    SOUND_MODE_SPORTS,
    SOUND_MODE_USER,
    SOUND_MODE_NUM
} EN_SOUND_MODE;

typedef enum
{
//#if (TV_SYSTEM == TV_NTSC)
    SOUND_MTS_MONO,
    SOUND_MTS_STEREO,
    SOUND_MTS_SAP,
//#elif ( TV_SYSTEM == TV_PAL )
//    SOUND_MTS_MONO,
//    SOUND_MTS_STEREO,
    SOUND_MTS_I,
    SOUND_MTS_II,
//#endif
    SOUND_MTS_NUM,

    SOUND_MTS_LANG_AB,
    SOUND_MTS_NICAM,
    SOUND_MTS_AUTO,
    SOUND_MTS_NONE
}EN_SOUND_MTS_TYPE;

typedef enum
{
    TVspeaker_Mode_IntSpeaker,      // TV un-mute its speakers. System Audio Control feature is not available
    TVspeaker_Mode_ExtAmp,  // If the System Audio Mode is off, then the audio control of the TV shall work as if ¡§On¡¨were selected
    TVspecker_Mode_NUM,
} EN_TVspeaker_MODE;

// This Enum is for UI part, dont use it for Core (Kernel)
typedef enum
{
    //EN_AspectRatio_Full,
    EN_AspectRatio_16X9     = 0,
    EN_AspectRatio_JustScan = 1,
    EN_AspectRatio_Original = 2, // Auto
    EN_AspectRatio_4X3      = 3,
    EN_AspectRatio_14X9     = 4,
    EN_AspectRatio_Zoom1    = 5,
    EN_AspectRatio_Zoom2    = 6,
    EN_AspectRatio_Panorama = 7,
    EN_AspectRatio_Point_to_Point = 8,
    EN_AspectRatio_Num,
} EN_MENU_AspectRatio;


#if(ENABLE_S2)
typedef enum
{
    EN_SORT_BY_DEFAULT,
    EN_SORT_BY_FREQ,
    EN_SORT_BY_SERVICE_NAME,
    EN_SORT_BY_SAT_NAME,
    EN_SORT_BY_Encrypt,
#if(ENABLE_S2_PROGRAM_PREPARE)
	EN_SORT_BY_PREPARE,
#endif
    EN_SORT_BY_MAX,
}EN_SORT_TYPE;
#endif

//******************************************************************************
//          Structures
//******************************************************************************
typedef struct
{
    U16 u16Year:12;
    U16 u8Month:4;
    U16 u8Day:5;
    U16 u8Hour:5;
    U16 u8Min:6;
    U8 u8Sec;
} ST_TIME;

typedef struct
{
    U16 wTimeDataCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    U16 cOnTimerChannel;
    U16 u16OffTimer_Info_Hour;
    U16 u16OffTimer_Info_Min;
    U16 u16OnTimer_Info_Hour;
    U32 u32ElapsedTimeCnt;
    S32 s32Offset_Time;
    EN_MENU_TIMEZONE                enTimeZone;
    EN_MENU_Clock_TimeZone          en_Clock_TimeZone;
    EN_MENU_ClockMode               en_ClockMode;
    EN_MENU_TIME_OffTimer           cOffTimerFlag;
    EN_MENU_TIME_OnTimer            cOnTimerFlag;
    EN_MENU_TIME_OnTimer_Source     cOnTimerSourceFlag;
    EN_MENU_TIME_AutoOff            cAutoSleepFlag;
    EN_AUTOSLEEP_TIME_STATE_SETTING cAutoSleepSetting;
    U8  cOnTimerVolume;
    U16 u16OnTimer_Info_Min;
    U8 NVRAM_g_u8TimeInfo_Flag;
}MS_TIME;

typedef struct
{
    EN_MS_NR eNR;                   // NR
    EN_MS_MPEG_NR eMPEG_NR;         // MPEG NR
} T_MS_NR_MODE;


#define ADC_CAL_NONE    0
#define ADC_CAL_DONE    0xAA

/// XC - ADC setting
typedef struct
{
    U16 u16ADCDataCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    APIXC_AdcGainOffsetSetting stAdcGainOffsetSetting;
    U8 u8CalibrationMode;  ///calibration mode
    U8 u8AdcCalOK;      ///< ADC Cal OK
} MS_ADC_SETTING;

//---------------------------------------------------------------------------------------
/// Country

typedef enum
{
    E_COUNTRY_MIN,
    // ------------------------------------
    E_AUSTRALIA = E_COUNTRY_MIN,    /// 0   < Australia
    E_AUSTRIA,                      /// 1   < Austria
    E_BELGIUM,                      /// 2   < Belgium
    E_BULGARIA,                     /// 3   < Bulgaria
    E_CROATIA,                      /// 4   < Croatia
    E_CZECH,                        /// 5   < Czech
    E_DENMARK,                      /// 6   < Denmark
    E_FINLAND,                      /// 7   < Finland
    E_FRANCE,                       /// 8   < France
    E_GERMANY,                      /// 9   < Germany
    E_GREECE,                       /// 10  < Greece
    E_HUNGARY,                      /// 11  < Hungary
    E_ITALY,                        /// 12  < Italy
    E_IRELAND,                      /// 13  < Ireland////TODO, wait UI
    E_LUXEMBOURG,                   /// 14  < Luxembourg
    E_NETHERLANDS,                  /// 15  < Netherland
    E_NORWAY,                       /// 16  < Norway
    E_POLAND,                       /// 17  < Poland
    E_PORTUGAL,                     /// 18  < Portugal
    E_ROMANIA,                      /// 19  < Romania
    E_RUSSIA,                       /// 20  < Russia
    E_SERBIA,                       /// 21  < Serbia
    E_SLOVENIA,                     /// 22  < Slovenia
    E_SPAIN,                        /// 23  < Spain
    E_SWEDEN,                       /// 24  < Sweden
    E_SWITZERLAND,                  /// 25  < Switzerland
    E_UK,                           /// 26  < UK
    E_UNITED_ARAB_EMIRATES,         /// 27  < United Arab Emirates
    E_NEWZEALAND,                   /// 28  < New Zealand
    E_CHINA,                        /// 29  < China
    E_ESTONIA,                      /// 30  < Estonia
    E_TURKEY,                       /// 31  < Turkey
    E_MOROCCO,                      /// 32  < Morocco
    E_TUNIS,                        /// 33  < Tunis
    E_ALGERIA,                      /// 34  < Algeria
    E_EGYPT,                        /// 35  < Egypt
    E_SOUTH_AFRICA,                 /// 36  < South Africa
    E_ISRAEL,                       /// 37  < Israel
    E_IRAN,                         /// 38  < Iran
    E_SLOVAKIA,                     /// 39  < Slovakia
    E_THAILAND,                     /// 40  < Thailand
    E_VIETNAM,                      /// 41  < Vietnam
    E_SINGAPORE,                    /// 42  < Sinapore
    E_MALAYSIA,                     /// 43  < Malaysia
    E_INDONESIA,                    /// 44  < Indonesia
    E_KUWAIT,                       /// 45  < Kuwait
    E_OMAN,                         /// 46  < Oman
    E_QATAR,                        /// 47  < Qatat
    E_SAUDI_ARABIA,                 /// 48  < Saudi Arabia
    E_BAHRAIN,                      /// 49  < Bahrain
    E_KENYA,                        /// 50  < Kenya
    E_MYANMAR,                      /// 51  < MYANMAR
    E_GHANA,                        /// 52  < Ghana
    E_ICELAND,                      /// 53  < Iceland
    E_SAMI,                         /// 54  < Sami

#if (ENABLE_DVB_TAIWAN_APP)
    E_TAIWAN,                       ///     < Taiwan
#endif

    E_BRAZIL,                       ///     < Brazil

    // ------------------------------------
    E_COUNTRY_NUM,
} MEMBER_COUNTRY;

#define    OSD_COUNTRY_AUSTRALIA       E_AUSTRALIA
#define    OSD_COUNTRY_AUSTRIA         E_AUSTRIA
#define    OSD_COUNTRY_BELGIUM         E_BELGIUM
#define    OSD_COUNTRY_BULGARIA        E_BULGARIA
#define    OSD_COUNTRY_CROATIA         E_CROATIA
#define    OSD_COUNTRY_CZECH           E_CZECH
#define    OSD_COUNTRY_DENMARK         E_DENMARK
#define    OSD_COUNTRY_FINLAND         E_FINLAND
#define    OSD_COUNTRY_FRANCE          E_FRANCE
#define    OSD_COUNTRY_GERMANY         E_GERMANY
#define    OSD_COUNTRY_GREECE          E_GREECE
#define    OSD_COUNTRY_HUNGARY         E_HUNGARY
#define    OSD_COUNTRY_ITALY           E_ITALY
#define    OSD_COUNTRY_IRELAND         E_IRELAND
#define    OSD_COUNTRY_LUXEMBOURG      E_LUXEMBOURG
#define    OSD_COUNTRY_NETHERLANDS     E_NETHERLANDS
#define    OSD_COUNTRY_NORWAY          E_NORWAY
#define    OSD_COUNTRY_POLAND          E_POLAND
#define    OSD_COUNTRY_PORTUGAL        E_PORTUGAL
#define    OSD_COUNTRY_ROMANIA         E_ROMANIA
#define    OSD_COUNTRY_RUSSIA          E_RUSSIA
#define    OSD_COUNTRY_SERBIA          E_SERBIA
#define    OSD_COUNTRY_SLOVENIA        E_SLOVENIA
#define    OSD_COUNTRY_SPAIN           E_SPAIN
#define    OSD_COUNTRY_SWEDEN          E_SWEDEN
#define    OSD_COUNTRY_SWITZERLAND     E_SWITZERLAND
#define    OSD_COUNTRY_UK              E_UK
#define    OSD_COUNTRY_UNITED_ARAB_EMIRATES     E_UNITED_ARAB_EMIRATES
#define    OSD_COUNTRY_NEWZEALAND      E_NEWZEALAND
#define    OSD_COUNTRY_CHINA           E_CHINA
#define    OSD_COUNTRY_ESTONIA         E_ESTONIA
#define    OSD_COUNTRY_TURKEY          E_TURKEY
#define    OSD_COUNTRY_MOROCCO         E_MOROCCO
#define    OSD_COUNTRY_TUNIS           E_TUNIS
#define    OSD_COUNTRY_ALGERIA         E_ALGERIA
#define    OSD_COUNTRY_EGYPT           E_EGYPT
#define    OSD_COUNTRY_SOUTH_AFRICA    E_SOUTH_AFRICA
#define    OSD_COUNTRY_ISRAEL          E_ISRAEL
#define    OSD_COUNTRY_IRAN            E_IRAN
#define    OSD_COUNTRY_SLOVAKIA        E_SLOVAKIA
#define    OSD_COUNTRY_THAILAND        E_THAILAND
#define    OSD_COUNTRY_VIETNAM         E_VIETNAM
#define    OSD_COUNTRY_SINGAPORE       E_SINGAPORE
#define    OSD_COUNTRY_MALAYSIA        E_MALAYSIA
#define    OSD_COUNTRY_INDONESIA       E_INDONESIA
#define    OSD_COUNTRY_KUWAIT          E_KUWAIT
#define    OSD_COUNTRY_OMAN            E_OMAN
#define    OSD_COUNTRY_QATAR           E_QATAR
#define    OSD_COUNTRY_SAUDI_ARABIA    E_SAUDI_ARABIA
#define    OSD_COUNTRY_BAHRAIN         E_BAHRAIN
#define    OSD_COUNTRY_KENYA           E_KENYA
#define    OSD_COUNTRY_MYANMAR         E_MYANMAR
#define    OSD_COUNTRY_GHANA           E_GHANA
#define    OSD_COUNTRY_ICELAND         E_ICELAND
#define    OSD_COUNTRY_SAMI            E_SAMI

#if (ENABLE_DVB_TAIWAN_APP)
#define    OSD_COUNTRY_TAIWAN          E_TAIWAN
#endif
#define    OSD_COUNTRY_BRAZIL          E_BRAZIL

#define    OSD_COUNTRY_NUMS    E_COUNTRY_NUM


#define EN_OSD_COUNTRY_SETTING  MEMBER_COUNTRY

//----------------------------------------------------------------------------------------

//******************************************************************************

#endif // #ifndef MAPP_GLOBALSETTINGSTCOMMON_H

