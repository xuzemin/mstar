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

#ifndef _MAPP_DMP_MAIN_H
#define _MAPP_DMP_MAIN_H

#include "datatype.h"
#include "MApp_Exit.h"
#include "MApp_ZUI_APIcommon.h"
#include "mapp_mplayer.h"

#ifdef MAPP_DMP_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define DMP_DBG(x)                  x //gchen @ 20171220 //open debug
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
#define DMP_DRIVE_NUM_PER_PAGE          10
#else
#define DMP_DRIVE_NUM_PER_PAGE          4
#endif

#define DMP_FILE_PAGE_COLUMN_NUM        1//4
#define DMP_NUM_OF_FILES_PER_PAGE       7//10//wht1203017_12 12->10
#define UI_DMP_PLAYLIST_NUMBER          10
#define DMP_VOLUME_TIMER                0
#define DMP_KEYSTONE_TIMER                0  //xzm @20171228

#if UI_SKIN_SEL == UI_SKIN_960X540XI8
#define DMP_PHOTO_THUMBNAIL             0
#define DMP_MOVIE_THUMBNAIL             0
#define DMP_MUSIC_THUMBNAIL             0
#else
#if (ENABLE_DMP_MINI_MENU && (MEMORY_MAP <= MMAP_32MB))
#define DMP_PHOTO_THUMBNAIL             0
#define DMP_MOVIE_THUMBNAIL             0
#define DMP_MUSIC_THUMBNAIL             0
#else
#define DMP_PHOTO_THUMBNAIL             1
#define DMP_MOVIE_THUMBNAIL             0
#define DMP_MUSIC_THUMBNAIL             1
#endif
#endif

#define DMP_MUSIC_PREVIEW               1

#if (MEMORY_MAP <= MMAP_32MB)
    #define DMP_MOVIE_PREVIEW               0
#else
    #define DMP_MOVIE_PREVIEW               1
#endif

#define DMP_TEXT_PREVIEW                0
#define DMP_UART_TIMER                  0

typedef enum
{
    DMP_FLAG_NONE                       = 0,
    DMP_FLAG_INITED                     = BIT0,
    DMP_FLAG_DRIVE_CONNECT_OK           = BIT1,
    DMP_FLAG_MEDIA_FILE_PLAYING         = BIT2,
    DMP_FLAG_BGM_MODE                   = BIT3,
    DMP_FLAG_THUMBNAIL_MODE             = BIT4,
    DMP_FLAG_THUMBNAIL_PLAYING          = BIT5,
    DMP_FLAG_MEDIA_FILE_PLAYING_ERROR   = BIT6,
    DMP_FLAG_MOVIE_REPEATAB_MODE        = BIT7,
  #if EN_DMP_SEARCH_ALL
    DMP_FLAG_BROWSER_ALL                = BIT8,
  #endif
} EN_DMP_FLAG;

typedef enum
{
    DMP_UI_STATE_MEDIA_SELECT,
    DMP_UI_STATE_DRIVE_SELECT,
    DMP_UI_STATE_FILE_SELECT,
#if PLAYLIST_BGM
    DMP_UI_STATE_BGM_DRIVE_SELECT,
    DMP_UI_STATE_BGM_FILE_SELECT,
#endif
    DMP_UI_STATE_LOADING,
    DMP_UI_STATE_PLAYING_STAGE,
} EN_DMP_UI_STATE;

typedef enum
{
    DMP_STATE_INIT,
    DMP_STATE_CONNECTING,
    DMP_STATE_UI,
    DMP_STATE_WAIT,
    DMP_STATE_CLEAN_UP,
    DMP_STATE_GOTO_STANDBY,
    DMP_STATE_GOTO_MENU,
    DMP_STATE_GOTO_INPUTSOURCE,
#if ENABLE_DMP_MINI_MENU
    DMP_STATE_GOTO_DMP_MINIMENU,
#endif
    DMP_STATE_GOTO_PREV_SRC,
    DMP_STATE_RETURN_FROM_MENU,
	DMP_STATE_RESET, 
} EN_DMP_STATE;

