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

#ifndef _MAPP_MENU_MAIN_H
#define _MAPP_MENU_MAIN_H

#include "datatype.h"
#include "MApp_Exit.h"

#ifdef MAPP_MENU_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


////////////////////////////////////////////////////////////////////////////////

#if (ENABLE_ATSC)

typedef enum
{
    ATV_SIGNAL,
    DTV_SIGNAL
}SignalType;

typedef enum
{
    DTV_SIGNAL_NONE,
    DTV_SIGNAL_BAD,
    DTV_SIGNAL_NORMAL,
    DTV_SIGNAL_GOOD,
}MenuChannelDTVSignalStatus;

INTERFACE MenuChannelDTVSignalStatus enDTVSignalStatus;
#endif // #if (ENABLE_ATSC)


typedef enum
{
    STATE_MENU_INIT,
    STATE_MENU_WAIT,
    STATE_MENU_EPGTIMER_WAIT,
    STATE_MENU_CLEAN_UP,
    STATE_MENU_GOTO_STANDBY,
    STATE_MENU_GOTO_SCAN,
    STATE_MENU_GOTO_EPG,
    STATE_MENU_GOTO_DTV_MANUALTUNING,
    STATE_MENU_GOTO_ATV_MANUALTUNING,
#if ENABLE_DVBC
    STATE_MENU_GOTO_CADTV_MANUALTUNING,
#endif
    STATE_MENU_GOTO_PREDIT,
    STATE_MENU_GOTO_CHANNELCHANGE,  // To chagne TV<->RADIO when banner is displayed.
    STATE_MENU_GOTO_CIMMI,
#if ENABLE_DMP
    STATE_MENU_GOTO_DMP,
#endif
#ifdef ENABLE_BT
    STATE_MENU_GOTO_BT,
#endif
#ifdef ENABLE_KTV
    STATE_MENU_GOTO_KTV,
#endif
#if(ENABLE_PVR ==1)
    STATE_MENU_GOTO_PVR_CHECK_FS,
#endif
    STATE_MENU_GOTO_OSDPAGE,
    STATE_MENU_GOTO_INPUT_SOURCE,
    STATE_MENU_GOTO_CHANNEL_LIST,
#if (ENABLE_OAD) //TODO
    STATE_MENU_GOTO_NETWORK_LIST,
    STATE_MENU_GOTO_OAD_SCAN,
#endif
    STATE_MENU_GOTO_INFO,
    STATE_MENU_GOTO_FAVORITE_LIST,

#ifdef ENABLE_YOUTUBE
    STATE_MENU_GOTO_YOUTUBE,
#endif
#ifdef ENABLE_RSS
    STATE_MENU_GOTO_RSS,
#endif
//#ifdef ENABLE_NETFLIX
//    STATE_MENU_GOTO_NETFLIX,
//#endif
#ifdef ENABLE_EXTENSION
    STATE_MENU_GOTO_EXTENSION,
#endif
#if(ENABLE_S2)
    STATE_MENU_GOTO_DISHSETUP,
#endif
#if ENABLE_FM_RADIO
    STATE_MENU_GOTO_FMRADIO,
#endif
} EN_MENU_STATE;

typedef enum
{
    STATE_RETURN_NULL,
    STATE_RETURN_DTV_MANUAL_TUNING,
    STATE_RETURN_ATV_MANUAL_TUNING,
    STATE_RETURN_CADTV_MANUAL_TUNING,
    STATE_RETURN_CIMMI,
    STATE_RETURN_PROGRAM_BLOCK,
    STATE_RETURN_PROGRAM_EDIT,
    STATE_RETURN_PVR_FILE_SYS,
    STATE_RETURN_DVBC_SCAN_TUNING,
    STATE_RETUNR_INSTALL_GUIDE,
#if ENABLE_ATSC_INSTALLGUIDE
    STATE_RETURN_SETUP_WIZARD,
#endif
} EN_MENU_RETURN_ITEM;

#if ENABLE_ATSC
INTERFACE BOOLEAN MApp_UiMenu_CheckTVSignal(SignalType type);
#endif

INTERFACE EN_MENU_STATE MApp_Menu_Main_GetState(void);

INTERFACE EN_RET MApp_Menu_Main(void);

INTERFACE EN_MENU_RETURN_ITEM _enReturnMenuItem;
#undef INTERFACE

//******************************************************************************

#endif  // _MAPP_MENU_MAIN_H

