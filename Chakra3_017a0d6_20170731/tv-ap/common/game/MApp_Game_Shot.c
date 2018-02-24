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
// Shot_game.c
// it is a game for entermainment.
/*************************************************************************/

/******************************************************************************/
/*   Header Files                                                                                                           */
/******************************************************************************/

#include "Board.h"

#if ( GAME_ENABLE && GAME_SHOT )
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "MApp_Game_Shot.h"
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

#define SHOT_DEBUG(x)               x

#define SHOT_MAP_NUM                12       //Max 12*12

#define SHOT_INIT_NUM               2       //Max 12*12

#define SHOT_MAP_X_NUM              16      // Block numbers in map X position
#define SHOT_MAP_Y_NUM              12      // Block numbers in map Y position

#define SHOT_TIMER_SPEED            100000  // Shot GameTimer refresh time

#define SHOT_LEVEL1_TIME            3000
#define SHOT_LEVEL2_TIME            2500
#define SHOT_LEVELMAX_TIME          2000

#define SHOT_LEVEL1_SCORE           100
#define SHOT_LEVEL2_SCORE           200
#define SHOT_LEVEL3_SCORE           300

static U8 CursorX = 0, CursorY = 0;
static U32 StartTime = 0, NowLevel = 0;

static U8 GunX = SHOT_MAP_NUM/2, GunY = SHOT_MAP_NUM-1;
static S16 ShotBullet = 0;
static U16 UpdateBlockTime = 0;
static U32 ShotScore = 0;

EN_GAME_KEY gu8ShotKey = EN_GAME_KEY_NULL;

BOOLEAN gbEnableShotTask = FALSE;
BOOLEAN gbShotStop = FALSE;
BOOLEAN gbShotPass = FALSE;

char gau8ShotMap[SHOT_MAP_NUM][SHOT_MAP_NUM] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
};

char gau8ShotMapInit[SHOT_MAP_NUM][SHOT_MAP_NUM] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
};

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
static DRAW_FILL_RECT Shot_FillRect_List[] =
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

static DRAW_TEXT_OUT_DYNAMIC Shot_Text_List[] =
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

static DRAW_BITMAP Shot_Bitmap_List[] =
{
     {//index0 Gun
        E_BMP_game_gun,
        TRUE,
        0x0,
        0x0,
        255
     },
     {//index1 Target
        E_BMP_game_block,
        TRUE,
        0,
        0,
        255
     },
     {//index2 Bullet
        E_BMP_game_bullet,
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
};

#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Shot_FillRect_List[] =
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

static DRAW_TEXT_OUT_DYNAMIC Shot_Text_List[] =
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

static DRAW_BITMAP Shot_Bitmap_List[] =
{
     {//index0 Gun
        E_BMP_game_gun,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index1 Target
        E_BMP_game_block,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index2 Bullet
        E_BMP_game_bullet,
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
};

#endif  //UI_SKIN_SEL


/******************************************************************************/
/*   Local Function                                                                                                        */
/******************************************************************************/

BOOLEAN MApp_Shot_DrawGameWin(void)
{
    U8 u8Txt[128] = {0};
    U16 u16TmpStr[128] = {0};
    U16 scrx = getmaxx(), scry = getmaxy();

    if(!MApp_Shot_CheckWin())
    {
        return FALSE;
    }

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Shot_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Shot_Text_List[0];

    RECT_SET(rect, (scrx - PASS_BAR_WIDTH) / 2, (scry - PASS_BAR_HEIGHT) / 2, PASS_BAR_WIDTH, PASS_BAR_HEIGHT);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    if( (gbShotPass == TRUE) && (ShotScore != SHOT_LEVEL3_SCORE) )
    {
        sprintf((char*)u8Txt, "%s", "YOU PASS CURRENT LEVEL !\a [OK] try next level [EXIT] have a rest");
    }
    else if( (gbShotPass == TRUE) && (ShotScore == SHOT_LEVEL3_SCORE) )
    {
        sprintf((char*)u8Txt, "%s", "YOU PASS ALL LEVEL !\a [OK] try again [EXIT] have a rest");
    }
    else
    {
        sprintf((char*)u8Txt, "%s", "Game Over!\a [OK] try again [EXIT] have a rest");
    }

    MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
    paramTextOut->pString = (LPTSTR)u16TmpStr;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    gbShotStop = TRUE;

    return TRUE;
}

static void MApp_Shot_DisplayInfo(void)
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

    DRAW_FILL_RECT* paramFillRect = &Shot_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Shot_Text_List[0];

    u16StartX = GAME_AREA_X + SHOT_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y/4;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Rank: %s", (MApp_Game_GetGameLevel()==EN_GAME_RANK_EASY)?"Easy":((MApp_Game_GetGameLevel()==EN_GAME_RANK_NORMAL)?"Normal":"Hard"));
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16StartX = GAME_AREA_X + SHOT_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Time %02d:%02d:%02d", u32Hour, u32Minute, u32Second);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16StartY = u16StartY + BLOCK_Y + BLOCK_Y/3;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Score %05d", ShotScore);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}

