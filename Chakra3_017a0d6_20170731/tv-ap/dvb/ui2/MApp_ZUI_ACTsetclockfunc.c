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

#define MAPP_ZUI_ACTSETCLOCKFUNC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "Utl.h"

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"

#include "msAPI_Global.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTsetclockfunc.h"
#include "MApp_ZUI_GlobalFunction.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_GlobalFunction.h"
#include "MApp_Sleep.h"
#include "msAPI_Timer.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_ATVSystem.h"
#include "MApp_Key.h"
#if (ENABLE_ATSC)
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_UiMenuFunc_ATSC.h"
#endif

#if ENABLE_DVB//(ENABLE_DTV)
//#include "mapp_demux.h"
//#include "mapp_si.h"
#include "MApp_Dvb_SI.h" // "mapp_si.h"
#endif

#include "drvpower_if.h"
///////////////////////////////////////////////////
//for adjust clock

extern U32 u32ProtectOffTimer;
U16 u16SetTimeInputValue;
U8 u8SetTimeDigitCount;

extern U16 OnTime;
extern U16 OffTime;
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
////////////////////////////////////////////////////

void MApp_ZUI_ACT_ResetTimeMenuTenKey(void)
{
    u8SetTimeDigitCount = 0;
    u16SetTimeInputValue = 0;
}

#if 0
BOOLEAN MApp_ZUI_ACT_ExecuteSetClockDialogAction(U16 act)
{
    ST_TIME _stTime;
    U16 MonthDays;

    switch(act)
    {
        /*
        case EN_EXE_CLOSE_SET_CLOCK:
            MApp_Sleep_SetOffTime(TRUE); //enable and setting timer
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_SET_CLOCK, SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_MENU_TIME_SET_CLOCK);
            MApp_Time_SetOnTime();
            MApp_ZUI_API_PostMessage(HWND_MENU_DLG_SET_CLOCK, MSG_EFFECT_ROLLUP, 0);
            return TRUE;
        */
        case EN_EXE_DEC_SET_CLOCK_YEAR:
        case EN_EXE_INC_SET_CLOCK_YEAR:

            //from case MAPP_UIMENUFUNC_ADJMENUDYEARVALUE:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
            if(!(g_u8TimeInfo_Flag & UI_TIME_YEAR_SET))
            {
                stLMGenSetting.stMD.u16Option_Info_Year = UI_TIME_YEAR_INIT;
            }

            stLMGenSetting.stMD.u16Option_Info_Year=
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SET_CLOCK_YEAR,
                    stLMGenSetting.stMD.u16Option_Info_Year, 2000, 2100, 1);

//              if(!(stLMGenSetting.stMD.u8Option_Info_TimeFlag & UI_TIME_YEAR_SET))
#if 0
            if(!(g_u8TimeInfo_Flag & UI_TIME_YEAR_SET))
            {
                stLMGenSetting.stMD.u16Option_Info_Year = UI_TIME_YEAR_INIT;
              }
#endif
            _stTime.u16Year=stLMGenSetting.stMD.u16Option_Info_Year;
            MonthDays = MApp_GetDaysOfThisMonth(_stTime.u16Year, _stTime.u8Month);

            if( stLMGenSetting.stMD.u16Option_Info_Day> MonthDays )
            {
              _stTime.u8Day= stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
            }

            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));

//              stLMGenSetting.stMD.u8Option_Info_TimeFlag |= UI_TIME_YEAR_SET;
            g_u8TimeInfo_Flag |= UI_TIME_YEAR_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_TENKEY_SET_CLOCK_YEAR:

            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

            if(u16SetTimeInputValue % 10000 > 2100)
                stLMGenSetting.stMD.u16Option_Info_Year = 2100;
            else if(u8SetTimeDigitCount==4 && u16SetTimeInputValue % 10000 < 2000)
                stLMGenSetting.stMD.u16Option_Info_Year = 2000;
            else
                stLMGenSetting.stMD.u16Option_Info_Year = u16SetTimeInputValue % 10000;

            if(u8SetTimeDigitCount == 4)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
                _stTime.u16Year=stLMGenSetting.stMD.u16Option_Info_Year;
                MonthDays = MApp_GetDaysOfThisMonth(_stTime.u16Year, _stTime.u8Month);

                if( stLMGenSetting.stMD.u16Option_Info_Day> MonthDays )
                {
                  _stTime.u8Day= stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
                }

                _stTime.u8Sec = 0;
                u32ProtectOffTimer = msAPI_Timer_GetTime0();
                MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
                g_u8TimeInfo_Flag |= UI_TIME_YEAR_SET;
            }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_DEC_SET_CLOCK_MONTH:
        case EN_EXE_INC_SET_CLOCK_MONTH:
            //from case MAPP_UIMENUFUNC_ADJMENUDMONTHVALUE:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

            if(!(g_u8TimeInfo_Flag & UI_TIME_MONTH_SET))
            {
                stLMGenSetting.stMD.u16Option_Info_Month = 0;
            }



            stLMGenSetting.stMD.u16Option_Info_Month=
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SET_CLOCK_MONTH,
                    stLMGenSetting.stMD.u16Option_Info_Month, 1, 12, 1);

//            if(!(stLMGenSetting.stMD.u8Option_Info_TimeFlag & UI_TIME_MONTH_SET))
#if 0
            if(!(g_u8TimeInfo_Flag & UI_TIME_MONTH_SET))
            {
                stLMGenSetting.stMD.u16Option_Info_Month = UI_TIME_MONTH_INIT;
            }
#endif
            _stTime.u8Month=(U8)stLMGenSetting.stMD.u16Option_Info_Month;
            MonthDays = MApp_GetDaysOfThisMonth(_stTime.u16Year, _stTime.u8Month);

            if( stLMGenSetting.stMD.u16Option_Info_Day> MonthDays )
            {
                _stTime.u8Day= stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
            }

            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
//            stLMGenSetting.stMD.u8Option_Info_TimeFlag |= UI_TIME_MONTH_SET;
            g_u8TimeInfo_Flag |= UI_TIME_MONTH_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_TENKEY_SET_CLOCK_MONTH:

            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

            MS_DEBUG_MSG(printf("u16SetTimeInputValue=%u \n",u16SetTimeInputValue));
            if(u16SetTimeInputValue%100 == 0)
                return TRUE;
            else
            if(u16SetTimeInputValue%100 > 12)
                stLMGenSetting.stMD.u16Option_Info_Month = 12;
            else
                stLMGenSetting.stMD.u16Option_Info_Month = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }
            _stTime.u8Month=(U8)stLMGenSetting.stMD.u16Option_Info_Month;
            MonthDays = MApp_GetDaysOfThisMonth(_stTime.u16Year, _stTime.u8Month);

            if( stLMGenSetting.stMD.u16Option_Info_Day> MonthDays )
            {
                _stTime.u8Day= stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
            }

            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
//            stLMGenSetting.stMD.u8Option_Info_TimeFlag |= UI_TIME_MONTH_SET;
            g_u8TimeInfo_Flag |= UI_TIME_MONTH_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_DEC_SET_CLOCK_DAY:
        case EN_EXE_INC_SET_CLOCK_DAY:
            //from case MAPP_UIMENUFUNC_ADJMENUDDAYVALUE:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

            if(!(g_u8TimeInfo_Flag & UI_TIME_DAY_SET))
            {
                //stLMGenSetting.stMD.u16Option_Info_Day = UI_TIME_DAY_INIT;
                stLMGenSetting.stMD.u16Option_Info_Month = UI_TIME_MONTH_INIT;
                stLMGenSetting.stMD.u16Option_Info_Day = 0;
            }

            MonthDays = MApp_GetDaysOfThisMonth(stLMGenSetting.stMD.u16Option_Info_Year,stLMGenSetting.stMD.u16Option_Info_Month);
            stLMGenSetting.stMD.u16Option_Info_Day=
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SET_CLOCK_DAY,
                    stLMGenSetting.stMD.u16Option_Info_Day, 1,   MonthDays, 1);