#if ENABLE_DMP_MINI_MENU
typedef enum
{
    DMP_MINI_MENU_STATE_INIT,
    DMP_MINI_MENU_STATE_CONNECTING,
    DMP_MINI_MENU_STATE_UI,
    DMP_MINI_MENU_STATE_WAIT,
    DMP_MINI_MENU_STATE_CLEAN_UP,
    DMP_MINI_MENU_STATE_GOTO_STANDBY,
    DMP_MINI_MENU_STATE_GOTO_MENU,
    DMP_MINI_MENU_STATE_GOTO_INPUTSOURCE,
    DMP_MINI_MENU_STATE_GOTO_PREV_SRC,
    DMP_MINI_MENU_STATE_RETURN_FROM_MENU,
} EN_DMP_MINI_MENU_STATE;
#endif

typedef struct
{
    U8                  u8Idx;                          //Current drive index
    U8                  u8PageIdx;                      //Current drive page index
    U8                  au8MapTbl[NUM_OF_MAX_DRIVE];    //drive mapping table
} ST_DRV_INFO;

typedef struct
{
    EN_DMP_STATE        enDmpState;     //DMP main state (ZUI related)
    EN_DMP_UI_STATE     enDmpUiState;   //ACTdmp internal state
    EN_DMP_FLAG         enDmpFlag;      //MPlayer status flag
    ST_DRV_INFO         stDrvInfo;      //Drive info
} ST_DMP_VAR;


INTERFACE EN_RET MApp_DMP_Main(void);
INTERFACE void MApp_DMP_Exit(void);
INTERFACE void MApp_DMP_Reset(void);
INTERFACE BOOLEAN MApp_DMP_RecalculateDriveMappingTable(void);
INTERFACE U8 MApp_DMP_GetDriveFromMappingTable(U8 u8Idx);
INTERFACE U8 MApp_DMP_GetCurDrvIdx(void);
INTERFACE U8 MApp_DMP_GetDrvPageIdx(void);
INTERFACE void MApp_DMP_SetCurDrvIdxAndCalPageIdx(U8 u8Idx);
INTERFACE void MApp_DMP_SetDrvPageIdx(U8 u8Idx);
INTERFACE void MApp_DMP_SetDmpFlag(EN_DMP_FLAG flag);
INTERFACE void MApp_DMP_ClearDmpFlag(EN_DMP_FLAG flag);
INTERFACE EN_DMP_FLAG MApp_DMP_GetDmpFlag(void);
//----------------------- DMP state machine APIs ----------------------------
INTERFACE void MApp_DMP_SetDmpUiState(EN_DMP_UI_STATE state);
INTERFACE EN_DMP_UI_STATE MApp_DMP_GetDmpUiState(void);
INTERFACE void MApp_DMP_UiStateTransition(EN_DMP_UI_STATE enState);
INTERFACE BOOLEAN MApp_DMP_GotoMainMenu(void);
INTERFACE BOOLEAN MApp_DMP_GotoInputSrcMenu(void);
#if ENABLE_DMP_MINI_MENU
INTERFACE BOOLEAN MApp_DMP_GotoDMPMiniMenu(void);
#endif
INTERFACE BOOLEAN MApp_DMP_GotoPreSrc(void);
INTERFACE void MApp_DMP_InitDMPStat(void);
INTERFACE void MApp_DMP_SetDMPStat(EN_DMP_STATE stat);
INTERFACE EN_DMP_STATE MApp_DMP_GetDMPStat(void);
INTERFACE BOOLEAN MApp_DMP_IsSuccessorWinVisible(HWND hWnd);
INTERFACE void MApp_DMP_BW_Control(BOOL bOsdOn);
//----------------------- MISC ------------------------------
INTERFACE BOOLEAN MApp_DMP_IsFileTypeByIdx(U16 u16Idx);
INTERFACE U16 MApp_DMP_QueryTotalPlayListNum(void);
//-----------------------------------------------------------
INTERFACE BOOLEAN MApp_DMP_IsOSDVisible(void);

#undef INTERFACE

#endif  // _MAPP_DMP_MAIN_H

