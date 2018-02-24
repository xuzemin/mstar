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

#define MAPP_ZUI_CTL_MOTIONTRANS_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "datatype.h"
#include "msAPI_OSD.h"
#include "msAPI_Memory.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
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

#define DIR_NONE    0
#define DIR_LEFT    1
#define DIR_RIGHT   2

typedef struct
{
    HWND hwnd;
    GUI_ENUM_DYNAMIC_LIST_STATE state;
} GUI_DATA_DYNAMIC_LIST_INTERNAL;

#if 0
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
            if (list[i].hwnd != child) //hidden state: not in the array....
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
#endif

void _MApp_ZUI_CTL_MotionTrans_DrawHWND(GRAPHIC_DC *pDC, HWND hWnd, U16 x, U16 y, float scale, float alpha)
{
    RECT rect;
    MApp_ZUI_API_GetWindowRect(hWnd, &rect);
    rect.left = x;
    rect.top = y;
    rect.width = rect.width * scale;
    rect.height = rect.height * scale;
    pDC->u8ConstantAlpha = 0xFF * alpha;
    _MApp_ZUI_API_DrawStyleList(pDC, &rect, GETNORMALDRAWSTYLE(hWnd));

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

S32 MApp_ZUI_CTL_MotionTrans_Icon_WinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_PAINT:
            return 0;
        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

S32 MApp_ZUI_CTL_MotionTransWinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_MOTION_TRANS * windata = (GUI_DATA_MOTION_TRANS*)GETWNDDATA(hWnd);

  #if 0
    GUI_DATA_MOTION_TRANS_VARDATA * pVar = windata->pVarData;

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return DEFAULTWINPROC(hWnd, pMsg);
#else
     // Add it by coverity_0492
    GUI_DATA_MOTION_TRANS_VARDATA * pVar = NULL;
    if (windata != NULL)
    {
        pVar = windata->pVarData;
    }

    //no dynamic list setting data...
    if (pVar == NULL)
    {
        return DEFAULTWINPROC(hWnd, pMsg);
    }
#endif

    switch(pMsg->message)
    {
        case MSG_NOTIFY_SHOW:
            {
//printf("MSG_NOTIFY_SHOW\n");
#if 0
                // 1. query all children status, show/hide/disable/enable them
                // 2. init first page child positions
                // 3. set focus to first
                _MApp_ZUI_CTL_DynamicListInitPage(hWnd, windata->hwndFirstItemOfPage,
                    TRUE);
#endif

                U16 width=0, height=0;

                pVar->step = 0;
                pVar->idx = 0;
                pVar->u8IconWidth = 128;
                pVar->u16IconX[0] = windata->margin;
                pVar->u16IconX[1] = pVar->u16IconX[0] + pVar->u8IconWidth * windata->icon_scale[0] + windata->icon_interval;
                pVar->u16IconX[2] = pVar->u16IconX[1] + pVar->u8IconWidth * windata->icon_scale[1] + windata->icon_interval;
                pVar->u16IconX[3] = pVar->u16IconX[2] + pVar->u8IconWidth * windata->icon_scale[2] + windata->icon_interval;
                pVar->u16IconX[4] = pVar->u16IconX[3] + pVar->u8IconWidth * windata->icon_scale[3] + windata->icon_interval;
                pVar->u16IconX[5] = pVar->u16IconX[4] + pVar->u8IconWidth * windata->icon_scale[4] + windata->icon_interval;
                pVar->u16IconX[6] = pVar->u16IconX[5] + pVar->u8IconWidth * windata->icon_scale[5] + windata->icon_interval;
                pVar->u16IconX[7] = pVar->u16IconX[6] + pVar->u8IconWidth * windata->icon_scale[6] + windata->icon_interval;

                pVar->u16CenterLeft = pVar->u16IconX[1];
                pVar->u16CenterWidth = pVar->u16IconX[6] - windata->icon_interval - pVar->u16IconX[1];
                width = pVar->u16IconX[7] - windata->icon_interval + windata->margin;
                height = 300;

                RECT rect;
                rect.left = windata->x;
                rect.top = windata->y;
                rect.width = width;
                rect.height = height;
                MApp_ZUI_API_MoveWindow(hWnd, &rect);

#if 0
                windata->shift1 = 90 / windata->pVarData->step;
                windata->shift2 = 140 / windata->pVarData->step;
                windata->pVarData->idx = 0;

                rect.left = 0;
                rect.top = 0;
                rect.width = 128*0.6;
                rect.height = 128*0.6;
                MApp_ZUI_API_MoveWindow(hWnd+1, &rect);

                left = 128*0.6 + 12;
                rect.left = left;
                rect.width = 128*0.8;
                rect.height = 128*0.8;
                MApp_ZUI_API_MoveWindow(hWnd+2, &rect);

                left += 128*0.8 + 12;
                rect.left = left;
                rect.width = 128;
                rect.height = 128;
                MApp_ZUI_API_MoveWindow(hWnd+3, &rect);

                left += 128 + 12;
                rect.left = left;
                rect.width = 128*0.8;
                rect.height = 128*0.8;
                MApp_ZUI_API_MoveWindow(hWnd+4, &rect);

                left += 128*0.8 + 12;
                rect.left = left;
                rect.width = 128*0.6;
                rect.height = 128*0.6;
                MApp_ZUI_API_MoveWindow(hWnd+5, &rect);
#endif
            }
            return 0;

        case MSG_NOTIFY_HIDE:
            {
//printf("MSG_NOTIFY_HIDE\n");
#if 0
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
#endif
            }
            return 0;

        case MSG_NOTIFY_CONTENT_CHANGED:
            {
//printf("MSG_NOTIFY_CONTENT_CHANGED\n");
#if 0
                HWND next = _MApp_ZUI_CTL_DynamicListInitPage(hWnd,
                    MApp_ZUI_API_GetFocus(),
                    TRUE);
                MApp_ZUI_API_SetFocus(next);
#endif
            }
            return 0;

        case MSG_NOTIFY_KEYDOWN:
            {
//printf("MSG_NOTIFY_KEYDOWN\n");
                MApp_ZUI_API_SetTimer(hWnd, 0, 50);

                if ( pMsg->wParam == VK_LEFT )
                {
                    windata->pVarData->dir = DIR_LEFT;
                }
                else if ( pMsg->wParam == VK_RIGHT )
                {
                    windata->pVarData->dir = DIR_RIGHT;
                }
                else
                {
                    return 0;
                }
#if 0
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
#endif
            }
            break; // Added it by coverity_349

        case MSG_TIMER:
            {
//printf("MSG_TIMER\n");
                pVar->step++;
                if ( pVar->step >= windata->steps )
                {
                    pVar->step = 0;
                    if ( pVar->dir == DIR_LEFT )
                    {
                        pVar->idx = (pVar->idx+6+1) % 6;
                    }
                    else if ( pVar->dir == DIR_RIGHT )
                    {
                        pVar->idx = (pVar->idx+6-1) % 6;
                    }
                    pVar->dir = DIR_NONE;

                    MApp_ZUI_API_KillTimer(hWnd, 0);
                }
                MApp_ZUI_API_InvalidateWindow(hWnd);
            }
            break;

        case MSG_PAINT:
            {
//printf("MSG_PAINT: step=%d\n", windata->pVarData->step);
                RECT rect;
                GRAPHIC_DC *pBufferDC = NULL;
                U8 i;

                pBufferDC = MApp_ZUI_API_GetBufferDC();
                rect.left = 0;
                rect.top = 0;
                MApp_ZUI_API_GetWindowRect(hWnd, &rect);
                GRAPHIC_DC dc = MApp_ZUI_API_CreateDC(rect.width, rect.height);

                #if 0
                clrBtn1.x = 0;
                clrBtn1.y = 0;
                clrBtn1.width = rect.width;
                clrBtn1.height = rect.height;
                clrBtn1.b_clr = 0xFF0000;
                clrBtn1.u8Gradient = CONSTANT_COLOR;
                clrBtn1.fHighLight = FALSE;
                msAPI_OSD_DrawBlock(&clrBtn1);
                #endif

                S16 m[10] = {0};
                U8 idx[10] = {0};
                float scale[10];
                float alpha[10];
                U8 offset_y[10];
                if ( pVar->dir == DIR_LEFT )
                {
                    for (i=0; i<6; i++)
                    {
                        m[i] = (pVar->u16IconX[i+1] - pVar->u16IconX[i] ) * pVar->step / windata->steps;
                        scale[i] = windata->icon_scale[i] + (windata->icon_scale[i+1] - windata->icon_scale[i]) * pVar->step / windata->steps;
                        alpha[i] = windata->icon_alpha[i] + (windata->icon_alpha[i+1] - windata->icon_alpha[i]) * pVar->step / windata->steps;
                        offset_y[i] = windata->icon_offset_y[i] + (windata->icon_offset_y[i+1] - windata->icon_offset_y[i]) * pVar->step / windata->steps;
                    }
                    m[i] = (pVar->u16IconX[i] - pVar->u16IconX[i] ) * pVar->step / windata->steps;
                    scale[i] = windata->icon_scale[i] + (windata->icon_scale[i] - windata->icon_scale[i] ) * pVar->step / windata->steps;
                    alpha[i] = windata->icon_alpha[i] + (windata->icon_alpha[i] - windata->icon_alpha[i] ) * pVar->step / windata->steps;
                    offset_y[i] = windata->icon_offset_y[i] + (windata->icon_offset_y[i+1] - windata->icon_offset_y[i]) * pVar->step / windata->steps;
                }
                else if ( pVar->dir == DIR_RIGHT )
                {
                    m[0] = (pVar->u16IconX[0] - pVar->u16IconX[0] ) * pVar->step / windata->steps;
                    scale[0] = windata->icon_scale[0] + (windata->icon_scale[0] - windata->icon_scale[0] ) * pVar->step / windata->steps;
                    alpha[0] = windata->icon_alpha[0] + (windata->icon_alpha[0] - windata->icon_alpha[0] ) * pVar->step / windata->steps;
                    offset_y[0] = windata->icon_offset_y[0] + (windata->icon_offset_y[0] - windata->icon_offset_y[0]) * pVar->step / windata->steps;
                    for (i=1; i<=6; i++)
                    {
                        m[i] = (pVar->u16IconX[i-1] - pVar->u16IconX[i] ) * pVar->step / windata->steps;
                        scale[i] = windata->icon_scale[i] + (windata->icon_scale[i-1] - windata->icon_scale[i] ) * pVar->step / windata->steps;
                        alpha[i] = windata->icon_alpha[i] + (windata->icon_alpha[i-1] - windata->icon_alpha[i] ) * pVar->step / windata->steps;
                        offset_y[i] = windata->icon_offset_y[i] + (windata->icon_offset_y[i-1] - windata->icon_offset_y[i]) * pVar->step / windata->steps;
                    }
                }
                else
                {
                    for (i=0; i<10; i++)
                    {
                        scale[i] = windata->icon_scale[i];
                        alpha[i] = windata->icon_alpha[i];
                        offset_y[i] = windata->icon_offset_y[i];
                    }
                }

                for (i=0; i<=6; i++)
                    idx[i] = (pVar->idx+3-i+6) % 6;

                HWND first_child = hWnd + 1;

                for (i=0; i<=6; i++)
                    _MApp_ZUI_CTL_MotionTrans_DrawHWND(&dc, first_child+idx[i], pVar->u16IconX[i] + m[i], offset_y[i], scale[i], alpha[i]);

                MSAPI_OSDRegion src, dest;
                src.x = windata->pVarData->u16CenterLeft;
                src.y = 0;
                src.width = windata->pVarData->u16CenterWidth;
                src.height = rect.height;
                src.fbID = dc.u8FbID;

                dest.x = rect.left;
                dest.y = rect.top;
                dest.width = windata->pVarData->u16CenterWidth;
                dest.height = rect.height;
                dest.fbID = pBufferDC->u8FbID;

                MApi_GFX_SetAlpha(FALSE, COEF_CONST, ABL_FROM_CONST, 0xFF);
                msAPI_OSD_SetClipWindow(rect.left, rect.top, rect.left+rect.width-1, rect.top+rect.height-1);
                msAPI_OSD_CopyRegion(&src, &dest);

                MApp_ZUI_API_DeleteDC(dc);
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hWnd, pMsg);
}


void MApp_ZUI_CTL_MotionTrans_SetStartPosition(HWND hWnd, U16 x, U16 y)
{
    GUI_DATA_MOTION_TRANS * windata = (GUI_DATA_MOTION_TRANS*)GETWNDDATA(hWnd);
    windata->x = x;
    windata->y = y;
}

#if 0
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
#endif

#if 0
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
    MApp_ZUI_API_PostMessage(hwnd, MSG_USER, hwndItem);
}
#endif

#if 0
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
#endif

#if 0
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
#endif

#if 0
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
#endif

#if 0
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
#endif

#if 0
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
#endif


#undef MAPP_ZUI_CTL_MOTIONTRANS_C
