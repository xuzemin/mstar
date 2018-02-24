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

#define MAPP_ZUI_CTL_EFFECTFLIP_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "string.h"
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_CTLeffectflip.h"

#define FRAMES              16

#define P_EDGE_ST           0
#define P_EDGE_END          1
#define P_EDGE_POS          2
#define TRAP_DIST           3
#define TRAP_DIST_DELTA     4
#define TRAP_GRAD0          5
#define TRAP_GRAD1          6
#define ABL_CONST           7

#define bitShift            14
#define FixShift            (1 << bitShift)

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

} Regset;

//parallel_edge0_st, parallel_edge0_end, parallel_edge0_pos, trap_distance, trape_distance_delta, trap_gradient0, trap_gradient1, abl_const
float flipTrap[2][14][8] = {
{
    {40.000000, 159.000000, 44.000000, 112.000000, 1.142857, -0.071429, 0.071429, 0.937500},
    {44.000000, 155.000000, 52.000000, 96.000000, 1.333333, -0.166667, 0.166667, 0.875000},
    {48.000000, 151.000000, 60.000000, 80.000000, 1.600000, -0.300000, 0.300000, 0.812500},
    {52.000000, 147.000000, 68.000000, 64.000000, 2.000000, -0.500000, 0.500000, 0.750000},
    {56.000000, 143.000000, 76.000000, 48.000000, 2.666667, -0.833333, 0.833333, 0.687500},
    {60.000000, 139.000000, 84.000000, 32.000000, 4.000000, -1.500000, 1.500000, 0.625000},
    {64.000000, 135.000000, 92.000000, 16.000000, 8.000000, -3.500000, 3.500000, 0.562500},
    {8.000000, 191.000000, 92.000000, 16.000000, 8.000000, 3.500000, -3.500000, 0.562500},
    {12.000000, 187.000000, 84.000000, 32.000000, 4.000000, 1.500000, -1.500000, 0.625000},
    {16.000000, 183.000000, 76.000000, 48.000000, 2.666667, 0.833333, -0.833333, 0.687500},
    {20.000000, 179.000000, 68.000000, 64.000000, 2.000000, 0.500000, -0.500000, 0.750000},
    {24.000000, 175.000000, 60.000000, 80.000000, 1.600000, 0.300000, -0.300000, 0.812500},
    {28.000000, 171.000000, 52.000000, 96.000000, 1.333333, 0.166667, -0.166667, 0.875000},
    {32.000000, 167.000000, 44.000000, 112.000000, 1.142857, 0.071429, -0.071429, 0.937500},
},
{
    {32.000000, 167.000000, 44.000000, 112.000000, 1.142857, 0.071429, -0.071429, 0.937500},
    {28.000000, 171.000000, 52.000000, 96.000000, 1.333333, 0.166667, -0.166667, 0.875000},
    {24.000000, 175.000000, 60.000000, 80.000000, 1.600000, 0.300000, -0.300000, 0.812500},
    {20.000000, 179.000000, 68.000000, 64.000000, 2.000000, 0.500000, -0.500000, 0.750000},
    {16.000000, 183.000000, 76.000000, 48.000000, 2.666667, 0.833333, -0.833333, 0.687500},
    {12.000000, 187.000000, 84.000000, 32.000000, 4.000000, 1.500000, -1.500000, 0.625000},
    {8.000000, 191.000000, 92.000000, 16.000000, 8.000000, 3.500000, -3.500000, 0.562500},
    {64.000000, 135.000000, 90.000000, 16.000000, 8.000000, -3.500000, 3.500000, 0.562500},
    {60.000000, 139.000000, 84.000000, 32.000000, 4.000000, -1.500000, 1.500000, 0.625000},
    {56.000000, 141.000000, 76.000000, 48.000000, 2.666667, -0.833333, 0.833333, 0.687500},
    {52.000000, 147.000000, 68.000000, 64.000000, 2.000000, -0.500000, 0.500000, 0.750000},
    {48.000000, 151.000000, 60.000000, 80.000000, 1.600000, -0.300000, 0.300000, 0.812500},
    {44.000000, 155.000000, 52.000000, 96.000000, 1.333333, -0.166667, 0.166667, 0.875000},
    {40.000000, 159.000000, 44.000000, 112.000000, 1.142857, -0.071429, 0.071429, 0.937500},
},
};

