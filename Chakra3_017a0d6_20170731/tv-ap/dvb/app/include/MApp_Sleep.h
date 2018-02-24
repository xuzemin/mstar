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

#ifndef MAPP_SLEEP_H
#define MAPP_SLEEP_H

#include "Board.h"
#include "datatype.h"

#ifdef MAPP_SLEEP_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    STATE_SLEEP_OFF,
    STATE_SLEEP_10MIN,
    STATE_SLEEP_20MIN,
    STATE_SLEEP_30MIN,
    STATE_SLEEP_60MIN,
    STATE_SLEEP_90MIN,
    STATE_SLEEP_120MIN,
    STATE_SLEEP_180MIN,
    STATE_SLEEP_240MIN,
    STATE_SLEEP_TOTAL,
}EN_SLEEP_TIME_STATE;


typedef enum
{
    STATE_SLEEP_OFFTIMER_OFF,
    STATE_SLEEP_OFFTIMER_ON,
    STATE_SLEEP_OFFTIMER_TRANSIT,
}EN_SLEEP_OFFTIMER_STATUS;

INTERFACE U32 u32SleepTimer;
INTERFACE BOOLEAN benableSleepTimer;

#if 1 //0
typedef enum
{
    TS_TYPE_NONE,
    TS_TYPE_SLEEPTIMER,
    TS_TYPE_SLEEPTIMER_NOSIGNAL,
    TS_TYPE_OFFTIMER,
    TS_TYPE_AUTOSLEEP_OFFTIMER,
    TS_TYPE_NUM,
}EN_TIMER_SOURCE_TYPE;

INTERFACE EN_TIMER_SOURCE_TYPE enIndicateTimerSource;  // indicate the source of Display Count
//ZUI: refine code: INTERFACE U32 u32OffTimeCheckTimer;
//ZUI: refine code: INTERFACE U32 u32OffTimeLastCounter;
#endif


INTERFACE U32 u32SleepTimeDur;
INTERFACE U32 u32OffTimeDur;
INTERFACE U8  benableOffTimer; //0: off, 1: On, 2:transit


INTERFACE EN_SLEEP_TIME_STATE enSleepTimeState;
INTERFACE U32 u32AutoOnTime;
INTERFACE BOOLEAN benableAutoOn_OffTimer;
INTERFACE BOOLEAN g_bSleepCountDown;

#define SLEEP_TIMER_TIMEBASE 60000*10 // current timebase is 10 min
#define MINUTE_TO_MS        60000   // 1 minute = 60000 ms
#define FINAL_COUNT         60000
#define DISPLAY_COUNTER     61

#define ONEDAY_TIME         86400//24*60*60
#define MINUTE_TO_S         60
#define PROTECT_OFF_TIMER   5000



#define SLEEPTIMER_COUNTDOWN_TIME_PERIOD 950
#define TIME_AUTO_OFF_AFTER_AUTO_ON      7200000 // 2Hours
INTERFACE void MApp_Sleep_SetTime(void);
INTERFACE void MApp_Sleep_Monitor(void);

INTERFACE void MApp_Sleep_ReleaseSleepTimer(void);
INTERFACE EN_SLEEP_TIME_STATE MApp_Sleep_GetCurrentSleepState(void);

INTERFACE U32 MApp_Sleep_GetSleepTimeRemainTime(void);
INTERFACE void MApp_Sleep_SetCurrentSleepTime(U8 CurrentSleepTime);
INTERFACE void MApp_Sleep_SetOffTime(BOOLEAN bEnable);
INTERFACE void MApp_Sleep_TransitOffTime(void);
INTERFACE void MApp_Sleep_SetAutoOn_OffTime(BOOLEAN bEnable);
INTERFACE EN_SLEEP_TIME_STATE MApp_GetCurSleepTime(BOOLEAN bDecInc);
#if 0 //non-used
INTERFACE void MApp_Timer_SetElapsedTimer(void);
#endif
INTERFACE void MApp_Sleep_SendKeyOffTimeDayOfWeek(void);
INTERFACE BOOLEAN MApp_OffTime_IsOffTimeInDayOfWeek(void);
INTERFACE U32 MApp_Sleep_DisplayCountDownTimer(void);
INTERFACE void MApp_Time_SetOnTime(void);
INTERFACE void MApp_InitRtcWakeUpTimer(void);
INTERFACE void MApp_Time_Tasks_Set_RTC_NextWakeUpTime(void);

#if (ENABLE_ATSC)
#if  ((ATSC_CC == ATV_CC)||(ATSC_CC == DTV_CC))
INTERFACE BOOLEAN MApp_Sleep_GetSleepTimerCountDownStatus(void);
#endif
#endif

#undef INTERFACE

#endif

