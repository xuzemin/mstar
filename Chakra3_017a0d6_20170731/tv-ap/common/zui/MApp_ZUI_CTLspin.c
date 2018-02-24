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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "datatype.h"
#include "msAPI_OSD.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIalphatables.h"

//extern bool MApp_ZUI_API_DoesIntersect (const RECT* psrc1, const RECT* psrc2);
//extern S32 _MApp_ZUI_API_ExecuteAction(ACTION_ENUM act, void * act_param);

///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_SpinPaint
///  paint function for "Spin" control
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     window message
///
///  This function doesn't return a value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_CTL_SpinPaint(HWND hwnd, PMSG pMsg)
{
    RECT ri;
    PAINT_PARAM * param = (PAINT_PARAM *)pMsg->wParam;
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    GUI_DATA_SPIN * windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);
    GUI_DATA_SPIN_INTERNAL * list;

    if (param->bIsDisable)
    {
        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hwnd);
    }
    else if (param->bIsFocus) //the same focus group
    {
        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
    }
    else
    {
        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);
    }

    //left button
    ri = *param->rect;
    ri.width = windata->u16ButtonWidth;
    RECT_SCALE(ri, windata->u16ButtonBorder, windata->u16ButtonBorder);
    if ((windata->u16FormatFlag & SP_FLAG_HIDE_LBUTTON) == 0)
    {
        if ((windata->u16FormatFlag & SP_FLAG_LEFT_PRESSING) != 0)
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, windata->pLeftButtonPressing);
        else
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, windata->pLeftButtonNormal);
    }

    //right button
    ri.left = param->rect->left + param->rect->width - windata->u16ButtonBorder - ri.width;
    if ((windata->u16FormatFlag & SP_FLAG_HIDE_RBUTTON) == 0)
    {
        //PRINT("_MApp_ZUI_API_SpinPaint(): fmt=%X\n", data->u16FormatFlag);
        if ((windata->u16FormatFlag & SP_FLAG_RIGHT_PRESSING) != 0)
        {
            //PRINT("_MApp_ZUI_API_SpinPaint(): A\n", data->u16FormatFlag);
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, windata->pRightButtonPressing);
        }
        else
        {
            //PRINT("_MApp_ZUI_API_SpinPaint(): B\n", data->u16FormatFlag);
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, windata->pRightButtonNormal);
        }
    }

    //content
    ri.top = param->rect->top;
    ri.height = param->rect->height;
    ri.width = param->rect->width - 2*windata->u16ButtonWidth;
    ri.left = param->rect->left + windata->u16ButtonWidth;
    list = &windata->pVardata->list;
    if (ri.width > 0 &&
        list->pItems &&
        list->u16Count &&
        list->u16FocusIndex < list->u16Count)
    {
        if (param->bIsFocus)
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, list->pItems[list->u16FocusIndex].pDrawItemFocus);
        else
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, list->pItems[list->u16FocusIndex].pDrawItemNormal);
    }
}


///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_SpinKeyDown
///  key down handler for "Spin" control
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static S32 _MApp_ZUI_CTL_SpinKeyDown(HWND hwnd, PMSG pMsg)
{
    //U16 i;
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    GUI_DATA_SPIN * windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);
    GUI_DATA_SPIN_INTERNAL * list;
    list = &windata->pVardata->list;

    if ( !list->u16Count )
    {
        //PRINT("_MApp_ZUI_API_SpinKeyDown: empty content\n");
        return DEFAULTWINPROC(hwnd, pMsg); //empty content
    }

    /*/control focus only if visible, enabled and got focus...
    if (GETWNDSTATE(hwnd)&WS_DISABLED ||
        (GETWNDSTATE(hwnd)&WS_VISIBLE) == 0 ||
        MApp_Menu_WndGetFocus() != hwnd)
    {
        //PRINT("_MApp_ZUI_API_SpinKeyDown: no focus\n");
        return DEFAULTWINPROC(hwnd, pMsg);
    }*/

    if (list->u16FocusIndex >= list->u16Count)
        list->u16FocusIndex = 0;
    switch(pMsg->wParam)
    {
        case VK_LEFT:
            if (windata->u16FormatFlag & SP_FLAG_HIDE_LBUTTON)
                return DEFAULTWINPROC(hwnd, pMsg);
            list->u16FocusIndex = (list->u16Count+list->u16FocusIndex-1) % list->u16Count;
            windata->u16FormatFlag |= SP_FLAG_LEFT_PRESSING;
            //PRINT("_MApp_ZUI_API_SpinKeyDown: left\n");
            break;
        case VK_RIGHT:
            if (windata->u16FormatFlag & SP_FLAG_HIDE_RBUTTON)
                return DEFAULTWINPROC(hwnd, pMsg);
            list->u16FocusIndex = (list->u16FocusIndex+1) % list->u16Count;
            windata->u16FormatFlag |= SP_FLAG_RIGHT_PRESSING;
            //PRINT("_MApp_ZUI_API_SpinKeyDown: right\n");
            break;
        case VK_UP:
        case VK_DOWN:
        default:
            //PRINT("_MApp_ZUI_API_SpinKeyDown: key is not left and right\n");
            return DEFAULTWINPROC(hwnd, pMsg);
    }

    //invoke event...
    //if (windata->OnSelectionChanged)
    //    windata->OnSelectionChanged(hwnd, list->u16FocusIndex);
    MApp_ZUI_ACT_ExecuteWndAction(hwnd);

    //PRINT("_MApp_ZUI_API_SpinKeyDown: success and set timer\n");
    MApp_ZUI_API_SetTimer(hwnd, 0, windata->u16PressingSleepTime);
    MApp_ZUI_API_InvalidateWindow(hwnd);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SpinWinProc
