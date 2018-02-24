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

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#ifndef _MSAPI_POWER_C_
#define _MSAPI_POWER_C_

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "debug.h"

#include "drvISR.h"
#include "drvPM.h"
#include "drvMVOP.h"
#include "drvGlobal.h"

#include "msAPI_Power.h"

#include "MApp_GlobalSettingSt.h"

//******************************************************************************

//------------------------------------------------------------------------------
// Global funciton
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function
//------------------------------------------------------------------------------

BOOLEAN msAPI_Power_Is1STBootUp(void)
{
#if (ENABLE_RTC)
    return MDrv_Power_Is1STBootUp(CHECK_PM_OFF_FLAG, MDrv_PM_RTCGetSystemTime());
#else
    return MDrv_Power_Is1STBootUp(CHECK_PM_OFF_FLAG, 0);
#endif
}

BOOLEAN msAPI_Power_IsPowerDown(void)
{
    BOOLEAN bPwrDown = FALSE;

    bPwrDown = MDrv_Power_IsPowerDown();
    if (bPwrDown)
        gWakeupSystemTime = 0xFFFFFFFF;
    return bPwrDown;
}

MENU_OnTimer msAPI_Power_GetOnTimer(void)
{
    return (MENU_OnTimer)g_eOnTimerDate;
}

//-------------------------------------------------------------------------------------------------
/// Checking it it is wake up by timer.
/// @param
/// @return TRUE- Success.
///         FALSE - Failure.
//-------------------------------------------------------------------------------------------------
/*
BOOLEAN msAPI_Power_IsWakeUpByOnTimer(void)
{
    return g_bWakeUpByOnTimer;
}

void msAPI_Power_ReSetTimerOnFlag(void)
{
     g_bWakeUpByOnTimer = FALSE;
}

BOOLEAN msAPI_GetTimerOnFlag()
{
     return msAPI_Power_IsWakeUpByOnTimer();
}
*/
void msAPI_Power_SetOnTimer(MENU_OnTimer eOnTimerDate)
{
    g_eOnTimerDateForStandBy = eOnTimerDate;
}

void msAPI_Power_SetDayOfWeek(DAYOFWEEK eDayOfWeek)
{
    g_eDayOfWeekForStandBy = eDayOfWeek;
}

void msAPI_Power_Saving_ADC(BOOLEAN bFlag)
{

    // Enable Power Saving
    if (bFlag)
    {
        MDrv_Power_Saving_Mode(PSM_MPEG, ENABLE, POWER_SAVING_T);
    }
    // Disable Power Saving
    else
    {
        MDrv_Power_Saving_Mode(PSM_MPEG, DISABLE, POWER_SAVING_T);
    }
}


/******************************************************************************/
/// Panel 1st time power on
/******************************************************************************/
void msAPI_Power_Panel1stPowerOn(void)
{

}

/******************************************************************************/
/// Panel 2nd time power on
/******************************************************************************/
void msAPI_Power_Panel2ndPowerOn(void)
{

}

/******************************************************************************/
/// Panel power off
/******************************************************************************/
void msAPI_Power_PanelPowerOff(void)
{

}

/******************************************************************************/
/// Panel power off
/******************************************************************************/
void msAPI_Power_EnableBacklight(BOOLEAN bEnable)
{
    bEnable = bEnable;
}

