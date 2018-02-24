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

#define MAPP_ZUI_MAIN_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


///////////////////////////////////////////////////////////////////////////////////////////////////
// Description: Menu GUI window/control basic functions
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "msAPI_MIU.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_ACTeffect.h"
#include "msAPI_Timer.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTsetclockfunc.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "OSDcp_String_EnumIndex.h"

#include "ZUI_tables_h.inl"
#include "ZUI_tables_c.inl"
#include "ZUI_componentTables_h.inl"
#include "ZUI_componentTables_c.inl"
#include "ZUI_posTables_c.inl"
#include "ZUI_styleTables_c.inl"
#include "ZUI_alphaTables_c.inl"
#include "msAPI_Global.h"

//-------------------------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------------------------

#define ZUI_DBG(x) //x

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------
ZUI_STATE _eZUIState = E_ZUI_STATE_UNKNOW;
E_OSD_ID  _eActiveOSD = E_OSD_EMPTY;

extern BOOLEAN _MApp_ZUI_API_WindowProcOnTimer(void);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);
//extern void MApp_ZUI_ACT_TerminateOSD(void);
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

#define ZUI_STATUS_MONITOR 0
#if ZUI_STATUS_MONITOR
#include "msAPI_Timer.h"
U32 zui_monitor_timer = 0;
ZUI_STATE preZUIState = 0;
#endif

extern void MApp_ZUI_ACTcoexistWin_Init(void);

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_Menu_MainTask
///  ZUI task/service entry
///
///  @return ZUI_RET latest state for ZUI task
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
extern void MApp_VDPlayer_MailBoxHandler(void);
extern BOOLEAN MApp_MPlayer_IsMoviePlaying(void);
extern MS_BOOL MApi_GOP_GWIN_IsEnabled(void);

#define ZUI_TASK_CHECKPOINT()   //CHECK_MIU_PROTECT_LOG_AND_CLEAR()

