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
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTglobal.h"

//extern bool MApp_ZUI_API_DoesIntersect (const RECT* psrc1, const RECT* psrc2);
//extern S32 _MApp_ZUI_API_ExecuteAction(ACTION_ENUM act, void * act_param);
//static HWND hwnd;
//static PMSG pMsg;
//static GUI_DATA_LIST_BOX * windata;

///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_ListBoxPaint
///  paint function for "List Box" control
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     window message
///
///  This function doesn't return a value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_CTL_ListBoxPaint(HWND hwnd, PMSG pMsg)
{
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    //GRAPHIC_DC * hdc;
    PAINT_PARAM * param = (PAINT_PARAM *)pMsg->wParam;
    //ASSUME: row-major....
    U16 x, y, idx;
    RECT itemout, itemin;
    //TCHAR str[64]; //ASSUME: no more than 64 string length
    //DRAW_BITMAP param;
    RECT rb;
    //GUI_DATA_LIST_BOX_STRINFO strInfo;
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

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

    //hdc = (GRAPHIC_DC*)pMsg->wParam;
    rb = *param->rect;
    RECT_SCALE(rb, windata->u16ItemBorderWidth, windata->u16ItemBorderHeight);
    if (rb.width > 0 && rb.height > 0 &&
        list->u16Count > 0)
    {
        //draw items (normal and focus)
        itemout.width = (param->rect->width - (windata->u16ThumbColumnCount - 1)*windata->u16ItemGapX - 2*windata->u16ListBorderWidth) / windata->u16ThumbColumnCount;
        itemout.height = (param->rect->height - (windata->u16ThumbRowCount - 1)*windata->u16ItemGapY - 2*windata->u16ListBorderHeight) / windata->u16ThumbRowCount;
        itemin.width = itemout.width - 2*windata->u16ItemBorderWidth;
        itemin.height = itemout.height - 2*windata->u16ItemBorderHeight;

        if (itemin.width > 0 && itemin.height > 0)
        {
            itemout.top = param->rect->top + windata->u16ListBorderHeight;
            for (y = 0; y < windata->u16ThumbRowCount; y++)
            {
                itemout.left = param->rect->left + windata->u16ListBorderWidth;
                for (x = 0; x < windata->u16ThumbColumnCount; x++)
                {
                    idx = list->u16StartItem + y*windata->u16ThumbColumnCount + x;
                    if ( idx >= list->u16EndItem )
                        break;


                    itemin.left = itemout.left + windata->u16ItemBorderWidth;
                    itemin.top = itemout.top + windata->u16ItemBorderHeight;
                    if ( idx == list->u16FocusIndex &&
                        (windata->enFocusType == LB_FOCUS_ALWAYS_SHOW ||
                         (windata->enFocusType == LB_FOCUS_AUTO && param->bIsFocus) ) )
                    {
                        //focus...selected
                        _MApp_ZUI_API_DrawStyleList(&param->dc, &itemout, windata->DrawItemBGFocus);
                        if (list->pItems)
                            _MApp_ZUI_API_DrawStyleList(&param->dc, &itemin, list->pItems[idx].pDrawItemFocus);
                    }
                    else
                    {
                        //unfocus..unselected
                        _MApp_ZUI_API_DrawStyleList(&param->dc, &itemout, windata->DrawItemBGNormal);
                        if (list->pItems)
                            _MApp_ZUI_API_DrawStyleList(&param->dc, &itemin, list->pItems[idx].pDrawItemNormal);
                    }

#if 0 //TODO: how to support function pointer callback??
                    //callback items
                    if ( CTL_GETLISTBOXSTRCALLBACK(hwnd) )
                    {
                        if ( CTL_GETLISTBOXSTRCALLBACK(hwnd)(idx, &strInfo) )
                        {
                            /*
                            MApi_Osd_BoxTextOut(hdc->pGC,
                                            style.eSystemFont,
                                            &itemin,
                                            str,
                                            UI_MENU_DRAW_COLOR_FMT,
                                            style.TextColor,
                                            style.eTextAttrib,
                                            style.flag,
                                            style.u8dis,
                                            style.bShadow);
                            */
                            TextOut_Dynamic_List[0].eSystemFont = strInfo.text_style->eSystemFont;
                            TextOut_Dynamic_List[0].TextColor = strInfo.text_style->TextColor;
                            TextOut_Dynamic_List[0].eTextAttrib = strInfo.text_style->eTextAttrib;
                            TextOut_Dynamic_List[0].flag = strInfo.text_style->flag;
                            TextOut_Dynamic_List[0].u8dis = strInfo.text_style->u8dis;
                            TextOut_Dynamic_List[0].bShadow = strInfo.text_style->bShadow;
                            TextOut_Dynamic_List[0].pString = strInfo.string;
                            _MApp_ZUI_API_DrawComponent(hdc, &itemin, CP_TEXT_OUT_DYNAMIC, 0);
                        }
                    }
                    else if ( CTL_GETLISTBOXBMPCALLBACK(hwnd) )
                    {
                        if ( CTL_GETLISTBOXBMPCALLBACK(hwnd)(idx, &param) )
                        {
                            /*
                            OSD_ALPHA_BLENDING alpha =
                            {
                                TRUE, COEF_CONST, ABL_FROM_CONST, param.u8Constant_Alpha
                            };
                            BMPHANDLE bmp = MApi_Osd_LoadBitmap(
                                param.bmpAddress, param.bmpTotalBytes,
                                param.bmpWidth, param.bmpHeight,
                                param.bmpColorFmt);
                            MApi_Osd_DrawBitmap(hdc->pGC,
                                            bmp,
                                            &itemin,
                                            param.bSrcColorKey,
                                            param.srcColorKeyFrom,
                                            param.srcColorKeyEnd,
                                            &alpha);
                            MDrv_GE_PE_FreeBitmap(bmp); //note: no free bitmap function
                            */
                            //_MApp_ZUI_API_DrawComponent(hdc, &itemin, CP_BITMAP, &param);

                        }
                    }
#endif

                    itemout.left += itemout.width + windata->u16ItemGapX;
                }
                itemout.top += itemout.height + windata->u16ItemGapY;
            }
        }
    }

}


