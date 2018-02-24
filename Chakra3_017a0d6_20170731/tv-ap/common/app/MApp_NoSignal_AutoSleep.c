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

#include "Board.h"


#if (NO_SIGNAL_AUTO_SHUTDOWN )

#include "msAPI_DrvInit.h"
#include "msAPI_Global.h"
#include "msAPI_Timer.h"

#include "MApp_Key.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_NoSignal_AutoSleep.h"
#include "MApp_SignalMonitor.h"
#include "MApp_VDMode.h"

//#include "ZUI_tables_h.inl"
#include "MApp_UI_EventHandler.h"


//-------------------------------------------------------------------------------
#define DEBUG_NO_SIGNAL_SLEEP(x)    //x

//=============================================================
#ifndef ENABLE_POWER_SAVING_DPMS_DVI
    #if(ENABLE_ATSC)
        #define ENABLE_POWER_SAVING_DPMS_DVI    1
    #else
        #define ENABLE_POWER_SAVING_DPMS_DVI    0
    #endif
#endif
//-------------------------------------------------------------------------------
//unit: ms
#define NO_SIGNAL_NORWAY_SLEEP_TIMER    (60000*5+30000) // current no siganl time is 10 min

#define NO_SIGNAL_AUTO_SLEEP_TIME_ATSC  (10*60000) // 10 min for ATSC
#define NO_SIGNAL_AUTO_SLEEP_TIME_DTV   (10*60000) // 10 min for DVB

#if ENABLE_POWER_SAVING_DPMS_DVI
    #define NO_SIGNAL_AUTO_SLEEP_TIME_HDMI  (60000*5) // 10 min for HDMI power saving secs unit:ms
#endif
#if ENABLE_POWER_SAVING_DPMS
    #define NO_SIGNAL_AUTO_SLEEP_TIME_VGA   (60000*5) // 5 min: VGA power saving secs
#endif

#define NO_SIGNAL_AUTO_SLEEP_NOTIFY_UI_TIME (60000) // 1 min

//-------------------------------------------------------------------------------

static U32 s_NoSignalAutoSleep_u32NoSignalStartTime;
static BOOLEAN s_NoSignalAutoSleep_bEnableCheckTimeout;

BOOLEAN g_NoSignalAutoSleep_bTimeoutAndGoToSleep = 0;

//-------------------------------------------------------------------------------

#if ENABLE_ATSC
    #define ATSC_NO_SIGNAL_AUTO_SHUTDOWN 1
#else
    #define ATSC_NO_SIGNAL_AUTO_SHUTDOWN 0
#endif


void MApp_NoSignalAutoSleep_Init(void)
{
    //benableNoSignalAutoSleep = TRUE;
    s_NoSignalAutoSleep_bEnableCheckTimeout = FALSE;
}

/*
void MApp_NoSignal_SetAutoSleep(BOOLEAN benable)
{
//PRINT_CURRENT_LINE();
    DEBUG_NO_SIGNAL_SLEEP( printf("MApp_NoSignal_SetAutoSleep(En=%u)\n", benable); );
    //benableNoSignalAutoSleep = benable;
}
*/

void MApp_NoSignalAutoSleep_Reset_StartTime(void)
{
    s_NoSignalAutoSleep_u32NoSignalStartTime = MsOS_GetSystemTime();

    DEBUG_NO_SIGNAL_SLEEP( printf("u32NoSignalStartTime=%u\n", s_NoSignalAutoSleep_u32NoSignalStartTime); );
}

