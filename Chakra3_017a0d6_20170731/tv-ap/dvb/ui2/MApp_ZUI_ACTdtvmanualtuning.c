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

#define MAPP_ZUI_ACTDTVMANUALTUNING_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal
#include "Board.h"

#if (ENABLE_DVB || ENABLE_ATSC_SCAN_NEW_MODE)

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "datatype.h"
#include "MsCommon.h"
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
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_SignalMonitor.h"
#include "MApp_DTV_ManualTuning_Main.h"
#include "MApp_SaveData.h"
#include "msAPI_FreqTableDTV.h"
#include "msAPI_Timer.h"
#include "mapp_demux.h"
#include "MApp_ChannelChange.h"
#include "MApp_TopStateMachine.h"
#include "MApp_Menu_Main.h"
#include "MApp_TV.h"
#include "MApp_InputSource.h"

#include "MApp_Scan.h"


#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif
#include "MApp_ZUI_ACTdtvmanualtuning.h"
/////////////////////////////////////////////////////////////////////

#if ENABLE_SBTVD_SCAN
extern E_ANTENNA_SOURCE_TYPE enLastWatchAntennaType;
#endif
extern EN_DTV_MANUALTUNING_STATE enDtvManualTuningState;
/*#if ENABLE_S2
extern U16               u8RFCh;
#else
extern U8                u8RFCh;
#endif*/
static EN_DTV_MANUALTUNING_STATE _enTargetDtvManualTuningState;
extern U32 u32ManualScanMonitorSignalTimer;
extern BOOLEAN MApp_CharTable_GetServiceNameToUCS2(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD * bChannelName, U8 ControlCodes);
extern void MApp_ChannelChange_EnableChannel_ResetTunerAndDemod(BYTE cRFChannelNumber, MEMBER_SERVICETYPE bServiceType, WORD wCurrentPosition );

#if ENABLE_ATSC_SCAN_NEW_MODE
extern EN_SCAN_CHANNEL_TYPE enScanChannelType;
#endif
//*************************************************************************
//              Defines
//*************************************************************************
typedef enum
{
    DTV_MANUAL_TUNING_COMMAND_INIT,
    DTV_MANUAL_TUNING_COMMAND_UP,
    DTV_MANUAL_TUNING_COMMAND_DOWN,
} EN_DTV_MANUAL_TUNING_COMMAND_TYPE;

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define DTV_MANUAL_TUNING_DBINFO(y)    //y

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
#define MANUAL_SCAN_MONITOR_DURATION 1000

S32 MApp_ZUI_ACT_DtvManualTuningWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                MApp_ZUI_API_SetTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
                MApp_ZUI_API_SetTimer(HWND_DTUNE_SIGNAL_BG, 1, MANUAL_SCAN_MONITOR_DURATION);
            }
            break;

        case MSG_TIMER:
            {
                switch(msg->wParam)
                {
                    case 0:
                    #if !ENABLE_ATSC_SCAN_NEW_MODE
                        MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_TXT, SW_HIDE);
                    #endif
                        MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_SEARCHING_TXT, SW_HIDE);
                        MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
                        if(g_LockStatus == FALSE)
                        {
                            MApp_ZUI_API_ShowWindow(hwnd, SW_SHOW);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(hwnd, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_ENTERKEY_REMIND_TXT, SW_SHOW);
                        }
                        break;
                    case 1:
                        MApp_ZUI_API_InvalidateWindow(hwnd);
                        break;
                    default:
                        MApp_ZUI_API_InvalidateWindow(hwnd);
                        break;
                }
            }
            break;

        default:
            break;

    }
    return DEFAULTWINPROC(hwnd, msg);

}

