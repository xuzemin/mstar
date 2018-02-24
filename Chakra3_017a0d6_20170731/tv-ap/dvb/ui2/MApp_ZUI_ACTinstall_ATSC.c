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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTINSTALL_ATSC_C
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
#include "msAPI_Global.h"
#include "msAPI_VD.h"
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
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_Install_Main_ATSC.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmenufunc.h"
#include "MApp_ZUI_ACTinstall_ATSC.h"
#include "MApp_TopStateMachine.h"
#include "MApp_Menu_Main.h"
#include "MApp_Scan_ATSC.h"
#include "MApp_InputSource.h"
#include "MApp_GlobalFunction.h"
#include "msAPI_audio.h"
#include "MApp_Scaler.h"
#include "MApp_SaveData.h"
#if  ENABLE_SBTVD_BRAZIL_APP
#include "MApp_ChannelChange.h"
#include "MApp_InputSource.h"
#endif
#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_UiMenuDef.h"
#include "MApp_Menu_Main.h"
#include "MApp_UiMenuFunc_ATSC.h"
#if ENABLE_DVBC
#include "MApp_TopStateMachine.h"
#endif
/////////////////////////////////////////////////////////////////////

extern EN_MENU_STATE enMainMenuState;
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

void MApp_ZUI_ACT_AppShowInstallGuide_ATSC(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_INSTALL_GUIDE_ATSC;

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
        ZUI_INSTALL_GUIDE_ATSC_XSTART, ZUI_INSTALL_GUIDE_ATSC_YSTART,
        ZUI_INSTALL_GUIDE_ATSC_WIDTH, ZUI_INSTALL_GUIDE_ATSC_HEIGHT);

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

    //_eTempCountry = OSD_COUNTRY_SETTING; //initial temp country

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_PAGE_TIME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_PAGE_ANT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_SCAN_RESULT_SUB_PAGE, SW_HIDE);

    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_OSD_LANGUAGE);

}


