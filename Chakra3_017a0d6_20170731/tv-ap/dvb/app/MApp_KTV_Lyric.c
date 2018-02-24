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

///////////////////////////////////////////////////////////////////////////////
/// @file MApp_KTV_Lyric.c
/// @brief KTV lyric decode and display
/// @author MStar Semiconductor Inc.
///
/// KTV function on MStar chip.
///
///////////////////////////////////////////////////////////////////////////////

#define MAPP_KTV_LYRIC_C

#include <stdio.h>
#include <string.h>
#ifdef ENABLE_KTV
#include "ctype.h"
//#include "datatype.h"
#include "SysInit.h"
//#include "apiGOP.h"

#include "MApp_Exit.h"
#include "sysinfo.h"

#include "msAPI_FCtrl.h"
#include "msAPI_OSD.h"
#include "apiGOP.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"

#include "MApp_GlobalVar.h"
#include "MApp_KTV_Lyric.h"
#include "MApp_Font.h"
#if DYNAMIC_VECTOR_FONT_ENABLE
#include "MApp_Font_Dynamic_MVF.h"
#endif
//Mass Storage ========================


//*****************************************************************************
//              Definitions
//*****************************************************************************

//*****************************************************************************
//              enums
//*****************************************************************************


//*****************************************************************************
//              Data structure
//*****************************************************************************
typedef struct
{
    U8      u8_GWIN_id;
    U16     u16_GWIN_left;
    U16     u16_GWIN_top;
    U16     u16_GWIN_width;
    U16     u16_GWIN_height;
} GOP_PARAM;


//*****************************************************************************
//              Global variables
//*****************************************************************************

//*****************************************************************************
//              Local variables
//*****************************************************************************
static U16 iSingText_x;
static U16 iSingText_y;
static U16 iSingText_w;
static U16 iSingText_line_w[3];
static U16 iSingText_xoffset = KTV_LYRIC_SECONDLINE_OFFSET;
static U8 iSingText_h;
static U8 iSingText_fw;
static U8 iSingText_time[3];
static U8 iSingText_remain_line[3];
static U8 iSingbufferFBId=GWIN_ID_INVALID;
static U8 iSingcurrentFBId;

static U32 Waittime0 = 0;
static U32 Waittime1 = 0;
static U32 Waittime2 = 0;

static GOP_PARAM  gop_parameters;
static BOOLEAN _b_KTV_Gwin_created = false;
static U8 u8OriGOP;
static U8 u8OriGwin;
static U16 _u16ClipLeft,_u16ClipTop, _u16ClipRight, _u16ClipBottom;

//*****************************************************************************
//              Local Functions Prototype
//*****************************************************************************


//*****************************************************************************
//              Local Functions
//*****************************************************************************
static void _MApp_KTV_ClearDisplayBlock(U8 u8_GWID, U16 u16_x, U16 u16_y, U16 u16_width, U16 u16_height )
{
    OSDClrBtn clrBtn;

    MApi_GOP_GWIN_Switch2Gwin(u8_GWID);
     msAPI_OSD_SetClipWindow(u16_x, u16_y, u16_x + u16_width-1, u16_y + u16_height-1);

    clrBtn.x = u16_x;
    clrBtn.y = u16_y;
    clrBtn.width = u16_width;
    clrBtn.height = u16_height;
    clrBtn.u8Gradient = CONSTANT_COLOR;
    clrBtn.fHighLight = FALSE;
    clrBtn.b_clr = 0x00;
    msAPI_OSD_DrawBlock(&clrBtn);

}
void MApp_coexistWin_SwitchGwin(void)
{
    u8OriGOP = MApi_GOP_GWIN_GetCurrentGOP();
    u8OriGwin = MApi_GOP_GWIN_GetCurrentWinId();
    if (u8OriGOP != E_GOP_APP)
    {
        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    }
    if (u8OriGwin != gop_parameters.u8_GWIN_id)
    {
        MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);
    }
       msAPI_OSD_SetClipWindow(_u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom);
}


