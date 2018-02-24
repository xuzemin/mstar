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

#ifndef _MAPP_ZUI_ACTEPG_H
#define _MAPP_ZUI_ACTEPG_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef MAPP_ZUI_ACTEPG_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
#define EPG_ServiceType_WithoutBaker	0x80
#define EPG_ServiceType_Return			0x40

#define PASSWORD_INPUT_MASK 0xF

INTERFACE U8    g_u8MenuMainItemIndex;
INTERFACE U8    g_u8PrevMenuMainItemIndex;
/////////////////////////////////////////
// Cutomize Window Procedures...
//INTERFACE S32 MApp_ZUI_ACT_EpgRootWinProc(HWND, PMSG);

//#define EPGROOT_WINPROC MApp_ZUI_ACT_EpgRootWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgTitleWinProc(HWND, PMSG);

#define EPGPROGRAMMEGUIDE_TITLE_WINPROC MApp_ZUI_ACT_EpgTitleWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgChannelItemWinProc(HWND,PMSG);

#define EPGPROGRAMMEGUIDE_CHANNELITEM_WINPROC MApp_ZUI_ACT_EpgChannelItemWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgTimeItemWinProc(HWND,PMSG);

#define EPGPROGRAMMEGUIDE_TIMEITEM_WINPROC MApp_ZUI_ACT_EpgTimeItemWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgTimeItemEventWinProc(HWND, PMSG);

#define EPGTIMEITEMEVENT_WINPROC MApp_ZUI_ACT_EpgTimeItemEventWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgChannelItemEventWinProc(HWND, PMSG);

#define EPGCHANNELITEMEVENT_WINPROC MApp_ZUI_ACT_EpgChannelItemEventWinProc

INTERFACE S32 MApp_ZUI_EpgUpdateAllTimeItemWinProc(HWND, PMSG);

#define EPG_UPDATEALLTIMEITEM_WINPROC MApp_ZUI_EpgUpdateAllTimeItemWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgTimePaneWinProc(HWND, PMSG);

#define EPGTIMEPANE_WINPROC MApp_ZUI_ACT_EpgTimePaneWinProc

#if 0
INTERFACE S32 MApp_ZUI_ACT_EpgTimerSettingWinProc(HWND, PMSG);

#define EPG_TIMER_SETTING_WINPROC MApp_ZUI_ACT_EpgTimerSettingWinProc
#endif

INTERFACE S32 MApp_ZUI_ACT_EpgTimerListItemWinProc(HWND, PMSG);

#define EPG_TIMER_LIST_ITEM_WINPROC MApp_ZUI_ACT_EpgTimerListItemWinProc

INTERFACE S32 MApp_ZUI_ACT_EpgTimerSaveDialogWinProc(HWND,PMSG);
#define EPG_TIMER_SAVE_DLG_WINPROC MApp_ZUI_ACT_EpgTimerSaveDialogWinProc

/////////////////////////////////////////
// Event Handlers....
INTERFACE void MApp_ZUI_ACT_AppShowEpg(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleEpgKey(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_TerminateEpg(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteEpgAction(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetEpgDynamicText(HWND hwnd);
INTERFACE U16 MApp_ZUI_ACT_GetEpgDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type);
//INTERFACE S16 MApp_ZUI_ACT_GetEpgDynamicValue(HWND hwnd);
INTERFACE void MApp_ZUI_EpgTimerCountDown(void);
//INTERFACE U16 MApp_ZUI_ACT_GetEpgDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type);

#if (ENABLE_ATSC)
INTERFACE void MApp_ZUI_ACT_AppShowEpg_ATSC(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleEpgKey_ATSC(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_TerminateEpg_ATSC(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteEpgAction_ATSC(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetEpgDynamicText_ATSC(HWND hwnd);
#endif

#if (ENABLE_EPG_MUX)
INTERFACE void   MApp_ZUI_ACT_TSBEPGMenu_Barker_EPG_Enter(void);
INTERFACE void   MApp_ZUI_ACT_TSBEPGMenu_Barker_EPG_Exit(void);
INTERFACE BOOLEAN MApp_IsBarkerEPG(void);
INTERFACE BOOLEAN MApp_IsBarkerEPG_Refresh(void);
INTERFACE void MApp_BarkerEPG_StartToCheck(void);
INTERFACE void MApp_BarkerEPG_Exit(void);
#endif

#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTEPG_H */

