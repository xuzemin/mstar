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

#define MAPP_ZUI_ACTSCREENSAVER_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_Timer.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "ZUI_exefunc.h"
#include "OSDcp_String_EnumIndex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MApp_UiMenuDef.h"
#include "apiGOP.h"
#include "MApp_InputSource.h"

#include "drvAUDIO_if.h"
#include "MApp_GlobalFunction.h"
#if ENABLE_PIP
#include "MApp_PIP.h"
#endif

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif
/////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
RECT rect, main_rect;
//#if (ENABLE_PIP)
#include "MApp_SignalMonitor.h"
RECT sub_rect_L;
RECT sub_rect_R;
RECT rect_pip;
extern BOOLEAN MApp_IsSrcHasSignal(SCALER_WIN);
//#endif

#if ENABLE_ATSC_TTS
static BOOLEAN bNoSignal;
#endif

#if (ENABLE_PIP)
static BOOLEAN MApp_ZUI_ACT_ScreenSaver_PIP_GetSubWinRect(MS_WINDOW_TYPE *pstWinRect)
{
    BOOL bResult;
    bResult = FALSE;
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        U8 u8TempPIP_Offset = 3;
        //First calculate the large sub window width and height
        U16 u16TempPIP_Width = (ZUI_SCREEN_SAVER_WIDTH- SCREEN_SAVER_FRAME_WIDTH)/2 - u8TempPIP_Offset;
        U16 u16TempPIP_Height = u16TempPIP_Width*ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH;
        MS_PIP_SETTING *pstPIPSetting = NULL;

        MApp_GetGenSetting(EN_GENSETTING_CLASS_PIP,  (void *)&pstPIPSetting);
        pstWinRect->x = 0;
        pstWinRect->y = 0;
        pstWinRect->width = ZUI_SCREEN_SAVER_WIDTH;
        pstWinRect->height = ZUI_SCREEN_SAVER_HEIGHT;
        if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
        {
            switch(pstPIPSetting->enPipSize)
            {
                default:
                case EN_PIP_SIZE_LARGE: //125%
                       pstWinRect->width = u16TempPIP_Width;
                       pstWinRect->height = u16TempPIP_Height;
                       break;
                case EN_PIP_SIZE_MEDIUM: //100%
                       pstWinRect->width = u16TempPIP_Width/5*4;
                       pstWinRect->height = pstWinRect->width*ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH;
                       break;
                case EN_PIP_SIZE_SMALL: //75%
                       pstWinRect->width = u16TempPIP_Width/5*3;
                       pstWinRect->height = pstWinRect->width*ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH;
                       break;
            }
            switch(pstPIPSetting->enPipPosition)
            {
                default:
                case EN_PIP_POSITION_LEFT_TOP:
                    pstWinRect->x = 0;
                    pstWinRect->y = 0;
                    break;
                case EN_PIP_POSITION_RIGHT_TOP:
                    pstWinRect->x = (ZUI_SCREEN_SAVER_WIDTH - pstWinRect->width);
                    pstWinRect->y = 0;
                    break;
                case EN_PIP_POSITION_LEFT_BOTTOM:
                    pstWinRect->x = 0;
                    pstWinRect->y = (ZUI_SCREEN_SAVER_HEIGHT - pstWinRect->height);
                    break;
                case EN_PIP_POSITION_RIGHT_BOTTOM:
                    pstWinRect->x = (ZUI_SCREEN_SAVER_WIDTH - pstWinRect->width);
                    pstWinRect->y = (ZUI_SCREEN_SAVER_HEIGHT - pstWinRect->height);
                    break;
            }
            bResult = TRUE;
        }
        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
        {
            pstWinRect->width = ZUI_SCREEN_SAVER_WIDTH/2;
            pstWinRect->height = ZUI_SCREEN_SAVER_HEIGHT;
            pstWinRect->x = ZUI_SCREEN_SAVER_WIDTH/2;
            pstWinRect->y = 0;
            bResult = TRUE;
        }
        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
        {
            pstWinRect->width = ZUI_SCREEN_SAVER_WIDTH/2;
            pstWinRect->height = (ZUI_SCREEN_SAVER_WIDTH/2) * ZUI_SCREEN_SAVER_HEIGHT / ZUI_SCREEN_SAVER_WIDTH;
            pstWinRect->y = ZUI_SCREEN_SAVER_HEIGHT/2-pstWinRect->height/2;
            pstWinRect->x = ZUI_SCREEN_SAVER_WIDTH/2;
            bResult = TRUE;
        }
    }
    return bResult;
}
#endif


