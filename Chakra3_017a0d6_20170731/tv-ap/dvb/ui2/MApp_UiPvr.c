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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
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
#ifndef PVR_8051
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal
#endif
#define MAPP_UIPVR_C

//system
#include "Board.h"

#include "debug.h"

#ifndef PVR_8051
#include "drvpower_if.h"
#endif
#include "sysinfo.h"

#if ENABLE_PVR

//api
#include "IOUtil.h"
#ifdef PVR_8051
#include "msAPI_GOP.h"
#endif
#include "msAPI_PVRFileSystem.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "msAPI_Subtitle_Pub.h"
#include "msAPI_Timer.h"
#if ENABLE_CI
#include "msAPI_CI.h"
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_CIPVR_Adaption.h"              //For pvr
MS_BOOL bChangeMessageboxTimer = FALSE;
#endif
#endif
//ap
#include "MApp_Key.h"
#include "MApp_GlobalFunction.h"
#include "mapp_si.h"
#include "MApp_Subtitle.h"
#include "mapp_eit.h"
#if ENABLE_TTX
#include "mapp_ttx.h"
extern U8 g_TTX_On;
#endif
#include "MApp_MassStorage.h"
#include "MApp_TimeShift.h"
#include "MApp_Record.h"
#include "MApp_Playback.h"
#include "MApp_PVR_Browser.h"
#include "MApp_PVR.h"
#include "MApp_TopStateMachine.h"
#include "MApp_MVDMode.h"
#include "MApp_ChannelChange.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#include "MApp_FileBrowser.h"
#include "MApp_BlockSys.h"
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "MApp_TV.h"
#endif
#ifndef PVR_8051
#include "MApp_CharTable.h"
#endif
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "MApp_TV.h"
#include "MApp_Standby.h"
#endif
//ui
#include "MApp_UiPvr.h"

#ifdef PVR_8051
#include "MApp_UiMenu.h"
#include "MApp_UiMenuTbl2.h"
#include "MApp_UiMenuDef.h"
#include "MApp_UiMenuFunc.h"
#include "MApp_UiMenuStr.h"
#include "MApp_UiMenuComponent3.h"
#include "MApp_UiMenuEpgTimer.h"
#else
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APItables.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_ACTpvr.h"
#include "MApp_ZUI_ACTpvrBrowser.h"
#include "MApp_ZUI_GlobalFunction.h"
#include "ZUI_exefunc.h"
#include "MApp_EpgTimer.h"
#endif
#include "MApp_MultiTasks.h"
#include "MApp_SaveData.h"
#include "MApp_InputSource.h"

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif
#include "MApp_Audio.h"
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
#include "msAPI_DrvInit.h"
#endif

#include "MApp_SDT_Monitor.h"

/*************************************************************************************************/
#ifndef PVR_8051
//UI_PORTING
//------------------------------------ MAPPING FUNCTIONS ------------------------------------------
#define MApp_UiMenu_PVR_OpenUI                      MApp_ZUI_ACT_PVR_OpenUI
#define MApp_UiMenu_PVR_CloseUI                     MApp_ZUI_ACT_PVR_CloseUI
#define MApp_UiMenu_PVR_PopUp_Warning_Msg           MApp_ZUI_ACT_PVR_PopUp_Msg
#define MApp_UiMenu_PVR_Record_TickInfo             MApp_ZUI_ACT_PVR_Record_TickInfo
#define MApp_UiMenu_PVR_CheckFS_PopUIPage           MApp_ZUI_ACT_PVR_CheckFS_PopUIPage
#define MApp_UiMenu_MSG_GOTO_MAINMENU               MApp_ZUI_ACT_PVR_GOTO_MAINMENU
#define MApp_UiMenu_PVR_TimeShift_TickInfo          MApp_ZUI_ACT_PVR_TimeShift_TickInfo
#define MApp_UiMenu_PVR_CheckFS_UpdateUI            MApp_ZUI_ACT_PVR_CheckFS_UpdateUI
#define MApp_UiPvr_Browser_RedrawPage               MApp_ZUI_ACT_PVR_Browser_RedrawPage
#define MApp_UiMenu_PVR_Browser_FileInfo_Close      MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Close
#define MApp_UiMenu_PVR_Browser_Close               MApp_ZUI_ACT_PVR_BROWSER_UI_Close
#define MApp_UiMenu_PVR_Initial_Warning_Open()      MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_INITIAL)
#define MApp_UiMenu_PVR_Initial_Warning_Close       MApp_ZUI_ACT_PVR_CloseUI
#define MApp_UiMenu_PVR_TimeShift_Brief_TickInfo(x) MApp_ZUI_ACT_PVR_TimeShift_TickInfo_Brief()
#define MApp_UiMenu_ExecuteKeyEvent_MIA_EXIT        MApp_ZUI_ACT_PVR_CloseUI
#define MApp_UiMenu_DrawSpecificComponentTbl2(w,x,y,z)
//------------------------------------ EMPTY FUNCTIONS --------------------------------------------
#define Draw_PVR_Icon_Pause                 0
#define Draw_PVR_Icon_Record                1
#define Draw_PVR_Icon_PlayAndLoop           2
#define Draw_PVR_Icon_Stop                  3

#define EN_CPSTATE_SELECT                   0
#define EN_CPSTATE_PATH                     1
#define EN_CPSTATE_HIDE                     2

#define GWIN_PVR            0
#define GWIN_ID_VALID       0x00
U8 u8OSDGWinTbl[] = {GWIN_ID_VALID};
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
extern BOOLEAN     g_bTimerTypeRecord;
#endif
U16 g_u16CiPinCode = 0;
#endif
/*************************************************************************************************/
#define UI_PVR_JUMP_SECOND              (U32)(30*1 )        // [[60*1    //one minute   ]]
#define UI_PVR_INSTANT_REPLAY_SECOND    (U32)(10*1 )        // [[60*1    //one minute   ]]

#define PVR_DBG(x)                               //x
#define PVR_CHECKFS_FORMATING_DBG(x)             x
#define PVR_AUTO_ACTION_DBG(x)                   x
#define PVR_CHECKFS_FLOW_DBG            0
#define PVR_STATE_DBG                   0
/*************************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////////// subtitle setting  ///////////////////////////////////////*/
/*###############################################################################################*/
#if (ENABLE_SUBTITLE)
/***************************************************************************************/
static SUBTITLE_MENU LiveSubtitleMenu[MAX_SUBTITLE_SERVICE_NUM];
static DVB_SUBTITLE_SERVICE LiveDVBSubtitleServices[MAX_SUBTITLE_SERVICE_NUM];
static U8 u8LiveDVBSubtitleServiceNum;
static U8 u8LiveFenableSubtitle;
static U8 u8LiveFenableTTXSubtitle;
static U8 u8LiveSutitleItemSelIdx;
static U8 u8LiveSubtitleMenuNum;
static BOOLEAN bResumeSubtitle = FALSE;
static U8 u8Liveu8TTXSubtitleServiceNum;
#ifndef PVR_8051
#if ENABLE_TTX
#ifdef PVR_UTOPIA
static U16 u16LiveTTXDefaultPID = MSAPI_DMX_INVALID_PID;
#endif
#endif
#endif
#ifdef PVR_8051
static BOOLEAN bResumeTTX = FALSE;
#endif
/***************************************************************************************/
static void MApp_UiPvr_SubtitlePause(void)
{
    if (stGenSetting.g_SysSetting.fEnableSubTitle)
    {
        stGenSetting.g_SysSetting.fEnableSubTitle = FALSE;
        bResumeSubtitle = TRUE;
    }
}

/***************************************************************************************/
static void MApp_UiPvr_SubtitleResume(void)
{
    if (bResumeSubtitle)
    {
        stGenSetting.g_SysSetting.fEnableSubTitle = TRUE;
        bResumeSubtitle = FALSE;
    }
}

/***************************************************************************************/
static void MApp_UiPvr_SubtitleBackupServices(void)
{
    memcpy(LiveDVBSubtitleServices, DVBSubtitleServices, sizeof(DVBSubtitleServices));
    memcpy(LiveSubtitleMenu,    SubtitleMenu,    sizeof(SubtitleMenu));

    #ifdef PVR_8051
    u8LiveSutitleItemSelIdx     = SutitleItemSelIdx;
    u8Liveu8TTXSubtitleServiceNum = u8TTXSubtitleServiceNum;
    #else//PVR_AEON
    u8LiveSutitleItemSelIdx     = u8SubtitleItemSelIdx;
    u8Liveu8TTXSubtitleServiceNum = gu8TTXSubtitleServiceNum;
    #endif
    u8LiveSubtitleMenuNum    = u8SubtitleMenuNum;
    u8LiveDVBSubtitleServiceNum = u8DVBSubtitleServiceNum;

    u8LiveFenableSubtitle    = stGenSetting.g_SysSetting.fEnableSubTitle;
    u8LiveFenableTTXSubtitle = stGenSetting.g_SysSetting.fEnableTTXSubTitle;
}

/***************************************************************************************/
static void MApp_UiPvr_SubtitleLoadServices(void)
{
    U8 u8fEnableSubtitle = 0;
    U8 u8fEnableTTXSubtitle = 0;
    MApp_Subtitle_Clear_ServiceData(TRUE);

    #ifdef PVR_8051
    MApp_PVR_PlaybackSubtitleLoadServices(&SutitleItemSelIdx, &u8DVBSubtitleServiceNum, DVBSubtitleServices);
    #else//PVR_AEON
    MApp_PVR_PlaybackSubtitleLoadServices(&u8SubtitleItemSelIdx, &u8DVBSubtitleServiceNum, DVBSubtitleServices);
    #endif

    #ifdef PVR_8051
    MApp_PVR_PlaybackSubtitleLoadMenu(&SutitleItemSelIdx, &u8SubtitleMenuNum, SubtitleMenu, &u8fEnableSubtitle, &u8fEnableTTXSubtitle);
    #else//PVR_AEON
    MApp_PVR_PlaybackSubtitleLoadMenu(&u8SubtitleItemSelIdx, &u8SubtitleMenuNum, SubtitleMenu, &u8fEnableSubtitle, &u8fEnableTTXSubtitle);
    #endif

    //can't change by PVR
    //stGenSetting.g_SysSetting.fEnableSubTitle    = u8fEnableSubtitle;
    //stGenSetting.g_SysSetting.fEnableTTXSubTitle = u8fEnableTTXSubtitle;

    #ifdef PVR_8051
    MApp_Subtitle_Select_Language(SutitleItemSelIdx - 1);
    #else//PVR_AEON
    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx - 1);
    #endif

    #ifdef PVR_8051
    MApp_PVR_PlaybackGetTTXSubtitleNum(&u8TTXSubtitleServiceNum);
    #else//PVR_AEON
    MApp_PVR_PlaybackGetTTXSubtitleNum(&gu8TTXSubtitleServiceNum);
    #endif

    MApp_Subtitle_PID_Updated();
}

/***************************************************************************************/
static void MApp_UiPvr_SubtitleRestoreServices(void)
{
    MApp_Subtitle_Force_Exit();

    #ifdef PVR_8051
    SutitleItemSelIdx       = u8LiveSutitleItemSelIdx;
    #else//PVR_AEON
    u8SubtitleItemSelIdx    = u8LiveSutitleItemSelIdx;
    #endif

    u8SubtitleMenuNum    = u8LiveSubtitleMenuNum;
    u8DVBSubtitleServiceNum = u8LiveDVBSubtitleServiceNum;

    memcpy(DVBSubtitleServices, LiveDVBSubtitleServices, sizeof(LiveDVBSubtitleServices));
    memcpy(SubtitleMenu,    LiveSubtitleMenu,    sizeof(LiveSubtitleMenu));

    #ifdef PVR_8051
    MApp_Subtitle_Select_Language(SutitleItemSelIdx - 1);
    u8TTXSubtitleServiceNum = u8Liveu8TTXSubtitleServiceNum;
    #else//PVR_AEON
    MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx - 1);
    gu8TTXSubtitleServiceNum = u8Liveu8TTXSubtitleServiceNum;
    #endif

    stGenSetting.g_SysSetting.fEnableSubTitle    = u8LiveFenableSubtitle;
    stGenSetting.g_SysSetting.fEnableTTXSubTitle = u8LiveFenableTTXSubtitle;

    MApp_Subtitle_PID_Updated();

}
#else //ENABLE_SUBTITLE==0
#define MApp_UiPvr_SubtitlePause()
#define MApp_UiPvr_SubtitleResume()
#define MApp_UiPvr_SubtitleBackupServices()
#define MApp_UiPvr_SubtitleLoadServices()
#define MApp_UiPvr_SubtitleRestoreServices()
#endif

/***************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////////////////// ui formula ///////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U8 MApp_UiPvr_TimeShiftGetPlaybackPercentage(void)
{
    U32 u32RecordStartTime = MApp_TimeShift_GetRecordStartTimeSec();
    U32 u32PlaybackTime    = MApp_TimeShift_GetPlaybackTimeSec();
  //U32 u32RecordEndTime   = MApp_TimeShift_GetRecordEndTimeSec();

    if((u32PlaybackTime == 0) || (u32RecordStartTime == 0) )
    {
        return 0;
    }
    if (MApp_TimeShift_GetRecordValidPeriodSec())
        return (U8)(u32PlaybackTime*100/MApp_TimeShift_GetRecordValidPeriodSec());
    return 0;
}

/***************************************************************************************/
U8 MApp_UiPvr_TimeShiftGetRecordPercentage(void)
{
    U32 u32RecordStartTime = MApp_TimeShift_GetRecordStartTimeSec();
  //U32 u32PlaybackTime    = MApp_TimeShift_GetPlaybackTimeSec();
    U32 u32RecordEndTime   = MApp_TimeShift_GetRecordEndTimeSec();

    if((u32RecordEndTime == 0) || (u32RecordStartTime == 0) || (u32RecordEndTime < u32RecordStartTime))
    {
        return 0;
    }
    if (MApp_TimeShift_GetRecordValidPeriodSec())
        return (U8)((u32RecordEndTime - u32RecordStartTime)*100/MApp_TimeShift_GetRecordValidPeriodSec());
    return 0;
}

/***************************************************************************************/
U8 MApp_UiPvr_PlaybackGetPlaybackPercentage(void)
{
    //U32 u32RecordStartTime = MApp_Playback_GetRecordStartTimeSec();
    U32 u32PlaybackTime    = MApp_Playback_GetPlaybackTimeSec();
    //U32 u32RecordEndTime   = MApp_Playback_GetRecordEndTimeSec();
    U32 u32TotalTime        = MApp_Playback_GetTotalTimeSec();

    if((u32PlaybackTime == 0)|| (u32TotalTime == 0)|| (u32PlaybackTime > u32TotalTime))
    {
        return 0;
    }

   // return (U8)((u32PlaybackTime - u32RecordStartTime)*100/(u32RecordEndTime - u32RecordStartTime));
   return (U8)(u32PlaybackTime*100/u32TotalTime);
}

/***************************************************************************************/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//<<<AB_LOOP_PROCESS_HERE
/*###############################################################################################*/
/*/////////////////////////////////// Instant Replay / AB Loop ////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static U32 _u32ABLoopStrTime = 0;
static U32 _u32ABLoopEndTime = 0;

/***************************************************************************************/
#if 0   //NOT SUPPORT YET =============================================================//
static void MApp_UiPvr_InstantReplaySet(U32 u32CurrentPlayTime)
{
    _u32ABLoopEndTime = u32CurrentPlayTime;
    _u32ABLoopStrTime = _u32ABLoopEndTime - UI_PVR_INSTANT_REPLAY_SECOND;
}
#endif  //NOT SUPPORT YET =============================================================//

/***************************************************************************************/
static void MApp_UiPvr_ABLoopStop(void)
{
    _u32ABLoopStrTime = 0;
    _u32ABLoopEndTime = 0;
    MApp_Playback_ABLoop_Off();
    MApp_TimeShift_ABLoop_Off();
}

/***************************************************************************************/
static U32 MApp_UiPvr_ABLoopGetJumpTime(void)
{
    if((_u32ABLoopStrTime == 0) || (_u32ABLoopEndTime == 0) || (_u32ABLoopEndTime < _u32ABLoopStrTime))
    {
        return 0;
    }
    else
    {
        return (_u32ABLoopEndTime - _u32ABLoopStrTime);
    }
}

/***************************************************************************************/
enPvrABLoopState MApp_UiPvr_GetABLoop_Status(void)
{
    if(_u32ABLoopEndTime != 0)
    {
        return E_ABLOOP_B_set;
    }
    else if(_u32ABLoopStrTime !=0)
    {
        return E_ABLOOP_A_set;
    }
    else
    {
        return E_ABLOOP_NONE;
    }
}

/***************************************************************************************/
//>>>AB_LOOP_PROCESS_HERE
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/*###############################################################################################*/
/*///////////////////////////////////// file name related ///////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static U8* MApp_UiPvr_GetDateString(ST_TIME* pstTime)
{
    U8 u8_idx = 0;
    #ifdef PVR_8051
        U16* p_string_buffer = (U16*)CHAR_BUFFER;
    #else
        U16* p_string_buffer = CHAR_BUFFER;
    #endif

    p_string_buffer[0] = 0;

    __MApp_UlongToString((U32)pstTime->u16Year, p_string_buffer+u8_idx, 4);
    u8_idx += 4;

    __MApp_UlongToString((U32)pstTime->u8Month, p_string_buffer+u8_idx, 2);
    u8_idx += 2;

    __MApp_UlongToString((U32)pstTime->u8Day, p_string_buffer+u8_idx, 2);
    u8_idx += 2;

    p_string_buffer[u8_idx] = 0;
    return (U8*) p_string_buffer;
}

/***************************************************************************************/
static U8* MApp_UiPvr_GetTimeString(ST_TIME* pstTime)
{
    U8 u8_idx = 0;
    #ifdef PVR_8051
        U16* p_string_buffer = (U16*)CHAR_BUFFER;
    #else
        U16* p_string_buffer = CHAR_BUFFER;
    #endif

    p_string_buffer[0] = 0;

    __MApp_UlongToString((U32)pstTime->u8Hour, &p_string_buffer[u8_idx], 2);
    u8_idx += 2;

    __MApp_UlongToString((U32)pstTime->u8Min, &p_string_buffer[u8_idx], 2);
    u8_idx += 2;

    __MApp_UlongToString((U32)pstTime->u8Sec, &p_string_buffer[u8_idx], 2);
    u8_idx += 2;

    p_string_buffer[u8_idx] = 0;
    return (U8*) p_string_buffer;
}

/***************************************************************************************/
#ifndef PVR_8051
static U16* MApp_UiPvr_GetChannelString(U16* pDestStr)
{
    U16 *_pu16 = (U16*)pDestStr;

  #if(PVR_RECORD_IN_ALL_INPUT_SOURCE ==FALSE)
    if ( IsDTVInUse() )
  #endif
    {
        U16 u16Count, u16Pos=0;
        MEMBER_SERVICETYPE bServiceType;

#if MHEG5_ENABLE // <-<<<
        bServiceType=g_eCurrentUserServiceType;

        u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

        if(bServiceType == E_SERVICETYPE_DTV)
            u16Pos=g_wCurrentTVUserServicePosition;
        else if(bServiceType == E_SERVICETYPE_RADIO)
            u16Pos=g_wCurrentRadioUserServicePosition;
#if NORDIG_FUNC //for Nordig spec v2.0
        else if(bServiceType == E_SERVICETYPE_DATA)
            u16Pos=g_wCurrentDataUserServicePosition;
#endif
        else
            u16Pos=0;
#else
        bServiceType = msAPI_CM_GetCurrentServiceType();
        u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        u16Pos = msAPI_CM_GetCurrentPosition(bServiceType);
#endif
        if (u16Count > 0)
        {
            U8 tempBuffer[MAX_SERVICE_NAME];
            U8 *tempBuf2;
            tempBuf2=(U8*)_pu16;
            #ifdef PVR_8051
            if(msAPI_CM_GetServiceName(bServiceType, u16Pos, tempBuf2)==E_RESULT_SUCCESS)
            #else
            if(msAPI_CM_GetServiceName(bServiceType, u16Pos, tempBuf2)==TRUE)
            #endif
            {
                MApp_SI_GetString(tempBuffer, MAX_SERVICE_NAME, tempBuf2, MAX_SERVICE_NAME, KEEP_CONTROL_CODE_NONE);
                MApp_CharTable_MappingDVBTextToUCS2(tempBuffer, _pu16, MAX_SERVICE_NAME, MAX_SERVICE_NAME, REMOVE_00AD_SOFT_HYPHEN);
            }
        }
    }
    return _pu16;
}

/***************************************************************************************/
static U16* MApp_UiPvr_GetProgramString(void)
{
    #ifdef PVR_UTOPIA
    U16 *_pu16 = (LPTSTR)CHAR_BUFFER;
    #else
    U16 *_pu16 = (U16*)au8StringBuffer;
    #endif
#if (ENABLE_DTV_EPG)
#ifndef PVR_8051
MS_EIT_CUR_EVENT_PF pastEventInfo[2];
#endif
#endif
    _pu16[0] = 0;

#if (ENABLE_DTV_EPG)

 #ifdef PVR_8051
  #if(PVR_RECORD_IN_ALL_INPUT_SOURCE ==FALSE)
    if ( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM)
       &&(IsDTVInUse()) )
  #else
    if ((pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM))
  #endif
 #else//PVR_AEON
    if ( (MApp_EIT_GetCurPFInfo(pastEventInfo)) && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM)
       &&(IsDTVInUse()
    ))
 #endif
    {
      #if MHEG5_ENABLE // <-<<<
        if ( g_eCurrentUserServiceType != g_eCurrentRealServiceType
           || (g_eCurrentRealServiceType == E_SERVICETYPE_DTV && g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition)
           || (g_eCurrentRealServiceType == E_SERVICETYPE_RADIO && g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition)
          #if NORDIG_FUNC //for Nordig spec v2.0
           || (g_eCurrentRealServiceType == E_SERVICETYPE_DATA && g_wCurrentDataUserServicePosition != g_wCurrentDataRealServicePosition)
          #endif
           )
        {
            return _pu16;
        }
      #endif

      #ifdef PVR_8051
        MApp_Epg_EventName_LoadFromSED(_pu16, MAX_SHORT_EVENT_DESCRIPTOR_LEN, pastEventInfo[bNextEvent].short_event_descriptor);
      #else
        MApp_Epg_EventName_LoadFromSED(_pu16, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN, pastEventInfo[bNextEvent].short_event_descriptor);
      #endif

        if (_pu16[0] != '\0')
        {
            return _pu16;
        }
    }
#endif //(ENABLE_DTV_EPG)

    return _pu16;
}

/***************************************************************************************/
#if(ENABLE_PVR_BROWSER)
static U16* MApp_UiPvr_GetProgramDesc(void)
{
    #ifdef PVR_UTOPIA
    U16 *_pu16 = (LPTSTR)CHAR_BUFFER;
    #else
    U16 *_pu16 = (U16*)au8StringBuffer;
    #endif

    _pu16[0] = '\0';

#ifdef PVR_8051
  #if(PVR_RECORD_IN_ALL_INPUT_SOURCE ==FALSE)
    if ( ( pastEventInfo ) && ( MApp_Dmx_EIT_Get_CurPfVer() != INVALID_VERSION_NUM )
       &&(IsDTVInUse()) )
  #else
    if ( ( pastEventInfo ) && ( MApp_Dmx_EIT_Get_CurPfVer() != INVALID_VERSION_NUM ))
  #endif
#else
  #if(PVR_RECORD_IN_ALL_INPUT_SOURCE ==FALSE)
    if ( ( MApp_EIT_IsCurPFInfoExist() ) && ( MApp_Dmx_EIT_Get_CurPfVer() != INVALID_VERSION_NUM )
       &&(IsDTVInUse()) )
  #else
    if ( ( MApp_EIT_IsCurPFInfoExist() ) && ( MApp_Dmx_EIT_Get_CurPfVer() != INVALID_VERSION_NUM ))
  #endif
#endif
    {
      #ifdef PVR_8051
        msAPI_MIU_Copy( CUR_EIT_MIU_ADDR(EIT_CUR_PRE_SECTION_START_ADR), (U32)CHAR_BUFFER, (PVR_BROWSER_MAX_PROGRAM_DESC_LEN-1)*2, MIU_SDRAM2SDRAM );
      #else
        MApp_EIT_GetPfString(NOW,(U8*)CHAR_BUFFER,0,(PVR_BROWSER_MAX_PROGRAM_DESC_LEN-1)*2);
        //msAPI_MIU_Copy( MApp_EIT_GetPfStrBufferAddr(NOW), (U32)CHAR_BUFFER, (PVR_BROWSER_MAX_PROGRAM_DESC_LEN-1)*2, MIU_SDRAM2SDRAM );
      #endif

        _pu16[PVR_BROWSER_MAX_PROGRAM_DESC_LEN -1] = 0;
    }
    return _pu16;
}
#endif
#endif  //#ifndef PVR_8051