LPTSTR MApp_ZUI_ACT_GetInstallGuideDynamicText_ATSC(HWND hwnd)
{
    U16 u16TempID = Empty;
    U16 u16Value;
    switch(hwnd)
    {
        case HWND_INSTALL_MAIN_OSD_LANGUAGE_OPTION:
            switch(MENU_LANGUAGE)
            {
                case LANGUAGE_ENGLISH:
                    u16TempID = en_str_English;
                    break;
                case LANGUAGE_FRENCH:
                    u16TempID = en_str_French;
                    break;
                case LANGUAGE_SPANISH:
                    u16TempID = en_str_Spanish;
                    break;
                default:
                    //
                    break;
            }
            break;
        case HWND_INSTALL_MAIN_OSD_TIME_OPTION:
            switch(stGenSetting.g_SysSetting.u8TimeZone)
            {
                case TIME_ZONE_ATLANTIC:
                    u16TempID = en_str_Atlantic;
                    break;
                case TIME_ZONE_EASTERN:
                    u16TempID = en_str_Eastern;
                    break;
                case TIME_ZONE_CENTRAL:
                    u16TempID = en_str_Central;
                    break;
                case TIME_ZONE_MOUNTAIN:
                    u16TempID = en_str_Mountain;
                    break;
                case TIME_ZONE_PACIFIC:
                    u16TempID = en_str_Pacific;
                    break;
                case TIME_ZONE_ALASKA:
                    u16TempID = en_str_Alaska;
                    break;
                case TIME_ZONE_HAWAII:
                    u16TempID = en_str_Hawaii;
                    break;
                default:
                    //
                    break;
            }
            break;
#if 0
        case HWND_INSTALL_MAIN_OSD_DST_OPTION:
            switch(stGenSetting.g_SysSetting.fTimeDST)
            {
                case TIME_DST_OFF:
                    u16TempID = en_str_Off;
                    break;
                case TIME_DST_ON:
                    u16TempID = en_str_On;
                    break;
                default:
                    //
                    break;
            }
            break;
#endif
        case HWND_INSTALL_MAIN_OSD_TIME_FORMAT_OPTION:
            if(stGenSetting.g_SysSetting.fTimeFormat == 0)
                u16TempID = en_str_24dashhour;
            else
                u16TempID = en_str_12dashhour;
            break;
        case HWND_INSTALL_MAIN_OSD_ANT_OPTION:
            switch(stGenSetting.stScanMenuSetting.u8Antenna)
            {
                case ANT_CATV:
                    u16TempID = en_str_Cable;
                    break;
                case ANT_AIR:
                    u16TempID = en_str_Air;
                    break;
                default:
                    //
                    break;
            }
            break;
         case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_ITEM_RFCH_VALUE:
            MApp_ZUI_API_ResetTimer(HWND_INSTALL_BACKGROUND, 0);
            u16Value = MApp_Scan_ATSC_GetCurRfCh();
        	printf("\n============ GetCurRfCh : %d ============\n",u16Value);
            return MApp_ZUI_API_GetU16String(u16Value);
         case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_ITEM_FOUND_VALUE:
            u16Value = MApp_Scan_ATSC_GetScanCHFound();
            return MApp_ZUI_API_GetU16String(u16Value);
         case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_ITEM_ANALOG_VALUE:
            u16Value = MApp_Scan_ATSC_GetScanAnalogCHFound();
            return MApp_ZUI_API_GetU16String(u16Value);
         case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_ITEM_DIGITAL_VALUE:
            u16Value = MApp_Scan_ATSC_GetScanDigitalCHFound();
            return MApp_ZUI_API_GetU16String(u16Value);
         case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_ITEM_PERCENT:
            u16Value = MApp_Scan_ATSC_GetScanPercentageValue();
        	printf("\n============ ScanPercentageValue : %d ============\n",u16Value);
            return MApp_ZUI_API_GetU16String(u16Value);
         case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_ITEM_CH_TYPE:
            if(MApp_Scan_ATSC_GetScanSubState() == NTSC_SCAN_STATE)
                u16TempID = en_str_ATV;
            else
                u16TempID = en_str_DTV;
            break;
        default:
            //
            break;
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

S16 MApp_ZUI_ACT_GetInstallGuideDynamicValue_ATSC(HWND hwnd)
{
    switch(hwnd)
    {

        case HWND_INSTALL_SCAN_RESULT_SUB_PAGE_PROGRESSBAR:
            return MApp_Scan_ATSC_GetScanPercentageValue();
        default:
            //
            break;
    }

    return 0; //for empty  data
}

BOOLEAN MApp_ZUI_ACT_ExecuteInstallGuideAction_ATSC(U16 act)
{
    HWND hwnd;
    MApp_ZUI_API_ResetTimer(HWND_INSTALL_BACKGROUND, 0);

    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_ShutdownOSD();
            stGenSetting.g_SysSetting.fFinishWizardMode = TRUE;

            enMainMenuState = STATE_MENU_INIT;
            MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);

            _enReturnMenuItem = STATE_RETURN_NULL;//STATE_RETURN_SETUP_WIZARD;   //    take care
            return TRUE;

        case EN_EXE_DEC_VALUE:
            hwnd = MApp_ZUI_API_GetFocus();
            switch(hwnd)
            {
                case HWND_INSTALL_MAIN_OSD_LANGUAGE:
                    MApp_UiMenuFunc_AdjustOptionLanguage(FALSE);
                    break;
                case HWND_INSTALL_MAIN_OSD_TIME:
                    MApp_UiMenuFunc_AdjTimeZone(FALSE);
                    break;
                    #if 0
                case HWND_INSTALL_MAIN_OSD_DST:
                    MApp_UiMenuFunc_AdjTimeDST(FALSE);
                    break;
                    #endif
                case HWND_INSTALL_MAIN_OSD_TIME_FORMAT:
                    MApp_UiMenuFunc_AdjTimeFormat();
                    break;
                case HWND_INSTALL_MAIN_OSD_ANT:
                    MApp_UiMenuFunc_AdjChannelAntenna(FALSE);
                    break;
                default:
                    //
                    break;
            }
            MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
            return TRUE;
        case EN_EXE_INC_VALUE:
            hwnd = MApp_ZUI_API_GetFocus();
            switch(hwnd)
            {
                case HWND_INSTALL_MAIN_OSD_LANGUAGE:
                    MApp_UiMenuFunc_AdjustOptionLanguage(TRUE);
                    break;
                case HWND_INSTALL_MAIN_OSD_TIME:
                    MApp_UiMenuFunc_AdjTimeZone(TRUE);
                    break;
                    #if 0
                case HWND_INSTALL_MAIN_OSD_DST:
                    MApp_UiMenuFunc_AdjTimeDST(TRUE);
                    break;
                    #endif
                case HWND_INSTALL_MAIN_OSD_TIME_FORMAT:
                    MApp_UiMenuFunc_AdjTimeFormat();
                    break;
                case HWND_INSTALL_MAIN_OSD_ANT:
                    MApp_UiMenuFunc_AdjChannelAntenna(TRUE);
                    break;
                default:
                    //
                    break;
            }
            MApp_ZUI_API_InvalidateAllSuccessors(hwnd);
            return TRUE;
        case EN_EXE_GOTO_PARENTPAGE:
            hwnd = MApp_ZUI_API_GetFocus();
            switch(hwnd)
            {
                case HWND_INSTALL_MAIN_OSD_LANGUAGE:
                case HWND_INSTALL_MAIN_OSD_LANGUAGE_NEXT:
                    MApp_ZUI_ACT_ShutdownOSD();
                    stGenSetting.g_SysSetting.fFinishWizardMode =TRUE;

                    //enUiMainMenuState = STATE_UIMENU_WAIT;
                	enMainMenuState = STATE_MENU_WAIT;
                    MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);

                    _enReturnMenuItem = STATE_RETURN_SETUP_WIZARD;  // take care

                    MApp_ZUI_ACT_StartupOSD(E_OSD_MAIN_MENU);
                    break;
                case HWND_INSTALL_MAIN_OSD_TIME:
                //case HWND_INSTALL_MAIN_OSD_DST:
                case HWND_INSTALL_MAIN_OSD_TIME_FORMAT:
                case HWND_INSTALL_MAIN_OSD_TIME_NEXT:
                    MApp_ZUI_API_ShowWindow(MApp_ZUI_API_GetParent(hwnd), SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_PAGE_LANGUAGE, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_OSD_LANGUAGE);
                    break;
                case HWND_INSTALL_MAIN_OSD_ANT:
                case HWND_INSTALL_MAIN_OSD_ANT_NEXT:
                    MApp_ZUI_API_ShowWindow(MApp_ZUI_API_GetParent(hwnd), SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_PAGE_TIME, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_OSD_TIME);
                    break;
                default:
                    //
                    break;
            }
            break;
        case EN_EXE_GOTO_SUBPAGE:
            hwnd = MApp_ZUI_API_GetFocus();
            switch(hwnd)
            {
                case HWND_INSTALL_MAIN_OSD_LANGUAGE_NEXT:
                    MApp_ZUI_API_ShowWindow(MApp_ZUI_API_GetParent(hwnd), SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_PAGE_TIME, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_OSD_TIME_FORMAT, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_OSD_TIME);
                    break;
                case HWND_INSTALL_MAIN_OSD_TIME_NEXT:
                    MApp_ZUI_API_ShowWindow(MApp_ZUI_API_GetParent(hwnd), SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_PAGE_ANT, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_OSD_ANT);
                    break;
                case HWND_INSTALL_MAIN_OSD_ANT_NEXT:
                    MApp_ZUI_API_ShowWindow(MApp_ZUI_API_GetParent(hwnd), SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_BACKGROUND_OK, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_INSTALL_SCAN_RESULT_SUB_PAGE, SW_SHOW);
                    MApp_Scan_ATSC_SetAutoScan();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ATSC_SCAN);
                    //MApp_TV_ExecuteAutoScan();
                    stGenSetting.g_SysSetting.fFinishWizardMode = TRUE;
                    if(stSystemInfo[MAIN_WINDOW].enInputSourceType != INPUT_SOURCE_TV)
                    {
                        MApp_InputSource_SwitchSource((E_UI_INPUT_SOURCE) INPUT_SOURCE_TV, MAIN_WINDOW );
                        UI_INPUT_SOURCE_TYPE = (E_UI_INPUT_SOURCE) INPUT_SOURCE_TV;
                    }
                    break;
                default:
                    //
                    break;
            }
            break;

        case EN_EXE_REPAINT_AUTOTUNING_PROGRESS:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_INSTALL_SCAN_RESULT_SUB_PAGE);
            break;
        default:
            //
            break;

    }
    return FALSE;
}

