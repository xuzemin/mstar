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

/******************************************************************************/
/*   Header Files                                                                                                           */
/******************************************************************************/

#include "Board.h"

#if (GAME_ENABLE && GAME_TETRIS)
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "Utl.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_OSD.h"
#include "MApp_SaveData.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "MApp_Game_lib.h"
#include "MApp_Game_Tetris.h"

/******************************************************************************/
/*   Local Defines                                                                                                         */
/******************************************************************************/

#define LINE_WIDTH                          2

#define PAUSE_BAR_WIDTH                     400
#define PAUSE_BAR_HEIGHT                    40

BOOLEAN bTetrisGameOver = FALSE;
BOOLEAN bIsGameTetrisPaused = FALSE;
BOOLEAN gbEnableTetrisTask = TRUE;

TetrisArrayBoard* TetrisBoard = NULL;

U32 FrameTime;

U8 gu8TetrisKey = EN_GAME_KEY_NULL;

U8 au8BufferCells[TETRIS_GRID_SIZE][TETRIS_GRID_SIZE];    /* used to judge if can rotate block */

Block* stCurrBlock = NULL;          /* current moving block */
Block* stNextBlock = NULL;          /* next Block to appear */

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define CellSize                            (12 * 2)
#define BoardLeft                           150
#define BoardTop                            60

/* Next block grid */
#define GridBoardLeft                       632
#define GridBoardTop                        60

/* Score board position */
#define ScoreBoardLeft                      (650-CellSize/2)
#define ScoreBoardTop                       (230-CellSize/2)
#define ScoreBoardWidth                     (CellSize*5)
#define ScoreBoardHeight                    (CellSize)

#define RankBlockTop                        (190-CellSize/2)

/* Infor text postion */
#define InfoLeft                            (ScoreBoardLeft)
#define InfoTop                             (ScoreBoardTop+ScoreBoardHeight+CellSize/6)
#define INFO_TEXT_WIDTH                     80
#define INFO_TEXT_HEIGHT                    24

#define TETRIS_PASS_BAR_WIDTH               500
#define TETRIS_PASS_BAR_HEIGHT              60

#define TETRIS_INFO_BMP_SIZE                20

#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
#define CellSize                            (18 * 2)
#define BoardLeft                           200
#define BoardTop                            80

/* next block grid */
#define GridBoardLeft                       900
#define GridBoardTop                        80

/* score board position */
#define ScoreBoardLeft                      (900-CellSize/2)
#define ScoreBoardTop                       (300-CellSize/2)
#define ScoreBoardWidth                     (CellSize*5)
#define ScoreBoardHeight                    (CellSize)

/* Rank background position*/
#define RankBlockTop                        (260-CellSize/2)

/* infor text postion */
#define InfoLeft                            (ScoreBoardLeft)
#define InfoTop                             (ScoreBoardTop+ScoreBoardHeight+CellSize/6)

#define INFO_TEXT_WIDTH                     100
#define INFO_TEXT_HEIGHT                    30

#define TETRIS_PASS_BAR_WIDTH               800
#define TETRIS_PASS_BAR_HEIGHT              100

#define TETRIS_INFO_BMP_SIZE                30

#endif  //UI_SKIN_SEL

/******************************************************************************/
/*   Extern Function                                                                                                        */
/******************************************************************************/

/* the data structure of the block */

