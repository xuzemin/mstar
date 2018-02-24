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
#include "Board.h"
#if (GAME_ENABLE && GAME_GOBANG)
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "Utl.h"
#include "msAPI_Memory.h"
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
#include "MApp_Game_Gobang.h"

#define GOBANG_MAX_STEP_X          19
#define GOBANG_MAX_STEP_Y          19

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define PASS_BAR_WIDTH      500
#define PASS_BAR_HEIGHT     60

#define INFO_START_X        700     // Right info block position
#define INFO_START_Y        80

#define GRAPH_OFFSET_X      100     // Grid graph position
#define GRAPH_OFFSET_Y      70
#define GRAPH_GRID_GAP      28
#define GRAPH_BMP_LEN       18
#define GRAPH_CURSOR_LEN    10
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
#define PASS_BAR_WIDTH      800
#define PASS_BAR_HEIGHT     100

#define INFO_START_X        900
#define INFO_START_Y        160

#define GRAPH_OFFSET_X      200
#define GRAPH_OFFSET_Y      100
#define GRAPH_GRID_GAP      30
#define GRAPH_BMP_LEN       18
#define GRAPH_CURSOR_LEN    10
#endif  //UI_SKIN_SEL

static int *_GobangBuf = NULL;

BOOLEAN bGobangGameOver = FALSE;
U8 u8PreCursorX = 0;
U8 u8PreCursorY = 0;
U8 u8CurCursorX = 0;
U8 u8CurCursorY = 0;

