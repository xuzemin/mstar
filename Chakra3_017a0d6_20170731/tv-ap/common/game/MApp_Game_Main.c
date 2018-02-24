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

#define MAPP_GAME_MAIN_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include "Board.h"
#include "Utl.h"
#if GAME_ENABLE
#define _ZUI_INTERNAL_INSIDE_
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiGOP.h"
#include "msAPI_Global.h"
#include "MApp_GlobalFunction.h"

#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"


#include "InfoBlock.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_IR.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_Game_Main.h"
#include "MApp_InputSource.h"
#include "MApp_Func_AudioVolume.h"
#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "MApp_PowerOnMusic.h"
#include "MApp_ZUI_ACTGameList.h"
#include "MApp_Game_lib.h"
#if GAME_TETRIS
#include "MApp_Game_Tetris.h"
#endif  //GAME_TETRIS
#if GAME_BOXMAN
#include "MApp_Game_Boxman.h"
#endif  //GAME_BOXMAN
#if GAME_GOBANG
#include "MApp_Game_Gobang.h"
#endif  //GAME_GOBANG
#if GAME_SNAKE
#include "MApp_Game_Snake.h"
#endif  //GAME_SNAKE
#if GAME_SUDOKU
#include "MApp_Game_Sudoku.h"
#endif  //GAME_SUDOKU
#if GAME_MINES
#include "MApp_Game_Mines.h"
#endif  //GAME_MINES
#if GAME_SHOT
#include "MApp_Game_Shot.h"
#endif  //GAME_SHOT

/******************************************************************************/
/*   Local Defines                                                                                                         */
/******************************************************************************/

#define DEBUG_GAME_STATE(x)         //x


#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )
#define WARNING_INFOBAR_WIDTH   600
#define WARNING_INFOBAR_HEIGHT  30
#else
#define WARNING_INFOBAR_WIDTH   800
#define WARNING_INFOBAR_HEIGHT  40
#endif  //UI_SKIN_960X540XI8

EN_GAME_STATE enGameState;
EN_GAME_RANK gu8CurrentGameLevel = EN_GAME_RANK_NONE;

static EN_GAME_TYPE enGameType = EN_GAME_NUM;

BOOLEAN bShowWarningMessage = FALSE;
GRAPHIC_DC pdc_Game;

U8 gu8GameListIndex = 0xFF;

typedef struct
{
    EN_GAME_TYPE eGameType;
    char* pcGameName;
    BOOLEAN (*pfGameInit)(void);
    BOOLEAN (*pfGameDeInit)(void);
    void (*pfGameTask)(void);
    BOOLEAN (*pfGameKeyInput)(EN_GAME_KEY enGameKey);
}StuGameInfo;

static StuGameInfo* s_pstCurGameInfo = NULL;

static StuGameInfo g_AllGameInfo[] =
{
#if GAME_BOXMAN
    {EN_GAME_BOXMAN, "Boxman", MApp_Boxman_Init, MApp_Boxman_DeInit, MApp_Boxman_MainTask, MApp_Boxman_KeyInput},
#endif  //GAME_BOXMAN
#if GAME_GOBANG
    {EN_GAME_GOBANG, "Gobang", MApp_Gobang_Init, MApp_Gobang_DeInit, MApp_Gobang_MainTask, MApp_Gobang_KeyInput},
#endif  //GAME_GOBANG
#if GAME_SNAKE
    {EN_GAME_SNAKE,  "Snake", MApp_Snake_Init, MApp_Snake_DeInit, MApp_Snake_MainTask, MApp_Snake_KeyInput},
#endif  //GAME_SNAKE
#if GAME_SUDOKU
    {EN_GAME_SUDOKU, "Sudoku", MApp_Sudoku_Init, MApp_Sudoku_DeInit, MApp_Sudoku_MainTask, MApp_Sudoku_KeyInput},
#endif  //GAME_SUDOKU
#if GAME_TETRIS
    {EN_GAME_TETRIS, "Tetris", MApp_Tetris_Init, MApp_Tetris_DeInit, MApp_Tetris_MainTask, MApp_Tetris_KeyInput},
#endif  //GAME_TETRIS
#if GAME_MINES
    {EN_GAME_MINES, "Mines", MApp_Mines_Init, MApp_Mines_DeInit, MApp_Mines_MainTask, MApp_Mines_KeyInput},
#endif  //GAME_MINES
#if GAME_SHOT
    {EN_GAME_SHOT, "Shot", MApp_Shot_Init, MApp_Shot_DeInit, MApp_Shot_MainTask, MApp_Shot_KeyInput},
#endif  //GAME_SHOT

};