void MApp_ZUI_ACT_AppShowScreenSaver(void)
{
    HWND wnd;
    E_OSD_ID osd_id = E_OSD_SCREEN_SAVER;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

#if 0//( CHAKRA3_AUTO_TEST )
    if (g_AT_bChangeSource)	//for no signal
    {
        MApp_AT_SendEvent( E_AT_EVENT_CHANGE_SOURCE_NO_SIGNAL, (void*)msAPI_Timer_GetTime0());
    }
#endif

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }


    RECT_SET(rect,
        ZUI_SCREEN_SAVER_XSTART, ZUI_SCREEN_SAVER_YSTART,
        ZUI_SCREEN_SAVER_WIDTH, ZUI_SCREEN_SAVER_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_BG_PANE, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_FRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_L, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_R, SW_HIDE);

    #if (ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if((MApp_Get_PIPMode() == EN_PIP_MODE_POP) || (MApp_Get_PIPMode()  == EN_PIP_MODE_POP_FULL))
        {
            if(SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NULL)
            {
                MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_L, SW_SHOW);
            }
            if(SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL)
            {
                MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_R, SW_SHOW);
            }
        }
        else
        {
            if(SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NULL)
            {
                MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_FRAME, SW_SHOW);
            }
            if(SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL)
            {
                MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_R,SW_SHOW);
            }
        }
    }
    else
    #endif
    {
        MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_FRAME, SW_SHOW);
    }
    //#endif
#if ENABLE_ATSC_TTS
    bNoSignal = FALSE;
#endif
    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_SHOWUP, E_ZUI_STATE_RUNNING);
}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleScreenSaverKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state
    UNUSED(key);
    /*
    switch(key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetScreenSaverState = STATE_SCREENSAVER_CLEAN_UP;
            return TRUE;
        case VK_POWER:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetScreenSaverState = STATE_SCREENSAVER_GOTO_STANDBY;
            return TRUE;
    }
    */
    return FALSE;
}

BOOLEAN MApp_ZUI_ACT_ExecuteScreenSaverAction(U16 act)
{
    UNUSED(act);
    return FALSE; //ignore...
}

void MApp_ZUI_ACT_TerminateScreenSaver(void)
{
    ZUI_MSG(printf("[]term:ss\n");)
    //enScreenSaverState = _enTargetScreenSaverState;
    SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
    #if (ENABLE_PIP)
    if(IsPIPSupported())
    {
        SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
    }
    #endif
}

