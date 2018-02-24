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

/*******************************COMMENTS**********************************/
// sudoku_game.c
// it is a game for entermainment.
/*************************************************************************/

/******************************************************************************/
/*   Header Files                                                                                                           */
/******************************************************************************/

#include "Board.h"

#if ( GAME_ENABLE && GAME_SUDOKU )
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "MApp_Game_Sudoku.h"
#include "SysInit.h"
#include "Utl.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "MApp_SaveData.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Key.h"
#include "MApp_IR.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "MApp_Game_Main.h"
#include "MApp_Game_lib.h"

/******************************************************************************/
/*   Local Defines                                                                                                         */
/******************************************************************************/

#define SUDOKU_DEBUG(x)     //x

#define MAP_NUM             9       //Max 9*9

#define SUDOKU_MAP_X_NUM    16      // Block numbers in map X position
//#define SUDOKU_MAP_Y_NUM           12      // Block numbers in map Y position

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define GAME_AREA_X         75     // Game X Left-Top position
                                    /* ((getmaxx() - BLOCK_X * SUDOKU_MAP_X_NUM) / 3)*/
#define GAME_AREA_Y         75     // Game Y Left-Top position

#define BLOCK_X             35      // Block width
#define BLOCK_Y             35      // Block height

#define PASS_BAR_WIDTH      500     // Game Win message box width
#define PASS_BAR_HEIGHT     60     // Game Win message box height
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
#define GAME_AREA_X         125     // Game X Left-Top position
                                    /* ((getmaxx() - BLOCK_X * SUDOKU_MAP_X_NUM) / 3)*/
#define GAME_AREA_Y         125     // Game Y Left-Top position

#define BLOCK_X             40      // Block width
#define BLOCK_Y             40      // Block height

#define PASS_BAR_WIDTH      800     // Game Win message box width
#define PASS_BAR_HEIGHT     100     // Game Win message box height
#endif  //UI_SKIN_SEL

#define SUDOKU_MAX_LEVEL    5       // Sudoku Game max level
#define SUDOKU_TIMER_SPEED  100000  // Sudoku GameTimer refresh time

static char *_SudokuBuf = NULL;

static U8 CursorX = 0, CursorY = 0;
static U16 SudokuNowLevel = 0;
static U32 StartTime = 0;

typedef char Sudoku_Map[MAP_NUM][MAP_NUM];

EN_GAME_KEY gu8SudokuKey = EN_GAME_KEY_NULL;

BOOLEAN gbSudokuPass = FALSE;
BOOLEAN gbEnableSudokuTask = FALSE;
BOOLEAN gbSudokuStop = FALSE;

extern GRAPHIC_DC pdc_Game;
extern EN_GAME_RANK gu8CurrentGameLevel;

/*************************/
/*       Easy Sudoku Map       */
/************************/

static char Map_Level0[MAP_NUM][MAP_NUM] =
{
    {0,6,0,0,0,3,9,0,0},
    {4,0,0,6,0,0,0,1,0},
    {5,7,0,1,4,0,0,2,6},
  /*-------------------*/
    {0,9,0,0,0,2,0,0,3},
    {7,2,0,0,0,1,0,5,9},
    {6,0,0,0,9,5,0,7,0},
  /*-------------------*/
    {9,1,0,0,5,6,0,3,4},
    {0,5,0,0,0,4,0,0,8},
    {0,0,6,3,0,0,0,9,0},
};

static char Map_Level1[MAP_NUM][MAP_NUM] =
{
    {0,6,0,0,0,8,1,0,2},
    {8,0,0,5,0,0,0,0,3},
    {0,2,0,0,0,9,0,6,0},
  /*-------------------*/
    {0,4,0,8,0,1,0,9,0},
    {5,0,0,0,9,0,0,0,6},
    {0,9,0,0,5,0,0,8,0},
  /*-------------------*/
    {0,1,0,6,0,0,0,2,0},
    {3,0,0,0,0,5,0,0,4},
    {6,0,9,4,0,0,0,3,0},
};

static char Map_Level2[MAP_NUM][MAP_NUM] =
{
    {0,8,0,0,2,0,7,0,0},
    {0,0,0,0,0,9,0,5,0},
    {4,0,0,0,0,8,0,1,0},
  /*-------------------*/
    {0,5,0,4,0,0,0,0,2},
    {0,4,0,0,9,1,0,3,0},
    {7,0,0,6,0,0,0,4,0},
  /*-------------------*/
    {0,1,0,3,0,0,0,0,4},
    {0,7,0,9,0,0,0,0,0},
    {0,0,6,0,4,0,0,8,0},
};