static void trapezoid_h_blt(GRAPHIC_DC *pdstDC, GRAPHIC_DC *psrcDC, Regset _reg)
{
    int   x, lines,  idst_y0, idst_y1;
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
    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);

    GOP_GwinFBAttr fbAttr;
    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    MApi_GOP_GWIN_GetFBInfo(psrcDC->u8FbID, &fbAttr);
    BitbltInfo.src_fm = fbAttr.fbFmt;
    PitBaseInfo.sb_base = fbAttr.addr;
    PitBaseInfo.sb_pit = fbAttr.pitch;

    MApi_GOP_GWIN_GetFBInfo(pdstDC->u8FbID, &fbAttr);
    BitbltInfo.dst_fm = fbAttr.fbFmt;
    PitBaseInfo.db_base = fbAttr.addr;
    PitBaseInfo.db_pit = fbAttr.pitch;

    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;

    msAPI_OSD_SetClipWindow(0, 0, fbAttr.width-1, fbAttr.height-1);

    for(x=(int)_reg.parallel_edge0_pos, lines=0; lines<(int)_reg.trap_distance; ++lines, ++x)
    {
        idst_y0 = (_fix_line_st >> bitShift);
        idst_y1 = (_fix_line_end >> bitShift);

        isrc_x = (_fix_src_x + (FixShift>>1)) >> bitShift;
        isrc_y = (_fix_src_y + (FixShift>>1)) >> bitShift;

        //src
        BitbltInfo.BitbltCoordinate.v2_x = (U16)isrc_x;
        BitbltInfo.BitbltCoordinate.v2_y = (U16)isrc_y;
        BitbltInfo.src_width = (U16)(_reg.trape_distance_delta);
        BitbltInfo.src_height = (U16)(_reg.src_height);

        //dst
        BitbltInfo.BitbltCoordinate.v0_x = (U16)x;
        BitbltInfo.BitbltCoordinate.v0_y = (U16)idst_y0;
        BitbltInfo.BitbltCoordinate.width = (U16)(1);
        BitbltInfo.BitbltCoordinate.height = (U16)(idst_y1 - idst_y0 + 1);

        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);

        _fix_src_x    += _fix_dist_delta;
        _fix_line_st  += _fix_grad0;
        _fix_line_end += _fix_grad1;
    }

    MDrv_GE_EnableAlphaBlending(FALSE);

}

static void trapezoid_v_blt(GRAPHIC_DC *pdstDC, GRAPHIC_DC *psrcDC, Regset _reg)
{
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
    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);

    GOP_GwinFBAttr fbAttr;
    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    MApi_GOP_GWIN_GetFBInfo(psrcDC->u8FbID, &fbAttr);
    BitbltInfo.src_fm = fbAttr.fbFmt;
    PitBaseInfo.sb_base = fbAttr.addr;
    PitBaseInfo.sb_pit = fbAttr.pitch;

    MApi_GOP_GWIN_GetFBInfo(pdstDC->u8FbID, &fbAttr);
    BitbltInfo.dst_fm = fbAttr.fbFmt;
    PitBaseInfo.db_base = fbAttr.addr;
    PitBaseInfo.db_pit = fbAttr.pitch;

    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;

    msAPI_OSD_SetClipWindow(0, 0, fbAttr.width-1, fbAttr.height-1);

    for(y=(int)_reg.parallel_edge0_pos, lines=0; lines<(int)_reg.trap_distance; ++lines, ++y)
    {
        idst_x0 = (_fix_line_st >> bitShift);
        idst_x1 = (_fix_line_end >> bitShift);

        isrc_x = (_fix_src_x + (FixShift>>1)) >> bitShift;
        isrc_y = (_fix_src_y + (FixShift>>1)) >> bitShift;

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

        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);

        _fix_src_y    += _fix_dist_delta;
        _fix_line_st  += _fix_grad0;
        _fix_line_end += _fix_grad1;
    }

    MDrv_GE_EnableAlphaBlending(FALSE);

}

