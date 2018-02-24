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

#define MAPP_ZUI_CTL_FAKE3D_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "MsCommon.h"
#include "apiGOP.h"
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

#define bitShift    14
#define FixShift    (1 << bitShift)
int trapecoef[2][40][8];

void preCalTrapeCoef(int dir, int step, int allframes, int src_width, int src_height)
{
    int     dst_x0, dst_y0;

    float   delta, scale_h, scale_w_long, scale_w_short, h, w_long, w_short;
    float   intensity, trap_edge_gradient;
    int     trap_parallel0_length, trap_parallel1_length, trap_distance;
    int     parallel_edge0_st, parallel_edge0_pos, parallel_edge0_end;
    int     step_tmp, step_countdown;

    // calculate parameters for bitblt
    dst_x0 = 0;
    dst_y0 = 0;

    if(step == 0 || step == allframes)
    {
        trapecoef[dir][step][0] = 0;
        trapecoef[dir][step][1] = 0;
        trapecoef[dir][step][2] = 0;
        trapecoef[dir][step][3] = 0;
        trapecoef[dir][step][4] = 0;
        trapecoef[dir][step][5] = 0;
        trapecoef[dir][step][6] = 0;
        trapecoef[dir][step][7] = 1;
        return;
    }

    // calculate parameters for Trapezoid
    delta = 1.0f / (float)allframes;

    if(dir == 1)
        step_tmp = step;
    else
        step_tmp = allframes - step;

    // trapezoid show current image (front face)
    if(((step*2 < allframes) && (dir == 1)) || ((step*2 > allframes) && (dir == 0)))
    {
        scale_h = 1.0f - (step_tmp * delta * 2);
        scale_w_long = 1.0f + (step_tmp * delta);
        scale_w_short = 1.0f - (step_tmp * delta);
        h = src_width * scale_h;
        w_long = src_height * scale_w_long;
        w_short = src_height * scale_w_short;
        trap_distance = (int)(h + 0.5f);
        trap_parallel0_length = (int)(w_long + 0.5f);
        trap_parallel1_length = (int)(w_short + 0.5f);
        trap_edge_gradient = (float)((trap_parallel0_length - trap_parallel1_length) >>1 ) / trap_distance;
        intensity = 1.0f - ((float)step_tmp*2 / allframes);

    }
    // trapezoid show next image (back face)
    else
    {
        step_countdown = allframes - step_tmp;

        scale_h = 1.0f - (step_countdown * delta * 2);
        scale_w_long = 1.0f + (step_countdown * delta);
        scale_w_short = 1.0f - (step_countdown * delta);
        h = src_width * scale_h;
        w_long = src_height * scale_w_long;
        w_short = src_height * scale_w_short;
        trap_distance = (int)(h + 0.5f);
        trap_parallel0_length = (int)(w_short + 0.5f);
        trap_parallel1_length = (int)(w_long + 0.5f);
        trap_edge_gradient = (float)((trap_parallel0_length - trap_parallel1_length) >>1 ) / trap_distance;
        intensity = 1.0f - ((float)step_countdown*2 / allframes);

    }
    parallel_edge0_st = dst_y0 - ((trap_parallel0_length - src_height)/2);
    parallel_edge0_end = parallel_edge0_st + trap_parallel0_length;
    parallel_edge0_pos = dst_x0 + (src_width - trap_distance) / 2;

    trapecoef[dir][step][0] = parallel_edge0_st * FixShift;
    trapecoef[dir][step][1] = parallel_edge0_end * FixShift;
    trapecoef[dir][step][2] = parallel_edge0_pos;
    trapecoef[dir][step][3] = trap_distance;
    trapecoef[dir][step][4] = (src_width * FixShift) / trap_distance;
    trapecoef[dir][step][5] = (int)(trap_edge_gradient * FixShift);
    trapecoef[dir][step][6] = -trapecoef[dir][step][5];
    trapecoef[dir][step][7] = (int)(intensity * 255);

}

