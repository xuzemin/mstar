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

#define MAPP_ZUI_ACTMSGBOX_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTeffect.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_ZUI_ACTmsgbox.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_UiMenuDef.h"
#include "MApp_Sleep.h"
#include "mapp_videoplayer.h"
#include "MApp_ZUI_ACTdmp.h"
#include "mapp_mplayer.h"

#include <string.h>
#include "msAPI_Memory.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_BlockSys.h"
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "MApp_Scan.h"
#endif

#if ENABLE_USB_DEVICE_LIST
#include "MApp_MassStorage.h"
#include "MApp_TopStateMachine.h"
#include "MApp_ChannelChange.h"
#include "MApp_InputSource.h"
#endif
#include "MApp_MenuFunc.h"
#if ENABLE_EWS
#include "MApp_EWS.h"
#include "mapp_si.h"
extern U16 u16EWS_ShowStartPosition;
extern MS_EWSSETTING stEwsSettingData;
#endif

#if(ENABLE_ATSC)
#include "MApp_VChip.h"
#include "MApp_UiMenuStr_ATSC.h"
#include "MApp_GlobalFunction.h"
#endif
#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_UiPvr.h"              //For pvr
#include "MApp_CIPVR_Adaption.h"              //For pvr
extern MS_BOOL bAutoTimeout;
#endif

#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTinputsource.h"

/////////////////////////////////////////////////////////////////////
#define COLOR_AWAS   0xFF0000
#define COLOR_SIAGA   0xFF8000

static MSGBOX_MODE _eMsgBoxMode;
extern BOOLEAN bParentalPWPassCheck;

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
extern BOOLEAN bIsCellIDRemoveMsgBox;
#endif

extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern U16 PasswordInput1, PasswordInput2;
extern BOOLEAN bStopMonitorBlock;
extern U16 _MApp_ZUI_ACT_PasswordConvertToSystemFormat(U16 password);
#if ENABLE_EWS
//extern U8 u8EwsStatus;
#endif
#if ENABLE_USB_DEVICE_LIST
#define DEVICELIST_NUM_PER_PAGE          4
static HWND _hwndUSBListItem[DEVICELIST_NUM_PER_PAGE] =
{
    HWND_MSGBOX_USB_LIST_ITEM0,
    HWND_MSGBOX_USB_LIST_ITEM1,
    HWND_MSGBOX_USB_LIST_ITEM2,
    HWND_MSGBOX_USB_LIST_ITEM3
};
static HWND _hwndUSBListString[DEVICELIST_NUM_PER_PAGE] =
{
    HWND_MSGBOX_USB_LIST_ITEM0_TEXT,
    HWND_MSGBOX_USB_LIST_ITEM1_TEXT,
    HWND_MSGBOX_USB_LIST_ITEM2_TEXT,
    HWND_MSGBOX_USB_LIST_ITEM3_TEXT
};
#endif

void MApp_ZUI_ACT_AppShowMessageBox(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_MESSAGE_BOX;

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

    //RECT_SET(rect, ((g_IPanel.HStart()+3)&0xFFFC), 1, g_IPanel.Width(), g_IPanel.Height());
    RECT_SET(rect,
        ZUI_MESSAGE_BOX_XSTART, ZUI_MESSAGE_BOX_YSTART,
        ZUI_MESSAGE_BOX_WIDTH, ZUI_MESSAGE_BOX_HEIGHT);

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

    #if ((UI_SKIN_SEL == UI_SKIN_1366X768X565) || (UI_SKIN_SEL == UI_SKIN_1920X1080X565) || (UI_SKIN_SEL == UI_SKIN_960X540X565))
    #if ENABLE_EWS
    if((MApp_EWS_DisasterStatusCheck() == TRUE) && (MApp_EWS_GetMsgCancelFlag() == FALSE))
    {
        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON, SW_HIDE);
        MApp_ZUI_API_KillTimer(HWND_MSGBOX_COMMON_BG, 0);
        if(MApp_EWS_GetStatus() == EN_EWS_WASPADA)
        {
            MApp_ZUI_API_ShowWindow(HWND_EWS_FRAME, SW_HIDE);
            //set focus in scroll bar
            MApp_ZUI_API_SetFocus(HWND_EWS_FRAME_WASPADA_SCROLL_BAR);
            MApp_EWS_Scroll_Text(EN_EWS_SCROLL_RESET);
            u16EWS_ShowStartPosition=0;
        }
        else
        {
            MApp_ZUI_API_ShowWindow(HWND_EWS_FRAME_WASPADA, SW_HIDE);
        }
    }
    else
    #endif
    {
        MApp_ZUI_API_ShowWindow(HWND_EWS_FRAME, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_EWS_FRAME_WASPADA, SW_HIDE);
    }
    #endif
   // MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    _eMsgBoxMode = EN_MSGBOX_MODE_INVALID;

}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleMessageBoxKey(VIRTUAL_KEY_CODE key)
{
    //note: don't do anything here! keys will be handled in state machines
    //      moved to MApp_TV_ProcessAudioVolumeKey()
    UNUSED(key);
    ZUI_DBG_FAIL(printf("[ZUI]IDLEKEY\n"));
    //ABORT();
    return FALSE;
}

void MApp_ZUI_ACT_TerminateMessageBox(void)
{
    ZUI_MSG(printf("[]term:msgbox\n");)
    //enMessageBoxState = _enTargetMessageBoxState;
}


//////////////////////////////////////////
MSGBOX_MODE MApp_ZUI_ACT_GetMessageBoxMode(void)
{
    return _eMsgBoxMode;
}

BOOLEAN MApp_ZUI_ACT_ExecuteMessageBoxAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
            if(bAutoTimeout)
            {
                bAutoTimeout = FALSE;
                if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG))
                {
                    _eMsgBoxMode =EN_MSGBOX_MODE_INVALID;
                    MApp_UiPvr_RecordStart(0xFFFF);
                }
                else if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE)
                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG))
                {
                    _eMsgBoxMode =EN_MSGBOX_MODE_INVALID;
                    MApp_UiPvr_TimeshiftRecordStart(0xFFFF);
                }
            }
