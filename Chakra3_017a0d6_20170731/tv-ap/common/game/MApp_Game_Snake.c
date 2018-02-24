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
/* snake_game.c

*/
/* it is a game for entermainment.

*/
/* in the begin,there is only a snake head,and it will have to eat food */
/* to become stronger,and it eat a piece of food each time,it will */
/* lengthen it's body,with the number of food the snake eats going up,it */
/* will become long more and more,and the score will goes up also. */
/* there is always useful information during the game process. */
/* if the path by which the snake goes to eat food is the shortest,the */
/* score will add up a double.

*/
/*

*/
/* enjoy yourself,and any problem,contact <blldw@etang.com> */
/*************************************************************************/
#include "Board.h"
#if (GAME_ENABLE && GAME_SNAKE)
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "MApp_Game_Snake.h"
#include "Utl.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
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

//========================================================

#define DEBUG_GAME_SNAKE(x)     //x


#define SOLID_LINE              1
#define THICK_WIDTH             2

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define SNAKE_SIZE                  10
#define ENCLOSURE_SIZE              25
#define SNAKE_ACTIVITY_START_X      80
#define SNAKE_ACTIVITY_START_Y      70
#define SNAKE_ACTIVITY_WIDTH        600
#define SNAKE_ACTIVITY_HEIGHT       400

#define PASS_BAR_WIDTH              500
#define PASS_BAR_HEIGHT             60
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
#define SNAKE_SIZE                  (20)
#define ENCLOSURE_SIZE              (30)
#define SNAKE_ACTIVITY_START_X      100//(SNAKE_SIZE * 5)
#define SNAKE_ACTIVITY_START_Y      120//(SNAKE_SIZE * 5)
#define SNAKE_ACTIVITY_WIDTH        780//((getmaxx() - SNAKE_ACTIVITY_START_X * 2) / SNAKE_SIZE * SNAKE_SIZE)
#define SNAKE_ACTIVITY_HEIGHT       480//(500 / SNAKE_SIZE * SNAKE_SIZE)

#define PASS_BAR_WIDTH              800
#define PASS_BAR_HEIGHT             100
#endif  //UI_SKIN_SEL

#define PAUSE_BAR_WIDTH              400
#define PAUSE_BAR_HEIGHT             40

//#define SNAKE_MAX_SPEED 400000
#define SNAKE_MAX_SPEED_L1 400000
#define SNAKE_MAX_SPEED_L2 300000
#define SNAKE_MAX_SPEED_L3 200000
#define SNAKE_MIN_SPEED 100000

Snake* snake=NULL;
Snake_Library_Para* stSnakeLibPara;

BOOLEAN gbEnableSnakeTask = FALSE;
EN_GAME_KEY gu8SnakeKey = EN_GAME_KEY_NULL;
BOOLEAN bSnakeGameOver = FALSE;
BOOLEAN bIsGamePaused = FALSE;