LPTSTR MApp_ZUI_ACT_GetScreenSaverDynamicText(HWND hwnd)
{
    U16 u16TempID_main = Empty;
    #if (ENABLE_PIP)
    U16 u16TempID_sub = Empty;
    #endif

    switch(hwnd)
    {
        case HWND_SCREEN_SAVER_TEXT:
        case HWND_SUB_SCREEN_SAVER_TEXT_L:
            switch(SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW))
            {
                case EN_SCREENSAVER_NULL:
                    break;
                case EN_SCREENSAVER_INVALID_SERVICE:
                    u16TempID_main = en_str_INVALID_SERVICE;
                    break;
                case EN_SCREENSAVER_NOT_RUNNING1:
                    u16TempID_main = en_str_Service_Not_Running;//en_str_INVALID_SERVICE;
                    break;
                case EN_SCREENSAVER_NOT_RUNNING2:
                    u16TempID_main = en_str_Service_Not_Running;
                    break;
                case EN_SCREENSAVER_SCRAMBLE: //note: please reference "MIA_SCRAMBLE_CHANNEL_MSG_BOX"
                    u16TempID_main = en_str_NO_CI_MODULE;
                    break;
                case EN_SCREENSAVER_SCRAMBLED_PROGRAM:
                    u16TempID_main = en_str_SCRAMBLED_PROGRAM;
                    break;
                case EN_SCREENSAVER_LOCKED_PROGRAM:
                    u16TempID_main = en_str_CH_BLOCKED;
                    break;
                case EN_SCREENSAVER_BLOCKRATING:
                    u16TempID_main = en_str_RATING_BLOCKED;
                    break;
                case EN_SCREENSAVER_AUDIOONLY:
                    u16TempID_main = en_str_Audio_Only;
                    break;
                case EN_SCREENSAVER_MHEGONLY:
                    u16TempID_main = en_str_MHEG5_ONLY;
                    break;
                case EN_SCREENSAVER_UNSUPPORT_MODE:
					#if ENABLE_ATSC
					u16TempID_main = en_str_Unsupported;
					#else
                    u16TempID_main = en_str_INVALID_FORMAT;
					#endif
					break;
				case EN_SCREENSAVER_OADCHECK:
					u16TempID_main = en_str_OAD_Tuning;
					break;

                default:
                case EN_SCREENSAVER_NO_SHOW_PROGRAM:
                case EN_SCREENSAVER_NOSIGNAL:
                    u16TempID_main = en_str_NO_SIGNAL;
                #if (ENABLE_ATSC_TTS)
                    if (!bNoSignal)
                    {
                        //MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID_main), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID_main)));
                        MApp_TTS_Cus_AddUniString( MApp_ZUI_API_GetString(u16TempID_main) );
                        MApp_TTSControlSetOn(TRUE);
                        bNoSignal = TRUE;
                    }
                #endif
                    break;
            }
            break;
        #if (ENABLE_PIP)
        case HWND_SUB_SCREEN_SAVER_TEXT_R:
            if(IsPIPSupported())
            {
                switch(SYS_SCREEN_SAVER_TYPE(SUB_WINDOW))
                {
                    case EN_SCREENSAVER_NULL:
                        break;
                    case EN_SCREENSAVER_NOT_RUNNING1:
                        u16TempID_sub = en_str_INVALID_SERVICE;
                        break;
                    case EN_SCREENSAVER_NOT_RUNNING2:
                        u16TempID_sub = en_str_Service_Not_Running;
                        break;
                    case EN_SCREENSAVER_SCRAMBLE: //note: please reference "MIA_SCRAMBLE_CHANNEL_MSG_BOX"
                        u16TempID_sub = en_str_NO_CI_MODULE;
                        break;
                    case EN_SCREENSAVER_SCRAMBLED_PROGRAM:
                        u16TempID_sub = en_str_SCRAMBLED_PROGRAM;
                        break;
                    case EN_SCREENSAVER_LOCKED_PROGRAM:
                        u16TempID_sub = en_str_CH_BLOCKED;
                        break;
                    case EN_SCREENSAVER_BLOCKRATING:
                        u16TempID_sub = en_str_RATING_BLOCKED;
                        break;
                    case EN_SCREENSAVER_AUDIOONLY:
                        u16TempID_sub = en_str_Audio_Only;
                        break;
                    case EN_SCREENSAVER_MHEGONLY:
                        u16TempID_sub = en_str_MHEG5_ONLY;
                        break;
                    case EN_SCREENSAVER_UNSUPPORT_MODE:
                        u16TempID_sub = en_str_INVALID_FORMAT;
                        break;
                    case EN_SCREENSAVER_OADCHECK:
                        u16TempID_main = en_str_OAD_Tuning;
                        break;

                    default:
                    case EN_SCREENSAVER_NO_SHOW_PROGRAM:
                    case EN_SCREENSAVER_NOSIGNAL:
                        u16TempID_sub = en_str_NO_SIGNAL;
                        break;
                }
            }
            break;
        #endif
    }

    if(hwnd == HWND_SCREEN_SAVER_TEXT)
    {
        if (u16TempID_main != Empty)
            return MApp_ZUI_API_GetString(u16TempID_main);
    }
    #if (ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if (u16TempID_sub != Empty)
            return MApp_ZUI_API_GetString(u16TempID_sub);
    }
    #endif
    return 0; //for empty string....
}

