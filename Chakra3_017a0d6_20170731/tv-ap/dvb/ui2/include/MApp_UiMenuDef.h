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

#ifndef MAPP_UI_MENUDEF_H
#define MAPP_UI_MENUDEF_H
#include "MsCommon.h"
#include "msAPI_OSD.h"
#include "MApp_GlobalVar.h"
#include "MApp_Sleep.h"

#define OSD_GOP_ID              E_GOP_OSD

#define ENABLE_MHEG_MSG         1
#if ENABLE_OAD
#define OAD_MENU                1
#else //(!ENABLE_OAD)
#define OAD_MENU                0
#endif //(!ENABLE_OAD)

typedef enum
{
    MIA_NOTHING,
    MIA_GOTONEXT,           // Goto next page
    MIA_GOTOPREV,           // Goto prev
    MIA_NEXTITEM,           // Goto next item

    MIA_PREVITEM,           // Goto prev item
    MIA_EXIT,               // Exit OSD Main Menu
    MIA_REDRAWMENU,
    MIA_INCVALUE,           // Increase Value
    MIA_DECVALUE,           // Decrease Value
    MIA_INCVALUE_OFFTIME,   // Increase Value
    MIA_DECVALUE_OFFTIME,   // Decrease Value
    MIA_INCVALUE_ONTIME,
    MIA_DECVALUE_ONTIME,
    MIA_INCVALUE_CHTYPE,     // Increase Value
    MIA_DECVALUE_CHTYPE,     // Decrease Value
    MIA_INCVALUE_CHNUMBER,   // Increase Value
    MIA_DECVALUE_CHNUMBER,   // Decrease Value
    MIA_INCVALUE_BAR,        // Increase Value
    MIA_DECVALUE_BAR,        // Decrease Value
    MIA_EXECFUNC,
    MIA_EXEC_NEXTITEM,       // Execute item function then Goto Next Item
    MIA_EXEC_PREVITEM,       // Execute item function then Goto Prev Item
    MIA_EXEC_GOTONEXT,       // Execute item function then Goto Next Function
    MIA_EXEC_GOTOPREV,       // Execute item function then Goto Prev Function
    MIA_EXECRECALL,          // Execute Recall Function
    MIA_SOURCE,

    MIA_FACTORY,
    MIA_INSTART,

    #if OAD_MENU
    MIA_OAD_MENU,
    MIA_OAD_REDRAW,
    #endif //OAD_MENU

    MIA_PARENTAL_BLOCK,     // For Parental block
    MIA_VOLUME,
    MIA_TV_AUTO_SCAN,
    MIA_BRIGHTNESS,         // For BRIGHTNESS Hotkey

    MIA_SUBTITLE_MODE,
    MIA_PICTURE_MODE,       // For Picture Hotkey
    MIA_PICTURE_MODE_ADJ,   // For Picture Hotkey
    MIA_SLEEP_MODE,         //for sleep hot key
    MIA_SLEEP_MODE_ADJ,
    MIA_FREEZE,
    MIA_AUDIO_MODE,
    MIA_AUDIO_MODE_ADJ,
    MIA_MTS_MODE,
    MIA_MTS_MODE_ADJ,
    MIA_ZOOM_MODE,
    MIA_ZOOM_ARROW_UP,
    MIA_ZOOM_ARROW_DOWN,
    MIA_ZOOM_ARROW_LEFT,
    MIA_ZOOM_ARROW_RIGHT,
    MIA_DSC_KEY_ARC4X3,
    MIA_DSC_KEY_ARC16X9,
    MIA_DSC_KEY_ARCZOOM,
    MIA_DSC_KEY_ARCPANORAMA,
    MIA_ZOOM_MODE_ADJ,
    MIA_DSC_KEY_TV,
    MIA_DSC_KEY_VIDEO1,
    MIA_DSC_KEY_VIDEO2,
    MIA_DSC_KEY_VIDEO3,
    MIA_DSC_KEY_COMP1,
    MIA_DSC_KEY_COMP2,
    MIA_DSC_KEY_RGBPC,
    MIA_DSC_KEY_RGBDTV,
    MIA_DSC_KEY_RGBDVI,
    MIA_DSC_KEY_HDMI1,
    MIA_DSC_KEY_HDMI2,
    MIA_DSC_KEY_MULTI_PIP,
    MIA_DSC_KEY_MULTIMEDIA,
    MIA_DSC_KEY_DVIPC,
    MIA_MSGBOX_EVENT_INFO,
    MIA_PROGRAM_BRIEF_INFO,
    MIA_PROGRAM_EXTEND_INFO,
    MIA_SOURCE_TV,
    MIA_SOURCE_AV,
    MIA_SOURCE_SV,
    MIA_SOURCE_YCBCR,
    MIA_EVENT_INFO,
    MIA_EXTEND_INFO,
    MIA_MUTE,
    MIA_ZOOM,
    MIA_MTS,
    MIA_SLEEP,
    MIA_POWER,
    MIA_PROGRAM_INFO_MSG_BOX,
    MIA_RADIO_CH_MSG_BOX,
    MIA_INVALID_SERVICE_MSG_BOX,
    MIA_NO_SIGNAL_MSG_BOX,
    MIA_NO_DATABASE_MSG_BOX,
    MIA_NO_SYNC_MSG_BOX,
    MIA_NO_CABLE_MSG_BOX,
    MIA_NO_PROGRAMS_SHOWN_MSG_BOX,
    MIA_UNSUPPORTED_MODE_MSG_BOX,
    MIA_CHANNEL_BLOCK_MSG_BOX,
    MIA_SCRAMBLE_CHANNEL_MSG_BOX,
    MIA_SCRAMBLED_PROGRAM_SHOWN_MSG_BOX,
    MIA_MHEG_CH_MSG_BOX,

    MIA_RECENT_CHANNEL_POWER,
    MIA_RECENT_CHANNEL_EXIT,
    MIA_RECENT_CHANNEL_UP,
    MIA_RECENT_CHANNEL_DOWN,
    MIA_RECENT_CHANNEL_LEFT,
    MIA_RECENT_CHANNEL_RIGHT,
    MIA_RECENT_CHANNEL_SWITCH,
    MIA_RECENT_CHANNEL_SELECT,

    MIA_CHANNEL_LIST_INIT,
    MIA_CHANNEL_LIST_SELECT,
    MIA_CHANNEL_LIST_UP,
    MIA_CHANNEL_LIST_DOWN,
    MIA_CHANNEL_LIST_PREVPAGE,
    MIA_CHANNEL_LIST_NEXTPAGE,

    MIA_CHANNEL_EDIT_INIT,
    MIA_CHANNEL_EDIT_SELECT,
    MIA_CHANNEL_EDIT_UP,
    MIA_CHANNEL_EDIT_DOWN,
    MIA_CHANNEL_EDIT_LEFT,
    MIA_CHANNEL_EDIT_RIGHT,
    MIA_CHANNEL_EDIT_PREVPAGE,
    MIA_CHANNEL_EDIT_NEXTPAGE,
    MIA_MANUAL_SCAN_MENU,

    MIA_GOTO_CIMMI,
    MIA_GOTO_CHANNEL_EDIT,
    MIA_GOTO_BLOCK_EDIT,

    MIA_CHANNEL_EDIT_MENU,
    MIA_CHANNEL_EDIT_CMF_MENU,
    MIA_CHANNEL_EDIT_FAV,
    MIA_CHANNEL_EDIT_SKIP,
    MIA_CHANNEL_EDIT_LOCK,
    MIA_CHANNEL_EDIT_DELETE,
    MIA_CHANNEL_EDIT_RENAME,
    MIA_CHANNEL_EDIT_MOVE,

    MIA_FAVORITE_LIST_INIT,
    MIA_FAVORITE_LIST_SELECT,
    MIA_FAVORITE_LIST_UP,
    MIA_FAVORITE_LIST_DOWN,
    MIA_FAVORITE_LIST_PREVPAGE,
    MIA_FAVORITE_LIST_NEXTPAGE,
    MIA_FAVORITE_CHANNEL_POWER,
    MIA_FAVORITE_CHANNEL_EXIT,
    MIA_FAVORITE_CHANNEL_LEFT,
    MIA_FAVORITE_CHANNEL_RIGHT,
    MIA_COUNTER_DOWN_MSG_BOX,
    MIA_GOTO_FactoryReset,
    MIA_ITEM_GOTO_D1_CLOCK,
    MIA_OPTION_GOBACK_ITEM,
    MIA_FORWARD_TO_SURROUND_PAGE,
    MIA_NEW_OPTION_GOBACK_NEW_ITEM,
    MIA_NEW_ITEM_GOTO_NEW_OPTION,

    MIA_MODE_GOTO_GOTO_PICTURE_USER_ADJ,
    MIA_NEW_ADJ_GOBACK_MODE,
    MIA_ITEM_GOTO_OPTION,
    MIA_ITEM_GOTO_MENUALSCAN,
    MIA_OPTION_GOTO_MODE,
    MIA_MODE_GOTO_ADJUST,
    MIA_ADJ_GOBACK_ITEM,
    MIA_ITEM_GOTO_ADJUST,
    MIA_ATV_NEXTITEM,
    MIA_ATV_PERCENT,
    MIA_ENTER_PASSWORD,
    MIA_ENTER_BLOCK_CH_PASSWORD,
    MIA_ITEM_GOTO_OPTION_DRAWFIRST,
    MIA_ITEM_GOTO_RATING,
    MIA_OPTION_GOTO_RATING,
    MIA_NEXTRATING,
    MIA_PREVRATING,
    MIA_GOTO_MSG_PAGE,
    //MIA_GOTO_HOTKEY_PAGE,
    MIA_EXIT_RESET_SETTING_MSG_PAGE,
    MIA_BACKTO_BALANCE_BAR,
    MIA_GOTO_BALANCE_BAR,
    MIA_GOTONEXT_WITHOUT_DRAWING,
    MIA_START_SCAN,
    MIA_REVERSE_OLD_COUNTRY_TO_MAINMENU,
    MIA_MSG_TO_MAINMENU,
    MIA_GOTOScanStartCHECK,
    MIA_SoftwareUpdate,
    MIA_FINISH_SCAN,
    MIA_OPEN_MAINMENU,
    MIA_START_OAD,
    MIA_SCAN_CH_TYPE,
    MIA_MANUAL_SCAN_CHANGE_RF,
    MIA_GOBACK_TWICE,
    MIA_GOBACK_TWICE_MIN,
    MIA_MANUALSCAN_CHANNELINFO,
    MIA_MANUALSCAN_ADD_DEL_CHANNEL,
    MIA_GOTO_UP,
    MIA_GOTO_DOWN,
    MIA_GOTO_LEFT,
    MIA_GOTO_RIGHT,

    MIA_EXEC_GOTO_UP,
    MIA_EXEC_GOTO_DOWN,
    MIA_EXEC_GOTO_LEFT,
    MIA_EXEC_GOTO_RIGHT,
    MIA_NEXTITEM_CLOCK,
    MIA_SCAN_EXIT_MAIN_MENU,
    MIA_NEXTITEM_TO_MANUALSCAN,
    MIA_PREVITEM_TO_MANUALSCAN,

    MIA_OPTION_GOTO_NEXT,
    MIA_SWITCH_SOURCE,
    MIA_EXEC_GOBACK_TITLE,
    MIA_NEXTITEM_EXEC,
    MIA_PREVITEM_EXEC,
    MIA_NEXTRESOLUTION,
    MIA_PREVRESOLUTION,
    MIA_PC_AUTO_CONFIG,
    MIA_PCMENU_POSITION_ADJKEY,
    MIA_EXIT_MAIN_MENU,

    MIA_MENU_TO_SCAN_INC,
    MIA_MENU_TO_SCAN_DEC,
    MIA_EPG_MANUAL_TIMER,
    MIA_EPG_TIMER_LIST,
    MIA_TIMERLIST_PREVITEM,
    MIA_TIMERLIST_NEXTITEM,
    MIA_TIMERLIST_PREVPAGE,
    MIA_TIMERLIST_NEXTPAGE,

    MIA_HKEY_AUDIO_LANG_UP,
    MIA_HKEY_AUDIO_LANG_DOWN,
    MIA_SUBTITLE_UP,
    MIA_SUBTITLE_DOWN,
    MIA_HKEY_AUDIO_LANG_LEFT,
    MIA_HKEY_AUDIO_LANG_RIGHT,

    MIA_NEXTITEM_ANI,
    MIA_PREVITEM_ANI,

    MIA_SHOW_MHEG_XOR_SUBTITLE_MSG,
    MIA_USB_EXPERT_UP,
    MIA_USB_EXPERT_DOWN,
    MIA_GOTO_WIZARD,
    #if OAD_MENU
    MIA_OAD_UPDATE,
    MIA_OAD_SHOW_STATUS,
    #endif //OAD_MENU
    MIA_SAVE_ATV_MANUALSCAN,
#if ENABLE_DMP
    MIA_MEDIA_PLAYER_GOTO_ITEM,
    MIA_MEDIAPLAYER_BOOT,
    MIA_MEDIAPLAYER_THUMBNAIL_NEXTROW,
    MIA_MEDIAPLAYER_THUMBNAIL_PREVROW,
    MIA_SOURCE_INFO_MSG_BOX,
    MIA_CHANNEL_EDIT_POWER,
    MIA_MEDIA_PLAYER_SELECT,
    MIA_MEDIA_PLAYER_UP,
    MIA_MEDIA_PLAYER_DOWN,
    MIA_MEDIA_PLAYER_LEFT,
    MIA_MEDIA_PLAYER_RIGHT,
    MIA_MEDIA_PLAYER_EXIT,
#endif
    MIA_EPGTIMER_SAVE,
    MIA_EPGTIMER_GOTO_LIST,
    MIA_EPGTIMER_GOTO_EPG,
    MIA_EPGTIMERLIST_DEL_TIMER,
    MIA_USB_DOWNLOAD_SEARCH,
    MIA_USB_DOWNLOAD_COPY,
    MIA_USB_DOWNLOAD_UPGRADE,
    MIA_EPGTIMER_COUNT_DOWN_MSG,
#if ENABLE_PVR
    MIA_TIME_SHIFT_OPEN_UI,
    MIA_TIME_SHIFT_DRAW_INDICATOR_FR_ICON,
    MIA_TIME_SHIFT_DRAW_INDICATOR_FF_ICON,
    MIA_TIME_SHIFT_DRAW_INDICATOR_PREVIOUS_ICON,
    MIA_TIME_SHIFT_DRAW_INDICATOR_NEXT_ICON,
    MIA_TIME_SHIFT_DRAW_INDICATOR_PLAY_ICON,
    MIA_TIME_SHIFT_DRAW_INDICATOR_PAUSE_ICON,
    MIA_TIME_SHIFT_DRAW_INFO,
    MIA_TIME_SHIFT_CLEAR_INFO,
    MIA_TIME_SHIFT_CLEAR_INDICATOR_ICON,
    MIA_TIME_SHIFT_CLOSE_UI,
#endif
#if ENABLE_DMP
    #if (ENABLE_POWERON_MUSIC)
    MIA_DMP_POWERON_MUSIC_DIALOG,
    #endif
    MIA_DMP_SLEEP_COUNT_DOWN,
#endif
} MenuItemActionType;