// dir=0(left), dir=1(right)
static void draw_hflip(int left, int top, GRAPHIC_DC *pdstDC, GRAPHIC_DC *pfrontsrcDC, GRAPHIC_DC *pbacksrcDC, int dir, int step)
{
    GRAPHIC_DC *psrcDC;

    int step2 = (step * 2);

    if(step2 == FRAMES)
        return;

    // trapezoid show current image (front face)
    if(((step*2 < FRAMES) && (dir == 1)) || ((step*2 > FRAMES) && (dir == 0)))
    {
        if(dir == 1)
            psrcDC = pfrontsrcDC;
        else
            psrcDC = pbacksrcDC;
    }
    // trapezoid show next image (back face)
    else
    {
        if(dir == 1)
            psrcDC = pbacksrcDC;
        else
            psrcDC = pfrontsrcDC;
    }

    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(pfrontsrcDC->u8FbID, &fbAttr);
    int src_width = (int)fbAttr.width;
    int src_height = (int)fbAttr.height;

    // draw 1st or final step
    if(step == 0 || step == FRAMES)
    {
        int alpha = (int)(255.0f * 1);
        MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);

        MSAPI_OSDRegion CopyFB;
        MSAPI_OSDRegion PasteFB;

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(left, top, left+src_width-1, top+src_height-1);

        PasteFB.fbID=pdstDC->u8FbID;
        PasteFB.x=left;
        PasteFB.y=top;
        PasteFB.width=src_width;
        PasteFB.height=src_height;

        CopyFB.fbID=(step == 0)?pfrontsrcDC->u8FbID:pbacksrcDC->u8FbID;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=src_width;
        CopyFB.height=src_height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        MDrv_GE_EnableAlphaBlending(FALSE);
        return;
    }

#if 0
    {
        Regset reg;
        // draw foreground
        int frame = (step2 > FRAMES)? (step - 2) : (step - 1);
        reg.trap_dir = 1;         // horizontal
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (flipTrap[dir][frame][P_EDGE_ST]-36)*src_height/128+top;
        reg.parallel_edge0_end = (flipTrap[dir][frame][P_EDGE_END]-36)*src_height/128+top;
        reg.parallel_edge0_pos = (flipTrap[dir][frame][P_EDGE_POS]-36)*src_width/128+left;
        reg.trap_distance = flipTrap[dir][frame][TRAP_DIST]*src_width/128;
        reg.trape_distance_delta = flipTrap[dir][frame][TRAP_DIST_DELTA];
        reg.trap_gradient0 = flipTrap[dir][frame][TRAP_GRAD0]*src_height/src_width;
        reg.trap_gradient1 = flipTrap[dir][frame][TRAP_GRAD1]*src_height/src_width;
        reg.abl_const = flipTrap[dir][frame][ABL_CONST];
        trapezoid_h_blt(pdstDC, psrcDC, reg);
    }
#else
    {
        float   delta, scale_h, scale_w_long, scale_w_short, h, w_long, w_short;
        float   intensity;
        float   trap_edge_gradient;
        int     trap_parallel0_length, trap_parallel1_length, trap_distance;
        int     parallel_edge0_st, parallel_edge0_pos, parallel_edge0_end;
        int     step_tmp, step_countdown;

        // calculate parameters for Trapezoid
        delta = 1.0f / (float)FRAMES;

        if(dir == 1)
            step_tmp = step;
        else
            step_tmp = FRAMES - step;

        // trapezoid show current image (front face)
        if(((step*2 < FRAMES) && (dir == 1)) || ((step*2 > FRAMES) && (dir == 0)))
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
            intensity = 1.0f - ((float)step_tmp*2 / FRAMES);
        }
        // trapezoid show next image (back face)
        else
        {
            step_countdown = FRAMES - step_tmp;

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
            intensity = 1.0f - ((float)step_countdown*2 / FRAMES);
        }
        parallel_edge0_st = top - ((trap_parallel0_length - src_height)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel0_length - 1;
        parallel_edge0_pos = left + (src_width - trap_distance) / 2;

        Regset reg;
        memset(&reg,0,sizeof(Regset));
        // draw
        reg.trap_dir = 1;         // horizontal
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (float)parallel_edge0_st;
        reg.parallel_edge0_end = (float)parallel_edge0_end;
        reg.parallel_edge0_pos = (float)parallel_edge0_pos;
        reg.trap_distance = (float)trap_distance;
        reg.trape_distance_delta = (float)src_width / (float)trap_distance;
        reg.trap_gradient0 = trap_edge_gradient;
        reg.trap_gradient1 = -trap_edge_gradient;
        reg.abl_const = intensity;
        trapezoid_h_blt(pdstDC, psrcDC, reg);
    }
