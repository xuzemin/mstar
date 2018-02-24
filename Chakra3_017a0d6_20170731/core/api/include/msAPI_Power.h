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

#ifndef _MSAPI_POWER_H_
#define _MSAPI_POWER_H_

#include "drvpower_if.h"

#ifdef _MSAPI_POWER_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

//================== On Timer ====================
typedef enum
{
    SUN        = 0,
    MON        = 1,
    TUE        = 2,
    WED        = 3,
    THU        = 4,
    FRI        = 5,
    SAT        = 6,
    MAX_DAYOFWEEK,
} DAYOFWEEK;

typedef enum
{
    EN_OnTimer_Off,
    EN_OnTimer_Once,
    EN_OnTimer_Everyday,
    EN_OnTimer_Mon2Fri,
    EN_OnTimer_Mon2Sat,
    EN_OnTimer_Sat2Sun,
    EN_OnTimer_Sun,
    EN_OnTimer_Num
} MENU_OnTimer;

typedef enum
{
    EN_POWER_AC_BOOT,
    EN_POWER_DC_BOOT,
}EN_POWER_ON_MODE;

typedef enum
{
    EN_PM_MODE_STANBY      = 0x01,
    EN_PM_MODE_SLEEP       = 0x02,
    EN_PM_MODE_DEEPSLEEP   = 0x03,
    EN_PM_MODE_DEFAULT     = 0xFF,
}EN_PM_MODE;

#define PM_MODE_STANBY          0x01
#define PM_MODE_DEEPSLEEP       0x02

#define PM_MODE_DEFAULT         0xFF


#if (PM_MODE_SELECT == PM_MODE_DEEPSLEEP)

typedef struct _PMTblType
{
    U32 dwReg;
    U8  ucValue;
    U8  ucMask;
    U16 wAct;
}PMTblType;

/// Wake-up device
enum
{
    PM_WAKEUP_BY_KEYPAD         = (1 << 0),
    PM_WAKEUP_BY_CEC            = (1 << 1),
    PM_WAKEUP_BY_RTC            = (1 << 2),
    PM_WAKEUP_BY_DDC            = (1 << 3),

    PM_WAKEUP_BY_VGA            = (1 << 4),
    PM_WAKEUP_BY_DVI            = (1 << 5),
    PM_WAKEUP_BY_GPI            = (1 << 6),

    PM_WAKEUP_BY_IR_NEC         = (1 << 7),
    PM_WAKEUP_BY_IR_RC          = (1 << 8),
    PM_WAKEUP_BY_IR             = PM_WAKEUP_BY_IR_NEC | PM_WAKEUP_BY_IR_RC,

    PM_WAKEUP_BY_ALL_xIR        = PM_WAKEUP_BY_KEYPAD
                                | PM_WAKEUP_BY_CEC
                                | PM_WAKEUP_BY_RTC
                                | PM_WAKEUP_BY_DDC
                                | PM_WAKEUP_BY_VGA
                                | PM_WAKEUP_BY_DVI
                                | PM_WAKEUP_BY_GPI,

    PM_WAKEUP_BY_ALL            = PM_WAKEUP_BY_ALL_xIR | PM_WAKEUP_BY_IR_NEC,
};

///////////////////////////////////////////////////////////////////////////////