void MApp_coexistWin_RestoreGwin(void)
{
    if (u8OriGOP != E_GOP_APP)
    {
        MApi_GOP_GWIN_SwitchGOP(u8OriGOP);
    }
    if (u8OriGwin != gop_parameters.u8_GWIN_id)
    {
        MApi_GOP_GWIN_Switch2Gwin(u8OriGwin);
    }
}
//-------------------------------------------------------------------------------------------------
/// Media Player UI function. Open subtitle Gwin & FB.
/// @param
/// @return
//-------------------------------------------------------------------------------------------------
static BOOLEAN _MApp_KTV_OpenSubtitleWin(void)
{
    U16 _u16HSize = KTV_LYRIC_GW_HSIZE;
    U16 _u16VSize = KTV_LYRIC_GW_VSIZE;
    U16 _u16Left = KTV_LYRIC_GW_LEFT;
    U16 _u16Top = KTV_LYRIC_GW_TOP;

    gop_parameters.u16_GWIN_width = _u16HSize/8 * 8;
    gop_parameters.u16_GWIN_height = _u16VSize/8 * 8;
    gop_parameters.u16_GWIN_left = _u16Left/8 * 8;
    gop_parameters.u16_GWIN_top = _u16Top/8 * 8;

    //MApi_GOP_GWIN_SetGOPDst( E_GOP_APP, E_GOP_DST_IP0);
    u8OriGOP = MApi_GOP_GWIN_GetCurrentGOP();
    u8OriGwin = MApi_GOP_GWIN_GetCurrentWinId();
    MApi_GOP_GWIN_SwitchGOP( E_GOP_APP);

    MApi_GOP_GWIN_SetForceWrite(TRUE);

    gop_parameters.u8_GWIN_id =MApi_GOP_GWIN_CreateWin( gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height, DEFAULT_FB_FMT);
    if(gop_parameters.u8_GWIN_id == GWIN_ID_INVALID)
    {
        // create frame buffer fails, do nothing
        KTV_LYRIC_DBG(printf("\nFail to create gwin (W:%x, H:%x)", gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height););
        return FALSE;
    }
    KTV_LYRIC_DBG(printf("\n Rinit created gwin %d (W:%x, H:%x)", gop_parameters.u8_GWIN_id , gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height););

    //MApi_GOP_GWIN_MapFB2Win(u8FbID, gop_parameters.u8_GWIN_id);
    MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);

    MApi_GOP_GWIN_SetWinPosition(gop_parameters.u8_GWIN_id, gop_parameters.u16_GWIN_left, gop_parameters.u16_GWIN_top);

   // clear the frame buffer
    _MApp_KTV_ClearDisplayBlock(gop_parameters.u8_GWIN_id, 0, 0, gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height);
    msAPI_OSD_GetClipWindow(&_u16ClipLeft,&_u16ClipTop,&_u16ClipRight,&_u16ClipBottom);

    MApi_GOP_GWIN_SetBlending(gop_parameters.u8_GWIN_id, true, 63); // range is 0~63

    MApi_GOP_GWIN_SetForceWrite(FALSE);

    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);

    //MApi_GOP_SetGOPClk(E_GOP_APP, E_GOP_DST_IP0);
    //MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT1, TRUE);      // enable transparent color

    MApi_GOP_GWIN_SwitchGOP(u8OriGOP);
    MApi_GOP_GWIN_Switch2Gwin(u8OriGwin);
    //msAPI_OSD_SetClipWindow(_u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom);
    _b_KTV_Gwin_created = TRUE;

    return TRUE;

}


static void _MApp_KTV_CloseSubtitleWin( void )
{
    if(_b_KTV_Gwin_created)
    {
        MApi_GOP_GWIN_SwitchGOP( E_GOP_APP);
        MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);
        MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
        MApi_GOP_GWIN_DeleteWin(gop_parameters.u8_GWIN_id);
        //printf("\r\n GWIN_id = %bx", gop_parameters.u8_GWIN_id);
        _b_KTV_Gwin_created = FALSE;
    }
}

static void MApp_UiMenu_iSingOpenDrawSubtitle(void)
{
    #if( DYNAMIC_VECTOR_FONT_ENABLE == 0)
    FONT_INFO finfo;
    #endif

    clrBtn1.x = 0;
    clrBtn1.y = 0;

    clrBtn1.width = KTV_LYRIC_DISP_HSIZE;// Width of space

    clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
    clrBtn1.Fontfmt.flag = GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP; //((GEFONT_FLAG_DEFAULT) & 0x7FFF);
    clrBtn1.Fontfmt.ifont_gap = LYRIC_FONT_GAP; // Gap number (pixel) of two font
    clrBtn1.u8Gradient = CONSTANT_COLOR;
    clrBtn1.fHighLight = FALSE;

    clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

    #if( DYNAMIC_VECTOR_FONT_ENABLE == 0)
    MDrv_GE_GetFontInfo(Font[FONT_CHINESE].fHandle, &finfo);

    clrBtn1.Fontfmt.flag |= GEFONT_FLAG_SCALE;
    clrBtn1.Fontfmt.height = finfo.height * 2;
    clrBtn1.Fontfmt.width  = finfo.width * 2;
    #else
    //clrBtn1.Fontfmt.flag |= GEFONT_FLAG_SCALE;
    clrBtn1.Fontfmt.height = MS_DYNAMIC_FONTSIZE ;
    clrBtn1.Fontfmt.width  = MS_DYNAMIC_FONTSIZE ;
    #endif
    //clrBtn1.Fontfmt.dis = 0;
    clrBtn1.y += KTV_LYRIC_DISP_VSIZE - clrBtn1.Fontfmt.height / 2; // Height of space
    clrBtn1.height = clrBtn1.Fontfmt.height + LYRIC_FONTHIGHT_OFFSET;

    iSingText_x = clrBtn1.x;
    iSingText_y = clrBtn1.y;
    iSingText_w = clrBtn1.width;
    iSingText_h = clrBtn1.height;
    iSingText_fw = clrBtn1.Fontfmt.width + clrBtn1.Fontfmt.ifont_gap;
    //printf("\r\n %d   %d  %d   %d   %d", iSingText_x, iSingText_y, iSingText_w, iSingText_h, iSingText_fw);

    iSingcurrentFBId = MApi_GOP_GWIN_GetFBfromGWIN(gop_parameters.u8_GWIN_id);
    if(iSingbufferFBId==GWIN_ID_INVALID)
    {
        iSingbufferFBId = MApi_GOP_GWIN_GetFreeFBID();
        MApi_GOP_GWIN_CreateFB2(iSingbufferFBId, 0, 0, iSingText_w, 3*iSingText_h, DEFAULT_FB_FMT);
        iSingText_line_w[0] = 0;
        iSingText_line_w[1] = 0;
        iSingText_line_w[2] = 0;
    }
}

static void MApp_UiMenu_iSingCloseDrawSubtitle(void)
{
    if(iSingbufferFBId!=GWIN_ID_INVALID)
    {
        MApi_GOP_GWIN_DeleteFB(iSingbufferFBId);
    }
    iSingbufferFBId=GWIN_ID_INVALID;
}

