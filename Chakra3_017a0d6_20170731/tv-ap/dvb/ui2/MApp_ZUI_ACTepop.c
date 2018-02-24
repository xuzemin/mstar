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

#define MAPP_ZUI_ACTEPOP_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------


#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiAUDIO.h"
#include "apiXC_Auto.h"
#include "apiXC_Ace.h"
#include "apiXC_Sys.h"

#include "MApp_GlobalSettingSt.h"
#include "msAPI_Timer.h"
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
#include "ZUI_exefunc.h"
#include "OSDcp_String_EnumIndex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MApp_UiMenuDef.h"
#include "apiGOP.h"
#include "MApp_InputSource.h"
#include "drvAUDIO_if.h"

#if ENABLE_E_POP

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern BOOLEAN MApp_IsSrcHasSignal(SCALER_WIN eWindow);
void MApp_ZUI_ACT_AppShowEpop(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_EPOP;
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
        ZUI_EPOP_XSTART, ZUI_EPOP_YSTART,
        ZUI_EPOP_WIDTH, ZUI_EPOP_HEIGHT);


    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    	}

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }



    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_EPOP_BG_PANE, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_EPOP_FRAME, SW_SHOW);
    //MApp_ZUI_API_SetTimer(HWND_EPOP_FRAME,0,8000);

}


BOOLEAN MApp_ZUI_ACT_ExecuteEpopAction(U16 act)
{

    UNUSED(act);
    return FALSE; //ignore...

}


BOOLEAN MApp_ZUI_ACT_HandleEpopKey(VIRTUAL_KEY_CODE key)
{
    UNUSED(key);
    return FALSE;

}


void MApp_ZUI_ACT_TerminateEpop(void)
{

	//printf("\n  MApp_ZUI_ACT_TerminateEpop \n");
}

LPTSTR MApp_ZUI_ACT_GetEpopDynamicText(HWND hwnd)
{
    UNUSED(hwnd);
    return 0; //for empty string....
}


S32 MApp_ZUI_ACT_EpopWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            break;
        case MSG_TIMER:
        //MApp_ZUI_API_KillTimer(HWND_EPOP_FRAME, 0);
        //MApp_ZUI_API_ShowWindow(HWND_EPOP_FRAME, SW_HIDE);
            break;
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

void MApp_ZUI_ACT_EpopHandler(void)
{
    if((MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
    && (stGenSetting.g_SysSetting.fEpop == TRUE)
    && (MApp_IsSrcHasSignal(MAIN_WINDOW) == TRUE) )
    {
         MApp_ZUI_ACT_StartupOSD(E_OSD_EPOP);
    }
}

#endif
#undef MAPP_ZUI_ACTEPOP_C
