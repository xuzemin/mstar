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
// have read, understood, and agree, To be bound by below terms ("Terms") and to
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
#define MAPP_ZUI_ACTDMP_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal
#if (ENABLE_DMP)
//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MsCommon.h"

// Common Definition
#include "MApp_GlobalSettingSt.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTepg.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_GlobalFunction.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_BlockSys.h"
#include "MApp_ZUI_ACTmsgbox.h"
#include "MApp_ChannelChange.h"
#if(ENABLE_DVB)
#include "MApp_EpgTimer.h"
#include "MApp_UiPvr.h"
#endif
#include "drvUART.h"
#include "msAPI_Memory.h"
#include "msAPI_OCP.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "MApp_MassStorage.h"
#include "apiGOP.h"
#include "MsTypes.h"
#include "MApp_DMP_Main.h"
#include "MApp_ZUI_ACTdmp.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "MApp_UiMenuDef.h"
#include "mapp_videoplayer.h"
#include "MApp_Audio.h"
#include "mapp_music.h"
#if (ENABLE_WMA)
#include "mapp_wma.h"
#endif
#include "msAPI_audio.h"
#include "msAPI_Timer.h"
#include "FSUtil.h"
#include "IOUtil.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mapp_txt.h"
#include "MApp_CharTable.h"
#include "msAPI_MPEG_Subtitle.h"
#include "Panel.h"
#if ENABLE_DRM
#include "MApp_SaveData.h"
#endif
#include "ZUI_tables_h.inl"
#include "GPIO.h"

#include "mapp_photo.h"

#if ENABLE_PIP
#include "MApp_InputSource.h"
#include "MApp_ChannelChange.h"
#include "drvPQ.h"
#include "apiXC_Hdmi.h"
#include "MApp_PIP.h"
#endif
#include "msAPI_CEC.h"

#include "MApp_IR.h" // jimmy.wang

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif

#if ENABLE_KEY_TO_SPEECH
#include "MApp_KeyToSpeech.h"
#endif

//#if (ENABLE_DMP)
#include "mapp_mplayer.h"
//#endif
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC *
pComp);

#ifndef U64
typedef unsigned long long U64;
#endif

#define DMP_STRING_BUF_SIZE             256//76
#define ENABLE_GOTO_TIME          0
#define DMP_TIMER_PROGRESS_WIN          0
#define DMP_TIME_MS_PROGRESS_WIN        1000
#define DMP_TIMER_PLAY_STATUS_WIN       0
#define DMP_TIME_MS_PLAY_STATUS_WIN     5000
#define DMP_TIMER_MOVIERESUME_WIN       0
#define DMP_TIME_MS_MOVIERESUME         40000//8000
#define DMP_TIMER_RESUMESTOP_WIN        0
#define DMP_TIME_MS_RESUMESTOP_WIN      10000

#define DMP_TIMER_PREV_BUTTON_CLICK_WIN     1
#define DMP_TIME_MS_PREV_BUTTON_CLICK_WIN   1200 // 800

#define DMP_INFOBAR_ICON_NUM            17
#define DMP_TIMER_EQ_PLAY               0
#define DMP_TIME_MS_EQ_PLAY             300
#define DMP_TIMER_PREVIEW_WIN           0
#define DMP_TIME_MS_PREVIEW_WIN         500
#define DMP_TIMER_INVALID_WIN           0
#define DMP_TIME_MS_INVALID_WIN         2000
#define DMP_TIME_MS_ERROR_WIN           (DEFAULT_PHOTO_ERROR_DELAY_TIME*1000)


#define DMP_MARQUEE_INITIAL_INTERVAL_MS 1500
#define DMP_MARQUEE_ANIMATION_INTERVAL_MS 500

#if ENABLE_DRM

static stDRMinfo DrmInfo;

typedef enum
{
    WinAuthError,
    WinViewRental,
    WinRentalExpired,
    WinUnsupported,
}EN_DRM_WIN;
static EN_DRM_WIN DRM_STATUS;

typedef enum
{
    DRM_Bitmap_None,
    DRM_Bitmap_Warning,
    DRM_Bitmap_Error,
}EN_DRM_BITMAP;
static EN_DRM_BITMAP _DrmBitmapIdx = DRM_Bitmap_None;

typedef enum
{
    Title_None,
    Title_ViewRental,
    Title_AuthError,
    Title_RentalExpired,
    DRM_STR0_MAX,
}EN_DRM_STR0;
static EN_DRM_STR0 _DrmStr0Idx = Title_None;
static U8 *DRMStrTable0[DRM_STR0_MAX] =
{
    (U8 *)"",
    (U8 *)"View DivX(R) VOD Rental",
    (U8 *)"Authorization Error",
    (U8 *)"Rental Expired",
};

typedef enum
{
    ViewRental,
    AuthError,
    Unsupported,
    DRM_STR1_MAX,
}EN_DRM_STR1;
static EN_DRM_STR1 _DrmStr1Idx = ViewRental;
static U8 *DRMStrTable1[DRM_STR1_MAX]=
{
    (U8 *)"This DivX(R) rental has used X of X views.",
    (U8 *)"This player is not authorized to play this video.",
    (U8 *)"Unsupported DivX(R) DRM Version",
};

typedef enum
{
    None,
    UseRental,
    RentalExpired,
    DRM_STR2_MAX,
}EN_DRM_STR2;
static EN_DRM_STR2 _DrmStr2Idx = None;
#if (ENABLE_MPLAYER_MOVIE)
static U32 u32PrevButtonTimer = 0;
static BOOLEAN bResume=TRUE;
#endif
static U16 m_u16DRMErrorNum = 0;
#endif
U8 IsPause = 0;
extern BOOLEAN g_bUnsupportAudio;  //20100809EL
BOOL bPlayEndFlag = FALSE; //wht120818_1
typedef enum
{
    DMP_MSG_TYPE_LOADING,
    DMP_MSG_TYPE_INVALID_OPERATION,
    DMP_MSG_TYPE_BAD_DRIVE,

    DMP_MSG_TYPE_NO_SELECT_FILE,
    DMP_MSG_TYPE_NO_ENOUGH_SPACE,
    DMP_MSG_TYPE_COPY_FILE_ERROR,
    DMP_MSG_TYPE_DELETE_FILE_ERROR,
    DMP_MSG_TYPE_FORMATTING,
    DMP_MSG_TYPE_UNSUPPORTED_FORMAT,

    DMP_MSG_TYPE_NEED_TO_SELECT_DELETE_FILE,
    DMP_MSG_TYPE_NEED_TO_SELECT_COPY_FILE,
    DMP_MSG_TYPE_PRESS_RED_BUTTON_PASTE,

    DMP_MSG_TYPE_UNSUPPORTED_FILE,
    DMP_MSG_TYPE_ALL_FILES_UNSUPPORTED,
    DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE,  //20100809EL
    DMP_MSG_TYPE_UNSUPPORTED_VIDEO_RESOLUTION,
    DMP_MSG_TYPE_UNSUPPORTED_VIDEO_FRAME_RATE,
	DMP_MSG_TYPE_UNSUPPORTED_BUTTON, //add by gchen @ 20110719
    DMP_MSG_TYPE_NODEVICE, //wht120612_7
    DMP_MSG_TYPE_MAX,
}EN_DMP_MSG_TYPE;


static HWND _hwndListDriveItem[DMP_DRIVE_NUM_PER_PAGE] =
{
    HWND_DMP_DRIVE_ITEM1,
    HWND_DMP_DRIVE_ITEM2,
    HWND_DMP_DRIVE_ITEM3,
    HWND_DMP_DRIVE_ITEM4
};

static HWND _hwndListDriveItemString[DMP_DRIVE_NUM_PER_PAGE] =
{
    HWND_DMP_DRIVE_ITEM1_STRING,
    HWND_DMP_DRIVE_ITEM2_STRING,
    HWND_DMP_DRIVE_ITEM3_STRING,
    HWND_DMP_DRIVE_ITEM4_STRING
};

static HWND _hwndListFileItem[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_FILE_PAGE_THUMB_ITEM1,
    HWND_DMP_FILE_PAGE_THUMB_ITEM2,
    HWND_DMP_FILE_PAGE_THUMB_ITEM3,
    HWND_DMP_FILE_PAGE_THUMB_ITEM4,
    HWND_DMP_FILE_PAGE_THUMB_ITEM5,
    HWND_DMP_FILE_PAGE_THUMB_ITEM6,
    HWND_DMP_FILE_PAGE_THUMB_ITEM7,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM8,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM9,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM10//,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM11,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM12
};

/*static HWND _hwndListFileFocus[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_FILE_PAGE_THUMB_ITEM1_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM2_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM3_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM4_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM5_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM6_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM7_FOCUS_ICON,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM8_FOCUS_ICON,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM9_FOCUS_ICON,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM10_FOCUS_ICON,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM11_FOCUS_ICON,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM12_FOCUS_ICON
};*/

static HWND _hwndListFileIcon[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_FILE_PAGE_THUMB_ITEM1_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM2_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM3_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM4_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM5_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM6_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM7_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM8_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM9_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM10_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM11_ICON,//wht1203017_12
   // HWND_DMP_FILE_PAGE_THUMB_ITEM12_ICON
};

static HWND _hwndListFileFocusIcon[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_FILE_PAGE_THUMB_ITEM1_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM2_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM3_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM4_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM5_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM6_FOCUS_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM7_FOCUS_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM8_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM9_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM10_ICON,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM11_ICON,//wht1203017_12
   // HWND_DMP_FILE_PAGE_THUMB_ITEM12_ICON
};

static HWND _hwndListFileString[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_FILE_PAGE_THUMB_ITEM1_STRING,
    HWND_DMP_FILE_PAGE_THUMB_ITEM2_STRING,
    HWND_DMP_FILE_PAGE_THUMB_ITEM3_STRING,
    HWND_DMP_FILE_PAGE_THUMB_ITEM4_STRING,
    HWND_DMP_FILE_PAGE_THUMB_ITEM5_STRING,
    HWND_DMP_FILE_PAGE_THUMB_ITEM6_STRING,
    HWND_DMP_FILE_PAGE_THUMB_ITEM7_STRING,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM8_STRING,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM9_STRING,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM10_STRING,
   //HWND_DMP_FILE_PAGE_THUMB_ITEM11_STRING,  //wht1203017_12
   // HWND_DMP_FILE_PAGE_THUMB_ITEM12_STRING,
};
/* static HWND _hwndListFileCheckMark[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_FILE_PAGE_THUMB_ITEM1_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM2_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM3_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM4_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM5_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM6_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM7_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM8_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM9_CHECK_ICON,
    HWND_DMP_FILE_PAGE_THUMB_ITEM10_CHECK_ICON//,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM11_CHECK_ICON,
    //HWND_DMP_FILE_PAGE_THUMB_ITEM12_CHECK_ICON
}; */

static HWND _hwndListPlaylistItem[UI_DMP_PLAYLIST_NUMBER] =
{
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM1,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM2,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM3,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM4,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM5,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM6,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM7,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM8,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM9,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM10,
};

static HWND _hwndPlayListFileString[UI_DMP_PLAYLIST_NUMBER] =
{
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM1_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM2_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM3_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM4_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM5_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM6_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM7_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM8_STRING,
    HWND_DMP_PLAYBACK_PLAYLIST_ITEM9_STRING,
	HWND_DMP_PLAYBACK_PLAYLIST_ITEM10_STRING,
   // HWND_DMP_FILE_PAGE_THUMB_ITEM11_ICON,//wht1203017_12
   // HWND_DMP_FILE_PAGE_THUMB_ITEM12_ICON
};

static HWND _hwndListInfoBar[DMP_INFOBAR_ICON_NUM]=
{
    HWND_DMP_PLAYBACK_INFOBAR_ITEM1,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM2,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM3,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM4,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM5,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM6,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM7,
    HWND_DMP_PLAYBACK_INFOBAR_ITEM8,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM9,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM10,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM11,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM12,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM13,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM14,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM15,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM16,
	HWND_DMP_PLAYBACK_INFOBAR_ITEM17,
};

#if PLAYLIST_BGM
static HWND _hwndBgmListDriveItemString[DMP_DRIVE_NUM_PER_PAGE] =
{
    HWND_DMP_DRIVE_BGM_ITEM1_STRING,
    HWND_DMP_DRIVE_BGM_ITEM2_STRING,
    HWND_DMP_DRIVE_BGM_ITEM3_STRING,
    HWND_DMP_DRIVE_BGM_ITEM4_STRING
};

static HWND _hwndBgmListDriveItem[DMP_DRIVE_NUM_PER_PAGE] =
{
    HWND_DMP_DRIVE_BGM_ITEM1,
    HWND_DMP_DRIVE_BGM_ITEM2,
    HWND_DMP_DRIVE_BGM_ITEM3,
    HWND_DMP_DRIVE_BGM_ITEM4
};

static HWND _hwndBgmListFileItem[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7,
    //HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8,
    //HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9,
    //HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10,
    //HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11,
    //HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12
};

static HWND _hwndBgmListFileIcon[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12_ICON
};

static HWND _hwndBgmListFileString[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11_STRING,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12_STRING,
};

static HWND _hwndBgmListFileCheckMark[DMP_NUM_OF_FILES_PER_PAGE] =
{
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11_CHECK_ICON,
    HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12_CHECK_ICON
};
#endif

static U8 _u8InfoBarIdx;
BOOL bIsSwitchDevice = FALSE; ////wht121124_1
#if ENABLE_LAST_MEMORY
#if (ENABLE_MPLAYER_MOVIE)
static U8 _u8RecordInfoBarIdx;
#endif
#endif
/*action bitmap string*/
#define INFOBAR_ACT_IDX     0
#define INFOBAR_BMP_IDX     1
#define INFOBAR_STR_IDX     2
#define INFOBAR_BMP_IDX_FOCUS     3
static U32 DMP_MovieInfoBarTable[][4] =
{
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_PLAY_PAUSE,E_BMP_DMP_BUTTON_ICON_PAUSE,en_str_Pause,E_BMP_DMP_BUTTON_ICON_PAUSE_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_FB,E_BMP_DMP_BUTTON_ICON_FB,en_str_FB,E_BMP_DMP_BUTTON_ICON_FB_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_FF,E_BMP_DMP_BUTTON_ICON_FF,en_str_FF,E_BMP_DMP_BUTTON_ICON_FF_FOCUS},

    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV,E_BMP_DMP_BUTTON_ICON_PREV,en_str_Prev,E_BMP_DMP_BUTTON_ICON_PREV_FOCUS},

    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_NEXT,E_BMP_DMP_BUTTON_ICON_NEXT,en_str_Next,E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_STOP,E_BMP_DMP_BUTTON_ICON_STOP,en_str_Stop,E_BMP_DMP_BUTTON_ICON_STOP_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_REPEAT,E_BMP_DMP_BUTTON_ICON_REPEAT,en_str_Repeat,E_BMP_DMP_BUTTON_ICON_REPEAT_FOCUS},

    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_AB_REPEAT,E_BMP_DMP_BUTTON_ICON_AB_REPEAT,en_str_SET_A,E_BMP_DMP_BUTTON_ICON_AB_REPEAT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_PLAYLIST,E_BMP_DMP_BUTTON_ICON_PLAY_LIST,en_str_Playlist,E_BMP_DMP_BUTTON_ICON_PLAY_LIST_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO,E_BMP_DMP_BUTTON_ICON_INFO,en_str_Info,E_BMP_DMP_BUTTON_ICON_INFO_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_SF,E_BMP_DMP_BUTTON_ICON_SF,en_str_Slow_Forward,E_BMP_DMP_BUTTON_ICON_SF_FOCUS},
	{EN_EXE_DMP_PLAYBACK_MOVIEINFO_SD,E_BMP_DMP_BUTTON_ICON_SD,en_str_Step_Forward,E_BMP_DMP_BUTTON_ICON_SD_FOCUS},
    //{EN_EXE_DMP_PLAYBACK_MOVIEINFO_GOTO_TIME,E_BMP_DMP_BUTTON_ICON_TIME,en_str_Goto_Time},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMIN,E_BMP_DMP_BUTTON_ICON_ZOOMOUT,en_str_Zoom_In,E_BMP_DMP_BUTTON_ICON_ZOOMOUT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMOUT,E_BMP_DMP_BUTTON_ICON_ZOOMIN,en_str_Zoom_Out,E_BMP_DMP_BUTTON_ICON_ZOOMIN_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_ASPECT_RATIO, E_BMP_DMP_BUTTON_ICON_FUNCTION, en_str_Aspect_Ratio,E_BMP_DMP_BUTTON_ICON_FUNCTION_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_MOVEVIEW, E_BMP_DMP_MOVE_VIEW, en_str_Move_View,E_BMP_DMP_MOVE_VIEW_FOCUS},
	{EN_EXE_DMP_PLAYBACK_MOVIEINFO_SOUND_CH, E_BMP_DMP_BUTTON_ICON_BGM, en_str_DMP_MovieInfoSoundCH,E_BMP_DMP_BUTTON_ICON_BGM_FOCUS}, //smc.chy 2010/06/04
#if (ENABLE_MPLAYER_CAPTURE_MOVIE == 1)
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_CAPTURE,E_BMP_DMP_BUTTON_ICON_CAPTURE,en_str_Capture},
#endif
#if (ENABLE_DIVX_PLUS == 1)
    {EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX,E_BMP_MAINMENU_IMG_CHANNEL_FOCUS,en_str_Divx_Setting},
#endif
};

typedef enum
{
    MOVIEINFO_PLAY_PAUSE,
    MOVIEINFO_FB,
    MOVIEINFO_FF,
    MOVIEINFO_PREV,
    MOVIEINFO_NEXT,
    MOVIEINFO_STOP,
    MOVIEINFO_REPEAT,
    MOVIEINFO_AB_REPEAT,
    MOVIEINFO_PLAYLIST,
    MOVIEINFO_INFO,
    MOVIEINFO_SF,
    MOVIEINFO_STEP_DISPLAY,
#if ENABLE_GOTO_TIME
    MOVIEINFO_GOTO_TIME,
#endif
    MOVIEINFO_ZOOMIN,
    MOVIEINFO_ZOOMOUT,
    MOVIEINFO_RATIO,
    MOVIEINFO_MOVEVIEW,
#if (ENABLE_MPLAYER_CAPTURE_MOVIE == 1)
    MOVIEINFO_CAPTURE,
#endif
#if (ENABLE_DIVX_PLUS == 1)
    MOVIEINFO_DIVX,
#endif
} MOVIEINFO_ORDER;

#if ENABLE_GOTO_TIME
static U8 u8MovieInfoBarMax = 18;
#else
static U8 u8MovieInfoBarMax = 17;
#endif

#if (ENABLE_MPLAYER_CAPTURE_LOGO== 1)
static const U8 u8PhotoInfoBarMax = 14;
#else
static const U8 u8PhotoInfoBarMax = 13;
#endif

/*action bitmapWnd stringWnd*/

static U32 DMP_PhotoInfoBarTable[][4] =
{
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_PLAY_PAUSE,E_BMP_DMP_BUTTON_ICON_PAUSE,en_str_Pause,E_BMP_DMP_BUTTON_ICON_PAUSE_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_PREV,E_BMP_DMP_BUTTON_ICON_PREV,en_str_Prev,E_BMP_DMP_BUTTON_ICON_PREV_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_NEXT,E_BMP_DMP_BUTTON_ICON_NEXT,en_str_Next,E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_STOP,E_BMP_DMP_BUTTON_ICON_STOP,en_str_Stop,E_BMP_DMP_BUTTON_ICON_STOP_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_REPEAT,E_BMP_DMP_BUTTON_ICON_REPEAT,en_str_Repeat,E_BMP_DMP_BUTTON_ICON_REPEAT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_MUSIC,E_BMP_DMP_BUTTON_ICON_BGM,en_str_Music,E_BMP_DMP_BUTTON_ICON_BGM_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_PLAYLIST,E_BMP_DMP_BUTTON_ICON_PLAY_LIST,en_str_Playlist,E_BMP_DMP_BUTTON_ICON_PLAY_LIST_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_INFO,E_BMP_DMP_BUTTON_ICON_INFO,en_str_Info,E_BMP_DMP_BUTTON_ICON_INFO_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_CLOCKWISE,E_BMP_DMP_BUTTON_ICON_ROTATE_CLOCK,en_str_Rotate,E_BMP_DMP_BUTTON_ICON_ROTATE_CLOCK_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_COUNTERCLOCKWISE,E_BMP_DMP_BUTTON_ICON_ROTATE_ANTICLOCK,en_str_Rotate,E_BMP_DMP_BUTTON_ICON_ROTATE_ANTICLOCK_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMIN,E_BMP_DMP_BUTTON_ICON_ZOOMOUT,en_str_Zoom_In,E_BMP_DMP_BUTTON_ICON_ZOOMOUT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMOUT,E_BMP_DMP_BUTTON_ICON_ZOOMIN,en_str_Zoom_Out,E_BMP_DMP_BUTTON_ICON_ZOOMIN_FOCUS},
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_MOVEVIEW, E_BMP_DMP_MOVE_VIEW, en_str_Move_View,E_BMP_DMP_MOVE_VIEW_FOCUS},
#if (ENABLE_MPLAYER_CAPTURE_LOGO == 1)
    {EN_EXE_DMP_PLAYBACK_PHOTOINFO_CAPTURE,E_BMP_DMP_BUTTON_ICON_CAPTURE,en_str_Capture},
#endif
};

typedef enum
{
    PHOTOINFO_PLAY_PAUSE,
    PHOTOINFO_PREV,
    PHOTOINFO_NEXT,
    PHOTOINFO_STOP,
    PHOTOINFO_REPEAT,
    PHOTOINFO_MUSIC,
    PHOTOINFO_PLAYLIST,
    PHOTOINFO_INFO,
    PHOTOINFO_CLOCKWISE,
    PHOTOINFO_COUNTERCLOCKWISE,
    PHOTOINFO_ZOOMIN,
    PHOTOINFO_ZOOMOUT,
    PHOTOINFO_MOVEVIEW,
#if (ENABLE_MPLAYER_CAPTURE_LOGO== 1)
    PHOTOINFO_CAPTURE,
#endif
} PHOTOINFO_ORDER;

static BOOL bNoDevice = FALSE;
/*action bitmapWnd stringWnd*/

static U32 DMP_MusicInfoBarTable[][4] =
{
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAY_PAUSE,E_BMP_DMP_BUTTON_ICON_PAUSE,en_str_Pause,E_BMP_DMP_BUTTON_ICON_PAUSE_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_FB,E_BMP_DMP_BUTTON_ICON_FB,en_str_FB,E_BMP_DMP_BUTTON_ICON_FB_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_FF,E_BMP_DMP_BUTTON_ICON_FF,en_str_FF,E_BMP_DMP_BUTTON_ICON_FF_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_PREV,E_BMP_DMP_BUTTON_ICON_PREV,en_str_Prev,E_BMP_DMP_BUTTON_ICON_PREV_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_NEXT,E_BMP_DMP_BUTTON_ICON_NEXT,en_str_Next,E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_STOP,E_BMP_DMP_BUTTON_ICON_STOP,en_str_Stop,E_BMP_DMP_BUTTON_ICON_STOP_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_REPEAT,E_BMP_DMP_BUTTON_ICON_REPEAT,en_str_Repeat,E_BMP_DMP_BUTTON_ICON_REPEAT_FOCUS},
    //{EN_EXE_DMP_PLAYBACK_MUSICINFO_AB_REPEAT,E_BMP_DMP_BUTTON_ICON_AB_REPEAT,en_str_SET_A,E_BMP_DMP_BUTTON_ICON_AB_REPEAT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_MUTE,E_BMP_DMP_BUTTON_ICON_MUTE,en_str_MUTE,E_BMP_DMP_BUTTON_ICON_MUTE_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAYLIST,E_BMP_DMP_BUTTON_ICON_PLAY_LIST,en_str_Playlist,E_BMP_DMP_BUTTON_ICON_PLAY_LIST_FOCUS},
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_INFO,E_BMP_DMP_BUTTON_ICON_INFO,en_str_Info,E_BMP_DMP_BUTTON_ICON_INFO_FOCUS},
#if (ENABLE_MPLAYER_CAPTURE_MUSIC == 1)
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_CAPTURE,E_BMP_DMP_BUTTON_ICON_CAPTURE,en_str_Capture,E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS},
#endif
#if ENABLE_GOTO_TIME
    {EN_EXE_DMP_PLAYBACK_MUSICINFO_GOTO_TIME,E_BMP_DMP_BUTTON_ICON_TIME,en_str_Goto_Time,E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS}
#endif
};

typedef enum
{
    MUSICINFO_PLAY_PAUSE,
    MUSICINFO_FB,
    MUSICINFO_FF,
    MUSICINFO_PREV,
    MUSICINFO_NEXT,
    MUSICINFO_STOP,
    MUSICINFO_REPEAT,
    //MUSICINFO_AB_REPEAT,
    MUSICINFO_MUTE,
    MUSICINFO_PLAYLIST,
    MUSICINFO_INFO,
#if (ENABLE_MPLAYER_CAPTURE_MUSIC== 1)
    MUSICINFO_CAPTURE,
#endif
#if ENABLE_GOTO_TIME
    MUSICINFO_GOTO_TIME,
#endif
} MUSICINFO_ORDER;


static const U8 u8MusicInfoBarMax = 10;

/*action bitmapWnd stringWnd*/
#if (ENABLE_MPLAYER_TEXT)
static U32 DMP_TextInfoBarTable[][4] =
{
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_PREV,E_BMP_DMP_BUTTON_ICON_FB,en_str_Prev_Page,E_BMP_DMP_BUTTON_ICON_FB_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXT,E_BMP_DMP_BUTTON_ICON_FF,en_str_Next_Page,E_BMP_DMP_BUTTON_ICON_FF_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_PREVFILE,E_BMP_DMP_BUTTON_ICON_PREV,en_str_Prev,E_BMP_DMP_BUTTON_ICON_PREV_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXTFILE,E_BMP_DMP_BUTTON_ICON_NEXT,en_str_Next,E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_STOP,E_BMP_DMP_BUTTON_ICON_STOP,en_str_Stop,E_BMP_DMP_BUTTON_ICON_STOP_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_MUSIC,E_BMP_DMP_BUTTON_ICON_BGM,en_str_Music,E_BMP_DMP_BUTTON_ICON_BGM_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_PLAYLIST,E_BMP_DMP_BUTTON_ICON_PLAY_LIST,en_str_Playlist,E_BMP_DMP_BUTTON_ICON_PLAY_LIST_FOCUS},
    {EN_EXE_DMP_PLAYBACK_TEXTINFO_INFO,E_BMP_DMP_BUTTON_ICON_INFO,en_str_Info,E_BMP_DMP_BUTTON_ICON_INFO_FOCUS},
};
#endif
typedef enum
{
    TEXTINFO_PREV,
    TEXTINFO_NEXT,
    TEXTINFO_PREVFILE,
    TEXTINFO_NEXTFILE,
    TEXTINFO_STOP,
#if (ENABLE_BGM) && (DIRECTORY_BGM)
    TEXTINFO_MUSIC,
#endif
    TEXTINFO_PLAYLIST,
    TEXTINFO_INFO,
    TEXTINFO_NUM,
} TEXTINFO_ORDER;

static const U8 u8TextInfoBarMax = 8;

typedef enum
{
    PLAY_MODE_ICON_NEXT,
    PLAY_MODE_ICON_PREVIOUS,
    PLAY_MODE_ICON_STOP,
    PLAY_MODE_ICON_PLAY,
    PLAY_MODE_ICON_PAUSE,
    PLAY_MODE_ICON_AB_REPEAT,
    PLAY_MODE_ICON_SETA,
    PLAY_MODE_ICON_AB_LOOP,
    PLAY_MODE_ICON_FF2X,
    PLAY_MODE_ICON_FF4X,
    PLAY_MODE_ICON_FF8X,
    PLAY_MODE_ICON_FF16X,
    PLAY_MODE_ICON_FF32X,
    PLAY_MODE_ICON_FB2X,
    PLAY_MODE_ICON_FB4X,
    PLAY_MODE_ICON_FB8X,
    PLAY_MODE_ICON_FB16X,
    PLAY_MODE_ICON_FB32X,
    PLAY_MODE_ICON_SF2X,
    PLAY_MODE_ICON_SF4X,
    PLAY_MODE_ICON_SF8X,
    PLAY_MODE_ICON_SF16X,
    PLAY_MODE_ICON_SD,
    PLAY_MODE_ICON_FB_INVALID,
    PLAY_MODE_ICON_FF_INVALID,
    PLAY_MODE_ICON_RATIO_Panorama,
    PLAY_MODE_ICON_RATIO_Original,
    PLAY_MODE_ICON_RATIO_4X3,
    PLAY_MODE_ICON_RATIO_16X9,
    PLAY_MODE_ICON_RATION_ZOOM1,
    PLAY_MODE_ICON_RATION_ZOOM2,
    PLAY_MODE_ICON_RATION_JUSTSCAN,
	
	//>>wht120613_4
    PLAY_MODE_ICON_SOUND_LL,
    PLAY_MODE_ICON_SOUND_LR,
    PLAY_MODE_ICON_SOUND_RR,
	//<<wht120613_4
	PLAY_MODE_ICON_BGMUSIC_MODE,//wht120514_1
	
    PLAY_MODE_ICON_ZOOM_1DIV4,
    PLAY_MODE_ICON_ZOOM_1DIV2,
    PLAY_MODE_ICON_ZOOM_1,
    PLAY_MODE_ICON_ZOOM_2,
    PLAY_MODE_ICON_ZOOM_4,
    PLAY_MODE_ICON_ZOOM_8,
    PLAY_MODE_ICON_ZOOM_IN_MODE,
    PLAY_MODE_ICON_ZOOM_OUT_MODE,
    PLAY_MODE_ICON_SLIDESHOW_NORMAL,
    PLAY_MODE_ICON_SLIDESHOW_RANDOM,
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
    PLAY_MODE_ICON_SLIDESHOW_BLOCKS,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
    PLAY_MODE_ICON_SLIDESHOW_DIAGONALBLOCKS,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
    PLAY_MODE_ICON_SLIDESHOW_WIPE,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
    PLAY_MODE_ICON_SLIDESHOW_SLIDE,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
    PLAY_MODE_ICON_SLIDESHOW_FADE,
#endif
    PLAY_MODE_ICON_CHANGE_AUDIOTRACK,
    PLAY_MODE_ICON_CHANGE_SUBTITLETRACK,
    PLAY_MODE_ICON_REPEAT_1,
    PLAY_MODE_ICON_REPEAT_NONE,
    PLAY_MODE_ICON_REPEAT_ALL,
	PLAY_MODE_ICON_ASPECT_MODE,
    PLAY_MODE_ICON_MAX,
}EN_DMP_PLAY_ICON_TYPE;

typedef struct
{
    //BOOLEAN     bFuncAdv;
    BOOLEAN     bSubtitleOff;   //is subtitle OFF mode
    U8          MPlayerSubtitleBuf[DMP_STRING_BUF_SIZE];
    U32         au32MovieRepeatTime[2]; //Repeat A->B
} ST_MOVIE_INFO;

typedef struct
{
    U8          MPlayerLyricBuf[DMP_STRING_BUF_SIZE];
    U32         au32MusicRepeatTime[2]; //Repeat A->B
} ST_MUSIC_INFO;

typedef struct
{
    ST_MOVIE_INFO   stMovieInfo;
    ST_MUSIC_INFO   stMusicInfo;
} ST_DMP_PLAYBACK_VAR;

typedef enum
{
    REPEATAB_MODE_NONE,
    REPEATAB_MODE_A,
    REPEATAB_MODE_AB,
    REPEATAB_MODE_MAX,
}EN_DMP_REPEATAB_STATUS;

typedef enum
{
    UART_NONE,
    UART_HK,
    UART_VDEC,
    UART_AEON,
    UART_NUM,
}EN_DMP_UART_MODE;

/////////////////////////////////////
//      Local Variables
/////////////////////////////////////
static EN_DMP_MSG_TYPE _enDmpMsgType = DMP_MSG_TYPE_MAX;
//static MPlayerFileInfo _stCopyFileInfo;
static EN_DMP_PLAY_ICON_TYPE _enDmpPlayIconType = PLAY_MODE_ICON_MAX;
static EN_DMP_PLAY_ICON_TYPE _enDmpPlayStrType = PLAY_MODE_ICON_MAX;
static U32 _u32MusicCurrentTime;
static U16 _u16MusicCurrentTime;
static enumMPlayerNotifyType _enNotify = E_MPLAYER_NOTIFY_NUM;
#if (ENABLE_MPLAYER_MOVIE)
static enumMPlayerMoviePlayMode _enPlayMode_AtNotify;
static U16 _u16MovieCurrentTime = 0;
static U16 _u16MovieTotalTime = 0;
#if DMP_UI_BMPSUBTITLE_EXCLUSIVE
/* This flag is used to prevent the E_MPLAYER_NOTIFY_HIDE_SUBTITLE interrupt,
the interrupt will close gwin, hence the ui cant be showed;
*/
static BOOLEAN bUIexist = FALSE;
#endif
#endif
static EN_DMP_REPEATAB_STATUS _enRepeatABStatus;
static U8 _u8Hour = 0, _u8Minute = 0, _u8Second = 0;
static U16 m_u16PlayErrorNum = 0;
static U16 m_u16BGMErrorNum = 0;

static EN_DMP_UART_MODE _u8UARTMode;
static HWND hwnd_before;

#if((MEMORY_MAP == MMAP_128MB) && (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA))
#define ENABLE_PHOTO_INFO_OK 0
#else
#define ENABLE_PHOTO_INFO_OK 1
#endif

#if(ENABLE_PHOTO_INFO_OK)
static BOOLEAN _bPhotoInfoOK = FALSE;
#endif

#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
BOOLEAN bIsDriveSelected = FALSE;
#endif

typedef enum
{
    DMP_USB_NODISK,
    DMP_USB_DISK1,
    DMP_USB_DISK2,
} EN_DMP_USB_DISK;

#if 1//(MS_BOARD_TYPE_SEL == BD_MST006B_10AVS_10315)
EN_DMP_USB_DISK                    u8UsbDeviceSel = DMP_USB_DISK2;
#else
EN_DMP_USB_DISK                    u8UsbDeviceSel = DMP_USB_DISK1;  
#endif
U8                    u8UsbDeviceSwitchStatus = DMP_USB_NODISK;
static U8 u8InfobarIdxTemp=0;
#if (ENABLE_DIVX_PLUS == 1)
typedef enum
{
    DIVX_MENU,
    DIVX_SET_TITLE,
    DIVX_SET_EDITION,
    DIVX_SET_CHAPTER,
    DIVX_SET_AUTOCHAPTER,
    DIVX_MAX,
}EN_DMP_DIVX_STATUS;


static U16 _u16DivxTitleIdx = 0;
static U16 _u16DivxEditionIdx = 0;
static U16 _u16DivxChpIdx = 0;
static U8 _u8DivxAutoChpIdx = 0;
static EN_DMP_DIVX_STATUS _enDmpDivxStatus;
#endif

typedef enum
{
    PHOTOINFO_SLIDESHOW_RANDOM,
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
    PHOTOINFO_SLIDESHOW_BLOCKS_RANDOM,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
    PHOTOINFO_SLIDESHOW_DIAGONAL_BLOCKS_RANDOM,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
    PHOTOINFO_SLIDESHOW_WIPE_RANDOM,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
    PHOTOINFO_SLIDESHOW_SLIDE_RANDOM,
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
    PHOTOINFO_SLIDESHOW_FADE_RANDOM,
#endif
    PHOTOINFO_SLIDESHOW_NORMAL,
    PHOTOINFO_SLIDESHOW_NUM,
} EN_PHOTOINFO_SLIDESHOW;

#if ENABLE_MPLAYER_RECORD_DIR_ENTRY
static U16 _u16FileIdxByDir[NUM_OF_MAX_DIRECTORY_DEPTH];
#if PLAYLIST_BGM
static U16 m_u8PhotoDrive=0;
static U16 m_u16PhotoIdxByDir[NUM_OF_MAX_DIRECTORY_DEPTH]={0};
static U16 m_u16PhotoDepth=0;
static U16 m_u16PhotoIdx=0;
static enumMPlayerPlayMode ePhotoPlayMode=E_MPLAYER_PLAY_ONE;
#if ENABLE_MPLAYER_SORT_EX
static enumMPlayerFileSortMode ePhotoSortMode=E_MPLAYER_SORT_NONE;
static enumMPlayerFileSortSubMode ePhotoOrderMode=E_MPLAYER_SORT_INCREMENT_ORDER;
#endif
static U16 m_u8BgmDrive=0;
static U16 m_u16BgmIdxByDir[NUM_OF_MAX_DIRECTORY_DEPTH]={0};
static U16 m_u16BgmDepth=0;
static U16 m_u16BgmIdx=0;
static enumMPlayerPlayMode eBgmPlayMode=E_MPLAYER_PLAY_ONE;
#if ENABLE_MPLAYER_SORT_EX
static enumMPlayerFileSortMode eBgmSortMode=E_MPLAYER_SORT_NONE;
static enumMPlayerFileSortSubMode eBgmOrderMode=E_MPLAYER_SORT_INCREMENT_ORDER;
#endif
static BOOLEAN m_bBGMOn = FALSE;
#endif
#endif
static ST_DMP_PLAYBACK_VAR  _stDmpPlayVar;

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);
#if ENABLE_DMP_MINI_MENU
extern void _MApp_ZUI_ACT_InvalidateMiniPlaybackPageTime(void);
#endif

#if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
static U16 _ThumbNOIdx = 0xFFFF;
static U16 _ThumbOKIdx = 0xFFFF;
static U8 _CopyFbId = 0xFF;
static BOOLEAN _InsertQFlag = TRUE;
static BOOLEAN _ThumbLoadPageFlag = TRUE;
static U8 _ThumbInsertNum = 0;
#endif

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
static BOOLEAN m_bCopyOn = FALSE;
#endif
#if (ENABLE_DELETE_SELECTED_FILES || ENABLE_COPY_SELECTED_FILES)
static U16 _u16CopyDeleteSelectNum = 0;
static U16 _u16CopyDeleteFinishNum = 0;
#endif

static void _MApp_ZUI_ACT_DmpRefreshPlayList(void);

#if ENABLE_BGM
static BOOLEAN _MApp_DMP_PlayBGM(void)
{
    BOOLEAN bRet = FALSE;

    if( E_MPLAYER_RET_OK == MApp_MPlayer_PlayMusic())
    {
        MApp_DMP_SetDmpFlag(DMP_FLAG_BGM_MODE);
        m_u16BGMErrorNum = 0;
        MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MUSIC, 0);
        bRet = TRUE;
    }

    return bRet;
}
#endif

#if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
static void _MApp_DMP_ThumbCopyRegion_ClearFB(void)
{
    if(_CopyFbId == 0xFF)
    {
        return;
    }
    else
    {
        GOP_GwinFBAttr fbAttr;
        MApi_GOP_GWIN_GetFBInfo(_CopyFbId, &fbAttr);
        MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0x0);
    }
}

static void _MApp_DMP_ThumbCopyRegion_Create(void)
{
    GOP_GwinFBAttr fbAttr;
    GRAPHIC_DC *dc = MApp_ZUI_API_GetScreenDC();
    if(_CopyFbId != 0xFF)
    {
        MApi_GOP_GWIN_DeleteFB(_CopyFbId);
    }
    MApi_GOP_GWIN_GetFBInfo(dc->u8FbID, &fbAttr);
    _CopyFbId = MApi_GOP_GWIN_GetFreeFBID();

#if defined(MAD_THUMBNAIL_FB_BUF_LEN) && (MAD_THUMBNAIL_FB_BUF_LEN!=0) //co-buffer to fix photo display
    if(!MApi_GOP_GWIN_CreateFBbyStaticAddr(_CopyFbId, ZUI_DMP_XSTART, ZUI_DMP_YSTART, ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT,  fbAttr.fbFmt, ((MAD_THUMBNAIL_FB_BUF_MEMORY_TYPE&MIU1)?MAD_THUMBNAIL_FB_BUF_ADR|MIU_INTERVAL:MAD_THUMBNAIL_FB_BUF_ADR) ))
#else
    if( !MApi_GOP_GWIN_CreateFB2(_CopyFbId, ZUI_DMP_XSTART, ZUI_DMP_YSTART,
                                    ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT, fbAttr.fbFmt))
#endif
    {
        MS_DEBUG_MSG(printf("\n _MApp_MediaPlayer_ThumbCopyRegion Fail to create buffer %u.\n",_CopyFbId));
        _CopyFbId = 0xFF;
        return;
    }
    _MApp_DMP_ThumbCopyRegion_ClearFB();
}

static void _MApp_DMP_ThumbCopyRegion_Destroy(void)
{
    if(_CopyFbId == 0xFF)
    {
        return;
    }
    MApi_GOP_GWIN_DeleteFB(_CopyFbId);
    _CopyFbId = 0xFF;
}

static void _MApp_DMP_ThumbCopyRegion_CloneRect(U8 fbId, RECT *rect)
{
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;
    if(_CopyFbId == 0xFF)
    {
        return;
    }
    //printf("[Clone Region] (%d, %d) w = %d, h = %d\n", rect->left, rect->top, rect->width, rect->height);
    msAPI_OSD_SetClipWindow(
    rect->left, rect->top,
    rect->left+rect->width-1,
    rect->top+rect->height-1);
    //Backup n thumbnail region
    PasteFB.fbID=_CopyFbId;
    PasteFB.x=rect->left;
    PasteFB.y=rect->top;
    PasteFB.width=rect->width;
    PasteFB.height=rect->height;
    CopyFB.fbID=fbId;
    CopyFB.x=rect->left;
    CopyFB.y=rect->top;
    CopyFB.width=rect->width;
    CopyFB.height=rect->height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
}

static void _MApp_DMP_ThumbCopyRegion_PasteTo(RECT *rect)
{
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;
    GRAPHIC_DC *dc = MApp_ZUI_API_GetBufferDC();
    if(_CopyFbId == 0xFF)
    {
        return;
    }
    //printf("[Paste Region] (%d, %d) w = %d, h = %d\n", rect->left, rect->top, rect->width, rect->height);
    msAPI_OSD_SetClipWindow(
    rect->left, rect->top,
    rect->left+rect->width-1,
    rect->top+rect->height-1);
    PasteFB.fbID=dc->u8FbID;
    PasteFB.x=rect->left;
    PasteFB.y=rect->top;
    PasteFB.width=rect->width;
    PasteFB.height=rect->height;
    CopyFB.fbID=_CopyFbId;
    CopyFB.x=rect->left;
    CopyFB.y=rect->top;
    CopyFB.width=rect->width;
    CopyFB.height=rect->height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
}

static void _MApp_DMP_Thumbnail_ChangePage(void)
{
    MApp_MPlayer_StopThumbnail();
    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
    _ThumbNOIdx = 0xFFFF;
    _ThumbOKIdx = 0xFFFF;
    _ThumbLoadPageFlag = TRUE;
    _ThumbInsertNum = 0;
    _MApp_DMP_ThumbCopyRegion_ClearFB();
}
#endif

U8 MApp_ZUI_ACT_GetCopyFbId(void)
{
    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
        return _CopyFbId;
    #else
        return 0;
    #endif

}


#if DMP_UI_BMPSUBTITLE_EXCLUSIVE
static void _MApp_ZUI_ACTdmp_RestoreGWINandFB(void)
{
    DMP_DBG(printf("_MApp_ZUI_ACTdmp_RestoreGWINandFB FALSE\n"));
#if (ENABLE_MPLAYER_MOVIE)
    msAPI_MpegSP_SetShowStatus(FALSE);
#endif
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
    MApp_TS_Subtitle_SetShowStatus(FALSE);
#endif
    {
        U8 u8GWinId = MApp_ZUI_API_QueryGWinID();
        if(u8GWinId == 0xFF)
        {
            //DMP_DBG(printf("close subtitle 5\n"););
            MApp_DMP_BW_Control(TRUE);
            //Reinit MM OSD
            {
                RECT rect;
                RECT_SET(rect,
                    ZUI_DMP_XSTART, ZUI_DMP_YSTART,
                    ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT);
                if (!MApp_ZUI_API_InitGDI(&rect))
                {
                    DMP_DBG(printf("[ZUI]GDI RE-INIT Failed 5!\n"));
                    //ABORT();
                    //return FALSE;
                }
                DMP_DBG(printf("MApp_ZUI_API_InitGDI 8\n"););
            }
        }
        u8GWinId = MApp_ZUI_API_QueryGWinID();
        if(!MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
        {
            DMP_DBG(printf("MApi_GOP_GWIN_Enable here %u\n",u8GWinId));
            MApi_GOP_GWIN_Enable(u8GWinId, TRUE);
        }
    }
}
#endif

#if (ENABLE_MPLAYER_MOVIE)
static void _MApp_ZUI_ACTdmp_OperateSubtitle(void)
{
    if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
    {
        if(_stDmpPlayVar.stMovieInfo.bSubtitleOff)
        {
#if (ENABLE_SUBTITLE_DMP)
            MApp_MPlayer_DisableSubtitle();
#endif
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE ,SW_HIDE);
            return;
        }
        else
        {
#if (ENABLE_SUBTITLE_DMP)
            MApp_MPlayer_EnableSubtitle();

            if (MApp_MPlayer_IsCurSubtitleText())
            {
                // Text subtitle needs to show ZUI subtitle window
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE ,SW_SHOW);
            }
            else
            {
                // Image subtitle displays by other gwin, so I hide ZUI subtitle window
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE ,SW_HIDE);
            }
#endif
        }

        {
            // check UI
            U8 u8GWinId = MApp_ZUI_API_QueryGWinID();
            if (u8GWinId == 0xFF)
            {
               return;
            }
            if(! MApi_GOP_GWIN_IsGWINEnabled(u8GWinId)) // UI doesnt exist
            {
                DMP_DBG(printf("_MApp_ZUI_ACTdmp_OperateSubtitle TRUE\n"));
#if (ENABLE_SUBTITLE_DMP)
                msAPI_MpegSP_SetShowStatus(TRUE);
#endif
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                MApp_TS_Subtitle_SetShowStatus(TRUE);
#endif
            }
            else // UI exist
            {
                if( // UI can not be seen
                    //!MApp_DMP_IsSuccessorWinVisible(HWND_DMP_BG_GRADIENT_TOP) &&
                    //!MApp_DMP_IsSuccessorWinVisible(HWND_DMP_BG_GRADIENT_BOTTOM) &&
                    //!MApp_DMP_IsSuccessorWinVisible(HWND_DMP_SEL_BAR_GROUP) &&
					!MApp_DMP_IsSuccessorWinVisible(HWND_DMP_MENU_BG) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_MEDIA_TYPE_PAGE) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_DRIVE_PAGE) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_FILE_SELECT_PAGE) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PLAYBACK_PAGE) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_ALERT_WINDOW) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_VOLUME_LIST) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_RESUME_STOP_WINDOW) &&
                    !MApp_DMP_IsSuccessorWinVisible(HWND_DMP_DRM_WINDOW)
                   )
                {
                    //if(MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
                    {
                        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                        MApi_GOP_GWIN_Enable(u8GWinId, FALSE);
                        #endif
                        MApp_DMP_BW_Control(FALSE);
                        DMP_DBG(printf("MApp_ZUI_API_TerminateGDI actdmp %u\n",u8GWinId););
                        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                        MApp_ZUI_API_EmptyMessageQueue();
                        MApp_ZUI_API_TerminateGDI();
                        DMP_DBG(printf("draw subtitle TRUE1\n"););
                        msAPI_MpegSP_SetShowStatus(TRUE);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                        MApp_TS_Subtitle_SetShowStatus(TRUE);
#endif
                        #endif
                    }
                }
                else // UI can be seen
                {
                    DMP_DBG(printf("close subtitle 2 FALSE\n"););
                    #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                    msAPI_MpegSP_SetShowStatus(FALSE);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                    MApp_TS_Subtitle_SetShowStatus(FALSE);
#endif
                    #endif
                }
            }
        }
    }
}
#endif

#if ENABLE_ZOOM_MAP

#if ((GE_FRAMEBUFFER_LEN >= ((ZUI_ALIGNED_VALUE(UI_OSD_PANE_W,8)*UI_OSD_PANE_H*2L)*2) + (((ZUI_ALIGNED_VALUE(UI_OSD_PANE_W,8)*UI_OSD_PANE_H*2L)/ZOOM_MAP_FACTOR)/ZOOM_MAP_FACTOR)) && (E_GOP_OSD != E_GOP_APP))
static U8 u8ZooMapWinId= 0xff;
#endif
#define THICKNESS 2
static void _MApp_ZUI_ACT_DrawZoomMap(BOOLEAN bCreatGwin, U16 startX, U16 startY, U8 factor)
{
#if ((GE_FRAMEBUFFER_LEN >= ((ZUI_ALIGNED_VALUE(UI_OSD_PANE_W,8)*UI_OSD_PANE_H*2L)*2) + (((ZUI_ALIGNED_VALUE(UI_OSD_PANE_W,8)*UI_OSD_PANE_H*2L)/ZOOM_MAP_FACTOR)/ZOOM_MAP_FACTOR)) && (E_GOP_OSD != E_GOP_APP))

    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_ZOOMMAP_GROUP, SW_HIDE);

    //***0. Get ZoomMap Info***//
    ST_ZOOM_MAP_INFO ZoomMapInfo;

    memset(&ZoomMapInfo, 0, sizeof(ZoomMapInfo));
    MApp_Photo_GetZoomMapInfo(&ZoomMapInfo);


    //***1. Calculate Screen, Image, Capture***//
    RECT Screen, Image, Capture;

    Screen.width = (((ZoomMapInfo.ScreenWidth*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor);
    Screen.height = (((ZoomMapInfo.ScreenHeight*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor);

    S16 ScreenAlignShiftX;
    ScreenAlignShiftX = ((GE_ALIGNED_VALUE(Screen.width, 8) - Screen.width)/2)+1;

    Image.left = (((ZoomMapInfo.ImageX*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor)+ScreenAlignShiftX;
    Image.top = (((ZoomMapInfo.ImageY*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor);
    Image.width = (((ZoomMapInfo.ImageWidth*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor);
    Image.height = (((ZoomMapInfo.ImageHeight*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor);

    Capture.height = (((ZoomMapInfo.CaptureHeight*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor);
    if(ZoomMapInfo.ImageY == ZoomMapInfo.CaptureY)
    {
        Capture.top = Image.top;
    }
    else
    {
       //Top' = (Top+Height)' - Height' to avoid Integer division truncates
       Capture.top = ((((ZoomMapInfo.CaptureY+ZoomMapInfo.CaptureHeight)*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor) - Capture.height;
    }

    Capture.width = (((ZoomMapInfo.CaptureWidth*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor);
    if(ZoomMapInfo.ImageX == ZoomMapInfo.CaptureX)
    {
        Capture.left = Image.left;
    }
    else
    {
       //Left' = (Left+Width)' - Height' to avoid Integer division truncates
        Capture.left = ((((ZoomMapInfo.CaptureX+ZoomMapInfo.CaptureWidth)*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor)+ScreenAlignShiftX - Capture.width;
    }

    if ((Capture.left+Capture.width) > (Image.left+Image.width))
    {
       Capture.width = (Image.left+Image.width) - Capture.left;
    }
    else if ((Capture.left+Capture.width) == (Image.left+Image.width))
    {
       Capture.width = (Image.left+Image.width) - (Capture.left+THICKNESS);
    }

    if ((Capture.top+Capture.height) > (Image.top+Image.height))
        Capture.height = (Image.top+Image.height) - Capture.top;

    //***2. Switch GOP & Creat Gwin***//
    U16 u16X0=0, u16X1=0, u16Y0=0, u16Y1=0;
    U8 u8PrevGopID;
    U8 u8PrevWinID;

    u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();
    u8PrevWinID = MApi_GOP_GWIN_GetCurrentWinId();
    msAPI_OSD_GetClipWindow(&u16X0, &u16Y0, &u16X1, &u16Y1);

    //MApi_GOP_GWIN_SetForceWrite(TRUE);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    #if (  (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)    \
    || (UI_SKIN_SEL ==  UI_SKIN_1366X768X4444)   \
    || (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)    \
    || (UI_SKIN_SEL ==  UI_SKIN_1366X768X8888)   \
    )
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0, ZUI_ALIGNED_VALUE(1366,8), 768);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,ZUI_ALIGNED_VALUE(1366,8),PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, PANEL_HEIGHT);
    }
    #endif

    #if (UI_SKIN_SEL ==  UI_SKIN_960X540X565 || UI_SKIN_SEL == UI_SKIN_960X540XI8)
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0, 960,540);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,960,PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
    }
    #endif
    #if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0, 1920,1080);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,1920,PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 1080, PANEL_HEIGHT);
    }
    #endif

    if (bCreatGwin)
    {
        u8ZooMapWinId = MApi_GOP_GWIN_CreateWin(GE_ALIGNED_VALUE(Screen.width, 8), Screen.height, GFX_FMT_ARGB1555);

        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);

        if(u8ZooMapWinId == 0xFF)
        {
            MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
            MApi_GOP_GWIN_Switch2Gwin(u8PrevWinID);
            msAPI_OSD_SetClipWindow(u16X0, u16Y0, u16X1, u16Y1);
            //printf("\n...failed to create ZoomMap window...\n");
            return;
        }

        MApi_GOP_GWIN_SetWinPosition(u8ZooMapWinId, startX, startY);

        MApi_GOP_GWIN_Switch2Gwin(u8ZooMapWinId);
        msAPI_OSD_SetClipWindow(0, 0, GE_ALIGNED_VALUE(Screen.width, 8), Screen.height);

        //msAPI_OSD_DrawBlock(&clrBtn);
        MApi_GOP_GWIN_SetBlending(u8ZooMapWinId, FALSE, 0x3f);
    }
    else
    {
        if(u8ZooMapWinId == 0xFF)
        {
            MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
            MApi_GOP_GWIN_Switch2Gwin(u8PrevWinID);
            msAPI_OSD_SetClipWindow(u16X0, u16Y0, u16X1, u16Y1);
            //printf("\n...failed, no ZoomMap window...\n");
            return;
        }
    }


    //***3. BitBlt ZoomImage***//
    GOP_GwinFBAttr m_ZoomMapFbAttr;
    ST_PHOTO_CAPTURE_RECT stPhotoImgTo, stPhotoImgFrom;

    memset(&stPhotoImgTo, 0, sizeof(stPhotoImgTo));
    memset(&stPhotoImgFrom, 0, sizeof(stPhotoImgFrom));

    MApi_GOP_GWIN_GetFBInfo(MApi_GOP_GWIN_GetFBfromGWIN(u8ZooMapWinId), &m_ZoomMapFbAttr);
    stPhotoImgTo.u32BuffAddr = m_ZoomMapFbAttr.addr;
    stPhotoImgTo.u16BuffW = m_ZoomMapFbAttr.width;
    stPhotoImgTo.u16BuffH = m_ZoomMapFbAttr.height;
    stPhotoImgTo.u8FbFmt =(U8) m_ZoomMapFbAttr.fbFmt; // it is because GOP driver, please ask min-cha ////GFX_FMT_ARGB1555
    //printf("\n u32BuffAddr=%lx, u16BuffW=%x , u16BuffH=%x  , fmt=%x \n",m_ZoomMapFbAttr.addr,m_ZoomMapFbAttr.width, m_ZoomMapFbAttr.height , (U8)m_ZoomMapFbAttr.fbFmt);


    MApp_Photo_GetImageCoordinatesOnSource(&stPhotoImgFrom.u16RectX, &stPhotoImgFrom.u16RectY, &stPhotoImgFrom.u16RectW, &stPhotoImgFrom.u16RectH);
    //printf("\n ImgFrom.u16RectX=%d, ImgFrom.u16RectY=%d , ImgFrom.u16RectW=%d  , ImgFrom.u16RectH=%d \n",stPhotoImgFrom.u16RectX,stPhotoImgFrom.u16RectY, stPhotoImgFrom.u16RectW, stPhotoImgFrom.u16RectH);

    stPhotoImgTo.u16RectX = Image.left;
    stPhotoImgTo.u16RectY = Image.top;
    stPhotoImgTo.u16RectW = Image.width;
    stPhotoImgTo.u16RectH = Image.height;
    //printf("\n ImgTo.u16RectX=%d, ImgTo.u16RectY=%d , ImgTo.u16RectW=%d  , ImgTo.u16RectH=%d \n",stPhotoImgTo.u16RectX,stPhotoImgTo.u16RectY, stPhotoImgTo.u16RectW, stPhotoImgTo.u16RectH);

    if (bCreatGwin)
    {
        msAPI_GE_ClearFrameBufferByWord((U32)stPhotoImgTo.u32BuffAddr, (2L * stPhotoImgTo.u16BuffW * stPhotoImgTo.u16BuffH), 0xC210C210);
    }

    MApp_Photo_Display_ZoomImage(
            &stPhotoImgTo,
            &stPhotoImgFrom,
            EN_PHOTO_ALIGN_TOP_LEFT,
            EN_PHOTO_FIT_VIEW_WINDOW);


    //***4. Draw ZoomCapture border***//
    static  DRAW_RECT_BORDER _ZUI_TBLSEG _DrawCaptureBorder =
    {
        COLOR_YELLOW,
        COLOR_YELLOW,
        THICKNESS,
        eSolidLine,
    };
    //get buffer GC for offline drawing...
    PAINT_PARAM st_param;
    memset(&st_param,0,sizeof(PAINT_PARAM));
    // Draw bolder
    DRAW_RECT_BORDER * pDrawBorder = (DRAW_RECT_BORDER*)_ZUI_MALLOC(sizeof(DRAW_RECT_BORDER));
    if (pDrawBorder)
    {
        RECT rect;
        memset(&rect,0,sizeof(RECT));
        rect.left = Capture.left;
        rect.top = Capture.top;
        rect.width = Capture.width;
        rect.height = Capture.height;
        st_param.dc.u8FbID = MApi_GOP_GWIN_GetFBfromGWIN(u8ZooMapWinId);
        st_param.dc.u8ConstantAlpha = 0xFF;
        st_param.dc.bSrcAlphaReplaceDstAlpha = 0;
        memcpy(pDrawBorder, &_DrawCaptureBorder, sizeof(DRAW_RECT_BORDER));
        _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, pDrawBorder, &st_param.dc, &rect);
        _ZUI_FREE(pDrawBorder);
    }


    //***5. Enable Gwin***//
    MApi_GOP_GWIN_Enable(u8ZooMapWinId, TRUE);


    //***6. Return to Prev GOP&Gwin***//
    MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
    MApi_GOP_GWIN_Switch2Gwin(u8PrevWinID);
    msAPI_OSD_SetClipWindow(u16X0, u16Y0, u16X1, u16Y1);
    //MApi_GOP_GWIN_SetForceWrite(FALSE);

 #else

    UNUSED(bCreatGwin);

    //***0. Get ZoomMap Info***//
    ST_ZOOM_MAP_INFO ZoomMapInfo;

    memset(&ZoomMapInfo, 0, sizeof(ZoomMapInfo));
    MApp_Photo_GetZoomMapInfo(&ZoomMapInfo);


    //***1. Calculate Screen, Image, Capture***//
    RECT Screen, Image, Capture;

    Screen.width = (((ZoomMapInfo.ScreenWidth*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor)-1;
    Screen.height = (((ZoomMapInfo.ScreenHeight*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor)-1;

    Image.left = (((ZoomMapInfo.ImageX*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor);
    Image.top = (((ZoomMapInfo.ImageY*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor);
    Image.width = (((ZoomMapInfo.ImageWidth*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor)-1;
    Image.height = (((ZoomMapInfo.ImageHeight*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor)-1;

    Capture.left = (((ZoomMapInfo.CaptureX*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor);
    Capture.top = (((ZoomMapInfo.CaptureY*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor);
    Capture.width = (((ZoomMapInfo.CaptureWidth*ZUI_DEFAULT_PANEL_WIDTH)/ZoomMapInfo.ScreenWidth)/factor)-1;
    Capture.height = (((ZoomMapInfo.CaptureHeight*ZUI_DEFAULT_PANEL_HEIGHT)/ZoomMapInfo.ScreenHeight)/factor)-1;

    if ((Capture.left+Capture.width) > (Image.left+Image.width))
        Capture.width = (Image.left+Image.width) - Capture.left;

    if ((Capture.top+Capture.height) > (Image.top+Image.height))
        Capture.height = (Image.top+Image.height) - Capture.top;

    //***3. Move ZUI Screen, Image, Capture layout***//
    //MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_ZOOMMAP_GROUP, SW_SHOW);
    U16 u16ScreenX;   //Jiangwen 20140411
    if(startX > (ZUI_DMP_WIDTH - Screen.width - startY))
    {
        u16ScreenX = ZUI_DMP_WIDTH - Screen.width -startY;
    }
    else
    {
        u16ScreenX = startX;
    }
    //MApp_ZUI_API_MoveWindowByOffset(HWND_DMP_PLAYBACK_ZOOMMAP_GROUP, u16ScreenX, startY, Screen.width, Screen.height);
    MApp_ZUI_API_MoveWindowByOffset(HWND_DMP_PLAYBACK_ZOOMMAP_SCREEN, u16ScreenX, startY, Screen.width, Screen.height);
    MApp_ZUI_API_MoveWindowByOffset(HWND_DMP_PLAYBACK_ZOOMMAP_IMAGE, u16ScreenX+Image.left, startY+Image.top, Image.width, Image.height);
    MApp_ZUI_API_MoveWindowByOffset(HWND_DMP_PLAYBACK_ZOOMMAP_CAPTURE, u16ScreenX+Capture.left, startY+Capture.top, Capture.width, Capture.height);
 #endif
}

static void _MApp_ZUI_ACT_DMPCloseZoomMapWin(void)
{
#if ((GE_FRAMEBUFFER_LEN >= ((ZUI_ALIGNED_VALUE(UI_OSD_PANE_W,8)*UI_OSD_PANE_H*2L)*2) + (((ZUI_ALIGNED_VALUE(UI_OSD_PANE_W,8)*UI_OSD_PANE_H*2L)/ZOOM_MAP_FACTOR)/ZOOM_MAP_FACTOR)) && (E_GOP_OSD != E_GOP_APP))
    //***0. Check ZoomMap Win***//
    if(u8ZooMapWinId == 0xFF)
        return;

    //***1. Switch GOP & Creat Gwin***//
    U16 u16X0, u16X1, u16Y0, u16Y1;
    U8 u8PrevGopID;
    U8 u8PrevWinID;

    u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();
    u8PrevWinID = MApi_GOP_GWIN_GetCurrentWinId();
    msAPI_OSD_GetClipWindow(&u16X0, &u16Y0, &u16X1, &u16Y1);

    // Switch to GOP APP
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_GWIN_Switch2Gwin(u8ZooMapWinId);
    MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT)0, TRUE);

    MApi_GOP_GWIN_Enable(u8ZooMapWinId, FALSE);
    MApi_GOP_GWIN_DestroyWin(u8ZooMapWinId);
    u8ZooMapWinId= 0xFF;

    // restore GOP
    MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
    MApi_GOP_GWIN_Switch2Gwin(u8PrevWinID);
    msAPI_OSD_SetClipWindow(u16X0, u16Y0, u16X1, u16Y1);

#else
    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_ZOOMMAP_GROUP, SW_HIDE);
#endif

}
#endif

static void _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND hwnd, BOOLEAN bEnable)
{
    //note: if enable, try to check string length is long enough, and then start animation
    //          if disable, stop and clear to normal status

    if (hwnd != HWND_INVALID)
    {
        GUI_DATA_MARQUEE_VARDATA * pData =
            (GUI_DATA_MARQUEE_VARDATA*)MApp_ZUI_API_GetWindowData(hwnd);

        if (pData == NULL)
            return;

        if (bEnable)
        {
            pData->u8ShowStartPosition = 0;
            MApp_ZUI_API_SetTimer(hwnd, 0, DMP_MARQUEE_INITIAL_INTERVAL_MS);

        }
        else
        {
            pData->u8ShowStartPosition = 0xFF;
            MApp_ZUI_API_KillTimer(hwnd, 0);
        }
        MApp_ZUI_API_InvalidateWindow(hwnd);
    }
}


#if ENABLE_USB_DEVICE_LIST
static BOOLEAN bIsDrvIdxByUser = FALSE;         //Set drive index
static U8 u8UserDrvIdx = 0xff;                  //Current drive index
static U8 u8UserDrvPageIdx = 0xff;              //Current drive page index

void MApp_ZUI_ACT_DMPSetDrvIdxByUser(BOOLEAN bEnable)
{
    bIsDrvIdxByUser = bEnable;
}

BOOLEAN MApp_ZUI_ACT_DMPGetIsDrvIdxByUser(void)
{
    return bIsDrvIdxByUser;
}

U8 MApp_ZUI_ACT_DMPGetCurDrvIdxByUser(void)
{
    return u8UserDrvIdx;      //drive idx is ZERO base
}

U8 MApp_ZUI_ACT_DMPGetDrvPageIdxByUser(void)
{
    return u8UserDrvPageIdx;  //page idx is NONE-ZERO base
}

void MApp_ZUI_ACT_DMPSetCurDrvIdxAndCalPageIdxByUser(U8 u8Idx)
{
    u8UserDrvIdx = u8Idx;
    u8UserDrvPageIdx = ((u8Idx+1) / DMP_DRIVE_NUM_PER_PAGE) + 1; //page idx is NONE-ZERO base
}

void MApp_ZUI_ACT_DMPSetDrvPageIdxByUser(U8 u8Idx)
{
    u8UserDrvPageIdx = u8Idx;
}
#endif

/////////////////////////////////////////////////////////////////////
static void _MApp_ACTdmp_ShowMediaTypePage(void)
{
	printf("gchen _MApp_ACTdmp_ShowMediaTypePage 111111 \n");//gchen  @ 20171220
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_TOP, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_BOTTOM, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_SEL_BAR_GROUP, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_DMP_MENU_BG, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_PAGE, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_PHOTO, SW_SHOW);
#if ENABLE_MPLAYER_MOVIE
    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_MOVIE, SW_SHOW);
#else
    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_MOVIE, SW_HIDE);
#endif
#if ENABLE_MPLAYER_TEXT
    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_TEXT, SW_SHOW);
#else
    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_TEXT, SW_HIDE);
#endif

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_MEDIA_TYPE_PAGE);
#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
    m_bCopyOn = FALSE;
#endif
}
 static void _MApp_ACTdmp_ShowDrivePage(void)
{
    U8 u8ShowItem;
    U8 u8TotalPageIdx = (MApp_MPlayer_QueryTotalDriveNum() / DMP_DRIVE_NUM_PER_PAGE)+1;
    if(MApp_DMP_GetDrvPageIdx() == u8TotalPageIdx) //last page
    {
        u8ShowItem = (MApp_MPlayer_QueryTotalDriveNum() % DMP_DRIVE_NUM_PER_PAGE)+1;
    }
    else
    {
        u8ShowItem = DMP_DRIVE_NUM_PER_PAGE;
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_TOP, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_BOTTOM, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_SEL_BAR_GROUP, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_DMP_MENU_BG, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DMP_DRIVE_PAGE, SW_SHOW);

    U8 i;
    for( i = DMP_DRIVE_NUM_PER_PAGE ; i > u8ShowItem ; i--)
    {
        MApp_ZUI_API_ShowWindow( _hwndListDriveItem[i-1],SW_HIDE);
    }
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_DRIVE_PAGE);
}

static void _MApp_ACTdmp_ShowFilePage(void)
{
    U16 u16X = 0;
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_BOTTOM, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_SELECT_PAGE, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_TEXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_GROUP, SW_HIDE);
    #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS, (m_bCopyOn==TRUE)?SW_SHOW:SW_HIDE);
    #else
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS, SW_HIDE);
    #endif
    for(u16X = 0; u16X < DMP_NUM_OF_FILES_PER_PAGE; u16X++)
    {
        MApp_ZUI_API_EnableWindow(_hwndListFileItem[u16X], ENABLE);
    }
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);

#if (ENABLE_ATSC_TTS)
    MApp_TTS_Cus_Set_InputText_Format( MApp_ZUI_API_GetU16String(MApp_MPlayer_QueryTotalFileNum()-1), EN_TTS_SPEAK_NUMBER_CARDINAL );
    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Main_Menu_Item), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Main_Menu_Item)));
    MApp_TTSControlSetOn(TRUE);
#endif
}

static void _MApp_ACTdmp_ShowPreviewWin(void)
{
    //File type
    //printf("\r\nPREVIEWWIND = %d", MApp_MPlayer_QueryCurrentMediaType
    switch(MApp_MPlayer_QueryCurrentMediaType() )
    {
        case E_MPLAYER_TYPE_MOVIE: // preview movie only
        // TODO: refine flag
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_THUMBNAIL_PLAYING)
            {
            }
            else
            {
                #if DMP_MOVIE_PREVIEW
                //MApp_MPlayer_BeginPreview();
                #endif
            }
        // move below code to E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW for movie only
        //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            break;

        case E_MPLAYER_TYPE_PHOTO:
			#if 1
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_THUMBNAIL_PLAYING)
            {
            }
            else
            {
                //MApp_MPlayer_BeginPreview();
            }
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            #endif
            break;

        case E_MPLAYER_TYPE_MUSIC:
            #if DMP_MUSIC_PREVIEW
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_BGM_MODE)
            {
                DMP_DBG(printf("BGM no preview music\n"));
            }
            else
            {
                DMP_DBG(printf("BGM preview music!\n"));
                //MApp_MPlayer_BeginPreview();
            }
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            #endif
            break;

        case E_MPLAYER_TYPE_TEXT:
			#if DMP_TEXT_PREVIEW
            //MApp_MPlayer_BeginPreview();
			#endif
            break;

        default:  // plugin
            break;
    }
}


#if PLAYLIST_BGM
static void _MApp_ACTdmp_ShowBgmDrivePage(void)
{
    U8 u8ShowItem;
    U8 u8TotalPageIdx = (MApp_MPlayer_QueryTotalDriveNum() / DMP_DRIVE_NUM_PER_PAGE)+1;

    if(MApp_DMP_GetDrvPageIdx() == u8TotalPageIdx) //last page
    {
        u8ShowItem = (MApp_MPlayer_QueryTotalDriveNum() % DMP_DRIVE_NUM_PER_PAGE)+1;
    }
    else
    {
        u8ShowItem = DMP_DRIVE_NUM_PER_PAGE;
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_TOP, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_BOTTOM, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_SEL_BAR_GROUP, SW_SHOW);
	
    MApp_ZUI_API_ShowWindow(HWND_DMP_DRIVE_BGM_PAGE, SW_SHOW);

    U8 i;
    for( i = DMP_DRIVE_NUM_PER_PAGE ; i > u8ShowItem ; i--)
    {
        MApp_ZUI_API_ShowWindow( _hwndBgmListDriveItem[i-1],SW_HIDE);
    }
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_DRIVE_BGM_PAGE);
}

static void _MApp_ACTdmp_ShowBgmFilePage(void)
{
    U16 u16X = 0;
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
    //MApp_ZUI_API_ShowWindow(HWND_DMP_BG_GRADIENT_BOTTOM, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DMP_BGM_FILE_SELECT_PAGE, SW_SHOW);
    for(u16X = 0; u16X < DMP_NUM_OF_FILES_PER_PAGE; u16X++)
    {
        MApp_ZUI_API_EnableWindow(_hwndBgmListFileItem[u16X], ENABLE);
    }
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BGM_FILE_SELECT_PAGE);
}
#endif
#if 0
static void _MApp_ACTdmp_ShowPreviewWin(void)
{
#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
    if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PROGRESS_WINDOW))
        return;

    if (m_bCopyOn == TRUE)
        return;
#endif
    //File type
    switch(MApp_MPlayer_QueryCurrentMediaType() )
    {

#if (ENABLE_MPLAYER_MOVIE)
        case E_MPLAYER_TYPE_MOVIE: // preview movie only
        // TODO: refine flag
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_THUMBNAIL_PLAYING)
            {
            }
            else
            {
                #if DMP_MOVIE_PREVIEW
                //MApp_MPlayer_BeginPreview();
                #endif
            }
        // move below code to E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW for movie only
        //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            break;
#endif
        case E_MPLAYER_TYPE_PHOTO:
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_THUMBNAIL_PLAYING)
            {
            }
            else
            {
                //MApp_MPlayer_BeginPreview();
            }
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            //#endif
            break;
        case E_MPLAYER_TYPE_MUSIC:
            #if DMP_MUSIC_PREVIEW
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_BGM_MODE)
            {
                DMP_DBG(printf("BGM no preview music\n"));
            }
            else
            {
                DMP_DBG(printf("BGM preview music!\n"));
            #if ENABLE_EMBEDDED_PHOTO_DISPLAY
                if(MApp_DMP_GetDmpFlag() & DMP_FLAG_THUMBNAIL_PLAYING)
                {
                }
                else
            #endif
                {
                    //MApp_MPlayer_BeginPreview();
                }
            }
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            #endif
            break;
#if (ENABLE_MPLAYER_TEXT)
        case E_MPLAYER_TYPE_TEXT:
            //MApp_MPlayer_BeginPreview();
            break;
#endif
        default:  // plugin
            break;
    }
}
#endif

static void _MApp_ACTdmp_HidePreviewWin(void)
{
    //File type
    MApp_MPlayer_StopPreview();
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_TEXT, SW_HIDE);
    MApp_ZUI_API_KillTimer(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, DMP_TIMER_PREVIEW_WIN);
    //_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_FILE_PAGE_PREVIEW_FILENAME_STRING, FALSE);
}

static void _MApp_ACTdmp_ShowAlertWin(EN_DMP_MSG_TYPE enMsgType)
{
    _enDmpMsgType = enMsgType;

    MApp_ZUI_API_StoreFocusCheckpoint();
    #if 0 //smc.chy 2010/07/01 for show loading alert when switch to Usb port
    if( MApp_DMP_GetDmpUiState() == DMP_UI_STATE_MEDIA_SELECT)
    {
        // for thumbnail is showing, we remove the usb disk, do not show the
        // alert window

    }
    else
    #endif
    {
        MApp_ZUI_API_ShowWindow(HWND_DMP_ALERT_WINDOW, SW_SHOW);
		if(enMsgType != DMP_MSG_TYPE_UNSUPPORTED_BUTTON && (enMsgType != DMP_MSG_TYPE_UNSUPPORTED_FILE))  //wht120519_2  add  //wht120715_1 add DMP_MSG_TYPE_UNSUPPORTED_FILE
        	MApp_ZUI_API_SetFocus(HWND_DMP_ALERT_WINDOW);
    }
}

static void _MApp_ACTdmp_HideAlertWin(void)
{
    MApp_ZUI_API_ShowWindow(HWND_DMP_ALERT_WINDOW, SW_HIDE);
    //printf("[Alert] focus check point : %d\n", MApp_ZUI_API_GetFocusCheckpoint());
    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
    {
        MApp_ZUI_API_SetTimer(HWND_DMP_RESUME_STOP_WINDOW, DMP_TIMER_RESUMESTOP_WIN, DMP_TIME_MS_RESUMESTOP_WIN);
        MApp_ZUI_API_SetFocus(HWND_DMP_RESUME_STOP_ICON_YES);
    }
    else
    {
        MApp_ZUI_API_SetFocus(MApp_ZUI_API_GetFocusCheckpoint());
    }
    _enDmpMsgType = DMP_MSG_TYPE_MAX;
}

#if (ENABLE_DELETE_SELECTED_FILES || ENABLE_COPY_SELECTED_FILES)
static void _MApp_ACTdmp_ShowProgressWin(void)
{
    MApp_ZUI_API_StoreFocusCheckpoint();

    MApp_ZUI_API_SetTimer(HWND_DMP_PROGRESS_WINDOW, DMP_TIMER_PROGRESS_WIN, DMP_TIME_MS_PROGRESS_WIN);
    MApp_ZUI_API_ShowWindow(HWND_DMP_PROGRESS_WINDOW, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DMP_PROGRESS_STOP, SW_HIDE);
    MApp_ZUI_API_SetFocus(HWND_DMP_PROGRESS_WINDOW);
    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
}
#endif

static void _MApp_ACTdmp_HideProgressWin(void)
{
    MApp_ZUI_API_KillTimer(HWND_DMP_PROGRESS_WINDOW, DMP_TIMER_PROGRESS_WIN);
    MApp_ZUI_API_ShowWindow(HWND_DMP_PROGRESS_WINDOW, SW_HIDE);
}

/* static void _MApp_ACTdmp_ShowSubMenu(void)
{
#if 0
    MPlayerFileInfo fileInfo;
    U16 u16Idx = MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE);

    //Set current thumb item to DISABLE attribute for displaying 'fake focus' on it
    MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetFocus(), DISABLE);
    MApp_ZUI_API_StoreFocusCheckpoint();
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_GROUP, SW_SHOW);
    if((MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16Idx, &fileInfo) == E_MPLAYER_RET_OK))
    {
        if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
        {
        #if (ENABLE_COPY_SELECTED_FILES == DISABLE)
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_COPY, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, SW_HIDE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, ENABLE);
            MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_DELETE);
        #else
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_COPY, DISABLE);

            if(MApp_MPlayer_IsCopyFileExist())
            {
                //Focus on DIR, only paste file can be done
                MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, ENABLE);
            }
            else
            {
                //Nothing can be done: press OK or EXIT to close submenu
                MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, DISABLE);
            }
            MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_DELETE);
        #endif
        }
        else
        {
        #if (ENABLE_COPY_SELECTED_FILES == DISABLE)
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_COPY, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, SW_HIDE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, ENABLE);
            MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_DELETE);
        #else
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_COPY, ENABLE);

            if(MApp_MPlayer_IsCopyFileExist())
            {
                MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, ENABLE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, DISABLE);
            }
            MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_DELETE);
        #endif

        }
    }

    #if (!ENABLE_MPLAYER_SORT_EX)
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, SW_HIDE);
    #endif
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_GROUP, SW_HIDE);
#else
    //Set current thumb item to DISABLE attribute for displaying 'fake focus' on it
    MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetFocus(), DISABLE);
    MApp_ZUI_API_StoreFocusCheckpoint();

    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_GROUP, SW_SHOW);

    #if (ENABLE_COPY_SELECTED_FILES == DISABLE)
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_COPY, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_FORMAT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_CANCEL, SW_HIDE);
    MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, ENABLE);
    MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, ENABLE);
    MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_DELETE);
    #else
    MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_COPY, ENABLE);
    if (m_bCopyOn == TRUE)
    {
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_FORMAT, DISABLE);
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, DISABLE);
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_CANCEL, ENABLE);
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, DISABLE);
    }
    else
    {
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_FORMAT, ENABLE);
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_DELETE, ENABLE);
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_CANCEL, DISABLE);
        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, ENABLE);
    }
    MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_COPY);
    #endif

    #if (!ENABLE_MPLAYER_SORT_EX)
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT, SW_HIDE);
    #endif
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_GROUP, SW_HIDE);
#endif
}
*/
static void _MApp_ACTdmp_HideSubMenu(void)
{
    MPlayerFileInfo fileInfo;
    U16 u16Idx = MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE);
    U16 u16X = 0;

    //Clear 'fake focus' status firstly
    for(u16X = 0; u16X < DMP_NUM_OF_FILES_PER_PAGE; u16X++)
    {
        MApp_ZUI_API_EnableWindow(_hwndListFileItem[u16X], ENABLE);
    }
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_GROUP, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_GROUP, SW_HIDE);
    MApp_ZUI_API_SetFocus(_hwndListFileItem[u16Idx]);
    //printf("    >> set focus to %d (hwnd=%d)\n", u16Idx, _hwndListFileItem[u16Idx]);
    if((MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16Idx, &fileInfo) == E_MPLAYER_RET_OK))
    {
        if(!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
        {
            //File type
            //_MApp_ACTdmp_ShowPreviewWin();
        }
    }
}

///
static U16 _MApp_DMP_QueryTotalPlayListNum(void)
{
    U16 u16PlayListNum = MApp_MPlayer_QuerySelectedFileNum(MApp_MPlayer_QueryCurrentMediaType());
    DMP_DBG(printf("_MApp_DMP_QueryTotalPlayListNum %u\n",u16PlayListNum););
    if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY
        || MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
    {
        u16PlayListNum = MApp_MPlayer_QueryTotalFileNum() - MApp_MPlayer_QueryDirectoryNumber();
    }
    return u16PlayListNum;
}

static void _MApp_DMP_ErrorHandling_GotoDefaultPage(enumMPlayerMediaType eMediaType)
{
    DMP_DBG(printf("[ERROR HANDLE] Back to default page\n"));

    MApp_MPlayer_Stop();
    MApp_MPlayer_StopMusic();

    msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

    switch(eMediaType)
    {
        case E_MPLAYER_TYPE_MOVIE:
#if (ENABLE_SUBTITLE_DMP)
            if(MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_MPEG4)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE ,SW_HIDE);
                MApp_MPlayer_DisableSubtitle();
                _stDmpPlayVar.stMovieInfo.bSubtitleOff = TRUE;
            }
#endif //#if (ENABLE_SUBTITLE_DMP)
            break;

        case E_MPLAYER_TYPE_MUSIC:
            _u16MusicCurrentTime = 0; //initial value for drawing 'MUSIC' current time
            if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
            {
                MApp_MPlayer_DisableLRCLyric();
                memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE, SW_HIDE);
            }
#if ENABLE_MUSIC_EQ_MODE
            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, SW_HIDE);
#endif
            break;

        case E_MPLAYER_TYPE_PHOTO:
            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FILE);
            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
            break;

        default:
            break;
    }

    //To do: set focus item
    //_MApp_MediaPlayer_SetDefaultFocus();
    //To do: Need to reset MM State flag??
    if(MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING)
    {
        MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
    }

    //MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);

    if (m_u16PlayErrorNum <= 1)
    {
        _enDmpMsgType = DMP_MSG_TYPE_UNSUPPORTED_FILE;
    }
    else
    {
        _enDmpMsgType = DMP_MSG_TYPE_ALL_FILES_UNSUPPORTED;
    }
    //MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
}

void _MApp_ACTdmp_MovieCancelRepeatAB(void)
{
    _enRepeatABStatus = REPEATAB_MODE_NONE;
    _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0]= 0xFFFFFFFF;
    _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] = 0xFFFFFFFF;
    MApp_MPlayer_MovieSetRepeatAB(E_MPLAYER_MOVIE_SET_REPEAT_AB_NONE, 0);
//    MApp_ZUI_API_InvalidateWindow(HWND_DMP_MOVIE_INFO_ICON_AB_REPEAT);
    MApp_DMP_ClearDmpFlag(DMP_FLAG_MOVIE_REPEATAB_MODE);
    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][2] = en_str_SET_A;
}

void _MApp_ACTdmp_MusicCancelRepeatAB(void)
{
    _enRepeatABStatus = REPEATAB_MODE_NONE;
    _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0]= 0xFFFFFFFF;
    _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1] = 0xFFFFFFFF;

    DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][2] = en_str_SET_A;
}

////
static BOOLEAN _MApp_DMP_GB2Unicode(U8 *pu8SrcString, U8 *pu8DstString, U16 u16StringMax)
{
    U16 u16SrcIdx, u16DstIdx;
    U16 pu16StrSrcTemp, pu16StrDstTemp;

    u16SrcIdx = 0;
    u16DstIdx = 0;
    while(u16SrcIdx < u16StringMax)
    {
        if(isprint(pu8SrcString[u16SrcIdx]))
        {
            pu8DstString[u16DstIdx] = pu8SrcString[u16SrcIdx];
            pu8DstString[u16DstIdx+1] = '\0';
            u16SrcIdx++;
            u16DstIdx+=2;
        }
        else if(pu8SrcString[u16SrcIdx] == '\0')
        {
            pu8DstString[u16DstIdx] = '\0';
            pu8DstString[u16DstIdx+1] = '\0';
            u16SrcIdx++;
            u16DstIdx+=2;
            break;
        }
        else
        {
            memcpy(&pu16StrSrcTemp,&pu8SrcString[u16SrcIdx],2);
            pu16StrSrcTemp=Swap16(pu16StrSrcTemp);
            pu16StrDstTemp = MApp_Transfer2Unicode(pu16StrSrcTemp);
            memcpy(&pu8DstString[u16DstIdx],&pu16StrDstTemp,2);
            u16SrcIdx+=2;
            u16DstIdx+=2;
        }
    }
    return TRUE;
}

#if PLAYLIST_BGM
static void _MApp_DMP_SavePhotoPath(void)
{
    m_u8PhotoDrive = MApp_DMP_GetCurDrvIdx();
    m_u16PhotoDepth = MApp_MPlayer_QueryDirectoryDepth();
    MApp_MPlayer_QueryDirectoryNode(m_u16PhotoIdxByDir, m_u16PhotoDepth);
    m_u16PhotoIdx = MApp_MPlayer_QueryCurrentPlayingList();

    ePhotoPlayMode = MApp_MPlayer_QueryPlayMode();
#if ENABLE_MPLAYER_SORT_EX
    ePhotoSortMode = MApp_MPlayer_QueryCurrentFileSortingMode();
    ePhotoOrderMode = MApp_MPlayer_QueryCurrentFileSortingOrderMode();
#endif
}

static void _MApp_DMP_EnterPhotoPath(void)
{
    MApp_MPlayer_Change2TargetDirectory(MApp_DMP_GetDriveFromMappingTable(m_u8PhotoDrive), m_u16PhotoIdxByDir, m_u16PhotoDepth);
    MApp_DMP_SetCurDrvIdxAndCalPageIdx(m_u8PhotoDrive);
    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, m_u16PhotoIdx);
    MApp_MPlayer_SetCurrentPageIndex(m_u16PhotoIdx/NUM_OF_MUSIC_FILES_PER_PAGE);

    MApp_MPlayer_SetPlayMode(ePhotoPlayMode);
#if ENABLE_MPLAYER_SORT_EX
    MApp_MPlayer_ReSortFileBrowser(ePhotoSortMode, ePhotoOrderMode);
#endif
}

static void _MApp_DMP_SaveBgmPath(void)
{
    m_u8BgmDrive = MApp_DMP_GetCurDrvIdx();
    m_u16BgmDepth = MApp_MPlayer_QueryDirectoryDepth();
    MApp_MPlayer_QueryDirectoryNode(m_u16BgmIdxByDir, m_u16BgmDepth);
    m_u16BgmIdx = MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY);

    eBgmPlayMode = MApp_MPlayer_QueryPlayMode();
#if ENABLE_MPLAYER_SORT_EX
    eBgmSortMode = MApp_MPlayer_QueryCurrentFileSortingMode();
    eBgmOrderMode = MApp_MPlayer_QueryCurrentFileSortingOrderMode();
#endif
}

static void _MApp_DMP_EnterBGMPath(void)
{
    MApp_MPlayer_Change2TargetDirectory(MApp_DMP_GetDriveFromMappingTable(m_u8BgmDrive), m_u16BgmIdxByDir, m_u16BgmDepth);
    MApp_DMP_SetCurDrvIdxAndCalPageIdx(m_u8BgmDrive);
    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, m_u16BgmIdx);
    MApp_MPlayer_SetCurrentPageIndex(m_u16BgmIdx/NUM_OF_MUSIC_FILES_PER_PAGE);

    MApp_MPlayer_SetPlayMode(eBgmPlayMode);
#if ENABLE_MPLAYER_SORT_EX
    MApp_MPlayer_ReSortFileBrowser(eBgmSortMode, eBgmOrderMode);
#endif
}

static void _MApp_ACTdmp_BGM_ReturnToPhotoSlideShow(void)
{
    _MApp_DMP_SaveBgmPath();
    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_PHOTO, TRUE);
    {
        _MApp_DMP_EnterPhotoPath();

        m_u16PlayErrorNum = 0;
        #if (ENABLE_DRM)
        m_u16DRMErrorNum = 0;
        #endif
        MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);

        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PAGE,SW_HIDE);
        //_MApp_ACTdmp_HidePreviewWin();
        // TODO: set this flag earlier!!! care this
        MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
        //MApp_DMP_SetDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
        //MApp_DMP_SetDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
        _InsertQFlag = FALSE;
        MApp_DMP_UiStateTransition(DMP_UI_STATE_LOADING);
        DMP_DBG(puts("\r\nSlide Show - File"););

        _u8InfoBarIdx = 0;
        MApp_DMP_NotifyUiState(DMP_UI_STATE_LOADING);
    }
}
#endif

///////////////
//this function will reset the focus, hence some notify need to restore the
// focus while calling...
///////////////
static U8 u8CurrentPlaylistPageIdx; // zero base
static U8 u8CurrentPlaylistTotalPage; // non-zero base
#if PLAYLIST_BGM
static BOOLEAN bIsBGMPlaylist;
#endif

static void _Mapp_ACTdmp_Playback_MarqueeText(U16 number){
	U8 i;
    for(i = 0; i < UI_DMP_PLAYLIST_NUMBER; i++)
    {
		_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndPlayListFileString[i],FALSE);
    }
	_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndPlayListFileString[number],TRUE);
}

static void _MApp_ACTdmp_Playback_ShowPlaylistWin(enumMPlayerMediaType eMediaType, bool bSetFoucsOnCurrentPlayingIdx)
{
    #define PLAYLIST_ARROW_UP_CURRENT_WIDTH 16//24    //wht120512_3  21->24
    #define PLAYLIST_ARROW_UP_CURRENT_HEIGHT 16//28   //wht120512_3  21->28
    #define PLAYLIST_ARROW_UP_CURRENT_X 531//797       //wht120512_3  add
    #define PLAYLIST_ARROW_UP_CURRENT_Y 57//96        //wht120512_3  add
    #define PLAYLIST_ARROW_UP_CURRENT_LOFFSET 5
    #define PLAYLIST_ARROW_UP_CURRENT_TOFFSET 5

    U32 i;
    U16 u16CurrentPlayingIdx = 0;
    U16 u16SelectedFileNum; // non-zero base

    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_GROUP,SW_SHOW);

    for(i = 0; i < UI_DMP_PLAYLIST_NUMBER; i++)
    {
        MApp_ZUI_API_ShowWindow(_hwndListPlaylistItem[i],SW_HIDE);
    }

    //calculate how many selected files in playlist
    u16SelectedFileNum = MApp_MPlayer_QueryPlayListFileNum(eMediaType);

    DMP_DBG(printf(" u16SelectedFileNum %u\n",u16SelectedFileNum););

    if(u16SelectedFileNum == 0) // these is no selected files
    {
        U16 u16CurrentDirFileNum;
        U16 u16CurrentDirMediaFileNum;

        u16CurrentDirFileNum = MApp_MPlayer_QueryTotalFileNum();

        DMP_DBG(printf("u16currentDirFileNum %u==========\n",u16CurrentDirFileNum););

        u16CurrentDirMediaFileNum = u16CurrentDirFileNum - MApp_MPlayer_QueryDirectoryNumber();

        if(u16CurrentDirMediaFileNum == 0)
        {
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_PLAYLIST_BUTTON_CANCEL);
            u8CurrentPlaylistTotalPage = 1;
        }
        else
        {
            u8CurrentPlaylistTotalPage = (u16CurrentDirMediaFileNum + UI_DMP_PLAYLIST_NUMBER - 1) / UI_DMP_PLAYLIST_NUMBER;
            if (bSetFoucsOnCurrentPlayingIdx)
            {
                u16CurrentPlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
                u16CurrentPlayingIdx = u16CurrentPlayingIdx - MApp_MPlayer_QueryDirectoryNumber();
                u8CurrentPlaylistPageIdx = u16CurrentPlayingIdx/UI_DMP_PLAYLIST_NUMBER;
            }
            if(u8CurrentPlaylistPageIdx+1 == u8CurrentPlaylistTotalPage) //last page
            {
                U16 u16CurrentPageMediaFileNum; //non-zero base
                u16CurrentPageMediaFileNum = u16CurrentDirMediaFileNum % UI_DMP_PLAYLIST_NUMBER;
                if (u16CurrentPageMediaFileNum == 0)
                {
                    u16CurrentPageMediaFileNum = UI_DMP_PLAYLIST_NUMBER;
                }
                DMP_DBG(printf("!!!!!u16CurrentPageFileNum %u\n",u16CurrentPageMediaFileNum););

                for(i = 0;i < u16CurrentPageMediaFileNum; i++)
                {
                    MApp_ZUI_API_ShowWindow(_hwndListPlaylistItem[i],SW_SHOW);
                }

                MApp_ZUI_API_SetFocus(_hwndListPlaylistItem[u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER]);
            }
            else
            {
                // show all items
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_GROUP,SW_SHOW);
                MApp_ZUI_API_SetFocus(_hwndListPlaylistItem[u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER]);
            }
        }
        //buttonclick or show arrow
        {
            //u16CurrentPlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
            u16CurrentPlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex() - MApp_MPlayer_QueryDirectoryNumber();
            U8 u8CurrentPlayingPageIdx = u16CurrentPlayingIdx/UI_DMP_PLAYLIST_NUMBER;
            if (u8CurrentPlayingPageIdx == u8CurrentPlaylistPageIdx)
            {
                // this playlist page has current playing file
                //MApp_ZUI_API_SetTimer(_hwndListPlaylistItem[u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER], 0, DMP_TIMER_BUTTONCLICK);
                U16  height = PLAYLIST_ARROW_UP_CURRENT_Y;//67;//91; //wht120512_3  67->PLAYLIST_ARROW_UP_CURRENT_Y
                i = u16CurrentPlayingIdx % UI_DMP_PLAYLIST_NUMBER;
                //height += i * 42;
                height += i*26;//i * 43;    //wht120512_3  29->43
                RECT rc;
                //RECT_SET(rc, 850,height,PLAYLIST_ARROW_UP_CURRENT_WIDTH,PLAYLIST_ARROW_UP_CURRENT_HEIGHT);// 35,35);
                RECT_SET(rc, PLAYLIST_ARROW_UP_CURRENT_X,height,PLAYLIST_ARROW_UP_CURRENT_WIDTH,PLAYLIST_ARROW_UP_CURRENT_HEIGHT);// 35,35);
                MApp_ZUI_API_MoveWindow(HWND_DMP_PLAYBACK_PLAYLIST_ARROW_UP_CURRENT, &rc );
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_ARROW_UP_CURRENT, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_ARROW_UP_CURRENT, SW_HIDE);
            }
        }
    }
    else  // there are some selected files, using playlist
    {
        u8CurrentPlaylistTotalPage = (u16SelectedFileNum + UI_DMP_PLAYLIST_NUMBER - 1) / UI_DMP_PLAYLIST_NUMBER;
        if (bSetFoucsOnCurrentPlayingIdx)
        {
            u16CurrentPlayingIdx = MApp_MPlayer_QueryCurrentPlayingList();
            u8CurrentPlaylistPageIdx = u16CurrentPlayingIdx/UI_DMP_PLAYLIST_NUMBER;
        }
        if(u8CurrentPlaylistPageIdx+1 == u8CurrentPlaylistTotalPage) //last page
        {
            U16 u16CurrentPageFileNum; //non-zero base
            u16CurrentPageFileNum = u16SelectedFileNum % UI_DMP_PLAYLIST_NUMBER;
            if (u16CurrentPageFileNum == 0)
            {
                u16CurrentPageFileNum = UI_DMP_PLAYLIST_NUMBER;
            }
            DMP_DBG(printf("u16CurrentPageFileNum %u\n",u16CurrentPageFileNum););

            for(i = 0;i < u16CurrentPageFileNum; i++)
            {
                MApp_ZUI_API_ShowWindow(_hwndListPlaylistItem[i],SW_SHOW);
            }

            MApp_ZUI_API_SetFocus(_hwndListPlaylistItem[u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER]);
        }
        else
        {
            // show all items
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_GROUP,SW_SHOW);
            MApp_ZUI_API_SetFocus(_hwndListPlaylistItem[u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER]);
        }
        {
            u16CurrentPlayingIdx = MApp_MPlayer_QueryCurrentPlayingList();
            U8 u8CurrentPlayingPageIdx = u16CurrentPlayingIdx/UI_DMP_PLAYLIST_NUMBER;
            if (u8CurrentPlayingPageIdx == u8CurrentPlaylistPageIdx)
            {
                // this playlist page has current playing file
                //MApp_ZUI_API_SetTimer(_hwndListPlaylistItem[u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER], 0, DMP_TIMER_BUTTONCLICK);
                U16  top =
                _GUI_WindowPositionList_Zui_Dmp[HWND_DMP_PLAYBACK_PLAYLIST_ITEM1].rect.top;
                i = u16CurrentPlayingIdx%UI_DMP_PLAYLIST_NUMBER;
                top += i *
                (_GUI_WindowPositionList_Zui_Dmp[HWND_DMP_PLAYBACK_PLAYLIST_ITEM2].rect.top
                - _GUI_WindowPositionList_Zui_Dmp[HWND_DMP_PLAYBACK_PLAYLIST_ITEM1].rect.top);
                top += PLAYLIST_ARROW_UP_CURRENT_TOFFSET;
                
                RECT rc;
                RECT_SET(rc,
                _GUI_WindowPositionList_Zui_Dmp[HWND_DMP_PLAYBACK_PLAYLIST_ITEM1].rect.left + PLAYLIST_ARROW_UP_CURRENT_LOFFSET,
                top,PLAYLIST_ARROW_UP_CURRENT_WIDTH,PLAYLIST_ARROW_UP_CURRENT_HEIGHT);// 35,35);
                MApp_ZUI_API_MoveWindow(HWND_DMP_PLAYBACK_PLAYLIST_ARROW_UP_CURRENT, &rc );
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_ARROW_UP_CURRENT, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_ARROW_UP_CURRENT, SW_HIDE);
            }
        }
    }

    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PLAYLIST_GROUP);
}

static void _MApp_ACTdmp_Playback_ShowInfoWin(enumMPlayerMediaType eMediaType)
{
    DMP_DBG(printf("_MApp_ACTdmp_Playback_ShowInfoWin: %u\n",eMediaType););
    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_SHOW);
    switch(eMediaType)
    {
#if (ENABLE_MPLAYER_MOVIE)
        case E_MPLAYER_TYPE_MOVIE:
            {
                U32 currentTime;
                U8 u8Min, u8Sec;
                S8 s8Hour = 0;
            	RECT rect;

                if(_enNotify == E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE
                    || _enNotify == E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE
                  #ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
                    || _enNotify == E_MPLAYER_NOTIFY_PLAY_NEXT_FILE
                  #endif
                    )
                {
                    if ((_enPlayMode_AtNotify >= E_MPLAYER_MOVIE_FB_2X) &&
                        (_enPlayMode_AtNotify <= E_MPLAYER_MOVIE_FB_16X))
                    {
                        // If FB to beginning of file, still show current time, it should be 0.
                        currentTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME)/1000;
                    }
                    else
                    {
                        currentTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME)/1000;
                    }

                }
                else
                {
                    currentTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME)/1000;
                }

                currentTime = currentTime>0 ? currentTime:0;
                s8Hour = (currentTime/3600);
                u8Min = (U8)(currentTime/60-s8Hour*60);
                u8Sec = (U8)(currentTime-s8Hour*3600-u8Min*60);
                _u16MovieCurrentTime = ((s8Hour*60)+u8Min)*60+u8Sec;
                if(_u16MovieTotalTime != 0xFFFF && _u16MovieTotalTime != 0)
                {
                    U32 u32Percent = _u16MovieCurrentTime*100 /_u16MovieTotalTime;

		    if(u32Percent>100)
		        u32Percent=100;

                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
                }
                else if(_u16MovieTotalTime == 0)
                {
                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                }
                else
                {
                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                    DMP_DBG(printf("[Error] Get total time failed! (0x%lx)\n", _u16MovieTotalTime););
                }

                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);

            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP,SW_SHOW);
                // marquee
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_FILENAME_TEXT, TRUE);
                //
            }
			#if ENABLE_GOTO_TIME
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_GOTO_TIME%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
				_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation();
            }
			#endif
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_MOVEVIEW%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
            }
            #if (ENABLE_MPLAYER_CAPTURE_MOVIE == 1)
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_CONFIRM_DIALOG))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_CAPTURE%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
            }
            #endif
#if (ENABLE_DIVX_PLUS != 1)
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_GROUP, SW_HIDE);
            }
#endif

            MApp_ZUI_API_GetWindowRect(HWND_DMP_PLAYBACK_SUBTITLE_TEXT,&rect);
            rect.top=10;
            MApp_ZUI_API_MoveWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE,&rect);
            MApp_ZUI_API_MoveWindow(HWND_DMP_PLAYBACK_SUBTITLE_TEXT,&rect);
        }
            break;
#endif
        case E_MPLAYER_TYPE_MUSIC:
            {
            U32 u32CurTime = _u16MusicCurrentTime;
            U32 u32TotalTime = MApp_MPlayer_QueryMusicFilePlayTime();
            _u16MusicCurrentTime = MApp_MPlayer_QueryMusicFileCurrentTime();

            if(u32TotalTime == 0)
            {
                DMP_DBG(printf("u32TotalTime == 0\n"););
                //u32TotalTime = 1;
                MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
            }
            else if(u32TotalTime != 0xFFFFFFFF && u32TotalTime != 0)
            {
                U32 u32Percent = u32CurTime*100 / (u32TotalTime);
				if(u32Percent>100)
					u32Percent=100;
                MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
            }
            else
            {
                DMP_DBG(printf("[Error] Get music total time failed! (0x%lx)\n", u32TotalTime););
            }
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSIC_BG, SW_SHOW);//wht1203017_4
            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MUSICINFO_INFO_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSICINFO_INFO_GROUP,SW_SHOW);
                // marquee
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_PLAYBACK_MUSICINFO_INFO_FILENAME_TEXT, TRUE);
                //
            }
            #if (ENABLE_MPLAYER_CAPTURE_MUSIC== 1)
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_CONFIRM_DIALOG))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_CAPTURE%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
            }
            #endif
			#if ENABLE_GOTO_TIME
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_GOTO_TIME%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
            }
			#endif
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM7,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM8,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM9,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM10,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM11,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM12,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM13,SW_HIDE);
			
			 MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_MUSIC_BG);//wht1203017_4
            }
            break;
        case E_MPLAYER_TYPE_PHOTO:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM5,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM6,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM7,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM8,SW_HIDE);

            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP,SW_SHOW);
                // marquee
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_FILENAME_TEXT, TRUE);
                //
            }
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[PHOTOINFO_MOVEVIEW%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
            }
            #if (ENABLE_MPLAYER_CAPTURE_LOGO== 1)
            else if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_CONFIRM_DIALOG))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG, SW_HIDE);
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[PHOTOINFO_CAPTURE%DMP_INFOBAR_ICON_NUM]);
                MApp_ZUI_API_StoreFocusCheckpoint();
            }
            #endif
            break;
#if (ENABLE_MPLAYER_TEXT)
        case E_MPLAYER_TYPE_TEXT:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM6,SW_HIDE);//wht1203017_5
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM7,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM8,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM9,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM10,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM11,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM12,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM13,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_ITEM14,SW_HIDE);

            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXTINFO_INFO_GROUP))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXTINFO_INFO_GROUP,SW_SHOW);
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
                HWND_DMP_PLAYBACK_TEXTINFO_INFO_FILENAME_TEXT, TRUE);
            }
            break;
#endif
        default:
            break;
    }
    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PLAYLIST_GROUP))
    {
        _MApp_ACTdmp_Playback_ShowPlaylistWin(eMediaType, TRUE);//wht120516_1  FALSE->TRUE
		 MApp_ZUI_API_StoreFocusCheckpoint();//wht120516_1  add
    }

    // TODO: Judge which to focus
    HWND hWnd = MApp_ZUI_API_GetFocusCheckpoint();
    if (MApp_ZUI_API_IsWindowVisible(hWnd))
    {
        if (MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_PLAYLIST_GROUP, hWnd) ||
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP, hWnd) ||
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MUSICINFO_INFO_GROUP, hWnd) ||
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP, hWnd) ||
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_TEXTINFO_INFO_GROUP, hWnd) ||
#if (ENABLE_DIVX_PLUS == 1)
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_GROUP,hWnd) ||
#endif
        #if PLAYLIST_BGM
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_BGMINFO_INFO_GROUP, hWnd) ||
        #endif
            MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_INFO_PANE, hWnd) )
        {
            /*if((hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM1)||(hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM2)||
                (hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM3)||(hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM4)||
                (hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM5)||(hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM6)||
                (hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM7)||(hWnd==HWND_DMP_PLAYBACK_INFOBAR_ITEM8))
                {
            MApp_ZUI_API_RestoreFocusCheckpoint();
			}
			else
			{
            MApp_ZUI_API_SetFocus(_hwndListInfoBar[_u8InfoBarIdx%DMP_INFOBAR_ICON_NUM]);
			}*/
			MApp_ZUI_API_RestoreFocusCheckpoint();
		}
		else
		{
            if(MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_PLAYLIST_GROUP, hWnd))
                MApp_ZUI_API_RestoreFocusCheckpoint();
            else
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[_u8InfoBarIdx%DMP_INFOBAR_ICON_NUM]);
        }
    }
    else
    {
        MApp_ZUI_API_SetFocus(_hwndListInfoBar[_u8InfoBarIdx%DMP_INFOBAR_ICON_NUM]);
    }
    //MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFO_PANE);
	//MApp_ZUI_API_RestoreFocusCheckpoint();
}

static void _MApp_ACTdmp_Playback_HideInfoWin(void)
{
    DMP_DBG(printf("_MApp_ACTdmp_Playback_HideInfoWin \n"););
    MApp_ZUI_API_StoreFocusCheckpoint();
    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_HIDE);

    enumMPlayerMediaType enMediaType;
    enMediaType = MApp_MPlayer_QueryCurrentMediaType();
    switch(enMediaType)
    {
#if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
            break;
#endif

#if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_TYPE_MUSIC:
            if(MApp_MPlayer_QueryMusicFilePlayTime() == MApp_MPlayer_QueryMusicFileCurrentTime())
            {
                //MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
                //MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, SW_HIDE);
            }
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
            break;
#endif

#if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_TYPE_MOVIE:
#if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG,SW_SHOW);
#endif
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
            break;
#endif

#if (ENABLE_MPLAYER_TEXT)
        case E_MPLAYER_TYPE_TEXT:
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
#endif
    default:
        break;
    }
	MApp_ZUI_API_MoveWindowByOffset(HWND_DMP_PLAYBACK_SUBTITLE_PAGE,0,0,0,0);
    MApp_ZUI_API_MoveWindowByOffset(HWND_DMP_PLAYBACK_SUBTITLE_TEXT,0,0,0,0);
    return;
}

#if (ENABLE_DIVX_PLUS == 1)
static void _MApp_ACTdmp_Playback_ShowDivxWin(void)
{
    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_GROUP, SW_SHOW);
    HWND hwnd;
    hwnd = MApp_ZUI_API_GetFocus();
    switch(_enDmpDivxStatus)
    {
        case DIVX_MENU:
            _u16DivxTitleIdx = 0;
            _u16DivxEditionIdx = 0;
            _u16DivxChpIdx = 0;
            _u8DivxAutoChpIdx = 0;
            if (MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_WINDOW, hwnd))
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETTITLE);
            }
            else if (MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_WINDOW, hwnd))
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETEDITION);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_WINDOW, hwnd))
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETCHAPTER);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_WINDOW, hwnd))
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETAUTOCHAPTER);
            }
            else
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETTITLE);
            }
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_WINDOW, SW_HIDE);
            break;
        case DIVX_SET_TITLE:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_TITLE_TEXT);
            break;
        case DIVX_SET_EDITION:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_TEXT);
            break;
        case DIVX_SET_CHAPTER:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_TEXT);
            break;
        case DIVX_SET_AUTOCHAPTER:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_WINDOW, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_WINDOW, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_TEXT);
            // 20100322
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_OK,SW_HIDE);
            break;
        default:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_GROUP, SW_HIDE);
            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_DIVX%DMP_INFOBAR_ICON_NUM]);
            break;
    }
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_GROUP);
}
#endif

#if ENABLE_DELETE_SELECTED_FILES
static BOOLEAN _MApp_ACTdmp_File_Delete(void)
{
#if 0
    U16 u16NewIdx = MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY);

    if(MApp_MPlayer_DeleteFile(E_MPLAYER_INDEX_CURRENT_PAGE,
                MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE)) == E_MPLAYER_RET_OK)
    {
//        MApp_MPlayer_DeleteFile(E_MPLAYER_INDEX_CURRENT_PAGE,
//                MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE));
        if(u16NewIdx > (MApp_MPlayer_QueryTotalFileNum()-1))
        {
            MApp_ZUI_API_EnableWindow(_hwndListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE], ENABLE);
            MApp_ZUI_API_EnableWindow(_hwndListFileItem[(MApp_MPlayer_QueryTotalFileNum()-1)%DMP_NUM_OF_FILES_PER_PAGE], DISABLE);
            MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, (MApp_MPlayer_QueryTotalFileNum()-1));
        }
        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
        return TRUE;
    }
    return FALSE;
#else
    if (MApp_MPlayer_BeginDeleteSelectedFiles() == E_MPLAYER_RET_OK)
    {
        _u16CopyDeleteSelectNum = MApp_MPlayer_QueryPlayListFileNum(MApp_MPlayer_QueryCurrentMediaType());
        _u16CopyDeleteFinishNum = 0;
        _MApp_ACTdmp_ShowProgressWin();
        _MApp_ZUI_API_WindowProcOnIdle();
        return TRUE;
    }
    return FALSE;
#endif
}
#endif

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
static BOOLEAN _MApp_ACTdmp_File_Copy(void)
{
#if 0
    //to remember current file name
    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE,
                                MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE),
                                &_stCopyFileInfo);
    MApp_MPlayer_SetCopyFile(E_MPLAYER_INDEX_CURRENT_PAGE,
                               MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE));
    if(MApp_MPlayer_IsCopyFileExist())
    {
        if(!MApp_ZUI_API_IsWindowEnabled(HWND_DMP_FILE_PAGE_SUBMENU_PASTE))
        {
            MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_PASTE, ENABLE);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_PAGE_SUBMENU_GROUP);
        }
        return TRUE;
    }
    return FALSE;
#else
    U16 au16CurDirectoryPath[128];
    if (MApp_MPlayer_GetFullPath(au16CurDirectoryPath, 128) == E_MPLAYER_RET_OK)
    {
        if (MApp_MPlayer_BeginCopySelectedFiles_New(MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx()), &au16CurDirectoryPath[0], FALSE) == TRUE)
        {
            _u16CopyDeleteSelectNum = MApp_MPlayer_QueryPlayListFileNum(MApp_MPlayer_QueryCurrentMediaType());
            _u16CopyDeleteFinishNum = 0;
            _MApp_ACTdmp_ShowProgressWin();
            _MApp_ZUI_API_WindowProcOnIdle();
            return TRUE;
        }
    }
    return FALSE;
#endif
}

static BOOLEAN _MApp_ACTdmp_File_Format(void)
{
    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_FORMATTING);
    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
    _MApp_ZUI_API_WindowProcOnIdle();

    MApp_MPlayer_FormatPartitionByDriveIndex(FORMAT_FAST, MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx()));
    return TRUE;
}
#endif

#if 0
static BOOLEAN _MApp_ACTdmp_Func_PasteFile(void)
{
    U8 u8Filename[FILE_INFO_LONG_FILENAME_SIZE];
    U8 u8NameStr[FILE_INFO_LONG_FILENAME_SIZE];
    U16 u16CaptureIdx = 1;
    U8  u8Len;
    U32 *pu32ptr=NULL;
    memset(u8Filename, 0, FILE_INFO_LONG_FILENAME_SIZE);
    // Truncate long string name

    pu32ptr = (U32*)msAPI_Memory_Allocate(FILE_INFO_LONG_FILENAME_SIZE, BUF_ID_FILEBROWER);
    if(pu32ptr == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    memcpy(pu32ptr, _stCopyFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
    if(FS_strlen_U((U16*)pu32ptr) >= ((FILE_INFO_LONG_FILENAME_SIZE/2)-7))
    {
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-9] = 0x2E; //'.'
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-8] = 0x00;
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-7] = _stCopyFileInfo.u8ExtFileName[0];
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-6] = 0x00;
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-5] = _stCopyFileInfo.u8ExtFileName[1];
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-4] = 0x00;
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-3] = _stCopyFileInfo.u8ExtFileName[2];
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-2] = 0x00;
        _stCopyFileInfo.u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE-1] = 0x00;
    }
    memcpy(u8Filename, _stCopyFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
    memcpy(pu32ptr, u8Filename, FILE_INFO_LONG_FILENAME_SIZE);
    u8Len = FS_strlen_U((U16*)pu32ptr);
    memset(u8NameStr, 0, FILE_INFO_LONG_FILENAME_SIZE);
    u8NameStr[0] = 0x30+(u16CaptureIdx/10);
    u8NameStr[1] = 0x00;
    u8NameStr[2] = 0x30+(u16CaptureIdx++%10);
    u8NameStr[3] = 0x00;
    u8NameStr[4] = 0x5F; // '_'
    u8NameStr[5] = 0x00;
    UnicodeCat((S8*)u8NameStr, (S8*)u8Filename);
     if (u8Len < ((FILE_INFO_LONG_FILENAME_SIZE/2)-3))
    u8Len+=3;   //String cat "xx_".  ex:"01_"
    /*
    if(u8Len<=12)     //Convert short name("filename.txt" 8+1+3) toupper
    {
        U16 i;
        for(i=0;i<u8Len*2;i++)
        {
            if(u8NameStr[i]>='a' && u8NameStr[i]<='z')
            {
                u8NameStr[i]=u8NameStr[i]-32;
            }
        }
    }
    */
    memcpy(pu32ptr, u8NameStr, FILE_INFO_LONG_FILENAME_SIZE);
    if(FS_strlen_U((U16*)pu32ptr) >= ((FILE_INFO_LONG_FILENAME_SIZE/2)-7))
    {
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-9] = 0x2E; //'.'
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-8] = 0x00;
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-7] = _stCopyFileInfo.u8ExtFileName[0];
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-6] = 0x00;
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-5] = _stCopyFileInfo.u8ExtFileName[1];
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-4] = 0x00;
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-3] = _stCopyFileInfo.u8ExtFileName[2];
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-2] = 0x00;
        u8NameStr[FILE_INFO_LONG_FILENAME_SIZE-1] = 0x00;
        memcpy(pu32ptr, u8NameStr, FILE_INFO_LONG_FILENAME_SIZE);
    }
    while(MApp_MPlayer_IsFilenameExistInCurrentDirectory((U16*)pu32ptr, u8Len))
    {
        msAPI_Timer_ResetWDT();
        if(u16CaptureIdx == 99)
        { // maximum captured number
            //sprintf(u8Digit, "_%02d", u16CaptureIdx);
            break;
        }
        u8NameStr[0] = 0x30+(u16CaptureIdx/10);
        u8NameStr[1] = 0x00;
        u8NameStr[2] = 0x30+(u16CaptureIdx++%10);
        u8NameStr[3] = 0x00;
        u8NameStr[4] = 0x5F; // '_'
        u8NameStr[5] = 0x00;
        memcpy(pu32ptr, u8NameStr, FILE_INFO_LONG_FILENAME_SIZE);
    }
    msAPI_Memory_Free(pu32ptr, BUF_ID_FILEBROWER);
    if(MApp_MPlayer_BeginPasteFile(u8NameStr)==E_MPLAYER_RET_OK)
    {
        DMP_DBG(printf("MApp_MPlayer_BeginPasteFile success\n"););
        return TRUE;
    }
    else
    {
        DMP_DBG(printf("MApp_MPlayer_BeginPasteFile fail\n"););
        return FALSE;
    }
}
#endif
#if 0
static BOOLEAN _MApp_ACTdmp_File_Paste(void)
{
    {
        U32 u32UnsuedSize = MApp_MPlayer_QueryUsbDiskUnusedSizeInKB(MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx()));
        // Check disk space first.
        //printf("[USB] Total Size : %ld KB\n", MApp_MPlayer_QueryUsbDiskTotalSizeInKB(g_u8CurrentDriveIdx));
        //printf("[USB] Unused Size : %ld KB\n", u32UnsuedSize);
        //printf("[File] %lu KB\n", _stCopyFileInfo.u32FileSize/1024);
        if(u32UnsuedSize > _stCopyFileInfo.u64FileSize.Lo/1024)
        {
            if(_MApp_ACTdmp_Func_PasteFile())
            {
                _MApp_ACTdmp_ShowProgressWin();
            }
            else
            {// Paste file error!
                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_PASTE_FILE_ERROR);
            }
        }
        else
        {
            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_DISK_FULL);
        }
    }
    return TRUE;
}
#endif
static void _MApp_ACTdmp_HandleUsbStatusChanged(void)
{
    msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

    if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU
        || MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE || MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
    {
        #if ENBALE_PARENTALRATING_MM
        if(MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
        {
            MApp_BlockSys_SetBlockStatus(FALSE);
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_DMP_SetDMPStat(DMP_STATE_INIT);
        }
        #endif
        MApp_DMP_Reset();
        MApp_DMP_SetDmpUiState(DMP_UI_STATE_MEDIA_SELECT);
        if(MApp_DMP_RecalculateDriveMappingTable())
        {
            if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx())) == E_MPLAYER_RET_OK)
            {
                DMP_DBG(printf("[1] connect drive %d OK ^_^\n", (int)MApp_DMP_GetCurDrvIdx()));
                MApp_DMP_SetDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, TRUE);
            }
        }
        else
        {
            MApp_DMP_ClearDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
            MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, FALSE);
        }
        return;
    }
    //Transit UI state to media type select page
    MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);

    /* if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY))
    {
        MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP,SW_HIDE);
    }
	*/
  #if ENABLE_EMBEDDED_PHOTO_DISPLAY
    MApp_MPlayer_StopEmbeddedPhoto();
  #endif

    if(MApp_DMP_RecalculateDriveMappingTable())
    {
        MApp_DMP_Reset();
        if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx())) == E_MPLAYER_RET_OK)
        {
            DMP_DBG(printf("[2] connect drive %d OK ^_^\n", (int)MApp_DMP_GetCurDrvIdx()));
            MApp_DMP_SetDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
            MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, TRUE);
        }
        else
        {
            MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, FALSE);
        }
    }
    else
    {
        if(MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING
            || MApp_DMP_GetDmpFlag() & DMP_FLAG_BGM_MODE)
        {
            MApp_MPlayer_Stop();
            MApp_MPlayer_StopMusic();
        }
        MApp_DMP_ClearDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
        MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
        MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
        MApp_DMP_Reset();
        MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, FALSE);
    }

    // thumbnail
    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
    {
        _MApp_DMP_ThumbCopyRegion_Destroy();
        MApp_MPlayer_LeaveThumbnailMode();
        MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
        MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
    }
    #endif

    #if ENABLE_ZOOM_MAP
    _MApp_ZUI_ACT_DMPCloseZoomMapWin();
    #endif
}
#if (ENABLE_MPLAYER_MOVIE)
static void _MApp_ACTdmp_Change_to_Normal_Play_Icon(void)
    // switch to Normal play anyway, this is the behavior must be followed
{
    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
	IsPause = 1 ;
    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;

    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
}
#endif
void MApp_ZUI_ACT_AppShowDmp(void)
{
    HWND wnd;
    E_OSD_ID osd_id = E_OSD_DMP;
    RECT rect;
    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }
    RECT_SET(rect,
        ZUI_DMP_XSTART, ZUI_DMP_YSTART,
        ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    //To show "Loading..." symbol
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
	//MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_HIDE);
    DMP_DBG(printf("show DMP_MSG_TYPE_LOADING\n"););
    if (DMP_STATE_UI != MApp_DMP_GetDMPStat())
    {
       _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_LOADING);
    }

    //Do not show transition effect to avoid a small block show up before entering MM main page.
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_EXIT, E_ZUI_STATE_RUNNING);
}

S32 MApp_ZUI_ACT_DMPMarqueeTextWinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_MARQUEE_VARDATA * pData =
        (GUI_DATA_MARQUEE_VARDATA*)MApp_ZUI_API_GetWindowData(hWnd);
    switch(pMsg->message)
    {
        case MSG_TIMER:
            if (pData)
            {
                if (pData->u8ShowStartPosition == 0)
                    MApp_ZUI_API_SetTimer(hWnd, pMsg->wParam, DMP_MARQUEE_ANIMATION_INTERVAL_MS);
                pData->u8ShowStartPosition++;
                MApp_ZUI_API_InvalidateWindow(hWnd);
            }
            return 0;

        case MSG_PAINT:
            {
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;
                DRAWSTYLE_TYPE ds_type = DS_NORMAL;

                if (param->bIsDisable)
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hWnd);
                    ds_type = DS_DISABLE;
                }
                else if (param->bIsFocus) //the same focus group
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
                    ds_type = DS_FOCUS;
                }
                else
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hWnd);
                }

                _MApp_ZUI_API_DefaultOnPaint(hWnd, param, FALSE);
                {
                    U16 u16TxtComponentIndex = _MApp_ZUI_API_FindFirstComponentIndex(hWnd, ds_type, CP_TEXT_OUT);
                    LPTSTR pStr = MApp_ZUI_ACT_GetDynamicText(hWnd);
                    if (u16TxtComponentIndex != 0xFFFF && pStr)
                    {
                        DRAW_TEXT_OUT_DYNAMIC dyna;

                        _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TxtComponentIndex, &dyna);
                        dyna.pString = pStr;
                        dyna.TextColor = MApp_ZUI_ACT_GetDynamicColor(hWnd, ds_type, dyna.TextColor);

                        //marquee animation:
                        // different here!!

                        if (/*ds_type == DS_FOCUS &&*/ pData != NULL &&
                            pData->u8ShowStartPosition != 0xFF)
                        {
                            if (pData->u8ShowStartPosition >= MApp_ZUI_API_Strlen(pStr))
                            {
                                pData->u8ShowStartPosition = 0xFF;
                                MApp_ZUI_API_KillTimer(hWnd, 0);
                            }
                            else if (pData->u8ShowStartPosition == 0)
                            {
                                U16 width;
                                clrBtn1.Fontfmt.flag = dyna.flag;
                                clrBtn1.Fontfmt.ifont_gap = dyna.u8dis;
                                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;
                                width = msAPI_OSD_GetStrWidth(Font[dyna.eSystemFont].fHandle, (U8*)pStr, &clrBtn1);
                                //note: add border for a little truncate case..
                                if (width+BTN_TEXT_GAP*2 <= param->rect->width)
                                {
                                    pData->u8ShowStartPosition = 0xFF;
                                    MApp_ZUI_API_KillTimer(hWnd, 0);
                                }
                            }
                            else
                            {
                                dyna.eTextAttrib = eTextAlignLeft;
                                dyna.pString += pData->u8ShowStartPosition;
                                dyna.u8dots = 0; //note: don't show dots for animation..
                            }
                        }
                        else
                        {
                            //note: pData may be shared with others, so don't clear them
                            //      but we need to stop the timer if animation still going
                            MApp_ZUI_API_KillTimer(hWnd, 0);
                        }

                        _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, &dyna, &param->dc, param->rect);
                    }

                }

            }
            return 0;

            default:
                break;
    }

    return DEFAULTWINPROC(hWnd, pMsg);
}

///////////////////////////////////////////////////////////////
// methods


S32 MApp_ZUI_ACT_DMPVolumeWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            MApp_ZUI_API_KillTimer(HWND_DMP_VOLUME_LIST, DMP_VOLUME_TIMER);
            MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_LIST, SW_HIDE);
        //    MApp_ZUI_API_RestoreFocusCheckpoint();
        break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_DMPKeystoneWinProc(HWND hwnd, PMSG msg)    //xzm @20171228 for timeout keystone
{
    switch(msg->message)
    {
        case MSG_TIMER:
            MApp_ZUI_API_KillTimer(HWND_DMP_KEYSTONE_LIST, DMP_VOLUME_TIMER);
            MApp_ZUI_API_ShowWindow(HWND_DMP_KEYSTONE_LIST, SW_HIDE);
        //    MApp_ZUI_API_RestoreFocusCheckpoint();
        break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_DMPUartWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            MApp_ZUI_API_KillTimer(HWND_DMP_BAR_TRANS, DMP_UART_TIMER);
            MApp_ZUI_API_ShowWindow(HWND_DMP_BAR_TRANS, SW_HIDE);
            MApp_ZUI_API_SetFocus(hwnd_before);//resolve mantis:0330741 can't exit mm through key vk_exit after uart menu auto close


        break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}
//////////////////////////////////////////////////////////
// Key Handler
BOOLEAN MApp_ZUI_ACT_HandleDmpKey(VIRTUAL_KEY_CODE key)
{
#if ENABLE_DMP_MINI_MENU
    if(MApp_MPlayer_IsMoviePlaying())
    {
        MApp_DMP_GotoDMPMiniMenu();
    }
    else
#endif
    {
    //Deal with DMP hotkeys here.
    switch(key)
    {
#if (ENABLE_DIVX_PLUS == 1)
        case VK_NUM_0:
        case VK_NUM_1:
        case VK_NUM_2:
        case VK_NUM_3:
        case VK_NUM_4:
        case VK_NUM_5:
        case VK_NUM_6:
        case VK_NUM_7:
        case VK_NUM_8:
        case VK_NUM_9:
        {
            if (_enDmpDivxStatus == DIVX_SET_AUTOCHAPTER)
            {
                VIRTUAL_KEY_CODE i = key - VK_NUM_0;
                _u8DivxAutoChpIdx = i; // 0~9
                _MApp_ACTdmp_MovieCancelRepeatAB();
                MApp_MPlayer_MovieChangeAutoGenChapter(_u8DivxAutoChpIdx);
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_TEXT);
            }
        }
        break;
#endif
#if ENABLE_ATSC_TTS
        case VK_EXIT:
            MApp_TTS_Cus_Say_exit();
        break;
#endif

        case VK_PREVIOUS:
            DMP_DBG(printf("hotkey VK_PREVIOUS\n"););
#if ENABLE_ATSC_TTS
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Prev), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Prev)));
            MApp_TTSControlSetOn(TRUE);
#endif
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MusicInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MusicInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM4);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM4);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MUSICINFO_PREV);
                        break;
                        #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MovieInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MovieInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM4);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM4);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                    #if ENABLE_DRM
                        if (msAPI_Timer_DiffTimeFromNow(u32PrevButtonTimer) > DMP_TIME_MS_PREV_BUTTON_CLICK_WIN)
                        {
                            MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV);
                        }
                        else
                        {
                            MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV);
                            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PREV_BUTTON_CLICK_WIN);
                        }
                        u32PrevButtonTimer = msAPI_Timer_GetTime0();
                     #else
                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV);
                     #endif
                        break;
                     #endif
                    case E_MPLAYER_TYPE_PHOTO:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8PhotoInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8PhotoInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM2);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM2);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_PHOTOINFO_PREV);
                        break;
                       #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                        //MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_PREVFILE);
                        break;
                       #endif
                    default:
                        break;
                }
            }
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW))
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_PREVFILE);
            }
            return TRUE;
		 /*case VK_DISPLAY:
         DMP_DBG(printf("hotkey VK_DISPLAY\n"););
	     if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT) //add by gchen @ 20110719
	     {
		  _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_BUTTON);
		  MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
		  return TRUE;
	     }

	     if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_PLAYING_STAGE) //add by gchen @ 20110719
	     {
	  	  switch(MApp_MPlayer_QueryCurrentMediaType())
	  	  {
			case E_MPLAYER_TYPE_MUSIC:
			case E_MPLAYER_TYPE_TEXT:
			  _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_BUTTON); 
			  MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
		  	  break;

			default:
			  break;
	  	  }
	     }
		 
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))					
	     {
		     switch(MApp_MPlayer_QueryCurrentMediaType())
		     	{
				case E_MPLAYER_TYPE_MOVIE:	
					{
						bDisplayFlag = TRUE; //wht120713_2
						utempCount= 0;
						MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_DISPLAY_FILE_INFO_OPEN);
				 	}
					break;

				case E_MPLAYER_TYPE_PHOTO:
					{
						bDisplayFlag = TRUE; ////wht120713_2
						utempCount= 0;
						MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_DISPLAY_FILE_INFO_OPEN);
					}
					break;

				default:
					{
					}
					break;
			}
	     	}
            return TRUE;*/
        case VK_NEXT:
            DMP_DBG(printf("hotkey VK_NEXT\n"););
#if ENABLE_ATSC_TTS
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Next), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Next)));
            MApp_TTSControlSetOn(TRUE);
#endif
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MusicInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MusicInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM5);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM5);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MUSICINFO_NEXT);
                        break;
                        #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MovieInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MovieInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM5);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM5);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_NEXT);
                        break;
                        #endif
                    case E_MPLAYER_TYPE_PHOTO:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8PhotoInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8PhotoInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM3);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM3);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_PHOTOINFO_NEXT);
                        break;
                        #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                        //MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXTFILE);
                        break;
                       #endif
                    default:
                        break;
                }
            }
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW))
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXTFILE);
            }
            return TRUE;
        case VK_STOP:
            DMP_DBG(printf("hotkey VK_STOP\n"););
#if ENABLE_ATSC_TTS
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Stop), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Stop)));
            MApp_TTSControlSetOn(TRUE);
#endif
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MusicInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MusicInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM6);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM6);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MUSICINFO_STOP);
                        break;
                        #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MovieInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MovieInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM6);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM6);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                #if ENABLE_DRM
                    #if ENABLE_RESUME_STOP
                        if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_RESUME_STOP_WINDOW))
                            MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_RESUMESTOP_YES);
                        else
                    #endif
                #endif
                            MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_STOP);
                        break;
                        #endif
                    case E_MPLAYER_TYPE_PHOTO:
                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8PhotoInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8PhotoInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM4);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM4);
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_PHOTOINFO_STOP);
                        break;
                        #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                        //MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_STOP);
                        break;
                        #endif
                    default:
                        break;
                }
            }
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW))
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_STOP);
            }
			
			if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
			MApp_ZUI_API_RestoreFocusCheckpoint();
			
            return TRUE;
        case VK_PLAY:
#if ENABLE_ATSC_TTS
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Play), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Play)));
            MApp_TTSControlSetOn(TRUE);
#endif		
			printf("hotkey VK_PLAY \n");
            //DMP_DBG(printf("hotkey VK_PLAY \n"););
            //MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_INFOBAR_GROUP,TRUE);
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                    {
                        if(MApp_MPlayer_QueryMusicPlayMode() == E_MPLAYER_MUSIC_NORMAL)
                        {
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_PAUSE);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            //MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
                            //MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        }
                        else // some FF FB ...
                        {
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;    IsPause = 1 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                            /* if(!MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY))
                            {
                               MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                            }  */
                        }

                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MusicInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MusicInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                             MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                        }

                    }
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                    {
                        enumMPlayerMoviePlayMode eMoviePlayMode = MApp_MPlayer_QueryMoviePlayMode();
                        if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
                        {
                           MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN, DMP_TIME_MS_MOVIERESUME);
                        }
                        if(eMoviePlayMode == E_MPLAYER_MOVIE_STOP)
                        {
                            break;
                        }
                       if(eMoviePlayMode == E_MPLAYER_MOVIE_NORMAL)
                        {
                            MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                        }
                        else
                        {

                            if(E_MPLAYER_RET_OK != MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL))
                            {
                                break;
                            }
                            if (MApi_GOP_GWIN_GetMaxGOPNum()!=1)
                            {
                                _MApp_ZUI_ACTdmp_OperateSubtitle();
                            }
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);

                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MovieInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8MovieInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                            // MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                             MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                        }
                        else
                        {
                           // MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                        }

                    }
                    break;
                    #endif
                    case E_MPLAYER_TYPE_PHOTO:
                    {

                        if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                        {
                            MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_NORMAL);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE; IsPause = 1 ;
                            DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                        {
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        }

                        if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                        {
                            if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8PhotoInfoBarMax)
                            {
                                S32 i;
                                for (i = DMP_INFOBAR_ICON_NUM; i > u8PhotoInfoBarMax -_u8InfoBarIdx; i--)
                                {
                                    MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                }
                            }
                            _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                             //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                             MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                        }
                        else
                        {
                            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                        }

                    }
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                         break;
                    #endif
                    default:
                        break;
                }
				
				if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
					MApp_ZUI_API_RestoreFocusCheckpoint();
                return TRUE;
            }
			if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
				MApp_ZUI_API_RestoreFocusCheckpoint();
            return FALSE;
        case VK_PAUSE:
			msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, 0, 0); //@xzm for exit audio
            DMP_DBG(printf("hotkey VK_PAUSE \n"););
#if ENABLE_ATSC_TTS
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Pause), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Pause)));
            MApp_TTSControlSetOn(TRUE);
#endif
            /*if (MApp_ZUI_API_IsSuccessor(HWND_DMP_PLAYBACK_PLAYLIST_GROUP, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_GROUP, SW_HIDE);
            }*/
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
#if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    U8 ret;

                    if (!MApp_VDPlayer_DVD_IsAllowed(E_MPLAYER_DVD_CMD_PLAY_PAUSE))
                    {
                        return TRUE;
                    }

                    ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_PLAY_PAUSE);
                }
#endif

                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        {
                            switch(MApp_MPlayer_QueryMusicPlayMode())
                            {
                                case E_MPLAYER_MUSIC_STOP:
                                case E_MPLAYER_MUSIC_PAUSE:
                                    //do nothing
                                    break;
                                default:
                                    //normal, FF, FB
                                    MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_PAUSE);
                                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                    break;
                            }
                            if(MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY))
                            {
                                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
                            }

                            if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                            {
                                if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MusicInfoBarMax)
                                {
                                    S32 i;
                                    for (i = DMP_INFOBAR_ICON_NUM; i > u8MusicInfoBarMax -_u8InfoBarIdx; i--)
                                    {
                                        MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                    }
                                }
                                _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                                 MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                            }
                            else
                            {
                                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                            }

                        }
                        break;
                        #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        {
                            enumMPlayerMoviePlayMode eMoviePlayMode = MApp_MPlayer_QueryMoviePlayMode();
                            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
                            {
                               MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN, DMP_TIME_MS_MOVIERESUME);
                            }
                            if(eMoviePlayMode == E_MPLAYER_MOVIE_STOP)
                            {
                                break;
                            }
                            if((eMoviePlayMode != E_MPLAYER_MOVIE_PAUSE) &&
                               (eMoviePlayMode != E_MPLAYER_MOVIE_STEP) )
                            {
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
                                DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            }
                            else
                            {
                                //do nothing
                            }

                            if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                            {
                                if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8MovieInfoBarMax)
                                {
                                    S32 i;
                                    for (i = DMP_INFOBAR_ICON_NUM; i > u8MovieInfoBarMax -_u8InfoBarIdx; i--)
                                    {
                                        MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                    }
                                }
                                _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                                 //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                                 MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                            }
                            else
                            {
                                //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                            }

                        }
                        break;
                        #endif
                    case E_MPLAYER_TYPE_PHOTO:
                        {
                            if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                            {
                                // do nothing
                            }
                            else if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                            {
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            }

                            if (_u8InfoBarIdx >= DMP_INFOBAR_ICON_NUM)
                            {
                                if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8PhotoInfoBarMax)
                                {
                                    S32 i;
                                    for (i = DMP_INFOBAR_ICON_NUM; i > u8PhotoInfoBarMax -_u8InfoBarIdx; i--)
                                    {
                                        MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                                    }
                                }
                                _u8InfoBarIdx-= DMP_INFOBAR_ICON_NUM;
                                 MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                            }
                            else
                            {
                                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
                            }

                        }
                        break;
                        #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                        break;
                        #endif
                    default:
                        break;
                }
				if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
					MApp_ZUI_API_RestoreFocusCheckpoint();
				
				msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);//@xzm for exit audio
                return TRUE;
            }
			if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
				MApp_ZUI_API_RestoreFocusCheckpoint();
				
			msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);//@xzm for exit audio
            return FALSE;
        case VK_REWIND:
            DMP_DBG(printf("hotkey VK_FF\n"););
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MUSICINFO_FF);
                        break;
                    case E_MPLAYER_TYPE_MOVIE:
                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_FF);
                        break;
                    case E_MPLAYER_TYPE_TEXT:
                        break;
                    default:
                        break;
                }
            }
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW))
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXT);
            }
            return TRUE;
        case VK_FF:
            DMP_DBG(printf("hotkey VK_REWIND\n"););
            if(MApp_MPlayer_IsMediaFileInPlaying() && (MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MUSICINFO_FB);
                        break;
                    case E_MPLAYER_TYPE_MOVIE:
                        MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_FB);
                        break;
                    case E_MPLAYER_TYPE_TEXT:
                        break;
                    default:
                        break;
                }
            }
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW))
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_PREV);
            }
            return TRUE;
        case VK_AUDIO: // movie audio track test
            DMP_DBG(printf("VK_AUDIO\n"););
            #if (ENABLE_MPLAYER_MOVIE)
            if( MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE
                && MApp_MPlayer_IsMoviePlaying())
            {
#if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    U8 ret;

                    DMP_DBG(printf("VK_AUDIO in DVD\n"));
                    ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_LANGUAGE);

                    return TRUE;
                }
                else
#endif  // ENABLE_DVD
                {
                    U16 u16TotalTrk = MApp_MPlayer_QueryMovieAudioChannelNum();
                    if (u16TotalTrk != MPLAYER_INVALID_INDEX && u16TotalTrk != 0)
                    {
                        U16 u16TrkID = MApp_MPlayer_QueryMovieCurAudioTrackIdx();
                        u16TrkID = (u16TrkID+1)%u16TotalTrk;
                        if(MApp_MPlayer_MovieChangeAudioTrack(u16TrkID) != E_MPLAYER_RET_OK)
                        {
                            DMP_DBG(printf("MApp_MPlayer_MovieChangeProgram fail\n"););
                        }
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_AUDIOTRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    }
                    else
                    {
                        DMP_DBG(printf("MApp_MPlayer_QueryMovieAudioChannelNum fail or 0\n"););
                    }
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT);
                }
            }
            #endif
            return TRUE;
        case VK_CHANNEL_MINUS:
        case VK_CHANNEL_PLUS:// movie program test
            DMP_DBG(printf("VK_CHANNEL_PLUS or VK_CHANNEL_MINUS\n"););
            #if (ENABLE_MPLAYER_MOVIE)
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalPgm = MApp_MPlayer_QueryMovieProgramNum();
                if (u16TotalPgm != MPLAYER_INVALID_INDEX && u16TotalPgm != 0)
                {
                    U16 u16PgmIdx = MApp_MPlayer_QueryMovieCurProgramIdx();
                    if(key == VK_CHANNEL_PLUS)
                    {
                        if( u16PgmIdx < u16TotalPgm -1)
                        {
                            DMP_DBG(printf("channel++\n"););
                            u16PgmIdx++;
                            if (MApp_MPlayer_MovieChangeProgram(u16PgmIdx) == E_MPLAYER_RET_OK)
                            {
                                _MApp_ACTdmp_MovieCancelRepeatAB();
                                _MApp_ACTdmp_Change_to_Normal_Play_Icon();
                            }
                            else
                            {
                                DMP_DBG(printf("channel++ fail\n"););
                            }
                        }
                    }
                    else  // VK_CHANNEL_MINUS
                    {
                        if(u16PgmIdx > 0)
                        {
                            DMP_DBG(printf("channel--\n"););
                            u16PgmIdx--;
                            if (MApp_MPlayer_MovieChangeProgram(u16PgmIdx) == E_MPLAYER_RET_OK)
                            {
                                _MApp_ACTdmp_MovieCancelRepeatAB();
                                _MApp_ACTdmp_Change_to_Normal_Play_Icon();
                            }
                            else
                            {
                                DMP_DBG(printf("channel-- fail\n"););
                            }
                        }
                    }
                }
                else
                {
                    DMP_DBG(printf("MApp_MPlayer_QueryMovieProgramNum fail or 0\n"););
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT);
            }
            #endif
            return TRUE;

        case VK_POWER:
            {
            // care
                MApp_DMP_SetDMPStat(DMP_STATE_GOTO_STANDBY);
            #if 0//def ATSC_SYSTEM
                if(MApp_MPlayer_IsMediaFileInPlaying())
                {
                    MApp_MPlayer_Stop();
                    MApp_MPlayer_StopMusic();
                }
                MApp_MPlayer_ExitMediaPlayer();
                //MApp_ZUI_API_ShowWindow(HWND_MAINFRAME,SW_HIDE);
                MApp_ZUI_ACT_TerminateDmp();
             #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                _MApp_DMP_ThumbCopyRegion_Destroy();
             #endif
            #else
                MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            #endif
                return TRUE;
            }
            break;


        case VK_HOME:
                hwnd_before = MApp_ZUI_API_GetFocus();
                MApp_ZUI_API_ShowWindow(HWND_DMP_BAR_TRANS, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_BAR);
                MApp_ZUI_API_SetTimer(HWND_DMP_BAR_TRANS, DMP_UART_TIMER, UART_DEBUG_TIME_OUT_MS);
            return TRUE;


        case VK_VOLUME_PLUS:
        case VK_VOLUME_MINUS:
        {
            printf("VK_VOLUME_PLUS MINUS\n");
			MApp_ZUI_API_ShowWindow(HWND_DMP_KEYSTONE_LIST, SW_HIDE);     //xzm @20171228 for keystone
			MApp_ZUI_API_KillTimer(HWND_DMP_KEYSTONE_LIST, DMP_KEYSTONE_TIMER);
            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                return TRUE;
            }

            if (MApp_ZUI_API_IsSuccessor(HWND_DMP_VOLUME_LIST, MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_API_ResetTimer(HWND_DMP_VOLUME_LIST, DMP_VOLUME_TIMER);
            }
            else
            {
                //MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_SetTimer(HWND_DMP_VOLUME_LIST, DMP_VOLUME_TIMER, AUDIO_VOLUME_TIME_OUT_MS);
            }


        #if(ENABLE_CEC)
            if( MApp_CEC_ARC_Is_ExtAudioDeviceConnected() )
          /*#if(CEC_VERSION_USING == CEC_NEW_VERSION)
            if (msAPI_CEC_IsAudioSystemKeyValid() == TRUE)
          #else
            if (msAPI_CEC_ARC_Is_Connect() == TRUE)
          #endif */
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_POWER_AMPLIFIER, SW_SHOW);
                if (msAPI_CEC_ARC_GetARCAudioVolume()>0)  //anvi22
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_CONFIG_PANE, SW_SHOW);
                    MApp_UiMenu_MuteWin_Hide();
                    MApp_UiMenu_ARCDeviceStatusWin_Hide();
                    //MApp_ZUI_API_SetFocus(HWND_DMP_VOLUME_CONFIG_BAR);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_VOLUME_CONFIG_PANE);
                }
                else
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_VOLUME_LIST, DMP_VOLUME_TIMER);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_CONFIG_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_POWER_AMPLIFIER, SW_HIDE);
                    MApp_UiMenu_MuteWin_Show();
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_VOLUME_LIST);
                    //MApp_ZUI_API_RestoreFocusCheckpoint();
                }
            }
            else
        #endif
            {
                if(key == VK_VOLUME_PLUS)
                {
                    if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
                    {
                        stGenSetting.g_SoundSetting.Volume+= 5;
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
                    }
                }
                else
                {
                    if( stGenSetting.g_SoundSetting.Volume > 0 )
                    {
                        stGenSetting.g_SoundSetting.Volume-= 5;
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
                    }
                }
                #if ENABLE_KEY_TO_SPEECH
                if(!MApp_KeyIsReapeatStatus())
                {
                    if(key == VK_VOLUME_PLUS)
                        MApp_KTS_Say(EN_KTS_VOLUME_UP);
                    else
                        MApp_KTS_Say(EN_KTS_VOLUME_DOWN);
                }
                #endif

              #if ENABLE_ATSC_TTS
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_Volume);
                MApp_TTS_Cus_Add_Str_By_HWndID(HWND_DMP_VOLUME_CONFIG_TEXT, EN_TTS_SPEAK_NUMBER_CARDINAL);
                MApp_TTSControlSetOn(TRUE);
              #endif

                if(stGenSetting.g_SoundSetting.Volume == 0)
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                else
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    //MUTE_Off();
                    MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
                }

                MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_POWER_AMPLIFIER, SW_HIDE);

                if(stGenSetting.g_SoundSetting.Volume>0)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_CONFIG_PANE, SW_SHOW);
                    MApp_UiMenu_MuteWin_Hide();
                    MApp_UiMenu_ARCDeviceStatusWin_Hide();
                    //MApp_ZUI_API_SetFocus(HWND_DMP_VOLUME_CONFIG_BAR);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_VOLUME_CONFIG_PANE);
                }
                else
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_VOLUME_LIST, DMP_VOLUME_TIMER);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_CONFIG_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_POWER_AMPLIFIER, SW_HIDE);
                    MApp_UiMenu_MuteWin_Show();
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_VOLUME_LIST);
                    //MApp_ZUI_API_RestoreFocusCheckpoint();
                }
            }

            break;
        }

		case VK_KEYSTONE_PLUS:      //xzm @ 20171227  for keystone
		case VK_KEYSTONE_MINUS:
		
            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                return TRUE;
            }

            if (MApp_ZUI_API_IsSuccessor(HWND_DMP_KEYSTONE_LIST, MApp_ZUI_API_GetFocus()))
            {
				printf("MApp_ZUI_API_ResetTimer\n");
                MApp_ZUI_API_ResetTimer(HWND_DMP_KEYSTONE_LIST, DMP_KEYSTONE_TIMER);
            }
            else
            {
				printf("MApp_ZUI_API_SetTimer\n");
                //MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_SetTimer(HWND_DMP_KEYSTONE_LIST, DMP_KEYSTONE_TIMER, AUDIO_KEYSTONE_TIME_OUT_MS);
            }
			
			
			MApp_ZUI_API_ShowWindow(HWND_DMP_KEYSTONE_LIST, SW_SHOW);
			
			if(key == VK_KEYSTONE_PLUS){
				printf("ACTdmp VK_KEYSTONE_PLUS\n");
				stGenSetting.g_SysSetting.KeyStoneValue++;
				if(stGenSetting.g_SysSetting.KeyStoneValue >= 38)
				stGenSetting.g_SysSetting.KeyStoneValue=38;
				 printf("ks2=%d",stGenSetting.g_SysSetting.KeyStoneValue);
				 keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			}else{
				printf("ACTdmp VK_KEYSTONE_MINUS\n");
				stGenSetting.g_SysSetting.KeyStoneValue--;
				if(stGenSetting.g_SysSetting.KeyStoneValue <=-38)
				stGenSetting.g_SysSetting.KeyStoneValue=-38;
				printf("ks1=%d",stGenSetting.g_SysSetting.KeyStoneValue);
				keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			}
			break;

        case VK_MENU:
        {
        #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PROGRESS_WINDOW))
                return TRUE;

            if (m_bCopyOn == TRUE)
            {
                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_PRESS_RED_BUTTON_PASTE);
                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                return TRUE;
            }
        #endif

            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                return TRUE;
            }

            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                MApp_ZUI_API_StoreFocusCheckpoint();

        #if 1//ndef ATSC_SYSTEM
            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_BAR))
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_BAR, SW_HIDE);
                MApp_ZUI_API_SetFocus(hwnd_before);
            }
            else
            {
        #endif
                if (MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
                {
                    //_MApp_ACTdmp_HidePreviewWin();
                    //MApp_MPlayer_StopPreview();
                }
              #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                {
                    _MApp_DMP_ThumbCopyRegion_Destroy();
                    MApp_MPlayer_LeaveThumbnailMode();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
                }
              #endif
              #if ENABLE_ZOOM_MAP
                _MApp_ZUI_ACT_DMPCloseZoomMapWin();
              #endif

            #if EN_DMP_SEARCH_ALL
              #if PLAYLIST_BGM
               if (MApp_DMP_GetDmpUiState() == DMP_UI_STATE_BGM_FILE_SELECT)
               {
                   printf("Go to DMP_UI_STATE_BGM_DRIVE_SELECT menu \n ");
                   MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
                   return TRUE;
               }
              #endif
                if (MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
                {
                    printf("Go to DMP_UI_STATE_MEDIA_SELECT menu \n ");
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
                    return TRUE;
                }
            #endif

                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_DMP_GotoMainMenu();

        #if 1//ndef ATSC_SYSTEM
            }
        #endif

            return TRUE;
        }


        case VK_INPUT_SOURCE:
            {
#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PROGRESS_WINDOW))
                    return TRUE;

                if (m_bCopyOn == TRUE)
                {
                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_PRESS_RED_BUTTON_PASTE);
                    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                    return TRUE;
                }
#endif
                if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
                {
                    return TRUE;
                }

                if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                    MApp_ZUI_API_StoreFocusCheckpoint();
                if (MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
                {
                    //_MApp_ACTdmp_HidePreviewWin();
                    //MApp_MPlayer_StopPreview();
                }
                #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                {
                    _MApp_DMP_ThumbCopyRegion_Destroy();
                    MApp_MPlayer_LeaveThumbnailMode();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
                }
                #endif
                #if ENABLE_ZOOM_MAP
                _MApp_ZUI_ACT_DMPCloseZoomMapWin();
                #endif
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_DMP_GotoInputSrcMenu();
                #if ENABLE_KEY_TO_SPEECH
                MApp_KTS_Say(EN_KTS_SOURCE);
                #endif
            }
            return TRUE;
        case VK_MUTE:
            {
                DMP_DBG(printf("hot key mute\n"););

                if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
                {
                    return TRUE;
                }

                MApp_KeyProc_Mute();
            }
            return TRUE;
#if 0
		 case VK_TEMP_DET: //add by gchen @ 20111006 //bat low warning
		     {
				 u8KeyCode = KEY_NULL;
				 MApp_UiMenu_TempDetWin_Show();
		     }
		     return TRUE;
#endif
	 case VK_BAT_LOW: //wht141014_8
	     {
	        printf("DMP DMP DMP VK_BAT_LOW\n\n\n");
			u8KeyCode = KEY_NULL;
			MApp_UiMenu_BatLowWin_Show();
	     }
	     return TRUE;
        /*
        case VK_BLUE:
            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
            return TRUE;
        */
    #if ENABLE_DVD
        case VK_BLUE:
            DMP_DBG(printf("VK_BLUE\n"));

            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                U8 ret;

                DMP_DBG(printf("VK_BLUE in DVD\n"));
                ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_TITLE);
            }
            return TRUE;
        case VK_RED:
            DMP_DBG(printf("VK_RED\n"));
            return TRUE;
    #endif  // ENABLE_DVD

        case VK_SUBTITLE:
            DMP_DBG(printf("hot VK_SUBTITLE\n"););
            {
                MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT_R);
            }
            break;

    #if ENABLE_DVD
        case VK_LEFT:
        case VK_RIGHT:
        case VK_UP:
        case VK_DOWN:
            if(MApp_MPlayer_IsMediaFileInPlaying() &&
                (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
            {
                if ((MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_TRANSPARENT_BG) &&
                    (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD))
                {
                    U8 ret;

                    switch(key)
                    {
                        case VK_LEFT:
                            DMP_DBG(printf("VK_LEFT in DVD\n"));
                            ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_LEFT);
                            break;
                        case VK_RIGHT:
                            DMP_DBG(printf("VK_RIGHT in DVD\n"));
                            ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_RIGHT);
                            break;
                        case VK_UP:
                            DMP_DBG(printf("VK_UP in DVD\n"));
                            ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_KEYUP);
                            break;
                        case VK_DOWN:
                            DMP_DBG(printf("VK_DOWN in DVD\n"));
                            ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_DOWN);
                            break;
                        default:
                            break;
                    }

                    return TRUE;
                }
            }
            break;
    #endif  // ENABLE_DVD

        case VK_ZOOM:
            #if ENABLE_PIP
            if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
               break;
            }
            #endif
            DMP_DBG(printf("hot VK_ZOOM\n"););

          #if ENABLE_3D_PROCESS
                if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
          #endif
            {
                MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_MOVIEINFO_ASPECT_RATIO);
            }
            break;
        #if ENABLE_PIP
        case VK_PICTURE:
            if(IsPIPSupported())
            {
                U8 u8PipModeCount = 0;
                EN_PIP_MODE enPIPMode = stGenSetting.g_stPipSetting.enPipMode;

                 u8PipModeCount = 0;
                 do
                 {
                    enPIPMode=(EN_PIP_MODE) MApp_ZUI_ACT_DecIncValue_Cycle(
                                    TRUE,enPIPMode, EN_PIP_MODE_OFF, EN_PIP_MODE_MAX, 1);
                    u8PipModeCount ++ ;
                }
                while((!MApp_Check_PIPMode_Supported(enPIPMode)) ||u8PipModeCount <= (EN_PIP_MODE_MAX+1));

                MApp_Set_PIPMode(enPIPMode,NULL,NULL);
                return TRUE;
            }
        #endif
#if 1 //smc.chy 2010/10/12 for use up down key to swicth page in text mode
        case VK_LEFT:
        case VK_RIGHT:
        case VK_UP:
        case VK_DOWN:
            if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_TEXT
                && MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW)) //&&MApp_MPlayer_IsMediaFileInPlaying() )
            {     
                    if (HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW != MApp_ZUI_API_GetFocus()) // if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_TEXTINFO_INFO_GROUP))
                    {
                        break;
                    }
                    else
                    {
                        switch(key)
                        {
                            case VK_LEFT:
                                {
                                    MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_PREVFILE);
                                }
                                break;
                            case VK_RIGHT:
                                {
                                    MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXTFILE);
                                }
                                break;
                            case VK_UP:
                                {
                                    MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_PREV);
                                }
                                break;
                            case VK_DOWN:
                                {
                                    MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXT);
                                }
                                break;
                            default:
                                break;
                        }

                        return TRUE;
                    }
            }
            break;
    #endif  // ENABLE_DVD

        default:
            break;
    }
    }
    return FALSE;
}
void MApp_ZUI_ACT_TerminateDmp(void)
{
    ZUI_MSG(printf("[]term:mplayer\n");)
    //enMediaPlayerState = _enTargetMediaPlayerState;
}

EN_MPLAYER_FORCE_STOP_RESULT  MApp_MplayerForceStop_UserExit(EN_MPLAYER_FORCE_STOP eType) // jimmy.wang
{
    if (E_MPLAYER_FORCE_STOP_INIT == eType)
    {
        MApp_ProcessUserInput();
        if ( u8KeyCode == KEY_EXIT && !MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
        {
            return (EN_MPLAYER_FORCE_STOP_RESULT)E_VDPLAYER_USER_EXIT;
        }
    }
    return (EN_MPLAYER_FORCE_STOP_RESULT)E_MPLAYER_CONTINUE_PLAYING;
}

/*U8 _MApp_ZUI_ACT_Get_InfoBarMax(void)
{
#if (ENABLE_MPLAYER_MOVIE)
    BUILD_ERROR_IF_TRUE( (MOVIEINFO_NUM != (sizeof(DMP_MovieInfoBarTable)/12)) );
#endif
#if (ENABLE_MPLAYER_PHOTO)
    BUILD_ERROR_IF_TRUE( (PHOTOINFO_NUM != (sizeof(DMP_PhotoInfoBarTable)/12)) );
#endif
#if (ENABLE_MPLAYER_MUSIC)
    BUILD_ERROR_IF_TRUE( (MUSICINFO_NUM != (sizeof(DMP_MusicInfoBarTable)/12)) );
#endif

    U8 u8InfoBarMax = 0;

    switch( MApp_MPlayer_QueryCurrentMediaType() )
    {
    #if (ENABLE_MPLAYER_MOVIE)
        case E_MPLAYER_TYPE_MOVIE:
            u8InfoBarMax = u8MovieInfoBarMax;
            break;
    #endif

        case E_MPLAYER_TYPE_MUSIC:
            u8InfoBarMax = u8MusicInfoBarMax;
            break;

    #if (ENABLE_MPLAYER_PHOTO)
        case E_MPLAYER_TYPE_PHOTO:
            u8InfoBarMax = u8PhotoInfoBarMax;
            break;
    #endif

      #if (ENABLE_MPLAYER_TEXT)
        case E_MPLAYER_TYPE_TEXT:
            u8InfoBarMax = u8TextInfoBarMax;
            break;
      #endif

        default:
            break;
    }

    return u8InfoBarMax;
}*/

BOOLEAN MApp_ZUI_ACT_ExecuteDmpAction(U16 act)
{
	printf("\r\nUSB SWITCH = %d \n",act);
	printf("\r\nUSB SWITCH = %d",EN_EXE_DMP_MEDIA_USB_SWITCH);
    switch(act)
    {
    #ifndef ATSC_SYSTEM
        case EN_EXE_DEC_UART_MODE:
        case EN_EXE_INC_UART_MODE:
            DMP_DBG(printf("###   EXE INC/DEC UART\n"));
            if(MApp_ZUI_API_IsSuccessor(HWND_DMP_BAR_TRANS, MApp_ZUI_API_GetFocus()))
            {
               MApp_ZUI_API_ResetTimer(HWND_DMP_BAR_TRANS, DMP_UART_TIMER);
            }
            else
            {
               MApp_ZUI_API_StoreFocusCheckpoint();
               MApp_ZUI_API_SetTimer(HWND_DMP_BAR_TRANS, DMP_UART_TIMER, UART_DEBUG_TIME_OUT_MS);
            }
            _u8UARTMode= (EN_DMP_UART_MODE)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_UART_MODE,
            _u8UARTMode, UART_NONE, UART_NUM-1, 1);
            DMP_DBG(printf("@@ _u8UARTMode = %d\n",_u8UARTMode));

            if(_u8UARTMode == UART_HK)
            {
              #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_M10) || \
                     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
                     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
                     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
                 mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
              #else
                 mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
              #endif
            }
            else if(_u8UARTMode == UART_VDEC)
             {
                mdrv_uart_connect(E_UART_PORT0, E_UART_VDEC);
             }
            else if(_u8UARTMode == UART_AEON)
            {
              #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)
                mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
              #else
                mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
              #endif
             }
            else
            {
               mdrv_uart_connect(E_UART_PORT0, E_UART_OFF);
             }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BAR_OPTION);
            break;

        case EN_EXE_GOTO_THUMBNAIL:
            DMP_DBG(printf("## EN_EXE_GOTO_THUMBNAIL\n"));
            MApp_ZUI_API_ShowWindow(HWND_DMP_BAR, SW_HIDE);
            MApp_ZUI_API_SetFocus(hwnd_before);
            return TRUE;
    #endif // #ifndef ATSC_SYSTEM

    #if (ENABLE_DRM)
        case EN_EXE_DMP_DRM_WINDOW_NO:
        case EN_EXE_DMP_DRM_WINDOW_DONE:
            DMP_DBG(printf("EN_EXE_DMP_DRM_WINDOW_NO\n"););
            //g_bIsResumePlay = FALSE;
            MApp_MPlayer_PlayDRMFile(FALSE);
            switch(DRM_STATUS)
            {
            case WinViewRental:
                MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                //MApp_ZUI_API_RestoreFocusCheckpoint();
                //MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;
            case WinUnsupported:
                MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                //MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                break;
            case WinAuthError:
                MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                //MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                break;
            case WinRentalExpired:
                MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                //MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                break;
            }

            m_u16DRMErrorNum++;
            if ((MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_1)
                || ((m_u16PlayErrorNum+m_u16DRMErrorNum) >= _MApp_DMP_QueryTotalPlayListNum()))
            {
                {
                    //g_bIsResumePlay = FALSE;
                    MApp_MPlayer_PlayDRMFile(FALSE);

                    MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                    //MApp_ZUI_API_KillTimer(HWND_DMP_DRM_WINDOW, DMP_TIMER_DRM_WIN);

                    MApp_MPlayer_StopPlayerErrorMsgPending();
                    MApp_MPlayer_Stop();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                    //MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);

                    //_MApp_ACTdmp_HideAlertWin();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_HIDE);
                    _MApp_ZUI_API_WindowProcOnIdle();
                }
                // set the file_select index and current page index
                // TODO: across dir, across drive?
                {
                    U16 u16PlayingIdx = 0;
                    // TODO: fix photo type
                #if !EN_DMP_SEARCH_ALL
                    if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
                    {
                        DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
                    }
                #endif
                    u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
                    MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx/NUM_OF_PHOTO_FILES_PER_PAGE);
                    DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););
                    if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
                    {
                        DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                        MApp_MPlayer_SetCurrentPageIndex(0);
                    }
                }
                m_u16DRMErrorNum = 0;
            }
            else
            {
                //if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                {
#if (ENABLE_SUBTITLE_DMP)
                   MApp_MPlayer_DisableSubtitle();
#endif
                   MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                }
                //MApp_MPlayer_PlayNextFile();
                #if (ENABLE_MPLAYER_MOVIE)
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MOVIE, DEFAULT_MOVIE_ERROR_DELAY_TIME);
                #endif
            }
            break;

        case EN_EXE_DMP_DRM_WINDOW_YES:
            DMP_DBG(printf("EN_EXE_DMP_DRM_WINDOW_YES\n"););
            switch(DRM_STATUS)
            {
                case WinViewRental:
                    MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                    MApp_ZUI_API_RestoreFocusCheckpoint();

                    MApp_MPlayer_PlayDRMFile(TRUE);
                    MApp_SaveDrmSetting();
                    break;
                case WinUnsupported:
                    MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                    break;
                case WinAuthError:
                    MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                    break;
                case WinRentalExpired:
                    MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_HIDE);
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                    break;
            }
            m_u16DRMErrorNum = 0;
            break;
    #endif //ENABLE_DRM
		/*case EN_EXE_DMP_MEDIA_USB_SWITCH:                
            printf("\r\nUSB SWITCH = %d",u8UsbDeviceSel);
            MApp_ZUI_API_StoreFocusCheckpoint();
            //MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_HIDE);
            //MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_HIDE);
           
            
            if (u8UsbDeviceSel == DMP_USB_DISK1)
            {
                u8UsbDeviceSwitchStatus = 1;
                //MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_SHOW);
                //MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_SHOW);
                //MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL);                
            }
            else if (u8UsbDeviceSel == DMP_USB_DISK2)
            {
                u8UsbDeviceSwitchStatus = 2;
                MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL);                
            }
            return TRUE;
			
		case EN_EXE_DMP_MEDIA_USB_EXIT:
             if (u8UsbDeviceSwitchStatus != 0)
                u8UsbDeviceSwitchStatus = 0;
             
            MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_HIDE);
            
     
            MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_SHOW);
         
            MApp_ZUI_API_RestoreFocusCheckpoint();
            return TRUE;
	
		case EN_EXE_DMP_MEDIA_USB_LEFT:
        case EN_EXE_DMP_MEDIA_USB_RIGHT:
			printf("EN_EXE_DMP_MEDIA_USB_RIGHT");
            if (u8UsbDeviceSwitchStatus == 1)
                u8UsbDeviceSwitchStatus = 2;
            else 
                u8UsbDeviceSwitchStatus = 1;

            if (u8UsbDeviceSel == DMP_USB_DISK1)
            {
                if (u8UsbDeviceSwitchStatus == 1)
                {  
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL);  
                }
                else  if (u8UsbDeviceSwitchStatus == 2)
                { 
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB1_ICON); 
                }
            }
            else if (u8UsbDeviceSel == DMP_USB_DISK2)
            {
                if (u8UsbDeviceSwitchStatus == 1)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB2_ICON); 
                }
                else  if (u8UsbDeviceSwitchStatus == 2)
                {  
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL);    
                }         
            }           
            
            return TRUE;
		case EN_EXE_DMP_MEDIA_USB_SEL:

            //printf("\r\nu8UsbDeviceSwitchStatus1 = %d", u8UsbDeviceSwitchStatus);
           // printf("\r\nu8UsbDeviceSel1 = %d", u8UsbDeviceSel);
           bIsSwitchDevice = TRUE;//wht121124_1			
			msAPI_MSDCtrl_Init();//wht121124_1
            if (u8UsbDeviceSwitchStatus == 1 && u8UsbDeviceSel == 2)
            {
                MDrv_USBSetPortSwitch(0);
                
                u8UsbDeviceSel = DMP_USB_DISK1;

                  //u8UsbDeviceSwitchStatus = 0;
            }
            else   if (u8UsbDeviceSwitchStatus == 2 && u8UsbDeviceSel == 1)
            {
                MDrv_USBSetPortSwitch(1);
                
                u8UsbDeviceSel = DMP_USB_DISK2;

                  //u8UsbDeviceSwitchStatus = 0;
            }
                
            //printf("\r\nu8UsbDeviceSwitchStatus2 = %d", u8UsbDeviceSwitchStatus);
            //printf("\r\nu8UsbDeviceSel2 = %d", u8UsbDeviceSel);
            if (u8UsbDeviceSel == DMP_USB_DISK1)
            {
                if (u8UsbDeviceSwitchStatus == 1)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL);            
                }
                else  if (u8UsbDeviceSwitchStatus == 2)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB1_ICON);     
                }
            }
            else if (u8UsbDeviceSel == DMP_USB_DISK2)
            {
                if (u8UsbDeviceSwitchStatus == 1)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB2_ICON);            
                }
                else  if (u8UsbDeviceSwitchStatus == 2)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL);     
                }         
            }      

            //printf("\r\nu8UsbDeviceSwitchStatus2 = %d", u8UsbDeviceSwitchStatus);
            //printf("\r\nu8UsbDeviceSel2 = %d", u8UsbDeviceSel);
            return TRUE;
			*/
    #if PLAYLIST_BGM
        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO:
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_GROUP ,SW_SHOW);
            MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_ITEM,TRUE);

            if(m_bBGMOn == TRUE)
            {
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_ITEM,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT_ITEM,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT_ITEM,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV_ITEM,TRUE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_ITEM,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT_ITEM,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT_ITEM,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV_ITEM,FALSE);
            }
            MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_INFOCLOSE,TRUE);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_ITEM);
            break;

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFOCLOSE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_INFOCLOSE\n"););
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_GROUP,SW_HIDE);
                if(BGMINFO_INFO < _u8InfoBarIdx)
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[BGMINFO_INFO+u8PhotoInfoBarMax -_u8InfoBarIdx]);
                }
                else
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[BGMINFO_INFO - _u8InfoBarIdx]);
                }
            }
            break;
		
        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_TEXT_R:
        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_TEXT_L:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_ONOFF_TEXT\n"));

                if(m_bBGMOn == TRUE)
                {
                    if(MApp_MPlayer_IsMusicPlaying())
                    {
                        MApp_MPlayer_StopMusic();
                        MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                    }
                    MApp_MPlayer_BGM_Playlist_DeInit();
                    m_bBGMOn = FALSE;
                }
                else
                {
                    MApp_MPlayer_BGM_Playlist_Init();

                    if(MApp_MPlayer_QuerySelectedFileNum(E_MPLAYER_TYPE_MUSIC) > 0)
                    {
                        if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                        {
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                        }

                        if(MApp_MPlayer_IsMusicPlaying())
                        {
                            MApp_MPlayer_StopMusic();
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                        }

                        if(FALSE == _MApp_DMP_PlayBGM())
                        {
                            break;
                        }
                    }
                    m_bBGMOn = TRUE;
                }

                if(m_bBGMOn == TRUE)
                {
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM,TRUE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_ITEM,TRUE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT_ITEM,TRUE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT_ITEM,TRUE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV_ITEM,TRUE);
                }
                else
                {
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM,FALSE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_ITEM,FALSE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT_ITEM,FALSE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT_ITEM,FALSE);
                    MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV_ITEM,FALSE);
                }

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_ITEM);
                MApp_ZUI_CTL_DynamicListRefreshContent(HWND_DMP_PLAYBACK_BGMINFO_INFO_GROUP);
            }
            break;

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_TEXT_R:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_REPEAT_TEXT_R\n"));

                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                //------------------------Enter music mode------------------------

                // TODO: need test
                enumMPlayerRepeatMode eRepeatMode = MApp_MPlayer_QueryRepeatMode();
                if(eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_1);
                }
                else if(eRepeatMode == E_MPLAYER_REPEAT_1)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                }
                else
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);
                }

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM);

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
            }
            break;

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_TEXT_L:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_REPEAT_TEXT_L\n"));

                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                //------------------------Enter music mode------------------------

                // TODO: need test
                enumMPlayerRepeatMode eRepeatMode = MApp_MPlayer_QueryRepeatMode();
                if(eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                }
                else if(eRepeatMode == E_MPLAYER_REPEAT_ALL)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_1);
                }
                else
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);
                }

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM);

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
            }
            break;
#if RANDOM_PLAY
        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_TEXT_R:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_RANDOM_TEXT_R\n"));

                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                //------------------------Enter music mode------------------------

                // TODO: need test
                enumMPlayerRandomMode eRandomMode = MApp_MPlayer_QueryRandomMode();
                if(eRandomMode == E_MPLAYER_RANDOM_NONE)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM);
                }
                else if(eRandomMode == E_MPLAYER_RANDOM)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }
                else
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_ITEM);

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
            }
            break;

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_TEXT_L:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_RANDOM_TEXT_L\n"));

                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                //------------------------Enter music mode------------------------

                // TODO: need test
                enumMPlayerRandomMode eRandomMode = MApp_MPlayer_QueryRandomMode();
                if(eRandomMode == E_MPLAYER_RANDOM_NONE)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM);
                }
                else if(eRandomMode == E_MPLAYER_RANDOM)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }
                else
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_ITEM);

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
            }
            break;
#endif

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_SELECT_TEXT:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_SELECT\n"));

                _MApp_DMP_SavePhotoPath();

                MApp_MPlayer_Stop();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);

                MApp_MPlayer_BGM_Playlist_Init();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, TRUE);

                _MApp_DMP_EnterBGMPath();

                MApp_DMP_UiStateTransition(DMP_UI_STATE_BGM_FILE_SELECT);

                MApp_ZUI_API_InvalidateWindow(HWND_MAINFRAME);
            }
            break;

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_NEXT_TEXT:
            {
                if(MApp_MPlayer_IsMusicPlaying())
                {
                    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                    //------------------------Enter music mode------------------------
                    {
                        MApp_MPlayer_PlayNextFile();
                    }
                    //------------------------Exit music mode------------------------
                    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, FALSE);
                }
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_NEXT\n"));
            }
            break;

        case EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_PREV_TEXT:
            {
                if(MApp_MPlayer_IsMusicPlaying())
                {
                    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                    //------------------------Enter music mode------------------------
                    {
                        g_bPlayPrev = TRUE;
                        MApp_MPlayer_PlayPrevFile();
                    }
                    //------------------------Exit music mode------------------------
                    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, FALSE);
                }
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BGMINFO_INFO_PREV\n"));
            }
            break;
    #endif
        case EN_EXE_CLOSE_CURRENT_OSD:
          #ifdef ATSC_SYSTEM
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME,SW_HIDE);
          #else
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
          #endif
            //_enTargetMediaPlayerState = STATE_MEDIA_PLAYER_CLEAN_UP;
            return TRUE;
        break;

        case EN_EXE_POWEROFF:
            //_enTargetMediaPlayerState = STATE_MEDIA_PLAYER_GOTO_STANDBY;
          #ifdef ATSC_SYSTEM
            if(MApp_MPlayer_IsMediaFileInPlaying())
            {
                MApp_MPlayer_Stop();
                MApp_MPlayer_StopMusic();
            }
            MApp_MPlayer_ExitMediaPlayer();
            //MApp_ZUI_API_ShowWindow(HWND_MAINFRAME,SW_HIDE);
            MApp_ZUI_ACT_TerminateDmp();
          #else
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
          #endif
            return TRUE;
        break;

        case EN_EXE_DMP_ALERT_EXIT:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_LOADING)
            {
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            }

            if( MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING_ERROR)
            {
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
            //    _MApp_DMP_ErrorHandling_GotoDefaultPage(MApp_MPlayer_QueryCurrentMediaType());
            }
			//>>wht120519_2 
             if(_enDmpMsgType != DMP_MSG_TYPE_UNSUPPORTED_BUTTON)
             {
	            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
	            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_HIDE);
             }
			 //<<wht120519_2
            _MApp_ACTdmp_HideAlertWin();
            MApp_ZUI_API_KillTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN);

            return TRUE;

        case EN_EXE_DMP_MEDIA_PAGE_SEL:
            DMP_DBG(printf("EN_EXE_DMP_MEDIA_PAGE_SEL >> (%d)\n", MApp_ZUI_API_GetFocus()));
			//MApp_MPlayer_GetAllFilesInCurDrive();
            #if PLAYLIST_BGM
            bIsBGMPlaylist = FALSE;
            m_bBGMOn = FALSE;
            #endif

            #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
            m_bCopyOn = FALSE;
            #endif

            if(!(MApp_DMP_GetDmpFlag() & DMP_FLAG_DRIVE_CONNECT_OK))
            {
                return TRUE;
            }
            if(HWND_DMP_MEDIA_TYPE_PHOTO == MApp_ZUI_API_GetFocus())
            {
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_PHOTO, TRUE);
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(1 == MApp_MPlayer_QueryTotalDriveNum())//USB and SD single Partition
				{
					if(MApp_DMP_RecalculateDriveMappingTable())
					{
						if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(0)) == E_MPLAYER_RET_OK)
						{
#if EN_DMP_SEARCH_ALL
							MApp_MPlayer_GetAllFilesInCurDrive();
#endif

							bIsDriveSelected = TRUE; 
							MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
						}
					}
				}
				else //multi Partition   
#endif
				{
                	MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);//wht120307_3 DMP_UI_STATE_DRIVE_SELECT -> DMP_UI_STATE_MEDIA_SELECT
				}
            }
            else if(HWND_DMP_MEDIA_TYPE_MUSIC == MApp_ZUI_API_GetFocus())
            {
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, TRUE);
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(1 == MApp_MPlayer_QueryTotalDriveNum())//USB and SD single Partition
				{
					if(MApp_DMP_RecalculateDriveMappingTable())
					{
						if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(0)) == E_MPLAYER_RET_OK)
						{
#if EN_DMP_SEARCH_ALL
							MApp_MPlayer_GetAllFilesInCurDrive();
#endif

							bIsDriveSelected = TRUE; 
							MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
						}
					}
				}
				else //multi Partition   
#endif
				{
                	MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);//wht120307_3 DMP_UI_STATE_DRIVE_SELECT -> DMP_UI_STATE_MEDIA_SELECT
				}
            }
            else if(HWND_DMP_MEDIA_TYPE_MOVIE == MApp_ZUI_API_GetFocus())
            {
            // stop bgm
                if(MApp_DMP_GetDmpFlag()  & DMP_FLAG_BGM_MODE)
                {
                    MApp_MPlayer_StopMusic();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                }
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MOVIE, TRUE);
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(1 == MApp_MPlayer_QueryTotalDriveNum())//USB and SD single Partition
				{
					if(MApp_DMP_RecalculateDriveMappingTable())
					{
						if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(0)) == E_MPLAYER_RET_OK)
						{
#if EN_DMP_SEARCH_ALL
							MApp_MPlayer_GetAllFilesInCurDrive();
#endif

							bIsDriveSelected = TRUE;
							MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
						}
					}
				}
				else //multi Partition  
#endif
                {
                	MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);//wht120307_3 DMP_UI_STATE_DRIVE_SELECT -> DMP_UI_STATE_MEDIA_SELECT
                }
			}
            else if(HWND_DMP_MEDIA_TYPE_TEXT == MApp_ZUI_API_GetFocus())
            {
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_TEXT, TRUE);
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(1 == MApp_MPlayer_QueryTotalDriveNum())//USB and SD single Partition
				{
					if(MApp_DMP_RecalculateDriveMappingTable())
					{
						if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(0)) == E_MPLAYER_RET_OK)
						{
#if EN_DMP_SEARCH_ALL
							MApp_MPlayer_GetAllFilesInCurDrive();
#endif

							bIsDriveSelected = TRUE; 
							MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
						}
					}
				}
				else //multi Partition  
#endif
				{
                	MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);//wht120307_3 DMP_UI_STATE_DRIVE_SELECT -> DMP_UI_STATE_MEDIA_SELECT
                }
            }
            else
            {
                DMP_DBG(printf("[DMP] Failed to set media type!\n"));
                return FALSE;
            }
            return TRUE;
        case EN_EXE_DMP_MEDIA_PAGE_EXIT:
        // clear BGM
            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_BGM_MODE)
            {
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
            }
			#if (ENABLE_USB_ITEM_IN_SOURCE_MENU) //gchen @ 20171220
			#else
            MApp_DMP_GotoPreSrc();
			#endif
            #if ENABLE_USB_DEVICE_LIST
            MApp_ZUI_ACT_DMPSetDrvIdxByUser(FALSE);
            #endif
            return TRUE;
        case EN_EXE_DMP_DRIVE_PAGE_RIGHT:
            {
                if ((_hwndListDriveItem[0]==MApp_ZUI_API_GetFocus()) && (MApp_DMP_GetDrvPageIdx() <= 1))
                {
                    break;
                }
                else
                {
                    U8 u8Idx = MApp_DMP_GetCurDrvIdx();
                    if(u8Idx+1 == MApp_MPlayer_QueryTotalDriveNum())
                    {
                        return TRUE;
                    }
                    else
                    {
                        MApp_DMP_SetCurDrvIdxAndCalPageIdx(u8Idx+1);
                    }
                }
                _MApp_ACTdmp_ShowDrivePage();
            }
            break;
        case EN_EXE_DMP_DRIVE_PAGE_LEFT:
            {
                if (MApp_DMP_GetDrvPageIdx() <= 1)
                {
                    if (_hwndListDriveItem[1]==MApp_ZUI_API_GetFocus())
                    {
                        break;
                    }
                    else if (_hwndListDriveItem[0]==MApp_ZUI_API_GetFocus())
                    {
                        return TRUE;
                    }
                }
                U8 u8Idx = MApp_DMP_GetCurDrvIdx();
                MApp_DMP_SetCurDrvIdxAndCalPageIdx(u8Idx-1);
               _MApp_ACTdmp_ShowDrivePage();
            }
            break;
        case EN_EXE_DMP_DRIVE_PAGE_SEL:
            {
                U8 u8Item = 0;
                for(u8Item = 0; u8Item < DMP_DRIVE_NUM_PER_PAGE; u8Item++)
                {
                    if(_hwndListDriveItem[u8Item] == MApp_ZUI_API_GetFocus())
                    {
                        break;
                    }
                }
                if(u8Item < DMP_DRIVE_NUM_PER_PAGE)
                {
                    U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item;
                    //printf("[Drive] %d was selected.\n", u8Idx);
                    if(u8Idx == 0)
                    {
                        #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                        if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PROGRESS_WINDOW))
                            return TRUE;

                        if (m_bCopyOn == TRUE)
                        {
                            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_PRESS_RED_BUTTON_PASTE);
                            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                            return TRUE;
                        }
                        #endif

                        if(MApp_MPlayer_IsMusicPlaying())
                        {
                            MApp_MPlayer_StopMusic();
                        }
                        #if PLAYLIST_BGM
                        MApp_MPlayer_BGM_Playlist_DeInit();
                        #endif
                        MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
                    }
                    else
                    {
                        if(MApp_DMP_RecalculateDriveMappingTable())
                        {
                            if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(u8Idx-1)) == E_MPLAYER_RET_OK)
                            {
                                #if EN_DMP_SEARCH_ALL
                                MApp_MPlayer_GetAllFilesInCurDrive();
                                MApp_MPlayer_LoadPlayList2FileBuffer(MApp_MPlayer_QueryCurrentMediaType(),TRUE);
                                #endif

                                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                            }
                        }
                        else
                        {
                            //Failed to connect drive, back to media type select page
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
                            MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
                        }
                    }
                }
            }
            break;
        case EN_EXE_DMP_DRIVE_PAGE_EXIT:
            {
                #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PROGRESS_WINDOW))
                    return TRUE;

                if (m_bCopyOn == TRUE)
                {
                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_PRESS_RED_BUTTON_PASTE);
                    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                    return TRUE;
                }
                #endif

                if(MApp_MPlayer_IsMusicPlaying())
                {
                    MApp_MPlayer_StopMusic();
                }
                #if PLAYLIST_BGM
                MApp_MPlayer_BGM_Playlist_DeInit();
                #endif
                MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
            }
            break;
			#if 0
        case EN_EXE_DMP_FILE_PAGE_RIGHT:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0;
                MS_DEBUG_MSG(printf("EN_EXE_DMP_FILE_PAGE_RIGHT\n"));
                if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) < MApp_MPlayer_QueryTotalFileNum() - 1)
                {
                }
                else
                {
                    //Already reach to the last item
                    #if ENABLE_GOTO_LASTORFIRST_INDEX
                    enumMPlayerRet Flag =E_MPLAYER_RET_FAIL;
                    do
                    {
                        Flag = MApp_MPlayer_PrevPage();
                    }
                    while(Flag == E_MPLAYER_RET_OK);
                    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                    #endif
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 0);
                    MApp_ZUI_API_SetFocus(_hwndListFileItem[0]);
                    //_MApp_ACTdmp_HidePreviewWin();
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                    #endif
                    return TRUE;
                }
                for(u16ItemIdx = 0; u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE; u16ItemIdx++)
                {
                    if(hwndFocus == _hwndListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
                //_MApp_ACTdmp_HidePreviewWin();
                //if(u16ItemIdx == NUM_OF_PHOTO_FILES_PER_PAGE-1)
                {
                    if((MApp_MPlayer_QueryCurrentPageIndex() < MApp_MPlayer_QueryTotalPages()-1) &&
                       (MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK))
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 0);
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            //_MApp_ACTdmp_ShowPreviewWin();
                        }
						MApp_ZUI_API_SetFocus(_hwndListFileItem[0]);
                    }
                    else
                    {
                        //Cannot process 'Next Page'
                        return TRUE;
                    }
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                }
                /* else if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) <
                       MApp_MPlayer_QueryTotalFileNum() - 1)
                    {
                        _MApp_ACTdmp_HidePreviewWin();
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx+1);
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            _MApp_ACTdmp_ShowPreviewWin();
                        }
                    }
                    else
                    {
                        //The last item
                        return TRUE;
                    }
                } */
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
            }
            break;
        case EN_EXE_DMP_FILE_PAGE_LEFT:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0;
                DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_LEFT\n");); //DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_LEFT\n");); //change by gchen @ 20110421
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(hwndFocus == _hwndListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
                //_MApp_ACTdmp_HidePreviewWin();
                //if(u16ItemIdx == 0)
                {
                    if((MApp_MPlayer_QueryCurrentPageIndex() > 0) &&
                       (MApp_MPlayer_PrevPage() == E_MPLAYER_RET_OK))
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE,
                                                    NUM_OF_PHOTO_FILES_PER_PAGE-1);
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            //_MApp_ACTdmp_ShowPreviewWin();
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                    }
                    else if(MApp_MPlayer_QueryCurrentPageIndex() == 0)
                    {
                        #if ENABLE_GOTO_LASTORFIRST_INDEX
                        enumMPlayerRet Flag =E_MPLAYER_RET_FAIL;
                        U16 UIndex = (MApp_MPlayer_QueryTotalFileNum()-1)%NUM_OF_PHOTO_FILES_PER_PAGE;
                        do
                        {
                            Flag = MApp_MPlayer_NextPage();
                        }
                        while(Flag == E_MPLAYER_RET_OK);
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE,
                                                    UIndex);
                        MApp_ZUI_API_SetFocus(_hwndListFileItem[UIndex]);
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            //_MApp_ACTdmp_ShowPreviewWin();
                        }
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);

                        #endif
                        return TRUE;
                    }
                }
                /* else if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    _MApp_ACTdmp_HidePreviewWin();
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx-1);
                    if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                    {
                        //File type
                        _MApp_ACTdmp_ShowPreviewWin();
                    }
                } */
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
            }
            break;
			#endif
        case EN_EXE_DMP_FILE_PAGE_DOWN:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0, u16NewIdx = 0, u16FocusIdx = 0;
                DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_DOWN\n"););
                if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) < MApp_MPlayer_QueryTotalFileNum() - 1)
                {
                }
                else
                {
                    //Already reach to the last item
                    return TRUE;
                }
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(hwndFocus == _hwndListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(!bIsDriveSelected) 
				{
					//printf(" bIsDriveSelected == FALSE test key down 0\n");
					if(u16ItemIdx == NUM_OF_PHOTO_FILES_PER_PAGE-1)
					{
						//printf(" u16ItemIdx == NUM_OF_PHOTO_FILES_PER_PAGE-1 test key down 1"); 
						if((MApp_MPlayer_QueryCurrentPageIndex() < MApp_MPlayer_QueryTotalPages()-1) &&
						(MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK))
						{
						MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 0);
						MApp_ZUI_API_SetFocus(_hwndListFileItem[0]); 
						//_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx], false); 
						//_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[0], true); 
						MApp_DMP_SetCurDrvIdxAndCalPageIdx((U8)(u16ItemIdx+1));
						}
						else
						{
							//Cannot process 'Next Page'
							return TRUE;
						}
						MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);  
					}
					else if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
					{
						if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) <
							MApp_MPlayer_QueryTotalDriveNum())
						{
							MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx+1);
							MApp_ZUI_API_SetFocus(_hwndListFileItem[u16ItemIdx+1]); 
							//_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx], false); 
							//_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx+1], true); 
							MApp_DMP_SetCurDrvIdxAndCalPageIdx((U8)(u16ItemIdx+1));
						}
						else
						{
							//The last item
							return TRUE;
						}
					}
#if ENABLE_PROGRESS_BAR
					U32 u32Percent = 0; 
					u32Percent = (MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) + 1) * 100 / 
					MApp_MPlayer_QueryTotalDriveNum();
					MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
					DMP_DBG(printf("u32Persent = %u\n", u32Percent));	
					MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_PAGE_SELECT_PROGRESS_BAR);
#endif
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);  
					DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
					DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));	    
					return TRUE;
				}
#endif
                u16FocusIdx = u16ItemIdx + MApp_MPlayer_QueryCurrentPageIndex()*DMP_NUM_OF_FILES_PER_PAGE;
                u16NewIdx = u16FocusIdx + DMP_FILE_PAGE_COLUMN_NUM;
                DMP_DBG(printf("    >> focus idx = %u, new idx = %u [total = %u]\n", u16FocusIdx, u16NewIdx, MApp_MPlayer_QueryTotalFileNum()););
                //_MApp_ACTdmp_HidePreviewWin();
                if(u16FocusIdx >= MApp_MPlayer_QueryTotalFileNum()-1)
                {
                    return TRUE;
                }
                if(u16ItemIdx >= NUM_OF_PHOTO_FILES_PER_PAGE-DMP_FILE_PAGE_COLUMN_NUM)
                {
                    //Need to do 'Next Page'
                    if((MApp_MPlayer_QueryCurrentPageIndex() < MApp_MPlayer_QueryTotalPages()-1) &&
                       (MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK))
                    {
                    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                    #endif
                        if(u16NewIdx > MApp_MPlayer_QueryTotalFileNum()-1)
                        {
                            //The last item
                            u16NewIdx = MApp_MPlayer_QueryTotalFileNum()-1;
                        }
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            //_MApp_ACTdmp_ShowPreviewWin();
                        }
                    }
                    else
                    {
                        //Cannot process 'Next Page' - the last page
                        if(u16NewIdx != u16FocusIdx)
                        {
                            if(u16NewIdx > MApp_MPlayer_QueryTotalFileNum()-1)
                            {
                                //The last item
                                u16NewIdx = MApp_MPlayer_QueryTotalFileNum()-1;
                            }
                            MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                            if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                            {
                                //File type
                                //_MApp_ACTdmp_ShowPreviewWin();
                            }
                        }
                        else
                        {
                            return TRUE;
                        }
                    }
                }
                else// if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    if(u16NewIdx > MApp_MPlayer_QueryTotalFileNum() - 1)
                    {
                        u16NewIdx = MApp_MPlayer_QueryTotalFileNum() - 1;
                    }
                    //_MApp_ACTdmp_HidePreviewWin();
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                    if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                    {
                        //File type
                        //_MApp_ACTdmp_ShowPreviewWin();
                    }
                }
                MApp_ZUI_API_SetFocus(_hwndListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] New Idx = %d (set focus to %d item)\n", u16NewIdx, u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
                return TRUE;
            }
            break;
        case EN_EXE_DMP_FILE_PAGE_UP:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0, u16NewIdx = 0, u16FocusIdx = 0;
                DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_UP\n"););
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(hwndFocus == _hwndListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
			  if(!bIsDriveSelected) 
			  {
				  if(u16ItemIdx == 0)
		                {
		                    if((MApp_MPlayer_QueryCurrentPageIndex() > 0) &&
		                       (MApp_MPlayer_PrevPage() == E_MPLAYER_RET_OK))
		                    {
		                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE,
		                                                    NUM_OF_PHOTO_FILES_PER_PAGE-1);
		                	   MApp_ZUI_API_SetFocus(_hwndListFileItem[NUM_OF_PHOTO_FILES_PER_PAGE-1]); 
		                	   _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx], false); 
					   _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[NUM_OF_PHOTO_FILES_PER_PAGE-1], true);				   
	                        	   MApp_DMP_SetCurDrvIdxAndCalPageIdx((U8)(u16ItemIdx-1));
		                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
		                    }
		                    else if(MApp_MPlayer_QueryCurrentPageIndex() == 0)
		                    {
		                        return TRUE;
		                    }
		                }
		                else if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
		                {
		                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx-1);
		                    MApp_ZUI_API_SetFocus(_hwndListFileItem[u16ItemIdx-1]); 
		                    _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx], false); 
		                    _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx], false); 
		                    _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndListFileString[u16ItemIdx-1], true);					
	                           MApp_DMP_SetCurDrvIdxAndCalPageIdx((U8)(u16ItemIdx-1));
		                }
				  //to show file page progress bar
#if ENABLE_PROGRESS_BAR
				  U32 u32Percent = 0; 
				  u32Percent = (MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) + 1) * 100 / 
				  				MApp_MPlayer_QueryTotalDriveNum();
				  MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
		                DMP_DBG(printf("u32Persent = %u\n", u32Percent));	
				  MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_PAGE_SELECT_PROGRESS_BAR);
#endif						
		                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
		                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));	    
				  return TRUE;
			  }
#endif
                u16FocusIdx = u16ItemIdx + MApp_MPlayer_QueryCurrentPageIndex()*DMP_NUM_OF_FILES_PER_PAGE;
                u16NewIdx = ((u16FocusIdx<DMP_FILE_PAGE_COLUMN_NUM)?0:(u16FocusIdx - DMP_FILE_PAGE_COLUMN_NUM));
                DMP_DBG(printf("    >> focus idx = %u, new idx = %u [total = %u]\n", u16FocusIdx, u16NewIdx, MApp_MPlayer_QueryTotalFileNum()););
                //_MApp_ACTdmp_HidePreviewWin();
                if(u16ItemIdx < DMP_FILE_PAGE_COLUMN_NUM)
                {
                    if((MApp_MPlayer_QueryCurrentPageIndex() > 0) &&
                       (MApp_MPlayer_PrevPage() == E_MPLAYER_RET_OK))
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        //MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                    }
                    else// if(MApp_MPlayer_QueryCurrentPageIndex() == 0)
                    {
                        //The first page
                        u16NewIdx = 0;
                    }
                }
                else// if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                }
                //_MApp_ACTdmp_HidePreviewWin();
                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                MApp_ZUI_API_SetFocus(_hwndListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                /* if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                {
                    //File type
                    _MApp_ACTdmp_ShowPreviewWin();
                } */
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
                return TRUE;
            }
            break;
    #if PLAYLIST_BGM
        case EN_EXE_DMP_BGM_FILE_PAGE_RIGHT:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0;
                MS_DEBUG_MSG(printf("EN_EXE_DMP_BGM_FILE_PAGE_RIGHT\n"));

                if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) < MApp_MPlayer_QueryTotalFileNum() - 1)
                {
                }
                else
                {
                    //Already reach to the last item
                    return TRUE;
                }
                for(u16ItemIdx = 0; u16ItemIdx < NUM_OF_MUSIC_FILES_PER_PAGE; u16ItemIdx++)
                {
                    if(hwndFocus == _hwndBgmListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
                //_MApp_ACTdmp_HidePreviewWin();
                if(u16ItemIdx == NUM_OF_PHOTO_FILES_PER_PAGE-1)
                {
                    if((MApp_MPlayer_QueryCurrentPageIndex() < MApp_MPlayer_QueryTotalPages()-1) &&
                       (MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK))
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 0);
                        /*
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            _MApp_ACTdmp_ShowPreviewWin();
                        }
                        */
                    }
                    else
                    {
                        //Cannot process 'Next Page'
                        return TRUE;
                    }
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BGM_FILE_SELECT_PAGE);
                }
                else if(u16ItemIdx < NUM_OF_MUSIC_FILES_PER_PAGE)
                {
                    if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) <
                       MApp_MPlayer_QueryTotalFileNum() - 1)
                    {
                            //_MApp_ACTdmp_HidePreviewWin();
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx+1);
                        /*
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            _MApp_ACTdmp_ShowPreviewWin();
                        }
                        */
                    }
                    else
                    {
                        //The last item
                        return TRUE;
                    }
                }
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
            }
            break;
        case EN_EXE_DMP_BGM_FILE_PAGE_LEFT:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0;
                DMP_DBG(printf("EN_EXE_DMP_BGM_FILE_PAGE_LEFT\n"););
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_MUSIC_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(hwndFocus == _hwndBgmListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
                //_MApp_ACTdmp_HidePreviewWin();
                if(u16ItemIdx == 0)
                {
                    if((MApp_MPlayer_QueryCurrentPageIndex() > 0) &&
                       (MApp_MPlayer_PrevPage() == E_MPLAYER_RET_OK))
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE,
                                                    NUM_OF_MUSIC_FILES_PER_PAGE-1);
                        /*
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            _MApp_ACTdmp_ShowPreviewWin();
                        }
                        */
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BGM_FILE_SELECT_PAGE);
                    }
                    else if(MApp_MPlayer_QueryCurrentPageIndex() == 0)
                    {
                        return TRUE;
                    }
                }
                else if(u16ItemIdx < NUM_OF_MUSIC_FILES_PER_PAGE)
                {
                    //_MApp_ACTdmp_HidePreviewWin();
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx-1);
                    /*
                    if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                    {
                        //File type
                        _MApp_ACTdmp_ShowPreviewWin();
                    }
                    */
                }
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
            }
            break;
        case EN_EXE_DMP_BGM_FILE_PAGE_DOWN:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0, u16NewIdx = 0, u16FocusIdx = 0;
                DMP_DBG(printf("EN_EXE_DMP_BGM_FILE_PAGE_DOWN\n"););
                if(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) < MApp_MPlayer_QueryTotalFileNum() - 1)
                {
                }
                else
                {
                    //Already reach to the last item
                    return TRUE;
                }
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_MUSIC_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(hwndFocus == _hwndBgmListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
                u16FocusIdx = u16ItemIdx + MApp_MPlayer_QueryCurrentPageIndex()*DMP_NUM_OF_FILES_PER_PAGE;
                u16NewIdx = u16FocusIdx + DMP_FILE_PAGE_COLUMN_NUM;
                DMP_DBG(printf("    >> focus idx = %u, new idx = %u [total = %u]\n", u16FocusIdx, u16NewIdx, MApp_MPlayer_QueryTotalFileNum()););
                //_MApp_ACTdmp_HidePreviewWin();
                if(u16FocusIdx >= MApp_MPlayer_QueryTotalFileNum()-1)
                {
                    return TRUE;
                }
                if(u16ItemIdx >= NUM_OF_PHOTO_FILES_PER_PAGE-DMP_FILE_PAGE_COLUMN_NUM)
                {
                    //Need to do 'Next Page'
                    if((MApp_MPlayer_QueryCurrentPageIndex() < MApp_MPlayer_QueryTotalPages()-1) &&
                       (MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK))
                    {
                    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                    #endif
                        if(u16NewIdx > MApp_MPlayer_QueryTotalFileNum()-1)
                        {
                            //The last item
                            u16NewIdx = MApp_MPlayer_QueryTotalFileNum()-1;
                        }
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                        /*
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            _MApp_ACTdmp_ShowPreviewWin();
                        }
                        */
                    }
                    else
                    {
                        //Cannot process 'Next Page' - the last page
                        if(u16NewIdx != u16FocusIdx)
                        {
                            if(u16NewIdx > MApp_MPlayer_QueryTotalFileNum()-1)
                            {
                                //The last item
                                u16NewIdx = MApp_MPlayer_QueryTotalFileNum()-1;
                            }
                            MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                            /*
                            if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                            {
                                //File type
                                _MApp_ACTdmp_ShowPreviewWin();
                            }
                            */
                        }
                        else
                        {
                            return TRUE;
                        }
                    }
                }
                else// if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    if(u16NewIdx > MApp_MPlayer_QueryTotalFileNum() - 1)
                    {
                        u16NewIdx = MApp_MPlayer_QueryTotalFileNum() - 1;
                    }
                    //_MApp_ACTdmp_HidePreviewWin();
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                    /*
                    if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                    {
                        //File type
                        _MApp_ACTdmp_ShowPreviewWin();
                    }
                    */
                }
                MApp_ZUI_API_SetFocus(_hwndBgmListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BGM_FILE_SELECT_PAGE);
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] New Idx = %d (set focus to %d item)\n", u16NewIdx, u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
                return TRUE;
            }
            break;
        case EN_EXE_DMP_BGM_FILE_PAGE_UP:
            {
                HWND hwndFocus = MApp_ZUI_API_GetFocus();
                U16 u16ItemIdx = 0, u16NewIdx = 0, u16FocusIdx = 0;
                DMP_DBG(printf("EN_EXE_DMP_BGM_FILE_PAGE_UP\n"););
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_MUSIC_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(hwndFocus == _hwndBgmListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
                u16FocusIdx = u16ItemIdx + MApp_MPlayer_QueryCurrentPageIndex()*DMP_NUM_OF_FILES_PER_PAGE;
                u16NewIdx = ((u16FocusIdx<DMP_FILE_PAGE_COLUMN_NUM)?0:(u16FocusIdx - DMP_FILE_PAGE_COLUMN_NUM));
                DMP_DBG(printf("    >> focus idx = %u, new idx = %u [total = %u]\n", u16FocusIdx, u16NewIdx, MApp_MPlayer_QueryTotalFileNum()););
                //_MApp_ACTdmp_HidePreviewWin();
                if(u16ItemIdx < DMP_FILE_PAGE_COLUMN_NUM)
                {
                    if((MApp_MPlayer_QueryCurrentPageIndex() > 0) &&
                       (MApp_MPlayer_PrevPage() == E_MPLAYER_RET_OK))
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        //MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                    }
                    else// if(MApp_MPlayer_QueryCurrentPageIndex() == 0)
                    {
                        //The first page
                        u16NewIdx = 0;
                    }
                }
                else// if(u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                }
                //_MApp_ACTdmp_HidePreviewWin();
                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                MApp_ZUI_API_SetFocus(_hwndBgmListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BGM_FILE_SELECT_PAGE);
                /*
                if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                {
                    //File type
                    _MApp_ACTdmp_ShowPreviewWin();
                }
                */
                DMP_DBG(printf("[File Page] Current Idx = %u\n", MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)));
                DMP_DBG(printf("[File Page] Current Page = %u\n", MApp_MPlayer_QueryCurrentPageIndex()));
                return TRUE;
            }
            break;

        case EN_EXE_DMP_BGM_FILE_PAGE_SEL:
            {
                DMP_DBG(printf("EN_EXE_DMP_BGM_FILE_PAGE_SEL :\n"););
                U16 u16FileIdx = MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY);
                MPlayerFileInfo fileInfo;

                if(u16FileIdx == 0)
                {
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_BGM_DRIVE_SELECT);
                }
                else if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                              u16FileIdx,
                                              &fileInfo) == E_MPLAYER_RET_OK)
                {
                    if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                    {
                        // TODO: refine here
                    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                    #endif

                    #if ENABLE_MPLAYER_RECORD_DIR_ENTRY
                        U16 u16DirDepth = MApp_MPlayer_QueryDirectoryDepth();
                        if(!(u16DirDepth > 0 && u16FileIdx == 1))
                        {
                            //printf("Record DIR info ...\n");
                            _u16FileIdxByDir[u16DirDepth] = u16FileIdx;
                        }
                        //sync current file path
                        MApp_MPlayer_QueryDirectoryNode(_u16FileIdxByDir,MApp_MPlayer_QueryDirectoryDepth());
                    #endif

                        if(MApp_MPlayer_EnterDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                                       u16FileIdx) == E_MPLAYER_RET_OK)
                        {
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_BGM_FILE_SELECT_PAGE);
                        #if ENABLE_MPLAYER_RECORD_DIR_ENTRY
                            if(u16DirDepth > 0 && u16FileIdx == 1)
                            {//Go to prev. directory...
                                //printf("Go to prev. directory ... (idx = %d)\n", _u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]);
                                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, _u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]);
                                MApp_MPlayer_SetCurrentPageIndex(_u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]/NUM_OF_MUSIC_FILES_PER_PAGE);
                                MApp_ZUI_API_SetFocus(_hwndBgmListFileItem[_u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]%NUM_OF_MUSIC_FILES_PER_PAGE]);
                            }
                            else
                        #endif
                            {
                                MApp_ZUI_API_SetFocus(HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1);
                            }
                        }
                    }
                    else
                    {
                        if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
                        {
                            MApp_MPlayer_SetFileUnselected(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16FileIdx);
                            MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());
                        }
                        else
                        {
                            MApp_MPlayer_SetFileSelected(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16FileIdx);
                            MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());
                        }
                    }
                    return TRUE;
                }
            }
            break;

        case EN_EXE_DMP_BGM_FILE_PAGE_PLAYBACK:
            {
                {//EN_EXE_DMP_FILE_PAGE_PLAYBACK
                    m_u16PlayErrorNum = 0;
                    #if (ENABLE_DRM)
                    m_u16DRMErrorNum = 0;
                    #endif
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);

                    U16 u16LastFileIdx = MApp_MPlayer_QueryTotalFileNum() - 1;
                    MPlayerFileInfo FileInfo;
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16LastFileIdx,&FileInfo);

                    if(MApp_MPlayer_QuerySelectedFileNum(E_MPLAYER_TYPE_MUSIC /*for selected files*/) > 0)
                    {
                        if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                        {
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                        }

                        MApp_MPlayer_SetPlayMode(E_MPLAYER_PLAY_SELECTED_FROM_CURRENT);

                        if(MApp_MPlayer_IsMusicPlaying())
                        {
                            MApp_MPlayer_StopMusic();
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                        }

                        if( FALSE ==  _MApp_DMP_PlayBGM())
                        {
                            break;
                        }

                        m_bBGMOn = TRUE;
                        //-------------------------------------------------------------------
                        _MApp_ACTdmp_BGM_ReturnToPhotoSlideShow();
                    }
                    else
                    {
                        // there is no select files...
                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_NO_SELECT_FILE);
                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                    }
                }
            }
            break;

        case EN_EXE_DMP_BGM_FILE_PAGE_EXIT:
            {
                MApp_MPlayer_StopPreview();
                MApp_DMP_UiStateTransition(DMP_UI_STATE_BGM_DRIVE_SELECT);
            }
            break;

        case EN_EXE_DMP_BGM_DRIVE_PAGE_RIGHT:
            {
                DMP_DBG(printf("EN_EXE_DMP_BGM_DRIVE_PAGE_RIGHT\n"););
                if ((_hwndBgmListDriveItem[0]==MApp_ZUI_API_GetFocus()) && (MApp_DMP_GetDrvPageIdx() <= 1))
                {
                    break;
                }
                else
                {
                    U8 u8Idx = MApp_DMP_GetCurDrvIdx();
                    if(u8Idx+1 == MApp_MPlayer_QueryTotalDriveNum())
                    {
                        return TRUE;
                    }
                    else
                    {
                        MApp_DMP_SetCurDrvIdxAndCalPageIdx(u8Idx+1);
                    }
                }
                _MApp_ACTdmp_ShowBgmDrivePage();
            }
            break;

        case EN_EXE_DMP_BGM_DRIVE_PAGE_LEFT:
            {
                DMP_DBG(printf("EN_EXE_DMP_BGM_DRIVE_PAGE_LEFT\n"););
                if (MApp_DMP_GetDrvPageIdx() <= 1)
                {
                    if (_hwndBgmListDriveItem[1]==MApp_ZUI_API_GetFocus())
                    {
                        break;
                    }
                    else if (_hwndBgmListDriveItem[0]==MApp_ZUI_API_GetFocus())
                    {
                        return TRUE;
                    }
                }
                U8 u8Idx = MApp_DMP_GetCurDrvIdx();
                MApp_DMP_SetCurDrvIdxAndCalPageIdx(u8Idx-1);
               _MApp_ACTdmp_ShowBgmDrivePage();
            }
            break;

        case EN_EXE_DMP_BGM_DRIVE_PAGE_SEL:
            {
                U8 u8Item = 0;
                DMP_DBG(printf("EN_EXE_DMP_BGM_DRIVE_PAGE_SEL\n"););

                for(u8Item = 0; u8Item < DMP_DRIVE_NUM_PER_PAGE; u8Item++)
                {
                    if(_hwndBgmListDriveItem[u8Item] == MApp_ZUI_API_GetFocus())
                    {
                        break;
                    }
                }
                if(u8Item < DMP_DRIVE_NUM_PER_PAGE)
                {
                    U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item;
                    //printf("[Drive] %d was selected.\n", u8Idx);
                    if(u8Idx == 0)
                    {
                        m_u16PlayErrorNum = 0;
                        #if (ENABLE_DRM)
                        m_u16DRMErrorNum = 0;
                        #endif
                        MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);

                        if(MApp_MPlayer_QuerySelectedFileNum(E_MPLAYER_TYPE_MUSIC /*only for selected files*/) > 0)
                        {
                            if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                            {
                                MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                            }

                            if( MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                                MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                            {
                                MApp_MPlayer_SetPlayMode(E_MPLAYER_PLAY_SELECTED_FROM_CURRENT);

                                if(MApp_MPlayer_IsMusicPlaying())
                                {
                                    MApp_MPlayer_StopMusic();
                                    MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                                }

                                _MApp_DMP_PlayBGM();
                                m_bBGMOn = TRUE;
                            }
                            else
                            {
                                if(!MApp_MPlayer_IsMusicPlaying())
                                {
                                    MApp_MPlayer_StopMusic();
                                    MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);

                                    _MApp_DMP_PlayBGM();
                                    m_bBGMOn = TRUE;
                                }
                            }
                        }
                        else
                        {
                            // there is no select files...
                            MApp_MPlayer_StopMusic();
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                            m_bBGMOn = FALSE;
                        }
                        _MApp_ACTdmp_BGM_ReturnToPhotoSlideShow();
                    }
                    else
                    {
                        if(MApp_DMP_RecalculateDriveMappingTable())
                        {
                            if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(u8Idx-1)) == E_MPLAYER_RET_OK)
                            {
                            #if EN_DMP_SEARCH_ALL
                                MApp_MPlayer_GetAllFilesInCurDrive();
                                MApp_MPlayer_LoadPlayList2FileBuffer(MApp_MPlayer_QueryCurrentMediaType(),TRUE);
                            #endif

                                MApp_DMP_UiStateTransition(DMP_UI_STATE_BGM_FILE_SELECT);
                            }
                        }
                        else
                        {
                            //Failed to connect drive, back to media type select page
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
                            MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
                        }
                    }
                }
            }
            break;

        case EN_EXE_DMP_BGM_DRIVE_PAGE_EXIT:
            {
                m_u16PlayErrorNum = 0;
                #if (ENABLE_DRM)
                m_u16DRMErrorNum = 0;
                #endif
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);

                if(MApp_MPlayer_QuerySelectedFileNum(E_MPLAYER_TYPE_MUSIC /*only for selected files*/) > 0)
                {
                    if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                    {
                        MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                    }

                    if( MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                        MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                    {
                        MApp_MPlayer_SetPlayMode(E_MPLAYER_PLAY_SELECTED_FROM_CURRENT);

                        if(MApp_MPlayer_IsMusicPlaying())
                        {
                            MApp_MPlayer_StopMusic();
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                        }

                        _MApp_DMP_PlayBGM();
                        m_bBGMOn = TRUE;
                    }
                    else
                    {
                        if(!MApp_MPlayer_IsMusicPlaying())
                        {
                            MApp_MPlayer_StopMusic();
                            MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);

                            _MApp_DMP_PlayBGM();
                            m_bBGMOn = TRUE;
                        }
                    }
                }
                else
                {
                    // there is no select files...
                    MApp_MPlayer_StopMusic();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                    m_bBGMOn = FALSE;
                }
                _MApp_ACTdmp_BGM_ReturnToPhotoSlideShow();
            }
            break;
    #endif
        case EN_EXE_DMP_FILE_PAGE_PAGE_DOWN:
		case EN_EXE_DMP_FILE_PAGE_RIGHT:  //wht120424_4
            // TODO: fixme
            DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_PAGE_DOWN\n"););
            {
                if(MApp_MPlayer_QueryCurrentPageIndex() < MApp_MPlayer_QueryTotalPages()-1)
                {
                    // nextpage exist
                    HWND hwndFocus = MApp_ZUI_API_GetFocus();
                    U16 u16ItemIdx = 0, u16NewIdx = 0, u16FocusIdx = 0;
                    for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                    {
                        if(hwndFocus == _hwndListFileItem[u16ItemIdx])
                        {
                            break;
                        }
                    }
                    u16FocusIdx = u16ItemIdx + MApp_MPlayer_QueryCurrentPageIndex()*DMP_NUM_OF_FILES_PER_PAGE;
                    u16NewIdx = u16FocusIdx + NUM_OF_PHOTO_FILES_PER_PAGE;
                    DMP_DBG(printf("    >> focus idx = %u, new idx = %u [total = %u]\n", u16FocusIdx, u16NewIdx, MApp_MPlayer_QueryTotalFileNum()););
                    //_MApp_ACTdmp_HidePreviewWin();
                    if(u16NewIdx <= MApp_MPlayer_QueryTotalFileNum()-1)
                    {
                        if(MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK)
                        {
                            #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                            _MApp_DMP_Thumbnail_ChangePage();
                            #endif
                            MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                            MApp_ZUI_API_SetFocus(_hwndListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                            if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                            {
                                //File type
                                //_MApp_ACTdmp_ShowPreviewWin();
                            }
                        }
                        else
                        {
                            DMP_DBG(printf("MApp_MPlayer_NextPage fail\n"););
                        }
                    }
                    else
                    {
                        // set index to last file
                        if(MApp_MPlayer_NextPage() == E_MPLAYER_RET_OK)
                        {
                            #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                            _MApp_DMP_Thumbnail_ChangePage();
                            #endif
                            U16 u16LastFileIdx = MApp_MPlayer_QueryTotalFileNum()-1;
                            //_MApp_ACTdmp_HidePreviewWin();
                            MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16LastFileIdx);
                            MApp_ZUI_API_SetFocus(_hwndListFileItem[u16LastFileIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                            /*if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                            {
                                //File type
                                _MApp_ACTdmp_ShowPreviewWin();
                            }*/
                        }
                        else
                        {
                            DMP_DBG(printf("MApp_MPlayer_NextPage fail 1\n"););
                        }
                    }
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
            break;
        case EN_EXE_DMP_FILE_PAGE_PAGE_UP:
		case EN_EXE_DMP_FILE_PAGE_LEFT:  //wht120424_4
            DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_PAGE_UP\n"););
            {
                if(MApp_MPlayer_QueryCurrentPageIndex() > 0)
                {
                    // prepage exist
                    HWND hwndFocus = MApp_ZUI_API_GetFocus();
                    U16 u16ItemIdx = 0, u16NewIdx = 0, u16FocusIdx = 0;
                    for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                    {
                        if(hwndFocus == _hwndListFileItem[u16ItemIdx])
                        {
                            break;
                        }
                    }
                    u16FocusIdx = u16ItemIdx + MApp_MPlayer_QueryCurrentPageIndex()*DMP_NUM_OF_FILES_PER_PAGE;
                    u16NewIdx = u16FocusIdx - NUM_OF_PHOTO_FILES_PER_PAGE;
                    DMP_DBG(printf("    >> focus idx = %u, new idx = %u [total = %u]\n", u16FocusIdx, u16NewIdx, MApp_MPlayer_QueryTotalFileNum()););
                    _MApp_ACTdmp_HidePreviewWin();
                    if(MApp_MPlayer_PrevPage() == E_MPLAYER_RET_OK)
                    {
                        #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                        #endif
                        //_MApp_ACTdmp_HidePreviewWin();
                        MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16NewIdx);
                        MApp_ZUI_API_SetFocus(_hwndListFileItem[u16NewIdx%DMP_NUM_OF_FILES_PER_PAGE]);
                        if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
                        {
                            //File type
                            //_MApp_ACTdmp_ShowPreviewWin();
                        }
                    }
                    else
                    {
                        DMP_DBG(printf("MApp_MPlayer_PrevPage fail\n"););
                    }
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
            break;
        case EN_EXE_DMP_FILE_PAGE_SEL:
            {
                DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_SEL :\n"););
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(!bIsDriveSelected)
				{
					U8 u8Item = 0;
					for(u8Item = 0; u8Item < DMP_DRIVE_NUM_PER_PAGE; u8Item++)
					{
						if(_hwndListFileItem[u8Item] == MApp_ZUI_API_GetFocus())
						{
							break;
						}
					}
					if(u8Item < DMP_DRIVE_NUM_PER_PAGE)
					{
						U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item;
						//printf("[Drive] %d was selected.\n", u8Idx);       
						if(MApp_DMP_RecalculateDriveMappingTable())
						{
							if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(u8Idx)) == E_MPLAYER_RET_OK)
							{
#if EN_DMP_SEARCH_ALL
								MApp_MPlayer_GetAllFilesInCurDrive();
#endif

								bIsDriveSelected = TRUE;
								MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
							}
						}
						else
						{
							//Failed to connect drive, back to media type select page
							MApp_DMP_ClearDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
							MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
						}                  
					}
					return TRUE;
				}
#endif
                U16 u16FileIdx = MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY);
                MPlayerFileInfo fileInfo;

            #if EN_DMP_SEARCH_ALL
               MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_FILE_PAGE_PLAYBACK);
               return TRUE;
            #endif
                if((0 == u16FileIdx) && 
					(0 == MApp_MPlayer_QueryDirectoryDepth()) &&   //wht1203017_1  if(u16FileIdx == 0)
					(1 != MApp_MPlayer_QueryTotalDriveNum()))
                {
	                #if REMOVE_DRIVE_SELECT_TO_FILE_LIST
					bIsDriveSelected = FALSE;
					MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
					#else					     
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);//wht120307_3 DMP_UI_STATE_DRIVE_SELECT -> DMP_UI_STATE_MEDIA_SELECT
                    #endif  
                }
                else if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                              u16FileIdx,
                                              &fileInfo) == E_MPLAYER_RET_OK)
                {
                    if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                    {
                        // TODO: refine here
                    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                        _MApp_DMP_Thumbnail_ChangePage();
                    #endif

                    #if ENABLE_MPLAYER_RECORD_DIR_ENTRY
                        U16 u16DirDepth = MApp_MPlayer_QueryDirectoryDepth();
                        if(!(u16DirDepth > 0 && u16FileIdx == 0)) //wht1203017_1  if(!(u16DirDepth > 0 && u16FileIdx == 1))
                        {
                            printf("Record DIR info ...\n");
                            _u16FileIdxByDir[u16DirDepth] = u16FileIdx;
                        }
						//MApp_MPlayer_QueryDirectoryNode(_u16FileIdxByDir,MApp_MPlayer_QueryDirectoryDepth());
                    #endif

                        if(MApp_MPlayer_EnterDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                                       u16FileIdx) == E_MPLAYER_RET_OK)
                        {
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                        #if ENABLE_MPLAYER_RECORD_DIR_ENTRY
                          if((u16DirDepth > 0 && u16FileIdx == 0)) //wht1203017_1  if(u16DirDepth > 0 && u16FileIdx == 1)
                            {//Go to prev. directory...
								printf("E_MPLAYER_INDEX_CURRENT_DIRECTORY 2 ");
                                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, _u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]);
                                MApp_MPlayer_SetCurrentPageIndex(_u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]/NUM_OF_PHOTO_FILES_PER_PAGE);
                                MApp_ZUI_API_SetFocus(_hwndListFileItem[_u16FileIdxByDir[MApp_MPlayer_QueryDirectoryDepth()]%NUM_OF_PHOTO_FILES_PER_PAGE]);
                            }
                            else
                        #endif
                            {
                                #if 1//wht120815_1
                                if(1 == MApp_MPlayer_QueryTotalFileNum())
                                {
									MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_THUMB_ITEM1); 
							    }
							    else
							    {
									MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 1);
									MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_THUMB_ITEM2); 
									if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY))) //add by gchen @ 20110616
									{
										//File type
										_MApp_ACTdmp_ShowPreviewWin();
									}		
							    }
                                #endif
                            }
                        }
//>>wht1203017_6		
#if ENABLE_PROGRESS_BAR
						U32 u32Percent = 0; //add by gchen @ 20110426
						u32Percent = (MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) + 1) * 100 / 
						MApp_MPlayer_QueryTotalFileNum();
						MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
						DMP_DBG(printf("u32Persent = %u\n", u32Percent));
						MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_PAGE_SELECT_PROGRESS_BAR);	
#endif
//<<wht1203017_6						
                    }
                    else
                    {
                    	MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_FILE_PAGE_PLAYBACK); //wht1203017_7 
                    /*
                        if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
                        {
                            MApp_MPlayer_SetFileUnselected(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16FileIdx);
                            MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());
                        }
                        else
                        {
                            MApp_MPlayer_SetFileSelected(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16FileIdx);
                            MApp_ZUI_API_InvalidateAllSuccessors(MApp_ZUI_API_GetFocus());
                        }*/
                        
                    }
                    return TRUE;
                }
            }
			
            break;
        case EN_EXE_DMP_FILE_PAGE_EXIT:
            {
                 MApp_MPlayer_StopPreview();
                 MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
            }
            break;
        case EN_EXE_DMP_FILE_PAGE_PLAYBACK:
            {
                MApp_ZUI_API_EnableWindow(HWND_DMP_PLAYBACK_INFOBAR_GROUP,TRUE);
                // check if there is files need to be played
                // put some initial variable or initial call before mapp_mplayer_play
                m_u16PlayErrorNum = 0;
                U16 u16LastFileIdx = MApp_MPlayer_QueryTotalFileNum() - 1;
                MPlayerFileInfo FileInfo;
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
                MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16LastFileIdx,&FileInfo);
                if( !(FileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY) /*for no-select files*/
                    || MApp_MPlayer_QuerySelectedFileNum(MApp_MPlayer_QueryCurrentMediaType() /*for selected files*/))
                {
                    _u8InfoBarIdx = 0;
					u8InfobarIdxTemp=0;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PAGE,SW_HIDE);
                    //_MApp_ACTdmp_HidePreviewWin();
                    // TODO: set this flag earlier!!! care this
                    MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);

                    enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    //MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_LOADING);
                    DMP_DBG(printf("EN_EXE_DMP_FILE_PAGE_PLAYBACK type %u\n",eMediaType););

                    if(MApp_MPlayer_QuerySelectedFileNum(eMediaType))
                    {
                        MApp_MPlayer_SetPlayMode(E_MPLAYER_PLAY_SELECTED_FROM_CURRENT);
                    }
                    else
                    {
                        MApp_MPlayer_SetPlayMode(E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT);
                    }
                    // TODO: repeat mode?
                    if ((MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_ALL) && (MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_NONE) && (MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_1))
                    {
                        MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                    }

                    switch(eMediaType)
                    {
                        // TODO: fix me: every type of media
                        case E_MPLAYER_TYPE_PHOTO:
                        {
							MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                            // put here or notify:"before play one file"?
                            if(MApp_MPlayer_QueryPhotoPlayMode() != E_MPLAYER_PHOTO_NORMAL)
                            {
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_NORMAL);
                            }
                            // reset slide show timer(in MPlayer)

                            MApp_MPlayer_SetPhotoSlideShowDelayTime(DEFAULT_PHOTO_SLIDESHOW_DELAY_TIME);
                        }
                        break;
                        case E_MPLAYER_TYPE_MUSIC:
                        {
                            // TODO: fix me
                            if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                            {
                                MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                                // open music info page
                            }
		#if ENABLE_BGM
		              if(MApp_MPlayer_IsMusicPlaying())
			        {
			             MApp_MPlayer_StopMusic();
		               }
		#endif
#if 0
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
#endif
                        }
                        break;
                        case E_MPLAYER_TYPE_MOVIE:
                        {
                            // TODO: need to find a time or stage to initialize
                            // these variables....
                            // dont touch vdplayer before mapp_mplayer_play()!!
                            //MApp_MPlayer_MovieSetRepeatAB(E_MPLAYER_MOVIE_SET_REPEAT_AB_NONE);

                        }
                        break;
						//>>wht120612_2
						case E_MPLAYER_TYPE_TEXT:
                        {
		                    if (MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_ALL)
		                    {
		                        MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
		                    }
                        }
                        break;
						//<<wht120612_2
                        default:
                            break;
                    }
                }
                else
                {
                    // there is no media files...
                }
            }
            break;
			/*
        case EN_EXE_DMP_FILE_PAGE_SUBMENU:
            {
                //_MApp_ACTdmp_HidePreviewWin();
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);
                //_MApp_ACTdmp_ShowSubMenu();
            }
            break; 
        case EN_EXE_DMP_SUBMENU_EXIT:
            {
                _MApp_ACTdmp_HideSubMenu();
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS, (m_bCopyOn==TRUE)?SW_SHOW:SW_HIDE);
                #endif
            }
            break;
        case EN_EXE_DMP_SUBMENU_SEL:
            {
                if(0)
                {
                }
#if(ENABLE_DELETE_SELECTED_FILES == ENABLE)
                else if(MApp_ZUI_API_GetFocus() == HWND_DMP_FILE_PAGE_SUBMENU_DELETE)
                {
                    if (MApp_MPlayer_QueryPlayListFileNum(MApp_MPlayer_QueryCurrentMediaType()) == 0)
                    {
                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_NEED_TO_SELECT_DELETE_FILE);
                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                    }
                    else
                    {
                        MApp_ZUI_API_StoreFocusCheckpoint();
                        MApp_ZUI_API_ShowWindow(HWND_DMP_DELETE_CONFIRM_DIALOG, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_DMP_DELETE_CONFIRM_NO);
                    }
                }
#endif
#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                else if(MApp_ZUI_API_GetFocus() == HWND_DMP_FILE_PAGE_SUBMENU_COPY)
                {
                    if (m_bCopyOn == TRUE)
                    {
                        if (MApp_MPlayer_QueryPlayListFileNum(MApp_MPlayer_QueryCurrentMediaType()) == 0)
                        {
                            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_NEED_TO_SELECT_COPY_FILE);
                            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                        }
                        else
                        {
                            _MApp_ACTdmp_File_Copy();
                            m_bCopyOn = FALSE;

                            _MApp_ACTdmp_HideSubMenu();
                            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

                            MApp_ZUI_API_RestoreFocusCheckpoint();

                            MApp_MPlayer_ExitCopyMode();
                        }
                    }
                    else
                    {
                        if (MApp_MPlayer_QueryPlayListFileNum(MApp_MPlayer_QueryCurrentMediaType()) == 0)
                        {
                            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_NEED_TO_SELECT_COPY_FILE);
                            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                        }
                        else
                        {
                            MApp_ZUI_API_StoreFocusCheckpoint();
                            MApp_ZUI_API_ShowWindow(HWND_DMP_COPY_CONFIRM_DIALOG, SW_SHOW);
                            MApp_ZUI_API_SetFocus(HWND_DMP_COPY_CONFIRM_NO);
                        }
                    }
                }
                else if(MApp_ZUI_API_GetFocus() == HWND_DMP_FILE_PAGE_SUBMENU_CANCEL)
                {
                    if (m_bCopyOn == TRUE)
                    {
                        MApp_ZUI_API_StoreFocusCheckpoint();
                        MApp_ZUI_API_ShowWindow(HWND_DMP_CANCEL_CONFIRM_DIALOG, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_DMP_CANCEL_CONFIRM_NO);
                    }
                }
                else if(MApp_ZUI_API_GetFocus() == HWND_DMP_FILE_PAGE_SUBMENU_FORMAT)
                {
                    MApp_ZUI_API_StoreFocusCheckpoint();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FORMAT_CONFIRM_DIALOG, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DMP_FORMAT_CONFIRM_NO);
                }
#endif
                #if 0
                else if(MApp_ZUI_API_GetFocus() == HWND_DMP_FILE_PAGE_SUBMENU_PASTE)
                {
                    //_MApp_ACTdmp_File_Paste will handle error cases by itself.
                    if (_MApp_ACTdmp_File_Paste())
                    {
                        _MApp_ACTdmp_HideSubMenu();
                        //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                    }
                }
                #endif
#if ENABLE_MPLAYER_SORT_EX
                else if(MApp_ZUI_API_GetFocus() == HWND_DMP_FILE_PAGE_SUBMENU_SORT)
                {
                    MApp_ZUI_API_StoreFocusCheckpoint();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_GROUP, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_GROUP, SW_SHOW);

                    MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_TYPE_ITEM,TRUE);
                    if (MApp_MPlayer_QueryCurrentFileSortingMode() == E_MPLAYER_SORT_NONE)
                    {
                        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_ITEM,FALSE);
                    }
                    else
                    {
                        MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_ITEM,TRUE);
                    }
                    MApp_ZUI_API_SetFocus(HWND_DMP_FILE_PAGE_SUBMENU_SORT_TYPE_ITEM);
                }
#endif
                else
                {
                    _MApp_ACTdmp_HideSubMenu();
                    //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                    #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS, (m_bCopyOn==TRUE)?SW_SHOW:SW_HIDE);
                    #endif
                }
            }
            break;
			*/
#if ENABLE_MPLAYER_SORT_EX
        case EN_EXE_DMP_SUBMENU_SORT_TYPE_TEXT_R:
        case EN_EXE_DMP_SUBMENU_SORT_TYPE_TEXT_L:
            {
                enumMPlayerFileSortMode CurFileSortingMode;
                CurFileSortingMode = MApp_MPlayer_QueryCurrentFileSortingMode();

                CurFileSortingMode= (enumMPlayerFileSortMode)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_DMP_SUBMENU_SORT_TYPE_TEXT_R,
                    CurFileSortingMode, E_MPLAYER_SORT_NONE, E_MPLAYER_SORT_TYPE_NUM-1, 1);

                if(MApp_MPlayer_QueryCurrentFileSortingMode()!=CurFileSortingMode)
                {
                    MApp_MPlayer_ReSortFileBrowser(CurFileSortingMode, MApp_MPlayer_QueryCurrentFileSortingOrderMode());
                }

                if (CurFileSortingMode == E_MPLAYER_SORT_NONE)
                    MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_ITEM,FALSE);
                else
                    MApp_ZUI_API_EnableWindow(HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_ITEM,TRUE);

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_PAGE_SUBMENU_SORT_TYPE_ITEM);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_ITEM);
            }
            break;

        case EN_EXE_DMP_SUBMENU_SORT_ORDER_TEXT_R:
        case EN_EXE_DMP_SUBMENU_SORT_ORDER_TEXT_L:
            {
                enumMPlayerFileSortSubMode CurFileSortingOrder;
                CurFileSortingOrder = MApp_MPlayer_QueryCurrentFileSortingOrderMode();

                CurFileSortingOrder= (enumMPlayerFileSortSubMode)MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_DMP_SUBMENU_SORT_ORDER_TEXT_R,
                    CurFileSortingOrder, E_MPLAYER_SORT_INCREMENT_ORDER, E_MPLAYER_ORDER_TYPE_NUM-1, 1);

                if(MApp_MPlayer_QueryCurrentFileSortingOrderMode()!=CurFileSortingOrder)
                {
                    MApp_MPlayer_ReSortFileBrowser(MApp_MPlayer_QueryCurrentFileSortingMode(), CurFileSortingOrder);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_ITEM);
            }
            break;

        case EN_EXE_DMP_SUBMENU_SORT_EXIT:
            {
                _MApp_DMP_Thumbnail_ChangePage();
                _MApp_ACTdmp_HideSubMenu();
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS, SW_HIDE);
            }
            break;
#endif
		
        case EN_EXE_DMP_PROGRESS_EXIT:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
            #if (ENABLE_DELETE_SELECTED_FILES == ENABLE)
                if (MApp_MPlayer_IsDeleting() == TRUE)
                {
                    MApp_MPlayer_StopDelete();
                }
            #endif
            #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                if (MApp_MPlayer_IsCopying() == TRUE)
                {
                    MApp_MPlayer_StopCopy();
                }
            #endif
                MApp_ZUI_API_ShowWindow(HWND_DMP_PROGRESS_STOP, SW_SHOW);
                _MApp_ZUI_API_WindowProcOnIdle();
                MsOS_DelayTask(500);
            }
            break;

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
        case EN_EXE_DMP_COPY_CONFIRM_DIALOG_YES:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                if (m_bCopyOn == FALSE)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_COPY_CONFIRM_DIALOG, SW_HIDE);
                    m_bCopyOn = TRUE;

                    _MApp_ACTdmp_HideSubMenu();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_SHOW);

                    MApp_ZUI_API_RestoreFocusCheckpoint();

                    MApp_MPlayer_EnterCopyMode();
                }
            }
            break;

        case EN_EXE_DMP_COPY_CONFIRM_DIALOG_NO:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_COPY_CONFIRM_DIALOG, SW_HIDE);
                m_bCopyOn = FALSE;

                _MApp_ACTdmp_HideSubMenu();
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

                MApp_ZUI_API_RestoreFocusCheckpoint();

                MApp_MPlayer_ExitCopyMode();
            }
            break;

        case EN_EXE_DMP_CANCEL_CONFIRM_DIALOG_YES:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                if (m_bCopyOn == TRUE)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_CANCEL_CONFIRM_DIALOG, SW_HIDE);
                    m_bCopyOn = FALSE;

                    _MApp_ACTdmp_HideSubMenu();
                    //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

                    MApp_ZUI_API_RestoreFocusCheckpoint();

                    MApp_MPlayer_ExitCopyMode();
                }
            }
            break;

        case EN_EXE_DMP_CANCEL_CONFIRM_DIALOG_NO:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_CANCEL_CONFIRM_DIALOG, SW_HIDE);

                _MApp_ACTdmp_HideSubMenu();
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_SHOW);

                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            break;
#endif

#if ENABLE_DELETE_SELECTED_FILES
        case EN_EXE_DMP_DELETE_CONFIRM_DIALOG_YES:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_DELETE_CONFIRM_DIALOG, SW_HIDE);

                if(_MApp_ACTdmp_File_Delete())
                {
                    _MApp_ACTdmp_HideSubMenu();
                    //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

                    MApp_ZUI_API_RestoreFocusCheckpoint();
                }
                else
                {
                    //Failed to delete file
                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_DELETE_FILE_ERROR);
                    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                }
            }
            break;

        case EN_EXE_DMP_DELETE_CONFIRM_DIALOG_NO:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_DELETE_CONFIRM_DIALOG, SW_HIDE);
                _MApp_ACTdmp_HideSubMenu();
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);
            }
            break;
#endif

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
        case EN_EXE_DMP_FORMAT_CONFIRM_DIALOG_YES:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_FORMAT_CONFIRM_DIALOG, SW_HIDE);
                _MApp_ACTdmp_File_Format();
            }
            break;

        case EN_EXE_DMP_FORMAT_CONFIRM_DIALOG_NO:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_FORMAT_CONFIRM_DIALOG, SW_HIDE);
                _MApp_ACTdmp_HideSubMenu();
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);
            }
            break;
#endif
		
		/*PLAYBACK_INFOBAR*/
        case EN_EXE_DMP_PLAYBACK_INFOBAR_LEFT:
        DMP_DBG(printf(" - EN_EXE_DMP_PLAYBACK_INFOBAR_LEFT\n"));
        {
            U8 u8InfoBarMax=0;
			if(u8InfobarIdxTemp>=1)
				u8InfobarIdxTemp -=1;
			else//µÚÒ»¸öµÄÊ±ºò£¬×ªµ½×îºóÒ»¸ö
			{
	            switch(MApp_MPlayer_QueryCurrentMediaType())
	            {
	                case E_MPLAYER_TYPE_MOVIE:
							u8InfobarIdxTemp=u8MovieInfoBarMax-1;
	                    break;
	                case E_MPLAYER_TYPE_MUSIC:
							u8InfobarIdxTemp=u8MusicInfoBarMax-1;
	                    break;
	                case E_MPLAYER_TYPE_PHOTO:
							u8InfobarIdxTemp=u8PhotoInfoBarMax-1;
	                    break;
	                case E_MPLAYER_TYPE_TEXT:
							u8InfobarIdxTemp=u8TextInfoBarMax-1;
	                    break;
	                default:
	                    break;
	            }
			}
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MOVIE:
                    u8InfoBarMax = u8MovieInfoBarMax;
					if (u8InfobarIdxTemp >= u8MovieInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   						
						MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_MUSIC:
                    u8InfoBarMax = u8MusicInfoBarMax;
					if (u8InfobarIdxTemp >= u8MusicInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   	
					    if(u8InfobarIdxTemp>=6)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_PHOTO:
                    u8InfoBarMax = u8PhotoInfoBarMax;
					if (u8InfobarIdxTemp >= u8PhotoInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   						
					    if(u8InfobarIdxTemp>=4)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_TEXT:
                    u8InfoBarMax = u8TextInfoBarMax;
					if (u8InfobarIdxTemp >= u8TextInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   						
					    if(u8InfobarIdxTemp>=5)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+9]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                default:
                    break;
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            return TRUE;
        }
        break;
        /*PLAYBACK_INFOBAR*/
/*case EN_EXE_DMP_PLAYBACK_INFOBAR_LEFT:
        DMP_DBG(printf(" - EN_EXE_DMP_PLAYBACK_INFOBAR_LEFT\n"));
        {
            U8 u8InfoBarMax=0;
			if(u8InfobarIdxTemp>=1)
				u8InfobarIdxTemp -=1;
			else//µÚÒ»¸öµÄÊ±ºò£¬×ªµ½×îºóÒ»¸ö
			{
	            switch(MApp_MPlayer_QueryCurrentMediaType())
	            {
	                case E_MPLAYER_TYPE_MOVIE:
							u8InfobarIdxTemp=u8MovieInfoBarMax-1;
	                    break;
	                case E_MPLAYER_TYPE_MUSIC:
							u8InfobarIdxTemp=u8MusicInfoBarMax-1;
	                    break;
	                case E_MPLAYER_TYPE_PHOTO:
							u8InfobarIdxTemp=u8PhotoInfoBarMax-1;
	                    break;
	                case E_MPLAYER_TYPE_TEXT:
							u8InfobarIdxTemp=u8TextInfoBarMax-1;
	                    break;
	                default:
	                    break;
	            }
			}
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MOVIE:
                    u8InfoBarMax = u8MovieInfoBarMax;
					if (u8InfobarIdxTemp >= u8MovieInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   						
						MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_MUSIC:
                    u8InfoBarMax = u8MusicInfoBarMax;
					if (u8InfobarIdxTemp >= u8MusicInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   	
					    if(u8InfobarIdxTemp>=6)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_PHOTO:
                    u8InfoBarMax = u8PhotoInfoBarMax;
					if (u8InfobarIdxTemp >= u8PhotoInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   						
					    if(u8InfobarIdxTemp>=4)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_TEXT:
                    u8InfoBarMax = u8TextInfoBarMax;
					if (u8InfobarIdxTemp >= u8TextInfoBarMax)
					{
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM17); 
					}
					else
					{   						
					    if(u8InfobarIdxTemp>=5)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+8]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                default:
                    break;
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            return TRUE;
        }
        break;
		*/
        /*case EN_EXE_DMP_PLAYBACK_INFOBAR_RIGHT:
        DMP_DBG(printf(" - EN_EXE_DMP_PLAYBACK_INFOBAR_RIGHT\n"));
        {
			
            U8 u8InfobarIdx = _u8InfoBarIdx + 1; // 1 base
            u8InfobarIdx += (MApp_ZUI_API_GetFocus() - HWND_DMP_PLAYBACK_INFOBAR_ITEM1)/3;

            U8 u8InfoBarMax = _MApp_ZUI_ACT_Get_InfoBarMax();

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
            if (((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)&&(DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_REPEAT))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)&&(DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_RANDOM))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)&&(DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMOUT))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)&&(DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_MOVEVIEW))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)&&(DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_SLIDESHOW))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)&&(DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MUSICINFO_REPEAT))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)&&(DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MUSICINFO_RANDOM))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)&&(DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MUSICINFO_GOTO_TIME))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_REPEAT))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_RANDOM))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_SF))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_SD))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_GOTO_TIME))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMOUT))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_ASPECT_RATIO))
                ||((MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)&&(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_MOVEVIEW))
                        )
            {
                if(u8InfobarIdx%8 == 0) // reset to 1st item
                {
                    _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation((MApp_ZUI_API_GetFocus() - 24)+ 5, TRUE);
                }
                else
                {
                    _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(MApp_ZUI_API_GetFocus() + 5, TRUE);
                }
            }
#endif
            //last term
            if (u8InfobarIdx == u8InfoBarMax)
            {
                return TRUE;
            }
            //not 8th term in current infobar page, do navigation
            else if(u8InfobarIdx < (_u8InfoBarIdx + DMP_INFOBAR_ICON_NUM))
            {
                return FALSE;
            }
            //8th  term in current infobar page
            else
            {
                S32 i;
                _u8InfoBarIdx+=DMP_INFOBAR_ICON_NUM;
                // if next page is last page
                if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8InfoBarMax)
                {
                    for ( i = DMP_INFOBAR_ICON_NUM; i > u8InfoBarMax -_u8InfoBarIdx; i--)
                    {
                        MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], FALSE);
                    }
                }
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                return TRUE;
            }
        }
        break;
		*/
		case EN_EXE_DMP_PLAYBACK_INFOBAR_RIGHT:
        DMP_DBG(printf(" - EN_EXE_DMP_PLAYBACK_INFOBAR_RIGHT\n"));
        {
            
            U8 u8InfoBarMax=0;
			u8InfobarIdxTemp +=1;
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MOVIE:
                    u8InfoBarMax = u8MovieInfoBarMax;
					if (u8InfobarIdxTemp >= DMP_INFOBAR_ICON_NUM)
					{
						u8InfobarIdxTemp= 0;
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1); 
					}
					else
					{   						
						MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_MUSIC:
                    u8InfoBarMax = u8MusicInfoBarMax;
					if (u8InfobarIdxTemp >= u8MusicInfoBarMax)
					{
						u8InfobarIdxTemp= 0;
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1); 
					}
					else
					{   
					    if(u8InfobarIdxTemp>=6)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_PHOTO:
                    u8InfoBarMax = u8PhotoInfoBarMax;
					if (u8InfobarIdxTemp >= u8PhotoInfoBarMax)
					{
						u8InfobarIdxTemp= 0;
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1); 
					}
					else
					{   
					    if(u8InfobarIdxTemp>=4)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                case E_MPLAYER_TYPE_TEXT:
                    u8InfoBarMax = u8TextInfoBarMax;
					if (u8InfobarIdxTemp >= u8TextInfoBarMax)
					{
						u8InfobarIdxTemp= 0;
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1); 
					}
					else
					{   
					    if(u8InfobarIdxTemp>=5)
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+9]);
						else
							MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
					}
                    break;
                default:
                    break;
            }
			MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
			#if 0
            //last term
            if (u8InfobarIdx == u8InfoBarMax)
            {
            #if 0  // truth.xu delete for xun huan select 20100629
                return TRUE;
	     #endif
  //<<truth.xu add for xun huan select 20100629
	      	{    S32 i;
                _u8InfoBarIdx=0;
                    for (i = DMP_INFOBAR_ICON_NUM; i > 0; i--)
                    {
                        MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], TRUE);
                    }
                 MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                 MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                 return TRUE;
		}
 //truth.xu add for xun huan select 20100629>>
            }
            //not 8th term in current infobar page, do navigation
            else if(u8InfobarIdx < (_u8InfoBarIdx + DMP_INFOBAR_ICON_NUM))
            {
            DMP_DBG(printf("not 8th term in current infobar page, do navigation \n"));
                return FALSE;
            }
            //8th  term in current infobar page
            else
            {
            DMP_DBG(printf("8th  term in current infobar page\n"));
                S32 i;
                _u8InfoBarIdx+=DMP_INFOBAR_ICON_NUM;
                // if next page is last page
                if (_u8InfoBarIdx+DMP_INFOBAR_ICON_NUM > u8InfoBarMax)
                {
                    for ( i = DMP_INFOBAR_ICON_NUM; i > u8InfoBarMax -_u8InfoBarIdx; i--)
                    {
                        MApp_ZUI_API_EnableWindow(_hwndListInfoBar[i-1], FALSE);
                    }
                }
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                return TRUE;
            }
			#endif
        }
        break;
		case EN_EXE_DMP_PLAYBACK_INFOBAR_DOWN:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_INFO_CLOSE\n"););
            {   //>>wht120815_3
				if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)					
				{
					//MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_BG_EXIT);
				}
				else //<<wht120815_3
				{
                	_MApp_ACTdmp_Playback_HideInfoWin();
				}
                _MApp_ZUI_ACTdmp_OperateSubtitle();
            }
            break;
        case EN_EXE_DMP_PLAYBACK_INFOBAR_SELECT:
        {
            U16 focushwnd = MApp_ZUI_API_GetFocus();
            U32 i,j;
            for( i = 0; i < DMP_INFOBAR_ICON_NUM ; i++)
            {
                if(focushwnd == _hwndListInfoBar[i])
                {
                    break;
                }
            }
			if(focushwnd == _hwndListInfoBar[0]){
						msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, 0, 0);
			}
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
					if(focushwnd == _hwndListInfoBar[0]){
						msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
					}
                    j = (_u8InfoBarIdx+i);
					return MApp_ZUI_ACT_ExecuteDmpAction(DMP_MovieInfoBarTable[j][INFOBAR_ACT_IDX]);
                #endif
                case E_MPLAYER_TYPE_MUSIC:
					if(focushwnd == _hwndListInfoBar[0]){
						msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
					}
                    j = (_u8InfoBarIdx+i);
					if(j<6)
                    	return MApp_ZUI_ACT_ExecuteDmpAction(DMP_MusicInfoBarTable[j][INFOBAR_ACT_IDX]);
					else
						return MApp_ZUI_ACT_ExecuteDmpAction(DMP_MusicInfoBarTable[j-7][INFOBAR_ACT_IDX]);
                case E_MPLAYER_TYPE_PHOTO:
                    j = (_u8InfoBarIdx+i);
					if(j<4)
                    	return MApp_ZUI_ACT_ExecuteDmpAction(DMP_PhotoInfoBarTable[j][INFOBAR_ACT_IDX]);
					else
						return MApp_ZUI_ACT_ExecuteDmpAction(DMP_PhotoInfoBarTable[j-4][INFOBAR_ACT_IDX]);
                #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    j = (_u8InfoBarIdx+i);
					if(j<5)
                    	return MApp_ZUI_ACT_ExecuteDmpAction(DMP_TextInfoBarTable[j][INFOBAR_ACT_IDX]);
					else
						return MApp_ZUI_ACT_ExecuteDmpAction(DMP_TextInfoBarTable[j-9][INFOBAR_ACT_IDX]);
                #endif
                default:
                    break;
            }

        }
        break;
   //
        case EN_EXE_DMP_PLAYBACK_BG_EXIT:
			msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, 0, 0);
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BG_EXIT\n"););
            _u8InfoBarIdx = 0;
			u8InfobarIdxTemp=0;
			
          #if ENABLE_DVD
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                DMP_DBG(printf("VK_STOP in DVD\n"));

                MApp_MPlayer_Stop();
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                //msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                //MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            }
            else
          #endif  // ENABLE_DVD
            {
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
						msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);//wht120615_5
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        //if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                        {
#if (ENABLE_SUBTITLE_DMP)
                            MApp_MPlayer_DisableSubtitle();
#endif
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                        }
                        MApp_MPlayer_Stop();
						 msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);//wht120615_5
                    break;
                    #endif
                    case E_MPLAYER_TYPE_MUSIC:
						// go into BGM mode !!
                        MApp_DMP_SetDmpFlag(DMP_FLAG_BGM_MODE);
                        if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                        {
                            MApp_MPlayer_DisableLRCLyric();
                            memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE, SW_HIDE);
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_LYRIC_PAGE);
                        }
                        _u16MusicCurrentTime = 0;
						MApp_MPlayer_Stop();//wht121121_3
                        MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                        MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
						#if ENABLE_MUSIC_EQ_MODE
                        MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP,SW_HIDE);
						#endif
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE, SW_HIDE);

                    break;
                    default:
                        MApp_MPlayer_Stop();
                        break;
                }
                //msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

                //MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                //MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                MApp_ZUI_API_InvalidateWindow(HWND_MAINFRAME);
            }
            // set the file_select index and current page index
            // TODO: across dir, across drive?
            {
                U16 u16PlayingIdx = 0;
                // TODO: fix photo type
            #if !EN_DMP_SEARCH_ALL
                if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
                {
                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
                }
            #endif
                u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
                MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx/NUM_OF_PHOTO_FILES_PER_PAGE);
                DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););
                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
                {
                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                    MApp_MPlayer_SetCurrentPageIndex(0);
                }
            }
			msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            break;
        case EN_EXE_DMP_PLAYBACK_BG_INFO:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_BG_INFO\n"););
              #if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    U8 ret;

                    DMP_DBG(printf("VK_ENTER in DVD\n"));
                    ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_ENTER);
                    if (!ret)
                        _MApp_ACTdmp_Playback_ShowInfoWin(MApp_MPlayer_QueryCurrentMediaType());
                }
                else
              #endif  // ENABLE_DVD
                _MApp_ACTdmp_Playback_ShowInfoWin(MApp_MPlayer_QueryCurrentMediaType());
				_MApp_ZUI_ACTdmp_OperateSubtitle();
            }
            break;

        case EN_EXE_DMP_PLAYBACK_INFO_CLOSE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_INFO_CLOSE\n"););
            {   //>>wht120815_3
				if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)					
				{
					MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_BG_EXIT);
				}
				else //<<wht120815_3
				{
                	_MApp_ACTdmp_Playback_HideInfoWin();
				}
                _MApp_ZUI_ACTdmp_OperateSubtitle();
            }
            break;

//=========MOVIEINFO_info key=============
#if (ENABLE_MPLAYER_MOVIE)
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_PLAYLIST:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_INFO_PLAYLIST\n"););
                u8CurrentPlaylistPageIdx = 0;
                u8CurrentPlaylistTotalPage = 1;
                _MApp_ACTdmp_Playback_ShowPlaylistWin(E_MPLAYER_TYPE_MOVIE, TRUE);
            }
			break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_NEXT:
          #if ENABLE_DVD
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                U8 ret;

                DMP_DBG(printf("VK_NEXT in DVD\n"));
                ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_NEXT);
            }
            else
          #endif  // ENABLE_DVD
            {
                //if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                {
#if (ENABLE_SUBTITLE_DMP)
                   MApp_MPlayer_DisableSubtitle();
#endif
                   MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                }
                MApp_MPlayer_PlayNextFile();
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MOVIE, DEFAULT_MOVIE_ERROR_DELAY_TIME);
            }
            m_u16PlayErrorNum = 0;
            #if (ENABLE_DRM)
            m_u16DRMErrorNum = 0;
            #endif
            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE; IsPause = 1 ;
            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_NEXT;
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV:
          #if ENABLE_DVD
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                U8 ret;

                DMP_DBG(printf("VK_PREV1 in DVD\n"));
                ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_PREV);
            }
            else
          #endif  // ENABLE_DVD
            {
                //if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                {
#if (ENABLE_SUBTITLE_DMP)
                    MApp_MPlayer_DisableSubtitle();
#endif
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                }
                g_bPlayPrev = TRUE;
                MApp_MPlayer_PlayPrevFile();
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MOVIE, DEFAULT_MOVIE_ERROR_DELAY_TIME);
            }
            m_u16PlayErrorNum = 0;
            #if (ENABLE_DRM)
            m_u16DRMErrorNum = 0;
            #endif
            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE; IsPause = 1 ;
            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PREVIOUS;
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            break;
#if ENABLE_DRM
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_BEGIN:
            m_u16PlayErrorNum = 0;
            #if (ENABLE_DRM)
            m_u16DRMErrorNum = 0;
            #endif
            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PREVIOUS;
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PREV_BUTTON_CLICK_WIN, DMP_TIME_MS_PREV_BUTTON_CLICK_WIN);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV_CLICK:
            if (msAPI_Timer_DiffTimeFromNow(u32PrevButtonTimer) > DMP_TIME_MS_PREV_BUTTON_CLICK_WIN)
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV);
            }
            else
            {
                MApp_ZUI_ACT_ExecuteDmpAction( EN_EXE_DMP_PLAYBACK_MOVIEINFO_PREV);
                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PREV_BUTTON_CLICK_WIN);
            }
            u32PrevButtonTimer = msAPI_Timer_GetTime0();
            break;
#endif
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_SF:
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = TRUE;
        #endif
            {
                enumMPlayerMoviePlayMode ePlayMode = MApp_MPlayer_QueryMoviePlayMode();
                 _MApp_ACTdmp_MovieCancelRepeatAB();
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                if(!(ePlayMode >= E_MPLAYER_MOVIE_SF_2X && ePlayMode <= E_MPLAYER_MOVIE_SF_16X))
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_2X);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SF2X;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE; IsPause = 1 ;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_SF_2X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_4X);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SF4X;
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_SF_4X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_8X);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SF8X;
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_SF_8X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_16X);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SF16X;
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_SF_16X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                }
                if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN))
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                if (_enDmpPlayIconType == PLAY_MODE_ICON_PLAY)
                {
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                }
            }
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = FALSE;
        #endif
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_SD:
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = TRUE;
        #endif
            {
                _MApp_ACTdmp_MovieCancelRepeatAB();
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                _enDmpPlayStrType = _enDmpPlayIconType = PLAY_MODE_ICON_SD;
                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_STEP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            }
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = FALSE;
        #endif
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_FF:
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = TRUE;
        #endif
          #if ENABLE_DVD
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                U8 ret;

                DMP_DBG(printf("VK_FF in DVD\n"));

                if (!MApp_VDPlayer_DVD_IsAllowed(E_MPLAYER_DVD_CMD_FF))
                    break;

                ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_FF);

                switch (ret)
                {
                    case 1:
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF2X;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 2:
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF4X;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 3:
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF8X;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 4:
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF16X;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 5:
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF32X;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 6:
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                }
				IsPause = 1 ;
                if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN))
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                if (_enDmpPlayIconType == PLAY_MODE_ICON_PLAY)
                {
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                }
            }
            else
          #endif  // ENABLE_DVD
            {
                enumMPlayerMoviePlayMode ePlayMode = MApp_MPlayer_QueryMoviePlayMode();
                 _MApp_ACTdmp_MovieCancelRepeatAB();
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                if(!(ePlayMode >= E_MPLAYER_MOVIE_FF_2X && ePlayMode <= E_MPLAYER_MOVIE_FF_32X))
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_2X) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF2X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_FF_2X)
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_4X) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF4X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_FF_4X)
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_8X) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF8X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_FF_8X)
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_16X) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF16X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_FF_16X)
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_32X) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF32X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                else if(ePlayMode == E_MPLAYER_MOVIE_FF_32X)
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                if (_enDmpPlayIconType == PLAY_MODE_ICON_PLAY)
                {
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                }
            }
            #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = FALSE;
            #endif
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_FB:
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = TRUE;
        #endif
          #if ENABLE_DVD
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                U8 ret;

                DMP_DBG(printf("VK_FB in DVD\n"));

                if (!MApp_VDPlayer_DVD_IsAllowed(E_MPLAYER_DVD_CMD_FF))
                    break;

                ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_FB);

                switch (ret)
                {
                    case 1:
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB2X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 2:
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB4X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 3:
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB8X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 4:
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB16X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 5:
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB32X;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    case 6:
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        break;
                    default:
                        break;
                }
				IsPause = 1 ;
                if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN))
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                if (_enDmpPlayIconType == PLAY_MODE_ICON_PLAY || _enDmpPlayIconType == PLAY_MODE_ICON_FB_INVALID)
                {
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                }
            }
            else
          #endif
            {
                if(MApp_MPlayer_IsMovieIndexTableExist())
                {
                    enumMPlayerMoviePlayMode ePlayMode = MApp_MPlayer_QueryMoviePlayMode();
                    _MApp_ACTdmp_MovieCancelRepeatAB();
                    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                    if(!(ePlayMode >= E_MPLAYER_MOVIE_FB_2X && ePlayMode <= E_MPLAYER_MOVIE_FB_32X))
                    {
                        if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_2X) == E_MPLAYER_RET_OK)
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB2X;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        }
                    }
                    else if(ePlayMode == E_MPLAYER_MOVIE_FB_2X)
                    {
                        if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_4X) == E_MPLAYER_RET_OK)
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB4X;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        }
                    }
                    else if(ePlayMode == E_MPLAYER_MOVIE_FB_4X)
                    {
                        if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_8X) == E_MPLAYER_RET_OK)
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB8X;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        }
                    }
                    else if(ePlayMode == E_MPLAYER_MOVIE_FB_8X)
                    {
                        if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_16X) == E_MPLAYER_RET_OK)
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB16X;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        }
                    }
                    else if(ePlayMode == E_MPLAYER_MOVIE_FB_16X)
                    {
                        if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_32X) == E_MPLAYER_RET_OK)
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB32X;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        }
                    }
                    else if(ePlayMode == E_MPLAYER_MOVIE_FB_32X)
                    {
                        if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL) == E_MPLAYER_RET_OK)
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        }
                        else
                        {
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        }
                    }
                }
                else
                {
                    if(MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL) == E_MPLAYER_RET_OK)
                    {
                        _enDmpPlayStrType = _enDmpPlayIconType = PLAY_MODE_ICON_FB_INVALID;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                    else
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    }
                }
                if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN))
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_STATUS_GROUP);
                if ((_enDmpPlayIconType == PLAY_MODE_ICON_PLAY) || (_enDmpPlayIconType == PLAY_MODE_ICON_FB_INVALID))
                {
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                }
            }
            #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            bUIexist = FALSE;
            #endif
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_PLAY_PAUSE:
            {
                enumMPlayerMoviePlayMode eMoviePlayMode = MApp_MPlayer_QueryMoviePlayMode();

            #if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    U8 ret;

                    if (!MApp_VDPlayer_DVD_IsAllowed(E_MPLAYER_DVD_CMD_PLAY_PAUSE))
                        break;

                    ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_PLAY_PAUSE);
                    if (ret == 1)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                    }
                    else if (ret == 2)
                    {
                        _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    }
                }
                else
            #endif
                {
                if(eMoviePlayMode == E_MPLAYER_MOVIE_STOP)
                {
                    break;
                }
                if((eMoviePlayMode != E_MPLAYER_MOVIE_PAUSE) &&
                   (eMoviePlayMode != E_MPLAYER_MOVIE_STEP) )
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                }
                else
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                }
                }
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_STOP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_STOP\n"););
            MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_BG_EXIT);
/*
            _u8InfoBarIdx = 0;
        #if ENABLE_DVD
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                DMP_DBG(printf("VK_STOP in DVD\n"));
                MApp_MPlayer_Stop();
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            }
            else
        #endif  // ENABLE_DVD
            {
                _MApp_ACTdmp_MovieCancelRepeatAB();
                if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                {
                    MApp_MPlayer_DisableSubtitle();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                }
                msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                MApp_MPlayer_Stop();
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                MApp_ZUI_API_InvalidateWindow(HWND_MAINFRAME);
            }
            // set the file_select index and current page index
            // TODO: across dir, across drive?
            {
                U16 u16PlayingIdx = 0;
                if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
                {
                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
                }
                u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
                MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx/NUM_OF_MOVIE_FILES_PER_PAGE);
                DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););
                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
                {
                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                    MApp_MPlayer_SetCurrentPageIndex(0);
                }
            }
*/
            break;
#endif
#if ENABLE_GOTO_TIME
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_GOTO_TIME:
        {
            _u8Hour = 0;
            _u8Minute = 0;
            _u8Second = 0;
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_SHOW);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT1);

        #if ENABLE_ATSC_TTS
            U8 au8TmpBuf[2];
            au8TmpBuf[0] = _u8Hour + '0';
            au8TmpBuf[1] = 0;
            MApp_TTS_Cus_Add_Str_By_StrId(en_str_Hour);
            MApp_TTS_Cus_AddU8String(au8TmpBuf);
        #endif
        }
            break;
#endif
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM1:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM2:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM3:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM4:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM5:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM6:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM7:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM8:
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM9:
            {
            U8 u8digit = 0;
#if ENABLE_ATSC_TTS
            U8 u8timeinput[3] = {0,0,0};
#endif
            if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT1)
            {
                u8digit = _u8Hour % 10;
                _u8Hour = (U8)(act - EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0) * 10 + u8digit;
#if ENABLE_ATSC_TTS
                u8timeinput[0] = _u8Hour/10 + 0x30;
                u8timeinput[1] = _u8Hour%10 + 0x30;
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_Hour);
                MApp_TTS_Cus_AddU8String(u8timeinput);
                MApp_TTSControlSetOn(TRUE);
#endif
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT2)
            {
                u8digit = (_u8Hour / 10) * 10;
                _u8Hour = (U8)(act - EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0) + u8digit;
#if ENABLE_ATSC_TTS
                u8timeinput[0] = _u8Hour/10 + 0x30;
                u8timeinput[1] = _u8Hour%10 + 0x30;
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_Hour);
                MApp_TTS_Cus_AddU8String(u8timeinput);
                MApp_TTSControlSetOn(TRUE);
#endif
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_MINUTE_DIGIT1)
            {
                u8digit = _u8Minute % 10;
                _u8Minute = (U8)(act - EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0) * 10 + u8digit;
#if ENABLE_ATSC_TTS
                u8timeinput[0] = _u8Minute/10 + 0x30;
                u8timeinput[1] = _u8Minute%10 + 0x30;
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_min);
                MApp_TTS_Cus_AddU8String(u8timeinput);
                MApp_TTSControlSetOn(TRUE);
#endif
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_MINUTE_DIGIT2)
            {
                u8digit = (_u8Minute / 10) * 10;
                _u8Minute = (U8)(act - EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0) + u8digit;
#if ENABLE_ATSC_TTS
                u8timeinput[0] = _u8Minute/10 + 0x30;
                u8timeinput[1] = _u8Minute%10 + 0x30;
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_min);
                MApp_TTS_Cus_AddU8String(u8timeinput);
                MApp_TTSControlSetOn(TRUE);
#endif
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_SEC_DIGIT1)
            {
                u8digit = _u8Second % 10;
                _u8Second = (U8)(act - EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0) * 10 + u8digit;
#if ENABLE_ATSC_TTS
                u8timeinput[0] = _u8Second/10 + 0x30;
                u8timeinput[1] = _u8Second%10 + 0x30;
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_second);
                MApp_TTS_Cus_AddU8String(u8timeinput);
                MApp_TTSControlSetOn(TRUE);
#endif
            }
            else if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_SEC_DIGIT2)
            {
                u8digit = (_u8Second / 10) * 10;
                _u8Second = (U8)(act - EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_NUM0) + u8digit;
#if ENABLE_ATSC_TTS
                u8timeinput[0] = _u8Second/10 + 0x30;
                u8timeinput[1] = _u8Second%10 + 0x30;
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_second);
                MApp_TTS_Cus_AddU8String(u8timeinput);
                MApp_TTSControlSetOn(TRUE);
#endif
            }
            //invalid time?
            if(_u8Minute > 60)
            {
                _u8Minute = 59;
           MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_MINUTE_DIGIT1);
           MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_MINUTE_DIGIT2);
            }
            if(_u8Second > 60)
            {
                _u8Second = 59;
           MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_SEC_DIGIT1);
           MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_SEC_DIGIT2);
            }
            //printf("[Time] %02d:%02d:%02d\n", _u8Hour, _u8Minute, _u8Second);
            if(MApp_ZUI_API_GetFocus() != HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK)
            {
                MApp_ZUI_API_SetFocus((HWND)(MApp_ZUI_API_GetFocus()+1));
            }
        }
        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP);
        break;
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_EXIT:
        {
            enumMPlayerMediaType eMediaType= MApp_MPlayer_QueryCurrentMediaType();
            switch (eMediaType)
            {
            #if ENABLE_MPLAYER_MOVIE
                case E_MPLAYER_TYPE_MOVIE:
                    {
                        _u8Hour = 0;
                        _u8Minute = 0;
                        _u8Second = 0;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_HIDE);
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                        DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_SHOW);
						#if ENABLE_GOTO_TIME
                        if(MOVIEINFO_GOTO_TIME< _u8InfoBarIdx)
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_GOTO_TIME+u8MovieInfoBarMax -_u8InfoBarIdx]);
                        }
                        else
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_GOTO_TIME - _u8InfoBarIdx]);
                        }
						#endif
                    }
                    break;
            #endif
                case E_MPLAYER_TYPE_MUSIC:
                    {
                        _u8Hour = 0;
                        _u8Minute = 0;
                        _u8Second = 0;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_HIDE);
                        _MApp_ACTdmp_MusicCancelRepeatAB();
                        //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                        //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_SHOW);
						#if ENABLE_GOTO_TIME
                        if(MUSICINFO_GOTO_TIME< _u8InfoBarIdx)
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_GOTO_TIME+u8MusicInfoBarMax -_u8InfoBarIdx]);
                        }
                        else
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_GOTO_TIME - _u8InfoBarIdx]);
                        }
						#endif
                    }
                    break;
                default:
                    break;
            }
        }
            break;
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_SELECT:
        {
            if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK)
            {
                enumMPlayerMediaType eMediaType= MApp_MPlayer_QueryCurrentMediaType();
                switch (eMediaType)
                {
                #if ENABLE_MPLAYER_MOVIE
                    case E_MPLAYER_TYPE_MOVIE:
                    {
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                        DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_SHOW);
                        U32 u32GotoTimeMs = (_u8Second+_u8Minute*60+_u8Hour*3600)*1000;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_HIDE);
						#if ENABLE_GOTO_TIME
                        if(MOVIEINFO_GOTO_TIME< _u8InfoBarIdx)
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_GOTO_TIME+u8MovieInfoBarMax -_u8InfoBarIdx]);
                        }
                        else
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_GOTO_TIME - _u8InfoBarIdx]);
                        }
						#endif
                        // To do : process GOTO TIME.
                        //printf("[Time] Go : %02d:%02d:%02d (%ld)\n", _u8Hour, _u8Minute, _u8Second, u32GotoTimeMs);
                        _u8Hour = 0;
                        _u8Minute = 0;
                        _u8Second = 0;

                        if(u32GotoTimeMs > MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME))
                        { // Invalid operation
                            //_MApp_MediaPlayer_ShowMessageBox(MOVIE_MESSAGE_TYPE_GOTO_TIME_EXCEED);
                            // TODO: error handling
                            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                           MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                        }
                        else
                        {
                            // 1. Cancel Repeat AB Mode
                            enumMPlayerRet eRet=E_MPLAYER_RET_FAIL;
                            if(MApp_DMP_GetDmpFlag()& DMP_FLAG_MOVIE_REPEATAB_MODE)
                            {
                                _MApp_ACTdmp_MovieCancelRepeatAB();
                            //    MApp_ZUI_API_ShowWindow(HWND_DMP_MOVIE_INFO_ICON_ADVENCE_GROUP, SW_SHOW);
                            }
                            // 2. Disable trick play --> Normal play
                            if(MApp_MPlayer_QueryMoviePlayMode() != E_MPLAYER_MOVIE_NORMAL)
                            {
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP,SW_HIDE);
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                            }
                            eRet=MApp_MPlayer_SetPlayPosition(u32GotoTimeMs,FALSE);
                            if(eRet==E_MPLAYER_RET_FAIL)
                            {
                                // TODO: error handling
                               _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                            }
                        }
                    }
                        break;
                    #endif

                    case E_MPLAYER_TYPE_MUSIC:
                    {
                        _MApp_ACTdmp_MusicCancelRepeatAB();
                        //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                        //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_SHOW);
                        U32 u32GotoTime = _u8Second+_u8Minute*60+_u8Hour*3600;
                        U32 u32GotoTimeMs = u32GotoTime*1000;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_HIDE);
						#if ENABLE_GOTO_TIME
                        if(MUSICINFO_GOTO_TIME< _u8InfoBarIdx)
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_GOTO_TIME+u8MusicInfoBarMax -_u8InfoBarIdx]);
                        }
                        else
                        {
                            MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_GOTO_TIME - _u8InfoBarIdx]);
                        }
						#endif
                        // To do : process GOTO TIME.
                        //printf("[Time] Go : %02d:%02d:%02d (%ld)\n", _u8Hour, _u8Minute, _u8Second, u32GotoTimeMs);
                        _u8Hour = 0;
                        _u8Minute = 0;
                        _u8Second = 0;
                        if(u32GotoTime >= MApp_MPlayer_QueryMusicFilePlayTime())
                        { // Invalid operation
                            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                        }
                        else
                        {
                            switch(MApp_MPlayer_QueryCurrentFileMediaSubType())
                            {
                            #if (ENABLE_WMA)
                                case E_MPLAYER_SUBTYPE_WMA:
                                    MApp_WMA_ProcessTimeOffset(u32GotoTimeMs);
                                    break;
                            #endif

                                case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
                                case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
                                case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_OGG)
                                case E_MPLAYER_SUBTYPE_OGG:
#endif
#if ( ENABLE_AMR )
                                case E_MPLAYER_SUBTYPE_AMR:
                                case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_FLAC)
                                case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
                                case E_MPLAYER_SUBTYPE_AC3:
#endif

                                    MApp_Music_ProcessTimeOffset(u32GotoTimeMs);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                        break;
                    default:
                        break;
                }
            }
            else
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK);
            }
        }
            break;
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_UP:
        {
            if(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK)
            {
                MApp_ZUI_API_SetFocus((HWND)(MApp_ZUI_API_GetFocus()-1));
            }
        }
        break;
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_DOWN:
        {
            if(MApp_ZUI_API_GetFocus() != HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK)
            {
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK);
            }
        }
        break;
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_LEFT:
        {
            if(MApp_ZUI_API_GetFocus() > HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT1)
            {
                MApp_ZUI_API_SetFocus((HWND)(MApp_ZUI_API_GetFocus()-1));
#if ENABLE_ATSC_TTS
                MApp_TTS_Cus_Add_Str_By_HWndID(MApp_ZUI_API_GetFocus(),EN_TTS_SPEAK_NORMAL);
#endif
            }
        }
        break;
        case EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_RIGHT:
        {
            if(MApp_ZUI_API_GetFocus() < HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK)
            {
                MApp_ZUI_API_SetFocus((HWND)(MApp_ZUI_API_GetFocus()+1));
#if ENABLE_ATSC_TTS
                if(!(MApp_ZUI_API_GetFocus() == HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_OK))
                {
                     MApp_TTS_Cus_Add_Str_By_HWndID(MApp_ZUI_API_GetFocus(),EN_TTS_SPEAK_NORMAL);
                }
#endif
            }
        }
        break;

// this EN_EXE_DMP_PLAYBACK_PLAYLIST_CANCEL is shared for movie photo music...
        case EN_EXE_DMP_PLAYBACK_PLAYLIST_CANCEL:
        {
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PLAYLIST_GROUP, SW_HIDE);
			U8 i;
			for(i = 0; i < UI_DMP_PLAYLIST_NUMBER; i++)
			{
				_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(_hwndPlayListFileString[i],FALSE);
			}
            enumMPlayerMediaType eMediaType= MApp_MPlayer_QueryCurrentMediaType();
            switch (eMediaType)
            {
                case E_MPLAYER_TYPE_PHOTO:
                 if(PHOTOINFO_PLAYLIST< _u8InfoBarIdx)
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
                    }
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    if(MOVIEINFO_PLAYLIST< _u8InfoBarIdx)
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp]);
                    }
                    break;
                    #endif
                case E_MPLAYER_TYPE_MUSIC:
                    if(MUSICINFO_PLAYLIST< _u8InfoBarIdx)
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
                    }
                    break;
                #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    if(TEXTINFO_PLAYLIST< _u8InfoBarIdx)
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+9]);
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+9]);
                    }
                    break;
                #endif
                default:
                    DMP_DBG(printf("=.=.=.=.=.=.=\n"););
                    break;
            }
        }
            break;
#if (ENABLE_MPLAYER_MOVIE)
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO:
        {
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT);
            _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
            HWND_DMP_PLAYBACK_MOVIEINFO_INFO_FILENAME_TEXT,TRUE);
        }
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT_R:
        {
            if( MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE
                && MApp_MPlayer_IsMoviePlaying())
            {
            #if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    U8 ret;

                    DMP_DBG(printf("VK_AUDIO in DVD\n"));
                    ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_LANGUAGE);

                    return TRUE;
                }
                else
            #endif  // ENABLE_DVD
                {
                    U16 u16TotalTrk = MApp_MPlayer_QueryMovieAudioChannelNum();
                    if (u16TotalTrk != MPLAYER_INVALID_INDEX && u16TotalTrk != 0)
                    {
                        U16 u16TrkID = MApp_MPlayer_QueryMovieCurAudioTrackIdx();
                        if(u16TrkID < u16TotalTrk-1)
                        {
                            u16TrkID++;
                            if(MApp_MPlayer_MovieChangeAudioTrack(u16TrkID) != E_MPLAYER_RET_OK)
                            {
                                DMP_DBG(printf("MApp_MPlayer_MovieChangeProgram fail\n"););
                            }
                            _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_AUDIOTRACK;
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        }
                    }
                    else
                    {
                        DMP_DBG(printf("MApp_MPlayer_QueryMovieAudioChannelNum fail or 0\n"););
                    }
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT);
                }
            }
            return TRUE;
        }
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT_L:
        {

            if( MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE
                && MApp_MPlayer_IsMoviePlaying())
            {
            #if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    U8 ret;

                    DMP_DBG(printf("VK_AUDIO in DVD\n"));
                    ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_LANGUAGE);

                    return TRUE;
                }
                else
            #endif  // ENABLE_DVD
                {
                    U16 u16TotalTrk = MApp_MPlayer_QueryMovieAudioChannelNum();
                    if (u16TotalTrk != MPLAYER_INVALID_INDEX && u16TotalTrk != 0)
                    {
                        U16 u16TrkID = MApp_MPlayer_QueryMovieCurAudioTrackIdx();
                        if(u16TrkID != 0 && u16TrkID <= u16TotalTrk)
                        {
                            u16TrkID--;
                            if(MApp_MPlayer_MovieChangeAudioTrack(u16TrkID) != E_MPLAYER_RET_OK)
                            {
                                DMP_DBG(printf("MApp_MPlayer_MovieChangeProgram fail\n"););
                            }
                            _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_AUDIOTRACK;
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        }
                    }
                    else
                    {
                        DMP_DBG(printf("MApp_MPlayer_QueryMovieAudioChannelNum fail or 0\n"););
                    }
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT);
                }
            }
            return TRUE;
        }
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT_R:
        {
            DMP_DBG(printf("hot VK_SUBTITLE_R\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
            #if (ENABLE_SUBTITLE_DMP)
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                #if ENABLE_DVD
                    if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                    {
                        U8 ret;

                        DMP_DBG(printf("VK_SUBTITLE in DVD\n"));
                        ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_SUBTITLE);

                        return TRUE;
                    }
                #endif  // ENABLE_DVD
                    U16 u16TrkID,u16TotalTrk;
                    u16TrkID=MApp_MPlayer_QueryMovieCurSubtitleTrackIdx() ;
                    u16TotalTrk=MApp_MPlayer_QueryMovieSubtitleNum();

                    if (u16TotalTrk == 0)
                    {
                        DMP_DBG(printf("No SUBTITLE exist!!\n"););
                        break;
                    }
                    else if(_stDmpPlayVar.stMovieInfo.bSubtitleOff)
                    {
                        DMP_DBG(printf("Turn ON SUBTITLE 1\n"););
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_SUBTITLETRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        _stDmpPlayVar.stMovieInfo.bSubtitleOff = FALSE;
                        MApp_MPlayer_MovieChangeSubtitleTrack(0);
                        _MApp_ZUI_ACTdmp_OperateSubtitle();
                    }
                    else if((u16TrkID+1)<u16TotalTrk)
                    {
                        DMP_DBG(printf("change subtitle \n"));
                        MApp_MPlayer_MovieChangeSubtitleTrack((u16TrkID+1)%u16TotalTrk);
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_SUBTITLETRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        _MApp_ZUI_ACTdmp_OperateSubtitle();
                    }
                    else
                    {
                        DMP_DBG(printf("Turn OFF SUBTITLE R\n"););
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_SUBTITLETRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        _stDmpPlayVar.stMovieInfo.bSubtitleOff = TRUE;
                        _MApp_ZUI_ACTdmp_OperateSubtitle();
                    }

                    // check subtitle sync.
                    // On + External subtitle => Enable sync,
                    // other                  => Disable sync.

                    // clear previous subtitle?
                    memset((U8*)_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf, 0, DMP_STRING_BUF_SIZE);
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT);
                }
            #endif // #if (ENABLE_SUBTITLE_DMP)
            }
        }
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT_L:
        {
            DMP_DBG(printf("hot VK_SUBTITLE_L\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
            #if (ENABLE_SUBTITLE_DMP)
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                #if ENABLE_DVD
                    if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                    {
                        U8 ret;

                        DMP_DBG(printf("VK_SUBTITLE left is not supported in DVD\n"));
                        ret = MApp_MPlayer_DVD_Command(E_MPLAYER_DVD_CMD_SUBTITLE);

                        return TRUE;
                    }
                #endif  // ENABLE_DVD
                    U16 u16TrkID,u16TotalTrk;
                    u16TrkID=MApp_MPlayer_QueryMovieCurSubtitleTrackIdx() ;
                    u16TotalTrk=MApp_MPlayer_QueryMovieSubtitleNum();
                    if (u16TotalTrk == 0)
                    {
                        DMP_DBG(printf("No SUBTITLE exist!!\n"););
                        break;
                    }
                    else if(_stDmpPlayVar.stMovieInfo.bSubtitleOff)
                    {
                        DMP_DBG(printf("Turn ON SUBTITLE\n"););
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_SUBTITLETRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        _stDmpPlayVar.stMovieInfo.bSubtitleOff = FALSE;
                        MApp_MPlayer_MovieChangeSubtitleTrack(u16TotalTrk-1);
                        _MApp_ZUI_ACTdmp_OperateSubtitle();

                    }
                    else if(u16TrkID != 0)
                    {
                        MApp_MPlayer_MovieChangeSubtitleTrack((u16TrkID-1)%u16TotalTrk);
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_SUBTITLETRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        _MApp_ZUI_ACTdmp_OperateSubtitle();
                    }
                    else
                    {
                        DMP_DBG(printf("Turn OFF SUBTITLE_L\n"););
                        _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_CHANGE_SUBTITLETRACK;
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        _stDmpPlayVar.stMovieInfo.bSubtitleOff = TRUE;
                        _MApp_ZUI_ACTdmp_OperateSubtitle();
                     }

                    // check subtitle sync.
                    // On + External subtitle => Enable sync,
                    // other                  => Disable sync.

                    // clear previous subtitle?
                    memset((U8*)_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf, 0, DMP_STRING_BUF_SIZE);
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT);
                }
            #endif // #if (ENABLE_SUBTITLE_DMP)
            }
        }
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_SYNC_TEXT_R:
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_SYNC_TEXT_L:
        {
            DMP_DBG(printf("hot VK_SYNC\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
            #if (ENABLE_SUBTITLE_DMP)
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                    S32 s32SubtitleTimeShiftSec=0;
                    s32SubtitleTimeShiftSec = MApp_MPlayer_GetSubtitleTimeShift(); //ms
                    s32SubtitleTimeShiftSec = s32SubtitleTimeShiftSec/1000; //s

                    s32SubtitleTimeShiftSec = (S32)MApp_ZUI_ACT_DecIncS8Value((act==EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_SYNC_TEXT_R), (S8)s32SubtitleTimeShiftSec, -10, 10, 1);

                    MApp_MPlayer_SetSubtitleTimeShift(s32SubtitleTimeShiftSec*1000);
                    // clear previous subtitle?
                    //memset((U8*)_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf, 0, DMP_STRING_BUF_SIZE);
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                }
            #endif // #if (ENABLE_SUBTITLE_DMP)
            }
        }
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_CODEPAGE_TEXT_R:
        {
            DMP_DBG(printf("hot VK_CODEPAGE_R\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
            #if (ENABLE_SUBTITLE_DMP)
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                    enumSubtitleCharsetType enSubtitleCharsetType = SUBTITLE_CHARSET_DEFAULT;

                    enSubtitleCharsetType = MApp_MPlayer_GetSubtitleCharsetType();

                    switch(enSubtitleCharsetType)
                    {
                        case SUBTITLE_CHARSET_GBK:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP874);
                        break;
                        case SUBTITLE_CHARSET_CP874:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1250);
                        break;
                        case SUBTITLE_CHARSET_CP1250:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1251);
                        break;
                        case SUBTITLE_CHARSET_CP1251:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1252);
                        break;
                        case SUBTITLE_CHARSET_CP1252:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1253);
                        break;
                        case SUBTITLE_CHARSET_CP1253:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1254);
                        break;
                        case SUBTITLE_CHARSET_CP1254:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1255);
                        break;
                        case SUBTITLE_CHARSET_CP1255:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1256);
                        break;
                        case SUBTITLE_CHARSET_CP1256:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1257);
                        break;
                        case SUBTITLE_CHARSET_CP1257:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1258);
                        break;
                        case SUBTITLE_CHARSET_CP1258:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_KOREAN);
                        break;
                        case SUBTITLE_CHARSET_KOREAN:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_ISO_8859_05);
                        break;
                        case SUBTITLE_CHARSET_ISO_8859_05:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_GBK);
                        break;
                        default:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1252);
                        break;
                     }
                     MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                }
            #endif // #if (ENABLE_SUBTITLE_DMP)
            }
        }
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_CODEPAGE_TEXT_L:
        {
            DMP_DBG(printf("hot VK_CODEPAGE_L\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
            #if (ENABLE_SUBTITLE_DMP)
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                    enumSubtitleCharsetType enSubtitleCharsetType = SUBTITLE_CHARSET_DEFAULT;

                    enSubtitleCharsetType = MApp_MPlayer_GetSubtitleCharsetType();

                    switch(enSubtitleCharsetType)
                    {
                        case SUBTITLE_CHARSET_GBK:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_ISO_8859_05);
                        break;
                        case SUBTITLE_CHARSET_CP874:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_GBK);
                        break;
                        case SUBTITLE_CHARSET_CP1250:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP874);
                        break;
                        case SUBTITLE_CHARSET_CP1251:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1250);
                        break;
                        case SUBTITLE_CHARSET_CP1252:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1251);
                        break;
                        case SUBTITLE_CHARSET_CP1253:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1252);
                        break;
                        case SUBTITLE_CHARSET_CP1254:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1253);
                        break;
                        case SUBTITLE_CHARSET_CP1255:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1254);
                        break;
                        case SUBTITLE_CHARSET_CP1256:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1255);
                        break;
                        case SUBTITLE_CHARSET_CP1257:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1256);
                        break;
                        case SUBTITLE_CHARSET_CP1258:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1257);
                        break;
                        case SUBTITLE_CHARSET_KOREAN:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1258);
                        break;
                        case SUBTITLE_CHARSET_ISO_8859_05:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_KOREAN);
                        break;
                        default:
                            MApp_MPlayer_SetSubtitleCharsetType(SUBTITLE_CHARSET_CP1252);
                        break;
                     }
                     MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                }
            #endif // #if (ENABLE_SUBTITLE_DMP)
            }
        }
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT_R:
        {
            DMP_DBG(printf("VK_CHANNEL_MINUS\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalPgm = MApp_MPlayer_QueryMovieProgramNum();
                if (u16TotalPgm != MPLAYER_INVALID_INDEX && u16TotalPgm != 0)
                {
                    U16 u16PgmIdx = MApp_MPlayer_QueryMovieCurProgramIdx();
                    {
                        if( u16PgmIdx < u16TotalPgm -1)
                        {
                            DMP_DBG(printf("channel++\n"););
                            u16PgmIdx++;
                            if (MApp_MPlayer_MovieChangeProgram(u16PgmIdx) == E_MPLAYER_RET_OK)
                            {
                                _MApp_ACTdmp_MovieCancelRepeatAB();
                                _MApp_ACTdmp_Change_to_Normal_Play_Icon();
                            }
                            else
                            {
                                DMP_DBG(printf("channel++ fail\n"););
                            }
                        }
                    }
                }
                else
                {
                    DMP_DBG(printf("MApp_MPlayer_QueryMovieProgramNum fail or 0\n"););
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT);
            }
            return TRUE;
        }
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT_L:
        {
            DMP_DBG(printf("VK_CHANNEL_MINUS\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalPgm = MApp_MPlayer_QueryMovieProgramNum();
                if (u16TotalPgm != MPLAYER_INVALID_INDEX && u16TotalPgm != 0)
                {
                    U16 u16PgmIdx = MApp_MPlayer_QueryMovieCurProgramIdx();
                    {
                        if(u16PgmIdx > 0)
                        {
                            DMP_DBG(printf("channel--\n"););
                            u16PgmIdx--;
                            if (MApp_MPlayer_MovieChangeProgram(u16PgmIdx) == E_MPLAYER_RET_OK)
                            {
                                _MApp_ACTdmp_MovieCancelRepeatAB();
                                _MApp_ACTdmp_Change_to_Normal_Play_Icon();
                            }
                            else
                            {
                                DMP_DBG(printf("channel-- fail\n"););
                            }
                        }
                    }
                }
                else
                {
                    DMP_DBG(printf("MApp_MPlayer_QueryMovieProgramNum fail or 0\n"););
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT);
            }
            return TRUE;
        }
        break;
    #if (ENABLE_DIVX_PLUS == 1)
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX:
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU:
        {
            _enDmpDivxStatus= DIVX_MENU;
            _MApp_ACTdmp_Playback_ShowDivxWin();
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_SELECT:
        {
            switch (MApp_ZUI_API_GetFocus())
            {
                case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETTITLE:
                    _enDmpDivxStatus = DIVX_SET_TITLE;
                    break;
                case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETEDITION:
                    _enDmpDivxStatus = DIVX_SET_EDITION;
                    break;
                case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETCHAPTER:
                    _enDmpDivxStatus = DIVX_SET_CHAPTER;
                    break;
                case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_MENU_SETAUTOCHAPTER:
                    _enDmpDivxStatus = DIVX_SET_AUTOCHAPTER;
                    break;
                default:
                    _enDmpDivxStatus = DIVX_MAX;
                    break;
            }
            _MApp_ACTdmp_Playback_ShowDivxWin();
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_TITLE_TEXT_R:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_TITLE_TEXT_R\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                if (u16TotalTitle != MPLAYER_INVALID_INDEX && u16TotalTitle!= 0)
                {
                    if( _u16DivxTitleIdx < u16TotalTitle-1)
                    {
                        _u16DivxTitleIdx++;
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_TITLE_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_TITLE_TEXT_L:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_TITLE_TEXT_L\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                if (u16TotalTitle != MPLAYER_INVALID_INDEX && u16TotalTitle!= 0)
                {
                    if( _u16DivxTitleIdx >0)
                    {
                        _u16DivxTitleIdx--;
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_TITLE_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_EDITION_TEXT_R:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_EDITION_TEXT_R\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                U16 u16TotalEdition = MApp_MPlayer_QueryMovieEditionNum();
                if (u16TotalTitle == 0)
                {
                    return TRUE;
                }
                if (u16TotalEdition!= MPLAYER_INVALID_INDEX && u16TotalEdition!= 0)
                {
                    if( _u16DivxEditionIdx < u16TotalEdition-1)
                    {
                        _u16DivxEditionIdx++;
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_EDITION_TEXT_L:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_EDITION_TEXT_L\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                U16 u16TotalEdition = MApp_MPlayer_QueryMovieEditionNum();
                if (u16TotalTitle == 0)
                {
                    return TRUE;
                }
                if (u16TotalEdition!= MPLAYER_INVALID_INDEX && u16TotalEdition!= 0)
                {
                    if( _u16DivxEditionIdx > 0)
                    {
                        _u16DivxEditionIdx--;
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_CHAPTER_TEXT_R:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_CHAPTER_TEXT_R\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                U16 u16TotalEdition = MApp_MPlayer_QueryMovieEditionNum();
                U16 u16TotalChp = MApp_MPlayer_QueryMovieChapterNum();
                if ((u16TotalTitle == 0) || (u16TotalEdition == 0))
                {
                    return TRUE;
                }
                if (u16TotalChp!= MPLAYER_INVALID_INDEX && u16TotalChp!= 0)
                {
                    if( _u16DivxChpIdx < u16TotalChp-1)
                    {
                        _u16DivxChpIdx++;
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_CHAPTER_TEXT_L:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_CHAPTER_TEXT_L\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                U16 u16TotalEdition = MApp_MPlayer_QueryMovieEditionNum();
                U16 u16TotalChp = MApp_MPlayer_QueryMovieChapterNum();
                if ((u16TotalTitle == 0) || (u16TotalEdition == 0))
                {
                    return TRUE;
                }
                if (u16TotalChp!= MPLAYER_INVALID_INDEX && u16TotalChp!= 0)
                {
                    if( _u16DivxChpIdx > 0)
                    {
                        _u16DivxChpIdx--;
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_AUTOCHAPTER_TEXT_L:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_AUTOCHAPTER_TEXT_L\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                if( _u8DivxAutoChpIdx > 0) // 0~9
                {
                    _u8DivxAutoChpIdx--;
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        if(E_MPLAYER_RET_OK == MApp_MPlayer_MovieChangeAutoGenChapter(_u8DivxAutoChpIdx))
                        {
                        }
                        else
                        {
                            _u8DivxAutoChpIdx++;
                            DMP_DBG(printf("MApp_MPlayer_MovieChangeAutoGenChapter fail\n"););
                        }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_AUTOCHAPTER_TEXT_R:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_AUTOCHAPTER_TEXT_R\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                if( _u8DivxAutoChpIdx < 9) // 0~9
                {
                    _u8DivxAutoChpIdx++;
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        if(E_MPLAYER_RET_OK == MApp_MPlayer_MovieChangeAutoGenChapter(_u8DivxAutoChpIdx))
                        {
                        }
                        else
                        {
                            _u8DivxAutoChpIdx--;
                            DMP_DBG(printf("MApp_MPlayer_MovieChangeAutoGenChapter fail !\n"););
                        }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_TEXT);
            }
            return TRUE;
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_OK:
        {
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_OK\n"););
            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE && MApp_MPlayer_IsMoviePlaying())
            {
                switch (_enDmpDivxStatus)
                {
                    case DIVX_SET_TITLE:
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        if (MApp_MPlayer_MovieChangeTitle((U8)_u16DivxTitleIdx) == E_MPLAYER_RET_FAIL)
                        {
                            // TODO: Error handling
                            DMP_DBG(printf("MApp_MPlayer_MovieChangeTitle(%u)\n",_u16DivxTitleIdx););
                        }
                        break;
                    case DIVX_SET_EDITION:
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        if (MApp_MPlayer_MovieChangeEdition(_u16DivxEditionIdx) == E_MPLAYER_RET_FAIL)
                        {
                            // TODO: Error handling
                            DMP_DBG(printf("MApp_MPlayer_MovieChangeEdition(%u)\n",_u16DivxEditionIdx););
                        }
                        break;
                    case DIVX_SET_CHAPTER:
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        if (MApp_MPlayer_MovieChangeChapter(_u16DivxChpIdx) == E_MPLAYER_RET_FAIL)
                        {
                            // TODO: Error handling
                            DMP_DBG(printf("MApp_MPlayer_MovieChangeChapter(%u)\n",_u16DivxChpIdx););
                        }
                        break;

                    case DIVX_SET_AUTOCHAPTER:
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        MApp_MPlayer_MovieChangeAutoGenChapter(_u8DivxAutoChpIdx);
                        break;
                    default:
                        break;
                }
                _enDmpDivxStatus = DIVX_MENU;
                _MApp_ACTdmp_Playback_ShowDivxWin();
            }
        }
        break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_DIVX_CLOSE:
        {
            _enDmpDivxStatus = DIVX_MAX;
            _MApp_ACTdmp_Playback_ShowDivxWin();
        }
        break;
    #endif  // (ENABLE_DIVX_PLUS == 1)
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_INFOCLOSE:
        {
            _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
            HWND_DMP_PLAYBACK_MOVIEINFO_INFO_FILENAME_TEXT,FALSE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP,SW_HIDE);
            if(MOVIEINFO_INFO < _u8InfoBarIdx)
            {
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_INFO+u8MovieInfoBarMax -_u8InfoBarIdx]);
            }
            else
            {
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_INFO - _u8InfoBarIdx]);
            }
        }
        break;

    #if (ENABLE_MPLAYER_CAPTURE_MOVIE == 1)
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_CAPTURE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_CAPTURE\n"););
            {
                switch(MApp_MPlayer_QueryMoviePlayMode())
                {
                    case E_MPLAYER_MOVIE_NORMAL:
                        _enDmpPlayStrType = PLAY_MODE_ICON_PLAY;
                        break;
                    case E_MPLAYER_MOVIE_PAUSE:
                        _enDmpPlayStrType = PLAY_MODE_ICON_PAUSE;
                        break;
                    case E_MPLAYER_MOVIE_FF_2X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FF2X;
                        break;
                    case E_MPLAYER_MOVIE_FF_4X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FF4X;
                        break;
                    case E_MPLAYER_MOVIE_FF_8X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FF8X;
                        break;
                    case E_MPLAYER_MOVIE_FF_16X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FF16X;
                        break;
                    case E_MPLAYER_MOVIE_FF_32X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FF32X;
                        break;
                    case E_MPLAYER_MOVIE_FB_2X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FB2X;
                        break;
                    case E_MPLAYER_MOVIE_FB_4X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FB4X;
                        break;
                    case E_MPLAYER_MOVIE_FB_8X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FB8X;
                        break;
                    case E_MPLAYER_MOVIE_FB_16X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FB16X;
                        break;
                    case E_MPLAYER_MOVIE_FB_32X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_FB32X;
                        break;
                    case E_MPLAYER_MOVIE_SF_2X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_SF2X;
                        break;
                    case E_MPLAYER_MOVIE_SF_4X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_SF4X;
                        break;
                    case E_MPLAYER_MOVIE_SF_8X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_SF8X;
                        break;
                    case E_MPLAYER_MOVIE_SF_16X:
                        _enDmpPlayStrType = PLAY_MODE_ICON_SF16X;
                        break;
                    case E_MPLAYER_MOVIE_STEP:
                        _enDmpPlayStrType = PLAY_MODE_ICON_SD;
                        break;
                    default:
                        break;
                }
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG,SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_CONFIRM_YES);
                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
            }
        break;
    #endif // #if (ENABLE_MPLAYER_CAPTURE_MOVIE == 1)

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_REPEAT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_REPEAT\n"););
            {
                enumMPlayerRepeatMode eRepeatMode = MApp_MPlayer_QueryRepeatMode();
                if(eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_1);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_1;
                }
                else if(eRepeatMode == E_MPLAYER_REPEAT_1)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_ALL;
                }
                else
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_NONE;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
        // TODO: need to show the repeat mode on screen?
            break;
#if RANDOM_PLAY
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_RANDOM:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_RANDOM\n"););
            {
                enumMPlayerRandomMode eRandomMode = MApp_MPlayer_QueryRandomMode();
                if(eRandomMode == E_MPLAYER_RANDOM_NONE)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM);
                }
                else if(eRandomMode == E_MPLAYER_RANDOM)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }
                else
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
        // TODO: need to show the random mode on screen?
            break;
#endif

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_AB_REPEAT:
            if(MApp_MPlayer_QueryMoviePlayMode() != E_MPLAYER_MOVIE_NORMAL)
            {
                //error handling
                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                break;
            }
            if(MApp_MPlayer_IsMediaFileInPlaying() &&
                MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING
                && MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
            {
            #if ENABLE_DVD
                if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
                {
                    if (!MApp_VDPlayer_DVD_IsAllowed(E_MPLAYER_DVD_CMD_REPEATAB))
                    {
                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                        return TRUE;
                    }
                }
                else
            #endif
                {
                    if(!MApp_MPlayer_IsMovieIndexTableExist())
                    {
                        //error handling
                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                        return TRUE;
                    }
                }

                //FOR TEST - Movie Repeat A->B
                _enDmpPlayStrType =_enDmpPlayIconType =PLAY_MODE_ICON_AB_REPEAT;
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;

                if(_stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0] == 0xFFFFFFFF
                    && _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] == 0xFFFFFFFF)
                {
                }
                if(_stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0] == 0xFFFFFFFF)
                {// Repeat A
                    _enRepeatABStatus = REPEATAB_MODE_A;
                    _enDmpPlayStrType =_enDmpPlayIconType =PLAY_MODE_ICON_SETA;
                    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_B;
                    _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0] = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                    MApp_MPlayer_MovieSetRepeatAB(E_MPLAYER_MOVIE_SET_REPEAT_A, _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0] );
                    //MApp_DMP_SetDmpFlag(DMP_FLAG_MOVIE_REPEATAB_MODE);
                }
                else if(_stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] == 0xFFFFFFFF)
                {// Repeat B
                    _enRepeatABStatus = REPEATAB_MODE_AB;
                    _enDmpPlayStrType =_enDmpPlayIconType =PLAY_MODE_ICON_AB_LOOP;
                    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                    DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_None;
                    _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                    if(_stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] > _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0])
                    {
                        MApp_MPlayer_MovieSetRepeatAB(E_MPLAYER_MOVIE_SET_REPEAT_B, _stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] );
                        MApp_DMP_SetDmpFlag(DMP_FLAG_MOVIE_REPEATAB_MODE);
                    }
                    else
                    { //Invalid time : B <= A
                        //error handling

                        _MApp_ACTdmp_MovieCancelRepeatAB();
                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                    }
                }
                else
                {// Clear A->B
                    _MApp_ACTdmp_MovieCancelRepeatAB();
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);

            }
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMIN:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMIN\n"););
            {
            #if (FBL_ZOOM==1 || ENABLE_3D_PROCESS)
                if((MApi_XC_IsCurrentFrameBufferLessMode() || g_bForceToFB) ||\
                    (MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE))
                {
                    DMP_DBG(printf("FrameBuffer less mode\n"));
                    _enDmpPlayStrType= PLAY_MODE_ICON_FF_INVALID;
                    _enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    break;
                }
            #endif

                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                   (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                    enumMPlayerZoom eZoomScale;
                    enumMPlayerMediaType eMediaType;
                    eZoomScale = MApp_MPlayer_QueryZoomScale();
                    eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    switch(eMediaType)
                    {
                        case E_MPLAYER_TYPE_MOVIE:
                            //MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);

                      #if ENABLE_3D_PROCESS
                         #if (ENABLE_EXTERN_MFC_CHIP)
                              if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
                            {

                                _enDmpPlayStrType= PLAY_MODE_ICON_FF_INVALID;
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                              }
                            else
                         #endif
                      #endif
                           {
                            if(eZoomScale < E_MPLAYER_ZOOM_8)
                            {
                                eZoomScale++;
                                switch (eZoomScale)
                                {
                                        case E_MPLAYER_ZOOM_1_DIV4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV4;
                                                break;
                                        case E_MPLAYER_ZOOM_1_DIV2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV2;
                                                break;
                                        case E_MPLAYER_ZOOM_1:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1;
                                                break;
                                        case E_MPLAYER_ZOOM_2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_2;
                                                break;
                                        case E_MPLAYER_ZOOM_4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_4;
                                                break;
                                        case E_MPLAYER_ZOOM_8:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_8;
                                                break;
                                        default:
                                                break;
                                }

                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_MPlayer_Zoom(eZoomScale);
                            }
                            }
                            break;
                        default:
                            DMP_DBG(printf("unsupport type for zoomin now!!"););
                            break;
                    }
                }
            }
			_enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_IN_MODE;
            break;
        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMOUT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_ZOOMOUT\n"););
            {
            #if (FBL_ZOOM==1 || ENABLE_3D_PROCESS)
                if((MApi_XC_IsCurrentFrameBufferLessMode() || g_bForceToFB) ||\
                    (MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE))
                {
                    DMP_DBG(printf("FrameBuffer less mode\n"));
                    _enDmpPlayStrType = PLAY_MODE_ICON_FF_INVALID;
                    _enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    break;
                }
            #endif
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    ((MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING)
                    /*|| (MApp_MediaPlayer_GetMediaPlayerStateFlag() & E_FLAG_THUMBNAIL_PLAYING)*/))
                {
                    enumMPlayerZoom eZoomScale;
                    enumMPlayerMediaType eMediaType;
                    eZoomScale = MApp_MPlayer_QueryZoomScale();
                    eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    switch(eMediaType)
                    {
                        case E_MPLAYER_TYPE_MOVIE:

                    #if ENABLE_3D_PROCESS
                         #if (ENABLE_EXTERN_MFC_CHIP)
                              if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
                            {

                                _enDmpPlayStrType= PLAY_MODE_ICON_FF_INVALID;
                                _enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

                              }
                            else
                        #endif
                    #endif
                            {
                            if(eZoomScale > E_MPLAYER_ZOOM_1_DIV4)
                            {
                                eZoomScale--;
                                switch (eZoomScale)
                                {
                                        case E_MPLAYER_ZOOM_1_DIV4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV4;
                                                break;
                                        case E_MPLAYER_ZOOM_1_DIV2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV2;
                                                break;
                                        case E_MPLAYER_ZOOM_1:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1;
                                                break;
                                        case E_MPLAYER_ZOOM_2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_2;
                                                break;
                                        case E_MPLAYER_ZOOM_4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_4;
                                                break;
                                        case E_MPLAYER_ZOOM_8:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_8;
                                                break;
                                        default:
                                                break;
                                }
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_MPlayer_Zoom(eZoomScale);
                            }
                        }
                            break;
                        default:
                            DMP_DBG(printf("unsupport type for zoomout now!!"););
                            break;
                    }
                }
            }
			_enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_OUT_MODE;
            break;

        case EN_EXE_DMP_PLAYBACK_MOVIEINFO_ASPECT_RATIO:

            if(MApp_MPlayer_QueryCurrentMediaType()== E_MPLAYER_TYPE_MOVIE
            && MApp_MPlayer_IsMoviePlaying())
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_ASPECT_RATIO\n"););
                {
                #if !ENABLE_FBL_ASPECT_RATIO_BY_MVOP
                    if(MApi_XC_IsCurrentFrameBufferLessMode() || g_bForceToFB)
                    {
                        DMP_DBG(printf("FrameBuffer less mode\n"));
                        _enDmpPlayStrType = PLAY_MODE_ICON_FF_INVALID;
                        _enDmpPlayIconType = PLAY_MODE_ICON_MAX;
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        break;
                    }
                #endif
                    if(MApp_MPlayer_IsMediaFileInPlaying() &&
                       (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                    {
                    #ifndef ATSC_SYSTEM
                        //MApp_MPlayer_Zoom(E_MPLAYER_ZOOM_1); //set normal zoom before adjust aspect ratio
                        switch(ST_VIDEO.eAspectRatio)
                        {
                           /* case EN_AspectRatio_JustScan:
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_RATIO_Original;
                                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                                stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE; // Keep source H/V ratio and scale to fit panel
                                break;
                         */
                            case EN_AspectRatio_Original:
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_RATIO_16X9;
                                ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9;
                                stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_MM_16_9; // Display window: H:V=16:9
                                break;

                            case EN_AspectRatio_16X9:
                            #if 0// ENABLE_3D_PROCESS
                                if(MApi_XC_Get_3D_Output_Mode() != E_XC_3D_OUTPUT_MODE_NONE)
                                {
                                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_RATION_JUSTSCAN;
                                    ST_VIDEO.eAspectRatio = EN_AspectRatio_JustScan;
                                    stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_3D_CENTER; // H and V scale to fit panel
                                }
                                else
                            #endif
                                {
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_RATIO_4X3;
                                ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
                                stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_MM_4_3; // Display window: H:V=4:3
                                }
                                break;
                            case EN_AspectRatio_4X3:
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_RATIO_Original;
                                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                                stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_ORIGIN; // Display window: H:V=16:9
                                break;
                            default:
                                MS_DEBUG_MSG(printf("Unsupported ST_VIDEO.eAspectRatio %u!!\n",ST_VIDEO.eAspectRatio));
                                MS_DEBUG_MSG(printf("Force to FULL\n"));
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_RATIO_Original;
                                ST_VIDEO.eAspectRatio = EN_AspectRatio_Original;
                                stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE; // H and V scale to fit panel
                                break;
                        }
                        //MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio , MAIN_WINDOW );
                        //stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(ST_VIDEO.eAspectRatio);
                        MApp_MPlayer_Zoom(E_MPLAYER_ZOOM_1); //set normal zoom before adjust aspect ratio
                    #else
                        DMP_DBG(printf("ATSC not support NOW!!!!\n"));
                    #endif

                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    }
                }
            }
			_enDmpPlayIconType = PLAY_MODE_ICON_ASPECT_MODE;
            break;
#endif
//=========PHOTO and MOVIE MOVEVIEW==========
            case EN_EXE_DMP_PLAYBACK_MOVIEINFO_MOVEVIEW:
            case EN_EXE_DMP_PLAYBACK_PHOTOINFO_MOVEVIEW:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVIEINFO_MOVEVIEW or EN_EXE_DMP_PLAYBACK_PHOTO_INFO_MOVEVIEW\n"););
            {
                if (MApp_MPlayer_QueryZoomScale() > E_MPLAYER_ZOOM_1)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP,SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVEVIEW_EXIT);
                    #if ENABLE_ZOOM_MAP
                    if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
                    {
                        //_MApp_ZUI_ACT_DrawZoomMap(TRUE, ZOOM_MAP_START_X, ZOOM_MAP_START_Y, ZOOM_MAP_FACTOR);
                    }
                    #else
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_ZOOMMAP_GROUP, SW_HIDE);
                    #endif
                }
                else
                {
                    DMP_DBG(printf("Zoom Scale <= 1\n"););
                }
            }
            break;


            case EN_EXE_DMP_PLAYBACK_MOVEVIEW_EXIT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVEVIEW_EXIT\n"););
            {
            #if (!ENABLE_4K2K)
                if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
                {
                    if(PHOTOINFO_MOVEVIEW < _u8InfoBarIdx)
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[PHOTOINFO_MOVEVIEW+u8MovieInfoBarMax -_u8InfoBarIdx]);
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[PHOTOINFO_MOVEVIEW - _u8InfoBarIdx]);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP,SW_HIDE);
                    #if ENABLE_ZOOM_MAP
                    _MApp_ZUI_ACT_DMPCloseZoomMapWin();
                    #endif
                }
            #endif
            #if (ENABLE_MPLAYER_MOVIE)
                else if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    if(MOVIEINFO_MOVEVIEW < _u8InfoBarIdx)
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_MOVEVIEW+u8MovieInfoBarMax -_u8InfoBarIdx]);
                    }
                    else
                    {
                        MApp_ZUI_API_SetFocus(_hwndListInfoBar[MOVIEINFO_MOVEVIEW - _u8InfoBarIdx]);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVEVIEW_GROUP,SW_HIDE);
                }
            #endif
            }
            break;
			case EN_EXE_DMP_PLAYBACK_MOVIEINFO_SOUND_CH:
				if(g_u8LRAudioMode >= 2)
                {
                    g_u8LRAudioMode = 0;
                }
                else
                {
                    g_u8LRAudioMode++;
                }
                
                if(g_u8LRAudioMode == 0)
                {
                    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
					_enDmpPlayStrType = PLAY_MODE_ICON_SOUND_LR; //wht120613_4
                }
                else if(g_u8LRAudioMode == 1)
                {
                    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
					_enDmpPlayStrType = PLAY_MODE_ICON_SOUND_RR; //wht120613_4
                }
                else if(g_u8LRAudioMode == 2)
                {
                    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
					_enDmpPlayStrType = PLAY_MODE_ICON_SOUND_LL; //wht120613_4
                }
				_enDmpPlayIconType = PLAY_MODE_ICON_BGMUSIC_MODE;//wht120613_4
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
				//>>wht120613_4
				MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
				//<<wht120613_4		
				break;
            case EN_EXE_DMP_PLAYBACK_MOVEVIEW_UP:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVEVIEW_UP\n"););
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_UP);
                if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
                {
                    MApp_MPlayer_PhotoMove(E_MPLAYER_DIRECTION_UP, 100);
                    #if ENABLE_ZOOM_MAP
                    _MApp_ZUI_ACT_DrawZoomMap(FALSE, ZOOM_MAP_START_X, ZOOM_MAP_START_Y, ZOOM_MAP_FACTOR);
                    #endif
                }
            #if (ENABLE_MPLAYER_MOVIE)
                else if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    MApp_MPlayer_MovieMove(E_MPLAYER_DIRECTION_UP, 100);
                }
            #endif
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_UP, 0, 500);
                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            break;
            case EN_EXE_DMP_PLAYBACK_MOVEVIEW_DOWN:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVEVIEW_DOWN\n"););
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_DOWN);
                if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
                {
                    MApp_MPlayer_PhotoMove(E_MPLAYER_DIRECTION_DOWN, 100);
                    #if ENABLE_ZOOM_MAP
                    _MApp_ZUI_ACT_DrawZoomMap(FALSE, ZOOM_MAP_START_X, ZOOM_MAP_START_Y, ZOOM_MAP_FACTOR);
                    #endif
                }
            #if (ENABLE_MPLAYER_MOVIE)
                else if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    MApp_MPlayer_MovieMove(E_MPLAYER_DIRECTION_DOWN, 100);
                }
            #endif
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_DOWN, 0, 500);
                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            break;
            case EN_EXE_DMP_PLAYBACK_MOVEVIEW_LEFT:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVEVIEW_LEFT\n"););
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_LEFT);
                if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
                {
                    MApp_MPlayer_PhotoMove(E_MPLAYER_DIRECTION_LEFT, 100);
                    #if ENABLE_ZOOM_MAP
                    _MApp_ZUI_ACT_DrawZoomMap(FALSE, ZOOM_MAP_START_X, ZOOM_MAP_START_Y, ZOOM_MAP_FACTOR);
                    #endif
                }
            #if (ENABLE_MPLAYER_MOVIE)
                else if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    MApp_MPlayer_MovieMove(E_MPLAYER_DIRECTION_LEFT, 100);
                }
            #endif
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_LEFT, 0, 500);
                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            break;
            case EN_EXE_DMP_PLAYBACK_MOVEVIEW_RIGHT:
            {
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MOVEVIEW_RIGHT\n"););
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_RIGHT);
                if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO)
                {
                    MApp_MPlayer_PhotoMove(E_MPLAYER_DIRECTION_RIGHT, 100);
                    #if ENABLE_ZOOM_MAP
                    _MApp_ZUI_ACT_DrawZoomMap(FALSE, ZOOM_MAP_START_X, ZOOM_MAP_START_Y, ZOOM_MAP_FACTOR);
                    #endif
                }
            #if (ENABLE_MPLAYER_MOVIE)
                else if (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    MApp_MPlayer_MovieMove(E_MPLAYER_DIRECTION_RIGHT, 100);
                }
            #endif
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVEVIEW_ARROW_RIGHT, 0, 500);
                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            break;

//=========PHOTOINFO_INFO key===============
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_PLAY_PAUSE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_PLAY_PAUSE"););
            {
                if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                {
                    MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_NORMAL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                }
                else if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                {
                    MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);

            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_NEXT:
             DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_NEXT"););
            {
                 if (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                {
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                }
				if(MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_1)//wht120522_5
                	MApp_MPlayer_PlayNextFile();
                m_u16PlayErrorNum = 0;
                MApp_MPlayer_SetPhotoSlideShowDelayTime(DEFAULT_PHOTO_SLIDESHOW_DELAY_TIME);
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_NEXT;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_PREV:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_PREV"););
            {
                if (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                {
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                }
				if(MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_1)//wht120522_5
                	MApp_MPlayer_PlayPrevFile();
                m_u16PlayErrorNum = 0;
                MApp_MPlayer_SetPhotoSlideShowDelayTime(DEFAULT_PHOTO_SLIDESHOW_DELAY_TIME);
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PREVIOUS;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_STOP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_STOP\n"););
            MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_BG_EXIT);
/*
            {
                msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                MApp_MPlayer_Stop();
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                MApp_ZUI_API_InvalidateWindow(HWND_MAINFRAME);
                U16 u16PlayingIdx = 0;
                // TODO: fix photo type
                if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
                {
                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
                }
                u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
                MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx/NUM_OF_PHOTO_FILES_PER_PAGE);
                DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););
                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
                {
                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                    MApp_MPlayer_SetCurrentPageIndex(0);
                }
            }
*/
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_INFO:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_INFO\n"););
            {
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
                HWND_DMP_PLAYBACK_PHOTOINFO_INFO_FILENAME_TEXT,TRUE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_INFOCLOSE);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_INFOCLOSE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_INFOCLOSE\n"););
            {
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
                HWND_DMP_PLAYBACK_PHOTOINFO_INFO_FILENAME_TEXT,FALSE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP,SW_HIDE);
                if(PHOTOINFO_INFO < _u8InfoBarIdx)
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
                }
                else
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+4]);
                }
            }
            break;

    #if (ENABLE_MPLAYER_CAPTURE_LOGO == 1)
        // TODO: fix me
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_CAPTURE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_CAPTURE\n"););
            {
                switch(MApp_MPlayer_QueryPhotoPlayMode())
                {
                    case E_MPLAYER_PHOTO_NORMAL:
                        _enDmpPlayStrType = PLAY_MODE_ICON_PLAY;
                        break;
                    case E_MPLAYER_PHOTO_PAUSE:
                        _enDmpPlayStrType = PLAY_MODE_ICON_PAUSE;
                        break;
                    default:
                        break;
                }
                MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG,SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_CONFIRM_YES);
                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
            }
            break;
    #endif

        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMIN:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMIN\n"););
            {
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                {
                    enumMPlayerZoom eZoomScale;
                    enumMPlayerMediaType eMediaType;
                    eZoomScale = MApp_MPlayer_QueryZoomScale();
                    eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    switch(eMediaType)
                    {
                        case E_MPLAYER_TYPE_PHOTO:
#if(ENABLE_PHOTO_INFO_OK)
                            if (!_bPhotoInfoOK)
                            {
                                DMP_DBG(printf("not ready for zoom\n"););
                                break;
                            }
#endif
                            if (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                            {
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                            }
                            if(eZoomScale < E_MPLAYER_ZOOM_8)
                            {
                                eZoomScale++;
                                switch (eZoomScale)
                                {
                                        case E_MPLAYER_ZOOM_1_DIV4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV4;
                                                break;
                                        case E_MPLAYER_ZOOM_1_DIV2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV2;
                                                break;
                                        case E_MPLAYER_ZOOM_1:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1;
                                                break;
                                        case E_MPLAYER_ZOOM_2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_2;
                                                break;
                                        case E_MPLAYER_ZOOM_4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_4;
                                                break;
                                        case E_MPLAYER_ZOOM_8:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_8;
                                                break;
                                        default:
                                                break;
                                }
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_MPlayer_Zoom(eZoomScale);
                            }
                            break;
                        default:
                            DMP_DBG(printf("unsupport type for zoomin now!!"););
                            break;
                    }
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMOUT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_ZOOMOUT\n"););
            {
                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                    ((MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING)
                    /*|| (MApp_MediaPlayer_GetMediaPlayerStateFlag() & E_FLAG_THUMBNAIL_PLAYING)*/))
                {
                    enumMPlayerZoom eZoomScale;
                    enumMPlayerMediaType eMediaType;
                    eZoomScale = MApp_MPlayer_QueryZoomScale();
                    eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    switch(eMediaType)
                    {
                        case E_MPLAYER_TYPE_PHOTO:
#if(ENABLE_PHOTO_INFO_OK)
                            if (!_bPhotoInfoOK)
                            {
                                DMP_DBG(printf("not ready for zoom\n"););
                                break;
                            }
#endif
                            if (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                            {
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                            }
                            if(eZoomScale > E_MPLAYER_ZOOM_1_DIV4)
                            {
                                eZoomScale--;
                                switch (eZoomScale)
                                {
                                        case E_MPLAYER_ZOOM_1_DIV4:
                                                _enDmpPlayStrType = _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV4;
                                                break;
                                        case E_MPLAYER_ZOOM_1_DIV2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1DIV2;
                                                break;
                                        case E_MPLAYER_ZOOM_1:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_1;
                                                break;
                                        case E_MPLAYER_ZOOM_2:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_2;
                                                break;
                                        case E_MPLAYER_ZOOM_4:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_4;
                                                break;
                                        case E_MPLAYER_ZOOM_8:
                                                _enDmpPlayStrType =  _enDmpPlayIconType = PLAY_MODE_ICON_ZOOM_8;
                                                break;
                                        default:
                                                break;
                                }
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                MApp_MPlayer_Zoom(eZoomScale);
                            }
                            break;
                        default:
                            DMP_DBG(printf("unsupport type for zoomout now!!"););
                            break;
                    }
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_REPEAT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_REPEAT\n"););
            {
                enumMPlayerRepeatMode eRepeatMode = MApp_MPlayer_QueryRepeatMode();
                if(eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_1);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_1;
                }
                else if(eRepeatMode == E_MPLAYER_REPEAT_1)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_ALL;
                }
                else
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_NONE;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
        // TODO: need to show the repeat mode on screen?
            break;
#if RANDOM_PLAY
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_RANDOM:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_RANDOM\n"););
            {
                enumMPlayerRandomMode eRandomMode = MApp_MPlayer_QueryRandomMode();
                if(eRandomMode == E_MPLAYER_RANDOM_NONE)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM);
                }
                else if(eRandomMode == E_MPLAYER_RANDOM)
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }
                else
                {
                    MApp_MPlayer_SetRandomMode(E_MPLAYER_RANDOM_NONE);
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
        // TODO: need to show the random mode on screen?
            break;
#endif
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_MUSIC:
#if ENABLE_BGM
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_MUSIC\n"););
            {
                // TODO:  need enhance?
                if(MApp_MPlayer_IsMusicPlaying())
                {
                    MApp_MPlayer_StopMusic();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                }
                else
                {
                    _MApp_DMP_PlayBGM();
                }
            }
#endif
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_CLOCKWISE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_CLOCKWISE\n"););
            {
                enumMPlayerPhotoRotate eRotate;

                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                ((MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING)
                /*|| (MApp_DMP_GetDmpFlag() & E_FLAG_THUMBNAIL_PLAYING)*/))
                {
                    enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    switch(eMediaType)
                    {
                        case E_MPLAYER_TYPE_PHOTO:
#if(ENABLE_PHOTO_INFO_OK)
                            if (!_bPhotoInfoOK)
                            {
                                DMP_DBG(printf("not ready for rotate\n"););
                                break;
                            }
#endif
                            eRotate = MApp_MPlayer_QueryPhotoRotateMode();
                            if(eRotate < E_MPLAYER_PHOTO_ROTATE_270)
                            {
                                eRotate++;
                            }
                            else
                            {
                                eRotate = E_MPLAYER_PHOTO_ROTATE_0;
                            }
                            //UI_DBG(printf(" - (2) Rotate Mode : %bu\n", (U8)eRotate));
                            // TODO: need to refine , pause and play key?
                            if (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                            {
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            }
                            MApp_MPlayer_PhotoRotate(eRotate);
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        break;
                        default:
                            break;
                    }
                    //return TRUE;
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_COUNTERCLOCKWISE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_COUNTERCLOCKWISE\n"););
            {
                enumMPlayerPhotoRotate eRotate;

                if(MApp_MPlayer_IsMediaFileInPlaying() &&
                ((MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING)
                /*|| (MApp_MediaPlayer_GetMediaPlayerStateFlag() &
                E_FLAG_THUMBNAIL_PLAYING)*/))
                {
                    enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    switch(eMediaType)
                    {
                        case E_MPLAYER_TYPE_PHOTO:
#if(ENABLE_PHOTO_INFO_OK)
                            if (!_bPhotoInfoOK)
                            {
                                DMP_DBG(printf("not ready for rotate\n"););
                                break;
                            }
#endif
                            eRotate = MApp_MPlayer_QueryPhotoRotateMode();
                            if(eRotate > E_MPLAYER_PHOTO_ROTATE_0)
                            {
                                eRotate--;
                            }
                            else
                            {
                                eRotate = E_MPLAYER_PHOTO_ROTATE_270;
                            }
                            //UI_DBG(printf(" - (2) Rotate Mode : %bu\n", (U8)eRotate));
                            // TODO: need to refine , pause and play key?
                            if (MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                            {
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                                DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            }
                            MApp_MPlayer_PhotoRotate(eRotate);
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        break;
                        default:
                            break;
                    }
                    //return TRUE;
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_SLIDESHOW:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_SLIDESHOW\n"););
            {
                EN_PHOTOINFO_SLIDESHOW eSlideShowEffect = PHOTOINFO_SLIDESHOW_RANDOM;

                switch (MApp_Photo_GetSlideShowEffect())
                {
                    case E_SLIDE_SHOW_EFFECT_RANDOM:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_RANDOM;
                            break;
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
                    case E_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_BLOCKS_RANDOM;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
                    case E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_RANDOM:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_DIAGONAL_BLOCKS_RANDOM;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
                    case E_SLIDE_SHOW_EFFECT_WIPE_RANDOM:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_WIPE_RANDOM;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
                    case E_SLIDE_SHOW_EFFECT_SLIDE_RANDOM:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_SLIDE_RANDOM;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
                    case E_SLIDE_SHOW_EFFECT_FADE_RANDOM:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_FADE_RANDOM;
                            break;
#endif
                    case E_SLIDE_SHOW_EFFECT_NORMAL:
                    default:
                            eSlideShowEffect = PHOTOINFO_SLIDESHOW_NORMAL;
                            break;
                }

                eSlideShowEffect++;

                if(eSlideShowEffect >= PHOTOINFO_SLIDESHOW_NUM)
                {
                    eSlideShowEffect = PHOTOINFO_SLIDESHOW_RANDOM;
                }

                switch (eSlideShowEffect)
                {
                    case PHOTOINFO_SLIDESHOW_RANDOM:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_RANDOM);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_RANDOM;
                            break;
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
                    case PHOTOINFO_SLIDESHOW_BLOCKS_RANDOM:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_BLOCKS;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
                    case PHOTOINFO_SLIDESHOW_DIAGONAL_BLOCKS_RANDOM:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_DIAGONAL_BLOCKS_RANDOM);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_DIAGONALBLOCKS;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
                    case PHOTOINFO_SLIDESHOW_WIPE_RANDOM:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_WIPE_RANDOM);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_WIPE;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
                    case PHOTOINFO_SLIDESHOW_SLIDE_RANDOM:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_SLIDE_RANDOM);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_SLIDE;
                            break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
                    case PHOTOINFO_SLIDESHOW_FADE_RANDOM:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_FADE_RANDOM);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_FADE;
                            break;
#endif
                    case PHOTOINFO_SLIDESHOW_NORMAL:
                    default:
                            MApp_Photo_SetSlideShowEffect(E_SLIDE_SHOW_EFFECT_NORMAL);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_SLIDESHOW_NORMAL;
                            break;
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            break;
        case EN_EXE_DMP_PLAYBACK_PHOTOINFO_PLAYLIST:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PHOTOINFO_PLAYLIST\n"););
            {
                u8CurrentPlaylistPageIdx = 0;
                u8CurrentPlaylistTotalPage = 1;
                // TODO:calculate how many files in playlist?
                _MApp_ACTdmp_Playback_ShowPlaylistWin(E_MPLAYER_TYPE_PHOTO, TRUE);
            }
            break;
    #if PLAYLIST_BGM
        case EN_EXE_DMP_PLAYBACK_BGMINFO_PLAYLIST:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAYLIST\n"););
            {
                u8CurrentPlaylistPageIdx = 0;
                u8CurrentPlaylistTotalPage = 1;
                bIsBGMPlaylist = TRUE;
                MApp_MPlayer_BGM_Playlist_Init();
                _MApp_ACTdmp_Playback_ShowPlaylistWin(E_MPLAYER_TYPE_MUSIC, TRUE);
            }
            break;
    #endif
//=====================MUSICINFO key=====================
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_INFO:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_INFO"););
            {
                _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
                HWND_DMP_PLAYBACK_MUSICINFO_INFO_FILENAME_TEXT,TRUE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSICINFO_INFO_GROUP, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MUSICINFO_INFO_INFOCLOSE);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_INFOCLOSE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_INFOCLOSE"););
            _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
            HWND_DMP_PLAYBACK_MUSICINFO_INFO_FILENAME_TEXT,FALSE);
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSICINFO_INFO_GROUP,SW_HIDE);
				//printf("\nu8InfobarIdxTemp=%d\n",u8InfobarIdxTemp);
                if(MUSICINFO_INFO < _u8InfoBarIdx)
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
                }
                else
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+7]);
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_NEXT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_NEXT"););
            {
                if (MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                {
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                }
                if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                {
                    memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                    MApp_MPlayer_DisableLRCLyric();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE,SW_HIDE);
                }

                MApp_MPlayer_PlayNextFile();
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MUSIC, DEFAULT_MUSIC_ERROR_DELAY_TIME);
                m_u16PlayErrorNum = 0;
                #if (ENABLE_DRM)
                m_u16DRMErrorNum = 0;
                #endif
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_NEXT;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_PREV:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_PREV"););
            {
                if (MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                {
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                }
                if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                {
                    memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                    MApp_MPlayer_DisableLRCLyric();
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE,SW_HIDE);
                }
                g_bPlayPrev = TRUE;
                MApp_MPlayer_PlayPrevFile();
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MUSIC, DEFAULT_MUSIC_ERROR_DELAY_TIME);
                m_u16PlayErrorNum = 0;
                #if (ENABLE_DRM)
                m_u16DRMErrorNum = 0;
                #endif
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PREVIOUS;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAY_PAUSE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAY_PAUSE\n"););
            {
                if(MApp_MPlayer_QueryMusicPlayMode() == E_MPLAYER_MUSIC_PAUSE)
                {
                    MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;

                    //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                }
                else if(MApp_MPlayer_QueryMusicPlayMode() == E_MPLAYER_MUSIC_STOP)
                {
                    MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                }
                else if(MApp_MPlayer_QueryMusicPlayMode() == E_MPLAYER_MUSIC_NORMAL)
                {
                    MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_PAUSE);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PAUSE;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                   // MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0;
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;

                    //MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
                }
                else // some FF FB ...
                {
                    MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                    //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            break;
            case EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAYLIST:
                DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_PLAYLIST\n"););
                {
                    u8CurrentPlaylistPageIdx = 0;
                    u8CurrentPlaylistTotalPage = 1;
                    _MApp_ACTdmp_Playback_ShowPlaylistWin(E_MPLAYER_TYPE_MUSIC, TRUE);
                }
                break;

        case EN_EXE_DMP_PLAYBACK_MUSICINFO_STOP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_STOP\n"););
            MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_BG_EXIT);
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_FF:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_FF\n"););
            {
                U8 *pu8FfSpeed=MApp_MPlayer_QueryMusicInfo(MP3_INFO_CHECK_FF_FB,NULL);
                _MApp_ACTdmp_MusicCancelRepeatAB();
                //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;

                if(*pu8FfSpeed != 0)
                {
                    switch(MApp_MPlayer_QueryMusicPlayMode())
                    {
                        case E_MPLAYER_MUSIC_PAUSE:
                            //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY,DMP_TIME_MS_EQ_PLAY);
                        case E_MPLAYER_MUSIC_NORMAL:
                        case E_MPLAYER_MUSIC_FB_2X:
                        case E_MPLAYER_MUSIC_FB_4X:
                        case E_MPLAYER_MUSIC_FB_8X:
                        case E_MPLAYER_MUSIC_FB_16X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FF_2X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF2X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FF_2X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FF_4X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF4X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FF_4X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FF_8X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF8X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FF_8X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FF_16X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FF16X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FF_16X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                            //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                            break;
                        default:
                            DMP_DBG(printf("Current state do not allow trick play!\n"););
                            break;
                    }
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                    if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN))
                    {
                        MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    if (_enDmpPlayIconType == PLAY_MODE_ICON_PLAY)
                    {
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    }
                }
                else
                {
                //    _enMediaPlayerIconType = PLAY_MODE_ICON_FF_INVALID;
                //    MApp_ZUI_API_SetTimer(HWND_MEDIA_PLAYER_MUSIC_PLAY_STATUS_ICON, MPLAYER_MUSIC_ICON_TIMER, MUSIC_ICON_PERIOD);
                //    MApp_ZUI_API_InvalidateWindow(HWND_MEDIA_PLAYER_MUSIC_PLAY_STATUS_ICON);
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_FB:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_FB\n"););
            {
                U8 *pu8FfSpeed=MApp_MPlayer_QueryMusicInfo(MP3_INFO_CHECK_FF_FB,NULL);
                _MApp_ACTdmp_MusicCancelRepeatAB();
                //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                //DMP_MusicInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
                if(MApp_MPlayer_QueryMusicFileCurrentTime() < 2) // 2 sec
                {
                    break;
                }
                if(*pu8FfSpeed != 0)
                {
                    switch(MApp_MPlayer_QueryMusicPlayMode())
                    {
                        case E_MPLAYER_MUSIC_PAUSE:
                            //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                        case E_MPLAYER_MUSIC_NORMAL:
                        case E_MPLAYER_MUSIC_FF_2X:
                        case E_MPLAYER_MUSIC_FF_4X:
                        case E_MPLAYER_MUSIC_FF_8X:
                        case E_MPLAYER_MUSIC_FF_16X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FB_2X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB2X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FB_2X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FB_4X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB4X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FB_4X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FB_8X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB8X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FB_8X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_FB_16X);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_FB16X;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;IsPause = 0 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
                            break;
                        case E_MPLAYER_MUSIC_FB_16X:
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                            _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                            //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                            break;
                        default:
                            DMP_DBG(printf("Current state do not allow trick play!\n"););
                            break;
                    }
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                    if (MApp_ZUI_API_IsExistTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN))
                    {
                        MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                    }
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                    if (_enDmpPlayIconType == PLAY_MODE_ICON_PLAY)
                    {
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                    }
                }
                else
                {
                //    _enMediaPlayerIconType = PLAY_MODE_ICON_FB_INVALID;
                //    MApp_ZUI_API_SetTimer(HWND_MEDIA_PLAYER_MUSIC_PLAY_STATUS_ICON, MPLAYER_MUSIC_ICON_TIMER, MUSIC_ICON_PERIOD);
                //    MApp_ZUI_API_InvalidateWindow(HWND_MEDIA_PLAYER_MUSIC_PLAY_STATUS_ICON);
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_MUTE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_MUTE\n"););
            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_VOLUME_CONFIG_PANE))
                {
                    MApp_ZUI_API_KillTimer(HWND_DMP_VOLUME_LIST, DMP_VOLUME_TIMER);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_VOLUME_LIST, SW_HIDE);
                //    MApp_ZUI_API_RestoreFocusCheckpoint();
                }
            {
                MApp_KeyProc_Mute();
            }
            break;
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_REPEAT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_REPEAT\n"););
            {
                // TODO: need test
                enumMPlayerRepeatMode eRepeatMode = MApp_MPlayer_QueryRepeatMode();
                if(eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_1);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_1;
                }
                else if(eRepeatMode == E_MPLAYER_REPEAT_1)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_ALL;
                }
                else
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_NONE);
                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_REPEAT_NONE;
                }
            }
            if(MUSICINFO_REPEAT < _u8InfoBarIdx)
            {
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_REPEAT+u8MusicInfoBarMax -_u8InfoBarIdx]);
            }
            else
            {
                MApp_ZUI_API_SetFocus(_hwndListInfoBar[MUSICINFO_REPEAT - _u8InfoBarIdx]);
            };
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            break;
        /*case EN_EXE_DMP_PLAYBACK_MUSICINFO_AB_REPEAT:
            if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
            {
                //error handling
                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                break;
            }
            if(MApp_MPlayer_IsMediaFileInPlaying() &&
                MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING
                && MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)
            {
                //FOR TEST - Music Repeat A->B
                _enDmpPlayStrType =_enDmpPlayIconType =PLAY_MODE_ICON_AB_REPEAT;
                DMP_MusicInfoBarTable[MUSICINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                DMP_MusicInfoBarTable[MUSICINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;

                if(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0] == 0xFFFFFFFF
                    && _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1] == 0xFFFFFFFF)
                {
                }
                if(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0] == 0xFFFFFFFF)
                {// Repeat A
                    _enRepeatABStatus = REPEATAB_MODE_A;
                    _enDmpPlayStrType =_enDmpPlayIconType =PLAY_MODE_ICON_SETA;
                    DMP_MusicInfoBarTable[MUSICINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                    DMP_MusicInfoBarTable[MUSICINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_B;
                    _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0] = MApp_MPlayer_QueryMusicFileCurrentTime();
                }
                else if(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1] == 0xFFFFFFFF)
                {// Repeat B
                    _enRepeatABStatus = REPEATAB_MODE_AB;
                    _enDmpPlayStrType =_enDmpPlayIconType =PLAY_MODE_ICON_AB_LOOP;
                    DMP_MusicInfoBarTable[MUSICINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                    DMP_MusicInfoBarTable[MUSICINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_None;
                    _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1] = MApp_MPlayer_QueryMusicFileCurrentTime();

                    if(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1] > _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0])
                    {
                        switch(MApp_MPlayer_QueryCurrentFileMediaSubType())
                        {
                        #if (ENABLE_WMA)
                            case E_MPLAYER_SUBTYPE_WMA:
                                MApp_WMA_ProcessTimeOffset(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0]*1000);
                                break;
                        #endif

                            case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
                            case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
                            case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_OGG)
                            case E_MPLAYER_SUBTYPE_OGG:
#endif
#if ( ENABLE_AMR )
                            case E_MPLAYER_SUBTYPE_AMR:
                            case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_FLAC)
                            case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
                            case E_MPLAYER_SUBTYPE_AC3:
#endif


                                MApp_Music_ProcessTimeOffset(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0]*1000);
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    { //Invalid time : B <= A
                        //error handling
                        _MApp_ACTdmp_MusicCancelRepeatAB();
                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                    }
                }
                else
                {// Clear A->B
                    _MApp_ACTdmp_MusicCancelRepeatAB();
                }
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);

            }
            break;
		*/
        #if (ENABLE_MPLAYER_CAPTURE_MUSIC == 1)
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_CAPTURE:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_CAPTURE\n"););
            {
                if(MApp_MPlayer_IsMusicRecording() == FALSE)
                {
                    if (MApp_MPlayer_StartCaptureBootUpMusic() == E_MPLAYER_RET_OK)
                    {
                        DMP_MusicInfoBarTable[MUSICINFO_CAPTURE][INFOBAR_STR_IDX] = en_str_Capture_Stop;
                    }
                }
                else if(MApp_MPlayer_IsMusicRecording() == TRUE)
                {
                    if (MApp_MPlayer_EndCaptureBootUpMusic() == E_MPLAYER_RET_OK)
                    {
                        DMP_MusicInfoBarTable[MUSICINFO_CAPTURE][INFOBAR_STR_IDX] = en_str_Capture;
                    }
                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            break;
        #endif
		#if ENABLE_GOTO_TIME
        case EN_EXE_DMP_PLAYBACK_MUSICINFO_GOTO_TIME:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_MUSICINFO_GOTO_TIME\n"););
            {
                _u8Hour = 0;
                _u8Minute = 0;
                _u8Second = 0;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP, SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_GROUP);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT1);

            #if ENABLE_ATSC_TTS
                MApp_TTS_Cus_Add_Str_By_StrId(en_str_Hour);

                U8 au8TmpBuf[2]={0};
                au8TmpBuf[0] = '0' + _u8Hour;
                au8TmpBuf[1] = 0; // For string end
                MApp_TTS_Cus_AddU8String(au8TmpBuf);
            #endif
            }
            break;
			#endif
 //========================TEXTINFO============================//
#if (ENABLE_MPLAYER_TEXT)
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_MUSIC:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_MUSIC\n"););
            {
                if(MApp_MPlayer_IsMusicPlaying())
                {
                     msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    MApp_MPlayer_StopMusic();
                    //if (!msAPI_AUD_IsAudioMutedByUser()) //smc.chy 2011/04/22
                    {
                        //printf("ENTER 1");
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
               }
                else
                {
                //>>wht120514_2
                  //  if(E_MPLAYER_RET_OK==MApp_MPlayer_PlayMusic())
                    //    MApp_DMP_SetDmpFlag(DMP_FLAG_BGM_MODE);
                    MApp_DMP_SetDmpFlag(DMP_FLAG_BGM_MODE);
                    MApp_MPlayer_PlayMusic();
			   //<<wht120514_2
                }
            }
			//>>wht120514_2
			DMP_TextInfoBarTable[TEXTINFO_MUSIC][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_BGM;
			DMP_TextInfoBarTable[TEXTINFO_MUSIC][INFOBAR_STR_IDX] = en_str_Music;
			_enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_BGMUSIC_MODE;	
			MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
			MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
			//<<wht120514_2
			MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
			break;
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_INFO:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_INFO\n"););
            _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
            HWND_DMP_PLAYBACK_TEXTINFO_INFO_FILENAME_TEXT,TRUE);
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXTINFO_INFO_GROUP, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TEXTINFO_INFO_INFOCLOSE);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_INFOCLOSE:
             DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_INFOCLOSE\n"););
            _MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
            HWND_DMP_PLAYBACK_TEXTINFO_INFO_FILENAME_TEXT,FALSE);
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXTINFO_INFO_GROUP,SW_HIDE);
                if(TEXTINFO_INFO < _u8InfoBarIdx)
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+9]);
                }
                else
                {
                    MApp_ZUI_API_SetFocus(_hwndListInfoBar[u8InfobarIdxTemp+9]);
                }
            }
            break;
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_PLAYLIST:

            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_PLAYLIST\n"););
            {
                u8CurrentPlaylistPageIdx = 0;
                u8CurrentPlaylistTotalPage = 1;
                _MApp_ACTdmp_Playback_ShowPlaylistWin(E_MPLAYER_TYPE_TEXT, TRUE);
            }
            break;
        // text control===============================
        //Previous Page
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_PREV:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_PREV\n"););
            {
                if (MApp_TEXT_GetPageIndex() > 0)
                {
                    if(MApp_MPlayer_TextPrevPage() == E_MPLAYER_RET_OK)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
                    }
                }
            }
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_PREV %lu %lu\n",MApp_TEXT_GetPageIndex(),MApp_TEXT_GetTotalPage()));
            break;
        case EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PAGE_UP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PAGE_UP\n"););
            {
                if (MApp_TEXT_GetPageIndex() > 0)
                {
                    if(MApp_MPlayer_TextPrevPage() == E_MPLAYER_RET_OK)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
                    }
                }
            }
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PAGE_UP %lu %lu\n",MApp_TEXT_GetPageIndex(),MApp_TEXT_GetTotalPage()));
            break;
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXT\n"););
            {
                if (MApp_TEXT_GetPageIndex() < MApp_TEXT_GetTotalPage())
                {
                    if(MApp_MPlayer_TextNextPage() == E_MPLAYER_RET_OK)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
                    }
                }
            }
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXT %lu %lu\n",MApp_TEXT_GetPageIndex(),MApp_TEXT_GetTotalPage()));
            break;
        case EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PAGE_DOWN:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PAGE_DOWN\n"););
            {
                if (MApp_TEXT_GetPageIndex() < MApp_TEXT_GetTotalPage())
                {
                    if(MApp_MPlayer_TextNextPage() == E_MPLAYER_RET_OK)
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
                    }
                }
            }
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PAGE_DOWN %lu %lu\n",MApp_TEXT_GetPageIndex(),MApp_TEXT_GetTotalPage()));
            break;
        case EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_EXIT:
        case EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_STOP:
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_STOP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_EXIT\n"););
            {
                // TODO: need refine
                MApp_MPlayer_Stop();
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MAINFRAME);

                if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
                {
                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
                }

                U16 u16PlayingIdx = 0;

                u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();

                MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx / NUM_OF_PHOTO_FILES_PER_PAGE);

                DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););

                if (MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
                {
                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                    MApp_MPlayer_SetCurrentPageIndex(0);
                }
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            }
            break;
        case EN_EXE_DMP_PLAYBACK_TEXTINFO_NEXTFILE:
        case EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_NEXT:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_NEXT\n"););
            {
                MApp_MPlayer_PlayNextFile();
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_TEXT, DEFAULT_TEXT_ERROR_DELAY_TIME);
                m_u16PlayErrorNum = 0;
                #if (ENABLE_DRM)
                m_u16DRMErrorNum = 0;
                #endif
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_NEXT;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            }
            break;

        case EN_EXE_DMP_PLAYBACK_TEXTINFO_PREVFILE:
        case EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PREVIOUS:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_TEXT_FULL_WIN_PREVIOUS\n"););
            {
                MApp_MPlayer_PlayPrevFile();
                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_TEXT, DEFAULT_TEXT_ERROR_DELAY_TIME);
                m_u16PlayErrorNum = 0;
                #if (ENABLE_DRM)
                m_u16DRMErrorNum = 0;
                #endif
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PREVIOUS;
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            }
            break;
            // TODO: fix below 2 action!?
        case EN_EXE_DMP_PLAYBACK_MAIN_PAGE_ITEM_MENU:
            break;
        case EN_EXE_DMP_PLAYBACK_MAIN_PAGE_ITEM_INPUTSOURCE:
            break;

#endif
//==================PLAYLIST ========================//
        case EN_EXE_DMP_PLAYBACK_PLAYLIST_NAV_PAGEUP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PLAYLIST_NAV_PAGEUP\n"););
            {
                enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                if(u8CurrentPlaylistPageIdx == 0) // first page
                {
                    // do nothing
                }
                else
                {
                    u8CurrentPlaylistPageIdx--;
                    _MApp_ACTdmp_Playback_ShowPlaylistWin(eMediaType, FALSE);
                    MApp_ZUI_API_SetFocus(_hwndListPlaylistItem[UI_DMP_PLAYLIST_NUMBER-1]);
                }
            }
			_Mapp_ACTdmp_Playback_MarqueeText((MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2);
            return TRUE;
        case EN_EXE_DMP_PLAYBACK_PLAYLIST_PAGEUP:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PLAYLIST_PAGEUP\n"););
            {
                enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                if(u8CurrentPlaylistPageIdx == 0) // first page
                {
                    // do nothing
                }
                else
                {
                    u8CurrentPlaylistPageIdx--;
                    _MApp_ACTdmp_Playback_ShowPlaylistWin(eMediaType, FALSE);
                }
            }
			_Mapp_ACTdmp_Playback_MarqueeText((MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2);
            return TRUE;
		case EN_EXE_DMP_PLAYBACK_PLAYLIST_UP:
			_Mapp_ACTdmp_Playback_MarqueeText((MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2-1);
			break;
        case EN_EXE_DMP_PLAYBACK_PLAYLIST_DOWN:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PLAYLIST_DOWN\n"););
            {
                enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                U16 u16PlaylistTotalFileNum = 0;
#if PLAYLIST_BGM
                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                if (bIsBGMPlaylist == TRUE)
                {
                    ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                    eMediaType = E_MPLAYER_TYPE_MUSIC;
                    //------------------------Enter music mode------------------------
                }
#endif
                u16PlaylistTotalFileNum = MApp_MPlayer_QueryPlayListFileNum(eMediaType);
                U16 u16FocusIdx;
                u16FocusIdx = (MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2;
                u16FocusIdx += u8CurrentPlaylistPageIdx * UI_DMP_PLAYLIST_NUMBER;
                if(u16PlaylistTotalFileNum == 0) // no selected files
                {
                    u16PlaylistTotalFileNum = MApp_MPlayer_QueryTotalFileNum();
#if PLAYLIST_BGM
                    if (bIsBGMPlaylist == TRUE)
                        u16PlaylistTotalFileNum -= MApp_MPlayer_QueryMusicDirectoryNumber();
                    else
#endif
                        u16PlaylistTotalFileNum -= MApp_MPlayer_QueryDirectoryNumber();
                }
                if (u16FocusIdx == u16PlaylistTotalFileNum-1)
                {
#if PLAYLIST_BGM
                    if (bIsBGMPlaylist == TRUE)
                    {
                        //------------------------Exit music mode------------------------
                        MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
                    }
#endif
                    //last turn;
					//_Mapp_ACTdmp_Playback_MarqueeText((MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2);
                    return TRUE;
                }
#if PLAYLIST_BGM
                if (bIsBGMPlaylist == TRUE)
                {
                    //------------------------Exit music mode------------------------
                    MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
                }
#endif
            }
			_Mapp_ACTdmp_Playback_MarqueeText((MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2+1);
            break;
        case EN_EXE_DMP_PLAYBACK_PLAYLIST_PAGEDOWN:
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PLAYLIST_PAGEDOWN\n"););
            {
                enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                U16 u16PlaylistTotalFileNum = 0;
#if PLAYLIST_BGM
                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                if (bIsBGMPlaylist == TRUE)
                {
                    ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                    MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                    eMediaType = E_MPLAYER_TYPE_MUSIC;
                    //------------------------Enter music mode------------------------
                }
#endif
                u16PlaylistTotalFileNum = MApp_MPlayer_QueryPlayListFileNum(eMediaType);

                // 2 case: has selected files or none
                if(u16PlaylistTotalFileNum == 0) // no selected files
                {
                    U16 u16TotalFileNum = 0;
                    u16TotalFileNum = MApp_MPlayer_QueryTotalFileNum();
#if PLAYLIST_BGM
                    if (bIsBGMPlaylist == TRUE)
                        u16TotalFileNum -= MApp_MPlayer_QueryMusicDirectoryNumber();
                    else
#endif
                        u16TotalFileNum -= MApp_MPlayer_QueryDirectoryNumber();
                    u8CurrentPlaylistTotalPage = (u16TotalFileNum + UI_DMP_PLAYLIST_NUMBER - 1)/UI_DMP_PLAYLIST_NUMBER;
                    if(u8CurrentPlaylistPageIdx == u8CurrentPlaylistTotalPage - 1)
                    {
#if PLAYLIST_BGM
                        if (bIsBGMPlaylist == TRUE)
                        {
                            //------------------------Exit music mode------------------------
                            MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
                        }
#endif
                        //do nothing
                        return TRUE;
                    }
                    else
                    {
                        u8CurrentPlaylistPageIdx++;
                    }
                }
                else
                {
                    u8CurrentPlaylistTotalPage = (u16PlaylistTotalFileNum + UI_DMP_PLAYLIST_NUMBER - 1)/UI_DMP_PLAYLIST_NUMBER;
                    if(u8CurrentPlaylistPageIdx == u8CurrentPlaylistTotalPage - 1)
                    {
#if PLAYLIST_BGM
                        if (bIsBGMPlaylist == TRUE)
                        {
                            //------------------------Exit music mode------------------------
                            MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
                        }
#endif
                        //do nothing
                        return TRUE;
                    }
                    else
                    {
                        u8CurrentPlaylistPageIdx++;
                    }
                }

                _MApp_ACTdmp_Playback_ShowPlaylistWin(eMediaType, FALSE);
#if PLAYLIST_BGM
                if (bIsBGMPlaylist == TRUE)
                {
                    //------------------------Exit music mode------------------------
                    MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
                }
#endif
            }
			_Mapp_ACTdmp_Playback_MarqueeText((MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2);
            return TRUE;
        case EN_EXE_DMP_PLAYBACK_PLAYLIST_SELECT:
            // TODO: can not across different directories, need to change
            // directories, change dirves.......;
            // refer MApp_MPlayer_MusicPlayList_PlayByIdx()
            DMP_DBG(printf("EN_EXE_DMP_PLAYBACK_PLAYLIST_SELECT"););
            {
                enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
                m_u16PlayErrorNum = 0;
                #if (ENABLE_DRM)
                m_u16DRMErrorNum = 0;
                #endif
                switch(eMediaType)
                {
                    // TODO: fix every mediaType
                    case E_MPLAYER_TYPE_PHOTO:
#if PLAYLIST_BGM
                        if (bIsBGMPlaylist == TRUE)
                        {
                            //need to check if there is selected files...
                            U16 u16FileIdx, u16PlayingIdx;
                            U32 i;

                            i = (MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2;
                            u16PlayingIdx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER)+ i;

                            _MApp_DMP_SavePhotoPath();

                            //------------------------Enter music mode------------------------
                            {
                                MApp_MPlayer_StopMusic();

                                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);

                                if(MApp_MPlayer_QueryPlayListFileNum(E_MPLAYER_TYPE_MUSIC) == 0)
                                {
                                    //there is no selected file

                                    //MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx,&FileInfo);
                                    //MApp_MPlayer_StopMusic();
                                    //msAPI_Timer_Delayms(50);

                                    MApp_MPlayer_Change2TargetDirectory(MApp_DMP_GetDriveFromMappingTable(m_u8BgmDrive), m_u16BgmIdxByDir, m_u16BgmDepth);
                                    u16PlayingIdx += MApp_MPlayer_QueryMusicDirectoryNumber();
                                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx);
                                    eBgmPlayMode = E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT;
                                    MApp_MPlayer_SetPlayMode(eBgmPlayMode);

                                }
                                else
                                {
                                    //there are some selected files
                                    //MApp_MPlayer_StopMusic();
                                    //msAPI_Timer_Delayms(50);
                                    if(!MApp_MPlayer_Change2TargetPath(u16PlayingIdx))
                                    {
                                        DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail MUSIC\n"););
                                    }
                                    u16FileIdx = MApp_MPlayer_QueryFileIdxByPlayingIdx(u16PlayingIdx);
                                    if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx)!=E_MPLAYER_RET_OK )
                                    {
                                        DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail MUSIC\n"););
                                    }
                                    eBgmPlayMode = E_MPLAYER_PLAY_SELECTED_FROM_CURRENT;
                                    MApp_MPlayer_SetPlayMode(eBgmPlayMode);

                                }
                                _MApp_DMP_PlayBGM();
                            }
                            //------------------------Exit music mode------------------------
                            MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_PHOTO, FALSE);
                            _MApp_DMP_EnterPhotoPath();

                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        }
                        else
#endif
                        {
                            //need to check if there is selected files...
                            U16 u16FileIdx;
                            U16 u16PlayingIdx;
                            U32 i;
                            i = (MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2;
                            u16PlayingIdx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER)+ i;
                            if(MApp_MPlayer_QueryPhotoPlayMode() != E_MPLAYER_PHOTO_NORMAL)
                            {
                               _enDmpPlayStrType = _enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                               MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                               MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            }
                            if(MApp_MPlayer_QueryPlayListFileNum(E_MPLAYER_TYPE_PHOTO) == 0)
                            {
                                //there is no selected file
                                u16PlayingIdx += MApp_MPlayer_QueryDirectoryNumber();
                                //MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx,&FileInfo);
                                MApp_MPlayer_Stop();
                                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16PlayingIdx);
                                MApp_MPlayer_Play();
                                MApp_MPlayer_SetPhotoSlideShowDelayTime(DEFAULT_PHOTO_SLIDESHOW_DELAY_TIME);
                                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_PHOTO, DEFAULT_PHOTO_ERROR_DELAY_TIME);
                            }
                            else
                            {
                                //there are some selected files
                                MApp_MPlayer_Stop();
                            #if !EN_DMP_SEARCH_ALL
                                if(!MApp_MPlayer_Change2TargetPath(u16PlayingIdx))
                                {
                                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail PHOTO\n"););
                                }
                            #endif
                                u16FileIdx = MApp_MPlayer_QueryFileIdxByPlayingIdx(u16PlayingIdx);
                                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx)!=E_MPLAYER_RET_OK )
                                {
                                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail PHOTO\n"););
                                }
                                MApp_MPlayer_Play();
                                //reset timer
                                MApp_MPlayer_SetPhotoSlideShowDelayTime(DEFAULT_PHOTO_SLIDESHOW_DELAY_TIME);
                                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_PHOTO, DEFAULT_PHOTO_ERROR_DELAY_TIME);
                            }
                            DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        }
                        break;

#if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        {
                            //need to check if there is selected files...
                            U16 u16FileIdx;
                            U16 u16PlayingIdx;
                            //if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                            {
#if (ENABLE_SUBTITLE_DMP)
                                MApp_MPlayer_DisableSubtitle();
#endif
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                            }

                            U32 i;
                            i = (MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2;
                            u16PlayingIdx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER)+ i;
                            if(MApp_MPlayer_QueryMoviePlayMode() != E_MPLAYER_MOVIE_NORMAL)
                            {
                               _enDmpPlayStrType = _enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                               MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                               MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            }
                            if(MApp_MPlayer_QueryPlayListFileNum(E_MPLAYER_TYPE_MOVIE) == 0)
                            {
                                //there is no selected file
                                u16PlayingIdx += MApp_MPlayer_QueryDirectoryNumber();
                                //MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx,&FileInfo);
                                MApp_MPlayer_Stop();
                                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16PlayingIdx);
                                MApp_MPlayer_Play();
                                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MOVIE, DEFAULT_MOVIE_ERROR_DELAY_TIME);
                            }
                            else
                            {
                                //there are some selected files
                                MApp_MPlayer_Stop();
                            #if !EN_DMP_SEARCH_ALL
                                if(!MApp_MPlayer_Change2TargetPath(u16PlayingIdx))
                                {
                                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail MOVIE\n"););
                                }
                            #endif
                                  u16FileIdx = MApp_MPlayer_QueryFileIdxByPlayingIdx(u16PlayingIdx);

                                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx)!=E_MPLAYER_RET_OK )
                                {
                                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail MOVIE\n"););
                                }
                                MApp_MPlayer_Play();
                                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MOVIE, DEFAULT_MOVIE_ERROR_DELAY_TIME);
                            }
                            _MApp_ACTdmp_MovieCancelRepeatAB();

                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
#if (ENABLE_SUBTITLE_DMP)
                            //MApp_MPlayer_MovieChangeSubtitleTrack(0);
                            MApp_MPlayer_DisableSubtitle();
#endif
                            _MApp_ZUI_ACTdmp_OperateSubtitle();

                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        }
                        break;
#endif
                    case E_MPLAYER_TYPE_MUSIC:
                        {
                            if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                            {
                               _enDmpPlayStrType = _enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                               MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                               MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            }
                            MApp_MPlayer_StopMusic();
                            if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                            {
                                MApp_MPlayer_DisableLRCLyric();
                                memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE, SW_HIDE);
                            }
                            msAPI_Timer_Delayms(50);
                            U32 i;
                            i = (MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2;

                            if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
                                (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
                            {
                                //there are some selected files
                                U16 u16Idx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER) + i;

                                MApp_MPlayer_Stop();
                            #if !EN_DMP_SEARCH_ALL
                                if(!MApp_MPlayer_Change2TargetPath(u16Idx))
                                {
                                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail music\n"););
                                }
                            #endif
                                U16 u16FileIdx = MApp_MPlayer_QueryFileIdxByPlayingIdx(u16Idx);

                                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx)!=E_MPLAYER_RET_OK )
                                {
                                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail MUSIC\n"););
                                }
                                MApp_MPlayer_Play();
                                MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MUSIC, DEFAULT_MUSIC_ERROR_DELAY_TIME);
                            }
                            else if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                                    MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                            {
                                U16 u16PlayingIdx;
                                u16PlayingIdx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER)+ i;
                                if(MApp_MPlayer_QueryPlayListFileNum(E_MPLAYER_TYPE_MUSIC) == 0)
                                {
                                    //there is no selected file
                                    u16PlayingIdx += MApp_MPlayer_QueryDirectoryNumber();
                                    MApp_MPlayer_Stop();
                                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16PlayingIdx);
                                    MApp_MPlayer_Play();
                                    MApp_MPlayer_SetPlayerErrorDelayTime(E_MPLAYER_TYPE_MUSIC, DEFAULT_MUSIC_ERROR_DELAY_TIME);
                                }
                            }
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                            DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                        }
                        break;
                        #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                        {
                            //need to check if there is selected files...
                            U16 u16FileIdx;
                            U16 u16PlayingIdx;
                            U32 i;
                            i = (MApp_ZUI_API_GetFocus() - _hwndListPlaylistItem[0])/2;
                            u16PlayingIdx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER)+ i;

                            if(MApp_MPlayer_QueryPlayListFileNum(E_MPLAYER_TYPE_TEXT) == 0)
                            {
                                //there is no selected file
                                u16PlayingIdx += MApp_MPlayer_QueryDirectoryNumber();
                                //MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx,&FileInfo);
                                MApp_MPlayer_Stop();
                                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16PlayingIdx);
                                MApp_MPlayer_Play();

                            }
                            else
                            {
                                //there are some selected files
                                MApp_MPlayer_Stop();
                            #if !EN_DMP_SEARCH_ALL
                                if(!MApp_MPlayer_Change2TargetPath(u16PlayingIdx))
                                {
                                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail text\n"););
                                }
                            #endif
                                u16FileIdx = MApp_MPlayer_QueryFileIdxByPlayingIdx(u16PlayingIdx);

                                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx)!=E_MPLAYER_RET_OK )
                                {
                                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail text\n"););
                                }
                                MApp_MPlayer_Play();
                            }
                        }
                        break;
                        #endif
                    default:
                        DMP_DBG(printf("unsupport EN_EXE_DMP_PLAYBACK_PLAYLIST_SELECT"););
                        break;
                }
            }
            break;
// dialog=================
            case EN_EXE_DMP_PLAYBACK_CONFIRM_DIALOG_YES:
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG,SW_HIDE);
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_PHOTO:
                        #if (DISPLAY_LOGO)
                        {
                            if(MApp_MPlayer_CaptureLogo() != E_MPLAYER_RET_OK)
                            {
                                DMP_DBG(printf("save logo fail\n"););
                            }
                        }
                        #endif
                        switch(_enDmpPlayStrType)
                        {
                            case PLAY_MODE_ICON_PLAY:
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_NORMAL);
                                break;
                            case PLAY_MODE_ICON_PAUSE:
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                                break;
                            default:
                                break;
                        }
                        _enDmpPlayStrType = _enDmpPlayIconType;
                        MApp_ZUI_API_RestoreFocusCheckpoint();
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_GROUP, SW_SHOW);
                        break;
                        #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        if(MApp_MPlayer_IsMediaFileInPlaying() &&
                            (MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING))
                        {
                            U8 *pu8Filename;
                            pu8Filename = (U8*)msAPI_Memory_Allocate(FILE_INFO_LONG_FILENAME_SIZE, BUF_ID_FILEBROWER);

                            if(pu8Filename == NULL)
                            {
                                __ASSERT(0);
                                return FALSE;
                            }
                            snprintf((char*)pu8Filename, 8, "CAP.JPG");
                            //if(MApp_MPlayer_GenCaptureFileName(pu8Filename, FILE_INFO_LONG_FILENAME_SIZE) == E_MPLAYER_RET_OK)
                            {
                                // Hide all window
                                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);

                            #if 0
                                GOP_GwinFBAttr fbAttr;
                                GRAPHIC_DC *dc = MApp_ZUI_API_GetBufferDC();
                                MApi_GOP_GWIN_GetFBInfo(dc->u8FbID, &fbAttr);

                                if(MApp_MPlayer_CaptureVideo(pu8Filename, &fbAttr) != E_MPLAYER_RET_OK)
                                {
                                    DMP_DBG(printf("MApp_MPlayer_CaptureVideo fail\n"););
                                }
                            #endif
                            #if(ENABLE_MPLAYER_VIDEO_CAPTURE)
                                ST_VIDEO_CAPTURE_SET_INFO Info;
                                U16 u16DirName[9] = {'\\', 'C', 'A', 'P', 'T', 'U', 'R', 'E', 0};
                                memset(&Info,0,sizeof(ST_VIDEO_CAPTURE_SET_INFO));
                                Info.ThumbBitBltInfo.bThumbnail = FALSE;
                                Info.bScreenFreeze = FALSE;
                                Info.u8ConnectDrive = MApp_DMP_GetCurDrvIdx();
                                if(MApp_MassStorage_GetDrivePort(Info.u8ConnectDrive) == MSD_PORT_1)
                                {
                                    Info.u8ConnectPort = 0;
                                }
                                else if(MApp_MassStorage_GetDrivePort(Info.u8ConnectDrive) == MSD_PORT_2)
                                {
                                    Info.u8ConnectPort = 1;
                                }
                                else
                                {
                                    Info.u8ConnectPort = 0xFF; // invalid
                                }
                                FS_ASCII2Unicode(pu8Filename);
                                Info.pu16FileName = (U16*)(void*)pu8Filename;
                                Info.pu16CapturePath = u16DirName;
                                Info.u16FileNameLen = FS_strlen_U((U16*)(void*)pu8Filename);
                                Info.u16CapturePathLen = FS_strlen_U(u16DirName)+1;//need to contain the last \0
                                Info.pfnIsPathUpdate= NULL;
                                Info.pfnRenameFileIfFileExisted = NULL;
                                Info.bLoadCoprocessor = FALSE;
                                DMP_DBG(printf("Start video capture\n"););
                                if(MApp_MPlayer_CaptureVideoBegin(&Info) != E_CAPTURE_RET_OK)
                                {
                                    DMP_DBG(printf("MApp_MPlayer_CaptureVideo fail\n"););
                                }
                            #endif
                                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                            }
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_SHOW);
                            MApp_ZUI_API_RestoreFocusCheckpoint();
                            msAPI_Memory_Free(pu8Filename, BUF_ID_FILEBROWER);

                            switch(_enDmpPlayStrType)
                            {
                                case PLAY_MODE_ICON_PLAY:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                                    break;
                                case PLAY_MODE_ICON_PAUSE:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
                                    break;
                                case PLAY_MODE_ICON_FF2X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_2X);
                                    break;
                                case PLAY_MODE_ICON_FF4X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_4X);
                                    break;
                                case PLAY_MODE_ICON_FF8X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_8X);
                                    break;
                                case PLAY_MODE_ICON_FF16X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_16X);
                                    break;
                                case PLAY_MODE_ICON_FF32X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_16X);
                                    break;
                                case PLAY_MODE_ICON_FB2X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_2X);
                                    break;
                                case PLAY_MODE_ICON_FB4X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_4X);
                                    break;
                                case PLAY_MODE_ICON_FB8X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_8X);
                                    break;
                                case PLAY_MODE_ICON_FB16X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_16X);
                                    break;
                                case PLAY_MODE_ICON_FB32X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_32X);
                                    break;
                                case PLAY_MODE_ICON_SF2X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_2X);
                                    break;
                                case PLAY_MODE_ICON_SF4X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_4X);
                                    break;
                                case PLAY_MODE_ICON_SF8X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_8X);
                                    break;
                                case PLAY_MODE_ICON_SF16X:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_16X);
                                    break;
                                case PLAY_MODE_ICON_SD:
                                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_STEP);
                                    break;
                                default:
                                    break;
                            }
                            _enDmpPlayStrType = _enDmpPlayIconType;
                            return TRUE;
                        }
                        break;
                        #endif
                    default:
                        break;

                }
                MApp_ZUI_API_RestoreFocusCheckpoint();
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_STATUS_GROUP);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
            }
                break;
            case EN_EXE_DMP_PLAYBACK_CONFIRM_DIALOG_NO:
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_CONFIRM_DIALOG,SW_HIDE);

                switch(MApp_MPlayer_QueryCurrentMediaType())
                {
                    case E_MPLAYER_TYPE_PHOTO:
                        //MApp_MPlayer_CaptureLogo();
                        switch(_enDmpPlayStrType)
                        {
                            case PLAY_MODE_ICON_PLAY:
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_NORMAL);
                                break;
                            case PLAY_MODE_ICON_PAUSE:
                                MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_PAUSE);
                                break;
                             default:
                                break;
                        }
                        _enDmpPlayStrType = _enDmpPlayIconType;
                        break;
                        #if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        switch(_enDmpPlayStrType)
                        {
                            case PLAY_MODE_ICON_PLAY:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                                break;
                            case PLAY_MODE_ICON_PAUSE:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
                                break;
                            case PLAY_MODE_ICON_FF2X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_2X);
                                break;
                            case PLAY_MODE_ICON_FF4X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_4X);
                                break;
                            case PLAY_MODE_ICON_FF8X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_8X);
                                break;
                            case PLAY_MODE_ICON_FF16X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_16X);
                                break;
                            case PLAY_MODE_ICON_FF32X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_32X);
                                break;
                            case PLAY_MODE_ICON_FB2X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_2X);
                                break;
                            case PLAY_MODE_ICON_FB4X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_4X);
                                break;
                            case PLAY_MODE_ICON_FB8X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_8X);
                                break;
                            case PLAY_MODE_ICON_FB16X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_16X);
                                break;
                            case PLAY_MODE_ICON_FB32X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_32X);
                                break;
                            case PLAY_MODE_ICON_SF2X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_2X);
                                break;
                            case PLAY_MODE_ICON_SF4X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_4X);
                                break;
                            case PLAY_MODE_ICON_SF8X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_8X);
                                break;
                            case PLAY_MODE_ICON_SF16X:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_SF_16X);
                                break;
                            case PLAY_MODE_ICON_SD:
                                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_STEP);
                                break;
                            default:
                                break;
                        }
                        _enDmpPlayStrType = _enDmpPlayIconType;
                        break;
                        #endif
                    default:
                        break;

                }
                MApp_ZUI_API_RestoreFocusCheckpoint();
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFOBAR_GROUP, SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_STATUS_GROUP);
            }
            break;
#if (ENABLE_MPLAYER_MOVIE)
        case EN_EXE_DMP_MOVIERESUME_NO:
			{
			//>>wht120717_1
		     switch(MApp_MPlayer_QueryCurrentMediaType())
	            {
		            case E_MPLAYER_TYPE_MOVIE:
			     {
			            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG,SW_SHOW);
			            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
			            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
			            //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG); //change by gchen @ 20110513

			            if(g_bUnsupportAudio)  //20100809EL
			            {
			                DMP_DBG(printf(">>>>>>>>>>>111   EN_EXE_DMP_MOVIERESUME_EXIT   Unsupport audio\n"););
			                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE);
			                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
			                g_bUnsupportAudio = FALSE;
			            }
			            bResume = TRUE; // always reset -> True for next time.

				     //add by gchen  @ 20110513
				     if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE)) // add by gchen @ 20110512
				     {
				   	   HWND hTemp = MApp_ZUI_API_GetFocusCheckpoint();
					   if (MApp_ZUI_API_IsWindowVisible(hTemp))
					   {
			    			MApp_ZUI_API_SetFocus(hTemp);
				          }
					   else //add by gchen @ 20111102 //focus bug
					   {
						MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
                				MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
					   }
					   MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
				     }
				     else
				     {
					    MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
					    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_INFO_PANE, SW_HIDE);
				     }
		            }
			     break;

			     case E_MPLAYER_TYPE_MUSIC:
			     {
			            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG,SW_SHOW);
			            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
			            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
						
			            bResume = TRUE; // always reset -> True for next time.

				     //add by gchen  @ 20110513
				     HWND hTemp = MApp_ZUI_API_GetFocusCheckpoint();
				     if (MApp_ZUI_API_IsWindowVisible(hTemp))
				     {
					     MApp_ZUI_API_SetFocus(hTemp);
			            }
				     else
				     {
					     MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
				     }
				     MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFO_PANE);
			     }
			     break;

			     default:
				 break;
		     	}
            }
			#if 0
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
            if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PAGE_INFOBAR))
                MApp_ZUI_API_RestoreFocusCheckpoint();
            else
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);

            if(g_bUnsupportAudio)  //20100809EL
            {
                DMP_DBG(printf(">>>>>>>>>>>111   EN_EXE_DMP_MOVIERESUME_EXIT   Unsupport audio\n"););
                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE);
                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                g_bUnsupportAudio = FALSE;
            }
            bResume = TRUE; // always reset -> True for next time.
			#endif
			//<<wht120717_1
            break;
        //>>wht120417_1
        case EN_EXE_DMP_MOVIERESUME_YES:
   {
			 switch(MApp_MPlayer_QueryCurrentMediaType()) //wht120614_1
            {
            	case E_MPLAYER_TYPE_MOVIE:   //wht120614_1
	     		{
		            if (bResume)
		            {
		                #if ENABLE_LAST_MEMORY
		                U32 TimeMs,PosL,PosH;
		                MApp_MPlayer_LastMemory_GetResumePos(&TimeMs, &PosL, &PosH);
		                // need to set _u8Second,_u8Minute,_u8Hour correctly
		                //U32 u32GotoTimeMs = (_u8Second+_u8Minute*60+_u8Hour*3600)*1000;
		                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
		                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
		                if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PAGE_INFOBAR))
		                MApp_ZUI_API_RestoreFocusCheckpoint();
		                else
		                    MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);

		                if(g_bUnsupportAudio)  //20100809EL
		                {
		                    DMP_DBG(printf(">>>>>>>>>>>222   EN_EXE_DMP_MOVIERESUME_YES   Unsupport audio\n"););
		                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE);
		                    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
		                    g_bUnsupportAudio = FALSE;
		                }

		                //MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_MOVIEINFO_GOTOTIME_WIN_SELECT);
		                _MApp_ACTdmp_MovieCancelRepeatAB();
		                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
		                DMP_MovieInfoBarTable[MOVIEINFO_AB_REPEAT][INFOBAR_STR_IDX] = en_str_SET_A;
		                // To do : process GOTO TIME.
		                //printf("[Time] Go : %02d:%02d:%02d (%ld)\n", _u8Hour, _u8Minute, _u8Second, u32GotoTimeMs);
		                _u8Hour = 0;
		                _u8Minute = 0;
		                _u8Second = 0;
		                if(TimeMs > MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME))
		                { // Invalid operation
		                    //_MApp_MediaPlayer_ShowMessageBox(MOVIE_MESSAGE_TYPE_GOTO_TIME_EXCEED);
		                    // TODO: error handling
		                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
		                    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
		                }
		                else
		                {
		                    // 1. Cancel Repeat AB Mode
		                    enumMPlayerRet eRet=E_MPLAYER_RET_FAIL;
		                    if(MApp_DMP_GetDmpFlag()& DMP_FLAG_MOVIE_REPEATAB_MODE)
		                    {
		                        _MApp_ACTdmp_MovieCancelRepeatAB();
		                        //    MApp_ZUI_API_ShowWindow(HWND_DMP_MOVIE_INFO_ICON_ADVENCE_GROUP, SW_SHOW);
		                    }
		                    // 2. Disable trick play --> Normal play
		                    if(MApp_MPlayer_QueryMoviePlayMode() != E_MPLAYER_MOVIE_NORMAL)
		                    {
		                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP,SW_HIDE);
		                        MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
		                    }
							eRet=MApp_MPlayer_SetPlayPosition(TimeMs,TRUE);

		                    if(eRet==E_MPLAYER_RET_FAIL)
		                    {
		                        // TODO: error handling
		                        _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
		                        MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
		                    }
		                }
		                #endif
		            }
		            else
		            {
		                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG,SW_SHOW);
		                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
		                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
		                if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PAGE_INFOBAR))
		                    MApp_ZUI_API_RestoreFocusCheckpoint();
		                else
		                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);

		                if(g_bUnsupportAudio)  //20100809EL
		                {
		                    DMP_DBG(printf(">>>>>>>>>>>111   EN_EXE_DMP_MOVIERESUME_NO   Unsupport audio\n"););
		                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE);
		                    MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
		                    g_bUnsupportAudio = FALSE;
		                }
		            }
		            bResume = TRUE; // always reset -> True for next time.
		        }
				break;
			//>>wht120614_1
			case E_MPLAYER_TYPE_MUSIC:
	 		{
	            if (bResume)
	            {
	                #if ENABLE_LAST_MEMORY
		                U32 TimeMs,PosL,PosH;
		                MApp_MPlayer_LastMemory_GetResumePos(&TimeMs, &PosL, &PosH);
				//  printf("TimeMs == %d \n", TimeMs); // test by ghcen @ 20110516
				//  printf("Totaltime == %d \n", MApp_MPlayer_QueryMusicFilePlayTime());
		                // need to set _u8Second,_u8Minute,_u8Hour correctly
		                //U32 u32GotoTimeMs = (_u8Second+_u8Minute*60+_u8Hour*3600)*1000;
		                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
		                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
						
		                // To do : process GOTO TIME.
		                //printf("[Time] Go : %02d:%02d:%02d (%ld)\n", _u8Hour, _u8Minute, _u8Second, u32GotoTimeMs);
	                        _u8Hour = 0;
	                        _u8Minute = 0;
	                        _u8Second = 0;
	                        if(TimeMs > (U32)(MApp_MPlayer_QueryMusicFilePlayTime() * 1000 )) //change by gchen @ 20110728 //fix warning comparison between signed and unsigned
	                        { // Invalid operation
	                            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
	                            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
	                        }
	                        else
	                        {
	                            //TimeMs = 30000; //add by gchen @ 20110516
					//printf(" TimeMs == %d \n", TimeMs);
					switch(MApp_MPlayer_QueryCurrentFileMediaSubType())
	                            {
	                            #if (ENABLE_WMA)
	                                case E_MPLAYER_SUBTYPE_WMA:
	                                    MApp_WMA_ProcessTimeOffset(TimeMs);
	                                    break;
	                            #endif

	                                case E_MPLAYER_SUBTYPE_MP3:
	                                case E_MPLAYER_SUBTYPE_AAC:
	                                case E_MPLAYER_SUBTYPE_WAV:
	                                case E_MPLAYER_SUBTYPE_OGG:
	                                    MApp_Music_ProcessTimeOffset(TimeMs);
	                                    break;
	                                default:
	                                    break;
	                            }
	                        }
	                #endif	
	            }
	            else
	            {
	                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG,SW_SHOW);
	                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
	                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
	            }
	            bResume = TRUE; // always reset -> True for next time.

			     //add by gchen  @ 20110516
			     HWND hTemp = MApp_ZUI_API_GetFocusCheckpoint();
			     if (MApp_ZUI_API_IsWindowVisible(hTemp))
			     {
				     MApp_ZUI_API_SetFocus(hTemp);
		            }
			     else
			     {
				     MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_INFOBAR_ITEM1);
			     }
			     MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFO_PANE);

				 }
		 		break;
			default: //add by gchen @ 20110728 //fix warning  not handled in switch
	 			break;
			//<<wht120614_1
			}
        }
        break;

#endif
#if ENABLE_DRM
#if ENABLE_RESUME_STOP
        case EN_EXE_DMP_RESUMESTOP_YES:
            DMP_DBG(printf("EN_EXE_DMP_RESUMESTOP_YES\n"););
            MApp_ZUI_API_ShowWindow(HWND_DMP_RESUME_STOP_WINDOW, SW_HIDE);
            MApp_ZUI_API_KillTimer(HWND_DMP_RESUME_STOP_WINDOW, DMP_TIMER_RESUMESTOP_WIN);
            #if ENABLE_LAST_MEMORY
            MApp_MPlayer_LastMemory_SetResumePlayAttribute(1);
            #endif

            _u8InfoBarIdx = 0;
            {
                _MApp_ACTdmp_MovieCancelRepeatAB();
                MApp_MPlayer_Stop();
                //if(MApp_MPlayer_IsCurrentExternalSubtitleAvailable() == E_MPLAYER_RET_OK)
                {
#if (ENABLE_SUBTITLE_DMP)
                    MApp_MPlayer_DisableSubtitle();
#endif
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
                }

                //msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

                //MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                //MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
                MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                MApp_ZUI_API_InvalidateWindow(HWND_MAINFRAME);
            }
            // set the file_select index and current page index
            // TODO: across dir, across drive?
            {
                U16 u16PlayingIdx = 0;
                // TODO: fix photo type
            #if !EN_DMP_SEARCH_ALL
                if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
                {
                    DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
                }
            #endif
                u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
                MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx/NUM_OF_PHOTO_FILES_PER_PAGE);
                DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););
                if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
                {
                    DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                    MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                    MApp_MPlayer_SetCurrentPageIndex(0);
                }
            }
            break;

        case EN_EXE_DMP_RESUMESTOP_NO:
            DMP_DBG(printf("EN_EXE_DMP_RESUMESTOP_NO\n"););
            MApp_ZUI_API_ShowWindow(HWND_DMP_RESUME_STOP_WINDOW, SW_HIDE);
            MApp_ZUI_API_KillTimer(HWND_DMP_RESUME_STOP_WINDOW, DMP_TIMER_RESUMESTOP_WIN);
            MApp_ZUI_API_RestoreFocusCheckpoint();
            break;
#endif
#endif
        default:
            break;
    }
    return FALSE;
}

// TODO: fix me
extern U32* MApp_TEXT_GetCurrentLineText(BOOLEAN);

LPTSTR MApp_ZUI_ACT_GetDmpDynamicText(HWND hwnd)
{
    memset((void*)CHAR_BUFFER, '\0', 128);
#ifndef ATSC_SYSTEM
    U16 u16TempID = Empty;
#endif
    switch(hwnd)
    {
		case HWND_DMP_FILE_PAGE_ITEM_TYPE:
		{
			switch(MApp_MPlayer_QueryCurrentMediaType())
			{
				case E_MPLAYER_TYPE_PHOTO:
					{
						u16TempID = en_str_MediaPlayerMainItemPhotoText; 
					}
					break;

				case E_MPLAYER_TYPE_MUSIC:
					{
						u16TempID = en_str_MediaPlayerMainItemMusicText;
					}
					break;

				case E_MPLAYER_TYPE_MOVIE:
					{
						u16TempID = en_str_MediaPlayerMainItemMovieText;
					}
					break;

				case E_MPLAYER_TYPE_TEXT:
					{
						u16TempID = en_str_MediaPlayerMainItemTextText;
					}
					break;

				default:
					break;
			}
			if (u16TempID != Empty) 
	            return MApp_ZUI_API_GetString(u16TempID);
			break;
		}	
    #ifndef ATSC_SYSTEM
    //===========================UART BAR
        case HWND_DMP_BAR_OPTION:
            switch(MApp_ZUI_ACT_GetCurrentUARTMode())
            {
                case E_UART_PIU_UART0:
                    u16TempID =(U16)en_str_HK;
                    break;
                case E_UART_VDEC:
                    u16TempID =(U16)en_str_VDEC;
                    break;
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)
                case E_UART_AEON_R2:
#else
                case E_UART_AEON:
#endif
                    u16TempID =(U16)en_str_AEON;
                    break;
                default:
                    u16TempID =(U16)en_str_None;
                    break;
            }
            return MApp_ZUI_API_GetString(u16TempID);
    #endif
    #if PLAYLIST_BGM
        case HWND_DMP_PLAYBACK_BGMINFO_INFO_ONOFF:
            {
                snprintf((char*)CHAR_BUFFER, 4, "BGM:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_TEXT:
            {
                if(m_bBGMOn == TRUE)
                    snprintf((char*)CHAR_BUFFER, 2, "ON");
                else
                    snprintf((char*)CHAR_BUFFER, 3, "OFF");

                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT:
            {
                snprintf((char*)CHAR_BUFFER, 16, "BGM Repeat mode:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_TEXT:
            {
                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                //------------------------Enter music mode------------------------

                enumMPlayerRepeatMode eRepeatMode = MApp_MPlayer_QueryRepeatMode();
                if(eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    snprintf((char*)CHAR_BUFFER, 3, "OFF");
                    //DMP_MusicInfoBarTable[MUSICINFO_REPEAT][INFOBAR_STR_IDX] = en_str_dmp;
                }
                else if(eRepeatMode == E_MPLAYER_REPEAT_1)
                {
                    snprintf((char*)CHAR_BUFFER, 10, "REPEAT ONE");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 10, "REPEAT ALL");
                }

                //snprintf((char*)CHAR_BUFFER, 3, "OFF");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);

                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM:
            {
                snprintf((char*)CHAR_BUFFER, 16, "BGM Random mode:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_RANDOM_TEXT:
            {
                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                //------------------------Enter music mode------------------------

                enumMPlayerRandomMode eRandomMode = MApp_MPlayer_QueryRandomMode();
                if(eRandomMode == E_MPLAYER_RANDOM_NONE)
                {
                    snprintf((char*)CHAR_BUFFER, 3, "OFF");
                }
                else if(eRandomMode == E_MPLAYER_RANDOM)
                {
                    snprintf((char*)CHAR_BUFFER, 2, "ON");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 3, "OFF");
                }

                //snprintf((char*)CHAR_BUFFER, 3, "OFF");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);

                return CHAR_BUFFER;
            }
            break;
        case HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT:
            {
                snprintf((char*)CHAR_BUFFER, 11, "BGM select:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT_TEXT:
            {
                snprintf((char*)CHAR_BUFFER, 2, "OK");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT:
            {
                snprintf((char*)CHAR_BUFFER, 9, "BGM next:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT_TEXT:
            {
                snprintf((char*)CHAR_BUFFER, 2, "OK");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV:
            {
                snprintf((char*)CHAR_BUFFER, 13, "BGM previous:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV_TEXT:
            {
                snprintf((char*)CHAR_BUFFER, 2, "OK");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;
    #endif
    //===========================INFOBAR
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM1_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM2_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM3_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM4_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM5_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM6_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM7_STRING:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM8_STRING:
        {
            U32 i;
            for( i = 0; i < DMP_INFOBAR_ICON_NUM; i++)
            {
                if( MApp_ZUI_API_IsSuccessor(_hwndListInfoBar[i], hwnd))
                {
                    break;
                }
            }
            U8 u8InfobarIdx = _u8InfoBarIdx+i;
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
            #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    //u8InfobarIdx = u8InfobarIdx %u8MovieInfoBarMax;
                    if(u8InfobarIdx >= u8MovieInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
                        }
                        return 0;
                    }
                    else
                    {
                        if (DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_REPEAT)
                        {
                            //DMP_DBG(printf("- Movie Repeat String\n"));

                            if  (MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_ALL)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "RepeatALL");
                            }
                            else if (MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_1)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "Repeat 1");
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 11, "RepeatNone");
                            }
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
#if RANDOM_PLAY
                        else if (DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MOVIEINFO_RANDOM)
                        {
                            DMP_DBG(printf("- Movie Random String\n"));
                            if  (MApp_MPlayer_QueryRandomMode() == E_MPLAYER_RANDOM)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "Random On");
                            }
                            else if (MApp_MPlayer_QueryRandomMode() == E_MPLAYER_RANDOM_NONE)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "Random Off");
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "Random Off");
                            }
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
#endif
                        else
                        {
                            //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                            return MApp_ZUI_API_GetString(DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_STR_IDX]);
                        };
                    }
                    break;
                #endif
                case E_MPLAYER_TYPE_PHOTO:
                    //u8InfobarIdx = u8InfobarIdx %u8PhotoInfoBarMax;
                    if(u8InfobarIdx >= u8PhotoInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
                        }
                        return 0;
                    }
                    else
                    {
                        if (DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_REPEAT)
                        {
                            DMP_DBG(printf("- Photo Repeat String\n"));
                            if  (MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_ALL)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "RepeatALL");
                            }
                            else if (MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_1)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "Repeat 1");
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 11, "RepeatNone");
                            }
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
                        #if RANDOM_PLAY
                        else if (DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_PHOTOINFO_RANDOM)
                        {
                            DMP_DBG(printf("- Photo Random String\n"));
                            if  (MApp_MPlayer_QueryRandomMode() == E_MPLAYER_RANDOM)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "Random On");
                            }
                            else if (MApp_MPlayer_QueryRandomMode() == E_MPLAYER_RANDOM_NONE)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "Random Off");
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "Random Off");
                            }
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
                        #endif
                        #if PLAYLIST_BGM
                        else if (DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_BGMINFO_PLAYLIST)
                        {
                            snprintf((char*)CHAR_BUFFER, 12, "BGM Playlist");
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
                        #endif
                        else
                        {
                            //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                            //MApp_ZUI_API_ShowWindow(MApp_ZUI_API_GetParent(hwnd), SW_SHOW);
                            return MApp_ZUI_API_GetString(DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_STR_IDX]);
                        }
                    }
                    break;
                case E_MPLAYER_TYPE_MUSIC:
                    //u8InfobarIdx = u8InfobarIdx %u8MusicInfoBarMax;
                    if(u8InfobarIdx >= u8MusicInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
                        }
                        return 0;
                    }
                    else
                    {
                       if (DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MUSICINFO_REPEAT)
                        {
                            DMP_DBG(printf("- Music Repeat String\n"));
                            if  (MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_ALL)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "RepeatALL");
                            }
                            else if (MApp_MPlayer_QueryRepeatMode() == E_MPLAYER_REPEAT_1)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "Repeat 1");
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 11, "RepeatNone");
                            }
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
#if RANDOM_PLAY
                        else if (DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_ACT_IDX] == EN_EXE_DMP_PLAYBACK_MUSICINFO_RANDOM)
                        {
                            DMP_DBG(printf("- MUSIC Random String\n"));
                            if  (MApp_MPlayer_QueryRandomMode() == E_MPLAYER_RANDOM)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "Random On");
                            }
                            else if (MApp_MPlayer_QueryRandomMode() == E_MPLAYER_RANDOM_NONE)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "Random Off");
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "Random Off");
                            }
                            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                            return CHAR_BUFFER;
                        }
#endif
                        else
                        {
                            //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                            return MApp_ZUI_API_GetString(DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_STR_IDX]);
                        }
                    }
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    //u8InfobarIdx = u8InfobarIdx %u8TextInfoBarMax;
                    if(u8InfobarIdx >=u8TextInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
                        }
                        return 0;
                    }
                    else
                    {
                        //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                        return MApp_ZUI_API_GetString(DMP_TextInfoBarTable[u8InfobarIdx][INFOBAR_STR_IDX]);
                    }
                    break;
                    #endif
                    default:
                        break;
            }
            break;
        }

        //================ [Media Select Page] ==================
        case HWND_DMP_MEDIA_TYPE_USB_STATUS_STRING:
        {
            enumMPlayerUSBDeviceStatus eUSBDeviceStatus;
            if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_1))
            {
                eUSBDeviceStatus = (enumMPlayerUSBDeviceStatus)msAPI_GetUsbDeviceStatus();
            }
        #if ENABLE_USB_2
            else if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_2))
            {
                eUSBDeviceStatus = (enumMPlayerUSBDeviceStatus)msAPI_GetUsbDeviceStatusPort2();
            }
        #endif
            else
            {
                eUSBDeviceStatus = E_MPLAYER_USB_NO_DEVICE;
            }
            switch (eUSBDeviceStatus)
            {
                case E_MPLAYER_USB_NO_DEVICE:
                    u16TempID =(U16)en_str_DMP_NoDevice;////>>wht1203018_1snprintf((char*)CHAR_BUFFER, 10, "No Device");
                    break;
                case E_MPLAYER_USB_USB11_DEVICE:
                    //snprintf((char*)CHAR_BUFFER, 8, "USB 1.1");
					if(u8UsbDeviceSel == DMP_USB_DISK2)//if(u8UsbDeviceSel == DMP_USB_DISK1)
					{
						if(MApp_MPlayer_QueryTotalDriveNum() >= 1)
						{
							u16TempID = (U16)en_str_DMP_USB11;  
						}
						else
						{
							u16TempID =(U16)en_str_DMP_NoDevice;
						}
					}
					else
					{
						u16TempID = (U16)en_str_DMP_SDCard;  
					}	
                    break;
                case E_MPLAYER_USB_USB20_DEVICE:
					if(u8UsbDeviceSel == DMP_USB_DISK2)//if(u8UsbDeviceSel == DMP_USB_DISK1)
					{
						if(MApp_MPlayer_QueryTotalDriveNum() >= 1)
						{
							u16TempID = (U16)en_str_DMP_USB20;  
						 }
						else
						{
						  u16TempID =(U16)en_str_DMP_NoDevice;
						}
					}
					else
					{
						 u16TempID = (U16)en_str_DMP_SDCard;  
					}	
                    break;
                case E_MPLAYER_USB_BAD_DEVICE:
                    u16TempID =(U16)en_str_DMP_BadDevice;//snprintf((char*)CHAR_BUFFER, 11, "Bad Device");
                    break;
                default:
                    break;
            }
            //FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            //>>wht141014_12
            if(u16TempID == en_str_DMP_NoDevice)
				bNoDevice = TRUE;
			else
				bNoDevice = FALSE;
			//<<wht141014_12
            if (u16TempID != Empty) 
	            return MApp_ZUI_API_GetString(u16TempID);	
        }
        break;
        //================ [Drive Select Page] ==================
        case HWND_DMP_DRIVE_ITEM1_STRING:
        case HWND_DMP_DRIVE_ITEM2_STRING:
        case HWND_DMP_DRIVE_ITEM3_STRING:
        case HWND_DMP_DRIVE_ITEM4_STRING:
        {
            U8 u8Item = 0;
            for(u8Item = 0; u8Item < DMP_DRIVE_NUM_PER_PAGE; u8Item++)
            {
                if(_hwndListDriveItemString[u8Item] == hwnd)
                {
                    break;
                }
            }
            if(u8Item == 0 && MApp_DMP_GetDrvPageIdx() <= 1)
            {
                return MApp_ZUI_API_GetString(en_str_Return);
            }
            else
            {
                U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item-1;
                if((u8Item < DMP_DRIVE_NUM_PER_PAGE) &&
                    u8Idx < MApp_MPlayer_QueryTotalDriveNum())
                {
                    CHAR_BUFFER[0] = 'C' + MApp_DMP_GetDriveFromMappingTable(u8Idx);
                    CHAR_BUFFER[1] = 0;
                    CHAR_BUFFER[2] = 0;
                    CHAR_BUFFER[3] = 0;
                }
            }
        }
        break;
        case HWND_DMP_DRIVE_INDEX_CUR_IDX:
        {
            snprintf((char*)CHAR_BUFFER, 3, "%u", MApp_DMP_GetDrvPageIdx());
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
        case HWND_DMP_DRIVE_INDEX_TOTAL_NUM:
        {
            snprintf((char*)CHAR_BUFFER, 3, "%u", MApp_MPlayer_QueryTotalDriveNum()/DMP_DRIVE_NUM_PER_PAGE+1);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
        //================ [File Select Page] ==================
        case HWND_DMP_FILE_PAGE_DIR_PATH_STRING:
		case HWND_DMP_PLAYBACK_MUSIC_DIR_PATH_STRING:
		case HWND_DMP_PLAYBACK_TEXT_DIR_PATH_STRING:
		{
            U16 au16TmpStr[128];
            U8 au8DrvId[16];//U8 au8DrvId[8];
			int iTmpIdCnt = 0;
			memset(au8DrvId, 0, 16);
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
			if(!bIsDriveSelected)
			{
				au8DrvId[0] = 0x5C;
				au8DrvId[1] = 0;
				au8DrvId[2] = 0x5C;
				au8DrvId[3] = 0;
				iTmpIdCnt = 4;
			} 
  	     	else
#endif
			if(DMP_USB_DISK2 != u8UsbDeviceSel)
			{
				au8DrvId[0] = 'C';
				au8DrvId[1] = 0;
				au8DrvId[2] = 'a';
				au8DrvId[3] = 0;
				au8DrvId[4] = 'r';
				au8DrvId[5] = 0;
				au8DrvId[6] = 'd';
				au8DrvId[7] = 0;
				au8DrvId[8] = 0x5C;	     
				au8DrvId[9] = 0;	     
				au8DrvId[10] = 0x5C;	     
				au8DrvId[11] = 0;	
				iTmpIdCnt = 12;
			}
			else
			{
				au8DrvId[0] = 'U';
				au8DrvId[1] = 0;
				au8DrvId[2] = 'S';
				au8DrvId[3] = 0;
				au8DrvId[4] = 'B';
				au8DrvId[5] = 0;
				if(hwnd == HWND_DMP_PLAYBACK_MUSIC_DIR_PATH_STRING
				   || hwnd == HWND_DMP_PLAYBACK_TEXT_DIR_PATH_STRING) 
	     		{
					if(1 == MApp_MPlayer_QueryTotalDriveNum())
					{
						au8DrvId[6] = 0x5C;
						au8DrvId[7] = 0;
						iTmpIdCnt = 8;
					}
					else
					{
						au8DrvId[6] = 0x2D;
						au8DrvId[7] = 0;	
						au8DrvId[8] = 'A' + MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx());
						au8DrvId[9] = 0;
						au8DrvId[10] = 0x5C;
						au8DrvId[11] = 0;
						iTmpIdCnt = 12;
					}
				}
				else
				{
					if(1 == MApp_MPlayer_QueryTotalDriveNum())
					{
						au8DrvId[6] = 0x5C;
						au8DrvId[7] = 0;
						au8DrvId[8] = 0x5C;
						au8DrvId[9] = 0;
						iTmpIdCnt = 10;
					}
					else
					{
						au8DrvId[6] = 0x2D;
						au8DrvId[7] = 0;	
						au8DrvId[8] = 'A' + MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx());
						au8DrvId[9] = 0;
						au8DrvId[10] = 0x5C;
						au8DrvId[11] = 0;
						au8DrvId[12] = 0x5C;
						au8DrvId[13] = 0;
						iTmpIdCnt = 14;
					}
				}
			}
#if 0  //old define 
			au8DrvId[0] = 'C' + MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx());
            au8DrvId[1] = 0;
            au8DrvId[2] = 0x3A;
            au8DrvId[3] = 0;
            au8DrvId[4] = 0x5C;
            au8DrvId[5] = 0;
            au8DrvId[6] = 0;
            au8DrvId[7] = 0;
#endif
            MApp_MPlayer_GetFullPath(au16TmpStr, 128);
            U16 tmp[16];//U16 tmp[8];
            memset(tmp, 0, 16);
            memcpy(tmp,au8DrvId,iTmpIdCnt);//memcpy(tmp,au8DrvId,8);
            MApp_ZUI_API_Strcat(CHAR_BUFFER, tmp);
			
			if(hwnd == HWND_DMP_PLAYBACK_MUSIC_DIR_PATH_STRING
				|| hwnd == HWND_DMP_PLAYBACK_TEXT_DIR_PATH_STRING) // add by gchen @ 20110510
			{
			#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(bIsDriveSelected)
			#endif
				{
					MApp_ZUI_API_Strcat(CHAR_BUFFER, au16TmpStr);
				}
				MPlayerFileInfo FileInfo;
				U16 au16MusicTmpStr[FILE_INFO_LONG_FILENAME_SIZE];
				U8  au8MusicSlash[8]; 
				U16 u16MusicTmp[8];
				memset(au8MusicSlash, 0, 8);
				memset(u16MusicTmp, 0, 8);
				memset(au16MusicTmpStr, 0, FILE_INFO_LONG_FILENAME_SIZE);
				if(MApp_MPlayer_QueryDirectoryDepth() <= 3)//wht120612_1 add
				{
					au8MusicSlash[0] = 0x5C;	     
					au8MusicSlash[1] = 0;	
				}
				U8 u8MusicCurIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();// - MApp_MPlayer_QueryDirectoryNumber() + 1;
				//printf("MApp_MPlayer_QueryCurrentPlayingFileIndex == %d  \n\n\n", MApp_MPlayer_QueryCurrentPlayingFileIndex()); //test by gchen @ 20110517

				MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u8MusicCurIdx,&FileInfo);  
				if(MApp_MPlayer_QueryDirectoryDepth() <= 3) //wht120612_1
				{
					memcpy(u16MusicTmp,au8MusicSlash,2); 
					MApp_ZUI_API_Strcat(CHAR_BUFFER, u16MusicTmp);
				}
				memcpy(au16MusicTmpStr,FileInfo.u8LongFileName, sizeof(FileInfo.u8LongFileName));
				#if 0  //wht120612_1
				MApp_ZUI_API_Strcat(CHAR_BUFFER, u16MusicTmp);
				//the first char has problem with use strcat method
				memset(u16MusicTmp, 0, 8);
				memcpy(u16MusicTmp,FileInfo.u8LongFileName, 1);
				MApp_ZUI_API_Strcat(CHAR_BUFFER, u16MusicTmp);
                 #endif
				MApp_ZUI_API_Strcat(CHAR_BUFFER, au16MusicTmpStr); //wht120519_1  remove (+1)
			}
			else
			{
			#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
				if(bIsDriveSelected)
			#endif
				{
					MApp_ZUI_API_Strcat(CHAR_BUFFER, au16TmpStr+1);
				}
			}
        }
		break;
#if PLAYLIST_BGM
        case HWND_DMP_BGM_FILE_PAGE_DIR_PATH_STRING:
#endif
        {
            U16 au16TmpStr[128];
            U8 au8DrvId[8];

            au8DrvId[0] = 'C' + MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx());
            au8DrvId[1] = 0;
            au8DrvId[2] = 0x3A;
            au8DrvId[3] = 0;
            au8DrvId[4] = 0x5C;
            au8DrvId[5] = 0;
            au8DrvId[6] = 0;
            au8DrvId[7] = 0;
            MApp_MPlayer_GetFullPath(au16TmpStr, 128);
            U16 tmp[8];
            memcpy(tmp,au8DrvId,8);
            MApp_ZUI_API_Strcat(CHAR_BUFFER, tmp);
            MApp_ZUI_API_Strcat(CHAR_BUFFER, au16TmpStr+1);
        }
        break;
        case HWND_DMP_FILE_PAGE_CUR_PAGE_IDX:
#if PLAYLIST_BGM
        case HWND_DMP_BGM_FILE_PAGE_CUR_PAGE_IDX:
#endif
        {
            U16 u16PageIdx = MApp_MPlayer_QueryCurrentPageIndex()+1;
            MApp_ZUI_API_GetU16String(u16PageIdx);
        }
        break;
        case HWND_DMP_FILE_PAGE_TOTAL_PAGE_NUM:
#if PLAYLIST_BGM
        case HWND_DMP_BGM_FILE_PAGE_TOTAL_PAGE_NUM:
#endif
        {
            U16 u16PageNum = (MApp_MPlayer_QueryTotalPages() > 0) ?
                                MApp_MPlayer_QueryTotalPages() : 1;
            MApp_ZUI_API_GetU16String(u16PageNum);
        }
        break;
        case HWND_DMP_FILE_PAGE_THUMB_ITEM1_STRING:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM2_STRING:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM3_STRING:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM4_STRING:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM5_STRING:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM6_STRING:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM7_STRING:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM8_STRING:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM9_STRING:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM10_STRING:
       // case HWND_DMP_FILE_PAGE_THUMB_ITEM11_STRING:  //wht120401_3
       // case HWND_DMP_FILE_PAGE_THUMB_ITEM12_STRING:
        {
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
		
			if(!bIsDriveSelected) 
			{
				printf(" Get dynamic text !bIsDriveSelected \n");
				U8 u8Item = 0;
				for(u8Item = 0; u8Item < DMP_DRIVE_NUM_PER_PAGE; u8Item++)
				{
					if(_hwndListFileString[u8Item] == hwnd)
					{
					    break;
					}
				}
			//U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item-1;
				U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item;
			    if((u8Item < DMP_DRIVE_NUM_PER_PAGE) &&
			        u8Idx < MApp_MPlayer_QueryTotalDriveNum())
			    {
					 if(DMP_USB_DISK2 == u8UsbDeviceSel)
					{
						CHAR_BUFFER[0] = 'C';
						CHAR_BUFFER[1] = 'a';
						CHAR_BUFFER[2] = 'r';
						CHAR_BUFFER[3] = 'd';
						CHAR_BUFFER[4] = 0;	   
					}
					else
					{
						CHAR_BUFFER[0] = 'U';
						CHAR_BUFFER[1] = 'S';
						CHAR_BUFFER[2] = 'B';

						if(1 == MApp_MPlayer_QueryTotalDriveNum())
						{
							CHAR_BUFFER[3] = 0;
						}
						else
						{
							CHAR_BUFFER[3] = 0x2D;
							CHAR_BUFFER[4] = 'A' + MApp_DMP_GetDriveFromMappingTable(u8Idx);
							CHAR_BUFFER[5] = 0;
						}
					}   // end if(DMP_USB_DISK1 == u8UsbDeviceSel)
			    }
				return CHAR_BUFFER;
			}
			else 
#endif
        {
            U16 u16ItemIdx = 0;
            MPlayerFileInfo fileInfo;
            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndListFileString[u16ItemIdx])
                {
                    break;
                }
            }
            //printf("[%d]\n", u16ItemIdx);
            if((u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE) &&
                (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
            {
                //printf("%d. EXT Name : %s\n", u16ItemIdx, fileInfo.u8LongFileName);
                if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                {
                    if(fileInfo.u8LongFileName[0] == 0x2e &&
                       fileInfo.u8LongFileName[1] == 0x00 &&
                       fileInfo.u8LongFileName[2] == 0x00 &&
                       fileInfo.u8LongFileName[3] == 0x00)
                    {
                        return MApp_ZUI_API_GetString(en_str_Up_Folder);
                    }
                    else
						if(fileInfo.u8LongFileName[0] == 0x2e &&
                           fileInfo.u8LongFileName[1] == 0x00 &&
                           fileInfo.u8LongFileName[2] == 0x2e &&
                           fileInfo.u8LongFileName[3] == 0x00 &&
                           fileInfo.u8LongFileName[4] == 0x00)
                    {
                        return MApp_ZUI_API_GetString(en_str_Up_Folder);
                    }
                }
                memcpy(CHAR_BUFFER, fileInfo.u8LongFileName, sizeof(fileInfo.u8LongFileName));
            }
        }
        }
        break;

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
        case HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS:
            {
                snprintf((char*)CHAR_BUFFER, 13, "Ready to Copy");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_FILE_PAGE_SUBMENU_COPY_STRING:
            {
                if (m_bCopyOn == TRUE)
                    snprintf((char*)CHAR_BUFFER, 5, "Paste");
                else
                    snprintf((char*)CHAR_BUFFER, 4, "Copy");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;
#endif

#if ENABLE_MPLAYER_SORT_EX
        case HWND_DMP_FILE_PAGE_SUBMENU_SORT_STRING:
            {
                snprintf((char*)CHAR_BUFFER, 4, "Sort");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_FILE_PAGE_SUBMENU_SORT_TYPE:
            {
                snprintf((char*)CHAR_BUFFER, 13, "Sorting Mode:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_FILE_PAGE_SUBMENU_SORT_TYPE_TEXT:
            {
                switch (MApp_MPlayer_QueryCurrentFileSortingMode())
                {
                    case E_MPLAYER_SORT_NONE:
                        snprintf((char*)CHAR_BUFFER, 4, "None");
                        break;
                    case E_MPLAYER_SORT_BY_NAME:
                        snprintf((char*)CHAR_BUFFER, 4, "Name");
                        break;
                    case E_MPLAYER_SORT_BY_TIME:
                        snprintf((char*)CHAR_BUFFER, 4, "Time");
                        break;
                    default:
                        break;
                }
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER:
            {
                snprintf((char*)CHAR_BUFFER, 14, "Sorting Order:");
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;

        case HWND_DMP_FILE_PAGE_SUBMENU_SORT_ORDER_TEXT:
            {
                switch (MApp_MPlayer_QueryCurrentFileSortingOrderMode())
                {
                    case E_MPLAYER_SORT_INCREMENT_ORDER:
                        snprintf((char*)CHAR_BUFFER, 8, "Increase");
                        break;
                    case E_MPLAYER_SORT_DECREASING_ORDER:
                        snprintf((char*)CHAR_BUFFER, 8, "Decrease");
                        break;
                    default:
                        break;
                }
                FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                return CHAR_BUFFER;
            }
            break;
#endif

#if PLAYLIST_BGM
        //================ [Drive Select Page] ==================
        case HWND_DMP_DRIVE_BGM_ITEM1_STRING:
        case HWND_DMP_DRIVE_BGM_ITEM2_STRING:
        case HWND_DMP_DRIVE_BGM_ITEM3_STRING:
        case HWND_DMP_DRIVE_BGM_ITEM4_STRING:
        {
            U8 u8Item = 0;
            for(u8Item = 0; u8Item < DMP_DRIVE_NUM_PER_PAGE; u8Item++)
            {
                if(_hwndBgmListDriveItemString[u8Item] == hwnd)
                {
                    break;
                }
            }
            if(u8Item == 0 && MApp_DMP_GetDrvPageIdx() <= 1)
            {
                return MApp_ZUI_API_GetString(en_str_Return);
            }
            else
            {
                U8 u8Idx = (MApp_DMP_GetDrvPageIdx()-1) * DMP_DRIVE_NUM_PER_PAGE + u8Item-1;
                if((u8Item < DMP_DRIVE_NUM_PER_PAGE) &&
                    u8Idx < MApp_MPlayer_QueryTotalDriveNum())
                {
                    CHAR_BUFFER[0] = 'C' + MApp_DMP_GetDriveFromMappingTable(u8Idx);
                    CHAR_BUFFER[1] = 0;
                    CHAR_BUFFER[2] = 0;
                    CHAR_BUFFER[3] = 0;
                }
            }
        }
        break;
        case HWND_DMP_DRIVE_BGM_INDEX_CUR_IDX:
        {
            snprintf((char*)CHAR_BUFFER, 3, "%u", MApp_DMP_GetDrvPageIdx());
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
        case HWND_DMP_DRIVE_BGM_INDEX_TOTAL_NUM:
        {
            snprintf((char*)CHAR_BUFFER, 3, "%u", MApp_MPlayer_QueryTotalDriveNum()/DMP_DRIVE_NUM_PER_PAGE+1);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11_STRING:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12_STRING:
        {
            U16 u16ItemIdx = 0;
            MPlayerFileInfo fileInfo;
            memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndBgmListFileString[u16ItemIdx])
                {
                    break;
                }
            }
            //printf("[%d]\n", u16ItemIdx);
            if((u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE) &&
                (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
            {
                //printf("%d. EXT Name : %s\n", u16ItemIdx, fileInfo.u8ExtFileName);
                if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                {
                    if(fileInfo.u8LongFileName[0] == 0x2e &&
                       fileInfo.u8LongFileName[1] == 0x00 &&
                       fileInfo.u8LongFileName[2] == 0x00 &&
                       fileInfo.u8LongFileName[3] == 0x00)
                    {
                        return MApp_ZUI_API_GetString(en_str_Up_Folder);
                    }
                    else if(fileInfo.u8LongFileName[0] == 0x2e &&
                           fileInfo.u8LongFileName[1] == 0x00 &&
                           fileInfo.u8LongFileName[2] == 0x2e &&
                           fileInfo.u8LongFileName[3] == 0x00 &&
                           fileInfo.u8LongFileName[4] == 0x00)
                    {
                        return MApp_ZUI_API_GetString(en_str_Up_Folder);
                    }
                }
                memcpy(CHAR_BUFFER, fileInfo.u8LongFileName, sizeof(fileInfo.u8LongFileName));
            }
        }
        break;
#endif
        /* case HWND_DMP_FILE_PAGE_PREVIEW_FILENAME_STRING:
        {
            U16 u16ItemIdx = 0;
            MPlayerFileInfo fileInfo;
            memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(MApp_ZUI_API_GetFocus() == _hwndListFileItem[u16ItemIdx])
                {
                    break;
                }
            }
            if (u16ItemIdx == NUM_OF_PHOTO_FILES_PER_PAGE)
            {
                //Focus on AlertWin
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(MApp_ZUI_API_GetFocusCheckpoint() == _hwndListFileItem[u16ItemIdx])
                    {
                        break;
                    }
                }
            }
            //printf("[%d] focus = %d\n", u16ItemIdx);
            if((u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE) &&
               (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
            {
                //printf("%d. EXT Name : %s\n", u16ItemIdx, fileInfo.u8ExtFileName);
                if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                {
                    if(fileInfo.u8LongFileName[0] == 0x2e &&
                       fileInfo.u8LongFileName[1] == 0x00 &&
                       fileInfo.u8LongFileName[2] == 0x00 &&
                       fileInfo.u8LongFileName[3] == 0x00)
                    {
                        return MApp_ZUI_API_GetString(en_str_Return);
                    }
                }
                memcpy(CHAR_BUFFER, fileInfo.u8LongFileName, sizeof(fileInfo.u8LongFileName));
            }
        }
        break;
		*/
		//>>wht1203017_8
		case HWND_DMP_PLAYBACK_MUSIC_CUR_FILE_IDX:
		//case HWND_DMP_PLAYBACK_PHOTO_FILE_INFO_STRING_CURRENT_IDX: //3
		//case HWND_DMP_PLAYBACK_MOVIE_FILE_INFO_CURRENT_IDX:
		{
			U16 u16PlaybackCurPlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex() - MApp_MPlayer_QueryDirectoryNumber();
            		MApp_ZUI_API_GetU16String(u16PlaybackCurPlayingIdx + 1);
			break;
		}

		case HWND_DMP_PLAYBACK_MUSIC_TOTAL_FILE_NUM:
		//case HWND_DMP_PLAYBACK_PHOTO_FILE_INFO_STRING_TOTAL_NUM: 
		//case HWND_DMP_PLAYBACK_MOVIE_FILE_INFO_TOTAL_NUM:
		{
			U16 u16PlaybackTotalNum = MApp_MPlayer_QueryTotalFileNum() - MApp_MPlayer_QueryDirectoryNumber();
            		MApp_ZUI_API_GetU16String(u16PlaybackTotalNum);
			break;
		}
//<<wht1203017_8
        case HWND_DMP_ALERT_STRING:
        {
            switch(_enDmpMsgType)
            {
                case DMP_MSG_TYPE_LOADING:
                    snprintf((char*)CHAR_BUFFER, 11, "Loading...");
                    break;
                case DMP_MSG_TYPE_UNSUPPORTED_FILE:
                #if ENABLE_DRM
                    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_FILE_FORMAT)==TRUE)
                    {
                        snprintf((char*)CHAR_BUFFER, 25, "DRM file can not preview");
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 17, "Unsupported File");
                    }
                #else
                    snprintf((char*)CHAR_BUFFER, 17, "Unsupported File");
                #endif
                    break;
                case DMP_MSG_TYPE_INVALID_OPERATION:
                    snprintf((char*)CHAR_BUFFER, 18, "Invalid Operation");
                    break;
                case DMP_MSG_TYPE_COPY_FILE_ERROR:
                    snprintf((char*)CHAR_BUFFER, 16, "Copy file failed");
                    break;
                case DMP_MSG_TYPE_DELETE_FILE_ERROR:
                    snprintf((char*)CHAR_BUFFER, 18, "Delete file failed");
                    break;
                case DMP_MSG_TYPE_NO_SELECT_FILE:
                    snprintf((char*)CHAR_BUFFER, 18, "Please select file");
                    break;
                case DMP_MSG_TYPE_NO_ENOUGH_SPACE:
                    snprintf((char*)CHAR_BUFFER, 15, "No enough space");
                    break;
                case DMP_MSG_TYPE_FORMATTING:
                    snprintf((char*)CHAR_BUFFER, 13, "Formatting...");
                    break;
                case DMP_MSG_TYPE_UNSUPPORTED_FORMAT:
                    snprintf((char*)CHAR_BUFFER, 18, "Unsupported Format");
                    break;
                case DMP_MSG_TYPE_ALL_FILES_UNSUPPORTED:
                    snprintf((char*)CHAR_BUFFER, 22, "All Files Unsupported");
                    break;
                case DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE:  //20100809EL
                    snprintf((char*)CHAR_BUFFER, 25, "Unsupported Audio Format");
                    break;
                 case DMP_MSG_TYPE_UNSUPPORTED_VIDEO_RESOLUTION:
                    snprintf((char*)CHAR_BUFFER, 25, "Video res. not supported");
                    break;
                case DMP_MSG_TYPE_UNSUPPORTED_VIDEO_FRAME_RATE:
                    snprintf((char*)CHAR_BUFFER, 25, "Video frame rate not supported");
                    break;
                case DMP_MSG_TYPE_NEED_TO_SELECT_DELETE_FILE:
                    snprintf((char*)CHAR_BUFFER, 28, "Please Select File to Delete");
                    break;
                case DMP_MSG_TYPE_NEED_TO_SELECT_COPY_FILE:
                    snprintf((char*)CHAR_BUFFER, 26, "Please Select File to Copy");
                    break;
				case DMP_MSG_TYPE_UNSUPPORTED_BUTTON: //add by gchen  @ 20110719
		  			u16TempID =(U16)en_strFunctionNotAvailable;
					break;
                case DMP_MSG_TYPE_PRESS_RED_BUTTON_PASTE:
                    snprintf((char*)CHAR_BUFFER, 27, "Please Cancel or Paste File");
                    break;
                default:
                    snprintf((char*)CHAR_BUFFER, 8, "Unknown");
                    break;
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

        case HWND_DMP_PROGRESS_MSG:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
            #if ENABLE_DELETE_SELECTED_FILES
                if (MApp_MPlayer_IsDeleting() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 21, "Deleting... (%u/%u)", _u16CopyDeleteFinishNum, _u16CopyDeleteSelectNum);
                }
            #endif
            #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                if (MApp_MPlayer_IsCopying() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 20, "Pasting... (%u/%u)", _u16CopyDeleteFinishNum, _u16CopyDeleteSelectNum);
                }
            #endif
            }
        #if 0
          #if (ENABLE_POWERON_MUSIC)
            else if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_PLAYING_STAGE)
            {
                snprintf((char*)CHAR_BUFFER, 12, "Recording...");
            }
          #endif
        #endif
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

        case HWND_DMP_PROGRESS_PERCENT:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
            #if ENABLE_DELETE_SELECTED_FILES
                if (MApp_MPlayer_IsDeleting() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 5, "%u%c", MApp_MPlayer_QueryDeleteFileStatus(), '%');
                }
            #endif
            #if ENABLE_COPY_SELECTED_FILES
                if (MApp_MPlayer_IsCopying() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 5, "%u%c", MApp_MPlayer_QueryPasteFileStatus(), '%');
                }
            #endif
            }
        #if 0
          #if (ENABLE_POWERON_MUSIC)
            else if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_PLAYING_STAGE)
            {
                U32 u32Percent = MApp_Music_GetRecordingTime()/(USER_MP3_CAPTURE_TIMEOUT/100);
                snprintf((char*)CHAR_BUFFER, 5, "%d%c", (U16)u32Percent, '%');
            }
          #endif
        #endif
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

        case HWND_DMP_PROGRESS_STOP:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
            #if ENABLE_DELETE_SELECTED_FILES
                if (MApp_MPlayer_IsDeleting() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 21, "Delete file (%u/%u)", _u16CopyDeleteFinishNum, _u16CopyDeleteSelectNum);
                }
            #endif
            #if (ENABLE_COPY_SELECTED_FILES == ENABLE)
                if (MApp_MPlayer_IsCopying() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 19, "Copy file (%u/%u)", _u16CopyDeleteFinishNum, _u16CopyDeleteSelectNum);
                }
            #endif
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
        case HWND_DMP_COPY_CONFIRM_TEXT:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                if (m_bCopyOn == FALSE)
                {
                    snprintf((char*)CHAR_BUFFER, 20, "Copy selected files?");
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

        case HWND_DMP_CANCEL_CONFIRM_TEXT:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                if (m_bCopyOn == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 18, "Cancel copy files?");
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
#endif

        case HWND_DMP_DELETE_CONFIRM_TEXT:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                snprintf((char*)CHAR_BUFFER, 25, "Press YES to delete files");
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

#if (ENABLE_COPY_SELECTED_FILES == ENABLE)
        case HWND_DMP_FORMAT_CONFIRM_TEXT:
        {
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                snprintf((char*)CHAR_BUFFER, 23, "Press YES to format USB");
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
#endif

#if ENABLE_DRM
#if ENABLE_RESUME_STOP
        case HWND_DMP_RESUME_STOP_STRING:
        {
            snprintf((char*)CHAR_BUFFER, 128, "If you stop playback now you will lose a view. Do you want to stop?");
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
#endif
#endif

        case HWND_DMP_PLAYBACK_PAGE_TIME_TOTAL:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
             #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                {
                    if (!MApp_MPlayer_IsMoviePlaying())
                    {
                        snprintf((char*)CHAR_BUFFER, 9, "00:00:00");
                    }
                    else
                    {
                        U32 totalTime;
                        U8 u8Hour, u8Min, u8Sec;

                        totalTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME);

                        if(totalTime != 0xFFFFFFFF
                            && totalTime != 0)
                        {
                            totalTime /= 1000;
                            totalTime = totalTime>0 ? totalTime:0;
                            u8Hour = (U8)(totalTime/3600);
                            u8Min = (U8)(totalTime/60-u8Hour*60);
                            u8Sec = (U8)(totalTime-u8Hour*3600-u8Min*60);
                            _u16MovieTotalTime = ((u8Hour*60)+u8Min)*60+u8Sec;
                            snprintf((char*)CHAR_BUFFER, 9, "%02d:%02d:%02d", u8Hour,u8Min,u8Sec);
                        }
                        else if(totalTime == 0)
                        {
                             snprintf((char*)CHAR_BUFFER, 9, "00:00:00");
                        }
                        else
                        {
                            snprintf((char*)CHAR_BUFFER, 9, "--:--:--");
                        }
                    }
                }
                break;
            #endif
                case E_MPLAYER_TYPE_MUSIC:
                {
                    if (!MApp_MPlayer_IsMusicPlaying())
                    {
                        snprintf((char*)CHAR_BUFFER, 9, "00:00:00");
                    }
                    else
                    {
                        U32 totalTime;
                        U16 u16Hour;
                        U8 u8Min, u8Sec;

                        totalTime = MApp_MPlayer_QueryMusicFilePlayTime();

                        if(totalTime != 0xFFFFFFFF
                            && totalTime != 0)
                        {

                            u16Hour = (U16)(totalTime/3600);
                            u8Min = (U8)(totalTime/60-u16Hour*60);
                            u8Sec = (U8)(totalTime-u16Hour*3600-u8Min*60);
                            if(u16Hour < 100)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "%02d:%02d:%02d", u16Hour,u8Min,u8Sec);
                            }
                            else if(u16Hour < 1000)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "%03d:%02d:%02d", u16Hour,u8Min,u8Sec);
                            }
                            else if(u16Hour < 10000)
                            {
                                snprintf((char*)CHAR_BUFFER, 11, "%04d:%02d:%02d", u16Hour,u8Min,u8Sec);
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "--:--:--");
                            }
                        }
                        else
                        {
                            snprintf((char*)CHAR_BUFFER, 9, "--:--:--");
                        }
                    }
                }
                break;
                default:
                    break;
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;

        case HWND_DMP_PLAYBACK_PAGE_TIME_CURRENT:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
            #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    if (!MApp_MPlayer_IsMoviePlaying())
                    {
                        snprintf((char*)CHAR_BUFFER, 9, "00:00:00");
                    }
                    else
                    {
                        U32 currentTime;
                        U8 u8Min, u8Sec;
                        S8 s8Hour = 0;

                        if(_enNotify == E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE
                            || _enNotify == E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE
                          #ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
                            || _enNotify == E_MPLAYER_NOTIFY_PLAY_NEXT_FILE
                          #endif
                            )
                        {
                            if ((_enPlayMode_AtNotify >= E_MPLAYER_MOVIE_FB_2X) &&
                                (_enPlayMode_AtNotify <= E_MPLAYER_MOVIE_FB_32X))
                            {
                                // If FB to beginning of file, still show current time, it should be 0.
                                currentTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME)/1000;
                            }
                            else
                            {
                                currentTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME)/1000;
                            }

                        }
                        else
                        {
                            currentTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME)/1000;
                        }

                        currentTime = currentTime>0 ? currentTime:0;
                        s8Hour = (currentTime/3600);
                        u8Min = (U8)(currentTime/60-s8Hour*60);
                        u8Sec = (U8)(currentTime-s8Hour*3600-u8Min*60);
                        _u16MovieCurrentTime = ((s8Hour*60)+u8Min)*60+u8Sec;
                        if(s8Hour >= 0 && s8Hour <= 48)
                        {
                            snprintf((char*)CHAR_BUFFER, 9, "%02d:%02d:%02d", s8Hour,u8Min,u8Sec);
                        }
                        else
                        {// If we get an invalid time, reset time info.
                            snprintf((char*)CHAR_BUFFER, 9, "00:00:00");
                        }
                    }
                    break;
           #endif
                    case E_MPLAYER_TYPE_MUSIC:
                    {
                        if (!MApp_MPlayer_IsMusicPlaying())
                        {
                            snprintf((char*)CHAR_BUFFER, 9, "00:00:00");
                        }
                        else
                        {
                            U32 currentTime;
                            U16 u16Hour;
                            U8 u8Min, u8Sec;
                            currentTime =_u32MusicCurrentTime ;

                            currentTime = currentTime>0 ? currentTime:0;
                            u16Hour = (currentTime/3600);
                            u8Min = (U8)(currentTime/60-u16Hour*60);
                            u8Sec = (U8)(currentTime-u16Hour*3600-u8Min*60);
                            if(u16Hour < 100)
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "%02d:%02d:%02d", u16Hour,u8Min,u8Sec);
                            }
                            else if(u16Hour < 1000)
                            {
                                snprintf((char*)CHAR_BUFFER, 10, "%03d:%02d:%02d", u16Hour,u8Min,u8Sec);
                            }
                            else if(u16Hour < 10000)
                            {
                                snprintf((char*)CHAR_BUFFER, 11, "%04d:%02d:%02d", u16Hour,u8Min,u8Sec);
                            }
                            else
                            {
                                snprintf((char*)CHAR_BUFFER, 9, "--:--:--");
                            }
                        }
                    }
                    break;
                    default:
                        break;
                }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
        }
        break;
        case HWND_DMP_PLAYBACK_STATUS_STRING:
        {
            DMP_DBG(printf("HWND_DMP_PLAYBACK_STATUS_STRING %u\n",_enDmpPlayStrType););
            U16 u16StringId = E_ZUI_STR_MAX;
            // TODO: need to contorl _enDmpPlayIconType!?
            switch(_enDmpPlayStrType)
            {
            #if (ENABLE_MPLAYER_MOVIE)
                case PLAY_MODE_ICON_CHANGE_AUDIOTRACK:
                {
                    U16 u16TrkID = MApp_MPlayer_QueryMovieCurAudioTrackIdx()+1;
                    snprintf((char*)CHAR_BUFFER, 17, "Audio Track %u", u16TrkID);
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                }
            #endif
#if (ENABLE_SUBTITLE_DMP)
                case PLAY_MODE_ICON_CHANGE_SUBTITLETRACK:
                {
                    if(_stDmpPlayVar.stMovieInfo.bSubtitleOff)
                    {
                        snprintf((char*)CHAR_BUFFER, 13, "Subtitle Off");
                    }
                    else
                    {
                        U16 u16TrkID = MApp_MPlayer_QueryMovieCurSubtitleTrackIdx()+1;
                        snprintf((char*)CHAR_BUFFER, 20, "Subtitle Track %u", u16TrkID);
                    }
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                }
#endif
			//>>wht120613_4
				case PLAY_MODE_ICON_SOUND_LL:
					 u16StringId =(U16)en_str_DMP_MovieInfoSoundCHLL;
					break;
				case PLAY_MODE_ICON_SOUND_LR:
					u16StringId =(U16)en_str_DMP_MovieInfoSoundCHLR;
					break;
				case PLAY_MODE_ICON_SOUND_RR:
					u16StringId =(U16)en_str_DMP_MovieInfoSoundCHRR;
					break;   
			//<<wht120613_4
                case PLAY_MODE_ICON_NEXT:
                    u16StringId = en_str_Next;
                    break;
                case PLAY_MODE_ICON_PREVIOUS:
                    u16StringId = en_str_Prev;
                    break;
                case PLAY_MODE_ICON_STOP:
                    u16StringId = en_str_Stop;
                    break;
                case PLAY_MODE_ICON_PLAY:
                    u16StringId = en_str_Play;
                    break;
                case PLAY_MODE_ICON_PAUSE:
                    u16StringId = en_str_Pause;
                    break;
                case PLAY_MODE_ICON_AB_REPEAT:
                    u16StringId = en_str_None;
                    break;
				//>>wht120514_1
				case PLAY_MODE_ICON_BGMUSIC_MODE:
			        if  (MApp_MPlayer_IsMusicPlaying())
			        {
			           // snprintf((char*)CHAR_BUFFER, 10, "Music On");
			           u16StringId =(U16)en_str_DMP_MusicOn;
			        }               
			        else
			        {
			            //snprintf((char*)CHAR_BUFFER, 11, "Music Off");
			            u16StringId =(U16)en_str_DMP_MusicOff;
			        }
			        //FS_ASCII2Unicode((U8*)CHAR_BUFFER);
			       // return CHAR_BUFFER;
			       	break;
				//<<wht120514_1	
				
                case PLAY_MODE_ICON_SETA:
                    //u16StringId = en_str_SET_A;
                    snprintf((char*)CHAR_BUFFER, 6, "A-set");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_AB_LOOP:
                    //u16StringId = en_str_DMP_AB_Loop;
                    snprintf((char*)CHAR_BUFFER,7, "AB-set");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_SD:;
                    snprintf((char*)CHAR_BUFFER, 5, "Step");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_FB_INVALID:
                case PLAY_MODE_ICON_FF_INVALID:
                    snprintf((char*)CHAR_BUFFER, 11, "NotSupport");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_SLIDESHOW_NORMAL:
                    snprintf((char*)CHAR_BUFFER, 6, "Normal");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_SLIDESHOW_RANDOM:
                    snprintf((char*)CHAR_BUFFER, 6, "Random");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
#if (ENABLE_PHOTO_TRANS_EFFECT_BLOCKS)
                case PLAY_MODE_ICON_SLIDESHOW_BLOCKS:
                    snprintf((char*)CHAR_BUFFER, 6, "Blocks");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_DIAGONAL_BLOCKS)
                case PLAY_MODE_ICON_SLIDESHOW_DIAGONALBLOCKS:
                    snprintf((char*)CHAR_BUFFER, 15, "Diagonal Blocks");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_WIPE)
                case PLAY_MODE_ICON_SLIDESHOW_WIPE:
                    snprintf((char*)CHAR_BUFFER, 4, "Wipe");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_SLIDE)
                case PLAY_MODE_ICON_SLIDESHOW_SLIDE:
                    snprintf((char*)CHAR_BUFFER, 5, "Slide");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
#endif
#if (ENABLE_PHOTO_TRANS_EFFECT_FADE)
                case PLAY_MODE_ICON_SLIDESHOW_FADE:
                    snprintf((char*)CHAR_BUFFER, 4, "Fade");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
#endif
                case PLAY_MODE_ICON_REPEAT_NONE:
                    snprintf((char*)CHAR_BUFFER, 6, "RepOff");  //text change by xzm 20180208
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_REPEAT_1:
                    snprintf((char*)CHAR_BUFFER, 6, "RepOne");	//text change by xzm 20180208
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                case PLAY_MODE_ICON_REPEAT_ALL:
                    snprintf((char*)CHAR_BUFFER, 6, "RepAll");	//text change by xzm 20180208
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                    return CHAR_BUFFER;
                    break;
                default:
                {
                    U8 u8Str[10] = {0};
                    U16 tmp[10];
                    switch(_enDmpPlayStrType)
                    {
                        case PLAY_MODE_ICON_ZOOM_1DIV4:
                            u16StringId = en_str_Zoom;
                            snprintf((char*)u8Str, 5, " 1/4");
                            break;
                        case PLAY_MODE_ICON_ZOOM_1DIV2:
                            u16StringId = en_str_Zoom;
                            snprintf((char*)u8Str, 5, " 1/2");
                            break;
                        case PLAY_MODE_ICON_ZOOM_1:
                            u16StringId = en_str_Zoom;
                            snprintf((char*)u8Str, 3, " 1");
                            break;
                        case PLAY_MODE_ICON_FF2X:
                            u16StringId = en_str_FF;
                            snprintf((char*)u8Str, 3, "2X");
                            break;
                        case PLAY_MODE_ICON_FB2X:
                            u16StringId = en_str_FB;
                            snprintf((char*)u8Str, 3, "2X");
                            break;
                        case PLAY_MODE_ICON_SF2X:
                            u16StringId = en_str_SF;
                            snprintf((char*)u8Str, 3, "2X");
                            break;
                        case PLAY_MODE_ICON_ZOOM_2:
                            u16StringId = en_str_Zoom;
                            snprintf((char*)u8Str, 3, " 2");
                            break;
                        case PLAY_MODE_ICON_FF4X:
                            u16StringId = en_str_FF;
                            snprintf((char*)u8Str, 3, "4X");
                            break;
                        case PLAY_MODE_ICON_FB4X:
                            u16StringId = en_str_FB;
                            snprintf((char*)u8Str, 3, "4X");
                            break;
                        case PLAY_MODE_ICON_SF4X:
                            u16StringId = en_str_SF;
                            snprintf((char*)u8Str, 3, "4X");
                            break;
                        case PLAY_MODE_ICON_ZOOM_4:
                            u16StringId = en_str_Zoom;
                            snprintf((char*)u8Str, 3, " 4");
                            break;
                        case PLAY_MODE_ICON_FF8X:
                            u16StringId = en_str_FF;
                            snprintf((char*)u8Str, 3, "8X");
                            break;
                        case PLAY_MODE_ICON_FB8X:
                            u16StringId = en_str_FB;
                            snprintf((char*)u8Str, 3, "8X");
                            break;
                        case PLAY_MODE_ICON_SF8X:
                            u16StringId = en_str_SF;
                            snprintf((char*)u8Str, 3, "8X");
                            break;
                        case PLAY_MODE_ICON_ZOOM_8:
                            u16StringId = en_str_Zoom;
                            snprintf((char*)u8Str, 3, " 8");
                            break;
                        case PLAY_MODE_ICON_FF16X:
                            u16StringId = en_str_FF;
                            snprintf((char*)u8Str, 4, "16X");
                            break;
                        case PLAY_MODE_ICON_FF32X:
                            u16StringId = en_str_FF;
                            snprintf((char*)u8Str, 4, "32X");
                            break;
                        case PLAY_MODE_ICON_FB16X:
                            u16StringId = en_str_FB;
                            snprintf((char*)u8Str, 4, "16X");
                            break;
                        case PLAY_MODE_ICON_FB32X:
                            u16StringId = en_str_FB;
                            snprintf((char*)u8Str, 4, "32X");
                            break;
                        case PLAY_MODE_ICON_SF16X:
                            u16StringId = en_str_SF;
                            snprintf((char*)u8Str, 4, "16X");
                            break;
                  #ifndef ATSC_SYSTEM
                        case PLAY_MODE_ICON_RATIO_Original:
                            u16StringId = en_str_Auto;  //auto
                            break;
                        case PLAY_MODE_ICON_RATIO_4X3:
                            u16StringId = en_str_4colon3;
                            break;
                        case PLAY_MODE_ICON_RATIO_16X9:
                            u16StringId = en_str_16colon9;
                            break;
                        case PLAY_MODE_ICON_RATION_ZOOM1:
                            u16StringId = en_str_Zoom1;
                            break;
                        case PLAY_MODE_ICON_RATION_ZOOM2:
                            u16StringId = en_str_Zoom2;
                            break;
                        case PLAY_MODE_ICON_RATION_JUSTSCAN:
                            u16StringId = en_str_Just_Scan;
                            break;
                        case PLAY_MODE_ICON_RATIO_Panorama:
                            u16StringId = en_str_Panorama;
                            break;
                  #endif
                        default:
                            break;
                    }
                    MApp_ZUI_API_GetString(u16StringId);
                    FS_ASCII2Unicode((U8*)u8Str);
                    memcpy(tmp,u8Str,10);
                    MApp_ZUI_API_Strcat(CHAR_BUFFER, tmp);
                    return CHAR_BUFFER;
                    break;
                }
            }
            //if (MApp_MPlayer_QueryCurrentMediaType()!= E_MPLAYER_TYPE_PHOTO) _enDmpPlayStrType = PLAY_MODE_ICON_MAX;
            return MApp_ZUI_API_GetString(u16StringId);
        }
        break;
//===========================MOVIEINFO====//

        case HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT1:
        {
            CHAR_BUFFER[0] = (_u8Hour / 10) + 0x30;
            CHAR_BUFFER[1] = 0;
            CHAR_BUFFER[2] = 0;
            CHAR_BUFFER[3] = 0;
        }
        break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_HOUR_DIGIT2:
        {
            CHAR_BUFFER[0] = (_u8Hour % 10) + 0x30;
            CHAR_BUFFER[1] = 0;
            CHAR_BUFFER[2] = 0;
            CHAR_BUFFER[3] = 0;
        }
        break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_MINUTE_DIGIT1:
        {
            CHAR_BUFFER[0] = (_u8Minute / 10) + 0x30;
            CHAR_BUFFER[1] = 0;
            CHAR_BUFFER[2] = 0;
            CHAR_BUFFER[3] = 0;
        }
        break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_MINUTE_DIGIT2:
        {
            CHAR_BUFFER[0] = (_u8Minute % 10) + 0x30;
            CHAR_BUFFER[1] = 0;
            CHAR_BUFFER[2] = 0;
            CHAR_BUFFER[3] = 0;
        }
        break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_SEC_DIGIT1:
        {
            CHAR_BUFFER[0] = (_u8Second / 10) + 0x30;
            CHAR_BUFFER[1] = 0;
            CHAR_BUFFER[2] = 0;
            CHAR_BUFFER[3] = 0;
        }
        break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_GOTOTIME_SEC_DIGIT2:
        {
            CHAR_BUFFER[0] = (_u8Second % 10) + 0x30;
            CHAR_BUFFER[1] = 0;
            CHAR_BUFFER[2] = 0;
            CHAR_BUFFER[3] = 0;
        }
        break;

    #if 0
        case HWND_DMP_MOVIE_INFO_AB_REPEAT_STRING:
            if(_enRepeatABStatus == REPEATAB_MODE_NONE)
            {
                snprintf((char*)CHAR_BUFFER, 6, "Set A");
            }
            else if(_enRepeatABStatus == REPEATAB_MODE_A)
            {
                snprintf((char*)CHAR_BUFFER, 6, "Set B");
            }
            else if(_enRepeatABStatus == REPEATAB_MODE_AB)
            {
                snprintf((char*)CHAR_BUFFER, 8, "AB None");
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
    #endif
    #if (ENABLE_MPLAYER_MOVIE)
        case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_FILENAME_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying())
                {
                    snprintf((char*)CHAR_BUFFER, 3, "--");
                    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
                }
                else
                {
                    MApp_MPlayer_QueryCurrentPlayingFileName((U8*)CHAR_BUFFER);
                }
            }
            //FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_WHX_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 3, "--");
                }
                else
                {
                    U32 w = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE);
                    U32 h = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);

                    snprintf((char*)CHAR_BUFFER, 20, "%ld x %ld", w, h);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    U16 u16TrkID, u16TotalTrk;
                    u16TotalTrk = MApp_MPlayer_QueryMovieAudioChannelNum();
                    u16TrkID = MApp_MPlayer_QueryMovieCurAudioTrackIdx()+1;
                    if(u16TotalTrk > 0)
                    {
                        snprintf((char*)CHAR_BUFFER, 11, "%u / %u", u16TrkID, u16TotalTrk);
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT:
            {
                #if (ENABLE_SUBTITLE_DMP)
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    U16 u16TotalSub = MApp_MPlayer_QueryMovieSubtitleNum();
                    U16 u16SubIdx = MApp_MPlayer_QueryMovieCurSubtitleTrackIdx();
                    enumMPlayerLanguage enSubLan = E_MPLAYER_LANGUAGE_UNDEFINED;

                    if(_stDmpPlayVar.stMovieInfo.bSubtitleOff)
                    {
                        snprintf((char*)CHAR_BUFFER, 4, "OFF");
                    }
                    else
                    {
                        if(u16TotalSub > 0)
                        {
                            enSubLan = MApp_MPlayer_QueryMovieSubtitleLanguageByTrackIndex(u16SubIdx);

                            switch(enSubLan)
                            {
                                case E_MPLAYER_LANGUAGE_CZECH:// 0
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Czech", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_DANISH:// 1
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Danish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_GERMAN:// 2
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.German", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_ENGLISH:// 3
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.English", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_SPANISH:// 4
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Spanish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_GREEK:// 5
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Greek", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_FRENCH:// 6
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.French", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_CROATIAN:// 7
                                    snprintf((char*)CHAR_BUFFER, 4+8, "%d.Croatian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_ITALIAN:// 8
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Italian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_HUNGARIAN:// 9
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Hungarian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_DUTCH:// 10
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Dutch", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_NORWEGIAN:// 11
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Norwegian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_POLISH:// 12
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Polish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_PORTUGUESE:// 13
                                    snprintf((char*)CHAR_BUFFER, 4+10, "%d.Portuguese", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_RUSSIAN:// 14
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Russian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_ROMANIAN:// 15
                                    snprintf((char*)CHAR_BUFFER, 4+8, "%d.Romanian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_SLOVENIAN:// 16
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Slovenian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_SERBIAN:// 17
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Serbian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_FINNISH:// 18
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Finnish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_SWEDISH:// 19
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Swedish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_BULGARIAN:// 20
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Bulgarian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_GAELIC:// 21
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Gaelic", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_WELSH:// 22
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Welsh", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_IRISH:// 23
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Irish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_ARABIC:// 24
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Arabic", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_CATALAN:// 25
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Catalan", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_CHINESE:// 26
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Chinese", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_KOREAN:// 27
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Korean", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_JAPAN:// 28
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Japan", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_TURKISH:// 29
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Turkish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_HEBREW:// 30
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Hebrew", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_GALLEGAN:// 31
                                    snprintf((char*)CHAR_BUFFER, 4+8, "%d.Gallegan", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_BASQUE:// 32
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Basque", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_LUXEMBOURGISH:// 33
                                    snprintf((char*)CHAR_BUFFER, 4+13, "%d.Luxembourgish", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_ICELANDIC:// 34
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Icelandic", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_LATVIAN:// 35
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Latvian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_ESTONIAN:// 36
                                    snprintf((char*)CHAR_BUFFER, 4+8, "%d.Estonian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_LITHUANIAN:// 37
                                    snprintf((char*)CHAR_BUFFER, 4+10, "%d.Lithuanian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_UKRAINIAN:// 38
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Ukrainian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_BELARUSIAN:// 39
                                    snprintf((char*)CHAR_BUFFER, 4+10, "%d.Belarusian", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_HINDI:// 40
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Hindi", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_KIRUNDI:// 41
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Kirundi", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_MAORI:// 42
                                    snprintf((char*)CHAR_BUFFER, 4+5, "%d.Maori", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_SLOVAK:// 43
                                    snprintf((char*)CHAR_BUFFER, 4+6, "%d.Slovak", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_VOLAPUK:// 44
                                    snprintf((char*)CHAR_BUFFER, 4+7, "%d.Volapuk", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_MANDARIN:// 45
                                    snprintf((char*)CHAR_BUFFER, 4+8, "%d.Mandarin", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_CANTONESE:// 46
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Cantonese", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_SAMI:// 47
                                    snprintf((char*)CHAR_BUFFER, 4+4, "%d.Sami", u16SubIdx+1);
                                break;
                                case E_MPLAYER_LANGUAGE_QAA:// 48
                                    snprintf((char*)CHAR_BUFFER, 4+3, "%d.Qaa", u16SubIdx+1);
                                break;
                                default:
                                    snprintf((char*)CHAR_BUFFER, 4+9, "%d.Undefined", u16SubIdx+1);
                                break;
                            }
                        }
                        else
                        {
                            snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                        }
                    }
                }
                #else
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 4, "OFF");
                }
                #endif //#if (ENABLE_SUBTITLE_DMP)

            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        /*case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_SYNC_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 1, "0");
                }
                else
                {
                    if ((_stDmpPlayVar.stMovieInfo.bSubtitleOff == FALSE) && (MApp_MPlayer_IsCurSubtitleExternal() == TRUE))
                    {
                        S32 s32SubtitleTimeShiftSec=0;
                      #if (ENABLE_SUBTITLE_DMP)
                        s32SubtitleTimeShiftSec = MApp_MPlayer_GetSubtitleTimeShift(); //ms
                      #endif
                        s32SubtitleTimeShiftSec = s32SubtitleTimeShiftSec/1000; //s
                        snprintf((char*)CHAR_BUFFER, 4, "%ld", s32SubtitleTimeShiftSec);
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 1, "0");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_CODEPAGE_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 3, "OFF");
                }
                else
                {
                    if ((_stDmpPlayVar.stMovieInfo.bSubtitleOff == FALSE) && (MApp_MPlayer_IsCurSubtitleExternal() == TRUE))
                    {
                        enumSubtitleCharsetType enSubtitleCharsetType = SUBTITLE_CHARSET_DEFAULT;

                        enSubtitleCharsetType = MApp_MPlayer_GetSubtitleCharsetType();

                        switch(enSubtitleCharsetType)
                        {
                            case SUBTITLE_CHARSET_GBK:
                                snprintf((char*)CHAR_BUFFER, 7, "Chinese");
                            break;
                            case SUBTITLE_CHARSET_CP874:
                                snprintf((char*)CHAR_BUFFER, 4, "Thai");
                            break;
                            case SUBTITLE_CHARSET_CP1250:
                                snprintf((char*)CHAR_BUFFER, 7, "Latin 2");
                            break;
                            case SUBTITLE_CHARSET_CP1251:
                                snprintf((char*)CHAR_BUFFER, 8, "Cyrillic");
                            break;
                            case SUBTITLE_CHARSET_CP1252:
                                snprintf((char*)CHAR_BUFFER, 7, "Latin 1");
                            break;
                            case SUBTITLE_CHARSET_CP1253:
                                snprintf((char*)CHAR_BUFFER, 5, "Greek");
                            break;
                            case SUBTITLE_CHARSET_CP1254:
                                snprintf((char*)CHAR_BUFFER, 7, "Turkish");
                            break;
                            case SUBTITLE_CHARSET_CP1255:
                                snprintf((char*)CHAR_BUFFER, 6, "Hebrew");
                            break;
                            case SUBTITLE_CHARSET_CP1256:
                                snprintf((char*)CHAR_BUFFER, 6, "Arabic");
                            break;
                            case SUBTITLE_CHARSET_CP1257:
                                snprintf((char*)CHAR_BUFFER, 7, "Latin 4");
                            break;
                            case SUBTITLE_CHARSET_CP1258:
                                snprintf((char*)CHAR_BUFFER, 10, "Vietnamese");
                            break;
                            case SUBTITLE_CHARSET_KOREAN:
                                snprintf((char*)CHAR_BUFFER, 6, "Korean");
                            break;
                            case SUBTITLE_CHARSET_ISO_8859_05:
                                snprintf((char*)CHAR_BUFFER, 13, "Cyrillic(ISO)");
                            break;
                            default:
                                snprintf((char*)CHAR_BUFFER, 7, "Latin 1");
                            break;
                         }
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 3, "OFF");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
			*/
        case HWND_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) !=E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    U16 u16TotalPgm = MApp_MPlayer_QueryMovieProgramNum();
                    U16 u16PgmIdx = MApp_MPlayer_QueryMovieCurProgramIdx();
                    if(u16TotalPgm > 0)
                    {
                        snprintf((char*)CHAR_BUFFER, 11, "%d / %d", u16PgmIdx+1, u16TotalPgm);
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;

    #if (ENABLE_DIVX_PLUS==1)
        case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETTITLE_TITLE_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying())
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                    if(u16TotalTitle>= 1)
                    {
                        snprintf((char*)CHAR_BUFFER, 11, "%d / %d", _u16DivxTitleIdx+1, u16TotalTitle);
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETEDTION_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying())
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                    U16 u16TotalEdition = MApp_MPlayer_QueryMovieEditionNum();
                    if((u16TotalTitle != 0) && (u16TotalEdition>= 1))
                    {
                        snprintf((char*)CHAR_BUFFER, 11, "%d / %d", _u16DivxEditionIdx+1, u16TotalEdition);
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETCHAPTER_TEXT:
            {
                if (!MApp_MPlayer_IsMoviePlaying() && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) != E_MOVIE_PREVIEW_RUNNING))
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                }
                else
                {
                    U16 u16TotalTitle = MApp_MPlayer_QueryMovieTitleNum();
                    U16 u16TotalEdition = MApp_MPlayer_QueryMovieEditionNum();
                    U16 u16TotalChp = MApp_MPlayer_QueryMovieChapterNum();
                    //U16 u16ChpIdx = MApp_MPlayer_QueryMovieCurChapterIdx();
                    if((u16TotalTitle != 0) && (u16TotalEdition!= 0) && (u16TotalChp>= 1))
                    {
                        snprintf((char*)CHAR_BUFFER, 11, "%d / %d", _u16DivxChpIdx+1, u16TotalChp);
                    }
                    else
                    {
                        snprintf((char*)CHAR_BUFFER, 7, "-- / 0");
                    }
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
         case HWND_DMP_PLAYBACK_MOVIEINFO_DIVX_SETAUTOCHAPTER_TEXT:
            {
                {
                    snprintf((char*)CHAR_BUFFER, 8, "%d / 9", _u8DivxAutoChpIdx);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        #endif
    #endif  // divx
// =====================DMP_PLAYBACK_PLAYLIST_GROUP!?=================
        case HWND_DMP_PLAYBACK_PLAYLIST_PAGE_TOTAL_NUM:
            snprintf((char*)CHAR_BUFFER, 4, "%d",u8CurrentPlaylistTotalPage);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_PLAYLIST_PAGE_IDX_NUM:
            snprintf((char*)CHAR_BUFFER, 4, "%d",u8CurrentPlaylistPageIdx+1);
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM1_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM2_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM3_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM4_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM5_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM6_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM7_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM8_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM9_STRING:
        case HWND_DMP_PLAYBACK_PLAYLIST_ITEM10_STRING:
        {
            U32 i;
            for( i = 0 ; i < UI_DMP_PLAYLIST_NUMBER ; i++)
            {
                if( MApp_ZUI_API_IsSuccessor(_hwndListPlaylistItem[i], hwnd))
                {
                    break;
                }
            }
            // i from 0 to 9
            U16 u16FileIdx = (u8CurrentPlaylistPageIdx*UI_DMP_PLAYLIST_NUMBER) + i;
            // TODO: need to check there's no selected files?
            enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
#if PLAYLIST_BGM
            if (bIsBGMPlaylist == TRUE)
            {
                enumMPlayerMediaType ePreMediaType = E_MPLAYER_TYPE_INVALID;
                ePreMediaType = MApp_MPlayer_QueryCurrentMediaType();
                MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_MUSIC, FALSE);
                eMediaType = E_MPLAYER_TYPE_MUSIC;
                //------------------------Enter music mode------------------------

                if(MApp_MPlayer_QueryPlayListFileNum(eMediaType) == 0)
                {
                    // there is no selected files ,so need to shift the idx by how many
                    // directories
                    MPlayerFileInfo FileInfo;
                    for( i = 0; i < MApp_MPlayer_QueryTotalMusicFileNum(); i++)
                    {
                        _MApp_MPlayer_GetMusicFileInfo(i,&FileInfo);
                        if(FileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                        {
                            u16FileIdx++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    _MApp_MPlayer_GetMusicFileInfo(u16FileIdx,&FileInfo);
                    memcpy(CHAR_BUFFER,FileInfo.u8LongFileName,FILE_INFO_LONG_FILENAME_SIZE);
                }
                else
                {
                    MApp_MPlayer_QueryLongFilenameByPlayingIdx(u16FileIdx, (U8 *)CHAR_BUFFER,0);
                }

                //------------------------Exit music mode------------------------
                MApp_MPlayer_SetCurrentMediaType(ePreMediaType, FALSE);
            }
            else
#endif
            {
                if(MApp_MPlayer_QueryPlayListFileNum(eMediaType) == 0)
                {
                    // there is no selected files ,so need to shift the idx by how many
                    // directories
                    MPlayerFileInfo FileInfo;
                    memset(&FileInfo,0,sizeof(MPlayerFileInfo));
                    for( i = 0; i < MApp_MPlayer_QueryTotalFileNum(); i++)
                    {
                        MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,i,&FileInfo);
                        if(FileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                        {
                            u16FileIdx++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,u16FileIdx,&FileInfo);
                    memcpy(CHAR_BUFFER,FileInfo.u8LongFileName,FILE_INFO_LONG_FILENAME_SIZE);
                }
                else
                {
                    MApp_MPlayer_QueryLongFilenameByPlayingIdx(u16FileIdx, (U8 *)CHAR_BUFFER,0);
                }
            }
        }
            break;


//===========================MUSICINFO====//

/*        case HWND_DMP_MUSIC_INFO_CAPTURE_STRING:
            {
                if(MApp_MPlayer_IsMusicRecording() == FALSE)
                {
                    snprintf((char*)CHAR_BUFFER, 8, "Capture");
                }
                else if (MApp_MPlayer_IsMusicRecording() == TRUE)
                {
                    snprintf((char*)CHAR_BUFFER, 13, "Stop Capture");
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
*/
        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_FILENAME_TEXT:
            {
                MPlayerFileInfo stFileInfo;
                memset(&stFileInfo, 0, sizeof(MPlayerFileInfo));

                if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
                    (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
                {
                    U8 u8Len = 0;
                    MApp_MPlayer_QueryLongFilenameByPlayingIdx(MApp_MPlayer_QueryCurrentPlayingList(), (U8*)CHAR_BUFFER, u8Len);
                }
                else if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                        MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                {
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, MApp_MPlayer_QueryCurrentPlayingFileIndex(), &stFileInfo);
                    memcpy((void*)CHAR_BUFFER, (void*)stFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
                }
            }
            break;

        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_ALBUM_TEXT:
            {
                U8 *pu8Data;
                U8 u8Length;
                pu8Data = MApp_MPlayer_QueryMusicInfo(MP3_INFO_ALBUM,&u8Length);
                //memset((U8 *)CHAR_BUFFER,0,u8Length*2);

                if(pu8Data[0]==0x00)
                {
                    // TODO: fix me!!
                    _MApp_DMP_GB2Unicode(pu8Data+1, (U8 *)CHAR_BUFFER, u8Length-1); // [u8Length*2-2] = 0 , [u8Length*2-1]=0  String end
                }
                else if(pu8Data[0]==0x03)
                {
                    msAPI_OCP_MappinUTF8ToUCS2(pu8Data+1, CHAR_BUFFER, u8Length-1, u8Length-1);
                }
                else //if(pu8Data[0]==0x01)
                {
                    memcpy(CHAR_BUFFER,pu8Data+1,u8Length-1);  // [u8Length-2] = 0 , [u8Length-1]=0  String end
                }
            }
            break;
        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_TITLE_TEXT:
            {
                U8 *pu8Data;
                U8 u8Length = 0;
                pu8Data=MApp_MPlayer_QueryMusicInfo(MP3_INFO_TITLE,&u8Length);

                if(pu8Data == NULL || u8Length == 0)
                {
                    DMP_DBG(printf("Query music title information failed.\n");)
                    //Clear CHAR_BUFFER.
                    memset((U8 *)CHAR_BUFFER, 0, STRING_BUFFER_LENGTH*2);
                }
                else
                {
                    memset((U8 *)CHAR_BUFFER,0,u8Length*2);

                    if(pu8Data[0]==0x00)
                    {
                        // TODO: fixme
                        _MApp_DMP_GB2Unicode(pu8Data+1, (U8 *)CHAR_BUFFER, u8Length-1); // [u8Length*2-2] = 0 , [u8Length*2-1]=0  String end
                    }
                    else if(pu8Data[0]==0x03)
                    {
                        msAPI_OCP_MappinUTF8ToUCS2(pu8Data+1, CHAR_BUFFER, u8Length-1, u8Length-1);
                    }
                    else //if(pu8Data[0]==0x01)
                    {
                        memcpy(CHAR_BUFFER,pu8Data+1,u8Length-1);  // [u8Length-2] = 0 , [u8Length-1]=0  String end
                    }
                }
            }
            break;
        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_SAMPLING_TEXT:
            {
                U8 *pu8Data;
                U8 u8Length = 0;
                pu8Data = MApp_MPlayer_QueryMusicInfo(MP3_INFO_SAMPLINGRATE,&u8Length);

                if(pu8Data == NULL)
                {
                    DMP_DBG(printf("Query music sampling rate information failed.\n");)
                    //Clear CHAR_BUFFER.
                    memset((U8 *)CHAR_BUFFER, 0, STRING_BUFFER_LENGTH*2);
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 6, "%s", pu8Data);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_BITRATE_TEXT:
            {
                U8 *pu8Data;
                U8 u8Length = 0;
                pu8Data = MApp_MPlayer_QueryMusicInfo(MP3_INFO_BITRATE,&u8Length);

                if(pu8Data == NULL)
                {
                    DMP_DBG(printf("Query music bit rate information failed.\n");)
                    //Clear CHAR_BUFFER.
                    memset((U8 *)CHAR_BUFFER, 0, STRING_BUFFER_LENGTH*2);
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 5, "%s", pu8Data);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;

        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_ARTIST_TEXT:
            {
                U8 *pu8Data;
                U8 u8Length = 0;
                pu8Data=MApp_MPlayer_QueryMusicInfo(MP3_INFO_ARTIST,&u8Length);

                if(pu8Data == NULL || u8Length == 0)
                {
                    DMP_DBG(printf("Query music artist information failed.\n");)
                    //Clear CHAR_BUFFER.
                    memset((U8 *)CHAR_BUFFER, 0, STRING_BUFFER_LENGTH*2);
                }
                else
                {
                    memset((U8 *)CHAR_BUFFER,0,u8Length*2);

                    if(pu8Data[0]==0x00)
                    {
                        // TODO: fix me
                        _MApp_DMP_GB2Unicode(pu8Data+1, (U8 *)CHAR_BUFFER, u8Length-1); // [u8Length*2-2] = 0 , [u8Length*2-1]=0  String end
                    }
                    else if(pu8Data[0]==0x03)
                    {
                        msAPI_OCP_MappinUTF8ToUCS2(pu8Data+1, CHAR_BUFFER, u8Length-1, u8Length-1);
                    }
                    else //if(pu8Data[0]==0x01)
                    {
                        memcpy(CHAR_BUFFER,pu8Data+1,u8Length-1);  // [u8Length-2] = 0 , [u8Length-1]=0  String end
                    }
                }
            }
            break;

        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_YEAR_TEXT:
            {
                U8 *pu8Data;
                U8 u8Length;
                pu8Data=MApp_MPlayer_QueryMusicInfo(MP3_INFO_YEAR,&u8Length);
                memset((U8 *)CHAR_BUFFER,0,u8Length*2);
                if(pu8Data != NULL)
                {
                    if(pu8Data[0]==0x00)
                    {
                        // TODO: fix me
                        _MApp_DMP_GB2Unicode(pu8Data+1, (U8 *)CHAR_BUFFER, u8Length-1); // [u8Length*2-2] = 0 , [u8Length*2-1]=0  String end
                    }
                    else if(pu8Data[0]==0x03)
                    {
                        msAPI_OCP_MappinUTF8ToUCS2(pu8Data+1, CHAR_BUFFER, u8Length-1, u8Length-1);
                    }
                    else //if(pu8Data[0]==0x01)
                    {
                        memcpy(CHAR_BUFFER,pu8Data+1,u8Length-1);  // [u8Length-2] = 0 , [u8Length-1]=0  String end
                    }
                }
            }
            break;
//=======================playback_photoinfo==================
// TODO: there is still some useful info in MPlayerPhotoInfo... fix me
        case HWND_DMP_PLAYBACK_PHOTOINFO_INFO_FILENAME_TEXT:

            {
                 MApp_MPlayer_QueryCurrentPlayingFileName((U8*)CHAR_BUFFER);
            }
            //attention!! MApp_MPlayer_QueryCurrentPlayingFileName return unicode
            //FS_ASCII2Unicode((U8*)CHAR_BUFFER);

            break;
        case HWND_DMP_PLAYBACK_PHOTOINFO_INFO_WXH_TEXT:
            {
                MPlayerPhotoInfo stPhotoInfo;
                memset(&stPhotoInfo,0,sizeof(MPlayerPhotoInfo));

                MApp_MPlayer_QueryPhotoInfo(&stPhotoInfo);

                if(stPhotoInfo.u16Width == 0 && stPhotoInfo.u16Height == 0)
                {
                    snprintf((char*)CHAR_BUFFER, 7, "-- X --");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER,14, "%d X %d", stPhotoInfo.u16Width, stPhotoInfo.u16Height);
                }

            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_PHOTOINFO_INFO_DATE_TEXT:
		case HWND_DMP_PLAYBACK_TEXTINFO_INFO_DATE_TEXT:      //wht1203017_9
            {
                MPlayerPhotoInfo stPhotoInfo;
                MPlayerFileInfo stFileInfo;
                U16 u16ItemIdx;
                U16 u16PageIdx = MApp_MPlayer_QueryCurrentPageIndex();

                memset(&stPhotoInfo, 0x00, sizeof(MPlayerPhotoInfo));
                memset(&stFileInfo, 0x00, sizeof(MPlayerFileInfo));

                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(MApp_ZUI_API_IsSuccessor(MApp_ZUI_API_GetFocus(), _hwndListFileString[u16ItemIdx]) )
                    {
                        break;
                    }
                }
                if (u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    //preview
                    u16ItemIdx += u16PageIdx * NUM_OF_PHOTO_FILES_PER_PAGE;
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16ItemIdx, &stFileInfo);
                }
                else  if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
                    (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
                {
                    MApp_MPlayer_GetPlayListFileInfo(MApp_MPlayer_QueryCurrentPlayingList(),&stFileInfo);
                }
               else if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                    MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                {
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, MApp_MPlayer_QueryCurrentPlayingFileIndex(), &stFileInfo);
                }
    // printf(" FileBrowser u16Year : %d\n",  stFileInfo.u16Year);
     //printf(" FileBrowser u8Month : %d\n",    stFileInfo.u8Month);
    // printf(" FileBrowser u8Day : %d\n",    stFileInfo.u8Day);
    // printf(" FileBrowser u8Hour : %d\n",    stFileInfo.u8Hour);
    // printf(" FileBrowser u8Minute : %d\n",    stFileInfo.u8Minute);
    // printf(" FileBrowser u8Second : %d\n",    stFileInfo.u8Second);
                MApp_MPlayer_QueryPhotoInfo(&stPhotoInfo);
                if (stPhotoInfo.bHasDateTime == FALSE)
                {
                    snprintf((char*)CHAR_BUFFER, 15, "%04lu / %02lu / %02lu", stFileInfo.u16Year, stFileInfo.u8Month, stFileInfo.u8Day);
                   // snprintf((char*)CHAR_BUFFER, 15, "---- / -- / --");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 15, "%04lu / %02lu / %02lu", stPhotoInfo.u32Year, stPhotoInfo.u32Month, stPhotoInfo.u32Day);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_PHOTOINFO_INFO_TIME_TEXT:
		case HWND_DMP_PLAYBACK_TEXTINFO_INFO_TIME_TEXT:	//wht1203017_9
            {
                MPlayerPhotoInfo stPhotoInfo;
                MPlayerFileInfo stFileInfo;
                U16 u16ItemIdx;
                U16 u16PageIdx = MApp_MPlayer_QueryCurrentPageIndex();

                memset((void *)&stFileInfo, 0, sizeof(MPlayerFileInfo));
                memset((void *)&stPhotoInfo, 0, sizeof(MPlayerPhotoInfo));
                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(MApp_ZUI_API_IsSuccessor(MApp_ZUI_API_GetFocus(), _hwndListFileString[u16ItemIdx]) )
                    {
                        break;
                    }
                }
                if (u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    //preview
                    u16ItemIdx += u16PageIdx * NUM_OF_PHOTO_FILES_PER_PAGE;
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16ItemIdx, &stFileInfo);
                }
                else if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
                    (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
                {
                    MApp_MPlayer_GetPlayListFileInfo(MApp_MPlayer_QueryCurrentPlayingList(),&stFileInfo);
                }
               else if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                    MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                {
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, MApp_MPlayer_QueryCurrentPlayingFileIndex(), &stFileInfo);
                }
                MApp_MPlayer_QueryPhotoInfo(&stPhotoInfo);
                if (stPhotoInfo.bHasDateTime == FALSE)
                {
                    snprintf((char*)CHAR_BUFFER, 13, "%02lu : %02lu : %02lu", stFileInfo.u8Hour, stFileInfo.u8Minute, stFileInfo.u8Second);
                   // snprintf((char*)CHAR_BUFFER, 13, "-- : -- : --");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 13, "%02lu : %02lu : %02lu", stPhotoInfo.u32Hour, stPhotoInfo.u32Minute, stPhotoInfo.u32Second);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_MUSICINFO_INFO_SIZE_TEXT:
        case HWND_DMP_PLAYBACK_PHOTOINFO_INFO_SIZE_TEXT:
/*
            {
                MPlayerPhotoInfo stPhotoInfo;
                MApp_MPlayer_QueryPhotoInfo(&stPhotoInfo);
                if(stPhotoInfo.u32FileSize == 0)
                {
                    snprintf((char*)CHAR_BUFFER, 9, "-- KBytes");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 12, "%lu KBytes", (stPhotoInfo.u32FileSize+1023)/1024);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
*/
            return MApp_ZUI_ACT_GetDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_SIZE_TEXT);
            break;
// =======================playback textinfo====================//
#if (ENABLE_MPLAYER_TEXT)

        case HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW_PAGE_TOTALPAGE:
            {
                U32 page = MApp_TEXT_GetTotalPage();
                snprintf((char*)CHAR_BUFFER, 6, "%lu",page+1);
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW_PAGE_CURRENT:
            {
                U32 page = MApp_TEXT_GetPageIndex();
                snprintf((char*)CHAR_BUFFER, 6, "%lu",page+1);
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;

        case HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW_TEXT:
            return (LPTSTR)MApp_TEXT_GetCurrentLineText(FALSE);

        /*case HWND_DMP_FILE_PAGE_PREVIEW_TEXT:
            return (LPTSTR)MApp_TEXT_GetCurrentLineText(TRUE);
            break; */
			
        case HWND_DMP_PLAYBACK_TEXTINFO_INFO_SIZE_TEXT:
            {
                MPlayerFileInfo stFileInfo;
                memset(&stFileInfo,0,sizeof(MPlayerFileInfo));

                U64 u64FileSize;
                U16 u16ItemIdx;
                U16 u16PageIdx = MApp_MPlayer_QueryCurrentPageIndex();

                for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
                {
                    if(MApp_ZUI_API_IsSuccessor(MApp_ZUI_API_GetFocus(), _hwndListFileString[u16ItemIdx]) )
                    {
                        break;
                    }
                }
                if (u16ItemIdx < NUM_OF_PHOTO_FILES_PER_PAGE)
                {
                    //preview
                    u16ItemIdx += u16PageIdx * NUM_OF_PHOTO_FILES_PER_PAGE;
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16ItemIdx, &stFileInfo);
                }
                else if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
                    (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
                {
                    MApp_MPlayer_GetPlayListFileInfo(MApp_MPlayer_QueryCurrentPlayingList(),&stFileInfo);
                }
                else if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                        MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                {
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, MApp_MPlayer_QueryCurrentPlayingFileIndex(), &stFileInfo);
                    //memcpy((void*)CHAR_BUFFER, (void*)stFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
                }

                //printf(" FileSize.hi[%lu]\n", stFileInfo.u64FileSize.Hi);
                //printf(" FileSize.lo[%lu]\n", stFileInfo.u64FileSize.Lo);
                u64FileSize=(unsigned long long)stFileInfo.u64FileSize.Hi<<32|stFileInfo.u64FileSize.Lo;
                //printf(" FileSize[%llu]\n", u64FileSize);
                if((stFileInfo.u64FileSize.Lo== 0)&&(stFileInfo.u64FileSize.Hi== 0))
                {
                    snprintf((char*)CHAR_BUFFER, 9, "-- KBytes");
                }
                else
                {
                    snprintf((char*)CHAR_BUFFER, 20, "%llu KBytes", (u64FileSize+1023)/1024);
                }
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;

        case HWND_DMP_PLAYBACK_TEXTINFO_INFO_FILENAME_TEXT:
            {
                MPlayerFileInfo stFileInfo;
                memset(&stFileInfo,0,sizeof(MPlayerFileInfo));

                if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
                    (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
                {
                    U8 u8Len = 0;
                    MApp_MPlayer_QueryLongFilenameByPlayingIdx(MApp_MPlayer_QueryCurrentPlayingList(), (U8*)CHAR_BUFFER, u8Len);
                }
                else if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT ||
                        MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY)
                {
                    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, MApp_MPlayer_QueryCurrentPlayingFileIndex(), &stFileInfo);
                    memcpy((void*)CHAR_BUFFER, (void*)stFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
                }
            }
            break;
#endif
////=================== MISC==================================
        case HWND_DMP_VOLUME_CONFIG_TEXT:
        #if(ENABLE_CEC)
            if( MApp_CEC_ARC_Is_ExtAudioDeviceConnected() )
          /*#if(CEC_VERSION_USING == CEC_NEW_VERSION)
            if (msAPI_CEC_IsAudioSystemKeyValid()== TRUE)
          #else
            if (msAPI_CEC_ARC_Is_Connect() == TRUE)
          #endif */
            {
                return MApp_ZUI_API_GetU16String(msAPI_CEC_ARC_GetARCAudioVolume()/5); // anvi22
            }
            else
        #endif
            {
                return MApp_ZUI_API_GetU16String(stGenSetting.g_SoundSetting.Volume/5);
            }

		case HWND_DMP_KEYSTONE_CONFIG_TEXT:    //xzm 20171228 for keystone text
			return  MApp_ZUI_API_GetS16SignString(stGenSetting.g_SysSetting.KeyStoneValue);
        case HWND_DMP_PLAYBACK_CONFIRM_TEXT:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_PHOTO:
                    snprintf((char*)CHAR_BUFFER, 14, "Save as logo?");
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    snprintf((char*)CHAR_BUFFER, 14, "Save as file?");
                    break;
                    #endif
                case E_MPLAYER_TYPE_MUSIC:
                    snprintf((char*)CHAR_BUFFER, 24, "Save as power on music?");
                    break;
                default:
                    break;
            }
            FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        }
        case HWND_DMP_PLAYBACK_LYRIC_TEXT:
        {
            memcpy((char*)CHAR_BUFFER,_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf,DMP_STRING_BUF_SIZE);
        }
        //    FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
        case HWND_DMP_PLAYBACK_SUBTITLE_TEXT:
        {
            memcpy((char*)CHAR_BUFFER,_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf,DMP_STRING_BUF_SIZE);
        }
        //FS_ASCII2Unicode((U8*)CHAR_BUFFER);
            break;
// =================== Preview Info ===================
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO1:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Albumcolon);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_API_GetString(en_str_Resolutioncolon);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_API_GetString(en_str_Resolutioncolon);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    return MApp_ZUI_API_GetString(en_str_Sizecolon);
                    break;
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT1:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MUSICINFO_INFO_ALBUM_TEXT);
                    break;
                     #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_WHX_TEXT);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_WXH_TEXT);
                    break;
                     #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_SIZE_TEXT);
                    break;
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO2:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Titlecolon);
                    break;
                     #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_API_GetString(en_str_AudioTrackcolon);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_API_GetString(en_str_Sizecolon);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT2:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MUSICINFO_INFO_TITLE_TEXT);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_AUDIOTRACK_TEXT);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_SIZE_TEXT);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
					 return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_DATE_TEXT);//wht1203017_9 add
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO3:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Bit_Ratecolon);
                    break;
                     #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_API_GetString(en_str_Subtitlecolon);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_API_GetString(en_str_Datecolon);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT3:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MUSICINFO_INFO_BITRATE_TEXT);
                    break;
                     #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_SUBTITLE_TEXT);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_DATE_TEXT);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
					return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_TIME_TEXT);//wht1203017_9 add
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO4:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Artistcolon);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_API_GetString(en_str_Programcolon);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_API_GetString(en_str_Timecolon);
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT4:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MUSICINFO_INFO_ARTIST_TEXT);
                    break;
                     #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_PROGRAM_TEXT);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_TIME_TEXT);
                    break;
    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO5:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Samplingcolon);
                    break;
                     #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_API_GetString(en_str_Sizecolon);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT5:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MUSICINFO_INFO_SAMPLING_TEXT);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_SIZE_TEXT);
                    break;
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO6:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Yearcolon);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT6:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_MUSICINFO_INFO_YEAR_TEXT);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO7:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_API_GetString(en_str_Sizecolon);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                    #endif
                default:
                    break;
            }
            break;
        }

        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT7:
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MUSIC:
                    return MApp_ZUI_ACT_GetDmpDynamicText(HWND_DMP_PLAYBACK_TEXTINFO_INFO_SIZE_TEXT);
                    break;
                    #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
                    #endif
                case E_MPLAYER_TYPE_PHOTO:
                    #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                    #endif
                default:
                    break;
            }
            break;
        }
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_INFO8:
        case HWND_DMP_FILE_PAGE_PREVIEW_INFO_TEXT8:
            break;

// =================== Drm ===================
    #if ENABLE_DRM
        case HWND_DMP_DRM_STRING_0:
            if(_DrmStr0Idx == Title_ViewRental)
            {
                U16 u16len = 0;
                u16len = strlen((char *)DRMStrTable0[_DrmStr0Idx]);
                if(u16len < STRING_BUFFER_LENGTH)
                {
                    snprintf((char*)CHAR_BUFFER, u16len, (char *)DRMStrTable0[_DrmStr0Idx]);
                }
                }
            else if(_DrmStr0Idx == Title_AuthError)
            {
                U16 u16len = 0;
                u16len = strlen((char *)DRMStrTable0[_DrmStr0Idx]);
                if(u16len < STRING_BUFFER_LENGTH)
                {
                    snprintf((char*)CHAR_BUFFER, u16len, (char *)DRMStrTable0[_DrmStr0Idx]);
                }
            }
            else
            {
                U16 u16len = 0;
                u16len = strlen((char *)DRMStrTable0[_DrmStr0Idx]);
                if(u16len < STRING_BUFFER_LENGTH)
                {
                    snprintf((char*)CHAR_BUFFER, u16len, (char *)DRMStrTable0[_DrmStr0Idx]);
                }
            }
            DMP_DBG(printf("%s\n",CHAR_BUFFER););
            FS_ASCII2Unicode((U8 *)CHAR_BUFFER);
            break;
        case HWND_DMP_DRM_STRING_1:
            if(_DrmStr1Idx == ViewRental)
            {
                if(_DrmStr2Idx != RentalExpired)
                {
                    snprintf((char*)CHAR_BUFFER, 46, "This rental has %u views left.",
                    (DrmInfo.u32DrmRentalLimit - DrmInfo.u32DrmRentalUseCount));
                }
            }
            else
            {
                U16 _u16len = 0;
                _u16len = strlen((char *)DRMStrTable1[_DrmStr1Idx]);
                if(_u16len < STRING_BUFFER_LENGTH)
                {
                    snprintf((char*)CHAR_BUFFER, _u16len, (char *)DRMStrTable1[_DrmStr1Idx]);
                }
                //strcpy((char *)CHAR_BUFFER,(char *)DRMStrTable1[_DrmStr1Idx]);
            }
                DMP_DBG(printf("%s\n",CHAR_BUFFER););
                FS_ASCII2Unicode((U8 *)CHAR_BUFFER);
            break;

        case HWND_DMP_DRM_STRING_2:
            if(_DrmStr1Idx == ViewRental)
            {
                if(_DrmStr2Idx != RentalExpired)
                {
                    snprintf((char*)CHAR_BUFFER, 46, "Do you want to use one of your %u views now.",
                    (DrmInfo.u32DrmRentalLimit - DrmInfo.u32DrmRentalUseCount));
                }
            }
            DMP_DBG(printf("%s\n",CHAR_BUFFER););
            FS_ASCII2Unicode((U8 *)CHAR_BUFFER);
            break;
    #endif
        case HWND_DMP_PLAYBACK_MOVIERESUME_TEXT:
            snprintf((char*)CHAR_BUFFER, 13, "Resume Play?");
            FS_ASCII2Unicode((U8 *)CHAR_BUFFER);
#if (ENABLE_ATSC_TTS)
            MApp_TTS_Cus_AddUniString(CHAR_BUFFER);
            MApp_TTSControlSetOn(TRUE);
#endif
            break;
        default:
            break;
    }
    return CHAR_BUFFER;
}


#if ENABLE_DRM
void _MApp_ACTdmp_ShowDrmWin(EN_DRM_WIN win)
{
    DRM_STATUS = win;
    switch(win)
    {
        case WinUnsupported:
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_YES, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_NO, SW_HIDE);

            MApp_ZUI_API_SetFocus(HWND_DMP_DRM_ICON_DONE);
            _DrmStr1Idx = Unsupported;
            _DrmStr2Idx = None;
            _DrmBitmapIdx = DRM_Bitmap_None;
            break;
        case WinAuthError:
            //Authorization Error
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_YES, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_NO, SW_HIDE);

            MApp_ZUI_API_SetFocus(HWND_DMP_DRM_ICON_DONE);
            _DrmStr0Idx = Title_AuthError;
            _DrmStr1Idx = AuthError;
            _DrmStr2Idx = None;
            _DrmBitmapIdx = DRM_Bitmap_Error;
            break;
        case WinViewRental:
            //View DivX(R) VOD Rental
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_DONE, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_DMP_DRM_ICON_YES);
            _DrmStr0Idx = Title_ViewRental;
            _DrmStr1Idx = ViewRental;
            _DrmStr2Idx = UseRental;
            _DrmBitmapIdx = DRM_Bitmap_None;
            break;
        case WinRentalExpired:
            //Rental Expired
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_WINDOW, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_YES, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DMP_DRM_ICON_NO, SW_HIDE);

            MApp_ZUI_API_SetFocus(HWND_DMP_DRM_ICON_DONE);
            _DrmStr0Idx = Title_RentalExpired;
            _DrmStr1Idx = ViewRental;
            _DrmStr2Idx = RentalExpired;
            _DrmBitmapIdx = DRM_Bitmap_Warning;
            break;
    }
}
#endif

U16 MApp_ZUI_ACT_GetDmpDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    U16 u16BtimapIdx=0xFFFF;
    switch(hwnd)
    {
		
//>>wht1203017_10
		case HWND_DMP_FILE_PAGE_DIR_PATH_ICON:
		{
			switch(MApp_MPlayer_QueryCurrentMediaType())
			{
				case E_MPLAYER_TYPE_PHOTO:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_PHOTO; 
					}
					break;

				case E_MPLAYER_TYPE_MUSIC:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_MUSIC;
					}
					break;

				case E_MPLAYER_TYPE_MOVIE:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_MOVIE;
					}
					break;

				case E_MPLAYER_TYPE_TEXT:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_TEXT;
					}
					break;

				default:
					break;
			}
			break;
		}
//<<wht1203017_10
		case HWND_DMP_PLAYBACK_MUSIC_MEDIA_TYPE_ICON:
		case HWND_DMP_PLAYBACK_TEXT_MEDIA_TYPE_ICON:
		{
			switch(MApp_MPlayer_QueryCurrentMediaType())
			{
				case E_MPLAYER_TYPE_PHOTO:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_PHOTO; 
					}
					break;

				case E_MPLAYER_TYPE_MUSIC:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_MUSIC_SMALL;
					}
					break;

				case E_MPLAYER_TYPE_MOVIE:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_MOVIE;
					}
					break;

				case E_MPLAYER_TYPE_TEXT:
					{
						u16BtimapIdx = E_BMP_DMP_MEDIA_TYPE_TEXT_SMALL;
					}
					break;

				default:
					break;
			}
			break;
		}
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM1_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM2_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM3_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM4_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM5_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM6_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM7_ICON:
        case HWND_DMP_PLAYBACK_INFOBAR_ITEM8_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM9_ICON: //wht1203017_2 add
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM10_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM11_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM12_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM13_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM14_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM15_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM16_ICON:
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM17_ICON:	
        {
            U32 i;
            for( i = 0; i < DMP_INFOBAR_ICON_NUM; i++)
            {
                if( MApp_ZUI_API_IsSuccessor(_hwndListInfoBar[i], hwnd))
                {
                    break;
                }
            }
			HWND hwndFocus = MApp_ZUI_API_GetFocus();
            U8 u8InfobarIdx = _u8InfoBarIdx+i;
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                #if (ENABLE_MPLAYER_MOVIE)
                case E_MPLAYER_TYPE_MOVIE:
					if(u8InfobarIdx == 0 ){
						if(IsPause == 1){
							return E_BMP_DMP_BUTTON_ICON_PAUSE;
						}else{
							return E_BMP_DMP_BUTTON_ICON_PLAY;
						}
					}
					if(u8InfobarIdx >= u8MovieInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
			    			break;
                        }
                        return E_ZUI_BMP_MAX;
                    }
                    else
                    {
                        //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                        if((hwndFocus+1) == hwnd)
                        	{
								return DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX_FOCUS];
                        	}
						else
                        return DMP_MovieInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX];
                    }
                    break;
                #endif
                case E_MPLAYER_TYPE_PHOTO:
                     //u8InfobarIdx = u8InfobarIdx %u8PhotoInfoBarMax;
                    if(u8InfobarIdx>7)
                    u8InfobarIdx=u8InfobarIdx-4;
                    if(u8InfobarIdx >= u8PhotoInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
							break;
                        }
                        return E_ZUI_BMP_MAX;
                    }
                    else
                    {
                        //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
						if((hwndFocus+1) == hwnd)
                        	{
						return DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX_FOCUS];
                        	}
						else
                        return DMP_PhotoInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX];
                    }
                    break;
                case E_MPLAYER_TYPE_MUSIC:
                    //u8InfobarIdx = u8InfobarIdx %u8MusicInfoBarMax;
                    if(u8InfobarIdx>=13){
						u8InfobarIdx=u8InfobarIdx-7;
					}
                    if(u8InfobarIdx >= u8MusicInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
			    			break;
                        }
                        return E_ZUI_BMP_MAX;
                    }
                    else
                    {
                        //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                        if((hwndFocus+1) == hwnd)
                        {
							return	DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX_FOCUS];
                        }
						else
                        return DMP_MusicInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX];
                    }
                    break;
                    #if (ENABLE_MPLAYER_TEXT)
                case E_MPLAYER_TYPE_TEXT:
                    //u8InfobarIdx = u8InfobarIdx %u8TextInfoBarMax;
                    if(u8InfobarIdx>=14)
                    u8InfobarIdx=u8InfobarIdx-9;
                    if(u8InfobarIdx >= u8TextInfoBarMax)
                    {
                        if (MApp_ZUI_API_IsWindowEnabled(MApp_ZUI_API_GetParent(hwnd)))
                        {
                            MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), FALSE);
			    break;
                        }
                        return E_ZUI_BMP_MAX;
                    }
                    else
                    {
                        //MApp_ZUI_API_EnableWindow(MApp_ZUI_API_GetParent(hwnd), TRUE);
                        if((hwndFocus+1) == hwnd)
                        	{
							return DMP_TextInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX_FOCUS];
                        	}
						else
                        return DMP_TextInfoBarTable[u8InfobarIdx][INFOBAR_BMP_IDX];
                    }
                    break;
                    #endif
                default:
                    break;
            }
            break;
        }
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM1_ICON_FOCUS:
			switch(MApp_MPlayer_QueryCurrentMediaType()){
				case E_MPLAYER_TYPE_TEXT:
					return E_BMP_DMP_BUTTON_ICON_FB_FOCUS;
				default:
					if(IsPause == 1){
						return E_BMP_DMP_BUTTON_ICON_PAUSE_FOCUS;
						}else{
						return E_BMP_DMP_BUTTON_ICON_PLAY_FOCUS;
					}
			}
		break;
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM2_ICON_FOCUS:
			switch(MApp_MPlayer_QueryCurrentMediaType()){
				case E_MPLAYER_TYPE_PHOTO:
					return E_BMP_DMP_BUTTON_ICON_PREV_FOCUS;
				case E_MPLAYER_TYPE_TEXT:
					return E_BMP_DMP_BUTTON_ICON_FF_FOCUS;
				default:
					return E_BMP_DMP_BUTTON_ICON_FB_FOCUS;
				break;
			}
		break;
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM3_ICON_FOCUS:
			switch(MApp_MPlayer_QueryCurrentMediaType()){
				case E_MPLAYER_TYPE_PHOTO:
					return E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS;
				case E_MPLAYER_TYPE_TEXT:
					return E_BMP_DMP_BUTTON_ICON_PREV_FOCUS;
				default:
					return E_BMP_DMP_BUTTON_ICON_FF_FOCUS;
			}
		break;
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM4_ICON_FOCUS:
			switch(MApp_MPlayer_QueryCurrentMediaType()){
				case E_MPLAYER_TYPE_PHOTO:
					return E_BMP_DMP_BUTTON_ICON_STOP_FOCUS;
				case E_MPLAYER_TYPE_TEXT:
					return E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS;
				default:
					return E_BMP_DMP_BUTTON_ICON_PREV_FOCUS;
				break;
			}
		break;
		case HWND_DMP_PLAYBACK_INFOBAR_ITEM5_ICON_FOCUS:
			switch(MApp_MPlayer_QueryCurrentMediaType()){
				case E_MPLAYER_TYPE_TEXT:
					return E_BMP_DMP_BUTTON_ICON_STOP_FOCUS;
				default:
					return E_BMP_DMP_BUTTON_ICON_NEXT_FOCUS;
				break;
			}
		break;
		
        /*case HWND_DMP_MEDIA_TYPE_USB1_ICON:
            {
#if 1
    #if (0)
                MPlayerDeviceStatus *pDeviceStatus;

                if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP1)
                {
                    MApp_MPlayer_QueryDeviceConnectionStatus(&pDeviceStatus);
                    if(pDeviceStatus[0].u16LunValid != 0 )
                    {
                        return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_COLOUR;
                    }
                    else
                    {
                        return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_GREY;
                    }
                }
    #else
                if (u8UsbDeviceSwitchStatus == 0)
                {
                    if (u8UsbDeviceSel == DMP_USB_DISK1)
                    {
                       // return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_COLOUR;
                       return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_COLOR;//return E_BMP_DMP_MEDIA_TYPE_USB_ICON_COLOR;//wht120303_7
                    }
                    else
                    {
                       // return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_GREY;
                       return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_GREY;//return E_BMP_DMP_MEDIA_TYPE_USB_ICON_GREY;//wht120303_7
                    }
                }
                else if (u8UsbDeviceSwitchStatus == 1)
                {
                    break;
                }
                else if (u8UsbDeviceSwitchStatus == 2)
                {
                    if (u8UsbDeviceSel == DMP_USB_DISK1)
                    {
                       // return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_COLOUR;
                       return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_COLOR;//return E_BMP_DMP_MEDIA_TYPE_USB_ICON_COLOR;//wht120303_7
                    }
                    else
                    {
                        //return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_GREY;
                        return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_GREY;//return E_BMP_DMP_MEDIA_TYPE_USB_ICON_GREY;//wht120303_7
                    }
                }
    #endif

#else
                MPlayerDeviceStatus *pDeviceStatus;
                MApp_MPlayer_QueryDeviceConnectionStatus(&pDeviceStatus);
                if(pDeviceStatus[0].u16LunValid != 0)
                {
                    return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_COLOUR;
                }
                else
                {
                    return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_GREY;
                }
#endif
            }
            break;
        case HWND_DMP_MEDIA_TYPE_USB2_ICON:
            {
#if 1
 #if( 0 )        
                MPlayerDeviceStatus *pDeviceStatus;

                if (UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP2)
                {
                    MApp_MPlayer_QueryDeviceConnectionStatus(&pDeviceStatus);
                    if(pDeviceStatus[0].u16LunValid != 0 )
                    {
                        return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_COLOUR;
                    }
                    else
                    {
                        return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_GREY;
                    }
                }
 #else          
                if (u8UsbDeviceSwitchStatus == 0)
                {
                    if (u8UsbDeviceSel == DMP_USB_DISK2)
                    {
                        //return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_COLOUR;
                        return E_BMP_DMP_MEDIA_TYPE_USB_ICON_COLOR;//return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_COLOR;//wht120303_7
                    }
                    else
                    {
                       // return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_GREY;
                       return E_BMP_DMP_MEDIA_TYPE_USB_ICON_GREY;//return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_GREY;//wht120303_7
                    }
                }
                else if (u8UsbDeviceSwitchStatus == 1)
                {
                    if (u8UsbDeviceSel == DMP_USB_DISK2)
                    {
                        //return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_COLOUR;
                        return E_BMP_DMP_MEDIA_TYPE_USB_ICON_COLOR;//return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_COLOR;//wht120303_7
                    }
                    else
                    {
                       // return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_GREY;
                       return E_BMP_DMP_MEDIA_TYPE_USB_ICON_GREY;//return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_GREY;//wht120303_7
                    }
                }
                else if (u8UsbDeviceSwitchStatus == 2)
                {
                    break;
                }
        #endif
#else
                MPlayerDeviceStatus *pDeviceStatus;
                MApp_MPlayer_QueryDeviceConnectionStatus(&pDeviceStatus);
                if(pDeviceStatus[1].u16LunValid != 0)
                {
                    return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_COLOUR;
                }
                else
                {
                    return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_GREY;
                }
#endif
            }
            break;
		
        case HWND_DMP_MEDIA_TYPE_USB1_ICON_SEL:

                #if( 0 )             
                    break;
                #endif
                
                if (u8UsbDeviceSwitchStatus == 0)
                {
                    break;
                }
                else if (u8UsbDeviceSwitchStatus == 1)
                {
                    if (u8UsbDeviceSel == DMP_USB_DISK1)
                    {
                       // return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_COLOUR_SEL;
                       return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_COLOR_FOCUS;//return E_BMP_DMP_MEDIA_TYPE_USB_ICON_COLOR;//wht120303_7
                    }
                    else
                    {
                        //return E_BMP_DMP_MEDIA_TYPE_USB1_ICON_GREY_SEL;
                        return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_GREY_FOCUS;//return E_BMP_DMP_MEDIA_TYPE_USB_ICON_GREY;//wht120303_7
                    }
                }
                else if (u8UsbDeviceSwitchStatus == 2)
                {
                    break;
                }
            break;
		*/
        case HWND_DMP_MEDIA_TYPE_USB2_ICON_SEL:

                 #if( 0 )             
                    break;
                #endif

                
               if (MApp_MPlayer_QueryTotalDriveNum() == 0)
                {
                       return E_BMP_DMP_MEDIA_TYPE_USB_ICON_GREY_FOCUS;//return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_GREY;//wht120303_7
                }
                else
                {
                        //return E_BMP_DMP_MEDIA_TYPE_USB2_ICON_COLOUR;
                        return E_BMP_DMP_MEDIA_TYPE_USB_ICON_COLOR_FOCUS;//return E_BMP_DMP_MEDIA_TYPE_SD_CARD_ICON_COLOR;//wht120303_7
                }
		case HWND_DMP_KEYSTONE_CONFIG_ICON:     //xzm @201712228 for keystone icon
			if(stGenSetting.g_SysSetting.KeyStoneValue >= 0)
		 	{
				printf("BMP_UP_KEYSTONE %d \n",E_BMP_UP_KEYSTONE);
				u16BtimapIdx = E_BMP_UP_KEYSTONE;
		 	}
			 else
		 	{
				printf("BMP_DOWN_KEYSTONE %d \n",E_BMP_DOWN_KEYSTONE);
				u16BtimapIdx = E_BMP_DOWN_KEYSTONE;
		 	}
			break;
        case HWND_DMP_DRIVE_BGM_ITEM1_ICON:
        case HWND_DMP_DRIVE_ITEM1_ICON:
            {
                if(MApp_DMP_GetDrvPageIdx() <= 1)
                {
                    return E_BMP_DMP_DRIVE_PAGE_RETURN_SMALL;
                }
                else
                {
                    return E_BMP_DMP_DRIVE_ICON_SMALL;
                }
            }
        break;
        case HWND_DMP_FILE_PAGE_THUMB_ITEM1_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM2_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM3_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM4_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM5_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM6_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM7_ICON:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM8_ICON:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM9_ICON:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM10_ICON:
       // case HWND_DMP_FILE_PAGE_THUMB_ITEM11_ICON:  //wht120401_3
       // case HWND_DMP_FILE_PAGE_THUMB_ITEM12_ICON:
        {
            MPlayerFileInfo fileInfo;
            U16 u16ItemIdx = 0;
            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndListFileIcon[u16ItemIdx])
                {
                    break;
                }
            }
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
			if(!bIsDriveSelected)
			{
				if(u16ItemIdx <  (MApp_MPlayer_QueryTotalDriveNum()  -
				(MApp_DMP_GetDrvPageIdx() - 1)	* NUM_OF_PHOTO_FILES_PER_PAGE))
				{
				//printf(" CurDrvPageIdx is %d", MApp_DMP_GetDrvPageIdx()); 
				return E_BMP_DMP_DRIVE_ICON_SMALL;
				}
			}
			else  
#endif
			{
	            if((u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE) &&
	               (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
	            {
	                if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
	                {
	                    if(fileInfo.u8LongFileName[0] == 0x2e &&
	                       fileInfo.u8LongFileName[1] == 0x00 &&
	                       fileInfo.u8LongFileName[2] == 0x00 &&
	                       fileInfo.u8LongFileName[3] == 0x00)
	                    {
	                       u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_BACK;//wht1203017_1  u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_RETURN;
	                    }
	                    else if(fileInfo.u8LongFileName[0] == 0x2e &&
	                            fileInfo.u8LongFileName[1] == 0x00 &&
	                            fileInfo.u8LongFileName[2] == 0x2e &&
	                            fileInfo.u8LongFileName[3] == 0x00 &&
	                            fileInfo.u8LongFileName[4] == 0x00 &&
	                            fileInfo.u8LongFileName[5] == 0x00)
	                    {
	                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_BACK;
	                    }
	                    else if(ds_type == DS_FOCUS)
	                    {
	                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_DIR;
	                    }
	                    else
	                    {
	                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_DIR;
	                    }
	                }
	                else
	                {
	                    //if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
	                    {
	                        switch(MApp_MPlayer_QueryCurrentMediaType())
	                        {
	                            case E_MPLAYER_TYPE_PHOTO:
	                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_PICTURE;
                                break;
                            case E_MPLAYER_TYPE_MUSIC:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_MUSIC;
                                break;
                                #if (ENABLE_MPLAYER_MOVIE)
                            case E_MPLAYER_TYPE_MOVIE:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_MOVIE;
                                break;
                                #endif
                                #if (ENABLE_MPLAYER_TEXT)
                            case E_MPLAYER_TYPE_TEXT:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_TXT;
                                break;
                                #endif
                            default:
	                                break;
                        }
                    }
                }
            }
       		}
        }
        break;
    #if PLAYLIST_BGM
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12_ICON:
        {
            MPlayerFileInfo fileInfo;
            U16 u16ItemIdx = 0;
            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndBgmListFileIcon[u16ItemIdx])
                {
                    break;
                }
            }
            if((u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE) &&
               (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
            {
                if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
                {
                    if(fileInfo.u8LongFileName[0] == 0x2e &&
                       fileInfo.u8LongFileName[1] == 0x00 &&
                       fileInfo.u8LongFileName[2] == 0x00 &&
                       fileInfo.u8LongFileName[3] == 0x00)
                    {
                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_RETURN;
                    }
                    else if(fileInfo.u8LongFileName[0] == 0x2e &&
                            fileInfo.u8LongFileName[1] == 0x00 &&
                            fileInfo.u8LongFileName[2] == 0x2e &&
                            fileInfo.u8LongFileName[3] == 0x00 &&
                            fileInfo.u8LongFileName[4] == 0x00 &&
                            fileInfo.u8LongFileName[5] == 0x00)
                    {
                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_BACK;
                    }
                    else if(ds_type == DS_FOCUS)
                    {
                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_DIR;
                    }
                    else
                    {
                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_DIR;
                    }
                }
                else
                {
                    //if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
                    {
                        switch(MApp_MPlayer_QueryCurrentMediaType())
                        {
                            case E_MPLAYER_TYPE_PHOTO:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_PICTURE;
                                break;
                            case E_MPLAYER_TYPE_MUSIC:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_MUSIC;
                                break;
                                #if (ENABLE_MPLAYER_MOVIE)
                            case E_MPLAYER_TYPE_MOVIE:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_MOVIE;
                                break;
                                #endif
                                #if (ENABLE_MPLAYER_TEXT)
                            case E_MPLAYER_TYPE_TEXT:
                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_TXT;
                                break;
                                #endif
                            default:
                                break;
                        }
                    }
                }
            }
        }
        break;
		/*
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM1_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM2_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM3_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM4_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM5_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM6_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM7_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM8_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM9_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM10_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM11_CHECK_ICON:
        case HWND_DMP_BGM_FILE_PAGE_THUMB_ITEM12_CHECK_ICON:
        {
            MPlayerFileInfo fileInfo;
            U16 u16ItemIdx = 0;
            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndBgmListFileCheckMark[u16ItemIdx])
                {
                    break;
                }
            }
            if((u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE) &&
               (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
            {
                if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
                {
                    u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_CHECK;
                }
            }
        }
        break;
		*/
    #endif
        
		case HWND_DMP_FILE_PAGE_THUMB_ITEM1_FOCUS_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM2_FOCUS_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM3_FOCUS_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM4_FOCUS_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM5_FOCUS_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM6_FOCUS_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM7_FOCUS_ICON:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM8_FOCUS_ICON:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM9_FOCUS_ICON:
        //case HWND_DMP_FILE_PAGE_THUMB_ITEM10_FOCUS_ICON:
       // case HWND_DMP_FILE_PAGE_THUMB_ITEM11_ICON:  //wht120401_3
       // case HWND_DMP_FILE_PAGE_THUMB_ITEM12_ICON:
        {
            MPlayerFileInfo fileInfo;
			//HWND hwndFocus = MApp_ZUI_API_GetFocus();
            U16 u16ItemIdx = 0;
            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndListFileFocusIcon[u16ItemIdx])
                {
                    break;
                }
            }
			//printf("\n---u16ItemIdx=%d--\n",u16ItemIdx);
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
			if(!bIsDriveSelected)
			{
				if(u16ItemIdx <  (MApp_MPlayer_QueryTotalDriveNum()  -
				(MApp_DMP_GetDrvPageIdx() - 1)	* NUM_OF_PHOTO_FILES_PER_PAGE))
				{
				//printf(" CurDrvPageIdx is %d", MApp_DMP_GetDrvPageIdx()); 
				return E_BMP_DMP_DRIVE_ICON_SMALL;
				}
			}
			else  
#endif
			{
	            if((u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE) &&
	               (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
	            {
	                if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
	                {
	                    if(fileInfo.u8LongFileName[0] == 0x2e &&
	                       fileInfo.u8LongFileName[1] == 0x00 &&
	                       fileInfo.u8LongFileName[2] == 0x00 &&
	                       fileInfo.u8LongFileName[3] == 0x00)
	                    {
	                       u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_BACK_FOCUS;//wht1203017_1  u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_RETURN;
	                    }
	                    else if(fileInfo.u8LongFileName[0] == 0x2e &&
	                            fileInfo.u8LongFileName[1] == 0x00 &&
	                            fileInfo.u8LongFileName[2] == 0x2e &&
	                            fileInfo.u8LongFileName[3] == 0x00 &&
	                            fileInfo.u8LongFileName[4] == 0x00 &&
	                            fileInfo.u8LongFileName[5] == 0x00)
	                    {
	                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_BACK_FOCUS;
	                    }
	                    else if(ds_type == DS_FOCUS)
	                    {
	                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_DIR_FOCUS;
	                    }
	                    else
	                    {
	                        u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_DIR_FOCUS;
	                    }
	                }
	                else
	                {
	                    //if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
	                    {
	                        switch(MApp_MPlayer_QueryCurrentMediaType())
	                        {
	                            case E_MPLAYER_TYPE_PHOTO:
	                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_PICTURE_FOCUS;
	                                break;
	                            case E_MPLAYER_TYPE_MUSIC:
	                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_MUSIC_FOCUS;
	                                break;
	                            case E_MPLAYER_TYPE_MOVIE:
	                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_MOVIE_FOCUS;
	                                break;
	                            case E_MPLAYER_TYPE_TEXT:
	                                u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_TXT_FOCUS;
	                                break;
	                            default:
	                                break;
	                        }
	                    }
	                }
	            }
       		}
        }
        break;
#if 0		//wht120401_3
        case HWND_DMP_FILE_PAGE_THUMB_ITEM1_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM2_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM3_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM4_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM5_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM6_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM7_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM8_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM9_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM10_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM11_CHECK_ICON:
        case HWND_DMP_FILE_PAGE_THUMB_ITEM12_CHECK_ICON:
        {
            MPlayerFileInfo fileInfo;
            U16 u16ItemIdx = 0;
            for(u16ItemIdx=0;u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE;u16ItemIdx++)
            {
                if(hwnd == _hwndListFileCheckMark[u16ItemIdx])
                {
                    break;
                }
            }
            if((u16ItemIdx<NUM_OF_PHOTO_FILES_PER_PAGE) &&
               (MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE, u16ItemIdx, &fileInfo) == E_MPLAYER_RET_OK))
            {
                if(fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
                {
                    u16BtimapIdx = E_BMP_DMP_FILE_SELECT_ICON_CHECK;
                }
            }
        }
        break;
#endif
        case HWND_DMP_ALERT_ICON:
        {
            switch(_enDmpMsgType)
            {
                case DMP_MSG_TYPE_LOADING:
                    u16BtimapIdx = E_BMP_DMP_ALERT_ICON_LOADING_BG;
                    break;
                case DMP_MSG_TYPE_UNSUPPORTED_FILE:
                    u16BtimapIdx = E_BMP_DMP_ALERT_ICON_UNSUPPORTED;
                    break;
                case DMP_MSG_TYPE_INVALID_OPERATION:
                    u16BtimapIdx = E_BMP_DMP_ALERT_ICON_INVALID_OPERATION;
                    break;
                default:
                    u16BtimapIdx = E_BMP_DMP_ALERT_ICON_UNSUPPORTED;
                    break;
            }
        }
        break;
        case HWND_DMP_PLAYBACK_STATUS_ICON:
        {
            DMP_DBG(printf("HWND_DMP_PLAYBACK_STATUS_ICON, %u\n", _enDmpPlayIconType););
            switch((unsigned int) _enDmpPlayIconType)
            {
				//>>wht120514_1
                case PLAY_MODE_ICON_BGMUSIC_MODE:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_BGM;
                    break;                    
                //<<wht120514_1    
                case PLAY_MODE_ICON_NEXT:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_NEXT;
                    break;
                case PLAY_MODE_ICON_PREVIOUS:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_PREV;
                    break;
                case PLAY_MODE_ICON_STOP:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_STOP;
                    break;
                case PLAY_MODE_ICON_PLAY:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_PLAY;
                    break;
                case PLAY_MODE_ICON_PAUSE:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_PAUSE;
                    break;
                case PLAY_MODE_ICON_AB_REPEAT:
                case PLAY_MODE_ICON_SETA:
                case PLAY_MODE_ICON_AB_LOOP:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_AB_REPEAT;
                    break;
                case PLAY_MODE_ICON_FF2X:
                case PLAY_MODE_ICON_FF4X:
                case PLAY_MODE_ICON_FF8X:
                case PLAY_MODE_ICON_FF16X:
                case PLAY_MODE_ICON_FF32X:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_FF;
                    break;
                case PLAY_MODE_ICON_SF2X:
                case PLAY_MODE_ICON_SF4X:
                case PLAY_MODE_ICON_SF8X:
                case PLAY_MODE_ICON_SF16X:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_SF;
                    break;
                case PLAY_MODE_ICON_FB2X:
                case PLAY_MODE_ICON_FB4X:
                case PLAY_MODE_ICON_FB8X:
                case PLAY_MODE_ICON_FB16X:
                case PLAY_MODE_ICON_FB32X:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_FB;
                    break;
                case PLAY_MODE_ICON_SD:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_SD;
                    break;
                case PLAY_MODE_ICON_FB_INVALID:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_FB_INVALID;
                    break;
                case PLAY_MODE_ICON_FF_INVALID:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_FF_INVALID;
                    break;
				case PLAY_MODE_ICON_REPEAT_1:
				case PLAY_MODE_ICON_REPEAT_NONE:
				case PLAY_MODE_ICON_REPEAT_ALL:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_REPEAT;
                    break;
                case PLAY_MODE_ICON_ZOOM_IN_MODE:          
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_ZOOMOUT;//wht120515_2  E_BMP_DMP_BUTTON_ICON_ZOOMIN;
                    break;
                            
                case PLAY_MODE_ICON_ZOOM_OUT_MODE:
                    u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_ZOOMIN;//wht120515_2 E_BMP_DMP_BUTTON_ICON_ZOOMOUT;             
                    break;
				case PLAY_MODE_ICON_ASPECT_MODE:
					u16BtimapIdx = E_BMP_DMP_BUTTON_ICON_FUNCTION;
					break;
            #if 0//(ENABLE_DRM)
                case HWND_DMP_DRM_ALERT_ICON:
                    switch(_DrmBitmapIdx)
                    {
                        case DRM_Bitmap_None:
                            //u16BtimapIdx = 0xFFFF;
                            break;
                        case DRM_Bitmap_Warning:
                            u16BtimapIdx = E_BMP_DMP_ALERT_ICON_INVALID_OPERATION;
                            break;
                        case DRM_Bitmap_Error:
                            u16BtimapIdx = E_BMP_DMP_ALERT_ICON_UNSUPPORTED;
                            break;
                    }
                    break;
            #endif //ENABLE_DRM

                default:
                    break;
            }
           // if (MApp_MPlayer_QueryCurrentMediaType()!= E_MPLAYER_TYPE_PHOTO) _enDmpPlayIconType = PLAY_MODE_ICON_MAX;
        }
        break;

        default:
            break;
    }
    return u16BtimapIdx;
}

S16 MApp_ZUI_ACT_GetDmpDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_DMP_VOLUME_CONFIG_BAR:
        #if(ENABLE_CEC)
            if( MApp_CEC_ARC_Is_ExtAudioDeviceConnected() )
          /*#if(CEC_VERSION_USING == CEC_NEW_VERSION)
            if (msAPI_CEC_IsAudioSystemKeyValid()== TRUE)
          #else
            if (msAPI_CEC_ARC_Is_Connect() == TRUE)
          #endif */
            {
                return msAPI_CEC_ARC_GetARCAudioVolume(); // anvi22
            }
            else
       #endif
            {
                return stGenSetting.g_SoundSetting.Volume;
            }

		case HWND_DMP_KEYSTONE_CONFIG_BAR:     //xzm @20171228 for keystone bar
		
			return stGenSetting.g_SysSetting.KeyStoneValue+39;
			
        default:
            break;
    }

    return 0; //for empty  data
}

#if (ENABLE_DRM)
/*
extern BOOLEAN MApp_VDPlayer_CheckDRMActivationFile(void);

static void _MApp_ACTdmp_CheckDRMActivation(void)
{
    if(MApp_VDPlayer_CheckDRMActivationFile() == TRUE)
    {
        DMP_DBG(printf("activation!\n"););
        MApp_LoadGenSetting();
        if(stGenSetting.g_VDplayerDRMInfo.bIsActivated==FALSE)
        {
            stGenSetting.g_VDplayerDRMInfo.bIsActivated = TRUE;
            stGenSetting.g_VDplayerDRMInfo.bIsDeactivated = FALSE;
            MApp_SaveGenSetting();
        }
    }
    else
    {
        DMP_DBG(printf("MApp_VDPlayer_CheckDRMActivationFile() == FALSE\n"););
    }
}
*/
void _MApp_ZUI_ACTdmp_AppShowDRM(void)
{
    DrmInfo = MApp_VDPlayer_GetDRMInfo();
    DMP_DBG(printf(" >>>      FILE_FORMAT= %lu  \n",DrmInfo.u8DrmFileFormat););
    DMP_DBG(printf(" >>>    AUTHORIZATION_STATUS=%lu \n",DrmInfo.u8DrmAuthorization););
    DMP_DBG(printf(" >>>     RENTAL_EXPIRE_STATUS=%lu  \n",DrmInfo.u8DrmRentalStatus););
    DMP_DBG(printf(" >>>      RENTAL_USE_LIMIT=%lu  \n",DrmInfo.u32DrmRentalLimit););
    DMP_DBG(printf(" >>>     E_SHAREMEM_DRM_RENTAL_USE_COUNT=%lu  \n",DrmInfo.u32DrmRentalUseCount););
    DMP_DBG(printf(" >>>     E_VDPLAYER_ERROR_INFO=%lu  \n",DrmInfo.u32VDPlayerErrCode););

    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_ALERT_WINDOW))
    {
        MApp_ZUI_API_ShowWindow(HWND_DMP_ALERT_WINDOW,SW_HIDE);
    }

    if(DrmInfo.u32VDPlayerErrCode == EN_VDP_ERRORCODE_DRM_ERR_VERSION_EXPIRED)
    {
        _MApp_ACTdmp_ShowDrmWin(WinUnsupported);
    }
    else
    {
        if(DrmInfo.u8DrmFileFormat)// Check if it is DRM file
        {
            DMP_DBG(printf("DrmInfo.u8DrmFileFormat true\n"););
            if(!DrmInfo.u8DrmAuthorization) // init fail
            {
                DMP_DBG(printf("V03\n"););
                //MENU_DLG_DRM_AUTHORIZATION Error PAGE
                _MApp_ACTdmp_ShowDrmWin(WinAuthError);
            }
            else
            {
                DMP_DBG(printf("DrmInfo.u8DrmAuthorization TRUE\n"););
            //can play drm
                if(DrmInfo.u8DrmRentalStatus)
                {
                    DMP_DBG(printf("show show user expired\n"););
                    //MENU_DLG_DRM_RETAL_EXPIRE
                    //show user expired
                    _MApp_ACTdmp_ShowDrmWin(WinRentalExpired);
                }
                else
                {
                    //RENTAL_EXPIRE_STATUS
                    //show user limit
                    DMP_DBG(printf("V04\n"););
                    //_MApp_ACTdmp_CheckDRMActivation();
                    _MApp_ACTdmp_ShowDrmWin(WinViewRental);
                }
            }
        }
        else
        {
            DMP_DBG(printf("DrmInfo.u8DrmFileFormat false\n"););
        }
    }
}
#endif

static void _MApp_DMP_ErrorHandling_GotoFileSelectPage(enumMPlayerMediaType eMediaType)
{
    DMP_DBG(printf("[ERROR HANDLE] Back to FileSelect page\n"));

    MApp_MPlayer_Stop();
    MApp_MPlayer_StopMusic();

    msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

    switch(eMediaType)
    {
        case E_MPLAYER_TYPE_MOVIE:
#if (ENABLE_SUBTITLE_DMP)
            if(MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_MPEG4)
            {
                MApp_MPlayer_DisableSubtitle();
                _stDmpPlayVar.stMovieInfo.bSubtitleOff = TRUE;
            }
#endif //#if (ENABLE_SUBTITLE_DMP)
            break;

        case E_MPLAYER_TYPE_MUSIC:
            _u16MusicCurrentTime = 0; //initial value for drawing 'MUSIC' current time
            if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
            {
                MApp_MPlayer_DisableLRCLyric();
                memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
            }
            break;

        case E_MPLAYER_TYPE_PHOTO:
            break;

        default:
            break;
    }

    if(MApp_DMP_GetDmpFlag()& DMP_FLAG_MEDIA_FILE_PLAYING)
    {
        MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
    }

}


/////////////////////////////////////////////////////////
// Customize Window Procedures
BOOLEAN MApp_UiMediaPlayer_Notify(enumMPlayerNotifyType eNotify, void *pInfo)
{
    if (IsStorageInUse())
    {
        if (MApp_ZUI_GetActiveOSD() == E_OSD_DMP)
        {
            // notification accepted
        }
        else if (((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)
                        || (MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE)||(MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX))
                && ((eNotify == E_MPLAYER_NOTIFY_USB_DEVICE_STATUS_CHANGE)
                        || (eNotify == E_MPLAYER_NOTIFY_USB_ACTIVE_DEVICE_STATUS_CHANGE)))
        {
            // notification accepted
        }
        #if ENABLE_DMP_MINI_MENU
        else if(MApp_ZUI_GetActiveOSD() == E_OSD_DMP_MINI_MENU)
        {
        }
        #endif
        else
        {
            // notification not accepted
            // ZUIMM_DBG(printf("Notification (%d) doesn't accept\n", eNotify));
            return FALSE;
        }
    }

    _enNotify = eNotify; //backup notify event.
    #if (ENABLE_MPLAYER_MOVIE)
    _enPlayMode_AtNotify = MApp_MPlayer_QueryMoviePlayMode();
    #endif

    switch(eNotify)
    {
    #if ENABLE_DRM
        case E_MPLAYER_NOTIFY_DRM_INIT:
        {
            DMP_DBG(printf("E_MPLAYER_NOTIFY_DRM_INIT\n"););
            _MApp_ZUI_ACTdmp_AppShowDRM();
        }
        break;
    #endif
        case E_MPLAYER_NOTIFY_USB_DEVICE_STATUS_CHANGE:
            DMP_DBG(printf("E_MPLAYER_NOTIFY_USB_DEVICE_STATUS_CHANGE\n"));
            break;

        case E_MPLAYER_NOTIFY_USB_ACTIVE_DEVICE_STATUS_CHANGE:
            DMP_DBG(printf("E_MPLAYER_NOTIFY_USB_ACTIVE_DEVICE_STATUS_CHANGE\n"));
            #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL || MApp_Get_PIPMode() == EN_PIP_MODE_POP)
            {
                MApp_Set_PIPMode(EN_PIP_MODE_OFF,NULL,NULL);
            }
            #endif
            {
                _MApp_ACTdmp_HandleUsbStatusChanged();
            }
            break;
        case E_MPLAYER_NOTIFY_DRIVE_CHANGE:
            DMP_DBG(printf("E_MPLAYER_NOTIFY_DRIVE_CHANGE\n"));
            {
                if(MApp_DMP_RecalculateDriveMappingTable())
                {
                    _MApp_ZUI_ACT_DmpRefreshPlayList();

                    MApp_DMP_SetDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
                    U8 i;
                    // Search previous mapped drive

                    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
                    {
                        if(MApp_MPlayer_QueryCurrentDriveIndex() == MApp_DMP_GetDriveFromMappingTable(i))
                        {
                            MApp_DMP_SetCurDrvIdxAndCalPageIdx(i);
                        }
                        //printf("[Mappings] %bu. --> drive %bu\n", i, MApp_MediaPlayer_GetDriveFromMappingTable(i));
                    }

                    if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU
                        || MApp_ZUI_GetActiveOSD() == E_OSD_INPUT_SOURCE||MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
                    {
                        return FALSE;;
                    }

                    if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_DRIVE_SELECT)
                    {
                        U8 u8Idx = (MApp_DMP_GetCurDrvIdx()+1) % DMP_DRIVE_NUM_PER_PAGE;
                        MApp_ZUI_API_SetFocus(_hwndListDriveItem[u8Idx]);
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_DRIVE_PAGE);
                    }
                #if PLAYLIST_BGM
                    else if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_BGM_DRIVE_SELECT)
                    {
                        U8 u8Idx = (MApp_DMP_GetCurDrvIdx()+1) % DMP_DRIVE_NUM_PER_PAGE;
                        MApp_ZUI_API_SetFocus(_hwndBgmListDriveItem[u8Idx]);
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_DRIVE_BGM_PAGE);
                    }
                #endif
                    else
                    {
                        MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_MEDIA_TYPE_USB_GROUP);
                    }
                }
                else
                {
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
                    MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
                    MApp_MPlayer_Stop(); // for bgm
                }
            }
            break;
        case E_MPLAYER_NOTIFY_SHOW_MUSIC_NFO:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_SHOW_MUSIC_NFO\n"));
            {
                // do nothing
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_SHOW);
            }
            break;

#if (ENABLE_MPLAYER_MOVIE)
        case E_MPLAYER_NOTIFY_HIDE_SUBTITLE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_HIDE_SUBTITLE\n"));
            {
                memset(_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf,0, DMP_STRING_BUF_SIZE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE,SW_HIDE);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);
            }
            #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            if( !MApp_DMP_IsOSDVisible()&&
                !bUIexist && !MApp_MPlayer_IsCurSubtitleText()
                )
            {
                U8 u8GWinId = MApp_ZUI_API_QueryGWinID();
                if(u8GWinId == 0xFF)
                {
                    MApp_ZUI_API_EmptyMessageQueue();
                    return FALSE;
                }
                if(MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
                {
                    MApi_GOP_GWIN_Enable(u8GWinId, FALSE);
                    MApp_DMP_BW_Control(FALSE);
                    MApp_ZUI_API_EmptyMessageQueue();
                    MApp_ZUI_API_TerminateGDI();
                    msAPI_MpegSP_SetShowStatus(TRUE);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                    MApp_TS_Subtitle_SetShowStatus(FALSE);
#endif
                    DMP_DBG(printf("MApp_ZUI_API_TerminateGDI 3\n"););
                }
            }
            #endif

            break;
#endif
        case E_MPLAYER_NOTIFY_SHOW_SUBTITLE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_SHOW_SUBTITLE\n"));
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            if(!_stDmpPlayVar.stMovieInfo.bSubtitleOff)
            {
                #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                _MApp_ZUI_ACTdmp_RestoreGWINandFB();
                #endif
                memcpy(_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf,(U8*)pInfo, DMP_STRING_BUF_SIZE);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE,SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);

            }
            break;

        case E_MPLAYER_NOTIFY_SHOW_LYRIC:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_SHOW_LYRIC\n"));
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            {
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE,SW_SHOW);
                memcpy(_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf,(U8*)pInfo, DMP_STRING_BUF_SIZE);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_LYRIC_PAGE);
            }
            break;

        case E_MPLAYER_NOTIFY_PLAYING_TIME_TICK:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_PLAYING_TIME_TICK\n"));
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            #if ENABLE_DMP_MINI_MENU
            if(MApp_MPlayer_IsMoviePlaying())
            {
                _MApp_ZUI_ACT_InvalidateMiniPlaybackPageTime();
            }
            else
            #endif
            {
                #if (ENABLE_MPLAYER_MOVIE)
                if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    // Todo: update movie info window - current time
                    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                    {
                        if(_u16MovieTotalTime != 0xFFFF && _u16MovieTotalTime != 0)
                        {
                            U32 u32Percent = _u16MovieCurrentTime*100 /_u16MovieTotalTime;


                            if(MApp_MPlayer_QueryMoviePlayMode() >= E_MPLAYER_MOVIE_FB_2X &&
                                MApp_MPlayer_QueryMoviePlayMode() <= E_MPLAYER_MOVIE_FB_32X)
                            {
                                if (u32Percent < 6)
                                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                                else
                                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)u32Percent);

                            }
                            else
                            {
                                MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)u32Percent);
                            }

                        }
                        else if(_u16MovieTotalTime == 0)
                        {
                            MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                        }
                        else
                        {
                            MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                            DMP_DBG(printf("[Error] Get total time failed! (0x%lx)\n", _u16MovieTotalTime););
                        }
                        MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                    }
                }
                else
                #endif
                {
                    if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)
                    {
                        U32 u32MusicCurrentTime = *(U32*)pInfo;

                        if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                        {
                            _u32MusicCurrentTime = u32MusicCurrentTime;
                            //printf("===============%u\n",MApp_MPlayer_QueryMusicFilePlayTime());
                            if(MApp_MPlayer_QueryMusicFilePlayTime() == u32MusicCurrentTime)
                            { // to the end of file
                                //printf("################%u\n",u16MusicCurrentTime);
                                if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                                {
                                    MApp_MPlayer_DisableLRCLyric();
                                    memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE, SW_HIDE);
                                }
                                /*
                                MApp_ZUI_API_KillTimer(HWND_MEDIA_PLAYER_EQ_LIST, MPLAYER_EQ_TIMER);
                                MApp_ZUI_API_ShowWindow(HWND_MEDIA_PLAYER_EQ_LIST, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_MEDIA_PLAYER_LYRIC_STATUS, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_MEDIA_PLAYER_PREVIEW_TIME, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_MEDIA_PLAYER_PLAY_STATUS, SW_HIDE);

                                if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                                {
                                    MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                                }
                                */
                            }
                            if(MApp_MPlayer_QueryMusicFilePlayTime() >= u32MusicCurrentTime)
                            {
                                // Todo: update music preview window - current time
                                U32 u32TotalTime = MApp_MPlayer_QueryMusicFilePlayTime();
                                if(u32TotalTime == 0)
                                {
                                    DMP_DBG(printf("u32TotalTime == 0\n"););
                                    //u32TotalTime = 1;
                                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                                }
                                else if(u32TotalTime != 0xFFFFFFFF)
                                {
                                    //printf("%d\n", (U8)u32Percent);
                                    U32 u32CurTime = u32MusicCurrentTime;
                                    U32 u32Percent = u32CurTime*100 / (u32TotalTime);
                                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)u32Percent);
                                }
                                else
                                {
                                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                                    DMP_DBG(printf("[Error] Get total time failed! (0x%lx)\n", u32TotalTime););
                                }
                                MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                            }
                            if(u32MusicCurrentTime == 0)
                            {
                                //need reset music status
                                if(MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)
                                {
                                    _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                                    DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                    MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                                }
                            }
                        }
                        else if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_STATUS_GROUP))
                        {
                            if((MApp_MPlayer_QueryMusicPlayMode() != E_MPLAYER_MUSIC_NORMAL)&&(u32MusicCurrentTime == 0))
                            {
                                MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                                _MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_MUSIC);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                            }

                        }

                        if((_enRepeatABStatus == REPEATAB_MODE_AB)
                            && _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0] != 0xFFFFFFFF
                            && _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1] != 0xFFFFFFFF)
                        {
                            if (u32MusicCurrentTime >= _stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[1])
                            {
                                switch(MApp_MPlayer_QueryCurrentFileMediaSubType())
                                {
                                #if (ENABLE_WMA)
                                    case E_MPLAYER_SUBTYPE_WMA:
                                        MApp_WMA_ProcessTimeOffset(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0]*1000);
                                        break;
                                #endif

                                    case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
                                    case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
                                    case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_OGG)
                                    case E_MPLAYER_SUBTYPE_OGG:
#endif
#if ( ENABLE_AMR )
                                    case E_MPLAYER_SUBTYPE_AMR:
                                    case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_FLAC)
                                    case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
                                    case E_MPLAYER_SUBTYPE_AC3:
#endif


                                        MApp_Music_ProcessTimeOffset(_stDmpPlayVar.stMusicInfo.au32MusicRepeatTime[0]*1000);
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case E_MPLAYER_NOTIFY_BEFORE_PHOTO_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_PHOTO_PREVIEW\n"));
            {
                MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_SHOW);
                DMP_DBG(printf("MApp_ZUI_CTL_MarqueeTextEnableAnimation \n"););
                //_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_FILE_PAGE_PREVIEW_FILENAME_STRING, TRUE);
            }
            break;
        case E_MPLAYER_NOTIFY_END_OF_PHOTO_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_PHOTO_PREVIEW\n"));
            // TODO: refine here
            //MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_SHOW);
            //_MApp_ACTdmp_HidePreviewWin();
            break;
        case E_MPLAYER_NOTIFY_BEFORE_MUSIC_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_MUSIC_PREVIEW\n"));
            break;
        case E_MPLAYER_NOTIFY_END_OF_MUSIC_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_MUSIC_PREVIEW\n"));
            {
               // _MApp_ACTdmp_HidePreviewWin();
            }
            break;
        case E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW\n"));
            {
                _stDmpPlayVar.stMovieInfo.bSubtitleOff = TRUE;
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_SHOW);
                //_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(
                //HWND_DMP_FILE_PAGE_PREVIEW_FILENAME_STRING, TRUE);
                //don't set timer to keep preview info
                //MApp_ZUI_API_SetTimer(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, DMP_TIMER_PREVIEW_WIN, DMP_TIME_MS_PREVIEW_WIN);
            }
            break;
        case E_MPLAYER_NOTIFY_END_OF_MOVIE_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_MOVIE_PREVIEW\n"));
            #if ENABLE_AUTOTEST
            printf("151_dmp_movie_preview"); // don't del it cause it is for autotest MM
            #endif
            {
                //MApp_ZUI_API_KillTimer(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, DMP_TIMER_PREVIEW_WIN);
                // don't call stop preview here to leave last frame on screen
                // MApp_MPlayer_StopPreview();
                //MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP);
                // special case, leave preview window here
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
            }
            break;
            #if (ENABLE_MPLAYER_MOVIE)
        #if ENBALE_PARENTALRATING_MM
        case E_MPLAYER_NOTIFY_MOVIE_RATING_CONTROL:
            {
                MApp_BlockSys_SetBlockStatus(TRUE);
                MApp_ChannelChange_CheckBlockChannelPW();
                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
            }
                break;
        #endif
            #endif
        case E_MPLAYER_NOTIFY_END_OF_TEXT_PREVIEW:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_TEXT_PREVIEW\n"));
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_INFO_GROUP, SW_SHOW);
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_TEXT, SW_SHOW);
            break;
        case E_MPLAYER_NOTIFY_MEDIA_PREDECODE_OK:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_MEDIA_PREDECODE_OK\n"));
            MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
            break;
        #if ENABLE_LAST_MEMORY
        case E_MPLAYER_NOTIFY_LAST_MEMORY_RESUME_PLAY:
        // this notify is behind the E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE immediately
        //popup the resume dialog
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_LAST_MEMORY_RESUME_PLAY\n"));
            if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
            {
                if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PAGE_INFOBAR))
                    MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
				MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN, DMP_TIME_MS_MOVIERESUME);//wht141014_13
            }
			else if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC)//>>wht120614_1
            {
                if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PAGE_INFOBAR))
                    MApp_ZUI_API_StoreFocusCheckpoint();
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_MOVIERESUME_YES);
				MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN, DMP_TIME_MS_MOVIERESUME);//wht141014_13
            }
            break; //<<wht120614_1
        #endif //ENABLE_LAST_MEMORY
		case E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE:
			DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE\n"));
					{
			#if ENABLE_DRM
						if(pInfo == NULL)
						{
							MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_HIDE);
							break;
						}
			#endif
						if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
						{
							// for movie thumbnail, do nothing
						}
						else if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_LOADING)
						{
							// TODO: need refine
							m_u16PlayErrorNum = 0;
							bPlayEndFlag = FALSE;//wht120818_1
							MApp_DMP_UiStateTransition(DMP_UI_STATE_PLAYING_STAGE);
							DMP_DBG(printf("    - change to PLAYING_STAGE\n"));
							#if ENABLE_FIX_GREENPANEL_BUG
							if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
							{
								devOPE_Display_Buffer_Freeze(TRUE);
								bIsBufferFreeze = TRUE;//wht1200919_1
							}
							#endif
						}
						else if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_PLAYING_STAGE)
						{
							//m_u16PlayErrorNum = 0;
							DMP_DBG(printf("    -PLAYING_STAGE--\n"));
							// put some initial variable or initial call after mapp_mplayer_play

							BOOLEAN bInfoShow = FALSE; // this is for info page
							enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
							g_bPlayPrev = FALSE;
							bPlayEndFlag = FALSE; //wht120818_1
							if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
							{
								bInfoShow = TRUE;
								MApp_ZUI_API_StoreFocusCheckpoint();
							}
							DMP_DBG(printf("playing eMediaType %u\n",eMediaType););
							#if ENABLE_FIX_GREENPANEL_BUG
							if(eMediaType == E_MPLAYER_TYPE_MOVIE)
							{
								devOPE_Display_Buffer_Freeze(TRUE);
								bIsBufferFreeze = TRUE;//wht1200919_1
							}
							#endif
							//>>wht120522_8
							if ((_enDmpPlayIconType >= PLAY_MODE_ICON_FB2X) && (_enDmpPlayIconType <= PLAY_MODE_ICON_FB16X))
							{
								_enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
								DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;
								DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
								MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
							}
							//<<wht120522_8
							switch(eMediaType)
							{
								case E_MPLAYER_TYPE_MOVIE:
								{
								   _MApp_ACTdmp_MovieCancelRepeatAB();
								#if (ENABLE_DIVX_PLUS == 1)
									_u16DivxTitleIdx = 0;
									_u16DivxEditionIdx = 0;
									_u16DivxChpIdx = 0;
									_u8DivxAutoChpIdx = 0;
								#endif
									MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
									DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
									DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
									if(bInfoShow)
									{
										_MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_MOVIE);
									}
									else
									{
										MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
									}

									//MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);

										_stDmpPlayVar.stMovieInfo.bSubtitleOff = FALSE;
			#if (ENABLE_SUBTITLE_DMP)
	
									MApp_MPlayer_MovieChangeSubtitleTrack(0);

			#endif
									_MApp_ZUI_ACTdmp_OperateSubtitle();
									DMP_DBG(printf("Turn ON external SUBTITLE\n"););
									MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE ,SW_SHOW);
									MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_SUBTITLE_PAGE);

									_stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[0] = 0xFFFFFFFF;
									_stDmpPlayVar.stMovieInfo.au32MovieRepeatTime[1] = 0xFFFFFFFF;
									memset((U8*)_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf, 0, DMP_STRING_BUF_SIZE);
								}
									break;

								case E_MPLAYER_TYPE_PHOTO:
									MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
									if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
									{
										DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
										DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
									}
									else if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
									{
										DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PLAY;
										DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Play;
									}
									if(bInfoShow)
									{
										_MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_PHOTO);
									}
									else
									{
										MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
									}

									break;

								case E_MPLAYER_TYPE_MUSIC:
									if(MApp_DMP_GetDmpFlag() & DMP_FLAG_BGM_MODE)
									{
									}
									else
									{
										MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
										DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;
										DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
										MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
										if(bInfoShow)
										{
											_MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_MUSIC);
										}
										else
										{
											MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
										}
										// lyrics
										if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
										{
											MApp_MPlayer_EnableLRCLyric();
											//MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE,SW_SHOW);
										}
										else
										{
											DMP_DBG(printf("MApp_MPlayer_IsCurrentLRCLyricAvailable fail playing stage\n"););
										}
										#if ENABLE_MUSIC_EQ_MODE
										MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
										#endif
									}
									break;
								case E_MPLAYER_TYPE_TEXT:
									MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXT_DIR_PATH_STRING, SW_SHOW);
									MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW, SW_SHOW);
									if(bInfoShow)
									{
										_MApp_ACTdmp_Playback_ShowInfoWin(eMediaType);
									}
									else
									{
										MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
									}
									//
									MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
									break;
								default:
									break;
							}
							#if 0//DMP_UI_BMPSUBTITLE_EXCLUSIVE
							U8 u8GWinId = MApp_ZUI_API_QueryGWinID();
							if(u8GWinId == 0xFF)
							{
								MApp_ZUI_API_EmptyMessageQueue();
							}
							#endif
							#if DMP_UI_BMPSUBTITLE_EXCLUSIVE
							 // enable UI
							_MApp_ZUI_ACTdmp_RestoreGWINandFB();
							#endif //DMP_UI_BMPSUBTITLE_EXCLUSIVE

						}
						else
						{
							DMP_DBG(printf("    - UI state entered an unknown state! (%d)\n", MApp_DMP_GetDmpUiState()));
							MApp_MPlayer_Stop();
							MApp_MPlayer_StopMusic();
							MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
						}
					}
					
					if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
					MApp_ZUI_API_RestoreFocusCheckpoint();
				
					break;
        case E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE:
        DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE\n"));
        {
            m_u16PlayErrorNum = 0;
			/*if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
			{
				//_MApp_ACTdmp_Playback_ShowInfoWin(MApp_MPlayer_QueryCurrentMediaType());
				MApp_ZUI_API_StoreFocusCheckpoint();
			}*/

            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_MOVIE:
                {

                    if(_u16MovieTotalTime != 0xFFFF && _u16MovieTotalTime != 0)
                    {
                        U32 u32Percent = _u16MovieCurrentTime*100 /_u16MovieTotalTime;
		        if(u32Percent>100)
			    u32Percent=100;
                        MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
                    }
                    else if(_u16MovieTotalTime == 0)
                    {
                        MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                    }
                    else
                    {
                        MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                        DMP_DBG(printf("[Error] Get total time failed! (0x%lx)\n", _u16MovieTotalTime););
                    }
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);

                        memset((U8*)_stDmpPlayVar.stMovieInfo.MPlayerSubtitleBuf, 0, DMP_STRING_BUF_SIZE);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_SUBTITLE_PAGE, SW_HIDE);

                    // update movie info window - current time
                    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                    {
                        MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                    }
					 if(MApp_ZUI_GetActiveOSD() == E_OSD_DMP)//wht121129_2  add
					 {
	                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_HIDE);
	                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
					 }
                }
                #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                U8 u8GWinId = MApp_ZUI_API_QueryGWinID();
                if(u8GWinId == 0xFF)
                {
                    MApp_ZUI_API_EmptyMessageQueue();
                }
                #endif
				bPlayEndFlag = TRUE; //wht120818_1
                break;
                case E_MPLAYER_TYPE_MUSIC:
                    if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                    {
                        memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                        MApp_MPlayer_DisableLRCLyric();
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE,SW_HIDE);
                    }
					if(MApp_ZUI_GetActiveOSD() == E_OSD_DMP) //wht121129_2 add
					{
	                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_HIDE);
	                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
					}
                    break;
                default:
                    break;
            }
        }
		MApp_ZUI_API_RestoreFocusCheckpoint();
        break;
        case E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE:
        DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE\n"));
        {
            switch(MApp_MPlayer_QueryCurrentMediaType())
            {
                case E_MPLAYER_TYPE_PHOTO:
                case E_MPLAYER_TYPE_TEXT:
                    MApp_MPlayer_StopMusic();
                    break;
                case E_MPLAYER_TYPE_MOVIE:
                    break;
                case E_MPLAYER_TYPE_MUSIC:
					#if ENABLE_MUSIC_EQ_MODE
                    MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, SW_HIDE);
					#endif
                    break;
                default:
                    break;
            }
            U16 u16PlayingIdx = 0;
            if (!MApp_MPlayer_Change2TargetPath(MApp_MPlayer_QueryCurrentPlayingList()))
            {
                DMP_DBG(printf("MApp_MPlayer_Change2TargetPath fail EXIT\n");)
            }
            u16PlayingIdx = MApp_MPlayer_QueryCurrentPlayingFileIndex();
            MApp_MPlayer_SetCurrentPageIndex(u16PlayingIdx/NUM_OF_PHOTO_FILES_PER_PAGE);
            DMP_DBG(printf("\n### Current playing idx : %d\n", u16PlayingIdx););
            if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16PlayingIdx) != E_MPLAYER_RET_OK)
            {
                DMP_DBG(printf("MApp_MPlayer_SetCurrentFile fail 1\n"););
                MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 0);
                MApp_MPlayer_SetCurrentPageIndex(0);
            }
            msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
            if( MApp_DMP_GetDMPStat()==DMP_STATE_RETURN_FROM_MENU)
            {
                MApp_MPlayer_Stop();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                MApp_DMP_SetDmpUiState(DMP_UI_STATE_FILE_SELECT);

            }
            else
           {
            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
        	}
        }
        break;
        case E_MPLAYER_NOTIFY_TEXT_PREV_PAGE:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_TEXT_PREV_PAGE\n"));
            break;
        case E_MPLAYER_NOTIFY_TEXT_NEXT_PAGE:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_TEXT_NEXT_PAGE\n"));
            break;
        case E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL\n"));
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
          #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
            {
                MPlayerNotifyOneThumbnail *pThumb = (MPlayerNotifyOneThumbnail*)pInfo;
                if(!pThumb->bOK)
                {
                    _ThumbNOIdx = pThumb->u16FileIdx;
                    _ThumbNOIdx = _ThumbNOIdx + MApp_MPlayer_QueryCurrentPageIndex()*NUM_OF_PHOTO_FILES_PER_PAGE;
                    DMP_DBG(printf("_ThumbNOIdx %u\n",_ThumbNOIdx););
                    MApp_ZUI_API_InvalidateWindow((HWND)(_hwndListFileIcon[pThumb->u16FileIdx%NUM_OF_PHOTO_FILES_PER_PAGE] ));
                    _InsertQFlag = FALSE;
                }
                else
                {
                    _ThumbOKIdx = pThumb->u16FileIdx;
                    _ThumbOKIdx = _ThumbOKIdx + MApp_MPlayer_QueryCurrentPageIndex()*NUM_OF_PHOTO_FILES_PER_PAGE;
                    DMP_DBG(printf("_ThumbOKIdx ok %u\n",_ThumbOKIdx););
                    MApp_ZUI_API_InvalidateWindow((HWND)(_hwndListFileIcon[pThumb->u16FileIdx%NUM_OF_PHOTO_FILES_PER_PAGE] ));
                    _InsertQFlag = FALSE;
                }
            }
          #endif
            break;

        case E_MPLAYER_NOTIFY_END_OF_THUMBNAIL:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_THUMBNAIL\n"));
            MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
            if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY))
                && !MApp_ZUI_API_IsWindowVisible(HWND_DMP_FILE_PAGE_SUBMENU_GROUP)
                && !MApp_ZUI_API_IsWindowVisible(HWND_DMP_ALERT_WINDOW)
                && !MApp_ZUI_API_IsWindowVisible(HWND_DMP_BGM_FILE_SELECT_PAGE)
                && !MApp_ZUI_API_IsWindowVisible(HWND_DMP_RESUME_STOP_WINDOW)
              )
            {
                //_MApp_ACTdmp_ShowPreviewWin();
            }
            break;

        case E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE:
        DMP_DBG(printf("    - E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE\n"));
        {
            // thumbnail
            {
                if(MApp_DMP_GetDmpFlag()& DMP_FLAG_THUMBNAIL_PLAYING)
                {
                    return FALSE;
                }
            }
            enumMPlayerMediaType eMediaType = *(enumMPlayerMediaType *)pInfo;

            if(MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING
                || MApp_DMP_GetDmpFlag() & DMP_FLAG_THUMBNAIL_PLAYING)
            {
                DMP_DBG(printf("    - _MApp_DMP_ErrorHandling_PLAYING \n"));
/*
                if(_MApp_DMP_QueryTotalPlayListNum() == 1)
                {
                    DMP_DBG(printf("    - _MApp_DMP_ErrorHandling_GotoDefaultPage 1\n"));
                    MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
                    _MApp_DMP_ErrorHandling_GotoDefaultPage(eMediaType);
                    //    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FILE);
                }
*/
                m_u16PlayErrorNum++;
                if (MApp_MPlayer_QueryRepeatMode() ==E_MPLAYER_REPEAT_1)
                {
                    DMP_DBG(printf("    - _MApp_DMP_ErrorHandling_GotoDefaultPage: Repeat_1\n"));
                    MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
                    _MApp_DMP_ErrorHandling_GotoDefaultPage(eMediaType);
                    return FALSE;
                    //    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FILE);
                }
                else
                {// N files in the play list.
                    DMP_DBG(printf("[check] Play file error number = %d, Total Files : %d\n", m_u16PlayErrorNum, _MApp_DMP_QueryTotalPlayListNum()));
                    if(m_u16PlayErrorNum >= _MApp_DMP_QueryTotalPlayListNum())
                    {// All selected files are decoded error!
                        MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
                        if( MApp_DMP_GetDMPStat()==DMP_STATE_RETURN_FROM_MENU)
                        {
                            _MApp_DMP_ErrorHandling_GotoFileSelectPage(eMediaType);
                        }
                        else
                        {
                        _MApp_DMP_ErrorHandling_GotoDefaultPage(eMediaType);
                        }
                        DMP_DBG(printf(" All selected files are decoded error!\n"));
                        return FALSE;
                    }
                    if( eMediaType == E_MPLAYER_TYPE_PHOTO ) // Error at play photo
                    {
                        // Let MApp_mplayer.c decide what to do~
                        return TRUE; // Continue play
                        //return FALSE; // Stop play
                    }
                    else
                    {
                    DMP_DBG(printf("    - MApp_MPlayer_PlayNextFile()\n"));
                    MApp_MPlayer_PlayNextFile();
                    return TRUE;
                }
            }
            }
            else
            {//Error occured in default page - Preview Mode or BGM Mode(error occured in !MUSIC type)
                DMP_DBG(printf("    - _MApp_DMP_ErrorHandling_NOT playing \n"));
                MApp_MPlayer_StopPreview();

                switch(eMediaType)
                {
                    case E_MPLAYER_TYPE_MUSIC:
                        if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                        {
                            MApp_MPlayer_DisableLRCLyric();
                            memset((U8*)_stDmpPlayVar.stMusicInfo.MPlayerLyricBuf, 0, DMP_STRING_BUF_SIZE);
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE,SW_HIDE);
                        }
                        break;
                    case E_MPLAYER_TYPE_TEXT:
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW, SW_HIDE);
                        break;
                    default:
                        break;
                }
                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FILE);
				MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);//wht120424_5
            }
        }
            break;


        case E_MPLAYER_NOTIFY_PHOTO_INFO_OK:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_PHOTO_INFO_OK\n"));
#if(ENABLE_PHOTO_INFO_OK)
            _bPhotoInfoOK = TRUE;
#endif
            if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP))
            {
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_PHOTOINFO_INFO_GROUP);
            }
            break;
            #if (ENABLE_MPLAYER_MOVIE)
        case E_MPLAYER_NOTIFY_PLAY_NEXT_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_PLAY_NEXT_FILE\n"));
            #if ENABLE_LAST_MEMORY
                if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
                    {
                        //printf("<<<>>>111\n");
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
                        MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
                        //MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                    }

                    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                    {
                        _u8RecordInfoBarIdx = MOVIEINFO_NEXT;
                    }
                }
            #endif

            break;
        case E_MPLAYER_NOTIFY_PLAY_PREVIOUS_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_PLAY_PREVIOUS_FILE\n"));
            #if ENABLE_LAST_MEMORY
                if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                {
                    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
                    {
                        //printf("<<<>>>222\n");
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE,SW_HIDE);
                        MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
                        MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                    }

                    if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_INFO_PANE))
                    {
                        _u8RecordInfoBarIdx = MOVIEINFO_PREV;
                    }
                }
            #endif
            break;
            #endif
        case E_MPLAYER_NOTIFY_SETUP_DISPLAY:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_SETUP_DISPLAY\n"));
            {
                // hence while movie playing, press channel+-, the vdplayer need a little time to change program
                // so need to wait the E_MPLAYER_NOTIFY_SETUP_DISPLAY notify then get the correct text
                /*if (MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP))
                {
                    MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MOVIEINFO_INFO_GROUP);
                }*/
            }
            break;

    #if ENABLE_DVD
        case E_MPLAYER_NOTIFY_DVD_RESUME_NORMAL_PLAY:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_DVD_RESUME_NORMAL_PLAY\n"));
            if (MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_DVD)
            {
                MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PLAYBACK_INFOBAR_GROUP);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
            }
            break;
    #endif

    #if ENABLE_EMBEDDED_PHOTO_DISPLAY
        case E_MPLAYER_NOTIFY_BEFORE_EMBEDDED_PHOTO_DISPLAY:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_EMBEDDED_PHOTO_DISPLAY\n"));
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            {
                if (*(enumMusicPreviewState*)pInfo == E_MUSIC_PREVIEW_RUNNING)
                {
                    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
                    //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_SHOW);
                    //_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_FILE_PAGE_PREVIEW_FILENAME_STRING, TRUE);
                }
            }
            break;
        break;
        case E_MPLAYER_NOTIFY_END_OF_EMBEDDED_PHOTO_DISPLAY:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_EMBEDDED_PHOTO_DISPLAY\n"));
        break;
        case E_MPLAYER_NOTIFY_ERROR_OF_EMBEDDED_PHOTO_DISPLAY:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_ERROR_OF_EMBEDDED_PHOTO_DISPLAY\n"));
            {
                //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_PREVIEW_GROUP, SW_HIDE);
                //_MApp_ZUI_ACT_DMPMarqueeTextEnableAnimation(HWND_DMP_FILE_PAGE_PREVIEW_FILENAME_STRING, FALSE);
            }
        break;
    #endif

    #if ENABLE_COPY_SELECTED_FILES
        case E_MPLAYER_NOTIFY_BEFORE_COPY_ONE_FILE:
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_COPY_ONE_FILE, CopyIndex=%d\n", *(U16*)pInfo));
            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                _u16CopyDeleteFinishNum = *(U16*)pInfo;
                MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)MApp_MPlayer_QueryPasteFileStatus());
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                _MApp_ZUI_API_WindowProcOnIdle();
            }
            break;

        case E_MPLAYER_NOTIFY_END_OF_COPY_ONE_FILE:
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_COPY_ONE_FILE, CopyIndex=%d\n", *(U16*)pInfo));
            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                _u16CopyDeleteFinishNum = (*(U16*)pInfo)+1;
                MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)MApp_MPlayer_QueryPasteFileStatus());
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                _MApp_ZUI_API_WindowProcOnIdle();
            }
            break;
    #endif

        case E_MPLAYER_NOTIFY_END_OF_COPY_ALL_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_COPY_ALL_FILE\n"));

           if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
           {
                //MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                //_MApp_ZUI_API_WindowProcOnIdle();
                MsOS_DelayTask(1500);
            }

            _MApp_ACTdmp_HideProgressWin();

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;

        case E_MPLAYER_NOTIFY_ERROR_OF_COPY_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_ERROR_OF_COPY_FILE\n"));

            _MApp_ACTdmp_HideProgressWin();

            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_COPY_FILE_ERROR);
            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
            _MApp_ZUI_API_WindowProcOnIdle();
            MsOS_DelayTask(DMP_TIME_MS_INVALID_WIN);

            _MApp_ACTdmp_HideSubMenu();
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;

        case E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_COPY_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_COPY_FILE\n"));

            _MApp_ACTdmp_HideProgressWin();

            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FORMAT);
            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
            _MApp_ZUI_API_WindowProcOnIdle();
            MsOS_DelayTask(DMP_TIME_MS_INVALID_WIN);

            _MApp_ACTdmp_HideSubMenu();
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;

        case E_MPLAYER_NOTIFY_NO_ENOUGH_SPACE_OF_COPY_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_NO_ENOUGH_SPACE_OF_COPY_FILE\n"));

            _MApp_ACTdmp_HideProgressWin();

            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_NO_ENOUGH_SPACE);
            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
            _MApp_ZUI_API_WindowProcOnIdle();
            MsOS_DelayTask(DMP_TIME_MS_INVALID_WIN);

            _MApp_ACTdmp_HideSubMenu();
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;

        case E_MPLAYER_NOTIFY_COPY_USED_USB_REMOVE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_COPY_USED_USB_REMOVE\n"));
            break;

        case E_MPLAYER_NOTIFY_UPDATE_COPIED_FILE_SIZE:
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_UPDATE_COPIED_FILE_SIZE, size = %ld\n", *(U32*)pInfo));
            break;

#if ENABLE_DELETE_SELECTED_FILES
        case E_MPLAYER_NOTIFY_BEFORE_DELETE_ONE_FILE:
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_DELETE_ONE_FILE, Deletecount = %ld\n", *(U16*)pInfo));
            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                _u16CopyDeleteFinishNum = *(U16*)pInfo;
                MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)MApp_MPlayer_QueryDeleteFileStatus());
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                _MApp_ZUI_API_WindowProcOnIdle();
            }
            break;

        case E_MPLAYER_NOTIFY_END_OF_DELETE_ONE_FILE:
            if(pInfo == NULL)
            {
                MApp_Fatal_Error("pInfo can not be NULL!!!\n", __FUNCTION__);
                break;
            }
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_DELETE_ONE_FILE, Deletecount = %ld\n", *(U16*)pInfo));
            if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
            {
                _u16CopyDeleteFinishNum = *(U16*)pInfo;
                MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)MApp_MPlayer_QueryDeleteFileStatus());
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                _MApp_ZUI_API_WindowProcOnIdle();
            }
            break;

        case E_MPLAYER_NOTIFY_END_OF_DELETE_ALL_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_DELETE_ALL_FILE\n"));

           if (MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW))
           {
                //MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                //_MApp_ZUI_API_WindowProcOnIdle();
                MsOS_DelayTask(1500);
            }

            _MApp_ACTdmp_HideProgressWin();

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;

        case E_MPLAYER_NOTIFY_ERROR_OF_DELETE_FILE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_ERROR_OF_DELETE_FILE\n"));

            _MApp_ACTdmp_HideProgressWin();

            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_DELETE_FILE_ERROR);
            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
            _MApp_ZUI_API_WindowProcOnIdle();
            MsOS_DelayTask(DMP_TIME_MS_INVALID_WIN);

            _MApp_ACTdmp_HideSubMenu();
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;
#endif
        case E_MPLAYER_NOTIFY_DELETE_USED_USB_REMOVE:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_DELETE_USED_USB_REMOVE\n"));
            break;

        case E_MPLAYER_NOTIFY_BEFORE_FORMAT:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_BEFORE_FORMAT\n"));
            break;

        case E_MPLAYER_NOTIFY_END_OF_FORMAT:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_END_OF_FORMAT\n"));
            _MApp_ACTdmp_HideAlertWin();
            MApp_DMP_UiStateTransition(DMP_UI_STATE_MEDIA_SELECT);
            break;

        case E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_FORMAT:
            DMP_DBG(printf("    - E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_FORMAT\n"));

            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FORMAT);
            MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
            _MApp_ZUI_API_WindowProcOnIdle();
            MsOS_DelayTask(DMP_TIME_MS_INVALID_WIN);

            _MApp_ACTdmp_HideSubMenu();
            //MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_RED,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_DMP_FILE_PAGE_SUB_MENU_COPY_STATUS,SW_HIDE);

            MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
            break;

        default:
            DMP_DBG(printf("    - Unknown notify (%d)\n", (U16)eNotify));
            break;
    }
    return FALSE;
}

extern BOOLEAN _MApp_ZUI_API_WindowProcOnTimer(void);
void MApp_DMP_NotifyUiState(EN_DMP_UI_STATE enDmpUiState)
{
  #if EN_DMP_SEARCH_ALL
    if(enDmpUiState == DMP_UI_STATE_FILE_SELECT)
        MApp_DMP_SetDmpFlag(DMP_FLAG_BROWSER_ALL);
    else
        MApp_DMP_ClearDmpFlag(DMP_FLAG_BROWSER_ALL);
  #endif

    switch(enDmpUiState)
    {
        case DMP_UI_STATE_MEDIA_SELECT:
        #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            // enable UI
            _MApp_ZUI_ACTdmp_RestoreGWINandFB();
        #endif //DMP_UI_BMPSUBTITLE_EXCLUSIVE
            {
                enumMPlayerMediaType enMediaType = MApp_MPlayer_QueryCurrentMediaType();
                DMP_DBG(printf("DMP_UI_STATE_MEDIA_SELECT\n"););
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
		  		bIsDriveSelected = FALSE; 
                MApp_DMP_SetCurDrvIdxAndCalPageIdx(0); 
#endif
                _MApp_ACTdmp_HideAlertWin();
                _MApp_ACTdmp_ShowMediaTypePage();
				//>>wht120813_1
                if (MApp_MPlayer_QueryRepeatMode() != E_MPLAYER_REPEAT_ALL)
                {
                    MApp_MPlayer_SetRepeatMode(E_MPLAYER_REPEAT_ALL);
                }
				//<<wht120813_1
                switch(enMediaType)
                {
                    case E_MPLAYER_TYPE_PHOTO:
                        MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_PHOTO);
                        break;
                    case E_MPLAYER_TYPE_MUSIC:
                        MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_MUSIC);
                        break;
#if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                        MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_MOVIE);
                        break;
#endif
                        #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                        MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_TEXT);
                        break;
                        #endif
                    default:
                        MApp_ZUI_API_SetFocus(HWND_DMP_MEDIA_TYPE_MOVIE);
                        break;
                }
            }
            break;

        case DMP_UI_STATE_DRIVE_SELECT:
            {
            /* #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                {
                    _MApp_DMP_ThumbCopyRegion_Destroy();
                    MApp_MPlayer_LeaveThumbnailMode();
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
                    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
                }
            #endif
            #if ENABLE_ZOOM_MAP
                _MApp_ZUI_ACT_DMPCloseZoomMapWin();
            #endif
                DMP_DBG(printf("DMP_UI_STATE_DRIVE_SELECT\n"););
                //_MApp_ACTdmp_ShowDrivePage();    //move down

            #if ENABLE_USB_DEVICE_LIST
                if (MApp_ZUI_ACT_DMPGetIsDrvIdxByUser() == TRUE)
                {
                    MApp_DMP_SetCurDrvIdxAndCalPageIdx(MApp_ZUI_ACT_DMPGetCurDrvIdxByUser());
                    MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx()));

                    MApp_ZUI_ACT_DMPSetDrvIdxByUser(FALSE);
                }
                else
             #endif
                {
                    U8 i;
                    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
                    {
                        if(MApp_MPlayer_QueryCurrentDriveIndex() == MApp_DMP_GetDriveFromMappingTable(i))
                        {
                            MApp_DMP_SetCurDrvIdxAndCalPageIdx(i);
                        }
                    }
                }
				*/
                //_MApp_ACTdmp_ShowDrivePage();
				_MApp_ACTdmp_ShowFilePage();
				MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 0);
				MApp_ZUI_API_SetFocus(_hwndListFileItem[MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE)]);
               // U8 u8Idx = (MApp_DMP_GetCurDrvIdx()+1) % DMP_DRIVE_NUM_PER_PAGE;
                //MApp_ZUI_API_SetFocus(_hwndListDriveItem[u8Idx]);
            }
            break;

        case DMP_UI_STATE_FILE_SELECT:
            #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            // enable UI
            _MApp_ZUI_ACTdmp_RestoreGWINandFB();
			//MApp_MPlayer_GetAllFilesInCurDrive();
            #endif //DMP_UI_BMPSUBTITLE_EXCLUSIVE
            MApp_ZUI_API_EnableFullScreenRelease(FALSE);
            {
                DMP_DBG(printf("DMP_UI_STATE_FILE_SELECT\n"););
                _MApp_ACTdmp_ShowFilePage();

              #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL)
                _ThumbNOIdx = 0xFFFF;
                _ThumbOKIdx = 0xFFFF;
                _ThumbLoadPageFlag = TRUE;
                _InsertQFlag = TRUE;
                _ThumbInsertNum = 0;
                _MApp_DMP_ThumbCopyRegion_Create();
              #endif
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST//move drive page to file page
				if(!bIsDriveSelected)
				{
					DMP_DBG(printf(" ui notify drive not selected \n"));
					//U8 u8Idx = (MApp_DMP_GetCurDrvIdx()+1) % DMP_DRIVE_NUM_PER_PAGE;
					U8 u8Idx = MApp_DMP_GetCurDrvIdx() % DMP_DRIVE_NUM_PER_PAGE;
					MApp_ZUI_API_SetFocus(_hwndListFileItem[u8Idx]);			  		
					MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, u8Idx);
#if ENABLE_PROGRESS_BAR
					U32 u32Percent = 0; 
					u32Percent = (MApp_DMP_GetCurDrvIdx() + 1) * 100 / 
					MApp_MPlayer_QueryTotalFileNum();
					MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
					DMP_DBG(printf("u32Persent = %u\n", u32Percent));
					MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_PAGE_SELECT_PROGRESS_BAR);	
#endif
				}
				else
#endif
              	{
	                MApp_ZUI_API_SetFocus(_hwndListFileItem[MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE)]);
	                if( MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING_ERROR)
	                {
	                    DMP_DBG(printf("DMP_UI_STATE_FILE_SELECT playing error mode\n"););
	                    _MApp_ACTdmp_ShowAlertWin(_enDmpMsgType);
						//>>wht120807_1
						if((_enDmpMsgType == DMP_MSG_TYPE_UNSUPPORTED_FILE) || (_enDmpMsgType == DMP_MSG_TYPE_ALL_FILES_UNSUPPORTED))
							MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
						//<<wht120807_1
	                    // playing error mode
	                }
	                else if(MApp_DMP_IsFileTypeByIdx(MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
	                {
	                    //File type
	                    //_MApp_ACTdmp_ShowPreviewWin();
	                }
	//>>wht1203017_6
#if ENABLE_PROGRESS_BAR
					U32 u32Percent = 0; 
					u32Percent = (MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY) + 1) * 100 / 
					MApp_MPlayer_QueryTotalFileNum();
					MApp_ZUI_CTL_PercentProgressBar_SetPercentage(u32Percent);
					DMP_DBG(printf("u32Persent = %u\n", u32Percent));
					MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_PAGE_SELECT_PROGRESS_BAR);
#endif
	//<<wht1203017_6
              	}
            }
            break;
	#if PLAYLIST_BGM
        case DMP_UI_STATE_BGM_FILE_SELECT:
            #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            // enable UI
            _MApp_ZUI_ACTdmp_RestoreGWINandFB();
            #endif //DMP_UI_BMPSUBTITLE_EXCLUSIVE
            MApp_ZUI_API_EnableFullScreenRelease(FALSE);
            {
                DMP_DBG(printf("DMP_UI_STATE_BGM_FILE_SELECT\n"););
                _MApp_ACTdmp_ShowBgmFilePage();

              #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
                _ThumbNOIdx = 0xFFFF;
                _ThumbOKIdx = 0xFFFF;
                _ThumbLoadPageFlag = TRUE;
                _InsertQFlag = TRUE;
                _ThumbInsertNum = 0;
                _MApp_DMP_ThumbCopyRegion_Create();
              #endif

                MApp_ZUI_API_SetFocus(_hwndBgmListFileItem[MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE)]);
                if( MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING_ERROR)
                {
                    DMP_DBG(printf("DMP_UI_STATE_BGM_FILE_SELECT playing error mode\n"););
                    _MApp_ACTdmp_ShowAlertWin(_enDmpMsgType);
                    // playing error mode
                }
            }
            break;
    #endif
        case DMP_UI_STATE_LOADING:
            {
                #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL)
                _MApp_DMP_ThumbCopyRegion_Destroy();
                MApp_MPlayer_LeaveThumbnailMode();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
                MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
                #endif

                if( MApp_DMP_GetDmpFlag() & DMP_FLAG_MEDIA_FILE_PLAYING_ERROR)
                {
                    DMP_DBG(printf("DMP_UI_STATE_LOADING playing error mode\n"););
                    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);
                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_FILE);
					MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);//wht120424_5
                    // playing error mode
                }
                else
                {
                    // normal mode
                    DMP_DBG(printf("DMP_UI_STATE_LOADING normal mode\n"););
                   // MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);               ////wht120715_1
                  //  MApp_ZUI_API_ShowWindow(HWND_DMP_ROOT_TRANSPARENT_BG, SW_SHOW);  //wht120715_1
                    _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_LOADING);
                    if(MApp_DMP_GetDmpFlag() & DMP_FLAG_BGM_MODE)
                    {
                        MApp_MPlayer_StopMusic();
                        MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
                    }					
                    MApp_MPlayer_Play();
                }
            }
            break;


        case DMP_UI_STATE_PLAYING_STAGE:
            //MApp_ZUI_API_EnableFullScreenRelease(FALSE);

            {
                DMP_DBG(printf("hahah DMP_UI_STATE_PLAYING_STAGE\n"););
                if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_ALERT_WINDOW))
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_ALERT_WINDOW,SW_HIDE);
                }
                MApp_DMP_SetDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
                _enDmpPlayStrType =_enDmpPlayIconType = PLAY_MODE_ICON_PLAY;
                switch(MApp_MPlayer_QueryCurrentMediaType())
                {

#if (ENABLE_MPLAYER_MOVIE)
                    case E_MPLAYER_TYPE_MOVIE:
                    {
                    #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                        bUIexist = TRUE;
                    #endif
                        // case NEW_notify
                        // patch the focus, because the "last memory" feature
                    #if ENABLE_LAST_MEMORY
                        if(MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
                        {
                            MApp_ZUI_API_StoreFocusCheckpoint();

                            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, SW_SHOW);
                            MApp_ZUI_API_RestoreFocusCheckpoint();
                            _MApp_ZUI_API_WindowProcOnTimer();
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN, DMP_TIME_MS_MOVIERESUME);
                            MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);

                        }
                        else
                        {
                        #if ENABLE_DMP_MINI_MENU
                            if(MApp_MPlayer_IsMoviePlaying())
                            {
                                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                                MApp_ZUI_ACT_ShutdownOSD();
                                MApp_DMP_GotoDMPMiniMenu();
                            }
                            else
                        #endif
                            {
                                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                                _MApp_ZUI_API_WindowProcOnTimer();
                                MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                            }
                        }
                    #else // ENABLE_LAST_MEMORY
                        MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        _MApp_ZUI_API_WindowProcOnTimer();
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                    #endif //ENABLE_LAST_MEMORY

                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MovieInfoBarTable[MOVIEINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        _MApp_ACTdmp_MovieCancelRepeatAB();

                        //_MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_MOVIE);

                        if(MApp_MPlayer_GetMovieAudioCodecSupported() == FALSE)
                        {
                            if(!MApp_ZUI_API_IsWindowVisible(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE))
                            {
                                DMP_DBG(printf(">>>>>>>>>>>>>  Unsupport audio\n"););
                                _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_UNSUPPORTED_AUDIO_FILE);
                                MApp_ZUI_API_SetTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN, DMP_TIME_MS_INVALID_WIN);
                            }
                        }

                        MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                        MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                    #if DMP_UI_BMPSUBTITLE_EXCLUSIVE
                        bUIexist = FALSE;
                    #endif
                    }
                    break;
#endif // ENABLE_MPLAYER_MOVIE

                    case E_MPLAYER_TYPE_PHOTO:
                    {
                        if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_PAUSE)
                        {
                            MApp_MPlayer_PhotoChangePlayMode(E_MPLAYER_PHOTO_NORMAL);
                        }
                        else if(MApp_MPlayer_QueryPhotoPlayMode() == E_MPLAYER_PHOTO_NORMAL)
                        {
                            //do nothing;
                        }

                        DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_PhotoInfoBarTable[PHOTOINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                        _MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_PHOTO);
                    }
                    break;

                    // because there is no other screen while playing music
                    // hence show the info page for music start
                    case E_MPLAYER_TYPE_MUSIC:
                    {
                        _MApp_ACTdmp_MusicCancelRepeatAB();

                        if(MApp_MPlayer_QueryMusicPlayMode() == E_MPLAYER_MUSIC_NORMAL)
                        {
                            // do nothing
                        }
                        else // some FF FB ...
                        {
                            MApp_MPlayer_MusicChangePlayMode(E_MPLAYER_MUSIC_NORMAL);
                        }

                        DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_BMP_IDX] = E_BMP_DMP_BUTTON_ICON_PAUSE;IsPause = 1 ;
                        DMP_MusicInfoBarTable[MUSICINFO_PLAY_PAUSE][INFOBAR_STR_IDX] = en_str_Pause;
                        MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN, DMP_TIME_MS_PLAY_STATUS_WIN);
                        MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
                        _MApp_ACTdmp_Playback_ShowInfoWin(E_MPLAYER_TYPE_MUSIC);
                        MApp_ZUI_CTL_PercentProgressBar_SetPercentage(0);
                        MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_PAGE_TIME_GROUP);
                        if(MApp_MPlayer_IsCurrentLRCLyricAvailable() == E_MPLAYER_RET_OK)
                        {
                            MApp_MPlayer_EnableLRCLyric();
                            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_LYRIC_PAGE, SW_SHOW);
                        }
                        else
                        {
                            DMP_DBG(printf("MApp_MPlayer_IsCurrentLRCLyricAvailable lyric fail\n"););
                        }

                        // EQ
                        //MApp_ZUI_API_SetTimer(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP, DMP_TIMER_EQ_PLAY, DMP_TIME_MS_EQ_PLAY);
                    }
                    break;

                  #if (ENABLE_MPLAYER_TEXT)
                    case E_MPLAYER_TYPE_TEXT:
                    {
                        MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW,SW_SHOW);
						MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW_TEXT, SW_SHOW);
                        MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
                        MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_TEXT_FULL_WINDOW);
                    }
                    break;
                  #endif

                    default:
                        break;
                }
            }

            break;
    }
}

////////////////////////////////////////////
//  if( isPhotoFile)
//  {
//      if( decode finish)
//      {
//          if( have showed)
//          {
//              do nothing
//          }
//          else
//          {
//              show on screen
//          }
//      }
//      else
//      {
//          starting decoding
//          show default directory bitmap
//      }
//  }
//  else
//  {
//    show directory bitmap or "return arrow" bitmap
//  }
//
//  // problem : if UI doesnt move; middleware will send notify to UI?
//
////////////////////////////////////////////
S32 MApp_ZUI_ACT_DmpFileSelectThumbnailWinProc(HWND hwnd, PMSG msg)
{
#if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
    if(( DMP_PHOTO_THUMBNAIL&&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO))
        #if (ENABLE_MPLAYER_MOVIE)
        || (DMP_MOVIE_THUMBNAIL&&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE))
        #endif
     || (DMP_MUSIC_THUMBNAIL&&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC))
    )
    {
        switch(msg->message)
        {
            case MSG_PAINT:
            {
                if(_CopyFbId == 0xFF)
                {
                    return DYNAMICBITMAP_WINPROC(hwnd, msg);
                }
                PAINT_PARAM * param = (PAINT_PARAM *)msg->wParam;
                U32 i;
                for(i = 0; i < NUM_OF_PHOTO_FILES_PER_PAGE; i++)
                {
                    if (_hwndListFileIcon[i] == hwnd)
                        break;
                }
                U16 u16FileIdx = i + MApp_MPlayer_QueryCurrentPageIndex()*NUM_OF_PHOTO_FILES_PER_PAGE;

                if(!(MApp_DMP_GetDmpFlag()& DMP_FLAG_THUMBNAIL_MODE))
                {
                    GOP_GwinFBAttr fbAttr;
                    MApi_GOP_GWIN_GetFBInfo(param->dc.u8FbID, &fbAttr);
                    if(MApp_MPlayer_EnterThumbnailMode(&fbAttr) == E_MPLAYER_RET_OK)
                    {
                        DMP_DBG(printf("MApp_MPlayer_EnterThumbnailMode success\n"););
                        //MApp_MPlayer_BeginThumbnail();
                        _InsertQFlag = TRUE;
                    }
                    /*
                    GRAPHIC_DC *dc = MApp_ZUI_API_GetScreenDC();
                    GOP_GwinFBAttr FbAttr;
                    MApi_GOP_GWIN_GetFBInfo(dc->u8FbID, &FbAttr);
                    MApp_MPlayer_SetZUIFbAttr(FbAttr);
                    */
                    MApp_DMP_SetDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
                }
                if((_ThumbNOIdx != 0xFFFF)&&(_ThumbNOIdx==u16FileIdx))
                {
                    DMP_DBG(printf("decode fail %d\n",_ThumbNOIdx););
                    MApp_ZUI_CTL_DynamicBitmapWinProc(hwnd, msg);

                    GRAPHIC_DC *dc = MApp_ZUI_API_GetBufferDC();
                    //printf("[Clone] %d item to tmp buffer.\n", u8Idx);
                    _MApp_DMP_ThumbCopyRegion_CloneRect(dc->u8FbID, param->rect);
                    _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                    _ThumbNOIdx = 0xFFFF;
                    return 0;
                }
                if(! MApp_DMP_IsFileTypeByIdx(u16FileIdx) ) // not a photo
                {
                    break;
                }
                else // is photo or movie file
                {
                    if(_InsertQFlag)
                    {
                        if(_ThumbLoadPageFlag)
                        {
                            if( !(MApp_DMP_GetDmpFlag()&DMP_FLAG_THUMBNAIL_PLAYING))
                            {
                                MApp_DMP_SetDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
                            }
                            DMP_DBG(printf("A. insert Queue (%d)\n", u16FileIdx););
                            MApp_MPlayer_DrawThumbnailByIdx(u16FileIdx%NUM_OF_PHOTO_FILES_PER_PAGE);
                            _ThumbInsertNum++;

                            if(_ThumbInsertNum == NUM_OF_PHOTO_FILES_PER_PAGE)
                            {
                                _ThumbLoadPageFlag = FALSE;
#if (ENABLE_ATSC_TTS)
                                MApp_TTSControlSetInputText(MApp_ZUI_API_GetU16String(_ThumbInsertNum), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetU16String(_ThumbInsertNum)));
                                MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Main_Menu_Item), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Main_Menu_Item)));
                                MApp_TTSControlSetOn(TRUE);
#endif
                            }
                            if((u16FileIdx%NUM_OF_PHOTO_FILES_PER_PAGE) == NUM_OF_PHOTO_FILES_PER_PAGE-1)
                            {
                                _ThumbLoadPageFlag = FALSE;
#if (ENABLE_ATSC_TTS)
                                MApp_TTSControlSetInputText(MApp_ZUI_API_GetU16String(_ThumbInsertNum), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetU16String(_ThumbInsertNum)));
                                MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Main_Menu_Item), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Main_Menu_Item)));
                                MApp_TTSControlSetOn(TRUE);
#endif
                            }
                            if(MApp_MPlayer_QueryCurrentPageIndex()+1 ==MApp_MPlayer_QueryTotalPages()) // last page
                            {
                                if(u16FileIdx == MApp_MPlayer_QueryTotalFileNum()-1 )
                                {
                                    _ThumbLoadPageFlag = FALSE;
#if (ENABLE_ATSC_TTS)
                                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetU16String(_ThumbInsertNum), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetU16String(_ThumbInsertNum)));
                                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Main_Menu_Item), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Main_Menu_Item)));
                                    MApp_TTSControlSetOn(TRUE);
#endif
                                }
                            }
                        }
                        else
                        {
                            DMP_DBG(printf("B. Paste to (%d)\n",u16FileIdx););
                            _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                        }
                    }
                    else if( !_InsertQFlag &&(_ThumbOKIdx != 0xFFFF)&&(_ThumbOKIdx==u16FileIdx))// decode finish
                    {
                        //printf("[Clone] %d item to tmp buffer.\n", u8Idx);
                        _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                        //_InsertQFlag = TRUE;
                        _ThumbLoadPageFlag = FALSE;
                        DMP_DBG(printf(" decode finish %u\n",u16FileIdx););
                        _ThumbOKIdx = 0xFFFF;
                        //MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_SELECT_PAGE);
                    }
                    else
                    {
                        //GRAPHIC_DC *dc = MApp_ZUI_API_GetScreenDC();
                        //printf("[Clone] %d item to tmp buffer.\n", u8Idx);
                        //_MApp_DMP_ThumbCopyRegion_CloneRect(dc->u8FbID, param->rect);
                        _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                        //_InsertQFlag = TRUE;
                        _ThumbLoadPageFlag = FALSE;
                        DMP_DBG(printf(" decode haha %u\n",u16FileIdx););
                    }
                    return 0;
                }
            }

            default:
                break;
        }
    }
#endif
    return DYNAMICBITMAP_WINPROC(hwnd, msg);
}
#if PLAYLIST_BGM
S32 MApp_ZUI_ACT_DmpBgmFileSelectThumbnailWinProc(HWND hwnd, PMSG msg)
{
#if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
    if(( DMP_PHOTO_THUMBNAIL&&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO))
        || (DMP_MOVIE_THUMBNAIL&&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE))
     || (DMP_MUSIC_THUMBNAIL&&(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC))
    )
    {
        switch(msg->message)
        {
            case MSG_PAINT:
            {
                if(_CopyFbId == 0xFF)
                {
                    return DYNAMICBITMAP_WINPROC(hwnd, msg);
                }
                PAINT_PARAM * param = (PAINT_PARAM *)msg->wParam;
                U32 i;
                for(i = 0; i < NUM_OF_PHOTO_FILES_PER_PAGE; i++)
                {
                    if (_hwndBgmListFileIcon[i] == hwnd)
                        break;
                }
                U16 u16FileIdx = i + MApp_MPlayer_QueryCurrentPageIndex()*NUM_OF_PHOTO_FILES_PER_PAGE;

                if(!(MApp_DMP_GetDmpFlag()& DMP_FLAG_THUMBNAIL_MODE))
                {
                    GOP_GwinFBAttr fbAttr;
                    MApi_GOP_GWIN_GetFBInfo(param->dc.u8FbID, &fbAttr);
                    if(MApp_MPlayer_EnterThumbnailMode(&fbAttr) == E_MPLAYER_RET_OK)
                    {
                        DMP_DBG(printf("MApp_MPlayer_EnterThumbnailMode success\n"););
                        //MApp_MPlayer_BeginThumbnail();
                        _InsertQFlag = TRUE;
                    }
                    /*
                    GRAPHIC_DC *dc = MApp_ZUI_API_GetScreenDC();
                    GOP_GwinFBAttr FbAttr;
                    MApi_GOP_GWIN_GetFBInfo(dc->u8FbID, &FbAttr);
                    MApp_MPlayer_SetZUIFbAttr(FbAttr);
                    */
                    MApp_DMP_SetDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
                }
                if((_ThumbNOIdx != 0xFFFF)&&(_ThumbNOIdx==u16FileIdx))
                {
                    DMP_DBG(printf("decode fail %d\n",_ThumbNOIdx););
                    MApp_ZUI_CTL_DynamicBitmapWinProc(hwnd, msg);

                    GRAPHIC_DC *dc = MApp_ZUI_API_GetBufferDC();
                    //printf("[Clone] %d item to tmp buffer.\n", u8Idx);
                    _MApp_DMP_ThumbCopyRegion_CloneRect(dc->u8FbID, param->rect);
                    _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                    _ThumbNOIdx = 0xFFFF;
                    return 0;
                }
                if(! MApp_DMP_IsFileTypeByIdx(u16FileIdx) ) // not a photo
                {
                    break;
                }
                else // is photo or movie file
                {
                    if(_InsertQFlag)
                    {
                        if(_ThumbLoadPageFlag)
                        {
                            if( !(MApp_DMP_GetDmpFlag()&DMP_FLAG_THUMBNAIL_PLAYING))
                            {
                                MApp_DMP_SetDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
                            }
                            DMP_DBG(printf("A. insert Queue (%d)\n", u16FileIdx););
                            MApp_MPlayer_DrawThumbnailByIdx(u16FileIdx%NUM_OF_PHOTO_FILES_PER_PAGE);
                            _ThumbInsertNum++;

                            if(_ThumbInsertNum == NUM_OF_PHOTO_FILES_PER_PAGE)
                            {
                                _ThumbLoadPageFlag = FALSE;
                            }
                            if((u16FileIdx%NUM_OF_PHOTO_FILES_PER_PAGE) == NUM_OF_PHOTO_FILES_PER_PAGE-1)
                            {
                                _ThumbLoadPageFlag = FALSE;
                            }
                            if(MApp_MPlayer_QueryCurrentPageIndex()+1 ==MApp_MPlayer_QueryTotalPages()) // last page
                            {
                                if(u16FileIdx == MApp_MPlayer_QueryTotalFileNum()-1 )
                                {
                                    _ThumbLoadPageFlag = FALSE;
                                }
                            }
                        }
                        else
                        {
                            DMP_DBG(printf("B. Paste to (%d)\n",u16FileIdx););
                            _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                        }
                    }
                    else if( !_InsertQFlag &&(_ThumbOKIdx != 0xFFFF)&&(_ThumbOKIdx==u16FileIdx))// decode finish
                    {
                        GRAPHIC_DC *dc = MApp_ZUI_API_GetScreenDC();
                        //printf("[Clone] %d item to tmp buffer.\n", u8Idx);
                        _MApp_DMP_ThumbCopyRegion_CloneRect(dc->u8FbID, param->rect);
                        _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                        //_InsertQFlag = TRUE;
                        _ThumbLoadPageFlag = FALSE;
                        DMP_DBG(printf(" decode finish %u\n",u16FileIdx););
                        _ThumbOKIdx = 0xFFFF;
                        //MApp_ZUI_API_InvalidateWindow(HWND_DMP_FILE_SELECT_PAGE);
                    }
                    else
                    {
                        //GRAPHIC_DC *dc = MApp_ZUI_API_GetScreenDC();
                        //printf("[Clone] %d item to tmp buffer.\n", u8Idx);
                        //_MApp_DMP_ThumbCopyRegion_CloneRect(dc->u8FbID, param->rect);
                        _MApp_DMP_ThumbCopyRegion_PasteTo(param->rect);
                        //_InsertQFlag = TRUE;
                        _ThumbLoadPageFlag = FALSE;
                        DMP_DBG(printf(" decode haha %u\n",u16FileIdx););
                    }
                    return 0;
                }
            }

            default:
                break;
        }
    }
#endif
    return DYNAMICBITMAP_WINPROC(hwnd, msg);
}
#else
S32 MApp_ZUI_ACT_DmpBgmFileSelectThumbnailWinProc(HWND hwnd, PMSG msg)
{
    return DYNAMICBITMAP_WINPROC(hwnd, msg);
}
#endif

S32 MApp_ZUI_ACT_DmpProgressWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_FILE_SELECT)
            {
                U16 u16Percentage=0;
            #if ENABLE_DELETE_SELECTED_FILES
                if (MApp_MPlayer_IsDeleting() == TRUE)
                {
                    u16Percentage = MApp_MPlayer_QueryDeleteFileStatus();
                }
            #endif
            #if ENABLE_COPY_SELECTED_FILES
                if (MApp_MPlayer_IsCopying() == TRUE)
                {
                    u16Percentage = MApp_MPlayer_QueryPasteFileStatus();
                }
            #endif

                if(u16Percentage >= 100)
                {
                    _MApp_ACTdmp_HideProgressWin();

                    MApp_DMP_UiStateTransition(DMP_UI_STATE_FILE_SELECT);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_FILE_SELECT_PAGE);
                }
                else
                {
                    MApp_ZUI_API_ResetTimer(HWND_DMP_PROGRESS_WINDOW, DMP_TIMER_PROGRESS_WIN);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_DMP_PROGRESS_WINDOW);
                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)u16Percentage);
                }
            }
        #if 0 //Implement code when playback is finished
          #if (ENABLE_POWERON_MUSIC)
            else if(MApp_DMP_GetDmpUiState() == DMP_UI_STATE_PLAYING_STAGE)
            {
                U32 u32Percent = 0;
                if(MApp_Music_GetRecordingTime() >= USER_MP3_CAPTURE_TIMEOUT)
                {
                    MApp_ZUI_API_KillTimer(HWND_MEDIA_PLAYER_PROGRESS_DIALOG, MPLAYER_PROGRESS_BAR_TIMER);
                    MApp_ZUI_API_ShowWindow(HWND_MEDIA_PLAYER_PROGRESS_DIALOG, SW_HIDE);
                    MApp_ZUI_API_RestoreFocusCheckpoint();
                }
                else
                {
                    u32Percent = MApp_Music_GetRecordingTime()/(USER_MP3_CAPTURE_TIMEOUT/100);
                    MApp_ZUI_API_ResetTimer(HWND_MEDIA_PLAYER_PROGRESS_DIALOG, MPLAYER_PROGRESS_BAR_TIMER);
                    MApp_ZUI_API_InvalidateAllSuccessors(HWND_MEDIA_PLAYER_PROGRESS_DIALOG);
                    MApp_ZUI_CTL_PercentProgressBar_SetPercentage((U8)u32Percent);
                }
            }
          #endif
        #endif
            break;

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_DmpPlayStatusWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            DMP_DBG(printf("\nRun MApp_ZUI_ACT_DmpPlayStatusWinProc(,)\n"));
#if ENABLE_DRM
            if (msg->wParam == DMP_TIMER_PLAY_STATUS_WIN)
            {
                _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_MAX;
                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_HIDE);
            }
            else if (msg->wParam == DMP_TIMER_PREV_BUTTON_CLICK_WIN)
            {
                // 1. Cancel Repeat AB Mode
                if(MApp_DMP_GetDmpFlag()& DMP_FLAG_MOVIE_REPEATAB_MODE)
                {
                    _MApp_ACTdmp_MovieCancelRepeatAB();
                    //    MApp_ZUI_API_ShowWindow(HWND_DMP_MOVIE_INFO_ICON_ADVENCE_GROUP, SW_SHOW);
                }
                // 2. Disable trick play --> Normal play
                if(MApp_MPlayer_QueryMoviePlayMode() != E_MPLAYER_MOVIE_NORMAL)
                {
                    MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP,SW_HIDE);
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                }
                //MApp_MPlayer_SetPlayPosition(0);
                MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PREV_BUTTON_CLICK_WIN);
            }
#else
            _enDmpPlayIconType = _enDmpPlayStrType = PLAY_MODE_ICON_MAX;
            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_STATUS_GROUP, DMP_TIMER_PLAY_STATUS_WIN);
            MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_STATUS_GROUP, SW_HIDE);
#endif
            break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}
S32 MApp_ZUI_ACT_DmpAlertWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            DMP_DBG(printf("\nRun MApp_ZUI_ACT_DmpInvalidWinProc(,)\n"));
            MApp_ZUI_API_KillTimer(HWND_DMP_ALERT_WINDOW, DMP_TIMER_INVALID_WIN);
            MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_ALERT_EXIT);
            break;

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

static void _MApp_ACTdmp_EqPlay(void)
{
    static U8 eq_bar[10] = {0};
    U8 ran_bar_num, i, j;
    srand(msAPI_Timer_GetTime0());
    for(i = 0; i < 10; i++)
    {
        ran_bar_num = rand() % 10;
        j = eq_bar[i];
        U8 k = i * 10;
        if(ran_bar_num > eq_bar[i])
        {
            for(j = 0; j < ran_bar_num; j++)
                MApp_ZUI_API_ShowWindow((HWND_DMP_PLAYBACK_MUSIC_EQ_BAR_00 + k + j), SW_SHOW);
        }
        else if(ran_bar_num < eq_bar[i])
        {
            for(; j > ran_bar_num; j--)
                MApp_ZUI_API_ShowWindow((HWND_DMP_PLAYBACK_MUSIC_EQ_BAR_00 + k + j), SW_HIDE);
        }
        eq_bar[i] = ran_bar_num;
    }
    //MApp_ZUI_API_InvalidateWindow(HWND_DMP_PLAYBACK_MUSIC_EQ_GROUP);
}

S32 MApp_ZUI_ACT_DmpEqPlayWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            _MApp_ACTdmp_EqPlay();
            break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_DmpPreviewWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
            MApp_ZUI_API_SetTimer(hwnd, DMP_TIMER_PREVIEW_WIN, DMP_TIME_MS_PREVIEW_WIN);
            break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_DMPMovieResumeWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_MOVIERESUME_NO);
            MApp_ZUI_API_KillTimer(HWND_DMP_PLAYBACK_MOVIERESUME_PAGE, DMP_TIMER_MOVIERESUME_WIN);
            break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

S32 MApp_ZUI_ACT_DMPResumeStopWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_TIMER:
            MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_RESUMESTOP_NO);
            MApp_ZUI_API_KillTimer(hwnd, DMP_TIMER_RESUMESTOP_WIN);
            break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

#if PLAYLIST_BGM
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryDMPStatus(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_DMP_PLAYBACK_BGMINFO_INFO_ONOFF_ITEM:
            return EN_DL_STATE_NORMAL;

        case HWND_DMP_PLAYBACK_BGMINFO_INFO_REPEAT_ITEM:
        case HWND_DMP_PLAYBACK_BGMINFO_INFO_SELECT_ITEM:
        case HWND_DMP_PLAYBACK_BGMINFO_INFO_NEXT_ITEM:
        case HWND_DMP_PLAYBACK_BGMINFO_INFO_PREV_ITEM:
        {
            if(m_bBGMOn == TRUE)
                return EN_DL_STATE_NORMAL;
            else
                return EN_DL_STATE_DISABLED;
        }
        break;

        default:
            return EN_DL_STATE_NORMAL;
    }
}
#endif
U8 MApp_ZUI_ACT_GetCurrentUARTMode(void)
{
    U8 _u8CurrentUART = (U8)mdrv_uart_get_connection(E_UART_PORT0);
    return _u8CurrentUART;
}

#if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
void MApp_ZUI_ACT_ExitThumbnailMode(void)
{
    _MApp_DMP_ThumbCopyRegion_Destroy();
    MApp_MPlayer_LeaveThumbnailMode();
    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_MODE);
    MApp_DMP_ClearDmpFlag(DMP_FLAG_THUMBNAIL_PLAYING);
}
#endif

BOOLEAN MApp_UiMediaPlayer_IsSubtitleEnabled(void)
{
    return !(_stDmpPlayVar.stMovieInfo.bSubtitleOff);
}


void MApp_ZUI_ACT_DmpGotoStandby(void)
{
       MApp_DMP_SetDMPStat(DMP_STATE_GOTO_STANDBY);
       if(MApp_MPlayer_IsMediaFileInPlaying())
       {
           MApp_MPlayer_Stop();
           MApp_MPlayer_StopMusic();
       }
       MApp_MPlayer_ExitMediaPlayer();
       MApp_ZUI_ACT_TerminateDmp();
    #if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
      _MApp_DMP_ThumbCopyRegion_Destroy();
    #endif
    #if ENABLE_ZOOM_MAP
      _MApp_ZUI_ACT_DMPCloseZoomMapWin();
    #endif
}

static void _MApp_ZUI_ACT_DmpRefreshPlayList(void)
{
    U16 u16Idx;
    enumMPlayerMediaType eMediaType;

    for(eMediaType = E_MPLAYER_TYPE_PHOTO ; eMediaType < E_MPLAYER_TYPE_NUM ; eMediaType++)
    {
        U16 u16PlayListNum = MApp_MPlayer_QuerySelectedFileNum(eMediaType);

        for(u16Idx = 0 ; u16Idx < u16PlayListNum ; u16Idx++)
        {
            if(!MApp_MPlayer_QueryPlayListFileAvailable(eMediaType, (u16PlayListNum-1)-u16Idx))
            {
                MApp_MPlayer_RemoveFileFromPlayList(eMediaType, (u16PlayListNum-1)-u16Idx, TRUE);
                DMP_DBG(printf("Delete Playlist, eMediaType: %d, Idx : %d\n", eMediaType, (u16PlayListNum-1)-u16Idx));
            }
            else
            {
                DMP_DBG(printf("Save Playlist, eMediaType: %d, Idx : %d\n", eMediaType, (u16PlayListNum-1)-u16Idx));
            }
        }
    }
}

#endif //ENABLE_DMP

#undef MAPP_ZUI_ACTDMP_C
