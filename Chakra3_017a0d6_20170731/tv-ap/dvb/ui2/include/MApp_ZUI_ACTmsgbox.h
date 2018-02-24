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

#ifndef _MAPP_ZUI_ACTMSGBOX_H
#define _MAPP_ZUI_ACTMSGBOX_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"

typedef enum _MSGBOX_MODE
{
    EN_MSGBOX_MODE_INVALID,
    EN_MSGBOX_MODE_FUNC_NOT_AVAIL    ,      ///< show function not availiable message box
#if FOR_BENCH_CODE
    EN_MSGBOX_MODE_PING_MSGBOX,                     ///< show ping result message box
#endif
    EN_MSGBOX_MODE_MHEG5_SUBTITLE    ,      ///< show MHEG5 subtitle co-exist message box
    EN_MSGBOX_MODE_LOADING_MHEG5    ,       ///< show loading MHEG5 message box
    EN_MSGBOX_MODE_AUTO_ADJUSTING    ,      ///< show auto adjusting message box
    EN_MSGBOX_MODE_NO_TELETEXT   ,       ///< show no teletext message box
    EN_MSGBOX_MODE_NO_TTX_SUBTITLE_MSGBOX,             ///< show no teletext subtitle message box
    EN_MSGBOX_MODE_KEY_LOCK    ,            ///< show key lock message box
    EN_MSGBOX_MODE_CEC_DEVICE,              ///< show CEC device message
    EN_MSGBOX_MODE_POWER_OFF_COUNTDOWN,         ///< show power off countdown message box
    EN_MSGBOX_MODE_PASSWORD_INPUT,
#if ( ENABLE_CI_PLUS_V1_4 )
    EN_MSGBOX_MODE_CI_PLUS_POWER_OFF_COUNTDOWN_CHECK,         ///< show power off countdown message box
#endif  //ENABLE_CI_PLUS_V1_4
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE,
    EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG,
    EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE,
    EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG,
#endif
    EN_MSGBOX_MODE_PASSWORD_WRONG,
#if ENABLE_ATSC
    EN_MSGBOX_MODE_PARENTAL_BLOCK,
#endif
    EN_MSGBOX_MODE_USB_LIST,
    EN_MSGBOX_MODE_USB_LIST_SEL,

#if(ENABLE_OAD)
    EN_MSGBOX_MODE_OAD_NOT_AVAIL,
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT) //TODO
    EN_MSGBOX_MODE_NETWORK_CHANGE_MSGBOX,
    #ifdef ENABLE_DELETE_PROGRAM_CONTROL
    EN_MSGBOX_MODE_PROGRAM_DELETE_MSGBOX,
    #endif
    EN_MSGBOX_MODE_NEW_MULTIPLEX_MIGHT_AVAILABLE_MSGBOX,
    EN_MSGBOX_MODE_MULTIPLEX_IS_REMOVED_MSGBOX,
    EN_MSGBOX_MODE_FREQUENCY_CHANGE_MSGBOX,
    EN_MSGBOX_MODE_LOSS_OF_SIGNAL_MSGBOX,
    EN_MSGBOX_MODE_SCANNING_MSGBOX,
    EN_MSGBOX_MODE_NO_OAD_MSGBOX,
#endif

#if ENABLE_FAVORITE_NETWORK
    EN_MSGBOX_MODE_NETWORK_CHANGE,
    EN_MSGBOX_MODE_MULTIPLEX_AVAILABLE,
    EN_MSGBOX_MODE_MULTIPLEX_REMOVED,
    EN_MSGBOX_MODE_FREQ_CHANGE,
    EN_MSGBOX_MODE_LOSS_SIGNAL,
#endif

#if(ASTRA_HD_ENABLE)
    EN_MSGBOX_MODE_ADD2CHLIST_MSGBOX,
    EN_MSGBOX_MODE_NETWORKCHANGE_MSGBOX,
#endif

#if ( ENABLE_UNITY_MEDIA_SETTING )
    EN_MSGBOX_MODE_SHOW_WELCOME_MSGBOX,
#endif  //ENABLE_UNITY_MEDIA_SETTING

#if ENABLE_EWS
    //EN_MSGBOX_MODE_EWS,
#endif
} MSGBOX_MODE;

#ifdef MAPP_ZUI_ACTMSGBOX_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/////////////////////////////////////////
// Cutomize Window Procedures...
//INTERFACE S32 MApp_ZUI_ACT_MessageBoxWinProc(HWND, PMSG);

//#define MESSAGEBOX_WINPROC MApp_ZUI_ACT_MessageBoxWinProc

INTERFACE S32 MApp_ZUI_ACT_MsgBoxTextPaneWinProc(HWND, PMSG);
INTERFACE S32 MApp_ZUI_ACT_MsgBox_PasswordInputWinProc(HWND hwnd, PMSG msg);
#define MSGBOXTEXTPANE_WINPROC MApp_ZUI_ACT_MsgBoxTextPaneWinProc
#define MSGBOXPWDINPUT_WINPROC MApp_ZUI_ACT_MsgBox_PasswordInputWinProc
/////////////////////////////////////////
// Event Handlers....
INTERFACE void MApp_ZUI_ACT_AppShowMessageBox(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleMessageBoxKey(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_TerminateMessageBox(void);
INTERFACE MSGBOX_MODE MApp_ZUI_ACT_GetMessageBoxMode(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteMessageBoxAction(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetMessageBoxDynamicText(HWND hwnd);
#if (ENABLE_EWS == TRUE)
INTERFACE OSD_COLOR MApp_ZUI_ACT_GetMsgBoxmenuDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, U32 colorOriginal);
INTERFACE U16 MApp_ZUI_ACT_GetMsgBoxDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type);
#endif
//INTERFACE S16 MApp_ZUI_ACT_GetMessageBoxDynamicValue(HWND hwnd);
#define PASSWORD_INPUT_MASK 0xF

#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTMSGBOX_H */