/***************************************************************************************/
static void MApp_UiPvr_GetFileName(U16* _pu16Str, ST_TIME* pstTime)
{
    U8 u8len = 0;
    U16 u16i = 0, u16j = 0;

    UnicodeCpy((S8*)_pu16Str, (S8*)MApp_UiPvr_GetDateString(pstTime));
    u8len = UnicodeLen((S8*)_pu16Str);
    _pu16Str[u8len++] = CHAR_US;
    _pu16Str[u8len] = 0;

    UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiPvr_GetTimeString(pstTime));
    u8len=UnicodeLen((S8*)_pu16Str);
    _pu16Str[u8len++] = CHAR_US;

    _pu16Str[u8len++] = CHAR_LEFT_BRACKET;
    _pu16Str[u8len] = 0;

    #ifdef PVR_8051
    UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiMenu_String(CURPROGRAMNUMBERTEXT));
    u8len = UnicodeLen((S8*)_pu16Str);
    _pu16Str[u8len++] = CHAR_SPACE;
    _pu16Str[u8len++] = 0;
    UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiMenu_String(CURPROGRAMNAMETEXT));
    #else//PVR_AEON
    UnicodeCat((S8*)_pu16Str, (S8*)MApp_ZUI_GetCurrentChNumber());
    u8len = UnicodeLen((S8*)_pu16Str);
    _pu16Str[u8len++] = CHAR_SPACE;
    _pu16Str[u8len] = 0;
    MApp_UiPvr_GetChannelString((U16*)&_pu16Str[u8len]);
    #endif

    u8len=UnicodeLen((S8*)_pu16Str);
    _pu16Str[u8len++] = CHAR_RIGHT_BRACKET;
    _pu16Str[u8len++] = CHAR_US;
    _pu16Str[u8len++] = CHAR_LEFT_BRACKET;
    _pu16Str[u8len] = 0;

    if(MApp_EpgTimer_IsTriggerByTimer())
    {
        if(MApp_EpgTimer_GetStartingEventName(&_pu16Str[u8len]) == FALSE)
        {
        #ifdef PVR_8051
            UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiMenu_String (INFO_EVENTTITLETEXT));
        #else
            //UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiPvr_GetProgramString());
            UnicodeCat2((S8*)_pu16Str, (S8*)MApp_UiPvr_GetProgramString(), RECORD_NAME_LENGTH - u8len - 7);
        #endif
        }
    }
    else
    {
    #ifdef PVR_8051
        UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiMenu_String (INFO_EVENTTITLETEXT));
    #else
        //UnicodeCat((S8*)_pu16Str, (S8*)MApp_UiPvr_GetProgramString());
        UnicodeCat2((S8*)_pu16Str, (S8*)MApp_UiPvr_GetProgramString(), RECORD_NAME_LENGTH - u8len - 7);
    #endif
    }

    u8len = UnicodeLen((S8*)_pu16Str);
    _pu16Str[u8len++] = CHAR_RIGHT_BRACKET;
    _pu16Str[u8len++] = CHAR_DOT;
    _pu16Str[u8len++] = CHAR_t;
    _pu16Str[u8len++] = CHAR_s;
    _pu16Str[u8len] = 0;

    // Remove illegal character
    u16j = 0;
    for (u16i=0; u16i < u8len ; u16i ++)
    {
        if(_pu16Str[u16i] < 0x20)
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == 0x22)                  /* " */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == FS_CHAR_STAR)     /* * */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == FS_CHAR_SLASH)    /* / */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == FS_CHAR_COLON)    /* : */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == 0x3C)             /* < */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == FS_CHAR_GT)       /* > */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == FS_CHAR_QM)       /* ? */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == 0x5C)             /* \ */
            _pu16Str[u16j] = CHAR_SPACE;
        else if(_pu16Str[u16i] == 0x7C)             /* | */
            _pu16Str[u16j] = CHAR_SPACE;

        if(u16j!=0 || _pu16Str[u16j]!=CHAR_SPACE)  /*remove first blank*/
        {
            u16j++;
        }
    }
    _pu16Str[u16j] = 0;
}

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////////    system related     /////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
#if MHEG5_ENABLE
void MApp_UiPvr_Exit_MHEG5(void)
{
    MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_STOPDSMCC);
}
#endif

/***************************************************************************************/
void MApp_UiPvr_MiniChannelChange(void)
{
    AUD_INFO stAudioStreamInfo;
#if(!defined(S3PLUS) && !defined(S4LITE))
    AUD_INFO stAdAudioStreamInfo;
#endif
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;

#ifdef PVR_8051
#if(!defined(S3PLUS) && !defined(S4LITE))
    MApp_UiMenu_SearchAdAudio();
#endif
#endif

    #if 0//def PVR_8051
    enPreSdtRunniungSts = SI_SDT_RUN_RUNNING;
    #else//PVR_AEON
    MApp_SDT_ResetRunningStatus();
    #endif

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAudioStreamInfo, g_u8AudLangSelected);
#if(!defined(S3PLUS) && !defined(S4LITE))
    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAdAudioStreamInfo, g_u8AdAudSelected);
#endif
    g_u16Current_PCRPID       = msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition);
    g_u16Current_PVR_VideoPID = msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
    g_u16Current_PVR_AudioPID = stAudioStreamInfo.wAudPID;
    //g_wCurrent_AudioType      = stAudioStreamInfo.wAudType;
    g_wCurrent_AudioType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);

#if(!defined(S3PLUS) && !defined(S4LITE))
    g_u16Current_AudioDescriptorPID = stAdAudioStreamInfo.wAudPID;
#endif
    MApp_VID_VariableInit();

    #ifndef S3PLUS
    bH264FirstTimeCheck = TRUE;
    #endif

    fEnableSignalMonitor = TRUE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////// ui trigger start/stop /////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static EN_PVR_PAGE_MODE _enPvrPageMode = EN_PVR_PAGE_NORMAL;
//static U8 u8LiveAudioSelected;

#if(ENABLE_PVR_BROWSER)
static void MApp_UiPvr_Browser_AddProgramme(U16* _pu16Filename, U32 recStartTime);
#endif

/***************************************************************************************/
void MApp_UiPvr_TimeshiftRecordStart(U16 u16CiPinCode)
{
    /*[04-5]ap action =========================================================*/
    g_u16CiPinCode = u16CiPinCode;
    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);

    /*[04-6]ui global =========================================================*/
    if(MApp_PVR_StateMachineGet()       == E_PVR_STATE_TIMESHIFT &&         //{should re-get after SMInput}
       MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING)     //{should re-get after SMInput}
    {
        _enPvrPageMode = EN_PVR_PAGE_NORMAL;
    }

    //global variables , very bad, should remove ==============================//
    g_u32TimeShiftClockStartTime         = MApp_GetLocalSystemTime();
    g_u32TimeShiftStartRecordingTime_Sec = MApp_TimeShift_GetRecordStartTimeSec();
    //global variables , very bad, should remove ==============================//

}

/***************************************************************************************/
void MApp_UiPvr_RecordStart(U16 u16CiPinCode)
{
    ST_TIME stRecordedDate;
    U32 u32RecordedDate;
    int retrys=0;
    g_u16CiPinCode = u16CiPinCode;
#if MHEG5_ENABLE
    MApp_MHEG5_ExitMheg5();
#endif
#if (UI_PVR_BLOCK_SCRAMBLE_CHANNEL_RECORD)
    {   //Check scramble
        MEMBER_SERVICETYPE serviceType;
        U16 u16Pos;
        serviceType = msAPI_CM_GetCurrentServiceType();
        u16Pos = msAPI_CM_GetCurrentPosition(serviceType);

        if(msAPI_CM_GetProgramAttribute(serviceType, u16Pos, E_ATTRIBUTE_IS_SCRAMBLED))
        {   //Block scramble recording
        #ifdef PVR_8051
            if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_SCRAMBLE)))
        #else
            if(g_PVR_PopUpWarning != E_PVR_WARNING_REC_SCRAMBLE)
        #endif
            {
                MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_SCRAMBLE);
            }
            return;
        }
    }
#endif

    // Get & Set File Name
    u32RecordedDate = MApp_GetLocalSystemTime();
    MApp_ConvertSeconds2StTime(u32RecordedDate, &stRecordedDate);
    while( retrys < 10)
    {
        g_pu16TempFileName[0]= 0;

        MApp_UiPvr_GetFileName(g_pu16TempFileName, &stRecordedDate);

        //printf("\n--- [%s]->%d;string=%s-%s.\n",__func__,__LINE__,g_pu16TempFileName,&stRecordedDate);
        //printf("\n--- [%s]->%d;result=%d.\n",__func__,__LINE__,msAPI_PVRFS_FileExist(g_pu16TempFileName));

        if(msAPI_PVRFS_FileExist(g_pu16TempFileName) == FALSE)
        {
            break;
        }
        else
        {
            retrys++;
            stRecordedDate.u8Sec = (stRecordedDate.u8Sec+1)%60;
        }
    }

    if( retrys >= 10) //only try 10 times
    {
        return;
    }

    MApp_PVR_StateMachineInput(E_PVR_INPUT_RECORD_OPEN, (U32)(g_pu16TempFileName));

    if(MApp_Record_StateMachineGet()== E_RECORD_STATE_RECORDING)            //{should re-get after SMInput}
    {
    #if(ENABLE_PVR_BROWSER)
        if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel==0)
        {
            MApp_UiPvr_Browser_AddProgramme(g_pu16TempFileName, u32RecordedDate);       //set record file info to bulk file system & browser buffer
            MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, g_pu16TempFileName, NULL);
        }
    #endif
        _enPvrPageMode = EN_PVR_PAGE_NORMAL;    // ui reset
    }

    if(MApp_EpgTimer_IsTriggerByTimer())
    {
         MApp_EpgTimer_RecordQueueSetPath(MApp_EpgTimer_GetStartingIndex(), RECORD_PATH_DEFAULT);
         MApp_EpgTimer_ClearStartingIndex();
    }
    else
    {
        MApp_EpgTimer_RecordQueueAdd(EPGTIMER_INDEX_USER, RECORD_PATH_DEFAULT);
    }
}

/***************************************************************************************/
void MApp_UiPvr_RecordStop(void)
{
    //-------------------------------------------------------------------------
    //TimeShift ALSO call this function when user press "STOP",
    //some code are not allowed in Timeshift mode
    //-------------------------------------------------------------------------
    if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel == 0)
    {
    #if(ENABLE_PVR_BROWSER)
        if(MApp_PvrBrowser_IsAnyFileRecording())
        {
            U32 recTime = (MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT));
            MApp_PvrBrowser_GetRecordingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)CHAR_BUFFER, RECORD_NAME_LENGTH*2);
            MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_DURATION, (U16*)CHAR_BUFFER, (BYTE*)&recTime);
            MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, NULL, NULL);
        }
        if(MApp_PvrBrowser_IsAnyFilePlaying()) //for record&play case
        {
            MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)CHAR_BUFFER, RECORD_NAME_LENGTH*2);
            MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
        }
    #endif
    }

    MApp_PVR_StateMachineInput(E_PVR_INPUT_RECORD_CLOSE, RECORD_PATH_DEFAULT);
    if(E_PVR_RECORDER_TIMEUP_RECORDING == g_PVR_RecordStatus)
    {
        g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
    }

    MApp_EpgTimer_RecordQueueDel(RECORD_PATH_DEFAULT);
#if (ENABLE_SUBTITLE)
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
    MApp_ReMoveUnShowSubtitle();
#endif
#endif
}

/***************************************************************************************/
void MApp_UiPvr_PlaybackStart(void)
{
    enPVRState       PVRState       = MApp_PVR_StateMachineGet();           //<---only get state here
  //enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();     //<---only get state here
  //enRecordState    RecordState    = MApp_Record_StateMachineGet();        //<---only get state here
  //enPlaybackState  PlaybackState  = MApp_Playback_StateMachineGet();      //<---only get state here

    #if MHEG5_ENABLE
    MApp_UiPvr_Exit_MHEG5();
    #endif

    if ((PVRState == E_PVR_STATE_WAIT) || (PVRState == E_PVR_STATE_RECORD))
    {
        if((msAPI_CM_CountProgram(E_SERVICETYPE_ATV,       E_PROGACESS_INCLUDE_VISIBLE_ONLY)==0) &&
           (msAPI_CM_CountProgram(E_SERVICETYPE_DTV,       E_PROGACESS_INCLUDE_VISIBLE_ONLY)==0) &&
           (msAPI_CM_CountProgram(E_SERVICETYPE_RADIO,     E_PROGACESS_INCLUDE_VISIBLE_ONLY)==0) &&
           (msAPI_CM_CountProgram(E_SERVICETYPE_DATA,      E_PROGACESS_INCLUDE_VISIBLE_ONLY)==0) &&
           (msAPI_CM_CountProgram(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)==0)    )
        {
            MApp_UiPvr_MiniChannelChange();
        }

    #ifdef PVR_8051
        #if ENABLE_TTX
        bResumeTTX = g_TTX_On;
        MApp_TTX_TeletextCommand(TTX_TV);
        #endif
    #else
        #if ENABLE_TTX
        MApp_TTX_TeletextCommand(TTX_TV);
        #endif
    #endif
    }
    if ((PVRState == E_PVR_STATE_WAIT) || (PVRState == E_PVR_STATE_RECORD) || (PVRState == E_PVR_STATE_TIMESHIFT))
    {
        #ifndef PVR_8051
        #if ENABLE_TTX
        #ifdef PVR_UTOPIA
        //disable ttx
        {
            u16LiveTTXDefaultPID = MApp_TTX_GetDefaultTTX_PID();
            if ( *MApp_Dmx_GetFid(EN_TTX_FID) != MSAPI_DMX_INVALID_FLT_ID )
            {
                msAPI_TTX_VBIAcquireEnable(FALSE);
                msAPI_TTX_SetTTXFid(MSAPI_DMX_INVALID_FLT_ID);
                msAPI_DMX_CloseFilter( *MApp_Dmx_GetFid(EN_TTX_FID));
                MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_TTX_FID);
                MApp_TTX_Reflesh();
                MApp_TTX_SetDefaultTTX_PID(MSAPI_DMX_INVALID_PID);
                MApp_TTX_TeletextCommand(TTX_TV);
            }
        }
        #endif
        #endif
        #endif
    }

    /* Subtitle Before*/
    MApp_UiPvr_SubtitleBackupServices();

    if (PVRState == E_PVR_STATE_TIMESHIFT)
    {
        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, (U32)g_pu16TempFileName);
    }
    else if ((PVRState == E_PVR_STATE_WAIT) || (PVRState == E_PVR_STATE_RECORD))
    {
        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_OPEN, (U32)g_pu16TempFileName);
    }
    else
    {
        PVR_DBG(printf("Unknow input to MApp_UiPvr_PlaybackStart()\n"));
    }

    if (  (MApp_Playback_StateMachineGet()  == E_PLAYBACK_STATE_PLAYBACKING           ) //{should re-get after SMInput}
//#ifdef S3PLUS
        ||(MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) //{should re-get after SMInput}
        ||(MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING          ) //{should re-get after SMInput}
//#endif
       )
    {
        MApp_UiPvr_ABLoopStop();

        /* Subtitle After */
        MApp_UiPvr_SubtitleLoadServices();

        /* Audio */
        // u8LiveAudioSelected = g_u8AudLangSelected;
        if (PVRState == E_PVR_STATE_TIMESHIFT)
        {
            //MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
        }
        else
        {
            g_u8AudLangSelected = MApp_PVR_PlaybackAudioGetLanguageSelection();
            MApp_PVR_PlaybackAudioSelectLanguage(g_u8AudLangSelected);
        }

        /* UI Reset */
        _enPvrPageMode = EN_PVR_PAGE_NORMAL;

        /* TTX subtitle */
        #ifndef PVR_8051
        #if ENABLE_TTX
        #ifdef PVR_UTOPIA
        if ((SubtitleMenu[u8SubtitleItemSelIdx - 1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT) ||
           (SubtitleMenu[u8SubtitleItemSelIdx - 1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH))
        {
            MApp_TTX_TeletextCommand(TTX_TV);   // exit TTX
           // u16LiveTTXDefaultPID = MApp_TTX_GetDefaultTTX_PID();
            MApp_TTX_SetDefaultTTX_PID(SubtitleMenu[u8SubtitleItemSelIdx - 1].u16PID);
            MApp_TTX_SetDTV_TTXSystem(SubtitleMenu[u8SubtitleItemSelIdx - 1].u16PID, FALSE);
        }
        #endif
        #endif
        #endif
    }
    else
    {
        MApp_UiPvr_SubtitleRestoreServices();
    #if ENABLE_TTX
        #ifdef PVR_UTOPIA
        if(u16LiveTTXDefaultPID != MSAPI_DMX_INVALID_PID)
        {
            MApp_TTX_SetDefaultTTX_PID(u16LiveTTXDefaultPID);
            u16LiveTTXDefaultPID = MSAPI_DMX_INVALID_PID;
        }
        #endif
        MApp_TTX_TeletextCommand(TTX_TV);
        MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetDefaultTTX_PID(), TRUE);
    #endif

    #if (MHEG5_ENABLE)
        enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
    #endif
    }
}

/***************************************************************************************/
void MApp_UiPvr_PlaybackStop(void)
{
    //-------------------------------------------------------------------------
    //TimeShift ALSO call this function when user press "STOP",
    //some code are not allowed in Timeshift mode
    //-------------------------------------------------------------------------
    enPVRState       PVRState       = MApp_PVR_StateMachineGet();           //<---only get state here
    enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();     //<---only get state here
  //enRecordState    RecordState    = MApp_Record_StateMachineGet();        //<---only get state here
  //enPlaybackState  PlaybackState  = MApp_Playback_StateMachineGet();      //<---only get state here
    #ifndef PVR_8051
    #if ENABLE_TTX
    #ifdef PVR_UTOPIA
        if((PVRState==E_PVR_STATE_RECORDnPLAYBACK) || (PVRState==E_PVR_STATE_PLAYBACK) || (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING) || (TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING))
        {
            if ( *MApp_Dmx_GetFid(EN_TTX_FID) != MSAPI_DMX_INVALID_FLT_ID )
            {
                msAPI_TTX_VBIAcquireEnable(FALSE);
                msAPI_TTX_SetTTXFid(MSAPI_DMX_INVALID_FLT_ID);
                msAPI_DMX_CloseFilter( *MApp_Dmx_GetFid(EN_TTX_FID));
                MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_TTX_FID);
                MApp_TTX_Reflesh();
                MApp_TTX_SetDefaultTTX_PID(MSAPI_DMX_INVALID_PID);
                MApp_TTX_TeletextCommand(TTX_TV);
            }
        }
    #endif
    #endif
    #endif

    // Remove old patch(A7)!
#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 )
    MDrv_WriteRegBit( 0x1025A0, 1, BIT0);
    //msAPI_Scaler_SetCVBSMute(ENABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
#endif
    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_CLOSE, 0);
#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 )
    MDrv_WriteRegBit( 0x1025A0, 0, BIT0);
#endif

    MApp_UiPvr_ABLoopStop();

#if(ENABLE_PVR_BROWSER)
    if(MApp_PvrBrowser_IsAnyFilePlaying())
    {
        MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)CHAR_BUFFER, RECORD_NAME_LENGTH*2);
        MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
    }
#endif

#ifndef S3PLUS
    if((PVRState==E_PVR_STATE_RECORDnPLAYBACK) || (PVRState==E_PVR_STATE_PLAYBACK) || (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING) || (TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING))
#endif
    {
        MApp_UiPvr_SubtitleRestoreServices();
       // g_u8AudLangSelected = u8LiveAudioSelected;
    }

#ifdef PVR_8051
    #if ENABLE_TTX
        g_TTX_On = FALSE;
        msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_MIU, MSAPI_DMX_DATAPATH_IN_MIU, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
        MApp_Dmx_CloseFilter( u8TTXFid );
        msAPI_DMX_RestoreDataPath();
        u8TTXFid = MSAPI_DMX_INVALID_PID;
        MApp_TTX_Reflesh();
        #ifndef S3PLUS
            msAPI_DMX_StartFilter(MApp_TTX_GetDefaultTTX_PID(), MSAPI_DMX_FILTER_TYPE_TELETEXT, &u8TTXFid);
        #endif
        g_TTX_On = bResumeTTX;
        MApp_TTX_TeletextCommand(TTX_TV);
    #endif
#else
    #if ENABLE_TTX
        #ifdef PVR_UTOPIA
        if(u16LiveTTXDefaultPID != MSAPI_DMX_INVALID_PID)
        {
            MApp_TTX_SetDefaultTTX_PID(u16LiveTTXDefaultPID);
            u16LiveTTXDefaultPID = MSAPI_DMX_INVALID_PID;
        }
        #endif
        MApp_TTX_TeletextCommand(TTX_TV);
        MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetDefaultTTX_PID(), TRUE);
    #endif
#endif

#if (MHEG5_ENABLE)
    enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
#endif
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////////////////// pvr ui /////////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
#define PVR_UI_ALL_UPDATE_PERIOD_ms             500
#define PVR_UI_PLAY_ICON_SHINE_TIME_PERIOD      1000

static U32 _u32PvrUiLastInfoUpdateTime;
static U32 _u32PvrBrowserUiUpdateTime;

static void MApp_UiPvr_CheckFS_UsbMonitor(void);

/***************************************************************************************/
void  MApp_UiPvr_Init(void)
{
    if(stGenSetting.g_SysSetting.u32PVR_RecordMaxTime < SECONDS_PER_HALF_HOUR
        || stGenSetting.g_SysSetting.u32PVR_RecordMaxTime > PVR_CHECKFS_MAX_RECORD_TIME)
    {
        stGenSetting.g_SysSetting.u32PVR_RecordMaxTime = PVR_CHECKFS_MAX_RECORD_TIME;
    }

    #define PVR_RESET_RECORD_ALL_WHEN_BOOT      TRUE
    #if PVR_RESET_RECORD_ALL_WHEN_BOOT
        stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel = 0;
    #else
        if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel >1)
        {
            stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel = 0;
        }
    #endif
}

/***************************************************************************************/
BOOLEAN MApp_UiPvr_IsRecordingExceedMaxTime(U8 RecorPath)
{
    U32 TotalTime = MApp_Record_GetTotalTimeSec(RecorPath);
    U32 LimitTime = stGenSetting.g_SysSetting.u32PVR_RecordMaxTime;

    if(TotalTime> LimitTime)
    {
        return TRUE;
    }
    else{
              return FALSE;
          }

}