#endif
}


// dir=0(up), dir=1(down)
static void draw_vflip(int left, int top, GRAPHIC_DC *pdstDC, GRAPHIC_DC *pfrontsrcDC, GRAPHIC_DC *pbacksrcDC, int dir, int step)
{
    GRAPHIC_DC *psrcDC;

    int step2 = (step * 2);

    if(step2 == FRAMES)
        return;

    // trapezoid show current image (front face)
    if(((step2 < FRAMES) && (dir == 1)) || ((step2 > FRAMES) && (dir == 0)))
    {
        if(dir == 1)
            psrcDC = pfrontsrcDC;
        else
            psrcDC = pbacksrcDC;
    }
    // trapezoid show next image (back face)
    else
    {
        if(dir == 1)
            psrcDC = pbacksrcDC;
        else
            psrcDC = pfrontsrcDC;
    }

    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(pfrontsrcDC->u8FbID, &fbAttr);
    int src_width = (int)fbAttr.width;
    int src_height = (int)fbAttr.height;

    // draw 1st or final step
    if(step == 0 || step == FRAMES)
    {
        int alpha = (int)(255.0f * 1);
        MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);

        MSAPI_OSDRegion CopyFB;
        MSAPI_OSDRegion PasteFB;

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(left, top, left+src_width-1, top+src_height-1);

        PasteFB.fbID=pdstDC->u8FbID;
        PasteFB.x=left;
        PasteFB.y=top;
        PasteFB.width=src_width;
        PasteFB.height=src_height;

        CopyFB.fbID=(step == 0)?pfrontsrcDC->u8FbID:pbacksrcDC->u8FbID;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=src_width;
        CopyFB.height=src_height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        MDrv_GE_EnableAlphaBlending(FALSE);
        return;
    }

#if 0
    {
        Regset reg;
        // draw
        int frame = (step2 > FRAMES)? (step - 2) : (step - 1);
        reg.trap_dir = 0;         // vertical
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (flipTrap[dir][frame][P_EDGE_ST]-36)*src_width/128+left;
        reg.parallel_edge0_end = (flipTrap[dir][frame][P_EDGE_END]-36)*src_width/128+left;
        reg.parallel_edge0_pos = (flipTrap[dir][frame][P_EDGE_POS]-36)*src_height/128+top;
        reg.trap_distance = flipTrap[dir][frame][TRAP_DIST]*src_height/128;
        reg.trape_distance_delta = flipTrap[dir][frame][TRAP_DIST_DELTA];
        reg.trap_gradient0 = flipTrap[dir][frame][TRAP_GRAD0]*src_width/src_height;
        reg.trap_gradient1 = flipTrap[dir][frame][TRAP_GRAD1]*src_width/src_height;
        reg.abl_const = flipTrap[dir][frame][ABL_CONST];
        trapezoid_v_blt(pdstDC, psrcDC, reg);
    }
