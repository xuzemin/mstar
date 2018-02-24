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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_OSD.h
/// @brief API for OSD Drawing functions
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_OSD2_C

/******************************************************************************/
/*                 Header Files                                               */
/******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "datatype.h"

#include "msAPI_OSD.h"
#include "msAPI_OSD_Resource.h"
#include "apiGOP.h"

#if 0//defined(MIPS_CHAKRA)
#define GOP_GwinFBAttr GOP_GwinFBAttr
#endif

#define APIOSD_DBG(x) //x

#define AQU_BOUND_WIDTH 4

/********************************************************************************/
/*                     Local                                                    */
/********************************************************************************/
//static GELineRectInfo  GELineRect;
//static OSDClrBtn       OSDClrBtnRec;
//static GEBitBltInfo  BitbltInfo;
//static GEPitBaseInfo PitBaseInfo;
/********************************************************************************/
/*                   Functions                                                     */
/********************************************************************************/

/******************************************************************************/
/// API for copy one rectangle from one buffer to another:
/// @param *src \b IN pointer to a struct defining one OSD region as source.
/// @param *dst \b IN pointer to a struct defining one OSD region as destination.
/// -@see MSAPI_OSDRegion
/******************************************************************************/
U8 msAPI_OSD_CopyRegion(MSAPI_OSDRegion *src, MSAPI_OSDRegion *dst)
{
#if 1
    GOP_GwinFBAttr fbAttr;
    GFX_DrawRect bitbltInfo;

    GFX_BufferInfo srcbuf_bak, dstbuf_bak, srcbuf, dstbuf;
//    ASSERT(src==NULL);
//    ASSERT(dst==NULL);
    //msAPI_OSD_GET_resource();

    MApi_GFX_SetAlpha(TRUE, COEF_ONE, ABL_FROM_ASRC, 0xFF);

    bitbltInfo.srcblk.x = src->x;
    bitbltInfo.srcblk.y = src->y;
    bitbltInfo.srcblk.width = src->width;
    bitbltInfo.srcblk.height = src->height;

    bitbltInfo.dstblk.x = dst->x;
    bitbltInfo.dstblk.y = dst->y;
    bitbltInfo.dstblk.width = dst->width;
    bitbltInfo.dstblk.height = dst->height;

    MApi_GOP_GWIN_GetFBInfo(src->fbID, &fbAttr);

    // there is no such source format, set to legacy 1555.
    if( GFX_FMT_ARGB1555_DST == (fbAttr.fbFmt & 0xff) )
    {
        srcbuf.u32ColorFmt = GFX_FMT_ARGB1555;
        MApi_GFX_SetAlpha_ARGB1555(0xFF); //for alpha channel of ARGB1555 bitblt
    }
    else
        srcbuf.u32ColorFmt = (GFX_Buffer_Format)(fbAttr.fbFmt & 0xff);

    srcbuf.u32Addr = fbAttr.addr;
    srcbuf.u32Pitch = fbAttr.pitch;
    MApi_GFX_SetSrcBufferInfo(&srcbuf, 0);

    MApi_GOP_GWIN_GetFBInfo(dst->fbID, &fbAttr);
    dstbuf.u32ColorFmt = (GFX_Buffer_Format)(fbAttr.fbFmt & 0xff);
    dstbuf.u32Addr = fbAttr.addr;
    dstbuf.u32Pitch = fbAttr.pitch;

    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

#if 0
    BitbltInfo.BitbltCoordinate.v0_x = dst->x;
    BitbltInfo.BitbltCoordinate.v0_y = dst->y;
    BitbltInfo.BitbltCoordinate.height = dst->height;
    BitbltInfo.BitbltCoordinate.width = dst->width;

    BitbltInfo.BitbltCoordinate.v2_x = src->x;
    BitbltInfo.BitbltCoordinate.v2_y = src->y;
    BitbltInfo.src_height = src->height;
    BitbltInfo.src_width = src->width;

    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;

    MApi_GOP_GWIN_GetFBInfo(src->fbID, &fbAttr);
    BitbltInfo.src_fm = fbAttr.fbFmt;
    PitBaseInfo.sb_base = fbAttr.addr;
    PitBaseInfo.sb_pit = fbAttr.pitch;

    MApi_GOP_GWIN_GetFBInfo(dst->fbID, &fbAttr);
    BitbltInfo.dst_fm = fbAttr.fbFmt;
    PitBaseInfo.db_base = fbAttr.addr;
    PitBaseInfo.db_pit = fbAttr.pitch;
#endif
    MApi_GFX_GetBufferInfo(&srcbuf_bak, &dstbuf_bak);

    if ((src->fbID != 0xFF) && (dst->fbID != 0xFF))
    {
        MApi_GFX_BitBlt(&bitbltInfo, 0);
//        MDrv_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
    }
    else
    {
        //printf("ERR:  dst->fbID %bx / dst->fbID%bx \n ",src->fbID,dst->fbID);
    }

    MApi_GFX_SetSrcBufferInfo(&srcbuf_bak, 0);
    MApi_GFX_SetDstBufferInfo(&dstbuf_bak, 0);

#endif
    //msAPI_OSD_Free_resource();
    return 0;
}


