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

#define MAPP_ZUI_ACTCADTVMANUALTUNING_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "MsCommon.h"
#include "Board.h"
#if ENABLE_DVBC
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_SignalMonitor.h"
#include "MApp_CADTV_ManualTuning_Main.h"
#include "MApp_CADTV_Proc.h"
#include "MApp_TV.h"
#include "MApp_InputSource.h"
#include "MApp_SaveData.h"
#include "MApp_Menu_Main.h"
#include "MApp_ZUI_ACTcadtvmanualtuning.h"
#include "MApp_Scan.h"
#include "MApp_ChannelChange.h"

/////////////////////////////////////////////////////////////////////

#define MANUAL_SCAN_MONITOR_DURATION 1000
#define CADTV_MANUAL_SCAN_END_TIME_OUT_MS 10000

extern void  MApp_ZUI_ACT_SetTargetMenuState(EN_MENU_STATE MenuState);
extern EN_OSD_TUNE_TYPE_SETTING eTuneType;
extern EN_CADTV_MANUALTUNING_STATE enCadtvManualTuningState;
static EN_CADTV_MANUALTUNING_STATE _enTargetCadtvManualTuningState;
static U8 u8ManualScan_StoreChannel_Value;
static U32 _u32CatvFreq;
static U16 _u16SRValue;
static U16 _u16NetworkID;
static U8  _u8DigitCount;

//#if ENABLE_T_C_COMBO
EN_OSD_DVBC_SCAN_TYPE eDVBScanType = OSD_DVBC_TYPE_FULL;
BOOL bIsDVBCScan = FALSE;
//#endif
//static BOOLEAN bManualScan_Skip_IsChange;

//*************************************************************************
//              Defines
//*************************************************************************

typedef enum
{
    CADTV_MANUAL_TUNING_COMMAND_INIT,
    CADTV_MANUAL_TUNING_COMMAND_UP,
    CADTV_MANUAL_TUNING_COMMAND_DOWN,
} EN_CADTV_MANUAL_TUNING_COMMAND_TYPE;

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

#define CADTV_MANUAL_SCAN_DELAY 200

/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define CATV_MANUAL_TUNING_DBINFO(y)    //y

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

static U16 _MApp_ZUI_ACT_CadtvManualTuningGetProgramNumber(void)
{
    //return ((U16)msAPI_ATV_GetCurrentProgramNumber());
    return 0;
}

S32 MApp_ZUI_ACT_CadtvManualTuningWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
        {
            MApp_ZUI_API_SetTimer(HWND_CATUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            MApp_ZUI_API_SetTimer(HWND_CATUNE_SIGNAL_BG, 1, MANUAL_SCAN_MONITOR_DURATION);

            break;
        }

        case MSG_TIMER:
        {
            switch(msg->wParam)
            {
                case 0:
                    MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_TXT, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_SEARCHING_TXT, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
                    if(g_LockStatus == FALSE)
                    {
                        MApp_ZUI_API_ShowWindow(hwnd, SW_SHOW);
                    }
                    else
                    {
                        MApp_ZUI_API_ShowWindow(hwnd, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_ENTERKEY_REMIND_TXT, SW_SHOW);
                    }
                    break;
                case 1:
                    MApp_ZUI_API_InvalidateWindow(hwnd);
                    break;
                default:
                    MApp_ZUI_API_InvalidateWindow(hwnd);
                    break;
            }

            break;
        }


        default:
            break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}

static void _MApp_ZUI_ACT_Change_TS_Setting(void)
{
    MS_TP_SETTING stTempTP;
    memset((void *)&stTempTP, 0x00, sizeof(MS_TP_SETTING));// fix coverity 207494

    if(IsDTVInUse())
    {
        //disable current channel & talbe monitor
        MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
        MApp_Dmx_DisableTableMonitor();
        MApp_Dmx_CloseAllFilters();

        stTempTP.u32Frequency = MApp_CadtvManualTuning_GetFrequency();
        //stTempTP.enBandWidth = E_RF_CH_BAND_8MHz;
        stTempTP.u32Symbol_rate = MApp_CadtvManualTuning_GetSymbol();
        stTempTP.u8Modulation = (U8)MApp_CadtvManualTuning_GetQamType();
        stTempTP.bAutoSRFlag = 0;
        stTempTP.bAutoQamFlag = 0;
        msAPI_Tuner_Tune2RfCh(&stTempTP);
    }
}