//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleInstallGuideKey_ATSC(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    //MApp_ZUI_API_ResetTimer(HWND_INSTALL_BACKGROUND, 0);


    switch(key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_ShutdownOSD();
            stGenSetting.g_SysSetting.fFinishWizardMode = TRUE;

            enMainMenuState = STATE_MENU_WAIT;
            MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);
            _enReturnMenuItem = STATE_RETURN_SETUP_WIZARD;
            MApp_ZUI_ACT_StartupOSD(E_OSD_MAIN_MENU);
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_TopStateMachine_SetTopState(STATE_TOP_STDBY);
            return TRUE;
        default:
            //
            break;
    }
    return FALSE;
}


void MApp_ZUI_ACT_TerminateInstallGuide_ATSC(void)
{
    //MApp_SaveGenSetting();
}

/////////////////////////////////////////////////////////
// Customize Window Procedures
S32 MApp_ZUI_ACT_InstallGuideWinProc_ATSC(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                U32 timeout_ms = MApp_ZUI_API_GetWindowData(hwnd);
                if (timeout_ms > 0)
                {
                    //setting AP timeout, auto close
                    MApp_ZUI_API_SetTimer(hwnd, 0, timeout_ms);
                }
            }
            break;

        case MSG_TIMER:
            {
                if (MApp_ZUI_API_IsWindowVisible(HWND_INSTALL_BACKGROUND_ATSC))
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                }
            }
            break;

        default:
            break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}

