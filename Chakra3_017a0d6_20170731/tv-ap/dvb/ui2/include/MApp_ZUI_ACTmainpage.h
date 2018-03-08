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

#ifndef _MAPP_ZUI_ACTMAINPAGE_H
#define _MAPP_ZUI_ACTMAINPAGE_H
//#include "msAPI_CEC.h"

#include "MApp_ZUI_APItables.h"
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef MAPP_ZUI_ACTMAINPAGE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
typedef enum _VCHIP_PAGE_TYPE
{
    EN_VCHIP_MPAA,
    EN_VCHIP_CANADAENG,
    EN_VCHIP_CANADAFRE
}VCHIP_PAGE_TYPE;

INTERFACE VCHIP_PAGE_TYPE g_vchipPageType;
#endif

#if(ENABLE_ATSC)  // The following items from Chakra2_ATSC MApp_ZUI_ACTmainpage.h
#define MAX_NUM_OF_SRV_ITEM                 10
#define MAX_NUM_OF_RRT_ITEM                 10
#define MAX_NUM_OF_CHL_ITEM                 10 //max item number of channel lock page
#define MAX_NUM_OF_DIM_ITEM                 10 //max item number of channel lock page
INTERFACE BOOLEAN bChannelListType; //0:favorite list, 1:Show/Hide list
#define TOTAL_DIM_ITEM_NUM (stGenSettingVchipRegion5.u8NoDimension)
#define RRT_ITEM_NUM_IN_CUR_DIM (stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u8Values_Defined+1) //+1: ALL

#if ENABLE_ATSC_MENU_UI
typedef enum _VCHIP_PAGE_TYPE
{
    EN_VCHIP_MPAA,
    EN_VCHIP_CANADAENG,
    EN_VCHIP_CANADAFRE
}VCHIP_PAGE_TYPE;

INTERFACE VCHIP_PAGE_TYPE g_vchipPageType;
#endif

INTERFACE BOOLEAN MApp_ZUI_ACT_MainMenuCurDimRRTIsAllRating(U8 u8CurDimension);
#endif


INTERFACE E_UI_INPUT_SOURCE MApp_ZUI_ACT_GetAppItemSource(int APP);
INTERFACE U16 MApp_ZUI_ACT_GetAppItemString(int APP);

#if ENABLE_TTSTEST_FROM_USB
#define TTSTest_DBG(x)          x

typedef enum
{
    EN_TTSTEST_PAUSE,       //PAUSE
    EN_TTSTEST_PLAY,        //PLAY
    EN_TTSTEST_PLAY_MODE_NUM,
} enumTTSTestPlayMode;