#ifdef MAPP_UIMENUDEF_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//////////////////////////////////////////////////////////////
// from MApp_UiMenuFunc.h

#define UI_TIME_YEAR_SET    0x01
#define UI_TIME_MONTH_SET   0x02
#define UI_TIME_DAY_SET     0x04
#define UI_TIME_HOUR_SET    0x08
#define UI_TIME_MINUTE_SET  0x10

#define UI_TIME_MANUAL_SET (UI_TIME_YEAR_SET|UI_TIME_MONTH_SET|UI_TIME_DAY_SET|UI_TIME_HOUR_SET|UI_TIME_MINUTE_SET)

#define UI_TIME_OFFTIME_HOUR_SET    0x20
#define UI_TIME_ONTIME_HOUR_SET     0x40
#define UI_TIME_ONTIME_MINUTE_SET   0x80
#define UI_TIME_CLOCK_PM            0x01
#define UI_TIME_OFFTIME_PM          0x02
#define UI_TIME_ONTIME_PM           0x04
#define UI_AUDIO_MONO_BITMASK       0x01
#define UI_AUDIO_STEREO_BITMASK     0x02
#define UI_AUDIO_SAP_BITMASK        0x04
#define UI_TIME_YEAR_INIT           2007
#define UI_TIME_MONTH_INIT          1
#define UI_TIME_DAY_INIT            1
#define UI_TIME_HOUR_INIT           0
#define UI_TIME_MINUTE_INIT         0

