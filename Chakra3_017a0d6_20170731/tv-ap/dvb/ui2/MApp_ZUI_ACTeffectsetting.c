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

#define MAPP_ZUI_ACTEFFECTSETTING_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_CTLeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_OSDPage_Main.h"
#include "MApp_ZUI_ACTeffectsetting.h"

#include "MApp_GlobalFunction.h"
#include "msAPI_audio.h"
#include "MApp_Scaler.h"
#include "MApp_SaveData.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_UiMenuDef.h"

/////////////////////////////////////////////////////////////////////
static EN_OSDPAGE_STATE _enTargetState;

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

void MApp_ZUI_ACT_AppShowEffectSetting(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_EFFECT_SETTING;

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
        ZUI_EFFECT_SETTING_XSTART, ZUI_EFFECT_SETTING_YSTART,
        ZUI_EFFECT_SETTING_WIDTH, ZUI_EFFECT_SETTING_HEIGHT);

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

    MApp_ZUI_API_SetFocus(HWND_EFFECT_MAIN_PAGE);

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    //printf("KY test.....MApp_ZUI_ACT_AppShowEffectSetting end\n");

}


//////////////////////////////////////////////////////////
// Key Handler

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

U16 _MApp_ZUI_ACT_GetMainPageStringID(EN_3D_MAIN_PAGE eMainPageEff)
{
    U16 u16TempID;
    switch(eMainPageEff)
    {
        case EN_3D_MAIN_PAGE_MotionTrans:
            u16TempID = en_str_Motion_Transdot;
            break;
        case EN_3D_MAIN_PAGE_Fake3D:
            u16TempID = en_str_Fake_3D;
            break;
/*
        case EN_3D_MAIN_PAGE_EFF3:
            u16TempID = en_str_Effect_Main_Page_Eff3;
            break;
        case EN_3D_MAIN_PAGE_EFF4:
            u16TempID = en_str_Effect_Main_Page_Eff4;
            break;
*/
        default:
            u16TempID = Empty;
    }
    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetMainMenuOpenStringID(EN_3D_MAIN_MENU_OPEN eMainMenuOpenEff)
{
    U16 u16TempID;
    switch(eMainMenuOpenEff)
    {
        case EN_3D_MAIN_MENU_OPEN_OFF:
            u16TempID = en_str_Off;
            break;
/*
        case EN_3D_MAIN_MENU_OPEN_SPREAD:
            u16TempID = en_str_Spread_Out;
            break;
*/
        case EN_3D_MAIN_MENU_OPEN_FADE:
            u16TempID = en_str_Fade_In;
            break;
        case EN_3D_MAIN_MENU_OPEN_MOSAIC:
            u16TempID = 
en_str_Mosaic;
            break;
        case EN_3D_MAIN_MENU_OPEN_UP:
            u16TempID = en_str_Up;
            break;
        case EN_3D_MAIN_MENU_OPEN_DOWN:
            u16TempID = en_str_Down;
            break;
        case EN_3D_MAIN_MENU_OPEN_LEFT:
            u16TempID = en_str_Left;
            break;
        case EN_3D_MAIN_MENU_OPEN_RIGHT:
            u16TempID = en_str_Right;
            break;
        default:
            u16TempID = Empty;
    }
    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetMainMenuCloseStringID(EN_3D_MAIN_MENU_CLOSE eMainMenuCloseEff)
{
    U16 u16TempID;
    switch(eMainMenuCloseEff)
    {
        case EN_3D_MAIN_MENU_CLOSE_OFF:
            u16TempID = en_str_Off;
            break;
        case EN_3D_MAIN_MENU_CLOSE_ROLL:
            u16TempID = en_str_Roll_Up;
            break;
        case EN_3D_MAIN_MENU_CLOSE_FADE:
            u16TempID = en_str_Fade_Out;
            break;
        case EN_3D_MAIN_MENU_CLOSE_UP:
            u16TempID = en_str_Up;
            break;
        case EN_3D_MAIN_MENU_CLOSE_DOWN:
            u16TempID = en_str_Down;
            break;
        case EN_3D_MAIN_MENU_CLOSE_LEFT:
            u16TempID = en_str_Left;
            break;
        case EN_3D_MAIN_MENU_CLOSE_RIGHT:
            u16TempID = en_str_Right;
            break;
        default:
            u16TempID = Empty;
    }
    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetMainMenuItemStringID(EN_3D_MAIN_MENU_ITEM eMainMenuItemEff)
{
    U16 u16TempID;
    switch(eMainMenuItemEff)
    {
        case EN_3D_MAIN_MENU_ITEM_OFF:
            u16TempID = en_str_Off;
            break;
        case EN_3D_MAIN_MENU_ITEM_ON:
            u16TempID = en_str_On;
            break;
        default:
            u16TempID = Empty;
    }
    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetPopupDialogStringID(EN_3D_POPUP_DIALOG ePopupDialogEff)
{
    U16 u16TempID;
    switch(ePopupDialogEff)
    {
        case EN_3D_POPUP_DIALOG_OFF:
            u16TempID = en_str_Off;
            break;
        case EN_3D_POPUP_DIALOG_ON:
            u16TempID = en_str_On;
            break;
        default:
            u16TempID = Empty;
    }
    return u16TempID;
}

U16 _MApp_ZUI_ACT_GetAssistantMenuStringID(EN_3D_ASSISTANT_MENU eAssistantMenuEff)
{
    U16 u16TempID;
    switch(eAssistantMenuEff)
    {
        case EN_3D_ASSISTANT_MENU_OFF:
            u16TempID = en_str_Off;
            break;
        case EN_3D_ASSISTANT_MENU_ROLL:
            u16TempID = en_str_Roll;
            break;
        case EN_3D_ASSISTANT_MENU_FADE:
            u16TempID = en_str_Fade;
            break;
        case EN_3D_ASSISTANT_MENU_MOSAIC:
            u16TempID = 
en_str_Mosaic;
            break;
        case EN_3D_ASSISTANT_MENU_UP:
            u16TempID = en_str_Up;
            break;
        case EN_3D_ASSISTANT_MENU_DOWN:
            u16TempID = en_str_Down;
            break;
        case EN_3D_ASSISTANT_MENU_LEFT:
            u16TempID = en_str_Left;
            break;
        case EN_3D_ASSISTANT_MENU_RIGHT:
            u16TempID = en_str_Right;
            break;
        default:
            u16TempID = Empty;
    }
    return u16TempID;
}

BOOLEAN MApp_ZUI_ACT_HandleEffectSettingKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    //printf("received key=%d\n", key);
    MApp_ZUI_API_ResetTimer(HWND_EFFECT_BACKGROUND, 0);

    //show click animation
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            {VK_SELECT, HWND_EFFECT_BOTTOM_HALF_OK_BG},
            {VK_EXIT, HWND_EFFECT_BOTTOM_HALF_EXIT_BG},
            {VK_UP, HWND_EFFECT_BOTTOM_HALF_UP_ARROW},
            {VK_DOWN, HWND_EFFECT_BOTTOM_HALF_DOWN_ARROW},
            {VK_LEFT, HWND_EFFECT_BOTTOM_HALF_LEFT_ARROW},
            {VK_RIGHT, HWND_EFFECT_BOTTOM_HALF_RIGHT_ARROW},
        };
        U8 i;

        for (i = 0; i < COUNTOF(_key2btn); i++)
        {
            if (_key2btn[i].key == key)
            {
                MApp_ZUI_API_SetTimer(_key2btn[i].hwnd, 0, BUTTONANICLICK_PERIOD);
                MApp_ZUI_API_InvalidateWindow(_key2btn[i].hwnd);
                break;
            }
        }
    }

    switch(key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_ExecuteEffectSettingAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecuteEffectSettingAction(EN_EXE_POWEROFF);
            return TRUE;

        case VK_MENU:
            MApp_ZUI_ACT_ExecuteEffectSettingAction(EN_EXE_GOTO_MAINMENU);
            return TRUE;

        case VK_INPUT_SOURCE:
            MApp_ZUI_ACT_ExecuteEffectSettingAction(EN_EXE_SHOW_SOURCE_BANNER);
            return TRUE;

        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateEffectSetting(void)
{
    ZUI_MSG(printf("[]term:install\n");)
    MApp_OSDPage_SetState(_enTargetState);
}

BOOLEAN MApp_ZUI_ACT_ExecuteEffectSettingAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_CLEAN_UP;
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_STANDBY;
            return TRUE;

        ///adjust functions//////////////////////
        case EN_EXE_INC_MAIN_PAGE:
        case EN_EXE_DEC_MAIN_PAGE:
            return TRUE;

        case EN_EXE_INC_MAIN_MENU_OPEN:
        case EN_EXE_DEC_MAIN_MENU_OPEN:
            return TRUE;

        case EN_EXE_INC_MAIN_MENU_CLOSE:
        case EN_EXE_DEC_MAIN_MENU_CLOSE:
            return TRUE;

        case EN_EXE_INC_MAIN_MENU_ITEM:
        case EN_EXE_DEC_MAIN_MENU_ITEM:
            return TRUE;

        case EN_EXE_INC_POPUP_DIALOG:
        case EN_EXE_DEC_POPUP_DIALOG:
            return TRUE;

        case EN_EXE_INC_ASSISTANT_MENU:
        case EN_EXE_DEC_ASSISTANT_MENU:
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_MAIN_MENU;
            return TRUE;

        case EN_EXE_SHOW_SOURCE_BANNER:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetState = STATE_OSDPAGE_GOTO_INPUT_SOURCE;
            return TRUE;

    }
    return FALSE;
}


LPTSTR MApp_ZUI_ACT_GetEffectSettingDynamicText(HWND hwnd)
{
    UNUSED(hwnd);
    return 0; //for empty string....
}

/////////////////////////////////////////////////////////
// Customize Window Procedures


#undef MAPP_ZUI_ACTEFFECTSETTING_C
