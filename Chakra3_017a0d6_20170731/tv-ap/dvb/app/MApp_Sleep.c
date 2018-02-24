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


/********************************************************************************/
/*                      Header Files                                            */
/********************************************************************************/
#include "MsCommon.h"
#include "hwreg.h"
#include "MApp_Key.h"
#include "drvpower_if.h"

#define MAPP_SLEEP_C

#include "MApp_TV.h"
#include "MApp_GlobalVar.h"
#include "MApp_PCMode.h"
#include "apiXC_PCMonitor.h"

#include "MApp_Sleep.h"
#include "msAPI_Timer.h"
#include "msAPI_Power.h"
#if 0//(NO_SIGNAL_AUTO_SHUTDOWN==1)
#include "MApp_SignalMonitor.h"
#include "MApp_VDMode.h"
#endif
#include "MApp_UiMenuDef.h"
#include "MApp_SaveData.h"

#include "MApp_GlobalFunction.h"
#include "MApp_GlobalSettingSt.h"
#if (ENABLE_TTX)
#include "mapp_ttx.h"
#endif
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"
#include "MApp_TopStateMachine.h"
#if ENABLE_DMP
#include "mapp_mplayer.h"
#include "MApp_UiMediaPlayer.h"
#endif
#include "MApp_ZUI_ACTcoexistWin.h"
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "MApp_Scan.h"
#endif

#if ENABLE_OAD
#include "MApp_OAD.h"
#endif

#include "msAPI_DrvInit.h"
#if ENABLE_CEC
#include "msAPI_CEC.h"
#endif

#if ENABLE_PIP
#include "MApp_PIP.h"
#endif

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#endif
#include "MApp_NoSignal_AutoSleep.h"

#if (ENABLE_ATSC)
#if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
#include "mapp_closedcaption.h"
#endif
#endif

//================================================
#define DEBUG_SLEEP_TIME(x)     //x


#define DEBUG_AUTO_SLEEP(x)         x


#define TH_SiganlStatusCheck_Count 50
/*static EN_SLEEP_TIME_STATE enSleepTimeState = STATE_SLEEP_OFF;*/

U32 u32ProtectOffTimer;
U32 u32OffTimeFreeze = 0;
BOOLEAN bSkipCountdown = TRUE;

#if (ENABLE_ATSC)
#if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
static BOOLEAN bStartCountDown;
#endif
#endif

static U8 const code au8SleepTimeCoef[STATE_SLEEP_TOTAL]= {0,1,2,3,6,9,12,18,24};
extern void MApp_ZUI_ACTcoexistWin_Init(void);
extern DWORD MApp_GetEpgManualTimerStartDate(void);

#if (ENABLE_NO_OPERATE_AUTO_SLEEP )
extern U32 MApp_NoOperateAutoSleep_Get_CountDownTime(void);
#endif

extern U32 MApp_CI_PowerDown_CountDownTime(void);
//=========================================================================

void MApp_Sleep_SetTime(void)
{
    DEBUG_SLEEP_TIME(printf("MApp_Sleep_SetTime()\n"););

    switch(++enSleepTimeState)
    {
        case STATE_SLEEP_TOTAL:
        case STATE_SLEEP_OFF:
                enSleepTimeState = STATE_SLEEP_OFF;
                benableSleepTimer=FALSE;
                u32SleepTimeDur=0;
                break;

        default:
                benableSleepTimer = TRUE;
                u32SleepTimeDur = (U32)SLEEP_TIMER_TIMEBASE*(U32)au8SleepTimeCoef[enSleepTimeState];

                u32SleepTimer = msAPI_Timer_GetTime0();
                DEBUG_SLEEP_TIME(printf("u32SleepTimeDur=%u\n",u32SleepTimeDur););
                DEBUG_SLEEP_TIME(printf("u32SleepTimer=%u\n",u32SleepTimer););

                //u32SleepTimeDur=(U32)65000*(U32)au8SleepTimeCoef[enSleepTimeState];
                //DEBUG_SLEEP_TIME(printf("u32SleepTimeDur=%u\n",u32SleepTimeDur););
                break;
    }
}
/*
BOOLEAN _MApp_Sleep_TurnOff_OtherOSD(BOOLEAN bPass)
{
    BOOLEAN bret = TRUE;

    #if ENABLE_TTX
        if(MApp_TTX_TeletextCommand(TTX_TV) != E_RESULT_FAILURE)//turn TTX OFF if need be
        {
            ;// the TTX will be turn off by MApp_TTX_TeletextCommand(TTX_TV)
        }
        else
    #endif
        if(0)// turn Subtitle OFF if need be
        {
            u8KeyCode = KEY_COUNTDOWN_EXIT_TT_SUBTITLE;
        }
        else if(0)// turn MHEG5 OFF if need be
        {
            ;
        }
        else if(0)// turn C.C OFF if need be
        {
            ;
        }
        else if(MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY && MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX)// Other OSD On
        {
            if (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER && (bPass || bSkipCountdown == FALSE))
            {
                MApp_ZUI_ACT_ShutdownOSD();
                SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
            }
            else
            if( MApp_ZUI_GetState() == E_ZUI_STATE_STANDBY
                || MApp_ZUI_GetState() == E_ZUI_STATE_RUNNING)
            {
                u8KeyCode = KEY_EXIT;
            }
        }
        else
            bret = FALSE;

        return bret;

}
*/