typedef struct
{
    int     src_x0;
    int     src_y0;

    //int     src_width;
    int     src_height;

    int     abl_const;

    // registers for Trapezoid Bitblt
    int     trap_dir;                   // 1 bit: 0: vertical, 1: horizontal
    int     parallel_edge0_pos;         // 11 bits (11.0): y-coor for vertical, x-coor for horizontal
    int     parallel_edge0_st;          // 11 bits (11.0): x-coor for vertial, y-coor for horizontal
    int     parallel_edge0_end;         // 11 bits (11.0): x-coor for vertial, y-coor for horizontal
    int     trap_distance;              // 11 bits (11.0): the distance between parallel edge0 and parallel edge1
    int     trap_gradient0;             // 18 bits (s5.12): dx for vertical, dy for horizontal
    int     trap_gradient1;             // 18 bits (s5.12): dx for vertical, dy for horizontal
    int     trape_distance_delta;       // 17 bits (5.12): dx for horizontal, dy for vertical

} Cefset;

Cefset motion_h(int dir, int step)
{
    Cefset  cef;

    cef.trap_dir = 1;         // horizontal
    cef.src_x0 = 0;
    cef.src_y0 = 0;

#if 0 ///TODO: fixme
    cef.src_height = (int)icon_info.u32Height;
#endif
    cef.src_height = 128;

    cef.parallel_edge0_st = trapecoef[dir][step][0];
    cef.parallel_edge0_end = trapecoef[dir][step][1];
    cef.parallel_edge0_pos = trapecoef[dir][step][2];

    cef.trap_distance = trapecoef[dir][step][3];
    cef.trape_distance_delta = trapecoef[dir][step][4];

    cef.trap_gradient0 = trapecoef[dir][step][5];
    cef.trap_gradient1 = trapecoef[dir][step][6];

    cef.abl_const = trapecoef[dir][step][7];

    return cef;
}

void _MApp_ZUI_CTL_Fake3D_DrawHWND(GRAPHIC_DC *pDC, HWND hWnd, U16 x, U16 y, float scale, float alpha)
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