/******************************************************************************/
/// Query "AC on" or "DC on"
/******************************************************************************/
EN_POWER_ON_MODE msAPI_Power_QueryPowerOnMode(void)
{
#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)

    U16 u8PowerDownMode = MDrv_Read2Byte(PM_SLEEP_POWERON_FLAG);

    //printf("u8PowerDownMode = %x \n", u8PowerDownMode);

    if(u8PowerDownMode == MAKEWORD(POWERON_FLAG2, POWERON_FLAG1))
    {
        return EN_POWER_DC_BOOT;
    }
    else
    {
        return EN_POWER_AC_BOOT;
    }

#elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
       (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)  || \
       (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
       (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
       (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON))

    U8 u8PowerDownMode = MDrv_ReadByte(PM_SLEEP_AC_DC_ON);

    //printf("u8PowerDownMode = %x \n", u8PowerDownMode);

    switch ( u8PowerDownMode )
    {
        // DC ON
        case EN_PM_MODE_STANBY:    // 0x01
        case EN_PM_MODE_SLEEP:     // 0x02
        case EN_PM_MODE_DEEPSLEEP: // 0x03
        {
            return EN_POWER_DC_BOOT;
        }

        // AC ON
        case EN_PM_MODE_DEFAULT:   // 0xFF
        {
            return EN_POWER_AC_BOOT;
        }

        // EXCEPTION
        default:
        {
            printf("read PM_SLEEP_AC_DC_ON error \n");
            return EN_POWER_DC_BOOT;
        }
    }
#else
    printf("\n !!! msAPI_Power_QueryPowerOnMode TO DO \n");
    return EN_POWER_AC_BOOT;
#endif
}


BOOLEAN  msAPI_Power_IswakeupsourceRTC(void)
{
  #if ((PM_RUNS_IN == PM_RUNS_IN_FLASH)||(PM_RUNS_IN == PM_RUNS_IN_CACHE))
    if (stPowerGenSetting.g_ucWakeUpDevice & WakeUp_by_RTC)
  #else
    if ( (stPowerGenSetting.g_ucWakeUpDevice & E_PM_WAKEUPSRC_RTC)
       ||(stPowerGenSetting.g_ucWakeUpDevice & E_PM_WAKEUPSRC_RTC2)
       )
  #endif
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#if ENABLE_WAKEUP_BY_CEC
BOOLEAN  msAPI_Power_IswakeupsourceCEC(void)
{
  #if ((PM_RUNS_IN == PM_RUNS_IN_FLASH)||(PM_RUNS_IN == PM_RUNS_IN_CACHE))
    //if (stPowerGenSetting.wPM_WakeUpDevice & WakeUp_by_CEC)
    if (stPowerGenSetting.g_ucWakeUpDevice & WakeUp_by_CEC)
  #else
    if (stPowerGenSetting.g_ucWakeUpDevice & E_PM_WAKEUPSRC_CEC)
  #endif
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif



// for PM.bin runs in FLASH
#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)

void msAPI_Power_SetPowerMode(void)
{
    MDrv_Write2Byte(PM_SLEEP_POWERON_FLAG, MAKEWORD(POWERON_FLAG2, POWERON_FLAG1));

    printf(" msAPI_Power_SetPowerMode = 0x%x \n", MDrv_Read2Byte(PM_SLEEP_POWERON_FLAG));
}

void msAPI_Power_SetWakeUpDevice(void)
{
    MDrv_Write2Byte(PM_SLEEP_WAKEUP_DEVICE_FLAG, stPowerGenSetting.wPM_WakeUpDevice);
    printf(" msAPI_Power_SetWakeUpDevice = 0x%x \n", MDrv_Read2Byte(PM_SLEEP_WAKEUP_DEVICE_FLAG));
}

#endif // #if (PM_RUNS_IN == PM_RUNS_IN_FLASH)

#if (PM_RUNS_IN == PM_RUNS_IN_51)

static U16 _msAPI_CEC_TranslateDevice(U16 u16Device)
{
    switch(u16Device)
    {
        case E_PM_WAKEUPSRC_NONE:
            return 0xFFFF;
        case E_PM_WAKEUPSRC_IR:
            return PM_WAKEUP_BY_IR;
        case E_PM_WAKEUPSRC_DVI:
            return PM_WAKEUP_BY_DVI0;
        case E_PM_WAKEUPSRC_DVI2:
            return PM_WAKEUP_BY_DVI2;
        case E_PM_WAKEUPSRC_CEC:
            return PM_WAKEUP_BY_CEC;
        case E_PM_WAKEUPSRC_SAR:
            return PM_WAKEUP_BY_KEYPAD;
        case E_PM_WAKEUPSRC_ESYNC:
            return PM_WAKEUP_BY_ESYNC;
        case E_PM_WAKEUPSRC_SYNC:
            return PM_WAKEUP_BY_SYNC;
        case E_PM_WAKEUPSRC_RTC:
            return PM_WAKEUP_BY_RTC0;
        case E_PM_WAKEUPSRC_RTC2:
            return PM_WAKEUP_BY_RTC1;
        case E_PM_WAKEUPSRC_AVLINK:
            return PM_WAKEUP_BY_AVLINK;
        case E_PM_WAKEUPSRC_UART:
            return PM_WAKEUP_BY_UART1;
        case E_PM_WAKEUPSRC_GPIO:
            return PM_WAKEUP_BY_GPIO0;
        case E_PM_WAKEUPSRC_MHL:
            return PM_WAKEUP_BY_MHL;
        case E_PM_WAKEUPSRC_WOL:
            return PM_WAKEUP_BY_WOL;

        default:
            return 0xFFFF;
    }
}
#endif

U16 msAPI_Power_CheckWakeupDevice(void)
{
    U8 u8tmpReg = 0x00;
    #if (PM_MODE_SELECT == PM_MODE_DEEPSLEEP)
        U16 u16WakeUpDevice = 0xFFFF; //0xFFFF is no wake up source in PM_MODE_DEEPSLEEP
    #else
        U16 u16WakeUpDevice = 0x0; //0x0 is no wake up source
    #endif

    if ( stPowerGenSetting.g_ucACorDCon == EN_POWER_DC_BOOT )
    {
    #if (PM_MODE_SELECT == PM_MODE_DEEPSLEEP)
        u8tmpReg = MDrv_ReadByte(0x100125);
        MDrv_WriteByteMask(0x100125, BIT2|BIT1, BIT2|BIT1);

        u16WakeUpDevice = (U16) MDrv_ReadByte(0x00341E);

        MDrv_WriteByte(0x100125, u8tmpReg);
    #else // #if (PM_MODE_SELECT == PM_MODE_STANBY)

      #if (PM_RUNS_IN == PM_RUNS_IN_FLASH)
        u16WakeUpDevice = MDrv_Read2Byte(PM_SLEEP_NOTIFY_WAKEUP_DEVICE_FLAG);
        MDrv_Write2Byte(PM_SLEEP_NOTIFY_WAKEUP_DEVICE_FLAG, WakeUp_by_None);
      #elif (PM_RUNS_IN == PM_RUNS_IN_CACHE)
        u16WakeUpDevice = MDrv_Read2Byte(PM_SLEEP_NOTIFY_WAKEUP_DEVICE_FLAG);
        MDrv_Write2Byte(PM_SLEEP_NOTIFY_WAKEUP_DEVICE_FLAG, WakeUp_by_None);
      #else
        u16WakeUpDevice = _msAPI_CEC_TranslateDevice((MDrv_ReadByte(PM_SLEEP_Wakeup_Source) & 0x0F));
        MDrv_WriteByte(PM_SLEEP_Wakeup_Source, E_PM_WAKEUPSRC_NONE);
      #endif
        UNUSED(u8tmpReg);
    #endif
    }

    return u16WakeUpDevice;
}


void msAPI_PowerSetting_Init(void)
{
#if ((MARLON_SUPPORT_STR) &&(STR_ENABLE == ENABLE))
    MDrv_SYS_Init();    //(NONOS_STR)
    if(IsSTREnable())
    {
        g_bPQTableSTRReset = TRUE;
    }
#endif
    stPowerGenSetting.wPM_WakeUpDevice = PM_WAKEUP_BY_PART;  // set PM Wake-up Devices
    printf("wPM_WakeUpDevice 0x%x \n", stPowerGenSetting.wPM_WakeUpDevice);

    stPowerGenSetting.g_ucACorDCon = msAPI_Power_QueryPowerOnMode();
    printf("=> %s (%d) \n", (stPowerGenSetting.g_ucACorDCon)?("DC_BOOT"):("AC_BOOT"),
                               stPowerGenSetting.g_ucACorDCon);

    stPowerGenSetting.g_ucWakeUpDevice = msAPI_Power_CheckWakeupDevice();// check which Device to wake up PM
    printf("PM Wakeup by 0x%x \n", stPowerGenSetting.g_ucWakeUpDevice);

    MDrv_Power_PMPowerRst();
}



//***************************************************************************************
#undef _DRVPOWER_C_

//***************************************************************************************
#endif