#endif
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return FALSE; //for entering power off purpose, return False

        case EN_EXE_RESET_AUTO_CLOSE_TIMER:
            //reset timer if any key
            MApp_ZUI_API_ResetTimer(HWND_MSGBOX_COMMON_BG, 0);
            return FALSE;

        case EN_EXE_MSGBOX_BTN_OK_GO_LEFT:
            MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_BTN_CLEAR);
            return TRUE;
        case EN_EXE_MSGBOX_BTN_CLEAR:
    #if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Add_Str_By_StrId(en_str_Clear);
            MApp_TTSControlSetOn(TRUE);
    #endif
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
            PasswordInput1=PasswordInput2=0;
            return TRUE;
       // case EN_EXE_MSGBOX_BTN_CLEAR_GO_RIGHT:
       //     MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_BTN_OK);
       //     return TRUE;

        case EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX:
            return _eMsgBoxMode == EN_MSGBOX_MODE_POWER_OFF_COUNTDOWN;
    #if ( ENABLE_CI_PLUS_V1_4 )
        case EN_EXE_QUERY_IS_CI_PLUS_POWER_OFF_COUNTDOWN_MSG_BOX:
            return _eMsgBoxMode == EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK;
    #endif  //ENABLE_CI_PLUS_V1_4
        case EN_EXE_QUERY_IS_PASSWORD_INPUT_MSG_BOX:
            return _eMsgBoxMode == EN_MSGBOX_MODE_PASSWORD_INPUT;
        case EN_EXE_SHOW_FUNC_NOT_AVAIL_MSGBOX:
        case EN_EXE_SHOW_MHEG5_SUBTITLE_MSGBOX:
        case EN_EXE_SHOW_LOADING_MHEG5_MSGBOX:
        case EN_EXE_SHOW_AUTO_ADJUSTING_MSGBOX:
        case EN_EXE_SHOW_NO_TELETEXT_MSGBOX:
        case EN_EXE_SHOW_NO_TTX_SUBTITLE_MSGBOX:
        case EN_EXE_SHOW_KEY_LOCK_MSGBOX:
        case EN_EXE_SHOW_CEC_DEVICE_MSGBOX:
        case EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX:
    #if ( ENABLE_CI_PLUS_V1_4 )
        case EN_EXE_SHOW_CI_PLUS_POWER_OFF_COUNTDOWN_MSG_BOX:
    #endif  //ENABLE_CI_PLUS_V1_4
	#if FOR_BENCH_CODE
        case EN_EXE_SHOW_PING_MSGBOX:
	#endif
        case EN_MSGBOX_MODE_NO_TTX_SUBTITLE_MSGBOX:
	#if(ENABLE_OAD)
        case EN_EXE_NO_OAD_AVAILABLE:
	#endif
	#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
        case EN_EXE_SHOW_NETWORK_CHANGE_MSGBOX:

        #ifdef ENABLE_DELETE_PROGRAM_CONTROL
        case EN_EXE_SHOW_PROGRAM_DELETE_MSGBOX:
        #endif  //ENABLE_DELETE_PROGRAM_CONTROL

        case EN_EXE_SHOW_NEW_MULTIPLEX_MIGHT_AVAILABLE_MSGBOX:
        case EN_EXE_SHOW_MULTIPLEX_IS_REMOVED_MSGBOX:
        case EN_EXE_SHOW_FREQUENCY_CHANGE_MSGBOX:
        case EN_EXE_SHOW_LOSS_OF_SIGNAL_MSGBOX:
        case EN_EXE_SHOW_SCANNING_MSGBOX:
	#endif  //ENABLE_UPDATE_MULTIPLEX_VIA_NIT
			_eMsgBoxMode =(MSGBOX_MODE)( act - EN_EXE_SHOW_FUNC_NOT_AVAIL_MSGBOX + EN_MSGBOX_MODE_FUNC_NOT_AVAIL);

			if(_eMsgBoxMode == EN_MSGBOX_MODE_POWER_OFF_COUNTDOWN ||
			#if ( ENABLE_CI_PLUS_V1_4 )
			    _eMsgBoxMode == EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK ||
			#endif  //ENABLE_CI_PLUS_V1_4
				_eMsgBoxMode == EN_MSGBOX_MODE_LOADING_MHEG5       ||
				_eMsgBoxMode == EN_MSGBOX_MODE_AUTO_ADJUSTING      ||
				_eMsgBoxMode == EN_MSGBOX_MODE_FUNC_NOT_AVAIL      ||
			#if FOR_BENCH_CODE
				_eMsgBoxMode == EN_MSGBOX_MODE_PING_MSGBOX         ||
			#endif
				_eMsgBoxMode == EN_MSGBOX_MODE_MHEG5_SUBTITLE      ||
				_eMsgBoxMode == EN_MSGBOX_MODE_NO_TELETEXT         ||
				_eMsgBoxMode == EN_MSGBOX_MODE_NO_TTX_SUBTITLE_MSGBOX
			#if (ENABLE_OAD)
				||_eMsgBoxMode == EN_MSGBOX_MODE_OAD_NOT_AVAIL
			#endif
			#if ENABLE_FAVORITE_NETWORK
				||_eMsgBoxMode == EN_MSGBOX_MODE_NETWORK_CHANGE
				||_eMsgBoxMode == EN_MSGBOX_MODE_MULTIPLEX_AVAILABLE
				||_eMsgBoxMode == EN_MSGBOX_MODE_MULTIPLEX_REMOVED
				||_eMsgBoxMode == EN_MSGBOX_MODE_FREQ_CHANGE
				||_eMsgBoxMode == EN_MSGBOX_MODE_LOSS_SIGNAL
			#endif
			)
            {
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_L, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_C, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_R, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_NEW_BG_L, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_NEW_BG_C, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_NEW_BG_R, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_TEXT_PANE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_CLEAR, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);
            #if ( ENABLE_CI_PLUS_V1_4 )
                if( _eMsgBoxMode == EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK )
                {
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_CONFIRM_MSG_BAR, SW_HIDE);
                }
            #endif  //ENABLE_CI_PLUS_V1_4
            #if (ENABLE_OAD)
                if ( _eMsgBoxMode == EN_MSGBOX_MODE_OAD_NOT_AVAIL )
                {
                    MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_TEXT2);
                    MApp_ZUI_API_SetTimer(HWND_MSGBOX_COMMON_BG, 0, 3000);
                }
            #endif  //ENABLE_OAD
            }
		#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
            else if( _eMsgBoxMode == EN_MSGBOX_MODE_LOSS_OF_SIGNAL_MSGBOX )
            {
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_1, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_2, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_3, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_4, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_BTN_CLEAR);
            }
            else if( _eMsgBoxMode == EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX
                  || _eMsgBoxMode == EN_MSGBOX_MODE_MULTIPLEX_IS_REMOVED_MSGBOX
            #ifdef ENABLE_DELETE_PROGRAM_CONTROL
                  || _eMsgBoxMode == EN_MSGBOX_MODE_PROGRAM_DELETE_MSGBOX
            #endif  //ENABLE_DELETE_PROGRAM_CONTROL
                    )
            {
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_1, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_2, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_3, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_4, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_CLEAR, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_MSG_OK);
                MApp_ZUI_API_KillTimer(HWND_MSGBOX_COMMON_BG, 0);//add for increase ui display time
            }
        	else if( _eMsgBoxMode == EN_MSGBOX_MODE_SCANNING_MSGBOX )
            {
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_1, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_2, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_3, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_INPUT_4, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_CLEAR, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);
            }
	    #endif  //ENABLE_UPDATE_MULTIPLEX_VIA_NIT
            else
            {
                MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_BTN_OK);
            }
            SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
            return TRUE;

    #if ( ENABLE_UNITY_MEDIA_SETTING )
        case EN_EXE_SHOW_WELCOME_MSGBOX:
        {
             _eMsgBoxMode = EN_MSGBOX_MODE_SHOW_WELCOME_MSGBOX;

             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON, SW_SHOW);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_CONFIRM_MSG_BAR, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_L, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_C, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_R, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TITLE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT1, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT_OPTION, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_HIDE);
        }
             return TRUE;
    #endif  //ENABLE_UNITY_MEDIA_SETTING

        case EN_EXE_SHOW_PASSWORD_INPUT_MSGBOX:
            _eMsgBoxMode = EN_MSGBOX_MODE_PASSWORD_INPUT;
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);
	        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK,SW_HIDE);
	        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
        #if (UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_CONFIRM_MSG_BAR,SW_HIDE);
        #endif

            MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
            PasswordInput1=PasswordInput2=0;
            return TRUE;
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        case EN_EXE_SHOW_CIPLUS_PVR_CAM_PINCODE_MSGBOX:
            _eMsgBoxMode = EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE;
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT2, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
#if (UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_CONFIRM_MSG_BAR,SW_HIDE);
#endif

            MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
            PasswordInput1=PasswordInput2=0;
            return TRUE;
        case EN_EXE_SHOW_TIMESHIFT_CIPLUS_PVR_CAM_PINCODE_MSGBOX:
            _eMsgBoxMode = EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE;
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT2, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
#if (UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_CONFIRM_MSG_BAR,SW_HIDE);
#endif
            MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
            PasswordInput1=PasswordInput2=0;
            return TRUE;
#endif
#if ENABLE_ATSC
        case EN_EXE_MSGBOX_MODE_PARENTAL_BLOCK:
			 _eMsgBoxMode = EN_MSGBOX_MODE_PARENTAL_BLOCK;
			MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
			MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
			MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);

			MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);

			MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
			PasswordInput1=PasswordInput2=0;
			return TRUE;
#endif
        case EN_EXE_CHECK_INPUT_PASSWORD:
        case EN_EXE_MSGBOX_BTN_OK:
#if(ENABLE_ATSC)
            if(g_bInputBlocked && (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) == EN_SCREENSAVER_NULL))
            {
                if (_MApp_ZUI_ACT_PasswordConvertToSystemFormat(PasswordInput1) ==
                   MApp_MenuFunc_Setup_BlockSysPassWord_Get())
                {
                    g_bInputBlocked = DISABLE;
                    MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);

                    MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
                }
                else
                {
                    //password wrong...
                    _eMsgBoxMode = EN_MSGBOX_MODE_PASSWORD_WRONG;
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);

                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT1, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT2, SW_SHOW);

                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);

                    MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
                    PasswordInput1=PasswordInput2=0;
                }
            }
            else if(IsAtscInUse()||IsATVInUse())
            {
                if (_MApp_ZUI_ACT_PasswordConvertToSystemFormat(PasswordInput1) ==
                   MApp_MenuFunc_Setup_BlockSysPassWord_Get())
                {
                    fVChipPassWordEntered = TRUE;
                    MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
                }
                else
                {
                    //password wrong...
                    _eMsgBoxMode = EN_MSGBOX_MODE_PASSWORD_WRONG;
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);

                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT1, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT2, SW_SHOW);

                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);

                    MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
                    PasswordInput1=PasswordInput2=0;
                }
            }
            else
#endif
            {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG)
                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE)
                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG))
                {
                    BOOL bPinCodeCorrect = FALSE;
                    U16 u16CachedPinCode = 0;
                    U16 ret = 0;
                    ret += (PasswordInput1)&PASSWORD_INPUT_MASK;
                    ret *= 10;
                    ret += (PasswordInput1>>4)&PASSWORD_INPUT_MASK;
                    ret *= 10;
                    ret += (PasswordInput1>>8)&PASSWORD_INPUT_MASK;
                    ret *= 10;
                    ret += (PasswordInput1>>12)&PASSWORD_INPUT_MASK;
                    printf("..............messagebox 4444444444444.....0x%x  %d.........\n",PasswordInput1,
                                 ret);
                    MAPP_CIPVR_CISendCCPin(FALSE,ret);
                    MAPP_CIPVR_CICheckPinEventStatus(&bPinCodeCorrect, &u16CachedPinCode);
                    if(bPinCodeCorrect)
                    {
                        MApp_ZUI_ACT_ShutdownOSD();
                        if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
                            || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG))
                        {printf("..............messagebox 5555555555555.........\n");
                            _eMsgBoxMode =EN_MSGBOX_MODE_INVALID;
                            MApp_UiPvr_RecordStart(u16CachedPinCode);
                        }
                        else if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE)
                                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG))
                        {printf("..............messagebox 66666666666666.........\n");
                            _eMsgBoxMode =EN_MSGBOX_MODE_INVALID;
                            MApp_UiPvr_TimeshiftRecordStart(u16CachedPinCode);
                        }
                    }
                    else
                    {
                        printf("..............messagebox EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG........\n");
                        if(_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
                        {
                            _eMsgBoxMode = EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG;
                        }
                        else if(_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE)
                        {
                            _eMsgBoxMode = EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG;
                        }
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);

                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT1, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT2, SW_SHOW);

                        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);

                        MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
                        MApp_ZUI_API_SetTimer(HWND_MSGBOX_COMMON_BG, 0, 30000);
                        PasswordInput1=PasswordInput2=0;
                    }
                }
                else
#endif
                {
                    if (_MApp_ZUI_ACT_PasswordConvertToSystemFormat(PasswordInput1) ==
                        MApp_MenuFunc_Setup_BlockSysPassWord_Get())
                    {
                        //password correct
                        MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
                        bStopMonitorBlock = TRUE;
                        bParentalPWPassCheck = TRUE;
                        g_bInputBlocked = FALSE;
#if(ENABLE_ATSC)
                        fVChipPassWordEntered = TRUE;
#endif
                        MApp_EnableBlockProgramme(FALSE);
                        MApp_ParentalControl_SetBlockStatus(FALSE);
#if ENABLE_DMP
#if ENBALE_PARENTALRATING_MM
        				if(IsStorageInUse())
        				{
        					MApp_ZUI_ACT_StartupOSD(E_OSD_DMP);
        					MApp_ZUI_API_ShowWindow(HWND_DMP_ALERT_WINDOW, SW_HIDE);
        				      if(MApp_VDPlayer_IsPreview())
        				      {
        						MApp_DMP_NotifyUiState(DMP_UI_STATE_FILE_SELECT);
                                MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW, NULL);
        				   	}
        					else
        					{
                                MApp_ZUI_API_ShowWindow(HWND_DMP_PLAYBACK_TRANSPARENT_BG, SW_SHOW);
                                MApp_ZUI_API_SetFocus(HWND_DMP_PLAYBACK_TRANSPARENT_BG);
        					}
                            #if (ENABLE_MPLAYER_MOVIE)
        					MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                            #endif
        					MApp_VDPlayer_SetRatingCtrl(0x0000);//For  continue check parental rating
        				}
#endif
#endif
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                            SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
                        #if (ENABLE_PIP)
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                            SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
                        #endif
                    }
                    else
                    {
                        //password wrong...
                        _eMsgBoxMode = EN_MSGBOX_MODE_PASSWORD_WRONG;
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_MSG_OK, SW_HIDE);

                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT1, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TEXT2, SW_SHOW);

                        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);

                        MApp_ZUI_API_SetFocus(HWND_MSGBOX_PASSWORD_INPUT_1);
                        PasswordInput1=PasswordInput2=0;
                    }
                }
            }
            return TRUE;

        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case EN_EXE_MESSAGE_BOX_BTN_SELECT_OK:
            {
                //Press Ok in Msg Box
                if( ( _eMsgBoxMode == EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX )
                 || ( _eMsgBoxMode == EN_MSGBOX_MODE_MULTIPLEX_IS_REMOVED_MSGBOX )
                  )
                {
                    //Put Network Change Code Here.
                    MApp_DTV_Scan_NetworkChange_Cornfim_OK();
                }
                break;
            }

            case EN_EXE_MESSAGE_BOX_BTN_SELECT_YES:
            {
            #ifdef ENABLE_DELETE_PROGRAM_CONTROL
                if( _eMsgBoxMode == EN_MSGBOX_MODE_PROGRAM_DELETE_MSGBOX)
                {
                    MApp_ZUI_ACT_ShutdownOSD();
                    msAPI_CM_IsUserRemoveProgram(FALSE);
                }
                else
            #endif  //ENABLE_DELETE_PROGRAM_CONTROL
                if( _eMsgBoxMode == EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX)
                {
                    MApp_DTV_Scan_NetworkChange_Cornfim_OK();
                }
                return TRUE;
            }

            case EN_EXE_MESSAGE_BOX_BTN_SELECT_NO:
            {
            #ifdef ENABLE_DELETE_PROGRAM_CONTROL
                if( _eMsgBoxMode == EN_MSGBOX_MODE_PROGRAM_DELETE_MSGBOX){
                    MApp_ZUI_ACT_ShutdownOSD();
                    msAPI_CM_IsUserRemoveProgram(FALSE);
                }
                else
            #endif  //ENABLE_DELETE_PROGRAM_CONTROL
                if( _eMsgBoxMode == EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX)
                {
                    MApp_DTV_Scan_NetworkChange_Cornfim_NO();
                }
                return TRUE;
            }
        #endif  //ENABLE_UPDATE_MULTIPLEX_VIA_NIT

        #if ENABLE_USB_DEVICE_LIST
        case EN_EXE_SHOW_USB_LIST_MSG:
            _eMsgBoxMode = EN_MSGBOX_MODE_USB_LIST;
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_TITLE, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_TEXT_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_OK, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_CLEAR, SW_HIDE);

            {
                U8 u8ShowItem;
                U8 u8TotalPageIdx = (MApp_MassStorage_GetTotalDriveNum() / DEVICELIST_NUM_PER_PAGE)+1;
                U8 i;

                MApp_ZUI_ACT_DMPSetCurDrvIdxAndCalPageIdxByUser(0);

                if(MApp_ZUI_ACT_DMPGetDrvPageIdxByUser() == u8TotalPageIdx) //last page
                {
                    u8ShowItem = (MApp_MassStorage_GetTotalDriveNum() % DEVICELIST_NUM_PER_PAGE);
                }
                else
                {
                    u8ShowItem = DEVICELIST_NUM_PER_PAGE;
                }

                MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_SHOW);

                for( i = DEVICELIST_NUM_PER_PAGE ; i > u8ShowItem ; i--)
                {
                    MApp_ZUI_API_ShowWindow( _hwndUSBListItem[i-1],SW_HIDE);
                }

                U8 u8Idx = (MApp_ZUI_ACT_DMPGetCurDrvIdxByUser()) % DEVICELIST_NUM_PER_PAGE;
                MApp_ZUI_API_SetFocus(_hwndUSBListItem[u8Idx]);

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MSGBOX_USB_LIST_PANE);
            }
            return TRUE;

        case EN_EXE_USB_LIST_SEL:
            {
                U8 u8Item = 0;
                for(u8Item = 0; u8Item < DEVICELIST_NUM_PER_PAGE; u8Item++)
                {
                    if(_hwndUSBListItem[u8Item] == MApp_ZUI_API_GetFocus())
                    {
                        break;
                    }
                }
                if(u8Item < DEVICELIST_NUM_PER_PAGE)
                {
                    U8 u8Idx = (MApp_ZUI_ACT_DMPGetDrvPageIdxByUser()-1) * DEVICELIST_NUM_PER_PAGE + u8Item;

                    MApp_ZUI_ACT_DMPSetCurDrvIdxAndCalPageIdxByUser(u8Idx);
                    MApp_ZUI_ACT_DMPSetDrvIdxByUser(TRUE);

                    //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                    //MApp_APEngine_Start();
                    MApp_InputSource_RecordSource(UI_INPUT_SOURCE_TYPE);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DMP;
                    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);

                    MApp_ChannelChange_VariableInit();

                    MApp_TopStateMachine_SetTopState(STATE_TOP_DMP);

                    MDrv_USBSetPortAutoSwitchStatus(1);
                    //MApp_OSDPage_SetOSDPage(E_OSD_DMP);
                }
            }
            return TRUE;
         #endif