#define UI_NET_ADDRESS_A_SET        0x01
#define UI_NET_ADDRESS_B_SET        0x02
#define UI_NET_ADDRESS_C_SET        0x04
#define UI_NET_ADDRESS_D_SET        0x08
#define UI_NETWORK_INIT             0

typedef struct
{
    U16 u16SelectionItem;
    U16 u16StringIndex;
}ST_OSD_SELECTION_STRING_MAPPING_LIST;

typedef enum
{
    EN_SUBTITILE_SYSTEM_OFF=0,
    EN_SUBTITILE_SYSTEM_ON=1,
    EN_SUBTITILE_SYSTEM_NUM=2,
} EN_SUBTITILE_SYSTEM;

typedef enum
{
    EN_OSD_EFFECT_ON =0,  //default on
//    EN_OSD_EFFECT_OFF=1,
    EN_OSD_EFFECT_ROTATION_ONLY=1,
    EN_OSD_EFFECT_NUM=2,
} EN_OSD_EFFECT_MODE;

typedef enum
{
    EN_ATV_SystemType_BG=0,
    EN_ATV_SystemType_I=1,
    EN_ATV_SystemType_DK=2,
    EN_ATV_SystemType_L=3,
    EN_ATV_SystemType_M=4,
//    EN_ATV_SystemType_MAX,
} EN_ATV_SYSTEM_TYPE;