#else //#if (PM_MODE_SELECT == PM_MODE_STANBY)

  #if (PM_RUNS_IN == PM_RUNS_IN_FLASH)

    // for msAPI_Power_CheckWakeupDevice to check
    #define WakeUp_by_IR        0
    #define WakeUp_by_CEC       BIT0
    #define WakeUp_by_GPIO      BIT1
    #define WakeUp_by_RTC       BIT2
    #define WakeUp_by_SAR       BIT3
    #define WakeUp_by_DDCD      BIT4
    #define WakeUp_by_DVI       BIT5
    #define WakeUp_by_SYNC      BIT6
   #if (PM_MODE_SELECT == PM_MODE_STANBY)
    #define WakeUp_by_USB       BIT7
   #endif
    #define WakeUp_by_MHL       BIT8

    #define WakeUp_by_None      0xFFFF

    // Wake-up device selection
    enum
    {
        PM_WAKEUP_BY_KEYPAD         = (1 << 0),
        PM_WAKEUP_BY_CEC            = (1 << 1),
        PM_WAKEUP_BY_RTC            = (1 << 2),
        PM_WAKEUP_BY_DDC            = (1 << 3),

        PM_WAKEUP_BY_VGA            = (1 << 4),
        PM_WAKEUP_BY_DVI            = (1 << 5),
        PM_WAKEUP_BY_GPI            = (1 << 6),
        PM_WAKEUP_BY_IR             = (1 << 7),

        PM_WAKEUP_BY_UART           = (1 << 8),
        PM_WAKEUP_BY_USB            = (1 << 9),
        PM_WAKEUP_BY_MHL            = (1 << 10),

#if(ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE)
        // Add for Maya
        PM_WAKEUP_BY_DVI0           = PM_WAKEUP_BY_DVI,
        PM_WAKEUP_BY_DVI1           = (1 << 11),
        PM_WAKEUP_BY_DVI2           = (1 << 12),
        PM_WAKEUP_BY_DVI3           = (1 << 13),
#endif


        PM_WAKEUP_BY_PART            = PM_WAKEUP_BY_KEYPAD
                                     | PM_WAKEUP_BY_CEC
                                     | PM_WAKEUP_BY_RTC
                                     //| PM_WAKEUP_BY_DDC
                                     | PM_WAKEUP_BY_VGA
                                     //| PM_WAKEUP_BY_DVI
                                     //| PM_WAKEUP_BY_GPI
                                     | PM_WAKEUP_BY_IR
                                     | PM_WAKEUP_BY_UART
                                     | PM_WAKEUP_BY_USB
                                     | PM_WAKEUP_BY_MHL
                                    // | PM_WAKEUP_BY_DVI1
                                    // | PM_WAKEUP_BY_DVI2
                                     ,

        PM_WAKEUP_BY_ALL            = PM_WAKEUP_BY_KEYPAD
                                    | PM_WAKEUP_BY_CEC
                                    | PM_WAKEUP_BY_RTC
                                    | PM_WAKEUP_BY_DDC
                                    | PM_WAKEUP_BY_VGA
                                    | PM_WAKEUP_BY_DVI
                                #if(ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE)
                                    | PM_WAKEUP_BY_DVI1
                                    | PM_WAKEUP_BY_DVI2
                                    | PM_WAKEUP_BY_DVI3
                                #endif
                                    | PM_WAKEUP_BY_GPI
                                    | PM_WAKEUP_BY_IR
                                    | PM_WAKEUP_BY_UART
                                    | PM_WAKEUP_BY_USB
                                    | PM_WAKEUP_BY_MHL
                                    ,
    };

#if(ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE)
    #define PM_WAKEUP_BY_DVI_ALL    (PM_WAKEUP_BY_DVI|PM_WAKEUP_BY_DVI1|PM_WAKEUP_BY_DVI2|PM_WAKEUP_BY_DVI3)
