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
// Mines_game.c
// it is a game for entermainment.
/*************************************************************************/

/******************************************************************************/
/*   Header Files                                                                                                           */
/******************************************************************************/

#include "Board.h"

#if ( GAME_ENABLE && GAME_MINES )
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "MApp_Game_Mines.h"
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

static U8 CursorX = 0, CursorY = 0;
static U32 StartTime = 0;

#define MINES_MAP_NUM               8       //Max 8*8
#define MINES_NUM                   5       //Max num of mines

U8 MinesTrigger = 0;
U8 MinesFlagNum = 0;

EN_GAME_KEY gu8MinesKey = EN_GAME_KEY_NULL;

BOOLEAN gbEnableMinesTask = FALSE;
BOOLEAN gbMinesStop = FALSE;
BOOLEAN gbMinesPass = FALSE;

#define MINES_DEBUG(x)              x

#define MINES_MAP_X_NUM             16      // Block numbers in map X position
#define MINES_MAP_Y_NUM             12      // Block numbers in map Y position

#define MINES_TIMER_SPEED           100000  // Mines GameTimer refresh time

char gau8MinesMap[MINES_MAP_NUM][MINES_MAP_NUM] =
{
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
    {10,10,10,10,10,10,10,10},
};

char gau8MapFlag[MINES_MAP_NUM][MINES_MAP_NUM] = {{0}};

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define GAME_AREA_X                 75      // Game X Left-Top position
                                            /* ((getmaxx() - BLOCK_X * SUDOKU_MAP_X_NUM) / 3)*/
#define GAME_AREA_Y                 75      // Game Y Left-Top position

#define BLOCK_X                     35      // Block width
#define BLOCK_Y                     35      // Block height

#define PASS_BAR_WIDTH              500     // Game Win message box width
#define PASS_BAR_HEIGHT             60      // Game Win message box height
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
#define GAME_AREA_X                 125     // Game X Left-Top position
                                            /* ((getmaxx() - BLOCK_X * SUDOKU_MAP_X_NUM) / 3)*/
#define GAME_AREA_Y                 125     // Game Y Left-Top position

#define BLOCK_X                     40      // Block width
#define BLOCK_Y                     40      // Block height

#define PASS_BAR_WIDTH              800     // Game Win message box width
#define PASS_BAR_HEIGHT             100     // Game Win message box height
#endif  //UI_SKIN_SEL



extern GRAPHIC_DC pdc_Game;
extern EN_GAME_RANK gu8CurrentGameLevel;


#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
static DRAW_FILL_RECT Mines_FillRect_List[] =
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