BOOL MApp_NoSignalAutoSleep_Is_CurSourceSupportAutoSleep(void)
{
    BOOL bEnableNoSignalAutoSleep = FALSE;

#if(CHAKRA3_AUTO_TEST)
    return FALSE;
#endif

    if( MApp_Is_InFactoryMode() // // Factory not support
      ||MApp_Is_InAutoScan_DTV()
      ||MApp_Is_InAutoScan_ATV()
    #if (ENABLE_ATSC)
      ||MApp_Is_InAutoScan_ATSC()
    #endif
      )
    {
        return FALSE;
    }

    if( IsVgaInUse() )
    {
    #if( ENABLE_POWER_SAVING_DPMS )
        bEnableNoSignalAutoSleep = TRUE;
    #endif
    }
    else if( IsHDMIInUse() )
    {
    #if( ENABLE_POWER_SAVING_DPMS_DVI )
        bEnableNoSignalAutoSleep = TRUE;
    #endif
    }
    else if( IsDTVInUse() )
    {
    #if (ENABLE_ATSC)
        if( IsAtscInUse() )
        {
        #if(ATSC_NO_SIGNAL_AUTO_SHUTDOWN)
            bEnableNoSignalAutoSleep = TRUE;
        #endif
        }
        else
    #endif
        {
        #if 0//(ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            if( MApp_Is_SignalLostLock() == TRUE )
                bEnableNoSignalAutoSleep = TRUE;
        #endif
            bEnableNoSignalAutoSleep = TRUE;
        }
    }

    return bEnableNoSignalAutoSleep;
}

BOOL MApp_NoSignalAutoSleep_Is_AtscHasSignal(void)
{
  #if ENABLE_ATSC
    if( IsAtscInUse() && (!MApp_GetSignalLockStatus()) )
        return FALSE;
  #endif

    return TRUE;
}

BOOL MApp_NoSignalAutoSleep_Is_DvbHasSignal(void)
{
    EN_SIGNAL_LOCK_STATUS e_SIGNAL_LOCK_STATUS = MApp_GetSignalStatus();

    if( (e_SIGNAL_LOCK_STATUS == SIGNAL_UNLOCK)
      ||(e_SIGNAL_LOCK_STATUS == SIGNAL_UNKNOWN)
      )
        return FALSE;

    return TRUE;
}

BOOL MApp_NoSignalAutoSleep_Is_CurSrcHasSignal(void)
{
    BOOL bHasSignal = TRUE;


    if( IsVgaInUse() || IsHDMIInUse())
    {
        bHasSignal = MApp_IsSrcHasSignal(MAIN_WINDOW);
    }
#if(ENABLE_DTV)
    else if( IsDTVInUse() )
    {
    #if (ENABLE_ATSC)
        if( IsAtscInUse() )
        {
            bHasSignal = MApp_NoSignalAutoSleep_Is_AtscHasSignal();
        }
        else
    #endif
        {
            bHasSignal = MApp_NoSignalAutoSleep_Is_DvbHasSignal();
        }
    }
#endif
    else
    {
        bHasSignal = MApp_IsSrcHasSignal(MAIN_WINDOW);
    }

    return bHasSignal;
}

U32 MApp_NoSignalAutoSleep_Get_TimeoutTime(void)
{
    U32 u32TimeoutTime = 0xFFFFFFFF;

    if( IsDTVInUse() )
    {
    #if(ENABLE_ATSC)
        if( IsAtscInUse() )
        {
            u32TimeoutTime = NO_SIGNAL_AUTO_SLEEP_TIME_ATSC;
        }
        else
    #endif
        {
        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            U16 u16OrginalNetworkID = msAPI_CM_GetON_ID(E_SERVICETYPE_DTV,msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
            if ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY) && (u16OrginalNetworkID == 0x2242))
                u32TimeoutTime = (U32)NO_SIGNAL_NORWAY_SLEEP_TIMER;
            else
                u32TimeoutTime = NO_SIGNAL_AUTO_SLEEP_TIME_DTV;
        #else
            u32TimeoutTime = NO_SIGNAL_AUTO_SLEEP_TIME_DTV;
        #endif
        }
    }
#if(ENABLE_POWER_SAVING_DPMS)
    else if( IsVgaInUse() )
    {
        u32TimeoutTime = NO_SIGNAL_AUTO_SLEEP_TIME_VGA;
    }
#endif
#if(ENABLE_POWER_SAVING_DPMS_DVI)
    else if( IsHDMIInUse() )
    {
        u32TimeoutTime = NO_SIGNAL_AUTO_SLEEP_TIME_HDMI;
    }