EN_GAME_TYPE s_aeGameList[] = // for game list order
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

};

EN_GAME_RANK s_aeGameRankList[] = // for game rank list order
{
    EN_GAME_RANK_NONE,
    EN_GAME_RANK_EASY,
    EN_GAME_RANK_NORMAL,
    EN_GAME_RANK_HARD,
    EN_GAME_RANK_NUM,
};

#if ( UI_SKIN_SEL == UI_SKIN_960X540XI8 )

static DRAW_FILL_RECT FillRect_List[] =
{
    {//BG color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//info color
        0x000000C2,
        0x000000C2,
        OSD_GRADIENT_DISABLE
    },
};
static DRAW_TEXT_OUT_DYNAMIC Text_List[] =
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

#else
static DRAW_FILL_RECT FillRect_List[] =
{
    {//BG color
        0x00000000,
        0x00000000,
        OSD_GRADIENT_DISABLE
    },
    {//info color
        0x00FF0000,
        0x00FF0000,
        OSD_GRADIENT_DISABLE
    },
};
static DRAW_TEXT_OUT_DYNAMIC Text_List[] =
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
#endif

/******************************************************************************/
/*   Local Function                                                                                                        */
/******************************************************************************/

BOOLEAN MApp_Game_IsShowExitWarningInfo(void)
{
    return bShowWarningMessage;
}

void MApp_Game_ShowExitWarningInfo(BOOLEAN bEn)
{
    DRAW_FILL_RECT* paramFillRect = &FillRect_List[0];
    RECT rect;
    RECT_SET(rect, (getmaxx() - WARNING_INFOBAR_WIDTH) , 0, WARNING_INFOBAR_WIDTH, WARNING_INFOBAR_HEIGHT);
    bShowWarningMessage = bEn;
    if(bEn)
    {
         paramFillRect = &FillRect_List[1];
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

        DRAW_TEXT_OUT_DYNAMIC* paramTextOut = &Text_List[0];
        U8 u8Txt[128];
        U16 u16TmpStr[128];
        sprintf((char*)u8Txt, "%s", "Are you sure to Exit game? [OK] to Exit, [Exit] to cancel.");
        MApp_U8StringToU16String((U8*)u8Txt, (U16*)u16TmpStr, strlen((char*)u8Txt));
        paramTextOut->pString = (LPTSTR)u16TmpStr;
        _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, paramTextOut, &pdc_Game, &rect);

    }
    else
    {
        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, &pdc_Game, &rect);

    }
}

StuGameInfo* MApp_Game_FindGameInfo(EN_GAME_TYPE eGameType)
{
    U8 u8Index;

    for( u8Index = 0; u8Index < (sizeof(g_AllGameInfo) / sizeof(StuGameInfo)); ++u8Index)
    {
        if( g_AllGameInfo[u8Index].eGameType == eGameType )
            return &(g_AllGameInfo[u8Index]);
    }

    return NULL;
}

U8 MApp_Game_GetGameListIdx(void)
{
    return gu8GameListIndex;
}

EN_GAME_TYPE MApp_Game_GetGameListByIdx(U8 u8Index)
{
    if(u8Index < COUNTOF(s_aeGameList))
    {
        return s_aeGameList[u8Index];
    }
    return EN_GAME_UNKNOW;
}

EN_GAME_RANK MApp_Game_GetGameLevelListByIdx(U8 u8Index)
{
    if(u8Index < COUNTOF(s_aeGameRankList))
    {
        return s_aeGameRankList[u8Index];
    }
    return EN_GAME_RANK_NORMAL;
}