static char Map_Level3[MAP_NUM][MAP_NUM] =
{
    {0,0,0,0,6,0,2,0,0},
    {5,0,0,4,0,0,0,8,0},
    {0,0,2,0,0,9,0,6,0},
  /*-------------------*/
    {0,0,1,0,2,0,0,5,0},
    {6,0,0,1,0,0,0,0,4},
    {0,2,0,0,3,7,9,0,0},
  /*-------------------*/
    {0,9,0,3,0,0,1,0,0},
    {0,8,0,0,0,5,0,0,2},
    {0,0,3,0,4,0,0,0,0},
};

static char Map_Level4[MAP_NUM][MAP_NUM] =
{
    {0,0,9,0,2,0,8,0,0},
    {7,0,0,0,0,8,5,0,0},
    {0,0,0,7,0,0,0,0,2},
  /*-------------------*/
    {2,0,0,9,5,0,7,0,0},
    {0,3,0,0,0,7,0,1,0},
    {0,0,8,0,0,2,0,0,4},
  /*-------------------*/
    {3,0,0,0,0,9,0,0,0},
    {0,0,4,1,0,0,0,0,6},
    {0,0,2,0,6,0,9,0,0},
};

static char Map_Level5[MAP_NUM][MAP_NUM] =
{
    {0,2,0,0,7,0,3,0,0},
    {0,0,5,0,0,0,6,0,0},
    {0,9,0,4,0,0,0,0,0},
  /*-------------------*/
    {7,0,0,0,0,8,0,4,0},
    {0,0,6,0,0,0,1,0,0},
    {0,4,0,3,0,0,0,0,9},
  /*-------------------*/
    {0,0,0,0,0,3,0,6,0},
    {0,0,3,0,0,0,5,0,0},
    {0,0,9,0,5,0,0,7,0},
};

Sudoku_Map* g_Sudoku_MapData[SUDOKU_MAX_LEVEL+1] =
{
    &Map_Level0,
    &Map_Level1,
    &Map_Level2,
    &Map_Level3,
    &Map_Level4,
    &Map_Level5,
};

/**************************/
/*      Normal Sudoku Map      */
/*************************/

static char Normal_Map_Level0[MAP_NUM][MAP_NUM] =
{
    {0,4,0,2,1,0,0,0,0},
    {8,0,7,0,0,0,0,9,0},
    {2,0,0,8,0,0,4,0,1},
  /*-------------------*/
    {3,0,0,0,0,2,9,0,5},
    {0,0,5,7,0,8,6,0,0},
    {7,0,6,5,0,0,0,0,4},
  /*-------------------*/
    {5,0,1,0,0,4,0,0,9},
    {0,6,0,0,0,0,7,0,8},
    {0,0,0,0,2,7,0,5,0},
};

static char Normal_Map_Level1[MAP_NUM][MAP_NUM] =
{
    {0,0,0,0,0,0,6,5,0},
    {0,0,0,1,0,7,0,0,2},
    {0,5,0,9,6,8,1,0,4},
  /*-------------------*/
    {0,0,6,0,9,0,3,0,5},
    {0,7,0,6,0,3,0,8,0},
    {9,0,3,0,1,0,2,0,0},
  /*-------------------*/
    {3,0,7,5,2,9,0,1,0},
    {5,0,0,4,0,1,0,0,0},
    {0,4,1,0,0,0,0,0,0},
};

static char Normal_Map_Level2[MAP_NUM][MAP_NUM] =
{
    {7,9,0,1,0,0,8,0,5},
    {2,0,0,4,0,0,0,7,0},
    {0,0,4,0,0,0,0,0,2},
  /*-------------------*/
    {0,2,0,5,0,0,0,1,0},
    {3,1,0,8,0,6,0,9,4},
    {0,8,0,0,0,1,0,5,0},
  /*-------------------*/
    {5,0,0,0,0,0,9,0,0},
    {0,4,0,0,0,9,0,0,6},
    {9,0,8,0,0,5,0,3,7},
};