typedef enum
{
    EN_ATV_VideoStandard_PAL_BGHI        = 0x00,        // Video standard PAL BGHI
    EN_ATV_VideoStandard_NTSC_M          = 0x01,        // Video standard NTSC M
    EN_ATV_VideoStandard_SECAM           = 0x02,        // Video standard SECAM
    EN_ATV_VideoStandard_NTSC_44         = 0x03,        // Video standard  NTSC 44
    EN_ATV_VideoStandard_PAL_M           = 0x04,        // Video standard  PAL M
    EN_ATV_VideoStandard_PAL_N           = 0x05,        // Video standard  PAL N
    EN_ATV_VideoStandard_PAL_60          = 0x06,        // Video standard PAL 60
    EN_ATV_VideoStandard_AUTO            = 0x07,         // Video standard AUTO
    EN_ATV_VideoStandard_MAX
} EN_ATV_VIDEOSTANDARD_TYPE;

typedef enum
{
    EN_ATV_BandType_Cable=0,
    EN_ATV_BandType_VHF=1,
} EN_ATV_BAND_TYPE;

typedef enum
{
    EN_ManualScan_ChannelType_ATV=0,
    EN_ManualScan_ChannelType_DTV=1,
    EN_ManualScan_ChannelType_Num=2
} EN_ManualScan_ChannelType;

typedef enum
{
    EN_PictureMode_Daylight=0,
    EN_PictureMode_Normal=1,
    EN_PictureMode_NightTime=2,
    EN_PictureMode_User=3,
#if PICTURE_USER_2
    EN_PictureMode_User2=4,
    EN_PictureMode_Num=5,
#else
    EN_PictureMode_Num=4,
#endif
} EN_PICTURE_MODE;

typedef enum
{
    EN_ColorTemp_Cool=0,
    EN_ColorTemp_Medium=1,
    EN_ColorTemp_Warm=2,
    EN_ColorTemp_User=3,
    EN_ColorTemp_Num=4
} EN_COLOR_TEMPERATURE;

typedef enum
{
    EN_ColorTempUser_Red=0,
    EN_ColorTempUser_Green=1,
    EN_ColorTempUser_Blue=2,
    EN_ColorTempUser_Num=3
} EN_COLOR_TEMPERATURE_USER;

typedef enum
{
    EN_PcMode_Resolution=0,
    EN_PcMode_Position=1,
    EN_PcMode_Size=2,
    EN_PcMode_Phase=3,
    EN_PcMode_Reset=4,
} EN_PC_MODE_MENU;

typedef enum
{
    EN_PcModeResolution_1024=0,
    EN_PcModeResolution_1280=1,
    EN_PcModeResolution_1360=2,
    EN_PcModeResolution_1366=3,
    EN_PcModeResolution_Num=4,
} EN_PC_MODE_RESOLUTION;

typedef enum
{
    EN_SoundMode_Standard=0,
    EN_SoundMode_Music=1,
    EN_SoundMode_Movie=2,
    EN_SoundMode_Sports=3,
    EN_SoundMode_User=4,
    EN_SoundMode_Num=5
} EN_SOUND_MODE2;

typedef enum
{
    EN_OsdLang_English=0,
    EN_OsdLang_Spanish=1,
    EN_OsdLang_French=2,
    EN_OsdLang_Num=3
} EN_OSD_LANGUAGE;

typedef enum
{
    EN_AudioLang_English=0,
    EN_AudioLang_Spanish=1,
    EN_AudioLang_French=2,
    EN_AudioLang_Num=3
} EN_AUDIO_LANGUAGE;


typedef enum
{
    EN_LockSystem_Off,
    EN_LockSystem_On,
    EN_LockSystem_Num
} EN_LOCK_SYSTEM;
/*
typedef enum
{
    EN_MovieRating_Off,
    EN_MovieRating_X,
    EN_MovieRating_NC17,
    EN_MovieRating_R,
    EN_MovieRating_PG13,
    EN_MovieRating_PG,
    EN_MovieRating_G,
    EN_MovieRating_Num
} EN_MOVIE_RATING;

typedef enum
{
    EN_TvRating_Age,
    EN_TvRating_FantasyViolence,
    EN_TvRating_Num
} EN_TV_RATING;

typedef enum
{
    EN_TvRatingAge_Off,
    EN_TvRatingAge_TVY7,
    EN_TvRatingAge_TVY,
    EN_TvRatingAge_Num
} EN_TV_RATING_AGE;

typedef enum
{
    EN_TvRatingFantasyViolence_Off,
    EN_TvRatingFantasyViolence_TVY7,
    EN_TvRatingFantasyViolence_Num
} EN_TV_RATING_FANTASY_VIOLENCE;

typedef enum
{
    EN_TvRatingGeneral_Age,
    EN_TvRatingGeneral_Dialogue,
    EN_TvRatingGeneral_Language,
    EN_TvRatingGeneral_Sex,
    EN_TvRatingGeneral_Violence,
    EN_TvRatingGeneral_Num
} EN_TV_RATING_GENERAL;

typedef enum
{
    EN_TvRatingGeneralAge_Off,
    EN_TvRatingGeneralAge_TVMA,
    EN_TvRatingGeneralAge_TV14,
    EN_TvRatingGeneralAge_TVPG,
    EN_TvRatingGeneralAge_TVG,
    EN_TvRatingGeneralAge_Num
} EN_TV_RATING_GENERAL_AGE;

typedef enum
{
    EN_TvRatingGeneralDialogue_Off,
    EN_TvRatingGeneralDialogue_TV14,
    EN_TvRatingGeneralDialogue_TVPG,
    EN_TvRatingGeneralDialogue_Num
} EN_TV_RATING_GENERAL_DIALOGUE;

typedef enum
{
    EN_TvRatingGeneralLanguage_Off,
    EN_TvRatingGeneralLanguage_TVMA,
    EN_TvRatingGeneralLanguage_TV14,
    EN_TvRatingGeneralLanguage_TVPG,
    EN_TvRatingGeneralLanguage_Num
} EN_TV_RATING_GENERAL_LANGUAGE;

typedef enum
{
    EN_TvRatingGeneralSex_Off,
    EN_TvRatingGeneralSex_TVMA,
    EN_TvRatingGeneralSex_TV14,
    EN_TvRatingGeneralSex_TVPG,
    EN_TvRatingGeneralSex_Num
} EN_TV_RATING_GENERAL_SEX;

typedef enum
{
    EN_TvRatingGeneralViolence_Off,
    EN_TvRatingGeneralViolence_TVMA,
    EN_TvRatingGeneralViolence_TV14,
    EN_TvRatingGeneralViolence_TVPG,
    EN_TvRatingGeneralViolence_Num
} EN_TV_RATING_GENERAL_VIOLENCE;
*/
typedef enum
{
  EN_FacAdjust_ADC_Calibration,
  EN_FacAdjust_ADC,
  EN_FacAdjust_SUB_BC,
  EN_FacAdjust_WB,
  EN_FacAdjust_WhitePattern,
  EN_FacAdjust_2Hr_Off,
  EN_FacAdjust_OAD,
  EN_FacAdjust_Num,
} EN_FACTORY_ADJUST;

