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

#ifndef _MAPP_ZUI_ACTDMP_H
#define _MAPP_ZUI_ACTDMP_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APItables.h"
#if PLAYLIST_BGM
#include "MApp_ZUI_ACTglobal.h"
#endif
#include "mapp_mplayer.h"
#include "MApp_DMP_Main.h"

#ifdef MAPP_ZUI_ACTDMP_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/////////////////////////////////////////
#if ENABLE_USB_DEVICE_LIST
INTERFACE void MApp_ZUI_ACT_DMPSetDrvIdxByUser(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_ZUI_ACT_DMPGetIsDrvIdxByUser(void);
INTERFACE U8 MApp_ZUI_ACT_DMPGetCurDrvIdxByUser(void);
INTERFACE U8 MApp_ZUI_ACT_DMPGetDrvPageIdxByUser(void);
INTERFACE void MApp_ZUI_ACT_DMPSetCurDrvIdxAndCalPageIdxByUser(U8 u8Idx);
INTERFACE void MApp_ZUI_ACT_DMPSetDrvPageIdxByUser(U8 u8Idx);
#endif
/////////////////////////////////////////
// Cutomize Window Procedures...
#define DMP_PROGRESS_WINPROC MApp_ZUI_ACT_DmpProgressWinProc
#define DMP_PLAY_STATUS_WINPROC MApp_ZUI_ACT_DmpPlayStatusWinProc
#define DMP_FILE_SELECT_THUMBNAIL_WINPROC MApp_ZUI_ACT_DmpFileSelectThumbnailWinProc
#define DMP_VOLUME_WINPROC MApp_ZUI_ACT_DMPVolumeWinProc
#define DMP_KEYSTONE_WINPROC MApp_ZUI_ACT_DMPKeystoneWinProc    //xzm @20171228
#define DMP_EQ_PLAY_WINPROC MApp_ZUI_ACT_DmpEqPlayWinProc
#define DMP_PREVIEW_WINPROC MApp_ZUI_ACT_DmpPreviewWinProc
#define DMP_ALERT_WINPROC MApp_ZUI_ACT_DmpAlertWinProc
#define DMP_MARQUEE_WINPROC MApp_ZUI_ACT_DMPMarqueeTextWinProc
#define DMP_MOVIERESUME_WINPROC MApp_ZUI_ACT_DMPMovieResumeWinProc
#define DMP_RESUMESTOP_WINPROC MApp_ZUI_ACT_DMPResumeStopWinProc
#define DMP_UART_WINPROC MApp_ZUI_ACT_DMPUartWinProc
#define DMP_BGM_FILE_SELECT_THUMBNAIL_WINPROC MApp_ZUI_ACT_DmpBgmFileSelectThumbnailWinProc
/////////////////////////////////////////
// Event Handlers....
INTERFACE void MApp_ZUI_ACT_AppShowDmp(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_HandleDmpKey(VIRTUAL_KEY_CODE key);
INTERFACE void MApp_ZUI_ACT_TerminateDmp(void);
INTERFACE BOOLEAN MApp_ZUI_ACT_ExecuteDmpAction(U16 act);
INTERFACE LPTSTR MApp_ZUI_ACT_GetDmpDynamicText(HWND hwnd);
INTERFACE U16 MApp_ZUI_ACT_GetDmpDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type);
INTERFACE S16 MApp_ZUI_ACT_GetDmpDynamicValue(HWND hwnd);
INTERFACE S32 MApp_ZUI_ACT_DmpProgressWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DmpPlayStatusWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DmpAlertWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DmpFileSelectThumbnailWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DMPVolumeWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DMPKeystoneWinProc(HWND hwnd, PMSG msg);    //xzm @20171228
INTERFACE S32 MApp_ZUI_ACT_DmpEqPlayWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DmpPreviewWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DMPMarqueeTextWinProc(HWND hWnd, PMSG pMsg);
INTERFACE U8 MApp_ZUI_ACT_GetCurrentUARTMode(void);
INTERFACE S32 MApp_ZUI_ACT_DMPMovieResumeWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DMPResumeStopWinProc(HWND hwnd, PMSG msg);
#if PLAYLIST_BGM
INTERFACE GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryDMPStatus(HWND hwnd);
#endif
INTERFACE BOOLEAN MApp_ACTdmp_IsSubtitleOFF(void);
INTERFACE S32 MApp_ZUI_ACT_DMPUartWinProc(HWND hwnd, PMSG msg);
INTERFACE S32 MApp_ZUI_ACT_DmpBgmFileSelectThumbnailWinProc(HWND hwnd, PMSG msg);
/////////////////////////////////////////
// Middleware callback function
INTERFACE BOOLEAN MApp_UiMediaPlayer_Notify(enumMPlayerNotifyType eNotify, void *pInfo);
INTERFACE void MApp_DMP_NotifyUiState(EN_DMP_UI_STATE enDmpUiState);
#if (DMP_PHOTO_THUMBNAIL || DMP_MOVIE_THUMBNAIL || DMP_MUSIC_THUMBNAIL)
INTERFACE void MApp_ZUI_ACT_ExitThumbnailMode(void);
#endif
INTERFACE void MApp_ZUI_ACT_DmpGotoStandby(void);
INTERFACE U8 MApp_ZUI_ACT_GetCopyFbId(void);

INTERFACE BOOLEAN MApp_UiMediaPlayer_IsSubtitleEnabled(void);
#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_ACTDMP_H */