void MApp_ZUI_ACT_AppShowCadtvManualTuning(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_CADTV_MANUAL_TUNING;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    // clean digital key count and buffer
    MApp_Set_IdleDigitCount(0);
    MApp_Set_IdleInputValue(0);
    _u8DigitCount = 0;

    {
        MEMBER_SERVICETYPE bServiceType;
        DTVPROGRAMID_M stDPI;
        U8 u8PhNum=0;
        WORD wCurrentPosition;
        BYTE cRFChannelNumber;
        bServiceType = msAPI_CM_GetCurrentServiceType();
        wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
        cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
        u8PhNum = msAPI_CM_Get_RFChannelIndex(cRFChannelNumber);
        memset(&stDPI, 0, sizeof(stDPI));
        if(msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE))
        {
            MApp_CadtvManualTuning_SetFrequency(stDPI.u32Frequency);

            //MApp_CadtvManualTuning_SetSymbol(stDPI.u32SymbRate);
            MApp_CadtvManualTuning_SetSymbol(msAPI_CM_Get_IDTab_SymbolRate(&stDPI));

            MApp_CadtvManualTuning_SetQamType((EN_CAB_CONSTEL_TYPE)stDPI.QamMode);
        }
        _MApp_ZUI_ACT_Change_TS_Setting();
    }

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_CADTV_MANUAL_TUNING_XSTART, ZUI_CADTV_MANUAL_TUNING_YSTART,
        ZUI_CADTV_MANUAL_TUNING_WIDTH, ZUI_CADTV_MANUAL_TUNING_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

  #if 0//ENABLE_DVBC_PLUS_DTMB_CHINA_APP
    if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_DTV )
    {
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE , MAIN_WINDOW );
    }
  #else
    if( (UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_DVBC)
      ||(UI_PREV_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_DVBC) )
    {
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE , MAIN_WINDOW );
    }
  #endif

    u8ManualScan_StoreChannel_Value = _MApp_ZUI_ACT_CadtvManualTuningGetProgramNumber();

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);

//#if ENABLE_T_C_COMBO

    if(bIsDVBCScan == TRUE )
    {
        if(MApp_DVBC_SCAN_GetCurrentType() == OSD_DVBC_TYPE_FULL)
        {
            MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_FREQUENCY_BG, DISABLE);
            MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_NETWORKID_BG, DISABLE);
        }
        else
        {
            MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_FREQUENCY_BG, ENABLE);
            MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_NETWORKID_BG, ENABLE);
        }
        MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_DVB_SCAN_PAGE, SW_SHOW);
        MApp_ZUI_API_KillTimer(HWND_CATUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0);
        MApp_ZUI_API_SetFocus(HWND_DVBCSCAN_SCAN_TYPE_BG);
    }
    else
    {
        MApp_ZUI_API_ShowWindow(HWND_CATUNE_BG_PANE, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_CATUNE_PAGE_LIST, SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_CATUNE_BOTTOM_HALF_BG_L, SW_HIDE);
        MApp_ZUI_API_ShowWindow(HWND_CATUNE_BOTTOM_HALF_BG_R, SW_HIDE);
        MApp_ZUI_API_SetFocus(HWND_CATUNE_FREQUENCY);
    }
//#else
//    {
//        MApp_ZUI_API_ShowWindow(HWND_CATUNE_BG_PANE, SW_SHOW);
//        MApp_ZUI_API_ShowWindow(HWND_CATUNE_PAGE_LIST, SW_SHOW);
//        MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT, SW_HIDE);
 //       MApp_ZUI_API_ShowWindow(HWND_CATUNE_BOTTOM_HALF_BG_L, SW_HIDE);
 //       MApp_ZUI_API_ShowWindow(HWND_CATUNE_BOTTOM_HALF_BG_R, SW_HIDE);
  //      MApp_ZUI_API_SetFocus(HWND_CATUNE_FREQUENCY);
 //   }
//#endif
   MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_TXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_SEARCHING_TXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);

    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_SHOWUP, E_ZUI_STATE_RUNNING);
}

void MApp_ZUI_ACT_TerminateCadtvManualTuning(void)
{
    //printf("[]term:Catv manual tuning\n");
    enCadtvManualTuningState = _enTargetCadtvManualTuningState;
}