typedef enum
{
    EN_FacAdj_AdcAdjust_RGB,
    EN_FacAdj_AdcAdjust_R_Gain,
    EN_FacAdj_AdcAdjust_G_Gain,
    EN_FacAdj_AdcAdjust_B_Gain,
    EN_FacAdj_AdcAdjust_R_Offset,
    EN_FacAdj_AdcAdjust_G_Offset,
    EN_FacAdj_AdcAdjust_B_Offset,
    EN_FacAdj_AdcAdjust_Num,
} EN_FACTORY_ADC_ADJUST;

typedef enum
{
    EN_FacAdj_AdcMode_RGB,
    EN_FacAdj_AdcMode_Ypbpr_SD,
	EN_FacAdj_AdcMode_Ypbpr_HD,
	EN_FacAdj_AdcMode_Scart,
    EN_FacAdj_AdcMode_Ypbpr_Num,
} EN_FACTORY_ADC_ADJUST_MODE;

typedef enum
{
    EN_FacAdj_SubBcAdj_Mode,
    EN_FacAdj_SubBcAdj_Brightnes,
    EN_FacAdj_SubBcAdj_Contrast,
    EN_FacAdj_SubBcAdj_CopyAll,
    EN_FacAdj_SubBcAdj_Num,
} EN_FACTORY_SUB_BC_ADJUST;

typedef enum
{
    EN_FacAdj_SubBcAdjMode_DTV,
    EN_FacAdj_SubBcAdjMode_ATV,
    EN_FacAdj_SubBcAdjMode_AV,
    EN_FacAdj_SubBcAdjMode_COMPONENT,
    EN_FacAdj_SubBcAdjMode_RGB,
    EN_FacAdj_SubBcAdjMode_Num,
} EN_FACTORY_SUB_BC_ADJUST_MODE;

typedef enum
{
    EN_FacAdj_WB_AdjustMode,
    EN_FacAdj_WB_Temperature,
    EN_FacAdj_WB_R_Gain,
    EN_FacAdj_WB_G_Gain,
    EN_FacAdj_WB_B_Gain,
    EN_FacAdj_WB_R_Offset,
    EN_FacAdj_WB_G_Offset,
    EN_FacAdj_WB_B_Offset,
    EN_FacAdj_WB_CopyAll,
    EN_FacAdj_WB_Num,
} EN_FACTORY_WB_ADJUST;

typedef enum
{
    EN_FacAdj_WhitePattern_Off,
    EN_FacAdj_WhitePattern_White,
    EN_FacAdj_WhitePattern_Red,
    EN_FacAdj_WhitePattern_Green,
    EN_FacAdj_WhitePattern_Blue,
    EN_FacAdj_WhitePattern_Black,
    EN_FacAdj_WhitePattern_Num,
}EN_FACTORY_WHITE_PATTERN;

typedef enum
{
    EN_FacAdj_FO1_Coarse,
    EN_FacAdj_FO1_Fine,
    EN_FacAdj_FO2_Coarse,
    EN_FacAdj_FO2_Fine,
    EN_FacAdj_FO3_Coarse,
    EN_FacAdj_FO3_Fine,
    EN_FacAdj_Gain1,
    EN_FacAdj_Gain2,
    EN_FacAdj_Gain3,
    EN_FacAdj_Q1,
    EN_FacAdj_Q2,
    EN_FacAdj_Q3,
    EN_FacAdj_PEQ_Num,
}EN_FACTORY_PEQ;

typedef enum
{
    EN_FacAdj_2HourOff_Off,
    EN_FacAdj_2HourOff_On,
    EN_FacAdj_2HourOff_Num,
}EN_FACTORY_2HOURS_OFF;

typedef enum
{
    EN_SCART_SEL_AV,
    EN_SCART_SEL_SV,
    EN_SCART_SEL_NUM,
} EN_SCART_SELECT;

typedef enum
{
    EN_FacAdj_AreaOption_USA,
    EN_FacAdj_AreaOption_CANADA,
    EN_FacAdj_AreaOption_MEXICO,
    EN_FacAdj_AreaOption_Num,
}EN_FACTORY_AREA_OPTION;


// Variable Collection ================================================================
/*
typedef struct
{
    EN_PC_MODE_MENU         enMenuItem_PCMENU;
    EN_PC_MODE_RESOLUTION   enMenuItem_PCMENU_Resolution;
    EN_FACTORY_ADJUST       enMenuItem_Factory_Adjust;
} L_MENU_STATE_VAR;
*/