#if(ASTRA_HD_ENABLE)
         case EN_EXE_ADD_CHANNEL2LIST:
         {
             //printf("EN_EXE_ADD_CHANNEL2LIST\n");
             _eMsgBoxMode = EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX;

             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON, SW_SHOW);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_USB_LIST_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_PASSWORD_PRESSED_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BTN_PANE, SW_HIDE);

             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_L, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_C, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MSGBOX_COMMON_BG_R, SW_HIDE);
             MApp_ZUI_API_SetFocus(HWND_MSGBOX_COMMON_TEXT_OPTION);
             MApp_ZUI_API_KillTimer(HWND_MSGBOX_COMMON_BG, 0);//add for increase ui display time
             return TRUE;
         }
         case EN_EXE_MSGBOX_COMMON_BTN_YES:
         {
             //printf("EN_EXE_MSGBOX_COMMON_BTN_YES\n");
             if(_eMsgBoxMode == EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX)
             {
                 printf("EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX\n");
                 MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_CLOSE_CURRENT_OSD);
                 msAPI_CM_ArrangeDataManager(TRUE, FALSE);
                 msAPI_CM_ClearAllNewService();

             }
             return TRUE;
         }
         case EN_EXE_MSGBOX_COMMON_BTN_NO:
         {
             //printf("EN_EXE_MSGBOX_COMMON_BTN_NO\n");
             if(_eMsgBoxMode == EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX)
             {
                 printf("EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX\n");
                 MApp_ZUI_ACT_ExecuteInputSourceAction(EN_EXE_CLOSE_CURRENT_OSD);
                 msAPI_CM_RemoveIsNewService();
                 msAPI_CM_ArrangeDataManager(TRUE, FALSE);
             }
             return TRUE;
         }
#endif


    }
    return FALSE;
}