/***************************************************************************************/
static void MApp_UiPvr_UpdateUI(void)
{
    enPVRState       PVRState         = MApp_PVR_StateMachineGet();         //<---only get state here
    enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();   //<---only get state here
    enRecordState    RecordState      = MApp_Record_StateMachineGet();      //<---only get state here
    enPlaybackState  PlaybackState    = MApp_Playback_StateMachineGet();    //<---only get state here

    PVR_DBG(printf("MApp_UiPvr_UpdateUI, UI PVR state:%u\n", PVRState));

    /*[00]not allowed in program browser mode/ shortcut menu ==========================*/
    #ifdef PVR_8051
    if(g_u8MenuPageIndex == MENU_PVR_FILE_BROWSER          ||
       g_u8MenuPageIndex == MENU_PVR_FILE_BROWSER_FILEINFO ||
       g_u8MenuPageIndex == MENU_SIMILAR_LIST                )
    {
        return;
    }

    if( g_u8MenuPageIndex == MENU_PROGRAM_BRIEF  ||
        g_u8MenuPageIndex == MENU_CHANNEL_BANNER ||
        g_u8MenuPageIndex == MENU_PROGRAM_EVENT    )
    {
        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
        u32MonitorOsdTimer = msAPI_Timer_GetTime0();
    }
    #endif

    switch(PVRState)
    {
        /*[01]Idle state ==============================================================*/
        default:
        case E_PVR_STATE_IDLE:
        case E_PVR_STATE_INIT:
            break;
        case E_PVR_STATE_WAIT:
            break;

        /*[02]Record state ============================================================*/
        case E_PVR_STATE_RECORD:
        {
            PVR_DBG(printf("UI record state:%u\n", RecordState));

            switch(RecordState)
            {
                default:
                {
                    if(g_PVR_PopUpWarning != E_PVR_WARNING_NONE)
                    {
                        MApp_UiMenu_PVR_CloseUI();
                    }
                    break;
                }
                case E_RECORD_STATE_RECORDING:
                {
                    if ( !IsDTVInUse() )
                    {
                        break;
                    }

                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_RECORD);
                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Record , EN_CPSTATE_SELECT);
                    }
                    else
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_RECORDING_BRIEF);
                    }
                    break;
                }
                case E_RECORD_STATE_STOP:
                {
                    break;
                }
            }
            break;
        }

        /*[03]Record & Playback state =================================================*/
        case E_PVR_STATE_RECORDnPLAYBACK:
        {
            /*[03-1]Record state ======================================================*/
            //if RECORDnPLAYBACK, show PLAYBACK only
            PVR_DBG(printf("UI record state:%u\n", RecordState));

            /*[03-2]Playback state ====================================================*/
            PVR_DBG(printf("UI playback state:%u\n", PlaybackState));

            switch(PlaybackState)
            {
                case E_PLAYBACK_STATE_PLAYBACKING:
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);

                        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                        //<<<AB_LOOP_PROCESS_HERE
                        if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                        {
                            MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_PlayAndLoop , EN_CPSTATE_PATH); // A B loop End Time Set
                        }
                        else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                        {
                            MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_PlayAndLoop , EN_CPSTATE_HIDE); // A B loop Start Time Set
                        }
                        //>>>AB_LOOP_PROCESS_HERE
                        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                        else //if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_NONE)
                        {
                            MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_PlayAndLoop , EN_CPSTATE_SELECT);
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                    }
                    else if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                        #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #endif
                    }
                    break;
                }

                case E_PLAYBACK_STATE_PAUSE:
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Pause, EN_CPSTATE_SELECT);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PAUSE_BRIEF);
                    }
                    else if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                        #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #endif
                    }
                    break;
                }

                case E_PLAYBACK_STATE_STOP:
                {
                    #ifdef PVR_8051
                    if(MENU_PVR_PLAYBACK != g_u8MenuPageIndex)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                    }
                    else
                    #endif
                    if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                        #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #endif
                    }
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Stop, EN_CPSTATE_SELECT);
                    break;
                }

                case E_PLAYBACK_STATE_FASTFORWARD:
            #ifdef PVR_8051
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);

                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X2, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X4, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X8, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X16, EN_CPSTATE_SELECT);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);

                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X2_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X4_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X8_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X16_Brief, EN_CPSTATE_SELECT);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
            #elif (defined PVR_UTOPIA)
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                    }
                    break;
                }
            #else
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16_BRIEF, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
            #endif

                case E_PLAYBACK_STATE_FASTBACKWARD:
            #ifdef PVR_8051
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);

                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X2, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X4, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X8, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X16, EN_CPSTATE_SELECT);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);

                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X2_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X4_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X8_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X16_Brief, EN_CPSTATE_SELECT);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
            #elif (defined PVR_UTOPIA)
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                    }
                    break;
                }
            #else
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16_BRIEF, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
            #endif

                default:
                {
                    MApp_UiMenu_PVR_CloseUI();
                    break;
                }
            }
            break;
        }

        /*[04]Playback state ==========================================================*/
        case E_PVR_STATE_PLAYBACK:
        {
            PVR_DBG(printf("UI playback state:%u\n", PlaybackState));

            switch(PlaybackState)
            {
                case E_PLAYBACK_STATE_PLAYBACKING:
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                    #ifdef PVR_8051
                        if(MENU_LOADING_MHEG_MSG == g_u8MenuPageIndex)
                        {
                            MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                        }
                    #endif
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);

                        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                        //<<<AB_LOOP_PROCESS_HERE
                        if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                        {
                            MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_PlayAndLoop , EN_CPSTATE_PATH); // A B loop End Time Set
                        }
                        else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                        {
                            MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_PlayAndLoop , EN_CPSTATE_HIDE); // A B loop Start Time Set
                        }
                        //>>>AB_LOOP_PROCESS_HERE
                        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                        else //if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_NONE)
                        {
                            MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_PlayAndLoop , EN_CPSTATE_SELECT);
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                    }
                    else if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                      #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                      #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                      #endif
                    }
                    break;
                }
                case E_PLAYBACK_STATE_PAUSE:
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Pause, EN_CPSTATE_SELECT);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PAUSE_BRIEF);
                    }
                    else if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                      #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                      #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                      #endif
                    }
                    break;
                }
                case E_PLAYBACK_STATE_STOP:
                {
                    #ifdef PVR_8051
                    if(MENU_PVR_PLAYBACK != g_u8MenuPageIndex)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                    }
                    else
                    #endif
                    if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                      #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                      #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                      #endif
                    }
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Stop, EN_CPSTATE_SELECT);
                    break;
                }

                case E_PLAYBACK_STATE_FASTFORWARD:
            #ifdef PVR_8051
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);

                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X2, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X4, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X8, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X16, EN_CPSTATE_SELECT);
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                         MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);

                         switch(MApp_Playback_GetPlaybackSpeed())
                         {
                             case E_PLAY_SPEED_2X:
                                 MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X2_Brief, EN_CPSTATE_SELECT);
                                 break;
                             case E_PLAY_SPEED_4X:
                                 MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X4_Brief, EN_CPSTATE_SELECT);
                                 break;
                             case E_PLAY_SPEED_8X:
                                 MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X8_Brief, EN_CPSTATE_SELECT);
                                 break;
                             case E_PLAY_SPEED_16X:
                                 MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X16_Brief, EN_CPSTATE_SELECT);
                                 break;
                         }
                    }
                    break;
                }
            #elif (defined PVR_UTOPIA)
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                    }
                    break;
                }
            #else
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16_BRIEF, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
            #endif

                case E_PLAYBACK_STATE_FASTBACKWARD:
            #ifdef PVR_8051
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);

                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X2, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X4, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X8, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X16, EN_CPSTATE_SELECT);
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X2_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X4_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X8_Brief, EN_CPSTATE_SELECT);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X16_Brief, EN_CPSTATE_SELECT);
                                break;
                        }
                    }
                    break;
                }
            #elif (defined PVR_UTOPIA)
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                    }
                    break;
                }
            #else
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
                        switch(MApp_Playback_GetPlaybackSpeed())
                        {
                            case E_PLAY_SPEED_2X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_PLAY_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_AB_LOOP_BRIEF_ICON, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_4X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_8X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8_BRIEF, SW_SHOW);
                                break;
                            case E_PLAY_SPEED_16X:
                                MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16_BRIEF, SW_SHOW);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
            #endif

                default:
                {
                    MApp_UiMenu_PVR_CloseUI();
                    break;
                }
            }
            break;
        }

        /*[05]TimeShift state =========================================================*/
        case E_PVR_STATE_TIMESHIFT:
        {
            PVR_DBG(printf("UI timeshift state:%u\n", TimeShiftState));

            switch(TimeShiftState)
            {
                case E_TIMESHIFT_STATE_RECORDING:
                {
                    if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Pause, EN_CPSTATE_SELECT);
                    }
                    else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    {
                        MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                    }
                    else if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                    {
                        #ifdef PVR_UTOPIA
                        MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #else
                        msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                        #endif
                    }
                    break;
                }

                case E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING:
                case E_TIMESHIFT_STATE_PLAYBACKING:
                {
                    switch(MApp_TimeShift_Playback_StateMachineGet())
                    {
                        case E_TIMESHIFT_PLAYBACK_STATE_PAUSE:
                        case E_TIMESHIFT_PLAYBACK_STATE_OPEN:
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                                MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Pause, EN_CPSTATE_SELECT);
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                            }
                            break;
                        }

                        case E_TIMESHIFT_PLAYBACK_STATE_RUNNING:
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                            #ifdef PVR_8051
                                if(MENU_ROOT == g_u8MenuPageIndex || MENU_PVR_TIME_SHIFT == g_u8MenuPageIndex || MENU_PVR_TIME_SHIFT_BRIEF == g_u8MenuPageIndex)
                                {
                                    MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);

                                    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                                    //<<<AB_LOOP_PROCESS_HERE
                                    if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set)
                                    {
                                      MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_TimeShiftAndLoop , EN_CPSTATE_PATH); // A B loop End Time Set
                                    }
                                    else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)
                                    {
                                      MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_TimeShiftAndLoop , EN_CPSTATE_HIDE); // A B loop Start Time Set
                                    }
                                    //>>>AB_LOOP_PROCESS_HERE
                                    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                                    else //if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_NONE)
                                    {
                                      MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_TimeShiftAndLoop , EN_CPSTATE_SELECT);
                                    }
                                }
                            #else//PVR_AEON
                                    MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                            #endif
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                            }
                            else if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                            {
                            #ifdef PVR_UTOPIA
                                MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                            #else
                                msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                            #endif
                            }
                            break;
                        }

                        case E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD:
                    #ifdef PVR_8051
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X2, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X4, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X8, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X16, EN_CPSTATE_SELECT);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X2_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X4_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X8_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FF_X16_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        }
                    #elif (defined PVR_UTOPIA)
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PAUSE, SW_HIDE);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_1X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_SHOW);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_HIDE);
                                        break;
                                    case E_PLAY_SPEED_2X:
                                    case E_PLAY_SPEED_4X:
                                    case E_PLAY_SPEED_8X:
                                    case E_PLAY_SPEED_16X:
                                        if(MApp_TimeShift_IfFastForward())
                                        {
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_HIDE);
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_SHOW);
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_SHOW);

                                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                                        }
                                        else if(MApp_TimeShift_IfFastBackward())
                                        {
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_PLAY, SW_HIDE);
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FB, SW_SHOW);
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_ICON_FF, SW_HIDE);
                                            MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT, SW_SHOW);


                                            MApp_ZUI_API_InvalidateWindow(HWND_PVR_TIMESHIFT_INFO_XN_TEXT);
                                        }
                                        break;
                                    default:
                                    break;
                                }

                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                            }
                            break;
                        }
                    #else
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_AB_LOOP_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16, SW_SHOW);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_BRIEF_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_AB_LOOP_BRIEF_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X2_BRIEF, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X4_BRIEF, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X8_BRIEF, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FF_X16_BRIEF, SW_SHOW);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        }
                    #endif

                        case E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD:
                    #ifdef PVR_8051
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X2, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X4, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X8, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X16, EN_CPSTATE_SELECT);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X2_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X4_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X8_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_FB_X16_Brief, EN_CPSTATE_SELECT);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        }
                    #elif (defined PVR_UTOPIA)
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                            }
                            break;
                        }
                    #else
                        {
                            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_AB_LOOP_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16, SW_SHOW);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            else if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                            {
                                MApp_UiMenu_PVR_OpenUI(MENU_PVR_TIME_SHIFT_BRIEF);
                                switch(MApp_TimeShift_GetPlaybackSpeed())
                                {
                                    case E_PLAY_SPEED_2X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAY_BRIEF_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_AB_LOOP_BRIEF_ICON, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X2_BRIEF, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_4X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X4_BRIEF, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_8X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X8_BRIEF, SW_SHOW);
                                        break;
                                    case E_PLAY_SPEED_16X:
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_COMMON_ICON_PANE, SW_HIDE);
                                        MApp_ZUI_API_ShowWindow(HWND_PVR_PLAYBACK_FR_X16_BRIEF, SW_SHOW);
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        }
                    #endif

                        default:
                            break;
                    }
                    break;
                }

                default:
                {
                    MApp_UiMenu_PVR_CloseUI();
                    break;
                }
            }
            break;
        }
    }
}

/***************************************************************************************/
#if PVR_STATE_DBG   //for debug
enPVRState       prePVRState         = E_PVR_STATE_IDLE;
enTimeShiftState preTimeShiftState   = E_TIMESHIFT_STATE_WAIT;
enRecordState    preRecordState      = E_RECORD_STATE_WAIT;
enPlaybackState  prePlaybackState    = E_PLAYBACK_STATE_WAIT;

enPvrApiStatus   prePVRStatus        = E_PVR_API_STATUS_OK;
enPvrApiStatus   preTimeShiftStatus  = E_PVR_API_STATUS_OK;
enPvrApiStatus   preRecordStatus     = E_PVR_API_STATUS_OK;
enPvrApiStatus   prePlaybackStatus   = E_PVR_API_STATUS_OK;
#endif


#if ((ENABLE_CI_PLUS == 1) && (!ENABLE_CIPLUS_PVR))
extern MS_BOOL bIsURIBlock;
#endif

/***************************************************************************************/
void MApp_UiPvr_UIMonitor(void)
{
    enPVRState       PVRState         = MApp_PVR_StateMachineGet();         //<---only get state here
    enTimeShiftState TimeShiftState   = MApp_TimeShift_StateMachineGet();   //<---only get state here
    enRecordState    RecordState      = MApp_Record_StateMachineGet();      //<---only get state here
    enPlaybackState  PlaybackState    = MApp_Playback_StateMachineGet();    //<---only get state here

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    enPvrApiStatus   PVRStatus        = MApp_PVR_StatusGet();           //only MApp_UiPvr_UIMonitor can get status !!!
    enPvrApiStatus   TimeShiftStatus  = MApp_TimeShift_StatusGet();     //only MApp_UiPvr_UIMonitor can get status !!!
    enPvrApiStatus   RecordStatus     = MApp_Record_StatusGet();        //only MApp_UiPvr_UIMonitor can get status !!!
    enPvrApiStatus   PlaybackStatus   = MApp_Playback_StatusGet();      //only MApp_UiPvr_UIMonitor can get status !!!
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#if PVR_STATE_DBG   //for debug
if(prePVRState != PVRState)
{
    printf("PVRState:%d=>%d\n",prePVRState,PVRState);
    prePVRState = PVRState;
}
if(prePVRStatus != PVRStatus)
{
    printf("PVRStatus:%d=>%d\n",prePVRStatus,PVRStatus);
    prePVRStatus = PVRStatus;
}
if(preTimeShiftState != TimeShiftState)
{
    printf("TimeShiftState:%d=>%d\n",preTimeShiftState,TimeShiftState);
    preTimeShiftState = TimeShiftState;
}
if(preTimeShiftStatus != TimeShiftStatus)
{
    printf("TimeShiftStatus:%d=>%d\n",preTimeShiftStatus,TimeShiftStatus);
    preTimeShiftStatus = TimeShiftStatus;
}
if(preRecordState != RecordState)
{
    printf("RecordState:%d=>%d\n",preRecordState,RecordState);
    preRecordState = RecordState;
}
if(preRecordStatus != RecordStatus)
{
    printf("RecordStatus:%d=>%d\n",preRecordStatus,RecordStatus);
    preRecordStatus = RecordStatus;
}
if(prePlaybackState != PlaybackState)
{
    printf("PlaybackState:%d=>%d\n",prePlaybackState,PlaybackState);
    prePlaybackState = PlaybackState;
}
if(prePlaybackStatus != PlaybackStatus)
{
    printf("PlaybackStatus:%d=>%d\n",prePlaybackStatus,PlaybackStatus);
    prePlaybackStatus = PlaybackStatus;
}
#endif
    if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
       msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
        if(MApp_TimeShift_IsRecordStoping())
        {
           if(PVRStatus == E_PVR_API_STATUS_NO_DISK_FOR_WRITE)
            {
            printf("%s,%d===>No device!\n",__FUNCTION__,__LINE__);
            }
           else
            {
            if(MApp_TimeShift_RecordStopDiv() >= 1000) //wait Scaler ready and video show
                {
                MApp_TimeShift_DelTsFileName();
                MApp_UiMenu_PVR_CloseUI();
                }
            return;
            }
        }
    }
    /*[00-0]URI protect ==========================================================*/
#if ENABLE_CI_PLUS
    if((PVRStatus == E_PVR_API_STATUS_PROTECTION) && msAPI_CI_CardDetect() && (EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif

            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);

            #ifdef PVR_8051
            msAPI_Timer_Delayms(2000);
            #endif
        }

        MApp_UiPvr_ABLoopStop();
        MApp_UiPvr_RecordStop();
        MApp_UiPvr_SubtitleResume();
    }
#endif




    /*[00-1]No Device Detect ==========================================================*/
    if(PVRStatus == E_PVR_API_STATUS_NO_DISK_FOR_WRITE)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_DEVICE)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_DEVICE)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif

            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_NO_DEVICE);
            MApp_UiPvr_RecordStop();
        #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
            if(MApp_GetActiveStandbyMode())
            {
                g_bTimerTypeRecord = FALSE;
                MApp_Standby_Init();
            }
        #endif
            #ifdef PVR_8051
            msAPI_Timer_Delayms(2000);
            #endif
        }
    }

    else if(PVRStatus == E_PVR_API_STATUS_NO_DISK_FOR_READ)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_PLAY_NO_DEVICE)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_PLAY_NO_DEVICE)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PLAY_NO_DEVICE);
            #ifdef PVR_8051
            msAPI_Timer_Delayms(2000);
            #endif
        }
    }

    /*[00-2]No Signal Detect (by AP state/status) =====================================*/
    else if(RecordStatus == E_PVR_API_STATUS_RECORD_NO_INPUT)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState != E_PLAYBACK_STATE_PAUSE))
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#01 PLAYBACK->PAUSE \n"));
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
            }
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_NO_SIGNAL);
          #if 0//def PVR_8051
            msAPI_Timer_Delayms(1000);
          #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_PROCESSING);
            MApp_UiPvr_RecordStop();
        #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
            if(MApp_GetActiveStandbyMode())
            {
                g_bTimerTypeRecord = FALSE;
                MApp_Standby_Init();
            }
        #endif
            if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState != E_PLAYBACK_STATE_PAUSE))
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#02 PAUSE->RESUME \n"));
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME,0);
            }
        }
    }

    else if(TimeShiftStatus == E_PVR_API_STATUS_RECORD_NO_INPUT)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_NO_SIGNAL);
            MApp_UiPvr_UpdateUI();
        }
    }
    else if(TimeShiftStatus == E_PVR_API_STATUS_NO_DISK_SPACE)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_TIMESHIFT_NO_DISK_SPACE);
            MApp_UiPvr_UpdateUI();
        }
    }
    /*[00-3]No Disk Space Detect (by AP state/status) =================================*/
    else if(RecordStatus== E_PVR_API_STATUS_NO_DISK_SPACE)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_DISK_SPACE)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_DISK_SPACE)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState != E_PLAYBACK_STATE_PAUSE))
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#03 PLAYBACK->PAUSE \n"));
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
            }
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_NO_DISK_SPACE);
            MApp_UiPvr_RecordStop();
        #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
            if(MApp_GetActiveStandbyMode())
            {
                g_bTimerTypeRecord = FALSE;
                MApp_Standby_Init();
            }
        #endif
            if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState != E_PLAYBACK_STATE_PAUSE))
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#04 PAUSE->RESUME \n"));
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
            }
        }
    }
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    else if(RecordStatus== E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_URI_BLOCK)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_URI_BLOCK)))
        #endif
        {
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);
            MApp_UiPvr_RecordStop();
        }
    }
#endif
    /*[00-4]Disk Speed Slow (by AP state/status) ======================================*/
    else if((RecordStatus == E_PVR_API_STATUS_DISK_SPEED_SLOW      ) ||
            (RecordStatus == E_PVR_API_STATUS_RECORD_BUFFER_OVERRUN) ||
            (RecordStatus == E_PVR_API_STATUS_TIMESHIFT_BUFFER_NOT_ENOUGH))
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_LOW_DISK_SPEED)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_LOW_DISK_SPEED)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_LOW_DISK_SPEED);
            //record continully , event the speed too low
            //MApp_UiPvr_RecordStop();
/*
            //###################### DELETE FILE IF DISK SPEED SLOW #####################
            if(RecordStatus == E_PVR_API_STATUS_DISK_SPEED_SLOW)
            {
                U16 fileIdx = MApp_PvrBrowser_GetLogicalIndexByFileName(g_PVRBrowerSort,g_pu16TempFileName);
                if(fileIdx != PVR_NULL_FILE_INDEX)
                {
                    MApp_PvrBrowser_DeleteFileEntry(g_PVRBrowerSort, fileIdx);
                }
                MApp_Record_ClearCurrentFileName(RECORD_PATH_DEFAULT);  //for instant play
            }
            //###################### DELETE FILE IF DISK SPEED SLOW #####################
            */
        }
    }
    else if(PlaybackStatus  == E_PVR_API_STATUS_PLAYBACK_BUFFER_UNDERRUN ||
            TimeShiftStatus == E_PVR_API_STATUS_PLAYBACK_BUFFER_UNDERRUN   )
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_PLAY_LOW_DISK_SPEED)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_PLAY_LOW_DISK_SPEED)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PLAY_LOW_DISK_SPEED);
        }
    }
    else if(TimeShiftStatus == E_PVR_API_STATUS_DISK_SPEED_SLOW      ||
            TimeShiftStatus == E_PVR_API_STATUS_RECORD_BUFFER_OVERRUN||
            (TimeShiftStatus== E_PVR_API_STATUS_TIMESHIFT_BUFFER_NOT_ENOUGH))
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_LOW_DISK_SPEED)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_LOW_DISK_SPEED)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_LOW_DISK_SPEED);
        }
    }
    else if(PlaybackStatus  == E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR ||
            TimeShiftStatus == E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR   )
    {
        MApp_UiMenu_PVR_CloseUI();
        if(PVRState == E_PVR_STATE_TIMESHIFT)
        {
            MApp_UiPvr_PlaybackStop();
            MApp_UiPvr_RecordStop();
        }
        else if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) || (PVRState == E_PVR_STATE_PLAYBACK))
        {
            MApp_UiPvr_PlaybackStop();  //<---become E_PVR_STATE_RECORD
        }
    }

    /*[00-5]Other error (by AP state/status) ==========================================*/
    else if(RecordStatus != E_PVR_API_STATUS_OK)
    {
        MApp_UiMenu_PVR_CloseUI();
        if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState != E_PLAYBACK_STATE_PAUSE))
        {
            PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#05 PLAYBACK->PAUSE \n"));
            MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
        }
        MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_SYSTEM_ERROR);
      #if 0//def PVR_8051
        msAPI_Timer_Delayms(1000);
      #endif
        MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_PROCESSING);
        MApp_UiPvr_RecordStop();
        if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState != E_PLAYBACK_STATE_PAUSE))
        {
            PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#06 PAUSE->RESUME \n"));
            MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
        }
    }
    else if(PlaybackStatus == E_PVR_API_STATUS_FILE_READ_ERROR)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_PVR_FILE_READ_ERROR)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_PVR_FILE_READ_ERROR)))
        #endif
        {
            MApp_UiMenu_PVR_CloseUI();
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_FILE_READ_ERROR);
            MApp_UiPvr_PlaybackStop();
            #ifdef PVR_8051
            msAPI_Timer_Delayms(2000);
            #endif
        }
    }
    else if(PlaybackStatus == E_PVR_API_STATUS_PLAYBACK_NO_OUTPUT)
    {
    #if(ENABLE_PVR_BROWSER)
        if(MApp_UiPvr_Browser_GetPlayingServiceType() == E_SERVICETYPE_RADIO)
        {
            //wait until audio dsp is not decoding, ask AUDIO_TEAM
            MS_DEBUG_MSG(printf("wait until audio dsp is not decoding\n"));
        }
        else
    #endif
        {
            if(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE)
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#07 PLAYBACK->STOP \n"));
                MApp_UiPvr_PlaybackStop();
            }
        }
    }
    else if(PlaybackStatus == E_PVR_API_STATUS_FILE_BUMP_END)
    {
        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#08 PLAYBACK->STOP \n"));  //basically this is for jump forward
        MApp_UiPvr_PlaybackStop();
    }
    else if(TimeShiftStatus== E_PVR_API_STATUS_PLAYBACK_NO_OUTPUT)
    {
        if(msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_RADIO)
        {
            //wait until audio dsp is not decoding, ask AUDIO_TEAM
            MS_DEBUG_MSG(printf("wait until audio dsp is not decoding\n"));
        }
        else
        {
            if(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE)
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#09 PLAYBACK->STOP \n"));
                MApp_UiPvr_PlaybackStop();
            }
        }
    }
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    else if((PlaybackStatus == E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION)
        || (PlaybackStatus == E_PVR_API_STATUS_ERROR_CIPLUS_UNPLUGIN))
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_URI_BLOCK)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_URI_BLOCK)))
        #endif
        {
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);
            MApp_UiPvr_PlaybackStop();
            #ifdef PVR_8051
            msAPI_Timer_Delayms(2000);
            #endif
        }
    }
    else if(PlaybackStatus == E_PVR_API_STATUS_ERROR_RETENTION_LIMIT_EXPIRED)
    {
        #ifdef PVR_8051
        if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_URI_BLOCK)))
        #else//PVR_AEON
        if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
            (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_URI_BLOCK)))
        #endif
        {
            #ifdef PVR_8051
            MApp_UiMenu_PVR_CloseUI();
            #endif
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);
            MApp_UiPvr_PlaybackStop();
            #ifdef PVR_8051
            msAPI_Timer_Delayms(2000);
            #endif
        }
    }
