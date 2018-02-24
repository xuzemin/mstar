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

#define MAPP_ZUI_ACTAUDIOVOLUME_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MsCommon.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_EventNotify.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "MApp_ZUI_ACTaudiovolume.h"
#include "MApp_Func_AudioVolume.h"
#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_GlobalFunction.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif
#if ENABLE_KEY_TO_SPEECH
#include "MApp_KeyToSpeech.h"
#include "MApp_IR.h"
#endif

/////////////////////////////////////////////////////////////////////

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);


void MApp_ZUI_ACT_AppShowAudioVolume(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_AUDIO_VOLUME;

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
        ZUI_AUDIO_VOLUME_XSTART, ZUI_AUDIO_VOLUME_YSTART,
        ZUI_AUDIO_VOLUME_WIDTH, ZUI_AUDIO_VOLUME_HEIGHT);

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
	
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_VOLUME_MUTE_PANE, SW_HIDE);
    //MApp_ZUI_API_ShowWindow(HWND_VOLUME_EAS_PANE, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_AUDIO_VOLUME_CONFIG_PANE, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_AUDIO_VOLUME_CONFIG_ICON, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_AUDIO_VOLUME_CONFIG_BAR, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_AUDIO_VOLUME_CONFIG_TEXT, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_VOLUME_CONFIG_PANE, SW_HIDE);
    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_SHOWUP, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleAudioVolumeKey(VIRTUAL_KEY_CODE key)
{
    //note: don't do anything here! keys will be handled in state machines
    //      moved to MApp_TV_ProcessAudioVolumeKey()
    UNUSED(key);
    ZUI_DBG_FAIL(printf("[ZUI]IDLEKEY\n"));
    //ABORT();
    return FALSE;
}

void MApp_ZUI_ACT_TerminateAudioVolume(void)
{
    ZUI_MSG(printf("[]term:volume\n"));
    //enAudioVolumeState = _enTargetAudioVolumeState;
}
void MApp_Ui_AudioVolumePage_Notify(AUDIO_VOLUME_PAGE_NOTIFY_TYPE enAudioVolumeNotify, BOOL para1)
{
    switch(enAudioVolumeNotify)
    {
        case EN_AUDIO_VOLUME_PAGE_NOTIFY_SHOW_HIDE_ARC_DISCONNECT:
            MApp_ZUI_API_ShowWindow(HWND_ARC_DISCONNECT_WINDOW,para1);
            break;
        case EN_AUDIO_VOLUME_PAGE_NOTIFY_SHOW_HIDE_POWER_AMPLIFIER:
            MApp_ZUI_API_ShowWindow(HWND_VOLUME_POWER_AMPLIFIER,para1);
            break;
        case EN_AUDIO_VOLUME_PAGE_NOTIFY_VOLUME:
			MApp_ZUI_API_ShowWindow(HWND_AUDIO_VOLUME_CONFIG_PANE,TRUE);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_AUDIO_VOLUME_CONFIG_PANE);

        #if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Say_AudioVolume();
        #endif
            break;
        default:
            break;
    }
}


BOOLEAN MApp_ZUI_ACT_ExecuteAudioVolumeAction(U16 act)
{
    //stUserSoundSettingType *pstSoundSetting = NULL;
    //MApp_GetGenSetting(EN_GENSETTING_CLASS_SOUND, (void *)&pstSoundSetting);
    switch(act)
    {

        case EN_EXE_CLOSE_CURRENT_OSD:
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return (act != EN_EXE_POWEROFF); // return FALSE for KEY_POWER

        case EN_EXE_RESET_AUTO_CLOSE_TIMER:
            //reset timer if any key
            MApp_ZUI_API_ResetTimer(HWND_AUDIO_VOLUME_CONFIG_PANE, 0);
            return FALSE;

        case EN_EXE_DEC_AUDIO_VOLUME:
        case EN_EXE_INC_AUDIO_VOLUME:
        {
            U8 tempflag = (act==EN_EXE_INC_AUDIO_VOLUME);
            MApp_FuncExec_AudioVolume(EN_FUNC_AUDIO_VOLUME_ADJ_VOLUME,&tempflag);
        #if ENABLE_KEY_TO_SPEECH
            if(!MApp_KeyIsReapeatStatus())
            {
                if(act == EN_EXE_INC_AUDIO_VOLUME)
                    MApp_KTS_Say(EN_KTS_VOLUME_UP);
                else
                    MApp_KTS_Say(EN_KTS_VOLUME_DOWN);
            }
        #endif
            return TRUE;
        }

    }
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetAudioVolumeDynamicText(HWND hwnd)
{
    // Marked it by coverity_296
    //U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_AUDIO_VOLUME_CONFIG_TEXT:
        {
            U8 tempflag;
            MApp_FuncExec_AudioVolume(EN_FUNC_AUDIO_VOLUME_GET_VOLUME,&tempflag);
            return MApp_ZUI_API_GetU16String(tempflag/5);
        }
    }

    return 0; //for empty string....
}



S16 MApp_ZUI_ACT_GetAudioVolumeDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_AUDIO_VOLUME_CONFIG_BAR:
            return stGenSetting.g_SoundSetting.Volume;
    }

    return 0; //for empty  data
}

/////////////////////////////////////////////////////////
// Customize Window Procedures
/*
S32 MApp_ZUI_ACT_AudioVolumeWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                //setting AP timeout, auto close
                MApp_ZUI_API_SetTimer(hwnd, 0, HOT_MENU_TIME_OUT_3SEC);
            }
            break;

        case MSG_TIMER:
            {
                //if the time is up, kill the timer and then close AP!
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            break;


    }

    return DEFAULTWINPROC(hwnd, msg);
}
*/

#undef MAPP_ZUI_ACTAUDIOVOLUME_C