#if !ENABLE_ATSC_SCAN_NEW_MODE
static void _MApp_ZUI_ACT_ChangeChannel(void)
{
    MS_TP_SETTING stTempTP;

    if(IsDTVInUse())
    {
        MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

        MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);
        //disable current channel & talbe monitor
        MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
        MApp_Dmx_DisableTableMonitor();
        MApp_Dmx_CloseAllFilters();

        // change FN
        if( msAPI_DFT_GetTSSetting(pstScanMenuSetting->u8RFChannelNumber, &stTempTP) == TRUE)
        {
        #if ENABLE_DVB_T2
            if(IsDVBTInUse())
            {
                MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);
                if(pstScanMenuSetting->u8RFChannelNumber != pstScanMenuSetting->u8PreRFChannelNumber)
                {
                    MAPP_DTV_Scan_T2_DoScan(DVB_T_DEMOD,FALSE);
                    u32ManualScanMonitorSignalTimer = msAPI_Timer_GetTime0();
                }
            }
        #endif
			if(msAPI_CM_GetCountry() == E_NORWAY)
			{
				msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(FALSE);
			}
            msAPI_Tuner_Tune2RfCh(&stTempTP);
        }
    }
}
#endif

BOOLEAN MApp_ZUI_ACT_ExecuteDtvManualTuningAction(U16 act)
{
    MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);

    switch(act)
    {
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetDtvManualTuningState = STATE_DTV_MANUALTUNING_GOTO_STANDBY;
            return TRUE;


        case EN_EXE_CLOSE_CURRENT_OSD:
        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);

            if(act == EN_EXE_CLOSE_CURRENT_OSD)
            {
                _enTargetDtvManualTuningState = STATE_DTV_MANUALTUNING_CLEAN_UP;
            }
            else
            {
                _enTargetDtvManualTuningState = STATE_DTV_MANUALTUNING_GOTO_MAIN_MENU;
            }

            pstScanMenuSetting->u8PreRFChannelNumber =  pstScanMenuSetting->u8RFChannelNumber;

            return TRUE;

        case EN_EXE_GET_PREV_CHANNEL:
        #if ENABLE_ATSC_SCAN_NEW_MODE
            if(ANT_TYPE == ANT_AIR)
            {
                stGenSetting.stScanMenuSetting.u8RFChannelNumber =
                    MApp_ZUI_ACT_DecIncValue_Cycle(
                        FALSE,  (U16)stGenSetting.stScanMenuSetting.u8RFChannelNumber, CHAN_AIR_MIN, CHAN_AIR_MAX, 1);
            }
            else
            {
                stGenSetting.stScanMenuSetting.u8RFChannelNumber =
                    MApp_ZUI_ACT_DecIncValue_Cycle(
                        FALSE,  (U16)stGenSetting.stScanMenuSetting.u8RFChannelNumber, CHAN_CATV_MIN, CHAN_CATV_MAX, 1);
            }
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_INIT;
            MApp_Set_IdleDigitCount(0);
            MApp_Set_IdleInputValue(0);
        #else
             pstScanMenuSetting->u8RFChannelNumber = msAPI_DFT_GetPrevPhysicalChannelNumber( pstScanMenuSetting->u8RFChannelNumber);
            if( INVALID_PHYSICAL_CHANNEL_NUMBER ==  pstScanMenuSetting->u8RFChannelNumber )
            {
                pstScanMenuSetting->u8RFChannelNumber = MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER();
            }
          #ifndef HISENSE_OSD_STYLE
            _MApp_ZUI_ACT_ChangeChannel();
          #endif
        #endif
            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_CHANNEL_NAME_TXT);
            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_UFH_TXT);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_TXT, SW_HIDE);
            MApp_ZUI_API_SetTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            return TRUE;
        case EN_EXE_GET_NEXT_CHANNEL:
        #if ENABLE_ATSC_SCAN_NEW_MODE
            if(ANT_TYPE == ANT_AIR)
            {
                stGenSetting.stScanMenuSetting.u8RFChannelNumber =
                    MApp_ZUI_ACT_DecIncValue_Cycle(
                        TRUE,  (U16)stGenSetting.stScanMenuSetting.u8RFChannelNumber, CHAN_AIR_MIN, CHAN_AIR_MAX, 1);
            }
            else
            {
                stGenSetting.stScanMenuSetting.u8RFChannelNumber =
                    MApp_ZUI_ACT_DecIncValue_Cycle(
                        TRUE,  (U16)stGenSetting.stScanMenuSetting.u8RFChannelNumber, CHAN_CATV_MIN, CHAN_CATV_MAX, 1);
            }
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_INIT;
            MApp_Set_IdleDigitCount(0);
            MApp_Set_IdleInputValue(0);
        #else
            pstScanMenuSetting->u8RFChannelNumber = msAPI_DFT_GetNextPhysicalChannelNumber(pstScanMenuSetting->u8RFChannelNumber);
            if( INVALID_PHYSICAL_CHANNEL_NUMBER == pstScanMenuSetting->u8RFChannelNumber )
            {
                pstScanMenuSetting->u8RFChannelNumber = msAPI_DFT_GetFirstPhysicalChannelNumber();
            }
          #ifndef HISENSE_OSD_STYLE
            _MApp_ZUI_ACT_ChangeChannel();
          #endif
        #endif

            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_CHANNEL_NAME_TXT);
            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_UFH_TXT);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_TXT, SW_HIDE);
            MApp_ZUI_API_SetTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            return TRUE;

    #if ENABLE_ATSC_SCAN_NEW_MODE
        case EN_EXE_SWITCH_PREV_SCAN_TYPE:
        case EN_EXE_SWITCH_NEXT_SCAN_TYPE:
            if(act == EN_EXE_SWITCH_NEXT_SCAN_TYPE)
            {
                if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_ATV)
                    MApp_Scan_ATSC_SetScanType(ATSC_SCAN_TYPE_AIR_DTV);
                else
                    MApp_Scan_ATSC_SetScanType((EN_ATSC_SCAN_TYPE)(MApp_Scan_ATSC_GetScanType()+1));
            }
            else
            {
                if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_DTV)
                    MApp_Scan_ATSC_SetScanType(ATSC_SCAN_TYPE_CABLE_ATV);
                else
                    MApp_Scan_ATSC_SetScanType((EN_ATSC_SCAN_TYPE)(MApp_Scan_ATSC_GetScanType()-1));
            }
            switch(MApp_Scan_ATSC_GetScanType())
            {
                default:
                case ATSC_SCAN_TYPE_AIR_DTV:
                    enScanChannelType = SCAN_DIGITAL_CHANNEL;
                    ANT_TYPE = ANT_AIR;
                    break;
                case ATSC_SCAN_TYPE_AIR_ATV:
                    enScanChannelType = SCAN_ANALOG_CHANNEL;
                    ANT_TYPE = ANT_AIR;
                    break;
                case ATSC_SCAN_TYPE_CABLE_DTV:
                    enScanChannelType = SCAN_DIGITAL_CHANNEL;
                    ANT_TYPE = ANT_CATV;
                    break;
                case ATSC_SCAN_TYPE_CABLE_ATV:
                    enScanChannelType = SCAN_ANALOG_CHANNEL;
                    ANT_TYPE = ANT_CATV;
                    break;
            }
            if(MApp_Get_IdleDigitCount() == 0)
            {
                if(ANT_TYPE == ANT_AIR)
                {
                    if(stGenSetting.stScanMenuSetting.u8RFChannelNumber < CHAN_AIR_MIN)
                        stGenSetting.stScanMenuSetting.u8RFChannelNumber = CHAN_AIR_MIN;
                    else if(stGenSetting.stScanMenuSetting.u8RFChannelNumber > CHAN_AIR_MAX)
                        stGenSetting.stScanMenuSetting.u8RFChannelNumber = CHAN_AIR_MAX;
                }
                else
                {
                    if(stGenSetting.stScanMenuSetting.u8RFChannelNumber < CHAN_CATV_MIN)
                        stGenSetting.stScanMenuSetting.u8RFChannelNumber = CHAN_CATV_MIN;
                    else if(stGenSetting.stScanMenuSetting.u8RFChannelNumber > CHAN_CATV_MAX)
                        stGenSetting.stScanMenuSetting.u8RFChannelNumber = CHAN_CATV_MAX;
                }
            }
            MApp_ChannelChange_ChangeProgramList ((EN_ANT_TYPE)ANT_TYPE);
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_INIT;
            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_CHANNEL_NAME_TXT);
            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_UFH_TXT);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_TXT, SW_HIDE);
            MApp_ZUI_API_SetTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            return TRUE;
    #endif

         case EN_EXE_MANUAL_SCAN_CHANGE_RF:
        #if ENABLE_ATSC_SCAN_NEW_MODE
            MApp_Set_IdleDigitCount(0);
            MApp_Set_IdleInputValue(0);
            MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_CHANNEL_NAME_TXT);
        #endif
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_GOTO_DTV_SCAN;
            u16ScanDtvChNum = 0;
            u16ScanRadioChNum = 0;
        #if NORDIG_FUNC //for Nordig Spec v2.0
            u16ScanDataChNum = 0;
        #endif

            pstScanMenuSetting->u8ScanType=SCAN_TYPE_MANUAL;