#if ENABLE_S2
extern BOOLEAN _DishSetup_HandleSatelliteOrTPListKey(VIRTUAL_KEY_CODE key);
#endif

void  MApp_Sleep_Monitor(void)
{
    if(benableSleepTimer)
    {
        U32 u32SleepTimerDiff = msAPI_Timer_DiffTimeFromNow(u32SleepTimer);

        DEBUG_SLEEP_TIME(printf("u32SleepTimerDiff=%u\n", u32SleepTimerDiff););

        if( u32SleepTimerDiff >= u32SleepTimeDur )
        {
            DEBUG_SLEEP_TIME(printf("sleep time is up: %u\n", (u32SleepTimerDiff-u32SleepTimeDur)););

            // < one minute
            if( (u32SleepTimerDiff-u32SleepTimeDur) < (60*1000) && (u32SleepTimerDiff-u32SleepTimeDur) > 0 )
            {
                DEBUG_SLEEP_TIME(printf("Over < 60\n"););
#if (ENABLE_ATSC)
#if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
                bStartCountDown = TRUE;
#endif
#endif
                if( MApp_ZUI_GetActiveOSD() == E_OSD_ATV_MANUAL_TUNING
                    || MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING
                    #if ENABLE_DTV
                    || MApp_ZUI_GetActiveOSD() == E_OSD_DTV_MANUAL_TUNING
                    #endif
                   )
                {
                    u32SleepTimer += 1000;
                    return;
                }

                #if ENABLE_DMP
                if(UI_INPUT_SOURCE_DMP == UI_INPUT_SOURCE_TYPE)
                {
                    if((u8CoexistWinType != COWIN_ID_COUNT_DOWN_WIN))
                    {
                        enIndicateTimerSource = TS_TYPE_SLEEPTIMER;
                        MApp_UiMenu_CountDownWin_Create();
                    }
                    else if(u8KeyCode != KEY_NULL)
                    {
                        MApp_ZUI_ACTcoexist_Delete();
                       if(msAPI_AUD_IsAudioMutedByUser()) //redraw MUTE icon after close CountDown OSD
                       {
                          MApp_UiMenu_MuteWin_Show();
                       }
                       //else
                         //MApp_ZUI_ACTcoexistWin_Init();

                        MApp_Sleep_ReleaseSleepTimer();
                        enSleepTimeState = STATE_SLEEP_OFF;
                        u8KeyCode = KEY_NULL;
                        enIndicateTimerSource = TS_TYPE_NONE;
						#if ENABLE_ATSC_TTS
							MApp_TTS_Say_Stop();
                        #endif
                    }
                    else if(u8CoexistWinType == COWIN_ID_COUNT_DOWN_WIN)
                    {
                        MApp_UiMenu_CountDownWin_Draw();
                    }
                }
                else
                #endif
                {
                     if(u8KeyCode != KEY_NULL)
                    {
                        MApp_Sleep_ReleaseSleepTimer();
                        enSleepTimeState = STATE_SLEEP_OFF;
                        u8KeyCode = KEY_NULL;
                        enIndicateTimerSource = TS_TYPE_NONE;
                        MApp_ZUI_ACT_ShutdownOSD();
#if (ENABLE_ATSC)
#if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
                        bStartCountDown = FALSE;
#endif
#endif
						#if ENABLE_ATSC_TTS
							MApp_TTS_Say_Stop();
                        #endif
                    }
                    else
                    {
                        if (MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX ||
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX) == FALSE)
                        {
                        #if ENABLE_S2
                            if(MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()) == HWND_MENU_DISHSETUP_SATLIST)
                            {
                                 _DishSetup_HandleSatelliteOrTPListKey(VK_EXIT);

                            }
			  			#endif
                            if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY)
                            {
                                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                            }
                            enIndicateTimerSource = TS_TYPE_SLEEPTIMER;
#if (ENABLE_ATSC)
  #if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
                            if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_INIT)
  #endif
#endif
                            {
                                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX);
                            }
                        }
                    }

                }

                return;
            }
            else if ((u32SleepTimerDiff-u32SleepTimeDur) >= 60*1000)
            {
                DEBUG_SLEEP_TIME(printf("Over >= 60\n"););
                u8KeyCode  = KEY_POWER;
                enIndicateTimerSource = TS_TYPE_NONE;
                return;
            }
        }
    }

    if (benableAutoOn_OffTimer)
    {
        if (msAPI_Timer_DiffTime((u32AutoOnTime+TIME_AUTO_OFF_AFTER_AUTO_ON), msAPI_Timer_GetTime0()) == 0) //unit = ms
        {
            u8KeyCode = KEY_POWER;

            return;
        }
    }

    if (!(g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET))
        return;

    if (benableOffTimer == STATE_SLEEP_OFFTIMER_TRANSIT)
    {
        U32 u32LocalOneDayTime = MApp_GetLocalSystemTime() % ONEDAY_TIME;

        if (u32LocalOneDayTime > u32OffTimeDur)
        {
            MApp_Sleep_SetOffTime(TRUE);
        }
        return;
    }
    else if((benableOffTimer == STATE_SLEEP_OFFTIMER_ON) && (MApp_OffTime_IsOffTimeInDayOfWeek() == TRUE))  //Off timer is this time & this day
    {
        U32 u32LocalOneDayTime;
        U32 u32OffTimerDiff;

        u32LocalOneDayTime = MApp_GetLocalSystemTime()% ONEDAY_TIME;

        if((u32OffTimeDur+u32OffTimeFreeze)< u32LocalOneDayTime) //the time already pass
        {
            if(u8CoexistWinType == COWIN_ID_COUNT_DOWN_WIN)
         {
                MApp_ZUI_ACTcoexist_Delete();
                MApp_ZUI_ACTcoexistWin_Init();
                if(msAPI_AUD_IsAudioMutedByUser()) //redraw MUTE icon after close CountDown OSD
                {
                   MApp_UiMenu_MuteWin_Show();
                }
        }
            return;
      }
        u32OffTimerDiff = msAPI_Timer_DiffTime(u32OffTimeDur+u32OffTimeFreeze, u32LocalOneDayTime);

        if(u32OffTimerDiff <= 60 && u32OffTimerDiff >0 && (bSkipCountdown == FALSE))
        {
            if( MApp_ZUI_GetActiveOSD() == E_OSD_ATV_MANUAL_TUNING
                || MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING
                #if ENABLE_DTV
                || MApp_ZUI_GetActiveOSD() == E_OSD_DTV_MANUAL_TUNING
                #endif
               )
            {
                u32OffTimeFreeze++;
                if(u32OffTimerDiff < 62)
                    u32OffTimeFreeze++;
                return;
            }



            #if ENABLE_DMP
            if(UI_INPUT_SOURCE_DMP == UI_INPUT_SOURCE_TYPE)
            {
                if((u8CoexistWinType != COWIN_ID_COUNT_DOWN_WIN))
                {
                    enIndicateTimerSource = TS_TYPE_OFFTIMER;
                    MApp_UiMenu_CountDownWin_Create();
                }
                else if(u8KeyCode != KEY_NULL)
                {
                    MApp_ZUI_ACTcoexist_Delete();
                    //MApp_ZUI_ACTcoexistWin_Init();
                    if(msAPI_AUD_IsAudioMutedByUser()) //redraw MUTE icon after close CountDown OSD
                    {
                       MApp_UiMenu_MuteWin_Show();
                    }
                    bSkipCountdown = TRUE;
                    u32OffTimeFreeze = 0;
                    u8KeyCode = KEY_NULL;
                    enIndicateTimerSource = TS_TYPE_NONE;
                    if(stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Once)
                    {
                        stGenSetting.g_Time.cOffTimerFlag = EN_Time_OffTimer_Off;
                        MApp_ZUI_API_InvalidateWindow(HWND_MENU_TIME_SET_OFFTIME_OPTION);
                    }
					#if ENABLE_ATSC_TTS
                        MApp_TTS_Say_Stop();
                    #endif
                }
                else if(u8CoexistWinType == COWIN_ID_COUNT_DOWN_WIN)
                {
                    MApp_UiMenu_CountDownWin_Draw();
                }
            }
            else
            #endif
            {
                if(u8KeyCode != KEY_NULL &&  u8KeyCode != 0x1b )
                {
                    bSkipCountdown = TRUE;
                    u32OffTimeFreeze = 0;
                    u8KeyCode = KEY_NULL;
                    enIndicateTimerSource = TS_TYPE_NONE;
                    MApp_ZUI_ACT_ShutdownOSD();
                    if(stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Once)
                    {
                        stGenSetting.g_Time.cOffTimerFlag = EN_Time_OffTimer_Off;
                    }
					#if ENABLE_ATSC_TTS
                        MApp_TTS_Say_Stop();
                    #endif
                }
                else
                {
                    if (MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX ||
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX) == FALSE)
                    {

                        if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY)
                        {
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                        }
                        enIndicateTimerSource = TS_TYPE_OFFTIMER;
                        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX);
                    }
                }
            }
            return;
        }
        else if(u32OffTimerDiff== 0 && bSkipCountdown == FALSE)
        {
            u8KeyCode  = KEY_POWER;
            enIndicateTimerSource = TS_TYPE_NONE;

            return;
        }
        else if(u32OffTimerDiff > 60)
        {
            bSkipCountdown = FALSE;
         if(u8CoexistWinType == COWIN_ID_COUNT_DOWN_WIN)
         {
             MApp_ZUI_ACTcoexist_Delete();
             MApp_ZUI_ACTcoexistWin_Init();
           if(msAPI_AUD_IsAudioMutedByUser()) //redraw MUTE icon after close CountDown OSD
           {
               MApp_UiMenu_MuteWin_Show();
           }
         }
        }
    }
}