///  Window Proc for "Spin" control, which select one of a collection of item in the box
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_CTL_SpinWinProc(HWND hwnd, PMSG pMsg)
{
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    GUI_DATA_SPIN * windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);
    if (!windata)
    {
        //PRINT("MApp_ZUI_API_SpinWinProc(%x): data NULL\n", hwnd);
        ABORT();
        return DEFAULTWINPROC(hwnd, pMsg);
    }

    switch(pMsg->message)
    {
        case MSG_CREATE:
            //NOTE: don't support for static init data...
            //memset(&CTL_GETSPINLIST(hwnd), 0, sizeof(GUI_DATA_SPIN_INTERNAL));
            break;

        //case MSG_SETFOCUS:
        //    break;

        case MSG_KEYDOWN:
            //override default behavior...
            return _MApp_ZUI_CTL_SpinKeyDown(hwnd, pMsg);

        case MSG_TIMER:
            //PRINT("_MApp_ZUI_API_SpinWindowProc(): MSG_TIMER\n");
            //TODO: not writable!! windata->u16FormatFlag &= ~(SP_FLAG_LEFT_PRESSING|SP_FLAG_RIGHT_PRESSING);
            MApp_ZUI_API_InvalidateWindow(hwnd);
            MApp_ZUI_API_KillTimer(hwnd, 0);
            break;

        case MSG_DESTROY:
            MApp_ZUI_API_KillTimer(hwnd, 0);
            MApp_ZUI_CTL_SpinClearItems(hwnd);
            break;

        case MSG_PAINT:
            //draw default at the background...
            DEFAULTWINPROC(hwnd, pMsg);
            //should be visible: if ((win->dwState & WS_VISIBLE))
            {
                _MApp_ZUI_CTL_SpinPaint(hwnd, pMsg);
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, pMsg);

}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SpinSetSelectIndex
///  Spin control API: select a specific item
///
///  @param [in]       hwnd HWND     Spin control window handle
///  @param [in]       focus_idx U16     item index to select
///
///  @return BOOL TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_CTL_SpinSetSelectIndex(HWND hwnd, U16 focus_idx)
{
    GUI_DATA_SPIN * windata = NULL;
    GUI_DATA_SPIN_INTERNAL * list;

    if (hwnd != HWND_INVALID)
    {
        windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);
        if (windata != NULL)
        {
            list = &windata->pVardata->list;
            if (list->u16FocusIndex != focus_idx &&
                focus_idx < list->u16Count)
            {
                list->u16FocusIndex = focus_idx;

                //NOTE: need NOT to invoke OnSelectionChanged event..

                MApp_ZUI_API_InvalidateWindow(hwnd);
                return TRUE;
            }
            return TRUE;
        }
    }
    //PRINT("MApp_ZUI_API_SpinSetSelectIndex(%x): error\n", hwnd);
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SpinGetSelectIndex
///  Spin control API: query selection index for Spin control
///
///  @param [in]       hwnd HWND     Spin control handle
///
///  @return U16 selection index in the items
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_CTL_SpinGetSelectIndex(HWND hwnd)
{
    const GUI_DATA_SPIN * windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            GUI_DATA_SPIN_INTERNAL * list;
            list = &windata->pVardata->list;
            return list->u16FocusIndex;
        }
    }
    //PRINT("MApp_ZUI_API_SpinGetSelectIndex(%x): error\n", hwnd);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SpinSetItems
///  Spin control API: setup the data collection of spin controls
///
///  @param [in]       hwnd HWND     Spin control handle
///  @param [in]       pItems GUI_DATA_SPIN_ITEM*     data collection pointer
///  @param [in]       u16Count U16     number of data collection
///
///  @return BOOLEAN success or not
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

BOOLEAN MApp_ZUI_CTL_SpinSetItems(HWND hwnd, GUI_DATA_SPIN_ITEM * pItems, U16 u16Count)
{
    GUI_DATA_SPIN * windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);

    MApp_ZUI_CTL_SpinClearItems(hwnd);
    if (hwnd != HWND_INVALID && pItems && u16Count > 0)
    {
        if (windata)
        {
            GUI_DATA_SPIN_INTERNAL * list;
            list = &windata->pVardata->list;
            //list->pItems = MsOS_AllocateMemory(sizeof(GUI_DATA_SPIN_ITEM)*u16Count, gs32CachedPoolID);
            //memcpy(list->pItems, pItems, sizeof(GUI_DATA_SPIN_ITEM)*u16Count);
            list->pItems = pItems;
            list->u16Count = list->u16Size = u16Count;
            list->u16FocusIndex = 0;
            return TRUE;
        }
    }
    //PRINT("MApp_ZUI_API_SpinSetItems(%x): error\n", hwnd);
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SpinClearItems
///  Spin control API: clear the data collection of spin controls
///
///  @param [in]       hwnd HWND     Spin control handle
///
///  @return NONE
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_SpinClearItems(HWND hwnd)
{
    GUI_DATA_SPIN * windata = (GUI_DATA_SPIN*)GETWNDDATA(hwnd);

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            GUI_DATA_SPIN_INTERNAL * list;
            list = &windata->pVardata->list;
            if (list->pItems)
            {
                //MsOS_FreeMemory(list->pItems, gs32CachedPoolID);
                list->pItems = NULL;
            }
            //memset(&CTL_GETSPINLIST(hwnd), 0, sizeof(GUI_DATA_SPIN_INTERNAL));
            MApp_ZUI_API_InvalidateWindow(hwnd);
            return;
        }
    }
    //PRINT("MApp_ZUI_API_SpinClearItems(%x): error\n", hwnd);
    return;
}