#if ENABLE_CI_PLUS
			stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = FALSE;  // clean flag
#endif
            MApp_ZUI_API_KillTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0);
            MApp_ZUI_API_KillTimer(HWND_DTUNE_BG_PANE, 0);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_DTV_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_RADIO_TXT, SW_HIDE);
#if NORDIG_FUNC //for Nordig Spec v2.0
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_DATA_TXT, SW_HIDE);
#endif
#if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_DATA_TXT, SW_HIDE);
            }
#endif
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_SEARCHING_TXT, SW_SHOW);
            return TRUE;

        case EN_EXE_DTV_MANUAL_SCAN_END:
#if NORDIG_FUNC //for Nordig Spec v2.0
            if((!u16ScanDtvChNum)&&(!u16ScanRadioChNum)&&(!u16ScanDataChNum))
#else
            if((!u16ScanDtvChNum)&&(!u16ScanRadioChNum))
#endif
            {
                MApp_ZUI_API_SetTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
            }
        #if !ENABLE_ATSC_SCAN_NEW_MODE
            MApp_ZUI_API_SetTimer(HWND_DTUNE_BG_PANE, 0, DTV_MANUAL_SCAN_END_TIME_OUT_MS);
        #endif
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_SEARCHING_TXT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
        #if ENABLE_ATSC_SCAN_NEW_MODE
            if(enScanChannelType == SCAN_DIGITAL_CHANNEL)
            {
                MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_DTV_TXT, SW_SHOW);
            }
        #else
            MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_TXT, SW_SHOW);
        #endif
        #if(CHAKRA3_AUTO_TEST)
            MApp_AT_SendEvent(E_AT_EVENT_DTV_MANUAL_SCAN_FINISH, NULL);
        #endif
            return TRUE;


    case EN_EXE_MANUAL_SCAN_NUMBERKEY_0:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_1:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_2:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_3:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_4:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_5:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_6:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_7:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_8:
    case EN_EXE_MANUAL_SCAN_NUMBERKEY_9:
        {
        #if ENABLE_ATSC_SCAN_NEW_MODE
            U8 u8TmpIdleDigitCount = MApp_Get_IdleDigitCount();
            U16 u16TmpIdleInputValue = MApp_Get_IdleInputValue();
            u16TmpIdleInputValue = u16TmpIdleInputValue * 10 + (act - EN_EXE_MANUAL_SCAN_NUMBERKEY_0);
            u8TmpIdleDigitCount++;
            if(u8TmpIdleDigitCount >= 3)
            {
                if(ANT_TYPE == ANT_AIR)
                {
                    if(u16TmpIdleInputValue < CHAN_AIR_MIN)
                        u16TmpIdleInputValue = CHAN_AIR_MIN;
                    else if(u16TmpIdleInputValue > CHAN_AIR_MAX)
                        u16TmpIdleInputValue = CHAN_AIR_MAX;
                }
                else if(ANT_TYPE == ANT_CATV)
                {
                    if(u16TmpIdleInputValue < CHAN_CATV_MIN)
                        u16TmpIdleInputValue = CHAN_CATV_MIN;
                    else if(u16TmpIdleInputValue > CHAN_CATV_MAX)
                        u16TmpIdleInputValue = CHAN_CATV_MAX;
                }
            }
            stGenSetting.stScanMenuSetting.u8RFChannelNumber = u16TmpIdleInputValue;
            if (u8TmpIdleDigitCount >= 3)
            {
                enDtvManualTuningState = STATE_DTV_MANUALTUNING_INIT;
                u8TmpIdleDigitCount = 0;
                u16TmpIdleInputValue = 0;
            }
            MApp_Set_IdleDigitCount(u8TmpIdleDigitCount);
            MApp_Set_IdleInputValue(u16TmpIdleInputValue);
        #else
            BOOLEAN eRes;
            MS_TP_SETTING stTPSetting;
            U8 u8TmpIdleDigitCount = MApp_Get_IdleDigitCount();
            U16 u16TmpIdleInputValue = MApp_Get_IdleInputValue();

            MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
            MApp_Dmx_DisableTableMonitor();

            u16ScanDtvChNum = 0;
            u16ScanRadioChNum = 0;
          #if NORDIG_FUNC //for Nordig Spec v2.0
            u16ScanDataChNum = 0;
          #endif
            u16TmpIdleInputValue = u16TmpIdleInputValue * 10 + (act - EN_EXE_MANUAL_SCAN_NUMBERKEY_0);
            u8TmpIdleDigitCount++;
            if (u8TmpIdleDigitCount >= 2)
            {
	   #if ENABLE_DTMB_ADD_FREQUENCY
            if(u16TmpIdleInputValue >= 25)
            {
                u16TmpIdleInputValue = u16TmpIdleInputValue + 5;
            }
          #endif


                eRes = msAPI_DFT_GetTSSetting((U8)u16TmpIdleInputValue, &stTPSetting);
                if ( eRes != TRUE )
                {
                    msAPI_Timer_Delayms(500);
                    u8TmpIdleDigitCount = 0;
                }
                else
                {
                    pstScanMenuSetting->u8RFChannelNumber = u16TmpIdleInputValue;
                }
                _MApp_ZUI_ACT_ChangeChannel();
                u8TmpIdleDigitCount = 0;
                u16TmpIdleInputValue = 0;
            }
            MApp_Set_IdleDigitCount(u8TmpIdleDigitCount);
            MApp_Set_IdleInputValue(u16TmpIdleInputValue);
        #endif
        }
        MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_CHANNEL_NAME_TXT);
        MApp_ZUI_API_InvalidateWindow(HWND_DTUNE_MANUAL_SCAN_UFH_TXT);
        MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_TXT, SW_HIDE);
        MApp_ZUI_API_SetTimer(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, 0, MANUAL_SCAN_MONITOR_DURATION);
        return TRUE;

    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateDtvManualTuning(void)
{
    ZUI_MSG(printf("[]term:dtv manual tuning\n"));
    enDtvManualTuningState = _enTargetDtvManualTuningState;
}