//            if(!(stLMGenSetting.stMD.u8Option_Info_TimeFlag & UI_TIME_DAY_SET))
#if 0
            if(!(g_u8TimeInfo_Flag & UI_TIME_DAY_SET))
            {
                stLMGenSetting.stMD.u16Option_Info_Day = UI_TIME_DAY_INIT;
            }
#endif
            _stTime.u8Day=(U8)stLMGenSetting.stMD.u16Option_Info_Day;
            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
//            stLMGenSetting.stMD.u8Option_Info_TimeFlag |= UI_TIME_DAY_SET;
            g_u8TimeInfo_Flag |= UI_TIME_DAY_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_TENKEY_SET_CLOCK_DAY:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
            MonthDays = MApp_GetDaysOfThisMonth(stLMGenSetting.stMD.u16Option_Info_Year,stLMGenSetting.stMD.u16Option_Info_Month);
            MS_DEBUG_MSG(printf("MonthDays=%u SetTimeInputValue=%u \n",MonthDays,u16SetTimeInputValue));
            if(MonthDays != 0 && u16SetTimeInputValue%100 > MonthDays)
                stLMGenSetting.stMD.u16Option_Info_Day = MonthDays;
            else if( u16SetTimeInputValue%100 <= 31 )
                stLMGenSetting.stMD.u16Option_Info_Day = u16SetTimeInputValue%100;
            else
                stLMGenSetting.stMD.u16Option_Info_Day = 31;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }
            _stTime.u8Day=(U8)stLMGenSetting.stMD.u16Option_Info_Day;
            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
//            stLMGenSetting.stMD.u8Option_Info_TimeFlag |= UI_TIME_DAY_SET;
            g_u8TimeInfo_Flag |= UI_TIME_DAY_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            return TRUE;
        case EN_EXE_DEC_SET_CLOCK_HOUR:
        case EN_EXE_INC_SET_CLOCK_HOUR:
            //from case MAPP_UIMENUFUNC_ADJMENUDHOURVALUE:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
            if(!(g_u8TimeInfo_Flag & UI_TIME_HOUR_SET))
                stLMGenSetting.stMD.u16Option_Info_Hour = UI_TIME_HOUR_INIT;

            stLMGenSetting.stMD.u16Option_Info_Hour=
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SET_CLOCK_HOUR,
                    stLMGenSetting.stMD.u16Option_Info_Hour, 0, 24-1, 1);
//            if(!(stLMGenSetting.stMD.u8Option_Info_TimeFlag & UI_TIME_HOUR_SET))
#if 0
            if(!(g_u8TimeInfo_Flag & UI_TIME_HOUR_SET))
                stLMGenSetting.stMD.u16Option_Info_Hour = UI_TIME_HOUR_INIT;
#endif
            _stTime.u8Hour=(U8)stLMGenSetting.stMD.u16Option_Info_Hour;
            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
//            stLMGenSetting.stMD.u8Option_Info_TimeFlag |= UI_TIME_HOUR_SET;
            g_u8TimeInfo_Flag |= UI_TIME_HOUR_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_TENKEY_SET_CLOCK_HOUR:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

            if( u16SetTimeInputValue%100 > 23)
                stLMGenSetting.stMD.u16Option_Info_Hour = 23;
            else
                stLMGenSetting.stMD.u16Option_Info_Hour = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }

            _stTime.u8Hour=(U8)stLMGenSetting.stMD.u16Option_Info_Hour;
            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));

            g_u8TimeInfo_Flag |= UI_TIME_HOUR_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_DEC_SET_CLOCK_MIN:
        case EN_EXE_INC_SET_CLOCK_MIN:
            //from case MAPP_UIMENUFUNC_ADJMENUDMINVALUE:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
            if(!(g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET))
                stLMGenSetting.stMD.u16Option_Info_Min = UI_TIME_MINUTE_INIT;

            stLMGenSetting.stMD.u16Option_Info_Min=
                MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SET_CLOCK_MIN,
                    stLMGenSetting.stMD.u16Option_Info_Min, 0, 60-1, 1);
#if 0
            if(!(g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET))
                stLMGenSetting.stMD.u16Option_Info_Min = UI_TIME_MINUTE_INIT;
#endif
            _stTime.u8Min=(U8)stLMGenSetting.stMD.u16Option_Info_Min;

            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
            g_u8TimeInfo_Flag |= UI_TIME_MINUTE_SET;