#endif


    INTERFACE void msAPI_Power_SetWakeUpDevice(void);
  #elif (PM_RUNS_IN == PM_RUNS_IN_CACHE)

    // for msAPI_Power_CheckWakeupDevice to check
    #define WakeUp_by_IR        0
    #define WakeUp_by_CEC       BIT0
    #define WakeUp_by_GPIO      BIT1
    #define WakeUp_by_RTC       BIT2
    #define WakeUp_by_SAR       BIT3
    #define WakeUp_by_DDCD      BIT4
    #define WakeUp_by_DVI       BIT5
    #define WakeUp_by_SYNC      BIT6
    #define WakeUp_by_USB       BIT7
    #define WakeUp_by_MHL       BIT8
    #define WakeUp_by_None      0xFFFF

    // Wake-up device selection
    enum
    {
        PM_WAKEUP_BY_IR             = (1 << 0),
        PM_WAKEUP_BY_KEYPAD         = (1 << 1),
        PM_WAKEUP_BY_GPIO0          = (1 << 2),
        PM_WAKEUP_BY_GPIO1          = (1 << 3),
        PM_WAKEUP_BY_UART           = (1 << 4),
        PM_WAKEUP_BY_VGA            = (1 << 5), //same as PM_WAKEUP_BY_SYNC in CPU_PM
        PM_WAKEUP_BY_ESYNC          = (1 << 6),
        PM_WAKEUP_BY_RTC0           = (1 << 7),
        PM_WAKEUP_BY_RTC1           = (1 << 8),
        PM_WAKEUP_BY_DVI            = (1 << 9), //same as PM_WAKEUP_BY_DVI0 in CPU_PM
        PM_WAKEUP_BY_DVI2           = (1 << 10),
        PM_WAKEUP_BY_CEC            = (1 << 11),
        PM_WAKEUP_BY_AVLINK         = (1 << 12),
        PM_WAKEUP_BY_MHL            = (1 << 13),
        PM_WAKEUP_BY_WOL            = (1 << 14),

        PM_WAKEUP_BY_PART            = PM_WAKEUP_BY_IR
                                     | PM_WAKEUP_BY_KEYPAD
                                     | PM_WAKEUP_BY_CEC
                                     | PM_WAKEUP_BY_RTC0
                                     | PM_WAKEUP_BY_VGA
                                     | PM_WAKEUP_BY_UART
                                     | PM_WAKEUP_BY_DVI
                                     | PM_WAKEUP_BY_MHL,

        PM_WAKEUP_BY_ALL            = PM_WAKEUP_BY_IR
                                    | PM_WAKEUP_BY_KEYPAD
                                    | PM_WAKEUP_BY_GPIO0
                                    | PM_WAKEUP_BY_GPIO1
                                    | PM_WAKEUP_BY_UART
                                    | PM_WAKEUP_BY_VGA
                                    | PM_WAKEUP_BY_ESYNC
                                    | PM_WAKEUP_BY_RTC0
                                    | PM_WAKEUP_BY_RTC1
                                    | PM_WAKEUP_BY_DVI
                                    | PM_WAKEUP_BY_DVI2
                                    | PM_WAKEUP_BY_CEC
                                    | PM_WAKEUP_BY_AVLINK
                                    | PM_WAKEUP_BY_MHL
                                    | PM_WAKEUP_BY_WOL,

    };

    INTERFACE void msAPI_Power_SetWakeUpDevice(void);

  #else

    // for msAPI_Power_CheckWakeupDevice to check
    // PM_WakeupSource define in drvPM.h

    // Wake-up device selection
    // based on the PM_WakeCfg define in drvPM.h
    enum
    {
        PM_WAKEUP_BY_IR             = (1 << 0),
        PM_WAKEUP_BY_KEYPAD         = (1 << 1),
        PM_WAKEUP_BY_GPIO0          = (1 << 2),
        PM_WAKEUP_BY_GPIO1          = (1 << 3),
        PM_WAKEUP_BY_UART1          = (1 << 4),
        PM_WAKEUP_BY_SYNC           = (1 << 5),
        PM_WAKEUP_BY_ESYNC          = (1 << 6),
        PM_WAKEUP_BY_RTC0           = (1 << 7),
        PM_WAKEUP_BY_RTC1           = (1 << 8),
        PM_WAKEUP_BY_DVI0           = (1 << 9),
        PM_WAKEUP_BY_DVI2           = (1 << 10),
        PM_WAKEUP_BY_CEC            = (1 << 11),
        PM_WAKEUP_BY_AVLINK         = (1 << 12),
        PM_WAKEUP_BY_MHL            = (1 << 13),
        PM_WAKEUP_BY_WOL            = (1 << 14),


        PM_WAKEUP_BY_PART           = PM_WAKEUP_BY_IR
                                    | PM_WAKEUP_BY_KEYPAD
                                    | PM_WAKEUP_BY_RTC0
                                    | PM_WAKEUP_BY_CEC
                                    | PM_WAKEUP_BY_MHL
                                    | 0,

        PM_WAKEUP_BY_ALL            = PM_WAKEUP_BY_IR
                                    | PM_WAKEUP_BY_KEYPAD
                                    | PM_WAKEUP_BY_GPIO0
                                    | PM_WAKEUP_BY_GPIO1
                                    | PM_WAKEUP_BY_UART1
                                    | PM_WAKEUP_BY_SYNC
                                    | PM_WAKEUP_BY_ESYNC
                                    | PM_WAKEUP_BY_RTC0
                                    | PM_WAKEUP_BY_RTC1
                                    | PM_WAKEUP_BY_DVI0
                                    | PM_WAKEUP_BY_DVI2
                                    | PM_WAKEUP_BY_CEC
                                    | PM_WAKEUP_BY_AVLINK
                                    | PM_WAKEUP_BY_MHL
//                                    | PM_WAKEUP_BY_WOL
                                    | 0,
    };
  #endif

#endif


//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
INTERFACE MENU_OnTimer msAPI_Power_GetOnTimer(void);
INTERFACE BOOLEAN msAPI_Power_Is1STBootUp(void);
INTERFACE BOOLEAN msAPI_Power_IsPowerDown(void);
INTERFACE void msAPI_ReSetTimerOnFlag(void);
INTERFACE void msAPI_Power_SetOnTimer(MENU_OnTimer eOnTimerDate);
INTERFACE void msAPI_Power_SetDayOfWeek(DAYOFWEEK eDayOfWeek);
INTERFACE void msAPI_Power_Saving_ADC(BOOLEAN bFlag);

INTERFACE void msAPI_Power_Panel1stPowerOn(void);
INTERFACE void msAPI_Power_Panel2ndPowerOn(void);
INTERFACE void msAPI_Power_PanelPowerOff(void);
INTERFACE void msAPI_Power_EnableBacklight(BOOLEAN bEnable);

INTERFACE EN_POWER_ON_MODE msAPI_Power_QueryPowerOnMode(void);
INTERFACE BOOLEAN  msAPI_Power_IswakeupsourceRTC(void);

#if ENABLE_WAKEUP_BY_CEC
INTERFACE BOOLEAN  msAPI_Power_IswakeupsourceCEC(void);
#endif

#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)
INTERFACE void msAPI_Power_SetPowerMode(void);
#endif

INTERFACE U16 msAPI_Power_CheckWakeupDevice(void);
INTERFACE void msAPI_PowerSetting_Init(void);


//***************************************************************************************
#undef INTERFACE

//***************************************************************************************
#endif // _DRVPOWER_H_