extern GRAPHIC_DC pdc_Game;
extern EN_GAME_RANK gu8CurrentGameLevel;
U32 u32SnakeMaxSpeed = SNAKE_MAX_SPEED_L1;

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
static DRAW_FILL_RECT Snake_FillRect_List[] =
{
    {//BG color
        0xFF000000,
        0xFF000000,
        OSD_GRADIENT_DISABLE
    },
    {//FG color
        0x00000048,
        0x00000048,
        OSD_GRADIENT_DISABLE
    },
    {//Food color
        0x00000086,
        0x00000086,
        OSD_GRADIENT_DISABLE
    },
    {//Snake color
        0x000000CB,
        0x000000CB,
        OSD_GRADIENT_DISABLE
    },
    {//game over color
        0xFF9CA3B5,
        0xFF9CA3B5,
        OSD_GRADIENT_DISABLE
    },
    {//empty
        0xFF000000,
        0xFF000000,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Snake_Rect_Border_List[] =
{
    {//BG
        0xFF000000, // colorLeftTop;
        0xFF000000, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
    {//FG
        0x000000CB, // colorLeftTop;
        0x000000CB, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Snake_Text_List[] =
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
};
static DRAW_BITMAP Snake_Bitmap_List[] =
{
     {//index0  Wall
        E_BMP_MENU_IMG_POP_UP_BLANK,
        TRUE,
        0x0,
        0x0,
        255
     },
     {//index1 Play
        E_BMP_DMP_BUTTON_ICON_PLAY,
        TRUE,
        0,
        0,
        255
     },
     {//index2 Pause
        E_BMP_DMP_BUTTON_ICON_PAUSE,
        TRUE,
        0,
        0,
        255
     },
     {//index3 OK
        E_BMP_BOTTON_OK,
        TRUE,
        5,
        5,
        255
     },
     {//index4 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0,
        0,
        255
     },
};
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Snake_FillRect_List[] =
{
    {//BG color
        0xFF000000,
        0xFF000000,
        OSD_GRADIENT_DISABLE
    },
    {//FG color
        0xFF4F535F,
        0xFF4F535F,
        OSD_GRADIENT_DISABLE
    },
    {//Food color
        0xFF00FF00,
        0xFF00FF00,
        OSD_GRADIENT_DISABLE
    },
    {//Snake color
        0xFFFF00FF,
        0xFFFF00FF,
        OSD_GRADIENT_DISABLE
    },
    {//game over color
        0xFF9CA3B5,
        0xFF9CA3B5,
        OSD_GRADIENT_DISABLE
    },
    {//empty
        0xFF000000,
        0xFF000000,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Snake_Rect_Border_List[] =
{
    {//BG
        0xFF000000, // colorLeftTop;
        0xFF000000, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
    {//FG
        0xFF4F535F, // colorLeftTop;
        0xFF4F535F, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Snake_Text_List[] =
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
static DRAW_BITMAP Snake_Bitmap_List[] =
{
     {//index0  Wall
        E_BMP_MENU_IMG_POP_UP_BLANK,
        TRUE,
        0x0,
        0x0,
        255
     },
     {//index1 Play
        E_BMP_DMP_BUTTON_ICON_PLAY,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index2 Pause
        E_BMP_DMP_BUTTON_ICON_PAUSE,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index3 OK
        E_BMP_BOTTON_OK,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index4 Exit
        E_BMP_BOTTON_EXIT,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
};
#endif  //UI_SKIN_SEL

void MApp_Snake_UpdateScore(void)//draw score
{
    char cstring[20];
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Snake_Text_List[0];
    LPTSTR pstringBuffer = CHAR_BUFFER;
    RECT rect;

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    RECT_SET(rect, 700 + ENCLOSURE_SIZE, 100 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
    RECT_SET(rect, 950 + ENCLOSURE_SIZE, 180 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#endif  //UI_SKIN_SEL
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    RECT_SET(rect, 700 + ENCLOSURE_SIZE, 100 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
    RECT_SET(rect, 950 + ENCLOSURE_SIZE, 180 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#endif  //UI_SKIN_SEL
    sprintf((char *)cstring, "Score : %d", stSnakeLibPara->score);
    MApp_U8StringToU16String((MS_U8*)cstring, (MS_U16*)pstringBuffer, strlen(cstring));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}
void MApp_Snake_DrawPauseInfo(BOOLEAN bEn)
{
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[0];
    RECT rect;
    RECT_SET(rect, (getmaxx() - PAUSE_BAR_WIDTH) , 0, PAUSE_BAR_WIDTH, PAUSE_BAR_HEIGHT);
    if(bEn)
    {
         paramFillRect = &Snake_FillRect_List[4];
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

        DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Snake_Text_List[0];
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

void MApp_Snake_DrawInfo(void)
{
    DEBUG_GAME_SNAKE(printf("MApp_Snake_DrawInfo()\n"););

    DRAW_BITMAP* paramBitmap = &Snake_Bitmap_List[0];
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[0];
    DRAW_RECT_BORDER* paramRectBorder = &Snake_Rect_Border_List[0];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Snake_Text_List[0];
    LPTSTR pstringBuffer = CHAR_BUFFER;
    RECT rect;
    char cstring[20];

    RECT_SET(rect, 0, 0, getmaxx(), getmaxy());
    paramFillRect = &Snake_FillRect_List[5];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Snake", (U16*)pstringBuffer, strlen("Snake"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);


    int x = SNAKE_ACTIVITY_START_X - ENCLOSURE_SIZE;
    int y = SNAKE_ACTIVITY_START_Y - ENCLOSURE_SIZE;

    int Index = SNAKE_ACTIVITY_WIDTH/ENCLOSURE_SIZE;
    RECT_SET(rect, x, y, ENCLOSURE_SIZE, ENCLOSURE_SIZE);
    for (;Index >= 0; Index--)
    {
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
        RECT_SHIFT(rect, ENCLOSURE_SIZE, 0);
    }
    Index = SNAKE_ACTIVITY_HEIGHT/ENCLOSURE_SIZE;
    for (;Index >= 0; Index--)
    {
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
        RECT_SHIFT(rect, 0, ENCLOSURE_SIZE);
    }
    Index = SNAKE_ACTIVITY_WIDTH/ENCLOSURE_SIZE;
    for (;Index >= 0; Index--)
    {
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
        RECT_SHIFT(rect, -ENCLOSURE_SIZE, 0);

    }
    Index =  SNAKE_ACTIVITY_HEIGHT/ENCLOSURE_SIZE;
    for (;Index >= 0; Index--)
    {
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
        RECT_SHIFT(rect, 0, -ENCLOSURE_SIZE);
    }

    RECT_SET(rect,SNAKE_ACTIVITY_START_X, SNAKE_ACTIVITY_START_Y, SNAKE_ACTIVITY_WIDTH, SNAKE_ACTIVITY_HEIGHT);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

#if ( UI_SKIN_SEL != UI_SKIN_960X540XI8 )
    RECT_SET(rect,950,180, 260,380);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramRectBorder, &pdc_Game, &rect);
#endif  //UI_SKIN_SEL

    MApp_Snake_UpdateScore();

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    RECT_SET(rect, 700 + ENCLOSURE_SIZE, 50 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
    RECT_SET(rect, 950 + ENCLOSURE_SIZE, 130 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#endif  //UI_SKIN_SEL
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, &Snake_FillRect_List[1], &pdc_Game, &rect);

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    RECT_SET(rect, 700 + ENCLOSURE_SIZE, 50 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
    RECT_SET(rect, 950 + ENCLOSURE_SIZE, 130 + ENCLOSURE_SIZE*7/4, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
#endif  //UI_SKIN_SEL
    sprintf((char *)cstring, " Rank: %s", (MApp_Game_GetGameLevel()==EN_GAME_RANK_EASY)?"Easy":((MApp_Game_GetGameLevel()==EN_GAME_RANK_NORMAL)?"Normal":"Hard"));
    MApp_U8StringToU16String((MS_U8*)cstring, (MS_U16*)pstringBuffer, strlen(cstring));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
    x = 700 + ENCLOSURE_SIZE;
    y = 100 + ENCLOSURE_SIZE*7/4;
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
    x = 950 + ENCLOSURE_SIZE;
    y = 180 + ENCLOSURE_SIZE*7/4;
#endif  //UI_SKIN_SEL

    RECT_SET(rect, x, y, 260 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2 );
    for (Index = 0; Index < 4; Index++)
    {
        RECT_SHIFT(rect, 0, ENCLOSURE_SIZE*2);
        paramFillRect = &Snake_FillRect_List[1];
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramRectBorder, &pdc_Game, &rect);
    }

    x += ENCLOSURE_SIZE;
    y += ENCLOSURE_SIZE/3;
    RECT_SET(rect, x, y, 30, 30);
    for (Index = 1; Index < 5; Index++)
    {
        RECT_SHIFT(rect, 0, ENCLOSURE_SIZE*2);
        paramBitmap = &Snake_Bitmap_List[Index];
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
    }


    x += ENCLOSURE_SIZE*2;
    RECT_SET(rect, x, y, 160 - ENCLOSURE_SIZE*2, ENCLOSURE_SIZE*3/2);

    RECT_SHIFT(rect, 0, ENCLOSURE_SIZE*2);
    MApp_U8StringToU16String((U8*)"Play", (U16*)pstringBuffer, strlen("Play"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ENCLOSURE_SIZE*2);
    MApp_U8StringToU16String((U8*)"Pause", (U16*)pstringBuffer, strlen("Pause"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ENCLOSURE_SIZE*2);
    MApp_U8StringToU16String((U8*)"OK", (U16*)pstringBuffer, strlen("OK"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SHIFT(rect, 0, ENCLOSURE_SIZE*2);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);
}

void MApp_Snake_DrawGameOver(void)
{
    U32 u32StartX,u32StartY;
    u32StartX = 100;
    u32StartY = 100;

    U16 scrx = getmaxx(), scry = getmaxy();
    RECT rect;
    RECT_SET(rect, (scrx - PASS_BAR_WIDTH) / 2, (scry - PASS_BAR_HEIGHT) / 2, PASS_BAR_WIDTH, PASS_BAR_HEIGHT);

    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[4];

    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    U8 u8Txt[128];
    U16 u16TmpStr[128];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Snake_Text_List[0];

    sprintf((char*)u8Txt, "%s", "Game Over !\a [OK] try again [EXIT] have a rest.");
    MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
    paramTextOut->pString = (LPTSTR)u16TmpStr;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}
void MApp_Snake_DrawSnake(RECT stRect)
{
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &stRect);
}
void MApp_Snake_DrawSnakeEye(RECT stRect)
{
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &stRect);
}

void MApp_Snake_DrawFood(RECT stRect)
{
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[2];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &stRect);
}

void MApp_Snake_DrawBG(RECT stRect)
{
    DRAW_FILL_RECT* paramFillRect = &Snake_FillRect_List[0];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &stRect);
}

void MApp_Snake_GameOver(void)
{
    bSnakeGameOver = TRUE;
    MApp_Snake_UpdateScore();
    MApp_Snake_DrawGameOver();
}

void MApp_Snake_MainTask(void)
{

    if(bSnakeGameOver && gu8SnakeKey == EN_GAME_KEY_SELECT)
    {
        MApp_Snake_Init();
    }

    if(gu8SnakeKey == EN_GAME_KEY_PAUSE && !bIsGamePaused)
    {
        bIsGamePaused = TRUE;
        MApp_Snake_DrawPauseInfo(bIsGamePaused);
    }
    else if(gu8SnakeKey == EN_GAME_KEY_PLAY && bIsGamePaused)
    {
        bIsGamePaused = FALSE;
        MApp_Snake_DrawPauseInfo(bIsGamePaused);
    }


    if(!gbEnableSnakeTask || bSnakeGameOver || bIsGamePaused || MApp_Game_IsShowExitWarningInfo())
        return;

    if (gu8SnakeKey == EN_GAME_KEY_NULL)
    {
        MApp_Snake_UpdateContent(stSnakeLibPara);

        msAPI_Timer_DelayUs((SNAKE_MIN_SPEED + (u32SnakeMaxSpeed - SNAKE_MIN_SPEED) * (MAX_NODE - stSnakeLibPara->score / 10) / MAX_NODE));
    }
    else
    {
        if (gu8SnakeKey == EN_GAME_KEY_UP && stSnakeLibPara->direction != 4)
        {
            stSnakeLibPara->direction = 3;
        }
        else if (gu8SnakeKey == EN_GAME_KEY_RIGHT && stSnakeLibPara->direction != 2)
        {
            stSnakeLibPara->direction = 1;

        }
        else if (gu8SnakeKey == EN_GAME_KEY_LEFT && stSnakeLibPara->direction != 1)
        {
            stSnakeLibPara->direction = 2;
        }
        else  if (gu8SnakeKey == EN_GAME_KEY_DOWN && stSnakeLibPara->direction != 3)
        {
            stSnakeLibPara->direction = 4;
        }
    }
    gu8SnakeKey = EN_GAME_KEY_NULL;
}

BOOLEAN MApp_Snake_Init(void)
{
    DEBUG_GAME_SNAKE(printf("MApp_Snake_Init()\n"););

    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_SNAKE_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Snake support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_SNAKE), u16Ver));

    bSnakeGameOver = FALSE;
    bIsGamePaused = FALSE;
    gbEnableSnakeTask = TRUE;
    gu8SnakeKey = EN_GAME_KEY_NULL;

    snake = msAPI_Memory_Allocate(sizeof(Snake), BUF_ID_APP_GAME);

    if( snake == NULL )
    {
        printf("\nError:snake malloc failed!\n");
        return FALSE;
    }
    memset( snake, 0, sizeof(Snake));

    stSnakeLibPara = msAPI_Memory_Allocate(sizeof(Snake_Library_Para), BUF_ID_APP_GAME);

    if( stSnakeLibPara == NULL )
    {
        printf("\nError:stSnakeLibPara malloc failed!\n");
        return FALSE;
    }
    memset( stSnakeLibPara, 0, sizeof(Snake_Library_Para));

    stSnakeLibPara->u16Snake_Activity_Width = SNAKE_ACTIVITY_WIDTH;
    stSnakeLibPara->u16Snake_Activity_Height = SNAKE_ACTIVITY_HEIGHT;
    stSnakeLibPara->u16Snake_Activity_Start_X = SNAKE_ACTIVITY_START_X;
    stSnakeLibPara->u16Snake_Activity_Start_Y = SNAKE_ACTIVITY_START_Y;
    stSnakeLibPara->u16Snake_Size = SNAKE_SIZE;
    stSnakeLibPara->direction = 1;
    stSnakeLibPara->node = 2;

    snake->x[0] = SNAKE_ACTIVITY_START_X + SNAKE_SIZE * 5;
    snake->y[0] = SNAKE_ACTIVITY_START_Y + SNAKE_SIZE * 5;
    snake->x[1] = snake->x[0] + SNAKE_SIZE;
    snake->y[1] = snake->y[0];

    //set game level
    switch(MApp_Game_GetGameLevel())
    {
        case EN_GAME_RANK_EASY:
            u32SnakeMaxSpeed = SNAKE_MAX_SPEED_L1;
            break;
        case EN_GAME_RANK_NORMAL:
            u32SnakeMaxSpeed = SNAKE_MAX_SPEED_L2;
            break;
        case EN_GAME_RANK_HARD:
            u32SnakeMaxSpeed = SNAKE_MAX_SPEED_L3;
            break;
        default:
            u32SnakeMaxSpeed = SNAKE_MAX_SPEED_L1;
            break;
    }
    MApp_Snake_Library_SetPara(snake->x,snake->y);

    // Draw OSD
    MApp_Snake_DrawInfo();

    return TRUE;
}

//-------------------------------------------------------------------------------------------------
/// Key Input
//-------------------------------------------------------------------------------------------------
BOOLEAN MApp_Snake_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8SnakeKey = enGameKey;
    return TRUE;
}

BOOLEAN MApp_Snake_DeInit(void)
{
    if(gbEnableSnakeTask)
    {
        if( snake )
        {
            msAPI_Memory_Free( snake, BUF_ID_APP_GAME );
            snake = NULL;
        }
        if( stSnakeLibPara )
        {
            msAPI_Memory_Free( stSnakeLibPara, BUF_ID_APP_GAME );
            stSnakeLibPara = NULL;
        }
        gbEnableSnakeTask = FALSE;
        bSnakeGameOver = FALSE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
BOOLEAN MApp_Snake_IsGameOver(void)
{
    return bSnakeGameOver;
}

#endif