#if 0	//
extern EN_INSTALL_STATE enInstallGuideState;

static EN_INSTALL_STATE _enTargetInstallState;

EN_INSTALL_GUIDE_PAGE enInstallGuidePage = PAGE_INSTALL_OSD_LANGUAGE;

#if ENABLE_SBTVD_BRAZIL_APP
extern E_ANTENNA_SOURCE_TYPE enLastWatchAntennaType;
#endif

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
void MApp_ZUI_ACT_Set_InstallGuidePage(EN_INSTALL_GUIDE_PAGE enPageIndex)
{
	enInstallGuidePage = enPageIndex;
}

EN_INSTALL_GUIDE_PAGE MApp_ZUI_ACT_Get_InstallGuidePage(void)
{
	return enInstallGuidePage;
}

//NOTE: when we are selecting country, don't modify the real one!!
EN_OSD_COUNTRY_SETTING _eTempCountry;

U8 MApp_ZUI_ACT_Install_GetOsdLanguageIndex(void)
{
    return GET_OSD_MENU_LANGUAGE_DTG();
}
void MApp_ZUI_ACT_Install_SetOsdLanguageIndex(U8 u8Index)
{
    SET_OSD_MENU_LANGUAGE((EN_LANGUAGE)u8Index);
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_INSTALL_MAIN_PAGE);
}

LPTSTR MApp_ZUI_ACT_Install_GetLanguageStringByIndex(U8 u8Index)
{
    U16 u16TempID = Empty;
    if(u8Index <= LANGUAGE_MENU_MAX)
    {
        u16TempID = _MApp_ZUI_ACT_GetLanguageStringID((EN_LANGUAGE)u8Index, FALSE);
        if (u16TempID != Empty)
            return MApp_ZUI_API_GetString(u16TempID);
    }
    return 0; //for empty string....
}
extern ST_OSD_SELECTION_STRING_MAPPING_LIST stAutoTuningCountryList[];
extern U8 MApp_ZUI_ACT_GetTuningCountryIndexMax(void);
extern LPTSTR MApp_ZUI_ACT_GetCountryStringByIndex(U8 u8Index);
U8 MApp_ZUI_ACT_Install_GetTuningMenuCountryIndex(void)
{
    U8 u8Idx = 0;
    for (u8Idx = 0; u8Idx <= MApp_ZUI_ACT_GetTuningCountryIndexMax(); u8Idx++)
    {
        if (_eTempCountry == (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Idx].u16SelectionItem)
        {
            return u8Idx;
        }
    }
    return 0;
}
void MApp_ZUI_ACT_Install_SetTuningMenuCountryIndex( U8 u8Index )
{
    _eTempCountry = (EN_OSD_COUNTRY_SETTING)stAutoTuningCountryList[u8Index].u16SelectionItem;
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_INSTALL_MAIN_PAGE);
}
LPTSTR MApp_ZUI_ACT_Install_GetCountryStringIDByIndex(U8 u8Index)
{
    return MApp_ZUI_ACT_GetCountryStringByIndex(u8Index);
}