BOOLEAN MApp_ZUI_ACT_HandleDtvManualTuningKey(VIRTUAL_KEY_CODE key)
{
    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_DTUNE_BG_PANE, 0);

    switch(key)
    {
        case VK_EXIT:
			{
				MEMBER_SERVICETYPE bServiceType;
				WORD wCurrentPosition;
				bServiceType = msAPI_CM_GetCurrentServiceType();
				wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
	                    MApp_ZUI_ACT_ExecuteDtvManualTuningAction(EN_EXE_CLOSE_CURRENT_OSD);
                       #if !ENABLE_ATSC_SCAN_NEW_MODE
                           MApp_ChannelChange_EnableChannel_ResetTunerAndDemod(msAPI_SI_GetCurrentRF(), bServiceType, wCurrentPosition);
                       #endif
        	}
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_ExecuteDtvManualTuningAction(EN_EXE_POWEROFF);
            return TRUE;
        case VK_MENU:
            MApp_ZUI_ACT_ExecuteDtvManualTuningAction(EN_EXE_GOTO_MAINMENU);
            _enReturnMenuItem = STATE_RETURN_DTV_MANUAL_TUNING;
            return TRUE;

        default:
            break;

    }
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetDtvManualTuningDynamicText(HWND hwnd)
{
    MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);
    switch(hwnd)
    {
        case HWND_DTUNE_MANUAL_SCAN_UFH_TXT:
            {
            #if ENABLE_ATSC_SCAN_NEW_MODE
                U16 u16TempID = Empty;
                if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_DTV)
                {
                    u16TempID = en_str_Air_DTV;
                }
                else if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_AIR_ATV)
                {
                    u16TempID = en_str_Air_TV;
                }
                else if(MApp_Scan_ATSC_GetScanType() == ATSC_SCAN_TYPE_CABLE_DTV)
                {
                    u16TempID = en_str_CADTV;
                }
                else
                {
                    u16TempID = en_str_CATV;
                }

                if (u16TempID != Empty)
                    return MApp_ZUI_API_GetString(u16TempID);
            #else
                LPTSTR str = CHAR_BUFFER;
                U8 u8Index;

                u8Index = 0;
                if(((21 <= pstScanMenuSetting->u8RFChannelNumber )&& (pstScanMenuSetting->u8RFChannelNumber <= 69 )&&(MApp_TopStateMachine_GetTopState() != STATE_TOP_DTV_SCAN))
                    ||((21 <= MApp_Scan_Get_CurRFChannel())&&(MApp_Scan_Get_CurRFChannel() <= 69)&&(MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_SCAN)))
                {
                    str[u8Index++] = CHAR_U;
                    str[u8Index++] = CHAR_H;
                    str[u8Index++] = CHAR_F;
                }
                else
                {
                    str[u8Index++] = CHAR_V;
                    str[u8Index++] = CHAR_H;
                    str[u8Index++] = CHAR_F;
                }
                str[u8Index++] = CHAR_SPACE;
                str[u8Index++] = CHAR_SPACE;
                str[u8Index++] = CHAR_C;
                str[u8Index++] = CHAR_H;
                str[u8Index] = 0;
                return CHAR_BUFFER;
            #endif
            }
            break;

        case HWND_DTUNE_MANUAL_SCAN_CHANNEL_NAME_TXT:
            {
            #if ENABLE_ATSC_SCAN_NEW_MODE
                LPTSTR str = CHAR_BUFFER;
                U8 u8TmpIdleDigitCount = MApp_Get_IdleDigitCount();
                U8 u8Index;
                U8 u8NoOfRFChannelNumber;
                u8Index = 3;

                extern U8 MApp_GetNoOfDigit ( U32 u32Data );
                if (u8TmpIdleDigitCount == 0)
                {
                    u8NoOfRFChannelNumber = MApp_GetNoOfDigit(stGenSetting.stScanMenuSetting.u8RFChannelNumber);
                    if(u8NoOfRFChannelNumber == 1)
                    {
                        str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber%10 + CHAR_0;;
                        str[u8Index++] = 0;                    }
                    else if (u8NoOfRFChannelNumber == 2)
                    {
                        str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber/10 + CHAR_0;
                        str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber%10 + CHAR_0;;
                        str[u8Index++] = 0;
                    }
                    else if (u8NoOfRFChannelNumber == 3)
                    {
                        str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber/100 + CHAR_0;
                        str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber/10%10 + CHAR_0;
                        str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber%10 + CHAR_0;;
                        str[u8Index++] = 0;
                    }
                }
                else if (u8TmpIdleDigitCount == 1)
                {
                    str[u8Index++] = MApp_Get_IdleInputValue() + CHAR_0;
                    str[u8Index++] = CHAR_MINUS;
                    str[u8Index++] = CHAR_MINUS;
                    str[u8Index++] = 0;
                }
                else if (u8TmpIdleDigitCount == 2)
                {
                    str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber/10 + CHAR_0;
                    str[u8Index++] = stGenSetting.stScanMenuSetting.u8RFChannelNumber%10 + CHAR_0;
                    str[u8Index++] = CHAR_MINUS;;
                    str[u8Index++] = 0;
                }
                str[0] = CHAR_C;
                str[1] = CHAR_H;
                str[2] = CHAR_SPACE;
                return CHAR_BUFFER;
            #else
                U8 RFChannelName[4];
                LPTSTR str = CHAR_BUFFER;
                U8 u8Index;
                U8 u8TmpIdleDigitCount = MApp_Get_IdleDigitCount();

                //U8 u8NoOfDigit;
                u8Index = 0;
                str[u8Index] = 0;
                if (u8TmpIdleDigitCount == 0)
                {
                  #if ENABLE_DTMB_ADD_FREQUENCY
                    if(stGenSetting.stScanMenuSetting.u8RFChannelNumber <= 24)
                    {
                    	     if(TRUE == msAPI_DFT_GetPhysicalChannelName((stGenSetting.stScanMenuSetting.u8RFChannelNumber),RFChannelName,4))
	                    {
	                        str[u8Index++] = (U16)RFChannelName[0];
	                        str[u8Index++] = (U16)RFChannelName[1];
	                        str[u8Index++] = (U16)RFChannelName[2];
	                        str[u8Index++] = (U16)RFChannelName[3];
	                        str[u8Index++] = 0;
	                    }
                    }
                    else if(stGenSetting.stScanMenuSetting.u8RFChannelNumber >= 30)
                    {
                    		if(TRUE == msAPI_DFT_GetPhysicalChannelName((stGenSetting.stScanMenuSetting.u8RFChannelNumber - 5),RFChannelName,4))
                    {
                        str[u8Index++] = (U16)RFChannelName[0];
                        str[u8Index++] = (U16)RFChannelName[1];
                        str[u8Index++] = (U16)RFChannelName[2];
                        str[u8Index++] = (U16)RFChannelName[3];
                        str[u8Index++] = 0;
                    }
                    }
                    else
                    {
                    	     str[u8Index++] = 2 + '0';
                          str[u8Index++] = 4 + '0';
                          str[u8Index++] = CHAR_PLUS;
                          str[u8Index++] = (stGenSetting.stScanMenuSetting.u8RFChannelNumber - 24) + '0';
                          str[u8Index++] = 0;
                    }
                  #else
                    if(TRUE == msAPI_DFT_GetPhysicalChannelName((stGenSetting.stScanMenuSetting.u8RFChannelNumber),RFChannelName,4))
                    {
                        str[u8Index++] = (U16)RFChannelName[0];
                        str[u8Index++] = (U16)RFChannelName[1];
                        str[u8Index++] = (U16)RFChannelName[2];
                        str[u8Index++] = (U16)RFChannelName[3];
                        str[u8Index++] = 0;
                    }
                  #endif
                }
                else if (u8TmpIdleDigitCount == 1)
                {
                    MApp_ZUI_API_GetU16String(MApp_Get_IdleInputValue());
                    CHAR_BUFFER[1] = CHAR_MINUS;
                    CHAR_BUFFER[2] = 0;
                }
                else if (u8TmpIdleDigitCount == 2)
                {
                    return MApp_ZUI_API_GetU16String(pstScanMenuSetting->u8RFChannelNumber);

                }
                else
                {
                    CHAR_BUFFER[0] = 0;
                }
                return CHAR_BUFFER;
            #endif
            }
            break;

        case HWND_DTUNE_SCAN_RESULT_DTV_NUMBER_TXT:
        #if ENABLE_ATSC_SCAN_NEW_MODE
            return MApp_ZUI_API_GetU16String(MApp_Scan_ATSC_GetScanCHFound());
        #else
            return MApp_ZUI_API_GetU16String(u16ScanDtvChNum);
        #endif

        case HWND_DTUNE_SCAN_RESULT_RADIO_NUMBER_TXT:
            return MApp_ZUI_API_GetU16String(u16ScanRadioChNum);

