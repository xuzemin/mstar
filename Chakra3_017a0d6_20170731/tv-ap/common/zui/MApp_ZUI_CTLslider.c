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
#include "datatype.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTglobal.h"


///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_SliderPaint
///  paint function for "Slider" control
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     window message
///
///  This function doesn't return a value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_CTL_SliderPaint(HWND hwnd, PMSG pMsg)
{
    RECT ri, thumb;
    //GRAPHIC_DC * hdc = (GRAPHIC_DC*)pMsg->wParam;
    PAINT_PARAM * param = (PAINT_PARAM *)pMsg->wParam;
    GUI_DATA_SLIDER * windata = (GUI_DATA_SLIDER*)GETWNDDATA(hwnd);

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

    RECT_SET(ri,
        param->rect->left+windata->rcInnerBar.left,
        param->rect->top+windata->rcInnerBar.top,
        windata->rcInnerBar.width,
        windata->rcInnerBar.height);
    //if (ri.width < 0 || ri.height < 0)
    //    return; //illegal size

    _MApp_ZUI_API_DrawStyleList(&param->dc, &ri, windata->pInnerBar);

    if (CTL_GETSLIDERMINVALUE(hwnd) == CTL_GETSLIDERMAXVALUE(hwnd) ||
        CTL_GETSLIDERVALUE(hwnd) < CTL_GETSLIDERMINVALUE(hwnd) ||
        CTL_GETSLIDERVALUE(hwnd) > CTL_GETSLIDERMAXVALUE(hwnd))
        return; //illegal data value

    if (windata->u16FormatFlag & SL_FLAG_VERTICAL)
    {
        //vert slider
        ri.height = ri.height*(CTL_GETSLIDERVALUE(hwnd)-CTL_GETSLIDERMINVALUE(hwnd))/(CTL_GETSLIDERMAXVALUE(hwnd)-CTL_GETSLIDERMINVALUE(hwnd));
        _MApp_ZUI_API_DrawStyleList(&param->dc, &ri, windata->pActiveBar);

        RECT_SET(thumb,
            ri.left+(ri.width/2)-(windata->u16ThumbWidth/2),
            ri.top+ri.height-(windata->u16ThumbHeight/2),
            windata->u16ThumbWidth,
            windata->u16ThumbHeight);
        _MApp_ZUI_API_DrawStyleList(&param->dc, &thumb, windata->pThumb);
    }
    else
    {
        //hor slider
        ri.width = ri.width*(CTL_GETSLIDERVALUE(hwnd)-CTL_GETSLIDERMINVALUE(hwnd))/(CTL_GETSLIDERMAXVALUE(hwnd)-CTL_GETSLIDERMINVALUE(hwnd));
        _MApp_ZUI_API_DrawStyleList(&param->dc, &ri, windata->pActiveBar);

        RECT_SET(thumb,
            ri.left+ri.width-(windata->u16ThumbWidth/2),
            ri.top+(ri.height/2)-(windata->u16ThumbHeight/2),
            windata->u16ThumbWidth,
            windata->u16ThumbHeight);
        _MApp_ZUI_API_DrawStyleList(&param->dc, &thumb, windata->pThumb);
    }
}