static DRAW_RECT_BORDER Mines_Rect_Border_List[] =
{
    {//Border
        0x000000CB, // colorLeftTop;
        0x000000CB, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Mines_Text_List[] =
{
    {//Number1 and Info string
       FONT_NORMAL, // eSystemFont;
       NULL, // pString;
       0x00000009, // TextColor;
       eTextAlignMiddle, // eTextAttrib;
       (GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP), // flag;
       2, // u8dis;
       EN_STRING_ENDING_3_DOT // u8dots
    },
};

static DRAW_BITMAP Mines_Bitmap_List[] =
{
     {//index0 wall
        E_BMP_MENU_IMG_POP_UP_BLANK,
        TRUE,
        0x0,
        0x0,
        255
     },
     {//index1 Box
        E_BMP_game_box,
        TRUE,
        0,
        0,
        255
     },
     {//index2 Man
        E_BMP_game_man,
        TRUE,
        0,
        0,
        255
     },
     {//index3 Up
        E_BMP_MENU_IMG_MENU_UP_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index4 Down
        E_BMP_MENU_IMG_MENU_DOWN_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index5 Left
        E_BMP_MENU_IMG_MENU_LEFT_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index6 Right
        E_BMP_MENU_IMG_MENU_RIGHT_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index7 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0,
        0,
        255
     },
     {//index8 OK
        E_BMP_BOTTON_OK,
        TRUE,
        5,
        5,
        255
     },
     {//index9 Pause
        E_BMP_DMP_BUTTON_ICON_PAUSE,
        TRUE,
        0,
        0,
        255
     },
};

#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Mines_FillRect_List[] =
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

static DRAW_RECT_BORDER Mines_Rect_Border_List[] =
{
    {//Border
        0x00FF00FF, // colorLeftTop;
        0x00FF00FF, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Mines_Text_List[] =
{
    {//Number1 and Info string
       FONT_NORMAL, // eSystemFont;
       NULL, // pString;
       0x00FFFFFF, // TextColor;
       eTextAlignMiddle, // eTextAttrib;
       (GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP), // flag;
       2, // u8dis;
       EN_STRING_ENDING_3_DOT // u8dots
    },
};

static DRAW_BITMAP Mines_Bitmap_List[] =
{
     {//index0 wall
        E_BMP_MENU_IMG_POP_UP_BLANK,
        TRUE,
        0x0,
        0x0,
        255
     },
     {//index1 Box
        E_BMP_game_box,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index2 Man
        E_BMP_game_man,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index3 Up
        E_BMP_MENU_IMG_MENU_UP_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index4 Down
        E_BMP_MENU_IMG_MENU_DOWN_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index5 Left
        E_BMP_MENU_IMG_MENU_LEFT_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index6 Right
        E_BMP_MENU_IMG_MENU_RIGHT_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index7 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index8 OK
        E_BMP_BOTTON_OK,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index9 Pause
        E_BMP_DMP_BUTTON_ICON_PAUSE,
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

void MApp_Mines_AddAroundNum(U8 u8X, U8 u8Y)
{
    if( (u8X+1 < MINES_MAP_NUM) && (u8Y+1 < MINES_MAP_NUM) )
    {
        gau8MinesMap[u8X+1][u8Y+1] == 19?:gau8MinesMap[u8X+1][u8Y+1]++;
    }

    if( (u8X-1 >= 0) && (u8Y-1 >= 0) )
    {
        gau8MinesMap[u8X-1][u8Y-1] == 19?:gau8MinesMap[u8X-1][u8Y-1]++;
    }

    if( u8X+1 < MINES_MAP_NUM )
    {
        gau8MinesMap[u8X+1][u8Y] == 19?:gau8MinesMap[u8X+1][u8Y]++;
    }

    if( u8Y+1 < MINES_MAP_NUM )
    {
        gau8MinesMap[u8X][u8Y+1] == 19?:gau8MinesMap[u8X][u8Y+1]++;
    }

    if( u8X-1 >= 0 )
    {
        gau8MinesMap[u8X-1][u8Y] == 19?:gau8MinesMap[u8X-1][u8Y]++;
    }

    if( u8Y-1 >= 0 )
    {
        gau8MinesMap[u8X][u8Y-1] == 19?:gau8MinesMap[u8X][u8Y-1]++;
    }

    if( (u8X+1 < MINES_MAP_NUM) && (u8Y-1 >= 0) )
    {
        gau8MinesMap[u8X+1][u8Y-1] == 19?:gau8MinesMap[u8X+1][u8Y-1]++;
    }

    if( (u8X-1 >= 0) && (u8Y+1 < MINES_MAP_NUM) )
    {
        gau8MinesMap[u8X-1][u8Y+1] == 19?:gau8MinesMap[u8X-1][u8Y+1]++;
    }

}

void MApp_Mines_SelectSqure(U8 u8idX, U8 u8idY)
{
    if( (gau8MinesMap[u8idX][u8idY] < 10 )
     || (gau8MapFlag[u8idX][u8idY] == 1)
     || (u8idX >= MINES_MAP_NUM)
     || (u8idY >= MINES_MAP_NUM)
      )
        return;

    if( gau8MinesMap[u8idX][u8idY] == 10 )
    {
        gau8MinesMap[u8idX][u8idY] -= 10;      //background
    }
    else if( gau8MinesMap[u8idX][u8idY] > 10 || (gau8MinesMap[u8idX][u8idY] <= 18) )
    {
        gau8MinesMap[u8idX][u8idY] -= 10;      // if its num,return
        return;
    }

    //Trigger to select 8 squre around
    MApp_Mines_SelectSqure(u8idX-1, u8idY);
    MApp_Mines_SelectSqure(u8idX+1, u8idY);
    MApp_Mines_SelectSqure(u8idX, u8idY-1);
    MApp_Mines_SelectSqure(u8idX, u8idY+1);
    MApp_Mines_SelectSqure(u8idX+1, u8idY+1);
    MApp_Mines_SelectSqure(u8idX-1, u8idY+1);
    MApp_Mines_SelectSqure(u8idX+1, u8idY-1);
    MApp_Mines_SelectSqure(u8idX-1, u8idY-1);
}

void MApp_Mines_GenerateMines(void)
{
    U16 u16LoadIndex_X = 0, u16LoadIndex_Y = 0;
    U16 u16MapRangIndex_I = 0, u16MapRangIndex_J = 0;

    MinesTrigger = FALSE;

    for(u16LoadIndex_X = 0; u16LoadIndex_X < MINES_MAP_NUM; u16LoadIndex_X++)
    {
        for(u16LoadIndex_Y = 0; u16LoadIndex_Y < MINES_MAP_NUM; u16LoadIndex_Y++)
        {
            gau8MinesMap[u16LoadIndex_X][u16LoadIndex_Y] = 10;          //Init map
            gau8MapFlag[u16LoadIndex_X][u16LoadIndex_Y] = 0;            //Int map_flag
        }
    }

    for(u16LoadIndex_X = 0; u16LoadIndex_X < MINES_NUM; u16LoadIndex_X++)
    {
        u16MapRangIndex_I = rand()%(MINES_MAP_NUM-1+1);                   //x,y ranges from 0 to MAP_NUM
        u16MapRangIndex_J = rand()%(MINES_MAP_NUM-1+1);

        if( gau8MinesMap[u16MapRangIndex_I][u16MapRangIndex_J] == 19 )   //Avoid rand generate the same postion
        {
            u16LoadIndex_X--;

            continue;
        }

        gau8MinesMap[u16MapRangIndex_I][u16MapRangIndex_J] = 19;

        MApp_Mines_AddAroundNum(u16MapRangIndex_I, u16MapRangIndex_J);//accumulate around square's num
    }
}

void MApp_Mines_SetFlag(U8 u8PosX, U8 u8PosY)
{
    if( gau8MapFlag[u8PosX][u8PosY] == 1 )
    {
        gau8MapFlag[u8PosX][u8PosY] = 0;     //If square had been set flag,recover to 0
        MinesFlagNum--;//accumulate flagnum

        return;
    }
    else if( gau8MinesMap[u8PosX][u8PosY] < 10 )
    {
        return;                                 //Map less than 10,means square has open
    }
    else
    {
        if( MinesFlagNum < MINES_NUM )           // If flag numbers over than Mines, cannot set flag continuiosly.
        {
            MinesFlagNum++;
            gau8MapFlag[u8PosX][u8PosY] = 1;
        }
    }
}

BOOLEAN MApp_Mines_DrawGameWin(void)
{
    U8 u8Txt[128] = {0};
    U16 u16TmpStr[128] = {0};
    U16 scrx = getmaxx(), scry = getmaxy();

    if(!MApp_Mines_CheckWin())
    {
        return FALSE;
    }

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Mines_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Mines_Text_List[0];

    RECT_SET(rect, (scrx - PASS_BAR_WIDTH) / 2, (scry - PASS_BAR_HEIGHT) / 2, PASS_BAR_WIDTH, PASS_BAR_HEIGHT);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);


    if( MinesTrigger )
    {
        sprintf((char*)u8Txt, "%s", "Game Over !\a [OK] try again [EXIT] have a rest.");
    }
    else
    {
        sprintf((char*)u8Txt, "%s", "You Win !\a [OK] try again [EXIT] have a rest.");
    }

    MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
    paramTextOut->pString = (LPTSTR)u16TmpStr;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    gbMinesPass = TRUE;
    gbMinesStop = TRUE;

    return TRUE;
}

static void MApp_Mines_DisplayInfo(void)
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

    DRAW_FILL_RECT* paramFillRect = &Mines_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Mines_Text_List[0];

    u16StartX = GAME_AREA_X + MINES_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y/4;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Rank: %s", (MApp_Game_GetGameLevel()==EN_GAME_RANK_EASY)?"Easy":((MApp_Game_GetGameLevel()==EN_GAME_RANK_NORMAL)?"Normal":"Hard"));
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16StartX = GAME_AREA_X + MINES_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Time %02d:%02d:%02d", u32Hour, u32Minute, u32Second);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16StartY = u16StartY + BLOCK_Y + BLOCK_Y/3;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Flag %02d/%02d", MinesFlagNum, MINES_NUM);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}

void MApp_Mines_DrawBlock(U8 u8Y, U8 u8X, U16 u16Object)
{
    U16 u16XStart = GAME_AREA_X + u8X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u8Y * BLOCK_Y + 1;

    char cstring[20] = {0};

    RECT rect;
    DRAW_FILL_RECT* paramFillRect_Blank = &Mines_FillRect_List[2];
    DRAW_FILL_RECT* paramFillRect_Number = &Mines_FillRect_List[1];
    DRAW_RECT_BORDER* paramRectBorder = &Mines_Rect_Border_List[0];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Mines_Text_List[0];
    DRAW_BITMAP* paramBitmap = &Mines_Bitmap_List[0];

    switch(u16Object)
    {
        case MINES_SQUARE_NONE:   //General Blank
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Blank, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_1:    // Number Sqaure
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 1 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_2:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 2 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_3:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 3 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_4:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 4 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_5:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 5 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_6:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 6 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_7:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 7 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_NUM_8:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);     // Background & Digit
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Number, &pdc_Game, &rect);
            sprintf((char *)cstring, " 8 ");
            MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
            _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_MINE:         //Mine
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Mines_Bitmap_List[2];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);

        }
        break;

        case MINES_SQUARE_FLAG:         //Set a found flag
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Mines_Bitmap_List[1];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
            paramRectBorder = &Mines_Rect_Border_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);

        }
        break;

        case MINES_SQUARE_EXPLORE:      //Mine exploeds
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Blank, &pdc_Game, &rect);
            paramBitmap = &Mines_Bitmap_List[2];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game, &rect);

        }
        break;

        case MINES_SQUARE_CURSOR:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);
        }
        break;

        case MINES_SQUARE_SURFACE:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Mines_Bitmap_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;

        default:
            break;
    }
}