#endif
    else
    {
        u32TimeoutTime = 0xFFFFFFFF;
    }

    //DEBUG_NO_SIGNAL_SLEEP( printf("u32TimeoutTime=%u\n", u32TimeoutTime); );

    return u32TimeoutTime;
}

U32 MApp_NoSignalAutoSleep_Get_CountDownTime(void)
{
    U32 u32CountDownTime = 0xFFFFFFFF;

    if( FALSE == s_NoSignalAutoSleep_bEnableCheckTimeout )
    {
        return u32CountDownTime;
    }

    U32 u32NoSignalPeriod = msAPI_Timer_DiffTime_2(s_NoSignalAutoSleep_u32NoSignalStartTime, MsOS_GetSystemTime() );
    U32 u32TimeoutTime = MApp_NoSignalAutoSleep_Get_TimeoutTime();

    DEBUG_NO_SIGNAL_SLEEP(printf(" u32NoSignalStartTime = %u\n", s_NoSignalAutoSleep_u32NoSignalStartTime););
    DEBUG_NO_SIGNAL_SLEEP(printf(" u32NoSignalPeriod = %u\n", u32NoSignalPeriod););
    DEBUG_NO_SIGNAL_SLEEP(printf(" TimeoutTime = %u\n", u32TimeoutTime););

    if( u32NoSignalPeriod >= u32TimeoutTime ) // Already timeout, should go to sleep
    {
        u32CountDownTime = 0;
    }
    else
    {
        u32CountDownTime = u32TimeoutTime - u32NoSignalPeriod;
    }

    DEBUG_NO_SIGNAL_SLEEP(printf(" ==> u32CountDownTime = %u\n", u32CountDownTime););

    return u32CountDownTime;
}