void MApp_Sleep_ReleaseSleepTimer()
{
    DEBUG_SLEEP_TIME(printf("MApp_Sleep_ReleaseSleepTimer()\n"););

#if 0//(NO_SIGNAL_AUTO_SHUTDOWN==1)
    benableNoSiganlSleepCheck = FALSE;
#endif
    enSleepTimeState = STATE_SLEEP_OFF;
    benableSleepTimer=FALSE;
}

U32 MApp_Sleep_DisplayCountDownTimer()
{
    if(enIndicateTimerSource == TS_TYPE_SLEEPTIMER)
    {
        U32 u32SleepTimerDiff = msAPI_Timer_DiffTime(u32SleepTimer+u32SleepTimeDur, msAPI_Timer_GetTime0());
        return (60-(u32SleepTimerDiff/1000));
    }
    else if(enIndicateTimerSource  == TS_TYPE_OFFTIMER )
    {
        U32 u32LocalOneDayTime = MApp_GetLocalSystemTime()%ONEDAY_TIME;
        U32 u32OffTimerDiff = msAPI_Timer_DiffTime(u32OffTimeDur+u32OffTimeFreeze, u32LocalOneDayTime);
        return u32OffTimerDiff;
    }
#if ( NO_SIGNAL_AUTO_SHUTDOWN )
    else if(enIndicateTimerSource == TS_TYPE_SLEEPTIMER_NOSIGNAL)
    {
        U32 u32SleepTimerNoSignalDiff = MApp_NoSignalAutoSleep_Get_CountDownTime();
        return u32SleepTimerNoSignalDiff/1000;
    }
#endif
#if (ENABLE_NO_OPERATE_AUTO_SLEEP )
    else if(enIndicateTimerSource == TS_TYPE_AUTOSLEEP_OFFTIMER)
    {
        return MApp_NoOperateAutoSleep_Get_CountDownTime()/1000;
    }
#endif
#if ( ENABLE_CI_PLUS_V1_4 )
    else
    {
        return MApp_CI_PowerDown_CountDownTime()/1000;
    }
#endif  //ENABLE_CI_PLUS_V1_4

    return 0;
}

