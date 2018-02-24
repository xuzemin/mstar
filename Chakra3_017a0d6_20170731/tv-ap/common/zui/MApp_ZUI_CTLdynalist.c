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

#define MAPP_ZUI_CTL_DYNALIST_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "datatype.h"
#include "debug.h"
#include "msAPI_OSD.h"
#include "msAPI_Memory.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTglobal.h"

/////////////////////////////////////////////////////
//NOTE: must be the same bank with table, because of GETWNDDATA()

typedef struct
{
    HWND hwnd;
    GUI_ENUM_DYNAMIC_LIST_STATE state;
} GUI_DATA_DYNAMIC_LIST_INTERNAL;

static U8 _MApp_ZUI_CTL_CountChildren(HWND hParent)
{
    U8 ret = 0;
    HWND child, last_succ; //2008/4/12: get last successor once
    last_succ = MApp_ZUI_API_GetLastSuccessor(hParent);
    for (child = hParent+1; child <= last_succ; child++)
    {
        if (MApp_ZUI_API_GetParent(child) == hParent)
            ret++;
    }
    return ret;
}

static U8 _MApp_ZUI_CTL_CountChildrenRegion(HWND hParent, HWND hFrom, HWND hTo)
{
    U8 ret = 0;
    HWND child;
    for (child = hFrom; child <= hTo; child++)
    {
        if (MApp_ZUI_API_GetParent(child) == hParent)
            ret++;
    }
    return ret;
}