/*
typedef struct
{
    EN_ManualScan_ChannelType   enA2_ManualScan_ChannelType;
    U16                         u16A2_ManualScan_ChannelNumber_TV;
    U16                         u16A2_ManualScan_ChannelNumber_DTV;
    U16                         u16A2_ManualScan_ChannelNumber_CATV;
    U16                         u16A2_ManualScan_ChannelNumber_CADTV;
}L_MENU_SETUP_A_VAR;
*/
typedef struct
{
    U16                         u16B7_PCMenu_Size;
    U16                         u16B7_PCMenu_Phase;
    BOOLEAN                     BOOLEANB7_PCMenu_IsRest;
}L_MENU_VIDEO_B_VAR;

typedef struct
{
    EN_SLEEP_TIME_STATE         enD4_SleepTimer;
//	EN_AUTOSLEEP_TIME_STATE     enD4_AutoSleepTimer;
    U8                          u8Option_Info_TimeFlag;
    U16                         u16Option_Info_Year;
    U16                         u16Option_Info_Month;
    U16                         u16Option_Info_Day;
    U16                         u16Option_Info_Hour;
    U16                         u16Option_Info_Min;
    U8                          bTimer_Info_PM;
}L_MENU_TIME_D_VAR;

/*
typedef struct
{
    EN_OSD_LANGUAGE                 enE1_Language_Menu;
    EN_AUDIO_LANGUAGE               enE1_Language_Audio;
    //EN_MENU_E2_InputSource               enE2_InputSource_Video1;
    //EN_MENU_E2_InputSource               enE2_InputSource_Video2;
    //EN_MENU_E2_InputSource               enE2_InputSource_Comp1;
    //EN_MENU_E2_InputSource               enE2_InputSource_Comp2;
    //EN_MENU_E2_InputSource               enE2_InputSource_RGB;
    //EN_MENU_E2_InputSource               enE2_InputSource_HDMI1;
    //EN_MENU_E2_InputSource               enE2_InputSource_HDMI2;


}L_MENU_OPTION_E_VAR;
*/
/*
typedef struct
{
    EN_LOCK_SYSTEM                  enF1_LockSystem;

    EN_MOVIE_RATING                 enF4_MovieRating;

    EN_TV_RATING                    enF5_TVRatingChildren;
    EN_TV_RATING_AGE                enF5_TVRatingChildren_Age;
    EN_TV_RATING_FANTASY_VIOLENCE   enF5_TVRatingChildren_FantasyViolence;

    EN_TV_RATING_GENERAL            enF6_TVRatingGeneral;
    EN_TV_RATING_GENERAL_AGE        enF6_TVRatingGeneral_Age;
    EN_TV_RATING_GENERAL_DIALOGUE   enF6_TVRatingGeneral_Dialogue;
    EN_TV_RATING_GENERAL_LANGUAGE   enF6_TVRatingGeneral_Language;
    EN_TV_RATING_GENERAL_SEX        enF6_TVRatingGeneral_Sex;
    EN_TV_RATING_GENERAL_VIOLENCE   enF6_TVRatingGeneral_Violence;

}L_MENU_LOCK_F_VAR;
*/
typedef struct
{
    EN_FACTORY_ADC_ADJUST               enH1_ADC_ADJUST;
    EN_FACTORY_ADC_ADJUST_MODE          enH1_ADC_ADJUST_MODE;
    EN_FACTORY_SUB_BC_ADJUST            enH2_SUB_BC_ADJUST;
    EN_FACTORY_SUB_BC_ADJUST_MODE       enH2_SUB_BC_ADJUST_MODE;
    EN_FACTORY_WB_ADJUST                enH3_WB_ADJUST;


    EN_FACTORY_WHITE_PATTERN            enTMP_WHITE_PATTERN;
    EN_FACTORY_PEQ                      enPEQ;
//    EN_FACTORY_2HOURS_OFF     enTMP_2HOUR_OFF;
    U8 enTmp_OAD_DOWNLOAD;

    EN_FACTORY_AREA_OPTION   enTMP_AREA_OPTION;
    U8 enTMP_A2_THRESHOLD;
}L_MENU_FACTORY_ADJUST_VAR;



// ========== DESIGN MENU =============

typedef enum
{
  EN_DesAdjust_ADC_Calibration,
  EN_DesAdjust_ADC,
  EN_DesAdjust_SUB_BC,
  EN_DesAdjust_WB,
  EN_DesAdjust_WhitePattern,
  EN_DesAdjust_2Hr_Off,
  EN_DesAdjust_OAD,
  EN_DesAdjust_Num,
} EN_DESIGN_ADJUST;

typedef enum
{
    EN_DesAdj_AdcAdjust_RGB,
    EN_DesAdj_AdcAdjust_R_Gain,
    EN_DesAdj_AdcAdjust_G_Gain,
    EN_DesAdj_AdcAdjust_B_Gain,
    EN_DesAdj_AdcAdjust_R_Offset,
    EN_DesAdj_AdcAdjust_G_Offset,
    EN_DesAdj_AdcAdjust_B_Offset,
    EN_DesAdj_AdcAdjust_Num,
} EN_DESIGN_ADC_ADJUST;

typedef enum
{
    EN_DesAdj_AdcMode_RGB,
    EN_DesAdj_AdcMode_Ypbpr_SD,
    EN_DesAdj_AdcMode_Ypbpr_HD,
    EN_DesAdj_AdcMode_Ypbpr_Num,
} EN_DESIGN_ADC_ADJUST_MODE;

typedef enum
{
    EN_DesAdj_SubBcAdj_Mode,
    EN_DesAdj_SubBcAdj_Brightnes,
    EN_DesAdj_SubBcAdj_Contrast,
    EN_DesAdj_SubBcAdj_CopyAll,
    EN_DesAdj_SubBcAdj_Num,
} EN_DESIGN_SUB_BC_ADJUST;

typedef enum
{
    EN_DesAdj_SubBcAdjMode_DTV,
    EN_DesAdj_SubBcAdjMode_ATV,
    EN_DesAdj_SubBcAdjMode_AV,
    EN_DesAdj_SubBcAdjMode_COMPONENT,
    EN_DesAdj_SubBcAdjMode_RGB,
    EN_DesAdj_SubBcAdjMode_Num,
} EN_DESIGN_SUB_BC_ADJUST_MODE;

