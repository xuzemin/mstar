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

#ifndef _MAPP_GAME_MAIN_H
#define _MAPP_GAME_MAIN_H

#include "Board.h"

#if GAME_ENABLE

/******************************************************************************/
/*   Header Files                                                                                                           */
/******************************************************************************/

#include "datatype.h"
#include "MApp_Exit.h"
#include "ZUI_tables_h.inl"

#ifdef MAPP_GAME_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/******************************************************************************/
/*   Local Defines                                                                                                         */
/******************************************************************************/

#define GAME_DEBUG(x)       //x

#define TITLE_POSITION_X 100
#define TITLE_POSITION_Y 50

#define getmaxx()           ZUI_GAME_LIST_WIDTH//1280
#define getmaxy()           ZUI_GAME_LIST_HEIGHT//720

typedef enum
{
#if GAME_BOXMAN
    EN_GAME_BOXMAN,
#endif  //GAME_BOXMAN
#if GAME_GOBANG
    EN_GAME_GOBANG,
#endif  //GAME_GOBANG
#if GAME_SNAKE
    EN_GAME_SNAKE,
#endif  //GAME_SNAKE
#if GAME_SUDOKU
    EN_GAME_SUDOKU,
#endif  //GAME_SUDOKU
#if GAME_TETRIS
    EN_GAME_TETRIS,
#endif  //GAME_TETRIS
#if GAME_MINES
    EN_GAME_MINES,
#endif  //GAME_MINES
#if GAME_SHOT
    EN_GAME_SHOT,
#endif  //GAME_SHOT
    EN_GAME_NUM,
    EN_GAME_UNKNOW,
} EN_GAME_TYPE;

typedef enum
{
    EN_GAME_RANK_NONE,
    EN_GAME_RANK_EASY,
    EN_GAME_RANK_NORMAL,
    EN_GAME_RANK_HARD,
    EN_GAME_RANK_NUM,
} EN_GAME_RANK;

typedef enum
{
    GAME_STATE_INIT,
    GAME_STATE_WAIT_IN_LIST,
    GAME_STATE_WAIT_IN_GAME,
    GAME_STATE_CLEAN_UP,
    GAME_STATE_GOTO_STANDBY,
    GAME_STATE_GOTO_MENU,
    GAME_STATE_GOTO_INPUTSOURCE,
    GAME_STATE_GOTO_TVSOURCE,
} EN_GAME_STATE;

typedef enum
{
    EN_GAME_KEY_UP,
    EN_GAME_KEY_DOWN,
    EN_GAME_KEY_LEFT,
    EN_GAME_KEY_RIGHT,
    EN_GAME_KEY_SELECT,
    EN_GAME_KEY_EXIT,
    EN_GAME_KEY_PLAY,
    EN_GAME_KEY_PAUSE,
    EN_GAME_KEY_NUM0,
    EN_GAME_KEY_NUM1,
    EN_GAME_KEY_NUM2,
    EN_GAME_KEY_NUM3,
    EN_GAME_KEY_NUM4,
    EN_GAME_KEY_NUM5,
    EN_GAME_KEY_NUM6,
    EN_GAME_KEY_NUM7,
    EN_GAME_KEY_NUM8,
    EN_GAME_KEY_NUM9,
    EN_GAME_KEY_NULL = 0xFF,
} EN_GAME_KEY;


INTERFACE BOOLEAN MApp_Game_Init(void);
INTERFACE void MApp_Game_Exit(void);
INTERFACE void MApp_Game_MultiTask(void);
INTERFACE EN_RET MApp_Game_Main(void);
INTERFACE EN_GAME_STATE MApp_Game_GetState(void);
INTERFACE void MApp_Game_SetState(EN_GAME_STATE enState);
INTERFACE char* MApp_Game_GetGameName(U8 u8Index);
INTERFACE U8 MApp_Game_GetGameItemIndex(void);
INTERFACE U8 MApp_Game_GetGameListIdx(void);
INTERFACE EN_GAME_TYPE MApp_Game_GetGameListByIdx(U8 u8Index);
INTERFACE EN_GAME_RANK MApp_Game_GetGameLevelListByIdx(U8 u8Index);
INTERFACE BOOLEAN MApp_Game_IsShowExitWarningInfo(void);
INTERFACE BOOLEAN MApp_Game_CheckGameLevelSupport(HWND hwnd);
INTERFACE void MApp_Game_SetGameLevel(HWND hwnd);
INTERFACE EN_GAME_RANK MApp_Game_GetGameLevel(void);


#undef INTERFACE

#endif
#endif