void MApp_ZUI_ACT_AppShowInstallGuide(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_INSTALL_GUIDE;

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
        ZUI_INSTALL_GUIDE_XSTART, ZUI_INSTALL_GUIDE_YSTART,
        ZUI_INSTALL_GUIDE_WIDTH, ZUI_INSTALL_GUIDE_HEIGHT);

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

    _eTempCountry = OSD_COUNTRY_SETTING; //initial temp country

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);

#if 0 //ENABLE_SBTVD_BRAZIL_APP
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_OSD_LANGUAGE, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_COUNTRY, SW_HIDE);
    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_AUTO_TUNE);
#else
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_TEXT_1, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_INSTALL_MAIN_TEXT_2, SW_HIDE);
    //MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_OSD_LANGUAGE);
#endif
    if( MApp_ZUI_ACT_Get_InstallGuidePage() == PAGE_INSTALL_OSD_LANGUAGE )
    {
        MApp_ZUI_CTL_Grid_SetIndex(HWND_INSTALL_MAIN_PAGE_GRID, MApp_ZUI_ACT_Install_GetOsdLanguageIndex, MApp_ZUI_ACT_Install_SetOsdLanguageIndex, LANGUAGE_MENU_MIN, LANGUAGE_MENU_MAX);
        MApp_ZUI_CTL_Grid_SetFnGetTextByIndex(HWND_INSTALL_MAIN_PAGE_GRID, MApp_ZUI_ACT_Install_GetLanguageStringByIndex);

    }
    else
    {
        MApp_ZUI_CTL_Grid_SetIndex(HWND_INSTALL_MAIN_PAGE_GRID, MApp_ZUI_ACT_Install_GetTuningMenuCountryIndex, MApp_ZUI_ACT_Install_SetTuningMenuCountryIndex, 0, MApp_ZUI_ACT_GetTuningCountryIndexMax());
        MApp_ZUI_CTL_Grid_SetFnGetTextByIndex(HWND_INSTALL_MAIN_PAGE_GRID, MApp_ZUI_ACT_Install_GetCountryStringIDByIndex);
    }
    MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_PAGE_GRID);

    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////
// Key Handler

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

BOOLEAN MApp_ZUI_ACT_HandleInstallGuideKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_INSTALL_BACKGROUND, 0);

    /*//show click animation
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            {VK_SELECT, HWND_INSTALL_BOTTOM_HALF_OK_BG},
            {VK_EXIT, HWND_INSTALL_BOTTOM_HALF_EXIT_BG},
            {VK_UP, HWND_INSTALL_BOTTOM_HALF_UP_ARROW},
            {VK_DOWN, HWND_INSTALL_BOTTOM_HALF_DOWN_ARROW},
            {VK_LEFT, HWND_INSTALL_BOTTOM_HALF_LEFT_ARROW},
            {VK_RIGHT, HWND_INSTALL_BOTTOM_HALF_RIGHT_ARROW},
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
    }*/

    switch(key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_ExecuteInstallGuideAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecuteInstallGuideAction(EN_EXE_POWEROFF);
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateInstallGuide(void)
{
    ZUI_MSG(printf("[]term:install\n");)
    enInstallGuideState = _enTargetInstallState;
}

BOOLEAN MApp_ZUI_ACT_ExecuteInstallGuideAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            stGenSetting.stMiscSetting.bRunInstallationGuide = FALSE;
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInstallState = STATE_INSTALL_CLEAN_UP;
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetInstallState = STATE_INSTALL_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_GOTO_AUTO_TUNING:
            if( MApp_ZUI_ACT_Get_InstallGuidePage() == PAGE_INSTALL_OSD_LANGUAGE )
            {
                MApp_ZUI_ACT_SetTuningCountryByOSDLanguage();
                MApp_ZUI_CTL_Grid_SetIndex(HWND_INSTALL_MAIN_PAGE_GRID, MApp_ZUI_ACT_Install_GetTuningMenuCountryIndex, MApp_ZUI_ACT_Install_SetTuningMenuCountryIndex, 0, MApp_ZUI_ACT_GetTuningCountryIndexMax());
                MApp_ZUI_CTL_Grid_SetFnGetTextByIndex(HWND_INSTALL_MAIN_PAGE_GRID, MApp_ZUI_ACT_Install_GetCountryStringIDByIndex);
            #if ENABLE_DVBC
                MApp_ZUI_ACT_Set_InstallGuidePage(PAGE_INSTALL_SELECT_DVBC);
                MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
                MApp_ZUI_ACT_ShutdownOSD();
                stGenSetting.stMiscSetting.bRunInstallationGuide = FALSE;
                _enReturnMenuItem = STATE_RETUNR_INSTALL_GUIDE;
                MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);
                _enTargetInstallState = STATE_INSTALL_INIT;
            #else
                MApp_ZUI_ACT_Set_InstallGuidePage(PAGE_INSTALL_TUNING_COUNTRY);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_INSTALL_MAIN_PAGE);
                MApp_ZUI_API_SetFocus(HWND_INSTALL_MAIN_PAGE_GRID);
            #endif
            }
            else if( MApp_ZUI_ACT_Get_InstallGuidePage() == PAGE_INSTALL_TUNING_COUNTRY )
            {
                stGenSetting.stMiscSetting.bRunInstallationGuide = FALSE;
                #if  ENABLE_SBTVD_BRAZIL_APP
                //fixed first scan LCN error,show 3.32
                _eTempCountry = OSD_COUNTRY_BRAZIL;
                #endif
                //from case MIA_START_SCAN
                MApp_SetOSDCountrySetting(_eTempCountry, TRUE);
                u8ScanAtvChNum = 0;
#if ENABLE_SBTVD_BRAZIL_APP
                u8ScanCATVChNum = 0;
                u8ScanAirTVChNum = 0;
#endif
                u16ScanDtvChNum=0;
                u16ScanRadioChNum=0;
#if NORDIG_FUNC //for Nordig Spec v2.0
                u16ScanDataChNum=0;
#endif
                u8ScanPercentageNum=0;

#if  ENABLE_SBTVD_BRAZIL_APP
                    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);

                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
                   #if ENABLE_SBTVD_BRAZIL_APP
                       enLastWatchAntennaType = ANTENNA_DTV_TYPE;
                      MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE , MAIN_WINDOW );
                   #else
                       MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                   #endif
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
#else
                mvideo_vd_set_videosystem(SIG_PAL); //dealut value for DVB
                //MApp_UiMenuFunc_A_StartAutoScanFunction();
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                //ST_VIDEO.eAspectRatio = EN_AspectRatio_16X9; //[SQE-195]Set ARC 16:9 Auto Scanning state
                MApp_Scaler_Setting_SetVDScale(EN_AspectRatio_16X9, MAIN_WINDOW);
