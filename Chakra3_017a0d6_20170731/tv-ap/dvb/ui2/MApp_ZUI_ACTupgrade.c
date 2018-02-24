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

#define MAPP_ZUI_ACTUPGRADE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "MsCommon.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_GlobalVar.h"
#include "MApp_ZUI_CTLdynalist.h"
#include "MApp_GlobalSettingSt.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "ZUI_tables_h.inl"
#include "MApp_Exit.h"
#include "MApp_Menu_Main.h"
#include "MApp_OSDPage_Main.h"
#include "MApp_TopStateMachine.h"
#include "madp.h"

#include "MApp_ZUI_ACTupgrade.h"


extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
BOOLEAN g_bdetect_upgrade_packet=FALSE;

typedef enum
{
    STATE_UPGRADE_INIT,
    STATE_UPGRADE_EXIT,
    STATE_UPGRADE_WAIT,
    STATE_UPGRADE_STANDBY,
    STATE_UPGRADE_MAX
}EN_UPGRADE_STATE;



EN_UPGRADE_STATE enUpgradeState;
static U8 s_u8updatestate=UPGRADE_STATE_REQ;
U16 g_u16upgrade_pid=0;
U8 u8UpdateChIndex;

//////////////////////////////////////////////////////////
void vSetTopStateUpgrade(void)
{
    EN_TOP_STATE top_state;

    top_state=MApp_TopStateMachine_GetTopState();
    if(top_state==STATE_TOP_DIGITALINPUTS)
    {
        extern void MApp_TV_ExitAndGotoMenuState(void);
        MApp_TV_ExitAndGotoMenuState();
        MApp_TopStateMachine_SetTopState(STATE_TOP_UPGRADE);
    }
    else if(top_state == STATE_TOP_MENU)
    {
        extern EN_MENU_STATE enMainMenuState;
        enMainMenuState = STATE_MENU_INIT;
        MApp_TopStateMachine_SetTopState(STATE_TOP_UPGRADE);
    }
    else if(top_state == STATE_TOP_OSDPAGE)
    {
        MApp_OSDPage_SetState(STATE_OSDPAGE_INIT);
        MApp_TopStateMachine_SetTopState(STATE_TOP_UPGRADE);
    }
    else if(top_state == STATE_TOP_APENGINE)
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_UPGRADE);
    }
}

EN_RET MApp_Upgrade_Main(void)
{
    EN_RET enRetVal =EXIT_NULL;

    switch(enUpgradeState)
    {
        case STATE_UPGRADE_INIT:
            MApp_ZUI_ACT_StartupOSD(E_OSD_UPGRADE);
            enUpgradeState = STATE_UPGRADE_WAIT;
            break;

        case STATE_UPGRADE_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        case STATE_UPGRADE_EXIT:
            g_bdetect_upgrade_packet=FALSE;
            MApp_ZUI_ACT_ShutdownOSD();
            enUpgradeState = STATE_UPGRADE_INIT;
            enRetVal = EXIT_CLOSE;
            break;

        case STATE_UPGRADE_STANDBY:
            g_bdetect_upgrade_packet=FALSE;
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal = EXIT_GOTO_STANDBY;
            break;

    default:
        enUpgradeState = STATE_UPGRADE_WAIT;
        break;
    }
    return enRetVal;
}


