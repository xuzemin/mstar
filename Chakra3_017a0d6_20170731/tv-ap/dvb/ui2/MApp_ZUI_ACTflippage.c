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

#define MAPP_ZUI_ACTFLIPPAGE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_ACTflippage.h"

#if ENABLE_PVR  //20100716EL
#include "MApp_PVR.h"
#endif


#if ENABLE_MAINPAGE_EFFECT
#define FRAMES              8
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

    //int alpha = (int)(255.0f * _reg.abl_const);
    //MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, (U8)alpha);
    MApi_GFX_SetAlpha(TRUE, COEF_ONE, ABL_FROM_ASRC, 0xFF);

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

    GFX_DrawRect bitbltInfo;
    MS_U32 flag = 0;
    GFX_BufferInfo srcbuf_bak, dstbuf_bak, srcbuf, dstbuf;
    MApi_GFX_GetBufferInfo(&srcbuf_bak, &dstbuf_bak);
    // there is no such source format, set to legacy 1555.
    if( GFX_FMT_ARGB1555_DST == BitbltInfo.src_fm )
    {
        srcbuf.u32ColorFmt = GFX_FMT_ARGB1555;
        MApi_GFX_SetAlpha_ARGB1555(0xFF); //for alpha channel of ARGB1555 bitblt
    }
    else
        srcbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo.src_fm;
    srcbuf.u32Addr = PitBaseInfo.sb_base;
    srcbuf.u32Pitch = PitBaseInfo.sb_pit;
    MApi_GFX_SetSrcBufferInfo(&srcbuf, 0);

    dstbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo.dst_fm;
    dstbuf.u32Addr = PitBaseInfo.db_base;
    dstbuf.u32Pitch = PitBaseInfo.db_pit;
    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

    for (x=(int)_reg.parallel_edge0_pos, lines=0; lines<(int)_reg.trap_distance; ++lines, ++x)
    {
        idst_y0 = (_fix_line_st >> bitShift);
        idst_y1 = (_fix_line_end >> bitShift);
        isrc_x = (_fix_src_x + (FixShift>>1)) >> bitShift;
        isrc_y = (_fix_src_y + (FixShift>>1)) >> bitShift;

        //src
        bitbltInfo.srcblk.x = (U16)isrc_x;
        bitbltInfo.srcblk.y = (U16)isrc_y;
        bitbltInfo.srcblk.width = (U16)(_reg.trape_distance_delta);
        bitbltInfo.srcblk.height = (U16)(_reg.src_height);

        //dst
        bitbltInfo.dstblk.x = (U16)x;
        bitbltInfo.dstblk.y = (U16)idst_y0;
        bitbltInfo.dstblk.width = (U16)(1);
        bitbltInfo.dstblk.height = (U16)(idst_y1 - idst_y0 + 1);

        if( (bitbltInfo.srcblk.width != bitbltInfo.dstblk.width) ||
            (bitbltInfo.srcblk.height != bitbltInfo.dstblk.height))
            flag = GFXDRAW_FLAG_SCALE;

        MApi_GFX_BitBlt(&bitbltInfo, flag);

        _fix_src_x    += _fix_dist_delta;
        _fix_line_st  += _fix_grad0;
        _fix_line_end += _fix_grad1;
    }

    MApi_GFX_SetSrcBufferInfo(&srcbuf_bak, 0);
    MApi_GFX_SetDstBufferInfo(&dstbuf_bak, 0);

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
static void draw_hflip(int left, int top, GRAPHIC_DC *pdstDC, GRAPHIC_DC *pfrontsrcDC, GRAPHIC_DC *pbacksrcDC, int dir, int step, float delta_array[])
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

    {
        float   delta, delta_step, scale_h, scale_w_long, scale_w_short, h, w_long, w_short;
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
            delta_step = delta_array[step_tmp];

            scale_h = 1.0f - (delta_step * 2);
            scale_w_long = 1.0f + (delta_step);
            scale_w_short = 1.0f - (delta_step);
            h = src_width * scale_h;
            w_long = src_height * scale_w_long;
            w_short = src_height * scale_w_short;
            trap_distance = (int)(h + 0.5f);
            trap_parallel0_length = (int)(w_long + 0.5f);
            trap_parallel1_length = (int)(w_short + 0.5f);
            trap_edge_gradient = (float)((trap_parallel0_length - trap_parallel1_length) >>1 ) / trap_distance;
            intensity = 1.0f - (delta_step * 2);
        }
        // trapezoid show next image (back face)
        else
        {
            step_countdown = FRAMES - step_tmp;
            delta_step = delta_array[step_countdown];

            scale_h = 1.0f - (delta_step * 2);
            scale_w_long = 1.0f + (delta_step);
            scale_w_short = 1.0f - (delta_step);
            h = src_width * scale_h;
            w_long = src_height * scale_w_long;
            w_short = src_height * scale_w_short;
            trap_distance = (int)(h + 0.5f);
            trap_parallel0_length = (int)(w_short + 0.5f);
            trap_parallel1_length = (int)(w_long + 0.5f);
            trap_edge_gradient = (float)((trap_parallel0_length - trap_parallel1_length) >>1 ) / trap_distance;
            intensity = 1.0f - (delta_step * 2);
        }
        parallel_edge0_st = top - ((trap_parallel0_length - src_height)/2);
        parallel_edge0_end = parallel_edge0_st + trap_parallel0_length - 1;
        parallel_edge0_pos = left + (src_width - trap_distance) / 2;

        Regset reg;
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
}