static void MApp_UiMenu_iSingDrawSubtitle(U8 line)
{
    U16 *pu16Str;
    S16 i;
    U8  u8CharPerLine;
    MSAPI_OSDRegion src;
    MSAPI_OSDRegion dst;

    pu16Str = (U16*)au8LineSection;
    u8CharPerLine = 0;
    for(i=0;
        (i<256) &&
        (pu16Str[i] != 0x0000);
        i++)
    {
        if(0==(i%3))
        {
            u8CharPerLine++;
            if(u8CharPerLine >= (U8)KTV_UI_CHAR_PER_LINE) // Specify the maximum characters per line.
            {
                pu16Str[i] = 0x0000;
                break;
            }
        }
    }
    pu16Str[i] = 0x0000;

    if((clrBtn1.y >=iSingText_h)&&(line>0)&&(line<3))
    {
        if(line == 2)
        {
            clrBtn1.x = iSingText_xoffset + u16SingerNameDisplayOffset;
        }
        else
        {
            clrBtn1.x = u16SongNameDisplayOffset;
        }
        clrBtn1.y = iSingText_y-(3-line)*iSingText_h;
        clrBtn1.b_clr = COLOR_TRANSPARENT;
        msAPI_OSD_DrawBlock(&clrBtn1);
        /*clrBtn1.t_clr = COLOR_RED;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif*/
#if 1 //TEST
        clrBtn1.t_clr = COLOR_LTGRAY;
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x -= LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE;
        clrBtn1.y += LYRIC_FONT_FRAME_SIZE;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.y -= LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x -= LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.y += LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        // Center
        clrBtn1.x -= LYRIC_FONT_FRAME_SIZE;
        clrBtn1.y -= LYRIC_FONT_FRAME_SIZE;
        clrBtn1.t_clr = COLOR_RED;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
#endif

        dst.fbID=iSingbufferFBId;
        if(line == 2)
        {
            dst.x= iSingText_xoffset;
        }
        else
        {
            dst.x=0;
        }
        dst.y=line*iSingText_h;
        dst.width=iSingText_w;
        dst.height=iSingText_h;

        src.fbID=iSingcurrentFBId;
        if(line == 2)
        {
            src.x=iSingText_x + iSingText_xoffset;
        }
        else
        {
            src.x=iSingText_x;
        }
        src.y=iSingText_y-(3-line)*iSingText_h;
        src.width=iSingText_w;
        src.height=iSingText_h;

        msAPI_OSD_CopyRegion(&src, &dst);

        /*clrBtn1.x += 4;
        clrBtn1.t_clr = COLOR_LTGRAY;

        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif*/
#if 1 //TEST
        clrBtn1.t_clr = COLOR_BLUE;
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x -= LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE;
        clrBtn1.y += LYRIC_FONT_FRAME_SIZE;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.y -= LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x -= LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.y += LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        clrBtn1.x += LYRIC_FONT_FRAME_SIZE * 2;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
        // Center
        clrBtn1.x -= LYRIC_FONT_FRAME_SIZE;
        clrBtn1.y -= LYRIC_FONT_FRAME_SIZE;
        clrBtn1.t_clr = COLOR_LTGRAY;
        //printf( "\r\n y = %d", clrBtn1.y);
        #if DYNAMIC_VECTOR_FONT_ENABLE
        msAPI_OSD_DrawText( Font[FONT_DYNAMIC_MVF_EXT].fHandle, au8LineSection, &clrBtn1 );
        #else
        msAPI_OSD_DrawText( Font[FONT_CHINESE].fHandle, au8LineSection, &clrBtn1 );
        #endif
#endif

    }
    else if((clrBtn1.y >=iSingText_h)&&(line==0))
    {
            U8 r_clr, g_clr, b_clr;
            U8 i;

            //#if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444 || MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
            //for ARGB4444 and ARGB8888, use bitmap original alpha value
            //MDrv_GE_SetAlpha(TRUE, COEF_ASRC, ABL_FROM_ASRC, 0);
            //#endif

            clrBtn1.x = 0;
            clrBtn1.y = 0;

            gbmpfmt.width = KTV_DOWNCOUNTER_BMP_SIZE;
            gbmpfmt.height = KTV_DOWNCOUNTER_BMP_SIZE;

            gbmpfmt.bScale = TRUE;

            gbmpfmt.bBmpColorKeyEnable = TRUE;

            r_clr=((0xF800F8&0x00ff0000)>>16)&0xff;
            g_clr=((0xF800F8&0x0000ff00)>>8)&0xff;
            b_clr=((0xF800F8&0x000000ff))&0xff;

            gbmpfmt.clrrange.color_s.a = 0;
            gbmpfmt.clrrange.color_s.r = r_clr;
            gbmpfmt.clrrange.color_s.g = g_clr;
            gbmpfmt.clrrange.color_s.b = b_clr;

            r_clr=((0xFF00FF&0x00ff0000)>>16)&0xff;
            g_clr=((0xFF00FF&0x0000ff00)>>8)&0xff;
            b_clr=((0xFF00FF&0x000000ff))&0xff;

            gbmpfmt.clrrange.color_e.a = 0;
            gbmpfmt.clrrange.color_e.r = r_clr;
            gbmpfmt.clrrange.color_e.g = g_clr;
            gbmpfmt.clrrange.color_e.b = b_clr;
            switch(au8LineSection[0]  )
            {
                case '4' :
                    for(i=0; i<4; i++)
                    {
                        msAPI_OSD_DrawColorKeyBitmap(KTV_DOWNCOUNTER_BMP, clrBtn1.x + (KTV_DOWNCOUNTER_BMP_SIZE + KTV_DOWNCOUNTER_BMP_GAP)* i, clrBtn1.y, gbmpfmt);
                    }
                    break;
                case '3' :
                    _MApp_KTV_ClearDisplayBlock(gop_parameters.u8_GWIN_id, clrBtn1.x + (KTV_DOWNCOUNTER_BMP_SIZE + KTV_DOWNCOUNTER_BMP_GAP) * 3, 0, KTV_DOWNCOUNTER_BMP_SIZE, KTV_DOWNCOUNTER_BMP_SIZE);
                    break;
                case '2' :
                    _MApp_KTV_ClearDisplayBlock(gop_parameters.u8_GWIN_id, clrBtn1.x + (KTV_DOWNCOUNTER_BMP_SIZE + KTV_DOWNCOUNTER_BMP_GAP) * 2, 0, KTV_DOWNCOUNTER_BMP_SIZE, KTV_DOWNCOUNTER_BMP_SIZE);
                    break;
                case '1' :
                    _MApp_KTV_ClearDisplayBlock(gop_parameters.u8_GWIN_id, clrBtn1.x + (KTV_DOWNCOUNTER_BMP_SIZE + KTV_DOWNCOUNTER_BMP_GAP) * 1, 0, KTV_DOWNCOUNTER_BMP_SIZE, KTV_DOWNCOUNTER_BMP_SIZE);
                    break;
                default:
                    _MApp_KTV_ClearDisplayBlock(gop_parameters.u8_GWIN_id, clrBtn1.x, 0, KTV_DOWNCOUNTER_BMP_SIZE, KTV_DOWNCOUNTER_BMP_SIZE);
                    break;
            }

            //#if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444 || MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
            //MDrv_GE_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, 0xFF);
            //#endif
    }
    iSingText_time[line]=0;
    iSingText_line_w[line]=0;
    iSingText_remain_line[line]=0;
}