#endif
    else if(PlaybackStatus  == E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR ||
            TimeShiftStatus == E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR   )
    {
        MApp_UiMenu_PVR_CloseUI();
        if(PVRState == E_PVR_STATE_TIMESHIFT)
        {
            MApp_UiPvr_PlaybackStop();
            MApp_UiPvr_RecordStop();
        }
        else if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) || (PVRState == E_PVR_STATE_PLAYBACK))
        {
            MApp_UiPvr_PlaybackStop();  //<---become E_PVR_STATE_RECORD
        }
    }

    /*[01]RECORD state (RECORD bar/icon) ==============================================*/
    if((PVRState == E_PVR_STATE_RECORD) &&
       (RecordState == E_RECORD_STATE_RECORDING) &&
       (msAPI_Timer_DiffTimeFromNow(_u32PvrUiLastInfoUpdateTime) >= PVR_UI_ALL_UPDATE_PERIOD_ms))
    {
#ifdef PVR_8051
          static BOOLEAN isPVRRecordIconShow = TRUE;
#endif
/* monitor in EPG timer
        if(MApp_UiPvr_IsRecordingExceedMaxTime())   //(1)RECORD
        {
            MApp_UiPvr_RecordStop();
        }
*/
        /*[01-1]Prevent Channel Change State updating drawing messup the UI ===========*/
        if(STATE_TOP_DIGITALINPUTS != MApp_TopStateMachine_GetTopState())
        {
            return;
        }

        /*[01-2]MHEG5 =================================================================*/
    #if MHEG5_ENABLE
        #ifdef PVR_8051
        #ifndef S3PLUS
        if(MApp_MHEG5_CheckGoMHEG5Process() && u8OSDGWinTbl[GWIN_PVR] == GWIN_ID_INVALID)
        #else
        if(u8OSDGWinTbl[GWIN_PVR] == GWIN_ID_INVALID)
        #endif
        #else//PVR_AEON
        if(MApp_MHEG5_CheckGoMHEG5Process() && (MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY))
        #endif
        {
            MApp_UiPvr_UpdateUI();
        }
    #endif

    #if (ENABLE_CI)
        {
            static BOOLEAN isPreRecordModeCiInserted;
            BOOLEAN isRecordModeCiInserted = msAPI_CI_CardDetect();
            if (isPreRecordModeCiInserted == TRUE && !msAPI_CI_CardDetect())
            {
                if(MApp_SI_CheckCurProgScramble())
                {
                    MApp_UiPvr_RecordStop();
                    MApp_UiMenu_PVR_CloseUI();
                }
            }

            isPreRecordModeCiInserted = isRecordModeCiInserted;
        }
    #endif

        /*[01-3]RECORD BRIEF ==========================================================*/
        #ifdef PVR_8051
        if(g_u8MenuPageIndex == MENU_PVR_RECORDING_BRIEF)
        #else//PVR_AEON
        if(g_PvrMenuPageType == MENU_PVR_RECORDING_BRIEF)
        #endif
        {
            #ifdef PVR_8051
            if(isPVRRecordIconShow)
            {
                MApp_UiMenu_DrawSpecificComponent1(0, 0, Draw_PVR_RECORD_FLASH_ON, EN_CPSTATE_SELECT);
            }
            else
            {
                MApp_UiMenu_DrawSpecificComponent1(0, 0, Draw_PVR_RECORD_FLASH_OFF, EN_CPSTATE_SELECT);
            }
            isPVRRecordIconShow = !isPVRRecordIconShow;
            #endif
        }

        /*[01-4]RECORD BAR ============================================================*/
        #ifdef PVR_8051
        else if(g_u8MenuPageIndex == MENU_PVR_RECORD)
        #else//PVR_AEON
        else if(g_PvrMenuPageType == MENU_PVR_RECORD)
        #endif
        {
            MApp_UiMenu_PVR_Record_TickInfo();
        }

        /*[01-5]OTHERS ================================================================*/
        else
        {
            #ifdef PVR_8051
            if(g_u8MenuPageIndex == MENU_ROOT)
            #else//PVR_AEON
            if((MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY) || (MApp_ZUI_GetActiveOSD() == E_OSD_PVR))
            #endif
            {
                MApp_UiPvr_UpdateUI();
            }
        }

        /*[01-6]next time =============================================================*/
        _u32PvrUiLastInfoUpdateTime = msAPI_Timer_GetTime0();
    }

    /*[02]RECORDnPLAYBACK state || PLAYBACK state (PLAYBACK bar/icon) =================*/
    else if(((PVRState == E_PVR_STATE_RECORDnPLAYBACK) || (PVRState == E_PVR_STATE_PLAYBACK)) &&
            (msAPI_Timer_DiffTimeFromNow(_u32PvrUiLastInfoUpdateTime) >= PVR_UI_ALL_UPDATE_PERIOD_ms))
    {
        static BOOLEAN isPVRPlaybackIconShow = TRUE;

        U32 u32RecordStartTime = MApp_Playback_GetRecordStartTimeSec();
        U32 u32PlaybackTime    = MApp_Playback_GetPlaybackTimeSec();
        U32 u32RecordEndTime   = MApp_Playback_GetRecordEndTimeSec();
        U32 u32TotalTime        = MApp_Playback_GetTotalTimeSec();
        /*[02-1]#AUTOMATICALLY PLAY -> STOP WHEN END OF FILE# =========================*/

        if(u32TotalTime <= (u32PlaybackTime+(U8)MApp_Playback_GetPlaybackSpeed() / 2 + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)
            && (PVRState == E_PVR_STATE_RECORDnPLAYBACK) && (PlaybackState == E_PLAYBACK_STATE_FASTFORWARD))
        {
            //if(PlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
            {
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                MApp_UiPvr_UpdateUI();
            }
        }

        /*[02-2]#AUTOMATICALLY FAST_BACKWARD -> PLAY WHEN REACH FILE BEGINNING# =======*/
        else if(PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)
        {
            if(u32PlaybackTime <= u32TotalTime-(u32RecordEndTime-u32RecordStartTime) +1)   //no need UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC in playback mode
            {
                if(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE)  //play until run out
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#11 FAST_BACKWARD->RESUME \n"));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                    MApp_UiPvr_UpdateUI();
                }
            }
        }

        else if((u32TotalTime <= u32PlaybackTime) ||((PlaybackState == E_PLAYBACK_STATE_FASTFORWARD)&&(u32PlaybackTime == 0) ))   //no need UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC in playback mode
        {
            if(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE)  //play until run out
            {
                U16 u16NewFileName[RECORD_NAME_LENGTH];
                memset(&u16NewFileName[0], 0, RECORD_NAME_LENGTH*sizeof(U16));

                if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                   msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
                {
                #if(ENABLE_PVR_BROWSER)
                    MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)u16NewFileName, RECORD_NAME_LENGTH*2);
                #endif
                }

                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#10 PLAYBACK->STOP \n"));
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_UpdateUI();

                if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                   msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
                {
                    if(MApp_Record_GetNextSeqFileName(u16NewFileName))
                    {
                        if(msAPI_PVRFS_FileExist(u16NewFileName))
                        {
                            PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#10 PLAY NEXT FILE\n"));
                            UnicodeCpy((S8 *)g_pu16TempFileName, (S8 *)u16NewFileName);
                            MApp_UiPvr_PlaybackStart();
                            MApp_UiPvr_UpdateUI();
                        }
                    }
                }
            }
        }

        /*[02-3]#AUTOMATICALLY AB LOOP DISABLE# =======================================*/
        else if(PlaybackState == E_PLAYBACK_STATE_PLAYBACKING)
        {
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            //<<<AB_LOOP_PROCESS_HERE
            if((MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set) &&
               (u32PlaybackTime +u32RecordStartTime >= _u32ABLoopEndTime))
            {
                /*[02-2-1]#AUTOMATICALLY STOP AB LOOP# ================================*/
                if(u32PlaybackTime <= ( MApp_UiPvr_ABLoopGetJumpTime()+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#12 AB_LOOP->RESUME \n"));
                    MApp_UiPvr_ABLoopStop();
                }
                /*[02-2-2]#AUTOMATICALLY AB LOOP JUMP BACKWARD# =======================*/
                else
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#13 AB_LOOP->JUMP_BACKWARD \n"));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, MApp_UiPvr_ABLoopGetJumpTime());
                }
            }
           //>>>AB_LOOP_PROCESS_HERE
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        }

        /*[02-4]draw playback bar/icon ================================================*/

        #ifdef PVR_8051
        switch(g_u8MenuPageIndex)
        {
            case MENU_ROOT:
            {
                switch(PlaybackState)
                {
                    case E_PLAYBACK_STATE_PLAYBACKING:
                    case E_PLAYBACK_STATE_PAUSE:
                    case E_PLAYBACK_STATE_FASTFORWARD:
                    case E_PLAYBACK_STATE_FASTBACKWARD:
                    {
                        MApp_UiPvr_UpdateUI();
                    }
                    break;
                }
                break;
            }
            case MENU_PVR_PLAYBACK:
            {
                MApp_UiMenu_PVR_Playback_TickInfo();
                break;
            }
            case MENU_PVR_PLAYBACK_BRIEF:
            {
                MApp_UiMenu_PVR_Playback_Brief_TickInfo(isPVRPlaybackIconShow);
                break;
            }
            case MENU_PVR_PAUSE_BRIEF:
            {
                if( MApp_Playback_GetPlaybackSpeed() > E_PLAY_SPEED_1X)
                {
                }
                else if(PlaybackState == E_PLAYBACK_STATE_PAUSE)
                {
                    if(isPVRPlaybackIconShow)
                    {
                        MApp_UiMenu_DrawSpecificComponent1(0, 0, Draw_PVR_PAUSE_PLAYBACK_FLASH_ON, EN_CPSTATE_SELECT);
                    }
                    else
                    {
                        MApp_UiMenu_DrawSpecificComponent1(0, 0, Draw_PVR_PAUSE_PLAYBACK_FLASH_OFF, EN_CPSTATE_SELECT);
                    }
                }
                break;
            }
            default:    //do nothing here,  to prevent interrupt other OSD menu action.
            {
                break;
            }
        }
        #elif (defined PVR_UTOPIA)
        if(MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
        {
            if( _enPvrPageMode == EN_PVR_PAGE_NORMAL )
                MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_PLAYBACK);
            if( _enPvrPageMode == EN_PVR_PAGE_BRIEF )
                MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
        }

        if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR)
        {
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_PLAY_PLAYBACK_TIME_TEXT);
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_PLAY_PERCENTAGE_BAR);
        }

        #else//PVR_AEON
        //return from other OSD for example:main menu,volumn key..etc
        if(MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
        {
            if( _enPvrPageMode == EN_PVR_PAGE_NORMAL )
                MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_PLAYBACK);
            if( _enPvrPageMode == EN_PVR_PAGE_BRIEF )
                MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_PLAYBACK_BRIEF);
        }

        if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR)
        {
            //update playback time
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_PLAYBACK_PLAYBACK_TIME_TXT);
            //update playback progress bar
            MApp_ZUI_API_InvalidateWindow(HWND_PVR_PLAYBACK_PERCENTAGE_BAR);

            //shining of Playback Brief Icon
            if( _enPvrPageMode == EN_PVR_PAGE_BRIEF &&
                (PlaybackState == E_PLAYBACK_STATE_PLAYBACKING ||
                 PlaybackState == E_PLAYBACK_STATE_FASTFORWARD ||
                 PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)
              )
            {
                //update playback brief time
                MApp_ZUI_API_InvalidateWindow(HWND_PVR_PLAYBACK_PLAYBACK_TIME_BRIEF_TXT);
            }
        }
        #endif

        /*[02-5]next time =============================================================*/
        isPVRPlaybackIconShow = !isPVRPlaybackIconShow;
        _u32PvrUiLastInfoUpdateTime = msAPI_Timer_GetTime0();

    }

    /*[03]TIMESHIFT state =============================================================*/
    if((PVRState == E_PVR_STATE_TIMESHIFT)
        && (msAPI_Timer_DiffTimeFromNow(_u32PvrUiLastInfoUpdateTime) >= PVR_UI_ALL_UPDATE_PERIOD_ms))
    {
        static BOOLEAN isPVRTimeShiftIconShow = TRUE;

        U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
        U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
        U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

        /*[03-1]Prevent Channel Change State updating drawing messup the UI ===========*/
        if(STATE_TOP_DIGITALINPUTS != MApp_TopStateMachine_GetTopState())
        {
            return;
        }

        #if (ENABLE_CI)
        {

            static BOOLEAN isPreTimeShitfModeCiInserted;
            BOOLEAN isTimeShitfModeCiInserted = msAPI_CI_CardDetect();

            if (isPreTimeShitfModeCiInserted == TRUE && !msAPI_CI_CardDetect())
            {
                //u8KeyCode = KEY_STOP;  //fixed mantis:1237178
            }

            isPreTimeShitfModeCiInserted = isTimeShitfModeCiInserted;
        }
        #endif

        /*[03-2]#AUTOMATICALLY CHECK IN RECORDING STATE# ==============================*/
        if(TimeShiftState == E_TIMESHIFT_STATE_RECORDING)
        {
            /*[03-2-1]#AUTOMATICALLY PAUSE -> PLAY WHEN BUFFER IS ALMOST FULL# ========*/
            if(((u32PlaybackTime == 0) &&
                (u32RecordEndTime - u32RecordStartTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)) ||
               ((u32PlaybackTime != 0) &&
              (u32RecordEndTime - u32RecordStartTime - u32PlaybackTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))    )
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#14 PAUSE->PLAY \n"));
                u8KeyCode = KEY_PLAY;
            }

            #ifdef PVR_8051
            /* Move to MApp_UiMenu_PVR_TimeShift_Brief_TickInfo(), Draw_PVR_PAUSE_TIMESHIFT_FLASH_ON*/
            #elif (defined PVR_UTOPIA)
            #else
            if(g_PvrMenuPageType == MENU_PVR_PAUSE_BRIEF)
            {
                MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_BRIEF_TXT, SW_SHOW);
            }
            #endif
        }

        /*[03-3]#AUTOMATICALLY CHECK IN RECORDING&PLAYBACKING STATE# ==================*/
        else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
                (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING)             )
        {
            /*[03-3-1]#AUTOMATICALLY PAUSE -> PLAY WHEN BUFFER IS ALMOST FULL# ========*/
            if(MApp_TimeShift_IfPause() == TRUE)
            {
                if(  ((u32PlaybackTime == 0) &&
                      (u32RecordEndTime - u32RecordStartTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)) ||
                     ((u32PlaybackTime != 0) &&
                      (u32RecordEndTime - u32RecordStartTime - u32PlaybackTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))   )
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#15 PAUSE->PLAY \n"));
                    u8KeyCode = KEY_PLAY;
                }

                #ifdef PVR_8051
                /* Move to MApp_UiMenu_PVR_TimeShift_Brief_TickInfo(), Draw_PVR_PAUSE_TIMESHIFT_FLASH_ON*/
                #elif (defined PVR_UTOPIA)
                #else
                if(g_PvrMenuPageType == MENU_PVR_PAUSE_BRIEF)
                {
                    MApp_ZUI_API_ShowWindow(HWND_PVR_TIMESHIFT_PLAYBACK_TIME_BRIEF_TXT, SW_SHOW);
                }
                #endif
            }

            /*[03-3-2]#AUTOMATICALLY PLAY -> STOP WHEN END OF FILE# ===================*/
            #if 0 //auto-stop-timeshift ===============================================//
            else if(u32RecordEndTime <= (u32PlaybackTime+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
            {
                if(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE)  //play until run out
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#16 TIMESHIFT->STOP \n"));
                    MApp_UiPvr_PlaybackStop();
                    MApp_UiPvr_RecordStop();
                }
            }
            #else //===================================================================//
            else if((u32RecordEndTime-u32RecordStartTime) <= (u32PlaybackTime+(U8)MApp_TimeShift_GetPlaybackSpeed() / 2 + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
            {
                if(MApp_TimeShift_IfFastForward() == TRUE)
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]: FAST_FORWARD->RESUME \n"));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                    MApp_UiPvr_UpdateUI();
                }
            }
            #endif //==================================================================//

            /*[03-3-3]#AUTOMATICALLY FAST_BACKWARD -> PLAY WHEN REACH FILE BEGINNING# =*/
            else if((MApp_TimeShift_IfFastBackward() == TRUE))
            {
                U8 u8SafeSecToBorder = (U8)MApp_TimeShift_GetPlaybackSpeed() / 2 + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC;
                if(u32PlaybackTime <= u8SafeSecToBorder)
                {
                    if(1)//(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE) //force resume to prevent exceed border
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#17 FAST_BACKWARD->RESUME \n"));
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                        MApp_UiPvr_UpdateUI();
                    }
                }
            }

            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            //<<<AB_LOOP_PROCESS_HERE
            else if((MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set) &&
                    (u32PlaybackTime +u32RecordStartTime >= _u32ABLoopEndTime))
            {
                /*[03-3-4]#AUTOMATICALLY FORCE AB LOOP DISABLE# =======================*/
                if(u32PlaybackTime <= (MApp_UiPvr_ABLoopGetJumpTime()+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#18 AB_LOOP->RESUME \n"));
                    MApp_UiPvr_ABLoopStop();
                    MApp_UiPvr_UpdateUI();
                }
                /*[03-3-5]#AUTOMATICALLY AB LOOP JUMP BACKWARD# =======================*/
                else
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#19 AB_LOOP->JUMP_BACKWARD \n"));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, MApp_UiPvr_ABLoopGetJumpTime());
                }
            }
            //>>>AB_LOOP_PROCESS_HERE
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        }
#if 0
        /*[03-4]#AUTOMATICALLY CHECK IN PLAYBACKING STATE# ============================*/
        else if(TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING)
        {
            /*[03-4-1]#AUTOMATICALLY FAST_BACKWARD -> PLAY WHEN REACH FILE BEGINNING# =*/
            if(MApp_TimeShift_IfFastBackward() == TRUE)
            {
                if(u32PlaybackTime <= (u32RecordStartTime + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                {
                    if(MApp_PVR_IsVideoFrameCountStillIncrease() == FALSE)
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#20 FAST_BACKWARD->RESUME \n"));
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_PAUSE, 0);
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                        MApp_UiPvr_UpdateUI();
                    }
                }
            }

            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            //<<<AB_LOOP_PROCESS_HERE
            else if((MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set) &&
                    (u32PlaybackTime >= _u32ABLoopEndTime))
            {
                /*[03-4-2]#AUTOMATICALLY FORCE AB LOOP DISABLE# =======================*/
                if(u32PlaybackTime <= (u32RecordStartTime + MApp_UiPvr_ABLoopGetJumpTime()+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#21 AB_LOOP->RESUME \n"));
                    MApp_UiPvr_ABLoopStop();
                }
                /*[03-4-3]#AUTOMATICALLY AB LOOP JUMP BACKWARD# =======================*/
                else
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#22 AB_LOOP->JUMP_BACKWARD \n"));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, MApp_UiPvr_ABLoopGetJumpTime());
                }
            }
            //>>>AB_LOOP_PROCESS_HERE
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        }
#endif
        /*[03-5]#AUTOMATICALLY STOP TIMESHIFT# ========================================*/
        else if(TimeShiftState == E_TIMESHIFT_STATE_WAIT)
        {
            #ifdef PVR_8051
            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR]))
            #else//PVR_AEON
            if(g_PvrMenuPageType == MENU_PVR_TIME_SHIFT ||
               g_PvrMenuPageType == MENU_PVR_TIME_SHIFT_BRIEF)
            #endif
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#23 TIMESHIFT->STOP \n"));
                MApp_UiPvr_RecordStop();
                MApp_UiPvr_PlaybackStop();
            }
        }

        /*[03-6]TIMESHIFT BAR =========================================================*/
    #ifdef PVR_8051
        if(g_u8MenuPageIndex == MENU_PVR_TIME_SHIFT)
    #else//PVR_AEON
        if(g_PvrMenuPageType == MENU_PVR_TIME_SHIFT)
    #endif
        {
            MApp_UiMenu_PVR_TimeShift_TickInfo();
        }
    #ifdef PVR_8051
        else if(g_u8MenuPageIndex == MENU_PVR_TIME_SHIFT_BRIEF || g_u8MenuPageIndex == MENU_PVR_PAUSE_BRIEF)
    #else//PVR_AEON
        else if((g_PvrMenuPageType == MENU_PVR_PAUSE_BRIEF) || g_PvrMenuPageType == (MENU_PVR_TIME_SHIFT_BRIEF))
    #endif
        {
            MApp_UiMenu_PVR_TimeShift_Brief_TickInfo(isPVRTimeShiftIconShow);
        }
    #ifdef PVR_8051
        else if(g_u8MenuPageIndex == MENU_ROOT)
    #else//PVR_AEON
        if(MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
    #endif
        {
            PVR_DBG(printf("MApp_ZUI_GetActiveOSD=Empty\n");)
            switch(TimeShiftState)
            {
                case E_TIMESHIFT_STATE_RECORDING:
                case E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING:
                case E_TIMESHIFT_STATE_PLAYBACKING:
                    MApp_UiPvr_UpdateUI();
                    break;
                default:
                    break;
            }
        }

        /*[03-7]next time =============================================================*/
        isPVRTimeShiftIconShow = !isPVRTimeShiftIconShow;
        _u32PvrUiLastInfoUpdateTime = msAPI_Timer_GetTime0();
    }


    /*[04]#AUTOMATICALLY close PVR UI# ================================================*/
    {   //Monitor state change
        static enPVRState prvPVRState;

        /*[04-1]PVR initial message ===================================================*/
        if ( PVRState == E_PVR_STATE_INIT
           &&(IsDTVInUse() )
           &&(msAPI_Timer_DiffTimeFromNow(_u32PvrUiLastInfoUpdateTime) >= PVR_UI_ALL_UPDATE_PERIOD_ms)
           )
        {
        #ifdef PVR_8051
            if ( g_u8MenuPageIndex == MENU_ROOT
             #if MHEG5_ENABLE
              #ifndef S3PLUS
               ||(MApp_MHEG5_CheckGoMHEG5Process() && g_u8MenuPageIndex == MENU_PVR_INITIAL_WARNING_MSG)
              #else
               ||(g_u8MenuPageIndex == MENU_PVR_INITIAL_WARNING_MSG)
              #endif
             #endif
            )
        #else   //PVR_AEON
            if(MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
        #endif
            {
                MApp_UiMenu_PVR_Initial_Warning_Open();
                _u32PvrUiLastInfoUpdateTime = msAPI_Timer_GetTime0();
            }
        }

    #ifdef PVR_8051
        if(PVRState != prvPVRState)
        {
            if(prvPVRState == E_PVR_STATE_INIT)
            {
                MApp_UiMenu_PVR_Initial_Warning_Close();
            }
        }
    #endif

        /*[04-2]force close PVR UI,for catch un-attention conditions ==================*/
        if(PVRState != prvPVRState)
        {
            if ( ( (PVRState    == E_PVR_STATE_WAIT)
                 ||(PVRState    == E_PVR_STATE_IDLE)
                 ||(PVRState    == E_PVR_STATE_INIT)
                 ||(PVRState    == E_PVR_STATE_WAITFORMAT) )
               &&
                 ( (prvPVRState == E_PVR_STATE_TIMESHIFT)
                 ||(prvPVRState == E_PVR_STATE_RECORD)
                 ||(prvPVRState == E_PVR_STATE_RECORDnPLAYBACK)
                 ||(prvPVRState == E_PVR_STATE_PLAYBACK) )
               )
            {
                MApp_UiMenu_PVR_CloseUI();
            }

            //Catch unattended stoping recorder conditions
            if ( (E_PVR_STATE_RECORD == prvPVRState || E_PVR_STATE_RECORDnPLAYBACK == prvPVRState)
               &&(E_PVR_STATE_RECORD != PVRState && E_PVR_STATE_RECORDnPLAYBACK != PVRState)
               &&(E_PVR_RECORDER_TIMEUP_RECORDING == g_PVR_RecordStatus)
               )
            {
                g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
            }

            prvPVRState = PVRState;
        }
    }   //Monitor state change

    /*[04-3]Close stop record waiting message =========================================*/
#ifdef PVR_8051
    if(E_PVR_WARNING_REC_PROCESSING == g_PVR_PopUpWarning
        && MENU_PVR_POP_UP_WARNING_MSG == g_u8MenuPageIndex)
    {
        MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
    }
#endif

    /*[05]program browser =============================================================*/
    ///update browser playing icon & delete button(static component)
    /*[05-1]PLAYBACK ==================================================================*/
#if(ENABLE_PVR_BROWSER)
    if(MApp_PvrBrowser_IsAnyFilePlaying())
    {
        if(!MApp_PVR_IsPlaybacking())  //playback stop!
        {
            #ifdef PVR_8051
            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_BROWSER]))
            {
                MApp_UiMenu_PVR_Browser_Close();
                MApp_UiMenu_PVR_Browser_Open();
                MApp_UiPvr_Browser_RedrawPage();
            }
            #endif
        }
    }