void _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(GRAPHIC_DC *pDC, HWND hWnd, U16 x, U16 y, int dir, int step, int allframes, int scale)
{
#if 0
    if (x >= (int)tmp2_info.u32Width || x <= 10 /*|| scale < 33000*/)
        return 0;

    //tmp1.u32Height = tmp_info.u32Height;
    //clear_range(tmp_info.u32Addr, tmp_info.u32Width, 0, 0, tmp_info.u32Width, tmp_info.u32Height, 0x00000000);

    icon_info.u32Height = 197;
#endif

    RECT rect;
    MApp_ZUI_API_GetWindowRect(hWnd, &rect);

    GRAPHIC_DC dcTmp = MApp_ZUI_API_CreateDC(rect.width, rect.height);
    _MApp_ZUI_CTL_Fake3D_DrawHWND(&dcTmp, hWnd, 0, 0, 1.0, 1.0);

    if (step == 0)
    {
#if 0
        rect.left = x;
        rect.top = y;
        rect.width = rect.width * scale;
        rect.height = rect.height * scale;
        pDC->u8ConstantAlpha = 0xFF;
        _MApp_ZUI_API_DrawStyleList(pDC, &rect, GETNORMALDRAWSTYLE(hWnd));
#endif

        GOP_GwinFBAttr fbAttr;
        MSAPI_OSDRegion src;
        MSAPI_OSDRegion dst;

        MApi_GOP_GWIN_GetFBInfo(dcTmp.u8FbID, &fbAttr);
        src.fbID = dcTmp.u8FbID;
        src.x = src.y = 0;
        src.width = fbAttr.width;
        src.height = fbAttr.height;

        MApi_GOP_GWIN_GetFBInfo(pDC->u8FbID, &fbAttr);
        dst.fbID = pDC->u8FbID;
        dst.x = x;
        dst.y = y;
        dst.width = src.width;
        dst.height = src.height;

        msAPI_OSD_SetClipWindow(0, 0, fbAttr.width-1, fbAttr.height-1);
        msAPI_OSD_CopyRegion(&src, &dst);

        MApp_ZUI_API_DeleteDC(dcTmp);

        return;
    }

    // draw trapezoid
    Cefset _reg = motion_h(dir, step);

    int src_x = (int)(_reg.parallel_edge0_pos);
    int src_nW = (_reg.trap_distance);
    int src_nH = 0;
    int dst_x = x;
    int dst_y = y;

    // check if out of window
    if (dst_x < 0)
    {
        src_x = (int)(src_x - dst_x);
        src_nW = src_nW + dst_x;
        if (src_nW <= 0)
            return;
        dst_x = 0;
    }

    // calculate y offset
    int y_offset;
    if (dir == 0)
        y_offset = ((allframes - step) * FixShift) / allframes;
    else
        y_offset = ((allframes + step) * FixShift) / allframes;

    src_nH = ((int)128 * y_offset) >> bitShift;
    int scale_h = src_nH * scale >> bitShift;
    int ypos = (scale_h - src_nH) / 2;

    dst_y = (y - ypos) * FixShift;
    dst_y = (dst_y >> bitShift) << bitShift;

    int dst_h = (_reg.parallel_edge0_end - _reg.parallel_edge0_st) >> bitShift;
    dst_h = ((dst_h * scale) >> bitShift) << bitShift;

    int     lines, idst_y0, idst_y1, isrc_x;

    int     _fix_src_x = _reg.src_x0;
    int     _fix_src_y = _reg.src_y0;
    int     _fix_line_st = _reg.parallel_edge0_st + dst_y;
    int     _fix_line_end = _fix_line_st + dst_h;
    int     _fix_distance_delta = _reg.trape_distance_delta >> bitShift;
    int     ltemp = _reg.trap_gradient0 * scale;
    int     _fix_grad0 = (int)(ltemp >> bitShift);
    int     _fix_grad1 = -_fix_grad0;

    GOP_GwinFBAttr fbAttr;
    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    MApi_GOP_GWIN_GetFBInfo(dcTmp.u8FbID, &fbAttr);
    BitbltInfo.src_fm = fbAttr.fbFmt;
    PitBaseInfo.sb_base = fbAttr.addr;
    PitBaseInfo.sb_pit = fbAttr.pitch;

    MApi_GOP_GWIN_GetFBInfo(pDC->u8FbID, &fbAttr);
    BitbltInfo.dst_fm = fbAttr.fbFmt;
    PitBaseInfo.db_base = fbAttr.addr;
    PitBaseInfo.db_pit = fbAttr.pitch;

    MDrv_GE_EnableAlphaBlending(TRUE);
    MDrv_GE_SetAlphaBlending(COEF_CONST, _reg.abl_const);
    msAPI_OSD_SetClipWindow(0, 0, fbAttr.width-1, fbAttr.height-1);
    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;

    for (x=dst_x, lines=0; lines<_reg.trap_distance; ++lines, ++x)
    {
        idst_y0 = (_fix_line_st  >> bitShift);
        idst_y1 = (_fix_line_end >> bitShift);
        isrc_x = _fix_src_x >> bitShift;

        //src
        BitbltInfo.BitbltCoordinate.v2_x = (U16)isrc_x;
        BitbltInfo.BitbltCoordinate.v2_y = (U16)_fix_src_y;
        BitbltInfo.src_width = (U16)(_fix_distance_delta);
        BitbltInfo.src_height = (U16)(_reg.src_height);
        //dst
        BitbltInfo.BitbltCoordinate.v0_x = (U16)x;
        BitbltInfo.BitbltCoordinate.v0_y = (U16)idst_y0;
        BitbltInfo.BitbltCoordinate.width = 1;
        BitbltInfo.BitbltCoordinate.height = (U16)(idst_y1 - idst_y0);

#if 0
        printf("(%d,%d,%d,%d)->(%d,%d,%d,%d)\n",
            BitbltInfo.BitbltCoordinate.v2_x,
            BitbltInfo.BitbltCoordinate.v2_y,
            BitbltInfo.src_width,
            BitbltInfo.src_height,
            BitbltInfo.BitbltCoordinate.v0_x,
            BitbltInfo.BitbltCoordinate.v0_y,
            BitbltInfo.BitbltCoordinate.width,
            BitbltInfo.BitbltCoordinate.height);
#endif

        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);

#if 0//EdgeAA
        if (EnAA)
        {
            // end point do Alpha blending for AA
            src_addr = icon_info.u32Addr + (rect.srcblk.x + rect.srcblk.width/2) * 4;
            dst_addr = tmp2_info.u32Addr + (rect.dstblk.y * tmp2_info.u32Pitch) + rect.dstblk.x * 4;
            frac = (FixShift - (_fix_line_st & FracMask));

            color.dw = *(unsigned long *)((unsigned char *)src_addr);
            color.r = ((color.r * frac) >> bitShift) * _reg.abl_const / 255;
            color.g = ((color.g * frac) >> bitShift) * _reg.abl_const / 255;
            color.b = ((color.b * frac) >> bitShift) * _reg.abl_const / 255;
            color.a = (_reg.abl_const * frac) >> bitShift;
            *(unsigned long *)((unsigned char *)dst_addr) = color.dw;

            /*src_addr = icon_info.u32Addr + isrc_x * 4;
            dst_addr = tmp2_info.u32Addr + (idst_y1 * tmp2_info.u32Pitch) + x*4;
            frac = (_fix_line_end & FracMask);
            color.dw = *(unsigned long *)((unsigned char *)src_addr);
            color.r = (color.r * frac) >> bitShift;
            color.g = (color.g * frac) >> bitShift;
            color.b = (color.b * frac) >> bitShift;
            *(unsigned long *)((unsigned char *)dst_addr) = color.dw;*/
        }
#endif

        _fix_src_x += _reg.trape_distance_delta;
        _fix_line_st += _fix_grad0;
        _fix_line_end += _fix_grad1;
    }

    MDrv_GE_EnableAlphaBlending(FALSE);
    MApp_ZUI_API_DeleteDC(dcTmp);

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