EN_SLEEP_TIME_STATE MApp_Sleep_GetCurrentSleepState()
{
    return enSleepTimeState;
}

void MApp_Sleep_SetCurrentSleepTime(U8 CurrentSleepTime)
{
    DEBUG_SLEEP_TIME(printf("MApp_Sleep_SetCurrentSleepTime(CurrentSleepTime=%u)\n", CurrentSleepTime););

    enSleepTimeState =(EN_SLEEP_TIME_STATE)(CurrentSleepTime -1);
    MApp_Sleep_SetTime();
}

U32 MApp_Sleep_GetSleepTimeRemainTime(void)
{
    U32 TimeRemain;
    U32 tmpTime;
    tmpTime = msAPI_Timer_GetTime0();

    if (tmpTime >= u32SleepTimer+u32SleepTimeDur)
        TimeRemain = 1;
    else
        TimeRemain=msAPI_Timer_DiffTime(u32SleepTimer+u32SleepTimeDur,tmpTime);

    if((TimeRemain%MINUTE_TO_MS)==0)
    {
        return (TimeRemain/MINUTE_TO_MS);
    }
    else
    {
        return (TimeRemain/MINUTE_TO_MS)+1;
    }
}

void MApp_Time_SetOnTime(void)
{
    ST_TIME _stTime;

    if (stGenSetting.g_Time.cOnTimerFlag == EN_Time_OnTimer_Off)
    {
        gWakeupSystemTime = 0xFFFFFFFF;
    }
    else
    {
        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
        _stTime.u8Hour = (U8)stGenSetting.g_Time.u16OnTimer_Info_Hour;
        _stTime.u8Min = (U8)stGenSetting.g_Time.u16OnTimer_Info_Min;
        _stTime.u8Sec = 0;
        MApp_SetLocalWakeUpTime(MApp_ConvertStTime2Seconds(&_stTime));
    }
    //*******************************************************
}

