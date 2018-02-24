//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and U16ernational treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and U16erest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or U16erest to MStar Software and any
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

#if (GAME_ENABLE && GAME_BOXMAN)
#define _ZUI_INTERNAL_INSIDE_
#include "MsCommon.h"
#include "datatype.h"
#include "Utl.h"
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
#include "MApp_Game_Boxman.h"

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define GAME_AREA_X         75//((getmaxx() - BLOCK_X * BOXMAN_MAP_X_NUM) / 3)
#define GAME_AREA_Y         75
#define BLOCK_X             35
#define BLOCK_Y             35

#define PASS_BAR_WIDTH      600
#define PASS_BAR_HEIGHT     60
#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
#define GAME_AREA_X         125//((getmaxx() - BLOCK_X * BOXMAN_MAP_X_NUM) / 3)
#define GAME_AREA_Y         125
#define BLOCK_X             40
#define BLOCK_Y             40

#define PASS_BAR_WIDTH      800
#define PASS_BAR_HEIGHT     100
#endif  //UI_SKIN_SEL

#define BOXMAN_MAP_X_NUM           16
#define BOXMAN_MAP_Y_NUM           12

U8 gau8Map[BOXMAN_MAP_Y_NUM][BOXMAN_MAP_X_NUM];

U16 NowLevel;
U16 MaxLevel;

extern U16 gu16Man_X, gu16Man_Y;

U16 gu16Step;
BOOLEAN  gbBoxmanPass;

static BOOLEAN    gbEnableBoxManTask = FALSE;

EN_GAME_KEY gu8BoxmanKey = EN_GAME_KEY_NULL;

extern GRAPHIC_DC pdc_Game;

#define  MAX_LEVEL      6
//===================================================
#if 0
char Level0[] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,2,0,0,3,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,4,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,6,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

char Level1[] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,
    1,0,0,0,1,5,0,0,3,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,
    1,0,0,0,1,0,0,2,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,6,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

char Level2[] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,2,0,0,3,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,4,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,0,1,0,0,0,0,1,1,1,
    1,0,0,0,3,0,0,0,0,0,1,0,0,0,0,1,
    1,0,0,2,0,0,6,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
#else
char Level0[] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,2,0,0,3,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,4,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,6,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

char Level1[] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,2,0,0,3,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,2,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,0,1,0,0,0,0,1,1,1,
    1,0,0,0,3,0,0,0,0,0,1,0,0,0,0,1,
    1,0,2,0,0,0,5,0,0,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