#endif

    /*[05-2]RECORD ====================================================================*/
#if(ENABLE_PVR_BROWSER)
    if(MApp_PvrBrowser_IsAnyFileRecording())
    {
        if(!MApp_PVR_IsRecording())    //recording stop!
        {
            #ifdef PVR_8051
            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_BROWSER]))
            {
                MApp_UiMenu_PVR_Browser_Close();
                MApp_UiMenu_PVR_Browser_Open();
                MApp_UiPvr_Browser_RedrawPage();
            }
            #endif
        }
    }
#endif

    /*[05-3]draw key effect of PVR Browser ============================================*/
#ifdef PVR_8051
    if(g_KeyEffect_PrvBtnVal == BTN_INDEX && g_u8MenuPageIndex == MENU_PVR_FILE_BROWSER  &&  msAPI_Timer_DiffTimeFromNow(g_KeyEffect_KeyPressTimer) > 200)
    {
        MApp_UiMenu_DrawSpecificComponent1(UI_CHANNEL_LIST_BG_X+20+74+74, UI_CHANNEL_LIST_BG_Y+UI_CHANNEL_LIST_BG_H+4, Draw_KeyPress_INDEX, EN_CPSTATE_UNSELECT);
        g_KeyEffect_PrvBtnVal = BTN_NOTHING;
    }

    if(g_KeyEffect_PrvBtnVal == BTN_RED && g_u8MenuPageIndex == MENU_PVR_FILE_BROWSER  &&  msAPI_Timer_DiffTimeFromNow(g_KeyEffect_KeyPressTimer) > 200)
    {
        if(!(MApp_PVR_IsPlaybacking()||MApp_PVR_IsRecording()))
        {
            MApp_UiMenu_DrawSpecificComponent1(UI_CHANNEL_LIST_BG_X+20, UI_CHANNEL_LIST_BG_Y+UI_CHANNEL_LIST_BG_H+4, Draw_KeyPress_RED_DELETE, EN_CPSTATE_UNSELECT);
            g_KeyEffect_PrvBtnVal = BTN_NOTHING;
        }
    }
#endif

    /*[06]monitoring USB unplug on File Checking ======================================*/
    MApp_UiPvr_CheckFS_UsbMonitor();

    /*[07]EPG =========================================================================*/
    /*[07-1]EPG recorder wakeup =======================================================*/
    if(E_PVR_RECORDER_TIMEUP == g_PVR_RecordStatus)
    {
        //May Show Delay Message Here.
        g_PVR_RecordStatus = E_PVR_RECORDER_TIMEUP_TO_REC;
        g_u32RecorderPvrLeadingTime = msAPI_Timer_GetTime0();
    }
    else if(E_PVR_RECORDER_TIMEUP_TO_REC == g_PVR_RecordStatus)
    {
        if (msAPI_Timer_DiffTimeFromNow(g_u32RecorderPvrLeadingTime) >= (1000L * EPG_RECORDER_PVR_LEADING_TIME_s))
        {
        #if ENABLE_CI_PLUS
            //when signal come, we should wait CI stable
            {
                #define WAITSTABLECOUNT 1000
                static U16 _u16WaitCount = 0;
                if ((enMVDVideoStatus == MVD_GOOD_VIDEO) || MApi_AUDIO_IsMadLock())
                {
                    if(_u16WaitCount < WAITSTABLECOUNT)
                    {
                        ++_u16WaitCount;
                        return;
                    }
                }
                else
                    return;
                _u16WaitCount = 0;
            }
        #if (!ENABLE_CIPLUS_PVR)
            //if CI is setting content protect, do not record
            if(bIsURIBlock && msAPI_CI_CardDetect() && (EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
            {
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR)
                    || (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)
                          && g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
                {
                    g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);
                    return;
                }
            }
        #endif
        #endif

            if((msAPI_CM_GetCurrentServiceType()==E_SERVICETYPE_DATA) ||
                                     ((g_u16Current_PVR_VideoPID == MSAPI_DMX_INVALID_PID) &&
                                      (g_u16Current_PVR_AudioPID == MSAPI_DMX_INVALID_PID)    ))
             {
                 //not_allow_data_recording  not_allow_mpeg5 text_recording
                 MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_RECORD_CANTSUPPORT);//???
                 g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
                 MApp_UiPvr_RecordStop();
                 return;
             }

        #ifdef PVR_8051
            MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
        #endif

            if((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) ||
               (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED))
            {

            }
            else
            {
                MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_NO_DEVICE);
                g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
                if(MApp_EpgTimer_IsTriggerByTimer())
                {
                     MApp_EpgTimer_RecordQueueSetPath(MApp_EpgTimer_GetStartingIndex(), RECORD_PATH_DEFAULT);
                     MApp_EpgTimer_ClearStartingIndex();
                }
                MApp_UiPvr_RecordStop();
            #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
                if(MApp_GetActiveStandbyMode())
                {
                    g_bTimerTypeRecord = FALSE;
                    MApp_Standby_Init();
                }
            #endif
                  MApp_EpgTimer_DelPastTimeAndNoDeviceCurItems(MApp_GetLocalSystemTime());
                return;
            }

            if(MApp_GetSignalStatus() == SIGNAL_UNKNOWN||MApp_GetSignalStatus() == SIGNAL_UNLOCK||(MApp_ParentalControl_GetBlockStatus()))
            {
                MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_NO_SIGNAL);
                g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
                MApp_UiPvr_RecordStop();
                return;
            }

            if(PVRState != E_PVR_STATE_IDLE && PVRState != E_PVR_STATE_INIT && PVRState != E_PVR_STATE_WAITFORMAT)
            {
                g_PVR_RecordStatus = E_PVR_RECORDER_TIMEUP_RECORDING;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
                MApp_UiPvr_Browser_Init();
            #endif
                MApp_UiPvr_RecordStart(g_u16CiPinCode);
            }
            else
            {
                g_PVR_RecordStatus = E_PVR_RECORDER_IDLE;
            }
            g_u32RecorderPvrLeadingTime = 0xFFFFFFFF;
        }
        else if(STATE_TOP_DIGITALINPUTS != MApp_TopStateMachine_GetTopState())
        {
            return;
        }
    #ifdef PVR_8051
        else if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_EPG_RECORDER_REC_PREPARING)))
    #else//PVR_AEON
        else if(!(g_PVR_PopUpWarning == E_PVR_WARNING_EPG_RECORDER_REC_PREPARING))
    #endif
        {
            MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_EPG_RECORDER_REC_PREPARING);
        }
    }

    /*[UI Monitor End]=================================================================*/
}

/***************************************************************************************/

static EN_PVR_KEY_INPUT_RETURN _MApp_UiPvr_KeyProcessor(void);
void MApp_UiPvr_VirtualKeyProcessor(HWND current)
{
    PVR_DBG(printf("MApp_UiPvr_VirtualKeyProcessor:%d\n", current));

    switch(current)
    {
        default:
            return;
        case HWND_PVR_TIMESHIFT_ICON_PLAY:
        case HWND_PVR_PLAY_ICON_PLAY:
        case HWND_PVR_RECORDING_ICON_PLAY:
            u8KeyCode = KEY_PLAY;
            break;
        case HWND_PVR_TIMESHIFT_ICON_FB:
        case HWND_PVR_PLAY_ICON_FB:
        case HWND_PVR_RECORDING_ICON_FB:
            u8KeyCode = KEY_REWIND;
            break;
        case HWND_PVR_TIMESHIFT_ICON_FF:
        case HWND_PVR_PLAY_ICON_FF:
        case HWND_PVR_RECORDING_ICON_FF:
            u8KeyCode = KEY_FF;
            break;
        case HWND_PVR_TIMESHIFT_ICON_NEXT:
        case HWND_PVR_PLAY_ICON_NEXT:
        case HWND_PVR_RECORDING_ICON_NEXT:
            u8KeyCode = KEY_NEXT;
            break;
        case HWND_PVR_TIMESHIFT_ICON_PREV:
        case HWND_PVR_PLAY_ICON_PREV:
        case HWND_PVR_RECORDING_ICON_PREV:
            u8KeyCode = KEY_PREVIOUS;
            break;
        case HWND_PVR_TIMESHIFT_ICON_PAUSE:
        case HWND_PVR_PLAY_ICON_PAUSE:
        case HWND_PVR_RECORDING_ICON_PAUSE:
            u8KeyCode = KEY_PAUSE;
            break;
        case HWND_PVR_TIMESHIFT_ICON_STOP:
        case HWND_PVR_PLAY_ICON_STOP:
        case HWND_PVR_RECORDING_ICON_STOP:
            u8KeyCode = KEY_STOP;
            break;
    }

    if(EN_PVR_KEYRTN_PROCESSED == _MApp_UiPvr_KeyProcessor())
    {
        u8KeyCode = KEY_NULL;
    }
}

EN_PVR_KEY_INPUT_RETURN MApp_UiPvr_KeyProcessor(void)
{   //Key Filter for non-hotkey style new UI
//    enPVRState       PVRState       = MApp_PVR_StateMachineGet();

    switch (u8KeyCode)
    {
#if 0   //tempary not blocking key for test.
        case KEY_PLAY:
        case KEY_RECORD:
        case KEY_PAUSE:
//        case KEY_STOP:
        case KEY_FF:
        case KEY_REWIND:
        case KEY_NEXT:
        case KEY_PREVIOUS:

            if( E_PVR_STATE_TIMESHIFT == PVRState
/*
                ||E_PVR_STATE_RECORD == PVRState
                ||E_PVR_STATE_RECORDnPLAYBACK == PVRState
                ||E_PVR_STATE_PLAYBACK == PVRState
*/
            )
            {
                return EN_PVR_KEYRTN_PROCESSED;
            }
            break;
#endif

        default:
            //Do nothing
            break;

    }
    return _MApp_UiPvr_KeyProcessor();
}

static EN_PVR_KEY_INPUT_RETURN _MApp_UiPvr_KeyProcessor(void)
{
    enPVRState       PVRState       = MApp_PVR_StateMachineGet();           //<---only get state here
    enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();     //<---only get state here
    enRecordState    RecordState    = MApp_Record_StateMachineGet();        //<---only get state here
    enPlaybackState  PlaybackState  = MApp_Playback_StateMachineGet();      //<---only get state here

    EN_PVR_KEY_INPUT_RETURN rtnVal = EN_PVR_KEYRTN_NONE;

    if(MApp_TimeShift_IsRecordStoping())
    {
        return EN_PVR_KEYRTN_PROCESSED;
    }

    //(00)NULL KEY / ONLY IF DTV ======================================================//
    if (u8KeyCode == KEY_NULL || !(IsDTVInUse()) )
    {
        return EN_PVR_KEYRTN_NONE;
    }

    if (E_PVR_RECORDER_TIMEUP == g_PVR_RecordStatus)
    {
        u8KeyCode = KEY_NULL;
        return EN_PVR_KEYRTN_PROCESSED;
    }

#ifndef PVR_8051
    //prevent ZUI enter infinite loop if we are in PVR filebrowser select a file and press PLAY then immediately press FF
  #ifdef PVR_UTOPIA
    if( (KEY_FF == u8KeyCode || KEY_REWIND == u8KeyCode) && MApp_ZUI_GetState() != E_ZUI_STATE_RUNNING )
  #else
    if( (KEY_FF == u8KeyCode || KEY_REW == u8KeyCode) && MApp_ZUI_GetState() != E_ZUI_STATE_RUNNING )
  #endif
    {
        u8KeyCode = KEY_NULL;
        return EN_PVR_KEYRTN_PROCESSED;
    }
#endif

#if 0//def PVR_8051

    if(MENU_PVR_POP_UP_WARNING_MSG == g_u8MenuPageIndex &&
        KEY_STOP == u8KeyCode)
    {
        //do nothing, stop PVR
    }
    else if(MENU_PVR_POP_UP_WARNING_MSG == g_u8MenuPageIndex)
    {
        if(KEY_INDEX    == u8KeyCode  ||
           KEY_PLAY     == u8KeyCode  ||
           KEY_PAUSE    == u8KeyCode  ||
           KEY_RECORD   == u8KeyCode  ||
           /*KEY_STOP     == u8KeyCode  ||*/
           KEY_FF       == u8KeyCode  ||
           KEY_REW      == u8KeyCode  ||
           KEY_NEXT     == u8KeyCode  ||
           KEY_PREVIOUS == u8KeyCode    )
        {
            return EN_PVR_KEYRTN_PROCESSED;
        }
        else if(KEY_EXIT == u8KeyCode)
        {
            MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
        }
        return EN_PVR_KEYRTN_NONE;
    }
  #if MHEG5_NO_TTX_TOP_STATE
    else if(MENU_LOADING_MHEG_MSG == g_u8MenuPageIndex)
    {
        return EN_PVR_KEYRTN_NONE;
    }
  #endif
    else if((KEY_VOLUME       == u8KeyCode ||
             KEY_VOLUME_MINUS == u8KeyCode ||
             KEY_VOLUME_PLUS  == u8KeyCode   ) &&
             MApp_PVR_IsFastPlaybacking()         )
    {
        return EN_PVR_KEYRTN_PROCESSED;
    }
    else if ( (KEY_INFO == u8KeyCode)
            &&( (PVRState == E_PVR_STATE_PLAYBACK || PVRState == E_PVR_STATE_RECORDnPLAYBACK)
              &&( PlaybackState == E_PLAYBACK_STATE_PLAYBACKING
                ||PlaybackState == E_PLAYBACK_STATE_FASTFORWARD
                ||PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD
                ||PlaybackState == E_PLAYBACK_STATE_PAUSE) )
            )
    {
        return EN_PVR_KEYRTN_PROCESSED;
    }
#endif

    switch (u8KeyCode)
    {
        //(01)KEY_INDEX ===============================================================//
        case KEY_INDEX: //For PVR file list
        {
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_INDEX\n"));
            if((ENABLE_FRANCE_DTV==ENABLE)||(ENABLE_TIMESHIT==DISABLE))
            {
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            if(MApp_PVR_IsFileFormatVersionChanged())
            {
              #if 0//def PVR_8051
                if ( !(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED))
              #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED)))
              #endif

                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            else if(MApp_PVR_IsFileFormatCheckFail())
            {
                #if 0//def PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR)))
                #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_ERROR);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            if(!MApp_PVR_IsSystemReady())
            {
                #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
                #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

    #if(ENABLE_PVR_BROWSER)
        #ifdef PVR_8051
            MApp_UiMenu_PVR_Browser_Open();
            MApp_UiPvr_Browser_RedrawPage();
        #else
            MApp_UiPvr_Browser_Reset();
        #endif
    #endif

            _u32PvrBrowserUiUpdateTime = msAPI_Timer_GetTime0();

            #ifdef PVR_8051
            rtnVal = EN_PVR_KEYRTN_TO_MENU_STATE;
            #else//PVR_AEON
            rtnVal = EN_PVR_KEYRTN_TO_FILE_BROWSWER;
            #endif
            break;
        }

        //(02)KEY_UPDATE ==============================================================//
        case KEY_UPDATE:          //exit timeshift bar / recording icon / playback bar
        {
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_UPDATE\n"));

            /*[02-1]ui action =========================================================*/
            if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
            {
                _enPvrPageMode=EN_PVR_PAGE_BRIEF;
            }
            else if(_enPvrPageMode==EN_PVR_PAGE_BRIEF)
            {
                _enPvrPageMode = EN_PVR_PAGE_NORMAL;
            }
            rtnVal = EN_PVR_KEYRTN_PROCESSED;

            break;
        }

        //(03)KEY_PLAY ================================================================//
        case KEY_PLAY:          //start timeshift or record or playback
        {
            if(ENABLE_TIMESHIT==DISABLE)
            {
                MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_PLAYBACK_CANTSUPPORT);
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            switch (PVRState)
            {
                case E_PVR_STATE_TIMESHIFT:
                    MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_PLAY);
                    break;
                case E_PVR_STATE_RECORD:
                    MApp_ZUI_API_SetFocus(HWND_PVR_RECORDING_ICON_PLAY);
                    break;
                case E_PVR_STATE_RECORDnPLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
                    break;
                case E_PVR_STATE_PLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
                    break;
                default:
                    break;
            }
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_PLAY\n"));

            if (TimeShiftState == E_TIMESHIFT_STATE_RECORDING)
            {
                MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_FF, TRUE);
                MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_FB, TRUE);
                MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_PAUSE, TRUE);
            }
            else if(TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
            {
                U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();
                 if(!((u32RecordEndTime - u32RecordStartTime)<= (u32PlaybackTime+ UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)))
                {
                    MApp_ZUI_API_EnableWindow (HWND_PVR_TIMESHIFT_ICON_PAUSE, TRUE);
                }
            }

            if( ENABLE_FRANCE_DTV==ENABLE)
            {
               MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_PLAYBACK_CANTSUPPORT);
               rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            /*[03-1]PVR state action ==================================================*/
            msAPI_MSDCtrl_CheckDevices();
            if((msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_BUSY) &&
               (msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_IDLE) &&
               (msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_INSERTED))
            {
                #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
                #endif

                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(MApp_PVR_IsFileFormatCheckFail())
            {
            #ifdef PVR_8051
                if(MApp_PVR_IsFileFormatVersionChanged())
                {
                    if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED))
                    {
                        MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED);
                    }
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
                else if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR))
            #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR)))
            #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_ERROR);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(!MApp_PVR_IsSystemReady())
            {
            #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
            #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
            #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel)
            {
                if(PVRState == E_PVR_STATE_RECORD)
                {
                    MS_DEBUG_MSG(printf("not_allow_playback_when_record_all\n"));
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
            }

            /*[03-2]TIMESHIFT state action ============================================*/
            if(((TimeShiftState == E_TIMESHIFT_STATE_RECORDING            )  ||
                (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING          )  ||
                (TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)    ) &&
               ((MApp_TimeShift_IfPause()       ) ||
                (MApp_TimeShift_IfFastForward() ) ||
                (MApp_TimeShift_IfFastBackward())   ))
            {
                if(MApp_TimeShift_IfPause())
                {
                    U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                  //U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                    U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                    if((u32RecordEndTime - u32RecordStartTime)< UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#24 NOT_ALLOW_RESUME \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }
                    else
                    {
                        if (TimeShiftState == E_TIMESHIFT_STATE_RECORDING)
                        {
                             MApp_UiPvr_PlaybackStart();
                        }
                        else
                        {
                             MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                        }
                    }
                }
                else if(MApp_TimeShift_IfFastForward())
                {
                    U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                    U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                    U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                    if((u32RecordEndTime -u32RecordStartTime )<= (u32PlaybackTime + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#25 NOT_ALLOW_RESUME \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }
                    else
                    {
                        MApp_UiPvr_SubtitleResume();
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                    }
                }
                else if(MApp_TimeShift_IfFastBackward())
                {
                    MApp_UiPvr_SubtitleResume();
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                }
            }

            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            //<<<AB_LOOP_PROCESS_HERE
            else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) || (TimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
            {
                U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
              //U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                if(MApp_TimeShift_IfPause()== FALSE)
                {
                    if(u32PlaybackTime <= UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#26 NOT_ALLOW_AB_LOOP \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }
                }

                if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_NONE)      //set A
                {
                    _u32ABLoopStrTime = u32PlaybackTime +u32RecordStartTime;
                    MApp_TimeShift_ABLoop_SetA();
                    PVR_DBG(printf("[PVR_UI]: SET AB LOOP START TIME: %02lu:%02lu S\n",(_u32ABLoopStrTime)/60, (_u32ABLoopStrTime)%60));
                }
                else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set) //set B
                {
                    if(u32PlaybackTime +u32RecordStartTime <= (_u32ABLoopStrTime+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#27 NOT_ALLOW_AB_LOOP \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }

                    _u32ABLoopEndTime = u32PlaybackTime + u32RecordStartTime;
                    MApp_TimeShift_ABLoop_SetB();
                    PVR_DBG(printf("[PVR_UI]: SET AB LOOP END   TIME: %02lu:%02lu S\n",(_u32ABLoopEndTime)/60, (_u32ABLoopEndTime)%60));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, MApp_UiPvr_ABLoopGetJumpTime());
                }
            }
            //>>>AB_LOOP_PROCESS_HERE
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

            /*[03-3]PLAYBACK state action =============================================*/
            else if((PlaybackState == E_PLAYBACK_STATE_PAUSE)       ||
                    (PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)  )
            {
                MApp_UiPvr_SubtitleResume();
                MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
            }
            else if(PlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
            {
                //U32 u32RecordStartTime  = MApp_Playback_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_Playback_GetPlaybackTimeSec();
                //U32 u32RecordEndTime    = MApp_Playback_GetRecordEndTimeSec();
                U32 u32TotalTime        = MApp_Playback_GetTotalTimeSec();

                if(u32TotalTime<= (u32PlaybackTime + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#28 NOT_ALLOW_RESUME \n");)
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
                else
                {
                    MApp_UiPvr_SubtitleResume();
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_RESUME, 0);
                }
            }

            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            //<<<AB_LOOP_PROCESS_HERE
            else if((PlaybackState == E_PLAYBACK_STATE_PLAYBACKING))
            {
                U32 u32RecordStartTime  = MApp_Playback_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_Playback_GetPlaybackTimeSec();
              //U32 u32RecordEndTime    = MApp_Playback_GetRecordEndTimeSec();

                if(u32PlaybackTime <= UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#29 NOT_ALLOW_AB_LOOP \n");)
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }

                if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_NONE)          //set A
                {
                    _u32ABLoopStrTime = u32PlaybackTime+u32RecordStartTime;
                    MApp_Playback_ABLoop_SetA();
                    PVR_DBG(printf("[PVR_UI]: SET AB LOOP START TIME: %02lu:%02lu S\n",(_u32ABLoopStrTime)/60, (_u32ABLoopStrTime)%60));
                }
                else if(MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set)    //set B
                {
                    if(u32PlaybackTime + u32RecordStartTime<= (_u32ABLoopStrTime+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#30 NOT_ALLOW_AB_LOOP \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }

                    _u32ABLoopEndTime = u32PlaybackTime + u32RecordStartTime;
                    MApp_Playback_ABLoop_SetB();
                    PVR_DBG(printf("[PVR_UI]: SET AB LOOP END   TIME: %02lu:%02lu S\n",(_u32ABLoopEndTime)/60, (_u32ABLoopEndTime)%60));
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, MApp_UiPvr_ABLoopGetJumpTime());
                }
            }
            //>>>AB_LOOP_PROCESS_HERE
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

            /*[03-4]Direct play action ================================================*/
            else if((PVRState == E_PVR_STATE_WAIT || PVRState == E_PVR_STATE_RECORD)&&
                    (PlaybackState == E_PLAYBACK_STATE_WAIT))
            {
                MApp_Record_GetCurrentFileName(RECORD_PATH_DEFAULT, g_pu16TempFileName);

                if(*g_pu16TempFileName != 0)
                {
                    U32 u32RecordStartTime  = MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT);
                    U32 u32RecordEndTime    = MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT);

                    if((PVRState == E_PVR_STATE_RECORD) && ((u32RecordEndTime-u32RecordStartTime) < UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#31 NOT_ALLOW_INSTANT_PLAY \n");)
                    }
                    else
                    {
                        MApp_Record_GetCurrentFileName(RECORD_PATH_DEFAULT, g_pu16TempFileName);
                        MApp_UiPvr_PlaybackStart();
                    }
                }
            }

            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }
        //(04)KEY_PAUSE ===============================================================//
        case KEY_PAUSE:         //pause timeshift or playback
        {
            if(ENABLE_TIMESHIT==DISABLE)
            {
                 MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_TIMESHIFT_CANTSUPPORT);
                 rtnVal = EN_PVR_KEYRTN_PROCESSED;
                 break;
            }
            switch (PVRState)
            {
                case E_PVR_STATE_RECORDnPLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PAUSE);
                    break;
                case E_PVR_STATE_PLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PAUSE);
                    break;
                default:
                    break;
            }
            if ((E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == TimeShiftState) ||
                    (E_TIMESHIFT_STATE_PLAYBACKING == TimeShiftState))
            {
                MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_PAUSE);
            }
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_PAUSE\n"));
            if( ENABLE_FRANCE_DTV==ENABLE)
            {
                MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_TIMESHIFT_CANTSUPPORT);
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
#if ((ENABLE_CI_PLUS == 1) && (!ENABLE_CIPLUS_PVR))
            if(bIsURIBlock && msAPI_CI_CardDetect() && (EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
            {
            #ifdef PVR_8051
                if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
            #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
            #endif
                {
                #ifdef PVR_8051
                    MApp_UiMenu_PVR_CloseUI();
                #endif

                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);

                #ifdef PVR_8051
                    msAPI_Timer_Delayms(2000);
                #endif
                }
                break;
            }
#endif

            /*[04-1]system check ======================================================*/
            msAPI_MSDCtrl_CheckDevices();
            if((msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_BUSY) &&
               (msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_IDLE) &&
               (msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_INSERTED))
            {
                #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
                #endif

                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(MApp_PVR_IsFileFormatCheckFail())
            {
            #ifdef PVR_8051
            if(MApp_PVR_IsFileFormatVersionChanged())
            {
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED))
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            else if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR))
            #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR)))
            #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_ERROR);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(!MApp_PVR_IsSystemReady())
            {
            #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
            #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
            #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(PVRState == E_PVR_STATE_WAIT)
            {
                if(MApp_GetSignalStatus() == SIGNAL_UNKNOWN||MApp_GetSignalStatus() == SIGNAL_UNLOCK||(MApp_ParentalControl_GetBlockStatus())|| ENABLE_FRANCE_DTV==ENABLE
                    || (ENABLE_TIMESHIT==DISABLE))
                {
                    //printf("No signal or Parent blocked, can't timeshiftl\n");

                    #ifdef PVR_8051
                    if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) &&
                         ((g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL) || (g_PVR_PopUpWarning == E_PVR_WARNING_REC_SCRAMBLE))))
                    #else//PVR_AEON
                    if(!((MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)) &&
                         ((g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL) || (g_PVR_PopUpWarning == E_PVR_WARNING_REC_SCRAMBLE))))
                    if(!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_CLOCK_NOT_SET))
                    #endif
                    {
                        //MApp_UiMenu_PVR_CloseUI();                                        //<---message not required
                        //MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_SCRAMBLE);    //<---message not required
                    }

                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
            }

            if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel)
            {
                MS_DEBUG_MSG(printf("not_allow_timeshifting_when_record_all\n"));
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            /*[04-2]system time check =================================================*/
            else if(!MApp_UiMenuFunc_IsSystemClockSet() && !MApp_PVR_IsPlaybacking())
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#32 SYSTEM TIME NOT SET YET \n"));
            #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_CLOCK_NOT_SET))
            #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE) && g_PVR_PopUpWarning == E_PVR_WARNING_CLOCK_NOT_SET)))
            #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_CLOCK_NOT_SET);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(PVRState == E_PVR_STATE_WAIT)
            {
                if((msAPI_CM_GetCurrentServiceType()==E_SERVICETYPE_DATA) ||
                   ((g_u16Current_PVR_VideoPID == MSAPI_DMX_INVALID_PID) &&
                    (g_u16Current_PVR_AudioPID == MSAPI_DMX_INVALID_PID)    ))
                {
                     //not_allow_data_timeshift
                     //printf("not_allow_data_timeshifting\n");
                     MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_TIMESHIFT_CANTSUPPORT);
                     rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
            }

            /*[04-3]#AUTOMATICALLY SKIP PAUSE# ========================================*/
            if(TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
            {
                U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                if((((u32PlaybackTime == 0) &&
                     (u32RecordEndTime - u32RecordStartTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)) ||
                    ((u32PlaybackTime != 0) &&
                    (u32RecordEndTime - u32RecordStartTime - u32PlaybackTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))   ))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#33 SKIP PAUSE \n"));
                    //MApp_UiMenu_PVR_CloseUI();                          //->not to close OSD
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_TIMESHIFT_NO_DISK_SPACE);

                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
            }

            /*[04-4]ui action =========================================================*/

            #if 0
            #ifndef S3PLUS
            MApp_UiPvr_SubtitleBackupServices();
            #ifdef PVR_8051
                #ifndef DISABLE_TTX
                bResumeTTX = g_TTX_On;
                MApp_TTX_TeletextCommand(TTX_TV);
                #endif
            #else
                #ifdef ENABLE_TTX
                MApp_TTX_TeletextCommand(TTX_TV);
                #endif
            #endif
            #endif
            #endif
        #if MHEG5_ENABLE
            if((PVRState != E_PVR_STATE_RECORDnPLAYBACK && PVRState != E_PVR_STATE_PLAYBACK)
            &&(TimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING && TimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING))
            {
                 MApp_MHEG5_ExitMheg5();
            }
        #endif

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
            if(TRUE == MAPP_CIPVR_CICheckCCPinCapabilities(true, true, false))
            {
                bChangeMessageboxTimer = TRUE;
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_TIMESHIFT_CIPLUS_PVR_CAM_PINCODE_MSGBOX);
            }
            else