#if FOR_BENCH_CODE
static char* _MApp_GetToken(FILE* MemoryFile)
{
    char *buffer;
    char c;
    int idx = 0;

    buffer = (char*)malloc(sizeof(char)*256);
    if (buffer == NULL)
    {
        ASSERT(buffer);
        return NULL;
    }
    buffer[0] = '\0';

    while(!feof(MemoryFile))
    {
        while(1)
        {
            c = (char)fgetc(MemoryFile);
            if(feof(MemoryFile))
            {
                buffer[idx] = '\0';
                return buffer;
            }
            if((c != ' ') && (c != '\n')&& (c != '\t'))
            {
                if(c == '\r')
                {
                    c = (char)fgetc(MemoryFile);
                    c = (char)fgetc(MemoryFile);
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        idx = 0;
        buffer[idx++] = c;
        c = (char)fgetc(MemoryFile);
        while(1)
        {
            if(feof(MemoryFile))
            {
                buffer[idx] = '\0';
                return buffer;
            }
            if((c == ' ') || (c == '\n')||(c == '\t'))
            {
                break;
            }
            if(c == '\r')
            {
                c = (char)fgetc(MemoryFile);
                if(c == '\n')
                {
                    break;
                }
            }
            buffer[idx++] = c;
            c = (char)fgetc(MemoryFile);
        }
        buffer[idx] = '\0';
        return buffer;
    }
    return buffer;
}

int MApp_OpenPingLog(void)
{
    FILE *FilePtr = NULL;
    char *buffer;

    FilePtr = fopen("/ping.log", "r+");
    if(FilePtr)
    {
        while(!feof(FilePtr))
        {
            buffer = _MApp_GetToken(FilePtr);
            if(strcmp(buffer, "round-trip") == 0)
            {
                //printf("ping pass!\n");
                return 1;
            }
        }
        //printf("ping failed!\n");
    }
    else
    {
        //printf("Open ping.log file failed!\n");
    }

    return 0;
}
#endif


LPTSTR MApp_ZUI_ACT_GetMessageBoxDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_MSGBOX_COMMON_TITLE:
            #if ENABLE_USB_DEVICE_LIST
            if(_eMsgBoxMode == EN_MSGBOX_MODE_USB_LIST)
            {
                U8 str[] = {"USB Device"};
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
                return CHAR_BUFFER;
            }
            #endif
            break;
        case HWND_MSGBOX_COMMON_TEXT1:
        {
            switch(_eMsgBoxMode)
            {
                case EN_MSGBOX_MODE_FUNC_NOT_AVAIL:
                    u16TempID = en_str_Not_Available;
                    break;
        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                case EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX:
                    u16TempID = en_str_Network_Change_press_ok_to_update;
                    break;
                case EN_MSGBOX_MODE_SCANNING_MSGBOX:
                    u16TempID = en_str_Install_ScanCheck_TEXT2;
                    break;
                case EN_MSGBOX_MODE_MULTIPLEX_IS_REMOVED_MSGBOX:
                    u16TempID = en_str_Multiplex_is_removed_Update_now;
                    break;
            #ifdef ENABLE_DELETE_PROGRAM_CONTROL
                case EN_MSGBOX_MODE_PROGRAM_DELETE_MSGBOX:
                    u16TempID = en_str_Network_Change_press_ok_to_update;
                    break;
            #endif  //ENABLE_DELETE_PROGRAM_CONTROL
        #endif  //ENABLE_UPDATE_MULTIPLEX_VIA_NIT
                case EN_MSGBOX_MODE_MHEG5_SUBTITLE:
                    u16TempID = en_str_Subtitle_cant_work_simultaneously;
                    break;
                case EN_MSGBOX_MODE_LOADING_MHEG5:
                    u16TempID = en_str_Waiting3dot;
                    break;
                case EN_MSGBOX_MODE_AUTO_ADJUSTING:
                    u16TempID = en_str_Auto_Adjusting3dot;
                    break;
                case EN_MSGBOX_MODE_NO_TELETEXT:
                    u16TempID = en_str_No_Teletext;
                    break;
                case EN_MSGBOX_MODE_NO_TTX_SUBTITLE_MSGBOX:
                    u16TempID = en_str_No_TTX_Subtitle;
                    break;
                case EN_MSGBOX_MODE_KEY_LOCK:
                    u16TempID = en_str_Key_Lock;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                    break;
            #if ( ENABLE_CI_PLUS_V1_4 )
                case EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK:
                    {
                        LPTSTR str = CHAR_BUFFER;
                        MApp_ZUI_API_GetU16String((U16)MApp_Sleep_DisplayCountDownTimer());
                        str += MApp_ZUI_API_Strlen(str);
                        MApp_ZUI_API_LoadString(en_str_SECOND_TO_POWER_OFF, str);
                        return CHAR_BUFFER;
                    }
                    break;
            #endif  //ENABLE_CI_PLUS_V1_4
                case EN_MSGBOX_MODE_POWER_OFF_COUNTDOWN:
                    {
                        LPTSTR str = CHAR_BUFFER;
                        MApp_ZUI_API_GetU16String((U16)MApp_Sleep_DisplayCountDownTimer());
                        str += MApp_ZUI_API_Strlen(str);
                        MApp_ZUI_API_LoadString(en_str_SECOND_TO_POWER_OFF, str);
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(CHAR_BUFFER, MApp_UiMenu_u16Strlen(CHAR_BUFFER));
                    MApp_TTSControlSetOn(TRUE);
#endif
                        return CHAR_BUFFER;
                    }
                    break;
#if FOR_BENCH_CODE
                case EN_MSGBOX_MODE_PING_MSGBOX:
                    if(MApp_OpenPingLog())
                    {
                        U8 str[] = {"Ping success"};
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
                    }
                    else
                    {
                        U8 str[] = {"Ping failed"};
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str,strlen((char *)str));
                    }
                    return CHAR_BUFFER;
                break;
#endif
#if ENABLE_FAVORITE_NETWORK
                case EN_MSGBOX_MODE_NETWORK_CHANGE:
                     u16TempID = en_str_Network_Change_Update_now;
                     break;
                case EN_MSGBOX_MODE_MULTIPLEX_AVAILABLE:
                     u16TempID = en_str_New_Multiplex_might_be_available_Redashscan_is_required;
                     break;
                case EN_MSGBOX_MODE_MULTIPLEX_REMOVED:
                     u16TempID = en_str_Multiplex_is_removed_Update_now;
                     break;
                case EN_MSGBOX_MODE_FREQ_CHANGE:
                     u16TempID = en_str_Frequency_change_Redashscan_is_required;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                     break;
                case EN_MSGBOX_MODE_LOSS_SIGNAL:
                     u16TempID = en_str_Loss_of_signal_Whether_a_new_frequency_check_or_not;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                     break;
#endif
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
                case EN_MSGBOX_MODE_FREQUENCY_CHANGE_MSGBOX:
                     u16TempID = en_str_Frequency_change_Redashscan_is_required;
                     break;
#endif
                case EN_MSGBOX_MODE_PASSWORD_INPUT:
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                case EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE:
                case EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE:
#endif
                    u16TempID = en_str_Please_enter_password;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                    break;
#if ENABLE_ATSC
				case EN_MSGBOX_MODE_PARENTAL_BLOCK:
                    u16TempID = en_str_Channel_Blocked;
                    break;
#endif
                case EN_MSGBOX_MODE_PASSWORD_WRONG:
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                case EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG:
                case EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG:
#endif
                    u16TempID = en_str_Wrong_password;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                    break;
                #if ( ENABLE_OAD )
                case EN_MSGBOX_MODE_OAD_NOT_AVAIL:
                    u16TempID = en_str_NO_OAD_AVAILABLE;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                    break;
                #endif  // ENABLE_OAD

#if(ASTRA_HD_ENABLE)
                case EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX:
                {
                    U8 str[] = {"New channel available."};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    //printf("EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX\n");
                    //printf("%s\n",CHAR_BUFFER);
                    return CHAR_BUFFER;
                }
                case EN_MSGBOX_MODE_NETWORKCHANGE_MSGBOX:
                {
                    U8 str[] = {"Network Change!"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    //printf("EN_MSGBOX_MODE_NETWORKCHANGE_MSGBOX\n");
                    //printf("%s\n",CHAR_BUFFER);
                    return CHAR_BUFFER;
                }
#endif
                default:
                    ZUI_DBG_FAIL(printf("[ZUI]MBOXMODE\n"));
                    ABORT();
            }
            break;
        }
//            printf("u16TempID=%u\n", u16TempID);
        case HWND_MSGBOX_COMMON_TEXT2:
        {
            switch(_eMsgBoxMode)
            {
            #if ( ENABLE_CI_PLUS_V1_4 )
                case EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK:
                {
                    if( g_bCallbackOKFromCICAM )
                    {
                        U8 str[] = {"CICAM Response OK, Enter Standby Now."};
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    }
                    else if( TRUE == msAPI_CI_CU_GetState() )
                    {
                        U8 str[] = {"CICAM Firmware Upgrade Started, Cancel Power Off."};
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    }
                    else
                    {
                        U8 str[] = {"Waiting CICAM Response."};
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    }
                    return CHAR_BUFFER;
                }
                break;
            #endif  //ENABLE_CI_PLUS_V1_4
                case EN_MSGBOX_MODE_POWER_OFF_COUNTDOWN:
                {
                    MApp_ZUI_API_LoadString(en_str_Please_press_any_key_to_cancel, CHAR_BUFFER);
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(CHAR_BUFFER, MApp_UiMenu_u16Strlen(CHAR_BUFFER));
                    MApp_TTSControlSetOn(TRUE);
#endif
                    return CHAR_BUFFER;
                }
                break;

                case EN_MSGBOX_MODE_PASSWORD_WRONG:
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                case EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG:
                case EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG:
#endif
                    u16TempID = en_str_Reenter_password;
#if (ENABLE_ATSC_TTS)
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
                    MApp_TTSControlSetOn(TRUE);
#endif
                    break;
#if ENABLE_ATSC
			case EN_MSGBOX_MODE_PARENTAL_BLOCK:
                    {
                        U8 pu8VchipString[256];
    					//strcpy((char *)pu8VchipString, (const char *)RatingInfoText());
    					strncpy((char *)pu8VchipString, (const char *)RatingInfoText(), 256-1);
    					MApp_U8StringToU16String(pu8VchipString,CHAR_BUFFER,strlen((const char *)pu8VchipString));
                    }
					return CHAR_BUFFER;
#endif

#if(ASTRA_HD_ENABLE)
                case EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX:
                {
                    //printf("HWND_MSGBOX_COMMON_TEXT2\n");
                    U8 str[] = {"Add to Main list?"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    return CHAR_BUFFER;
                }
                case EN_MSGBOX_MODE_NETWORKCHANGE_MSGBOX:
                {
                    U8 str[] = {"Would you start scan?"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    return CHAR_BUFFER;
                }
#endif

            #if ( ENABLE_UNITY_MEDIA_SETTING )
                case EN_MSGBOX_MODE_SHOW_WELCOME_MSGBOX:
                {
                    U8 str[] = {"Welcome! Installation complete."};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,strlen((char *)str));
                    return CHAR_BUFFER;
                }
            #endif  //ENABLE_UNITY_MEDIA_SETTING

                default:
                    break;
            }
            //printf("u16TempID=%u\n", u16TempID);
            break;
        }

#if ENABLE_USB_DEVICE_LIST
        case HWND_MSGBOX_USB_LIST_ITEM0_TEXT:
        case HWND_MSGBOX_USB_LIST_ITEM1_TEXT:
        case HWND_MSGBOX_USB_LIST_ITEM2_TEXT:
        case HWND_MSGBOX_USB_LIST_ITEM3_TEXT:
        {
            U8 u8Item = 0;
            for(u8Item = 0; u8Item < DEVICELIST_NUM_PER_PAGE; u8Item++)
            {
                if(_hwndUSBListString[u8Item] == hwnd)
                {
                    break;
                }
            }

            {
                U8 u8Idx = (MApp_ZUI_ACT_DMPGetDrvPageIdxByUser()-1) * DEVICELIST_NUM_PER_PAGE + u8Item;

                if((u8Item < DEVICELIST_NUM_PER_PAGE) &&
                    u8Idx < MApp_MassStorage_GetTotalDriveNum())
                {
                    CHAR_BUFFER[0] = 'C' + MApp_DMP_GetDriveFromMappingTable(u8Idx);
                    CHAR_BUFFER[1] = 0;
                    CHAR_BUFFER[2] = 0;
                    CHAR_BUFFER[3] = 0;
                    return CHAR_BUFFER;
                }
            }
        }
        break;
#endif
#if (ENABLE_EWS == TRUE)
        case HWND_DISASTER_LOCATION_STATUS_TXT:
            if(MApp_EWS_GetStatus() == EN_EWS_SIAGA)
            {
                u16TempID = en_str_SIAGA0;
            }
            else
            {
                u16TempID = en_str_AWAS0;
            }
            break;

        case HWND_LOCATION_OF_DISASTER2:
        case HWND_LOCATION_OF_DISASTER:
        {
             return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,stEwsSettingData.u8_EwsLocationDisaster,strlen((char *)stEwsSettingData.u8_EwsLocationDisaster));
        }

        case HWND_TYPE_CONTENT:
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,stEwsSettingData.u8_EwsDisasterType,strlen((char *)stEwsSettingData.u8_EwsDisasterType));

        case HWND_DATE_CONTENT:
               return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,stEwsSettingData.u8_EwsDisasterDate,strlen((char *)stEwsSettingData.u8_EwsDisasterDate));


        case HWND_LONGITUDE_CONTENT:
              return  MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,stEwsSettingData.u8_EwsDisasterLongitude,strlen((char *)stEwsSettingData.u8_EwsDisasterLongitude));

        case HWND_CHARACTER_CONTENT:
               return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,stEwsSettingData.u8_EwsDisasterCharacter,strlen((char *)stEwsSettingData.u8_EwsDisasterCharacter));

        case HWND_REMARK_DESCRIPTION:
            {
                #if 0
                U16 strcount;
                //U16 u16StrBuf[400]={0};
                U16* u16StrBuf = msAPI_Memory_Allocate( sizeof(U16)*STRING_BUFFER_LENGTH, BUF_ID_ZUI_STR_BUF );

                if( u16StrBuf == NULL )
                    break;

                memset(u16StrBuf, 0, sizeof(U16)*STRING_BUFFER_LENGTH );

                strcount = strlen((char *)stEwsSettingData.u8_EwsDisasterType);
                MApp_ZUI_API_StringBuffU8toU16(u16StrBuf,stEwsSettingData.u8_EwsDisasterType,strcount);
                strcount = MApp_ZUI_API_Strlen(u16StrBuf);
                if(stEwsSettingData.u8_EwsDisasterType[0]!=0)
                {
                    u16StrBuf[strcount++]=',';
                    u16StrBuf[strcount++]=' ';
                    u16StrBuf[strcount++]=0;
                }
                strcount = MApp_ZUI_API_Strlen(u16StrBuf);
                MApp_ZUI_API_StringBuffU8toU16(&u16StrBuf[strcount],stEwsSettingData.u8_EwsDisasterRemark,strlen((char *)stEwsSettingData.u8_EwsDisasterRemark));

                //Daerah Anda :
                strcount = MApp_ZUI_API_Strlen(u16StrBuf);
                if(stEwsSettingData.u8_EwsDisasterRemark[0]!=0)
                {
                    u16StrBuf[strcount++]=',';
                    u16StrBuf[strcount++]=' ';
                }
                u16StrBuf[strcount++]='D';
                u16StrBuf[strcount++]='a';
                u16StrBuf[strcount++]='e';
                u16StrBuf[strcount++]='r';
                u16StrBuf[strcount++]='a';
                u16StrBuf[strcount++]='h';
                u16StrBuf[strcount++]=' ';
                u16StrBuf[strcount++]='A';
                u16StrBuf[strcount++]='n';
                u16StrBuf[strcount++]='d';
                u16StrBuf[strcount++]='a';
                u16StrBuf[strcount++]=' ';
                u16StrBuf[strcount++]=':';
                u16StrBuf[strcount++]=' ';

                //CHAR_BUFFER[strcount++]=0;

                switch(MApp_EWS_GetStatus())
                {
                    case EN_EWS_AWAS:
                        u16TempID = en_str_AWAS0;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[strcount], MApp_ZUI_API_GetString(u16TempID));
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                    break;

                    case EN_EWS_SIAGA:
                        u16TempID = en_str_SIAGA0;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[strcount], MApp_ZUI_API_GetString(u16TempID));
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                    break;

                    case EN_EWS_WASPADA:
                        u16TempID = en_str_WASPADA0;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[strcount], MApp_ZUI_API_GetString(u16TempID));
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                    break;

                    default:
                        //u16TempID = en_str_Space;
                        u16StrBuf[strcount++]=0;

                        break;
                }
                #endif

                MApp_EWS_Set_Description();

                memset(u16StringBuffer, 0, STRING_BUFFER_LENGTH);
                MApp_EWS_Get_Description(u16StringBuffer, STRING_BUFFER_LENGTH);

                return CHAR_BUFFER;
            }

        case HWND_REMARK_DESCRIPTION2:
        {
             U16 strcount;

             //U16 u16StrBuf[500]={0};
            U16* u16StrBuf = msAPI_Memory_Allocate( sizeof(U16)*STRING_BUFFER_LENGTH, BUF_ID_ZUI_STR_BUF );

            if( u16StrBuf == NULL )
                break;

            memset(u16StrBuf, 0, sizeof(U16)*STRING_BUFFER_LENGTH );


             MApp_ZUI_API_StringBuffU8toU16(u16StrBuf,stEwsSettingData.u8_EwsDisasterType,strlen((char *)stEwsSettingData.u8_EwsDisasterType));
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);
             if(stEwsSettingData.u8_EwsDisasterType[0]!=0)
             {
                 u16StrBuf[strcount++]=',';
                 u16StrBuf[strcount++]=' ';
                 u16StrBuf[strcount]=0;
             }
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);

            u16StrBuf[strcount++]='T';
            u16StrBuf[strcount++]='a';
            u16StrBuf[strcount++]='n';
            u16StrBuf[strcount++]='g';
            u16StrBuf[strcount++]='g';
            u16StrBuf[strcount++]='a';
            u16StrBuf[strcount++]='l';
            u16StrBuf[strcount++]=' ';
            u16StrBuf[strcount++]=':';
            u16StrBuf[strcount++]=' ';
            u16StrBuf[strcount]=0;

             MApp_ZUI_API_StringBuffU8toU16(&u16StrBuf[strcount],stEwsSettingData.u8_EwsDisasterDate,strlen((char *)stEwsSettingData.u8_EwsDisasterDate));

             strcount = MApp_ZUI_API_Strlen(u16StrBuf);
             if(stEwsSettingData.u8_EwsDisasterDate[0]!=0)
             {
                 u16StrBuf[strcount++]=',';
                 u16StrBuf[strcount++]=' ';
                 u16StrBuf[strcount++]=0;
             }
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);

            u16StrBuf[strcount++]='P';
            u16StrBuf[strcount++]='o';
            u16StrBuf[strcount++]='s';
            u16StrBuf[strcount++]='i';
            u16StrBuf[strcount++]='s';
            u16StrBuf[strcount++]='i';
            u16StrBuf[strcount++]=' ';
            u16StrBuf[strcount++]=':';
            u16StrBuf[strcount++]=' ';
            u16StrBuf[strcount]=0;

             MApp_ZUI_API_StringBuffU8toU16(&u16StrBuf[strcount],stEwsSettingData.u8_EwsDisasterLongitude,strlen((char *)stEwsSettingData.u8_EwsDisasterLongitude));
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);
             if(stEwsSettingData.u8_EwsDisasterLongitude[0]!=0)
             {
                 u16StrBuf[strcount++]=',';
                 u16StrBuf[strcount++]=' ';
                 u16StrBuf[strcount++]=0;
             }
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);

             MApp_ZUI_API_StringBuffU8toU16(&u16StrBuf[strcount],stEwsSettingData.u8_EwsDisasterCharacter,strlen((char *)stEwsSettingData.u8_EwsDisasterCharacter));
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);

             if(stEwsSettingData.u8_EwsDisasterCharacter[0]!=0)
             {
                 u16StrBuf[strcount++]=',';
                 u16StrBuf[strcount++]=' ';
                 u16StrBuf[strcount++]=0;
             }
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);

             MApp_ZUI_API_StringBuffU8toU16(&u16StrBuf[strcount],stEwsSettingData.u8_EwsDisasterRemark,strlen((char *)stEwsSettingData.u8_EwsDisasterRemark));
             strcount = MApp_ZUI_API_Strlen(u16StrBuf);
             if(stEwsSettingData.u8_EwsDisasterRemark[0]!=0)
             {
                 u16StrBuf[strcount++]=',';
                 u16StrBuf[strcount++]=' ';
             }
             u16StrBuf[strcount++]='D';
             u16StrBuf[strcount++]='a';
             u16StrBuf[strcount++]='e';
             u16StrBuf[strcount++]='r';
             u16StrBuf[strcount++]='a';
             u16StrBuf[strcount++]='h';
             u16StrBuf[strcount++]=' ';
             u16StrBuf[strcount++]='A';
             u16StrBuf[strcount++]='n';
             u16StrBuf[strcount++]='d';
             u16StrBuf[strcount++]='a';
             u16StrBuf[strcount++]=' ';
             u16StrBuf[strcount++]=':';
             u16StrBuf[strcount++]=' ';



            switch(MApp_EWS_GetStatus())
            {
                case EN_EWS_AWAS:
                    u16TempID = en_str_AWAS0;

                    MApp_ZUI_API_Strcpy(&u16StrBuf[strcount], MApp_ZUI_API_GetString(u16TempID));
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                break;

                case EN_EWS_SIAGA:
                    u16TempID = en_str_SIAGA0;
                    MApp_ZUI_API_Strcpy(&u16StrBuf[strcount], MApp_ZUI_API_GetString(u16TempID));
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);

                break;

                case EN_EWS_WASPADA:
                    u16TempID = en_str_WASPADA0;
                    MApp_ZUI_API_Strcpy(&u16StrBuf[strcount], MApp_ZUI_API_GetString(u16TempID));
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);

                break;

                default:
                    u16StrBuf[strcount++]=0;
                    break;
            }

            MSAPI_MEMORY_FREE( u16StrBuf, BUF_ID_ZUI_STR_BUF);

            return CHAR_BUFFER;
        }