#if NORDIG_FUNC //for Nordig Spec v2.0
        case HWND_DTUNE_SCAN_RESULT_DATA_NUMBER_TXT:
            return MApp_ZUI_API_GetU16String(u16ScanDataChNum);
#endif

    }

    //if (u16TempID != Empty)
    //    return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

S16 MApp_ZUI_ACT_GetDtvManualTuningDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_DTUNE_SIGNAL_BAR:
            return g_CurSignalStrength;
    }

    return 0; //for empty  data
}

void MApp_ZUI_ACT_AppShowDtvManualTuning(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_DTV_MANUAL_TUNING;
    MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);
    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

#if ENABLE_ATSC_SCAN_NEW_MODE
    if(ANT_TYPE == ANT_AIR)
    {
        pstScanMenuSetting->u8RFChannelNumber = CHAN_AIR_MIN;
    }
    else if(ANT_TYPE == ANT_CATV)
    {
        pstScanMenuSetting->u8RFChannelNumber = CHAN_CATV_MIN;
    }
#else
    if( msAPI_CM_GetPhysicalChannelNumber(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType())) != INVALID_PHYSICAL_CHANNEL_NUMBER )
        pstScanMenuSetting->u8RFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
    else
        pstScanMenuSetting->u8RFChannelNumber = msAPI_DFT_GetFirstPhysicalChannelNumber();