U32 MApp_OnTime_GetNextWakeUpTime(void)
{
    ST_TIME _stTime;
    DAYOFWEEK _Today = SUN;
    U32 _u32NextDay = 0;
    U32 OnTime;

    if(stGenSetting.g_Time.cOnTimerFlag == EN_Time_OnTimer_Off)
    {
        return 0;
    }
    else
    {
        MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);

        _Today = (DAYOFWEEK)MApp_GetDayOfWeek(_stTime.u16Year, _stTime.u8Month, _stTime.u8Day);
        _stTime.u8Hour = (U8)stGenSetting.g_Time.u16OnTimer_Info_Hour;
        _stTime.u8Min = (U8)stGenSetting.g_Time.u16OnTimer_Info_Min;
        _stTime.u8Sec = 0;
        OnTime = MApp_ConvertStTime2Seconds(&_stTime);

        if(OnTime < MApp_GetLocalSystemTime()) //the time pass, find next day
        {
            switch(stGenSetting.g_Time.cOnTimerFlag)
            {
                default :
                case EN_Time_OnTimer_Off:
                    return 0;

                case EN_Time_OnTimer_Once:
                case EN_Time_OnTimer_Everyday:
                    _u32NextDay = SECONDS_PER_DAY;
                    break;

                case EN_Time_OnTimer_Mon2Fri:
                    switch(_Today)
                    {
                        case FRI:
                            _u32NextDay += SECONDS_PER_DAY*3; break;
                        case SAT:
                            _u32NextDay += SECONDS_PER_DAY*2; break;
                        default:
                            _u32NextDay += SECONDS_PER_DAY; break;
                    }
                    break;

                case EN_Time_OnTimer_Mon2Sat:
                    switch(_Today)
                    {
                        case SAT:
                            _u32NextDay += SECONDS_PER_DAY*2; break;
                        default:
                            _u32NextDay += SECONDS_PER_DAY; break;
                    }
                    break;

                case EN_Time_OnTimer_Sat2Sun:
                    switch(_Today)
                    {
                        case SUN: _u32NextDay += SECONDS_PER_DAY*6; break;
                        case MON: _u32NextDay += SECONDS_PER_DAY*5; break;
                        case TUE: _u32NextDay += SECONDS_PER_DAY*4; break;
                        case WED: _u32NextDay += SECONDS_PER_DAY*3; break;
                        case THU: _u32NextDay += SECONDS_PER_DAY*2; break;
                        case FRI:
                        case SAT:
                                  _u32NextDay += SECONDS_PER_DAY; break;
                        default: break;
                    }
                    break;

                case EN_Time_OnTimer_Sun:
                    switch(_Today)
                    {
                        case SUN: _u32NextDay += SECONDS_PER_DAY*7; break;
                        case MON: _u32NextDay += SECONDS_PER_DAY*6; break;
                        case TUE: _u32NextDay += SECONDS_PER_DAY*5; break;
                        case WED: _u32NextDay += SECONDS_PER_DAY*4; break;
                        case THU: _u32NextDay += SECONDS_PER_DAY*3; break;
                        case FRI: _u32NextDay += SECONDS_PER_DAY*2; break;
                        case SAT: _u32NextDay += SECONDS_PER_DAY;   break;
                        default: break;
                    }
                    break;
            }
        }
        else
        {
            switch(stGenSetting.g_Time.cOnTimerFlag)
            {
                default :
                case EN_Time_OnTimer_Off:
                    return 0;

                case EN_Time_OnTimer_Once:
                case EN_Time_OnTimer_Everyday:
                    _u32NextDay = 0;
                    break;

                case EN_Time_OnTimer_Mon2Fri:
                    switch(_Today)
                    {
                        case SAT:   _u32NextDay += SECONDS_PER_DAY*2; break;
                        case SUN:   _u32NextDay += SECONDS_PER_DAY; break;
                        default:
                            break;
                    }
                    break;

                case EN_Time_OnTimer_Mon2Sat:
                        if(_Today == SUN)
                            _u32NextDay += SECONDS_PER_DAY;
                        break;

                case EN_Time_OnTimer_Sat2Sun:
                        switch(_Today)
                        {
                          #if 0
                            case MON:   _u32NextDay += SECONDS_PER_DAY*5;
                            case TUE:   _u32NextDay += SECONDS_PER_DAY*4;
                            case WED:   _u32NextDay += SECONDS_PER_DAY*3;
                            case THU:   _u32NextDay += SECONDS_PER_DAY*2;
                            case FRI:   _u32NextDay += SECONDS_PER_DAY;
                          #else // Modified by coverity_0612
                            case MON:   _u32NextDay += SECONDS_PER_DAY*5; break;
                            case TUE:   _u32NextDay += SECONDS_PER_DAY*4; break;
                            case WED:   _u32NextDay += SECONDS_PER_DAY*3; break;
                            case THU:   _u32NextDay += SECONDS_PER_DAY*2; break;
                            case FRI:   _u32NextDay += SECONDS_PER_DAY; break;
                          #endif

                            default:
                                break;
                        }
                        break;

                case EN_Time_OnTimer_Sun:
                        switch(_Today)
                        {
                            case MON:   _u32NextDay += SECONDS_PER_DAY*6; break;
                            case TUE:   _u32NextDay += SECONDS_PER_DAY*5; break;
                            case WED:   _u32NextDay += SECONDS_PER_DAY*4; break;
                            case THU:   _u32NextDay += SECONDS_PER_DAY*3; break;
                            case FRI:   _u32NextDay += SECONDS_PER_DAY*2; break;
                            case SAT:   _u32NextDay += SECONDS_PER_DAY; break;
                            default:
                                        break;
                        }
                        break;
            }
        }
        return (OnTime+_u32NextDay);
    }
}

//************************************************************
// patameter : bEnable
//             0: disable timer
//             1: set timer by stGenSetting.g_Time
//************************************************************
void MApp_Sleep_SetOffTime(BOOLEAN bEnable)
{
    U8 u8Hour, u8Min;


    DEBUG_SLEEP_TIME(printf("MApp_Sleep_SetOffTime(bEnable=%u)\n", bEnable););


    if(bEnable == FALSE)
    {
        benableOffTimer = STATE_SLEEP_OFFTIMER_OFF;
        return;
    }

    if (stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Off)
    {
        benableOffTimer = STATE_SLEEP_OFFTIMER_OFF;
    }
    else
    {
        benableOffTimer = STATE_SLEEP_OFFTIMER_ON;
    }

    u8Hour = stGenSetting.g_Time.u16OffTimer_Info_Hour;
    u8Min = stGenSetting.g_Time.u16OffTimer_Info_Min;
    if((u8Hour == 0)&&(u8Min == 0))
    {
        u32OffTimeDur = ONEDAY_TIME - 1;;
    }
    else
    {
        u32OffTimeDur = ((U32)u8Hour*60 + u8Min) * MINUTE_TO_S;
    }

    DEBUG_SLEEP_TIME(printf("u32OffTimeDur=%u\n", u32OffTimeDur););

    bSkipCountdown = FALSE;
}