INTERFACE BOOLEAN bIsAutoTestTTS;
INTERFACE void MApp_ZUI_ACT_QuaryTTSTestArray(void);
INTERFACE U8 *MApp_ZUI_ACT_GetTTSTestString(void);
INTERFACE U8 *MApp_ZUI_ACT_GetTTSStrEngTransl(void);
INTERFACE void MApp_ZUI_ACT_AutoCycleTTSTest(void);
INTERFACE enumTTSTestPlayMode MApp_ZUI_ACT_QueryTTSTestPlayMode(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_CheckTTSTestTXT(void);
#endif

typedef enum _COMMON_DLG_MODE
{
    EN_COMMON_DLG_MODE_INVALID,
    EN_COMMON_DLG_MODE_FACTORY_RESET,
    EN_COMMON_DLG_MODE_FACTORY_RESET_CONFIRM,
    EN_COMMON_DLG_MODE_DESIGN_RESET = EN_COMMON_DLG_MODE_FACTORY_RESET,
    EN_COMMON_DLG_MODE_DESIGN_RESET_CONFIRM = EN_COMMON_DLG_MODE_FACTORY_RESET_CONFIRM,
    EN_COMMON_DLG_MODE_DIVX,
    EN_COMMON_DLG_MODE_DEACTIVATION,
    EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM,
    EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD,
    EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD,
    EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD,
    EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD,
    EN_COMMON_DLG_MODE_DESIGN_RESET_INPUT_PASSWORD,
    EN_COMMON_DLG_MODE_WRONG_PASSWORD,
    EN_COMMON_DLG_MODE_MISMATCH_PASSWORD,
    EN_COMMON_DLG_MODE_INPUT_PASSWORD,
    EN_COMMON_DLG_MODE_SET_PASSWORD,
    EN_COMMON_DLG_MODE_FORCE_PRESET_PASSWORD,
    EN_COMMON_DLG_MODE_USB_NOT_DETECTED,
    EN_COMMON_DLG_MODE_CI_NO_MODULE,
    EN_COMMON_DLG_MODE_SW_FILE_NOT_DETECTED,
    EN_COMMON_DLG_MODE_USB_UPDATE_CONFIRM,
    EN_COMMON_DLG_MODE_USB_UPGRADING,
    EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD,
#if (ENABLE_ATSC)
    EN_COMMON_DLG_MODE_RESETRRT_CONFIRM,
#endif
} COMMON_DLG_MODE;

typedef enum _COMMON_OPTIONLIST_MODE
{
    EN_COMMON_OPTIONLIST_INVALID,
    EN_COMMON_OPTIONLIST_NETWORK_DNS,
    EN_COMMON_OPTIONLIST_NETWORK_GW,
    EN_COMMON_OPTIONLIST_NETWORK_IP,
    EN_COMMON_OPTIONLIST_NETWORK_NETMASK,
    EN_COMMON_OPTIONLIST_NETWORK_CONFIG,
    EN_COMMON_OPTIONLIST_SOUND_SWITCH,
    EN_COMMON_OPTIONLIST_SOUND_BALANCE,
} COMMON_OPTIONLIST_MODE;


typedef enum _COMMON_SINGLELIST_MODE
{
    EN_COMMON_SINGLELIST_INVALID,
    EN_COMMON_SINGLELIST_ASPECT_RATIO,
    EN_COMMON_SINGLELIST_NOISE_REDUCTION,
    EN_COMMON_SINGLELIST_MPEG_NOISE_REDUCTION,
    EN_COMMON_SINGLELIST_SURROUND_SOUND,
    EN_COMMON_SINGLELIST_TV_SPEAKER,
    EN_COMMON_SINGLELIST_SLEEP_TIMER,
    EN_COMMON_SINGLELIST_AUTOSLEEP_TIMER,
    EN_COMMON_SINGLELIST_PARENTAL_GUIDANCE,
#if  (ATSC_CC == ATV_CC)
	EN_COMMON_SINGLELIST_CC_OPTION,
#endif

//#if ENABLE_T_C_COMBO
//    EN_COMMON_SINGLELIST_DVB_SELECT,
//#endif

#if (NTV_FUNCTION_ENABLE)
	EN_COMMON_SINGLELIST_BANDWIDTH_SELECT,
#endif

#if ENABLE_3D_PROCESS
    EN_COMMON_SINGLELIST_3D_TYPE,
#endif

#if(ENABLE_SCART_SVIDEO)
    EN_COMMON_SINGLELIST_SCART_IN,
#endif

#if (ENABLE_ATSC)
    EN_COMMON_SINGLELIST_MTS,
    EN_COMMON_SINGLELIST_OSD_TIMEZONE,
    EN_COMMON_SINGLELIST_MENU_LANGUAGE,
#endif
#if (ENABLE_LANGUAGE_SWITCH_LIST_MENU)
     EN_COMMON_SINGLELIST_LANGUAE_PAGE,            ///< goto surrund sound page
#endif
#if (ENABLE_EDID_SWITCH)
    EN_COMMON_SINGLELIST_EDID,
#endif
#if (ENABLE_HDR)
    EN_COMMON_SINGLELIST_HDR,
#endif
} COMMON_SINGLELIST_MODE;

typedef enum _COMMON_PAGE_MODE
{
    EN_COMMON_INVALID,                  // 0
    EN_COMMON_PICTURE_MODE_PAGE,        // 1
    EN_COMMON_PICTURE_COLOR_PAGE,       // 2
    EN_COMMON_SOUND_BALANCE_PAGE,       // 3
    EN_COMMON_SOUND_SWITCH_PAGE,        // 4
    EN_COMMON_SOUND_AUDIO_DELAY_PAGE,   // 5
    EN_COMMON_OFFTIMER_PAGE,            // 6
    EN_COMMON_ONTIMER_PAGE,             // 7
    EN_COMMON_TIME_CLOCK_PAGE,          // 8
    EN_COMMON_SET_MFC_PAGE,             // 9
#if ENABLE_GAMMA_ADJUST
    EN_COMMON_GAMMA_ADJUST_PAGE,       // 10
#endif
#if ENABLE_ATSC_TTS
    EN_COMMON_OPTION_TTS_PAGE,
#endif
}COMMON_PAGE_MODE;
INTERFACE COMMON_PAGE_MODE g_mainpage_common;



/////////////////////////////////////////
// Cutomize Window Procedures...

INTERFACE S32 MApp_ZUI_ACT_UpDateCECDeviceWinProc(HWND hwnd, PMSG msg);
#define UPDATE_CEC_DEVICE_WINPROC  MApp_ZUI_ACT_UpDateCECDeviceWinProc
#if ENABLE_WAIT_CEC_READY
INTERFACE S32 MApp_ZUI_ACT_WaitCECPollingWinProc(HWND hwnd, PMSG msg);
#define WAIT_CEC_POLLING_WINPROC   MApp_ZUI_ACT_WaitCECPollingWinProc
#endif
INTERFACE BOOLEAN MApp_ZUI_ACT_InitMainMenuCECDeviceList(void);

INTERFACE S32 MApp_ZUI_ACT_ButtonAniClickWinProc(HWND, PMSG);
INTERFACE U16 MApp_ZUI_ACT_GetMainMenuDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type);

#define BUTTONANICLICK_WINPROC MApp_ZUI_ACT_ButtonAniClickWinProc

INTERFACE S32 MApp_ZUI_ACT_ButtonAniClickChildWinProc(HWND, PMSG);
INTERFACE S32 MApp_ZUI_ACT_Mainpage_DynamicListWinProc(HWND hWnd, PMSG pMsg);

#define BUTTONANICLICKCHILD_WINPROC MApp_ZUI_ACT_ButtonAniClickChildWinProc

/////////////////////////////////////////
// Event Handlers....
INTERFACE void MApp_ZUI_ACT_AppShowMainMenu(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleMainPageKey(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_TerminateMainMenu(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteMainMenuAction(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetMainMenuDynamicText(HWND hwnd);
INTERFACE LPTSTR MApp_ZUI_ACT_GetSingleListDynamicText(HWND hwnd);
INTERFACE LPTSTR MApp_ZUI_ACT_GetOptionListDynamicText(HWND hwnd);
INTERFACE COMMON_OPTIONLIST_MODE MApp_ZUI_ACT_GetOptionListMode(void);
INTERFACE void MApp_ZUI_ACT_SetOptionListMode(COMMON_OPTIONLIST_MODE mode);
INTERFACE COMMON_SINGLELIST_MODE MApp_ZUI_ACT_GetSingleListMode(void);
INTERFACE void MApp_ZUI_ACT_ShowMainMenuBackground(HWND hwnd);
#if ENABLE_DVBC
void MApp_ZUI_ACT_ShowDVBCScanPage(void);
#endif
#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTMAINPAGE_H */