static HWND _MApp_ZUI_CTL_DynamicListInitPage(HWND hList, HWND hTarget, BOOLEAN bForward)
{
    U8 total_children = 0, item_count = 0, visible_count = 0;
    HWND ret = HWND_INVALID;
    //HWND now = hTarget;
    U8 focus_item_index, page_start_index;
    GUI_DATA_DYNAMIC_LIST_INTERNAL * list;
    HWND * visible_list;
    GUI_DATA_DYNAMIC_LIST * windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(hList);
    //we can assume data is vaild here...

    total_children = _MApp_ZUI_CTL_CountChildren(hList);
    visible_count = _MApp_ZUI_CTL_CountChildrenRegion(hList, windata->hwndFirstItemOfPage, windata->hwndLastItemOfPage);
    //printf("[]total=%bu, visible=%bu\n", total_children, visible_count);
    if (total_children == 0 || visible_count == 0)
    {
        //illegal status, nothing to show? hide list self...
        MApp_ZUI_API_ShowWindow(hList, SW_HIDE);
        return HWND_INVALID;
    }

#if 1 //alignment patch to 4 byte alignment
    visible_list = (HWND*)_ZUI_MALLOC((U16)visible_count*sizeof(HWND)+4);

    list = (GUI_DATA_DYNAMIC_LIST_INTERNAL*)_ZUI_MALLOC(
        (U16)total_children*sizeof(GUI_DATA_DYNAMIC_LIST_INTERNAL)+4 );
    /*
    printf("[]size(HWND)=%u,size(internal)=%u\n", sizeof(HWND),
        sizeof(GUI_DATA_DYNAMIC_LIST_INTERNAL));
    printf("[]addr1=%X,addr2=%X\n", (U32)visible_list, (U32)list);
    */
    if (list == 0 || visible_list == 0)
    {
        __ASSERT(0);
        //not enough memory...
        MApp_ZUI_API_ShowWindow(hList, SW_HIDE);
        goto EXIT;
    }

    //address alignment patch..
    visible_list = (HWND*)((((U32)visible_list)+3)&(~3));
    list = (GUI_DATA_DYNAMIC_LIST_INTERNAL*)((((U32)list)+3)&(~3));

    //printf("[]addr1=%X,addr2=%X\n", (U32)visible_list, (U32)list);

#else  // alignment fail!! can't be 4 byte alignment
    visible_list = (HWND*)_ZUI_MALLOC((U16)visible_count*sizeof(HWND));

    list = (GUI_DATA_DYNAMIC_LIST_INTERNAL*)_ZUI_MALLOC(
        (U16)total_children*sizeof(GUI_DATA_DYNAMIC_LIST_INTERNAL) );

    if (list == 0 || visible_list == 0)
    {
        //not enough memory...
        MApp_ZUI_API_ShowWindow(hList, SW_HIDE);
        goto EXIT;
    }
#endif
    //rebuild visible list
    {
        U8 i = 0;
        HWND child;
        for (child = windata->hwndFirstItemOfPage; child <= windata->hwndLastItemOfPage; child++)
        {
            if (MApp_ZUI_API_GetParent(child) == hList)
            {
                visible_list[i] = child;
                //printf("vis[%bu]=%u\n", i, visible_list[i]);
                i++;
            }
        }
    }

    //reset list[n].state to EN_DL_STATE_HIDDEN
    //To avoid dipsaly redundant channel information when only one program in Channel List.(ATSC)
    {
        U8 i = 0;
        for (i = 0; i < total_children; i++)
        {
            list[i].state = EN_DL_STATE_HIDDEN;
            list[i].hwnd  = 0;
        }
    }


    //rebuild internal list
    // 1. query all children status, show/hide/disable/enable them
    {
        HWND child, last_succ; //2008/4/12: get last successor once
        last_succ = MApp_ZUI_API_GetLastSuccessor(hList);
        for (child = hList+1; child <= last_succ; child++)
        {
            if (MApp_ZUI_API_GetParent(child) != hList)
                continue;

            list[item_count].state = MApp_ZUI_ACT_QueryDynamicListItemStatus(child);
            if (list[item_count].state == EN_DL_STATE_HIDDEN)
                continue;

            list[item_count].hwnd = child;
            //printf("item[%bu]=%u,state=%bu\n", item_count, list[item_count].hwnd, list[item_count].state);
            item_count++;
        }
    }

    // 2. find real focus
    {
        S8 i, j;
        focus_item_index = 0xFF;
        if (bForward)
        {
            for (i = item_count; --i >= 0; )
            {
                //printf("[%bu]hwnd=%u,state=%bu\n", i, list[i].hwnd, list[i].state);
                if (list[i].hwnd < hTarget)
                    break;
            }
            i++;
            for (j = 0; j < item_count; j++)
            {
                if (list[(i+j)%item_count].state == EN_DL_STATE_NORMAL)
                {
                    focus_item_index = (i+j)%item_count;
                    break;
                }
            }
        }
        else
        {
            for (i = 0; i < item_count; i++)
            {
                if (list[i].hwnd > hTarget)
                    break;
            }
            i--;
            for (j = 0; j < item_count; j++)
            {
                if (list[(i+item_count*2-j)%item_count].state == EN_DL_STATE_NORMAL)
                {
                    focus_item_index = (i+item_count*2-j)%item_count;
                    break;
                }
            }
        }
        //printf("[]focus_idx=%bu\n", focus_item_index);
        if (focus_item_index == 0xFF)
        {
            ZUI_DBG_FAIL(printf("[ZUI]FNDLIST\n"));
            ABORT();
            focus_item_index = 0;
        }
    }

    // 3. find real page index
    page_start_index = visible_count*(focus_item_index/visible_count);
    //printf("[]page_start=%bu\n", page_start_index);
    windata->pVarData->hwndFirstShown= list[page_start_index].hwnd;
    windata->pVarData->u8CurrentState = 0; //reset status...
    if (page_start_index == 0)
        windata->pVarData->u8CurrentState |= DL_STATE_IS_FIRST_PAGE;

    // 4. init first page child positions
    {
        U8 i = 0;
        HWND child, last_succ;
        last_succ = MApp_ZUI_API_GetLastSuccessor(hList);
        for (child = hList+1; child <= last_succ; child++)
        {
            if (MApp_ZUI_API_GetParent(child) != hList)
                continue;

            //restore them first, avoiding movable window overflow
            MApp_ZUI_API_RestoreWindowRect(child);
            if (i >= item_count)
            {
            //end the list...
                MApp_ZUI_API_ShowWindow(child, SW_HIDE);
        }
            else if (list[i].hwnd != child) //hidden state: not in the array....
            {
                MApp_ZUI_API_ShowWindow(child, SW_HIDE);
            }
            else if (i < page_start_index || i >= page_start_index + visible_count)
            {
                //out of current page...
                MApp_ZUI_API_ShowWindow(child, SW_HIDE);
                i++;
            }
            else
            {
                //current page and normal state...
                MApp_ZUI_API_EnableWindow(child, (list[i].state == EN_DL_STATE_NORMAL));
                MApp_ZUI_API_ShowWindow(child, SW_SHOW);
                windata->pVarData->hwndLastShown = child;
                i++;
                if (i == item_count)
                    windata->pVarData->u8CurrentState |= DL_STATE_IS_LAST_PAGE;
            }

        }
        //move them here, avoiding movable window overflow
        for (i = page_start_index; i < item_count && i < page_start_index + visible_count; i++)
        {
            //current page and normal state...
            /*
            printf("[]hwnd=%u,(%d,%d)\n",
                list[i].hwnd,
                GETWNDINITRECT(visible_list[i-page_start_index]).left,
                GETWNDINITRECT(visible_list[i-page_start_index]).top);
            */
            RECT rect_hwnd;
            memset(&rect_hwnd,0,sizeof(RECT));
            MApp_ZUI_API_GetWindowInitialRect(visible_list[i-page_start_index], &rect_hwnd);
            MApp_ZUI_API_MoveAllSuccessors(
                list[i].hwnd,
                rect_hwnd.left,
                rect_hwnd.top);
        }
    }

    // note: don't set focus! avoiding conflict icon rotatation....
    //MApp_ZUI_API_SetFocus(list[focus_item_index].hwnd);
    ret = list[focus_item_index].hwnd;

EXIT:
    if (list)
        _ZUI_FREE(list);
    if (visible_list)
        _ZUI_FREE(visible_list);

    return ret;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicListWinProc
///  Window Proc for "dynamic list" control,
///     which dynamically change the list items by calling MApp_ZUI_ACT_QueryDynamicListItemStatus()
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

S32 MApp_ZUI_CTL_DynamicListWinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_DYNAMIC_LIST * windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(hWnd);

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return DEFAULTWINPROC(hWnd, pMsg);

    switch(pMsg->message)
    {
        case MSG_NOTIFY_SHOW:
            {
                // 1. query all children status, show/hide/disable/enable them
                // 2. init first page child positions
                // 3. set focus to first
                _MApp_ZUI_CTL_DynamicListInitPage(hWnd, windata->hwndFirstItemOfPage,
                    TRUE);

            }
            return 0;

        case MSG_NOTIFY_HIDE:
            {
                //restore all child movable window!!
                HWND child, last_succ; //2008/4/12: get last successor once
                last_succ = MApp_ZUI_API_GetLastSuccessor(hWnd);
                //printf("[]notify_hide\n");
                for (child = hWnd+1; child <= last_succ; child++)
                {
                    if (hWnd == MApp_ZUI_API_GetParent(child))
                    {
                        MApp_ZUI_API_RestoreWindowRect(child);
                    }
                }
                //note:
                if (!MApp_ZUI_API_IsWindowVisible(hWnd))
                {
                    MApp_ZUI_API_ShowWindow(hWnd, SW_HIDE);
                }
            }
            return 0;

        case MSG_NOTIFY_CONTENT_CHANGED:
            {
                HWND next = _MApp_ZUI_CTL_DynamicListInitPage(hWnd,
                    MApp_ZUI_API_GetFocus(),
                    TRUE);
                MApp_ZUI_API_SetFocus(next);
            }
            return 0;

        case MSG_USER: //for MApp_ZUI_CTL_DynamicListSetItemFocus
            {
                //printf("[]n_user=%u\n", hWnd);
                HWND next = pMsg->wParam;
                next = _MApp_ZUI_CTL_DynamicListInitPage(hWnd,
                    next,
                    TRUE);
                MApp_ZUI_API_SetFocus(next);
            }
            return 0;

        case (MSG_USER1/*MSG_USER+1*/): //for MApp_ZUI_CTL_DynamicListEnsureVisible
            {
                //printf("[]n_usr1=%u\n", hWnd);
                _MApp_ZUI_CTL_DynamicListInitPage(hWnd,
                    (HWND)pMsg->wParam,
                    TRUE);
            }
            return 0;

        case MSG_NOTIFY_KEYDOWN:
            {
                // accept up/down/left/right key
                // 1. check navigation of current focus (ignore if the next one is not my child)
                // 2. query next status, if status==hide or disable, then contunue check next one
                // 3. if need to change page, then init that page
                // 4. set focus to it
                U8 count;
                HWND now = MApp_ZUI_API_GetFocus();
                KEYWNDNAV nav;

                if (now == HWND_INVALID)
                    goto DEFAULT;

                if (pMsg->wParam == VK_UP)
                    nav = NAV_UP;
                else if (pMsg->wParam == VK_DOWN)
                    nav = NAV_DOWN;
                else if (pMsg->wParam == VK_LEFT)
                    nav = NAV_LEFT;
                else if (pMsg->wParam == VK_RIGHT)
                    nav = NAV_RIGHT;
                else
                    goto DEFAULT;

                for (count = 0; count < 100; count++)
                {
                    HWND next;
                    if (GETWNDNAVI(now) == 0)
                        goto DEFAULT;
                    next = GETWNDNAVI(now)[nav];
                    if (next == now || next == HWND_INVALID)
                        goto DEFAULT;
                    //printf("[]next=%u\n", (U16)next);
                    if (MApp_ZUI_API_GetParent(next) != hWnd)
                    {
                        //2007/12/20: for jump to non-parent case: just SetFocusByNav
                        MApp_ZUI_API_SetFocusByNav(now, nav);
                        goto DEFAULT;
                    }
                    if ((windata->pVarData->hwndFirstShown <= next && next <= windata->pVarData->hwndLastShown) &&
                        MApp_ZUI_API_IsWindowVisible(next) &&
                        MApp_ZUI_API_IsWindowEnabled(next))
                    {
                        //shown region: trivial case: focus it
                        MApp_ZUI_API_SetFocus(next);
                        //printf("[]focus=%u\n", next);
                        break;
                    }
                    else if (windata->pVarData->hwndFirstShown <= next && next <= windata->pVarData->hwndLastShown)
                    {
                        //shown region: but this item is not shown: keep moving
                        //printf("[]move=%u\n", next);
                        now = next;
                    }
                    else
                    {
                        //not shown region: reinit new page
                        //printf("[]reinit=%u\n", next);
                        next = _MApp_ZUI_CTL_DynamicListInitPage(hWnd,
                            next,
                            pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT);
                        MApp_ZUI_API_SetFocus(next);
                        break;
                    }

                }
                if (count == 100)
                {
                    ZUI_DBG_FAIL(printf("[ZUI]FNDLOOP\n"));
                    ABORT();
                }
            }
DEFAULT:
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hWnd, pMsg);
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicListRefreshContent
///  Dynamic List control: force refresh content visible/disable checking
///
///  @param [in]       hwnd HWND     window handle
///
///  @return    no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_DynamicListRefreshContent(HWND hwnd)
{
    MApp_ZUI_API_PostMessage(hwnd, MSG_NOTIFY_CONTENT_CHANGED, 0);
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicListSetItemFocus
///  Dynamic List control: force set focus to item of a list
///
///  @param [in]       hwnd HWND     list window handle
///  @param [in]       hwnd HWND     item window handle
///
///  @return    no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_DynamicListSetItemFocus(HWND hwnd, HWND hwndItem)
{
    //printf("MApp_ZUI_CTL_DynamicListSetItemFocus\n");
    //MApp_ZUI_API_PostMessage(hwnd, MSG_USER, hwndItem);
    // benjamin.chen 2009/11/23, 2009/12/03
    MApp_ZUI_API_SendMessage(hwnd, MSG_USER, hwndItem);
    MApp_ZUI_API_PostMessage(hwnd, MSG_USER, hwndItem);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicListEnsureVisible
///  Dynamic List control: ensure a specific item of a list is visible
///
///  @param [in]       hwnd HWND     list window handle
///  @param [in]       hwnd HWND     item window handle
///
///  @return    no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_DynamicListEnsureVisible(HWND hwnd, HWND hwndItem)
{
    MApp_ZUI_API_PostMessage(hwnd, MSG_USER1/*MSG_USER+1*/, hwndItem);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicList_GetFirstItem
///  Dynamic List control: get first item of current page
///
///  @param [in]       hwnd HWND     window handle
///
///  @return HWND of first HWND
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
HWND MApp_ZUI_CTL_DynamicList_GetFirstItem(HWND hwnd)
{
    GUI_DATA_DYNAMIC_LIST * windata;

    if (hwnd == HWND_INVALID)
        return HWND_INVALID;

    windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(hwnd);

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return HWND_INVALID;

    return windata->pVarData->hwndFirstShown;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicList_GetLastItem
///  Dynamic List control: get last item of current page
///
///  @param [in]       hwnd HWND     window handle
///
///  @return HWND of last item
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
HWND MApp_ZUI_CTL_DynamicList_GetLastItem(HWND hwnd)
{
    GUI_DATA_DYNAMIC_LIST * windata;

    if (hwnd == HWND_INVALID)
        return HWND_INVALID;

    windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(hwnd);

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return HWND_INVALID;

    return windata->pVarData->hwndLastShown;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicListIsFirstPage
///  Dynamic List control: determine if first page of a dynamic list
///
///  @param [in]       hwnd HWND     window handle
///
///  @return BOOLEAN    true for first page
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

BOOLEAN MApp_ZUI_CTL_DynamicListIsFirstPage(HWND hwnd)
{
    GUI_DATA_DYNAMIC_LIST * windata;

    if (hwnd == HWND_INVALID)
        return FALSE;

    windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(hwnd);

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return FALSE;

    return windata->pVarData->u8CurrentState&DL_STATE_IS_FIRST_PAGE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicListIsLastPage
///  Dynamic List control: determine if last page of a dynamic list
///
///  @param [in]       hwnd HWND     window handle
///
///  @return BOOLEAN    true for last page
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

BOOLEAN MApp_ZUI_CTL_DynamicListIsLastPage(HWND hwnd)
{
    GUI_DATA_DYNAMIC_LIST * windata;

    if (hwnd == HWND_INVALID)
        return FALSE;

    windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(hwnd);

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return FALSE;

    return windata->pVarData->u8CurrentState&DL_STATE_IS_LAST_PAGE;
}



#undef MAPP_ZUI_CTL_DYNALIST_C