void MApp_Sleep_TransitOffTime(void)
{

    if(stGenSetting.g_Time.cOffTimerFlag == EN_Time_OffTimer_Once)
    {
        stGenSetting.g_Time.cOffTimerFlag = EN_Time_OffTimer_Off;
        benableOffTimer= STATE_SLEEP_OFFTIMER_OFF;
    }
    else
    {
        benableOffTimer = STATE_SLEEP_OFFTIMER_TRANSIT;
    }
}

void MApp_Sleep_SetAutoOn_OffTime(BOOLEAN bEnable)
{
    if(bEnable)
    {
        benableAutoOn_OffTimer = TRUE;
        u32AutoOnTime =msAPI_Timer_GetTime0();
    }
    else
    {
        benableAutoOn_OffTimer = FALSE;
    }
}

U8 MApp_GetSleepIndexTime(EN_SLEEP_TIME_STATE SleepIndex)
{
    return au8SleepTimeCoef[SleepIndex] * 10;
}

EN_SLEEP_TIME_STATE MApp_GetCurSleepTime(BOOLEAN bDecInc)
{
    EN_SLEEP_TIME_STATE i;
    U8 TimeRemain;

    if(MApp_Sleep_GetCurrentSleepState() != STATE_SLEEP_OFF)
    {
        TimeRemain = MApp_Sleep_GetSleepTimeRemainTime();

        for(i = STATE_SLEEP_OFF; i < STATE_SLEEP_TOTAL; i++)
        {
            if(TimeRemain <= (au8SleepTimeCoef[i] * 10))
            {
                if((TimeRemain < (au8SleepTimeCoef[i] * 10)) && (i>0) && bDecInc)
                    i--;

                return (i);
            }
        }
    }
    else
        return STATE_SLEEP_OFF;

    return STATE_SLEEP_240MIN;

}

#if 0 //non-used
void MApp_Timer_SetElapsedTimer(void)
{
    //printf("g_u16ElapsedTimeSecond %u\n", g_u16ElapsedTimeSecond );
    // TODO:
}
#endif

BOOLEAN MApp_OffTime_IsOffTimeInDayOfWeek(void)
{
    ST_TIME _stTime;
    DAYOFWEEK eDayOfWeek;

    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
    eDayOfWeek = (DAYOFWEEK)MApp_GetDayOfWeek(_stTime.u16Year, _stTime.u8Month, _stTime.u8Day);

    switch( stGenSetting.g_Time.cOffTimerFlag)
    {
        case EN_Time_OffTimer_Once:
        case EN_Time_OffTimer_Everyday:
        return TRUE;
        case EN_Time_OffTimer_Mon2Fri:
            if(eDayOfWeek > SUN && eDayOfWeek <= FRI)
        return TRUE;
        break;
        case EN_Time_OffTimer_Mon2Sat:
            if(eDayOfWeek >= MON && eDayOfWeek <= SAT)
        return TRUE;
        break;
        case EN_Time_OffTimer_Sat2Sun:
            if( eDayOfWeek == SAT || eDayOfWeek == SUN )
        return TRUE;
         break;
        case EN_Time_OffTimer_Sun:
            if( eDayOfWeek == SUN )
        return TRUE;
         break;
        default:
        return FALSE;
    }
    return FALSE;
}

void MApp_Sleep_SendKeyOffTimeDayOfWeek(void)
{
    ST_TIME _stTime;
    DAYOFWEEK eDayOfWeek;

    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(),&_stTime);
    eDayOfWeek = (DAYOFWEEK)MApp_GetDayOfWeek(_stTime.u16Year, _stTime.u8Month, _stTime.u8Day);

    switch( stGenSetting.g_Time.cOffTimerFlag)
    {
    case EN_Time_OffTimer_Once:
        MApp_Sleep_SetOffTime(FALSE);
        stGenSetting.g_Time.cOffTimerFlag = EN_Time_OffTimer_Off;
        benableOffTimer = STATE_SLEEP_OFFTIMER_OFF;
        u32OffTimeDur = 0xffffffff;
        u8KeyCode = KEY_POWER;
        break;

    case EN_Time_OffTimer_Everyday:
        u32OffTimeDur = 0xffffffff;
        u8KeyCode = KEY_POWER;
        break;

    case EN_Time_OffTimer_Mon2Fri:
        if(eDayOfWeek > SUN && eDayOfWeek <= FRI)
        {
            u32OffTimeDur = 0xffffffff;
            u8KeyCode = KEY_POWER;
        }
        break;

    case EN_Time_OffTimer_Mon2Sat:
        if(eDayOfWeek >= MON && eDayOfWeek <= SAT)
        {
            u32OffTimeDur = 0xffffffff;
            u8KeyCode = KEY_POWER;
        }
        break;

    case EN_Time_OffTimer_Sat2Sun:
        if( eDayOfWeek == SAT || eDayOfWeek == SUN )
        {
            u32OffTimeDur = 0xffffffff;
            u8KeyCode = KEY_POWER;
        }
        break;

    case EN_Time_OffTimer_Sun:
        if( eDayOfWeek == SUN )
        {
            u32OffTimeDur = 0xffffffff;
            u8KeyCode = KEY_POWER;
        }
        break;

    default:
        break;
    }
}