#endif
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}
#if (ENABLE_EWS == TRUE)
OSD_COLOR MApp_ZUI_ACT_GetMsgBoxmenuDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal)
{
    UNUSED(type);

    switch(hwnd)
    {
        case HWND_DISASTER_LOCATION_STATUS_TXT:
        {
            if(MApp_EWS_GetStatus() == EN_EWS_SIAGA)
                return COLOR_SIAGA;
            else
                return COLOR_AWAS;
        }
        break;
    }
    return colorOriginal;
}
U16 MApp_ZUI_ACT_GetMsgBoxDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    UNUSED(ds_type);
    switch(hwnd)
    {
        case HWND_DISASTER_SYMBOL:
        case HWND_DISASTER_SYMBOL2:
            switch(MApp_EWS_GetDisasterSymbol())//Symbol code
            {
                case 0x01:
                    return E_BMP_gempa;

                case 0x02:
                    return E_BMP_tsunami;

                case 0x03:
                    return E_BMP_gunung_meletus;

                case 0x04:
                    return E_BMP_gerakan_tanah;

                case 0x05:
                    return E_BMP_banjir;

                case 0x06:
                    return E_BMP_kekeringan;

                case 0x07:
                    return E_BMP_kebakaran_hutan;

                case 0x08:
                    return E_BMP_erosi;

                case 0x09:
                    return E_BMP_kebakaran_Gedung;

                case 0x0A:
                    return E_BMP_gelombang_ekstrin_dan_abrasi;

                case 0x0B:
                    return E_BMP_cuaca_eksrim;

                case 0x0C:
                    return E_BMP_kegagalan_teknologi;

                case 0x0D:
                    return E_BMP_Epidemi;

                case 0x0E:
                    return E_BMP_konflik_sosial;

                case 0xFF:
                default:
                    return E_BMP_cadangan;


            }
            break;

        case HWND_AUTHOR_SYMBOL:
        case HWND_AUTHOR_SYMBOL2:
            switch(MApp_EWS_GetAuthor())//Author code
            {
                default:
                case 0x01:
                    return E_BMP_Logo_BMKG_1;

                case 0x02:
                    return E_BMP_Logo_BNPB_1;
            }
            break;

        default:
            break;
    }

    return 0xFFFF; //for empty bitmap....
}
#endif