typedef enum
{
    EN_DesAdj_WB_AdjustMode,
    EN_DesAdj_WB_Temperature,
    EN_DesAdj_WB_R_Gain,
    EN_DesAdj_WB_G_Gain,
    EN_DesAdj_WB_B_Gain,
    EN_DesAdj_WB_R_Offset,
    EN_DesAdj_WB_G_Offset,
    EN_DesAdj_WB_B_Offset,
    EN_DesAdj_WB_CopyAll,
    EN_DesAdj_WB_Num,
} EN_DESIGN_WB_ADJUST;

typedef enum
{
    EN_DesAdj_WhitePattern_Off,
    EN_DesAdj_WhitePattern_White,
    EN_DesAdj_WhitePattern_Red,
    EN_DesAdj_WhitePattern_Green,
    EN_DesAdj_WhitePattern_Blue,
    EN_DesAdj_WhitePattern_Black,
    EN_DesAdj_WhitePattern_Num,
}EN_DESIGN_WHITE_PATTERN;

typedef enum
{
    EN_DesAdj_FO1_Coarse,
    EN_DesAdj_FO1_Fine,
    EN_DesAdj_FO2_Coarse,
    EN_DesAdj_FO2_Fine,
    EN_DesAdj_FO3_Coarse,
    EN_DesAdj_FO3_Fine,
    EN_DesAdj_Gain1,
    EN_DesAdj_Gain2,
    EN_DesAdj_Gain3,
    EN_DesAdj_Q1,
    EN_DesAdj_Q2,
    EN_DesAdj_Q3,
    EN_DesAdj_PEQ_Num,
}EN_DESIGN_PEQ;

typedef enum
{
    EN_DesAdj_2HourOff_Off,
    EN_DesAdj_2HourOff_On,
    EN_DesAdj_2HourOff_Num,
}EN_DESIGN_2HOURS_OFF;


typedef enum
{
    EN_DesAdj_AreaOption_USA,
    EN_DesAdj_AreaOption_CANADA,
    EN_DesAdj_AreaOption_MEXICO,
    EN_DesAdj_AreaOption_Num,
}EN_DESIGN_AREA_OPTION;

typedef struct
{
    EN_DESIGN_ADC_ADJUST               enH1_ADC_ADJUST;
    EN_DESIGN_ADC_ADJUST_MODE          enH1_ADC_ADJUST_MODE;
    EN_DESIGN_SUB_BC_ADJUST            enH2_SUB_BC_ADJUST;
    EN_DESIGN_SUB_BC_ADJUST_MODE       enH2_SUB_BC_ADJUST_MODE;
    EN_DESIGN_WB_ADJUST                enH3_WB_ADJUST;


    EN_DESIGN_WHITE_PATTERN            enTMP_WHITE_PATTERN;
    EN_DESIGN_PEQ                      enPEQ;
//    EN_DESIGN_2HOURS_OFF     enTMP_2HOUR_OFF;
    U8 enTmp_OAD_DOWNLOAD;
    U8 xvycc;
    EN_DESIGN_AREA_OPTION   enTMP_AREA_OPTION;
    U8 enTMP_A2_THRESHOLD;
}L_MENU_DESIGN_ADJUST_VAR;

// IDLE WIN ========================================
typedef enum
{
    EN_IDLE_MTS_MONO,
    EN_IDLE_MTS_STEREO,
    EN_IDLE_MTS_SAP,
    EN_IDLE_MTS_NUM,
}EN_IDLE_MTS_TYPE;

typedef struct
{
    EN_IDLE_MTS_TYPE       enIdle_MTSType;
}L_IDLE_WIN;
// END IDLE WIN ====================================

// end Variable Collection =============================================================

typedef struct
{
//    L_MENU_STATE_VAR        stMenu;
//    L_MENU_SETUP_A_VAR      stMA;
    L_MENU_VIDEO_B_VAR      stMB;
    //L_MENU_AUDIO_C_VAR      stMC;
    L_MENU_TIME_D_VAR       stMD;
//    L_MENU_OPTION_E_VAR     stME;
//    L_MENU_LOCK_F_VAR       stMF;

//    L_IDLE_WIN              stIdle;
    L_MENU_FACTORY_ADJUST_VAR    stMFactory_Adjust;
    L_MENU_DESIGN_ADJUST_VAR    stMDesign_Adjust;
}L_MENU_GENSETTING;


typedef struct
{
    U8 subtitleStringCode[3];
    EN_SUBTITLE_DEFAULT_LANGUAGE enSubtitleStringIndex;
} UIMENU_SUBTITLE_LANG;

INTERFACE L_MENU_GENSETTING stLMGenSetting;

//////////////////////////////////////////////
// From MApp_UiMenu.h

#define DIAGNOSTICS_SNR_UPDATE_DELAY       800        // in ms
#define HOT_MENU_TIME_OUT_5SEC  5000

typedef enum
{
    EN_SCREENSAVER_NULL,
    EN_SCREENSAVER_NOSIGNAL,
    EN_SCREENSAVER_NODATABASE,
    EN_SCREENSAVER_AUDIOONLY,
    EN_SCREENSAVER_BLOCKRATING,
    EN_SCREENSAVER_LOCKED_PROGRAM,
    EN_SCREENSAVER_SCRAMBLE,
    EN_SCREENSAVER_SCRAMBLED_PROGRAM,
    EN_SCREENSAVER_NO_SHOW_PROGRAM,
    EN_SCREENSAVER_NOCABLE,
    EN_SCREENSAVER_NOSYNC,
    EN_SCREENSAVER_NOSYNC_VD,
    EN_SCREENSAVER_UNSUPPORT_MODE,
    EN_SCREENSAVER_NOT_RUNNING1,
    EN_SCREENSAVER_NOT_RUNNING2,
    EN_SCREENSAVER_MHEGONLY,
    EN_SCREENSAVER_OADCHECK,
    EN_SCREENSAVER_INVALID_SERVICE,
} EN_SCREENSAVER_TYPE;

typedef enum
{
    EN_TOP,
    EN_MEDIUM,
    EN_BOTTOM,
}SubtitleBKType;