#endif
            {
                MApp_UiPvr_TimeshiftRecordStart(0xFFFF);
            }

            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }
        //(05)KEY_FF ==================================================================//
        case KEY_FF:            //fast foward
        {
            switch (PVRState)
            {
                case E_PVR_STATE_RECORDnPLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_FF);
                    break;
                case E_PVR_STATE_PLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_FF);
                    break;
                default:
                    break;
            }
            if ((E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == TimeShiftState) ||
                    (E_TIMESHIFT_STATE_PLAYBACKING == TimeShiftState))
                MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_FF);
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_FF\n"));

            if((PVRState == E_PVR_STATE_TIMESHIFT)
                 && (TimeShiftState != E_TIMESHIFT_STATE_WAIT))
            {
                U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                if((u32PlaybackTime < UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC) ||
                   ((u32RecordEndTime - u32RecordStartTime)<= (u32PlaybackTime+ UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#34 NOT_ALLOW_FAST_FORWARD \n");)
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
                else if((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
                    ((u32PlaybackTime != 0) &&
                    (u32RecordEndTime - u32RecordStartTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)))
                {
                        switch (PVRState)
                        {
                            case E_PVR_STATE_TIMESHIFT:
                                MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_PLAY);
                                break;
                            case E_PVR_STATE_RECORD:
                                MApp_ZUI_API_SetFocus(HWND_PVR_RECORDING_ICON_PLAY);
                                break;
                            case E_PVR_STATE_RECORDnPLAYBACK:
                                MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
                                break;
                            case E_PVR_STATE_PLAYBACK:
                                MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
                                break;
                            default:
                                break;
                        }

                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#35 NOT_ALLOW_FAST_FORWARD \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                }
                {   //block Radio
                    MEMBER_SERVICETYPE enServiceType;
                #if MHEG5_ENABLE
                    enServiceType = g_eCurrentUserServiceType;
                #else
                    enServiceType = msAPI_CM_GetCurrentServiceType();
                #endif
                    if(E_SERVICETYPE_RADIO == enServiceType )
                    {
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }
                }
            }
            else if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
                && (E_PLAYBACK_STATE_PLAYBACKING== PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState
                || E_PLAYBACK_STATE_FASTFORWARD == PlaybackState || E_PLAYBACK_STATE_FASTBACKWARD == PlaybackState))
            {
                //U32 u32RecordStartTime  = MApp_Playback_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_Playback_GetPlaybackTimeSec();
                //U32 u32RecordEndTime    = MApp_Playback_GetRecordEndTimeSec();
                U32 u32TotalTime        = MApp_Playback_GetTotalTimeSec();

                if((u32PlaybackTime <= UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC) ||
                   (u32TotalTime <= (u32PlaybackTime+ UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC)))
                {
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#36 NOT_ALLOW_FAST_FORWARD \n");)
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
            }

            if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
            #if(ENABLE_PVR_BROWSER)
                && (MApp_UiPvr_Browser_GetPlayingServiceType() == E_SERVICETYPE_RADIO)
            #else
                && (0) // Need modify ...
            #endif
                )
            {   //block Radio
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_FAST_FORWARD, 0);
            MApp_UiPvr_ABLoopStop();

            /*[05-1]TIMESHIFT state action ============================================*/
            if((PVRState == E_PVR_STATE_TIMESHIFT) &&
               (TimeShiftState != E_TIMESHIFT_STATE_WAIT))
            {
                MApp_UiPvr_SubtitlePause();
                #ifdef PVR_8051
                MApp_UiMenu2_SwitchToGwin(GWIN_PVR);
                #endif
           }

            /*[05-2]PLAYBACK state action =============================================*/
            if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
                && (E_PLAYBACK_STATE_PLAYBACKING== PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState
                || E_PLAYBACK_STATE_FASTFORWARD == PlaybackState || E_PLAYBACK_STATE_FASTBACKWARD == PlaybackState))
            {
                MApp_UiPvr_SubtitlePause();
                #ifdef PVR_8051
                MApp_UiMenu2_SwitchToGwin(GWIN_PVR);
                #endif
            }

            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }


        //(06)KEY_REW =================================================================//
        #ifdef PVR_UTOPIA
        case KEY_REWIND:        //fast rewind
        #else
        case KEY_REW:           //fast rewind
        #endif
        {
            switch (PVRState)
            {
                case E_PVR_STATE_RECORDnPLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_FB);
                    break;
                case E_PVR_STATE_PLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_FB);
                    break;
                default:
                    break;
            }
            if ((E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == TimeShiftState) ||
                    (E_TIMESHIFT_STATE_PLAYBACKING == TimeShiftState))
                MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_FB);
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_REW\n"));

            if((PVRState == E_PVR_STATE_TIMESHIFT)
                 && (TimeShiftState != E_TIMESHIFT_STATE_WAIT))
            {
                U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                if((u32PlaybackTime <= UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC) ||
                    ((TimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
                    ((u32PlaybackTime != 0) &&
                    (u32RecordEndTime - u32RecordStartTime) >= ((U32)MApp_TimeShift_GetRecordValidPeriodSec() - UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))))
                {
                    switch (PVRState)
                    {
                        case E_PVR_STATE_TIMESHIFT:
                            MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_PLAY);
                            break;
                        case E_PVR_STATE_RECORD:
                            MApp_ZUI_API_SetFocus(HWND_PVR_RECORDING_ICON_PLAY);
                            break;
                        case E_PVR_STATE_RECORDnPLAYBACK:
                            MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
                            break;
                        case E_PVR_STATE_PLAYBACK:
                            MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_PLAY);
                            break;
                        default:
                            break;
                    }
                    PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#37 NOT_ALLOW_FAST_BACKWARD \n");)
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }

                {   //block Radio
                    MEMBER_SERVICETYPE enServiceType;
                #if MHEG5_ENABLE
                    enServiceType = g_eCurrentUserServiceType;
                #else
                    enServiceType = msAPI_CM_GetCurrentServiceType();
                #endif
                    if(E_SERVICETYPE_RADIO == enServiceType )
                    {
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }
                }
            }

            if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
            #if(ENABLE_PVR_BROWSER)
                && (MApp_UiPvr_Browser_GetPlayingServiceType() == E_SERVICETYPE_RADIO)
            #else
                && (0) // Need modify ...
            #endif
                )
            {   //block Radio
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_FAST_BACKWARD, 0);
            MApp_UiPvr_ABLoopStop();

            /*[06-1]TIMESHIFT state action ============================================*/
            if(PVRState == E_PVR_STATE_TIMESHIFT
                && TimeShiftState != E_TIMESHIFT_STATE_WAIT)
            {
                MApp_UiPvr_SubtitlePause();
                #ifdef PVR_8051
                MApp_UiMenu2_SwitchToGwin(GWIN_PVR);
                #endif
            }

            /*[06-2]PLAYBACK state action =============================================*/
              if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
                && (E_PLAYBACK_STATE_PLAYBACKING== PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState
                || E_PLAYBACK_STATE_FASTFORWARD == PlaybackState || E_PLAYBACK_STATE_FASTBACKWARD == PlaybackState))
            {
                MApp_UiPvr_SubtitlePause();
                #ifdef PVR_8051 //-------------------------------------------------------
                MApp_UiMenu2_SwitchToGwin(GWIN_PVR);
                #endif //----------------------------------------------------------------
            }

            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }

        //(07)KEY_NEXT ================================================================//
        /*case KEY_NEXT:          //jump to next n seconds
        {
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_NEXT\n"));*/

            /*[07-1]PVR state action ==================================================*/
            /*if((PVRState != E_PVR_STATE_TIMESHIFT      ) &&
               (PVRState != E_PVR_STATE_RECORDnPLAYBACK) &&
               (PVRState != E_PVR_STATE_PLAYBACK       )   )
            {
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(MApp_TimeShift_IfFastForward() || MApp_TimeShift_IfFastBackward() ||
               (PlaybackState == E_PLAYBACK_STATE_FASTFORWARD) ||
               (PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)  )
            {
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }*/

            /*[07-2]TIMESHIFT state action ============================================*/
        /*#ifdef PVR_8051
            if(PVRState == E_PVR_STATE_TIMESHIFT
                && TimeShiftState != E_TIMESHIFT_STATE_WAIT)
            {
                if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                {
                    #ifdef PVR_UTOPIA
                    MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #else
                    msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #endif
                }

                if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Next, EN_CPSTATE_SELECT);
                else  if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Next_Brief, EN_CPSTATE_SELECT);
            }*/

            /*[07-3]PLAYBACK state action =============================================*/
           /* if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState) &&
               (E_PLAYBACK_STATE_PLAYBACKING == PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState))
            {
                if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                {
                    #ifdef PVR_UTOPIA
                    MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #else
                    msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #endif
                }

                if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Next, EN_CPSTATE_SELECT);
                else  if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Next_Brief, EN_CPSTATE_SELECT);
            }
        #endif*/

            /*[07-4]ap action =========================================================*/
            /*if((PVRState == E_PVR_STATE_TIMESHIFT && TimeShiftState != E_TIMESHIFT_STATE_WAIT &&  TimeShiftState != E_TIMESHIFT_STATE_RECORDING) ||
               ((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState) && (E_PLAYBACK_STATE_PLAYBACKING== PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState)) )
            {
                if(E_PVR_STATE_PLAYBACK == PVRState)
                {
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_FORWARD, UI_PVR_JUMP_SECOND);
                    MApp_UiPvr_ABLoopStop();
                }
                else
                { //continue Timeshift , except press STOP key
                    U32 u32PlaybackTime;
                    U32 u32RecordEndTime;

                    if(PVRState == E_PVR_STATE_TIMESHIFT)
                    {
                        u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                        u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();
                    }
                    else //(E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
                    {
                        u32PlaybackTime     = MApp_Playback_GetPlaybackTimeSec();
                        u32RecordEndTime    = MApp_Playback_GetRecordEndTimeSec();
                    }

                    if((u32RecordEndTime - u32PlaybackTime) >= (UI_PVR_JUMP_SECOND+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_FORWARD, UI_PVR_JUMP_SECOND);
                        MApp_UiPvr_ABLoopStop();
                    }
                    else if((u32RecordEndTime - u32PlaybackTime) > (UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_FORWARD, u32RecordEndTime-u32PlaybackTime-UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC);
                        MApp_UiPvr_ABLoopStop();
                    }
                }
            }

            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }*/
        //(08)KEY_PREVIOUS ============================================================//
        /*case KEY_PREVIOUS:      //jump to previous n seconds
        {
            PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_PREVIOUS\n"));*/

            /*[08-1]PVR state action ==================================================*/
            /*if((PVRState != E_PVR_STATE_TIMESHIFT) &&
               (PVRState != E_PVR_STATE_RECORDnPLAYBACK) &&
               (PVRState != E_PVR_STATE_PLAYBACK))
            {
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(MApp_TimeShift_IfFastForward() || MApp_TimeShift_IfFastBackward() ||
               (PlaybackState == E_PLAYBACK_STATE_FASTFORWARD) ||
               (PlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)  )
            {
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }*/

            /*[08-2]TIMESHIFT state action ============================================*/
            /*if(PVRState == E_PVR_STATE_TIMESHIFT
                && TimeShiftState != E_TIMESHIFT_STATE_WAIT)
            {
                if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                {
                    #ifdef PVR_UTOPIA
                    MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #else
                    msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #endif
                }

                if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                {
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Previous, EN_CPSTATE_SELECT);
                }
                else  if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                {
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Previous_Brief, EN_CPSTATE_SELECT);
                }
            }*/

            /*[08-3]PLAYBACK state action =============================================*/
            /*if((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
                && (E_PLAYBACK_STATE_PLAYBACKING== PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState))
            {
                if(u8OSDGWinTbl[GWIN_PVR] != GWIN_ID_INVALID)
                {
                    #ifdef PVR_UTOPIA
                    MApi_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #else
                    msAPI_GOP_GWIN_Switch2Gwin(u8OSDGWinTbl[GWIN_PVR]);
                    #endif
                }

                if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                {
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Previous, EN_CPSTATE_SELECT);
                }
                else  if(_enPvrPageMode == EN_PVR_PAGE_BRIEF)
                {
                    MApp_UiMenu_DrawSpecificComponentTbl2(0, 0, Draw_PVR_Icon_Previous_Brief, EN_CPSTATE_SELECT);
                }
            }*/

            /*[08-4]ap action =========================================================*/
            /*if((PVRState == E_PVR_STATE_TIMESHIFT
                && TimeShiftState != E_TIMESHIFT_STATE_WAIT &&  TimeShiftState != E_TIMESHIFT_STATE_RECORDING) ||
               ((E_PVR_STATE_PLAYBACK == PVRState || E_PVR_STATE_RECORDnPLAYBACK == PVRState)
                && (E_PLAYBACK_STATE_PLAYBACKING== PlaybackState || E_PLAYBACK_STATE_PAUSE == PlaybackState)) )
            {
                if(PVRState == E_PVR_STATE_TIMESHIFT)
                {
                    U32 u32RecordStartTime  = MApp_TimeShift_GetRecordStartTimeSec();
                    U32 u32PlaybackTime     = MApp_TimeShift_GetPlaybackTimeSec();
                  //U32 u32RecordEndTime    = MApp_TimeShift_GetRecordEndTimeSec();

                    if(u32PlaybackTime <= (u32RecordStartTime + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#37 NOT_ALLOW_JUMP_BACKWARD \n");)
                        rtnVal = EN_PVR_KEYRTN_PROCESSED;
                        break;
                    }
                    else if((u32PlaybackTime-UI_PVR_JUMP_SECOND) <= (u32RecordStartTime + UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC))
                    {
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, u32PlaybackTime-(u32RecordStartTime+UI_PVR_SAFE_TIMEGAP_TO_BORDER_SEC));
                    }
                    else
                    {
                        MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, UI_PVR_JUMP_SECOND);
                    }
                }
                else
                {
                    MApp_PVR_StateMachineInput(E_PVR_INPUT_PLAYBACK_JUMP_BACKWARD, UI_PVR_JUMP_SECOND);
                }
                MApp_UiPvr_ABLoopStop();
            }

            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }*/


        //(09)KEY_STOP ================================================================//
        case KEY_STOP:          //stop timeshift or record or playback
        case KEY_POWER:
        {
        #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
            if(g_bTimerTypeRecord)
            {
                if((u8KeyCode == KEY_POWER) || (u8KeyCode != KEY_POWER && MApp_GetActiveStandbyMode()))
                {
                    rtnVal = EN_PVR_KEYRTN_NONE;
                    break;
                }
            }
        #endif
            switch (PVRState)
            {
                case E_PVR_STATE_TIMESHIFT:
                    MApp_ZUI_API_SetFocus(HWND_PVR_TIMESHIFT_ICON_STOP);
                    break;
                case E_PVR_STATE_RECORD:
                    MApp_ZUI_API_SetFocus(HWND_PVR_RECORDING_ICON_STOP);
                    break;
                case E_PVR_STATE_RECORDnPLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_STOP);
                    break;
                case E_PVR_STATE_PLAYBACK:
                    MApp_ZUI_API_SetFocus(HWND_PVR_PLAY_ICON_STOP);
                    break;
                default:
                    break;
            }

            /*[09-1]PVR state action ==================================================*/
            if((PVRState != E_PVR_STATE_TIMESHIFT) &&
               (PVRState != E_PVR_STATE_RECORD) &&
               (PVRState != E_PVR_STATE_RECORDnPLAYBACK) &&
               (PVRState != E_PVR_STATE_PLAYBACK))
            {

                if (u8KeyCode == KEY_POWER)
                {
                    rtnVal = EN_PVR_KEYRTN_NONE;
                }
                else
                {
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                }
                break;
            }
            /*[09-2]TIMESHIFT state action ============================================*/
            /*[09-3]RECORD state action ===============================================*/
            /*[09-4]PLAYBACK state action =============================================*/

            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            //<<<AB_LOOP_PROCESS_HERE
            if((MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_A_set) || (MApp_UiPvr_GetABLoop_Status() == E_ABLOOP_B_set))    //stop AB Loop
            {
                PVR_AUTO_ACTION_DBG(printf("[PVR_UI]:AUTO#38 AB_LOOP->RESUME \n"));
                MApp_UiPvr_ABLoopStop();
            }
            //>>>AB_LOOP_PROCESS_HERE
            //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            else
            {
                if(PVRState == E_PVR_STATE_TIMESHIFT)
                {
                    MApp_UiPvr_PlaybackStop();
                    MApp_UiPvr_RecordStop();

                    //0976927: [SQC][Maya_084B][1st_ISDB][PVR] after Time shift, DTV shows no signal
                    //MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                }
                else if(PVRState == E_PVR_STATE_RECORD)
                {
                    g_PVR_PopUpWarning =E_PVR_WARNING_REC_PROCESSING;
                    MApp_ZUI_ACT_GetPvrDynamicText(HWND_PVR_WARNING_MESSAGE_MID_TXT);
                    MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_MESSAGE_PANE, SW_SHOW);
                    MApp_UiMenu_PVR_CloseUI();
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_PROCESSING);
                    //Record->Unplug Cable->Stop->No Signal + Last Picture(X)
                    //Should be black screen with No Signal
                    if(MApp_GetSignalStatus() == SIGNAL_UNLOCK)
                    {
                      #ifdef PVR_UTOPIA
                        MApp_ChannelChange_DisableAV(MAIN_WINDOW);
                      #else
                        MApp_ChannelChange_DisableAV();
                      #endif
                    }

                    if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel)
                    {
                        MApp_Dmx_EnableTableMonitor();
                    }
                    MApp_UiPvr_RecordStop();
                }
                else if((PVRState == E_PVR_STATE_RECORDnPLAYBACK) || (PVRState == E_PVR_STATE_PLAYBACK))
                {
                    MApp_UiPvr_PlaybackStop();  //<---become E_PVR_STATE_RECORD
                }
            }
            if (u8KeyCode == KEY_POWER)
            {
                rtnVal = EN_PVR_KEYRTN_NONE;
            }
            else
            {
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
            }
        #if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
            g_bTimerTypeRecord = FALSE;
        #endif
            break;
        }
        //(10)KEY_RECORD ==============================================================//
        case KEY_RECORD:        //start to record current program
        {
#if ((ENABLE_CI_PLUS == 1) && (!ENABLE_CIPLUS_PVR))
            if(bIsURIBlock && msAPI_CI_CardDetect() && (EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
            {
                #ifdef PVR_8051
                if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) && (g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL)))
                #endif
                {
                    #ifdef PVR_8051
                    MApp_UiMenu_PVR_CloseUI();
                    #endif

                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_URI_BLOCK);

                    //#ifdef PVR_8051
                    //msAPI_Timer_Delayms(2000);
                    //#endif
                 break;
                }
            }
