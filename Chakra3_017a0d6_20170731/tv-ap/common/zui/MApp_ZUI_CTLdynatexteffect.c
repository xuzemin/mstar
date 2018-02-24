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

#define MAPP_ZUI_CTL_DYNATEXT_EFFECT_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "datatype.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "msAPI_OSD.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_CTLdynatexteffect.h"

#include "MApp_ZUI_APIcomponent.h"
#include "apiGOP.h"
#include "Utl.h"

// ----- for Item Selected Effect ------
#define bitShift    14
#define FixShift    (1 << bitShift)
#define FracMask    ((1 << bitShift) - 1)
#define P_EDGE_ST           0
#define P_EDGE_END          1
#define P_EDGE_POS          2
#define TRAP_DIST           3
#define TRAP_DIST_DELTA   4
#define TRAP_GRAD0          5
#define TRAP_GRAD1          6
#define ABL_CONST           7
#define TRANSITION_EFFECT_TIMER_ID  0
#define TRANSITION_EFFECT_TIMER_MS  50

typedef struct
{
    int     src_x0;
    int     src_y0;

    int     src_width;
    int     src_height;

    U8      src_fbId;
    U8      dst_fbId;

    float   abl_const;

    // registers for Trapezoid Bitblt
    int     trap_dir;                   // 1 bit: 0: vertical, 1: horizontal
    float   parallel_edge0_pos;         // 11 bits (11.0): y-coor for vertical, x-coor for horizontal
    float   parallel_edge0_st;          // 11 bits (11.0): x-coor for vertial, y-coor for horizontal
    float   parallel_edge0_end;         // 11 bits (11.0): x-coor for vertial, y-coor for horizontal
    float   trap_distance;              // 11 bits (11.0): the distance between parallel edge0 and parallel edge1
    float   trap_gradient0;             // 18 bits (s5.12): dx for vertical, dy for horizontal
    float   trap_gradient1;             // 18 bits (s5.12): dx for vertical, dy for horizontal
    float   trape_distance_delta;       // 17 bits (5.12): dx for horizontal, dy for vertical

}Regset;

// trapezoid coefficient for flip, cube, fall, and fold
//parallel_edge0_st, parallel_edge0_end, parallel_edge0_pos, trap_distance, trape_distance_delta, trap_gradient0, trap_gradient1, abl_const
static float flipTrap[2][14][8] = {
{
    {36.000000, 155.000000, 40.000000, 112.000000, 1.142857, -0.071429, 0.071429, 0.937500},
    {40.000000, 151.000000, 48.000000, 96.000000, 1.333333, -0.166667, 0.166667, 0.875000},
    {44.000000, 147.000000, 56.000000, 80.000000, 1.600000, -0.300000, 0.300000, 0.812500},
    {48.000000, 143.000000, 64.000000, 64.000000, 2.000000, -0.500000, 0.500000, 0.750000},
    {52.000000, 139.000000, 72.000000, 48.000000, 2.666667, -0.833333, 0.833333, 0.687500},
    {56.000000, 135.000000, 80.000000, 32.000000, 4.000000, -1.500000, 1.500000, 0.625000},
    {60.000000, 131.000000, 88.000000, 16.000000, 8.000000, -3.500000, 3.500000, 0.562500},
    {4.000000, 187.000000, 88.000000, 16.000000, 8.000000, 3.500000, -3.500000, 0.562500},
    {8.000000, 183.000000, 80.000000, 32.000000, 4.000000, 1.500000, -1.500000, 0.625000},
    {12.000000, 179.000000, 72.000000, 48.000000, 2.666667, 0.833333, -0.833333, 0.687500},
    {16.000000, 175.000000, 64.000000, 64.000000, 2.000000, 0.500000, -0.500000, 0.750000},
    {20.000000, 171.000000, 56.000000, 80.000000, 1.600000, 0.300000, -0.300000, 0.812500},
    {24.000000, 167.000000, 48.000000, 96.000000, 1.333333, 0.166667, -0.166667, 0.875000},
    {28.000000, 163.000000, 40.000000, 112.000000, 1.142857, 0.071429, -0.071429, 0.937500},
},
{
    {28.000000, 163.000000, 40.000000, 112.000000, 1.142857, 0.071429, -0.071429, 0.937500},
    {24.000000, 167.000000, 48.000000, 96.000000, 1.333333, 0.166667, -0.166667, 0.875000},
    {20.000000, 171.000000, 56.000000, 80.000000, 1.600000, 0.300000, -0.300000, 0.812500},
    {16.000000, 175.000000, 64.000000, 64.000000, 2.000000, 0.500000, -0.500000, 0.750000},
    {12.000000, 179.000000, 72.000000, 48.000000, 2.666667, 0.833333, -0.833333, 0.687500},
    {8.000000, 183.000000, 80.000000, 32.000000, 4.000000, 1.500000, -1.500000, 0.625000},
    {4.000000, 187.000000, 88.000000, 16.000000, 8.000000, 3.500000, -3.500000, 0.562500},
    {60.000000, 131.000000, 88.000000, 16.000000, 8.000000, -3.500000, 3.500000, 0.562500},
    {56.000000, 135.000000, 80.000000, 32.000000, 4.000000, -1.500000, 1.500000, 0.625000},
    {52.000000, 139.000000, 72.000000, 48.000000, 2.666667, -0.833333, 0.833333, 0.687500},
    {48.000000, 143.000000, 64.000000, 64.000000, 2.000000, -0.500000, 0.500000, 0.750000},
    {44.000000, 147.000000, 56.000000, 80.000000, 1.600000, -0.300000, 0.300000, 0.812500},
    {40.000000, 151.000000, 48.000000, 96.000000, 1.333333, -0.166667, 0.166667, 0.875000},
    {36.000000, 155.000000, 40.000000, 112.000000, 1.142857, -0.071429, 0.071429, 0.937500},
},
};
//---------------------------------------

extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);
extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);

static void trapezoid_v_blt(Regset _reg)
{
    GOP_GwinFBAttr fbAttr;
    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    int   y, lines,  idst_x0, idst_x1;
    int   isrc_x, isrc_y;

    int _fix_src_x = _reg.src_x0 * FixShift;
    int _fix_src_y = _reg.src_y0 * FixShift;
    int _fix_line_st = _reg.parallel_edge0_st  * FixShift;
    int _fix_line_end = _reg.parallel_edge0_end  * FixShift;
    int _fix_dist_delta = _reg.trape_distance_delta * FixShift;
    int _fix_grad0 = _reg.trap_gradient0 * FixShift;
    int _fix_grad1 = _reg.trap_gradient1 * FixShift;

    _fix_line_st = _fix_line_st + (FixShift >> 1);
    _fix_line_end = _fix_line_end + (FixShift >> 1);

    int alpha = (int)(255.0f * _reg.abl_const);
    //int fix_alpha = _reg.abl_const * FixShift;

    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);

    for(y=(int)_reg.parallel_edge0_pos, lines=0; lines<(int)_reg.trap_distance; ++lines, ++y)
    {
        idst_x0 = (_fix_line_st >> bitShift);
        idst_x1 = (_fix_line_end >> bitShift);
        isrc_x = (_fix_src_x + (FixShift>>1)) >> bitShift;
        isrc_y = (_fix_src_y + (FixShift>>1)) >> bitShift;

        msAPI_OSD_SetClipWindow(
            (U16)idst_x0,
            (U16)y,
            (U16)idst_x0+(U16)(idst_x1 - idst_x0 ),
            (U16)y);
        msAPI_OSD_GET_resource();
        BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        //src
        BitbltInfo.BitbltCoordinate.v2_x = (U16)isrc_x;
        BitbltInfo.BitbltCoordinate.v2_y = (U16)isrc_y;
        BitbltInfo.src_width = (U16)(_reg.src_width);
        BitbltInfo.src_height = (U16)(_reg.trape_distance_delta);
        //dst
        BitbltInfo.BitbltCoordinate.v0_x = (U16)idst_x0;
        BitbltInfo.BitbltCoordinate.v0_y = (U16)y;
        BitbltInfo.BitbltCoordinate.width = (U16)(idst_x1 - idst_x0 + 1);
        BitbltInfo.BitbltCoordinate.height = (U16)(1);
#if 0
        printf("(%d) (%d, %d, %d, %d) --> (%d, %d, %d, %d) [fbId:%d, Dst:%d, alpha:%d]\n", lines,
            (U16)isrc_x, (U16)isrc_y, (U16)(_reg.src_width), (U16)(_reg.trape_distance_delta),
            (U16)idst_x0, (U16)y, (U16)(idst_x1 - idst_x0 + 1), (U16)(1), _reg.src_fbId, _reg.dst_fbId, alpha);
#endif
        MApi_GOP_GWIN_GetFBInfo(_reg.src_fbId, &fbAttr);
        BitbltInfo.src_fm = fbAttr.fbFmt;
        PitBaseInfo.sb_base = fbAttr.addr;
        PitBaseInfo.sb_pit = fbAttr.pitch;

        MApi_GOP_GWIN_GetFBInfo(_reg.dst_fbId, &fbAttr);
        //MApi_GOP_GWIN_GetFBInfo(dcScreen->u8FbID, &fbAttr);
        BitbltInfo.dst_fm = fbAttr.fbFmt;
        PitBaseInfo.db_base = fbAttr.addr;
        PitBaseInfo.db_pit = fbAttr.pitch;

        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
        msAPI_OSD_Free_resource();
#if 0//EdgeAA
        if (EnAA)
        {
            // end point do Alpha blending for AA
            int src_addr, dst_addr, frac, c_weight;
            Color color;

            src_addr = icon_info.u32Addr + (isrc_y * icon_info.u32Pitch) + (rect.srcblk.x) * 4;
            dst_addr = loc.u32Addr + (rect.dstblk.y * loc.u32Pitch) + rect.dstblk.x * 4;
            color.dw = *(unsigned long *)((unsigned char *)src_addr);

            frac = (FixShift - (_fix_line_st & FracMask));
            c_weight = (frac * fix_alpha) >> bitShift;
            color.r = (color.r * c_weight) >> bitShift;
            color.g = (color.g * c_weight) >> bitShift;
            color.b = (color.b * c_weight) >> bitShift;
            color.a = (255 * c_weight) >> bitShift;
            *(unsigned long *)((unsigned char *)dst_addr) = color.dw;

            src_addr = icon_info.u32Addr + (isrc_y * icon_info.u32Pitch) + (icon_info.u32Width - 1) * 4;
            dst_addr = loc.u32Addr + (rect.dstblk.y * loc.u32Pitch) + idst_x1*4;
            color.dw = *(unsigned long *)((unsigned char *)src_addr);

            frac = (_fix_line_end & FracMask);
            c_weight = (frac * fix_alpha) >> bitShift;
            color.r = (color.r * c_weight) >> bitShift;
            color.g = (color.g * c_weight) >> bitShift;
            color.b = (color.b * c_weight) >> bitShift;
            color.a = (255 * c_weight) >> bitShift;
            *(unsigned long *)((unsigned char *)dst_addr) = color.dw;
        }
#endif
        _fix_src_y    += _fix_dist_delta;
        _fix_line_st  += _fix_grad0;
        _fix_line_end += _fix_grad1;
    }

    MDrv_GE_EnableAlphaBlending(FALSE);

}
static void trapezoid_h_blt(Regset _reg)
{
    GOP_GwinFBAttr fbAttr;
    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    int     x, lines;
    int     idst_y0, idst_y1, distance_delta, pre_x;
    int     isrc_x;

    int _fix_gradient0 = _reg.trap_gradient0 * FixShift;
    int _fix_gradient1 = _reg.trap_gradient1 * FixShift;
    int _fix_distance_delta = _reg.trape_distance_delta * FixShift;
    int _fix_src_x = _reg.src_x0;
    int _fix_line_st = _reg.parallel_edge0_st * FixShift;
    int _fix_line_end = _reg.parallel_edge0_end * FixShift;
    int _fix_src_y;
    //GRAPHIC_DC *dcScreen = MApp_ZUI_API_GetScreenDC();
    int alpha = (int)(255.0f * _reg.abl_const);

    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);

    pre_x = _fix_src_x;
    for(x=(int)_reg.parallel_edge0_pos, lines=0; lines<(int)_reg.trap_distance; ++lines, ++x)
    {
        idst_y0 = (_fix_line_st >> bitShift);
        idst_y1 = (_fix_line_end >> bitShift);
        isrc_x  = (_fix_src_x >> bitShift);
        distance_delta = (isrc_x - pre_x);
        _fix_src_y = _reg.src_y0;

        /*_fix_11p0 = (float)(idst_y1 - idst_y0);
        _fix_scanline_delta = (float)_reg.src_height;
        _fix_scanline_delta = _fix_scanline_delta / _fix_11p0;*/

        msAPI_OSD_SetClipWindow(
            (U16)x,
            (U16)idst_y0,
            (U16)x,
            (U16)idst_y0+(U16)(idst_y1 - idst_y0 ));
        msAPI_OSD_GET_resource();
        BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        //dst
        BitbltInfo.BitbltCoordinate.v0_x = (U16)x;
        BitbltInfo.BitbltCoordinate.v0_y = (U16)idst_y0;
        BitbltInfo.BitbltCoordinate.width = 1;
        BitbltInfo.BitbltCoordinate.height = (U16)(idst_y1 - idst_y0 + 1);
        //src
        BitbltInfo.BitbltCoordinate.v2_x = (U16)isrc_x;
        BitbltInfo.BitbltCoordinate.v2_y = (U16)_fix_src_y;
        BitbltInfo.src_width = (U16)(_reg.trape_distance_delta);
        BitbltInfo.src_height = (U16)(_reg.src_height);
#if 0
        printf("(%d) (%d, %d, %d, %d) --> (%d, %d, %d, %d) [fbId:%d, Dst:%d, alpha:%d]\n", lines,
            (U16)isrc_x, (U16)_fix_src_y, (U16)(_reg.trape_distance_delta), (U16)(_reg.src_height),
            (U16)x, (U16)idst_y0, 1, (U16)(idst_y1 - idst_y0 + 1), _reg.src_fbId, _reg.dst_fbId, alpha);
#endif
        MApi_GOP_GWIN_GetFBInfo(_reg.src_fbId, &fbAttr);
        BitbltInfo.src_fm = fbAttr.fbFmt;
        PitBaseInfo.sb_base = fbAttr.addr;
        PitBaseInfo.sb_pit = fbAttr.pitch;

        MApi_GOP_GWIN_GetFBInfo(_reg.dst_fbId, &fbAttr);
        //MApi_GOP_GWIN_GetFBInfo(dcScreen->u8FbID, &fbAttr);
        BitbltInfo.dst_fm = fbAttr.fbFmt;
        PitBaseInfo.db_base = fbAttr.addr;
        PitBaseInfo.db_pit = fbAttr.pitch;

        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
        msAPI_OSD_Free_resource();

#if 0
        if (EnAA)
        {
            // end point do Alpha blending for AA
            int src_addr, dst_addr, frac, c_weight;
            Color color;
            src_addr = icon_info.u32Addr + (rect.srcblk.x) * 4;
            dst_addr = loc.u32Addr + (rect.dstblk.y * loc.u32Pitch) + rect.dstblk.x * 4;
            color.dw = *(unsigned long *)((unsigned char *)src_addr);

            frac = (FixShift - (_fix_line_st & FracMask));
            c_weight = (frac * fix_alpha) >> bitShift;
            color.r = (color.r * c_weight) >> bitShift;
            color.g = (color.g * c_weight) >> bitShift;
            color.b = (color.b * c_weight) >> bitShift;
            color.a = (255 * c_weight) >> bitShift;
            *(unsigned long *)((unsigned char *)dst_addr) = color.dw;

            src_addr = icon_info.u32Addr + ((_reg.src_height-1) * icon_info.u32Pitch) + (rect.srcblk.x) * 4;
            dst_addr = loc.u32Addr + (idst_y1 * loc.u32Pitch) + x * 4;
            color.dw = *(unsigned long *)((unsigned char *)src_addr);

            frac = (_fix_line_end & FracMask);
            c_weight = (frac * fix_alpha) >> bitShift;
            color.r = (color.r * c_weight) >> bitShift;
            color.g = (color.g * c_weight) >> bitShift;
            color.b = (color.b * c_weight) >> bitShift;
            color.a = (255 * c_weight) >> bitShift;
            *(unsigned long *)((unsigned char *)dst_addr) = color.dw;
        }
#endif
        _fix_src_x += _fix_distance_delta;
        _fix_line_st += _fix_gradient0;
        _fix_line_end += _fix_gradient1;
        pre_x = isrc_x;
    }

    MDrv_GE_EnableAlphaBlending(FALSE);

}
// dir=0: up, dir=1: down
static void flip_v(U8 dir, S8 step, S8 dstStep, U8 fbFg, U8 fbBg, U8 fbTmp, RECT *rectItem, RECT *rectTmp)
{
    Regset  reg;
    memset(&reg,0,sizeof(Regset));
    int     dst_x0, dst_y0;
    U8      fbId = 0xFF;

    int     src_width  = (int)rectItem->width;
    int     src_height = (int)rectItem->height;
    int     dst_width  = (int)rectTmp->width;
    int     dst_height = (int)rectTmp->height;
    GEColorRange clrrange;

    // calculate parameters for bitblt
    dst_x0 = ((dst_width - src_width) >> 1);
    dst_y0 = ((dst_height - src_height) >> 1);

    int step2 = (step * 2);

    if(step*2 == dstStep)
        return;

    // trapezoid show current image (front face)
    if(((step*2 < dstStep) && (dir == 1)) || ((step*2 > dstStep) && (dir == 0)))
    {
        if(dir == 1)
            fbId = fbFg;
        else
            fbId = fbBg;
    }
    // trapezoid show next image (back face)
    else
    {
        if(dir == 1)
            fbId = fbBg;
        else
            fbId = fbFg;
    }

    int frame = (step2 > dstStep)? (step - 2) : (step - 1);

    // draw foreground
    reg.trap_dir = 0;         // vertical
    reg.src_x0 = 0;
    reg.src_y0 = 0;
    reg.src_width = src_width;
    reg.parallel_edge0_st  = flipTrap[dir][frame][P_EDGE_ST] * rectItem->width / 128;
    reg.parallel_edge0_end = flipTrap[dir][frame][P_EDGE_END] * rectItem->width / 128;
    reg.parallel_edge0_pos = flipTrap[dir][frame][P_EDGE_POS] * rectTmp->height / 192;

    reg.trap_distance = flipTrap[dir][frame][TRAP_DIST] * rectTmp->height / 192;
    reg.trape_distance_delta = flipTrap[dir][frame][TRAP_DIST_DELTA];
    reg.trap_gradient0 = flipTrap[dir][frame][TRAP_GRAD0] * rectItem->width / 128;
    reg.trap_gradient1 = flipTrap[dir][frame][TRAP_GRAD1] * rectItem->width / 128;
    reg.abl_const = flipTrap[dir][frame][ABL_CONST];
    #if 0 //Debug
    printf("==========================================\n");
    printf("st : %ld, end : %ld, pos : %ld\n", (S32)reg.parallel_edge0_st, (S32)reg.parallel_edge0_end, (S32)reg.parallel_edge0_pos);
    printf("distance : %ld, distance_delta : %ld, gradient0 : %ld, gradient1 : %ld\n", (S32)reg.trap_distance,
        (S32)reg.trape_distance_delta, (S32)reg.trap_gradient0, (S32)reg.trap_gradient1);
    printf("==========================================\n");
    #endif

    reg.src_fbId = fbId;
    reg.dst_fbId = fbTmp;

    clrrange.color_s.r = 0;
    clrrange.color_s.g = 0;
    clrrange.color_s.b = 0;
    clrrange.color_e.r = 0;
    clrrange.color_e.g = 0;
    clrrange.color_e.b = 0;

    MApi_GFX_SetSrcColorKey(ENABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555, &clrrange.color_s, &clrrange.color_e);
    trapezoid_v_blt(reg);
    MApi_GFX_SetSrcColorKey(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555, NULL, NULL);

}
// dir=0: left, dir=1: right
static void flip_h(U8 dir, S8 step, S8 dstStep, U8 fbFg, U8 fbBg, U8 fbTmp, RECT *rectItem, RECT *rectTmp)
{
    Regset  reg;
    memset(&reg,0,sizeof(Regset));
    int     dst_x0, dst_y0;
    U8      fbId = 0xFF;
    GEColorRange clrrange;

    int     src_width  = (int)rectItem->width;
    int     src_height = (int)rectItem->height;
    int     dst_width  = (int)rectTmp->width;
    int     dst_height = (int)rectTmp->height;

    // calculate parameters for bitblt
    dst_x0 = ((dst_width - src_width) >> 1);
    dst_y0 = ((dst_height - src_height) >> 1);

    //printf("[flip] %d. dst_x0 = %d, dst_y0 = %d\n", step, dst_x0, dst_y0);

    int step2 = (step * 2);

    if(step*2 == dstStep)
        return;

    // trapezoid show current image (front face)
    if(((step*2 < dstStep) && (dir == 1)) || ((step*2 > dstStep) && (dir == 0)))
    {
        if(dir == 1)
            fbId = fbFg;
        else
            fbId = fbBg;
    }
    // trapezoid show next image (back face)
    else
    {
        if(dir == 1)
            fbId = fbBg;
        else
            fbId = fbFg;
    }

    int frame = (step2 > dstStep)? (step - 2) : (step - 1);

    // draw foreground
    reg.trap_dir = 1;         // horizontal
    reg.src_x0 = 0;
    reg.src_y0 = 0;
    reg.src_height = src_height;
    reg.parallel_edge0_st  = flipTrap[dir][frame][P_EDGE_ST] * rectItem->height / 128;
    reg.parallel_edge0_end = flipTrap[dir][frame][P_EDGE_END] * rectItem->height / 128;
    reg.parallel_edge0_pos = flipTrap[dir][frame][P_EDGE_POS] * rectTmp->width / 192;

    reg.trap_distance = flipTrap[dir][frame][TRAP_DIST] * rectTmp->width / 192;
    reg.trape_distance_delta = flipTrap[dir][frame][TRAP_DIST_DELTA];
    reg.trap_gradient0 = flipTrap[dir][frame][TRAP_GRAD0] * rectItem->height / 128;
    reg.trap_gradient1 = flipTrap[dir][frame][TRAP_GRAD1] * rectItem->height / 128;
    reg.abl_const = flipTrap[dir][frame][ABL_CONST];
    #if 0 //Debug
    printf("==========================================\n");
    printf("st : %ld, end : %ld, pos : %ld\n", (S32)reg.parallel_edge0_st, (S32)reg.parallel_edge0_end, (S32)reg.parallel_edge0_pos);
    printf("distance : %ld, distance_delta : %ld, gradient0 : %ld, gradient1 : %ld\n", (S32)reg.trap_distance,
        (S32)reg.trape_distance_delta, (S32)reg.trap_gradient0, (S32)reg.trap_gradient1);
    printf("==========================================\n");
    #endif

    reg.src_fbId = fbId;
    reg.dst_fbId = fbTmp;

    clrrange.color_s.r = 0;
    clrrange.color_s.g = 0;
    clrrange.color_s.b = 0;
    clrrange.color_e.r = 0;
    clrrange.color_e.g = 0;
    clrrange.color_e.b = 0;
    MApi_GFX_SetSrcColorKey(ENABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555, &clrrange.color_s, &clrrange.color_e);
    trapezoid_h_blt(reg);
    MApi_GFX_SetSrcColorKey(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555, NULL, NULL);

}