//------------------------------------------------------------------------------------------------
// [Use for iSing99 lyric parser]
// [  Function  ]  _MApp_MIC_ScanfLrCTime
// [ Description ]  Get lyric start time and weather the lyric need brush color or not. The data format must
//                be unicode.
// [    Input   ]  *pu8Data must point to the start of one line MIC lyric.
//                ColorBrush use to get the offset  of numbers.
// [   Output   ]  convert numbers for unicode to U32 data and put into pu32Ms[0].
// [   Return   ]  0 and 1 fail,  3  success.
//
//------------------------------------------------------------------------------------------------
static U8 _MApp_MIC_ScanfLrCTime(U8  *pu8Data, U32 *pu32Ms, BOOLEAN ColorBrush)
{
    U16 u16Index = 6;

    if( pu8Data == NULL || pu32Ms == NULL )
    {
        return 0;
    }
    *pu32Ms = 0;

    if(FALSE == ColorBrush)
        u16Index += 6;

    // Scan Ms
    pu32Ms[0] = 0;
    for(; pu8Data[u16Index] >= '0' && pu8Data[u16Index] <= '9';  u16Index += 2)
    {
        pu32Ms[0] = pu32Ms[0] * 10 + (U32)(pu8Data[u16Index] - '0');
    }

    if( pu32Ms[0] < 1000 )
    {
        return 1;
    }

    return 3;
}



//*****************************************************************************
//              Global Functions
//*****************************************************************************

BOOLEAN MApp_UiMenu_iSingOpenSubtitle(void)
{
    if(_MApp_KTV_OpenSubtitleWin() == FALSE)
        return FALSE;
    MApp_UiMenu_iSingOpenDrawSubtitle();
    return TRUE;
}

void MApp_UiMenu_iSingCloseSubtitle(void)
{
    _MApp_KTV_CloseSubtitleWin();
    MApp_UiMenu_iSingCloseDrawSubtitle();
    iSingText_remain_line[0] = 0;
    iSingText_remain_line[1] = 0;
    iSingText_remain_line[2] = 0;
}

void MApp_UiMenu_iSingDisplaySubtitle(U8 line)
{

    MApp_coexistWin_SwitchGwin();
    if(!_b_KTV_Gwin_created)
    {
        _MApp_KTV_OpenSubtitleWin();
    }

    MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);
    MApp_UiMenu_iSingOpenDrawSubtitle();
    MApp_UiMenu_iSingDrawSubtitle(line);
    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, TRUE);

    MApp_coexistWin_RestoreGwin();
}

void MApp_UiMenu_iSingDrawSubtitleChar(U8 line, U16 time)
{
    MSAPI_OSDRegion src;
    MSAPI_OSDRegion dst;

    MApp_coexistWin_SwitchGwin();
    if(iSingText_remain_line[line])
    {
        dst.fbID=iSingcurrentFBId;
        if(line == 2)
        {
            dst.x=iSingText_x + iSingText_xoffset + iSingText_line_w[line];
        }
        else
        {
            dst.x=iSingText_x+iSingText_line_w[line];
        }
        dst.y=iSingText_y-(3-line)*iSingText_h;
        dst.width=iSingText_remain_line[line];
        dst.height=iSingText_h;

        src.fbID=iSingbufferFBId;
        if(line == 2)
        {
            src.x = iSingText_xoffset + iSingText_line_w[line];
        }
        else
        {
            src.x = iSingText_line_w[line];
        }
        src.y=line*iSingText_h;
        src.width=iSingText_remain_line[line];
        src.height=iSingText_h;

        msAPI_OSD_CopyRegion(&src, &dst);
        iSingText_line_w[line]+=iSingText_remain_line[line];
    }

    iSingText_remain_line[line]=iSingText_fw * u8CharNum;
    iSingText_time[line]= (U8)(time/(iSingText_fw * u8CharNum));
    MApp_coexistWin_RestoreGwin();
}