#else
    {
        float   delta, scale_h, scale_w_long, scale_w_short, h, w_long, w_short;
        float   intensity;
        float   trap_edge_gradient;
        int     trap_parallel0_length, trap_parallel1_length, trap_distance;
        int     parallel_edge0_st, parallel_edge0_pos, parallel_edge0_end;
        int     step_tmp, step_countdown;

        // calculate parameters for Trapezoid
        delta = 1.0f / (float)FRAMES;

        if(dir == 1)
            step_tmp = step;
        else
            step_tmp = FRAMES - step;

        // trapezoid show current image (front face)
        if(((step*2 < FRAMES) && (dir == 1)) || ((step*2 > FRAMES) && (dir == 0)))
        {
            scale_h = 1.0f - (step_tmp * delta * 2);
            scale_w_long = 1.0f + (step_tmp * delta);
            scale_w_short = 1.0f - (step_tmp * delta);
            h = src_height * scale_h;
            w_long = src_width * scale_w_long;
            w_short = src_width * scale_w_short;
            trap_distance = (int)(h + 0.5f);
            trap_parallel0_length = (int)(w_long + 0.5f);
            trap_parallel1_length = (int)(w_short + 0.5f);
            trap_edge_gradient = (float)((trap_parallel0_length - trap_parallel1_length) >>1 ) / trap_distance;
            intensity = 1.0f - ((float)step_tmp*2 / FRAMES);
        }
        // trapezoid show next image (back face)
        else
        {
            step_countdown = FRAMES - step_tmp;

            scale_h = 1.0f - (step_countdown * delta * 2);
            scale_w_long = 1.0f + (step_countdown * delta);
            scale_w_short = 1.0f - (step_countdown * delta);
            h = src_height * scale_h;
            w_long = src_width * scale_w_long;
            w_short = src_width * scale_w_short;
            trap_distance = (int)(h + 0.5f);
            trap_parallel0_length = (int)(w_short + 0.5f);
            trap_parallel1_length = (int)(w_long + 0.5f);
            trap_edge_gradient = (float)((trap_parallel0_length - trap_parallel1_length) >>1 ) / trap_distance;
            intensity = 1.0f - ((float)step_countdown*2 / FRAMES);
        }
        parallel_edge0_st = left - ((trap_parallel0_length - src_width)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel0_length - 1;
        parallel_edge0_pos = top + (src_height - trap_distance) / 2;

        Regset reg;
        memset(&reg,0,sizeof(Regset));
        // draw
        reg.trap_dir = 0;         // vertical
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (float)parallel_edge0_st;
        reg.parallel_edge0_end = (float)parallel_edge0_end;
        reg.parallel_edge0_pos = (float)parallel_edge0_pos;
        reg.trap_distance = (float)trap_distance;
        reg.trape_distance_delta = (float)src_height / (float)trap_distance;
        reg.trap_gradient0 = trap_edge_gradient;
        reg.trap_gradient1 = -trap_edge_gradient;
        reg.abl_const = intensity;
        trapezoid_v_blt(pdstDC, psrcDC, reg);
    }
#endif
}