#endif


            //check device
            msAPI_MSDCtrl_CheckDevices();
            if((msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_BUSY) &&
               (msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_IDLE) &&
               (msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)!=MSD_STATUS_INSERTED))
            {
                #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
                #endif

                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(MApp_PVR_IsFileFormatCheckFail())
            {
                #ifdef PVR_8051
                if(MApp_PVR_IsFileFormatVersionChanged())
                {
                    if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED))
                    {
                        MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_VERSION_CHANGED);
                    }
                    rtnVal = EN_PVR_KEYRTN_PROCESSED;
                    break;
                }
                else if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_DISK_FORMAT_ERROR)))
                #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_DISK_FORMAT_ERROR);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(!MApp_PVR_IsSystemReady())
            {
                #ifdef PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY))
                #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_USB_NOT_READY)))
                #endif

                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_USB_NOT_READY);
                }
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }

            if(!MApp_UiMenuFunc_IsSystemClockSet())
            {

              #if 0//def PVR_8051
                if(!(g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG && g_PVR_PopUpWarning == E_PVR_WARNING_CLOCK_NOT_SET))
              #else//PVR_AEON
                if((MApp_ZUI_GetActiveOSD() != E_OSD_PVR) ||
                    (!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_CLOCK_NOT_SET)))
              #endif
                {
                    MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_CLOCK_NOT_SET);
                }

              #if 0//def PVR_8051
                rtnVal = TRUE;
              #else//PVR_AEON
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
              #endif
                break;
            }


            if(E_PVR_STATE_RECORD == PVRState
                && E_RECORD_STATE_RECORDING == RecordState)
            {   //toggle record UI mode
                if(_enPvrPageMode == EN_PVR_PAGE_NORMAL)
                {
                    _enPvrPageMode = EN_PVR_PAGE_BRIEF;
                }
                else if(_enPvrPageMode==EN_PVR_PAGE_BRIEF)
                {
                    _enPvrPageMode = EN_PVR_PAGE_NORMAL;
                }
                 rtnVal = EN_PVR_KEYRTN_PROCESSED;
                 break;
            }
            else if(RecordState == E_RECORD_STATE_RECORDING)
            {   //For E_PVR_STATE_RECORDnPLAYBACK
                rtnVal = EN_PVR_KEYRTN_PROCESSED;
                break;
            }
            else if(PVRState == E_PVR_STATE_TIMESHIFT && TimeShiftState != E_TIMESHIFT_STATE_WAIT)
            {
                //MApp_UiPvr_PlaybackStop();    //<===NOT ALLOWED key_triggering RECORD in TIMESHIFT state
                //MApp_UiPvr_RecordStop();      //<===NOT ALLOWED key_triggering RECORD in TIMESHIFT state
                //MApp_UiPvr_RecordStart();     //<===NOT ALLOWED key_triggering RECORD in TIMESHIFT state
            }
            else if(PVRState == E_PVR_STATE_PLAYBACK)
            {
                                                //<===NOT ALLOWED key_triggering RECORD in PLAYBACK  state
            }
            else if(MApp_GetSignalStatus() == SIGNAL_UNKNOWN||MApp_GetSignalStatus() == SIGNAL_UNLOCK||(MApp_ParentalControl_GetBlockStatus()))
            {
                //printf("\r\nNo signal or program locked, can't record ");
                #ifdef PVR_8051
                if(!((g_u8MenuPageIndex == MENU_PVR_POP_UP_WARNING_MSG) &&
                     ((g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL) || (g_PVR_PopUpWarning == E_PVR_WARNING_REC_SCRAMBLE))))
                #else//PVR_AEON
                if(!((MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)) &&
                     ((g_PVR_PopUpWarning == E_PVR_WARNING_REC_NO_SIGNAL) || (g_PVR_PopUpWarning == E_PVR_WARNING_REC_SCRAMBLE))))
                if(!(MApp_ZUI_API_IsWindowVisible(HWND_PVR_WARNING_MESSAGE_PANE)&& g_PVR_PopUpWarning == E_PVR_WARNING_CLOCK_NOT_SET))
                #endif
                {
                    //MApp_UiMenu_PVR_CloseUI();                                        //<---message not required
                    //MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_SCRAMBLE);    //<---message not required
                }
            }
            else if((msAPI_CM_GetCurrentServiceType()==E_SERVICETYPE_DATA) ||
                    ((g_u16Current_PVR_VideoPID == MSAPI_DMX_INVALID_PID) &&
                     (g_u16Current_PVR_AudioPID == MSAPI_DMX_INVALID_PID)    ))
            {
                MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_PVR_RECORD_CANTSUPPORT);
                 //not_allow_data_recording
                 //printf("not_allow_data_recording\n");
            }
            else
            {
                if(stGenSetting.g_SysSetting.u8PVR_IsRecordAllChannel)
                {
                    MApp_Dmx_DisableTableMonitor();
                }
                PVR_DBG(printf("MApp_UiPvr_KeyProcessor- KEY_RECORD\n"));
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                if(TRUE == MAPP_CIPVR_CICheckCCPinCapabilities(true, true, false))
                {
                    bChangeMessageboxTimer = TRUE;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_CIPLUS_PVR_CAM_PINCODE_MSGBOX);
                }
                else
#endif
                {
                    MApp_UiPvr_RecordStart(0xFFFF);
                }
            }
            rtnVal = EN_PVR_KEYRTN_PROCESSED;
            break;
        }

        //(00)NON_OF_ABOVE ============================================================//
        default:
        {
            switch(u8KeyCode)
            {   //Close PVR UI to yield OSD display
                case KEY_CHANNEL_FAV_LIST:  case KEY_CHANNEL_RETURN:    case KEY_CHANNEL_PLUS:  case KEY_CHANNEL_MINUS:
                case KEY_AUDIO:                     case KEY_VOLUME:        case KEY_VOLUME_PLUS:           case KEY_VOLUME_MINUS:
                case KEY_0:                case KEY_1:                case KEY_2:                case KEY_3:
                case KEY_4:                case KEY_5:                case KEY_6:                case KEY_7:
                case KEY_8:                case KEY_9:
                case KEY_MTS:       case KEY_SUBCODE:       case KEY_SUBTITLE:            case KEY_PICTURE:
                case KEY_SOUND:     case KEY_ZOOM:      case KEY_SLEEP:
                case KEY_DISABLE_KEYPAD:        case KEY_TV:        case KEY_SCART:     case KEY_COMPONENT:
                case KEY_PC:     case KEY_HDMI:     case KEY_AV:        case KEY_SV:
                case KEY_MENU:      case KEY_EPG:             case KEY_SELECT:        case KEY_INFO:
                case KEY_INPUT_SOURCE:      case KEY_CHANNEL_LIST:      case KEY_FREEZE:
                #ifdef PVR_8051
                    MApp_UiMenu_PVR_CloseUI();
                #endif
                    break;
            }
            return EN_PVR_KEYRTN_NONE;
        }
        // ============================================================================//
    }

    MApp_UiPvr_UpdateUI();
    return rtnVal;
}

/***************************************************************************************/
/*###############################################################################################*/
/*////////////////////////////////////// ui file system /////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
typedef enum
{
    EN_PVR_CHKPRG_INITIAL,                  // 0
    EN_PVR_CHKPRG_SELECT_ACTIVE_DISK,       // 1
    EN_PVR_CHKPRG_START_CHECK,              // 2
    EN_PVR_CHKPRG_CHECK_USB,                // 3
    EN_PVR_CHKPRG_CHECK_PARTITION,          // 4
    EN_PVR_CHKPRG_CHECK_DISK,               // 5
    EN_PVR_CHKPRG_CHECK_MINIMUN_DISK_SIZE,  // 6
    EN_PVR_CHKPRG_CHECK_FORMAT,             // 7
    EN_PVR_CHKPRG_CHECK_BULK,               // 8
    EN_PVR_CHKPRG_FORMAT_SETTING,     // 9
    EN_PVR_CHKPRG_START_FORMAT,             // 10
    EN_PVR_CHKPRG_CREATE_FILE_SYSTEM,       // 11
    EN_PVR_CHKPRG_SET_TMSHFT_SIZE,          // 12
    EN_PVR_CHKPRG_CHECK_TMSHFT_SIZE,        // 13
    EN_PVR_CHKPRG_CHECK_SPEED,              // 14
} EN_PVR_CHECK_FILE_SYSTEM_PROGRESS;
static EN_PVR_CHECK_FILE_SYSTEM_PROGRESS _PvrCheckFSProgress;

static U16 _u16CheckBulkIdx = 1;

/***************************************************************************************/
static void MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHECK_FILE_SYSTEM_STATUS checkStatus)
{
    g_PVRCheckFSStatus = checkStatus;

    MApp_UiMenu_PVR_CheckFS_UpdateUI();

    //Special case for Check Speed item
    if(g_PVRCheckFSStatus >= EN_PVR_CHKSTS_CHECK_SPEED_START)
    {
#ifdef PVR_8051
        MApp_UiMenu_DrawSubMenuItems(PVR_CHECKFS_ITEM_CHECK_SPEED);
#endif
    }
}

/***************************************************************************************/
extern void MApp_PVR_ReleaseEvnId(void);

void MApp_UiPvr_CheckFS_FlowControl(void)
{
    BOOLEAN isContinue;
    isContinue = TRUE;

    while(isContinue)
    {
        isContinue = FALSE;

#if (PVR_CHECKFS_FLOW_DBG)
        {
            static EN_PVR_CHECK_FILE_SYSTEM_PROGRESS prv_State = EN_PVR_CHKPRG_INITIAL;
            if(prv_State != _PvrCheckFSProgress)
            {
                printf("CheckFS_State:%u->%u\n", prv_State, _PvrCheckFSProgress);
                prv_State = _PvrCheckFSProgress;
            }
        }
#endif

        switch(_PvrCheckFSProgress)
        {
            case EN_PVR_CHKPRG_SELECT_ACTIVE_DISK:
            {
                if ((g_u8PVRActiveDevice != MSD_USB_INDEX_START) && (g_u8PVRActiveDevice != MSD_USB_2_INDEX_START))
                    g_u8PVRActiveDevice = MSD_USB_INDEX_START;

                MApp_UiMenu_PVR_CheckFS_PopUIPage(MENU_PVR_CHECKFS_SELECT_DISK_MSG);
                _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
            }
                break;

            case EN_PVR_CHKPRG_START_CHECK:
                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_USB);
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_USB;
                isContinue = TRUE;
                break;

            case EN_PVR_CHKPRG_CHECK_USB:
                if((g_u8PVRActiveDevice == MSD_USB_INDEX_START && !(MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED))
                    || (g_u8PVRActiveDevice == MSD_USB_2_INDEX_START && !(MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED)))
                {
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_USB_NOT_CONNECT);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                    break;
                }
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_PARTITION;
                isContinue = TRUE;
                break;

            case EN_PVR_CHKPRG_CHECK_PARTITION:
            {
                U8 deviceIndex = msAPI_PVRFS_GetDeviceIndex();
                if(msAPI_PVRFS_IsDeviceRAWDisk(deviceIndex))
                {
                    MApp_UiMenu_PVR_CheckFS_PopUIPage(MENU_PVR_CHECKFS_CREATE_PARTITION_MSG);
                    break;
                }
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_DISK;
                isContinue = TRUE;
            }
                break;

            case EN_PVR_CHKPRG_CHECK_DISK:
            {
                U8 deviceIndex;
                U8 diskDriveIndex;

                deviceIndex=msAPI_PVRFS_GetDeviceIndex();
                diskDriveIndex=msAPI_PVRFS_GetDriveIndex();

                if(!msAPI_PVRFS_IsPartitionReady(diskDriveIndex, deviceIndex))
                {
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_NO_PARTITION);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                    break;
                }
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_MINIMUN_DISK_SIZE;
                isContinue = TRUE;
            }
                break;

            case EN_PVR_CHKPRG_CHECK_MINIMUN_DISK_SIZE:
            {
                U32 diskSize_MB = MApp_PVR_DiskGetAvailableSizeMB();
                if((MApp_FileBrowser_GetCurrentFileSystemType() == FILE_SYSTEM_TYPE_FAT) && (diskSize_MB < 512))
                {  //PVR not support when < 512
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_SIZE_FAIL);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                    break;
                }
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_FORMAT;
                isContinue = TRUE;
            }
                 break;

            case EN_PVR_CHKPRG_CHECK_FORMAT:
            {
                U8 diskDriveIndex;

                if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
                    msAPI_PVRFS_Initial(TRUE); //force to initiate again
                else msAPI_PVRFS_Initial(FALSE);
                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_FORMAT);
                diskDriveIndex = msAPI_PVRFS_GetDriveIndex();
                if(EN_PVR_CHKMOD_CHECK_ALL == g_PVRCheckFSMode && msAPI_PVRFS_IsFormated(diskDriveIndex))
                {
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_FORMAT_PASS);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_BULK;
                    isContinue = TRUE;
                }
                else
                {
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_FORMAT_SETTING;
                    isContinue = TRUE;
                }
            }
                break;

            case EN_PVR_CHKPRG_CHECK_BULK:
            {
                #ifdef PVR_8051
                BOOLEAN _IsFinished = TRUE; //FALSE->TRUE: Disable to check all Bulk FS due to performance issue.
                #endif

                _u16CheckBulkIdx = 1;

            #if (ENABLE_BULK_FILE_SYSTEM)
                #ifdef PVR_8051
                while(!_IsFinished)
                {
                    if(!msAPI_PVRFS_IsBulkFileReady(msAPI_PVRFS_GetDriveIndex(), &_u16CheckBulkIdx, &_IsFinished))
                    {
                        MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_BULK_FAIL);
                        break;
                    }
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_BULK);
                }
                #endif
            #endif

                if(EN_PVR_CHKSTS_CHECK_BULK_FAIL == g_PVRCheckFSStatus)
                {
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_FORMAT_SETTING;
                    isContinue = TRUE;
                }
                else
                {
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_TMSHFT_SIZE;
                    isContinue = TRUE;
                }
            }
                break;

            case EN_PVR_CHKPRG_FORMAT_SETTING:
            {
                g_u16FileSystemDiskSize_GB = 0;    //set default value to All
            #if (ENABLE_BULK_FILE_SYSTEM)
                msAPI_PVRFS_SetTotalDiskSizeUsedMB((U32)g_u16FileSystemDiskSize_GB * MEGA_PER_GIGA);
            #endif
                MApp_UiMenu_PVR_CheckFS_PopUIPage(MENU_PVR_CHECKFS_FORMAT_SETTING_MSG);
            }
                break;

            case EN_PVR_CHKPRG_START_FORMAT:
            #if (ENABLE_BULK_FILE_SYSTEM)
                msAPI_PVRFS_ResetCurrentCreateBulkNum();
            #endif
                MApp_UiMenu_PVR_CheckFS_PopUIPage(MENU_PVR_CHECKFS_FORMAT_PROGRESS_MSG);
                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_FORMAT_PROGRESS);
                if(MApp_PVR_DiskFormat((EN_PVRFS_FSTYPE )g_u8PvrFormatFsType))
                {
                    if((g_u8PvrFormatFsType == PVR_FS_N51FAT32) || (msAPI_PVRFS_IsLinuxFileSystemType((EN_PVRFS_FSTYPE)g_u8PvrFormatFsType)))
                    {
                        MApp_PVR_SetDiskDriveIndex(g_u8PVRActiveDisk, TRUE);  //create PVR folder
                        //MApp_UiMenu_MSG_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN, 0);
                        MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_OK);
                        //_PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                        MApp_Record_ClearCurrentFileName(RECORD_PATH_DEFAULT); //for instant play
                    #if(ENABLE_PVR_BROWSER)
                        MApp_UiPvr_Browser_DeInit();    //clear browser buffer
                    #endif
                        MApp_PVR_ReleaseEvnId();
                        _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_SPEED;
                        isContinue = TRUE;
                        break;
                    }
                    else
                    {
                        _PvrCheckFSProgress = EN_PVR_CHKPRG_CREATE_FILE_SYSTEM;
                        isContinue = TRUE;
                    }
                }
                else
                {
                    MApp_UiMenu_MSG_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN, 0);
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_FORMAT_ERROR);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                }
                MApp_Record_ClearCurrentFileName(RECORD_PATH_DEFAULT); //for instant play
                MApp_UiPvr_SubtitlePause();

              #if (ENABLE_SUBTITLE)
                MApp_Subtitle_SetInvalidPID();
              #endif

            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();    //clear browser buffer
            #endif
                break;

            case EN_PVR_CHKPRG_CREATE_FILE_SYSTEM:
            {
            #if (ENABLE_BULK_FILE_SYSTEM)
                BOOLEAN isFinished;

                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PROGRESS);
                msAPI_PVRFS_SetFileSystemType(PVR_FS_BULKFS);
                #ifndef PVR_8051
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CHANGE_TO_CREATE_PVR_FILE_SYSTEM_PLEASE_WAIT_TXT);
                #endif
                if(!MApp_PVR_DiskFormatCreateFolder())
                {
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CREATE_FOLDER_ERROR);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                    break;
                }

                while (MApp_PVR_DiskFormatCreateBulks(&isFinished))
                {
                    if(isFinished)
                    {
                        break;
                    }
                }

                if(!MApp_PVR_DiskFormatCreateIndexFile())
                {
                    MApp_UiMenu_MSG_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN, 0);
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CREATE_INDEX_ERROR);
                    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                    break;
                }

                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PASS);
            #endif
                _PvrCheckFSProgress = EN_PVR_CHKPRG_SET_TMSHFT_SIZE;
                isContinue = TRUE;
            }
                break;

            case EN_PVR_CHKPRG_SET_TMSHFT_SIZE:
                //set default size.
                g_u16TimeShiftDiskSize_GB = PVR_TIMESHIFT_SIZE_512M_NUM;
                MApp_PVR_TimeShiftSetRecordLengthMB(512);
                MApp_UiMenu_PVR_CheckFS_PopUIPage(MENU_PVR_CHECKFS_SET_TMSHFT_SIZE_MSG);
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_TMSHFT_SIZE;
                break;

            case EN_PVR_CHKPRG_CHECK_TMSHFT_SIZE:
                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_TMSHFT_SIZE);
                _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_SPEED;
                isContinue = TRUE;
                break;

            case EN_PVR_CHKPRG_CHECK_SPEED:
                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_SPEED_START);
                {
                    U16 speed = MApp_PVR_DiskCheckSpeed();
                    g_u16DiskSpeed = speed;
                    MApp_PVR_DiskSetSpeed(speed);
                }
                if((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) || (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED))
                {
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_CHECK_SPEED_PASS);
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_OK);
                }
                else
                {
                    MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_USB_NOT_CONNECT);
                }
                _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
                MApp_UiPvr_SubtitleResume();
                break;

            default:
            case EN_PVR_CHKPRG_INITIAL:
                MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_INITIAL);
                break;
        }
    }
}

/***************************************************************************************/
void MApp_UiPvr_CheckFS_SelectActiveDisk(void)
{
    _PvrCheckFSProgress = EN_PVR_CHKPRG_SELECT_ACTIVE_DISK;
    MApp_UiPvr_CheckFS_FlowControl();
}

/***************************************************************************************/
void MApp_UiPvr_CheckFS_StartCheckAll(void)
{
    g_PVRCheckFSMode = EN_PVR_CHKMOD_CHECK_ALL;
    _PvrCheckFSProgress = EN_PVR_CHKPRG_START_CHECK;
    MApp_UiPvr_SubtitlePause();
    #if(ENABLE_SUBTITLE)
    MApp_Subtitle_SetInvalidPID();
    #endif
    MApp_UiPvr_CheckFS_FlowControl();
    MApp_UiPvr_SubtitleResume();
}

/***************************************************************************************/
#if (ENABLE_BULK_FILE_SYSTEM)
void MApp_UiPvr_CheckFS_Confirm_CreatePartition(void)
{
    U8 deviceIndex = msAPI_PVRFS_GetDeviceIndex();

    if(msAPI_PVRFS_IsDeviceRAWDisk(deviceIndex))
    {
        U32 totalSector = msAPI_MSDCtrl_GetBlockNum(deviceIndex);
        U8 u8UserBrowserHandle = MApp_FileBrowser_GetEnvironment();
        U8 u8DriveIndex = MApp_MassStorage_GetCurrentDriveIndex();

        PVR_CHECKFS_FORMATING_DBG(printf("Un-partition disk found, create partition....\n"));
        msAPI_PVRFS_ClearMBR(deviceIndex, 0);
        msAPI_PVRFS_AddMainPartition(deviceIndex, 0, TRUE, 1, (totalSector-1)&~31);
        PVR_CHECKFS_FORMATING_DBG(printf("Create Done\n"));

        //Re-Check device since the disk was partitioned.
        msAPI_MSDCtrl_ResetDevice(deviceIndex);
        msAPI_MSDCtrl_CheckDevices();
        if (!msAPI_FCtrl_ActiveDevice(deviceIndex))
        {
            __ASSERT(0);
            return;
        }
        //Prepare file system
        MApp_FileBrowser_Destroy(u8UserBrowserHandle);
        if(!MApp_MassStorage_DriveConnect(u8DriveIndex))
        {
            //PVR_CHECKFS_FORMATING_DBG(printf("MApp_PVR_SetDiskDriveIndex Connect No Device\n"));
            return;
        }
        u8UserBrowserHandle = MApp_FileBrowser_Create(u8DriveIndex);
        if(u8UserBrowserHandle == INVALID_BROWSER_HANDLE)
        {
            //PVR_CHECKFS_FORMATING_DBG(printf("MApp_PVR_SetDiskDriveIndex Create File browser Failed\n"));
            return;
        }
        MApp_FileBrowser_SetEnvironment(u8UserBrowserHandle);
    }

    _PvrCheckFSProgress = EN_PVR_CHKPRG_CHECK_DISK;
    MApp_UiPvr_CheckFS_FlowControl();
}
#endif
/***************************************************************************************/
void MApp_UiPvr_CheckFS_StartFormat(void)
{
    g_PVRCheckFSMode = EN_PVR_CHKMOD_FORCE_FORMAT;
    _PvrCheckFSProgress = EN_PVR_CHKPRG_START_CHECK;
    MApp_UiPvr_CheckFS_FlowControl();
}

/***************************************************************************************/
void MApp_UiPvr_CheckFS_Cancel(void)
{
    _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
    MApp_UiPvr_CheckFS_FlowControl();
}

/***************************************************************************************/
void MApp_UiPvr_CheckFS_Confirm_Formating(void)
{
    _PvrCheckFSProgress = EN_PVR_CHKPRG_START_FORMAT;
}

/***************************************************************************************/
void MApp_UiPvr_CheckFS_Initial(void)
{
    g_PVRCheckFSStatus = EN_PVR_CHKSTS_INITIAL;
}

/***************************************************************************************/
#if (ENABLE_BULK_FILE_SYSTEM)
U8 MApp_UiPvr_CheckFS_GetCheckBulkPercent(void)
{
    U16 totalBulks = msAPI_PVRFS_GetTotalBulkCnt();

    if(totalBulks != 0)
    {
        return
        (U8)((U32)(_u16CheckBulkIdx-1)*100/totalBulks);
    }
    else
    {
        return 0;
    }
}
#endif
/***************************************************************************************/
static void MApp_UiPvr_CheckFS_UsbMonitor(void)
{
#ifdef PVR_8051
    if((_PvrCheckFSProgress != EN_PVR_CHKPRG_INITIAL)
        && (g_u8MenuPageIndex >= MENU_PVR_CHECKFS_MAIN && g_u8MenuPageIndex <= MENU_PVR_CHECKFS_SET_TMSHFT_SIZE_MSG))
    {
        if(!(MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) &&
           !(MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED))
        {
            if(g_u8MenuPageIndex != MENU_PVR_CHECKFS_MAIN)
            {
                MApp_UiMenu_MSG_GOTO_MAINMENU(MENU_PVR_CHECKFS_MAIN, 0);
            }
            MApp_UiPvr_CheckFS_ChangeCheckStatus(EN_PVR_CHKSTS_USB_NOT_CONNECT);
            _PvrCheckFSProgress = EN_PVR_CHKPRG_INITIAL;
        }
    }
#else
    static BOOLEAN bUpdateUI = FALSE;
    if((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) ||
       (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED))
    {
        bUpdateUI = TRUE;
    }
    else
    {
        if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR && bUpdateUI)
        {
            MApp_UiMenu_PVR_CheckFS_UpdateUI();
            bUpdateUI = FALSE;
        }
    }