char Level2[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,
    0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,
    0,0,0,1,1,2,1,1,1,0,0,0,1,0,0,0,
    0,0,0,1,0,4,0,2,0,0,2,0,1,0,0,0,
    0,0,0,1,0,3,3,1,0,2,0,1,1,0,0,0,
    0,0,0,1,1,3,3,1,0,0,0,1,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

char Level3[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,
    0,0,0,0,0,1,4,2,0,0,1,0,0,0,0,0,
    0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,
    0,0,0,0,1,3,1,0,1,0,0,1,0,0,0,0,
    0,0,0,0,1,3,2,0,0,1,0,1,0,0,0,0,
    0,0,0,0,1,3,0,0,0,2,0,1,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

char Level4[] =
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,
   0,0,0,0,0,1,1,0,0,1,0,4,1,0,0,0,
   0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,
   0,0,0,0,0,1,2,0,2,0,2,0,1,0,0,0,
   0,0,0,0,0,1,0,2,1,1,0,0,1,0,0,0,
   0,0,0,1,1,1,0,2,0,1,0,1,1,0,0,0,
   0,0,0,1,3,3,3,3,3,0,0,1,0,0,0,0,
   0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

char Level5[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,
    0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,0,
    0,0,0,1,2,0,1,1,1,0,2,1,0,0,0,0,
    0,0,0,1,0,1,3,3,3,1,0,1,0,0,0,0,
    0,0,1,1,0,1,3,3,3,1,0,1,1,0,0,0,
    0,0,1,0,2,0,0,2,0,0,2,0,1,0,0,0,
    0,0,1,0,0,0,0,0,1,0,4,0,1,0,0,0,
    0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
#endif

char* g_BoxMan_AllMap[MAX_LEVEL] =
{
    Level0, Level1, Level2, Level3, Level4, Level5,
};

//=============================================================


#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
static DRAW_FILL_RECT Boxman_FillRect_List[] =
{
    {//Empty area
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//Info block
        0x00000007,
        0x00000007,
        OSD_GRADIENT_DISABLE
    },
};

static DRAW_RECT_BORDER Boxman_Rect_Border_List[] =
{
    {//Ball
        0x000000CB, // colorLeftTop;
        0x000000CB, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Boxman_Text_List[] =
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
static DRAW_BITMAP Boxman_Bitmap_List[] =
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
        E_BMP_MENU_IMG_GRIDE_UP_ARROW,
        TRUE,
        7,
        7,
        255
     },
     {//index4 Down
        E_BMP_MENU_IMG_GRIDE_DOWN_ARROW,
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
};

#else   //UI_SKIN_SEL = UI_SKIN_1366X768X565, and so on..
static DRAW_FILL_RECT Boxman_FillRect_List[] =
{
    {//Empty area
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//Info block
        0x00C0C0C0,
        0x00C0C0C0,
        OSD_GRADIENT_DISABLE
    },

};
static DRAW_RECT_BORDER Boxman_Rect_Border_List[] =
{
    {//Ball
        0x00FF00FF, // colorLeftTop;
        0x00FF00FF, // colorRightDown;
        2, // thickness;
        eSolidLine // lt;
    },
};

static DRAW_TEXT_OUT_DYNAMIC Boxman_Text_List[] =
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
static DRAW_BITMAP Boxman_Bitmap_List[] =
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
        E_BMP_MENU_IMG_GRIDE_UP_ARROW,
        TRUE,
        0x00FFFFFF,
        0x00FFFFFF,
        255
     },
     {//index4 Down
        E_BMP_MENU_IMG_GRIDE_DOWN_ARROW,
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
};

#endif  //UI_SKIN_SEL
void MApp_Boxman_DrawBlock(U16 u16Y, U16 u16X, U16 u16Object)
{

    U16 u16XStart = GAME_AREA_X + u16X * BLOCK_X + 1;
    U16 u16YStart = GAME_AREA_Y + u16Y * BLOCK_Y + 1;

    RECT    rect;
    DRAW_FILL_RECT* paramFillRect = &Boxman_FillRect_List[0];
    DRAW_BITMAP* paramBitmap = &Boxman_Bitmap_List[0];
    DRAW_RECT_BORDER* paramRectBorder = &Boxman_Rect_Border_List[0];

    switch (u16Object)
    {
        case EMPTY:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
        }
        break;

        case WALL:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Boxman_Bitmap_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;

        case BOX:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramBitmap = &Boxman_Bitmap_List[1];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;
        case MAN:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
            paramBitmap = &Boxman_Bitmap_List[2];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game, &rect);
        }
        break;

        case BALL:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
            paramRectBorder = &Boxman_Rect_Border_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);
        }
        break;

        case MANBALL:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramRectBorder = &Boxman_Rect_Border_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);

            paramBitmap = &Boxman_Bitmap_List[2];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;

        case BOXBALL:
        {
            RECT_SET(rect, u16XStart, u16YStart, BLOCK_X, BLOCK_Y);
            paramRectBorder = &Boxman_Rect_Border_List[0];
            _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, &pdc_Game, &rect);

            RECT_SET(rect, u16XStart+1, u16YStart+1, BLOCK_X, BLOCK_Y);
            paramBitmap = &Boxman_Bitmap_List[1];
            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap, &pdc_Game,&rect);
        }
        break;
        default:
        break;
    }
}