void MApp_ZUI_ACT_AppShowUpgrade(void)
{
    HWND wnd;
    RECT rect;

    g_GUI_WindowList = _GUI_WindowList_Zui_Upgrade;
    g_GUI_WinDrawStyleList = _GUI_WindowsDrawStyleList_Zui_Upgrade;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Upgrade;
    #if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = _GUI_WindowsAlphaList_Zui_Upgrade;
    #endif
    HWND_MAX = HWND_UPGRADE_MAX;
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(E_OSD_UPGRADE);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(E_OSD_UPGRADE);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_UPGRADE_XSTART, ZUI_UPGRADE_YSTART,
        ZUI_UPGRADE_WIDTH, ZUI_UPGRADE_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    //note: set the first invalid rect equal to gwin size
    MApp_ZUI_API_InvalidateRect(&rect);
    for (wnd = 1; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

    MApp_ZUI_API_SetFocus(HWND_MENU_UPGRADE_YES);
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    s_u8updatestate=UPGRADE_STATE_REQ;
}

void MApp_ZUI_ACT_TerminateUpgrade(void)
{
    ZUI_MSG(printf("[]term:volume\n"));
    //enAudioVolumeState = _enTargetAudioVolumeState;
}

BOOLEAN MApp_Upgrade_Send_Command(U8 *cmd,U8 len)
{
    if(g_u16upgrade_pid != 0)  // application is running
    {
	    if (MAdp_MSGCH_SendSignal(g_u16upgrade_pid, u8UpdateChIndex, cmd, len))
	    {
	       printf("Send to upgrade daemon OK\n");
	       return TRUE;
	    }
	    else
	    {
	       printf("Send to upgrade daemon fail\n");
	       return FALSE;
	    }
   }
   return FALSE;
}


BOOLEAN MApp_ZUI_ACT_HandleUpgradeKey(VIRTUAL_KEY_CODE key)
{
    HWND hwnd;
    U8 tmp;
    //note: don't do anything here! keys will be handled in state machines
    //      moved to MApp_TV_ProcessAudioVolumeKey()
    switch((U8)key)
    {
        case VK_SELECT:
            hwnd=MApp_ZUI_API_GetFocus();
            if(hwnd==HWND_MENU_UPGRADE_YES)
            {
                tmp=UPGRADE_CMD_START;
                if(!MApp_Upgrade_Send_Command(&tmp,1))
                {
                    enUpgradeState=STATE_UPGRADE_EXIT;
                    return FALSE;
                }
                s_u8updatestate=UPGRADE_STATE_START;
                MApp_ZUI_API_ShowWindow(HWND_MENU_UPGRADE_INFO, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MENU_UPGRADE_SEL, SW_HIDE);
            }
            else if(hwnd==HWND_MENU_UPGRADE_NO)
            {
                tmp=UPGRADE_CMD_CANCEL;
                if(!MApp_Upgrade_Send_Command(&tmp,1))
                {
                    enUpgradeState=STATE_UPGRADE_EXIT;
                    return FALSE;
                }
                else
                    enUpgradeState=STATE_UPGRADE_EXIT;
            }
            return TRUE;
    }
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteUpgradeAction(U16 act)
{

    switch(act)
    {

        case EN_EXE_CLOSE_CURRENT_OSD:
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;

        case EN_EXE_RESET_AUTO_CLOSE_TIMER:
            //reset timer if any key
            //MApp_ZUI_API_ResetTimer(HWND_AUDIO_VOLUME_CONFIG_PANE, 0);
            return FALSE;

    }
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetUpgradeDynamicText(HWND hwnd)
{
    // Marked it by coverity_296
    //U16 u16TempID = Empty;
    char buf[255];
    switch(hwnd)
    {
        case HWND_MENU_UPGRADE_INFO:
            if(s_u8updatestate==UPGRADE_STATE_START)  //updating
                sprintf(buf,"Please don't power off!Updating...");
            else if(s_u8updatestate==UPGRADE_STATE_DONE) //upgrade ok
                sprintf(buf,"Upgrade OK!");
            else if(s_u8updatestate==UPGRADE_STATE_FAIL) //upgrade fail
                sprintf(buf,"Upgrade fail!");
            else if(s_u8updatestate==UPGRADE_STATE_UNPACK_DONE) //unpack image file OK
                sprintf(buf,"Unpack image file OK!Reboot now...");
            else if(s_u8updatestate==UPGRADE_STATE_UNPACK_ERROR) //unpack image fail
                sprintf(buf,"Unpack image file fail!Reboot now...");
            else
                sprintf(buf,"Detect upgrade packet.Upgrade now?");

            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)buf,strlen(buf));
            return CHAR_BUFFER;

    }

    return 0; //for empty string....
}

void MApp_ZUI_ACT_SetUpgradeState(U8 state)
{
    s_u8updatestate=state;
}


BOOLEAN MApp_Upgrade_SetMsgDisplayTime(void)
{
    // set the display message time
    unsigned char buffer[12];
    buffer[0] = UPGRADE_CMD_SET_MSG_DISPLAY_TIME;
    buffer[DISPPLAY_MSG_UPDATE_DONE+1] = 3;
    buffer[DISPPLAY_MSG_UPDATE_ERROR+1] = 3;
    buffer[DISPPLAY_MSG_UNPACK_DONE+1] = 3;
    buffer[DISPPLAY_MSG_UNPACK_ERROR+1] = 3;
    return MApp_Upgrade_Send_Command(buffer, 5);
}