#endif

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_DTV_MANUAL_TUNING_XSTART, ZUI_DTV_MANUAL_TUNING_YSTART,
        ZUI_DTV_MANUAL_TUNING_WIDTH, ZUI_DTV_MANUAL_TUNING_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }


    if (!MApp_InputSrc_Is_UiInputSrcTypeDtv(UI_INPUT_SOURCE_TYPE))
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        UI_INPUT_SOURCE_TYPE = SYS_DEFAULT_DTV_UI_INPUTSOURCE;
        
    #if ENABLE_SBTVD_SCAN
        if(msAPI_SRC_IS_SBTVD_InUse())
        {
            enLastWatchAntennaType = ANTENNA_DTV_TYPE;
            MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE , MAIN_WINDOW );
        }
        else
    #endif
        {
            MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
        }

        MApp_SaveSysSetting();
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }


    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_NO_SIGNAL_BTN, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_SEARCHING_TXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_ENTERKEY_REMIND_TXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_DTV_TXT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_RADIO_TXT, SW_HIDE);
#if 1//NORDIG_FUNC //for Nordig Spec v2.0
    MApp_ZUI_API_ShowWindow(HWND_DTUNE_SCAN_RESULT_DATA_TXT, SW_HIDE);
#endif
    MApp_ZUI_API_SetFocus(HWND_DTUNE_MANUAL_SCAN_BAR);

}
#endif//#if ENABLE_DTV
#undef MAPP_ZUI_ACTDTVMANUALTUNING_C
