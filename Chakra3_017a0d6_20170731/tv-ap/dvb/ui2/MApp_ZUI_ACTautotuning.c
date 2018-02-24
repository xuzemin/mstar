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

#define MAPP_ZUI_ACTAUTOTUNING_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include <string.h>
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_Scan.h"
#include "MApp_ATV_Scan.h"
#include "MApp_Scan.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmainpage.h"

#include "MApp_TopStateMachine.h"
#include "MApp_GlobalFunction.h"
#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "msAPI_Tuning.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_FreqTableDTV.h"
#include "MApp_SaveData.h"
#include "msAPI_FreqTableATV.h"
#if(ENABLE_S2)

#include "MApp_ZUI_ACTDishSetup.h"
#include "apiDTVSatTable.h"

#include "Utl.h"
/////////////////////////////////////////////////////////////////////

extern MS_SAT_PARAM sat_info;
extern DTVPROGRAMID_M TPSInfo;
extern EN_SCAN_STATE enScanState;
#endif
#if (ENABLE_OAD)
#include "MApp_OAD.h"
#endif
#include "msAPI_DTVSystem.h"

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

/////////////////////////////////////////////////////////////////////
/*#if(ENABLE_S2)
extern U16                u8RFCh;
#else
extern U8                u8RFCh;
#endif*/
extern EN_OSD_TUNE_TYPE_SETTING eTuneType;
//extern EN_INSTALL_STATE enAutoTuningState;

#if( ENABLE_DTV )
extern MS_TP_SETTING stTPSetting;
#endif

#if ENABLE_TARGET_REGION
extern MW_DVB_TARGET_REGION_INFO* pInfo;
U8 u8TargetRegionCountryIdx = 0;
U16 u16PrimaryRegionInx = 0;
U16 u16SecondaryRegionInx = 0;
U16 u16TeritaryRegionInx = 0;
#endif

#if ENABLE_SBTVD_SCAN
extern BOOLEAN g_IskAutoScanFromCable;
#endif

#if (ENABLE_LCN_CONFLICT)
extern WORD wLcnConflictNumber;
extern BOOLEAN bManualDoWithLcn;
extern WORD     wStartChannelNum;
#endif
static EN_SCAN_STATE _enTargetAutoTuningDTVScanState;
static EN_ATV_SCAN_STATE _enTargetAutoTuningATVScanState;
#if ENABLE_FAVORITE_NETWORK
void    MApp_ZUI_ACT_AutoTune_Favorite_Network_Index_Control(U16 act);
void    MApp_ZUI_ACT_AutoTune_Favorite_Network_Set(void);
U8 msAPI_CM_Norwegian_Network_Total_Num_Get(void);
U8 msAPI_CM_Norwegian_Network_Next_Num_Get(U8 u8Idx);
U8 msAPI_CM_Norwegian_Network_Prev_Num_Get(U8 u8Idx);
#endif
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
//extern void _MApp_ZUI_API_DrawDynamicComponent(DRAWCOMPONENT component, const void * param, const GRAPHIC_DC * pdc, const RECT * rect);

#if ENABLE_DVB
extern U8 MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(MEMBER_COUNTRY eCountry);
#endif

static void _MApp_ZUI_ACT_Exit_SavingMsg(void)
{
    MApp_ATV_Scan_State_Init();
    MApp_Scan_State_Init();
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_MAIN_BG_ROTATE, E_ZUI_STATE_TERMINATE);
    MApp_ZUI_API_KillTimer(HWND_TUNE_SCAN_RESULT_MSG, 0);

    if (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN)
    {
        _enTargetAutoTuningATVScanState = STATE_ATV_SCAN_END;
        MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);

    }
    else
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_MENU);
        _enTargetAutoTuningDTVScanState = STATE_SCAN_END;
    }
}


void MApp_ZUI_ACT_AppShowAutoTuning(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_AUTO_TUNING;

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
        ZUI_AUTO_TUNING_XSTART, ZUI_AUTO_TUNING_YSTART,
        ZUI_AUTO_TUNING_WIDTH, ZUI_AUTO_TUNING_HEIGHT);

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
#if (ENABLE_OAD) //wait to do
    if(bShowOadScanPage == TRUE)
    {
        MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE_BG_PANE,SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE_SCAN_PROGRESS_PANE,SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_OAD_TUNE_SCAN_PROGRESS_BAR);
    }
    else
#endif
    {
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
  #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
  #endif
#if(ENABLE_S2)
    if(IsS2InUse())
    {
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_ITEM, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_TEXT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_COLON, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_COUNT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_PROG, SW_HIDE);
    }
#endif

#if (ENABLE_DTV == 0)
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DTV_TEXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DTV_COLON, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DTV_COUNT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DTV_PROG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_RADIO_TEXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_RADIO_COLON, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_RADIO_COUNT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_RADIO_PROG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
#endif

#if ENABLE_SBTVD_SCAN
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
    }
    else
#endif
    {
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
    }

#if (NORDIG_FUNC == 0) //for Nordig Spec v2.0
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
#endif

    printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __FUNCTION__);
    MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);

#if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
    MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
#endif

#if(ENABLE_S2)
    if(IsS2InUse()/*SateliteSearchsate == TRUE*/)
    {
        MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
        MApp_ZUI_API_SetFocus(HWND_SAT_SCAN_PROGRESS_BAR);
    }
    else
    {
        MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
        MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
    }
#else
    MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
    MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
#endif
    }

    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_SHOWUP, E_ZUI_STATE_RUNNING);

}


//////////////////////////////////////////////////////////

void MApp_ZUI_ACT_TerminateAutoTuning(void)
{
    ZUI_MSG(printf("[]term:auto_tune\n"));

    //MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_SHOW);

}

BOOLEAN MApp_ZUI_ACT_ExecuteAutoTuningAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_REPAINT_AUTOTUNING_PROGRESS:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_TUNE_SCAN_PROGRESS_PANE);
            return TRUE;

        case EN_EXE_AUTO_SCAN_FINISH:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
        #if(CHAKRA3_AUTO_TEST)
            MApp_AT_SendEvent(E_AT_EVENT_ATV_AUTO_SCAN_FINISH, NULL);
          #if(ENABLE_DTV)
            MApp_AT_SendEvent(E_AT_EVENT_DTV_AUTO_SCAN_FINISH, NULL);
          #endif
        #endif
            return TRUE;

        case EN_EXE_SCAN_CONFIRM_BTN_YES:

            if( MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN
             #if ENABLE_SBTVD_ATV_SYSTEM
             || MApp_TopStateMachine_GetTopState() == STATE_TOP_CATV_SCAN
             #endif
            )
            {
                MApp_ATV_ExitATVScanPause2Menu();
            }
            else
            {
            #if(ENABLE_SBTVD_DTV_SYSTEM)
                if( msAPI_SRC_IS_SBTVD_InUse() )
                {
                    MApp_DTV_ExitScanPause2Menu();
                }
                else
            #endif
                {
                    MApp_DTV_ExitScanPause2End();
                }
            }

            return TRUE;

        case EN_EXE_SCAN_CONFIRM_BTN_NO:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
          #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
          #endif
        #if(ENABLE_S2)
            if(IsS2InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_ATV_PROG, SW_HIDE);
            }
        #endif
            #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
            #endif
          #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
            }
            else
          #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
            }

             #if (NORDIG_FUNC == 0) //for Nordig Spec v2.0
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
          #endif