char* MApp_Game_GetGameName(U8 u8Index)
{
    StuGameInfo* s_pstGameInfo = NULL;
    s_pstGameInfo = MApp_Game_FindGameInfo(s_aeGameList[u8Index]);
    return s_pstGameInfo->pcGameName;
}

EN_GAME_RANK MApp_Game_GetGameLevel(void)
{
    return gu8CurrentGameLevel;
}

void MApp_Game_SetGameLevel(HWND hwnd)
{
    if((hwnd<HWND_GAMELIST_LEVEL_ITEM0)||(hwnd>HWND_GAMELIST_LEVEL_ITEM10))
       return;

    U8 u8LevelIndex = ((hwnd - HWND_GAMELIST_LEVEL_ITEM0) / 2)+1;

    gu8CurrentGameLevel = MApp_Game_GetGameLevelListByIdx(u8LevelIndex);
}

BOOLEAN MApp_Game_CheckGameLevelSupport(HWND hwnd)
{
    if( (hwnd < HWND_GAMELIST_ITEM0)||(hwnd > HWND_GAMELIST_ITEM10) )
        return FALSE;

    gu8GameListIndex = ((hwnd - HWND_GAMELIST_ITEM0) / 2);
    EN_GAME_TYPE GameType = MApp_Game_GetGameListByIdx(gu8GameListIndex);

    switch(GameType)
    {
    #if ( GAME_SNAKE )
        case EN_GAME_SNAKE:
            return TRUE;
    #endif  //GAME_SNAKE

    #if ( GAME_GOBANG )
        case EN_GAME_GOBANG:
            return TRUE;
    #endif  //GAME_GOBANG

    #if ( GAME_SUDOKU )
        case EN_GAME_SUDOKU:
            return TRUE;
    #endif  //GAME_SUDOKU

    #if ( GAME_TETRIS )
        case EN_GAME_TETRIS:
            return TRUE;
    #endif  //GAME_TETRIS

    #if ( GAME_MINES )
        case EN_GAME_MINES:
            return TRUE;
    #endif  //GAME_MINES

    #if ( GAME_SHOT)
        case EN_GAME_SHOT:
            return TRUE;
    #endif  //GAME_SHOT

        default:
            break;
    }

    return FALSE;
}

U8 MApp_Game_GetGameItemIndex(void)
{
    return enGameType;
}

void MApp_Game_UpdateGameType(void)
{
    U8 u8GameIndex = gu8GameListIndex;//((MApp_ZUI_API_GetFocus() - HWND_GAMELIST_ITEM0) / 2);//gu8GameListIndex;

    if( u8GameIndex < (sizeof(s_aeGameList) / sizeof(EN_GAME_TYPE)) )
    {
        enGameType = s_aeGameList[u8GameIndex];
    }

    s_pstCurGameInfo = MApp_Game_FindGameInfo(enGameType);

    if( s_pstCurGameInfo == NULL )
    {
        printf("\nError: Can't fine game! Use default game\n");
        s_pstCurGameInfo = &(g_AllGameInfo[0]);
    }
}

BOOLEAN MApp_Game_Graphics_Init(void)
{
   RECT rect;
   RECT_SET(rect, 0, 0, getmaxx(), getmaxy());

   MApp_ZUI_API_TerminateGDI();

   if (!MApp_ZUI_API_InitGDI(&rect))
   {
       printf("\nWarning: MApp_ZUI_API_InitGDI() return FALSE!!!\n");
       ABORT();
       return FALSE;
   }
   pdc_Game = *MApp_ZUI_API_GetScreenDC();
   pdc_Game.bSrcAlphaReplaceDstAlpha = TRUE;

   return TRUE;
}

BOOLEAN MApp_Game_Init(void)
{
    GAME_DEBUG(printf("MApp_Game_Init()\n"););

    MApp_UiMenu_MuteWin_Hide();

    MApp_Game_UpdateGameType();

    if( FALSE == MApp_Game_Graphics_Init() )
    {
        printf("\nError: MApp_Game_Graphics_Init failed!\n");
        return FALSE;
    }

    if( s_pstCurGameInfo == NULL )
        return FALSE;

    if( NULL == s_pstCurGameInfo->pfGameInit )
    {
        return FALSE;
    }

    BOOLEAN bResult = s_pstCurGameInfo->pfGameInit();

    if( bResult == FALSE )
    {
        printf("\nError: pfGameInit() failed!\n");
        return FALSE;
    }

#if ENABLE_SOUNDTEST_MUSIC_LOOP
    MApp_SoundTest_ON(TRUE);
#endif

    return bResult;
}