//            if (stLMGenSetting.stMD.u8Option_Info_TimeFlag == UI_TIME_MANUAL_SET)

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        case EN_EXE_TENKEY_SET_CLOCK_MIN:
            MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);


            if( u16SetTimeInputValue%100 > 59)
                stLMGenSetting.stMD.u16Option_Info_Min = 59;
            else
                stLMGenSetting.stMD.u16Option_Info_Min = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }

            _stTime.u8Min=(U8)stLMGenSetting.stMD.u16Option_Info_Min;

            _stTime.u8Sec = 0;
            u32ProtectOffTimer = msAPI_Timer_GetTime0();

            MApp_SetLocalSystemTime(MApp_ConvertStTime2Seconds(&_stTime));
            g_u8TimeInfo_Flag |= UI_TIME_MINUTE_SET;

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_CLOCK_PAGE);
            MApp_Time_SetOnTime();
            return TRUE;
        default:
            ZUI_DBG_FAIL(printf("[ZUI]CLOCKACT\n"));
            ABORT();


    }
    return FALSE;
}
#endif
BOOLEAN MApp_ZUI_ACT_ExecuteSetOffTimeDialogAction(U16 act)
{
    switch (act)
    {
        case EN_EXE_CLOSE_SET_OFFTIME:
            MApp_Sleep_SetOffTime(TRUE); //enable and setting timer
            return TRUE;
/*
        case EN_EXE_DEC_SET_OFFTIME_REPEAT:
        case EN_EXE_INC_SET_OFFTIME_REPEAT:
            stGenSetting.g_Time.cOffTimerFlag =
                (EN_MENU_TIME_OffTimer)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_OFFTIME_REPEAT,
                    stGenSetting.g_Time.cOffTimerFlag,(U16) EN_Time_OffTimer_Off, (U16)(EN_Time_OffTimer_Num-1), 1);

            if (stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Off)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_OFFTIME_HOUR, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_OFFTIME_MINUTE, DISABLE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_OFFTIME_PAGE, ENABLE);
            }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_OFFTIME_PAGE);
            return TRUE;

        case EN_EXE_DEC_SET_OFFTIME_HOUR:
        case EN_EXE_INC_SET_OFFTIME_HOUR:
            stGenSetting.g_Time.u16OffTimer_Info_Hour =
                MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_OFFTIME_HOUR,
                    stGenSetting.g_Time.u16OffTimer_Info_Hour, 0, 24-1, 1);

            if ( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
                && stGenSetting.g_Time.u16OnTimer_Info_Min == stGenSetting.g_Time.u16OffTimer_Info_Min)
            {
                EN_OSD_WNDEXEACTION_ENUM temp_act = (EN_OSD_WNDEXEACTION_ENUM)act;

                if(act == EN_EXE_INC_SET_OFFTIME_HOUR)
                {
                    if(stGenSetting.g_Time.u16OffTimer_Info_Min >= (60-1))
                        temp_act = EN_EXE_DEC_SET_OFFTIME_HOUR;
                }
                else
                {
                    if(stGenSetting.g_Time.u16OffTimer_Info_Min == 0)
                        temp_act = EN_EXE_INC_SET_OFFTIME_HOUR;
                }
                stGenSetting.g_Time.u16OffTimer_Info_Min =
                    MApp_ZUI_ACT_DecIncValue_Cycle(temp_act==EN_EXE_INC_SET_OFFTIME_HOUR,
                        stGenSetting.g_Time.u16OffTimer_Info_Min, 0, 60-1, 1);
            }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_OFFTIME_PAGE);
            return TRUE;

        case EN_EXE_TENKEY_SET_OFFTIME_HOUR:
            if( u16SetTimeInputValue%100 > 23)
                stGenSetting.g_Time.u16OffTimer_Info_Hour = 23;
            else
                stGenSetting.g_Time.u16OffTimer_Info_Hour = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_OFFTIME_PAGE);
            return TRUE;

        case EN_EXE_DEC_SET_OFFTIME_MIN:
        case EN_EXE_INC_SET_OFFTIME_MIN:
            stGenSetting.g_Time.u16OffTimer_Info_Min=
                MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_OFFTIME_MIN,
                    stGenSetting.g_Time.u16OffTimer_Info_Min, 0, 60-1, 1);

            if( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
                && stGenSetting.g_Time.u16OffTimer_Info_Min == stGenSetting.g_Time.u16OnTimer_Info_Min)
            {
                stGenSetting.g_Time.u16OffTimer_Info_Min=
                    MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_OFFTIME_MIN,
                        stGenSetting.g_Time.u16OffTimer_Info_Min, 0, 60-1, 1);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_OFFTIME_PAGE);
            return TRUE;

        case EN_EXE_TENKEY_SET_OFFTIME_MIN:
            if( u16SetTimeInputValue%100 > 59)
                stGenSetting.g_Time.u16OffTimer_Info_Min = 59;
            else
                stGenSetting.g_Time.u16OffTimer_Info_Min = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_OFFTIME_PAGE);
            return TRUE;
*/
        default:
            ZUI_DBG_FAIL(printf("[ZUI]OffTimeACT\n"));
            ABORT();
    }
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteSetOnTimeDialogAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_SET_ONTIME:
            MApp_Time_SetOnTime(); //enable and setting timer
            return TRUE;
/*
        case EN_EXE_DEC_SET_ONTIME_REPEAT:
        case EN_EXE_INC_SET_ONTIME_REPEAT:
        {
            stGenSetting.g_Time.cOnTimerFlag =
                (EN_MENU_TIME_OnTimer)MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_ONTIME_REPEAT,
                    stGenSetting.g_Time.cOnTimerFlag,(U16) EN_Time_OnTimer_Off, (U16)(EN_Time_OnTimer_Num-1), 1);

            MApp_Time_SetOnTime();

            if (stGenSetting.g_Time.cOnTimerFlag==EN_Time_OnTimer_Off)
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_HOUR, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_MINUTE, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_SOURCE, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_CHANNEL, DISABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_VOLUME, DISABLE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_PAGE, ENABLE);
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }

        case EN_EXE_DEC_SET_ONTIME_HOUR:
        case EN_EXE_INC_SET_ONTIME_HOUR:
        {
            stGenSetting.g_Time.u16OnTimer_Info_Hour =
                MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_ONTIME_HOUR,
                    stGenSetting.g_Time.u16OnTimer_Info_Hour, 0, 24-1, 1);

            if( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
                && stGenSetting.g_Time.u16OnTimer_Info_Min == stGenSetting.g_Time.u16OffTimer_Info_Min)
            {
                EN_OSD_WNDEXEACTION_ENUM temp_act = (EN_OSD_WNDEXEACTION_ENUM)act;
                if(act == EN_EXE_INC_SET_ONTIME_HOUR)
                {
                    if(stGenSetting.g_Time.u16OnTimer_Info_Min >= (60-1))
                        temp_act = EN_EXE_DEC_SET_ONTIME_HOUR;
                }
                else
                {
                    if(stGenSetting.g_Time.u16OnTimer_Info_Min == 0)
                        temp_act = EN_EXE_INC_SET_ONTIME_HOUR;
                }
                stGenSetting.g_Time.u16OnTimer_Info_Min =
                    MApp_ZUI_ACT_DecIncValue_Cycle(temp_act==EN_EXE_INC_SET_ONTIME_HOUR,
                        stGenSetting.g_Time.u16OnTimer_Info_Min, 0, 60-1, 1);
            }

            MApp_Time_SetOnTime();

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }
        case EN_EXE_TENKEY_SET_ONTIME_HOUR:
        {
            if( u16SetTimeInputValue%100 > 23)
                stGenSetting.g_Time.u16OnTimer_Info_Hour = 23;
            else
                stGenSetting.g_Time.u16OnTimer_Info_Hour = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }

            MApp_Time_SetOnTime();

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }
        case EN_EXE_DEC_SET_ONTIME_MIN:
        case EN_EXE_INC_SET_ONTIME_MIN:
        {
            stGenSetting.g_Time.u16OnTimer_Info_Min=
                MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_ONTIME_MIN,
                    stGenSetting.g_Time.u16OnTimer_Info_Min, 0, 60-1, 1);

            if( stGenSetting.g_Time.u16OnTimer_Info_Hour == stGenSetting.g_Time.u16OffTimer_Info_Hour
                && stGenSetting.g_Time.u16OnTimer_Info_Min == stGenSetting.g_Time.u16OffTimer_Info_Min)
            {
                stGenSetting.g_Time.u16OnTimer_Info_Min =
                    MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_ONTIME_MIN,
                        stGenSetting.g_Time.u16OnTimer_Info_Min, 0, 60-1, 1);
            }
            MApp_Time_SetOnTime();

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }
        case EN_EXE_TENKEY_SET_ONTIME_MIN:
        {
            if( u16SetTimeInputValue%100 > 59)
                stGenSetting.g_Time.u16OnTimer_Info_Min = 59;
            else
                stGenSetting.g_Time.u16OnTimer_Info_Min = u16SetTimeInputValue%100;

            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }

            MApp_Time_SetOnTime();

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }
        case EN_EXE_DEC_SET_ONTIME_SOURCE:
        case EN_EXE_INC_SET_ONTIME_SOURCE:
        {
            #if 0  //Thomas 20150714 to do
            U8 i = 4;
            U16 u16DtvCount=0, u16RadioCount=0, u16AtvCount=0;
#if NORDIG_FUNC //for Nordig Spec v2.0
            U16 u16DataCount=0;
#endif
		#if ENABLE_S2
			U16 u16S2Count = 0;
		#endif
#if ENABLE_DTV
            u16DtvCount = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            u16RadioCount = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
			#if NORDIG_FUNC //for Nordig Spec v2.0
            u16DataCount = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
			#endif
#endif
		#if ENABLE_S2
			u16S2Count = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
		#endif
            u16AtvCount = msAPI_ATV_GetActiveProgramCount();

            while (i>0)
            {
                BOOLEAN bNext = FALSE;

                i--;
            #if (ENABLE_ATSC)
                stGenSetting.g_Time.cOnTimerSourceFlag =(EN_MENU_TIME_OnTimer_Source) MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_SET_ONTIME_SOURCE), (U16)stGenSetting.g_Time.cOnTimerSourceFlag,(U16) EN_Time_OnTimer_Source_TV, (U16)(EN_Time_OnTimer_Source_Num-1), 1);
            #else
                stGenSetting.g_Time.cOnTimerSourceFlag =(EN_MENU_TIME_OnTimer_Source) MApp_ZUI_ACT_DecIncValue_Cycle((act==EN_EXE_INC_SET_ONTIME_SOURCE), (U16)stGenSetting.g_Time.cOnTimerSourceFlag,(U16) EN_Time_OnTimer_Source_DTV, (U16)(EN_Time_OnTimer_Source_Num-1), 1);
            #endif
                switch (stGenSetting.g_Time.cOnTimerSourceFlag)
                {
                #if (ENABLE_ATSC)
                    case EN_Time_OnTimer_Source_TV:
                        if (!MApp_ChanProc_GetNumOfServices(MAIN_LIST))
                        {
                            bNext = TRUE;
                        }
                        break;
                #else
                    case EN_Time_OnTimer_Source_DTV:
                        if (u16DtvCount == 0)
                        {
                            bNext = TRUE;
                        }
                        break;
                #endif
                    case EN_Time_OnTimer_Source_RADIO:
                        if (u16RadioCount == 0)
                        {
                            bNext = TRUE;
                        }
                        break;
		#if (ENABLE_DMP) //reload code for pure MM mode
			// case EN_Time_OnTimer_Source_DLNA: //must
                      case EN_Time_OnTimer_Source_MPLAYER://remove mm source for ontime source
			 {
				bNext = TRUE;
			 }
			break;
		#endif
                    #if NORDIG_FUNC //for Nordig Spec v2.0
                    case EN_Time_OnTimer_Source_DATA:
                        if (u16DataCount == 0)
                        {
                            bNext = TRUE;
                        }
                        break;
                    #endif

#if (!ENABLE_ATSC)
                    case EN_Time_OnTimer_Source_ATV:
                        if (u16AtvCount == 0)
                        {
                            bNext = TRUE;
                        }
                        break;
#endif
				#if ENABLE_S2
					case EN_Time_OnTimer_Source_DVBS2:
						if (u16S2Count == 0)
						{
							bNext = TRUE;
						}
						break;
				#endif
                    default:
                        break;
                }

                if (!bNext)
                {
                    break;
                }
				if (i == 0)
				{
					if(act==EN_EXE_INC_SET_ONTIME_SOURCE)
					{
                        #if (ENABLE_ATSC)
                        stGenSetting.g_Time.cOnTimerSourceFlag = (EN_MENU_TIME_OnTimer_Source)EN_Time_OnTimer_Source_TV;
                        #else
						stGenSetting.g_Time.cOnTimerSourceFlag = (EN_MENU_TIME_OnTimer_Source)EN_Time_OnTimer_Source_DTV;
                        #endif
						i = 4;
					}
					else
					{
						stGenSetting.g_Time.cOnTimerSourceFlag = (EN_MENU_TIME_OnTimer_Source)(EN_Time_OnTimer_Source_Num - 2);
						break;
					}
				}
            }
            // Fist Channel auto detect
            switch(stGenSetting.g_Time.cOnTimerSourceFlag)
            {
                case EN_Time_OnTimer_Source_RADIO:
                    stGenSetting.g_Time.cOnTimerChannel = 0;//msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_RADIO, 0);
                    break;
#if (ENABLE_ATSC)
                case EN_Time_OnTimer_Source_TV:
#else
                case EN_Time_OnTimer_Source_DTV:
#endif
			#if ENABLE_S2
				case EN_Time_OnTimer_Source_DVBS2:
			#endif
                    stGenSetting.g_Time.cOnTimerChannel = 0;//msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV, 0);
                    break;

                #if NORDIG_FUNC //for Nordig Spec v2.0
                case EN_Time_OnTimer_Source_DATA:
                    stGenSetting.g_Time.cOnTimerChannel = 0;//msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DATA, 0);
                    break;
                #endif
#if (!ENABLE_ATSC)
                case EN_Time_OnTimer_Source_ATV:
                    stGenSetting.g_Time.cOnTimerChannel = msAPI_ATV_GetFirstProgramNumber(FALSE);
                    break;
#endif
                default:
                    break;
            }

            if(stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_RADIO
            #if (ENABLE_ATSC)
                || stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_TV
            #else
                || stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DTV
            #endif
			#if ENABLE_S2
				|| stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBS2
			#endif
                #if NORDIG_FUNC //for Nordig Spec v2.0
                || stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DATA
                #endif
            #if (!ENABLE_ATSC)
                || stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_ATV
            #endif
                )
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_CHANNEL, TRUE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(HWND_MENU_TIME_ONTIME_CHANNEL, FALSE);
            }
#endif
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }

        case EN_EXE_DEC_SET_ONTIME_CHANNEL:
        case EN_EXE_INC_SET_ONTIME_CHANNEL:
        {
            #if 0//Thomas 20150714 to do
#if ENABLE_DTV
        #if (!ENABLE_ATSC)
            CHANNEL_LIST_TYPE eListMode = E_DTV_LIST;
        #endif
#endif
            switch (stGenSetting.g_Time.cOnTimerSourceFlag)
            {
#if ENABLE_DTV
            #if (ENABLE_ATSC)
                case EN_Time_OnTimer_Source_TV:
            #else
                case EN_Time_OnTimer_Source_DTV:
            #endif
			#if ENABLE_S2
				case EN_Time_OnTimer_Source_DVBS2:
			#endif
                case EN_Time_OnTimer_Source_RADIO:

                #if NORDIG_FUNC //for Nordig spec v2.0
                case EN_Time_OnTimer_Source_DATA:
                #endif
            #if (ENABLE_ATSC)
                if (act == EN_EXE_INC_SET_ONTIME_CHANNEL)
                {
                    stGenSetting.g_Time.cOnTimerChannel = MApp_GetPrevNextProgramIndex_ByProgIndex(FALSE, stGenSetting.g_Time.cOnTimerChannel);
                }
                else if (act == EN_EXE_DEC_SET_ONTIME_CHANNEL)
                {
                    stGenSetting.g_Time.cOnTimerChannel = MApp_GetPrevNextProgramIndex_ByProgIndex(TRUE, stGenSetting.g_Time.cOnTimerChannel);
                }
            #else
                {
                    MEMBER_SERVICETYPE type=E_SERVICETYPE_DTV;
				#if ENABLE_S2
					if ((stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DTV) || (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DVBS2))
				#else
                    if (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DTV)
				#endif
                    {
                        type = E_SERVICETYPE_DTV;
                        eListMode = E_DTV_LIST;
                    }
                    else if (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_RADIO)
                    {
                        type = E_SERVICETYPE_RADIO;
                        eListMode = E_RADIO_LIST;
                    }
                    #if NORDIG_FUNC //for Nordig spec v2.0
                        else if (stGenSetting.g_Time.cOnTimerSourceFlag == EN_Time_OnTimer_Source_DATA)
                        {
                            type = E_SERVICETYPE_DATA;
                            eListMode = E_DATA_LIST;
                        }
                    #endif

                    if (act == EN_EXE_INC_SET_ONTIME_CHANNEL)
                    {
                        stGenSetting.g_Time.cOnTimerChannel = msAPI_CM_GetNextProgramPosition(type, stGenSetting.g_Time.cOnTimerChannel, FALSE, eListMode,NULL);
                    }
                    else if (act == EN_EXE_DEC_SET_ONTIME_CHANNEL)
                    {
                        stGenSetting.g_Time.cOnTimerChannel = msAPI_CM_GetPrevProgramPosition(type, stGenSetting.g_Time.cOnTimerChannel, FALSE, eListMode,NULL);
                    }
                }
            #endif
                break;
#endif
            #if (!ENABLE_ATSC)
                case EN_Time_OnTimer_Source_ATV:
                {
                    if (act == EN_EXE_INC_SET_ONTIME_CHANNEL)
                    {
                        stGenSetting.g_Time.cOnTimerChannel = msAPI_ATV_GetNextProgramNumber(stGenSetting.g_Time.cOnTimerChannel, FALSE);
                    }
                    else if (act == EN_EXE_DEC_SET_ONTIME_CHANNEL)
                    {
                        stGenSetting.g_Time.cOnTimerChannel = msAPI_ATV_GetPrevProgramNumber(stGenSetting.g_Time.cOnTimerChannel, FALSE);
                    }
                }
                break;
            #endif
                default:
                    break;
            }
            #endif
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }

        case EN_EXE_DEC_SET_ONTIME_VOLUME:
        case EN_EXE_INC_SET_ONTIME_VOLUME:
        {
            stGenSetting.g_Time.cOnTimerVolume =(U8) MApp_ZUI_ACT_DecIncValue_Cycle(act==EN_EXE_INC_SET_ONTIME_VOLUME, stGenSetting.g_Time.cOnTimerVolume, 0, 100, 1);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }
        case EN_EXE_TENKEY_SET_ONTIME_VOLUME:
        {
            stGenSetting.g_Time.cOnTimerVolume = u16SetTimeInputValue%101;
            if(u8SetTimeDigitCount >= 2)
            {
                MApp_ZUI_ACT_ResetTimeMenuTenKey();
            }
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_TIME_ONTIME_PAGE);
            return TRUE;
        }
        */
        default:
            ZUI_DBG_FAIL(printf("[ZUI]OnTimeACT\n"));
            ABORT();
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
extern void _MApp_ZUI_ACT_LoadMonthString(U8 month, LPTSTR str);

LPTSTR MApp_ZUI_ACT_GetSetClockDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    ST_TIME _stTime;

    switch(hwnd)
    {
        case HWND_MENU_COMMON_ADJ_ITEM2_OPTION://HWND_MENU_TIME_CLOCK_DAY_OPTION:
            //from case D1_OPTION_DAYVALUETEXT:
            if((g_u8TimeInfo_Flag & UI_TIME_DAY_SET)
#if ENABLE_DVB
                || MApp_SI_IsAutoClockValid()
#endif
                )
            {
                U16 u16Len = 0;
                LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Date);
                u16Len = MApp_ZUI_API_Strlen(ptr);
                ptr[u16Len++] = CHAR_SPACE;
                MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
                stLMGenSetting.stMD.u16Option_Info_Day=_stTime.u8Day;
                __MApp_UlongToString((U16)stLMGenSetting.stMD.u16Option_Info_Day, ptr+u16Len, 2);
                return ptr;

            }
            else
            {
                u16TempID=en_str_dashdash;
            }
            break;

        case HWND_MENU_COMMON_ADJ_ITEM3_OPTION://HWND_MENU_TIME_CLOCK_MONTH_OPTION:
            //from case D1_OPTION_MONTHVALUETEXT:
            if((g_u8TimeInfo_Flag & UI_TIME_MONTH_SET)
#if ENABLE_DVB
                || MApp_SI_IsAutoClockValid()
#endif
                )
            {
                U16 u16Len = 0;
                LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Month);
                u16Len = MApp_ZUI_API_Strlen(ptr);
                ptr[u16Len++] = CHAR_SPACE;
                MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
                stLMGenSetting.stMD.u16Option_Info_Month=_stTime.u8Month;
                //return strMonthCal[stLMGenSetting.stMD.u16Option_Info_Month-1];
                _MApp_ZUI_ACT_LoadMonthString(stLMGenSetting.stMD.u16Option_Info_Month-1, ptr+u16Len);
                return ptr;
            }
            else
            {
                u16TempID=en_str_dashdash;
            }
            break;

        case HWND_MENU_COMMON_ADJ_ITEM4_OPTION://HWND_MENU_TIME_CLOCK_YEAR_OPTION:
            //from case D1_OPTION_YEARVALUETEXT:
        {
            U16 u16Len = 0;
            LPTSTR YearPtr = MApp_ZUI_API_GetString(en_str_Year);
            u16Len = MApp_ZUI_API_Strlen(YearPtr);
            YearPtr[u16Len++] = CHAR_SPACE;
            if((g_u8TimeInfo_Flag & UI_TIME_YEAR_SET)
#if ENABLE_DVB
                || MApp_SI_IsAutoClockValid()
#endif
                )
            {
                MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
                stLMGenSetting.stMD.u16Option_Info_Year = _stTime.u16Year;
                if(MApp_ZUI_API_GetFocus() == HWND_MENU_COMMON_ADJ_ITEM4 && u8SetTimeDigitCount >=1 && u8SetTimeDigitCount <= 3)
                {
                    MApp_UlongToU16String((u16SetTimeInputValue % 10000), (U16*)YearPtr+u16Len, MApp_GetNoOfDigit(u16SetTimeInputValue % 10000));
                    return YearPtr;
                }
                else
                {
                    MApp_UlongToU16String((stLMGenSetting.stMD.u16Option_Info_Year), (U16*)YearPtr+u16Len, MApp_GetNoOfDigit(stLMGenSetting.stMD.u16Option_Info_Year));
                    return YearPtr;
                }
            }
            else
            {   if(MApp_ZUI_API_GetFocus() == HWND_MENU_COMMON_ADJ_ITEM4 && u8SetTimeDigitCount > 0)
                {
                    MApp_UlongToU16String((u16SetTimeInputValue % 10000), (U16*)YearPtr+u16Len, MApp_GetNoOfDigit(u16SetTimeInputValue % 10000));
                    return YearPtr;
                }
                else
                    u16TempID=en_str_dashdash;
            }
            break;
        }

        case HWND_MENU_COMMON_ADJ_ITEM5_OPTION://HWND_MENU_TIME_CLOCK_HOUR_OPTION:
            //from case D1_OPTION_HOURVALUETEXT:
            {
                U16 u16Hour;
                U16 u16Len = 0;
                LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Hour);
                u16Len = MApp_ZUI_API_Strlen(ptr);
                ptr[u16Len++] = CHAR_SPACE;
                if ((g_u8TimeInfo_Flag & UI_TIME_HOUR_SET)
#if ENABLE_DVB
                    || MApp_SI_IsAutoClockValid()
#endif
                    )
                {
                    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_stTime);
                    stLMGenSetting.stMD.u16Option_Info_Hour=_stTime.u8Hour;
                    u16Hour = stLMGenSetting.stMD.u16Option_Info_Hour;
                    if (stLMGenSetting.stMD.u16Option_Info_Hour >= 12)
                    {
                        //u16Hour = stLMGenSetting.stMD.u16Option_Info_Hour - 12;
                        stLMGenSetting.stMD.bTimer_Info_PM |= UI_TIME_CLOCK_PM;
                    }
                    else
                    {
                       // u16Hour = stLMGenSetting.stMD.u16Option_Info_Hour;
                        stLMGenSetting.stMD.bTimer_Info_PM &= ~UI_TIME_CLOCK_PM;
                    }

                    //if(u16Hour == 0)
                    //    u16Hour = 12;

                    __MApp_UlongToString((U16)u16Hour, ptr+u16Len, 2);
                    return ptr;
                }
                else
                {
                    u16TempID=en_str_dashdash;
                }
            }
            break;

        case HWND_MENU_COMMON_ADJ_ITEM6_OPTION://HWND_MENU_TIME_CLOCK_MIN_OPTION:
            //from case D1_OPTION_MINVALUETEXT:
            if ((g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET)
#if ENABLE_DVB
                || MApp_SI_IsAutoClockValid()
#endif
                )
            {
                U16 u16Len = 0;
                LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Minute);
                u16Len = MApp_ZUI_API_Strlen(ptr);
                ptr[u16Len++] = CHAR_SPACE;
                MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &_stTime);
                stLMGenSetting.stMD.u16Option_Info_Min = _stTime.u8Min;
                __MApp_UlongToString((U16)stLMGenSetting.stMD.u16Option_Info_Min, ptr+u16Len, 2);

                return ptr;
            }
            else
            {
                u16TempID=en_str_dashdash;
            }
            break;
    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