BOOLEAN gbEnableGoBangTask = FALSE;
extern GRAPHIC_DC pdc_Game;
extern EN_GAME_RANK gu8CurrentGameLevel;
U8 gu8GoBangKey = EN_GAME_KEY_NULL;

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
static DRAW_FILL_RECT Gobang_FillRect_List[] =
{
    {//BG color
        0x00000048,
        0x00000048,
        OSD_GRADIENT_DISABLE
    },
    {//FG color
        0x00000048,
        0x00000048,
        OSD_GRADIENT_DISABLE
    },
    {//Line color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//black color
        0xFFFFFFFF,
        0xFFFFFFFF,
        OSD_GRADIENT_DISABLE
    },
    {//game over color
        0xFF9CA3B5,
        0xFF9CA3B5,
        OSD_GRADIENT_DISABLE
    },
    {//game cusor
        0x000000CB,
        0x000000CB,
        OSD_GRADIENT_DISABLE
    },
    {//grid
        0xFFD2D22D,
        0xFFD2D22D,
        OSD_GRADIENT_DISABLE
    },
    {//empty
        0xFF000000,
        0xFF000000,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_TEXT_OUT_DYNAMIC Gobang_Text_List[] =
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
static DRAW_BITMAP Gobang_Bitmap_List[] =
{
     {//index0  white chess
        E_BMP_game_white_chess ,
        TRUE,
        0,//0xFF00FF,
        0,//0xFF00FF,
        255
     },
     {//index1 black chess
        E_BMP_game_black_chess,
        TRUE,
        0,//0xFF00FF,
        0,//0xFF00FF,
        255
     },
     {//index2 OK
        E_BMP_BOTTON_OK,
        TRUE,
        5,
        5,
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
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Gobang_FillRect_List[] =
{
    {//BG color
        0xFF4F535F,
        0xFF4F535F,
        OSD_GRADIENT_DISABLE
    },
    {//FG color
        0xFF4F535F,
        0xFF4F535F,
        OSD_GRADIENT_DISABLE
    },
    {//Line color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//black color
        0xFFFFFFFF,
        0xFFFFFFFF,
        OSD_GRADIENT_DISABLE
    },
    {//game over color
        0xFF9CA3B5,
        0xFF9CA3B5,
        OSD_GRADIENT_DISABLE
    },
    {//game cusor
        0xFF00FF00,
        0xFF00FF00,
        OSD_GRADIENT_DISABLE
    },
    {//grid
        0xFFD2D22D,
        0xFFD2D22D,
        OSD_GRADIENT_DISABLE
    },
    {//empty
        0xFF000000,
        0xFF000000,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_TEXT_OUT_DYNAMIC Gobang_Text_List[] =
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
static DRAW_BITMAP Gobang_Bitmap_List[] =
{
     {//index0  white chess
        E_BMP_game_white_chess ,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index1 black chess
        E_BMP_game_black_chess,
        TRUE,
        0xFF00FF,
        0xFF00FF,
        255
     },
     {//index2 OK
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

static void MApp_Gobang_DisplayInfo(void)
{
    RECT rect;
    U32 u32StartX,u32StartY;
    char cstring[20];

    u32StartX = INFO_START_X;
    u32StartY = INFO_START_Y;

    DRAW_FILL_RECT* paramFillRect = &Gobang_FillRect_List[0];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Gobang_Text_List[0];
    DRAW_BITMAP* paramBitmap = &Gobang_Bitmap_List[0];
    LPTSTR pstringBuffer = CHAR_BUFFER;

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Gobang", (U16*)pstringBuffer, strlen("Gobang"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX, u32StartY, 250, 80);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+20, u32StartY+20, 210, 60);
    paramFillRect = &Gobang_FillRect_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+25, u32StartY+25, 180, 40);
    sprintf((char *)cstring, " Rank: %s", (MApp_Game_GetGameLevel()==EN_GAME_RANK_EASY)?"Easy":((MApp_Game_GetGameLevel()==EN_GAME_RANK_NORMAL)?"Normal":"Hard"));
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u32StartX = INFO_START_X;
    u32StartY = INFO_START_Y + 120;

    RECT_SET(rect, u32StartX, u32StartY, 200, 160);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+20, u32StartY+20, 160, 60);
    paramFillRect = &Gobang_FillRect_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+40, u32StartY+30, 40, 40);
    paramBitmap = &Gobang_Bitmap_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SET(rect, u32StartX+90, u32StartY+30, 80, 40);
    MApp_U8StringToU16String((U8*)"Com", (U16*)pstringBuffer, strlen("Com"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);


    u32StartX = u32StartX;
    u32StartY = u32StartY+70;
    RECT_SET(rect, u32StartX+20, u32StartY+20, 160, 60);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+40, u32StartY+30, 40, 40);
    paramBitmap = &Gobang_Bitmap_List[0];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SET(rect, u32StartX+90, u32StartY+30, 80, 40);
    MApp_U8StringToU16String((U8*)"User", (U16*)pstringBuffer, strlen("User"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u32StartX = INFO_START_X;
    u32StartY = INFO_START_Y + 320;

    RECT_SET(rect, u32StartX, u32StartY, 200, 160);
    paramFillRect = &Gobang_FillRect_List[0];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+20, u32StartY+20, 160, 60);
    paramFillRect = &Gobang_FillRect_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+40, u32StartY+30, 40, 40);
    paramBitmap = &Gobang_Bitmap_List[2];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SET(rect, u32StartX+80, u32StartY+30, 80, 40);
    MApp_U8StringToU16String((U8*)"Select", (U16*)pstringBuffer, strlen("Select"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    u32StartX = u32StartX;
    u32StartY = u32StartY+70;
    RECT_SET(rect, u32StartX+20, u32StartY+20, 160, 60);
    paramFillRect = &Gobang_FillRect_List[1];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u32StartX+40, u32StartY+30, 40, 40);
    paramBitmap = &Gobang_Bitmap_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SET(rect, u32StartX+80, u32StartY+30, 80, 40);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}
void MApp_Gobang_DrawBgGrid(void)
{
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.width = getmaxx();
    rect.height = getmaxy();
    DRAW_FILL_RECT* paramFillRect = &Gobang_FillRect_List[7];

    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    rect.left = GRAPH_OFFSET_X - GRAPH_BMP_LEN*2;
    rect.top = GRAPH_OFFSET_Y - GRAPH_BMP_LEN*2;
    rect.width = GRAPH_GRID_GAP*(GOBANG_MAX_STEP_X-1)+GRAPH_BMP_LEN*4;
    rect.height = GRAPH_GRID_GAP*(GOBANG_MAX_STEP_Y-1)+GRAPH_BMP_LEN*4;

    paramFillRect = &Gobang_FillRect_List[6];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    rect.left = GRAPH_OFFSET_X - GRAPH_BMP_LEN/2;
    rect.top = GRAPH_OFFSET_Y - GRAPH_BMP_LEN/2;
    rect.width = GRAPH_GRID_GAP*(GOBANG_MAX_STEP_X-1)+GRAPH_BMP_LEN;
    rect.height = GRAPH_GRID_GAP*(GOBANG_MAX_STEP_Y-1)+GRAPH_BMP_LEN;

    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    paramFillRect = &Gobang_FillRect_List[2];

    U8 u8Idx, u8Idxy;
    U32 u32StartX,u32StartY;
    for(u8Idx=0;u8Idx<GOBANG_MAX_STEP_X;u8Idx++) // vertical line
    {
        u32StartX = GRAPH_OFFSET_X+u8Idx*GRAPH_GRID_GAP;
        u32StartY = GRAPH_OFFSET_Y;

        rect.left = u32StartX;
        rect.top = u32StartY;
        rect.width = 2;
        rect.height = (GOBANG_MAX_STEP_X-1)*GRAPH_GRID_GAP;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    for(u8Idxy=0;u8Idxy<GOBANG_MAX_STEP_X;u8Idxy++)//horizon line
    {
        u32StartX = GRAPH_OFFSET_X;
        u32StartY = GRAPH_OFFSET_Y+u8Idxy*GRAPH_GRID_GAP;

        rect.left = u32StartX;
        rect.top = u32StartY;
        rect.width = (GOBANG_MAX_STEP_X-1)*GRAPH_GRID_GAP;
        rect.height = 2;
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }

    for(u8Idx=0;u8Idx<GOBANG_MAX_STEP_X;u8Idx++)
    {
        for(u8Idxy=0;u8Idxy<GOBANG_MAX_STEP_Y;u8Idxy++)
        {
            if(MApp_Gobang_GetTableValue(u8Idx,u8Idxy) == 0)
            {
                paramFillRect = &Gobang_FillRect_List[6];
                rect.width = GRAPH_CURSOR_LEN;
                rect.height = GRAPH_CURSOR_LEN;
            }
            else
            {
                if(MApp_Gobang_GetTableValue(u8Idx,u8Idxy) == 1)
                    paramFillRect = &Gobang_FillRect_List[2];
                else
                    paramFillRect = &Gobang_FillRect_List[3];

                rect.width = GRAPH_BMP_LEN;
                rect.height = GRAPH_BMP_LEN;
            }

            u32StartX = GRAPH_OFFSET_X+u8Idx*GRAPH_GRID_GAP - rect.width/2;
            u32StartY = GRAPH_OFFSET_Y+u8Idxy*GRAPH_GRID_GAP- rect.height/2;

            rect.left = u32StartX;
            rect.top = u32StartY;
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
        }
    }
    MApp_Gobang_DisplayInfo();

}

//u8idx: 0, user; 1 Computer
BOOLEAN MApp_Gobang_DrawBmp(U8 u8X, U8 u8Y, U8 u8Idx)
{
    if(u8X>GOBANG_MAX_STEP_X || u8Y>GOBANG_MAX_STEP_Y || u8Idx > 2)
    {
        printf("%s, %d, error!! \n", __FUNCTION__, __LINE__);
        return FALSE;
    }
    DRAW_BITMAP* paramBitmap = &Gobang_Bitmap_List[0];
    if(u8Idx == 0)
        paramBitmap = &Gobang_Bitmap_List[0];
    else
        paramBitmap = &Gobang_Bitmap_List[1];

    U32 u32StartX,u32StartY;
    u32StartX = GRAPH_OFFSET_X+u8X*GRAPH_GRID_GAP - 30/2;
    u32StartY = GRAPH_OFFSET_Y+u8Y*GRAPH_GRID_GAP- 30/2;

    RECT rect;
    rect.left = u32StartX;
    rect.top = u32StartY;
    rect.width = 30;
    rect.height = 30;
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    return TRUE;
}
void MApp_Gobang_DrawGameOver(BOOLEAN bUserWin)
{
    U32 u32StartX,u32StartY;
    u32StartX = 100;
    u32StartY = 100;

    int scrx = getmaxx(), scry = getmaxy();
    RECT rect;
    RECT_SET(rect, (scrx - PASS_BAR_WIDTH) / 2, (scry - PASS_BAR_HEIGHT) / 2, PASS_BAR_WIDTH, PASS_BAR_HEIGHT);

    DRAW_FILL_RECT* paramFillRect = &Gobang_FillRect_List[4];

    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    U8 u8Txt[128];
    U16 u16TmpStr[128];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Gobang_Text_List[0];

    if(bUserWin)
        sprintf((char*)u8Txt, "%s", "You Win !\a [OK] try again [EXIT] have a rest.");
    else
        sprintf((char*)u8Txt, "%s", "Game Over !\a [OK] try again [EXIT] have a rest.");
    MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
    paramTextOut->pString = (LPTSTR)u16TmpStr;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

//0, up; 1, right; 2, down;3, left ; 4 set position
void MApp_Gobang_MoveCursor(U8 u8Direction, U8 u8SetPosX, U8 u8SetPosY)
{
    if(u8Direction == 0) // up
    {
        if(u8PreCursorY == 0)
            return;

        u8CurCursorX = u8PreCursorX;
        u8CurCursorY = u8PreCursorY -1;
    }
    else if(u8Direction == 1) // right
    {
        if(u8PreCursorX == GOBANG_MAX_STEP_X-1)
            return;

        u8CurCursorX = u8PreCursorX+1;
        u8CurCursorY = u8PreCursorY;
    }
    else if(u8Direction == 2) // down
    {
        if(u8PreCursorY == GOBANG_MAX_STEP_X-1)
            return;

        u8CurCursorX = u8PreCursorX;
        u8CurCursorY = u8PreCursorY+1;
    }
    else if(u8Direction == 3) // left
    {
        if(u8PreCursorX == 0)
            return;

        u8CurCursorX = u8PreCursorX-1;
        u8CurCursorY = u8PreCursorY;
    }
    else //set cursor position
    {
        u8CurCursorX = u8SetPosX;
        u8CurCursorY = u8SetPosY;
    }

    //printf("%s, %d, (%d, %d) ->(%d, %d) ,\n", __FUNCTION__, __LINE__, u8PreCursorX, u8PreCursorY, u8CurCursorX, u8CurCursorY);

    U8 u8SrcX = u8PreCursorX;
    U8 u8SrcY = u8PreCursorY;
    U8 u8DstX = u8CurCursorX;
    U8 u8DstY = u8CurCursorY;

    if(u8SrcX>GOBANG_MAX_STEP_X || u8SrcY>GOBANG_MAX_STEP_Y
        || u8DstX>GOBANG_MAX_STEP_X || u8DstY>GOBANG_MAX_STEP_Y )
    {
        printf("%s, %d, error!! \n", __FUNCTION__, __LINE__);
        return;
    }

    RECT rect;
    U32 u32StartX,u32StartY;
    DRAW_FILL_RECT* paramFillRect = &Gobang_FillRect_List[0];
    DRAW_BITMAP* paramBitmap = &Gobang_Bitmap_List[0];
    ///SRC...
    if(MApp_Gobang_GetTableValue(u8SrcX,u8SrcY) == 0)
    {
        paramFillRect = &Gobang_FillRect_List[6];

        rect.width = GRAPH_CURSOR_LEN;
        rect.height = GRAPH_CURSOR_LEN;
        u32StartX = GRAPH_OFFSET_X+u8SrcX*GRAPH_GRID_GAP - rect.width/2;
        u32StartY = GRAPH_OFFSET_Y+u8SrcY*GRAPH_GRID_GAP- rect.height/2;

        rect.left = u32StartX;
        rect.top = u32StartY;

        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    }
    else
    {
        if(MApp_Gobang_GetTableValue(u8SrcX,u8SrcY) == 1)
            paramBitmap = &Gobang_Bitmap_List[0];
        else
            paramBitmap = &Gobang_Bitmap_List[1];


        rect.width = 30;
        rect.height = 30;
        u32StartX = GRAPH_OFFSET_X+u8SrcX*GRAPH_GRID_GAP - rect.width/2;
        u32StartY = GRAPH_OFFSET_Y+u8SrcY*GRAPH_GRID_GAP- rect.height/2;

        rect.left = u32StartX;
        rect.top = u32StartY;
        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);
    }

    ////DST...
    u32StartX = GRAPH_OFFSET_X+u8DstX*GRAPH_GRID_GAP - GRAPH_CURSOR_LEN/2;
    u32StartY = GRAPH_OFFSET_Y+u8DstY*GRAPH_GRID_GAP- GRAPH_CURSOR_LEN/2;

    rect.left = u32StartX;
    rect.top = u32StartY;
    rect.width = GRAPH_CURSOR_LEN;
    rect.height = GRAPH_CURSOR_LEN;
    paramFillRect = &Gobang_FillRect_List[5];
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    u8PreCursorX = u8CurCursorX;
    u8PreCursorY = u8CurCursorY;

}

BOOLEAN MApp_Gobang_Select(void)
{
    if(MApp_Gobang_UserSetPoint(u8CurCursorX, u8CurCursorY) == TRUE)
    {
        MApp_Gobang_DrawBmp(u8CurCursorX, u8CurCursorY, 0);

        U8 u8GameOverType = MApp_Gobang_CheckGameOver();
        if(u8GameOverType == 1)
        {
            MApp_Gobang_DrawGameOver(TRUE);
            bGobangGameOver = TRUE;
            //printf("%s, %d, User Win!! \n", __FUNCTION__, __LINE__);
        }
        else if(u8GameOverType == 2)
        {
            MApp_Gobang_DrawGameOver(FALSE);
            bGobangGameOver = TRUE;
            //printf("%s, %d, Computer Win!! \n", __FUNCTION__, __LINE__);
        }
        else
        {
            U8 u8ComX, u8ComY;
            MApp_Gobang_ComSetPoint(&u8ComX, &u8ComY);
            MApp_Gobang_DrawBmp(u8ComX, u8ComY, 1);
            u8GameOverType = MApp_Gobang_CheckGameOver();
            if(u8GameOverType == 1)
            {
                MApp_Gobang_DrawGameOver(TRUE);
                bGobangGameOver = TRUE;
                //printf("%s, %d, User Win!! \n", __FUNCTION__, __LINE__);
                return TRUE;
            }
            else if(u8GameOverType == 2)
            {
                MApp_Gobang_DrawGameOver(FALSE);
                bGobangGameOver = TRUE;
                //printf("%s, %d, Computer Win!! \n", __FUNCTION__, __LINE__);
                return TRUE;
            }
            MApp_Gobang_MoveCursor(4, u8ComX, u8ComY);
        }
    }

    return TRUE;
}
BOOLEAN MApp_Gobang_Init(void)
{
    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_GOBANG_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Gobang support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_GOBANG), u16Ver));

    SIZE sizeStep;

    sizeStep.cx = GOBANG_MAX_STEP_X;
    sizeStep.cy = GOBANG_MAX_STEP_Y;

    U16 u16BufSize;

    if(!MApp_Game_GetLibInfo(GAME_INFO_GOBANG_BUF_SIZE, &sizeStep, &u16BufSize))
    {
        GAME_DEBUG(printf("Can't get gobang buffer size\n"));
        return FALSE;
    }
    GAME_DEBUG(printf("buf size = %d\n", u16BufSize));

    if(_GobangBuf == NULL)
    {
        _GobangBuf = msAPI_Memory_Allocate(u16BufSize, BUF_ID_APP_GAME);

        if(_GobangBuf == NULL)
        {
            GAME_DEBUG(printf(ANSI_COLOR_RED"Alloc gobang buffer fail!\n"ANSI_COLOR_RESET));
            return FALSE;
        }
    }
    bGobangGameOver = FALSE;
    gbEnableGoBangTask = TRUE;
    gu8GoBangKey = EN_GAME_KEY_NULL;

    MApp_Gobang_TableInit(GOBANG_MAX_STEP_X, GOBANG_MAX_STEP_Y, _GobangBuf,MApp_Game_GetGameLevel());
    MApp_Gobang_DrawBgGrid();

    u8PreCursorX = GOBANG_MAX_STEP_X/2;
    u8PreCursorY = GOBANG_MAX_STEP_Y/2;
    u8CurCursorX = GOBANG_MAX_STEP_X/2;
    u8CurCursorY = GOBANG_MAX_STEP_Y/2;
    MApp_Gobang_MoveCursor(4, GOBANG_MAX_STEP_X/2, GOBANG_MAX_STEP_Y/2);

    return TRUE;
}

void MApp_Gobang_MainTask(void)
{
    if(!gbEnableGoBangTask)
        return;

    if (gu8GoBangKey == EN_GAME_KEY_NULL)
    {
        return;
    }
    else//if (u32Key != KEY_NULL)
    {
        if(bGobangGameOver == TRUE)
        {
            if(gu8GoBangKey == EN_GAME_KEY_SELECT)
            {
                MApp_Gobang_Init();
            }
        }
        else
        {
            if(gu8GoBangKey == EN_GAME_KEY_SELECT)
            {
                MApp_Gobang_Select();
            }
            else if(gu8GoBangKey == EN_GAME_KEY_UP)
            {
                MApp_Gobang_MoveCursor(0, 0, 0);
            }
            else if(gu8GoBangKey == EN_GAME_KEY_DOWN)
            {
                MApp_Gobang_MoveCursor(2, 0, 0);
            }
            else if(gu8GoBangKey == EN_GAME_KEY_LEFT)
            {
                MApp_Gobang_MoveCursor(3, 0, 0);
            }
            else if(gu8GoBangKey == EN_GAME_KEY_RIGHT)
            {
                MApp_Gobang_MoveCursor(1, 0, 0);
            }
        }
        gu8GoBangKey = EN_GAME_KEY_NULL;
    }
}
BOOLEAN MApp_Gobang_DeInit(void)
{
    if(_GobangBuf)
    {
        msAPI_Memory_Free(_GobangBuf, BUF_ID_APP_GAME);

        _GobangBuf = NULL;
    }
    if(gbEnableGoBangTask)
    {
        gbEnableGoBangTask = FALSE;
        bGobangGameOver = FALSE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

MS_BOOL MApp_Gobang_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8GoBangKey = enGameKey;
    return TRUE;
}
BOOLEAN MApp_Gobang_IsGameOver(void)
{
    return bGobangGameOver;
}

#endif