// hWnd : which wants to do transition effect.
static BOOLEAN _MApp_ZUI_CTL_DynamicTextEffect_Begin(HWND hWnd)
{
    //printf("Effect Begin.\n");
    if(MApp_ZUI_API_IsExistTimer(hWnd, TRANSITION_EFFECT_TIMER_ID))
    {
        //printf("Kill Timer : hWnd(%d) timer:%d\n", hWnd, TRANSITION_EFFECT_TIMER_ID);
        //MApp_ZUI_API_KillTimer(hWnd, TRANSITION_EFFECT_TIMER_ID);
    }
    MApp_ZUI_API_SetTimer(hWnd, TRANSITION_EFFECT_TIMER_ID, TRANSITION_EFFECT_TIMER_MS);
    return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_DynamicTextEffectWinProc
///  Window Proc for "dynamic text with transition effect" control,
///     which dynamic change the content by calling MApp_ZUI_ACT_GetDynamicText()
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/2/6
///////////////////////////////////////////////////////////////////////////////

S32 MApp_ZUI_CTL_DynamicTextEffectWinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_DYNATEXT_EFFECT *pWndData = (GUI_DATA_DYNATEXT_EFFECT*)GETWNDDATA(hWnd);
    GUI_DATA_DYNATEXT_EFFECT_VARDATA * pVar = pWndData->pVarData;
    static BOOLEAN bCloneFg = FALSE;

    //printf("[hWnd:%d] winData addr = 0x%lx, VAR = 0x%lx\n", hWnd, (U32)(pWndData), (U32)(pWndData->pVarData));

    switch(pMsg->message)
    {
        case MSG_NOTIFY_SHOW:
            //printf("MSG_NOTIFY_SHOW\n");
            pVar->dir = EN_EFFECT_DIRECTION_MAX;
            pVar->step = 0;
            break;
        case MSG_EFFECT_DYNATEXT_LEFT:
        case MSG_EFFECT_DYNATEXT_RIGHT:
            //printf("MSG_EFFECT_DYNATEXT(L/R)\n");
            {
                RECT rect;
                MApp_ZUI_API_GetWindowRect(hWnd, &rect);
                pVar->dcFg = MApp_ZUI_API_CreateDC(rect.width, rect.height);
                MApp_ZUI_API_InvalidateWindow(hWnd);
                if(pMsg->message == MSG_EFFECT_DYNATEXT_LEFT)
                {
                    pVar->dir = EN_EFFECT_DIRECTION_LEFT;
                }
                else
                {
                    pVar->dir = EN_EFFECT_DIRECTION_RIGHT;
                }
                pVar->step = pWndData->steps;
                bCloneFg = TRUE;
                _MApp_ZUI_API_WindowProcOnIdle();
            }
            break;
        case MSG_NOTIFY_KEYDOWN:
            //printf("[Dynamic Text effect] key : 0x%lx (hwnd = %d)\n", pMsg->wParam, (U16)hWnd);
            {
                RECT rect;
                MApp_ZUI_API_GetWindowRect(hWnd, &rect);
                pVar->dcFg = MApp_ZUI_API_CreateDC(rect.width, rect.height);
                MApp_ZUI_API_InvalidateWindow(hWnd);
                switch(pMsg->wParam)
                {
                    case VK_UP:
                        pVar->dir = EN_EFFECT_DIRECTION_UP;
                        break;
                    case VK_DOWN:
                        pVar->dir = EN_EFFECT_DIRECTION_DOWN;
                        break;
                    case VK_LEFT:
                        pVar->dir = EN_EFFECT_DIRECTION_LEFT;
                        break;
                    case VK_RIGHT:
                        pVar->dir = EN_EFFECT_DIRECTION_RIGHT;
                        break;
                    default:
                        pVar->dir = EN_EFFECT_DIRECTION_RIGHT;
                        break;
                }
                pVar->step = pWndData->steps;
                bCloneFg = TRUE;
                _MApp_ZUI_API_WindowProcOnIdle();
            }
            break;
        case MSG_PAINT:
            //printf("[Dynamic Text effect] MSG_PAINT\n");
            {
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;
                //DRAWSTYLE * style_list = 0;
                DRAWSTYLE_TYPE ds_type = DS_NORMAL;
                //GRAPHIC_DC *dcScreen = MApp_ZUI_API_GetScreenDC();
                GRAPHIC_DC *dcBackBuf = MApp_ZUI_API_GetBufferDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;
                GOP_GwinFBAttr fbAttr;
                GEBitBltInfo  BitbltInfo;
                GEPitBaseInfo PitBaseInfo;
                RECT rect, rectItem, rectTmp;
                memset(&rect,0,sizeof(RECT));
                GRAPHIC_DC dcBg, dcTmp, dcDst;
                int dst_x0, dst_y0;

                //Calculate effect regions
                MApp_ZUI_API_GetWindowRect(hWnd, &rect);
                rectItem.left = 0;
                rectItem.top = 0;
                rectItem.width = rect.width;
                rectItem.height = rect.height;
                rectTmp.left = rect.left - rect.width/4;
                rectTmp.top = rect.top - rect.height/4;
                rectTmp.width = rect.width + rect.width/2;
                rectTmp.height = rect.height + rect.height/2;
                dst_x0 = ((rectTmp.width - rectItem.width) >> 1);
                dst_y0 = ((rectTmp.height - rectItem.height) >> 1);

                //Create DCs
                dcBg = MApp_ZUI_API_CreateDC(rect.width, rect.height);
                dcTmp = MApp_ZUI_API_CreateDC(rectTmp.width, rectTmp.height);
                dcDst = MApp_ZUI_API_CreateDC(rectTmp.width, rectTmp.height);
                msAPI_OSD_SetClipWindow(0, 0, rectTmp.width-1, rectTmp.height-1);
                PasteFB.fbID=dcTmp.u8FbID;
                PasteFB.x=0;
                PasteFB.y=0;
                PasteFB.width=rectTmp.width;
                PasteFB.height=rectTmp.height;
                CopyFB.fbID=dcBackBuf->u8FbID;
                CopyFB.x=rectTmp.left;
                CopyFB.y=rectTmp.top;
                CopyFB.width=rectTmp.width;
                CopyFB.height=rectTmp.height;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                PasteFB.fbID=dcDst.u8FbID;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                //printf("(%d, %d) w = %d, h = %d\n", param->rect->left, param->rect->top, param->rect->width, param->rect->height);
                //find all static text => dynamic text
                if (param->bIsDisable)
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hWnd);
                    //style_list = GETDISABLEDRAWSTYLE(hWnd);
                    ds_type = DS_DISABLE;
                }
                else if (param->bIsFocus) //the same focus group
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
                    //style_list = GETFOCUSDRAWSTYLE(hWnd);
                    ds_type = DS_FOCUS;
                }
                else
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hWnd);
                    //style_list = GETNORMALDRAWSTYLE(hWnd);
                }

                //if (style_list)
                {
                    //while(style_list->component != CP_NOON)
                    {
                        _MApp_ZUI_API_DefaultOnPaint(hWnd, param, FALSE);
                        //if (style_list->component == CP_TEXT_OUT)
                        {
                            U16 u16TxtComponentIndex = _MApp_ZUI_API_FindFirstComponentIndex(hWnd, ds_type, CP_TEXT_OUT);
                            LPTSTR pStr = MApp_ZUI_ACT_GetDynamicText(hWnd);
                            if (u16TxtComponentIndex != 0xFFFF && pStr)
                            {
                                DRAW_TEXT_OUT_DYNAMIC dyna;
                                //dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                                //if (dyna)
                                {

                                    _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TxtComponentIndex, &dyna);
                                    dyna.pString = pStr;
                                    //_MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, &dyna, &param->dc, param->rect);
                                    //text out to dcBg
                                    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, &dyna, &dcBg, &rectItem);
                                    if(bCloneFg)
                                    {
                                        //printf("Clone Fg\n");
                                        _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, &dyna, &pVar->dcFg, &rectItem);
                                    }
                                    //_ZUI_FREE(dyna);

                                    //Effect doing ...
                                    if(pVar->step > 0)
                                    {
                                        switch(pVar->dir)
                                        {
                                            case EN_EFFECT_DIRECTION_LEFT:
                                                flip_h(0, pVar->step, pWndData->steps, dcBg.u8FbID, pVar->dcFg.u8FbID, dcTmp.u8FbID,
                                                        &rectItem, &rectTmp);
                                                break;
                                            case EN_EFFECT_DIRECTION_RIGHT:
                                                flip_h(1, pVar->step, pWndData->steps, dcBg.u8FbID, pVar->dcFg.u8FbID, dcTmp.u8FbID,
                                                        &rectItem, &rectTmp);
                                                break;
                                            case EN_EFFECT_DIRECTION_UP:
                                                flip_v(0, pVar->step, pWndData->steps, dcBg.u8FbID, pVar->dcFg.u8FbID, dcTmp.u8FbID,
                                                        &rectItem, &rectTmp);
                                                break;
                                            case EN_EFFECT_DIRECTION_DOWN:
                                                flip_v(1, pVar->step, pWndData->steps, dcBg.u8FbID, pVar->dcFg.u8FbID, dcTmp.u8FbID,
                                                        &rectItem, &rectTmp);
                                                break;
                                            default:
                                                flip_h(0, pVar->step, pWndData->steps, dcBg.u8FbID, pVar->dcFg.u8FbID, dcTmp.u8FbID,
                                                        &rectItem, &rectTmp);
                                                break;
                                        }
                                    }
                                    else
                                    {
                                        GEColorRange clrrange;
                                        clrrange.color_s.r = 0;
                                        clrrange.color_s.g = 0;
                                        clrrange.color_s.b = 0;
                                        clrrange.color_e.r = 0;
                                        clrrange.color_e.g = 0;
                                        clrrange.color_e.b = 0;
                                        MApi_GFX_SetSrcColorKey(ENABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555,
                                            &clrrange.color_s, &clrrange.color_e);

                                        msAPI_OSD_SetClipWindow(
                                            (U16)dst_x0,
                                            (U16)dst_y0,
                                            (U16)(dst_x0+rectItem.width-1),
                                            (U16)(dst_y0+rectItem.height-1));
                                        msAPI_OSD_GET_resource();
                                        BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
                                        //src
                                        BitbltInfo.BitbltCoordinate.v2_x = 0;
                                        BitbltInfo.BitbltCoordinate.v2_y = 0;
                                        BitbltInfo.src_width = (U16)rectItem.width;
                                        BitbltInfo.src_height = (U16)rectItem.height;
                                        //dst
                                        BitbltInfo.BitbltCoordinate.v0_x = (U16)dst_x0;
                                        BitbltInfo.BitbltCoordinate.v0_y = (U16)dst_y0;
                                        BitbltInfo.BitbltCoordinate.width = (U16)rectItem.width;
                                        BitbltInfo.BitbltCoordinate.height = (U16)rectItem.height;

                                        MApi_GOP_GWIN_GetFBInfo(dcBg.u8FbID, &fbAttr);
                                        BitbltInfo.src_fm = fbAttr.fbFmt;
                                        PitBaseInfo.sb_base = fbAttr.addr;
                                        PitBaseInfo.sb_pit = fbAttr.pitch;

                                        MApi_GOP_GWIN_GetFBInfo(dcTmp.u8FbID, &fbAttr);
                                        BitbltInfo.dst_fm = fbAttr.fbFmt;
                                        PitBaseInfo.db_base = fbAttr.addr;
                                        PitBaseInfo.db_pit = fbAttr.pitch;

                                        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
                                        msAPI_OSD_Free_resource();

                                        MApi_GFX_SetSrcColorKey(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555, NULL, NULL);
                                    }
                                    msAPI_OSD_SetClipWindow(
                                        rectTmp.left, rectTmp.top,
                                        rectTmp.left + rectTmp.width-1,
                                        rectTmp.top + rectTmp.height-1);
                                    PasteFB.fbID=dcBackBuf->u8FbID;
                                    PasteFB.x=rectTmp.left;
                                    PasteFB.y=rectTmp.top;
                                    PasteFB.width=rectTmp.width;
                                    PasteFB.height=rectTmp.height;
                                    CopyFB.fbID=dcTmp.u8FbID;
                                    CopyFB.x=0;
                                    CopyFB.y=0;
                                    CopyFB.width=rectTmp.width;
                                    CopyFB.height=rectTmp.height;
                                    MApi_GFX_SetAlpha(FALSE, COEF_CONST, ABL_FROM_CONST, 0xff);
                                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                                    if(bCloneFg)
                                    {
                                        bCloneFg = FALSE;
                                        _MApp_ZUI_CTL_DynamicTextEffect_Begin(hWnd);
                                        pVar->step = pWndData->steps;
                                    }
                                    #if 0//test
                                    msAPI_OSD_SetClipWindow(
                                        100, 100,
                                        100 + rectItem.width,
                                        100 + rectItem.height);
                                    PasteFB.fbID=dcScreen->u8FbID;
                                    PasteFB.x=100;
                                    PasteFB.y=100;
                                    PasteFB.width=rectItem.width;
                                    PasteFB.height=rectItem.height;
                                    CopyFB.fbID=pVar->dcFg.u8FbID;
                                    CopyFB.x=0;
                                    CopyFB.y=0;
                                    CopyFB.width=rectItem.width;
                                    CopyFB.height=rectItem.height;
                                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                                    msAPI_OSD_SetClipWindow(
                                        100, 200,
                                        100 + rectItem.width,
                                        200 + rectItem.height);
                                    PasteFB.fbID=dcScreen->u8FbID;
                                    PasteFB.x=100;
                                    PasteFB.y=200;
                                    PasteFB.width=rectItem.width;
                                    PasteFB.height=rectItem.height;
                                    CopyFB.fbID=dcBg.u8FbID;
                                    CopyFB.x=0;
                                    CopyFB.y=0;
                                    CopyFB.width=rectItem.width;
                                    CopyFB.height=rectItem.height;
                                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                                    #endif
                                    //-------------------------------------------------
                                }
                            }
                        }
                        //else
                        //{
                        //    _MApp_ZUI_API_DrawComponent(style_list->component, style_list->u16Index, &param->dc, param->rect);
                        //}
                        //style_list++;
                    }
                }
                //Destroy DC
                MApp_ZUI_API_DeleteDC(dcBg);
                MApp_ZUI_API_DeleteDC(dcTmp);
                MApp_ZUI_API_DeleteDC(dcDst);
            }
            return 0;
        case MSG_TIMER:
        {
            //printf("[MSG_TIMER] [hWnd:%d] Step = %d\n", hWnd, pVar->step);
            pVar->step -= 1;
            if(pVar->step < 0)
            {
                MApp_ZUI_API_KillTimer(hWnd, TRANSITION_EFFECT_TIMER_ID);
                MApp_ZUI_API_DeleteDC(pVar->dcFg);
            }
            else
            {
                MApp_ZUI_API_InvalidateWindow(hWnd);
            }
        }
        break;
        default:
            break;

    }
    return DEFAULTWINPROC(hWnd, pMsg);
}
#undef MAPP_ZUI_CTL_DYNATEXT_EFFECT_C