void MApp_UiMenu_iSingDrawSubtitleMonitor(void)
{
    MSAPI_OSDRegion src;
    MSAPI_OSDRegion dst;

    if ((msAPI_Timer_DiffTimeFromNow(Waittime0) > iSingText_time[0])&&(iSingText_remain_line[0]))
    {
        MApp_coexistWin_SwitchGwin();
        Waittime0 = msAPI_Timer_GetTime0();
        dst.fbID=iSingcurrentFBId;
        dst.x=iSingText_x+iSingText_line_w[0];
        dst.y=iSingText_y-(3-0)*iSingText_h;
        dst.width=1;
        dst.height=iSingText_h;

        src.fbID=iSingbufferFBId;
        src.x=iSingText_line_w[0];
        src.y=0*iSingText_h;
        src.width=1;
        src.height=iSingText_h;

        msAPI_OSD_CopyRegion(&src, &dst);
        iSingText_line_w[0]++;
        iSingText_remain_line[0]--;
        MApp_coexistWin_RestoreGwin();
    }

    if ((msAPI_Timer_DiffTimeFromNow(Waittime1) > iSingText_time[1])&&(iSingText_remain_line[1]))
    {
        MApp_coexistWin_SwitchGwin();
        Waittime1 = msAPI_Timer_GetTime0();
        dst.fbID=iSingcurrentFBId;
        dst.x=iSingText_x+iSingText_line_w[1];
        dst.y=iSingText_y-(3-1)*iSingText_h;
        dst.width=1;
        dst.height=iSingText_h;

        src.fbID=iSingbufferFBId;
        src.x=iSingText_line_w[1];
        src.y=1*iSingText_h;
        src.width=1;
        src.height=iSingText_h;

        msAPI_OSD_CopyRegion(&src, &dst);
        iSingText_line_w[1]++;
        iSingText_remain_line[1]--;
        MApp_coexistWin_RestoreGwin();
    }

    if ((msAPI_Timer_DiffTimeFromNow(Waittime2) > iSingText_time[2])&&(iSingText_remain_line[2]))
    {
        MApp_coexistWin_SwitchGwin();
        Waittime2 = msAPI_Timer_GetTime0();
        dst.fbID=iSingcurrentFBId;
        dst.x=iSingText_x + iSingText_xoffset + iSingText_line_w[2];
        dst.y=iSingText_y-(3-2)*iSingText_h;
        dst.width=1;
        dst.height=iSingText_h;

        src.fbID=iSingbufferFBId;
        src.x= iSingText_xoffset + iSingText_line_w[2];
        src.y=2*iSingText_h;
        src.width=1;
        src.height=iSingText_h;

        msAPI_OSD_CopyRegion(&src, &dst);
        iSingText_line_w[2]++;
        iSingText_remain_line[2]--;
        MApp_coexistWin_RestoreGwin();
    }
}

//------------------------------------------------------------------------------------------------
// [Use for iSing99 lyric parser]
// [  Function  ]  MApp_MIC_LyricInit
// [Description]  Initialize u16LyricTagCount to 0.
// [    Input    ]  N/A
// [    Output  ]  N/A
// [    Return  ]  N/A
//
//------------------------------------------------------------------------------------------------
void MApp_MIC_LyricInit(void)
{
    u16LyricTagCount = 0;
    u16LyricWordsCount = 0;
    u32LyricFileLen = 0;
    u32MicFileLen = 0;
    u16SongNameDisplayOffset = 0;
    u16SingerNameDisplayOffset = 0;
}

//------------------------------------------------------------------------------------------------
// [Use for iSing99 lyric parser]
// [  Function ]  _MApp_KTV_GetLyric
// [Description]  Get one line lyric.
// [   Input  ]  Need the lyric buffer address MUSIC_LYRIC_BUFFER_ADR. The file was in the buffer.
//               u16LyricPos is the position in the lyric file for this line lyric.
// [   Output  ]  pu8Dst is the lyric used to display.
// [   Return  ]  the lyric number
//
//------------------------------------------------------------------------------------------------
U8 _MApp_KTV_GetLyric(U16 u16LyricPos, U8 *pu8Dst)
{
    U16 u16Src, u16Dst;
    U8 u8Data, u8Data1;
    U8 u8CharNumber = 0;

    for(u16Dst=0,u16Src=0;u16Dst<KTV_LYRIC_MAX_SIZE;  )
    {
        msAPI_MIU_Copy(st_KTV_Lyric_buf_adr+u16LyricPos+u16Src,
                       XD2PHY(&u8Data),
                       1,
                       MIU_SDRAM2SDRAM);
        msAPI_MIU_Copy(st_KTV_Lyric_buf_adr+u16LyricPos+u16Src+1,
                       XD2PHY(&u8Data1),
                       1,
                       MIU_SDRAM2SDRAM);
        if((u8Data == 0x0A) && (u8Data1 == 0x00))
        {
            pu8Dst[u16Dst] = 0;
            pu8Dst[u16Dst+1] = 0;
            //pu8Dst[u16Dst+2] = 0;
            //pu8Dst[u16Dst+3] = 0;
            break;
        }
        else
        {
        pu8Dst[u16Dst] = u8Data;
        u16Src ++;
        msAPI_MIU_Copy(st_KTV_Lyric_buf_adr+u16LyricPos+u16Src,
                       XD2PHY(&u8Data),
                       1,
                       MIU_SDRAM2SDRAM);
        pu8Dst[u16Dst+1] = u8Data;
        u16Dst += 2;
        u16Src ++;
              u8CharNumber ++;
        }

    }

    pu8Dst[KTV_LYRIC_MAX_SIZE] = 0;
    pu8Dst[KTV_LYRIC_MAX_SIZE+1] = 0;

    return u8CharNumber;
}