/////////////////////////////////////////////////////////
// Customize Window Procedures
static MS_U8 _ss_move_x_positive_main;
static MS_U8 _ss_move_y_positive_main;
#if (ENABLE_PIP)
static MS_U8 _ss_move_y_positive_sub;
#endif
#define SCREEN_SAVER_MOVE_STEP 4  //align to 4
#define SCREEN_SAVER_MOVE_INTERVAL 400


S32 MApp_ZUI_ACT_ScreenSaverWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {
                if(hwnd == HWND_SCREEN_SAVER_FRAME)
                {
                    U16 x, y;
                    //MApi_GOP_GWIN_Enable(MApp_ZUI_API_QueryGWinID(), FALSE); //hide it first!
                    srand(msAPI_Timer_GetTime0());

                    #if (ENABLE_PIP)
                    if(IsPIPSupported())
                    {
                        MS_PIP_SETTING *pstPIPSetting = NULL;

                        MApp_GetGenSetting(EN_GENSETTING_CLASS_PIP,  (void *)&pstPIPSetting);
                        if(MApp_Get_PIPMode() == EN_PIP_MODE_POP ||MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                            break;

                        if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                        {
                            if(pstPIPSetting->enPipPosition == EN_PIP_POSITION_RIGHT_TOP
                                || pstPIPSetting->enPipPosition == EN_PIP_POSITION_RIGHT_BOTTOM)
                            {
                                x = ZUI_SCREEN_SAVER_WIDTH/2 - SCREEN_SAVER_FRAME_WIDTH/5*3;
                            }
                            else
                            {
                                x = ZUI_SCREEN_SAVER_WIDTH/2 - SCREEN_SAVER_FRAME_WIDTH/5*2;
                            }
                            y = 0;
                        }
                        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                        {
                            x = 0;
                            y = 0;
                        }
                        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
                        {
                            x = 0;
                            y = ZUI_SCREEN_SAVER_HEIGHT/2 - (ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2;
                        }
                        else
                        {
                            x = ZUI_SCREEN_SAVER_WIDTH/2;
                            y = ZUI_SCREEN_SAVER_HEIGHT/2;
                        }
                    }
                    else
                    #endif
                    {
                        x = ZUI_SCREEN_SAVER_WIDTH/2;
                        y = ZUI_SCREEN_SAVER_HEIGHT/2;
                    }

                    _ss_move_x_positive_main = 1;
                    _ss_move_y_positive_main = 1;
                    if ((rand()%2) == 0)
                        _ss_move_x_positive_main    = 0;
                    if ((rand()%2) == 0)
                        _ss_move_y_positive_main    = 0;

                    main_rect.left = x;
                    main_rect.top = y;
                    main_rect.width = SCREEN_SAVER_FRAME_WIDTH;
                    main_rect.height = SCREEN_SAVER_FRAME_HEIGHT;
                    MApp_ZUI_API_MoveAllSuccessors(hwnd, main_rect.left, main_rect.top);
                    MApp_ZUI_API_SetTimer(hwnd, 0, SCREEN_SAVER_MOVE_INTERVAL);
                }
                #if (ENABLE_PIP)
                else if(hwnd == HWND_SUB_SCREEN_SAVER_FRAME_L && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
                {
                    //First calculate the large sub window width and height
                    U16 sub_x = 0;
                    U16 sub_y = 0;

                    if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                    {
                        break;
                    }

                    if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        sub_x = 0;
                        sub_y = 0;
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
                    {
                        sub_x = 0;
                        sub_y = ZUI_SCREEN_SAVER_HEIGHT/2 - (ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2;
                    }

                    _ss_move_y_positive_sub = 1;

                    sub_rect_L.left = sub_x;
                    sub_rect_L.top = sub_y;
                    sub_rect_L.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                    sub_rect_L.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;

                    MApp_ZUI_API_MoveAllSuccessors(hwnd, sub_rect_L.left, sub_rect_L.top);
                    MApp_ZUI_API_SetTimer(hwnd, 1, SCREEN_SAVER_MOVE_INTERVAL);

                }
                else if(hwnd == HWND_SUB_SCREEN_SAVER_FRAME_R && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
                {
                    //First calculate the large sub window width and height
                    U16 sub_x = 0;
                    U16 sub_y = 0;

                    //if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                        //break;

                    if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        sub_x = ZUI_SCREEN_SAVER_WIDTH/2;
                        sub_y = 0;
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
                    {
                        sub_x = ZUI_SCREEN_SAVER_WIDTH/2;
                        sub_y = ZUI_SCREEN_SAVER_HEIGHT/2 - (ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2;
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                    {
                        MS_WINDOW_TYPE stWinRect;
                        if( MApp_ZUI_ACT_ScreenSaver_PIP_GetSubWinRect(&stWinRect))
                        {
                            //centor of sub windows.
                            sub_x = (stWinRect.width-SUB_SCREEN_SAVER_FRAME_WIDTH)/2 + stWinRect.x;
                            sub_y = stWinRect.y;
                        }
                        else
                        {
                            ZUI_DBG_FAIL(printf("[ZUI]Sub window R count Rect error\n"));
                        }
                    }

                    _ss_move_y_positive_sub = 1;

                    sub_rect_R.left = sub_x;
                    sub_rect_R.top = sub_y;
                    sub_rect_R.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                    sub_rect_R.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                    //printf("settimer start from:x [%d]:y [%d]:h [%d]:w [%d] \n",sub_rect_R.left,sub_rect_R.top,sub_rect_R.height,sub_rect_R.width);

                    MApp_ZUI_API_MoveAllSuccessors(hwnd, sub_rect_R.left, sub_rect_R.top);
                    MApp_ZUI_API_SetTimer(hwnd, 2, SCREEN_SAVER_MOVE_INTERVAL);

                }

                #endif //#if (ENABLE_PIP)
            }
            break;

        case MSG_TIMER:
            {
                MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_BG_PANE,SW_SHOW);

                if(SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NULL)
                {
                    #if (ENABLE_PIP)
                    if(IsPIPSupported()
                        && (MApp_Get_PIPMode() == EN_PIP_MODE_POP || MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL))
                    {
                        MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_L, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_SUB_SCREEN_SAVER_FRAME_L, 1, SCREEN_SAVER_MOVE_INTERVAL);
                        if(IsPIPSupported() && (SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) == EN_SCREENSAVER_NULL))
                            MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_R, SW_HIDE);
                    }
                    else
                    #endif
                    {
                        MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_FRAME, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_SCREEN_SAVER_FRAME, 0, SCREEN_SAVER_MOVE_INTERVAL);
                        #if (ENABLE_PIP)
                        if(IsPIPSupported() && (SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) == EN_SCREENSAVER_NULL))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_R, SW_HIDE);
                        }
                        #endif
                    }
                }


                #if (ENABLE_PIP)
                if(IsPIPSupported() && (SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL))
                {
                    if(MApp_Get_PIPMode() == EN_PIP_MODE_POP || MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL
                        || MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                    {  printf("H_R timer MSG_TIMER\n");
                        MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_R, SW_SHOW);
                        MApp_ZUI_API_SetTimer(HWND_SUB_SCREEN_SAVER_FRAME_R, 2, SCREEN_SAVER_MOVE_INTERVAL);
                        if(IsPIPSupported() && (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) == EN_SCREENSAVER_NULL))
                        {
                            if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                            {
                                MApp_ZUI_API_ShowWindow(HWND_SCREEN_SAVER_FRAME, SW_HIDE);
                            }
                            else
                            {
                                MApp_ZUI_API_ShowWindow(HWND_SUB_SCREEN_SAVER_FRAME_L, SW_HIDE);
                            }
                        }
                    }
                    else
                    {
                        //no sub windows
                    }
                }
                #endif

                if(hwnd == HWND_SCREEN_SAVER_FRAME)
                {
                    MApp_ZUI_API_GetWindowRect(hwnd, &main_rect);

                    #if (ENABLE_PIP)
                    if(IsPIPSupported())
                    {
                        if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                        {
                            if ( main_rect.top < SCREEN_SAVER_MOVE_STEP )
                                _ss_move_y_positive_main = 1;
                            else if ( main_rect.top >= ZUI_SCREEN_SAVER_HEIGHT-SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                                _ss_move_y_positive_main = 0;

                            if ( _ss_move_y_positive_main )
                                main_rect.top += SCREEN_SAVER_MOVE_STEP;
                            else
                                main_rect.top -= SCREEN_SAVER_MOVE_STEP;

                        }
                        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                        {
                        }
                        else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
                        {
                        }
                        else //EN_PIP_MODE_OFF
                        {
                            if ( main_rect.left < SCREEN_SAVER_MOVE_STEP )
                                _ss_move_x_positive_main = 1;
                            else if ( main_rect.left >= ZUI_SCREEN_SAVER_WIDTH-SCREEN_SAVER_FRAME_WIDTH-SCREEN_SAVER_MOVE_STEP )
                                _ss_move_x_positive_main = 0;

                            if ( _ss_move_x_positive_main )
                                main_rect.left += SCREEN_SAVER_MOVE_STEP;
                            else
                                main_rect.left -= SCREEN_SAVER_MOVE_STEP;

                            if ( main_rect.top < SCREEN_SAVER_MOVE_STEP )
                                _ss_move_y_positive_main = 1;
                            else if ( main_rect.top >= ZUI_SCREEN_SAVER_HEIGHT-SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                                _ss_move_y_positive_main = 0;

                            if ( _ss_move_y_positive_main )
                                main_rect.top += SCREEN_SAVER_MOVE_STEP;
                            else
                                main_rect.top -= SCREEN_SAVER_MOVE_STEP;
                        }
                    }
                    else //!IsPIPSupported()
                    #endif
                    {
                        if ( main_rect.left < SCREEN_SAVER_MOVE_STEP )
                            _ss_move_x_positive_main = 1;
                        else if ( main_rect.left >= ZUI_SCREEN_SAVER_WIDTH-SCREEN_SAVER_FRAME_WIDTH-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_x_positive_main = 0;

                        if ( _ss_move_x_positive_main )
                            main_rect.left += SCREEN_SAVER_MOVE_STEP;
                        else
                            main_rect.left -= SCREEN_SAVER_MOVE_STEP;

                        if ( main_rect.top < SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_main = 1;
                        else if ( main_rect.top >= ZUI_SCREEN_SAVER_HEIGHT-SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_main = 0;

                        if ( _ss_move_y_positive_main )
                            main_rect.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            main_rect.top -= SCREEN_SAVER_MOVE_STEP;
                    }

                    main_rect.width = SCREEN_SAVER_FRAME_WIDTH;
                    main_rect.height = SCREEN_SAVER_FRAME_HEIGHT;
                    MApp_ZUI_API_MoveAllSuccessors(hwnd, main_rect.left, main_rect.top);

                    //MApp_ZUI_API_SetGWinPosition(x, y);
                    //MApi_GOP_GWIN_Enable(MApp_ZUI_API_QueryGWinID(), TRUE); //hide it first!
                }
                #if (ENABLE_PIP)
                else if(IsPIPSupported() && hwnd == HWND_SUB_SCREEN_SAVER_FRAME_L)
                {
                    if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                    {
                        #if 0 //if pip mode is pip, Sub SS is fixed in specific location.
                        MApp_ZUI_API_GetWindowRect(hwnd, &sub_rect_L);

                        if ( sub_rect.top < SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 1;
                        else if ( sub_rect.top >= ZUI_SCREEN_SAVER_HEIGHT-SUB_SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 0;

                        if ( _ss_move_y_positive_sub )
                            sub_rect.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            sub_rect.top -= SCREEN_SAVER_MOVE_STEP;

                        sub_rect.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                        sub_rect.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                        #endif
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        #if 1
                        MApp_ZUI_API_GetWindowRect(hwnd, &sub_rect_L);

                        if ( sub_rect_L.top < SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 1;
                        else if ( sub_rect_L.top >= ZUI_SCREEN_SAVER_HEIGHT-SUB_SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 0;

                        if ( _ss_move_y_positive_sub )
                            sub_rect_L.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            sub_rect_L.top -= SCREEN_SAVER_MOVE_STEP;

                        sub_rect_L.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                        sub_rect_L.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                        #endif
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
                    {
                        #if 1
                        MApp_ZUI_API_GetWindowRect(hwnd, &sub_rect_L);

                        if ( sub_rect_L.top < (ZUI_SCREEN_SAVER_HEIGHT/2 - (ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2) + SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 1;
                        else if ( sub_rect_L.top >= (ZUI_SCREEN_SAVER_HEIGHT/2-(ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2)+(ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)-SUB_SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 0;

                        if ( _ss_move_y_positive_sub )
                            sub_rect_L.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            sub_rect_L.top -= SCREEN_SAVER_MOVE_STEP;

                        sub_rect_L.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                        sub_rect_L.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                        #endif
                    }

                    MApp_ZUI_API_MoveAllSuccessors(hwnd, sub_rect_L.left, sub_rect_L.top);
                }
                else if(IsPIPSupported() && hwnd == HWND_SUB_SCREEN_SAVER_FRAME_R)
                {
                    if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                    {

                        MS_WINDOW_TYPE stWinRect;

                        MApp_ZUI_API_GetWindowRect(hwnd, &sub_rect_R);
                        //printf("TIME: BEFOREx [%d]:y [%d]:h [%d]:w [%d] \n",stWinRect.x,stWinRect.y,stWinRect.height,stWinRect.width);

                        if( MApp_ZUI_ACT_ScreenSaver_PIP_GetSubWinRect(&stWinRect))
                        {
                            if ( sub_rect_R.top < stWinRect.y + SCREEN_SAVER_MOVE_STEP )
                                _ss_move_y_positive_sub = 1;
                            else if ( sub_rect_R.top >= stWinRect.y + stWinRect.height- SUB_SCREEN_SAVER_FRAME_HEIGHT - SCREEN_SAVER_MOVE_STEP )
                                _ss_move_y_positive_sub = 0;
                        }
                        else
                        {
                            ZUI_DBG_FAIL(printf("[ZUI]Sub window R count Rect error\n"));
                        }

                        if ( _ss_move_y_positive_sub )
                            sub_rect_R.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            sub_rect_R.top -= SCREEN_SAVER_MOVE_STEP;

                        sub_rect_R.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                        sub_rect_R.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                        //printf("TIME: AFTER [%d]:y [%d]:h [%d]:w [%d] \n",sub_rect_R.left,sub_rect_R.top,sub_rect_R.height,sub_rect_R.width);
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        #if 1
                        MApp_ZUI_API_GetWindowRect(hwnd, &sub_rect_R);

                        if ( sub_rect_R.top < SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 1;
                        else if ( sub_rect_R.top >= ZUI_SCREEN_SAVER_HEIGHT-SUB_SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 0;

                        if ( _ss_move_y_positive_sub )
                            sub_rect_R.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            sub_rect_R.top -= SCREEN_SAVER_MOVE_STEP;

                        sub_rect_R.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                        sub_rect_R.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                        #endif
                    }
                    else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP)
                    {
                        #if 1
                        MApp_ZUI_API_GetWindowRect(hwnd, &sub_rect_R);

                        if ( sub_rect_R.top < (ZUI_SCREEN_SAVER_HEIGHT/2 - (ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2) + SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 1;
                        else if ( sub_rect_R.top >= (ZUI_SCREEN_SAVER_HEIGHT/2-(ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)/2)+(ZUI_SCREEN_SAVER_WIDTH/2 * ZUI_SCREEN_SAVER_HEIGHT/ZUI_SCREEN_SAVER_WIDTH)-SUB_SCREEN_SAVER_FRAME_HEIGHT-SCREEN_SAVER_MOVE_STEP )
                            _ss_move_y_positive_sub = 0;

                        if ( _ss_move_y_positive_sub )
                            sub_rect_R.top += SCREEN_SAVER_MOVE_STEP;
                        else
                            sub_rect_R.top -= SCREEN_SAVER_MOVE_STEP;

                        sub_rect_R.width = SUB_SCREEN_SAVER_FRAME_WIDTH;
                        sub_rect_R.height = SUB_SCREEN_SAVER_FRAME_HEIGHT;
                        #endif
                    }
                    MApp_ZUI_API_MoveAllSuccessors(hwnd, sub_rect_R.left, sub_rect_R.top);
                }
                #endif //#if (ENABLE_PIP)
            }
            break;
            default:
                break;
        }
        return DEFAULTWINPROC(hwnd, msg);
}

#undef MAPP_ZUI_ACTSCREENSAVER_C