/////////////////////////////////////////////////////////
// Customize Window Procedures
/*
S32 MApp_ZUI_ACT_MessageBoxWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                //setting AP timeout, auto close
                MApp_ZUI_API_SetTimer(hwnd, 0, HOT_MENU_TIME_OUT_5SEC);
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

S32 MApp_ZUI_ACT_MsgBoxTextPaneWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                //checking timer...
            #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                if(_eMsgBoxMode >= EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX &&
                    _eMsgBoxMode <= EN_MSGBOX_MODE_NO_OAD_MSGBOX)
                {
                    MApp_ZUI_API_SetTimer(hwnd, 0, 3000); //redraw message box
                }
                else
            #endif  //ENABLE_UPDATE_MULTIPLEX_VIA_NIT
                {
                #if( ASTRA_HD_ENABLE )
                    if(_eMsgBoxMode == EN_MSGBOX_MODE_NETWORKCHANGE_MSGBOX)
                    {
                        MApp_ZUI_API_SetTimer(hwnd, 0, 3000); //redraw message box
                    }
                    else
                #endif  //ASTRA_HD_ENABLE
                    {
                        MApp_ZUI_API_SetTimer(hwnd, 0, 1000); //redraw message box
                    }
            }
            }
            break;

        case MSG_TIMER:
            {
                //repaint text message if msg mode is COUNT DOWN!
                if (_eMsgBoxMode == EN_MSGBOX_MODE_POWER_OFF_COUNTDOWN
                #if ( ENABLE_CI_PLUS_V1_4 )
                    || _eMsgBoxMode == EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK
                #endif  //ENABLE_CI_PLUS_V1_4
                    || _eMsgBoxMode == EN_MSGBOX_MODE_PASSWORD_INPUT
                    || _eMsgBoxMode == EN_MSGBOX_MODE_PASSWORD_WRONG
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                    || _eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG
                    || _eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG
#endif
                  #if ENABLE_ATSC
                    || _eMsgBoxMode == EN_MSGBOX_MODE_PARENTAL_BLOCK
                  #endif
                  #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
                    || _eMsgBoxMode == EN_MSGBOX_MODE_LOSS_OF_SIGNAL_MSGBOX
                  #endif
                    )
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(hwnd);

                    //don't auto close...
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                    if((_eMsgBoxMode != EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG)
                        && (_eMsgBoxMode != EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG))
#endif
                    {
                        MApp_ZUI_API_ResetTimer(HWND_MSGBOX_COMMON_BG, 0);
                    }
                }
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
                    || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE))
                {
                    MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
                }
#endif
		#if ( ENABLE_UPDATE_MULTIPLEX_VIA_NIT )
			#if ( ENABLE_NZ_FREEVIEW )
			    // Fixed #1258239 - [Freeview NZ_SI][v2.60_10][nz_si05f_026][TC15052000528] issue.
                else if( _eMsgBoxMode == EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX )
                {
                    if( ( bIsCellIDRemoveMsgBox ) && (u8KeyCode == KEY_NULL) )
                    {
                        bIsCellIDRemoveMsgBox = FALSE;
                        MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
                    }
                }
            #endif  //ENABLE_NZ_FREEVIEW
            #ifdef ENABLE_DELETE_PROGRAM_CONTROL
				else if(_eMsgBoxMode == EN_MSGBOX_MODE_PROGRAM_DELETE_MSGBOX)
                {
                    MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_MESSAGE_BOX_BTN_SELECT_YES);
                }
				else
                {
                    MApp_ZUI_API_ResetTimer(hwnd, 0);
                }
            #endif  //ENABLE_DELETE_PROGRAM_CONTROL
		#endif  //ENABLE_UPDATE_MULTIPLEX_VIA_NIT
        	}
            break;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, msg);
}

typedef struct
{
    HWND hwnd;
    HWND hwndNext;
    HWND hwndPressed;
    U16 * pVar;
    U8 u8ShiftBits;
}PASSWORD_INPUT_DATA_STRUCT;

S32 MApp_ZUI_ACT_MsgBox_PasswordInputWinProc(HWND hwnd, PMSG msg)
{
    static BOOLEAN _bPasswordBlinkBlack = FALSE;

    static  PASSWORD_INPUT_DATA_STRUCT _ZUI_TBLSEG _PasswordData[] =
    {
        {
            HWND_MSGBOX_PASSWORD_INPUT_1,
            HWND_MSGBOX_PASSWORD_INPUT_2,
            HWND_MSGBOX_PASSWORD_PRESSED_1,
            &PasswordInput1,
            0
        },
        {
            HWND_MSGBOX_PASSWORD_INPUT_2,
            HWND_MSGBOX_PASSWORD_INPUT_3,
            HWND_MSGBOX_PASSWORD_PRESSED_2,
            &PasswordInput1,
            4
        },
        {
            HWND_MSGBOX_PASSWORD_INPUT_3,
            HWND_MSGBOX_PASSWORD_INPUT_4,
            HWND_MSGBOX_PASSWORD_PRESSED_3,
            &PasswordInput1,
            8
        },
        {
            HWND_MSGBOX_PASSWORD_INPUT_4,
            HWND_MSGBOX_PASSWORD_PRESSED_4,
            HWND_MSGBOX_COMMON_BTN_OK,
            &PasswordInput1,
            12
        },
    };

    U8 i;
    for (i = 0; i < COUNTOF(_PasswordData); i++)
    {
        if (hwnd == _PasswordData[i].hwnd)
            break;
    }
    if (i == COUNTOF(_PasswordData)) //if not in the data list, we do nothing...
        return DEFAULTWINPROC(hwnd, msg);

    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
            {
                //enable blinking
                MApp_ZUI_API_SetTimer(hwnd, 0, 500);
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            return 0;

        case MSG_TIMER:
            {
                //blinking
                _bPasswordBlinkBlack = !_bPasswordBlinkBlack;
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            break;

        case MSG_NOTIFY_KILLFOCUS:
        case MSG_NOTIFY_HIDE:
            {
                //disable blinking
                MApp_ZUI_API_KillTimer(hwnd, 0);
            }
            return 0;

        case MSG_KEYDOWN:
            {
                if (VK_NUM_0 <= msg->wParam && msg->wParam <= VK_NUM_9 && i <= 3)
                {
                #if ENABLE_ATSC_TTS
                    U8 au8InputNumber[2];
                    au8InputNumber[0] = 0x30 + (msg->wParam - VK_NUM_0);
                    au8InputNumber[1] = 0;
                    MApp_TTS_Cus_AddU8String(au8InputNumber);
                    MApp_TTSControlSetOn(TRUE);
                    MApp_TTS_WaitSayFinish(2000);
                #endif
                    *(_PasswordData[i].pVar) &= ~(PASSWORD_INPUT_MASK<<_PasswordData[i].u8ShiftBits);
                    *(_PasswordData[i].pVar) |= ((msg->wParam-VK_NUM_0)<<_PasswordData[i].u8ShiftBits);
                        #if 1
                        if (i == 3) //last one
                        {
                            MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CHECK_INPUT_PASSWORD);
                        }
                        else
                        #endif
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }

                    return 0; //don't process default behavior....
                }
                else if (VK_LEFT== msg->wParam)
                {
                    MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_MSGBOX_BTN_CLEAR);
                    return 0;
                }
                else if(VK_RIGHT== msg->wParam)
                {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                    if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
                        || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG))
                    {
                        MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
                        printf("..........EN_EXE_CLOSE_CURRENT_OSD.......\n");
                        _eMsgBoxMode =EN_MSGBOX_MODE_INVALID;
                        MApp_UiPvr_RecordStart(0xFFFF);
                    }
                    else if((_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE)
                        || (_eMsgBoxMode == EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG))
                    {
                        MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
                        printf("..........EN_EXE_CLOSE_CURRENT_OSD.......\n");
                        _eMsgBoxMode =EN_MSGBOX_MODE_INVALID;
                        MApp_UiPvr_TimeshiftRecordStart(0xFFFF);
                    }
#endif
                    //MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
#if ENABLE_DMP
#if ENBALE_PARENTALRATING_MM
					if(IsStorageInUse())
				    {
                        MApp_ZUI_ACT_StartupOSD(E_OSD_DMP);
                        MApp_ZUI_API_ShowWindow(HWND_DMP_ALERT_WINDOW, SW_HIDE);
                        MApp_ZUI_ACT_ExecuteDmpAction(EN_EXE_DMP_PLAYBACK_BG_EXIT);
                        MApp_DMP_NotifyUiState(DMP_UI_STATE_FILE_SELECT);
                        MApp_BlockSys_SetBlockStatus(FALSE);
					}
#endif
#endif
                    return 0;
                }

            }
            break;

        case MSG_PAINT:
            {
                DEFAULTWINPROC(hwnd, msg);
                /*
                static  DRAW_RECT _ZUI_TBLSEG _DrawPasswordBlinkBgFocus =
                {
                    0x707070,
                    0x080808,
                    OSD_COLOR_GRADIENT_Y, //OSD_GRADIENT eRectGradient;
                    0, //OSD_COLOR BroderColor;
                    eRectBorder, //RECT_ATTRIB attrib;
                    0, //U8 sizeBorder;
                    0, //radius
                };
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)msg->wParam;
                if (param->bIsFocus && _bPasswordBlinkBlack)
                {

                    //2007/12/22: for bank issue, we prepare it in XDATA
                    DRAW_RECT * pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
                    if (pDraw)
                    {
                        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
                        memcpy(pDraw, &_DrawPasswordBlinkBgFocus, sizeof(DRAW_RECT));
                        _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, param->rect);
                        _ZUI_FREE(pDraw);
                    }
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else if (param->bIsFocus)
                {
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else
                {
                    //if focus is after this, show it as '*'
                    {
                        U8 j;
                        for (j = 0; j < COUNTOF(_PasswordData); j++)
                        {
                            if (MApp_ZUI_API_GetFocus()== _PasswordData[j].hwnd)
                                break;
                        }
                        if (j == COUNTOF(_PasswordData)) //if not in the password input, we do nothing...
                            return DEFAULTWINPROC(hwnd, msg);
                        if (i >= j) //if current password input is after focus (not yet input)
                            return DEFAULTWINPROC(hwnd, msg);
                    }
                    {
                        DRAW_TEXT_OUT_DYNAMIC * dyna;
                        U16 u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, DS_NORMAL, CP_TEXT_OUT);
                        if (u16TextIndex != 0xFFFF)
                        {
                            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);

                            dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                            if (dyna)
                            {
                                LPTSTR str = CHAR_BUFFER;
                                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                                str[0] = '*';
                                str[1] = 0;
                                dyna->pString = str;
                                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &param->dc, param->rect);
                                _ZUI_FREE(dyna);
                            }
                        }
                    }

                }*/
            }
            return 0;
        default:
            break;


    }

    return DEFAULTWINPROC(hwnd, msg);
}
#undef MAPP_ZUI_ACTMSGBOX_C