#ifdef MSAPI_OSD_AQUA

//static U16 angular_increment;
//static U16 normalised_angle;
static U16 x, y, last_y;
static U16 u16Temp1, u16Temp2, u16Temp3, u16Temp4, u16Temp5;
//static U32 u32Loop;

static S32 s32OR,s32OG,s32OB;
static S32 s32DR,s32DG,s32DB;
static U16 u16GrdHight;
//static GEPESettings  PESet;
//static U32 l32Clr;

/*****************************************************************************************************/

static void setGradientInfo_(U32 bc, U32 gc, U16 h)
{

    s32OR = ((bc & 0x00ff0000)>>16);
    s32OG = ((bc & 0x0000ff00)>>8);
    s32OB = (bc & 0x000000ff);

    s32DR = ((gc & 0x00ff0000)>>16) - s32OR;
    s32DG = ((gc & 0x0000ff00)>>8) - s32OG;
    s32DB = (gc & 0x000000ff) - s32OB;

    u16GrdHight = h;
}

static U32 getColorByHight_(U16 u16H)
{
    S32 s32R,s32G,s32B;
    U32 u32Tmp;

    s32R = (s32OR + ((s32DR*u16H)/u16GrdHight)) << 16;
    s32G = (s32OG + ((s32DG*u16H)/u16GrdHight)) << 8;
    s32B = (s32OB + ((s32DB*u16H)/u16GrdHight));

    u32Tmp = 0xff000000 | s32R | s32G | s32B;
    return u32Tmp;
}