#if (ENABLE_DTV == 0)
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DTV_ITEM, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_RADIO_ITEM, SW_HIDE);
#endif
            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);

            MApp_ATV_ExitATVScanPauseState();
            MApp_DTV_ExitScanPauseState();
            MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
            MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
        #if(ENABLE_S2)
            if(IsS2InUse()/*SateliteSearchsate == TRUE*/)
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_SAT_SCAN_PROGRESS_BAR);
            }
            else
        #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }
            return TRUE;

        case EN_EXE_SKIP_ATV_SCAN_CONFIRM_BTN_YES:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
          #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
          #endif
            #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
            #endif
          #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
            }
            else
          #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
            }

             #if (NORDIG_FUNC == 0) //for Nordig Spec v2.0
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
          #endif
            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
            MApp_ATV_ExitATVScanPause2ScanEnd();
            MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
            MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
        #if(ENABLE_S2)
            if(IsS2InUse()/*SateliteSearchsate == TRUE*/)
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_SAT_SCAN_PROGRESS_BAR);
            }
            else
        #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }
            return TRUE;

        case EN_EXE_SKIP_ATV_SCAN_CONFIRM_BTN_NO:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
          #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
          #endif
          #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
          #endif

          #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
            }
            else
          #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
            }

          #if (NORDIG_FUNC == 0) //for Nordig Spec v2.0
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
          #endif

            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);

            MApp_ATV_ExitATVScanPauseState();
            MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
            MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);

        #if(ENABLE_S2)
            if(IsS2InUse()/*SateliteSearchsate == TRUE*/)
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_SAT_SCAN_PROGRESS_BAR);
            }
            else
        #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }
            return TRUE;

        case EN_EXE_SKIP_DTV_SCAN_CONFIRM_BTN_YES:
         #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
              #if(UI_SKIN_SEL == UI_SKIN_1366X768X565 )
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
              #endif
              #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
                MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,      SW_HIDE);
              #endif
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
                MApp_DTV_ExitScanPause2End();
                MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }
            else
         #endif
            {
                #if (NORDIG_FUNC == 0) //for Nordig Spec v2.0
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
              #endif
              #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
                MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,      SW_HIDE);
              #endif
                MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
                MApp_DTV_ExitScanPause2End();
            }

            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
            return TRUE;

        case EN_EXE_SKIP_DTV_SCAN_CONFIRM_BTN_NO:
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
          #if(UI_SKIN_SEL == UI_SKIN_1366X768X565 )
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
          #endif
          #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,      SW_HIDE);
          #endif

          #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
            }
            else
          #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
            }

          #if (NORDIG_FUNC == 0) //for Nordig Spec v2.0
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
          #endif
            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);

            MApp_DTV_ExitScanPauseState();
            MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
            MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
        #if(ENABLE_S2)
            if(IsS2InUse()/*SateliteSearchsate == TRUE*/)
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_SetFocus(HWND_SAT_SCAN_PROGRESS_BAR);
            }
            else
        #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }
            return TRUE;


    #if ENABLE_SBTVD_SCAN
        case EN_EXE_SKIP_CATV_SCAN_CONFIRM_BTN_NO:
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
              #if(UI_SKIN_SEL == UI_SKIN_1366X768X565 )
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
              #endif
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);

              #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
                MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,      SW_HIDE);
              #endif
                MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);

                MApp_ATV_ExitATVScanPauseState();
                MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            #if(ENABLE_S2)
                if(IsS2InUse()/*SateliteSearchsate == TRUE*/)
                {
                    MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_SAT_SCAN_PROGRESS_BAR);
                }
                else
            #endif
                {
                    MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_INFO_ITEM, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
                }
               return TRUE;
            }
            break;

        case EN_EXE_SKIP_CATV_SCAN_CONFIRM_BTN_YES:
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ATV_ExitATVScanPause2ScanEnd();
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
              #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
                MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,      SW_HIDE);
              #endif
                return TRUE;
            }
            break;
    #endif


        case EN_EXE_OPEN_SCAN_SKIP_MENU:
            if (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN )
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_HELP_MSG);
            }
        #if ENABLE_SBTVD_ATV_SYSTEM
            else if (MApp_TopStateMachine_GetTopState() == STATE_TOP_CATV_SCAN )
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_TITLE_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_BG_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
                #if 1//(ENABLE_FAVORITE_NETWORK)//because increase favorite network item into autotuning page,so when show autotuing we neen hide it now
                MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,   SW_HIDE);
                #endif
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_CONFIRM_HELP_MSG);
            }
        #endif
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_HELP_MSG);
            }
            return TRUE;

        case EN_EXE_OPEN_SCAN_EXIT_MENU:
            MApp_ZUI_API_ShowWindow(HWND_TUNE_TITLE_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_CONFIRM_HELP_MSG);
            return TRUE;

          #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
            case EN_EXE_SET_ASTRA_CHANNEL_ID:
            {
                U8 u8ListIdCount;
                MApp_ZUI_API_ShowWindow(HWND_TUNE_TITLE_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_BG_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_SHOW);
                u8ListIdCount = msAPI_CM_GetServiceListIdCount();
                if(u8ListIdCount<4)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM3,SW_HIDE);
                }
                if(u8ListIdCount<3)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM2,SW_HIDE);
                }
                if(u8ListIdCount<2)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM1,SW_HIDE);
                }
                switch(msAPI_CM_GetDefaultFocusWithServListID())
                {
                    case 1:
                    MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM1);
                    break;
                    case 2:
                    MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM2);
                    break;
                    case 3:
                    MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM3);
                    break;
                    default:
                    MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_ID_SET_LIST_ITEM0);
                    break;
                }
            }
            return TRUE;

            case EN_EXE_SET_ASTRA_CHANNEL_ID_SELECT:
            {
                U32 _u32FocusHwnd = MApp_ZUI_API_GetFocus();
                U8 _u8FocusIndex = 0;
                if ((_u32FocusHwnd >= HWND_MENU_CHANNEL_ID_SET_LIST_ITEM0)
                    && (_u32FocusHwnd <= HWND_MENU_CHANNEL_ID_SET_LIST_ITEM3))
                {
                    _u8FocusIndex = (_u32FocusHwnd - HWND_MENU_CHANNEL_ID_SET_LIST_ITEM0)/2;
                }
#if(ASTRA_LCN_ENABLE)
                msAPI_CM_UpdateLCNByChannellistId(msAPI_CM_GetServiceListIDwithIndex(_u8FocusIndex));
#elif(ASTRA_HD_ENABLE)
                msAPI_CM_SetServiceListFocusIndex(_u8FocusIndex);
                stGenSetting.g_SysSetting.u8ServiceListID = (U8)msAPI_CM_GetAvailableServiceListID();
                MApp_ZUI_ACT_ShutdownOSD();
                MApp_ZUI_ACT_StartupOSD(E_OSD_AUTO_TUNING);
#endif
                MApp_DTV_ExitScanPauseState();
                MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_PANE);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }


            case EN_EXE_SET_ASTRA_LCNCONFICT:
            {
                //stGenSetting.g_SysSetting.u8ServiceListID = (U8)msAPI_CM_GetAvailableServiceListID();
                //MApp_ZUI_ACT_ShutdownOSD();
                //MApp_ZUI_ACT_StartupOSD(E_OSD_AUTO_TUNING);
                MApp_DTV_ExitScanPauseState();
                MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }

            case EN_EXE_ASTRAHD_LCN_CONFILICT_CONFIRM_BTN_YES:
            case EN_EXE_ASTRAHD_LCN_CONFILICT_CONFIRM_BTN_NO:
            {
                MApp_ZUI_ACT_ShutdownOSD();
                MApp_ZUI_ACT_StartupOSD(E_OSD_AUTO_TUNING);
                MApp_DTV_ExitScanPauseState();
                MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
                return TRUE;
            }
        #endif  //  (ASTRA_HD_ENABLE)

    #if ENABLE_TARGET_REGION
        case EN_EXE_SET_TARGET_REGION:
            MApp_ZUI_API_ShowWindow(HWND_TUNE_TITLE_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_SET_TARGET_REGION_COUNTRY_CODE);
            return TRUE;

        case EN_EXE_SET_TARGET_REGION_SELECT:
            if (MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_TERITARY)
            {
                U8 CountryCode[3]={0,0,0};
                U8 u8PrimaryCode=0,u8SecondaryCode=0;
                U16 u16TertiaryCode=0;
                if (pInfo->pCountryInfo)
                {
                    memcpy(CountryCode,pInfo->pCountryInfo[u8TargetRegionCountryIdx].au8CountryCode,3);
                    if(pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo)
                    {
                        u8PrimaryCode=pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].u8Code;
                        if(pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo)
                        {
                            u8SecondaryCode=pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].u8Code;
                            if(pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].pTertiaryRegionInfo)
                            {
                                u16TertiaryCode=pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].pTertiaryRegionInfo[u16TeritaryRegionInx].u16Code;
                            }
                        }
                    }
                }

            #if(ENABLE_DVB)
                if((OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA)
#if(ENABLE_COUNTRY_SINGAPORE)
                 ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE)