ZUI_RET MApp_ZUI_MainTask(void)
{
    static ZUI_STATE s_eZUIPrevState = E_ZUI_STATE_UNKNOW;

    ZUI_TASK_CHECKPOINT();

#if ZUI_STATUS_MONITOR
    if (msAPI_Timer_GetSystemTime() - zui_monitor_timer > 10)
    {
        printf("_eZUIState=%bx\n",_eZUIState);
        zui_monitor_timer = msAPI_Timer_GetSystemTime();
    }
    if(preZUIState != _eZUIState)
    {
        printf("_eZUIState=%bx\n",_eZUIState);
        preZUIState = _eZUIState;
    }
#endif

    switch (_eZUIState)
    {
        case E_ZUI_STATE_STANDBY:
            //PRINT("\n[MainTask] standby state");

            //note: don't dispatch this message, just let it go...

            break;

        case E_ZUI_STATE_TERMINATE:
            //2007/12/13: MApp_ZUI_API_EmptyMessageQueue();
            //2007/12/13: MApp_ZUI_API_TerminateGDI();
            //called inside MApp_ZUI_ACT_ShutdownOSD(): MApp_ZUI_ACT_TerminateOSD();
            MApp_ZUI_ACT_ShutdownOSD();

            s_eZUIPrevState = _eZUIState = E_ZUI_STATE_STANDBY;
            return RET_ZUI_EXIT;

        case E_ZUI_STATE_RUNNING:
            {
                MSG msg;

                //printf("[MainTask] runing state\n");
                //keep all messages are processed...
                while(MApp_ZUI_API_GetMessage(&msg))
                {
                    //printf("[taskX]\n");
                    //printf("[MainTask] got message win %u, msg %bu, wparam %lu\n", (U16)msg.hwnd, (U8)msg.message, (U32)msg.wParam);
                    ZUI_TASK_CHECKPOINT();
                    MApp_ZUI_API_DispatchMessage (&msg);
                    ZUI_TASK_CHECKPOINT();
                }
                //Note: in order to increase response time, so always check for invalide region   /*else*/

                //Note: if we are transfering to transition effect doing state, do nothing for this case:
				if (E_ZUI_STATE_RUNNING == _eZUIState)
                {
                    ZUI_TASK_CHECKPOINT();
                    //do drawing first, at this time, message queue is empty..
	            #if (ENABLE_UI_3D_PROCESS)
	                if(MApp_MPlayer_IsMoviePlaying() && MApp_ZUI_API_Is_UI_3D_Mode_ON() && MApi_GOP_GWIN_IsEnabled())
	                {
	                    MApp_VDPlayer_MailBoxHandler();
	                }
	            #endif
                    ZUI_TASK_CHECKPOINT();
                    _MApp_ZUI_API_WindowProcOnIdle();
                    ZUI_TASK_CHECKPOINT();
                #if (ENABLE_UI_3D_PROCESS)
                    if(MApp_MPlayer_IsMoviePlaying() && MApp_ZUI_API_Is_UI_3D_Mode_ON() && MApi_GOP_GWIN_IsEnabled())
                    {
                        MApp_VDPlayer_MailBoxHandler();
                    }
                #endif
                    ZUI_TASK_CHECKPOINT();
                    _MApp_ZUI_API_WindowProcOnTimer();
                    ZUI_TASK_CHECKPOINT();
                }
            }
            break;


        //case E_ZUI_STATE_TRANSEFF_BEGIN:
        //    MApp_Menu_TransInEffBegin();
        //    break;
        case E_ZUI_STATE_TRANSEFF_DOING:
            //2008/3/19: first time changed to E_ZUI_STATE_TRANSEFF_DOING
            //           process all remaining messages first..
            //           ex: MSG_NOTIFY_CONTENT_CHANGED
            if (_eZUIState != s_eZUIPrevState)
            {
                MSG msg;
                //printf("s_eZUIPrevState=%bx\n",s_eZUIPrevState);
                //keep all messages are processed...
                while(MApp_ZUI_API_GetMessage(&msg))
                {
                    ZUI_TASK_CHECKPOINT();
                    MApp_ZUI_API_DispatchMessage (&msg);
                    ZUI_TASK_CHECKPOINT();
                }
            }
            MApp_ZUI_ACT_TransitionEffectDoing();
            break;

        case E_ZUI_STATE_TRANSEFF_END:
            MApp_ZUI_ACT_TransitionEffectEnd();
            break;

        default:
            break;
    }

    s_eZUIPrevState = _eZUIState;

    ZUI_TASK_CHECKPOINT();

    return RET_ZUI_RUNNING;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_Init
///  ZUI system initialize
///
///  @return BOOLEAN TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_Init(void)
{
    HWND_MAX = HWND_MAINFRAME;
    OSDPAGE_BLENDING_ENABLE = FALSE;
    OSDPAGE_BLENDING_VALUE = ZUI_GWIN_BLENDING;
    if (!_MApp_ZUI_API_AllocateVarData()) //we have default HWND_MAX
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALINIT\n"));
        ABORT();
        return FALSE;
    }

    _eZUIState = E_ZUI_STATE_STANDBY;
    _eActiveOSD = E_OSD_EMPTY;
    if (MApp_ZUI_API_InitMsgQueue() == FALSE)
    {
        ZUI_DBG_FAIL(printf("[ZUI]MQINIT\n"));
        ABORT();
        return FALSE;
    }

    //done in MApp_ZUI_API_InitMsgQueue(): MApp_ZUI_API_EmptyMessageQueue();
    MApp_ZUI_API_InitGDIVariables();

    MApp_ZUI_ACTcoexistWin_Init();
    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_ProcessKey
///  send a key event into message queue
///
///  @param [in]       u8IRKey U8       key code
///
///  @return no return value
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ProcessKey(U8 u8IRKey)
{
    extern VIRTUAL_KEY_CODE _MApp_ZUI_ACT_MapToVirtualKeyCode(U8 IR_key_code);

    if ((_eZUIState == E_ZUI_STATE_RUNNING) || (_eZUIState == E_ZUI_STATE_TRANSEFF_DOING)) //if (u8IRKey != KEY_NULL)
    {
        VIRTUAL_KEY_CODE vk_code = _MApp_ZUI_ACT_MapToVirtualKeyCode(u8IRKey);
        if (vk_code != VK_NULL)
        {
            //printf("[]st=%bu,at=%bu\n", _eZUIState, _eActiveOSD);
            ZUI_MSG(printf("KeyDown:%x\n", u8IRKey));
            MApp_ZUI_ACT_GetTenKeyNum(u8IRKey);
            MApp_ZUI_API_PostMessage(HWND_MAINFRAME, MSG_KEYDOWN, vk_code);
        }
    }
#if ENABLE_OAD
	else if(_eZUIState == E_ZUI_STATE_STANDBY)
	{
		VIRTUAL_KEY_CODE vk_code = _MApp_ZUI_ACT_MapToVirtualKeyCode(u8IRKey);
		if(vk_code == VK_POWER)
		{
			extern void MApp_OAD_StandbyReceivePowerKey(void);
			MApp_OAD_StandbyReceivePowerKey();
		}
	}
#endif
}


///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_GetState
///  query current state of ZUI
///
///  @return ZUI_STATE current state
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
ZUI_STATE MApp_ZUI_GetState(void)
{
    return _eZUIState;
}

///////////////////////////////////////////////////////////////////////////////
///  public  MApp_ZUI_GetActiveOSD
///  query for the current OSD page in ZUI system
///
///  @return E_OSD_ID current osd page
///
///  @author MStarSemi @date 2007/3/2
///////////////////////////////////////////////////////////////////////////////
U32 MApp_ZUI_GetActiveOSD(void)
{
    return (U32) _eActiveOSD;
}
U32 MApp_ZUI_GetActive_ChannelInfo_OSD(void)
{
#if(ENABLE_ATSC)
    if (IsAtscInUse() || IsATVInUse())
    {
        if(MApp_ZUI_GetActiveOSD()==E_OSD_CHANNEL_INFO_ATSC)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if (MApp_ZUI_GetActiveOSD()==E_OSD_CHANNEL_INFO)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

#undef MAPP_ZUI_MAIN_C