void MApp_NoSignalAutoSleep_Task(void)
{
    static U32 _s_u32CheckNoSignal_LastTime = 0;


    if( msAPI_Timer_DiffTime_2(_s_u32CheckNoSignal_LastTime, MsOS_GetSystemTime() ) < 1000 )
        return;

    _s_u32CheckNoSignal_LastTime = MsOS_GetSystemTime();


    if( FALSE == MApp_NoSignalAutoSleep_Is_CurSourceSupportAutoSleep() )
    {
        s_NoSignalAutoSleep_bEnableCheckTimeout = FALSE;
        return;
    }

    // Check if current source has signal
    if( FALSE == MApp_NoSignalAutoSleep_Is_CurSrcHasSignal() ) // No signal
    {
        DEBUG_NO_SIGNAL_SLEEP(printf("Cur Src No Signal\n"););
        if (FALSE == s_NoSignalAutoSleep_bEnableCheckTimeout )
        {
            s_NoSignalAutoSleep_bEnableCheckTimeout = TRUE;
            //s_NoSignalAutoSleep_u32NoSignalStartTime = msAPI_Timer_GetTime0();
            MApp_NoSignalAutoSleep_Reset_StartTime();
        }
    }
    else // Has signal
    {
        DEBUG_NO_SIGNAL_SLEEP(printf("Cur Src Has Signal\n"););
        s_NoSignalAutoSleep_bEnableCheckTimeout = FALSE;
        MApp_UI_NotifySysEvent(E_SYS_EVENT_SIGNAL_DETECT_CLOSEWBX, NULL);

        // Reset NoSignal Time
        //s_NoSignalAutoSleep_u32NoSignalStartTime = 0;
    }


    if( FALSE == s_NoSignalAutoSleep_bEnableCheckTimeout )
    {
        return;
    }


    if ( s_NoSignalAutoSleep_bEnableCheckTimeout )
    {
        //U32 u32NoSignalPeriod = msAPI_Timer_DiffTime_2(s_NoSignalAutoSleep_u32NoSignalStartTime, MsOS_GetSystemTime() );
        U32 u32TimeoutTime = MApp_NoSignalAutoSleep_Get_TimeoutTime();
        //DEBUG_NO_SIGNAL_SLEEP(printf(" u32NoSignalStartTime = %u\n", s_NoSignalAutoSleep_u32NoSignalStartTime));
        //DEBUG_NO_SIGNAL_SLEEP(printf(" u32NoSignalPeriod = %u\n", u32NoSignalPeriod));
        //DEBUG_NO_SIGNAL_SLEEP(printf(" TimeoutTime = %u\n", u32TimeoutTime));

        U32 u32CountDownTime = MApp_NoSignalAutoSleep_Get_CountDownTime();

        if( 0 == u32CountDownTime ) // Already timeout, should go to sleep
        {
            DEBUG_NO_SIGNAL_SLEEP(printf("\n[NoSignalAutoSleep] Timeout => go to sleep\n"););

            g_NoSignalAutoSleep_bTimeoutAndGoToSleep = TRUE;

            //stGenSetting.g_Time.cAutoSleepFlag = EN_Time_AutoOff_Off;
            u8KeyCode = KEY_POWER;

        #if ENABLE_POWER_SAVING_DPMS
            if (IsVgaInUse())
            {
                MDrv_Power_SetMode(VGA_POWERSAVING);
                g_bVGANoSignalPowerDown = TRUE;
            }
        #endif
        }
        else
        {
            if( u32TimeoutTime >= (1000*70) ) // if TimeoutTime > 70 sec, should notify UI
            {
                if( u32CountDownTime <= NO_SIGNAL_AUTO_SLEEP_NOTIFY_UI_TIME ) //  CountDown < 1 min
                {
                    printf(" u32CountDownTime = %u\n", u32CountDownTime);
                    MApp_UI_NotifySysEvent(E_SYS_EVENT_NO_SIGNAL_AUTO_SLEEP_COUNT_DOWN_1_MIN, &u32CountDownTime);
                    /*if(u8KeyCode != KEY_NULL)
                    {
                        MApp_NoSignalAutoSleep_Reset_StartTime();
                        u8KeyCode = KEY_NULL;
                        enIndicateTimerSource = TS_TYPE_NONE;
                        MApp_ZUI_ACT_ShutdownOSD();
                    }
                    else
                    {
                        if (MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX)
                        {
                            if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY)
                            {
                                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                            }
                            enIndicateTimerSource = TS_TYPE_SLEEPTIMER_NOSIGNAL;
                            MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX);
                        }
                    } */
                }
            }
        }
#if 0//(ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    #if (LOSS_SIGNAL_ALTERNATIVE_ENABLE)
        else
        {?
            if (IsDTVInUse() && (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY))
            {
                if (LOSS_SIGNAL_INIT == MApp_DTV_Scan_GetLossSignalState() && (enFrotEndLockStatus == FRONTEND_UNLOCK))
                {
                    u16OrginalNetworkID = msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
                    if (u16OrginalNetworkID == 0x2242)
                    {
                        u32TimeDiff = (msAPI_Timer_DiffTime(u32NoSignal_MonitorStartTime+u32No_Signal_SleepTimeDur,msAPI_Timer_GetTime0())/1000);
                        if ((u32TimeDiff <= ((NO_SIGNAL_NORWAY_SLEEP_TIMER/1000)-120)) && (u32TimeDiff >= ((NO_SIGNAL_NORWAY_SLEEP_TIMER/1000)-121)))
                        {
                            //after 2mins, popup message to indicate the loss of signal
                            MApp_ZUI_ACT_ShutdownOSD();
                            MApp_DTV_Scan_Set_LossSignalFlag(TRUE);
                            MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_CONFIRM_MSG);
                        }
                    }
                }
                else if (LOSS_SIGNAL_NO_RETUNE == MApp_DTV_Scan_GetLossSignalState())
                {
                    u32NoSignal_MonitorStartTime = msAPI_Timer_GetTime0();
                    // subtract previous 2min
                    u32No_Signal_SleepTimeDur = NO_SIGNAL_NORWAY_SLEEP_TIMER - 180000;
                    MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_RETURN_TO_NOSIGNAL);
                }
            }
        }
    #endif // #if (LOSS_SIGNAL_ALTERNATIVE_ENABLE)
#endif // #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    }
}

#endif // #if(NO_SIGNAL_AUTO_SHUTDOWN)