#if( ENABLE_DTV_EPG )
static int MApp_TimeCompare(const void *a,const void *b)
{
    if (*(U32*)a<*(U32*)b)
    {
        return -1;
    }
    else if (*(U32*)a==*(U32*)b)
    {
        return 0 ;
    }
    else
    {
        return 1 ;
    }
}
#endif

void MApp_InitRtcWakeUpTimer(void)
{
    DEBUG_WAKE_UP( printf("MApp_InitRtcWakeUpTimer()\n"); );

#if ((ENABLE_DTV_EPG) )//ENABLE_DTV

    #if(ENABLE_OAD)
    #define ARRAYSIZE 3
    #else
    #define ARRAYSIZE 2
    #endif
    U32 RTCtimer,timeArray[ARRAYSIZE],j;

    memset(&timeArray[0], 0x00, ARRAYSIZE * sizeof(U32));
    timeArray[0] = MApp_GetEpgManualTimerStartDate();
    timeArray[1] = MApp_OnTime_GetNextWakeUpTime();
#if(ENABLE_OAD)
    if(MApp_OAD_GetScheduleStart()>0)
    {
        timeArray[2] = MApp_OAD_GetScheduleStart()+msAPI_Timer_GetOffsetTime();
    }
#endif

    for (j=0;j<ARRAYSIZE;j++)
    {
        printf("timeArray[%d] = 0x%X\n", j, timeArray[j]);
    }
    qsort(timeArray,ARRAYSIZE,4,MApp_TimeCompare) ;

    RTCtimer = 0 ;

    for (j=0;j<ARRAYSIZE;j++)
    {
       if (timeArray[j]>0)
       {
          RTCtimer = timeArray[j] ;
		#if(ENABLE_OAD)
          if(RTCtimer == (MApp_OAD_GetScheduleStart()+msAPI_Timer_GetOffsetTime()))//OAD
          {
              ST_TIME stStartTime;
              ST_TIME stCurTime;
              //msAPI_BLoader_SetUpdatedStatus(msAPI_BLoader_GetUpdatedStatus()|0x02);
              MApp_ConvertSeconds2StTime(RTCtimer, &stStartTime );
			  MApp_ConvertSeconds2StTime(msAPI_Timer_GetSystemTime(), &stCurTime );
			  printf(">>>>>> Current system time %04d:%02d:%02d	%02d:%02d:%02d\n",stCurTime.u16Year,stCurTime.u8Month,stCurTime.u8Day,stCurTime.u8Hour,stCurTime.u8Min,stCurTime.u8Sec);
			  printf(">>>>>> Schedule start time %04d:%02d:%02d  %02d:%02d:%02d\n",stStartTime.u16Year,stStartTime.u8Month,stStartTime.u8Day,stStartTime.u8Hour,stStartTime.u8Min,stStartTime.u8Sec);
          }
		#endif
          break ;
       }
    }

    if(RTCtimer > 0)
    {
        MApp_SetLocalWakeUpTime(RTCtimer);
        msAPI_Timer_EnableRTCWakeUp(TRUE);
    }
    else
        msAPI_Timer_EnableRTCWakeUp(FALSE);

#else
    U32 RTCtimer = MApp_OnTime_GetNextWakeUpTime();
    if(RTCtimer > 0)
    {
        MApp_SetLocalWakeUpTime(RTCtimer);
        msAPI_Timer_EnableRTCWakeUp(TRUE);
    }
    else
        msAPI_Timer_EnableRTCWakeUp(FALSE);
#endif
}