#endif
                stGenSetting.stScanMenuSetting.u8ScanType=SCAN_TYPE_AUTO;

                MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
                _enTargetInstallState = STATE_INSTALL_GOTO_SCAN;
            }
            return TRUE;


        ///adjust functions//////////////////////

        case EN_EXE_DEC_TEMP_COUNTRY:
        case EN_EXE_INC_TEMP_COUNTRY:
            //from case MAPP_UIMENUFUNC_ADJUSTE2COUNTRY:
            _eTempCountry =(EN_OSD_COUNTRY_SETTING) MApp_ZUI_ACT_DecIncValue_Cycle(
                act==EN_EXE_INC_TEMP_COUNTRY,
                _eTempCountry, OSD_COUNTRY_AUSTRALIA, OSD_COUNTRY_NUMS-1, 1);
            //MApp_ZUI_API_InvalidateWindow(HWND_INSTALL_MAIN_COUNTRY_OPTION);
            return TRUE;

    }
    return FALSE;
}

extern U16 _MApp_ZUI_ACT_GetLanguageStringID(EN_LANGUAGE lang, BOOLEAN bDefaultEnglish);

LPTSTR MApp_ZUI_ACT_GetInstallGuideDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

        if (MApp_ZUI_API_IsSuccessor(HWND_INSTALL_MAIN_PAGE_GRID, hwnd))
            return MApp_ZUI_CTL_GridGetDynamicText(HWND_INSTALL_MAIN_PAGE_GRID, hwnd);

        switch(hwnd)
        {
            case HWND_INSTALL_MAIN_TITLE:
                if( MApp_ZUI_ACT_Get_InstallGuidePage() == PAGE_INSTALL_OSD_LANGUAGE )
                {
                    //u16TempID=en_str_Language;
                    u16TempID=en_str_Please_select_an_OSD_Language;
                }
                else
                    u16TempID=en_str_Country;
                break;
            default:
                u16TempID = Empty;
                break;
        }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}