BOOLEAN MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetCadtvManualTuningState = STATE_CADTV_MANUALTUNING_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetCadtvManualTuningState = STATE_CADTV_MANUALTUNING_CLEAN_UP;
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetCadtvManualTuningState = STATE_CADTV_MANUALTUNING_GOTO_MAIN_MENU;

          #if ENABLE_T_C_COMBO
            if(bIsDVBCScan == TRUE)
            {
                _enReturnMenuItem = STATE_RETURN_CADTV_MANUAL_TUNING;
            }
          #endif
            return TRUE;


    #if ENABLE_T_C_COMBO
        case EN_EXE_GOTO_MAIN_DVBTYPE:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
           _enTargetCadtvManualTuningState = STATE_CADTV_MANUALTUNING_GOTO_MAIN_MENU;
           _enReturnMenuItem = STATE_RETURN_DVBC_SCAN_TUNING;
            return TRUE;
    #endif


        case EN_EXE_CADTV_CHANGE_FREQUENCY_LEFT:
            if(_u8DigitCount != 0)
            {
                MApp_CadtvManualTuning_SetFrequency(_u32CatvFreq);
                _u32CatvFreq = 0 ;
                _u8DigitCount = 0;
            }
            MApp_CadtvManualTuning_DecreaseFrequency();
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_InvalidateWindow(HWND_CATUNE_FREQUENCY_OPTION);
            return TRUE;

        case EN_EXE_CADTV_CHANGE_FREQUENCY_RIGHT:
            if(_u8DigitCount != 0)
            {
                MApp_CadtvManualTuning_SetFrequency(_u32CatvFreq);
                _u32CatvFreq = 0 ;
                _u8DigitCount = 0;
            }
            MApp_CadtvManualTuning_IncreaseFrequency();
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_InvalidateWindow(HWND_CATUNE_FREQUENCY_OPTION);
            return TRUE;
        case EN_EXE_CADTV_CHANGE_SYMBOL_LEFT:
            if(_u8DigitCount != 0)
            {
                MApp_CadtvManualTuning_SetSymbol(_u16SRValue);
                _u16SRValue = 0 ;
                _u8DigitCount = 0;
            }
            MApp_CadtvManualTuning_DecreaseSymbol();
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_InvalidateWindow(HWND_CATUNE_SYMBOL_OPTION);
            return TRUE;

        case EN_EXE_CADTV_CHANGE_SYMBOL_RIGHT:
            if(_u8DigitCount != 0)
            {
                MApp_CadtvManualTuning_SetSymbol(_u16SRValue);
                _u16SRValue = 0 ;
                _u8DigitCount = 0;
            }
            MApp_CadtvManualTuning_IncreaseSymbol();
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_InvalidateWindow(HWND_CATUNE_SYMBOL_OPTION);
            return TRUE;

        case EN_EXE_CADTV_CHANGE_QAMTYPE_LEFT:
            MApp_CadtvManualTuning_DecreaseQamType();
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_InvalidateWindow(HWND_CATUNE_QAM_TYPE_OPTION);
            return TRUE;

        case   EN_EXE_CADTV_CHANGE_QAMTYPE_RIGHT:
            MApp_CadtvManualTuning_IncreaseQamType();
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_InvalidateWindow(HWND_CATUNE_QAM_TYPE_OPTION);
            return TRUE;

        case   EN_EXE_CADTV_START_SEARCH:
            enCadtvManualTuningState = STATE_CADTV_MANUALTUNING_GOTO_CADTV_SCAN;
            u16ScanDtvChNum = 0;
            u16ScanRadioChNum = 0;
          #if NORDIG_FUNC //for Nordig Spec v2.0
            u16ScanDataChNum = 0;
          #endif

            {
                MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

                MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);
                pstScanMenuSetting->u8ScanType=SCAN_TYPE_MANUAL;
            }
            MApp_ZUI_API_KillTimer(HWND_CATUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0);
            MApp_ZUI_API_KillTimer(HWND_CATUNE_BG_PANE, 0);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_NO_SIGNAL_BTN, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_DTV_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_RADIO_TXT, SW_HIDE);
          #if NORDIG_FUNC //for Nordig Spec v2.0
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_DATA_TXT, SW_HIDE);
          #endif
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_TRANSPARENT_BG, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_SEARCHING_TXT, SW_SHOW);
            return TRUE;

         case EN_EXE_CADTV_MANUAL_SCAN_END:
          #if NORDIG_FUNC //for Nordig Spec v2.0
            if((!u16ScanDtvChNum)&&(!u16ScanRadioChNum)&&(!u16ScanDataChNum))
          #else
            if((!u16ScanDtvChNum)&&(!u16ScanRadioChNum))
          #endif
            {
                MApp_ZUI_API_SetTimer(HWND_CATUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            }
            MApp_ZUI_API_SetTimer(HWND_CATUNE_BG_PANE, 0, CADTV_MANUAL_SCAN_END_TIME_OUT_MS);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_SEARCHING_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_TXT, SW_SHOW);
            return TRUE;

        case EN_EXE_CADTV_NUM0:
        case EN_EXE_CADTV_NUM1:
        case EN_EXE_CADTV_NUM2:
        case EN_EXE_CADTV_NUM3:
        case EN_EXE_CADTV_NUM4:
        case EN_EXE_CADTV_NUM5:
        case EN_EXE_CADTV_NUM6:
        case EN_EXE_CADTV_NUM7:
        case EN_EXE_CADTV_NUM8:
        case EN_EXE_CADTV_NUM9:
        {
            if(MApp_ZUI_API_GetFocus() == HWND_CATUNE_FREQUENCY)
            {
                _u32CatvFreq = _u32CatvFreq * 10 + (act - EN_EXE_CADTV_NUM0);
                _u8DigitCount++;
                //range from 888 to 99
                if (_u8DigitCount == MApp_GetNoOfDigit(MAX_DVBC_FREQUENCY))
                {
                    MApp_CadtvManualTuning_SetFrequency(_u32CatvFreq);
                    _u32CatvFreq = 0 ;
                    _u8DigitCount = 0;
                }
                else if (_u32CatvFreq == 0)
                {
                    MApp_CadtvManualTuning_SetFrequency(_u32CatvFreq);
                    _u8DigitCount = 0;
                }

                MApp_ZUI_API_ShowWindow(HWND_CATUNE_FREQUENCY,SW_SHOW);
            }

            if(MApp_ZUI_API_GetFocus() == HWND_CATUNE_SYMBOL)
            {
                _u16SRValue = _u16SRValue * 10 + (act - EN_EXE_CADTV_NUM0);
                _u8DigitCount++;
                //range from 9999 to 9
                if (_u8DigitCount == MApp_GetNoOfDigit(MAX_DVBC_SYMBOL_RATE))
                {
                    MApp_CadtvManualTuning_SetSymbol(_u16SRValue);
                    _u16SRValue = 0 ;
                    _u8DigitCount = 0;
                }
                else if (_u16SRValue == 0)
                {
                    MApp_CadtvManualTuning_SetSymbol(_u16SRValue);
                    _u8DigitCount = 0;
                }
                MApp_ZUI_API_ShowWindow(HWND_CATUNE_SYMBOL,SW_SHOW);
            }
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SCAN_RESULT_TXT, SW_HIDE);
            MApp_ZUI_API_SetTimer(HWND_CATUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            return TRUE;
        }


        case EN_EXE_CADTV_CHANGE_FREQUENCY:
        {
            MApp_CadtvManualTuning_SetFrequency(_u32CatvFreq);
             _u32CatvFreq = 0 ;
             _u8DigitCount = 0;
             _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_FREQUENCY_OPTION,SW_SHOW);

            return TRUE;
        }


        case EN_EXE_CADTV_CHANGE_SYMBOL:
        {
            MApp_CadtvManualTuning_SetSymbol(_u16SRValue);
            _u16SRValue = 0 ;
            _u8DigitCount = 0;
            _MApp_ZUI_ACT_Change_TS_Setting();
            MApp_ZUI_API_ShowWindow(HWND_CATUNE_SYMBOL_OPTION,SW_SHOW);

            return TRUE;
        }


    #if ENABLE_T_C_COMBO
        case EN_EXE_DEC_DVBC_SCAN_TYPE:
        case EN_EXE_INC_DVBC_SCAN_TYPE:
            eDVBScanType = (EN_OSD_DVBC_SCAN_TYPE)MApp_ZUI_ACT_DecIncValue_Cycle(
            act==EN_EXE_INC_DVBC_SCAN_TYPE,
            eDVBScanType, OSD_DVBC_TYPE_FULL, OSD_DVBC_TYPE_NUMS-1, 1);

            if(eDVBScanType == OSD_DVBC_TYPE_FULL)
            {
                MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_FREQUENCY_BG, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_NETWORKID_BG, DISABLE);
                #if(!DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
                eTuneType = (EN_OSD_TUNE_TYPE_SETTING)OSD_TUNE_TYPE_DTV_PLUS_ATV;
                #endif
                g_enScanType = SCAN_TYPE_AUTO;
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_FREQUENCY_BG, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_DVBCSCAN_NETWORKID_BG, ENABLE);
                eTuneType = (EN_OSD_TUNE_TYPE_SETTING)OSD_TUNE_TYPE_DTV_ONLY;
                g_enScanType = SCAN_TYPE_NETWORK;
            }
            MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLG_DVBC_SCAN_TYPE_OPTION);
            return TRUE;
    #endif


        case EN_EXE_DVBC_SCAN_NUM0:
        case EN_EXE_DVBC_SCAN_NUM1:
        case EN_EXE_DVBC_SCAN_NUM2:
        case EN_EXE_DVBC_SCAN_NUM3:
        case EN_EXE_DVBC_SCAN_NUM4:
        case EN_EXE_DVBC_SCAN_NUM5:
        case EN_EXE_DVBC_SCAN_NUM6:
        case EN_EXE_DVBC_SCAN_NUM7:
        case EN_EXE_DVBC_SCAN_NUM8:
        case EN_EXE_DVBC_SCAN_NUM9:
            if((MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_FREQUENCY_BG) && (DVBCFreqScanType == 0))
            {
                _u32CatvFreq = _u32CatvFreq * 10 + (act - EN_EXE_DVBC_SCAN_NUM0);
                _u8DigitCount++;

                //range from 888 to 99
                if (_u8DigitCount == MApp_GetNoOfDigit(MAX_DVBC_FREQUENCY))
                {
                    MApp_CadtvManualTuning_SetFrequency(_u32CatvFreq);
                    _u32CatvFreq = 0 ;
                    _u8DigitCount = 0;
                }
                MApp_ZUI_API_ShowWindow(HWND_DVBCSCAN_FREQUENCY_BG,SW_SHOW);
            }

            if((MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_NETWORKID_BG) && (DVBCNetworkIdScanType == 0))
            {
                _u16NetworkID = _u16NetworkID * 10 + (act - EN_EXE_DVBC_SCAN_NUM0);
                _u8DigitCount++;
                //range from 888 to 99
                if (_u8DigitCount == MApp_GetNoOfDigit(DEFAULT_DVBC_NID))
                {
                    MApp_CadtvManualTuning_SetNID(_u16NetworkID);
                    _u16NetworkID = 0 ;
                    _u8DigitCount = 0;
                }
                MApp_ZUI_API_ShowWindow(HWND_DVBCSCAN_NETWORKID_BG,SW_SHOW);
            }

            if((MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_SYMBOL_RATE_BG) && (DVBCSymbolRateScanType == 0))
            {
                _u16SRValue = _u16SRValue * 10 + (act - EN_EXE_DVBC_SCAN_NUM0);
                _u8DigitCount++;
                //range from 0 ~ 65535
                if (_u8DigitCount == MApp_GetNoOfDigit(MAX_DVBC_SYMBOL_RATE))
                {
                    MApp_CadtvManualTuning_SetSymbol(_u16SRValue);
                    _u16SRValue = 0 ;
                    _u8DigitCount = 0;
                }
                MApp_ZUI_API_ShowWindow(HWND_DVBCSCAN_SYMBOL_RATE_BG,SW_SHOW);
            }
            _MApp_ZUI_ACT_Change_TS_Setting();
            return TRUE;


        case EN_EXE_CHANGE_DVBC_FREQ_TYPE:
            DVBCFreqScanType = (DVBCFreqScanType == 0) ? 1 : 0;
            MApp_ZUI_API_ShowWindow(HWND_DVBCSCAN_FREQUENCY_BG,SW_SHOW);
            return TRUE;

        case EN_EXE_CHANGE_DVBC_NID_TYPE:
            DVBCNetworkIdScanType = (DVBCNetworkIdScanType == 0) ? 1 : 0;
            MApp_ZUI_API_ShowWindow(HWND_DVBCSCAN_NETWORKID_BG,SW_SHOW);
            return TRUE;

        case EN_EXE_CHANGE_DVBC_SYMBOL_TYPE:
            DVBCSymbolRateScanType = (DVBCSymbolRateScanType == 0) ? 1 : 0;
            MApp_ZUI_API_ShowWindow(HWND_DVBCSCAN_SYMBOL_RATE_BG,SW_SHOW);
            return TRUE;

        default:
            break;
    }

    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_HandleCadtvManualTuningKey(VIRTUAL_KEY_CODE key)
{
    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_CATUNE_BG_PANE, 0);
    if((MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_NETWORKID_BG) && (DVBCFreqScanType == 0))
    {
        if (key < VK_NUM_0 || key > VK_NUM_9)
        {
            if((_u16NetworkID != 0) && (_u16NetworkID != 0xFFFF))
            {
                MApp_CadtvManualTuning_SetNID(_u16NetworkID);
            }
            _u16NetworkID = 0 ;
            _u8DigitCount = 0;
        }
    }
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
           // {VK_RED, HWND_CATUNE_BOTTOM_HALF_SAVE_BTN},
            //{VK_EXIT, HWND_CATUNE_BOTTOM_HALF_EXIT_BTN},
            {VK_UP, HWND_CATUNE_BOTTOM_HALF_UP_ARROW},
            {VK_DOWN, HWND_CATUNE_BOTTOM_HALF_DOWN_ARROW},
            {VK_LEFT, HWND_CATUNE_BOTTOM_HALF_LEFT_ARROW},
            {VK_RIGHT, HWND_CATUNE_BOTTOM_HALF_RIGHT_ARROW},
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
            MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(EN_EXE_POWEROFF);
            return TRUE;

        case VK_MENU:
          #if ENABLE_T_C_COMBO
            if(bIsDVBCScan == TRUE)
            {
                MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(EN_EXE_GOTO_MAIN_DVBTYPE);
            }
            else
            {
                MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(EN_EXE_GOTO_MAINMENU);
                _enReturnMenuItem = STATE_RETURN_CADTV_MANUAL_TUNING;
            }
          #else
            MApp_ZUI_ACT_ExecuteCadtvManualTuningAction(EN_EXE_GOTO_MAINMENU);
            _enReturnMenuItem = STATE_RETURN_CADTV_MANUAL_TUNING;
          #endif
            return TRUE;

        case VK_UP:
            _u16NetworkID = 0;
            _u16SRValue = 0;
            _u32CatvFreq = 0;
            _u8DigitCount =0 ;
            return FALSE;

        case VK_DOWN:
            _u16NetworkID = 0;
            _u16SRValue = 0;
            _u32CatvFreq = 0;
            _u8DigitCount =0 ;
            return FALSE;

        default:
            break;

    }
    return FALSE;
}