#endif
#if (ENABLE_COUNTRY_GHANA)
                 ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_GHANA)
#endif
                    )
                {
                    msAPI_CM_UpdateLCDV2((U8*)CountryCode, u8PrimaryCode);
                }
                else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_UK)
                {
                    MApp_SI_SetTargetRegion((U8*)CountryCode, u8PrimaryCode, u8SecondaryCode, u16TertiaryCode);
                }
            #endif

                u8TargetRegionCountryIdx = 0;
                u16PrimaryRegionInx = 0;
                u16SecondaryRegionInx = 0;
                u16TeritaryRegionInx = 0;

                MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
              #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
              #endif
                MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE, SW_HIDE);
            #if (ENABLE_S2)
                MApp_ZUI_API_ShowWindow(HWND_SAT_SCAN_PROGRESS_INFO_ITEM, SW_HIDE);
            #endif
            #if ENABLE_SBTVD_SCAN
                if(msAPI_SRC_IS_SBTVD_InUse())
                {
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_TEXT, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COLON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_COUNT, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_DATA_PROG, SW_HIDE);
                }
                else
            #endif
                {
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_TEXT, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COLON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_COUNT, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_CATV_PROG, SW_HIDE);
                }

                MApp_DTV_ExitScanPauseState();
                MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
                MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
            }
            else if (MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_COUNTRY_CODE)
                MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_SET_TARGET_REGION_PRIMARY);
            else if (MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_PRIMARY)
                MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_SET_TARGET_REGION_SECONDARY);
            else
                MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_SET_TARGET_REGION_TERITARY);

            return TRUE;

        case EN_EXE_SET_TARGET_REGION_LEFT:
        case EN_EXE_SET_TARGET_REGION_RIGHT:
            if(pInfo != NULL)
            {
                if (MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_COUNTRY_CODE)
                {
                    if (pInfo->u8CountryNum >0)
                    {
                        u8TargetRegionCountryIdx = (U8)MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_SET_TARGET_REGION_RIGHT, (U16)u8TargetRegionCountryIdx, 0, (U16)(pInfo->u8CountryNum-1), 1);
                    }
                }
                else if (MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_PRIMARY)
                {
                    if (pInfo->pCountryInfo != NULL
                        && pInfo->pCountryInfo[u8TargetRegionCountryIdx].u16PrimaryRegionNum >0)
                    {
                        u16PrimaryRegionInx=MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_SET_TARGET_REGION_RIGHT, u16PrimaryRegionInx, 0, pInfo->pCountryInfo[u8TargetRegionCountryIdx].u16PrimaryRegionNum-1, 1);
                    }
                }
                else if(MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_SECONDARY)
                {
                     if (pInfo->pCountryInfo != NULL
                         && pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo != NULL
                         && pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].u16SecondaryRegionNum >0)
                    {
                        u16SecondaryRegionInx=MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_SET_TARGET_REGION_RIGHT, u16SecondaryRegionInx, 0,
                        pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].u16SecondaryRegionNum-1, 1);
                    }

                }
                else if(MApp_ZUI_API_GetFocus() == HWND_MENU_CHANNEL_SET_TARGET_REGION_TERITARY)
                {
                     if (pInfo->pCountryInfo != NULL
                        && pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo != NULL
                        && pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo != NULL
                        && pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].u16TertiaryRegionNum >0)
                    {
                        u16TeritaryRegionInx=MApp_ZUI_ACT_DecIncValue(
                        act==EN_EXE_SET_TARGET_REGION_RIGHT, u16TeritaryRegionInx, 0,
                        pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].u16TertiaryRegionNum-1, 1);
                    }

                }
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE);
            return TRUE;

    #endif

    #if (ENABLE_LCN_CONFLICT)
        case EN_EXE_SET_LCN_CONFLICT:
            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_TITLE_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_HELP_MSG);
            return TRUE;

        case EN_EXE_LCN_CONFILCT_CONFIRM_BTN_YES:
        case EN_EXE_LCN_CONFLICT_EXIT_SCAN_PAUSE:
            bManualDoWithLcn = FALSE;