///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_ListBoxKeyDown
///  key down handler for "List Box" control
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static S32 _MApp_ZUI_CTL_ListBoxKeyDown(HWND hwnd, PMSG pMsg)
{
    //U16 i;
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    MSG msg;
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

    if ( !list->u16Count )
    {
        //PRINT("_MApp_ZUI_CTL_ListBoxKeyDown: empty content\n");
        return DEFAULTWINPROC(hwnd, pMsg); //empty content
    }
    if ( !windata->u16ThumbColumnCount || !windata->u16ThumbRowCount)
    {
        //PRINT("_MApp_ZUI_CTL_ListBoxKeyDown: grid is zero\n");
        return DEFAULTWINPROC(hwnd, pMsg); //empty content
    }

    //control focus only if "focus auto" or "focus show"
    if (windata->enFocusType == LB_FOCUS_ALWAYS_HIDE)
        return DEFAULTWINPROC(hwnd, pMsg);

    /*/control focus only if visible, enabled and got focus...
    if (GETWNDSTATE(hwnd)&WS_DISABLED ||
        (GETWNDSTATE(hwnd)&WS_VISIBLE) == 0 ||
        MApp_Menu_WndGetFocus() != hwnd)
        return DEFAULTWINPROC(hwnd, pMsg);*/

    //ASSUME: row-major...
    if (list->u16FocusIndex >= list->u16EndItem ||
        list->u16FocusIndex < list->u16StartItem )
    {
        list->u16StartItem = list->u16FocusIndex - list->u16FocusIndex%windata->u16ThumbColumnCount;
        list->u16EndItem = list->u16StartItem+windata->u16ThumbColumnCount*windata->u16ThumbRowCount;
        if (list->u16EndItem > list->u16Count)
            list->u16EndItem = list->u16Count;
    }
    switch(pMsg->wParam)
    {
        case VK_LEFT:
                if ((list->u16FocusIndex%windata->u16ThumbColumnCount) == 0)
            {
                return DEFAULTWINPROC(hwnd, pMsg);
            }
            list->u16FocusIndex--;
            break;
        case VK_RIGHT:
            if (windata->u16ThumbFormatFlag & LB_FLAG_RIGHT_AS_SELECT)
            {
                msg.hwnd = hwnd;
                msg.message = MSG_KEYDOWN;
                msg.wParam = (WPARAM)VK_SELECT;
                return DEFAULTWINPROC(hwnd, &msg);
            }
            if ((list->u16FocusIndex%windata->u16ThumbColumnCount) == windata->u16ThumbColumnCount-1 ||
                list->u16FocusIndex == list->u16Count-1)
            {
                return DEFAULTWINPROC(hwnd, pMsg);
            }
            list->u16FocusIndex++;
            break;
        case VK_UP:
            if (list->u16FocusIndex < windata->u16ThumbColumnCount)
            {
                return DEFAULTWINPROC(hwnd, pMsg);
            }
            list->u16FocusIndex -= windata->u16ThumbColumnCount;
            if (list->u16FocusIndex < list->u16StartItem) //need to scroll
            {
                if (windata->u16ThumbFormatFlag & LB_FLAG_SCROLL_PAGE)
                {
                    list->u16EndItem = list->u16StartItem;
                }
                else
                {
                    list->u16EndItem -= windata->u16ThumbColumnCount;
                }
                if (list->u16EndItem < windata->u16ThumbColumnCount*windata->u16ThumbRowCount)
                {
                    list->u16StartItem = 0;
                }
                else
                {
                    list->u16StartItem = list->u16EndItem - windata->u16ThumbColumnCount*windata->u16ThumbRowCount;
                }
            }

            break;
        case VK_DOWN:
            if (windata->u16ThumbFormatFlag & LB_FLAG_DOWN_AS_SELECT)
            {
                msg.hwnd = hwnd;
                msg.message = MSG_KEYDOWN;
                msg.wParam = (WPARAM)VK_SELECT;
                return DEFAULTWINPROC(hwnd, &msg);
            }
            if (list->u16FocusIndex+windata->u16ThumbColumnCount >= list->u16Count)
            {
                return DEFAULTWINPROC(hwnd, pMsg);
            }
            list->u16FocusIndex += windata->u16ThumbColumnCount;
            if (list->u16FocusIndex >= list->u16EndItem) //need to scroll
            {
                if (windata->u16ThumbFormatFlag & LB_FLAG_SCROLL_PAGE)
                {
                    list->u16StartItem = list->u16EndItem;
                }
                else
                {
                    list->u16StartItem += windata->u16ThumbColumnCount;
                }
                list->u16EndItem = list->u16StartItem+windata->u16ThumbColumnCount*windata->u16ThumbRowCount;
                if (list->u16EndItem > list->u16Count)
                    list->u16EndItem = list->u16Count;
            }
            break;

        default:
            return DEFAULTWINPROC(hwnd, pMsg);
    }

    //note: maybe use action to modify scrollbar/pageposc control...
    //if (windata->hWndScrollBar != HWND_INVALID)
    //{
    //    MApp_Menu_WndSetRangeData(windata->hWndScrollBar, list->u16Count, list->u16StartItem, list->u16EndItem);
    //}

    //invoke event...
    //if (windata->OnSelectionChanged)
    //{
        //MApp_Menu_WndPostMessage(hwnd, MSG_NOTIFY, MAKEWPARAM(MN_LISTSELCHNG, list->u16FocusIndex));
    //    windata->OnSelectionChanged(hwnd, list->u16FocusIndex);
    //}
    MApp_ZUI_ACT_ExecuteWndAction(hwnd);

    MApp_ZUI_API_InvalidateWindow(hwnd);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_ListBoxWinProc
///  Window Proc for "ListBox" control, which select one of a collection of item in the grid
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_CTL_ListBoxWinProc(HWND hwnd, PMSG pMsg)
{
    //hwnd = hwndList;
    //pMsg = pmessage;
    //windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);

    if (!windata)
    {
        //PRINT("MApp_ZUI_CTL_ListBoxWinProc(%x): data NULL\n", hwnd);
        ABORT();
        return DEFAULTWINPROC(hwnd, pMsg);
    }

    switch(pMsg->message)
    {
        //case MSG_CREATE:
            //NOTE: don't support for static init data...
            //PRINT("MApp_ZUI_CTL_ListBoxWinProc(%x): create!!\n", hwnd);
            //memset(&windata->list, 0, sizeof(GUI_DATA_LIST_BOX_INTERNAL));
        //  break;

        case MSG_DESTROY:
            MApp_ZUI_CTL_ListBoxClearItems(hwnd);
            break;

        case MSG_KEYDOWN:
            //override default behavior...
            return _MApp_ZUI_CTL_ListBoxKeyDown(hwnd, pMsg);


        case MSG_PAINT:
            //draw default at the background...
            DEFAULTWINPROC(hwnd, pMsg);
            //should be visible: if ((win->dwState & WS_VISIBLE))
            {
                _MApp_ZUI_CTL_ListBoxPaint(hwnd, pMsg);
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, pMsg);

}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_ListBoxSetSelectIndex
///  ListBox control API: select a specific item from the collection
///
///  @param [in]       hwnd HWND     List Box window handle
///  @param [in]       focus_idx U16     item index to select
///
///  @return BOOL TRUE for success, FALSE for fail
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_CTL_ListBoxSetSelectIndex(HWND hwnd, U16 focus_idx)
{
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            if (list->u16FocusIndex != focus_idx &&
                focus_idx < list->u16Count)
            {
                list->u16FocusIndex = focus_idx;

                //ensure visible...
                if (list->u16FocusIndex >= list->u16EndItem ||
                    list->u16FocusIndex < list->u16StartItem )
                {
                    list->u16StartItem = list->u16FocusIndex - list->u16FocusIndex%windata->u16ThumbColumnCount;
                    list->u16EndItem = list->u16StartItem+windata->u16ThumbColumnCount*windata->u16ThumbRowCount;
                    if (list->u16EndItem > list->u16Count)
                        list->u16EndItem = list->u16Count;

                    //note: maybe use action to modify scrollbar/pageposc control...
                    //if (windata->hWndScrollBar != HWND_INVALID)
                    //{
                    //    MApp_Menu_WndSetRangeData(windata->hWndScrollBar, list->u16Count, list->u16StartItem, list->u16EndItem);
                    //}
                    MApp_ZUI_ACT_ExecuteWndAction(hwnd);

                }
                MApp_ZUI_API_InvalidateWindow(hwnd);
                return TRUE;
            }
            return TRUE;
        }
    }
    //PRINT("MApp_ZUI_CTL_ListBoxSetSelectIndex(%x): error\n", hwnd);
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_ListBoxGetSelectIndex
///  List Box API: query selection index for ListBox control
///
///  @param [in]       hwnd HWND     List Box control handle
///
///  @return U16 selection index in the items
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
U16 MApp_ZUI_CTL_ListBoxGetSelectIndex(HWND hwnd)
{
    if (hwnd != HWND_INVALID)
    {
        GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
        GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

        if (windata)
        {
            return list->u16FocusIndex;
        }
    }
    //PRINT("MApp_ZUI_CTL_ListBoxGetSelectIndex(%x): error\n", hwnd);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_ListBoxSetItems
///  List Box API: set up the collection of list box control
///
///  @param [in]       hwnd HWND     List Box control handle
///  @param [in]       pItems GUI_DATA_LIST_BOX_ITEM*     collection pointer
///  @param [in]       u16Count U16     number of collection
///
///  @return BOOLEAN success or not
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

BOOLEAN MApp_ZUI_CTL_ListBoxSetItems(HWND hwnd, GUI_DATA_LIST_BOX_ITEM * pItems, U16 u16Count)
{
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

    MApp_ZUI_CTL_ListBoxClearItems(hwnd);
    if (hwnd != HWND_INVALID && pItems && u16Count > 0)
    {
        if (windata)
        {
            //struct mallinfo info = mallinfo();
            //PRINT("mallinfo:%d,%d START\n", info.usmblks, info.fsmblks);
            //list->pItems = MsOS_AllocateMemory(sizeof(GUI_DATA_LIST_BOX_ITEM)*u16Count, gs32CachedPoolID);
            //info = mallinfo();
            //PRINT("mallinfo:%d,%d END\n", info.usmblks, info.fsmblks);
            //if (!data->list.pItems)
            //{
            //    PRINT("MApp_ZUI_CTL_ListBox: ALLOC fail\n");
            //    ABORT();
            //    return FALSE;
            //}
            //memcpy(data->list.pItems, pItems, sizeof(GUI_DATA_LIST_BOX_ITEM)*u16Count);
            list->pItems = pItems;
            list->u16Count = list->u16Size = u16Count;
            list->u16FocusIndex = list->u16StartItem = 0;
            list->u16EndItem = windata->u16ThumbRowCount*windata->u16ThumbColumnCount;

            if (list->u16EndItem > u16Count)
                list->u16EndItem = u16Count;

            //note: maybe use action to modify scrollbar/pageposc control...
            //if (windata->hWndScrollBar != HWND_INVALID)
            //{
            //    MApp_Menu_WndSetRangeData(windata->hWndScrollBar, list->u16Count, list->u16StartItem, list->u16EndItem);
            //}
            MApp_ZUI_ACT_ExecuteWndAction(hwnd);

            MApp_ZUI_API_InvalidateWindow(hwnd);
            return TRUE;
        }
    }
    //PRINT("MApp_ZUI_CTL_ListBoxSetItems(%x): error\n", hwnd);
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_ListBoxClearItems
///  List Box API: clear up the collection of list box control
///
///  @param [in]       hwnd HWND     List Box control handle
///
///  @return no result value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_ListBoxClearItems(HWND hwnd)
{
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            if (list->pItems)
            {
                //struct mallinfo info = mallinfo();
                //PRINT("mallinfo:%d,%d START_FREE\n", info.usmblks, info.fsmblks);
                //MsOS_FreeMemory(data->list.pItems, gs32CachedPoolID);
                list->pItems = NULL;
                //info = mallinfo();
                //PRINT("mallinfo:%d,%d END_FREE\n", info.usmblks, info.fsmblks);
            }
            //memset(&data->list, 0, sizeof(GUI_DATA_LIST_BOX_INTERNAL));

            //note: maybe use action to modify scrollbar/pageposc control...
            //if (windata->hWndScrollBar != HWND_INVALID)
            //{
            //    MApp_Menu_WndSetRangeData(windata->hWndScrollBar, 0, 0, 0);
            //}
            MApp_ZUI_ACT_ExecuteWndAction(hwnd);


            MApp_ZUI_API_InvalidateWindow(hwnd);
            return;
        }
    }
    //PRINT("MApp_ZUI_CTL_ListBoxClearItems(%x): error\n", hwnd);
    return;
}

#if 0
BOOLEAN MApp_ZUI_CTL_ListBoxSetItemsCallback(HWND hwnd, fpIndexString fp_str, fpIndexBitmap fp_bmp, U16 u16Count)
{
    GUI_DATA_LIST_BOX * windata = (GUI_DATA_LIST_BOX*)GETWNDDATA(hwnd);
    GUI_DATA_LIST_BOX_INTERNAL * list = &windata->pVardata->list;

    if (hwnd != HWND_INVALID)
    {
        if (windata)
        {
            CTL_GETLISTBOXBMPCALLBACK(hwnd) = fp_bmp;
            CTL_GETLISTBOXSTRCALLBACK(hwnd) = fp_str;
            list->pItems = NULL;
            list->u16Count = list->u16Size = u16Count;
            list->u16FocusIndex = list->u16StartItem = 0;
            list->u16EndItem = windata->u16ThumbRowCount*windata->u16ThumbColumnCount;
            if (list->u16EndItem > u16Count)
                list->u16EndItem = u16Count;
            return TRUE;
        }
    }
    //PRINT("MApp_ZUI_CTL_ListBoxSetItems(%x): error\n", hwnd);
    return FALSE;
}
#endif

