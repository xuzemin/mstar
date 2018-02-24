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
#define MAPP_ZUI_ACTGAMELIST_C
#define _ZUI_INTERNAL_INSIDE_

#include "Board.h"
#include "datatype.h"

#if GAME_ENABLE

/******************************************************************************/
/*   Header Files                                                                                                           */
/******************************************************************************/

#include "MsCommon.h"
#include "Utl.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "msAPI_Global.h"
#include "MApp_GlobalVar.h"
#include "MApp_SaveData.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "ZUI_exefunc.h"
#include "MApp_Game_lib.h"
#include "MApp_Game_Main.h"
#include "ZUI_tables_h.inl"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "MApp_ZUI_ACTGameList.h"
#include "MApp_Menu_Main.h"

#undef DBG_TRACE
#ifdef MS_DEBUG
#define DBG_TRACE(fmt, args...) printf(fmt, ##args)
#else
#define DBG_TRACE(fmt, args...) {}
#endif


/******************************************************************************/
/*   Extern Function                                                                                                        */
/******************************************************************************/

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

/******************************************************************************/
/*   Local Function                                                                                                        */
/******************************************************************************/

void MApp_ZUI_ACT_AppShowGameList(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_GAME_LIST;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);


    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }
#if 0
    RECT_SET(rect,
        ZUI_GAME_XSTART, ZUI_GAME_YSTART,
        ZUI_GAME_WIDTH, ZUI_GAME_HEIGHT);
#endif
    RECT_SET(rect,
           ZUI_GAME_LIST_XSTART, ZUI_GAME_LIST_YSTART,
           ZUI_GAME_LIST_WIDTH, ZUI_GAME_LIST_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_GAMELIST_BG_PANE, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_GAMELIST_LIST_PANE, SW_SHOW);

    if(MApp_Game_GetGameItemIndex() != EN_GAME_NUM)
    {
        wnd = (MApp_Game_GetGameItemIndex() * 2) + HWND_GAMELIST_ITEM0;
    }
    else
    {
        U16 i;

        wnd = HWND_GAMELIST_ITEM0;

        for(i=0; i<100; i++)
        {
            if(MApp_ZUI_ACT_QueryGameItemStatus(wnd) == EN_DL_STATE_NORMAL)
                break;

            wnd = GETWNDNAVI(wnd)[NAV_DOWN];
        }
    }

    MApp_ZUI_API_SetFocus(wnd);

}