//===============Library global parameter===================
extern Tetris_Library_Para* stInitLibPara;
//==================================================
extern GRAPHIC_DC pdc_Game;
extern EN_GAME_RANK gu8CurrentGameLevel;

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
static DRAW_FILL_RECT Tetris_FillRect_List[] =
{
    {//BG color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//FG color
        0x0000000B,
        0x0000000B,
        OSD_GRADIENT_DISABLE
    },
    {//game over color
        0x0000002D,
        0x0000002D,
        OSD_GRADIENT_DISABLE
    },
    {//empty
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//T color
        0x000000AA,
        0x000000AA,
        OSD_GRADIENT_DISABLE
    },
    {//L color
        0x00000093,
        0x00000093,
        OSD_GRADIENT_DISABLE
    },
    {//J color
        0x00000044,
        0x00000044,
        OSD_GRADIENT_DISABLE
    },
    {//Z color
        0x000000C2,
        0x000000C2,
        OSD_GRADIENT_DISABLE
    },
    {//5 color
        0x0000006A,
        0x0000006A,
        OSD_GRADIENT_DISABLE
    },
    {//O color
        0x00000098,
        0x00000098,
        OSD_GRADIENT_DISABLE
    },
    {//I color
        0x00000035,
        0x00000035,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Tetris_Rect_Border_List[] =
{
    {//BG
        0x0000000B, // colorLeftTop;
        0x0000000B, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
    {//FG
        0x00000007, // colorLeftTop;
        0x00000007, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Tetris_Text_List[] =
{
    {//info string
       FONT_NORMAL, // eSystemFont;
       NULL, // pString;
       0x00000030, // TextColor;
       eTextAlignMiddle, // eTextAttrib;
       (GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP), // flag;
       2, // u8dis;
       EN_STRING_ENDING_3_DOT // u8dots
    },

};
static DRAW_BITMAP Tetris_Bitmap_List[] =
{
    {//index0 Play
        E_BMP_DMP_BUTTON_ICON_PLAY,
        TRUE,
        0,
        0,
        255
     },
     {//index1 Pause
        E_BMP_DMP_BUTTON_ICON_PAUSE,
        TRUE,
        0,
        0,
        255
     },
     {//index2 Left
        E_BMP_MENU_IMG_MENU_LEFT_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index3 Right
        E_BMP_MENU_IMG_MENU_RIGHT_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index4 Down
        E_BMP_MENU_IMG_GRIDE_UP_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index5 Up
        E_BMP_MENU_IMG_GRIDE_DOWN_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index6 OK
        E_BMP_BOTTON_OK,
        TRUE,
        5,
        5,
        255
     },
     {//index7 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0,
        0,
        255
     },
};

#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Tetris_FillRect_List[] =
{
    {//BG color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//FG color
        0x004F535F,
        0x004F535F,
        OSD_GRADIENT_DISABLE
    },
    {//game over color
        0x009CA3B5,
        0x009CA3B5,
        OSD_GRADIENT_DISABLE
    },
    {//empty
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//T color
        0x00EE82EE,
        0x00EE82EE,
        OSD_GRADIENT_DISABLE
    },
    {//L color
        0x00F0E68C,
        0x00F0E68C,
        OSD_GRADIENT_DISABLE
    },
    {//J color
        0x0000FFFF,
        0x0000FFFF,
        OSD_GRADIENT_DISABLE
    },
    {//Z color
        0x00FF0000,
        0x00FF0000,
        OSD_GRADIENT_DISABLE
    },
    {//5 color
        0x0000FF00,
        0x0000FF00,
        OSD_GRADIENT_DISABLE
    },
    {//O color
        0x00FF8C00,
        0x00FF8C00,
        OSD_GRADIENT_DISABLE
    },
    {//I color
        0x00008B8B,
        0x00008B8B,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Tetris_Rect_Border_List[] =
{
    {//BG
        0x00000000, // colorLeftTop;
        0x00000000, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
    {//FG
        0x004F535F, // colorLeftTop;
        0x004F535F, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Tetris_Text_List[] =
{
    {//info string
       FONT_NORMAL, // eSystemFont;
       NULL, // pString;
       0x00FFFFFF, // TextColor;
       eTextAlignMiddle, // eTextAttrib;
       (GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP), // flag;
       2, // u8dis;
       EN_STRING_ENDING_3_DOT // u8dots
    },

};
static DRAW_BITMAP Tetris_Bitmap_List[] =
{
    {//index0 Play
        E_BMP_DMP_BUTTON_ICON_PLAY,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index1 Pause
        E_BMP_DMP_BUTTON_ICON_PAUSE,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index2 Left
        E_BMP_MENU_IMG_MENU_LEFT_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index3 Right
        E_BMP_MENU_IMG_MENU_RIGHT_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index4 DOWN
        E_BMP_MENU_IMG_MENU_UP_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index5 Up
        E_BMP_MENU_IMG_GRIDE_DOWN_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index6 OK
        E_BMP_BOTTON_OK,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index7 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
};

#endif  //UI_SKIN_SEL

/******************************************************************************/
/*   Local Function                                                                                                        */
/******************************************************************************/

DRAW_FILL_RECT MApp_Tetris_GetElementColor(EN_TETRIS_ELEMENTS enElementName)
{
    switch (enElementName)
    {
        case EN_TETRIS_T://block->color = Violet;
            return Tetris_FillRect_List[4];
            break;
        case EN_TETRIS_L://block->color = Khaki;
            return Tetris_FillRect_List[5];
            break;
        case EN_TETRIS_J: //block->color = Blue;
            return Tetris_FillRect_List[6];
            break;
        case EN_TETRIS_Z://block->color = Red;
            return Tetris_FillRect_List[7];
            break;
        case EN_TETRIS_5:    //block->color = Green;
            return Tetris_FillRect_List[8];
            break;
        case EN_TETRIS_O: //block->color = Orange;
            return Tetris_FillRect_List[9];
            break;
        case EN_TETRIS_I: //block->color = Cyan;
            return Tetris_FillRect_List[10];
            break;
        default :
            return Tetris_FillRect_List[0];
            break;
    }
}

void MApp_Tetris_DrawBlockFillRect(U16 u16Left, U16 u16Top, U16 u16Width, U16 u16Height, EN_TETRIS_ELEMENTS enElementName)
{
    RECT rect;
    DRAW_FILL_RECT paramFillRect = MApp_Tetris_GetElementColor(enElementName);
    RECT_SET(rect, u16Left,u16Top,u16Width,u16Height);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, &paramFillRect, &pdc_Game, &rect);
}

void MApp_Tetris_DrawBGFillRect(U16 u16Left, U16 u16Top, U16 u16Width, U16 u16Height)
{
    DRAW_FILL_RECT* paramFillRect = &Tetris_FillRect_List[0];
    RECT rect;
    RECT_SET(rect, u16Left,u16Top,u16Width,u16Height);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
}

/* draw the block */
void MApp_Tetris_DrawBlock(Block *block, int bdLeft, int bdTop)
{
    int i, j;

    for (i = 0; i < (int)block->enGridSize; i++)
    {
        for (j = 0; j < (int)block->enGridSize; j++)
        {
            if (block->au8Grid[i][j] && (block->y + j) >= 0)
            {
                MApp_Tetris_DrawBlockFillRect(
                 (bdLeft + stInitLibPara->u16CellSize*(i + block->x) + stInitLibPara->u16LineWidth + 1),
                 (bdTop + stInitLibPara->u16CellSize*(j + block->y) + stInitLibPara->u16LineWidth + 1),
                 (stInitLibPara->u16CellSize - stInitLibPara->u16LineWidth * 2 + 1),
                 (stInitLibPara->u16CellSize - stInitLibPara->u16LineWidth * 2 + 1),
                 block->enElementName
                 );
            }
        }
    }
;
}

/* erase a block, only fill the filled cell with background color */
void MApp_Tetris_EraseBlock(Block *block, int bdLeft, int bdTop)
{
    int i, j;

    for (i = 0; i < (int)block->enGridSize; i++)
    {
        for (j = 0; j < (int)block->enGridSize; j++)
        {
            if (block->au8Grid[i][j] && (block->y + j) >= 0)
            {
                MApp_Tetris_DrawBGFillRect(
                     (bdLeft + stInitLibPara->u16CellSize*(i + block->x) + stInitLibPara->u16LineWidth + 1),
                     (bdTop + stInitLibPara->u16CellSize*(j + block->y) + stInitLibPara->u16LineWidth + 1),
                     (stInitLibPara->u16CellSize - stInitLibPara->u16LineWidth * 2 + 1),
                     (stInitLibPara->u16CellSize - stInitLibPara->u16LineWidth * 2 + 1)
                     );
            }
        }
    }
}


/* rotate the block, update the block struct data */
void MApp_Tetris_RotateCells(U8 u8grid[4][4], char blockSize)
{
    char temp;

    switch (blockSize)
    {
        case 3:
            temp = u8grid[0][0];
            u8grid[0][0] = u8grid[2][0];
            u8grid[2][0] = u8grid[2][2];
            u8grid[2][2] = u8grid[0][2];
            u8grid[0][2] = temp;

            temp = u8grid[0][1];
            u8grid[0][1] = u8grid[1][0],
            u8grid[1][0] = u8grid[2][1];
            u8grid[2][1] = u8grid[1][2];
            u8grid[1][2] = temp;
            break;
        case 4:    /* only 'I' block arived here! */
            u8grid[1][0] = 1 - u8grid[1][0];
            u8grid[1][2] = 1 - u8grid[1][2];
            u8grid[1][3] = 1 - u8grid[1][3];
            u8grid[0][1] = 1 - u8grid[0][1];
            u8grid[2][1] = 1 - u8grid[2][1];
            u8grid[3][1] = 1 - u8grid[3][1];
            break;
    }
}

/* judge if the block can move toward the direction */
BOOLEAN MApp_Tetris_CanMove(int dx, int dy)
{
    int i, j, tempX, tempY;

    for (i = 0;i < (int)stCurrBlock->enGridSize;i++)
    {
        for (j = 0;j < (int)stCurrBlock->enGridSize;j++)
        {
            if( stCurrBlock->au8Grid[i][j] )
            {
                /* cannot move leftward or rightward */
                tempX = stCurrBlock->x + i + dx;
                if (tempX < 0 || tempX > (stInitLibPara->u16BoardWidth- 1))
                    return FALSE; /* make sure x is valid! */

                /* cannot move downward */
                tempY = stCurrBlock->y + j + dy;
                if (tempY > (stInitLibPara->u16BoardHeight - 1))
                    return FALSE; /* y is only checked lower bound, maybe negative!!!! */

                /* the cell already filled, we must check Y's upper bound before check cell ! */
                if (tempY >= 0 && TetrisBoard->u32ArrayBoard[tempX][tempY][0])
                    return FALSE;
            }
        }
    }
    return TRUE;
}

/* judge if the block can rotate */
BOOLEAN MApp_Tetris_CanRotate(void)
{
    int i, j, tempX, tempY;

    /* update buffer */
    memcpy(au8BufferCells, stCurrBlock->au8Grid, sizeof(au8BufferCells));

    MApp_Tetris_RotateCells(au8BufferCells, stCurrBlock->enGridSize);

    for (i = 0;i < (int)stCurrBlock->enGridSize;i++)
    {
        for (j = 0;j < (int)stCurrBlock->enGridSize;j++)
        {
            if (au8BufferCells[i][j])
            {
                tempX = stCurrBlock->x + i;
                tempY = stCurrBlock->y + j;

                if (tempX < 0 || tempX > (stInitLibPara->u16BoardWidth - 1))
                    return FALSE;
                if (tempY > (stInitLibPara->u16BoardHeight - 1))
                    return FALSE;
                if (tempY >= 0 && TetrisBoard->u32ArrayBoard[tempX][tempY][0])
                    return FALSE;
            }
        }
    }
    return TRUE;
}

/* Rotate the block, if success, return true */
void MApp_Tetris_RotateBlock(Block *block)
{
    if (MApp_Tetris_CanRotate())
    {
        MApp_Tetris_EraseBlock(block, stInitLibPara->u16BoardLeft, stInitLibPara->u16BoardTop);
        memcpy(stCurrBlock->au8Grid, au8BufferCells, sizeof(au8BufferCells));
        MApp_Tetris_DrawBlock(block, stInitLibPara->u16BoardLeft, stInitLibPara->u16BoardTop);
    }
}

/* move by the direction if can, donothing if cannot
* return value: true - success, false - cannot move toward this direction*/
BOOLEAN MApp_Tetris_MoveBlock(Block *block, int dx, int dy)
{
    BOOLEAN bCanMove = MApp_Tetris_CanMove(dx, dy);

    if (bCanMove)
    {
        MApp_Tetris_EraseBlock(block, stInitLibPara->u16BoardLeft, stInitLibPara->u16BoardTop);
        block->x += dx;
        block->y += dy;
        MApp_Tetris_DrawBlock(block, stInitLibPara->u16BoardLeft, stInitLibPara->u16BoardTop);
    }

    return bCanMove;
}

/* drop the block to the bottom! */
void MApp_Tetris_DropBlock(Block *block)
{
    MApp_Tetris_EraseBlock(block, stInitLibPara->u16BoardLeft, stInitLibPara->u16BoardTop);
    while (MApp_Tetris_CanMove(0, 1))
    {
        block->y++;
    }
    MApp_Tetris_DrawBlock(block, stInitLibPara->u16BoardLeft, stInitLibPara->u16BoardTop);
}

/* set the isFilled and fillcolor data to the board */
void MApp_Tetris_FillBoardData(void)
{
    int i, j;

    for (i = 0;i < (int)stCurrBlock->enGridSize;i++)
    {
        for (j = 0;j < (int)stCurrBlock->enGridSize;j++)
        {
            if (stCurrBlock->au8Grid[i][j] && (stCurrBlock->y + j) >= 0)
            {
                TetrisBoard->u32ArrayBoard[stCurrBlock->x+i][stCurrBlock->y+j][0] = 1;
                TetrisBoard->u32ArrayBoard[stCurrBlock->x+i][stCurrBlock->y+j][1] = stCurrBlock->enElementName;
            }
        }
    }

}

void MApp_Tetris_UpdateFrame(void)
{
    /* Speed up the game when score is high, minimum is 400 */
    if( MApp_Game_GetGameLevel() == EN_GAME_RANK_EASY )
    {
        FrameTime = MAX(1600 - 100 * (MApp_Tetris_GetScore() / 200), 400);
    }
    else if( MApp_Game_GetGameLevel() == EN_GAME_RANK_HARD )
    {
        FrameTime = MAX(1000 - 100 * (MApp_Tetris_GetScore() / 200), 400);
    }
    else    // Rank : Normal
    {
        FrameTime = MAX(1300 - 100 * (MApp_Tetris_GetScore() / 200), 400);
    }
}

U32 MApp_Tetris_GetFrameTime(void)
{
    return FrameTime;
}

/* we call this function when a block is inactive. */
void MApp_Tetris_UpdateBoard(void)
{
    MApp_Tetris_FillBoardData();
    MApp_Tetris_UpdateFrame();
    MApp_Tetris_CheckBoard();
}

/* create a new block by key number,
* the block anchor to the top-left corner of 4*4 cells
*/
void MApp_Tetris_GenerateBlock(Block *block)
{
    EN_TETRIS_ELEMENTS enSeed = (EN_TETRIS_ELEMENTS)(msAPI_Timer_GetTime0() % EN_TETRIS_ELEMENTS_NUM + 1) ;

    memset(block->au8Grid, 0, sizeof(block->au8Grid));
    block->enElementName = enSeed;
    switch (enSeed)
    {
        case EN_TETRIS_T://block->color = Violet;
            block->enGridSize = ELEMENTS_GRID_3X3;
            block->au8Grid[1][0] = 1;
            block->au8Grid[1][1] = 1;
            block->au8Grid[2][1] = 1;
            block->au8Grid[1][2] = 1;
            break;
        case EN_TETRIS_L://block->color = Khaki;
            block->enGridSize = ELEMENTS_GRID_3X3;
            block->au8Grid[1][0] = 1;
            block->au8Grid[1][1] = 1;
            block->au8Grid[1][2] = 1;
            block->au8Grid[2][2] = 1;
            break;
        case EN_TETRIS_J: //block->color = Blue;
            block->enGridSize = ELEMENTS_GRID_3X3;
            block->au8Grid[1][0] = 1;
            block->au8Grid[1][1] = 1;
            block->au8Grid[1][2] = 1;
            block->au8Grid[0][2] = 1;
            break;
        case EN_TETRIS_Z://block->color = Red;
            block->enGridSize = ELEMENTS_GRID_3X3;
            block->au8Grid[0][0] = 1;
            block->au8Grid[1][0] = 1;
            block->au8Grid[1][1] = 1;
            block->au8Grid[2][1] = 1;
            break;
        case EN_TETRIS_5:    //block->color = Green;
            block->enGridSize = ELEMENTS_GRID_3X3;
            block->au8Grid[1][0] = 1;
            block->au8Grid[2][0] = 1;
            block->au8Grid[0][1] = 1;
            block->au8Grid[1][1] = 1;
            break;
        case EN_TETRIS_O: //block->color = Orange;
            block->enGridSize = ELEMENTS_GRID_2X2;
            block->au8Grid[0][0] = 1;
            block->au8Grid[1][0] = 1;
            block->au8Grid[0][1] = 1;
            block->au8Grid[1][1] = 1;
            break;
        case EN_TETRIS_I: //block->color = Cyan;
            block->enGridSize = ELEMENTS_GRID_4X4;
            block->au8Grid[1][0] = 1;
            block->au8Grid[1][1] = 1;
            block->au8Grid[1][2] = 1;
            block->au8Grid[1][3] = 1;
            break;
        default :
            break;
    }

}

/* get next block! */
void MApp_Tetris_NextBlock(void)
{
    /* copy the nextBlock to curBlock */
    memcpy(stCurrBlock, stNextBlock, sizeof(Block));
    stCurrBlock->enElementName = stNextBlock->enElementName;
    stCurrBlock->x = (TETRIS_BOARD_WIDTH - 4) / 2;
    stCurrBlock->y = -stCurrBlock->enGridSize;
    /* generate nextBlock and show it */
    MApp_Tetris_EraseBlock(stNextBlock, GridBoardLeft, GridBoardTop);
    MApp_Tetris_GenerateBlock(stNextBlock);
    MApp_Tetris_DrawBlock(stNextBlock, GridBoardLeft, GridBoardTop);
}

/* draw one line of the board */
void MApp_Tetris_PaintBoard(void)
{
    int i, j;
    DRAW_FILL_RECT paramFillRect;
    memset(&paramFillRect,0,sizeof(DRAW_FILL_RECT));
    for (j = 0;j < TETRIS_BOARD_HEIGHT; j++)
    {
        for (i = 0;i < TETRIS_BOARD_WIDTH; i++)
        {
            paramFillRect = MApp_Tetris_GetElementColor((EN_TETRIS_ELEMENTS)TetrisBoard->u32ArrayBoard[i][j][1]);

            RECT rect;
            RECT_SET(rect,
                     BoardLeft + i*CellSize + LINE_WIDTH + 1,
                     BoardTop + j*CellSize + LINE_WIDTH + 1,
                     CellSize - LINE_WIDTH * 2 + 1,
                     CellSize - LINE_WIDTH * 2 + 1);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, &paramFillRect, &pdc_Game, &rect);
        }
    }
}

void MApp_Tetris_DrawPauseInfo(BOOLEAN bEn)
{
    DRAW_FILL_RECT* paramFillRect = &Tetris_FillRect_List[0];
    RECT rect;
    RECT_SET(rect, (getmaxx() - PAUSE_BAR_WIDTH) , 0, PAUSE_BAR_WIDTH, PAUSE_BAR_HEIGHT);
    if(bEn)
    {
         paramFillRect = &Tetris_FillRect_List[2];
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

        DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Tetris_Text_List[0];
        U8 u8Txt[128];
        U16 u16TmpStr[128];
        sprintf((char*)u8Txt, "%s", "Paused !\a [Play] to continue.");
        MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
        paramTextOut->pString = (LPTSTR)u16TmpStr;
        _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
    }
    else
    {
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }
}

void MApp_Tetris_DrawGameOver(void)
{
    U16 scrx = getmaxx(), scry = getmaxy();

    RECT rect;
    RECT_SET(rect, (scrx - TETRIS_PASS_BAR_WIDTH) / 2, (scry - TETRIS_PASS_BAR_HEIGHT) / 2, TETRIS_PASS_BAR_WIDTH, TETRIS_PASS_BAR_HEIGHT);
    DRAW_FILL_RECT* paramFillRect = &Tetris_FillRect_List[2];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    U16 u16TmpStr[128];
    U8 u8Txt[128];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Tetris_Text_List[0];

    sprintf((char*)u8Txt, "Game Over !\a [OK] try again [EXIT] have a rest.");
    MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
    paramTextOut->pString = (LPTSTR)u16TmpStr;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}
/* display the score */
void MApp_Tetris_DisplayScore(void)
{
    char cstring[20];
    DRAW_FILL_RECT* paramFillRect = &Tetris_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Tetris_Text_List[0];
    LPTSTR pstringBuffer = CHAR_BUFFER;
    RECT rect;
    RECT_SET(rect, ScoreBoardLeft, ScoreBoardTop, ScoreBoardWidth, ScoreBoardHeight);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    sprintf((char *)cstring, "Score : %d", MApp_Tetris_GetScore());
    MApp_U8StringToU16String((MS_U8*)cstring, (MS_U16*)pstringBuffer, strlen(cstring));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}
static void MApp_Tetris_InitGame(void)
{
    U8 u8Index;
    char cstring_rank[20];
    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Tetris_FillRect_List[0];
    DRAW_RECT_BORDER* paramRectBorder = &Tetris_Rect_Border_List[0];
    DRAW_BITMAP* paramBitmap = &Tetris_Bitmap_List[0];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Tetris_Text_List[0];
    LPTSTR pstringBuffer = CHAR_BUFFER;
    OSDClrLine pstLineAttr;

    /* Draw board cells */
    memset(&pstLineAttr, 0, sizeof(OSDClrLine));

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    pstLineAttr.u32LineColor = 0x0000002D;
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
    pstLineAttr.u32LineColor = 0xFFFFFFFF;
#endif  //UI_SKIN_SEL
    pstLineAttr.u8LineWidth = LINE_WIDTH;

    RECT_SET(rect, 0, 0, getmaxx(), getmaxy());
    paramFillRect = &Tetris_FillRect_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Tetris", (U16*)pstringBuffer, strlen("Tetris"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SET(rect, BoardLeft-CellSize, BoardTop-CellSize, TETRIS_BOARD_WIDTH*CellSize+CellSize*2, TETRIS_BOARD_HEIGHT*CellSize+CellSize*2);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    for (u8Index = 0; u8Index <= TETRIS_BOARD_WIDTH; u8Index++)
    {
        pstLineAttr.x1 = BoardLeft + u8Index*CellSize;
        pstLineAttr.y1 = BoardTop;
        pstLineAttr.x2   = BoardLeft + u8Index*CellSize;
        pstLineAttr.y2   = BoardTop + TETRIS_BOARD_HEIGHT*CellSize;
        msAPI_OSD_DrawLine(&pstLineAttr);
    }

    for (u8Index = 0; u8Index <= TETRIS_BOARD_HEIGHT; u8Index++)
    {
        pstLineAttr.x1 = BoardLeft;
        pstLineAttr.y1 = BoardTop + u8Index*CellSize;
        pstLineAttr.x2   = BoardLeft + TETRIS_BOARD_WIDTH*CellSize;
        pstLineAttr.y2   = BoardTop + u8Index*CellSize;
        msAPI_OSD_DrawLine(&pstLineAttr);

    }
    /* Draw next block  bg */
    RECT_SET(rect, GridBoardLeft-CellSize, GridBoardTop-CellSize, CellSize*6, CellSize*6);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    /* Draw next block grids */
    for (u8Index = 0;u8Index <= TETRIS_GRID_SIZE;u8Index++)
    {
        pstLineAttr.x1 = GridBoardLeft + u8Index*CellSize;
        pstLineAttr.y1 = GridBoardTop;
        pstLineAttr.x2 = GridBoardLeft + u8Index*CellSize;
        pstLineAttr.y2 = GridBoardTop + TETRIS_GRID_SIZE*CellSize;
        msAPI_OSD_DrawLine(&pstLineAttr);

        pstLineAttr.x1 = GridBoardLeft;
        pstLineAttr.y1 = GridBoardTop + u8Index*CellSize;
        pstLineAttr.x2 = GridBoardLeft + TETRIS_GRID_SIZE*CellSize;
        pstLineAttr.y2 = GridBoardTop + u8Index*CellSize;
        msAPI_OSD_DrawLine(&pstLineAttr);
    }

    /* Draw Rank block background */
    paramFillRect = &Tetris_FillRect_List[1];
    RECT_SET(rect, ScoreBoardLeft, RankBlockTop, ScoreBoardWidth, ScoreBoardHeight);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    /* Draw Rank block text */
    RECT_SET(rect, ScoreBoardLeft, RankBlockTop, ScoreBoardWidth, ScoreBoardHeight);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring_rank, " Rank: %s", (MApp_Game_GetGameLevel()==EN_GAME_RANK_EASY)?"Easy":((MApp_Game_GetGameLevel()==EN_GAME_RANK_NORMAL)?"Normal":"Hard"));
    MApp_U8StringToU16String((U8*)cstring_rank, (U16*)paramTextOut->pString, strlen(cstring_rank));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    /* Draw score rect */
    MApp_Tetris_DisplayScore();

    MApp_Tetris_GenerateBlock(stNextBlock);
    MApp_Tetris_NextBlock();    /* create first block */

    RECT_SET(rect, InfoLeft, InfoTop, ScoreBoardWidth, ScoreBoardHeight);
    _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);

    for (u8Index = 1; u8Index < 8; u8Index++)
    {
        RECT_SHIFT(rect, 0, ScoreBoardHeight+ScoreBoardHeight/6);
        _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);
    }

    RECT_SET(rect, InfoLeft+CellSize/2, InfoTop+CellSize/9, TETRIS_INFO_BMP_SIZE, TETRIS_INFO_BMP_SIZE);

    for (u8Index = 0; u8Index < 8; u8Index++)
    {
        paramBitmap = &Tetris_Bitmap_List[u8Index];
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
        RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    }

    paramTextOut = &Tetris_Text_List[0];

    RECT_SET(rect, InfoLeft+CellSize*2, InfoTop, INFO_TEXT_WIDTH, INFO_TEXT_HEIGHT);
    MApp_U8StringToU16String((U8*)"Play", (U16*)pstringBuffer, strlen("Play"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Pause", (U16*)pstringBuffer, strlen("Pause"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Left", (U16*)pstringBuffer, strlen("Left"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Right", (U16*)pstringBuffer, strlen("Right"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Rotate", (U16*)pstringBuffer, strlen("Rotate"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Down", (U16*)pstringBuffer, strlen("Down"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Drop", (U16*)pstringBuffer, strlen("Drop"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ScoreBoardHeight+CellSize/6);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

BOOLEAN MApp_Tetris_Init(void)
{
    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_TETRIS_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Tetris support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_TETRIS), u16Ver));

    if( MApp_Game_GetGameLevel() == EN_GAME_RANK_EASY )
    {
        FrameTime = 1600;
    }
    else if( MApp_Game_GetGameLevel() == EN_GAME_RANK_HARD )
    {
        FrameTime = 1000;
    }
    else
    {
        FrameTime = 1300;
    }

    bTetrisGameOver = FALSE;
    bIsGameTetrisPaused = FALSE;
    gbEnableTetrisTask = TRUE;
    gu8TetrisKey = EN_GAME_KEY_NULL;

    //MApp_Tetris_Library_Init();
    stCurrBlock = msAPI_Memory_Allocate(sizeof(Block), BUF_ID_APP_GAME);
    if( stCurrBlock == NULL )
    {
        printf("\nError:stCurrBlock malloc failed!\n");
        return FALSE;
    }
    memset(stCurrBlock, 0, sizeof(Block));

    stNextBlock = msAPI_Memory_Allocate(sizeof(Block), BUF_ID_APP_GAME);
    if( stNextBlock == NULL )
    {
        printf("\nError:stNextBlock malloc failed!\n");
        return FALSE;
    }
    memset(stNextBlock, 0, sizeof(Block));

    stInitLibPara = msAPI_Memory_Allocate(sizeof(Tetris_Library_Para), BUF_ID_APP_GAME);
    if( stInitLibPara == NULL )
    {
        printf("\nError:stInitLibPara malloc failed!\n");
        return FALSE;
    }
    memset(stInitLibPara, 0, sizeof(Tetris_Library_Para));

    TetrisBoard = msAPI_Memory_Allocate(sizeof(Tetris_Library_Para), BUF_ID_APP_GAME);
    if( TetrisBoard == NULL )
    {
        printf("\nError:TetrisBoard malloc failed!\n");
        return FALSE;
    }
    memset(TetrisBoard, 0, sizeof(TetrisArrayBoard));
    memset(au8BufferCells, 0, sizeof(au8BufferCells));

    U32* u32TetrisBoard = &TetrisBoard->u32ArrayBoard[0][0][0];

    stInitLibPara->u16LineWidth = LINE_WIDTH;
    stInitLibPara->u16BoardWidth = TETRIS_BOARD_WIDTH;
    stInitLibPara->u16BoardHeight = TETRIS_BOARD_HEIGHT;
    stInitLibPara->u16GridSize = TETRIS_GRID_SIZE;
    stInitLibPara->u16CellSize = CellSize;
    stInitLibPara->u16BoardLeft = BoardLeft;
    stInitLibPara->u16BoardTop = BoardTop;
    stInitLibPara->u16GridBoardLeft = GridBoardLeft;
    stInitLibPara->u16GridBoardTop = GridBoardTop;

    MApp_Tetris_InitGame();
    MApp_Tetris_Library_SetPara(u32TetrisBoard, TETRIS_BOARD_WIDTH, TETRIS_BOARD_HEIGHT, TETRIS_BLOCK_INFO_ITEM);
    MApp_Tetris_Library_Init();
    return TRUE;
}

void MApp_Tetris_MainTask(void)
{
    static U32 Timertick = 0;
    if(bTetrisGameOver && gu8TetrisKey == EN_GAME_KEY_SELECT)
    {
        MApp_Tetris_Init();
    }

    if(gu8TetrisKey == EN_GAME_KEY_PAUSE && !bIsGameTetrisPaused)
    {
       bIsGameTetrisPaused = TRUE;
       MApp_Tetris_DrawPauseInfo(bIsGameTetrisPaused);
    }
    else if(gu8TetrisKey == EN_GAME_KEY_PLAY && bIsGameTetrisPaused)
    {
       bIsGameTetrisPaused = FALSE;
       MApp_Tetris_DrawPauseInfo(bIsGameTetrisPaused);
    }

    if(!gbEnableTetrisTask || bTetrisGameOver || bIsGameTetrisPaused || MApp_Game_IsShowExitWarningInfo())
           return;

    /* wait until a key pressed */
    if (gu8TetrisKey == EN_GAME_KEY_NULL)
    {
        Timertick += 1;

        if (Timertick >= MApp_Tetris_GetFrameTime())
        {
            /* our block has dead! (can't move down), we get next block */
            if (!MApp_Tetris_MoveBlock(stCurrBlock, 0, 1))
            {
                MApp_Tetris_UpdateBoard();
                MApp_Tetris_PaintBoard();
                MApp_Tetris_DisplayScore();
                MApp_Tetris_NextBlock();

                if (!MApp_Tetris_CanMove(0, 1))
                {
                    bTetrisGameOver = TRUE;
                    MApp_Tetris_DrawGameOver();
                    return;
                }
            }
            Timertick = 0;
        }
        msAPI_Timer_DelayUs(500);
    }
    else
    {
        switch (gu8TetrisKey)
        {
            case EN_GAME_KEY_LEFT:
                MApp_Tetris_MoveBlock(stCurrBlock, -1, 0);
                break;
            case EN_GAME_KEY_RIGHT:
                MApp_Tetris_MoveBlock(stCurrBlock, 1, 0);
                break;
            case EN_GAME_KEY_DOWN:
                MApp_Tetris_MoveBlock(stCurrBlock, 0, 1);
                break;
            case EN_GAME_KEY_UP:
                MApp_Tetris_RotateBlock(stCurrBlock);
                break;
            case EN_GAME_KEY_SELECT:
                MApp_Tetris_DropBlock(stCurrBlock);
                break;
        }
    }
    gu8TetrisKey = EN_GAME_KEY_NULL;
}

BOOLEAN MApp_Tetris_DeInit(void)
{
    if(gbEnableTetrisTask)
    {
        if( stCurrBlock )
        {
            msAPI_Memory_Free( stCurrBlock, BUF_ID_APP_GAME );
            stCurrBlock = NULL;
        }
        if( stNextBlock )
        {
            msAPI_Memory_Free( stNextBlock, BUF_ID_APP_GAME );
            stNextBlock = NULL;
        }
        if( stInitLibPara )
        {
            msAPI_Memory_Free( stInitLibPara, BUF_ID_APP_GAME );
            stInitLibPara = NULL;
        }
        if( TetrisBoard )
        {
            msAPI_Memory_Free( TetrisBoard, BUF_ID_APP_GAME );
            TetrisBoard = NULL;
        }
        gbEnableTetrisTask = FALSE;
        bTetrisGameOver = FALSE;
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

BOOLEAN MApp_Tetris_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8TetrisKey = enGameKey;
    return TRUE;
}

BOOLEAN MApp_Tetris_IsGameOver(void)
{
    return bTetrisGameOver;
}

#endif