/******************************************************************************/
/// API for Draw Gradient Round Block::
/// @param pclrBtn \b IN color
/******************************************************************************/
void msAPI_OSD_DrawGradientRoundBlock(OSDClrBtn *pclrBtn)
{
    GFX_RectFillInfo pfillblock;
    U32 tmpclr;

    /* for Y gradient only */
    if ( pclrBtn->radius > pclrBtn->width / 2 || pclrBtn->radius > pclrBtn->height / 2 )
    {
        return;
    }

    pfillblock.fmt = GFX_FMT_RGB565;
    msAPI_OSD_GET_resource();
    setGradientInfo_(pclrBtn->b_clr,
            pclrBtn->g_clr,
            pclrBtn->height );

//    GELineRect.LineRectCoordinate.direction = 0x0;
    pfillblock.dstBlock.x = pclrBtn->x;
    pfillblock.dstBlock.width = pclrBtn->x + pclrBtn->width ;
    pfillblock.dstBlock.y = pclrBtn->y + pclrBtn->radius - 1;
    pfillblock.dstBlock.height = pclrBtn->height - (2*pclrBtn->radius) + 2;
    pfillblock.flag = GFXRECT_FLAG_COLOR_GRADIENT_Y;
    tmpclr = getColorByHight_(pclrBtn->radius);
    memcpy(&pfillblock.colorRange.color_s, &tmpclr, 4);
    tmpclr = getColorByHight_(pclrBtn->height - pclrBtn->radius);
    memcpy(&pfillblock.colorRange.color_e, &tmpclr, 4);
    MApi_GFX_RectFill(&pfillblock);



    //GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_CONSTANT;
    pfillblock.flag = 0;

    /* draw top and bottom round */
    u16Temp1 = pclrBtn->x + pclrBtn->radius - 1;
    u16Temp2 = pfillblock.dstBlock.y;
    u16Temp3 = pclrBtn->width - 2 * pclrBtn->radius + 2;
    u16Temp4 = pclrBtn->y + pclrBtn->height - pclrBtn->radius;
    last_y = 0;

    u16Temp5 = (pclrBtn->radius*pclrBtn->radius)<<2;
    for ( y=1; ; y++ )
    {
        u16Temp5 = u16Temp5 - (y<<3) - 4;
        x = int_sqrt(u16Temp5);
        x = (x - 1)>>1;

        /* draw top round */
//        GELineRect.LineRectCoordinate.direction = 0x0;
        pfillblock.dstBlock.x = u16Temp1 - x;
        pfillblock.dstBlock.y = u16Temp2 - y;
        pfillblock.dstBlock.width = u16Temp3 + (x<<1) ;
        pfillblock.dstBlock.height =  (y - last_y) + 1;
        tmpclr = getColorByHight_(pfillblock.dstBlock.y - pclrBtn->y);
        memcpy(&pfillblock.colorRange.color_s, &tmpclr, 4);
        //memcpy(&pfillblock.colorRange.color_e, &tmpclr, 4);
        MApi_GFX_RectFill(&pfillblock);


        /* draw bottom round */
        //GELineRect.LineRectCoordinate.direction = 0x0;
        pfillblock.dstBlock.y = u16Temp4 + last_y;
        pfillblock.dstBlock.height = u16Temp4 + y - pfillblock.dstBlock.y;
        tmpclr = getColorByHight_(pfillblock.dstBlock.y + pfillblock.dstBlock.height -1 - pclrBtn->y);
        memcpy(&pfillblock.colorRange.color_s, &tmpclr, 4);
        //memcpy(&pfillblock.colorRange.color_e, &tmpclr, 4);
        MApi_GFX_RectFill(&pfillblock);

        /* draw top round */
        //GELineRect.LineRectCoordinate.direction = 0x0;
        pfillblock.dstBlock.x = u16Temp1 - y;
        pfillblock.dstBlock.y = u16Temp2 - x;
        pfillblock.dstBlock.width =  u16Temp3 + (y<<1) ;
        pfillblock.dstBlock.height =  2;
        tmpclr = getColorByHight_(pfillblock.dstBlock.y - pclrBtn->y);
        memcpy(&pfillblock.colorRange.color_s, &tmpclr, 4);
        //memcpy(&pfillblock.colorRange.color_e, &tmpclr, 4);
        MApi_GFX_RectFill(&pfillblock);

        /* draw bottom round */
        //GELineRect.LineRectCoordinate.direction = 0x0;

        pfillblock.dstBlock.y = u16Temp4 + x - 2;
        pfillblock.dstBlock.height = u16Temp4 + x - pfillblock.dstBlock.y;
        tmpclr = getColorByHight_(pfillblock.dstBlock.y+pfillblock.dstBlock.height -1  - pclrBtn->y);
        memcpy(&pfillblock.colorRange.color_s, &tmpclr, 4);
        //memcpy(&pfillblock.colorRange.color_e, &tmpclr, 4);
        MApi_GFX_RectFill(&pfillblock);


        last_y = y;

        if (x <= y)
            break;
    }
    msAPI_OSD_Free_resource();
}