#endif
}

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////////// ui file browser ////////////////////////////////////////*/
/*###############################################################################################*/

#if(ENABLE_PVR_BROWSER)

/***************************************************************************************/
#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

#define PVR_BROWSER_ITEM_PER_PAGE    10

U16 pF0[]={CHAR_F, CHAR_0, 0};
U16 pF1[]={CHAR_F, CHAR_1, 0};
U16 pF2[]={CHAR_F, CHAR_2, 0};
U16 pF3[]={CHAR_F, CHAR_3, 0};
U16 pF4[]={CHAR_F, CHAR_4, 0};
U16 pF5[]={CHAR_F, CHAR_5, 0};
U16 pF6[]={CHAR_F, CHAR_6, 0};
U16 pF7[]={CHAR_F, CHAR_7, 0};
U16 pF8[]={CHAR_F, CHAR_8, 0};
U16 pF9[]={CHAR_F, CHAR_9, 0};
U16 pF10[]={CHAR_F, CHAR_1, CHAR_0, 0};
U16 pF11[]={CHAR_F, CHAR_1, CHAR_1, 0};
U16 pF12[]={CHAR_F, CHAR_1, CHAR_2, 0};
U16 pF13[]={CHAR_F, CHAR_1, CHAR_3, 0};
U16 pF14[]={CHAR_F, CHAR_1, CHAR_4, 0};
U16 pF15[]={CHAR_F, CHAR_1, CHAR_5, 0};
U16 pF16[]={CHAR_F, CHAR_1, CHAR_6, 0};

static U8   gUiPVR_u8DriveNum;
static U8   gUiPVR_u8CurDriveIdx;

/***************************************************************************************/
void MApp_UiPvr_Browser_Init(void)
{
    if(MSD_USB_INDEX_START == g_u8PVRActiveDevice)
    {
        gUiPVR_u8DriveNum = msAPI_FCtrl_GetDriveCountByPort(MSD_PORT_1);
    }
    else if(MSD_USB_2_INDEX_START == g_u8PVRActiveDevice)
    {
        gUiPVR_u8DriveNum = msAPI_FCtrl_GetDriveCountByPort(MSD_PORT_2);
    }

    if(gUiPVR_u8DriveNum > 0)
    {
        gUiPVR_u8CurDriveIdx = g_u8PVRActiveDisk; //use active disk to initiate browser

        if(MApp_PvrBrowser_Create(gUiPVR_u8CurDriveIdx) == E_PVR_RET_OK)
        {
            g_PvrBrowser_TotalItem = MApp_PvrBrowser_GetTotalFileNum();
        }
        else
        {
            g_PvrBrowser_TotalItem = 0;
        }
    }

    g_PvrBrowser_PageStartItem = 0;
    g_PvrBrowser_FocusItem = 0;

    g_PVRBrowerSort = SORT_PROG_NAME;

#if 0//def PVR_8051
    if(g_u8MenuPageIndex == MENU_PVR_FILE_BROWSER)
    {
        MApp_UiPvr_Browser_RedrawPage();
    }
#endif
}

/***************************************************************************************/
void MApp_UiPvr_Browser_Reset(void)
{
    U16 u16StartIdx;

    g_PvrBrowser_TotalItem = MApp_PvrBrowser_GetTotalFileNum();
    g_PVRBrowerSort = SORT_PROG_NAME;

    u16StartIdx = MApp_PvrBrowser_GetPlayingIndex(g_PVRBrowerSort);
    if(u16StartIdx == PVR_NULL_FILE_INDEX)
    {
        u16StartIdx = MApp_PvrBrowser_GetRecordingIndex(g_PVRBrowerSort);
        if(u16StartIdx == PVR_NULL_FILE_INDEX)
        {
            g_PvrBrowser_FocusItem = 0;
            g_PvrBrowser_PageStartItem = 0;
        }
        else
        {
            g_PvrBrowser_FocusItem = u16StartIdx%PVR_BROWSER_ITEM_PER_PAGE;
            g_PvrBrowser_PageStartItem = u16StartIdx - g_PvrBrowser_FocusItem;
        }
    }
    else
    {
        g_PvrBrowser_FocusItem = u16StartIdx%PVR_BROWSER_ITEM_PER_PAGE;
        g_PvrBrowser_PageStartItem = u16StartIdx - g_PvrBrowser_FocusItem;
    }
}

/***************************************************************************************/
void MApp_UiPvr_Browser_DeInit(void)
{
    MApp_PvrBrowser_Destroy();

    g_PvrBrowser_TotalItem = 0;
    g_PvrBrowser_PageStartItem = 0;
    g_PvrBrowser_FocusItem = 0;
    MApp_UiMenu_PVR_Browser_FileInfo_Close();
    MApp_UiMenu_PVR_Browser_Close();
//#ifdef PVR_8051
//    if(g_u8MenuPageIndex == MENU_PVR_FILE_BROWSER)
//#endif
//    {
        //MApp_UiPvr_Browser_RedrawPage();
//    }
}
/***************************************************************************************/
#ifdef PVR_8051
void MApp_UiPvr_Browser_RedrawPage(void)
{
    U8 itemInPageIdx = 0;
    BOOLEAN FileAttr;

    g_PvrBrowser_CurrentDrawingItem = g_PvrBrowser_PageStartItem;

    for(itemInPageIdx = 0;
        itemInPageIdx < PVR_BROWSER_ITEM_PER_PAGE;
        g_PvrBrowser_CurrentDrawingItem++, itemInPageIdx++)
    {
        MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Brower_Item_DblBuf_On, EN_CPSTATE_SELECT);

        if(g_PvrBrowser_CurrentDrawingItem < g_PvrBrowser_TotalItem)
        {
            if(itemInPageIdx == g_PvrBrowser_FocusItem)
            {
                MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Brower_ListItem, EN_CPSTATE_SELECT);

                if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
                {
                    MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X + UI_FAVORITE_LIST_BG_W-20, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Browser_ListItem_ArrowLeft_Icon, EN_CPSTATE_SELECT);
                }
                else
                {
                    MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X + UI_FAVORITE_LIST_BG_W-20, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Browser_ListItem_ArrowRight_Icon, EN_CPSTATE_SELECT);
                }

            }
            else
            {
                MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Brower_ListItem, EN_CPSTATE_UNSELECT);
            }

            if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_IS_PLAYING,
                g_PVRBrowerSort, g_PvrBrowser_CurrentDrawingItem, (BYTE*)&FileAttr ,1)== E_PVR_RET_OK)
            {
                if(FileAttr)
                {
                    if(itemInPageIdx == g_PvrBrowser_FocusItem)
                        MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Browser_ListItem_Play_Icon, EN_CPSTATE_SELECT);
                    else
                        MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Browser_ListItem_Play_Icon, EN_CPSTATE_UNSELECT);
                }
                else
                {
                    if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_IS_RECORDING,
                        g_PVRBrowerSort, g_PvrBrowser_CurrentDrawingItem, (BYTE*)&FileAttr ,1)== E_PVR_RET_OK)
                    {
                        if(FileAttr)
                        {
                            if(itemInPageIdx == g_PvrBrowser_FocusItem)
                                MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Browser_ListItem_Record_Icon, EN_CPSTATE_SELECT);
                            else
                                MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Browser_ListItem_Record_Icon, EN_CPSTATE_UNSELECT);
                        }
                    }

                }
            }
        }
        else
        {
            MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Brower_ListItem_BG, EN_CPSTATE_UNSELECT);
        }

        MApp_UiMenu_DrawSpecificComponentTbl2(UI_CHANNEL_LIST_ITEM_X, UI_CHANNEL_LIST_ITEM_Y(itemInPageIdx), Draw_PVR_Brower_Item_DblBuf_Off, EN_CPSTATE_SELECT);
    }
}
#endif

/***************************************************************************************/
static void MApp_UiPvr_Browser_FileSort_Toggle(void)
{
#ifdef PVR_8051
    g_PVRBrowerSort = (SORT_TYPE)MApp_UiMenuFunc_DecIncValue_Cycle(MIA_INCVALUE, (U16)g_PVRBrowerSort, SORT_PROG_NAME, SORT_PROG_TIME, 1);
    MApp_UiMenu_DrawSpecificComponent1(0, 0, DrawPvrFileBrowserTitle, EN_CPSTATE_SELECT);
#else
    g_PVRBrowerSort = (SORT_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(1, g_PVRBrowerSort, SORT_PROG_NAME, SORT_PROG_TIME, 1);
#endif
}

/***************************************************************************************/
#ifdef PVR_8051
BOOLEAN MApp_UiPvr_Browser_KeyProcessor(void)
#else
BOOLEAN MApp_UiPvr_Browser_KeyProcessor(U8 KeyCode)
#endif
{
    enPVRState       PVRState       = MApp_PVR_StateMachineGet();           //<---only get state here
//  enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();     //<---only get state here
//  enRecordState    RecordState    = MApp_Record_StateMachineGet();        //<---only get state here
    enPlaybackState  PlaybackState  = MApp_Playback_StateMachineGet();      //<---only get state here

    BOOLEAN isKeyProcess = FALSE;

#ifdef PVR_8051
    switch(u8KeyCode)
#else
    switch(KeyCode)
#endif
    {
        case KEY_UP:
        {
        #ifdef PVR_8051
            BOOLEAN bFileInfoEnable = FALSE;
        #endif
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
#ifdef PVR_8051
            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
            {
                bFileInfoEnable = TRUE;
            }
            MApp_UiMenu_PVR_Browser_FileInfo_Close();
#endif
            if(g_PvrBrowser_FocusItem == 0)
            {
                if(g_PvrBrowser_PageStartItem == 0)
                {
                    g_PvrBrowser_PageStartItem = (g_PvrBrowser_TotalItem - 1)/PVR_BROWSER_ITEM_PER_PAGE*PVR_BROWSER_ITEM_PER_PAGE;
                    g_PvrBrowser_FocusItem = (g_PvrBrowser_TotalItem - 1)%PVR_BROWSER_ITEM_PER_PAGE;
                }
                else
                {
                    g_PvrBrowser_PageStartItem -= PVR_BROWSER_ITEM_PER_PAGE;
                    g_PvrBrowser_FocusItem = PVR_BROWSER_ITEM_PER_PAGE - 1;
                }
            }
            else
            {
                g_PvrBrowser_FocusItem--;
            }
#ifdef PVR_8051
            if(bFileInfoEnable)
            {
                MApp_UiMenu_PVR_Browser_FileInfo_Open();
            }
            MApp_UiPvr_Browser_RedrawPage();
#endif
            isKeyProcess = TRUE;
        }
            break;

        case KEY_DOWN:
        {
        #ifdef PVR_8051
            BOOLEAN bFileInfoEnable = FALSE;
        #endif
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
        #ifdef PVR_8051
            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
            {
                bFileInfoEnable = TRUE;
            }
            MApp_UiMenu_PVR_Browser_FileInfo_Close();
        #endif
            if((g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem) >= (g_PvrBrowser_TotalItem - 1))
            {   //end of all items
                g_PvrBrowser_FocusItem = 0;
                g_PvrBrowser_PageStartItem = 0;
            }
            else if(g_PvrBrowser_FocusItem >= PVR_BROWSER_ITEM_PER_PAGE - 1)
            {   //end of page
                g_PvrBrowser_FocusItem = 0;
                g_PvrBrowser_PageStartItem += PVR_BROWSER_ITEM_PER_PAGE;
            }
            else
            {
                g_PvrBrowser_FocusItem++;
            }
        #ifdef PVR_8051
            if(bFileInfoEnable)
            {
                MApp_UiMenu_PVR_Browser_FileInfo_Open();
            }
            MApp_UiPvr_Browser_RedrawPage();
        #endif
            isKeyProcess = TRUE;
        }
            break;

        case KEY_SELECT:
        case KEY_PLAY:
        {

            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }

            MApp_UiMenu_PVR_Browser_FileInfo_Close();

            //if(MApp_PVRBrowser_GetCurrEntryData(&E) == E_PVR_RET_OK)
            if(E_PVR_RET_OK != MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_FILE_NAME, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE*)g_pu16TempFileName, PVR_BROWSER_MAX_FILE_NAME_LEN*2))
            {
                break;
            }
            if(PlaybackState==E_PLAYBACK_STATE_PLAYBACKING)
            {
                MApp_UiPvr_PlaybackStop();
            }
            else if(PVRState == E_PVR_STATE_TIMESHIFT)
            {
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_RecordStop();
            }
       //     MApp_UiMenu_PVR_OpenUI(MENU_PVR_PLAYBACK);
            MApp_UiPvr_PlaybackStart();
            MApp_UiMenu_PVR_Browser_FileInfo_Close();
            MApp_UiMenu_PVR_Browser_Close();

            isKeyProcess = TRUE;
        }
            break;
#ifdef PVR_8051
        case KEY_INFO:
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
            MApp_UiMenu_PVR_Browser_FileInfo_Toggle();
            isKeyProcess = TRUE;
            break;

        case KEY_RIGHT:
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
            if(!msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
            {
                MApp_UiMenu_PVR_Browser_FileInfo_Open();
                MApp_UiPvr_Browser_RedrawPage();
            }
            isKeyProcess = TRUE;
            break;

        case KEY_LEFT:
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
            {
                MApp_UiMenu_PVR_Browser_FileInfo_Close();
                MApp_UiPvr_Browser_RedrawPage();
            }
            isKeyProcess = TRUE;
            break;
#endif

        case KEY_RED:
        {   //Delete file...
            //Not allowed to perform deleting file when recording/playback
            U32 Durtion = 0;
            /*if(g_PvrBrowser_TotalItem != 0)
            {
            MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_WARNING_MESSAGE_PANE, SW_SHOW); //need to add?
            }*/
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
            if(!(MApp_PVR_IsPlaybacking() || MApp_PVR_IsRecording()))
            {
                //PVR_UI_BROWSER_ENTRY E;
            #ifdef PVR_8051
                BOOLEAN bFileInfoEnable = FALSE;

                if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
                {
                    bFileInfoEnable = TRUE;
                }

                MApp_UiMenu_DrawSpecificComponent1(UI_CHANNEL_LIST_BG_X+20, UI_CHANNEL_LIST_BG_Y+UI_CHANNEL_LIST_BG_H+4, Draw_KeyPress_RED_DELETE, EN_CPSTATE_SELECT);
                g_KeyEffect_KeyPressTimer = msAPI_Timer_GetTime0();
                g_KeyEffect_PrvBtnVal = BTN_RED;
            #endif
                if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                    msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
                {
                    MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_DURATION,
                        g_PVRBrowerSort,g_PvrBrowser_PageStartItem+g_PvrBrowser_FocusItem, (BYTE*)&Durtion ,sizeof(U32));
                    if(Durtion > 600) //300MB(bit rate 0.5M)
                    {
                #ifdef PVR_8051
                        MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_PROCESSING);
                #else
                       MS_DEBUG_MSG(printf("Show UI here\n"));
                        //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_PVR_BROWSER_SHOW_PROCESS_MSG);
                #endif
                    }
                }

                if(MApp_PvrBrowser_DeleteFileEntry(g_PVRBrowerSort,g_PvrBrowser_PageStartItem+g_PvrBrowser_FocusItem)==E_PVR_RET_OK)
                {
                    if(Durtion > 600) //300MB(bit rate 0.5M)
                    {
                #ifdef PVR_8051
                       MApp_UiMenu_PVR_Close_PVR_BROWSER_Warning_Msg();
                #else
                    MS_DEBUG_MSG(printf("Show UI here\n"));
                    //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_PVR_BROWSER_CLOSE_PROCESS_MSG);
                #endif
                    }

                    if((g_PvrBrowser_FocusItem+g_PvrBrowser_PageStartItem) == (g_PvrBrowser_TotalItem-1)) //latest one
                    {
                        if(g_PvrBrowser_FocusItem==0) //change page
                        {
                            if(g_PvrBrowser_PageStartItem > 0)//total item ove one page
                            {
                                g_PvrBrowser_PageStartItem -= PVR_BROWSER_ITEM_PER_PAGE;
                                g_PvrBrowser_FocusItem = PVR_BROWSER_ITEM_PER_PAGE-1;
                            }
                            else
                            {
                                g_PvrBrowser_FocusItem = 0;
                            }
                        }
                        else
                        {
                            g_PvrBrowser_FocusItem--;
                        }
                    }
                    g_PvrBrowser_TotalItem--;
                    if(g_PvrBrowser_TotalItem == 0)
                    {
                        MApp_Record_ClearCurrentFileName(RECORD_PATH_DEFAULT);
                    }

                    #ifdef PVR_8051
                    MApp_UiMenu_PVR_Browser_FileInfo_Close();
                        if(bFileInfoEnable && g_PvrBrowser_TotalItem>0)
                        {
                            MApp_UiMenu_PVR_Browser_FileInfo_Open();
                        }
                    #endif
                    MApp_UiPvr_Browser_RedrawPage();
                }
                else
                {
                    __ASSERT(0);
                }
            }
        }
            //MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_WARNING_MESSAGE_PANE, SW_HIDE);
            isKeyProcess = TRUE;
            break;

        case KEY_INDEX:
        {
            SORT_TYPE OldSortType = g_PVRBrowerSort;
            U16 NewAbsoluteIndex;
        #ifdef PVR_8051
            BOOLEAN bFileInfoEnable = FALSE;

            if(msAPI_GOP_GWIN_IsGWINEnabled(u8OSDGWinTbl[GWIN_PVR_FILE_INFO]))
            {
                bFileInfoEnable = TRUE;
            }

            MApp_UiMenu_DrawSpecificComponent1(UI_CHANNEL_LIST_BG_X+20+74+74, UI_CHANNEL_LIST_BG_Y+UI_CHANNEL_LIST_BG_H+4, Draw_KeyPress_INDEX, EN_CPSTATE_SELECT);

            g_KeyEffect_KeyPressTimer = msAPI_Timer_GetTime0();
            g_KeyEffect_PrvBtnVal = BTN_INDEX;
       #endif
            MApp_UiPvr_Browser_FileSort_Toggle();
            if(g_PvrBrowser_TotalItem == 0)
            {
                isKeyProcess = TRUE;
                break;
            }
            NewAbsoluteIndex = MApp_PvrBrowser_ConvertIndex(OldSortType,g_PvrBrowser_PageStartItem+g_PvrBrowser_FocusItem, g_PVRBrowerSort);
            if(NewAbsoluteIndex == PVR_NULL_FILE_INDEX)
            { //error occurred, restore data
                g_PVRBrowerSort = OldSortType;
                NewAbsoluteIndex = g_PvrBrowser_PageStartItem+g_PvrBrowser_FocusItem;
            }
            g_PvrBrowser_FocusItem = NewAbsoluteIndex%PVR_BROWSER_ITEM_PER_PAGE;
            g_PvrBrowser_PageStartItem = NewAbsoluteIndex - g_PvrBrowser_FocusItem;

        #ifdef PVR_8051
            if(bFileInfoEnable)
            {
                MApp_UiMenu_PVR_Browser_FileInfo_Open();
            }
            MApp_UiPvr_Browser_RedrawPage();
        #endif
            isKeyProcess = TRUE;
        }
            break;

        case KEY_EXIT:
            MApp_UiMenu_PVR_Browser_FileInfo_Close();
            MApp_UiMenu_PVR_Browser_Close();
            isKeyProcess = TRUE;
            break;

    }

    return isKeyProcess;
}

/***************************************************************************************/
static void MApp_UiPvr_Browser_AddProgramme(U16* _pu16Filename, U32 recStartTime)
{
    U8 u8len;
    PVR_UI_BROWSER_ENTRY E;

    memset(&E, 0, sizeof(PVR_UI_BROWSER_ENTRY));

    UnicodeCpy((S8 *)&(E.u16FileName[0]), (S8 *) _pu16Filename);

#ifdef PVR_8051
    UnicodeCpy((S8*)E.u16ChannelName, (S8*)MApp_UiMenu_String(CURPROGRAMNUMBERTEXT));
    u8len = UnicodeLen((S8*)E.u16ChannelName);
    E.u16ChannelName[u8len++] = CHAR_SPACE;
    UnicodeCpy((S8*)&E.u16ChannelName[u8len], (S8*)MApp_UiMenu_String(CURPROGRAMNAMETEXT));
#else//PVR_AEON
    UnicodeCpy((S8*)E.u16ChannelName, (S8*)MApp_ZUI_GetCurrentChNumber());
    u8len = UnicodeLen((S8*)E.u16ChannelName);
    E.u16ChannelName[u8len++] = CHAR_SPACE;
    E.u16ChannelName[u8len] = 0;
    MApp_UiPvr_GetChannelString((U16*)&E.u16ChannelName[u8len]);
#endif

    if(MApp_EpgTimer_IsTriggerByTimer())
    {
        if(MApp_EpgTimer_GetStartingEventName(E.u16ProgramName) == TRUE)
        {
    #ifdef PVR_8051
        UnicodeCpy((S8*)E.u16ProgramName, (S8*)MApp_UiMenu_String (INFO_EVENTTITLETEXT));
    #else
        UnicodeCpy((S8*)E.u16ProgramName, (S8*)MApp_UiPvr_GetProgramString());
    #endif
        }
    }
    else
    {
    #ifdef PVR_8051
        UnicodeCpy((S8*)E.u16ProgramName, (S8*)MApp_UiMenu_String (INFO_EVENTTITLETEXT));
    #else
        UnicodeCpy((S8*)E.u16ProgramName, (S8*)MApp_UiPvr_GetProgramString());
    #endif
    }

//save program description
#ifdef PVR_8051
    {
        U16* p_string_buffer = (U16*)MApp_UiMenu_String(INFO_EVENTEXTENDEDTEXT);
        p_string_buffer[PVR_BROWSER_MAX_PROGRAM_DESC_LEN -1] = 0;
        UnicodeCpy((S8*)E.u16ProgDesc, (S8*)p_string_buffer);
    }
#else
    {
        U16* p_string_buffer = MApp_UiPvr_GetProgramDesc();
        p_string_buffer[PVR_BROWSER_MAX_PROGRAM_DESC_LEN -1] = 0;
        UnicodeCpy((S8*)E.u16ProgDesc, (S8*)p_string_buffer);
    }
#endif
    E.u32StartTime = recStartTime;
    E.u32Duration = 0;

#if MHEG5_ENABLE
    E.enServiceType = g_eCurrentUserServiceType;
#else
    E.enServiceType = msAPI_CM_GetCurrentServiceType();
#endif

    if(MApp_PvrBrowser_AddNewEntry(&E) == E_PVR_RET_OK)
    {
        g_PvrBrowser_TotalItem++;
    }
    else
    {
        __ASSERT(0);
    }
}

/***************************************************************************************/
void MApp_UiPvr_Browser_UpdateRecordingAttr(void)
{
    U16 RecFileName[RECORD_NAME_LENGTH];


    memset(&RecFileName,0,sizeof(RecFileName));

    MApp_PvrBrowser_GetRecordingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)RecFileName, RECORD_NAME_LENGTH*2);

#ifdef PVR_8051
    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_NAME, RecFileName, (BYTE*)MApp_UiMenu_String(INFO_EVENTTITLETEXT));
#else//PVR_AEON
    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_NAME, RecFileName, (BYTE*)MApp_UiPvr_GetProgramString());
#endif

    {
#ifdef PVR_8051
        U16* p_string_buffer = (U16*)MApp_UiMenu_String(INFO_EVENTEXTENDEDTEXT);
#else
        U16* p_string_buffer = MApp_UiPvr_GetProgramDesc();
#endif
        p_string_buffer[PVR_BROWSER_MAX_PROGRAM_DESC_LEN -1] = 0;
        MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_DESC, RecFileName, (BYTE*)p_string_buffer);
    }

    //update UI
    #ifdef PVR_8051

    #else//PVR_AEON
        MApp_ZUI_ACT_RenewPvrUI();
    #endif
}

/***************************************************************************************/
MEMBER_SERVICETYPE MApp_UiPvr_Browser_GetPlayingServiceType(void)
{
    MEMBER_SERVICETYPE serviceType;
    if(E_PVR_RET_OK == MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_SERVICE_TYPE, (BYTE*)&serviceType, sizeof(MEMBER_SERVICETYPE)))
    {
        return serviceType;
    }
    else
    {
        return E_SERVICETYPE_INVALID;
    }
}

#endif

/***************************************************************************************/

//BOOLEAN code Compile_mapp_uipvr;

#else

//BOOLEAN code Compile_mapp_uipvr;

#endif//ENABLE_PVR

#undef MAPP_UIPVR_C