void MApp_Shot_DrawBlock(U8 u8Y, U8 u8X, U16 u16Object)
{
    U16 u16XStart = GAME_AREA_X + u8X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u8Y * BLOCK_Y + 1;

    RECT rect;
    DRAW_FILL_RECT* paramFillRect_Blank = &Shot_FillRect_List[2];
    DRAW_BITMAP* paramBitmap = &Shot_Bitmap_List[0];

    switch(u16Object)
    {
        case SHOT_SQUARE_NONE:              //General Blank
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Blank, &pdc_Game, &rect);
        }
        break;

        case SHOT_SQUARE_GUN:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Shot_Bitmap_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;

        case SHOT_SQUARE_BULLET:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Shot_Bitmap_List[2];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;

        case SHOT_SQUARE_BLOCK:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Shot_Bitmap_List[1];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game, &rect);
        }
        break;

        default:
            break;
    }
}

void MApp_Shot_UpdateScore(void)
{
    RECT rect;
    char cstring[20] = {0};
    U16 u16StartX = 0, u16StartY = 0;

    DRAW_FILL_RECT* paramFillRect = &Shot_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Shot_Text_List[0];

    u16StartX = GAME_AREA_X + SHOT_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2 + BLOCK_Y + BLOCK_Y/3;

    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Score %05d", ShotScore);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}

void MApp_Shot_UpdateTimer(void)
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

    DRAW_FILL_RECT* paramFillRect = &Shot_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Shot_Text_List[0];

    u16StartX = GAME_AREA_X + SHOT_MAP_X_NUM*BLOCK_X + GAME_AREA_X + BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y + BLOCK_Y*3/2;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    sprintf((char *)cstring, " Time %02d:%02d:%02d", u32Hour, u32Minute, u32Second);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Shot_UpdateBlock(void)
{
    U16 u16UpdateBlockIndex_I = 0, u16UpdateBlockIndex_J = 0;
    U16 u16UpdateBlockIndex_X = 0;
    char ShotBlocks[SHOT_MAP_NUM] = {0};

    if( MsOS_GetSystemTime() - UpdateBlockTime < NowLevel )
    {
        return;
    }

    //generate MAP_NUM/4  blocks
    for(u16UpdateBlockIndex_I = 0; u16UpdateBlockIndex_I < SHOT_MAP_NUM/4; u16UpdateBlockIndex_I++)
    {
        u16UpdateBlockIndex_X = rand()%(SHOT_MAP_NUM-1 + 1);

        if(ShotBlocks[u16UpdateBlockIndex_X] == 3)
        {
            u16UpdateBlockIndex_I--;
            continue;
        }
        ShotBlocks[u16UpdateBlockIndex_X] = 3;
    }

    if( MApp_Shot_CheckEmptyLine() )
    {
        for (u16UpdateBlockIndex_I = SHOT_MAP_NUM-2; u16UpdateBlockIndex_I > 0 ; u16UpdateBlockIndex_I--)
        {
            for (u16UpdateBlockIndex_J = 0; u16UpdateBlockIndex_J < SHOT_MAP_NUM; u16UpdateBlockIndex_J++)
            {
                gau8ShotMap[u16UpdateBlockIndex_I][u16UpdateBlockIndex_J] = gau8ShotMap[u16UpdateBlockIndex_I-1][u16UpdateBlockIndex_J];
            }
        }

        //copy rand gen blocks to first line Map[0]
        for(u16UpdateBlockIndex_I = 0; u16UpdateBlockIndex_I<SHOT_MAP_NUM; u16UpdateBlockIndex_I++)
        {
            gau8ShotMap[0][u16UpdateBlockIndex_I] = ShotBlocks[u16UpdateBlockIndex_I];
        }
        UpdateBlockTime = MsOS_GetSystemTime();
    }
}

void MApp_Shot_UpdateBullet(void)
{
    MApp_Shot_DrawBlock(ShotBullet, GunX, SHOT_SQUARE_BULLET);
}


void MApp_Shot_UpdateMap(void)
{
    U8 u8UpdateIndex_X = 0, u8UpdateIndex_Y = 0;

    for(u8UpdateIndex_X = 0; u8UpdateIndex_X < SHOT_MAP_NUM; u8UpdateIndex_X++)
    {
        for(u8UpdateIndex_Y = 0; u8UpdateIndex_Y < SHOT_MAP_NUM; u8UpdateIndex_Y++)
        {  //if map(i,j)<10,means this is a selected position
            MApp_Shot_DrawBlock(u8UpdateIndex_X, u8UpdateIndex_Y, gau8ShotMap[u8UpdateIndex_X][u8UpdateIndex_Y]);
        }
    }

    MApp_Shot_DrawBlock(GunY, GunX, SHOT_SQUARE_GUN);

    //DrawBorder();
}

void MApp_Shot_ShotOnce(void)
{
    SHOT_DEBUG(printf("GunX %d,Bullet %+d,\n",GunX,MApp_Shot_ShotOnce););
    SHOT_DEBUG(printf("Map[GunX][Bullet] %d\n",gau8ShotMap[GunX][ShotBullet]););

    if( gau8ShotMap[ShotBullet][GunX] == 3 )
    {
        gau8ShotMap[ShotBullet][GunX] = 0;      //delete one block
        ShotScore += 5;
        ShotBullet = SHOT_MAP_NUM-2;
        MApp_Shot_UpdateMap();
    }
    else
    {

        MApp_Shot_UpdateMap();
        MApp_Shot_UpdateBullet();
        msAPI_Timer_DelayUs( SHOT_TIMER_SPEED/20 );
        ShotBullet--;
        MApp_Shot_ShotOnce();           //recursive shot
    }

    if(ShotBullet < 0)
    {
        ShotBullet = SHOT_MAP_NUM-2;
        return;
    }
}

void MApp_Shot_GameInit(void)       /* Game Parameters Initial */
{
    U16 u16InitStartX = 0, u16InitStartY = 0;

    LPTSTR pstringBuffer = CHAR_BUFFER;

    gbShotPass = FALSE;
    gbShotStop = FALSE;

    GunX = SHOT_MAP_NUM/2;
    GunY = SHOT_MAP_NUM-1;

    CursorX = 0;
    CursorY = 0;

    StartTime = MsOS_GetSystemTime();   //Reset Init time
    UpdateBlockTime = MsOS_GetSystemTime();

    if( (gbShotPass == FALSE)                //as only as pass current level ,level and score update
     || ( (gbShotPass == TRUE) && (ShotScore == SHOT_LEVEL3_SCORE) )
      )
    {
      NowLevel = SHOT_LEVEL1_TIME;
      ShotScore = 0;
    }

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Shot_FillRect_List[0];
    DRAW_FILL_RECT* paramFillRect_Info = &Shot_FillRect_List[0];    // Draw background color, need wait refined.
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Shot_Text_List[0];
    DRAW_BITMAP* paramBitmap = &Shot_Bitmap_List[0];

    /*----- Draw Game Title -----*/
    RECT_SET(rect, 0, 0, getmaxx(), getmaxy());
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Shot", (U16*)pstringBuffer, strlen("Shot"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    /*----- Init Shot Game Map -----*/
    memcpy(gau8ShotMap, gau8ShotMapInit, sizeof(gau8ShotMap));

    MApp_Shot_Library_SetConfig(SHOT_LEVEL1_TIME, SHOT_LEVEL2_TIME, SHOT_LEVELMAX_TIME, SHOT_LEVEL1_SCORE, SHOT_LEVEL2_SCORE, SHOT_LEVEL3_SCORE);
    MApp_Shot_DisplayInfo();
    MApp_Shot_UpdateMap();

    /*----- Draw Border Line -----*/
    U16 u16LineIndex_X = 0, u16LineIndex_Y = 0;
    U16 u16XStart = GAME_AREA_X + u16LineIndex_X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u16LineIndex_Y * BLOCK_Y + 1;

    paramFillRect = &Shot_FillRect_List[3];

    for(u16LineIndex_X=0; u16LineIndex_X <= SHOT_MAP_NUM; u16LineIndex_X += 12) // Vertical line
    {
        u16XStart = GAME_AREA_X + u16LineIndex_X*BLOCK_Y;
        u16YStart = GAME_AREA_Y;

        rect.left = u16XStart;
        rect.top = u16YStart;
        rect.width = 2;
        rect.height = SHOT_MAP_NUM*BLOCK_Y;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    for(u16LineIndex_Y=0; u16LineIndex_Y <= SHOT_MAP_NUM; u16LineIndex_Y += 12)//Horizontal line
    {
        u16XStart = GAME_AREA_X;
        u16YStart = GAME_AREA_Y + u16LineIndex_Y*BLOCK_X;

        rect.left = u16XStart;
        rect.top = u16YStart;
        rect.width = SHOT_MAP_NUM*BLOCK_X;
        rect.height = 2;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    /*----- Draw Up/Down/Left/Right Arrow -----*/
    u16InitStartX = GAME_AREA_X + SHOT_MAP_X_NUM*BLOCK_X + GAME_AREA_X;
    u16InitStartY = GAME_AREA_Y + BLOCK_Y*6 + BLOCK_Y/2;

    RECT_SET(rect, u16InitStartX, u16InitStartY, BLOCK_X*6, BLOCK_Y*5);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y*2/3,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y*2 + BLOCK_Y/3);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    u16InitStartX = u16InitStartX + BLOCK_X*3;
    u16InitStartY = u16InitStartY - BLOCK_Y/3;
    RECT_SET(rect, u16InitStartX - BLOCK_X/2, u16InitStartY + BLOCK_Y*4/3, 34, 20);
    paramBitmap = &Shot_Bitmap_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game,&rect);

    RECT_SHIFT(rect, 0, BLOCK_Y*4/3);
    paramBitmap = &Shot_Bitmap_List[4];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game,&rect);

    RECT_SET(rect, u16InitStartX - BLOCK_X, u16InitStartY + BLOCK_Y*3/2 + BLOCK_Y/3, 20, 34);
    paramBitmap = &Shot_Bitmap_List[5];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SHIFT(rect, BLOCK_X*4/3, 0);
    paramBitmap = &Shot_Bitmap_List[6];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    /*----- Draw Exit & OK & Flag Button -----*/
    u16InitStartX = u16InitStartX - BLOCK_X*7/3;
    u16InitStartY = u16InitStartY + BLOCK_Y*11/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Shot_Bitmap_List[7];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX+BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u16InitStartY = u16InitStartY + BLOCK_Y*4/3;

    RECT_SET(rect, u16InitStartX, u16InitStartY,  BLOCK_X*4 + BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect_Info, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*2/3, u16InitStartY + BLOCK_Y/6, 34, 30);
    paramBitmap = &Shot_Bitmap_List[8];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, &pdc_Game, &rect);

    RECT_SET(rect, u16InitStartX + BLOCK_X*5/2, u16InitStartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"OK", (U16*)pstringBuffer, strlen("OK"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Shot_MainTask(void)
{
    if( !gbEnableShotTask )
        return;

    if( gu8ShotKey == EN_GAME_KEY_NULL )
    {
        msAPI_Timer_DelayUs( SHOT_TIMER_SPEED );
        MApp_Shot_UpdateTimer();
    }
    else
    {
        if( gbShotStop)
        {
            if( gu8ShotKey == EN_GAME_KEY_SELECT )
            {
                if( NowLevel == SHOT_LEVELMAX_TIME )
                {
                    NowLevel = SHOT_LEVEL1_TIME;
                }
                else
                {
                    NowLevel -= 500;//minus 500ms per Level
                }
                MApp_Shot_GameInit();
            }
        }
        else
        {
            switch( gu8ShotKey )
            {
                case EN_GAME_KEY_LEFT:
                {
                    if( GunX > 0 )
                    {
                        GunX--;
                    }
                }
                break;

                case EN_GAME_KEY_RIGHT:
                {
                    if( GunX < SHOT_MAP_NUM-1 )
                    {
                        GunX++;
                    }
                }
                break;

                case EN_GAME_KEY_SELECT:
                {
                    ShotBullet = SHOT_MAP_NUM-2;
                    MApp_Shot_ShotOnce();
                }
                break;

                default:
                    break;
            }

            char* pu8ShotMap = &gau8ShotMap[0][0];

            MApp_Shot_Library_SetPara(pu8ShotMap, SHOT_MAP_NUM, ShotScore, NowLevel, gbShotPass);

            MApp_Shot_UpdateScore();
            MApp_Shot_UpdateBlock();
            MApp_Shot_UpdateMap();
            MApp_Shot_CheckWin();
            //MApp_Shot_DrawGameWin();
        }

        gu8ShotKey = EN_GAME_KEY_NULL;
    }
}

BOOLEAN MApp_Shot_Init(void)
{
    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_SHOT_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Shot support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_SHOT), u16Ver));

    gbEnableShotTask = TRUE;
    gu8ShotKey = EN_GAME_KEY_NULL;

    MApp_Shot_GameInit();

    return TRUE;
}

BOOLEAN MApp_Shot_DeInit(void)
{
    if( gbEnableShotTask )
    {
        gbEnableShotTask = FALSE;
        gbShotPass = FALSE;
        gbShotStop = FALSE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN MApp_Shot_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8ShotKey = enGameKey;

    return TRUE;
}

BOOLEAN MApp_Shot_IsGameOver(void)
{
    return gbShotStop;
}

#endif //( GAME_ENABLE && GAME_SHOT )