void MApp_Game_Exit(void)
{
    GAME_DEBUG(printf("MApp_Game_Exit()\n"););

#if ENABLE_SOUNDTEST_MUSIC_LOOP
    MApp_SoundTest_Exit();
    MApp_InputSource_ChangeAudioSource( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),UI_INPUT_SOURCE_NONE);
#endif

    if( s_pstCurGameInfo == NULL )
        return ;

    if( s_pstCurGameInfo->pfGameDeInit )
    {
        s_pstCurGameInfo->pfGameDeInit();
        MApp_ZUI_ACT_ShutdownOSD();
        MApp_Game_SetState(GAME_STATE_INIT);
    }
    if (msAPI_AUD_IsAudioMutedByUser())
    {
        MApp_UiMenu_MuteWin_Show();
    }
}

void MApp_Game_ProcessKey(U8 u8key)
{
    EN_GAME_KEY enGameKey = EN_GAME_KEY_NULL;
    static U8 u8PreKey = KEY_NULL;

    switch(u8key) //general key action
    {
        case KEY_MUTE:
            if (msAPI_AUD_IsAudioMutedByUser() == FALSE)
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            else
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            break;

        case KEY_VOLUME_PLUS:
        case KEY_VOLUME_MINUS:
            MApp_FuncExec_AdjustVolume(u8key == KEY_VOLUME_PLUS ? VK_VOLUME_PLUS : VK_VOLUME_MINUS);
            break;
			
		case VK_KEYSTONE_PLUS:      //xzm @ 20171227 for keystone
				stGenSetting.g_SysSetting.KeyStoneValue++;
		      if(stGenSetting.g_SysSetting.KeyStoneValue >= 38)
			  	stGenSetting.g_SysSetting.KeyStoneValue=39;
			
			  printf("ks2=%d",stGenSetting.g_SysSetting.KeyStoneValue);
			  keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;
			
		case VK_KEYSTONE_MINUS:
			 stGenSetting.g_SysSetting.KeyStoneValue--;
			  if(stGenSetting.g_SysSetting.KeyStoneValue <=-38)
			  	stGenSetting.g_SysSetting.KeyStoneValue=-39;

			  printf("ks1=%d",stGenSetting.g_SysSetting.KeyStoneValue);
			  keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;

        case KEY_EXIT:
        {
            if(
            #if GAME_TETRIS
                MApp_Tetris_IsGameOver() ||
            #endif  //GAME_TETRIS
            #if GAME_BOXMAN
                MApp_Boxman_IsGameOver() ||
            #endif  //GAME_BOXMAN
            #if GAME_GOBANG
                MApp_Gobang_IsGameOver() ||
            #endif  //GAME_GOBANG
            #if GAME_SNAKE
                MApp_Snake_IsGameOver() ||
            #endif  //GAME_SNAKE
            #if GAME_SUDOKU
                MApp_Sudoku_IsGameOver() ||
            #endif  //GAME_SUDOKU

            #if GAME_MINES
                MApp_Mines_IsGameOver() ||
            #endif  //GAME_MINES
            #if GAME_SHOT
                MApp_Shot_IsGameOver() ||
            #endif  //GAME_SHOT

            FALSE
            )
            {
                MApp_Game_Exit();
            }
            else
            {
                u8PreKey = KEY_EXIT;
                MApp_Game_ShowExitWarningInfo(!bShowWarningMessage);
            }
        }
        break;
        case KEY_SELECT:
        {
            if(bShowWarningMessage)
            {
                bShowWarningMessage = FALSE;

                if(u8PreKey == KEY_EXIT)
                {
                    MApp_Game_Exit();
                }
                else if(u8PreKey == KEY_POWER)
                {
                    MApp_Game_SetState(GAME_STATE_GOTO_STANDBY);
                }

                u8PreKey = KEY_NULL;
            }
        }
        break;
        case KEY_POWER:
        {
            if(
            #if GAME_TETRIS
                MApp_Tetris_IsGameOver() ||
            #endif  //GAME_TETRIS
            #if GAME_BOXMAN
                MApp_Boxman_IsGameOver() ||
            #endif  //GAME_BOXMAN
            #if GAME_GOBANG
                MApp_Gobang_IsGameOver() ||
            #endif  //GAME_GOBANG
            #if GAME_SNAKE
                MApp_Snake_IsGameOver() ||
            #endif  //GAME_SNAKE
            #if GAME_SUDOKU
                MApp_Sudoku_IsGameOver() ||
            #endif  //GAME_SUDOKU
            #if GAME_MINES
                MApp_Mines_IsGameOver() ||
            #endif  //GAME_MINES
            #if GAME_SHOT
                MApp_Shot_IsGameOver() ||
            #endif  //GAME_SHOT

            FALSE
            )
            {
                MApp_Game_SetState(GAME_STATE_GOTO_STANDBY);
            }
            else
            {
                u8PreKey = KEY_POWER;
                MApp_Game_ShowExitWarningInfo(!bShowWarningMessage);
            }
        }
        break;
        default:
            break;
    }


    if( s_pstCurGameInfo == NULL || bShowWarningMessage)
        return ;
    // key input control in game

    switch (u8key)// for Game key remapping
    {
        case KEY_UP:
        {
            enGameKey = EN_GAME_KEY_UP;
        }
        break;

        case KEY_DOWN:
        {
            enGameKey = EN_GAME_KEY_DOWN;
        }
        break;

        case KEY_LEFT:
        {
            enGameKey = EN_GAME_KEY_LEFT;
        }
        break;

        case KEY_RIGHT:
        {
            enGameKey = EN_GAME_KEY_RIGHT;
        }
        break;

        case KEY_SELECT:
        {
            enGameKey = EN_GAME_KEY_SELECT;
        }
        break;

        case KEY_EXIT:
        {
            enGameKey = EN_GAME_KEY_EXIT;
        }
        break;

        case KEY_PLAY:
        {
            enGameKey = EN_GAME_KEY_PLAY;
        }
        break;

        case KEY_PAUSE:
        {
            enGameKey = EN_GAME_KEY_PAUSE;
        }
        break;

        case KEY_0:
        {
            enGameKey = EN_GAME_KEY_NUM0;
        }
        break;

        case KEY_1:
        {
            enGameKey = EN_GAME_KEY_NUM1;
        }
        break;

        case KEY_2:
        {
            enGameKey = EN_GAME_KEY_NUM2;
        }
        break;

        case KEY_3:
        {
            enGameKey = EN_GAME_KEY_NUM3;
        }
        break;

        case KEY_4:
        {
            enGameKey = EN_GAME_KEY_NUM4;
        }
        break;

        case KEY_5:
        {
            enGameKey = EN_GAME_KEY_NUM5;
        }
        break;

        case KEY_6:
        {
            enGameKey = EN_GAME_KEY_NUM6;
        }
        break;

        case KEY_7:
        {
            enGameKey = EN_GAME_KEY_NUM7;
        }
        break;

        case KEY_8:
        {
            enGameKey = EN_GAME_KEY_NUM8;
        }
        break;

        case KEY_9:
        {
            enGameKey = EN_GAME_KEY_NUM9;
        }
        break;

        default:
            break;
    }
    if( s_pstCurGameInfo->pfGameKeyInput && enGameKey != EN_GAME_KEY_NULL)
    {
        s_pstCurGameInfo->pfGameKeyInput(enGameKey);

    }
}