/******************************************************************************/
/// API for Draw Aqua-Round Block::
/// @param pclrBtn \b IN color
/******************************************************************************/
#if 0
void msAPI_OSD_DrawAquaRoundBlock(OSDClrBtn *pclrBtn)
{
    U16 u16Tg;
    U16 u16Tw;

    memcpy(&OSDClrBtnRec, pclrBtn, sizeof(OSDClrBtn));
    OSDClrBtnRec.g_clr = 0xffffffff;
    msAPI_OSD_DrawGradientRoundBlock(&OSDClrBtnRec);


    u16Tg = OSDClrBtnRec.radius >> 2;
    u16Tw = OSDClrBtnRec.width - (OSDClrBtnRec.radius<<1);
    OSDClrBtnRec.x += OSDClrBtnRec.radius;
    OSDClrBtnRec.radius = MIN((((OSDClrBtnRec.height>>1) - u16Tg)>>1),(OSDClrBtnRec.radius-u16Tg));
    OSDClrBtnRec.x -= (OSDClrBtnRec.radius + (u16Tg >> 1));
    OSDClrBtnRec.y += u16Tg;
    OSDClrBtnRec.height = (OSDClrBtnRec.height>>1) - u16Tg;
    OSDClrBtnRec.width = u16Tw + (OSDClrBtnRec.radius << 1);
    OSDClrBtnRec.g_clr = ((0xffffffff - OSDClrBtnRec.b_clr) > 1) + OSDClrBtnRec.b_clr;
    OSDClrBtnRec.b_clr = 0xffffffff;

    msAPI_OSD_DrawGradientRoundBlock(&OSDClrBtnRec);
}

/******************************************************************************/
/// API for Draw Aqua-Flatten Block::
/// @param pclrBtn \b IN color
/******************************************************************************/
void msAPI_OSD_DrawAquaFlatBlock(OSDClrBtn *pclrBtn)
{
    memcpy(&OSDClrBtnRec, pclrBtn, sizeof(OSDClrBtn));

    GELineRect.LineRectCoordinate.direction = 0x0;
    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x;
    GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width - 1;
    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;
    GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height - 1;
    GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_GRADIENT_Y;
    GELineRect.ARGBClr.ForeGroundColor = 0xffffffff;
    l32Clr = pclrBtn->b_clr;//(pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
    VARBYTE(&l32Clr, 1) >>= 1;
    VARBYTE(&l32Clr, 2) >>= 1;
    VARBYTE(&l32Clr, 3) >>= 1;
    GELineRect.ARGBClr.GradientYColor = l32Clr;

    MDrv_GE_RectDraw(&GELineRect);

    GELineRect.LineRectCoordinate.direction = 0x0;
    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x + AQU_BOUND_WIDTH;
    GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width - 1 - AQU_BOUND_WIDTH;
    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y + AQU_BOUND_WIDTH;
    GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height - 1 - AQU_BOUND_WIDTH;
    GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_CONSTANT;
    GELineRect.ARGBClr.ForeGroundColor = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);

    MDrv_GE_RectDraw(&GELineRect);
}

/******************************************************************************/
/// API for Draw Aqua-Flatten and Round Block::
/// @param pclrBtn \b IN color
/******************************************************************************/
void msAPI_OSD_DrawAquaFlatRoundBlock(OSDClrBtn *pclrBtn)
{
    memcpy(&OSDClrBtnRec, pclrBtn, sizeof(OSDClrBtn));

    OSDClrBtnRec.b_clr = 0xffffffff;
    l32Clr = pclrBtn->b_clr;
    VARBYTE(&l32Clr, 1) >>= 1;
    VARBYTE(&l32Clr, 2) >>= 1;
    VARBYTE(&l32Clr, 3) >>= 1;
    OSDClrBtnRec.g_clr = l32Clr;

    msAPI_OSD_DrawGradientRoundBlock(&OSDClrBtnRec);

    OSDClrBtnRec.x += pclrBtn->bFrameWidth;
    OSDClrBtnRec.y += pclrBtn->bFrameWidth;
    OSDClrBtnRec.width  -= (pclrBtn->bFrameWidth)*2;
    OSDClrBtnRec.height -= (pclrBtn->bFrameWidth)*2;
    OSDClrBtnRec.b_clr = pclrBtn->b_clr;
    OSDClrBtnRec.radius -= pclrBtn->bFrameWidth;
    msAPI_OSD_DrawRoundBlock(&OSDClrBtnRec);
}

