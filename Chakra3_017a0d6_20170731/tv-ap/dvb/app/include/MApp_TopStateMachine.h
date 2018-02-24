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

#ifndef MAPP_TOPSTATEMACHINE_H
#define MAPP_TOPSTATEMACHINE_H

typedef enum
{
    STATE_TOP_CHANNELCHANGE,
#if ENABLE_DVB
    STATE_TOP_DTV_SCAN,
#endif
    STATE_TOP_ATV_SCAN,
#if(ENABLE_ATSC)
    STATE_TOP_ATSC_SCAN,
    STATE_TOP_STDBY,
    STATE_TOP_TV,
#endif

#if ENABLE_SBTVD_ATV_SYSTEM
    STATE_TOP_CATV_SCAN,
#endif

    STATE_TOP_DIGITALINPUTS,
    STATE_TOP_MENU,
    STATE_TOP_INSTALLGUIDE,
#if ENABLE_DVB || ENABLE_ATSC_SCAN_NEW_MODE
    STATE_TOP_DTV_MANUAL_TUNING,
#endif
    STATE_TOP_ATV_MANUAL_TUNING,
    STATE_TOP_INPUTSOURCE,


    STATE_TOP_STANDBY,
  #if ENABLE_STANDBY_STATE_MACHINE
    STATE_TOP_STANDBY_LOOP, // state machine for standby flow
  #endif

    STATE_TOP_TTX,
    STATE_TOP_ANALOG_SHOW_BANNER,

    STATE_TOP_EPG,

    STATE_TOP_OSDPAGE,
    STATE_TOP_USB_DOWNLOAD,

#if ENABLE_OAD
    STATE_TOP_OAD,
#endif

#if (ENABLE_SUBTITLE)
    STATE_TOP_SUBTITLE,
#endif

#if ENABLE_CI
    STATE_TOP_MMI,
#endif

#if ENABLE_DMP
    STATE_TOP_DMP,
  #if ENABLE_DMP_MINI_MENU
    STATE_TOP_DMP_MINI_MENU,
  #endif
    STATE_TOP_APENGINE,
#endif

#if 0//def ENABLE_KTV
    STATE_TOP_KTV,
#endif

#if GAME_ENABLE
    STATE_TOP_GAME,
#endif

#if(ENABLE_PVR ==1)
    STATE_TOP_PVR,
#endif

#if ENABLE_DVBC
    STATE_TOP_CADTV_MANUAL_TUNING,
#endif

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC) || ENABLE_ATSC)
    STATE_TOP_CLOSEDCAPTION,
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    STATE_TOP_SCAN_NEW_MUX,
#endif
#if ENABLE_S2
    STATE_TOP_DISHSETUP,
#endif
#if ENABLE_FM_RADIO
    STATE_TOP_FMRADIO,
#endif

} EN_TOP_STATE;


#ifdef MAPP_TOPSTATEMACHINE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void MApp_TopStateMachine(void);
INTERFACE EN_TOP_STATE MApp_TopStateMachine_GetTopState(void);
INTERFACE char* MApp_TopStateMachine_GetTopStateName(EN_TOP_STATE eTopState);

//ZUI:
#if 1
#define MApp_TopStateMachine_SetTopState(enSetTopState) do {                            \
    MApp_TopStateMachine_SetTopState_2(enSetTopState);                                  \
} while(0)
#else
#define MApp_TopStateMachine_SetTopState(enSetTopState) do {                            \
    PRINT_CURRENT_LINE(); printf(" Call MApp_TopStateMachine_SetTopState(0x%x)\n", enSetTopState);         \
    MApp_TopStateMachine_SetTopState_2(enSetTopState);                                  \
} while(0)
#endif
INTERFACE void MApp_TopStateMachine_SetTopState_2(EN_TOP_STATE enSetTopState);


#undef INTERFACE
#endif

