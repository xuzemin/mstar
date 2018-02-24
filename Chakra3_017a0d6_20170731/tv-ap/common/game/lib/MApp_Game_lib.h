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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#if ( GAME_ENABLE )

#define GAME_LIB_VER    02
#define GAME_LIB_DATE   "20170621"

//------------------------------------------------
#ifndef BUILD_LIB
#include "MsCommon.h"

#define _ZUI_INTERNAL_INSIDE_
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcomponent.h"
#endif

#define GAME_UI_SNAKE_GAMEOVER          0x0300
#define GAME_UI_SNAKE_UPDATESCORE       0x0301
#define GAME_UI_SNAKE_DRAWFOOD          0x0302    // para -> RECT
#define GAME_UI_SNAKE_DRAWBG            0x0303    // para -> RECT
#define GAME_UI_SNAKE_DRAWSNAKE         0x0304    // para -> RECT
#define GAME_UI_SNAKE_DRAWSNAKEEYE      0x0305    // para -> RECT

extern BOOLEAN MApp_Game_UiExec(U16 u16Cmd, void *para);

//------------------------------------------------

#define GAME_IS_SUPPORT_BOXMAN       0x01
#define GAME_IS_SUPPORT_GOBANG       0x02
#define GAME_IS_SUPPORT_SNAKE        0x03
#define GAME_IS_SUPPORT_SUDOKU       0x04
#define GAME_IS_SUPPORT_TETRIS       0x05
#define GAME_IS_SUPPORT_MINES        0x06
#define GAME_IS_SUPPORT_SHOT         0x07

BOOLEAN MApp_Game_IsLibSupport(U8 u16Game);

#define GAME_INFO_BOXMAN_VERSION          0x0100

#define GAME_INFO_GOBANG_VERSION          0x0200 //                 out -> U16
#define GAME_INFO_GOBANG_BUF_SIZE         0x0201 // in -> SIZE,     out -> U16

#define GAME_INFO_SNAKE_VERSION           0x0300

#define GAME_INFO_SUDOKU_VERSION          0x0400
#define GAME_INFO_SUDOKU_BUF_SIZE         0x0401 // in -> SIZE,     out -> U16

#define GAME_INFO_TETRIS_VERSION          0x0500

#define GAME_INFO_MINES_VERSION           0x0600

#define GAME_INFO_SHOT_VERSION            0x0700

BOOLEAN MApp_Game_GetLibInfo(U16 u16Cmd, void *in, void *out);

/*************************************Boxman API*****************************************/
#if ( GAME_BOXMAN )

typedef enum
{
    EMPTY    =0,
    WALL     =1,
    BOX      =2,
    BALL     =3,
    MAN      =4,
    MANBALL  =5,
    BOXBALL  =6,
} EN_BoxManType;

void MApp_Boxman_GetManPosition(void);
void MApp_Boxman_LoadMap(U16 BoxManMap_Y_Num,U16 BoxManMap_X_Num,U8* pu8BoxManMap,char* pcLevelData);
U8 MApp_Boxman_GetMapData(U8 u8Y, U8 u8X);
void MApp_Boxman_UpdataObject(U16 x1, U16 y1, U16 x2, U16 y2, U16 x3, U16 y3);
#endif  //GAME_BOXMAN

/*************************************Gobang API*****************************************/
#if ( GAME_GOBANG )
void MApp_Gobang_TableInit(U16 u16MaxStepX, U16 u16MaxStepY, int *table, U8 u8GameLevel);
int MApp_Gobang_GetTableValue(U8 u8x,U8 u8y);
int MApp_Gobang_CheckGameOver(void);
int MApp_Gobang_ComSetPoint(U8 *ComputerX, U8 *ComputerY);
BOOLEAN MApp_Gobang_UserSetPoint(int x, int y);
#endif  //GAME_GOBANG

/*************************************Snake API*****************************************/
#if(GAME_SNAKE)
typedef struct
{
    U16 u16Snake_Activity_Width;
    U16 u16Snake_Activity_Height;
    U16 u16Snake_Activity_Start_X;
    U16 u16Snake_Activity_Start_Y;
    U16 u16Snake_Size;
    U16 node;
    U8 direction;

    U32 score;

    U16 food_x;
    U16 food_y;
    BOOLEAN food_bShow;
}Snake_Library_Para;

void MApp_Snake_Library_SetPara(U16* pArrayX,U16* pArrayY);
void MApp_Snake_UpdateContent(Snake_Library_Para* stSnakeLibPara);
#endif

/*************************************Sudoku API*****************************************/
#if ( GAME_SUDOKU )

typedef enum
{
    SUDOKU_SQUARE_NONE      = 0,
    SUDOKU_SQUARE_NUM_1     = 1,
    SUDOKU_SQUARE_NUM_2     = 2,
    SUDOKU_SQUARE_NUM_3     = 3,
    SUDOKU_SQUARE_NUM_4     = 4,
    SUDOKU_SQUARE_NUM_5     = 5,
    SUDOKU_SQUARE_NUM_6     = 6,
    SUDOKU_SQUARE_NUM_7     = 7,
    SUDOKU_SQUARE_NUM_8     = 8,
    SUDOKU_SQUARE_NUM_9     = 9,
    SUDOKU_SQUARE_CURSOR    = 10,
} EN_SUDOKU_SQUARE_TYPE;