static char Normal_Map_Level3[MAP_NUM][MAP_NUM] =
{
    {0,0,0,0,4,0,0,6,9},
    {9,6,0,0,7,0,0,5,0},
    {0,1,5,0,0,9,2,0,0},
  /*-------------------*/
    {0,0,0,0,2,1,0,0,6},
    {4,0,7,0,0,0,8,0,1},
    {1,0,0,7,3,0,0,0,0},
  /*-------------------*/
    {0,0,9,3,0,0,5,1,0},
    {0,7,0,0,9,0,0,8,4},
    {5,3,0,0,1,0,0,0,0},
};

static char Normal_Map_Level4[MAP_NUM][MAP_NUM] =
{
    {6,0,4,1,2,0,3,9,0},
    {0,1,0,0,5,0,6,0,8},
    {0,0,0,6,0,8,0,0,0},
  /*-------------------*/
    {1,0,0,7,0,0,9,4,0},
    {0,0,6,8,0,3,7,0,0},
    {0,5,7,0,0,9,0,0,6},
  /*-------------------*/
    {0,0,0,4,0,1,0,0,0},
    {5,0,1,0,3,0,0,8,0},
    {0,4,9,0,7,2,1,0,3},
};

static char Normal_Map_Level5[MAP_NUM][MAP_NUM] =
{
    {5,7,0,0,1,0,3,0,0},
    {0,0,0,5,0,3,9,0,7},
    {8,3,0,0,0,0,2,5,1},
  /*-------------------*/
    {0,5,0,0,3,0,0,2,0},
    {6,0,0,4,0,5,1,0,9},
    {0,1,0,0,6,0,0,0,5},
  /*-------------------*/
    {0,0,0,0,0,7,5,0,4},
    {2,0,5,0,0,0,0,9,3},
    {0,0,7,0,5,0,0,1,2},
};

Sudoku_Map* g_Sudoku_Normal_MapData[SUDOKU_MAX_LEVEL+1] =
{
    &Normal_Map_Level0,
    &Normal_Map_Level1,
    &Normal_Map_Level2,
    &Normal_Map_Level3,
    &Normal_Map_Level4,
    &Normal_Map_Level5,
};

/**************************/
/*       Hard Sudoku Map        */
/************************/

static char Hard_Map_Level0[MAP_NUM][MAP_NUM] =
{
    {8,0,0,0,0,0,0,0,0},
    {0,0,3,6,0,0,0,0,0},
    {0,7,0,0,9,0,2,0,0},
  /*-------------------*/
    {0,5,0,0,0,7,0,0,0},
    {0,0,0,0,4,5,7,0,0},
    {0,0,0,1,0,0,0,3,0},
  /*-------------------*/
    {0,0,1,0,0,0,0,6,8},
    {0,0,8,5,0,0,0,1,0},
    {0,9,0,0,0,0,4,0,0},
};

static char Hard_Map_Level1[MAP_NUM][MAP_NUM] =
{
    {7,0,0,0,0,0,0,0,0},
    {5,0,8,0,1,7,0,0,0},
    {0,0,0,0,0,9,4,0,3},
  /*-------------------*/
    {0,0,4,7,0,2,0,5,0},
    {0,2,0,0,6,0,0,8,0},
    {0,7,0,1,0,4,2,0,0},
  /*-------------------*/
    {2,0,1,3,0,0,0,0,0},
    {0,0,0,5,9,0,3,0,7},
    {0,0,0,0,0,0,0,0,5},
};

static char Hard_Map_Level2[MAP_NUM][MAP_NUM] =
{
    {7,0,1,0,0,0,0,0,0},
    {8,0,0,1,3,0,0,0,9},
    {0,2,0,0,8,0,0,4,0},
  /*-------------------*/
    {0,0,7,4,0,0,2,0,6},
    {0,0,0,0,0,0,0,0,0},
    {5,0,6,0,0,8,7,0,0},
  /*-------------------*/
    {0,4,0,0,9,0,0,6,0},
    {2,0,0,0,7,6,0,0,1},
    {0,0,0,0,0,0,5,0,3},
};

static char Hard_Map_Level3[MAP_NUM][MAP_NUM] =
{
    {0,0,8,0,0,0,0,0,0},
    {0,0,2,5,1,0,9,0,0},
    {1,0,0,6,0,0,0,0,0},
  /*-------------------*/
    {0,2,0,0,0,4,0,8,9},
    {0,3,0,0,2,0,0,4,0},
    {6,8,0,9,0,0,0,7,0},
  /*-------------------*/
    {0,0,0,0,0,2,0,0,4},
    {0,0,7,0,9,3,1,0,0},
    {0,0,0,0,0,0,8,0,0},
};

