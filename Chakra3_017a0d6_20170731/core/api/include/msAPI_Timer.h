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

#ifndef MSAPI_TIMER_H
#define MSAPI_TIMER_H


//******************************************************************************
//              Function prototypes
//******************************************************************************

#include "datatype.h"

#ifdef MSAPI_TIMER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


#define DEBUG_WAKE_UP(x)    // x


//custom control
#define DELAY_FOR_ENTERING_MUTE     150
#define DELAY_FOR_LEAVING_MUTE      10
#define DELAY_FOR_STABLE_VIDEO      500
#define DELAY_FOR_STABLE_TUNER      700
#define DELAY_FOR_STABLE_SIF        400
//#define DELAY_FOR_STABLE_MPEG       1500
#define DELAY_FOR_CHANNELCHANGE     1500

INTERFACE BOOLEAN msAPI_Timer_IsSystemTimeValid(void);
INTERFACE void msAPI_Timer_DisableSystemTime(void);
INTERFACE void msAPI_Timer_SyncToPmRTC(void);

INTERFACE U32 msAPI_Timer_GetTime0(void); // tick counter of timer 0

INTERFACE U32 msAPI_Timer_GetDownTimer0(void);
INTERFACE void msAPI_Timer_SetDownTimer0(U32 u32Timer);
INTERFACE U32 msAPI_Timer_GetSystemTime(void);
INTERFACE S32 msAPI_Timer_GetOffsetTime(void);
INTERFACE U32 msAPI_Timer_GetWakeupTime(void);
INTERFACE void msAPI_Timer_SetSystemTime(U32 u32SystemTime);
INTERFACE void msAPI_Timer_SetOffsetTime(S32 s32OffsetTime);
INTERFACE void msAPI_Timer_SetWakeupTime(U32 u32Time);
INTERFACE U32 msAPI_Timer_DiffTime(U32 u32Timer, U32 u32TaskTimer); //unit = tick
U32 msAPI_Timer_DiffTime_2(U32 u32OldTime, U32 u32NewTime);

INTERFACE U32 msAPI_Timer_DiffTimeFromNow(U32 u32TaskTimer);

INTERFACE S32 msAPI_Timer_Load_OffsetTime(void);

//WDT
INTERFACE void msAPI_Timer_ResetWDT(void);
//RTC
INTERFACE void msAPI_Timer_SetRTCWakeUpTime(U32 u32SystemTime); //unit = sec
INTERFACE U32 msAPI_Timer_GetRTCWakeUpTime(void); //unit = sec
INTERFACE void msAPI_Timer_EnableRTCWakeUp(BOOLEAN bEnable);
INTERFACE U32 msAPI_Timer_GetRTCSystemTime(void);
INTERFACE void msAPI_Timer_SetTimeOfChange(U32 u32TimeOfChg);
INTERFACE void msAPI_Timer_SetNextTimeOffset(S32 s32OffsetTime);

void msAPI_Timer_1ms_ISR(void);
void msAPI_Timer_DelayUs(U32 u32DelayTimeus);

//============================================================================

typedef enum
{
    E_DELAY_ID_UNKNOWN,
    E_DELAY_ID_API_TIMER_DELAY      = 1,

    E_DELAY_ID_DRV_XC_INIT              = 10,
    E_DELAY_ID_DRV_XC_SET_FB            = 11,
    E_DELAY_ID_DRV_XC_SET_BLACK_WIN     = 12,
    E_DELAY_ID_DRV_XC_SET_DISABLE_INPUT = 13,
    E_DELAY_ID_DRV_XC_SET_WIN           = 14,
    E_DELAY_ID_XC_SYS                   = 17,


    E_DELAY_ID_AUDIO_DRV                    = 20,
    E_DELAY_ID_AUDIO_DRV_MApi_Audio_Monitor = 21,
    E_DELAY_ID_AUDIO_DRV_SPDIF_UNMUTE       = 22, // 30ms


    E_DELAY_ID_AUDIO_API        = 30,

    E_DELAY_ID_AUDIO_APP        = 40,

    E_DELAY_ID_USB_INIT         = 50, // Total 40ms

    E_DELAY_ID_DRV_FLASH            = 60,
    E_DELAY_ID_API_FLASH_WRITE_DONE = 61,


    E_DELAY_ID_DRV_PANEL        = 70,


    E_DELAY_ID_WAIT_POWER_ON_MUSIC_DONE = 100,

    E_DELAY_ID_PANEL_SET_BACKLIGHT_OFF  = 110,

} EnuDelayId;

#define ENABLE_DEBUG_DELAY_ID   0

#if(ENABLE_DEBUG_DELAY_ID)
    extern EnuDelayId g_Timer_eCurDelayId;
    #define TIMER_SET_DELAY_ID_START(id)    EnuDelayId eBackup_DelayId = g_Timer_eCurDelayId; g_Timer_eCurDelayId = (id)
    #define TIMER_SET_DELAY_ID_END()        g_Timer_eCurDelayId = eBackup_DelayId;
#else
    #define TIMER_SET_DELAY_ID_START(id)
    #define TIMER_SET_DELAY_ID_END()
#endif

INTERFACE void msAPI_Timer_Delayms_2(U32 u32DelayTime, EnuDelayId eDelayId); //unit = ms
INTERFACE void msAPI_Timer_Delayms(U32 u32DelayTime); //unit = ms

//============================================================================

#undef INTERFACE

#endif