void MApp_Time_Tasks_Set_RTC_NextWakeUpTime(void)
{
    ST_TIME _stTime;
    DAYOFWEEK _Today = SUN;
    U32 _u32NextDay = 0;
    BOOLEAN _bEnableWakeUp = TRUE;
    U32 u32LocalSystemTime;
    U32 u32LocalWakeUpTime;


    if (stGenSetting.g_Time.cOnTimerFlag != EN_Time_OnTimer_Off)
    {
        u32LocalSystemTime = MApp_GetLocalSystemTime();
        u32LocalWakeUpTime = MApp_GetLocalWakeUpTime();

        MApp_ConvertSeconds2StTime(u32LocalSystemTime,&_stTime);

        _Today = (DAYOFWEEK)MApp_GetDayOfWeek(_stTime.u16Year, _stTime.u8Month, _stTime.u8Day);
        _stTime.u8Hour = (U8)stGenSetting.g_Time.u16OnTimer_Info_Hour;
        _stTime.u8Min = (U8)stGenSetting.g_Time.u16OnTimer_Info_Min;
        _stTime.u8Sec = 0;

        if( u32LocalWakeUpTime < u32LocalSystemTime )
        {
            switch(stGenSetting.g_Time.cOnTimerFlag)
            {
                default :
                case EN_Time_OnTimer_Off:
                        _bEnableWakeUp = FALSE;
                        break;

                case EN_Time_OnTimer_Once:
                case EN_Time_OnTimer_Everyday:
                        _u32NextDay = SECONDS_PER_DAY;
                        break;

                case EN_Time_OnTimer_Mon2Fri:
                        switch(_Today)
                        {
                            case FRI: _u32NextDay += SECONDS_PER_DAY;
                            case SAT: _u32NextDay += SECONDS_PER_DAY;
                            default:
                                      _u32NextDay += SECONDS_PER_DAY;
                                    break;
                        }
                        break;

                case EN_Time_OnTimer_Mon2Sat:
                        switch(_Today)
                        {
                            case SAT: _u32NextDay += SECONDS_PER_DAY;
                            default:
                                      _u32NextDay += SECONDS_PER_DAY;
                                    break;
                        }
                        break;

                case EN_Time_OnTimer_Sat2Sun:
                        switch(_Today)
                        {
                            case SUN: _u32NextDay += SECONDS_PER_DAY;
                            case MON: _u32NextDay += SECONDS_PER_DAY;
                            case TUE: _u32NextDay += SECONDS_PER_DAY;
                            case WED: _u32NextDay += SECONDS_PER_DAY;
                            case THU: _u32NextDay += SECONDS_PER_DAY;
                            case FRI:
                            case SAT:
                                      _u32NextDay += SECONDS_PER_DAY;
                            default:
                                    break;
                        }
                        break;

                case EN_Time_OnTimer_Sun:
                        switch(_Today)
                        {
                            case SUN: _u32NextDay += SECONDS_PER_DAY;
                            case MON: _u32NextDay += SECONDS_PER_DAY;
                            case TUE: _u32NextDay += SECONDS_PER_DAY;
                            case WED: _u32NextDay += SECONDS_PER_DAY;
                            case THU: _u32NextDay += SECONDS_PER_DAY;
                            case FRI: _u32NextDay += SECONDS_PER_DAY;
                            case SAT: _u32NextDay += SECONDS_PER_DAY;
                            default:
                                    break;
                        }
                        break;
            }
            if (_u32NextDay != 0 )
            {
                DEBUG_WAKE_UP( printf("u32LocalSystemTime = %u\n", u32LocalSystemTime); );
                DEBUG_WAKE_UP( printf("u32LocalWakeUpTime = %u\n", u32LocalWakeUpTime); );

                MApp_SetLocalWakeUpTime(MApp_ConvertStTime2Seconds(&_stTime)+_u32NextDay);
                msAPI_Timer_EnableRTCWakeUp(_bEnableWakeUp);
            }
        }

        if( u32LocalWakeUpTime > u32LocalSystemTime )
        {
            _u32NextDay = 0;

            switch(stGenSetting.g_Time.cOnTimerFlag)
            {
                default :
                case EN_Time_OnTimer_Off:
                        _bEnableWakeUp = FALSE;
                        break;

                case EN_Time_OnTimer_Once:
                        break;

                case EN_Time_OnTimer_Everyday:
                        break;

                case EN_Time_OnTimer_Mon2Fri:
                        switch(_Today)
                        {
                            case SAT:   _u32NextDay += SECONDS_PER_DAY;
                            case SUN:   _u32NextDay += SECONDS_PER_DAY;
                            default:
                                        break;
                        }
                        break;

                case EN_Time_OnTimer_Mon2Sat:
                        if (_Today == SUN)
                        {
                            _u32NextDay += SECONDS_PER_DAY;
                        }
                        break;

                case EN_Time_OnTimer_Sat2Sun:
                        switch(_Today)
                        {
                            case MON:   _u32NextDay += SECONDS_PER_DAY;
                            case TUE:   _u32NextDay += SECONDS_PER_DAY;
                            case WED:   _u32NextDay += SECONDS_PER_DAY;
                            case THU:   _u32NextDay += SECONDS_PER_DAY;
                            case FRI:   _u32NextDay += SECONDS_PER_DAY;
                            default:
                                        break;
                        }
                        break;

                case EN_Time_OnTimer_Sun:
                        switch(_Today)
                        {
                            case MON:   _u32NextDay += SECONDS_PER_DAY;
                            case TUE:   _u32NextDay += SECONDS_PER_DAY;
                            case WED:   _u32NextDay += SECONDS_PER_DAY;
                            case THU:   _u32NextDay += SECONDS_PER_DAY;
                            case FRI:   _u32NextDay += SECONDS_PER_DAY;
                            case SAT:   _u32NextDay += SECONDS_PER_DAY;
                            default:
                                        break;
                        }
                        break;
            }

            if (_u32NextDay != 0 )
            {
                DEBUG_WAKE_UP( printf("u32LocalSystemTime = %u\n", u32LocalSystemTime); );
                DEBUG_WAKE_UP( printf("u32LocalWakeUpTime = %u\n", u32LocalWakeUpTime); );

                MApp_SetLocalWakeUpTime(MApp_ConvertStTime2Seconds(&_stTime)+_u32NextDay);
                msAPI_Timer_EnableRTCWakeUp(_bEnableWakeUp);
            }
        }
    }
}

#if (ENABLE_ATSC)
#if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
BOOLEAN MApp_Sleep_GetSleepTimerCountDownStatus(void)
{
    return bStartCountDown;
}
#endif
#endif

#undef MAPP_SLEEP_C