/******************************************************************************/
/// API for Draw Aqua-progress Block::
/// @param pClrBtnFrame \b IN color button frame
/// @param pClrBtnBar \b IN color button bar
/// @param u8Percentage \b IN percentage setting
/// @param u8ProgressBarFlag \b IN progress bar flag
/******************************************************************************/
void msAPI_OSD_DrawAquaProgBar(OSDClrBtn *pClrBtnFrame, OSDClrBtn *pClrBtnBar, U8 u8Percentage, U8 u8ProgressBarFlag)
{
    U16 percent_width;

    memcpy(&OSDClrBtnRec, pClrBtnFrame, sizeof(OSDClrBtn));

    if(u8Percentage > 100)
    {
        u8Percentage = 100;
    }

    if(u8ProgressBarFlag& 0x01)
    {
        OSDClrBtnRec.radius = (OSDClrBtnRec.height >> 1);
        //OSDClrBtnRec.b_clr = 0xffffffff;
        //OSDClrBtnRec.g_clr = COLOR_LTBLUE;
        msAPI_OSD_DrawGradientRoundBlock(&OSDClrBtnRec);
    }

    percent_width = pClrBtnBar->width * u8Percentage/100;
    memcpy(&OSDClrBtnRec, pClrBtnBar, sizeof(OSDClrBtn));

    if(u8ProgressBarFlag& 0x02)
    {
        //OSDClrBtnRec.b_clr = COLOR_PINK;
        //OSDClrBtnRec.g_clr = 0x7b4962;
        OSDClrBtnRec.width = percent_width;
        OSDClrBtnRec.u8Gradient = GRADIENT_Y_COLOR;
        msAPI_OSD_DrawBlock(&OSDClrBtnRec);
    }
    else if(u8ProgressBarFlag& 0x04)
    {
        //OSDClrBtnRec.b_clr = 0xffffffff;
        //OSDClrBtnRec.g_clr = COLOR_LTBLUE;
        OSDClrBtnRec.x += percent_width;
        OSDClrBtnRec.width -= percent_width;
        OSDClrBtnRec.u8Gradient = GRADIENT_Y_COLOR;
        msAPI_OSD_DrawBlock(&OSDClrBtnRec);
    }
}

void msAPI_OSD_CopyBoundary(U8 u8FId, U16 u16Width, U16 u16Heigh, U16 u16sx, U16 u16sy, U16 u16dx, U16 u16dy)
{
    GEPitBaseInfo PitBase;
    GOP_GwinFBAttr fbAttr;

    MApi_GOP_GWIN_GetFBInfo(u8FId, &fbAttr);

    BitbltInfo.src_fm = 0x17;
    BitbltInfo.dst_fm = 0x17;
    BitbltInfo.BitbltCoordinate.v0_x = u16dx;
    BitbltInfo.BitbltCoordinate.v0_y = u16dy;
    BitbltInfo.BitbltCoordinate.v2_x = u16sx;
    BitbltInfo.BitbltCoordinate.v2_y = u16sy;
    BitbltInfo.BitbltCoordinate.width = u16Width;
    BitbltInfo.BitbltCoordinate.height= u16Heigh;
    BitbltInfo.src_width                   = u16Width;
    BitbltInfo.src_height                  = u16Heigh;
    BitbltInfo.BitBltTypeFlag              = GEBitbltType_Normal;
    BitbltInfo.bmphandle                   = 0;
    PitBase.db_base                        = fbAttr.addr;
    PitBase.sb_base                        = fbAttr.addr;
    PitBase.db_pit                           = fbAttr.pitch;
    PitBase.sb_pit                           = fbAttr.pitch;

    MDrv_GE_BitBlt(&BitbltInfo, &PitBase);
    PESet.PE_Enable_Flag = GE_PE_FLAG_DEFAULT ;
    MDrv_GE_PixelEngine(&PESet);
}
#endif

#endif

#undef MSAPI_OSD2_C