LPTSTR MApp_ZUI_ACT_GetSetOffTimeDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    switch (hwnd)
    {
        case HWND_MENU_COMMON_ADJ_ITEM1_OPTION://HWND_MENU_TIME_OFFTIME_OPTION:
        {
            switch (stGenSetting.g_Time.cOffTimerFlag)
            {
                case EN_Time_OffTimer_Once:
                    u16TempID = en_str_Once;
                    break;
                case EN_Time_OffTimer_Everyday:
                    u16TempID = en_str_Every_Day;
                    break;
                case EN_Time_OffTimer_Mon2Fri:
                    u16TempID = en_str_Mon2Fri;
                    break;
                case EN_Time_OffTimer_Mon2Sat:
                    u16TempID = en_str_Mon2Sat;
                    break;
                case EN_Time_OffTimer_Sat2Sun:
                    u16TempID = en_str_Sat2Sun;
                    break;
                case EN_Time_OffTimer_Sun:
                    u16TempID = en_str_Sunday;
                    break;
                case EN_Time_OffTimer_Off:
                default:
                    u16TempID = en_str_Off;
                    break;
            }
            break;
        }

        case HWND_MENU_COMMON_ADJ_ITEM2_OPTION ://HWND_MENU_TIME_OFFTIME_HOUR_OPTION:
        {
            U16 u16Len = 0;
            LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Hour);

            // Added it by coverity_0534
            if (ptr == NULL)
            {
                u16TempID = en_str_dashdash;
                break;;
            }

            u16Len = MApp_ZUI_API_Strlen(ptr);
            ptr[u16Len++] = CHAR_SPACE;
            __MApp_UlongToString(stGenSetting.g_Time.u16OffTimer_Info_Hour, ptr+u16Len, 2);
            return ptr;
        }

        case HWND_MENU_COMMON_ADJ_ITEM3_OPTION://HWND_MENU_TIME_OFFTIME_MINUTE_OPTION:
        {
            U16 u16Len = 0;
            LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Minute);

            // Added it by coverity_0534
            if (ptr == NULL)
            {
                u16TempID=en_str_dashdash;
                break;
            }

            u16Len = MApp_ZUI_API_Strlen(ptr);
            ptr[u16Len++] = CHAR_SPACE;
            __MApp_UlongToString(stGenSetting.g_Time.u16OffTimer_Info_Min, ptr+u16Len, 2);
            return ptr;
        }
    }
    #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(OffTime != u16TempID)
        {
            printf("61_OffTime\n");
        }
        OffTime = u16TempID;
    }
    #endif

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}