#if(ASTRA_HD_ENABLE)
            if(GetASTRA_HD_ENABLE())
            {
    			msAPI_CM_SetAdd2ListSelectNOState(FALSE);
            }
#endif
            MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
          #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
          #endif
            MApp_DTV_ExitScanPauseState();
            MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
            MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);

            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);

            return TRUE;

        case EN_EXE_LCN_CONFILCT_CONFIRM_BTN_NO:
#if(ASTRA_HD_ENABLE)
            if(GetASTRA_HD_ENABLE())
            {
    		    msAPI_CM_SetAdd2ListSelectNOState(TRUE);
            }
#endif

            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_SHOW);

            MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_LCN_CONFLIC_1ST);
            return TRUE;

        case EN_EXE_LCN_CONFLICT_SELECT_CM:
            wStartChannelNum = wLcnConflictNumber + 1;
            #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
            msAPI_CM_SetSelectService(g_ucLcnConflict[(MApp_ZUI_API_GetFocus()-HWND_MENU_CHANNEL_LCN_CONFLIC_1ST)/2].dwLcnConflictPosition);
            #endif
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE);
            MApp_DTV_ExitScanPause2End();
            return TRUE;

        case EN_EXE_LCN_REFREASH_LCN_CONFILCT_MENU:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE);
            MApp_ZUI_API_SetFocus(HWND_MENU_CHANNEL_LCN_CONFLIC_1ST);
            return TRUE;
    #endif

    #if ENABLE_FAVORITE_NETWORK
        case EN_EXE_SET_FAVORITE_NETWORK:

             MApp_ZUI_API_ShowWindow(HWND_TUNE_TITLE_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_BG_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_PROGRESS_PANE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE,     SW_SHOW);
             MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_SEL_OPTION,SW_SHOW);
             MApp_ZUI_API_SetFocus(HWND_FAVORITE_NETWORK_SEL_BAR);
             return TRUE;

        case EN_EXE_SET_FAVORITE_NETWORK_LEFT:
        case EN_EXE_SET_FAVORITE_NETWORK_RIGHT:
             MApp_ZUI_ACT_AutoTune_Favorite_Network_Index_Control(act);
             return TRUE;

        case EN_EXE_SET_FAVORITE_NETWORK_SELECT:
             MApp_ZUI_ACT_AutoTune_Favorite_Network_Set();
             MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
           #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
           #endif
             MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE, SW_HIDE);
             MApp_DTV_ExitScanPauseState();
             return TRUE;

        case EN_EXE_FAVORITE_NETWORK_EXIT_SCAN_PAUSE:
             printf("\r\n EN_EXE_FAVORITE_NETWORK_EXIT_SCAN_PAUSE\n");
             MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_LCN_CONFLIC_PAGE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_SET_TARGET_REGION_PAGE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_TUNE_SCAN_RESULT_MSG, SW_HIDE);
           #if(UI_SKIN_SEL == UI_SKIN_1366X768X565)
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_MSG, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_ID_SET_PAGE, SW_HIDE);
           #endif
             MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE, SW_HIDE);
             MApp_ZUI_API_ShowWindow(HWND_FAVORITE_NETWORK_PAGE, SW_HIDE);
             MApp_DTV_ExitScanPauseState();
             MApp_ZUI_API_InvalidateWindow(HWND_TUNE_SCAN_PROGRESS_BAR);
             MApp_ZUI_API_SetFocus(HWND_TUNE_SCAN_PROGRESS_BAR);
             return TRUE;
    #endif

    #if (ENABLE_OAD) //TODO
        case EN_EXE_EXIT_OAD_SCAN:
        {
            bShowOadScanPage = FALSE;
            EN_OAD_SCAN_STATE state = STATE_OAD_SCAN_END;
            MApp_OAD_SetScanState(state);
            //_enReturnMenuItem = STATE_RETURN_AUTO_TUNING;

           return TRUE;
        }


        case EN_EXE_REPAINT_OAD_SCAN:
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_OAD_TUNE_SCAN_PROGRESS_PANE);
            MApp_ZUI_API_SetFocus(HWND_OAD_TUNE_SCAN_PROGRESS_BAR);
            return TRUE;
    #endif
    }

    return FALSE;
}


// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleAutoTuningKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    switch(key)
    {
        case VK_POWER:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            if (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN)
            {
                _enTargetAutoTuningATVScanState = STATE_ATV_SCAN_GOTO_STANDBY;
            }
            else
            {
                _enTargetAutoTuningDTVScanState = STATE_SCAN_GOTO_STANDBY;
            }
            return TRUE;
        default:
            return FALSE;
    }
    return FALSE;
}

static U16 _MApp_ZUI_ACT_AutoTuningGetPercentValue(void)
{
    U8 u8TempValue=0;
    EN_TOP_STATE TopState;

    TopState = MApp_TopStateMachine_GetTopState();

#if( ENABLE_ISDBT )
    if( msAPI_SRC_IS_SBTVD_InUse() )
    {
        if(TopState == STATE_TOP_DTV_SCAN)
        {
            u8TempValue= (u8ScanPercentageNum)/4 ;

            return  (U16)u8TempValue;
        }
        else if (TopState == STATE_TOP_ATV_SCAN)
        {
            u8TempValue = msAPI_Tuner_GetTuningProcessPercent();
            u8TempValue = (u8TempValue/4) + 25;
            return (U16)u8TempValue;
        }
        else if (TopState == STATE_TOP_CATV_SCAN)
        {
            u8TempValue = msAPI_Tuner_GetTuningProcessPercent();

            if( !g_IskAutoScanFromCable )
            {
                u8TempValue = (u8TempValue/2) + 50;
            }
            else
            {
                u8TempValue = u8TempValue;
            }

            return (U16)u8TempValue;
        }
    }
    else
#endif
    {
      #if ENABLE_DVB
        if (TopState == STATE_TOP_DTV_SCAN)
        {
            if(eTuneType == OSD_TUNE_TYPE_DTV_PLUS_ATV)
                u8TempValue= (u8ScanPercentageNum)/2 + 50;
            else
                u8TempValue= u8ScanPercentageNum;
            return  (U16)u8TempValue;
        }
        else
      #endif
        if (TopState == STATE_TOP_ATV_SCAN)
        {
            u8TempValue = msAPI_Tuner_GetTuningProcessPercent();
            if (eTuneType == OSD_TUNE_TYPE_DTV_PLUS_ATV)
            {
                //draw 50%
                u8TempValue = u8TempValue/2;
            }
            return (U16)u8TempValue;
        }
    }


    return 0;
}