///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_SliderKeyDown
///  key down handler for "Slider" control
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static S32 _MApp_ZUI_CTL_SliderKeyDown(HWND hwnd, PMSG pMsg)
{
    //U16 i;
    GUI_DATA_SLIDER * windata = (GUI_DATA_SLIDER*)GETWNDDATA(hwnd);

    //control focus only if visible, enabled and got focus...
    if (!MApp_ZUI_API_IsWindowEnabled(hwnd)||
        !MApp_ZUI_API_IsWindowVisible(hwnd)||
        MApp_ZUI_API_GetFocus() != hwnd)
    {
        //PRINT("_MApp_ZUI_API_SliderKeyDown: no focus\n");
        return DEFAULTWINPROC(hwnd, pMsg);
    }

    if (CTL_GETSLIDERMINVALUE(hwnd) == CTL_GETSLIDERMAXVALUE(hwnd) ||
        CTL_GETSLIDERVALUE(hwnd) < CTL_GETSLIDERMINVALUE(hwnd) ||
        CTL_GETSLIDERVALUE(hwnd) > CTL_GETSLIDERMAXVALUE(hwnd))
    {
        //printf("_MApp_ZUI_API_SliderKeyDown(): illegal value!");
        CTL_GETSLIDERVALUE(hwnd) = CTL_GETSLIDERMINVALUE(hwnd);
        //return -1; //illegal data value
    }

    switch(pMsg->wParam)
    {
        case VK_LEFT:
            if (windata->u16FormatFlag & SL_FLAG_VERTICAL)
                return DEFAULTWINPROC(hwnd, pMsg);
            CTL_GETSLIDERVALUE(hwnd) = MAX(CTL_GETSLIDERMINVALUE(hwnd), CTL_GETSLIDERVALUE(hwnd)-CTL_GETSLIDERDECVALUE(hwnd));
            break;
        case VK_RIGHT:
            if (windata->u16FormatFlag & SL_FLAG_VERTICAL)
                return DEFAULTWINPROC(hwnd, pMsg);
            CTL_GETSLIDERVALUE(hwnd) = MIN(CTL_GETSLIDERMAXVALUE(hwnd), CTL_GETSLIDERVALUE(hwnd)+CTL_GETSLIDERINCVALUE(hwnd));
            break;
        case VK_UP:
            if (!(windata->u16FormatFlag & SL_FLAG_VERTICAL))
                return DEFAULTWINPROC(hwnd, pMsg);
            CTL_GETSLIDERVALUE(hwnd) = MAX(CTL_GETSLIDERMINVALUE(hwnd), CTL_GETSLIDERVALUE(hwnd)-CTL_GETSLIDERDECVALUE(hwnd));
            break;
        case VK_DOWN:
            if (!(windata->u16FormatFlag & SL_FLAG_VERTICAL))
                return DEFAULTWINPROC(hwnd, pMsg);
            CTL_GETSLIDERVALUE(hwnd) = MIN(CTL_GETSLIDERMAXVALUE(hwnd), CTL_GETSLIDERVALUE(hwnd)+CTL_GETSLIDERINCVALUE(hwnd));
            break;
        default:
            //PRINT("_MApp_ZUI_API_SliderKeyDown: key is not left and right\n");
            return DEFAULTWINPROC(hwnd, pMsg);
    }

    //invoke event...
    //if (windata->OnSelectionChanged)
    //    windata->OnSelectionChanged(hwnd, CTL_GETSLIDERVALUE(hwnd));
    MApp_ZUI_ACT_ExecuteWndAction(hwnd);


    MApp_ZUI_API_InvalidateWindow(hwnd);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SliderWinProc
///  Window Proc for "Slider" control, which select one of a collection of item in the box
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_CTL_SliderWinProc(HWND hwnd, PMSG pMsg)
{
    GUI_DATA_SLIDER * windata = (GUI_DATA_SLIDER*)GETWNDDATA(hwnd);
    if (!windata)
    {
        //printf("MApp_ZUI_API_SliderWinProc(%x): data NULL\n", hwnd);
        ABORT();
        return DEFAULTWINPROC(hwnd, pMsg);
    }

    switch(pMsg->message)
    {
        //case MSG_CREATE:
        //  break;

        //case MSG_SETFOCUS:
        //  break;

        case MSG_KEYDOWN:
            //override default behavior...
            return _MApp_ZUI_CTL_SliderKeyDown(hwnd, pMsg);

        //case MSG_TIMER:
        //case MSG_DESTROY:
        //  break;

        case MSG_PAINT:
            //draw default at the background...
            DEFAULTWINPROC(hwnd, pMsg);
            //should be visible: if ((win->dwState & WS_VISIBLE))
            {
                _MApp_ZUI_CTL_SliderPaint(hwnd, pMsg);
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, pMsg);

}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SliderSetValue
///  Window "Slider" control API: set a value for current selection
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       value U16     selection value
///
///  @return BOOLEAN success or not
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

BOOLEAN MApp_ZUI_CTL_SliderSetValue(HWND hwnd, U16 value)
{
    GUI_DATA_SLIDER * windata = (GUI_DATA_SLIDER*)GETWNDDATA(hwnd);

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            if (value >= CTL_GETSLIDERMINVALUE(hwnd) &&
                value <= CTL_GETSLIDERMAXVALUE(hwnd))
            {
                CTL_GETSLIDERVALUE(hwnd) = value;

                //NOTE: need NOT to invoke OnSelectionChanged event..

                MApp_ZUI_API_InvalidateWindow(hwnd);
                return TRUE;
            }
            return TRUE;
        }
    }
    //PRINT("MApp_ZUI_API_SliderSetValue(%x): error\n", hwnd);
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_SliderGetValue
///  Window "Slider" control API: get a value for current selection
///
///  @param [in]       hwnd HWND     window handle
///
///  @return U16 current selection value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

U16 MApp_ZUI_CTL_SliderGetValue(HWND hwnd)
{
    const GUI_DATA_SLIDER * windata = (GUI_DATA_SLIDER*)GETWNDDATA(hwnd);

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            return CTL_GETSLIDERVALUE(hwnd);
        }
    }
    //PRINT("MApp_ZUI_API_SliderGetValue(%x): error\n", hwnd);
    return 0;
}