void MApp_Game_MultiTask(void)
{
    MApp_ProcessUserInput();
    MApp_Game_ProcessKey(u8KeyCode);
    u8KeyCode = KEY_NULL;

    if( s_pstCurGameInfo == NULL )
        return;

    if( s_pstCurGameInfo->pfGameTask )
        s_pstCurGameInfo->pfGameTask();

#if ENABLE_SOUNDTEST_MUSIC_LOOP
    MApp_SoundTest_Task(BIN_ID_GAME_MUSIC);
#endif
}

EN_GAME_STATE MApp_Game_GetState(void)
{
    return enGameState;
}

void MApp_Game_SetState(EN_GAME_STATE enState)
{
    enGameState = enState;
}

EN_RET MApp_Game_Main(void)
{
    EN_RET enRetVal = EXIT_NULL;

    switch(enGameState)
    {
        case GAME_STATE_INIT:
            //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_GAME, ENABLE, 0, MAIN_WINDOW);
            msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            enGameState = GAME_STATE_WAIT_IN_LIST;
            DEBUG_GAME_STATE(printf("Game_STATE_INIT\n"));
            MApp_ZUI_ACT_StartupOSD(E_OSD_GAME_LIST);
            break;

        case GAME_STATE_WAIT_IN_LIST:
            DEBUG_GAME_STATE(printf("GAME_STATE_WAIT_IN_LIST\n"));
            MApp_ProcessUserInput();
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;
        case GAME_STATE_WAIT_IN_GAME:
            DEBUG_GAME_STATE(printf("GAME_STATE_WAIT_IN_GAME\n"));
            MApp_Game_MultiTask();
            break;

        case GAME_STATE_GOTO_TVSOURCE:
            DEBUG_GAME_STATE(printf("Game_STATE_GOTO_TVSOURCE\n"));
            msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);
            MApp_ZUI_ACT_ShutdownOSD();
            enGameType = EN_GAME_NUM;
            enGameState = GAME_STATE_INIT;
            enRetVal = EXIT_GOTO_TV;
            break;

        case GAME_STATE_CLEAN_UP:
            DEBUG_GAME_STATE(printf("Game_STATE_CLEAN_UP\n"));
            MApp_ZUI_ACT_ShutdownOSD();
            enGameState = GAME_STATE_INIT;
            enRetVal = EXIT_CLOSE;
            break;

        case GAME_STATE_GOTO_STANDBY:
            DEBUG_GAME_STATE(printf("Game_STATE_GOTO_STANDBY\n"));
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal = EXIT_GOTO_STANDBY;
            break;

        case GAME_STATE_GOTO_MENU:
            DEBUG_GAME_STATE(printf("Game_STATE_GOTO_MENU\n"));
            MApp_ZUI_ACT_ShutdownOSD();
            enGameState = GAME_STATE_INIT;
            enRetVal = EXIT_GOTO_MENU;
            break;

        case GAME_STATE_GOTO_INPUTSOURCE:
            DEBUG_GAME_STATE(printf("Game_STATE_GOTO_INPUTSOURCE\n"));
            MApp_ZUI_ACT_ShutdownOSD();
            enGameState = GAME_STATE_INIT;
            enRetVal = EXIT_GOTO_INPUTSOURCE;
            break;

        default:
            printf("\nError: Out of state control\n");
            enGameState = GAME_STATE_INIT;
            break;
    }
    return enRetVal;
}

BOOLEAN MApp_Game_UiExec(U16 u16Cmd, void *para)
{
    BOOLEAN ret = FALSE;

    switch(u16Cmd)
    {
#if GAME_SNAKE
        case GAME_UI_SNAKE_GAMEOVER:
            MApp_Snake_GameOver();
            break;

        case GAME_UI_SNAKE_UPDATESCORE:
            MApp_Snake_UpdateScore();
            break;

        case GAME_UI_SNAKE_DRAWBG:
        {
            RECT *rc = para;
            MApp_Snake_DrawBG(*rc);
        }
            break;

        case GAME_UI_SNAKE_DRAWFOOD:
        {
            RECT *rc = para;
            MApp_Snake_DrawFood(*rc);
        }
            break;

        case GAME_UI_SNAKE_DRAWSNAKE:
        {
            RECT *rc = para;
            MApp_Snake_DrawSnake(*rc);
        }
            break;

        case GAME_UI_SNAKE_DRAWSNAKEEYE:
        {
            RECT *rc = para;
            MApp_Snake_DrawSnakeEye(*rc);
        }
            break;
#endif

        default:
            if(para)
            {
            }
            break;
    }
    return ret;
}


#endif
#undef MAPP_GAME_MAIN_C