#if(ENABLE_S2)
static U16 S2_MApp_ZUI_ACT_AutoTuningGetPercentValue(void)
{
    U8 u8TempValue=0;
       u8TempValue= u8ScanPercentageNum;
    return  (U16)u8TempValue;
}
extern MS_U8 u8CurrentEditSATId;
extern  BOOLEAN _GetSatInforByID(MS_U8 u8SATId,MS_SAT_PARAM *pSATParam);
#endif

LPTSTR MApp_ZUI_ACT_GetAutoTuningDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_TUNE_SCAN_PROGRESS_PERCENT:
          #if(ENABLE_S2)
            if(IsS2InUse())
                break;
          #endif
            return MApp_ZUI_API_GetU16String(_MApp_ZUI_ACT_AutoTuningGetPercentValue());

        case HWND_TUNE_SCAN_ATV_NUM:
        case HWND_TUNE_SCAN_PROGRESS_ATV_COUNT: //EN_DNUM_GetenA1_ScanATVNumber:
          #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                if(MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN )
                {
                    u8ScanAirTVChNum = msAPI_Tuner_GetNumberOfChBeFound_WhileAutoScan();
                }
                return MApp_ZUI_API_GetU16String(u8ScanAirTVChNum);
            }
            else
          #endif
            {
                return MApp_ZUI_API_GetU16String(u8ScanAtvChNum);
            }

        case HWND_TUNE_SCAN_DTV_NUM:
        case HWND_TUNE_SCAN_PROGRESS_DTV_COUNT: //EN_DNUM_GetenA1_ScanDTVNumber:
            return MApp_ZUI_API_GetU16String(u16ScanDtvChNum);

        case HWND_TUNE_SCAN_RADIO_NUM:
        case HWND_TUNE_SCAN_PROGRESS_RADIO_COUNT: //EN_DNUM_GetenA1_ScanRadeoNumber:
            return MApp_ZUI_API_GetU16String(u16ScanRadioChNum);

    #if ENABLE_SBTVD_ATV_SYSTEM
        case HWND_TUNE_SCAN_CATV_NUM:
        case HWND_TUNE_SCAN_PROGRESS_CATV_COUNT: //EN_DNUM_GetenA1_ScanATVNumber:
            if(MApp_TopStateMachine_GetTopState() == STATE_TOP_CATV_SCAN )
            {
                u8ScanCATVChNum = msAPI_Tuner_GetNumberOfChBeFound_WhileAutoScan();
            }
            return MApp_ZUI_API_GetU16String(u8ScanCATVChNum);
    #endif

    #if ENABLE_TARGET_REGION
        case HWND_MENU_CHANNEL_SET_TARGET_REGION_COUNTRY_CODE_OPTION:
            if(pInfo != NULL)
            {

                U8 u8_idx=0;
                LPTSTR str = CHAR_BUFFER;
                str[0] = 0;
                if(pInfo->pCountryInfo== NULL)
                    break;

                str[u8_idx++]=(U16)(pInfo->pCountryInfo[u8TargetRegionCountryIdx].au8CountryCode[0]);
                str[u8_idx++]=(U16)(pInfo->pCountryInfo[u8TargetRegionCountryIdx].au8CountryCode[1]);
                str[u8_idx++]=(U16)(pInfo->pCountryInfo[u8TargetRegionCountryIdx].au8CountryCode[2]);
                str[u8_idx++]=0;

                return CHAR_BUFFER;
            }
            break;
        case HWND_MENU_CHANNEL_SET_TARGET_REGION_PRIMARY_OPTION:
            if(pInfo->pCountryInfo== NULL)
                break;

            if (pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo != NULL)
            {


                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].name,
                    strlen((const char *)pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].name));
            }
            break;
        case HWND_MENU_CHANNEL_SET_TARGET_REGION_SECONDARY_OPTION:
            if(pInfo->pCountryInfo== NULL)
                break;
            if(pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo== NULL)
                break;

            if (pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo != NULL)
            {
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].name,
                    strlen((const char *)pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].name));
            }
            break;
        case HWND_MENU_CHANNEL_SET_TARGET_REGION_TERITARY_OPTION:
            if(pInfo->pCountryInfo== NULL)
                break;
            if(pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo== NULL)
                break;
            if(pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo == NULL)
                break;

            if (pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].pTertiaryRegionInfo != NULL)
            {
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].pTertiaryRegionInfo[u16TeritaryRegionInx].name,
                    strlen((const char *)pInfo->pCountryInfo[u8TargetRegionCountryIdx].pPrimaryRegionInfo[u16PrimaryRegionInx].pSecondaryRegionInfo[u16SecondaryRegionInx].pTertiaryRegionInfo[u16TeritaryRegionInx].name));
            }
            break;
    #endif // #if ENABLE_TARGET_REGION


    #if (ENABLE_OAD) //TODO
        case HWND_OAD_TUNE_SCAN_PROGRESS_PERCENT:
             return MApp_ZUI_API_GetU16String(u8OADpercentage);
        case HWND_OAD_TUNE_SCAN_PROGRESS_CH_UHF:
            return MApp_OAD_GetOadRfChannel();
    #endif


    #if NORDIG_FUNC //for Nordig Spec v2.0
        case HWND_TUNE_SCAN_DATA_NUM:
        case HWND_TUNE_SCAN_PROGRESS_DATA_COUNT: //EN_DNUM_GetenA1_ScanRadeoNumber:
            return MApp_ZUI_API_GetU16String(u16ScanDataChNum);
    #endif

        case HWND_TUNE_SCAN_PROGRESS_CH_TYPE:
        {
        #if ENABLE_DVB
            U8 u8_idx=0;
            LPTSTR str = CHAR_BUFFER;
            str[0] = 0;

            if (MApp_TopStateMachine_GetTopState()==STATE_TOP_DTV_SCAN)
            {
                //u16TempID = en_strA2_ManualScan_DTV;
                str[u8_idx++]='(';
                str[u8_idx++]='D';
                str[u8_idx++]='T';
                str[u8_idx++]='V';
                str[u8_idx++]=')';
                str[u8_idx++]=0;
                return CHAR_BUFFER;
            }

          #if ENABLE_SBTVD_ATV_SYSTEM
            else if(MApp_TopStateMachine_GetTopState()==STATE_TOP_CATV_SCAN)
            {
                str[u8_idx++]='(';
                str[u8_idx++]='C';
                str[u8_idx++]='A';
                str[u8_idx++]='T';
                str[u8_idx++]='V';
                str[u8_idx++]=')';
                str[u8_idx++]=0;
                return CHAR_BUFFER;
            }
          #endif
            else
        #endif
            {
                u16TempID = en_str_bracketsTV;
            }
        }
        break;

        case HWND_TUNE_SCAN_PROGRESS_CH_UHF:
          #if(ENABLE_S2)
            if(IsS2InUse())
                break;
          #endif
        {
            //case UHFCH_TEXT:
            U8 u8_idx;
            LPTSTR str = CHAR_BUFFER;
            str[0] = 0;
            u8_idx = 0;
            //show VHF/UHF
            //MIN_UHF_PHYSICAL_CHANNEL_NUMBER == 21 MAX_UHF_PHYSICAL_CHANNEL_NUMBER==69
            if(IsDTVInUse())//&& (_MApp_ZUI_ACT_AutoTuningGetPercentValue() != 0) )
            {
                MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

                MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);

            #if ENABLE_DVBC
                if( IsDVBCInUse() )
                {
                    str[u8_idx++]=CHAR_F;
                    str[u8_idx++]=CHAR_r;
                    str[u8_idx++]=CHAR_e;
                    str[u8_idx++]=CHAR_q;
                    str[u8_idx++]=0;
                }
                else
            #endif
                {
                  #if ENABLE_DVB
                    U8 u8MinUHF = MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(msAPI_CM_GetCountry());

                    if ( ((u8MinUHF <= pstScanMenuSetting->u8RFChannelNumber)
                       &&(MApp_TopStateMachine_GetTopState() != STATE_TOP_DTV_SCAN)
                        )
                       ||( (u8MinUHF <= MApp_Scan_Get_CurRFChannel())
                       &&(MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_SCAN)
                       ))
                    {
                        str[u8_idx++]=CHAR_U;
                        str[u8_idx++]=CHAR_H;
                        str[u8_idx++]=CHAR_F;
                    }
                    else
                    {
                        str[u8_idx++]=CHAR_V;
                        str[u8_idx++]=CHAR_H;
                        str[u8_idx++]=CHAR_F;
                    }
                    str[u8_idx++]=CHAR_SPACE;
                    str[u8_idx++]=CHAR_SPACE;
                    str[u8_idx++]=CHAR_C;
                    str[u8_idx++]=CHAR_H;
                    str[u8_idx++]=0;
                  #endif
                }
            }
            else
            {
                str[0]=0;
            }

            return CHAR_BUFFER;
        }
        break;

        case HWND_TUNE_SCAN_PROGRESS_ATV_FREQ:
          #if(ENABLE_S2)
            if(IsS2InUse())
            {
                break;
            }
          #endif

            if (IsATVInUse())
            {
                // Show Freqency
                WORD wTunerPLL,wTunerPLLI,wTunerPLLF;
                wTunerPLL = msAPI_Tuner_GetCurrentChannelPLL2UiStr();
                wTunerPLLI = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wTunerPLL);
                wTunerPLLF = msAPI_CFT_ConvertPLLtoFractionOfFrequency(wTunerPLL);

                CHAR_BUFFER[0] = ((wTunerPLLI/100) == 0) ? ' ' : '0'+(wTunerPLLI/100);
                CHAR_BUFFER[1] = '0'+((wTunerPLLI%100)/10);
                CHAR_BUFFER[2] = '0'+(wTunerPLLI%10);
                CHAR_BUFFER[3] = '.';
                CHAR_BUFFER[4] = '0'+(wTunerPLLF/100);
                CHAR_BUFFER[5] = '0'+((wTunerPLLF%100)/10);
                CHAR_BUFFER[6] = CHAR_SPACE;
                CHAR_BUFFER[7] = CHAR_M;
                CHAR_BUFFER[8] = CHAR_H;
                CHAR_BUFFER[9] = CHAR_z;
                CHAR_BUFFER[10] = 0;
                return CHAR_BUFFER;
            }
            else
            {
                CHAR_BUFFER[0]=0;
                return CHAR_BUFFER;
            }
        break;


        case HWND_TUNE_SCAN_PROGRESS_CH_NAME:
          #if(ENABLE_S2)
            if(IsS2InUse())
            {
                break;
            }
          #endif

            // case AUTO_SCAN_DTV_RF_NAME_TEXT:
        #if ENABLE_DVB //ENABLE_DTV
            if (IsDTVInUse())
            {
                U8 RFChannelName[4];
                U8 u8_idx;
                LPTSTR str = CHAR_BUFFER;
                str[0] = 0;
                u8_idx = 0;

                if(MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_SCAN)
                {
                #if ENABLE_DVBC
                    if( IsDVBCInUse() )
                    {
                    #if !ENABLE_SCAN_ONELINE_MSG
                        printf("tTPSetting.u32Frequency = %ld\n", stTPSetting.u32Frequency);
                    #endif
                        U32 tmp_integer = stTPSetting.u32Frequency / 1000;
                        U32 tmp_fraction = stTPSetting.u32Frequency % 1000;

                        str[u8_idx++] = ((tmp_integer/100) == 0) ? ' ' : '0'+(tmp_integer/100);
                        str[u8_idx++] = '0'+((tmp_integer%100)/10);
                        str[u8_idx++] = '0'+(tmp_integer%10);
                        str[u8_idx++] = '.';
                        str[u8_idx++] = '0'+(tmp_fraction/100);
                        str[u8_idx++] = 0;
                    }
                    else
                #endif
                    { // DVBT/DTMB
                    #if ENABLE_DTMB_ADD_FREQUENCY // DTMB
                        if(MApp_Scan_Get_CurRFChannel() <= 24)
                        {
                          if(TRUE == msAPI_DFT_GetPhysicalChannelName(MApp_Scan_Get_CurRFChannel(),RFChannelName,4))
                          {
                              str[u8_idx++] = (U16)RFChannelName[0];
                              str[u8_idx++] = (U16)RFChannelName[1];
                              str[u8_idx++] = (U16)RFChannelName[2];
                              str[u8_idx++] = (U16)RFChannelName[3];
                              str[u8_idx++] = 0;
                          }
                        }
                        else if(MApp_Scan_Get_CurRFChannel() >= 30)
                        {
                            if(TRUE == msAPI_DFT_GetPhysicalChannelName((MApp_Scan_Get_CurRFChannel() - 5),RFChannelName,4))
                            {
                              str[u8_idx++] = (U16)RFChannelName[0];
                              str[u8_idx++] = (U16)RFChannelName[1];
                              str[u8_idx++] = (U16)RFChannelName[2];
                              str[u8_idx++] = (U16)RFChannelName[3];
                              str[u8_idx++] = 0;
                            }
                        }
                        else
                        {
                            str[u8_idx++] = 2 + '0';
                            str[u8_idx++] = 4 + '0';
                            str[u8_idx++] = CHAR_PLUS;
                            str[u8_idx++] = (MApp_Scan_Get_CurRFChannel() - 24) + '0';
                            str[u8_idx++] = 0;
                        }
                    #else
                        // DVBT
                        if(TRUE == msAPI_DFT_GetPhysicalChannelName(MApp_Scan_Get_CurRFChannel(), RFChannelName,4))
                        {
                            str[u8_idx++] = (U16)RFChannelName[0];
                            str[u8_idx++] = (U16)RFChannelName[1];
                            str[u8_idx++] = (U16)RFChannelName[2];
                            str[u8_idx++] = (U16)RFChannelName[3];
                            str[u8_idx++] = 0;
                        }
                    #endif
                    }
                 }
                 return CHAR_BUFFER;
            }
            else
        #endif
            {
                CHAR_BUFFER[0]=0;
                return CHAR_BUFFER;
            }
        break;


    #if (ENABLE_OAD) //wait to do
        case HWND_OAD_TUNE_SCAN_PROGRESS_CH_TYPE:
        {
            CHAR_BUFFER[0] = CHAR_C;
            CHAR_BUFFER[1] = CHAR_H;
            CHAR_BUFFER[2] = 0;
            return CHAR_BUFFER;
        }
        break;
    #endif

        case HWND_TUNE_SCAN_CONFIRM_HELP_MSG:
        {
            u16TempID=en_str_Do_you_want_to_exit_tuning;
        }
        break;

        case HWND_TUNE_SCAN_SKIP_ATV_CONFIRM_HELP_MSG:
        {
            u16TempID=en_str_Do_you_want_to_skip_ATV_tuning;
        }
        break;

        case HWND_TUNE_SCAN_SKIP_CATV_CONFIRM_HELP_MSG:
        {
            u16TempID=en_str_Do_you_want_to_skip_CATV_tuning;
        }
        break;

        case HWND_TUNE_SCAN_SKIP_DTV_CONFIRM_HELP_MSG:
        {
            u16TempID=en_str_Do_you_want_to_skip_DTV_tuning;
        }
        break;


    #if(ENABLE_LCN_CONFLICT)
        case HWND_MENU_CHANNEL_HAVE_LCN_CONFILICT_HELP_MSG:
        {
            u16TempID=en_str_Conflicts_in_channel_numberingsemicolonPerform_an_automatic_resolution;
        }
        break;
        case HWND_MENU_CHANNEL_SET_LCN_CONFLIC_CH_NUM_VALUE:
        {
            return MApp_ZUI_API_GetU16String(wLcnConflictNumber);
        }
        break;

        case HWND_MENU_CHANNEL_SET_LCN_CONFLIC_1ST_NAME:
        {
            #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,g_ucLcnConflict[0].bLcnConflictChannelName,MAX_SERVICE_NAME);
            #endif
        }
        break;

        case HWND_MENU_CHANNEL_SET_LCN_CONFLIC_2ND_NAME:
        {
            #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,g_ucLcnConflict[1].bLcnConflictChannelName,MAX_SERVICE_NAME);
            #endif
        }
        break;

        case HWND_MENU_CHANNEL_SET_LCN_CONFLIC_3RD_NAME:
        {
            #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,g_ucLcnConflict[2].bLcnConflictChannelName,MAX_SERVICE_NAME);
            #endif
        }
        break;

        case HWND_MENU_CHANNEL_SET_LCN_CONFLIC_4TH_NAME:
        {
            #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,g_ucLcnConflict[3].bLcnConflictChannelName,MAX_SERVICE_NAME);
            #endif
        }
        break;

        case HWND_MENU_CHANNEL_SET_LCN_CONFLIC_5TH_NAME:
        {
            #if (UI_SKIN_SEL != UI_SKIN_960X540XI8)     //for fix complier error
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,g_ucLcnConflict[4].bLcnConflictChannelName,MAX_SERVICE_NAME);
            #endif
        }
        break;
    #endif


    #if ENABLE_FAVORITE_NETWORK
        case HWND_FAVORITE_NETWORK_SEL_OPTION:
        {
            U8 ucData[MAX_NETWORK_NAME];

            if (msAPI_CM_GetNetworkName(g_u8NetworkIndex,ucData))
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, ucData, MAX_NETWORK_NAME);

            return 0;
        }
    #endif


    #if(ENABLE_S2)
        case HWND_SAT_SCAN_PROGRESS_SAT_NAME:
            if(!IsS2InUse())
                break;
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)sat_info.aSatName , strlen((char *)(sat_info.aSatName)));
            return CHAR_BUFFER;

      #if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
        case HWND_MENU_CHANNEL_ID_SET_PAGE_TITLE_TEXT:
        {
            LPTSTR str = CHAR_BUFFER;
				*str++ = 'A';
				*str++ = 's';
				*str++ = 't';
				*str++ = 'r';
				*str++ = 'a';
				*str++ = ' ';
				*str++ = 'C';
                *str++ = 'h';
                *str++ = 'a';
                *str++ = 'n';
                *str++ = 'n';
                *str++ = 'e';
                *str++ = 'l';
				*str = 0;
				return CHAR_BUFFER;

        }
        return CHAR_BUFFER;

        case HWND_MENU_CHANNEL_ID_SET_LIST_ITEM0_TXT:
        {
            U8 str[MAX_SERVICE_LIST_NAME];

            memset(str,0,MAX_SERVICE_LIST_NAME);
            if (1 <= msAPI_CM_GetServiceListIdCount())
            {
                msAPI_CM_GetServiceListName(0,str);
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,MAX_SERVICE_LIST_NAME);
            }

        }
        return CHAR_BUFFER;

        case HWND_MENU_CHANNEL_ID_SET_LIST_ITEM1_TXT:
        {
            U8 str[MAX_SERVICE_LIST_NAME+5];

            memset(str,0,MAX_SERVICE_LIST_NAME);
            if (1 < msAPI_CM_GetServiceListIdCount())
            {
                msAPI_CM_GetServiceListName(1,str);
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,MAX_SERVICE_LIST_NAME);
            }
        }
        return CHAR_BUFFER;

        case HWND_MENU_CHANNEL_ID_SET_LIST_ITEM2_TXT:
        {
            U8 str[MAX_SERVICE_LIST_NAME];

            memset(str,0,MAX_SERVICE_LIST_NAME);
            if (2 < msAPI_CM_GetServiceListIdCount())
            {
                msAPI_CM_GetServiceListName(2,str);
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,MAX_SERVICE_LIST_NAME);
            }
        }
        return CHAR_BUFFER;

        case HWND_MENU_CHANNEL_ID_SET_LIST_ITEM3_TXT:
        {
            U8 str[MAX_SERVICE_LIST_NAME];

            memset(str,0,MAX_SERVICE_LIST_NAME);
            if (3 < msAPI_CM_GetServiceListIdCount())
            {
                msAPI_CM_GetServiceListName(3,str);
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str,MAX_SERVICE_LIST_NAME);
            }
        }
            return CHAR_BUFFER;

         case HWND_MENU_CHANNEL_ASTRAHD_LCN_CONFILICT_HELP_MSG:
         {
            //u16TempID=en_str_Detect_LCN_Conflict_Msg;
            break;
         }
    #endif

        case HWND_SAT_SCAN_PROGRESS_SEARCH_NUM:
            if(!IsS2InUse())
                break;

            if(S2_SCAN_TYPE_BLIND == g_enScanType)
            {
                if(enScanState < STATE_START)
                {
                    LPTSTR str = CHAR_BUFFER;
                    *str++ = 'W';
                    *str++ = 'a';
                    *str++ = 'i';
                    *str++ = 't';
                    *str++ = 'i';
                    *str++ = 'n';
                    *str++ = 'g';
                    *str = 0;
                    return CHAR_BUFFER;
                }
                else
                {
                    LPTSTR str = CHAR_BUFFER;
                    printf("\r\nosd.u32S2Frequency=%d",TPSInfo.u32S2Frequency);
                    __MApp_UlongToString( ( U32 )TPSInfo.u32S2Frequency, str, MApp_GetNoOfDigit( TPSInfo.u32S2Frequency ) );
                    str += MApp_ZUI_API_Strlen(str);
                    *str++ = CHAR_M;
                    *str++ = CHAR_H;
                    *str++ = CHAR_z;
                    *str = 0;
                    return CHAR_BUFFER;
                }
            }
            else
            {
                LPTSTR str = CHAR_BUFFER;
                printf("\r\nosd.u32S2Frequency=%d",TPSInfo.u32S2Frequency);
                __MApp_UlongToString( ( U32 )TPSInfo.u32S2Frequency, str, MApp_GetNoOfDigit( TPSInfo.u32S2Frequency ) );
                str += MApp_ZUI_API_Strlen(str);
                *str++ = CHAR_M;
                *str++ = CHAR_H;
                *str++ = CHAR_z;
                *str = 0;
                return CHAR_BUFFER;
            }
    #endif // #if(ENABLE_S2)
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return NULL; //for empty string
}