#if (MHEG5_ENABLE)
typedef enum
{
    EN_MHEG5_MONITOR,
    EN_MHEG5_RUNNING,
    EN_MHEG5_WAIT,
}EN_MONITOR_MHEG5_STATE;
#endif

INTERFACE U8 g_u8LRAudioMode;   //To use in Audio language (LR Mode)
//INTERFACE BOOLEAN g_versionNumberChange;
INTERFACE BOOLEAN UI_Hotkey_Subtitle;
INTERFACE U32 u32InfoOSD_Duration;
INTERFACE U32 u32MonitorOsdTimer;
INTERFACE U32 u32MonitorDiagnosticsSnrTimer;

#if (MHEG5_ENABLE)
INTERFACE EN_MONITOR_MHEG5_STATE enCheckMHEGLoadingStatus;
#endif


//#if (ENABLE_PIP)
INTERFACE EN_SCREENSAVER_TYPE enCurScreenSaver[2];
//#else
//INTERFACE EN_SCREENSAVER_TYPE enCurScreenSaver[1];
//#endif
#define SYS_SCREEN_SAVER_TYPE(WIN) enCurScreenSaver[WIN]


INTERFACE U8 u8SubtitleItemSelIdx;

INTERFACE BOOLEAN bExitMheg5AsScartInserted;
//////////////////////////////////////////////////////
// From MApp_UiMenuTbl.h

#define SIMPLE0_COMPLEX1_UIMODE_AUDIOFREQ_SEL  1  // 0:SIMPLE mode, 1:COMPLEX mode (audio freq appear/disappear)
#define SIMPLE0_COMPLEX1_UIMODE_5VANTENNA_SEL  0  // 0:SIMPLE mode, 1:COMPLEX mode (5vAntenna enable/disable)

#define UNUSEDFOUNCTION   0
//*******************************************
//             AUDIO FREQ SELECTION
//*******************************************
#if SIMPLE0_COMPLEX1_UIMODE_AUDIOFREQ_SEL
#define ENABLE_AUDIO_FREQ
#endif
//*******************************************
//             5V ANTENNA SELECTION
//*******************************************
#if SIMPLE0_COMPLEX1_UIMODE_5VANTENNA_SEL
#define ENABLE_5VANTENNA
#endif
//*******************************************
//             SOFTWARE UPDATE SELECTION
//*******************************************
#define ENABLE_KEEP_MUTE_ICON   1


#define ENABLE_SOFTWAREUPDATE   1

#if ENABLE_CI
#define ENABLE_CI_FUNCTION      1
#else
#define ENABLE_CI_FUNCTION      0
#endif

//////////////////////////////////////////////////////////////
// From MApp_UiMenuBlockSys.h
#define BLOCKSYS_PASSWORD_FORCE            BIT0    // When waiting entering password
#define BLOCKSYS_PASSWORD_CHANGE_OLD       BIT1    // Password is OK and unblock
#define BLOCKSYS_PASSWORD_CHANGE_NEW       BIT2    // Change password: first input password
#define BLOCKSYS_PASSWORD_CONFIRM          BIT3    // Change password: second input password
#define BLOCKSYS_PASSWORD_CONFIRM_ERROR    BIT4    // Change password confirm error
#define BLOCKSYS_SUPERPASSWORD_CHANGE_NEW  BIT5    // Change password: first input password
#define BLOCKSYS_SUPERPASSWORD_CONFIRM     BIT6    // Change password: second input password
#define BLOCKSYS_PASSWORD_ALL              0xFF
/*
typedef enum
{
    EN_F4_ParentalControl_On,
    EN_F4_ParentalControl_Num
} EN_MENU_F1_PARENTALCONTROL;
*/

#define EN_F4_ParentalControl_Off   (EN_F4_LockSystem_Min)

typedef enum
{
#if( !ENABLE_ISDBT_AND_DVB )
 #if ENABLE_SBTVD_DTV_SYSTEM
    EN_F4_LockSystem_Min=8,
 #else
    EN_F4_LockSystem_Min=3,
 #endif
#endif

#if ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
    EN_F4_LockSystem_Max=21,
#else
    EN_F4_LockSystem_Max=18,
#endif

} EN_MENU_F4_PARENTCONTROL_RATE;

#if ENABLE_ZIGGO
#define EN_F4_LockSystem_AllLock    (EN_F4_LockSystem_Max+1)
#endif

#if( ENABLE_ISDBT_AND_DVB )
extern U8 MApp_DataBase_Get_Default_LockSystem_Min(void);
#define EN_F4_LockSystem_Min (MApp_DataBase_Get_Default_LockSystem_Min())
#endif

/********************************************************************************/
/*                    Global                                                    */
/********************************************************************************/

//////////////////////////////////////////////////////////////
// From MApp_UiMenuTblColor.h


//******************************************************************************
//             COLOR SETTING START
//******************************************************************************
#define COLOR_UI_TRANSPARENT    0x000000

////////////////////////////////////////////////////////
// From MApp_UiMenuStr.h

//#define __strlen(x) MApp_UiMenu_u16Strlen((U16*) x)
//#define __strcpy(x, y) MApp_UiMenu_u16Strcpy((U16*) x, (U16*) y)
//#define __strcmp(x, y) MApp_UiMenu_u16Strcmp((U16*) x, (U16*) y)
//#define __strcat(x, y) MApp_UiMenu_u16Strcat((U16*) x, (U16*) y)
#define __MApp_UlongToString(x, y, z)   MApp_UlongToU16String(x, y, z)
//#define __MApp_UiMenuFunc_ConvertProgramNumber2Str(x, y) MApp_UiMenuFunc_ConvertProgramNumber2U16Str(x, y)
//#define __MApp_UiMenuFunc_ConvertTenKeyProgramNumber2Str(x, y) MApp_UiMenuFunc_ConvertTenKeyProgramNumber2U16Str(x, y)
//#define __MApp_ReturnResolution(x)  MApp_UiMenuFunc_ReturnResolutionU16(x)


#undef INTERFACE


#endif
