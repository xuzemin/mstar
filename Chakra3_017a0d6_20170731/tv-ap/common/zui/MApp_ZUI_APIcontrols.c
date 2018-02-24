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

#define MAPP_ZUI_APICONTROLS_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


///////////////////////////////////////////////////////////////////////////////////////////////////
// Description: default drawing style and default window proc
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"

#if ENABLE_ATSC_TTS
#include "OSDcp_String_EnumIndex.h"
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif

/////////////////////////////////////////////////////
//NOTE: must be the same bank with table, because of GETNORMALDRAWSTYLE()

#define GUI_CTL_DBG(x) //x

#if ZUI_DBG_RECURSIVE
static BIT _bInDefaultWindowProc = 0;
#endif //ZUI_DBG_RECURSIVE


extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_DefaultWindowProc
///  defualt window proc function, contains static image, static text
///      built-in navigation and window action behavior
///
///  @param [in]       hWnd HWND     window handle we are processing
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_API_DefaultWindowProc (HWND hWnd, PMSG pMsg)
{
    //WINDOWDATA * win;
    //static U16 key;
    //HWND focus;
    //GRAPHIC_DC * pdc;

    //PRINT("\n[Note] enter default winproc\n");

#if ZUI_DBG_RECURSIVE
    if (_bInDefaultWindowProc)
    {
        ZUI_DBG_FAIL(printf("[RECURSIVE]DefaultWindowProc!!\n"));
        ABORT();
        return 0;
    }
    _bInDefaultWindowProc = 1;
#endif //ZUI_DBG_RECURSIVE

    if (hWnd == HWND_INVALID)
    {
        GUI_CTL_DBG(printf("WinProc: HWND_INVALID\n"));
        ABORT();

#if ZUI_DBG_RECURSIVE
        _bInDefaultWindowProc = 0;
#endif //ZUI_DBG_RECURSIVE
        return 0;
    }
    //win = &g_GUI_WindowList[hWnd];
    //printf("[def_winproc]hwnd=%bu,msg=%bu\n", (U8)hWnd, (U8)pMsg->message);

    switch(pMsg->message)
    {
        case MSG_CREATE:
            //initial, so we need not to call MApp_ZUI_API_GetWindowRect()
            //MApp_ZUI_API_InvalidateRect(&GETWNDINITRECT(hWnd));
            MApp_ZUI_API_InvalidateWindow(hWnd);
            break;

        case MSG_KEYDOWN:
            //note: special cases moved to MApp_ZUI_API_DispatchMessage()
            { //general case..
                HWND focus = MApp_ZUI_API_GetFocus();
                BOOLEAN handled = FALSE;

                GUI_CTL_DBG(printf("[def_winproc]focus=%bu\n", (U8)focus));

                if (focus == HWND_INVALID)
                    focus = HWND_MAINFRAME;

                if (GETWNDKEYEVENT(focus))
                {
                    KEYEVENT *keyevent;

                    keyevent = GETWNDKEYEVENT(focus);
                    while (keyevent->u16VirKey != VK_NULL)
                    {
                        if (keyevent->u16VirKey == pMsg->wParam)
                        {
                            handled = MApp_ZUI_ACT_ExecuteWndAction(keyevent->u16ExeActID);
                            //we can allow multiple actions... depend on the last one action..
                        }
                        keyevent++;
                    }
                    if (handled)
                    {
                        return 0;
                    }
                }

                switch(pMsg->wParam)
                {
                    case VK_UP:
                        //MApp_ZUI_API_SetPaneFocus(GETWNDNAVI(focus, NAV_UP));
                        MApp_ZUI_API_SetFocusByNav(focus, NAV_UP);
                        break;
                    case VK_DOWN:
                        //MApp_ZUI_API_SetPaneFocus(GETWNDNAVI(focus, NAV_DOWN));
                        MApp_ZUI_API_SetFocusByNav(focus, NAV_DOWN);
                        break;
                    case VK_RIGHT:
                        //MApp_ZUI_API_SetPaneFocus(GETWNDNAVI(focus, NAV_RIGHT));
                        MApp_ZUI_API_SetFocusByNav(focus, NAV_RIGHT);
                        break;
                    case VK_LEFT:
                        //MApp_ZUI_API_SetPaneFocus(GETWNDNAVI(focus, NAV_LEFT));
                        MApp_ZUI_API_SetFocusByNav(focus, NAV_LEFT);
                        break;
                    /*
                    case VK_SELECT:
                        MApp_ZUI_ACT_ExecuteWndAction(focus, ACTION_SELECT);
                        break;
                    */
                    default:
                        break;
                }

        #if (ENABLE_ATSC_TTS)
                if( (MApp_ZUI_API_GetFocus()==HWND_DMP_PLAYBACK_MOVIEINFO_INFO_INFOCLOSE)
                  ||(MApp_ZUI_API_GetFocus()==HWND_DMP_PLAYBACK_PHOTOINFO_INFO_INFOCLOSE)
                  ||(MApp_ZUI_API_GetFocus()==HWND_DMP_PLAYBACK_MUSICINFO_INFO_INFOCLOSE))
                {
                    //MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Close),MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetU16String(u16CurrentDirFileNum)));
                    MApp_TTS_Cus_AddUniString( MApp_ZUI_API_GetString(en_str_Close) );
                    MApp_TTSControlSetOn(TRUE);
                }
        #endif

#if ZUI_DBG_RECURSIVE
                _bInDefaultWindowProc = 0;
#endif //ZUI_DBG_RECURSIVE

                return 0;
            }
            break;

        /* //note: don't use Send Message in window proc....
        case MSG_NOTIFY:
            if (GETWNDPARENT(hWnd) != hWnd && GETWNDPARENT(hWnd) != HWND_MAINFRAME)
                return MApp_ZUI_API_SendMessage(GETWNDPARENT(hWnd), pMsg->message, pMsg->wParam);
            break;//not supported key...*/

        case MSG_PAINT:
            {
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;

                _MApp_ZUI_API_DefaultOnPaint(hWnd, param, TRUE);
            }
            break;

        default:
            break;
    }

    //PRINT("\n[Note] leave default winproc\n");

#if ZUI_DBG_RECURSIVE
        _bInDefaultWindowProc = 0;
#endif //ZUI_DBG_RECURSIVE

    return 0;
}

#undef MAPP_ZUI_APICONTROLS_C