S16 MApp_ZUI_ACT_GetAutoTuningDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_TUNE_SCAN_PROGRESS_BAR: //case EN_DNUM_GetenA1_ScanPercentageValue:
          #if(ENABLE_S2)
            if(IsS2InUse())
                break;
          #endif

            return _MApp_ZUI_ACT_AutoTuningGetPercentValue();
        break;


    #if (ENABLE_OAD) //wait to do
        case HWND_OAD_TUNE_SCAN_PROGRESS_BAR:
        {
            return u8OADpercentage;
        }
        break;
    #endif

    #if(ENABLE_S2)
        case HWND_SAT_SCAN_PROGRESS_BAR:
            if(IsS2InUse())
            {
                return S2_MApp_ZUI_ACT_AutoTuningGetPercentValue();
            }
            break;
    #endif
    }

    return 0; //for empty  data
}



/////////////////////////////////////////////////////////
// Customize Window Procedures
S32 MApp_ZUI_ACT_AutoTuningSkipATVWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_TIMER:
            _MApp_ZUI_ACT_Exit_SavingMsg();
            break;

        default:
            break;

    }

    return DEFAULTWINPROC(hWnd, pMsg);
}


S32 MApp_ZUI_ACT_AutoTuningSkipDTVWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_TIMER:
            _MApp_ZUI_ACT_Exit_SavingMsg();
            break;

        default:
            break;
    }

    return DEFAULTWINPROC(hWnd, pMsg);
}