BOOLEAN MApp_Sudoku_CheckWin(void);
void MApp_Sudoku_LoadMap(U16 u16MapNum, char *table);
U16 MApp_Sudoku_GetTableValue(U8 u8X, U8 u8Y);
void MApp_Sudoku_UpdateTable(U8 u8Y,U8 u8X, U8 u8Value);
BOOLEAN MApp_Sudoku_CanBlockEdit(U8 u8Y, U8 u8X);
#endif  //GAME_SUDOKU

/*************************************Tetris API*****************************************/
#if ( GAME_TETRIS )

#define TETRIS_GRID_SIZE                    4
#define TETRIS_BOARD_WIDTH                  16
#define TETRIS_BOARD_HEIGHT                 18
#define TETRIS_BLOCK_INFO_ITEM              2

typedef enum
{
    ELEMENTS_GRID_2X2 = 2,
    ELEMENTS_GRID_3X3 = 3,
    ELEMENTS_GRID_4X4 = 4
} EN_TETRIS_ELEMENTS_GRID_SIZE;

typedef enum
{
    EN_TETRIS_NONE = 0,
    EN_TETRIS_I,
    EN_TETRIS_O,
    EN_TETRIS_T,
    EN_TETRIS_L,
    EN_TETRIS_J,
    EN_TETRIS_5,
    EN_TETRIS_Z,
    EN_TETRIS_ELEMENTS_NUM = EN_TETRIS_Z,
} EN_TETRIS_ELEMENTS;

typedef struct Tetris_LibraryPara
{
    U16 u16LineWidth;
    U16 u16BoardWidth;
    U16 u16BoardHeight;
    U16 u16GridSize;
    U16 u16CellSize;
    U16 u16BoardLeft;
    U16 u16BoardTop;
    U16 u16GridBoardLeft;
    U16 u16GridBoardTop;
} Tetris_Library_Para;

typedef struct tagBlock
{
    U8 au8Grid[TETRIS_GRID_SIZE][TETRIS_GRID_SIZE];     /* cell fill info array, 0-empty, 1-filled */
    int x;                              /* block position cx [ 0,BoardWidht -1] */
    int y;                              /* block position cy [-4,BoardHeight-1] */
    EN_TETRIS_ELEMENTS enElementName;
    EN_TETRIS_ELEMENTS_GRID_SIZE enGridSize;        /* block MAX size in width or height */
} Block;

void MApp_Tetris_Library_Init(void);
U32 MApp_Tetris_GetScore(void);
void MApp_Tetris_CheckBoard(void);
void MApp_Tetris_Library_SetPara(U32* pArrayBoard,U16 BoardWidth,U16 BoardHeight, U16 BlockInfo);
#endif  //GAME_TETRIS

/*************************************Mines API*****************************************/
#if ( GAME_MINES )

typedef enum
{
    MINES_SQUARE_NONE      = 0,
    MINES_SQUARE_NUM_1     = 1,
    MINES_SQUARE_NUM_2     = 2,
    MINES_SQUARE_NUM_3     = 3,
    MINES_SQUARE_NUM_4     = 4,
    MINES_SQUARE_NUM_5     = 5,
    MINES_SQUARE_NUM_6     = 6,
    MINES_SQUARE_NUM_7     = 7,
    MINES_SQUARE_NUM_8     = 8,
    MINES_SQUARE_MINE      = 9,
    MINES_SQUARE_FLAG      = 10,
    MINES_SQUARE_EXPLORE   = 11,
    MINES_SQUARE_ERROR     = 12,
    MINES_SQUARE_CURSOR    = 13,
    MINES_SQUARE_SURFACE   = 14,
} EN_MINES_SQUARE_TYPE;

BOOLEAN MApp_Mines_CheckWin(void);
void MApp_Mines_Library_SetPara(char* pArrayMineMap, char* pArrayMineMapFlag, U16 u16MapNum, U16 u16MinesNum, U16 u16Trigger);
#endif  //GAME_MINES

/*************************************Shot API*****************************************/
#if ( GAME_SHOT )

typedef enum
{
    SHOT_SQUARE_NONE        = 0,
    SHOT_SQUARE_GUN         = 1,
    SHOT_SQUARE_BULLET      = 2,
    SHOT_SQUARE_BLOCK       = 3,
} EN_SHOT_SQUARE_TYPE;

BOOLEAN MApp_Shot_CheckWin(void);
BOOLEAN MApp_Shot_CheckEmptyLine(void);
void MApp_Shot_Library_SetPara(char* pArrayShotMap, U16 u16MapNum, U32 u32Score, U32 u32NowLevel, U16 u16Pass);
void MApp_Shot_Library_SetConfig(U16 u16Level1Time, U16 u16Level2Time, U16 u16LevelMaxTime, U16 u16Level1Score, U16 u16Level2Score, U16 u16Level3Scroe);
#endif  //GAME_SHOT

#endif // GAME_ENABLE