void MApp_Mines_UpdateFlag(void)
{
    RECT rect;
    char cstring[20] = {0};
    U16 u16StartX = 0, u16StartY = 0;

    DRAW_FILL_RECT* paramFillRect = &Mines_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Mines_Text_List[0];

    u16StartX = GAME_AREA_X + MINES_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2 + BLOCK_Y + BLOCK_Y/3;

    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Flag %02d/%02d", MinesFlagNum, MINES_NUM);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}

void MApp_Mines_UpdateTimer(void)
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

    DRAW_FILL_RECT* paramFillRect = &Mines_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Mines_Text_List[0];

    u16StartX = GAME_AREA_X + MINES_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    sprintf((char *)cstring, " Time %02d:%02d:%02d", u32Hour, u32Minute, u32Second);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Mines_UpdateMap(void)
{
    U8 u8UpdateIndex_X = 0, u8UpdateIndex_Y = 0;

    if( !MinesTrigger )
    {
        for( u8UpdateIndex_X = 0; u8UpdateIndex_X < MINES_MAP_NUM; u8UpdateIndex_X++ )
        {
            for( u8UpdateIndex_Y = 0; u8UpdateIndex_Y < MINES_MAP_NUM; u8UpdateIndex_Y++ )
            {
                if( gau8MinesMap[u8UpdateIndex_X][u8UpdateIndex_Y] >= 10 )
                {
                    MApp_Mines_DrawBlock(u8UpdateIndex_X, u8UpdateIndex_Y, MINES_SQUARE_SURFACE);  //if map(i,j)>= 10,draw surface
                }
                else
                {
                    MApp_Mines_DrawBlock(u8UpdateIndex_X, u8UpdateIndex_Y, gau8MinesMap[u8UpdateIndex_X][u8UpdateIndex_Y]);//if map(i,j)<10,means this is a selected position
                }

                if( gau8MapFlag[u8UpdateIndex_X][u8UpdateIndex_Y] == 1 )
                {
                    MApp_Mines_DrawBlock(u8UpdateIndex_X, u8UpdateIndex_Y, MINES_SQUARE_FLAG);      //Draw flag
                }
            }
        }

        MINES_DEBUG(printf("\nCursorX,CursorY (%d,%d)\n",CursorX,CursorY););

        MApp_Mines_DrawBlock(CursorY,CursorX, MINES_SQUARE_CURSOR);
    }
    else
    {
        for( u8UpdateIndex_X = 0; u8UpdateIndex_X < MINES_MAP_NUM; u8UpdateIndex_X++ )
        {
            for( u8UpdateIndex_Y = 0; u8UpdateIndex_Y < MINES_MAP_NUM; u8UpdateIndex_Y++ )
            {
                if( gau8MinesMap[u8UpdateIndex_X][u8UpdateIndex_Y] >= 10 )
                {
                    MApp_Mines_DrawBlock(u8UpdateIndex_X, u8UpdateIndex_Y, gau8MinesMap[u8UpdateIndex_X][u8UpdateIndex_Y] - 10 );  //if map(i,j)>= 10,draw surface
                }
            }
        }
        MINES_DEBUG(printf("\nCursorX,CursorY (%d,%d)\n",CursorX,CursorY););

        MApp_Mines_DisplayInfo();
        MApp_Mines_DrawBlock(CursorY,CursorX, MINES_SQUARE_EXPLORE);
    }

}

void MApp_Mines_GameInit(void)       /* Game Parameters Initial */
{
    gbMinesPass = FALSE;
    gbMinesStop = FALSE;

    MinesFlagNum = 0;
    CursorX = 0;
    CursorY = 0;

    U16 u16InitStartX = 0, u16InitStartY = 0;

    LPTSTR pstringBuffer = CHAR_BUFFER;

    StartTime = MsOS_GetSystemTime();   //Reset Init time

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Mines_FillRect_List[0];
    DRAW_FILL_RECT* paramFillRect_Info = &Mines_FillRect_List[0];    // Draw background color, need wait refined.
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Mines_Text_List[0];
    DRAW_BITMAP* paramBitmap = &Mines_Bitmap_List[0];

    /*----- Draw Game Title -----*/
    RECT_SET(rect, 0, 0, getmaxx(), getmaxy());
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Mines", (U16*)pstringBuffer, strlen("Mines"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    MApp_Mines_DisplayInfo();

    MApp_Mines_GenerateMines();
    MApp_Mines_UpdateMap();

    /*----- Draw Up/Down/Left/Right Arrow -----*/
    u16InitStartX = GAME_AREA_X + MINES_MAP_X_NUM*BLOCK_X + GAME_AREA_X;
    u16InitStartY = GAME_AREA_Y + BLOCK_Y*6 + BLOCK_Y/2;

    RECT_SET(rect, u16InitStartX, u16InitStartY, BLOCK_X*6, BLOCK_Y*5);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y*2/3,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y*2 + BLOCK_Y/3);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    u16InitStartX = u16InitStartX + BLOCK_X*3;
    u16InitStartY = u16InitStartY - BLOCK_Y/3;
    RECT_SET(rect, u16InitStartX - BLOCK_X/2, u16InitStartY + BLOCK_Y*4/3, 34, 20);
    paramBitmap = &Mines_Bitmap_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game,&rect);

    RECT_SHIFT(rect, 0, BLOCK_Y*4/3);
    paramBitmap = &Mines_Bitmap_List[4];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game,&rect);

    RECT_SET(rect, u16InitStartX - BLOCK_X, u16InitStartY + BLOCK_Y*3/2 + BLOCK_Y/3, 20, 34);
    paramBitmap = &Mines_Bitmap_List[5];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SHIFT(rect, BLOCK_X*4/3, 0);
    paramBitmap = &Mines_Bitmap_List[6];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    /*----- Draw Exit & OK & Flag Button -----*/
    u16InitStartX = u16InitStartX - BLOCK_X*7/3;
    u16InitStartY = u16InitStartY + BLOCK_Y*11/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Mines_Bitmap_List[7];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX+BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16InitStartY = u16InitStartY + BLOCK_Y*4/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Mines_Bitmap_List[8];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"OK", (U16*)pstringBuffer, strlen("OK"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16InitStartY = u16InitStartY + BLOCK_Y*4/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Mines_Bitmap_List[9];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"Flag", (U16*)pstringBuffer, strlen("Flag"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}

void MApp_Mines_MainTask(void)
{
    if( !gbEnableMinesTask )
        return;

    if( gu8MinesKey == EN_GAME_KEY_NULL )
    {
        msAPI_Timer_DelayUs( MINES_TIMER_SPEED );
        MApp_Mines_UpdateTimer();
    }
    else
    {
        if( gbMinesPass )
        {
            if( gu8MinesKey == EN_GAME_KEY_SELECT )
            {
                MApp_Mines_GameInit();
            }
        }
        else
        {
            switch( gu8MinesKey )
            {
                case EN_GAME_KEY_UP:
                {
                    CursorX = CursorX;

                    if( ( CursorY - 1 ) >=0 )
                    {
                        CursorY = CursorY-1;
                    }
                    else
                    {
                        CursorY = CursorY;
                    }
                }
                break;

                case EN_GAME_KEY_DOWN:
                {
                    CursorX = CursorX;

                    if( ( CursorY + 1 ) < MINES_MAP_NUM )
                    {
                        CursorY = CursorY + 1;
                    }
                    else
                    {
                        CursorY = CursorY;
                    }
                }
                break;

                case EN_GAME_KEY_LEFT:
                {
                    CursorY = CursorY;

                    if( ( CursorX-1 ) >= 0 )
                    {
                        CursorX = CursorX - 1;
                    }
                    else
                    {
                        CursorX = CursorX;
                    }
                }
                break;

                case EN_GAME_KEY_RIGHT:
                {
                    CursorY = CursorY;

                    if( ( CursorX + 1) < MINES_MAP_NUM )
                    {
                        CursorX = CursorX + 1;
                    }
                    else
                    {
                        CursorX = CursorX;
                    }
                }
                break;

                case EN_GAME_KEY_SELECT:
                {
                    if( gau8MinesMap[CursorY][CursorX] == 19 )
                    {
                        MinesTrigger = TRUE;
                        break;
                    }

                    U8 TempIdX = 0, TempIdY = 0;
                    TempIdX = CursorY;
                    TempIdY = CursorX;
                    MApp_Mines_SelectSqure(TempIdX,TempIdY);   //note:cusror's x,y corresponding to Map's y,x
                }
                break;

                case EN_GAME_KEY_PAUSE:
                {
                    U8 TempPosX = 0, TempPosY = 0;
                    TempPosX = CursorY;
                    TempPosY = CursorX;
                    MApp_Mines_SetFlag(TempPosX, TempPosY);
                }
                break;

                default:
                    break;
            }

            char* pu8MinesMap = &gau8MinesMap[0][0];
            char* pu8MinesMapFlag = &gau8MapFlag[0][0];

            MApp_Mines_Library_SetPara(pu8MinesMap, pu8MinesMapFlag, MINES_MAP_NUM, MINES_NUM, MinesTrigger);

            MApp_Mines_UpdateMap();
            MApp_Mines_UpdateFlag();
            MApp_Mines_CheckWin();
            MApp_Mines_DrawGameWin();
        }

        gu8MinesKey = EN_GAME_KEY_NULL;
    }
}

BOOLEAN MApp_Mines_Init(void)
{
    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_MINES_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Mines support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_MINES), u16Ver));

    gbEnableMinesTask = TRUE;
    gu8MinesKey = EN_GAME_KEY_NULL;

    MApp_Mines_GameInit();

    return TRUE;
}

BOOLEAN MApp_Mines_DeInit(void)
{
    if( gbEnableMinesTask )
    {
        gbEnableMinesTask = FALSE;
        gbMinesPass = FALSE;
        gbMinesStop = FALSE;
        MinesTrigger = 0;
        MinesFlagNum = 0;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN MApp_Mines_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8MinesKey = enGameKey;

    return TRUE;
}

BOOLEAN MApp_Mines_IsGameOver(void)
{
    return gbMinesPass;
}

#endif //( GAME_ENABLE && GAME_MINES )

