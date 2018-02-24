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

#if (ENABLE_NO_OPERATE_AUTO_SLEEP )


#include "msAPI_Timer.h"

#include "MApp_GlobalVar.h"
#include "MApp_Key.h"

#include "MApp_NoOperate_AutoSleep.h"

#include "MApp_UI_EventHandler.h"



//-------------------------------------------------------------------------------
#define DEBUG_NO_OP_SLEEP(x)    //x

//=============================================================

#define NO_OPERATE_AUTO_SLEEP__1MIN     (60000)
#define NO_OPERATE_AUTO_SLEEP__1HOUR    (60*NO_OPERATE_AUTO_SLEEP__1MIN)

#define NO_OPERATE_AUTO_SLEEP_NOTIFY_UI_TIME    (60000*5) // 5 min for RiksTV

#define NO_OPERATE_AUTO_SLEEP_MONITER_PERIOD    4000

//-------------------------------------------------------------------------------

static U32 s_NoOpSleep_u32LastOpTime = 0;

//-------------------------------------------------------------------------------

EN_AUTOSLEEP_TIME_STATE MApp_NoOperateAutoSleep_Get_AutoSleepTime(void)
{
    //DEBUG_NO_OP_SLEEP( printf("MApp_NoOperateAutoSleep_Get_AutoSleepTime()\n"););
    return stGenSetting.g_Time.cAutoSleepSetting;
}

void MApp_NoOperateAutoSleep_Set_AutoSleepTime(EN_AUTOSLEEP_TIME_STATE eAutoSleepTime)
{
    if( eAutoSleepTime >= STATE_AUTOSLEEP_NUM )
        eAutoSleepTime = STATE_AUTOSLEEP_NEVER;

    stGenSetting.g_Time.cAutoSleepSetting = eAutoSleepTime;
}

BOOL MApp_NoOperateAutoSleep_Is_FuncEnable(void)
{
#if(CHAKRA3_AUTO_TEST)
    return FALSE;
#endif

    //return TRUE;
    return (MApp_NoOperateAutoSleep_Get_AutoSleepTime() != STATE_AUTOSLEEP_NEVER);
}

U32 MApp_NoOperateAutoSleep_Get_AutoSleepTime_Ms(void)
{
    U32 u32AutoSleepTime = 0xFFFFFFFF;

    //switch( enAutoSleepTimeState )
    switch( MApp_NoOperateAutoSleep_Get_AutoSleepTime() )
    {
        default:
            break;

        case STATE_AUTOSLEEP_4HOUR:
            u32AutoSleepTime = 4 * NO_OPERATE_AUTO_SLEEP__1HOUR;
            break;

        case STATE_AUTOSLEEP_6HOUR:
            u32AutoSleepTime = 6 * NO_OPERATE_AUTO_SLEEP__1HOUR;
            break;

        case STATE_AUTOSLEEP_8HOUR:
            u32AutoSleepTime = 8 * NO_OPERATE_AUTO_SLEEP__1HOUR;
            break;
    }

    return u32AutoSleepTime;
}

void MApp_NoOperateAutoSleep_ResetOpTime(void)
{
    s_NoOpSleep_u32LastOpTime = MsOS_GetSystemTime();

    DEBUG_NO_OP_SLEEP(printf(" Reset => s_NoOpSleep_u32LastOpTime = %u\n", s_NoOpSleep_u32LastOpTime););
}

U32 MApp_NoOperateAutoSleep_Get_CountDownTime(void)
{
    U32 u32CountDownTime = 0xFFFFFFFF;

    if( FALSE == MApp_NoOperateAutoSleep_Is_FuncEnable() )
    {
        return u32CountDownTime;
    }

    U32 u32NoOpPeriod = msAPI_Timer_DiffTime_2(s_NoOpSleep_u32LastOpTime, MsOS_GetSystemTime() );
    U32 u32TimeoutTime = MApp_NoOperateAutoSleep_Get_AutoSleepTime_Ms();

    DEBUG_NO_OP_SLEEP(printf(" s_NoOpSleep_u32LastOpTime = %u\n", s_NoOpSleep_u32LastOpTime););
    DEBUG_NO_OP_SLEEP(printf(" u32NoOpPeriod = %u\n", u32NoOpPeriod););
    DEBUG_NO_OP_SLEEP(printf(" TimeoutTime = %u\n", u32TimeoutTime););

    if( u32NoOpPeriod >= u32TimeoutTime ) // Already timeout, should go to sleep
    {
        u32CountDownTime = 0;
    }
    else
    {
        u32CountDownTime = u32TimeoutTime - u32NoOpPeriod;
    }

    DEBUG_NO_OP_SLEEP(printf(" ==> u32CountDownTime = %ums\n", u32CountDownTime););
    DEBUG_NO_OP_SLEEP(printf(" ==> %us, %umin, \n", u32CountDownTime/1000, u32CountDownTime/60000););

    return u32CountDownTime;
}

void MApp_NoOperateAutoSleep_GoToSleep(void)
{
    printf("\n[NoOperateAutoSleep] Go to sleep\n");

    //stGenSetting.g_Time.cAutoSleepFlag = EN_Time_AutoOff_Off;
    u8KeyCode = KEY_POWER;
}

void MApp_NoOperateAutoSleep_Task(void)
{
    static U32 _s_u32NoOperateAutoSleep_LastTime = 0;


    if( msAPI_Timer_DiffTime_2(_s_u32NoOperateAutoSleep_LastTime, MsOS_GetSystemTime() ) < NO_OPERATE_AUTO_SLEEP_MONITER_PERIOD )
        return;

    _s_u32NoOperateAutoSleep_LastTime = MsOS_GetSystemTime();


    // Check if function turn on
    if( !MApp_NoOperateAutoSleep_Is_FuncEnable() )
        return;


    //U32 u32NoOpPeriod = msAPI_Timer_DiffTime_2(s_NoOpSleep_u32LastOpTime, MsOS_GetSystemTime() );
    //DEBUG_NO_OP_SLEEP(printf("u32NoOpPeriod=%u\n", u32NoOpPeriod););

    U32 u32TimeoutTime = MApp_NoOperateAutoSleep_Get_AutoSleepTime_Ms();
    //DEBUG_NO_OP_SLEEP(printf("u32TimeoutTime=%u\n", u32TimeoutTime););

    U32 u32CountDownTime = MApp_NoOperateAutoSleep_Get_CountDownTime();

    if( 0 == u32CountDownTime ) // Already timeout, should go to sleep
    {
        MApp_NoOperateAutoSleep_GoToSleep();
        return;
    }
    else
    {
        if( u32TimeoutTime >= (1000*70) ) // if TimeoutTime > 70 sec, should notify UI
        {
            if( u32CountDownTime <= (NO_OPERATE_AUTO_SLEEP_NOTIFY_UI_TIME + NO_OPERATE_AUTO_SLEEP_MONITER_PERIOD)) //  CountDown < 1 min
            {
                printf(" u32CountDownTime = %u\n", u32CountDownTime);
                MApp_UI_NotifySysEvent(E_SYS_EVENT_NO_OPERATE_AUTO_SLEEP_COUNT_DOWN_5_MIN, &u32CountDownTime);
            }
        }
    }

}

#endif // #if(ENABLE_NO_OPERATE_AUTO_SLEEP)