//------------------------------------------------------------------------------------------------
// [Use for iSing99 lyric parser]
// [  Function  ]  MApp_KTV_GetLyricTag
// [ Description  ]  Get one lyric tag from the tag buffer by comparing the start time with the current time.
// [    Input   ]  Need the tag buffer address MUSIC_LYRIC_TAG_ADR. The tags were in the buffer.
//               u32Time -> the current time. The unit is ms.
// [   Output  ]  pLyricTag-> include the start time, the lyric position, the display position and the mark of
//                blushcolor.
//                Duringtime means it uses how much time to blush the word using red color or others.
// [    Return  ]  false-> fail,  true-> success.
//
//------------------------------------------------------------------------------------------------
BOOLEAN MApp_KTV_GetDownCounterLyricTag(U32 u32Time, Music_Mic_Lyric_Tag *pLyricTag)
{
    // Find the lyric which time is less or equal to u32Time.
    Music_Mic_Lyric_Tag *pLyricTagBase;
    S16 i;
    BOOLEAN bRet = FALSE;

    if(u32Time >= u32LyricTotalTime)
        return FALSE;

    pLyricTagBase = (Music_Mic_Lyric_Tag xdata *)st_KTV_Lyric_tags_adr;

    for(i=u16LyricTagCount-1;i>=0;i--)
    {
        if((pLyricTagBase[i].u32Time <= u32Time) && (pLyricTagBase[i].u8DisplayPos == 3))
        {
            pLyricTag->u32Time = pLyricTagBase[i].u32Time;
            pLyricTag->u16LyricPos = pLyricTagBase[i].u16LyricPos;
            pLyricTag->u8DisplayPos = pLyricTagBase[i].u8DisplayPos;
            pLyricTag->u8BlushColor = pLyricTagBase[i].u8BlushColor;
            bRet = TRUE;
            break;
        }
    }

    return bRet;
}
BOOLEAN MApp_KTV_GetLine1LyricTag(U32 u32Time, Music_Mic_Lyric_Tag *pLyricTag,  U16 *Duringtime)
{
    // Find the lyric which time is less or equal to u32Time.
    Music_Mic_Lyric_Tag *pLyricTagBase;
    S16 i, j;
    BOOLEAN bRet = FALSE;

    if(u32Time >= u32LyricTotalTime)
        return FALSE;

    pLyricTagBase = (Music_Mic_Lyric_Tag xdata *)st_KTV_Lyric_tags_adr;

    for(i=u16LyricTagCount-1;i>=0;i--)
    {
        if((pLyricTagBase[i].u32Time <= u32Time) && (pLyricTagBase[i].u8DisplayPos == 1))
        {
            pLyricTag->u32Time = pLyricTagBase[i].u32Time;
            pLyricTag->u16LyricPos = pLyricTagBase[i].u16LyricPos;
            pLyricTag->u8DisplayPos = pLyricTagBase[i].u8DisplayPos;
            pLyricTag->u8BlushColor = pLyricTagBase[i].u8BlushColor;
            if(pLyricTag->u8BlushColor)
            {
                for(j=i+1; j<u16LyricTagCount-1; j++)
                {
                        if(pLyricTagBase[j].u8DisplayPos == 1)
                            break;
                }
                *Duringtime = (U16)(pLyricTagBase[j].u32Time - pLyricTagBase[i].u32Time);
            }
            bRet = TRUE;
            break;
        }
    }

    return bRet;
}
BOOLEAN MApp_KTV_GetLine2LyricTag(U32 u32Time, Music_Mic_Lyric_Tag *pLyricTag,  U16 *Duringtime)
{
    // Find the lyric which time is less or equal to u32Time.
    Music_Mic_Lyric_Tag *pLyricTagBase;
    S16 i, j;
    BOOLEAN bRet = FALSE;

    if(u32Time >= u32LyricTotalTime)
        return FALSE;

    pLyricTagBase = (Music_Mic_Lyric_Tag xdata *)st_KTV_Lyric_tags_adr;

    for(i=u16LyricTagCount-1;i>=0;i--)
    {
        if((pLyricTagBase[i].u32Time <= u32Time) && (pLyricTagBase[i].u8DisplayPos == 2))
        {
            pLyricTag->u32Time = pLyricTagBase[i].u32Time;
            pLyricTag->u16LyricPos = pLyricTagBase[i].u16LyricPos;
            pLyricTag->u8DisplayPos = pLyricTagBase[i].u8DisplayPos;
            pLyricTag->u8BlushColor = pLyricTagBase[i].u8BlushColor;
            if(pLyricTag->u8BlushColor)
            {
                for(j=i+1; j<u16LyricTagCount-1; j++)
                {
                        if(pLyricTagBase[j].u8DisplayPos == 2)
                            break;
                }
                *Duringtime = (U16)(pLyricTagBase[j].u32Time - pLyricTagBase[i].u32Time);
            }
            bRet = TRUE;
            break;
        }
    }

    return bRet;
}