static char Hard_Map_Level4[MAP_NUM][MAP_NUM] =
{
    {8,0,0,0,0,2,4,0,0},
    {9,0,0,0,0,0,0,1,2},
    {0,0,3,6,0,0,0,0,0},
  /*-------------------*/
    {0,7,4,0,2,0,0,0,0},
    {0,0,0,1,0,7,0,0,0},
    {0,0,0,0,5,0,7,6,0},
  /*-------------------*/
    {0,0,0,0,0,1,8,0,0},
    {5,6,0,0,0,0,0,0,9},
    {0,0,2,7,0,0,0,0,3},
};

static char Hard_Map_Level5[MAP_NUM][MAP_NUM] =
{
    {0,2,0,0,0,0,0,1,0},
    {5,0,6,0,0,0,3,0,9},
    {0,8,0,5,0,2,0,6,0},
  /*-------------------*/
    {0,0,5,0,7,0,1,0,0},
    {0,0,0,2,0,8,0,0,0},
    {0,0,4,0,1,0,8,0,0},
  /*-------------------*/
    {0,5,0,8,0,7,0,3,0},
    {7,0,2,0,0,0,4,0,5},
    {0,4,0,0,0,0,0,7,0},
};

Sudoku_Map* g_Sudoku_Hard_MapData[SUDOKU_MAX_LEVEL+1] =
{
    &Hard_Map_Level0,
    &Hard_Map_Level1,
    &Hard_Map_Level2,
    &Hard_Map_Level3,
    &Hard_Map_Level4,
    &Hard_Map_Level5,
};

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
static DRAW_FILL_RECT Sudoku_FillRect_List[] =
{
    {//BG color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//Info Block
        0x00000007,
        0x00000007,
        OSD_GRADIENT_DISABLE
    },
    {//Grid color
        0x0000002D,
        0x0000002D,
        OSD_GRADIENT_DISABLE
    },
    {//Grid Line color
        0x00000086,
        0x00000086,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Sudoku_Rect_Border_List[] =
{
    {//Border
        0x000000CB, // colorLeftTop;
        0x000000CB, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Sudoku_Text_List[] =
{
    {//info string
       FONT_NORMAL, // eSystemFont;
       NULL, // pString;
       0x00000009, // TextColor;
       eTextAlignMiddle, // eTextAttrib;
       (GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP), // flag;
       2, // u8dis;
       EN_STRING_ENDING_3_DOT // u8dots
    },
    {//info string
       FONT_NORMAL, // eSystemFont;
       NULL, // pString;
       0x00000003, // TextColor;
       eTextAlignMiddle, // eTextAttrib;
       (GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP), // flag;
       2, // u8dis;
       EN_STRING_ENDING_3_DOT // u8dots
    },
};

static DRAW_BITMAP Sudoku_Bitmap_List[] =
{
     {//index0 Blank
        E_BMP_MAINMENU_IMG_AP,
        TRUE,
        5,
        5,
        255
     },
     {//index1 Up
        E_BMP_MENU_IMG_MENU_UP_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index2 Down
        E_BMP_MENU_IMG_MENU_DOWN_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index3 Left
        E_BMP_MENU_IMG_MENU_LEFT_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index4 Right
        E_BMP_MENU_IMG_MENU_RIGHT_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index5 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0,
        0,
        255
     },
     {//index6 OK
        E_BMP_BOTTON_OK,
        TRUE,
        5,
        5,
        255
     },
};

#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Sudoku_FillRect_List[] =
{
    {//BG color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//Info Block
        0xFF4F535F,
        0xFF4F535F,
        OSD_GRADIENT_DISABLE
    },
    {//Grid color
        0x00404040,
        0x00404040,
        OSD_GRADIENT_DISABLE
    },
    {//Grid Line color
        0x00E8E800,
        0x00E8E800,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Sudoku_Rect_Border_List[] =
{
    {//Border
        0x00FF00FF, // colorLeftTop;
        0x00FF00FF, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Sudoku_Text_List[] =
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

static DRAW_BITMAP Sudoku_Bitmap_List[] =
{
     {//index0 Blank
        E_BMP_MAINMENU_IMG_AP,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index1 Up
        E_BMP_MENU_IMG_MENU_UP_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index2 Down
        E_BMP_MENU_IMG_MENU_DOWN_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index3 Left
        E_BMP_MENU_IMG_MENU_LEFT_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index4 Right
        E_BMP_MENU_IMG_MENU_RIGHT_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index5 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index6 OK
        E_BMP_BOTTON_OK,
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

BOOLEAN MApp_Sudoku_DrawGameWin(void)
{
    U8 u8Txt[128] = {0};
    U16 u16TmpStr[128] = {0};
    //U16 u16Index_X = 0, u16Index_Y = 0;
    U16 scrx = getmaxx(), scry = getmaxy();


    if(!MApp_Sudoku_CheckWin())
    {
        return FALSE;
    }

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Sudoku_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Sudoku_Text_List[0];

    RECT_SET(rect, (scrx - PASS_BAR_WIDTH) / 2, (scry - PASS_BAR_HEIGHT) / 2, PASS_BAR_WIDTH, PASS_BAR_HEIGHT);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);


    if( SudokuNowLevel == SUDOKU_MAX_LEVEL )
    {
        sprintf((char*)u8Txt, "PASS_ALL_LEVEL ! [OK] try again [EXIT] have a rest.");
    }
    else
    {
        sprintf((char*)u8Txt, "PASS_CURRENT_LEVEL ! [OK] next [EXIT] have a rest.");
    }

    MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
    paramTextOut->pString = (LPTSTR)u16TmpStr;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    gbSudokuPass = TRUE;
    gbSudokuStop = TRUE;

    return TRUE;
}

static void MApp_Sudoku_DisplayInfo(void)
{
    RECT rect;
    char cstring[20] = {0};

    U16 u16StartX = 0, u16StartY = 0;
    U32 u32Hour = 0, u32Minute= 0, u32Second = 0;
    U32 u32GameTime = 0;

    u32GameTime = MsOS_GetSystemTime() - StartTime;
    u32Hour = ( u32GameTime / 1000 ) / 3600;
    u32Minute = ( ( u32GameTime / 1000 ) % 3600 ) / 60;
    u32Second = ( ( u32GameTime / 1000 ) % 60 );

    DRAW_FILL_RECT* paramFillRect = &Sudoku_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Sudoku_Text_List[0];

    u16StartX = GAME_AREA_X + SUDOKU_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y/4;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Rank: %s", (MApp_Game_GetGameLevel()==EN_GAME_RANK_EASY)?"Easy":((MApp_Game_GetGameLevel()==EN_GAME_RANK_NORMAL)?"Normal":"Hard"));
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16StartX = GAME_AREA_X + SUDOKU_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Time %02d:%02d:%02d", u32Hour, u32Minute, u32Second);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16StartY = u16StartY + BLOCK_Y + BLOCK_Y/3;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Level %02d/%02d", SudokuNowLevel, SUDOKU_MAX_LEVEL);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    /*----- Draw Grid Vertical & Horizontal  Internal Line -----*/
    U16 u16LineIndex_X = 0, u16LineIndex_Y = 0;
    U16 u16XStart = GAME_AREA_X + u16LineIndex_X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u16LineIndex_Y * BLOCK_Y + 1;

    paramFillRect = &Sudoku_FillRect_List[3];

    for(u16LineIndex_X=3; u16LineIndex_X <= MAP_NUM; u16LineIndex_X += 3) // Vertical line
    {
        u16XStart = GAME_AREA_X + u16LineIndex_X*BLOCK_Y;
        u16YStart = GAME_AREA_Y;

        rect.left = u16XStart;
        rect.top = u16YStart;
        rect.width = 2;
        rect.height = MAP_NUM*BLOCK_Y;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    for(u16LineIndex_Y=3; u16LineIndex_Y <= MAP_NUM; u16LineIndex_Y += 3)//Horizontal line
    {
        u16XStart = GAME_AREA_X;
        u16YStart = GAME_AREA_Y + u16LineIndex_Y*BLOCK_X;

        rect.left = u16XStart;
        rect.top = u16YStart;
        rect.width = MAP_NUM*BLOCK_X;
        rect.height = 2;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

}

void MApp_Sudoku_DrawBlock(U8 u8Y, U8 u8X, U16 u16Object)
{
    U16 u16XStart = GAME_AREA_X + u8X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u8Y * BLOCK_Y + 1;

    char cstring[20] = {0};

    RECT rect;
    DRAW_FILL_RECT* paramFillRect_Blank = &Sudoku_FillRect_List[2];
    DRAW_FILL_RECT* paramFillRect_Number = &Sudoku_FillRect_List[1];
    DRAW_RECT_BORDER* paramRectBorder = &Sudoku_Rect_Border_List[0];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Sudoku_Text_List[0];

    if(MApp_Sudoku_CanBlockEdit(u8Y,u8X))
    {
        paramFillRect_Number = &Sudoku_FillRect_List[1];//to diff  can edit block BG color
    }

    switch(u16Object)
    {
        case SUDOKU_SQUARE_NONE:   //General Blank
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Blank, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_1:    // Number Sqaure
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 1 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_2:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 2 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_3:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 3 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_4:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 4 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_5:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 5 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_6:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 6 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_7:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 7 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_8:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 8 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case SUDOKU_SQUARE_NUM_9:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            //RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Digit
            sprintf((char *)cstring, " 9 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

        }
        break;

        case SUDOKU_SQUARE_CURSOR:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            //_MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);
        }
        break;

        default:
            break;
    }
}

void MApp_Sudoku_UpdateMap(void)
{
    U8 u8UpdateIndex_X = 0, u8UpdateIndex_Y = 0;

    for( u8UpdateIndex_X = 0; u8UpdateIndex_X < MAP_NUM; u8UpdateIndex_X++ )
    {
        for( u8UpdateIndex_Y = 0; u8UpdateIndex_Y < MAP_NUM; u8UpdateIndex_Y++ )
        {
            SUDOKU_DEBUG(printf("\nx,y %d,%d,Map %d\n",u8UpdateIndex_X, u8UpdateIndex_Y););
            MApp_Sudoku_DrawBlock( u8UpdateIndex_X, u8UpdateIndex_Y, MApp_Sudoku_GetTableValue(u8UpdateIndex_X,u8UpdateIndex_Y));
        }
    }

    SUDOKU_DEBUG(printf("\nCursorX,CursorY (%d,%d)\n",CursorX,CursorY););
    MApp_Sudoku_DisplayInfo();
    MApp_Sudoku_DrawBlock( CursorY, CursorX, SUDOKU_SQUARE_CURSOR );
}

void MApp_Sudoku_UpdateTimer(void)
{
    RECT rect;
    char cstring[20] = {0};

    U16 u16StartX = 0, u16StartY = 0;
    U32 u32Hour = 0, u32Minute= 0, u32Second = 0;
    U32 u32GameTime = 0;

    u32GameTime = MsOS_GetSystemTime() - StartTime;
    u32Hour = ( u32GameTime / 1000 ) / 3600;
    u32Minute = ( ( u32GameTime / 1000 ) % 3600 ) / 60;
    u32Second = ( ( u32GameTime / 1000 ) % 60 );

    DRAW_FILL_RECT* paramFillRect = &Sudoku_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Sudoku_Text_List[0];

    u16StartX = GAME_AREA_X + SUDOKU_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    sprintf((char *)cstring, " Time %02d:%02d:%02d", u32Hour, u32Minute, u32Second);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Sudoku_GameInit(void)       /* Game Parameters Initial */
{
    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_SUDOKU_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Sudoku support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_SUDOKU), u16Ver));

    SIZE sizeStep;

    sizeStep.cx = sizeStep.cy = MAP_NUM;

    U16 u16BufSize;

    if( !MApp_Game_GetLibInfo(GAME_INFO_SUDOKU_BUF_SIZE, &sizeStep, &u16BufSize) )
    {
        GAME_DEBUG( printf(ANSI_COLOR_RED"Can't get Sudoku buffer size\n"ANSI_COLOR_RESET) );
    }

    GAME_DEBUG( printf("Buf size = %d\n", u16BufSize) );

    if(_SudokuBuf == NULL)
    {
        _SudokuBuf = msAPI_Memory_Allocate(u16BufSize, BUF_ID_APP_GAME);

        if(_SudokuBuf == NULL)
        {
            GAME_DEBUG( printf(ANSI_COLOR_RED"Alloc Sudoku buffer fail!\n"ANSI_COLOR_RESET) );
        }
    }

    gbSudokuPass = FALSE;
    gbSudokuStop = FALSE;

    CursorX = 0;
    CursorY = 0;

    U16 u16InitStartX = 0, u16InitStartY = 0;

    LPTSTR pstringBuffer = CHAR_BUFFER;

    StartTime = MsOS_GetSystemTime();   //Reset Init time

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Sudoku_FillRect_List[0];
    DRAW_FILL_RECT* paramFillRect_Info = &Sudoku_FillRect_List[0];    // Draw background color, need wait refined.
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Sudoku_Text_List[0];
    DRAW_BITMAP* paramBitmap = &Sudoku_Bitmap_List[0];

    /*----- Draw Game Title -----*/
    RECT_SET(rect, 0, 0, getmaxx(), getmaxy());
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Sudoku", (U16*)pstringBuffer, strlen("Sudoku"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    MApp_Sudoku_DisplayInfo();

    if( SudokuNowLevel > SUDOKU_MAX_LEVEL )
    {
        SudokuNowLevel = SUDOKU_MAX_LEVEL;
    }

    //Set game level
    switch(MApp_Game_GetGameLevel())
    {
        case EN_GAME_RANK_EASY:
            memcpy(_SudokuBuf, g_Sudoku_MapData[SudokuNowLevel], sizeof(U8)*MAP_NUM*MAP_NUM);
            break;
        case EN_GAME_RANK_NORMAL:
            memcpy(_SudokuBuf, g_Sudoku_Normal_MapData[SudokuNowLevel], sizeof(U8)*MAP_NUM*MAP_NUM);
            break;
        case EN_GAME_RANK_HARD:
            memcpy(_SudokuBuf, g_Sudoku_Hard_MapData[SudokuNowLevel], sizeof(U8)*MAP_NUM*MAP_NUM);
            break;
        default:
            memcpy(_SudokuBuf, g_Sudoku_MapData[SudokuNowLevel], sizeof(U8)*MAP_NUM*MAP_NUM);
            break;
    }

    MApp_Sudoku_LoadMap(MAP_NUM, _SudokuBuf);
    MApp_Sudoku_UpdateMap();

    /*----- Draw Grid Vertical & Horizontal Full Line -----*/
    U16 u16LineIndex_X = 0, u16LineIndex_Y = 0;
    U16 u16XStart = GAME_AREA_X + u16LineIndex_X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u16LineIndex_Y * BLOCK_Y + 1;

    paramFillRect = &Sudoku_FillRect_List[3];

    for(u16LineIndex_X=0; u16LineIndex_X <= MAP_NUM; u16LineIndex_X += 3) // Vertical line
    {
        u16XStart = GAME_AREA_X + u16LineIndex_X*BLOCK_Y;
        u16YStart = GAME_AREA_Y;

        rect.left = u16XStart;
        rect.top = u16YStart;
        rect.width = 2;
        rect.height = MAP_NUM*BLOCK_Y;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    for(u16LineIndex_Y=0; u16LineIndex_Y <= MAP_NUM; u16LineIndex_Y += 3)//Horizontal line
    {
        u16XStart = GAME_AREA_X;
        u16YStart = GAME_AREA_Y + u16LineIndex_Y*BLOCK_X;

        rect.left = u16XStart;
        rect.top = u16YStart;
        rect.width = MAP_NUM*BLOCK_X;
        rect.height = 2;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    /*----- Draw Up/Down/Left/Right Arrow -----*/
    u16InitStartX = GAME_AREA_X + SUDOKU_MAP_X_NUM*BLOCK_X + GAME_AREA_X;
    u16InitStartY = GAME_AREA_Y + BLOCK_Y*6 + BLOCK_Y/2;

    RECT_SET(rect, u16InitStartX, u16InitStartY, BLOCK_X*6, BLOCK_Y*5);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y*2/3,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y*2 + BLOCK_Y/3);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    u16InitStartX = u16InitStartX + BLOCK_X*3;
    u16InitStartY = u16InitStartY - BLOCK_Y/3;
    RECT_SET(rect, u16InitStartX - BLOCK_X/2, u16InitStartY + BLOCK_Y*4/3, 34, 20);
    paramBitmap = &Sudoku_Bitmap_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game,&rect);

    RECT_SHIFT(rect, 0, BLOCK_Y*4/3);
    paramBitmap = &Sudoku_Bitmap_List[2];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game,&rect);

    RECT_SET(rect, u16InitStartX - BLOCK_X, u16InitStartY + BLOCK_Y*3/2 + BLOCK_Y/3, 20, 34);
    paramBitmap = &Sudoku_Bitmap_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SHIFT(rect, BLOCK_X*4/3, 0);
    paramBitmap = &Sudoku_Bitmap_List[4];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    /*----- Draw Exit & OK Button -----*/
    u16InitStartX = u16InitStartX - BLOCK_X*7/3;
    u16InitStartY = u16InitStartY + BLOCK_Y*11/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Sudoku_Bitmap_List[5];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX+BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16InitStartY = u16InitStartY + BLOCK_Y*4/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Sudoku_Bitmap_List[6];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"OK", (U16*)pstringBuffer, strlen("OK"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Sudoku_MainTask(void)
{
    if( !gbEnableSudokuTask )
        return;

    if( gu8SudokuKey == EN_GAME_KEY_NULL )
    {
        msAPI_Timer_DelayUs( SUDOKU_TIMER_SPEED );
        MApp_Sudoku_UpdateTimer();
    }
    else
    {
        if( gbSudokuPass )
        {
            if( gu8SudokuKey == EN_GAME_KEY_SELECT )
            {
                if( SudokuNowLevel == SUDOKU_MAX_LEVEL )
                {
                    SudokuNowLevel = 0;
                }
                else
                {
                    SudokuNowLevel++;
                }

                MApp_Sudoku_GameInit();
            }
        }
        else
        {
            switch( gu8SudokuKey )
            {
                case EN_GAME_KEY_UP:
                {
                    CursorX = CursorX;

                    if( ( CursorY-1 ) >= 0 )
                        CursorY = CursorY - 1;
                    else
                        CursorY = CursorY;
                }
                break;

                case EN_GAME_KEY_DOWN:
                {
                    CursorX = CursorX;

                    if( ( CursorY + 1 ) < MAP_NUM )
                        CursorY = CursorY + 1;
                    else
                        CursorY = CursorY;
                }
                break;

                case EN_GAME_KEY_LEFT:
                {
                    CursorY = CursorY;

                    if( ( CursorX-1 ) >= 0 )
                        CursorX = CursorX - 1;
                    else
                        CursorX = CursorX;
                }
                break;

                case EN_GAME_KEY_RIGHT:
                {
                    CursorY = CursorY;

                    if( ( CursorX + 1 ) < MAP_NUM )
                        CursorX = CursorX + 1;
                    else
                        CursorX = CursorX;
                }
                break;

                case EN_GAME_KEY_NUM0:  // Clear the input
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NONE);
                }
                break;

                case EN_GAME_KEY_NUM1:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_1);
                }
                break;

                case EN_GAME_KEY_NUM2:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_2);
                }
                break;

                case EN_GAME_KEY_NUM3:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_3);
                }
                break;

                case EN_GAME_KEY_NUM4:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_4);
                }
                break;

                case EN_GAME_KEY_NUM5:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_5);
                }
                break;

                case EN_GAME_KEY_NUM6:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_6);
                }
                break;

                case EN_GAME_KEY_NUM7:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_7);
                }
                break;

                case EN_GAME_KEY_NUM8:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_8);
                }
                break;

                case EN_GAME_KEY_NUM9:
                {
                    MApp_Sudoku_UpdateTable(CursorY, CursorX, SUDOKU_SQUARE_NUM_9);
                }
                break;

                default:
                    break;
            }

            MApp_Sudoku_UpdateMap();
            MApp_Sudoku_CheckWin();
            MApp_Sudoku_DrawGameWin();

        }

        gu8SudokuKey = EN_GAME_KEY_NULL;
    }
}

BOOLEAN MApp_Sudoku_Init(void)
{
    gbEnableSudokuTask = TRUE;

    gu8SudokuKey = EN_GAME_KEY_NULL;

    MApp_Sudoku_GameInit();

    return TRUE;
}

BOOLEAN MApp_Sudoku_DeInit(void)
{
    if(_SudokuBuf)
    {
        msAPI_Memory_Free(_SudokuBuf, BUF_ID_APP_GAME);

        _SudokuBuf = NULL;
    }

    if( gbEnableSudokuTask )
    {
        gbEnableSudokuTask = FALSE;
        gbSudokuPass = FALSE;
        gbSudokuStop = FALSE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN MApp_Sudoku_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8SudokuKey = enGameKey;
    return TRUE;
}

BOOLEAN MApp_Sudoku_IsGameOver(void)
{
    return gbSudokuPass;
}

#endif //( GAME_ENABLE && GAME_SUDOKU )