#if ENABLE_FAVORITE_NETWORK
U8 msAPI_CM_Norwegian_Network_Total_Num_Get(void)
{
    U8 k;
    U8 u8TotalNetWorkNum = 0;

    for (k=0;k<MAX_NETWOEK_NUMBER;k++)
    {
        if (msAPI_CM_IS_NorwegianNetwork(k))
            u8TotalNetWorkNum++;
    }

   return u8TotalNetWorkNum;
}

U8 msAPI_CM_Norwegian_Network_Next_Num_Get(U8 u8Idx)
{
    U8 k;
    U8 u8TotalNetWorkNum = 0;

    u8TotalNetWorkNum = msAPI_CM_Norwegian_Network_Total_Num_Get();

    if (u8TotalNetWorkNum == 0)
        return (INVALID_NETWORKINDEX);

    for (k=0;k<MAX_NETWOEK_NUMBER;k++)
    {
        u8Idx++;

        if (u8Idx>=MAX_NETWOEK_NUMBER)
            u8Idx = 0;

        if (msAPI_CM_IS_NorwegianNetwork(u8Idx))
            return (u8Idx);
     }

      return INVALID_NETWORKINDEX;
}

U8 msAPI_CM_Norwegian_Network_Prev_Num_Get(U8 u8Idx)
{
    U8 k;
    U8 u8TotalNetWorkNum = 0;

    u8TotalNetWorkNum = msAPI_CM_Norwegian_Network_Total_Num_Get();

    if (u8TotalNetWorkNum == 0)
        return (INVALID_NETWORKINDEX);


    for (k=0;k<MAX_NETWOEK_NUMBER;k++)
    {
        if (u8Idx == 0)
            u8Idx = MAX_NETWOEK_NUMBER-1;
        else
            u8Idx--;

        if (msAPI_CM_IS_NorwegianNetwork(u8Idx))
            return (u8Idx);
    }

   return INVALID_NETWORKINDEX;
}
void MApp_ZUI_ACT_AutoTune_Favorite_Network_Index_Control(U16 act)
{
    /*
    g_u8NetworkIndex = MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_SET_FAVORITE_NETWORK_RIGHT,
                               (U16)g_u8NetworkIndex, 0, g_u8NetworkTotal-1, 1);
    */
    if (act==EN_EXE_SET_FAVORITE_NETWORK_RIGHT)
        g_u8NetworkIndex = msAPI_CM_Norwegian_Network_Next_Num_Get(g_u8NetworkIndex);
    else
        g_u8NetworkIndex = msAPI_CM_Norwegian_Network_Prev_Num_Get(g_u8NetworkIndex);

     MApp_ZUI_API_InvalidateWindow(HWND_FAVORITE_NETWORK_SEL_BAR);
}

void MApp_ZUI_ACT_AutoTune_Favorite_Network_Set(void)
{
     g_u8NetworkTotal = 0;
#if (NTV_FUNCTION_ENABLE)
     msAPI_CM_Set_FavoriteNetwork(g_u8NetworkIndex);
#endif
     printf("\r\n <MApp_ZUI_ACT_TSB_AutoTune_Favorite_Network_Set = %d>",g_u8NetworkIndex);
}

#endif // #if ENABLE_FAVORITE_NETWORK






//******************************************************************************

#undef MAPP_ZUI_ACTAUTOTUNING_C