///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_ExecuteAction_MenuProgManuSearch
///
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteGameListAction(U16 act)
{
    switch (act)
    {
        case EN_EXE_START_GAME:
            if(MApp_Game_Init())
            {
                MApp_Game_SetState(GAME_STATE_WAIT_IN_GAME);
            }
            return TRUE;

        case EN_EXE_POWEROFF:
            return TRUE;

        case EN_EXE_GOTO_TV_SOURCE:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            MApp_Game_SetState(GAME_STATE_GOTO_TVSOURCE);
            return TRUE;

        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            return TRUE;

        default:
            break;
    }
    return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_HandleGameListKey
///
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_HandleGameListKey(VIRTUAL_KEY_CODE key)
{
    HWND wnd;

    switch (key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_GOTO_TV_SOURCE);
            return TRUE;

        case VK_MENU:
        case VK_LEFT:
            if( (MApp_ZUI_API_GetFocus() >= HWND_GAMELIST_LEVEL_ITEM0)
             && (MApp_ZUI_API_GetFocus() <= HWND_GAMELIST_LEVEL_ITEM10) )
            {
                wnd = (MApp_Game_GetGameListIdx() * 2) + HWND_GAMELIST_ITEM0;

                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_BG_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_LEVEL_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_TOP_HALF_BANNER_TITLE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_LIST_PANE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_TOP_HALF_BANNER_TITLE, SW_SHOW);
                MApp_ZUI_API_SetFocus(wnd);
            }
            else
            {
                MApp_Game_SetState(GAME_STATE_GOTO_INPUTSOURCE);
            }
            return TRUE;

        case VK_SELECT:
        case VK_RIGHT:
            if(MApp_Game_CheckGameLevelSupport(MApp_ZUI_API_GetFocus()))
            {
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_LIST_PANE, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_BG_PANE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_GAMELIST_LEVEL_PANE, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_GAMELIST_LEVEL_ITEM0);
            }
            else
            {
                if((MApp_ZUI_API_GetFocus() >= HWND_GAMELIST_LEVEL_ITEM0)&&(MApp_ZUI_API_GetFocus() <= HWND_GAMELIST_LEVEL_ITEM10))
                {
                   MApp_Game_SetGameLevel(MApp_ZUI_API_GetFocus());
                }

                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_START_GAME);
            }
            return TRUE;

        default:
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_TerminateGameList
///
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ACT_TerminateGameList(void)
{
    //MApp_ZUI_API_KillTimer(HWND_PROG_MANUSEARCH_SPBARGROUP, 0); //delete auto-close timer.
    //tvview_ShowBlackScreen();

}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetDynamicText_GameList
///
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetDynamicText_GameList(HWND hwnd)
{
    UNUSED(hwnd);
    return NULL;
}
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryGameItemStatus(HWND hwnd)
{
    U8 u8ItemIndex= ((hwnd - HWND_GAMELIST_ITEM0) / 2);

    if(u8ItemIndex < EN_GAME_NUM)
    {
        EN_GAME_TYPE enGameType = MApp_Game_GetGameListByIdx(u8ItemIndex);

        switch(enGameType)
        {
        #if GAME_BOXMAN
            case EN_GAME_BOXMAN:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_BOXMAN))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_BOXMAN
        #if GAME_GOBANG
            case EN_GAME_GOBANG:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_GOBANG))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_GOBANG
        #if GAME_SNAKE
            case EN_GAME_SNAKE:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_SNAKE))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_SNAKE
        #if GAME_SUDOKU
            case EN_GAME_SUDOKU:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_SUDOKU))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_SUDOKU
        #if GAME_TETRIS
            case EN_GAME_TETRIS:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_TETRIS))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_TETRIS
        #if GAME_MINES
            case EN_GAME_MINES:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_MINES))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_MINES
        #if GAME_SHOT
            case EN_GAME_SHOT:
                if(MApp_Game_IsLibSupport(GAME_IS_SUPPORT_SHOT))
                {
                    return EN_DL_STATE_NORMAL;
                }
                break;
        #endif  //GAME_SHOT


                default:
                    break;
        }
    }
    return EN_DL_STATE_HIDDEN;
 }

LPTSTR MApp_ZUI_ACT_GetGameListDynamicText(HWND hwnd)
{
    char* pau8String = NULL;
    U8 u8Index = ((hwnd - HWND_GAMELIST_ITEM0_TEXT) / 2);

    switch(hwnd)
    {
        case HWND_GAMELIST_LEVEL_ITEM0_TEXT:
            pau8String = "Easy";
            MApp_U8StringToU16String ((U8*)pau8String, CHAR_BUFFER, strlen(pau8String) );
            return CHAR_BUFFER;
            break;

        case HWND_GAMELIST_LEVEL_ITEM1_TEXT:
            pau8String = "Normal";
            MApp_U8StringToU16String ((U8*)pau8String, CHAR_BUFFER, strlen(pau8String) );
            return CHAR_BUFFER;
            break;

       case HWND_GAMELIST_LEVEL_ITEM2_TEXT:
            pau8String = "Hard";
            MApp_U8StringToU16String ((U8*)pau8String, CHAR_BUFFER, strlen(pau8String) );
            return CHAR_BUFFER;
            break;
        default:
            break;
    }

    if(hwnd == HWND_GAMELIST_TOP_HALF_BANNER_TITLE)
    {
        if((MApp_ZUI_API_GetFocus() >= HWND_GAMELIST_LEVEL_ITEM0)&&(MApp_ZUI_API_GetFocus() <= HWND_GAMELIST_LEVEL_ITEM10))
        {
            pau8String = "Game Level";
        }
        else
        {
            pau8String = "Game List";
        }

        MApp_U8StringToU16String ((U8*)pau8String, CHAR_BUFFER, strlen(pau8String) );
        return CHAR_BUFFER;
    }
    else// for game items text
    {
        if(EN_GAME_NUM > u8Index)
        {
            pau8String = MApp_Game_GetGameName(u8Index);
            MApp_U8StringToU16String ((U8*)pau8String, CHAR_BUFFER, strlen(pau8String) );
            return CHAR_BUFFER;
        }
    }
    return NULL;
}

#endif
#undef MAPP_ZUI_ACTGAMELIST_C