static void _MApp_ZUI_CTL_Effect_HFlip(HWND bghWnd, HWND frontsrchWnd, HWND backsrchWnd, int dir, U32 ms)
{
    RECT bgrect;
    memset(&bgrect,0,sizeof(RECT));
    RECT srcrect;
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC bgDC;
    GRAPHIC_DC frontsrcDC;
    GRAPHIC_DC backsrcDC;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    bgDC = MApp_ZUI_API_CreateDC(bgrect.width, bgrect.height);
    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(bgDC.u8FbID, &fbAttr);

    MApp_ZUI_API_GetWindowRect(frontsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    frontsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&frontsrcDC, &srcrect, GETNORMALDRAWSTYLE(frontsrchWnd));

    MApp_ZUI_API_GetWindowRect(backsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    backsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&backsrcDC, &srcrect, GETNORMALDRAWSTYLE(backsrchWnd));

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    MApp_ZUI_API_GetWindowRect(frontsrchWnd, &srcrect);

    int left = srcrect.left-bgrect.left;
    int top = srcrect.top-bgrect.top;

    int step;
    for (step=0; step<=FRAMES; step++)
    {
        MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

        draw_hflip(left, top, &bgDC, &frontsrcDC, &backsrcDC, dir, step);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(bgrect.left, bgrect.top, 
        bgrect.left+bgrect.width-1, bgrect.top+bgrect.height-1);

        PasteFB.fbID=pBuffDC->u8FbID;
        PasteFB.x=bgrect.left;
        PasteFB.y=bgrect.top;
        PasteFB.width=bgrect.width;
        PasteFB.height=bgrect.height;

        CopyFB.fbID=bgDC.u8FbID;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=bgrect.width;
        CopyFB.height=bgrect.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(bgrect.left, bgrect.top, 
        bgrect.left+bgrect.width-1, bgrect.top+bgrect.height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=bgrect.left;
        PasteFB.y=bgrect.top;
        PasteFB.width=bgrect.width;
        PasteFB.height=bgrect.height;

        CopyFB.fbID=pBuffDC->u8FbID;
        CopyFB.x=bgrect.left;
        CopyFB.y=bgrect.top;
        CopyFB.width=bgrect.width;
        CopyFB.height=bgrect.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }

    MApp_ZUI_API_DeleteDC(bgDC);
    MApp_ZUI_API_DeleteDC(frontsrcDC);
    MApp_ZUI_API_DeleteDC(backsrcDC);

}

static void _MApp_ZUI_CTL_Effect_VFlip(HWND bghWnd, HWND frontsrchWnd, HWND backsrchWnd, int dir, U32 ms)
{
    RECT bgrect;
    memset(&bgrect,0,sizeof(RECT));
    RECT srcrect;
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC bgDC;
    GRAPHIC_DC frontsrcDC;
    GRAPHIC_DC backsrcDC;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    bgDC = MApp_ZUI_API_CreateDC(bgrect.width, bgrect.height);
    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(bgDC.u8FbID, &fbAttr);

    MApp_ZUI_API_GetWindowRect(frontsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    frontsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&frontsrcDC, &srcrect, GETNORMALDRAWSTYLE(frontsrchWnd));

    MApp_ZUI_API_GetWindowRect(backsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    backsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&backsrcDC, &srcrect, GETNORMALDRAWSTYLE(backsrchWnd));

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    MApp_ZUI_API_GetWindowRect(frontsrchWnd, &srcrect);

    int left = srcrect.left-bgrect.left;
    int top = srcrect.top-bgrect.top;

    int step;
    for (step=0; step<=FRAMES; step++)
    {
        MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

        draw_vflip(left, top, &bgDC, &frontsrcDC, &backsrcDC, dir, step);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(bgrect.left, bgrect.top, 
        bgrect.left+bgrect.width-1, bgrect.top+bgrect.height-1);

        PasteFB.fbID=pBuffDC->u8FbID;
        PasteFB.x=bgrect.left;
        PasteFB.y=bgrect.top;
        PasteFB.width=bgrect.width;
        PasteFB.height=bgrect.height;

        CopyFB.fbID=bgDC.u8FbID;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=bgrect.width;
        CopyFB.height=bgrect.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(bgrect.left, bgrect.top, 
        bgrect.left+bgrect.width-1, bgrect.top+bgrect.height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=bgrect.left;
        PasteFB.y=bgrect.top;
        PasteFB.width=bgrect.width;
        PasteFB.height=bgrect.height;

        CopyFB.fbID=pBuffDC->u8FbID;
        CopyFB.x=bgrect.left;
        CopyFB.y=bgrect.top;
        CopyFB.width=bgrect.width;
        CopyFB.height=bgrect.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }

    MApp_ZUI_API_DeleteDC(bgDC);
    MApp_ZUI_API_DeleteDC(frontsrcDC);
    MApp_ZUI_API_DeleteDC(backsrcDC);

}

static void _MApp_ZUI_CTL_Effect_DefalutFlip(HWND bghWnd, HWND srchWnd)
{
    RECT bgrect;
    memset(&bgrect,0,sizeof(RECT));
    RECT srcrect;
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC bgDC;
    GRAPHIC_DC srcDC;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    bgDC = MApp_ZUI_API_CreateDC(bgrect.width, bgrect.height);

    MApp_ZUI_API_GetWindowRect(srchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    srcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&srcDC, &srcrect, GETNORMALDRAWSTYLE(srchWnd));

    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(bgDC.u8FbID, &fbAttr);
    MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    //we MUST reset clip window before msAPI_OSD_CopyRegion()
    msAPI_OSD_SetClipWindow(0, 0, bgrect.width-1, bgrect.height-1);

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    MApp_ZUI_API_GetWindowRect(srchWnd, &srcrect);

    PasteFB.fbID=bgDC.u8FbID;
    PasteFB.x=srcrect.left-bgrect.left;
    PasteFB.y=srcrect.top-bgrect.top;
    PasteFB.width=srcrect.width;
    PasteFB.height=srcrect.height;

    CopyFB.fbID=srcDC.u8FbID;
    CopyFB.x=0;
    CopyFB.y=0;
    CopyFB.width=srcrect.width;
    CopyFB.height=srcrect.height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    //we MUST reset clip window before msAPI_OSD_CopyRegion()
    msAPI_OSD_SetClipWindow(bgrect.left, bgrect.top, bgrect.left+bgrect.width-1, bgrect.top+bgrect.height-1);

    PasteFB.fbID=pBuffDC->u8FbID;
    PasteFB.x=bgrect.left;
    PasteFB.y=bgrect.top;
    PasteFB.width=bgrect.width;
    PasteFB.height=bgrect.height;

    CopyFB.fbID=bgDC.u8FbID;
    CopyFB.x=0;
    CopyFB.y=0;
    CopyFB.width=bgrect.width;
    CopyFB.height=bgrect.height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    msAPI_OSD_SetClipWindow(bgrect.left, bgrect.top, bgrect.left+bgrect.width-1, bgrect.top+bgrect.height-1);

    PasteFB.fbID=pScrnDC->u8FbID;
    PasteFB.x=bgrect.left;
    PasteFB.y=bgrect.top;
    PasteFB.width=bgrect.width;
    PasteFB.height=bgrect.height;

    CopyFB.fbID=pBuffDC->u8FbID;
    CopyFB.x=bgrect.left;
    CopyFB.y=bgrect.top;
    CopyFB.width=bgrect.width;
    CopyFB.height=bgrect.height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    MApp_ZUI_API_DeleteDC(bgDC);
    MApp_ZUI_API_DeleteDC(srcDC);

}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_EffectFlipWinProc
///  Window Proc for "effect Flip" control
///
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/3/5
///////////////////////////////////////////////////////////////////////////////
#define HDELAY               4  //ms
#define VDELAY               10  //ms

S32 MApp_ZUI_CTL_EffectFlipItemWinProc(HWND hWnd, PMSG pMsg)
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

S32 MApp_ZUI_CTL_EffectFlipWinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_FLIP_EFFECT *pWndData = (GUI_DATA_FLIP_EFFECT*)GETWNDDATA(hWnd);

  #if 0
    GUI_DATA_FLIP_EFFECT_VARDATA * pVar = pWndData->pVarData;

    //no dynamic list setting data...
    if (pWndData == 0 || pWndData->pVarData == 0)
        return DEFAULTWINPROC(hWnd, pMsg);
  #else // Modifed it by coverity_0540
    GUI_DATA_FLIP_EFFECT_VARDATA * pVar = NULL;
    if (pWndData != NULL)
    {
        pVar = pWndData->pVarData;
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
                pVar->dir = EN_EFFECT_FLIP_CREATE;
            }
            return 0;

        case MSG_NOTIFY_KEYDOWN:
            {
                switch(pMsg->wParam)
                {
                    case VK_UP:
                        pVar->dir = EN_EFFECT_FLIP_UP;
                        break;
                    case VK_DOWN:
                        pVar->dir = EN_EFFECT_FLIP_DOWN;
                        break;
                    case VK_LEFT:
                        pVar->dir = EN_EFFECT_FLIP_LEFT;
                        break;
                    case VK_RIGHT:
                        pVar->dir = EN_EFFECT_FLIP_RIGHT;
                        break;
                    default:
                        pVar->dir = EN_EFFECT_FLIP_CREATE;
                        break;
                }
                MApp_ZUI_API_SetTimer(hWnd, 0, 2);
            }
            return 0;

        case MSG_TIMER:
            {
                MApp_ZUI_API_KillTimer(hWnd, 0);
                MApp_ZUI_API_InvalidateWindow(hWnd);
            }
            break;

        case MSG_PAINT:
            {
                if ( pVar->dir == EN_EFFECT_FLIP_CREATE )
                {
                    HWND srchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_DefalutFlip(hWnd, srchWnd);
                }
                else if ( pVar->dir == EN_EFFECT_FLIP_UP )
                {
                    HWND frontsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(frontsrchWnd, NAV_DOWN);
                    HWND backsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_VFlip(hWnd, frontsrchWnd, backsrchWnd, 0,  VDELAY);
                }
                else if ( pVar->dir == EN_EFFECT_FLIP_DOWN )
                {
                    HWND frontsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(frontsrchWnd, NAV_UP);
                    HWND backsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_VFlip(hWnd, frontsrchWnd, backsrchWnd, 1,  VDELAY);
                }
                else if ( pVar->dir == EN_EFFECT_FLIP_LEFT )
                {
                    HWND frontsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(frontsrchWnd, NAV_RIGHT);
                    HWND backsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_HFlip(hWnd, frontsrchWnd, backsrchWnd, 0,  HDELAY);
                }
                else if ( pVar->dir == EN_EFFECT_FLIP_RIGHT )
                {
                    HWND frontsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(frontsrchWnd, NAV_LEFT);
                    HWND backsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_HFlip(hWnd, frontsrchWnd, backsrchWnd, 1,  HDELAY);
                }

                pVar->dir = EN_EFFECT_FLIP_NONE;
            }
            return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_EFFECTFLIP_C