S32 MApp_ZUI_CTL_Fake3D_Icon_WinProc(HWND hWnd, PMSG pMsg)
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

S32 MApp_ZUI_CTL_Fake3D_WinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_FAKE3D * windata = (GUI_DATA_FAKE3D*)GETWNDDATA(hWnd);

  #if 0
    GUI_DATA_FAKE3D_VARDATA * pVar = windata->pVarData;

    //no dynamic list setting data...
    if (windata == 0 || windata->pVarData == 0)
        return DEFAULTWINPROC(hWnd, pMsg);
  #else // Modifed it by coverity_491
    GUI_DATA_FAKE3D_VARDATA * pVar = NULL;
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
        case MSG_CREATE:
            {
//printf("MSG_CREATE\n");

                pVar->step_c = 0;
                pVar->step_l = pVar->step_r = 10;
                pVar->step_l2 = pVar->step_r2 = 20;
                pVar->step_l3 = pVar->step_r3 = 30;

                int i;
                float sc0, sc1_large, sc1_small, sc2_large, sc2_small, sc3_large, sc3_small;
                for (i=0; i<10; i++)
                {
                    sc0 = ((float)(windata->allsteps + pVar->step_c) / (float)(windata->allsteps));

                    sc1_large = ((float)(windata->allsteps + pVar->step_c) / (float)(windata->allsteps - pVar->step_l));
                    sc1_small = ((float)(windata->allsteps - pVar->step_c) / (float)(windata->allsteps - pVar->step_r));

                    sc2_large = ((float)(windata->allsteps + pVar->step_l) / (float)(windata->allsteps - pVar->step_l2));
                    sc3_large = ((float)(windata->allsteps + pVar->step_l2) / (float)(windata->allsteps - pVar->step_l3));

                    sc2_small = ((float)(windata->allsteps + pVar->step_r) / (float)(windata->allsteps - pVar->step_r2));
                    sc3_small = ((float)(windata->allsteps + pVar->step_r2) / (float)(windata->allsteps - pVar->step_r3));

                    pVar->sc_array0[i] = (int)(sc0 * FixShift);
                    float fsc1_l = sc1_large * sc0;
                    float fsc1_s = sc1_small * sc0;
                    pVar->sc_array1[0][i] = (int)(fsc1_l * FixShift);
                    pVar->sc_array1[1][i] = (int)(fsc1_s * FixShift);
                    fsc1_l = fsc1_l * sc2_large;
                    fsc1_s = fsc1_s * sc2_small;
                    pVar->sc_array2[0][i] = (int)(fsc1_l * FixShift);
                    pVar->sc_array2[1][i] = (int)(fsc1_s * FixShift);
                    fsc1_l = fsc1_l * sc3_large;
                    fsc1_s = fsc1_s * sc3_small;
                    pVar->sc_array3[0][i] = (int)(fsc1_l * FixShift);
                    pVar->sc_array3[1][i] = (int)(fsc1_s * FixShift);

                    // center-left trapezoid
                    preCalTrapeCoef(1, pVar->step_c, windata->allsteps, 128, 128);
                    // left-1
                    preCalTrapeCoef(1, pVar->step_l, windata->allsteps, 128, 128);
                    // left-2
                    preCalTrapeCoef(1, pVar->step_l2, windata->allsteps, 128, 128);
                    // left-3
                    preCalTrapeCoef(1, pVar->step_l3, windata->allsteps, 128, 128);

                    // center-right
                    preCalTrapeCoef(0, pVar->step_c, windata->allsteps, 128, 128);
                    //right-1
                    preCalTrapeCoef(0, pVar->step_r, windata->allsteps, 128, 128);
                    //right-2
                    preCalTrapeCoef(0, pVar->step_r2, windata->allsteps, 128, 128);
                    //right-3
                    preCalTrapeCoef(0, pVar->step_r3, windata->allsteps, 128, 128);

                    pVar->step_c++;
                    pVar->step_l++;
                    pVar->step_l2++;
                    pVar->step_l3++;
                    pVar->step_r--;
                    pVar->step_r2--;
                    pVar->step_r3--;
                }
                pVar->step_c = 0;
                pVar->step_l = pVar->step_r = 10;
                pVar->step_l2 = pVar->step_r2 = 20;
                pVar->step_l3 = pVar->step_r3 = 30;

                pVar->scale_c = pVar->sc_array0[0];
                pVar->scale_l = pVar->sc_array1[0][0];
                pVar->scale_r = pVar->sc_array1[1][0];
                pVar->scale_l2 = pVar->sc_array2[0][0];
                pVar->scale_r2 = pVar->sc_array2[1][0];
                pVar->scale_l3 = pVar->sc_array3[0][0];
                pVar->scale_r3 = pVar->sc_array3[1][0];

                Cefset _reg;

                pVar->step = 0;
                pVar->idx = 0;
                pVar->u8IconWidth = 128;
                pVar->u16IconW[3] = pVar->u8IconWidth;
                _reg = motion_h(0, pVar->step_l);
                pVar->u16IconW[2] = _reg.trap_distance;
                _reg = motion_h(1, pVar->step_r);
                pVar->u16IconW[4] = _reg.trap_distance;
                _reg = motion_h(0, pVar->step_l2);
                pVar->u16IconW[1] = _reg.trap_distance;
                _reg = motion_h(1, pVar->step_r2);
                pVar->u16IconW[5] = _reg.trap_distance;
                _reg = motion_h(0, pVar->step_l3);
                pVar->u16IconW[0] = _reg.trap_distance;
                _reg = motion_h(1, pVar->step_r3);
                pVar->u16IconW[6] = _reg.trap_distance;

                pVar->u16IconX[0] = windata->margin;
                pVar->u16IconX[1] = pVar->u16IconX[0] + pVar->u16IconW[0] + windata->icon_interval;
                pVar->u16IconX[2] = pVar->u16IconX[1] + pVar->u16IconW[1] + windata->icon_interval;
                pVar->u16IconX[3] = pVar->u16IconX[2] + pVar->u16IconW[2] + windata->icon_interval;
                pVar->u16IconX[4] = pVar->u16IconX[3] + pVar->u16IconW[3] + windata->icon_interval;
                pVar->u16IconX[5] = pVar->u16IconX[4] + pVar->u16IconW[4] + windata->icon_interval;
                pVar->u16IconX[6] = pVar->u16IconX[5] + pVar->u16IconW[5] + windata->icon_interval;
                pVar->u16IconX[7] = pVar->u16IconX[6] + pVar->u16IconW[6] + windata->icon_interval;

                pVar->u16CenterLeft = pVar->u16IconX[1];
                pVar->u16CenterWidth = pVar->u16IconX[6] - windata->icon_interval - pVar->u16IconX[1];
                pVar->u16Width = pVar->u16IconX[7] - windata->icon_interval + windata->margin;
                pVar->u16Height = ( 128*(150+30)*pVar->scale_r3/150 ) >> bitShift;

                pVar->dir_l = 1;
                pVar->dir_c = 1;
                pVar->dir_r = 0;

                RECT rect;
                rect.left = windata->x;
                rect.top = windata->y;
                rect.width = pVar->u16CenterWidth;
                rect.height = pVar->u16Height;
                MApp_ZUI_API_MoveWindow(hWnd, &rect);


            }
            return 0;

        case MSG_NOTIFY_HIDE:
            {
//printf("MSG_NOTIFY_HIDE\n");
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
                if ( pVar->step != 0 )
                {
                    return 0;
                }
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
                    return DEFAULTWINPROC(hWnd, pMsg);
            }

            return 0; // Added by coverity_0605

        case MSG_TIMER:
            {
//printf("MSG_TIMER\n");
                pVar->step++;
                if ( pVar->step >= windata->steps )
                {
                    pVar->step = 0;
                    pVar->step_c = 0;
                    pVar->step_l = pVar->step_r = 10;
                    pVar->step_r2 = pVar->step_l2 = 20;
                    pVar->step_l3 = pVar->step_r3 = 30;
                    pVar->scale_c = pVar->sc_array0[0];
                    pVar->scale_l = pVar->sc_array1[0][0];
                    pVar->scale_r = pVar->sc_array1[1][0];
                    pVar->scale_l2 = pVar->sc_array2[0][0];
                    pVar->scale_r2 = pVar->sc_array2[1][0];
                    pVar->scale_l3 = pVar->sc_array3[0][0];
                    pVar->scale_r3 = pVar->sc_array3[1][0];

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

                int k = pVar->step % 10;
                pVar->scale_c = pVar->sc_array0[k];
                if ( pVar->dir == DIR_RIGHT )
                {
                    pVar->scale_l = pVar->sc_array1[0][k];
                    pVar->scale_r = pVar->sc_array1[1][k];
                    pVar->scale_l2 = pVar->sc_array2[0][k];
                    pVar->scale_r2 = pVar->sc_array2[1][k];
                    pVar->scale_l3 = pVar->sc_array3[0][k];
                    pVar->scale_r3 = pVar->sc_array3[1][k];

                    pVar->step_c++;
                    pVar->step_l++;  pVar->step_l2++; pVar->step_l3++;
                    pVar->step_r--;  pVar->step_r2--; pVar->step_r3--;
                    pVar->dir_l = 1;  pVar->dir_c = 1;  pVar->dir_r = 0;
                }
                else if ( pVar->dir == DIR_LEFT )
                {
                    pVar->scale_l = pVar->sc_array1[1][k];
                    pVar->scale_r = pVar->sc_array1[0][k];
                    pVar->scale_l2 = pVar->sc_array2[1][k];
                    pVar->scale_r2 = pVar->sc_array2[0][k];
                    pVar->scale_l3 = pVar->sc_array3[1][k];
                    pVar->scale_r3 = pVar->sc_array3[0][k];

                    pVar->step_c++;
                    pVar->step_l--;  pVar->step_l2--; pVar->step_l3--;
                    pVar->step_r++;  pVar->step_r2++; pVar->step_r3++;
                    pVar->dir_l = 1;  pVar->dir_c = 0;  pVar->dir_r = 0;
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
                GRAPHIC_DC dc = MApp_ZUI_API_CreateDC(pVar->u16Width, pVar->u16Height);

                #if 0
                clrBtn1.x = 0;
                clrBtn1.y = 0;
                clrBtn1.width = pVar->u16Width;
                clrBtn1.height = pVar->u16Height;
                clrBtn1.b_clr = 0xFF0000;
                clrBtn1.u8Gradient = CONSTANT_COLOR;
                clrBtn1.fHighLight = FALSE;
                msAPI_OSD_DrawBlock(&clrBtn1);
                #endif

                S16 m[10] = {0};
                U8 idx[10] = {0};
                if ( pVar->dir == DIR_LEFT )
                {
                    for (i=0; i<6; i++)
                    {
                        m[i] = (pVar->u16IconX[i+1] - pVar->u16IconX[i] ) * pVar->step / windata->steps;
                    }
                    m[i] = (pVar->u16IconX[i] - pVar->u16IconX[i] ) * pVar->step / windata->steps;
                }
                else if ( pVar->dir == DIR_RIGHT )
                {
                    m[0] = (pVar->u16IconX[0] - pVar->u16IconX[0] ) * pVar->step / windata->steps;
                    for (i=1; i<=6; i++)
                    {
                        m[i] = (pVar->u16IconX[i-1] - pVar->u16IconX[i] ) * pVar->step / windata->steps;
                    }
                }

                for (i=0; i<=6; i++)
                    idx[i] = (pVar->idx+3-i+6) % 6;

                HWND first_child = hWnd + 1;

                int ypos = (pVar->u16Height - 128) / 2;

                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[0], pVar->u16IconX[0] + m[0], ypos, pVar->dir_l, pVar->step_l3, 150, pVar->scale_l3);
                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[1], pVar->u16IconX[1] + m[1], ypos, pVar->dir_l, pVar->step_l2, 150, pVar->scale_l2);
                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[2], pVar->u16IconX[2] + m[2], ypos, pVar->dir_l, pVar->step_l, 150, pVar->scale_l);
                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[3], pVar->u16IconX[3] + m[3], ypos, pVar->dir_c, pVar->step_c, 150, pVar->scale_c);
                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[4], pVar->u16IconX[4] + m[4], ypos, pVar->dir_r, pVar->step_r, 150, pVar->scale_r);
                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[5], pVar->u16IconX[5] + m[5], ypos, pVar->dir_r, pVar->step_r2, 150, pVar->scale_r2);
                _MApp_ZUI_CTL_Fake3D_DrawTrapezoid(&dc, first_child+idx[6], pVar->u16IconX[6] + m[6], ypos, pVar->dir_r, pVar->step_r3, 150, pVar->scale_r3);

                MSAPI_OSDRegion src, dest;
                src.x = windata->pVarData->u16CenterLeft-1;
                src.y = 0;
                src.width = windata->pVarData->u16CenterWidth+2;
                src.height = pVar->u16Height;
                src.fbID = dc.u8FbID;

                dest.x = rect.left;
                dest.y = rect.top;
                dest.width = windata->pVarData->u16CenterWidth+2;
                dest.height = pVar->u16Height;
                dest.fbID = pBufferDC->u8FbID;

                MApi_GFX_SetAlpha(FALSE, COEF_CONST, ABL_FROM_CONST, 0xFF);
                msAPI_OSD_SetClipWindow(rect.left, rect.top, rect.left+pVar->u16Width-1, rect.top+pVar->u16Height-1);
                msAPI_OSD_CopyRegion(&src, &dest);

                MApp_ZUI_API_DeleteDC(dc);
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hWnd, pMsg);
}


void MApp_ZUI_CTL_Fake3D_SetStartPosition(HWND hWnd, U16 x, U16 y)
{
    GUI_DATA_FAKE3D * windata = (GUI_DATA_FAKE3D*)GETWNDDATA(hWnd);
    windata->x = x;
    windata->y = y;
}

#undef MAPP_ZUI_CTL_FAKE3D_C