//------------------------------------------------------------------------------------------------
// [Use for iSing99 lyric parser]
// [  Function  ]  MApp_MIC_Lyrics_Parser
// [ Description ]  Get the start time of every word, and the lyric position in the whole lyric file, get the
//                display position(first line or second line),
//                get the mark for blush color.
// [   Input   ]  u32FileSize  is the whole file's size. How mang bytes?
//               MUSIC_LYRIC_BUFFER_ADR is the start pointer of one 64KB buffer. The lyric file
//                was copyed to the buffer.
// [   Output  ]  MUSIC_LYRIC_TAG_ADR use to save the parser result. The buffer size is 4KB. Every
//                tag is Music_Mic_Lyric_Tag struct.
//                u16LyricTagCount is to show how many tags in the lyric file.
// [   Return  ]  false-> fail,  true-> success.
//
//------------------------------------------------------------------------------------------------
BOOLEAN MApp_MIC_Lyrics_Parser(U32 u32FileSize)
{
    #define MIC_LYRIC_CACHE_SIZE      256    //Use to copy one line
    Music_Mic_Lyric_Tag *pLyricTag;
    U32 u32ms;
    U32 u32ParsedPos;
    U16 u16TagStart;
    U16 i;
    U8 u8LyricStartinLine = 0;
    U8 *pu8Data = au8Section;
    U8 u8TagLen = 0, u8count;
    BOOLEAN bTagFound, bValidTagFound, bColorBrush;
    BOOLEAN bRet = FALSE;



#if DEBUG_MIC_LYRIC
    printf("\r MIC_Lyrics_Parser(%ld)\n", u32FileSize);
#endif

    u16LyricTagCount = 0;

    pLyricTag = (Music_Mic_Lyric_Tag xdata *)st_KTV_Lyric_tags_adr;

    // Parse the time
    u32ParsedPos = 0;

    while( (u32ParsedPos < u32FileSize)&&(u16LyricTagCount<KTV_LYRIC_MAX_TAG_COUNT) )
    {
        #if ( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
        #endif
        // Parser tag.Time ...
        bValidTagFound = FALSE;
        while( (u32ParsedPos < u32FileSize)&&(u16LyricTagCount<KTV_LYRIC_MAX_TAG_COUNT) )
        {
            // Search Lyric Tag start point
            bTagFound = FALSE;
            while( u32ParsedPos < u32FileSize )
            {
                msAPI_MIU_Copy(u32ParsedPos + st_KTV_Lyric_buf_adr,
                               XD2PHY(&pu8Data[0]),
                               MIC_LYRIC_CACHE_SIZE,
                               MIU_SDRAM2SDRAM);

                for( i=0; i<MIC_LYRIC_CACHE_SIZE; i++ )
                {
                    if( pu8Data[i] == 'i' )
                    {
                        if( pu8Data[i+2] == 'n' )
                        {
                            for(; i<MIC_LYRIC_CACHE_SIZE; i++)
                            {
                    if( (pu8Data[i+4] == 0x0A) && (pu8Data[i+5] == 0)) // line end
                    {
                        i += 6;
                                    break;
                    }
                            }
                            break;
                        }
                    }
                    else if( pu8Data[i] == 'M' )
                    {
                if( pu8Data[i+2] == 'e' )
                {
                                for(; i<MIC_LYRIC_CACHE_SIZE; i++)
                                {
                        if( (pu8Data[i+4] == 0x0A) && (pu8Data[i+5] == 0)) // line end
                        {
                            i += 6;
                                        break;
                        }
                                }
                    break;
                }
            }
            else if( pu8Data[i] == 'T' )
                    {
                if( pu8Data[i+2] == 'o' )
                {
                                    U8 j;
                                    u32LyricTotalTime = 0;
                                    for(j=26; pu8Data[j] >= '0' && pu8Data[j] <= '9';  j += 2)
                                    {
                                        u32LyricTotalTime = u32LyricTotalTime * 10 + (U32)(pu8Data[j] - '0');
                                    }
                                    KTV_LYRIC_DBG(printf("\r\n u32LyricTotalTime  %d", u32LyricTotalTime););
                                for(; i<MIC_LYRIC_CACHE_SIZE; i++)
                                {
                        if( (pu8Data[i+4] == 0x0A) && (pu8Data[i+5] == 0)) // line end
                        {
                            i += 6;
                                        break;
                        }
                                }
                    break;
                }
            }
            else if( pu8Data[0] == '1' || pu8Data[0] == '2' || pu8Data[0] == '3')
            {
                u8count = 0;
                for(; i<MIC_LYRIC_CACHE_SIZE; i++)
                {
                    if( (pu8Data[i] == 0x0A) && (pu8Data[i + 1] == 0) ) // line end
                    {
                        u8TagLen = i+2;
                                    break;
                    }
                    else if(pu8Data[i] == ':')
                    {
                        u8count++;
                        if(u8count == 2 || u8count == 4)
                            u8LyricStartinLine = i + 4;
                    }
                }
                if(u8count > 3)
                {
                    bColorBrush = FALSE;
                    bTagFound = TRUE;
                    i = 0;
                    break;
                }
                else if(u8count >= 2)
                {
                    bColorBrush = TRUE;
                    bTagFound = TRUE;
                    i = 0;
                    break;
                }
            }
                }
                u32ParsedPos += i;
                if( bTagFound )
                {
                #if DEBUG_MIC_LYRIC
                    printf("Tag found in %ld\n", u32ParsedPos);
                #endif
                    break;
                }
            }

            if( bTagFound )
            {

                // Get time from tag
                msAPI_MIU_Copy(u32ParsedPos + st_KTV_Lyric_buf_adr,
                               XD2PHY(&pu8Data[0]),
                               MIC_LYRIC_CACHE_SIZE,
                               MIU_SDRAM2SDRAM);
                pu8Data[u8TagLen] = '\0';
            #if DEBUG_MIC_LYRIC
                printf(" buf{%s}\n", pu8Data);
            #endif

                if( _MApp_MIC_ScanfLrCTime(pu8Data, &u32ms, bColorBrush) < 2 )
                {
                    // Invalid tag ...
                #if DEBUG_MIC_LYRIC
                    printf(" Invalid tag\n");
                #endif
                }
                else
                {
                    // Valid tag found ...
                    bValidTagFound = TRUE;

                    pLyricTag[u16LyricTagCount].u32Time =u32ms;
                    pLyricTag[u16LyricTagCount].u16LyricPos = (U16)u32ParsedPos + (U16)u8LyricStartinLine;
                    pLyricTag[u16LyricTagCount].u8DisplayPos = pu8Data[0] - '0';
                    pLyricTag[u16LyricTagCount].u8BlushColor = (U8)bColorBrush;
                #if DEBUG_MIC_LYRIC
                    #if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
                    #endif
                    printf(" TagTime=%ld\n", pLyricTag[u16LyricTagCount].u32Time);
                    printf(" u16LyricPos=%x\n", pLyricTag[u16LyricTagCount].u16LyricPos);
                    printf(" u8DisplayPos=%bx\n", pLyricTag[u16LyricTagCount].u8DisplayPos);
                    printf(" u8BlushColor=%bx\n", pLyricTag[u16LyricTagCount].u8BlushColor);
                    printf(" u16LyricTagCount=%x\n", u16LyricTagCount);
                #endif
                    u16LyricTagCount ++;
                }
                u32ParsedPos += u8TagLen;
            }

        }

    }

    // Sort by time stamp.
    if( u16LyricTagCount > 1 )
    {
        bRet = TRUE;
        for(u16TagStart=0; u16TagStart<u16LyricTagCount-1; u16TagStart++)
        for(i=u16TagStart+1; i<u16LyricTagCount; i++)
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif
            if(pLyricTag[i].u32Time < pLyricTag[u16TagStart].u32Time)
            {
                U32 u32Temp;
                U8 u8Temp;

                u32Temp = pLyricTag[i].u32Time;
                pLyricTag[i].u32Time = pLyricTag[u16TagStart].u32Time;
                pLyricTag[u16TagStart].u32Time = u32Temp;
                u32Temp = pLyricTag[i].u16LyricPos;
                pLyricTag[i].u16LyricPos = pLyricTag[u16TagStart].u16LyricPos;
                pLyricTag[u16TagStart].u16LyricPos = u32Temp;
                u8Temp = pLyricTag[i].u8DisplayPos;
                pLyricTag[i].u8DisplayPos = pLyricTag[u16TagStart].u8DisplayPos;
                pLyricTag[u16TagStart].u8DisplayPos = u8Temp;
                u8Temp = pLyricTag[i].u8BlushColor;
                pLyricTag[i].u8BlushColor = pLyricTag[u16TagStart].u8BlushColor;
                pLyricTag[u16TagStart].u8BlushColor = u8Temp;
            }
        }
#if DEBUG_MIC_LYRIC
        printf("\r u16LyricTagCount=%d\n",u16LyricTagCount);
        for(i=0; i<u16LyricTagCount; i++)
        {
            printf("Time = %ld, %x\n", pLyricTag[i].u32Time, pLyricTag[i].u16LyricPos);
            printf("u8DisplayPos = %bx,  u8BlushColor = %bx\n", pLyricTag[i].u8DisplayPos, pLyricTag[i].u8BlushColor);
        }
#endif
    }

    // Get all lyric for dynamic load font
    if( u16LyricTagCount > 1 )
    {
        U16 u16Src, u16Dst = 0;
        U8 u8Data, u8Data1;

        for(u16TagStart=0; u16TagStart<u16LyricTagCount-1; u16TagStart++)
        {
            for(u16Src=0; u16Src<KTV_LYRIC_MAX_SIZE;  )
            {
                msAPI_MIU_Copy(st_KTV_Lyric_buf_adr + pLyricTag[u16TagStart].u16LyricPos + u16Src,
                               XD2PHY(&u8Data),
                               1,
                               MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(st_KTV_Lyric_buf_adr + pLyricTag[u16TagStart].u16LyricPos + u16Src+1,
                               XD2PHY(&u8Data1),
                               1,
                               MIU_SDRAM2SDRAM);
                if((u8Data == 0x0A) && (u8Data1 == 0x00))
                {
                    u8Data = 0;
                msAPI_MIU_Copy(XD2PHY(&u8Data),  st_KTV_Lyric_words_adr + u16Dst,  1, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(XD2PHY(&u8Data),  st_KTV_Lyric_words_adr + u16Dst+1,  1, MIU_SDRAM2SDRAM);
                    break;
                }
                else
                {
                msAPI_MIU_Copy(XD2PHY(&u8Data),  st_KTV_Lyric_words_adr +  u16Dst,  1, MIU_SDRAM2SDRAM);
                u16Dst ++;
                u16Src ++;
                msAPI_MIU_Copy(st_KTV_Lyric_buf_adr+pLyricTag[u16TagStart].u16LyricPos+u16Src,
                               XD2PHY(&u8Data),
                               1,
                               MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(XD2PHY(&u8Data),  st_KTV_Lyric_words_adr + u16Dst,  1, MIU_SDRAM2SDRAM);
                u16Dst ++;
                u16Src ++;
                    u16LyricWordsCount ++;
                }

            }
        }

        #if DEBUG_MIC_LYRIC
        pu8Data = (U8 xdata *)st_KTV_Lyric_words_adr;
        printf("  \r u16LyricWordsCount[%d] \n", u16LyricWordsCount);
        for(i=0; i<u16LyricWordsCount * 2; i++)
        {
            printf("  [%bx] ", pu8Data[i]);
        }
        #endif

    }

    return bRet;
}

#endif


#undef MAPP_KTV_C