LPTSTR MApp_ZUI_ACT_GetCadtvManualTuningDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_CATUNE_FREQUENCY_OPTION:
            if(MApp_ZUI_API_GetFocus() == HWND_CATUNE_FREQUENCY && _u8DigitCount != 0)
            {
                MApp_UlongToU16String(_u32CatvFreq, CHAR_BUFFER, (S8)MApp_GetNoOfDigit(_u32CatvFreq));
                return CHAR_BUFFER;
            }
            else
            {
                MApp_UlongToU16String(MApp_CadtvManualTuning_GetFrequency(), CHAR_BUFFER, (S8)MApp_GetNoOfDigit(MApp_CadtvManualTuning_GetFrequency()));
                return CHAR_BUFFER;
            }

        case HWND_CATUNE_SYMBOL_OPTION:
            if(MApp_ZUI_API_GetFocus() == HWND_CATUNE_SYMBOL&& _u8DigitCount != 0)
            {
                return MApp_ZUI_API_GetU16String(_u16SRValue);
            }
            else
            {
                return MApp_ZUI_API_GetU16String(MApp_CadtvManualTuning_GetSymbol());
            }

        case HWND_CATUNE_QAM_TYPE_OPTION:
        {
            switch( MApp_CadtvManualTuning_GetQamType() )
            {
                case CAB_QAM16:
                    u16TempID = en_str_QAM_16;
                    break;
                case CAB_QAM32:
                    u16TempID = en_str_QAM_32;
                    break;
                case CAB_QAM64:
                    u16TempID = en_str_QAM_64;
                    break;
                case CAB_QAM128:
                    u16TempID = en_str_QAM_128;
                    break;
                case CAB_QAM256:
                    u16TempID = en_str_QAM_256;
                    break;
            }
            break;
        }

        case HWND_CATUNE_SCAN_RESULT_DTV_NUMBER_TXT:
            return MApp_ZUI_API_GetU16String(u16ScanDtvChNum);

        case HWND_CATUNE_SCAN_RESULT_RADIO_NUMBER_TXT:
            return MApp_ZUI_API_GetU16String(u16ScanRadioChNum);

    #if NORDIG_FUNC //for Nordig Spec v2.0
        case HWND_CATUNE_SCAN_RESULT_DATA_NUMBER_TXT:
            return MApp_ZUI_API_GetU16String(u16ScanDataChNum);
    #endif


    #if ENABLE_T_C_COMBO
        case HWND_MENU_DLG_DVBC_SCAN_TYPE_OPTION:
            switch(eDVBScanType)
            {
                case OSD_DVBC_TYPE_FULL:
                    u16TempID = en_str_Full;
                    break;
                case OSD_DVBC_TYPE_NETWOEKSCAN:
                    u16TempID = en_str_Network_Scan;
                    break;
                default :
                    u16TempID = en_str_Full;
                    break;
            }
            break;

        case HWND_MENU_DLG_DVBC_SCAN_FREQUENCY_OPTION:
            if (DVBCFreqScanType == 0)
            {
                if(MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_FREQUENCY_BG && _u8DigitCount != 0)
                {
                    MApp_UlongToU16String(_u32CatvFreq, CHAR_BUFFER, (S8)MApp_GetNoOfDigit(_u32CatvFreq));
                    return CHAR_BUFFER;
                }
                else
                {
                    MApp_UlongToU16String(MApp_CadtvManualTuning_GetFrequency(), CHAR_BUFFER, (S8)MApp_GetNoOfDigit(MApp_CadtvManualTuning_GetFrequency()));
                    return CHAR_BUFFER;
                }
            }
            else
                return MApp_ZUI_API_GetString(u16TempID = en_str_Auto);

        case HWND_MENU_DLG_DVBC_SCAN_NETWORKID_OPTION:
           if(DVBCNetworkIdScanType == 0)
           {
                if(MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_NETWORKID_BG&& _u8DigitCount != 0)
                    return MApp_ZUI_API_GetU16String(_u16NetworkID);
                else
                    return MApp_ZUI_API_GetU16String(MApp_CadtvManualTuning_GetNID());
            }
            else
                return MApp_ZUI_API_GetString(u16TempID = en_str_Auto);

        case HWND_MENU_DLG_DVBC_SCAN_SYMBOL_RATE_OPTION:
            if(DVBCSymbolRateScanType == 0)
            {
                if(MApp_ZUI_API_GetFocus() == HWND_DVBCSCAN_SYMBOL_RATE_BG&& _u8DigitCount != 0)
                   return MApp_ZUI_API_GetU16String(_u16SRValue);
                else
                    return MApp_ZUI_API_GetU16String(MApp_CadtvManualTuning_GetSymbol());
            }
            else
                return MApp_ZUI_API_GetString(u16TempID = en_str_Auto);
    #endif // #if ENABLE_T_C_COMBO

        default:
            break;
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

S16 MApp_ZUI_ACT_GetCADtvManualTuningDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_CATUNE_SIGNAL_BAR:
            //printf("g_CurSignalStrength = 0x%x\n", g_CurSignalStrength);
            return g_CurSignalStrength;
    }
    return 0; //for empty  data
}

//#if ENABLE_T_C_COMBO
EN_OSD_DVBC_SCAN_TYPE MApp_DVBC_SCAN_GetCurrentType(void)
{
    return eDVBScanType;
}
//#endif

GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryCadtvManualTuningStatus(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_CATUNE_FREQUENCY:
        case HWND_CATUNE_SYMBOL:
        case HWND_CATUNE_QAM_TYPE:
             return EN_DL_STATE_NORMAL;

        default:
            return EN_DL_STATE_NORMAL;
    }
}

#endif//#if ENABLE_CADTV




//******************************************************************************

#undef MAPP_ZUI_ACTCADTVMANUALTUNING_C