static void _MApp_ZUI_ACT_FlipPage_HFlip(U16 x0, U16 U16y0, GRAPHIC_DC *pbgDC, GRAPHIC_DC *pfrontsrcDC, GRAPHIC_DC *pbacksrcDC, int dir, U32 ms)
{
    UNUSED(ms);

    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    GOP_GwinFBAttr bgfbAttr;
    MApi_GOP_GWIN_GetFBInfo(pbgDC->u8FbID, &bgfbAttr);

    GOP_GwinFBAttr srcfbAttr;
    MApi_GOP_GWIN_GetFBInfo(pfrontsrcDC->u8FbID, &srcfbAttr);

    int left = (bgfbAttr.width - srcfbAttr.width)/2;
    int top = (bgfbAttr.height - srcfbAttr.height)/2;

    int step;
    float delta[] = {0, 10.0f/180, 30.0f/180, 60.0f/180, 90.0f/180, 120.0f/180, 150.0f/180, 170.0f/180, (float)180.0f/180};
    for (step=1; step<=FRAMES; step++)
    {
        MApp_ZUI_API_ClearDC(pbgDC, 0xFF101010);

        draw_hflip(left, top, pbgDC, pfrontsrcDC, pbacksrcDC, dir, step, delta);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(x0, U16y0, x0+bgfbAttr.width-1, U16y0+bgfbAttr.height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=x0;
        PasteFB.y=U16y0;
        PasteFB.width=bgfbAttr.width;
        PasteFB.height=bgfbAttr.height;

        CopyFB.fbID=pbgDC->u8FbID;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=bgfbAttr.width;
        CopyFB.height=bgfbAttr.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
    }

}

static void _MApp_ZUI_ACT_FlipPage_VFlip(U16 x0, U16 U16y0, GRAPHIC_DC *pbgDC, GRAPHIC_DC *pfrontsrcDC, GRAPHIC_DC *pbacksrcDC, int dir, U32 ms)
{
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();

    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    GOP_GwinFBAttr bgfbAttr;
    MApi_GOP_GWIN_GetFBInfo(pbgDC->u8FbID, &bgfbAttr);

    GOP_GwinFBAttr srcfbAttr;
    MApi_GOP_GWIN_GetFBInfo(pfrontsrcDC->u8FbID, &srcfbAttr);

    int left = (bgfbAttr.width - srcfbAttr.width)/2;
    int top = (bgfbAttr.height - srcfbAttr.height)/2;

    int step;
    for (step=0; step<=FRAMES; step++)
    {
        MApi_GFX_ClearFrameBuffer(bgfbAttr.addr, bgfbAttr.size, 0); // fill frame buffer with 0, black

        draw_vflip(left, top, pbgDC, pfrontsrcDC, pbacksrcDC, dir, step);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(x0, U16y0, x0+bgfbAttr.width-1, U16y0+bgfbAttr.height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=x0;
        PasteFB.y=U16y0;
        PasteFB.width=bgfbAttr.width;
        PasteFB.height=bgfbAttr.height;

        CopyFB.fbID=pbgDC->u8FbID;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=bgfbAttr.width;
        CopyFB.height=bgfbAttr.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }

}

static void _MApp_ZUI_ACT_FlipPage_PrepareBufferDC(void)
{
    //note: it is ALMOST default painting flow, but not update to screen!
    HWND hwnd;
    RECT * rect_inv;
    //BOOLEAN bFullScreen; //always full screen!
    PAINT_PARAM param;

    //redraw all controls
    rect_inv = &GETWNDINITRECT(HWND_MAINFRAME);
    ZUI_MSG(printf("[MainFrame]Repaint rect(%lu,%lu,%lu,%lu)\n",(U32)rect_inv->left, (U32)rect_inv->top,(U32)rect_inv->width, (U32)rect_inv->height);)
    //bFullScreen = TRUE;

    param.dc = *MApp_ZUI_API_GetBufferDC();
    param.dc.u8ConstantAlpha = 0xFF; //disable alpha blending

    //draw main frame...
    //_MApp_ZUI_API_DrawStyleList(&param.dc, rect_inv, GETNORMALDRAWSTYLE(HWND_MAINFRAME));
    param.rect = rect_inv;
    param.rect_invalidate = rect_inv;
    param.bIsDisable = param.bIsFocus = FALSE;
    param.bIsVisible = TRUE;
    _MApp_ZUI_API_DefaultOnPaint(HWND_MAINFRAME, &param, TRUE);

    //draw others....
    for (hwnd = HWND_MAINFRAME+1; hwnd < HWND_MAX; hwnd++)
    {
        //PRINT("\n[Note] loop hwnd = %d, state = %ld, u32State&WS_VISIBLE = %d", hwnd, u16State, (U16)u16State&WS_VISIBLE);

        param.bIsVisible = MApp_ZUI_API_IsWindowVisible(hwnd);
        if (param.bIsVisible)/* &&
            _MApp_ZUI_API_IsInsideScreen(&GETWNDRECT(hwnd)) )*/
        {
            RECT rect;
            MApp_ZUI_API_GetWindowRect(hwnd, &rect);
            param.rect = &rect;
            //if ( MApp_ZUI_API_DoesIntersect(rect_inv, param.rect) ) //always full screen!
            {
                param.bIsDisable = !MApp_ZUI_API_IsWindowEnabled(hwnd);

                //note: we assume if one window get focus, the child will be painted as focus style..
                param.bIsFocus = (MApp_ZUI_API_GetFocus()==hwnd || MApp_ZUI_API_IsParentFocused(hwnd));
                param.dc.bSrcAlphaReplaceDstAlpha = ((GETWNDINITSTATE(hwnd)&WS_SRCALPHAREPLACEDSTALPHA) != 0);

                //printf("\n[Note] send paint msg to win %d", hwnd);

                if ( //hwnd == HWND_MENU_CHANNEL_PAGE_LIST
                    //|| 
					hwnd == HWND_MENU_PICTURE_PAGE_LIST
                    || hwnd == HWND_MENU_SOUND_PAGE_LIST
                    || hwnd == HWND_MENU_OPTION_PAGE_LIST
                    //|| hwnd == HWND_MENU_TIME_PAGE_LIST
                    //|| hwnd == HWND_MENU_LOCK_PAGE_LIST
                    //|| hwnd == HWND_MENU_APP_PAGE_LIST
                   )
                {
                    MApp_ZUI_API_SendMessage(hwnd, MSG_NOTIFY_SHOW, (WPARAM)&param);
                }
                else
                {
                    MApp_ZUI_API_SendMessage(hwnd, MSG_PAINT, (WPARAM)&param);
                }
            }
            //else
            //{
            //    bFullScreen = FALSE; //something need not to paint (partally paint)
            //}
        }
    }

    //PRINT("Repaint buffer complete, cost=%d)\n", msAPI_Timer_GetTime0()-start_time);
    /*
    if (bFullScreen)
        MApp_ZUI_API_ReleaseFullScreenDC();
    else
        MApp_ZUI_API_ReleaseDC(rect_inv);
    */
    MApp_ZUI_API_ReleaseWithoutUpdateDC(); //note: don't update!!
    //To fix issue: In ATV, enter zmplayer, press KEY_EXIT to back to ATV
    //  and then press KEY_MENU to open Main Menu -> KEY_LEFT/KEY_RIGHT to
    //  do ROTATE effect, sometimes UI will show abnormally.
    //Root cause: although we prepare buffer DC and release without update DC,
    //  SW_SHOW messages still remained in ZUI message queue and will be
    //  processed after flip effect is finished. These events should be dropped
    //  before doing flip effect.
    MApp_ZUI_API_EmptyMessageQueue();
    //printf("==end\n");
}
#endif

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_FlipPageWinProc
///  [MENU application customization]
///
///  @param [in]       hwnd HWND     window handle we are processing
///  @param [in]       msg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/3/17
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_ACT_FlipPageWinProc(HWND hwnd, PMSG msg)
{
    GUI_DATA_FLIPPAGE *pWndData = (GUI_DATA_FLIPPAGE*) GETWNDDATA(hwnd);
    GUI_DATA_FLIPPAGE_VARDATA * pVar = pWndData->pVarData;

    static HWND _ZUI_TBLSEG page2ball[][2] =
    {
      //  { HWND_MENU_CHANNEL_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_CHANNEL},//wht120303_2
        { HWND_MENU_PICTURE_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_PICTURE},
        { HWND_MENU_SOUND_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_SOUND},
        { HWND_MENU_OPTION_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_OPTION},
       // { HWND_MENU_TIME_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_TIME},  //wht120303_2
     #if ENABLE_DTV
     
        //{ HWND_MENU_LOCK_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_LOCK},
     #endif
     #if (!ENABLE_USB_ITEM_IN_SOURCE_MENU)
        { HWND_MENU_APP_PAGE, HWND_MENU_BOTTOM_BALL_FOCUS_APP},
    #endif
    };

    switch(msg->message)
    {
        case MSG_CREATE:
            pVar->dir = EN_FLIPPAGE_NONE;
            #if 1 //smc.chy 2010/05/07
            pVar->hwndCurrent = HWND_MENU_PICTURE_PAGE;
            pVar->hwndNext = HWND_MENU_SOUND_PAGE;
            #else
            pVar->hwndCurrent = HWND_MENU_CHANNEL_PAGE;
            pVar->hwndNext = HWND_MENU_PICTURE_PAGE;
            #endif
            break;

        case MSG_EFFECT:
        /*
            MApp_ZUI_API_SetTimer(hwnd, 0, 10);
            break;

        case MSG_TIMER:
        */
            {
                MApp_ZUI_API_ShowWindow(pVar->hwndCurrent, SW_HIDE);
                MApp_ZUI_API_ShowWindow(pVar->hwndNext, SW_SHOW);
                MApp_ZUI_API_SetFocus(pVar->hwndNextFocus);
                U8 i;
                for (i=0; i<COUNTOF(page2ball); i++)
                {
                    if (pVar->hwndNext == page2ball[i][0])
                    {
                        MApp_ZUI_API_ShowWindow(page2ball[i][1], SW_SHOW);

                         #if  (ENABLE_DTV == 0) 
                         RECT rect;// Mantis 0118943

                         if (pVar->hwndNext == HWND_MENU_APP_PAGE)
                         {
                            MApp_ZUI_API_ShowWindow(HWND_MENU_BOTTOM_BALL_FOCUS_APP, SW_SHOW);
                            MApp_ZUI_API_GetWindowInitialRect(HWND_MENU_BOTTOM_BALL_FOCUS_LOCK, &rect);
                            MApp_ZUI_API_MoveAllSuccessors(HWND_MENU_BOTTOM_BALL_FOCUS_APP,rect.left, rect.top);
                         }
                         #endif

                    }
                    else
                    {
                        MApp_ZUI_API_ShowWindow(page2ball[i][1], SW_HIDE);
                    }
                }
#if ENABLE_MAINPAGE_EFFECT
                GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
                GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
                RECT bgrect;
                RECT srcrect;
                GRAPHIC_DC bgDC;
                GRAPHIC_DC frontsrcDC;
                GRAPHIC_DC backsrcDC;

                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;
                #if 1 //smc.chy 2010/05/07
                MApp_ZUI_API_GetWindowRect(HWND_MENU_PICTURE_PAGE, &srcrect);
                #else
                MApp_ZUI_API_GetWindowRect(HWND_MENU_CHANNEL_PAGE, &srcrect);
                #endif
                _MApp_ZUI_ACT_FlipPage_PrepareBufferDC();
                MApi_GFX_FlushQueue();
                backsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
                if ( backsrcDC.u8FbID != 0xFF )
                {
                    //we MUST reset clip window before msAPI_OSD_CopyRegion()
                    msAPI_OSD_SetClipWindow(0, 0, srcrect.width-1, srcrect.height-1);
                    PasteFB.fbID = backsrcDC.u8FbID;
                    PasteFB.x = 0;
                    PasteFB.y = 0;
                    PasteFB.width = srcrect.width;
                    PasteFB.height = srcrect.height;

                    CopyFB.fbID = pBuffDC->u8FbID;
                    CopyFB.x = srcrect.left;
                    CopyFB.y = srcrect.top;
                    CopyFB.width = srcrect.width;
                    CopyFB.height = srcrect.height;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }
                /*Release the back buffer of double buffer*/
                MApp_ZUI_API_DeleteDC(*pBuffDC);
                MApi_GFX_FlushQueue();
                frontsrcDC = MApp_ZUI_API_CreateDC(srcrect.width, srcrect.height);
                if ( frontsrcDC.u8FbID != 0xFF )
                {
                    //we MUST reset clip window before msAPI_OSD_CopyRegion()
                    msAPI_OSD_SetClipWindow(0, 0, srcrect.width-1, srcrect.height-1);
                    PasteFB.fbID = frontsrcDC.u8FbID;
                    PasteFB.x = 0;
                    PasteFB.y = 0;
                    PasteFB.width = srcrect.width;
                    PasteFB.height = srcrect.height;

                    CopyFB.fbID = pScrnDC->u8FbID;
                    CopyFB.x = srcrect.left;
                    CopyFB.y = srcrect.top;
                    CopyFB.width = srcrect.width;
                    CopyFB.height = srcrect.height;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }
                
                #if 1 //smc.chy 2010/05/07
                MApp_ZUI_API_GetWindowRect(HWND_MENU_PICTURE_PAGE, &bgrect);
                #else
                MApp_ZUI_API_GetWindowRect(HWND_MENU_CHANNEL_PAGE, &bgrect);
                #endif
                bgrect.top = bgrect.top - (bgrect.height*2/10);
                bgrect.height = bgrect.height*14/10;
                MApi_GFX_FlushQueue();
                bgDC = MApp_ZUI_API_CreateDC(bgrect.width, bgrect.height);

                if ( bgDC.u8FbID != 0xFF && frontsrcDC.u8FbID != 0xFF && backsrcDC.u8FbID != 0xFF)
                {
                    if (pVar->dir == EN_FLIPPAGE_LEFT)
                    {
                        _MApp_ZUI_ACT_FlipPage_HFlip(bgrect.left, bgrect.top, &bgDC, &frontsrcDC, &backsrcDC, 0,  0);
                    }
                    else if (pVar->dir == EN_FLIPPAGE_RIGHT)
                    {
                        _MApp_ZUI_ACT_FlipPage_HFlip(bgrect.left, bgrect.top, &bgDC, &frontsrcDC, &backsrcDC, 1,  0);
                    }
                    else if (pVar->dir == EN_FLIPPAGE_UP)
                    {
                        _MApp_ZUI_ACT_FlipPage_VFlip(bgrect.left, bgrect.top, &bgDC, &frontsrcDC, &backsrcDC, 0,  0);
                    }
                    else if (pVar->dir == EN_FLIPPAGE_DOWN)
                    {
                        _MApp_ZUI_ACT_FlipPage_VFlip(bgrect.left, bgrect.top, &bgDC, &frontsrcDC, &backsrcDC, 1,  0);
                    }
                }
                MApp_ZUI_API_DeleteDC(bgDC);
                MApp_ZUI_API_DeleteDC(frontsrcDC);
                MApp_ZUI_API_DeleteDC(backsrcDC);

                /*restore back buffer of the double buffer*/
                RECT GWinRect;
                MApp_ZUI_API_QueryGWinRect(&GWinRect);
                *pBuffDC = MApp_ZUI_API_CreateDC(GWinRect.width,GWinRect.height);

                //MApp_ZUI_API_EmptyMessageQueue();

}

#endif

                //MApp_ZUI_API_KillTimer(hwnd, 0);
            }
            break;

        case MSG_PAINT:
        {
            PAINT_PARAM * param = (PAINT_PARAM*)msg->wParam;
            _MApp_ZUI_API_DrawStyleListNoText(&param->dc, param->rect, GETNORMALDRAWSTYLE(hwnd));
            return 0;
        }

        default:
            break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}

#undef MAPP_ZUI_ACTFLIPPAGE_C