void MApp_ZUI_ACT_SetTuningCountryByOSDLanguage( void )
{

    switch( MApp_ZUI_ACT_Install_GetOsdLanguageIndex() )
    {
        case LANGUAGE_CZECH:
            _eTempCountry = OSD_COUNTRY_CZECH;
            break;
        case LANGUAGE_DANISH:
            _eTempCountry = OSD_COUNTRY_DENMARK;
            break;
        case LANGUAGE_GERMAN:
            _eTempCountry = OSD_COUNTRY_GERMANY;
            break;
        case LANGUAGE_ENGLISH:
            _eTempCountry = OSD_COUNTRY_UK;
            break;
    	case LANGUAGE_IRISH:
        	_eTempCountry = OSD_COUNTRY_IRELAND;
        	break;
        case LANGUAGE_SPANISH:
            _eTempCountry = OSD_COUNTRY_SPAIN;
            break;
        case LANGUAGE_GREEK:
            _eTempCountry = OSD_COUNTRY_GREECE;
            break;
        case LANGUAGE_FRENCH:
            _eTempCountry = OSD_COUNTRY_FRANCE;
            break;
        case LANGUAGE_CROATIAN:
            _eTempCountry = OSD_COUNTRY_CROATIA;
            break;
        case LANGUAGE_ITALIAN:
            _eTempCountry = OSD_COUNTRY_ITALY;
            break;
        case LANGUAGE_HUNGARIAN:
            _eTempCountry = OSD_COUNTRY_HUNGARY;
            break;
        case LANGUAGE_DUTCH:
            _eTempCountry = OSD_COUNTRY_NETHERLANDS;
            break;
        case LANGUAGE_NORWEGIAN:
            _eTempCountry = OSD_COUNTRY_NORWAY;
            break;
        case LANGUAGE_POLISH:
            _eTempCountry = OSD_COUNTRY_POLAND;
            break;
        case LANGUAGE_PORTUGUESE:
            _eTempCountry = OSD_COUNTRY_PORTUGAL;
            break;
        case LANGUAGE_RUSSIAN:
            _eTempCountry = OSD_COUNTRY_RUSSIA;
            break;
        case LANGUAGE_ROMANIAN:
            _eTempCountry = OSD_COUNTRY_RUMANIA;
            break;
        case LANGUAGE_SLOVENIAN:
            _eTempCountry = OSD_COUNTRY_SLOVENIA;
            break;
        case LANGUAGE_SERBIAN:
            _eTempCountry = OSD_COUNTRY_SERBIA;
        break;
        case LANGUAGE_FINNISH:
            _eTempCountry = OSD_COUNTRY_FINLAND;
        break;
        case LANGUAGE_SWEDISH:
            _eTempCountry = OSD_COUNTRY_SWEDEN;
        break;
        case LANGUAGE_BULGARIAN:
            _eTempCountry = OSD_COUNTRY_BULGARIA;
        break;
        case LANGUAGE_SLOVAK:
            _eTempCountry = OSD_COUNTRY_SLOVENIA;
        break;

#if (ENABLE_DVB_TAIWAN_APP)
        case LANGUAGE_CHINESE:
            _eTempCountry = OSD_COUNTRY_TAIWAN;
        break;
#elif (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP||CHINESE_SIMP_FONT_ENABLE ||CHINESE_BIG5_FONT_ENABLE)
        case LANGUAGE_CHINESE:
            _eTempCountry = OSD_COUNTRY_CHINA;
        break;
#endif
        case LANGUAGE_NETHERLANDS:
            _eTempCountry = OSD_COUNTRY_NETHERLANDS;
        break;

        default:
            _eTempCountry = OSD_COUNTRY_UK;
        break;
    }

    return;
}

#if 0 //use "auto close" control
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_InstallGuideRootWinProc
///  [install guide application customization] checking page key timeout
///
///  @param [in]       hwnd HWND     window handle we are processing
///  @param [in]       msg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_ACT_InstallGuideRootWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            //setting AP timeout, auto close
            MApp_ZUI_API_SetTimer(hwnd, 0, APPLEVEL_MENU_TIME_OUT);
            break;

        case MSG_TIMER:
            {
                //if the time is up, kill the timer and then close AP!
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_ACT_ExecuteInstallGuideAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            break;


    }

    return DEFAULTWINPROC(hwnd, msg);
}
#endif

#endif

#undef MAPP_ZUI_ACTINSTALL_ATSC_C

