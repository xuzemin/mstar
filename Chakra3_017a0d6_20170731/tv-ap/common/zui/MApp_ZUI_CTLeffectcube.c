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

#define MAPP_ZUI_CTL_EFFECTCUBE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <math.h>
#include "string.h"
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_CTLeffectcube.h"

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
float cubeTrap[2][30][8] = {
{
    {36.000000, 162.000000, 35.000000, 121.000000, 1.057851, -0.008264, 0.008264, 0.937500},
    {36.000000, 164.000000, 156.000000, 8.000000, 16.000000, 1.000000, -1.000000, 0.062500},
    {37.000000, 162.000000, 34.000000, 114.000000, 1.122807, -0.017544, 0.017544, 0.875000},
    {35.000000, 164.000000, 148.000000, 17.000000, 7.529412, 0.470588, -0.470588, 0.125000},
    {37.000000, 161.000000, 33.000000, 107.000000, 1.196262, -0.028037, 0.028037, 0.812500},
    {35.000000, 165.000000, 140.000000, 26.000000, 4.923077, 0.307692, -0.307692, 0.187500},
    {38.000000, 161.000000, 32.000000, 100.000000, 1.280000, -0.040000, 0.040000, 0.750000},
    {34.000000, 165.000000, 132.000000, 35.000000, 3.657143, 0.228571, -0.228571, 0.250000},
    {38.000000, 160.000000, 31.000000, 93.000000, 1.376344, -0.053763, 0.053763, 0.687500},
    {34.000000, 166.000000, 124.000000, 44.000000, 2.909091, 0.181818, -0.181818, 0.312500},
    {39.000000, 160.000000, 30.000000, 86.000000, 1.488372, -0.069767, 0.069767, 0.625000},
    {33.000000, 166.000000, 116.000000, 53.000000, 2.415094, 0.150943, -0.150943, 0.375000},
    {39.000000, 159.000000, 29.000000, 79.000000, 1.620253, -0.088608, 0.088608, 0.562500},
    {33.000000, 167.000000, 108.000000, 62.000000, 2.064516, 0.129032, -0.129032, 0.437500},
    {40.000000, 159.000000, 28.000000, 72.000000, 1.777778, -0.111111, 0.111111, 0.500000},
    {32.000000, 167.000000, 100.000000, 71.000000, 1.802817, 0.112676, -0.112676, 0.500000},
    {40.000000, 158.000000, 29.000000, 63.000000, 2.031746, -0.126984, 0.126984, 0.437500},
    {33.000000, 167.000000, 92.000000, 78.000000, 1.641026, 0.089744, -0.089744, 0.562500},
    {41.000000, 158.000000, 30.000000, 54.000000, 2.370370, -0.148148, 0.148148, 0.375000},
    {33.000000, 166.000000, 84.000000, 85.000000, 1.505882, 0.070588, -0.070588, 0.625000},
    {41.000000, 157.000000, 31.000000, 45.000000, 2.844445, -0.177778, 0.177778, 0.312500},
    {34.000000, 166.000000, 76.000000, 92.000000, 1.391304, 0.054348, -0.054348, 0.687500},
    {42.000000, 157.000000, 32.000000, 36.000000, 3.555556, -0.222222, 0.222222, 0.250000},
    {34.000000, 165.000000, 68.000000, 99.000000, 1.292929, 0.040404, -0.040404, 0.750000},
    {42.000000, 156.000000, 33.000000, 27.000000, 4.740741, -0.296296, 0.296296, 0.187500},
    {35.000000, 165.000000, 60.000000, 106.000000, 1.207547, 0.028302, -0.028302, 0.812500},
    {43.000000, 156.000000, 34.000000, 18.000000, 7.111111, -0.444444, 0.444444, 0.125000},
    {35.000000, 164.000000, 52.000000, 113.000000, 1.132743, 0.017699, -0.017699, 0.875000},
    {43.000000, 155.000000, 35.000000, 9.000000, 14.222222, -0.888889, 0.888889, 0.062500},
    {37.000000, 164.000000, 44.000000, 120.000000, 1.066667, 0.008333, -0.008333, 0.937500},
},
{
    {43.000000, 155.000000, 35.000000, 9.000000, 14.222222, -0.888889, 0.888889, 0.062500},
    {36.000000, 164.000000, 44.000000, 120.000000, 1.066667, 0.008333, -0.008333, 0.937500},
    {43.000000, 156.000000, 34.000000, 18.000000, 7.111111, -0.444444, 0.444444, 0.125000},
    {35.000000, 164.000000, 52.000000, 113.000000, 1.132743, 0.017699, -0.017699, 0.875000},
    {42.000000, 156.000000, 33.000000, 27.000000, 4.740741, -0.296296, 0.296296, 0.187500},
    {35.000000, 165.000000, 60.000000, 106.000000, 1.207547, 0.028302, -0.028302, 0.812500},
    {42.000000, 157.000000, 32.000000, 36.000000, 3.555556, -0.222222, 0.222222, 0.250000},
    {34.000000, 165.000000, 68.000000, 99.000000, 1.292929, 0.040404, -0.040404, 0.750000},
    {41.000000, 157.000000, 31.000000, 45.000000, 2.844445, -0.177778, 0.177778, 0.312500},
    {34.000000, 166.000000, 76.000000, 92.000000, 1.391304, 0.054348, -0.054348, 0.687500},
    {41.000000, 158.000000, 30.000000, 54.000000, 2.370370, -0.148148, 0.148148, 0.375000},
    {33.000000, 166.000000, 84.000000, 85.000000, 1.505882, 0.070588, -0.070588, 0.625000},
    {40.000000, 158.000000, 29.000000, 63.000000, 2.031746, -0.126984, 0.126984, 0.437500},
    {33.000000, 167.000000, 92.000000, 78.000000, 1.641026, 0.089744, -0.089744, 0.562500},
    {40.000000, 159.000000, 28.000000, 72.000000, 1.777778, -0.111111, 0.111111, 0.500000},
    {32.000000, 167.000000, 100.000000, 71.000000, 1.802817, 0.112676, -0.112676, 0.500000},
    {39.000000, 159.000000, 29.000000, 79.000000, 1.620253, -0.088608, 0.088608, 0.562500},
    {33.000000, 167.000000, 108.000000, 62.000000, 2.064516, 0.129032, -0.129032, 0.437500},
    {39.000000, 160.000000, 30.000000, 86.000000, 1.488372, -0.069767, 0.069767, 0.625000},
    {33.000000, 166.000000, 116.000000, 53.000000, 2.415094, 0.150943, -0.150943, 0.375000},
    {38.000000, 160.000000, 31.000000, 93.000000, 1.376344, -0.053763, 0.053763, 0.687500},
    {34.000000, 166.000000, 124.000000, 44.000000, 2.909091, 0.181818, -0.181818, 0.312500},
    {38.000000, 161.000000, 32.000000, 100.000000, 1.280000, -0.040000, 0.040000, 0.750000},
    {34.000000, 165.000000, 132.000000, 35.000000, 3.657143, 0.228571, -0.228571, 0.250000},
    {37.000000, 161.000000, 33.000000, 107.000000, 1.196262, -0.028037, 0.028037, 0.812500},
    {35.000000, 165.000000, 140.000000, 26.000000, 4.923077, 0.307692, -0.307692, 0.187500},
    {37.000000, 162.000000, 34.000000, 114.000000, 1.122807, -0.017544, 0.017544, 0.875000},
    {35.000000, 164.000000, 148.000000, 17.000000, 7.529412, 0.470588, -0.470588, 0.125000},
    {36.000000, 162.000000, 35.000000, 121.000000, 1.057851, -0.008264, 0.008264, 0.937500},
    {36.000000, 164.000000, 156.000000, 8.000000, 16.000000, 1.000000, -1.000000, 0.062500},
}
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
static void draw_hcube(int left, int top, GRAPHIC_DC *pdstDC, GRAPHIC_DC *pleftsrcDC, GRAPHIC_DC *prightsrcDC, int dir, int step)
{
    GRAPHIC_DC *pcursrcDC;
    GRAPHIC_DC *pnextsrcDC;

    if (dir == 0)
    {
        pcursrcDC = pleftsrcDC;
        pnextsrcDC = prightsrcDC;
    }
    else
    {
        pcursrcDC = prightsrcDC;
        pnextsrcDC = pleftsrcDC;
    }

    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(pcursrcDC->u8FbID, &fbAttr);
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

        CopyFB.fbID=(step == 0)?pcursrcDC->u8FbID:pnextsrcDC->u8FbID;
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
        // draw left image
        int frame = ((step-1)*2);
        reg.trap_dir = 1;         // horizontal
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (cubeTrap[dir][frame][P_EDGE_ST]-36)*src_height/128+top;
        reg.parallel_edge0_end = (cubeTrap[dir][frame][P_EDGE_END]-36)*src_height/128+top;
        reg.parallel_edge0_pos = (cubeTrap[dir][frame][P_EDGE_POS]-36)*src_width/128+left;
        reg.trap_distance = cubeTrap[dir][frame][TRAP_DIST]*src_width/128;;
        reg.trape_distance_delta = cubeTrap[dir][frame][TRAP_DIST_DELTA];
        reg.trap_gradient0 = cubeTrap[dir][frame][TRAP_GRAD0]*src_height/src_width;
        reg.trap_gradient1 = cubeTrap[dir][frame][TRAP_GRAD1]*src_height/src_width;
        reg.abl_const = cubeTrap[dir][frame][ABL_CONST];
        trapezoid_h_blt(pdstDC, pleftsrcDC, reg);

        // draw down image
        frame = frame + 1;
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (cubeTrap[dir][frame][P_EDGE_ST]-36)*src_height/128+top;
        reg.parallel_edge0_end = (cubeTrap[dir][frame][P_EDGE_END]-36)*src_height/128+top;
        reg.parallel_edge0_pos = (cubeTrap[dir][frame][P_EDGE_POS]-36)*src_width/128+left;
        reg.trap_distance = cubeTrap[dir][frame][TRAP_DIST]*src_width/128;;
        reg.trape_distance_delta = cubeTrap[dir][frame][TRAP_DIST_DELTA];
        reg.trap_gradient0 = cubeTrap[dir][frame][TRAP_GRAD0]*src_height/src_width;
        reg.trap_gradient1 = cubeTrap[dir][frame][TRAP_GRAD1]*src_height/src_width;
        reg.abl_const = cubeTrap[dir][frame][ABL_CONST];
        trapezoid_h_blt(pdstDC, prightsrcDC, reg);
    }
#else
    {
        float   diagonal;
        float   vmotion_left_delta, vmotion_mid_delta;
        int     parallel_left_pos, parallel_mid_pos, parallel_right_pos;

        float   delta1, delta2;
        float   scale_w_left, scale_w_mid, scale_w_right, w_left, w_mid, w_right;
        float   intensity_left, intensity_right;
        float   trap_edge_gradient_left, trap_edge_gradient_right;
        int     trap_parallel0_length, trap_parallel1_length, trap_parallel2_length;
        int     trap_distance_left, trap_distance_right;
        int     parallel_edge0_st, parallel_edge0_end;
        int     step_tmp;

        if(dir == 1)
            step_tmp = step;
        else
            step_tmp = FRAMES - step;

        // calculate parameters for Trapezoid
        delta1 = 1.0f / (float)FRAMES;
        delta2 = delta1 / 8.0f;

        diagonal = sqrt((double)(src_width * src_width * 2));
        vmotion_left_delta = ((float)(diagonal - (float)src_width) / (float)FRAMES) * 0.3f;
        vmotion_mid_delta = (float)src_width / (float)FRAMES;

        if(dir == 1)
        {
            step_tmp = step;
        }
        else
        {
            step_tmp = FRAMES - step;
        }

        if(step * 2 < FRAMES)
        {
            parallel_left_pos = (int)((float)left - step * vmotion_left_delta);
            parallel_right_pos = (int)((float)(left + src_width) + step * vmotion_left_delta);
        }
        else
        {
            parallel_left_pos = (int)((float)left - (FRAMES - step) * vmotion_left_delta);
            parallel_right_pos = (int)((float)(left + src_width) + (FRAMES - step) * vmotion_left_delta);
        }
        parallel_mid_pos = (int)((float)left + step_tmp * vmotion_mid_delta);

        if(((step*2 < FRAMES) && (dir == 1)) || ((step*2 > FRAMES) && (dir == 0)))
        {
            scale_w_mid = 1.0f + (step_tmp * delta2);
            intensity_left = (float)step_tmp / (float)FRAMES;
            intensity_right = 1 - ((float)step_tmp / (float)FRAMES);
        }
        else
        {
            scale_w_mid = 1.0f + ((FRAMES - step_tmp) * delta2);
            intensity_left = 1.0f - (float)(FRAMES - step_tmp) / (float)FRAMES;
            intensity_right = (float)(FRAMES - step_tmp) / (float)FRAMES;
        }
        scale_w_left = 1.0f - (FRAMES - step_tmp) * delta2;
        scale_w_right = 1.0f - (step_tmp * delta2);
        w_mid = src_height * scale_w_mid;
        w_left = src_height * scale_w_left;
        w_right = src_height * scale_w_right;
        trap_parallel0_length = (int)(w_left + 0.5f);
        trap_parallel1_length = (int)(w_mid + 0.5f);
        trap_parallel2_length = (int)(w_right + 0.5f);

        trap_distance_left = parallel_mid_pos - parallel_left_pos;
        trap_distance_right = parallel_right_pos - parallel_mid_pos;

        trap_edge_gradient_left = (float)( ((trap_parallel0_length - trap_parallel1_length)/2.0f) / trap_distance_left);
        trap_edge_gradient_right = (float)( ((trap_parallel1_length - trap_parallel2_length)/2.0f) / trap_distance_right);

        Regset reg;
        memset(&reg,0,sizeof(Regset));

        // draw left image
        parallel_edge0_st = top - ((trap_parallel0_length - src_height)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel0_length - 1;

        reg.trap_dir = 1;         // horizontal
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (float)parallel_edge0_st;
        reg.parallel_edge0_end = (float)parallel_edge0_end;
        reg.parallel_edge0_pos = (float)parallel_left_pos;
        reg.trap_distance = (float)trap_distance_left;
        reg.trape_distance_delta = (float)src_width / (float)trap_distance_left;
        reg.trap_gradient0 = trap_edge_gradient_left;
        reg.trap_gradient1 = -trap_edge_gradient_left;
        reg.abl_const = intensity_left;
        trapezoid_h_blt(pdstDC, pleftsrcDC, reg);

        // draw right image
        parallel_edge0_st = top - ((trap_parallel1_length - src_height)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel1_length - 1;

        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (float)parallel_edge0_st;
        reg.parallel_edge0_end = (float)parallel_edge0_end;
        reg.parallel_edge0_pos = (float)parallel_mid_pos;
        reg.trap_distance = (float)trap_distance_right;
        reg.trape_distance_delta = (float)src_width / (float)trap_distance_right;
        reg.trap_gradient0 = trap_edge_gradient_right;
        reg.trap_gradient1 = -trap_edge_gradient_right;
        reg.abl_const = intensity_right;
        trapezoid_h_blt(pdstDC, prightsrcDC, reg);
    }
#endif

}


// dir=0(up), dir=1(down)
static void draw_vcube(int left, int top, GRAPHIC_DC *pdstDC, GRAPHIC_DC *pupsrcDC, GRAPHIC_DC *pdownsrcDC, int dir, int step)
{
    GRAPHIC_DC *pcursrcDC;
    GRAPHIC_DC *pnextsrcDC;

    if (dir == 0)
    {
        pcursrcDC = pupsrcDC;
        pnextsrcDC = pdownsrcDC;
    }
    else
    {
        pcursrcDC = pdownsrcDC;
        pnextsrcDC = pupsrcDC;
    }

    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(pcursrcDC->u8FbID, &fbAttr);
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

        CopyFB.fbID=(step == 0)?pcursrcDC->u8FbID:pnextsrcDC->u8FbID;
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
        // draw up image
        int frame = ((step-1)*2);
        reg.trap_dir = 0;         // vertical
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (cubeTrap[dir][frame][P_EDGE_ST]-36)*src_width/128+left;
        reg.parallel_edge0_end = (cubeTrap[dir][frame][P_EDGE_END]-36)*src_width/128+left;
        reg.parallel_edge0_pos = (cubeTrap[dir][frame][P_EDGE_POS]-36)*src_height/128+top;
        reg.trap_distance = cubeTrap[dir][frame][TRAP_DIST]*src_height/128;
        reg.trape_distance_delta = cubeTrap[dir][frame][TRAP_DIST_DELTA];
        reg.trap_gradient0 = cubeTrap[dir][frame][TRAP_GRAD0]*src_width/src_height;
        reg.trap_gradient1 = cubeTrap[dir][frame][TRAP_GRAD1]*src_width/src_height;
        reg.abl_const = cubeTrap[dir][frame][ABL_CONST];
        trapezoid_v_blt(pdstDC, pupsrcDC, reg);

        // draw down image
        frame = frame + 1;
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (cubeTrap[dir][frame][P_EDGE_ST]-36)*src_width/128+left;
        reg.parallel_edge0_end = (cubeTrap[dir][frame][P_EDGE_END]-36)*src_width/128+left;
        reg.parallel_edge0_pos = (cubeTrap[dir][frame][P_EDGE_POS]-36)*src_height/128+top;
        reg.trap_distance = cubeTrap[dir][frame][TRAP_DIST]*src_height/128;
        reg.trape_distance_delta = cubeTrap[dir][frame][TRAP_DIST_DELTA];
        reg.trap_gradient0 = cubeTrap[dir][frame][TRAP_GRAD0]*src_width/src_height;
        reg.trap_gradient1 = cubeTrap[dir][frame][TRAP_GRAD1]*src_width/src_height;
        reg.abl_const = cubeTrap[dir][frame][ABL_CONST];
        trapezoid_v_blt(pdstDC, pdownsrcDC, reg);
    }
#else
    {
        float   diagonal;
        float   vmotion_top_delta, vmotion_mid_delta;
        int     parallel_top_pos, parallel_mid_pos, parallel_bot_pos;
        float   delta1, delta2;
        float   scale_w_up, scale_w_mid, scale_w_down, w_up, w_mid, w_down;
        float   intensity_up, intensity_down;
        float   trap_edge_gradient_up, trap_edge_gradient_down;
        int     trap_parallel0_length, trap_parallel1_length, trap_parallel2_length;
        int     trap_distance_up, trap_distance_down;
        int     parallel_edge0_st, parallel_edge0_end;
        int     step_tmp;

        if(dir == 1)
            step_tmp = step;
        else
            step_tmp = FRAMES - step;

        // calculate parameters for Trapezoid
        delta1 = 1.0f / (float)FRAMES;
        delta2 = delta1 / 8.0f;

        diagonal = sqrt((double)(src_height * src_height * 2));
        vmotion_top_delta = ((float)(diagonal - (float)src_height) / (float)FRAMES) * 0.3f;
        vmotion_mid_delta = (float)src_height / (float)FRAMES;

        if(dir == 1)
        {
            step_tmp = step;
        }
        else
        {
            step_tmp = FRAMES - step;
        }

        if(step * 2 < FRAMES)
        {
            parallel_top_pos = (int)((float)(top) - (step * vmotion_top_delta));
            parallel_bot_pos = (int)((float)(top + src_height) + (step * vmotion_top_delta));
        }
        else
        {
            parallel_top_pos = (int)((float)top - (FRAMES - step) * vmotion_top_delta);
            parallel_bot_pos = (int)((float)(top + src_height) + (FRAMES - step) * vmotion_top_delta);
        }
        parallel_mid_pos = (int)((float)top + step_tmp * vmotion_mid_delta);

        if(((step*2 < FRAMES) && (dir == 1)) || ((step*2 > FRAMES) && (dir == 0)))
        {
            scale_w_mid = 1.0f + (step_tmp * delta2);
            intensity_up = (float)step_tmp / (float)FRAMES;
            intensity_down = 1 - ((float)step_tmp / (float)FRAMES);
        }
        else
        {
            scale_w_mid = 1.0f + ((FRAMES - step_tmp) * delta2);
            intensity_up = 1.0f - (float)(FRAMES - step_tmp) / (float)FRAMES;
            intensity_down = (float)(FRAMES - step_tmp) / (float)FRAMES;
        }
        scale_w_up = 1.0f - (FRAMES - step_tmp) * delta2;
        scale_w_down = 1.0f - (step_tmp * delta2);
        w_mid = src_width * scale_w_mid;
        w_up = src_width * scale_w_up;
        w_down = src_width * scale_w_down;
        trap_parallel0_length = (int)(w_up + 0.5f);
        trap_parallel1_length = (int)(w_mid + 0.5f);
        trap_parallel2_length = (int)(w_down + 0.5f);

        trap_distance_up = parallel_mid_pos - parallel_top_pos;
        trap_distance_down = parallel_bot_pos - parallel_mid_pos;

        trap_edge_gradient_up = (float)( ((trap_parallel0_length - trap_parallel1_length)/2.0f) / trap_distance_up);
        trap_edge_gradient_down = (float)( ((trap_parallel1_length - trap_parallel2_length)/2.0f) / trap_distance_down);

        Regset reg;
        memset(&reg,0,sizeof(Regset));

        // draw up image
        parallel_edge0_st = left - ((trap_parallel0_length - src_width)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel0_length - 1;

        reg.trap_dir = 0;         // vertical
        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (float)parallel_edge0_st;
        reg.parallel_edge0_end = (float)parallel_edge0_end;
        reg.parallel_edge0_pos = (float)parallel_top_pos;
        reg.trap_distance = (float)trap_distance_up;
        reg.trape_distance_delta = (float)src_height / (float)trap_distance_up;
        reg.trap_gradient0 = trap_edge_gradient_up;
        reg.trap_gradient1 = -trap_edge_gradient_up;
        reg.abl_const = intensity_up;
        trapezoid_v_blt(pdstDC, pupsrcDC, reg);

        // draw down image
        parallel_edge0_st = left - ((trap_parallel1_length - src_width)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel1_length - 1;

        reg.src_x0 = 0;
        reg.src_y0 = 0;
        reg.src_width = src_width;
        reg.src_height = src_height;
        reg.parallel_edge0_st  = (float)parallel_edge0_st;
        reg.parallel_edge0_end = (float)parallel_edge0_end;
        reg.parallel_edge0_pos = (float)parallel_mid_pos;
        reg.trap_distance = (float)trap_distance_down;
        reg.trape_distance_delta = (float)src_height / (float)trap_distance_down;
        reg.trap_gradient0 = trap_edge_gradient_down;
        reg.trap_gradient1 = -trap_edge_gradient_down;
        reg.abl_const = intensity_down;
        trapezoid_v_blt(pdstDC, pdownsrcDC, reg);
    }
#endif
}

static void _MApp_ZUI_CTL_Effect_HCube(HWND bghWnd, HWND leftsrchWnd, HWND rightsrchWnd, int dir, U32 ms)
{
    RECT bgrect;
    memset(&bgrect,0,sizeof(RECT));
    RECT srcrect;
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC bgDC;
    GRAPHIC_DC leftsrcDC;
    GRAPHIC_DC rightsrcDC;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    bgDC = MApp_ZUI_API_CreateDC(bgrect.width, bgrect.height);
    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(bgDC.u8FbID, &fbAttr);

    MApp_ZUI_API_GetWindowRect(leftsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    leftsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&leftsrcDC, &srcrect, GETNORMALDRAWSTYLE(leftsrchWnd));

    MApp_ZUI_API_GetWindowRect(rightsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    rightsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&rightsrcDC, &srcrect, GETNORMALDRAWSTYLE(rightsrchWnd));

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    MApp_ZUI_API_GetWindowRect(leftsrchWnd, &srcrect);
    int left = srcrect.left-bgrect.left;
    int top = srcrect.top-bgrect.top;

    int step;
    for (step=0; step<=FRAMES; step++)
    {
        MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

        draw_hcube(left, top, &bgDC, &leftsrcDC, &rightsrcDC, dir, step);

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
    MApp_ZUI_API_DeleteDC(leftsrcDC);
    MApp_ZUI_API_DeleteDC(rightsrcDC);

}

static void _MApp_ZUI_CTL_Effect_VCube(HWND bghWnd, HWND upsrchWnd, HWND downsrchWnd, int dir, U32 ms)
{
    RECT bgrect;
    memset(&bgrect,0,sizeof(RECT));
    RECT srcrect;
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC bgDC;
    GRAPHIC_DC upsrcDC;
    GRAPHIC_DC downsrcDC;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    bgDC = MApp_ZUI_API_CreateDC(bgrect.width, bgrect.height);
    GOP_GwinFBAttr fbAttr;
    MApi_GOP_GWIN_GetFBInfo(bgDC.u8FbID, &fbAttr);

    MApp_ZUI_API_GetWindowRect(upsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    upsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&upsrcDC, &srcrect, GETNORMALDRAWSTYLE(upsrchWnd));

    MApp_ZUI_API_GetWindowRect(downsrchWnd, &srcrect);
    srcrect.left = 0;
    srcrect.top = 0;
    downsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
    _MApp_ZUI_API_DrawStyleList(&downsrcDC, &srcrect, GETNORMALDRAWSTYLE(downsrchWnd));

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    MApp_ZUI_API_GetWindowRect(bghWnd, &bgrect);
    MApp_ZUI_API_GetWindowRect(upsrchWnd, &srcrect);
    int left = srcrect.left-bgrect.left;
    int top = srcrect.top-bgrect.top;

    int step;
    for (step=0; step<=FRAMES; step++)
    {
        MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

        draw_vcube(left, top, &bgDC, &upsrcDC, &downsrcDC, dir, step);

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
    MApp_ZUI_API_DeleteDC(upsrcDC);
    MApp_ZUI_API_DeleteDC(downsrcDC);

}

static void _MApp_ZUI_CTL_Effect_DefalutCube(HWND bghWnd, HWND srchWnd)
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
///  global  MApp_ZUI_CTL_EffectCubeWinProc
///  Window Proc for "effect Cube" control
///
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/3/2
///////////////////////////////////////////////////////////////////////////////
#define HDELAY               2  //ms
#define VDELAY               8  //ms

S32 MApp_ZUI_CTL_EffectCubeItemWinProc(HWND hWnd, PMSG pMsg)
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

S32 MApp_ZUI_CTL_EffectCubeWinProc(HWND hWnd, PMSG pMsg)
{
    GUI_DATA_CUBE_EFFECT *pWndData = (GUI_DATA_CUBE_EFFECT*)GETWNDDATA(hWnd);

  #if 0
    GUI_DATA_CUBE_EFFECT_VARDATA * pVar = pWndData->pVarData;

    //no dynamic list setting data...
    if (pWndData == 0 || pWndData->pVarData == 0)
        return DEFAULTWINPROC(hWnd, pMsg);
  #else // Modifed it by coverity_0538
    GUI_DATA_CUBE_EFFECT_VARDATA * pVar = NULL;
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
                pVar->dir = EN_EFFECT_CUBE_CREATE;
            }
            return 0;

        case MSG_NOTIFY_KEYDOWN:
            {
                switch(pMsg->wParam)
                {
                    case VK_UP:
                        pVar->dir = EN_EFFECT_CUBE_UP;
                        break;
                    case VK_DOWN:
                        pVar->dir = EN_EFFECT_CUBE_DOWN;
                        break;
                    case VK_LEFT:
                        pVar->dir = EN_EFFECT_CUBE_LEFT;
                        break;
                    case VK_RIGHT:
                        pVar->dir = EN_EFFECT_CUBE_RIGHT;
                        break;
                    default:
                        pVar->dir = EN_EFFECT_CUBE_CREATE;
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
                if ( pVar->dir == EN_EFFECT_CUBE_CREATE )
                {
                    HWND srchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_DefalutCube(hWnd, srchWnd);
                }
                else if ( pVar->dir == EN_EFFECT_CUBE_UP )
                {
                    HWND upsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(upsrchWnd, NAV_DOWN);
                    HWND downsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_VCube(hWnd, upsrchWnd, downsrchWnd, 0,  VDELAY);
                }
                else if ( pVar->dir == EN_EFFECT_CUBE_DOWN )
                {
                    HWND downsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(downsrchWnd, NAV_UP);
                    HWND upsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_VCube(hWnd, upsrchWnd, downsrchWnd, 1,  VDELAY);
                }
                else if ( pVar->dir == EN_EFFECT_CUBE_LEFT )
                {
                    HWND leftsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(leftsrchWnd, NAV_RIGHT);
                    HWND rightsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_HCube(hWnd, leftsrchWnd, rightsrchWnd, 0,  HDELAY);
                }
                else if ( pVar->dir == EN_EFFECT_CUBE_RIGHT )
                {
                    HWND rightsrchWnd = MApp_ZUI_API_GetFocus();
                    MApp_ZUI_API_SetFocusByNav(rightsrchWnd, NAV_LEFT);
                    HWND leftsrchWnd = MApp_ZUI_API_GetFocus();
                    _MApp_ZUI_CTL_Effect_HCube(hWnd, leftsrchWnd, rightsrchWnd, 1,  HDELAY);
                }

                pVar->dir = EN_EFFECT_CUBE_NONE;
            }
            return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_EFFECTCUBE_C