static void MApp_Boxman_DisplayInfo(void)
{
    RECT rect;
    char cstring[20];

    U16 u16StartX,u16StartY;

    DRAW_FILL_RECT* paramFillRect = &Boxman_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Boxman_Text_List[0];

    u16StartX = GAME_AREA_X+BOXMAN_MAP_X_NUM*BLOCK_X+GAME_AREA_X+BLOCK_X*2/3;
    u16StartY = GAME_AREA_Y+BLOCK_Y*3/2;

    //RECT_SET(rect, startx-BLOCK_Y*2/3, starty-BLOCK_Y*2/3, BLOCK_X*6, BLOCK_Y*5);
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    //RECT_SET(rect, startx, starty, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    sprintf((char *)cstring, " Max Level: %d", MaxLevel);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    //U16StartX = U16StartX;
    u16StartY = u16StartY+BLOCK_Y+BLOCK_Y/3;
    RECT_SET(rect, u16StartX, u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);
    sprintf((char *)cstring, " Current Level: %d", NowLevel);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    //U16StartX = U16StartX;
    u16StartY = u16StartY+BLOCK_Y+BLOCK_Y/3;
    RECT_SET(rect, u16StartX,  u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u16StartX,  u16StartY, BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    sprintf((char *)cstring, " Your Step: %d", gu16Step);
    MApp_U8StringToU16String((U8*)cstring, (U16*)paramTextOut->pString, strlen(cstring));
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Boxman_GameInit(void)
{
    gu16Step = 0;
    gbBoxmanPass = FALSE;
    U16 u16Index_x, u16Index_y;


    if( (NowLevel < 1) || (NowLevel > MAX_LEVEL) )
    {
        return ;
    }
    memset(gau8Map,0,sizeof(gau8Map));
    U8* pu8BoxManMap = &gau8Map[0][0];

    MApp_Boxman_LoadMap(BOXMAN_MAP_Y_NUM,BOXMAN_MAP_X_NUM,pu8BoxManMap,g_BoxMan_AllMap[NowLevel-1]);

    MApp_Boxman_GetManPosition();
    LPTSTR pstringBuffer = CHAR_BUFFER;

    u16Index_y = getmaxx() / 2;

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Boxman_FillRect_List[0];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Boxman_Text_List[0];
    DRAW_BITMAP* paramBitmap = &Boxman_Bitmap_List[0];

    RECT_SET(rect, 0, 0, getmaxx(), getmaxy());
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, 0, 0, TITLE_POSITION_X, TITLE_POSITION_Y);
    MApp_U8StringToU16String((U8*)"Box Man", (U16*)pstringBuffer, strlen("Box Man"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    for (u16Index_y = 0;u16Index_y < BOXMAN_MAP_Y_NUM;u16Index_y++)
    {
        for (u16Index_x = 0;u16Index_x < BOXMAN_MAP_X_NUM;u16Index_x++)
        {
            //MApp_Boxman_DrawBlock(u16Index_y, u16Index_x, gau8Map[u16Index_y][u16Index_x]);
            MApp_Boxman_DrawBlock(u16Index_y, u16Index_x, MApp_Boxman_GetMapData(u16Index_y, u16Index_x) );
        }
    }

    MApp_Boxman_DisplayInfo();

    U16 u16StartX,U16StartY;
    u16StartX = GAME_AREA_X + BOXMAN_MAP_X_NUM*BLOCK_X + GAME_AREA_X;
    U16StartY = GAME_AREA_Y + BLOCK_Y*6 + BLOCK_Y/2;

    RECT_SET(rect, u16StartX, U16StartY, BLOCK_X*6, BLOCK_Y*5);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u16StartX+BLOCK_X*2/3, U16StartY+BLOCK_Y*2/3,  BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y*2+BLOCK_Y/3);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    u16StartX = u16StartX + BLOCK_X*3;
    U16StartY = U16StartY - BLOCK_Y/3;
    RECT_SET(rect, u16StartX-BLOCK_X/2, U16StartY+BLOCK_Y*4/3, 34, 20);
    paramBitmap = &Boxman_Bitmap_List[3];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SHIFT(rect, 0, BLOCK_Y*4/3);
    paramBitmap = &Boxman_Bitmap_List[4];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SET(rect, u16StartX-BLOCK_X, U16StartY+BLOCK_Y*3/2+BLOCK_Y/3, 20, 34);
    paramBitmap = &Boxman_Bitmap_List[5];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SHIFT(rect, BLOCK_X*4/3, 0);
    paramBitmap = &Boxman_Bitmap_List[6];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    u16StartX = u16StartX-BLOCK_X*7/3;
    U16StartY = U16StartY+BLOCK_Y*11/3;
    RECT_SET(rect, u16StartX, U16StartY,  BLOCK_X*4+BLOCK_X*2/3, BLOCK_Y);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    RECT_SET(rect, u16StartX+BLOCK_X*2/3, U16StartY+BLOCK_Y/6, 34, 30);
    paramBitmap = &Boxman_Bitmap_List[7];
    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP,paramBitmap,&pdc_Game,&rect);

    RECT_SET(rect, u16StartX+BLOCK_X*5/2, U16StartY, BLOCK_X*2, BLOCK_Y);
    MApp_U8StringToU16String((U8*)"Exit", (U16*)pstringBuffer, strlen("Exit"));
    paramTextOut->pString = pstringBuffer;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

}

void MApp_Boxman_UpdataMap(U16 x1, U16 y1, U16 x2, U16 y2, U16 x3, U16 y3)
{
    MApp_Boxman_UpdataObject(x1, y1, x2, y2, x3, y3);
    gu16Step++;
    MApp_Boxman_DisplayInfo();


//    MApp_Boxman_DrawBlock(y1, x1, gau8Map[y1][x1]);
  //  MApp_Boxman_DrawBlock(y2, x2, gau8Map[y2][x2]);
    //MApp_Boxman_DrawBlock(y3, x3, gau8Map[y3][x3]);

    MApp_Boxman_DrawBlock(y1, x1, MApp_Boxman_GetMapData(y1,x1) );
    MApp_Boxman_DrawBlock(y2, x2, MApp_Boxman_GetMapData(y2,x2) );
    MApp_Boxman_DrawBlock(y3, x3, MApp_Boxman_GetMapData(y3,x3) );
}

BOOLEAN MApp_Boxman_WinGame(void)
{
    U16 u16Index_x, u16Index_y;

    U16 scrx = getmaxx(), scry = getmaxy();

    for (u16Index_y = 0;u16Index_y < BOXMAN_MAP_Y_NUM;u16Index_y++)
    {
        for (u16Index_x = 0;u16Index_x < BOXMAN_MAP_X_NUM;u16Index_x++)
        {
            //if (gau8Map[u16Index_y][u16Index_x] == BOX)
            if ( MApp_Boxman_GetMapData(u16Index_y, u16Index_x) == BOX)
                return FALSE;
        }
    }

    RECT rect;
    DRAW_FILL_RECT* paramFillRect = &Boxman_FillRect_List[1];
    DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Boxman_Text_List[0];

    RECT_SET(rect, (scrx - PASS_BAR_WIDTH) / 2, (scry - PASS_BAR_HEIGHT) / 2, PASS_BAR_WIDTH, PASS_BAR_HEIGHT);
    _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    U8 u8Txt[100];
    U16 u16TmpStr[100];
    if(NowLevel == MaxLevel)
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

    gbBoxmanPass = TRUE;
    if (NowLevel == MaxLevel)
    {
        NowLevel = 1;
    }
    else
    {
        NowLevel++;
    }
    return TRUE;
}

void MApp_Boxman_MainTask(void)
{
    static U16 x1=0, y1=0, x2=0, y2=0, x3=0, y3=0;
    if(!gbEnableBoxManTask)
        return;

    if (gu8BoxmanKey == EN_GAME_KEY_NULL)
    {
        return;
    }
    else//if (u32Key != KEY_NULL)
    {
        if(gbBoxmanPass)
        {
            if(gu8BoxmanKey == EN_GAME_KEY_SELECT)
            {
                MApp_Boxman_GameInit();
            }
            #if 0
            else if(gu32BoxmanKey == ESC)
            {
                gbPass = FALSE;
            }
            #endif
        }
        else
        {
            x1 = gu16Man_X;
            y1 = gu16Man_Y;

            switch (gu8BoxmanKey)
            {
                case EN_GAME_KEY_UP:
                    x2 = x1;
                    y2 = y1 - 1;
                    x3 = x1;
                    y3 = y1 - 2;
                    break;
                case EN_GAME_KEY_DOWN:
                    x2 = x1;
                    y2 = y1 + 1;
                    x3 = x1;
                    y3 = y1 + 2;
                    break;
                case EN_GAME_KEY_LEFT:
                    x2 = x1 - 1;
                    y2 = y1;
                    x3 = x1 - 2;
                    y3 = y1;
                    break;
                case EN_GAME_KEY_RIGHT:
                    x2 = x1 + 1;
                    y2 = y1;
                    x3 = x1 + 2;
                    y3 = y1;
                    break;
                default:
                    break;
            }
            MApp_Boxman_UpdataMap(x1, y1, x2, y2, x3, y3);
            MApp_Boxman_WinGame();
        }
        gu8BoxmanKey = EN_GAME_KEY_NULL;

    }

}

/*
U16 MApp_Boxman_GetMaxLevel(void)
{
    char* pmapAarry[] = LEVEL_MAP_ARRAY;

    MAX_LEVEL = (sizeof(pmapAarry) / sizeof(U32));

    return MAX_LEVEL;
}
*/

BOOLEAN MApp_Boxman_Init(void)
{
    //MApp_Boxman_Graphics_Init();

    U16 u16Ver;

    MApp_Game_GetLibInfo(GAME_INFO_BOXMAN_VERSION, NULL, &u16Ver);

    GAME_DEBUG(printf("Boxman support:%d, ver:%d\n", MApp_Game_IsLibSupport(GAME_IS_SUPPORT_BOXMAN), u16Ver));

    gbEnableBoxManTask = TRUE;

    NowLevel = 1;
    MaxLevel = MAX_LEVEL;//MApp_Boxman_GetMaxLevel();
    MApp_Boxman_GameInit();
    gu8BoxmanKey = EN_GAME_KEY_NULL; //clean select key action to avoid update map

    return TRUE;
}

BOOLEAN MApp_Boxman_DeInit(void)
{
    if(gbEnableBoxManTask)
    {
        gbEnableBoxManTask = FALSE;
        gbBoxmanPass = FALSE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN MApp_Boxman_KeyInput(EN_GAME_KEY enGameKey)
{
    gu8BoxmanKey = enGameKey;
    return TRUE;
}

BOOLEAN MApp_Boxman_IsGameOver(void)
{
    return gbBoxmanPass;
}

#endif