LPTSTR MApp_ZUI_ACT_GetSetOnTimeDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    //ST_TIME _stTime;

    //printf("MApp_ZUI_ACT_GetSetOnTimeDynamicText(hwnd=%u)\n", hwnd);

    switch(hwnd)
    {
        case HWND_MENU_COMMON_ADJ_ITEM1_OPTION://HWND_MENU_TIME_ONTIME_REPEAT_OPTION:
        {
            switch (stGenSetting.g_Time.cOnTimerFlag)
            {
                case EN_Time_OnTimer_Once:
                    u16TempID = en_str_Once;
                    break;
                case EN_Time_OnTimer_Everyday:
                    u16TempID = en_str_Every_Day;
                    break;
                case EN_Time_OnTimer_Mon2Fri:
                    u16TempID = en_str_Mon2Fri;
                    break;
                case EN_Time_OnTimer_Mon2Sat:
                    u16TempID = en_str_Mon2Sat;
                    break;
                case EN_Time_OnTimer_Sat2Sun:
                    u16TempID = en_str_Sat2Sun;
                    break;
                case EN_Time_OnTimer_Sun:
                    u16TempID = en_str_Sunday;
                    break;
                case EN_Time_OnTimer_Off:
                default:
                    u16TempID = en_str_Off;
                    break;
            }
            return MApp_ZUI_API_GetString(u16TempID);
            break;
        }
        case HWND_MENU_COMMON_ADJ_ITEM2_OPTION://HWND_MENU_TIME_ONTIME_HOUR_OPTION:
        {
            U16 u16Len = 0;
            LPTSTR HourPtr = MApp_ZUI_API_GetString(en_str_Hour);

            // Added it by coverity_0535
            if (HourPtr == NULL)
            {
                u16TempID=en_str_dashdash;
                break;
            }

            u16Len = MApp_ZUI_API_Strlen(HourPtr);
            HourPtr[u16Len++] = CHAR_SPACE;
            __MApp_UlongToString(stGenSetting.g_Time.u16OnTimer_Info_Hour, HourPtr+u16Len, 2);
            return HourPtr;
        }

        case HWND_MENU_COMMON_ADJ_ITEM3_OPTION://HWND_MENU_TIME_ONTIME_MINUTE_OPTION:
        {
            U16 u16Len = 0;
            LPTSTR MinPtr = MApp_ZUI_API_GetString(en_str_Minute);

            // Added it by coverity_0536
            if (MinPtr == NULL)
            {
                u16TempID=en_str_dashdash;
                break;
            }

            u16Len = MApp_ZUI_API_Strlen(MinPtr);
            MinPtr[u16Len++] = CHAR_SPACE;
            __MApp_UlongToString(stGenSetting.g_Time.u16OnTimer_Info_Min, MinPtr+u16Len, 2);
            return MinPtr;
            break;
        }

        case HWND_MENU_COMMON_ADJ_ITEM4_OPTION://HWND_MENU_TIME_ONTIME_SOURCE_OPTION:
        {
            //LPTSTR SourcePtr = NULL;
            /*
            LPTSTR StringPtr = MApp_ZUI_API_GetString(en_str_Source);
            u16Len = MApp_ZUI_API_Strlen(ptr);
            StringPtr[u16Len++] = CHAR_SPACE;
            StringPtr[u16Len++] = 0;
            */
            switch (stGenSetting.g_Time.cOnTimerSourceFlag)
            {
            #if (ENABLE_ATSC)
                case EN_Time_OnTimer_Source_ATSC:
                    u16TempID = en_str_ATSC;
                    break;
            #else
                case EN_Time_OnTimer_Source_ATV:
                    #if ENABLE_ISDBT
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Cable));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    #else
                    u16TempID = en_str_ATV;
                    #endif
                    break;
            #endif

            #if ENABLE_DVBT
                case EN_Time_OnTimer_Source_DVBT:
                    u16TempID = en_str_DVBdashT;
                    break;

                case EN_Time_OnTimer_Source_DVBT_RADIO:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DVBdashT));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Radio));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;

                #if NORDIG_FUNC //for Nordig spec v2.0
                case EN_Time_OnTimer_Source_DVBT_DATA:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DVBdashT));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Data));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;
                #endif
            #endif

            #if ENABLE_DVBC
                case EN_Time_OnTimer_Source_DVBC:
                    u16TempID = en_str_DVBdashC;
                    break;

                case EN_Time_OnTimer_Source_DVBC_RADIO:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DVBdashC));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Radio));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;

                #if NORDIG_FUNC //for Nordig spec v2.0
                case EN_Time_OnTimer_Source_DVBC_DATA:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DVBdashC));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Data));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;
                #endif
            #endif

            #if ENABLE_DTMB
                case EN_Time_OnTimer_Source_DTMB:
                    u16TempID = en_str_DTMB;
                    break;

                case EN_Time_OnTimer_Source_DTMB_RADIO:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DTMB));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Radio));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;

                #if NORDIG_FUNC //for Nordig spec v2.0
                case EN_Time_OnTimer_Source_DTMB_DATA:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DTMB));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Data));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;
                #endif
            #endif

            #if ENABLE_ISDBT
                case EN_Time_OnTimer_Source_ISDBT:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Air));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;

                case EN_Time_OnTimer_Source_ISDBT_RADIO:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Radio));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;

                #if NORDIG_FUNC //for Nordig spec v2.0
                case EN_Time_OnTimer_Source_ISDBT_DATA:
                    {
                        U16 curStringLen = 0;
                        U16 u16StrBuf[32];
                        MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_ISDB));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = CHAR_SPACE;
                        curStringLen +=1;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Data));
                        curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                        u16StrBuf[curStringLen] = 0;
                        MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                        return (LPTSTR) CHAR_BUFFER;
                    }
                    break;
                #endif
            #endif

                #if (INPUT_SCART_VIDEO_COUNT >= 1)
                case EN_Time_OnTimer_Source_SCART:
                    u16TempID = en_str_SCART;
                    if(INPUT_SCART_VIDEO_COUNT >= 2)
                        u16TempID = en_str_SCART_1;
                    break;
                #endif

                #if (INPUT_SCART_VIDEO_COUNT >= 2)
                case EN_Time_OnTimer_Source_SCART2:
                    u16TempID = en_str_SCART_2;
                    break;
                #endif

                #if (INPUT_YPBPR_VIDEO_COUNT>=1)
                case EN_Time_OnTimer_Source_COMPONENT:
                    u16TempID = en_str_Component;
                    break;
                #endif

                #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
                case EN_Time_OnTimer_Source_COMPONENT2:
                    u16TempID = en_str_Component;//xxx need creat string
                    break;
                #endif

                case EN_Time_OnTimer_Source_RGB:
                    u16TempID = en_str_PCdashRGB;
                    break;

                #if (INPUT_HDMI_VIDEO_COUNT >= 1)
                case EN_Time_OnTimer_Source_HDMI:
                    u16TempID = en_str_HDMI;
                    if(INPUT_HDMI_VIDEO_COUNT >= 2)
                        u16TempID = en_str_HDMI1;
                    break;
                #endif

                #if (INPUT_HDMI_VIDEO_COUNT >= 2)
                case EN_Time_OnTimer_Source_HDMI2:
                    u16TempID = en_str_HDMI2;
                    break;
                #endif

                #if (INPUT_HDMI_VIDEO_COUNT >= 3)
                case EN_Time_OnTimer_Source_HDMI3:
                    u16TempID = en_str_HDMI3;
                    break;
                #endif

                #if (INPUT_HDMI_VIDEO_COUNT >= 4)
                case EN_Time_OnTimer_Source_HDMI4:
                    u16TempID = en_str_HDMI4;
                    break;
                #endif

                #if (INPUT_AV_VIDEO_COUNT >= 1)
                case EN_Time_OnTimer_Source_AV:
                    u16TempID = en_str_AV;
                    if(INPUT_AV_VIDEO_COUNT >= 2)
                        u16TempID = en_str_AV_1;
                    break;
                #endif

                #if (INPUT_AV_VIDEO_COUNT >= 2)
                case EN_Time_OnTimer_Source_AV2:
                    u16TempID = en_str_AV_2;
                    break;
                #endif

                #if (INPUT_AV_VIDEO_COUNT >= 3)
                case EN_Time_OnTimer_Source_AV3:
                    u16TempID = en_str_AV_3;
                    break;
                #endif

                #if (INPUT_SV_VIDEO_COUNT >= 1)
                case EN_Time_OnTimer_Source_SVIDEO:
                    u16TempID = en_str_SdashVideo;
                    if(INPUT_SV_VIDEO_COUNT >= 2)
                        u16TempID = en_str_SdashVideo_1;
                    break;
                #endif

                #if (INPUT_SV_VIDEO_COUNT >= 2)
                case EN_Time_OnTimer_Source_SVIDEO2:
                    u16TempID = en_str_SdashVideo_2;
                    break;
                #endif

                #if ENABLE_DMP
                    case EN_Time_OnTimer_Source_MPLAYER:
                        u16TempID = en_str_DMP;
                        break;
                  //  case EN_Time_OnTimer_Source_DLNA: //must
                   //     u16TempID = en_str_DLNA;
                   //     break;
                #endif

                #if ENABLE_S2
                    case EN_Time_OnTimer_Source_S2:
                        u16TempID = en_str_DVBdashS2;
                        break;

                    case EN_Time_OnTimer_Source_S2_RADIO:
                        {
                            U16 curStringLen = 0;
                            U16 u16StrBuf[32];
                            MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DVBdashS2));
                            curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                            u16StrBuf[curStringLen] = CHAR_SPACE;
                            curStringLen +=1;
                            MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Radio));
                            curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                            u16StrBuf[curStringLen] = 0;
                            MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                            return (LPTSTR) CHAR_BUFFER;
                        }
                        break;

                    #if NORDIG_FUNC //for Nordig spec v2.0
                    case EN_Time_OnTimer_Source_S2_DATA:
                        {
                            U16 curStringLen = 0;
                            U16 u16StrBuf[32];
                            MApp_ZUI_API_Strcpy(&u16StrBuf[0], MApp_ZUI_API_GetString(en_str_DVBdashS2));
                            curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                            u16StrBuf[curStringLen] = CHAR_SPACE;
                            curStringLen +=1;
                            MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(en_str_Data));
                            curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                            u16StrBuf[curStringLen] = 0;
                            MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                            return (LPTSTR) CHAR_BUFFER;
                        }
                        break;
                    #endif
                #endif

                default:
                    u16TempID=en_str_dashdash;
                    break;
            }
            break;
            /*MApp_ZUI_API_Strcat(ptr,(U16*)SourcePtr);
            u16Len = MApp_ZUI_API_Strlen(SourcePtr);
            SourcePtr[u16Len++] = 0;
            */
                //return SourcePtr;
        }

        case HWND_MENU_COMMON_ADJ_ITEM5_OPTION://HWND_MENU_TIME_ONTIME_CHANNEL_OPTION:
        {
#if ENABLE_DVB
            U16 u16Number;//, len;
#endif
            U16 u16Len = 0;
            LPTSTR ChannelPtr = MApp_ZUI_API_GetString(en_str_Channel);
            u16Len = MApp_ZUI_API_Strlen(ChannelPtr);
            ChannelPtr[u16Len++] = CHAR_SPACE;
            ChannelPtr[u16Len] = 0;
            //printf("u16Len=%u\n", u16Len);
            switch (stGenSetting.g_Time.cOnTimerSourceFlag)
            {
        #if ENABLE_DTV
            #if ENABLE_ATSC
                case EN_Time_OnTimer_Source_ATSC:
                    MApp_UiMenuFunc_ConvertProgramNumber2Str(&MApp_ChanProc_GetChannelPointer(VIR_CH_IDX(stGenSetting.g_Time.cOnTimerChannel))->stVirtualChNum, au8Section);
                    MApp_ZUI_API_StringBuffU8toU16(ChannelPtr+u16Len, au8Section, strlen((char *)au8Section));
                    return ChannelPtr;
            #endif

            #if ENABLE_DVB
            #if ENABLE_DVBT
                case EN_Time_OnTimer_Source_DVBT:
            #endif
            #if ENABLE_DVBC
                case EN_Time_OnTimer_Source_DVBC:
            #endif
            #if ENABLE_DTMB
                case EN_Time_OnTimer_Source_DTMB:
            #endif
            #if ENABLE_ISDBT
                case EN_Time_OnTimer_Source_ISDBT:
            #endif
                    u16Number = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel);
                    if(u16Number == INVALID_LOGICAL_CHANNEL_NUMBER)
                    {
                        printf("\nWarning: No DTV channel\n");
                        ChannelPtr[u16Len++] = '-';
                        ChannelPtr[u16Len++] = '-';
                        ChannelPtr[u16Len] = 0;
                        return ChannelPtr;
                    }
                    else
                    {
                        LPTSTR str = ChannelPtr+u16Len;
                        MApp_ZUI_DTV_ChNumString(u16Number, str);
                     }
                     return ChannelPtr;
                     break;

            #if ENABLE_DVBT
                case EN_Time_OnTimer_Source_DVBT_RADIO:
            #endif
            #if ENABLE_DVBC
                case EN_Time_OnTimer_Source_DVBC_RADIO:
            #endif
            #if ENABLE_DTMB
                case EN_Time_OnTimer_Source_DTMB_RADIO:
            #endif
            #if ENABLE_ISDBT
                case EN_Time_OnTimer_Source_ISDBT_RADIO:
            #endif
                    u16Number = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_RADIO, stGenSetting.g_Time.cOnTimerChannel);
                    if(u16Number == INVALID_LOGICAL_CHANNEL_NUMBER)
                    {
                        printf("\nWarning: No Radio channel\n");
                        ChannelPtr[u16Len++] = '-';
                        ChannelPtr[u16Len++] = '-';
                        ChannelPtr[u16Len] = 0;
                        return ChannelPtr;
                    }
                    else
                    {
                        LPTSTR str = ChannelPtr+u16Len;
                        MApp_ZUI_DTV_ChNumString(u16Number, str);
                    }
                    return ChannelPtr;
                    break;

            #if NORDIG_FUNC //for Nordig spec v2.0
            #if ENABLE_DVBT
                case EN_Time_OnTimer_Source_DVBT_DATA:
            #endif
            #if ENABLE_DVBC
                case EN_Time_OnTimer_Source_DVBC_DATA:
            #endif
            #if ENABLE_DTMB
                case EN_Time_OnTimer_Source_DTMB_DATA:
            #endif
            #if ENABLE_ISDBT
                case EN_Time_OnTimer_Source_ISDBT_DATA:
            #endif
                    u16Number = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DATA, stGenSetting.g_Time.cOnTimerChannel);
                    if(u16Number == INVALID_LOGICAL_CHANNEL_NUMBER)
                    {
                        printf("\nWarning: No Data channel\n");
                        ChannelPtr[u16Len++] = '-';
                        ChannelPtr[u16Len++] = '-';
                        ChannelPtr[u16Len] = 0;
                        return ChannelPtr;
                    }
                    else
                        __MApp_UlongToString(u16Number, ChannelPtr, MApp_GetNoOfDigit(u16Number));
                    return ChannelPtr;
                    break;
            #endif
            #endif // ENABLE_DVB
        #endif
            #if ENABLE_S2
                case EN_Time_OnTimer_Source_S2:
                    u16Number = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV, stGenSetting.g_Time.cOnTimerChannel);
                    if (u16Number == INVALID_LOGICAL_CHANNEL_NUMBER)
                    {
                    __MApp_UlongToString(0, ChannelPtr+u16Len, 1);
                    }
                    else
                    {
                        LPTSTR str = ChannelPtr+u16Len;
                        MApp_ZUI_DTV_ChNumString(u16Number, str);
                    }
                    return ChannelPtr;
                    break;
            #endif

            #if (!ENABLE_ATSC)
                case EN_Time_OnTimer_Source_ATV:
                    __MApp_UlongToString((stGenSetting.g_Time.cOnTimerChannel+1/*for OSD show 1~x*/), ChannelPtr+u16Len, 2);
                    return ChannelPtr;

                    break;
            #endif


                default:
                    u16TempID=en_str_dashdash;
            }
            break;
        }

        case HWND_MENU_COMMON_ADJ_ITEM6_OPTION://HWND_MENU_TIME_ONTIME_VOLUME_OPTION:
        {
            U16 u16Len = 0;
            LPTSTR ptr = MApp_ZUI_API_GetString(en_str_Volume);

            // Added it by coverity_0537
            if (ptr == NULL)
            {
                u16TempID=en_str_dashdash;
                break;
            }

            u16Len = MApp_ZUI_API_Strlen(ptr);
            ptr[u16Len++] = CHAR_SPACE;
            if(stGenSetting.g_Time.cOnTimerVolume<100)
                __MApp_UlongToString(stGenSetting.g_Time.cOnTimerVolume, ptr+u16Len, 2);
            else
                __MApp_UlongToString(stGenSetting.g_Time.cOnTimerVolume, ptr+u16Len, 3);

            return ptr;
        }
    }
    #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(OffTime != u16TempID)
        {
            printf("61_OnTime\n");
        }
        OffTime = u16TempID;
    }
    #endif

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....
}
void MApp_ZUI_ACT_GetTenKeyNum(U8 u8Key)
{
    U8 u8Num;
    //if( MApp_ZUI_API_GetFocus() == HWND_MENU_DLG_SET_CLOCK_YEAR)
    if(u8Key == KEY_UP || u8Key == KEY_DOWN)
    {
        MApp_ZUI_ACT_ResetTimeMenuTenKey();
        //printf("reset input value and digicount \n");
    }
    if(u8Key >= KEY_0 && u8Key <=KEY_9)
    {
        u8Num=u8Key-KEY_0;
        u16SetTimeInputValue %= 10000;
        u16SetTimeInputValue = u16SetTimeInputValue*10+u8Num;
        u8SetTimeDigitCount++;
        //printf("u8Num=%u DigitCount=%u InputValue=%u \n",u8Num,u8SetTimeDigitCount,u16SetTimeInputValue);
    }
}

#undef MAPP_ZUI_ACTSETCLOCKFUNC_C
