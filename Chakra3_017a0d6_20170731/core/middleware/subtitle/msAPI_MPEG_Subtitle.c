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
//-------------------------------------------------------------------------------------------------
// File Name:
//          msAPI_MPEG_Subtitle.c
// Description:
//          This file is Mpeg2, Mpeg4 subtitle decode engine that receives SPU packet then to decode and draw
//
// Note:
//          MStarSemi Inc.
//-------------------------------------------------------------------------------------------------

#define MSAPI_MPEG_SUBTITLE_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datatype.h"
#include "debug.h"

// Common Definition
#include "MsCommon.h"
#include "Board.h"
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY))
#include "msAPI_Global.h"
#endif
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "apiGOP.h"
#include "apiXC.h"
#include "msAPI_OSD.h"
#include "msAPI_Video.h"
#include "msAPI_MPEG_Subtitle.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "apiPNL.h"

#ifdef MSOS_TYPE_LINUX
#include "MsOS.h"
#endif

#include "msAPI_MMap.h"

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
/*** Free Type Library ***/
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#endif
#include "debug.h"
//#if(!((CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J)&&(MEMORY_MAP == MMAP_64MB)))



#if (ENABLE_SUBTITLE_DMP)
#define MAX_CMD_QUEUE_SIZE  30
#define SBTL_ERR(x)     //x
#define SBTL_TRACE(x)   //x
#define SBTL_DBG(x)     //x
#define SBTL_DATA(x)    //x
#define RLD_ALIGNMENT_REQUIRED
#define SUBTITLE_DEFAULT_SHOW_STATUS    TRUE
//#define GOP_USE_ARGB1555    FALSE
//#if (GOP_USE_ARGB1555) // use ARGB1555
//#define GOP_GWIN_FORMAT     GFX_FMT_ARGB1555//GFX_FMT_I8    //GFX_FMT_ARGB4444
//#else
//#define GOP_GWIN_FORMAT     GFX_FMT_I8    //GFX_FMT_ARGB4444
//#endif
#define GWIN_WIDTH_LIMIT    0x760
#define GWIN_HEIGHT_LIMIT   0x430
#define RAWDATA_WIDTH       100
//#if ((GWIN_WIDTH_LIMIT) * (GWIN_HEIGHT_LIMIT) +0x4000 > (GE_FRAMEBUFFER_LEN))
//#error "GE frame buffer to small to create MM subtitle Gwin"
//#endif

#define PALETTE_TABLE_SIZE  16
#define PALETTE_UNIT        4
#define SUBTL_ABOVE_BOTTOM     20
#ifndef ROUND_UP
#define ROUND_UP(size, granule) ((size)%(granule) ? (granule)*((size)/(granule)+1) : (size))
#endif
#ifndef ROUND_DOWN
#define ROUND_DOWN(size, granule)   ((size)/(granule)*(granule))
#endif
#define INTERPOLATION(X0, X1, Y0) (((U32)X1 * Y0) / (X0)) // X0:X1 = Y0:Y1

#define REDUCE_GWIN         TRUE

#if (ENABLE_DIVX_SUBTITLE_OP || ENABLE_VOB_SUBTITLE_OP)
#define GWIN_WIDTH  1360
#define GWIN_HEIGHT 768
#endif
#define SUBTITLE_DIFF_VIDEO_SCREEN 50
#define SUBTITLE_MAX_SEREEN_RATIO 3

// define for Queue
typedef struct _QueueElement
{
    U32 u32Address;
    U16 u16Len;      // The maximum SP length is 64k
    U32 u32PTS;
    U32 u32Duration;
    EN_VDP_CODECID enSubType;
}StQueueElement;   // 11 bytes


typedef struct _SpuQueue {
    StQueueElement contents[MAX_SPU_QUEUE_SIZE];
    U8 u8Front;
    U8 u8Count;
} StSpuQueue;

#define MPEG_SUB_CMD_EX_FIELD_LEN   6
typedef struct _Cmd{
    U32 u32Pts;
    U8  u8cmdCode;
    U8  extendField[MPEG_SUB_CMD_EX_FIELD_LEN];   // 11 bytes
} StCmd;

typedef struct _CmdQueue{
    StCmd   cmd[MAX_CMD_QUEUE_SIZE];
    U8  u8Front;
    U8  u8Count;
} StCmdQueue;

typedef struct _DisplayParam
{
    BOOLEAN bDisplayFlag;
    U8    u8Emp1Color;
    U8    u8Emp2Color;
    U8    u8PatternColor;
    U8    u8BkgrdColor;

    U8    u8Emp1Contrast;
    U8    u8Emp2Contrast;
    U8    u8PatternContrast;
    U8    u8BkgrdContrast;

    U16    u16AreaLeft;
    U16    u16AreaRight;
    U16    u16AreaTop;
    U16    u16AreaBottom;
    U16 u16Width;
    U16 u16Height;

    U16 u16RLTopField;
    U16 u16RLBottomField;
    U16 u16RLTopLen;
    U16 u16RLBottomLen;

}StDisplayParam;    // 31 bytes

typedef struct
{
    U8      u8_GWIN_id;

    U16     u16_GWIN_left;
    U16     u16_GWIN_top;
    U16     u16_GWIN_width;
    U16     u16_GWIN_height;
} GOP_PARAM;

///////////////////Local Functions ///////////////////////////////////////
BOOLEAN msAPI_MpegSP_SpuQueue_Init( void );
void msAPI_MpegSP_SpuQueue_DeInit( void );
void msAPI_MpegSP_SpuQueue_Reset( void );
BOOLEAN msAPI_MpegSP_SpuQueue_Pop( StQueueElement *qe);
BOOLEAN msAPI_MpegSP_SpuQueue_CheckPTS( U32 u32STC );

void msAPI_Decode_SPU(void);
BOOLEAN msAPI_MpegSP_Decoder_SPU( void );
void msAPI_DivXSP_ResetPixelBuffer(U16 _u16VideoHSize, U16 _u16VideoVSize);
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
static void msAPI_DivXTTF_ResetPixelBuffer(U16 _u16VideoHSize, U16 _u16VideoVSize);
static BOOLEAN msAPI_DivXTTF_Decoder_SPU( void );
static BOOLEAN msAPI_DivXTTF_Renderer_Display(void);
static BOOLEAN msAPI_DivXTTF_Decode_RLE(U32 u32RldOutputAddr, U8 u8TransPaletteIdx);
static void msAPI_DivXTTF_DrawBitmap( FT_Bitmap *pbitmap, U32 u32Position_x, U32 u32Position_y, U16 u16Left, U16 u16Top, U16 u16Rows, U16 u16Width);
static void SW_TTF_RLDI2( U8 u8TransPaletteIdx );
#endif
BOOLEAN msAPI_DivXSP_Decoder_SPU( void );
BOOLEAN msAPI_MpegSP_Decoder_Header( void );
BOOLEAN msAPI_MpegSP_Decoder_DCSQT( void );
U16 msAPI_MpegSP_Decoder_DCSQ(U16 addr);
BOOLEAN    msAPI_MpegSP_Decoder_DCCMDs(U32 pu32ReadAddr, U32 u32CmdStm);
void msAPI_MpegSP_CmdQueue_init(void);
BOOLEAN msAPI_MpegSP_CmdQueue_push(U32 u32Stm, U8 cmdCode, U8 *extendfield, U8 extendLen);
BOOLEAN msAPI_MpegSP_CmdQueue_pop(StCmd* pCmd);
U8 msAPI_MpegSP_CmdQueue_Size(void);
void msAPI_MpegSP_CmdQueue_Exec(U32 u32Stc);
BOOLEAN msAPI_MpegSP_CmdQueue_CheckStm(U32 u32STC);
BOOLEAN msAPI_MpegSP_SPU_GetByte(U32 u32ReadAddr, U8 *pu8buf );
BOOLEAN msAPI_MpegSP_SPU_GetWord(U32 u32ReadAddr, U16 *pu16buf );
//BOOLEAN msAPI_MpegSP_SPU_GetWordLsbf(U32 u32ReadAddr, U16 *pu16buf );
BOOLEAN msAPI_MpegSP_SPU_GetBuf(U32 u32ReadAddr, U8 *pu8buf, U16 u16Size );
BOOLEAN msAPI_MpegSP_SpuQueue_PeekN( StQueueElement *qe, U8 u8N );
void msAPI_MpegSP_SetMemoryLayout( void );
void msAPI_MpegSP_Clear_OffScreenBuffer(U8 u8TransPaletteIdx);
BOOLEAN msAPI_MpegSP_Renderer_Init(void);
static void msAPI_MpegSP_Renderer_ClearDisplayBlock(U8 u8_GWID, U16 u16_x, U16 u16_y, U16 u16_width, U16 u16_height );
static U8 msAPI_MpegSP_SetGopPalette(void);
static BOOLEAN msAPI_MpegSP_Renderer_Display( void );
static void msAPI_MpegSP_Renderer_DeInit( void );
static BOOLEAN msAPI_MpegSP_Decode_RLE(U32 u32RldOutputAddr, U8 u8TransPaletteIdx);
static void maAPI_MpegSP_SetPaletteIdx( void );
static U8 subPicGetBit(U8 Num);
void DUMP_SW_RLD_DATA(U16 i, U8 PxlData);
static void SW_RLDI2( U8 u8TransPaletteIdx );

static StQueueElement qeCur;
static StQueueElement qePreDisp;
static StSpuQueue *pstSpuQueue = NULL;
static StCmdQueue *pstCmdQueue = NULL;
static StDisplayParam *pstDisplayParam = NULL;
static stRLDParameters *pstSpRld = NULL;
static GERGBColor   *pPaletteTable=NULL;

static U16 _u16_SPU_length, _u16_DCSQCT_addr;
static BMPHANDLE  hBMP = 0;
static GOP_PARAM  gop_parameters;
static GERGBColor   gePaletteBkg;
static GERGBColor   gePalettePat;
static GERGBColor   gePaletteEmp1;
static GERGBColor   gePaletteEmp2;

static U32 _u32SPUQueueAddress;
static U8  _u8OrigGwinId;
static U16 _u16ClipLeft,_u16ClipTop, _u16ClipRight, _u16ClipBottom;
static BOOLEAN _b_MpegSP_inited = FALSE;
static BOOLEAN _b_MpegSP_Gwin_created = FALSE;
static BOOLEAN _bVobSubPaletteSetted = FALSE;
static U16 _u16FullPixelBuffer_Width=0;
static U16 _u16FullPixelBuffer_Pitch=0;
static U16 _u16FullPixelBuffer_Height=0;
static U32 _u32RLBuffAddr;
static U8 _u8LeftBit=0;

static U8 _u8IdxInnerCheck;
static U8 _u8container;
static U32 _u32_SPU_Display_Pts = 0;
static U8 _u8XPosScale=0xFF;
static U8 _u8YPosScale=0xFF;
static U16 _u16FinetunedBot;

static U32 SP_PIXELBUFFER_OFFSET_ADR;
static U32 SP_PIXELBUFFER_ADR;
static U32 SP_STREAM_BUF_ADR;
static U32 SP_STREAM_BUF_LEN;
static U32 SP_RL_FIELD_ADR;
static U16 _u16RleLeftLen;
static U8  _u8SetGwinFormat = 1;    //GOP Gwin default is ARGB4444
static U16 GOP_GWIN_FORMAT = 0;
BOOLEAN _b_MpegSP_Show = FALSE;
BOOLEAN _b_MpegSP_Status2Show = TRUE; // true to coexist with OSD

// highlight subtitle variables
static BOOLEAN _bEnableHighLight = FALSE;
static BOOLEAN _bEnableSubtitleOP = FALSE;
static U16 _u16Highlight_X;
static U16 _u16Highlight_Y;
static U16 _u16Highlight_W;
static U16 _u16Highlight_H;
static U32 _u32Highlight_Palette;
static U32 _u32Highlight_Pts;
static U16 _u16VideoWidth = 0;
static U16 _u16VideoHeight = 0;

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
//Type Type Font Rendering
static FT_Library _pFTLib;
static FT_Face _pFTFace;
#endif

/////////////////////////////////////////////////////////////////////////
void msAPI_MpegSP_Reset_SpuQueue(void)
{
    SBTL_TRACE(printf("\n MpegSp Reset spu Queue"););
    if(_b_MpegSP_inited)
    {
        _u32SPUQueueAddress = SP_STREAM_BUF_ADR;
        _u8IdxInnerCheck = 0xFF;      //reset emp1Idx for auto detect
        _u32_SPU_Display_Pts = 0;
        msAPI_MpegSP_SpuQueue_Reset();
        if(_b_MpegSP_Gwin_created)
            MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
    }
}

BOOLEAN msAPI_MpegSP_Init(void)
{
    if(!_b_MpegSP_inited)
    {
        SBTL_TRACE(printf("\n mpegSP Init"););
        if(msAPI_MpegSP_SpuQueue_Init()== FALSE)
        {
            return FALSE;
        }
        _u32SPUQueueAddress = SP_STREAM_BUF_ADR;
        SBTL_TRACE(printf("\n streamBufAdr:%lx", SP_STREAM_BUF_ADR););

        msAPI_MpegSP_CmdQueue_init();
        msAPI_MpegSP_SpuQueue_Reset();
        memset(&qeCur,0,sizeof(StQueueElement));
        _u8XPosScale=0xFF;
        _u8YPosScale=0xFF;
        _u8IdxInnerCheck = 0xFF;      //reset emp1Idx for auto detect
        _u16FullPixelBuffer_Width=0;
        _u16FullPixelBuffer_Height=0;
        _b_MpegSP_Show = FALSE;
        _b_MpegSP_inited = TRUE;
        memset(&qePreDisp,0x0,sizeof(StQueueElement));
    }

    return TRUE;
}

void msAPI_MpegSP_Dinit(void)
{
    if(_b_MpegSP_inited)
    {
        SBTL_TRACE(printf("\n mpegSP deinit"););
        msAPI_MpegSP_SpuQueue_DeInit();
        msAPI_MpegSP_Renderer_DeInit();
        _bVobSubPaletteSetted = FALSE;
        _b_MpegSP_Show = FALSE;
        _u16FullPixelBuffer_Width=0;
        _u16FullPixelBuffer_Height=0;
        _b_MpegSP_inited = FALSE;
    }
    else if(_b_MpegSP_Gwin_created)
    {
        msAPI_MpegSP_Renderer_DeInit();
    }
}


void msAPI_MpegSP_Main(U32 u32Stc)
{
    //printf("\n Sub main cur stc:%d!!!!!", u32Stc);

    msAPI_MpegSP_Init();

    if(!_b_MpegSP_Show)
    {
        if(_u32_SPU_Display_Pts >0 && _b_MpegSP_Gwin_created)
        {
            MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
            _u32_SPU_Display_Pts = 0;
            SBTL_TRACE(printf("\n re unshow again in main() "););
        }
        return;
    }



    if(! _b_MpegSP_Status2Show)
    {   // to free gwin memory
        msAPI_MpegSP_Renderer_DeInit();
        return;
    }

    if( msAPI_MpegSP_SpuQueue_CheckPTS(u32Stc) )    // STC larger than any SPU PTS
    {
        StQueueElement nextQE;

        while(1)
        {
            msAPI_MpegSP_SpuQueue_Pop(&qeCur);

            if (msAPI_MpegSP_SpuQueue_PeekN(&nextQE, 0) == TRUE)
            {
                if (nextQE.u32PTS < u32Stc)
                {
                    SBTL_TRACE(printf("\n next elem pts:%lx less than Stc:%lx", nextQE.u32PTS, u32Stc););
                    continue;
                }
            }
            break;
        }

        if(!_b_MpegSP_Gwin_created)
        {
            if(!msAPI_MpegSP_Renderer_Init())
            {
                return; // failed to renderer init
            }
        }

        if(u32Stc >= qeCur.u32PTS)   // show the element only if pts less than Stc
        {
            msAPI_Decode_SPU();
        }
    }

    if(msAPI_MpegSP_CmdQueue_CheckStm(u32Stc))    // STC larger than first cmd STM
    {
        SBTL_TRACE(printf("\n start execmd "););
        msAPI_MpegSP_CmdQueue_Exec(u32Stc);
    }

    return;
}

U32 msAPI_MpegSP_SpuQueue_GetSDRAMAddress( U16 u16Len )
{
    U32 u32Ret;

    if(!_b_MpegSP_inited)   // not yet initialized
        return 0;

    if (_u32SPUQueueAddress + u16Len > SP_STREAM_BUF_ADR + SP_STREAM_BUF_LEN)
    {
        _u32SPUQueueAddress = SP_STREAM_BUF_ADR;
    }

    u32Ret = _VA2PA(_u32SPUQueueAddress);

    _u32SPUQueueAddress += u16Len;

    return u32Ret;
}

void msAPI_MpegSP_SpuQueue_Reset( void )
{
    pstSpuQueue->u8Count = pstSpuQueue->u8Front = 0;
}

void msAPI_MpegSP_Show(void)
{
    SBTL_TRACE(printf("\n MpegSp change to Show Subtitle"););
    _b_MpegSP_Show = TRUE;
}
void msAPI_MpegSP_Unshow(void)
{
    SBTL_TRACE(printf("\n MpegSp change to Unshow Subtitle"););
    _b_MpegSP_Show = FALSE;
    _u32_SPU_Display_Pts = 0;
    if(_b_MpegSP_Gwin_created)
        MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
}

void msAPI_MpegSP_SetShowStatus(BOOLEAN bShowStatus)
{
    SBTL_DBG(printf("\n MpegSp set show status:%x", bShowStatus););
    _b_MpegSP_Status2Show = bShowStatus;

    if(!_b_MpegSP_inited)
    {
        SBTL_DBG(printf("\n _b_MpegSP_inited is not inited"););
        return;
    }

    if(!bShowStatus)
        msAPI_MpegSP_Renderer_DeInit();
    else
    {
        //only subtitle enable   call msAPI_MpegSP_Renderer_Init otherwise OP IP config may not right in msAPI_MpegSP_Renderer_Init
        if((!_b_MpegSP_Gwin_created) && ((qeCur.enSubType & E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP) != 0))
        {
            msAPI_MpegSP_Renderer_Init();
        }
    }
}

BOOLEAN msAPI_MpegSP_Get_Show_Status(void)
{
    return _b_MpegSP_Show;// && _b_MpegSP_Status2Show;
}

BOOLEAN msAPI_MpegSP_Get_Render_Status(void)
{
    return (_b_MpegSP_Show && _b_MpegSP_Status2Show);
}

BOOLEAN msAPI_MpegSP_SpuQueue_Push(EN_VDP_CODECID enSubType, U32 u32Address, U16 u16Len, U32 u32PTS, U32 u32Duration)
{
    U8 u8NewElementIndex;

    if(!_b_MpegSP_inited)   // not yet initialized
        return FALSE;

    if( enSubType != E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP &&
        enSubType != E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB &&
        enSubType != E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8 &&
        enSubType != E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS &&
        enSubType != E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA )
        return FALSE;   //currently only support above two types

    // check if queue full
    if (pstSpuQueue->u8Count == MAX_SPU_QUEUE_SIZE)
        msAPI_MpegSP_SpuQueue_Pop(&qeCur);

    u32Address = _PA2VA(u32Address);

    u8NewElementIndex = (pstSpuQueue->u8Front + pstSpuQueue->u8Count) % MAX_SPU_QUEUE_SIZE;

    //if( u8VideoType ==E_SUBTITLE_VIDEO_TYPE_DIVX) // parse [hh:mm:ss:000- to get display PTS
    if(enSubType == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)  // DivX
    {
        U8 u8Buf[13];
        memset(u8Buf, 0x0, 13);
        //msAPI_MpegSP_SPU_GetByte(u32Address, &u8Value1);
        msAPI_MpegSP_SPU_GetBuf(u32Address, u8Buf, 13);
        if(u8Buf[0] != 0x5b)
        {
            SBTL_ERR(printf("\nError: first byte not 0x5b it's: %x", u8Buf[0]););  // '['
            return FALSE;
        }
        u32PTS = (u8Buf[1]-0x30)*10 + (u8Buf[2]-0x30);          // hours

        u32PTS = u32PTS*60+ (u8Buf[4]-0x30)*10 + (u8Buf[5]-0x30);       // mins

        u32PTS = u32PTS*60+ (u8Buf[7]-0x30)*10 + (u8Buf[8]-0x30);       // secs

        u32PTS = u32PTS*100 + (u8Buf[10]-0x30)*10 + (u8Buf[11]-0x30);   // 1/100 secs

        u32PTS = u32PTS*10 + (u8Buf[12]-0x30);      // msecs
    }

    SBTL_TRACE(printf("\nPUSH [%x] : (t:%x addr:%lx, len:%x, pts:%lu, Duration:%lu)",
                u8NewElementIndex,
                enSubType,
                u32Address,
                u16Len,
                u32PTS,
                u32Duration));

    pstSpuQueue->contents[u8NewElementIndex].u32Address = u32Address;
    pstSpuQueue->contents[u8NewElementIndex].u16Len = u16Len;
    pstSpuQueue->contents[u8NewElementIndex].u32PTS = u32PTS;
    pstSpuQueue->contents[u8NewElementIndex].u32Duration = u32Duration;
    pstSpuQueue->contents[u8NewElementIndex].enSubType = enSubType;

    pstSpuQueue->u8Count ++;

    return TRUE;
}

BOOLEAN msAPI_MpegSP_SpuQueue_PeekN( StQueueElement *qe, U8 u8N )
{
    // check if we have that Nth element for peeking
    if (u8N >= pstSpuQueue->u8Count)
        return FALSE;

    u8N += pstSpuQueue->u8Front;
    u8N %= MAX_SPU_QUEUE_SIZE;
    qe->u32Address = pstSpuQueue->contents[u8N].u32Address;
    qe->u16Len       = pstSpuQueue->contents[u8N].u16Len;
    qe->u32PTS       = pstSpuQueue->contents[u8N].u32PTS;

    //SBTL_TRACE(printf("\t\t\tPEEK [%x] : (%lx, %x, PTS:%lx)\n",
    //        u8N,
    //        pstSpuQueue->contents[u8N].u32Address,
    //        pstSpuQueue->contents[u8N].u16Len-6,
    //        pstSpuQueue->contents[u8N].u32PTS););

    return TRUE;
}

BOOLEAN msAPI_MpegSP_SpuQueue_Pop( StQueueElement* qe )
{
    // check if we have any element for popping
    if (pstSpuQueue->u8Count == 0)
        return FALSE;

    qe->u32Address = pstSpuQueue->contents[pstSpuQueue->u8Front].u32Address;
    qe->u16Len       = pstSpuQueue->contents[pstSpuQueue->u8Front].u16Len;
    qe->u32PTS       = pstSpuQueue->contents[pstSpuQueue->u8Front].u32PTS;
    qe->u32Duration = pstSpuQueue->contents[pstSpuQueue->u8Front].u32Duration;
    qe->enSubType  = pstSpuQueue->contents[pstSpuQueue->u8Front].enSubType;

    SBTL_TRACE(printf("\nPOP[%x]:  (t:%x addr:%lx, len:%x, pts:%lx)",
                pstSpuQueue->u8Front,
                qe->enSubType,
                qe->u32Address,
                qe->u16Len,
                qe->u32PTS
                ););

    pstSpuQueue->u8Front++;
    pstSpuQueue->u8Front %= MAX_SPU_QUEUE_SIZE;

    pstSpuQueue->u8Count --;

    return TRUE;
}

BOOLEAN msAPI_MpegSP_SpuQueue_CheckPTS( U32 u32STC )
{
    StQueueElement qe;
    U8 u8N = 0;
    qe.u32PTS = 0xFFFFFFFF;

    while (msAPI_MpegSP_SpuQueue_PeekN(&qe, u8N++) == TRUE)
    {
        if (qe.u32PTS <= u32STC)
        {
            SBTL_TRACE(printf("\n cur STC:%lx larger than sp pts:%lx", u32STC, qe.u32PTS););
            return TRUE;
        }
    }
    return FALSE;
}

U8 msAPI_MpegSP_SpuQueue_GetCount(void)
{
    if (pstSpuQueue)
        return pstSpuQueue->u8Count;
    else
        return 0;
}

void msAPI_Decode_SPU(void)
{
    switch(qeCur.enSubType)
    {
    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
            SBTL_TRACE(printf("\nMpeg2 start decode"););
            msAPI_MpegSP_Decoder_SPU();
        break;
    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:    // divx
            SBTL_TRACE(printf("\nDivX start decode"););
            msAPI_DivXSP_Decoder_SPU();
        break;

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
    case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:    // divx TTF
    case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
            SBTL_TRACE(printf("\nDivXTTF start decode"););
            msAPI_DivXTTF_Decoder_SPU();
        break;
#endif

    default:
        break;
    }
}

BOOLEAN msAPI_DivXSP_Decoder_SPU(void)
{
    U32 u32ReadAddr, u32ClearTs;
    U8 u8Buf[43];

    memset(u8Buf, 0x0, 43);
    msAPI_MpegSP_CmdQueue_init();

    u32ReadAddr =  qeCur.u32Address;


    msAPI_MpegSP_SPU_GetBuf(u32ReadAddr, u8Buf, 1);
    if(u8Buf[0] != 0x5b)
    {
        SBTL_ERR(printf("\nError: first byte not 0x5b it's: %x", u8Buf[0]););  // '['
        return FALSE;
    }

    msAPI_MpegSP_SPU_GetBuf(u32ReadAddr+14, u8Buf, 43);
    u32ClearTs = (u8Buf[0]-0x30)*10 + (u8Buf[1]-0x30);       // hours

    u32ClearTs = u32ClearTs*60+ (u8Buf[3]-0x30)*10 + (u8Buf[4]-0x30);       // mins

    u32ClearTs = u32ClearTs*60+ (u8Buf[6]-0x30)*10 + (u8Buf[7]-0x30);       // secs

    u32ClearTs = u32ClearTs*100 + (u8Buf[9]-0x30)*10 + (u8Buf[10]-0x30);      // 1/100 secs

    u32ClearTs = u32ClearTs*10 + (u8Buf[11]-0x30);       // msecs

    if(u32ClearTs - qeCur.u32PTS < 500) // less than 500 ms
        return FALSE;        // skip this SPU

    SBTL_TRACE(printf("\n time period %lx - %lx", qeCur.u32PTS , u32ClearTs););

    pstDisplayParam->u16Width = (u8Buf[14] <<8) | u8Buf[13];
    pstDisplayParam->u16Height = (u8Buf[16] <<8) | u8Buf[15];
    pstDisplayParam->u16AreaLeft = (u8Buf[18] <<8) | u8Buf[17];
    pstDisplayParam->u16AreaTop = (u8Buf[20] <<8) | u8Buf[19];
    pstDisplayParam->u16AreaRight = (u8Buf[22] <<8) | u8Buf[21];
    pstDisplayParam->u16AreaBottom = (u8Buf[24] <<8) | u8Buf[23];

    SBTL_TRACE(printf("\n area W:%x, H:%x, L:%x, R:%x, T:%x, B:%x", pstDisplayParam->u16Width, pstDisplayParam->u16Height, pstDisplayParam->u16AreaLeft, pstDisplayParam->u16AreaRight, pstDisplayParam->u16AreaTop, pstDisplayParam->u16AreaBottom););

    if(_u16FullPixelBuffer_Width <= 720)
    {
        pstDisplayParam->u16RLTopField = 0x35;  // fixed top field offset, 53
        gePaletteBkg.a = 0x00;   // transparent
        gePalettePat.a = gePaletteEmp1.a = gePaletteEmp2.a = 0xff;
    }
    else    // HD profile
    {
        pstDisplayParam->u16RLTopField = 0x39;  // fixed top field offset, 57
        gePaletteBkg.a =  u8Buf[39];   // 0x00, transparent
        gePalettePat.a = u8Buf[40];
        gePaletteEmp1.a = u8Buf[41];
        gePaletteEmp2.a = u8Buf[42];    //0xff;
    }

    pstDisplayParam->u16RLTopLen =  (u8Buf[26]<<8) | u8Buf[25];
    pstDisplayParam->u16RLBottomField = pstDisplayParam->u16RLTopField +pstDisplayParam->u16RLTopLen;
    pstDisplayParam->u16RLBottomLen = qeCur.u16Len - pstDisplayParam->u16RLBottomField;
    SBTL_TRACE(printf("\n bot field:%x, top len:%x, bot len:%x", pstDisplayParam->u16RLBottomField, pstDisplayParam->u16RLTopLen, pstDisplayParam->u16RLBottomLen););

    gePaletteBkg.r  = u8Buf[27];
    gePaletteBkg.g  = u8Buf[28];
    gePaletteBkg.b  = u8Buf[29];
    gePalettePat.r  = u8Buf[30];
    gePalettePat.g  = u8Buf[31];
    gePalettePat.b  = u8Buf[32];
    gePaletteEmp1.r = u8Buf[33];
    gePaletteEmp1.g = u8Buf[34];
    gePaletteEmp1.b = u8Buf[35];
    gePaletteEmp2.r = u8Buf[36];
    gePaletteEmp2.g = u8Buf[37];
    gePaletteEmp2.b = u8Buf[38];

    msAPI_MpegSP_CmdQueue_push(qeCur.u32PTS, 0x01, NULL, 0);
    msAPI_MpegSP_CmdQueue_push(u32ClearTs, 0x02, NULL, 0);
    if(u32ClearTs > qeCur.u32PTS)
    {
        qeCur.u32Duration = u32ClearTs - qeCur.u32PTS;
    }

    return TRUE;
}

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)

#define TTF_BITMAP_WIDTH 32//32
#define TTF_BITMAP_HEIGHT 48//48
#define SPACE_OFFSET 12
#define START_X_OFFSET  0
#define START_Y_OFFSET  0
#define LINE_LIMIT 4
BOOLEAN msAPI_DivXTTF_InitTTF(U32 u32addr, U32 u32size)
{
    BOOLEAN bRet = FALSE;
    FT_Error error = 0;

    SBTL_TRACE(printf("msAPI_DivXTTF_InitTTF!!!!\n"));

    if(_pFTLib != NULL)
    {
        FT_Done_FreeType(_pFTLib);
        _pFTLib = NULL;
    }

    if(_pFTFace != NULL)
    {
        FT_Done_Face(_pFTFace);
        _pFTFace = NULL;
    }

    //  Init FreeType Lib to manage memory
    error = FT_Init_FreeType(&_pFTLib);
    if(error)
    {
        _pFTLib = 0;
        printf("There is some error when init free type lib\n");
        return FALSE;
    }

    //error = FT_New_Face(_pFTLib, "/TTF/Subtitle1.ttf", 0 , &_pFTFace);
    error = FT_New_Memory_Face(_pFTLib, (U8 *)u32addr, u32size, 0 , &_pFTFace);

    if(!error)
    {
        //FT_Set_Char_Size(_pFTFace, 0, TTF_BITMAP_WIDTH*TTF_BITMAP_HEIGHT, 300, 300);
        FT_Set_Pixel_Sizes(_pFTFace, TTF_BITMAP_WIDTH, TTF_BITMAP_HEIGHT);
        FT_Select_Charmap(_pFTFace, FT_ENCODING_UNICODE);

        bRet = TRUE;
    }
    else
    {
        printf("There is some error when init font table\n");
        return FALSE;
    }

    #if 0
    if(!error)
    {
        U16 u16_i,u16_j;
        FT_Bitmap bitmap;
        FT_BitmapGlyph    bitmap_glyph;

        FT_Set_Char_Size(_pFTFace, 16<<6, 16<<6, 300, 300);
        FT_Glyph glyph;

        //-------------------------------Examples-----------------------------------//
        // Load unicode ?
        //FT_Select_Charmap(_pFTFace, FT_ENCODING_UNICODE);
        FT_Load_Glyph(_pFTFace, FT_Get_Char_Index(_pFTFace, 'a'), FT_LOAD_DEFAULT);
        //--------------------------------------------------------------------------//

        error = FT_Get_Glyph(_pFTFace -> glyph,  & glyph);
        if(!error)
        {
            //  convert glyph to bitmap with 256 gray
            FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal,  0 ,  1 );
            bitmap_glyph  =  (FT_BitmapGlyph)glyph;
            bitmap = bitmap_glyph->bitmap;
            for(u16_i=0;u16_i < bitmap.rows; u16_i++)
            {
                for(u16_j=0;u16_j < bitmap.width; u16_j++)
                {
                    //  if it has gray>0 we set show it as 1, 0 otherwise
                    printf("%d" , bitmap.buffer[u16_i * bitmap.width + u16_j] ? 1 : 0 );
                }
                printf("_\n");
            }
            //  free glyph
            FT_Done_Glyph(glyph);
            glyph  =  NULL;
        }
        //  free face
        FT_Done_Face(_pFTFace);
        _pFTFace  =  NULL;
        bRet = TRUE;
    }
    else
    {
        printf("There is some error when init font table\n");
        return FALSE;
    }
    #endif

    return bRet;
}

static BOOLEAN msAPI_DivXTTF_Decoder_SPU(void)
{
    U32 u32ClearTs;

    msAPI_MpegSP_CmdQueue_init();

    u32ClearTs = (qeCur.u32PTS + qeCur.u32Duration);

    if(u32ClearTs - qeCur.u32PTS < 500) // less than 500 ms
        return FALSE;        // skip this SPU

    SBTL_TRACE(printf("\n time period %lx - %lx", qeCur.u32PTS , u32ClearTs););


    pstDisplayParam->u16Width = _u16FullPixelBuffer_Width;
    pstDisplayParam->u16Height = _u16FullPixelBuffer_Height;
    pstDisplayParam->u16AreaLeft = 0;
    pstDisplayParam->u16AreaTop = 0;
    pstDisplayParam->u16AreaRight = _u16FullPixelBuffer_Width;
    pstDisplayParam->u16AreaBottom = _u16FullPixelBuffer_Height;

    SBTL_TRACE(printf("\n area W:%x, H:%x, L:%x, R:%x, T:%x, B:%x", pstDisplayParam->u16Width, pstDisplayParam->u16Height, pstDisplayParam->u16AreaLeft, pstDisplayParam->u16AreaRight, pstDisplayParam->u16AreaTop, pstDisplayParam->u16AreaBottom););

/*
    if(_u16FullPixelBuffer_Width <= 720)
    {
        pstDisplayParam->u16RLTopField = 0x35;  // fixed top field offset, 53
        gePaletteBkg.a = 0x00;   // transparent
        gePalettePat.a = gePaletteEmp1.a = gePaletteEmp2.a = 0xff;
    }
    else    // HD profile
    {
        pstDisplayParam->u16RLTopField = 0x39;  // fixed top field offset, 57
        gePaletteBkg.a =  0x00;   // 0x00, transparent
        gePalettePat.a = 0xff;
        gePaletteEmp1.a = 0xff;
        gePaletteEmp2.a = 0xff;    //0xff;
    }
*/
    pstDisplayParam->u16RLTopField = 0x0;      //Top field offset!
    pstDisplayParam->u16RLTopLen = qeCur.u16Len;
    pstDisplayParam->u16RLBottomField = pstDisplayParam->u16RLTopField +pstDisplayParam->u16RLTopLen;  //Bottom field offset!
    pstDisplayParam->u16RLBottomLen = 0x0;

    SBTL_TRACE(printf("\n bot field:%x, top len:%x, bot len:%x", pstDisplayParam->u16RLBottomField, pstDisplayParam->u16RLTopLen, pstDisplayParam->u16RLBottomLen););

    gePaletteBkg.a =  0x0;   // 0x00, transparent
    gePaletteBkg.r  = 0x0;
    gePaletteBkg.g  = 0x0;
    gePaletteBkg.b  = 0x0;

    gePalettePat.a = 0xff;
    gePalettePat.r  = 0x55;
    gePalettePat.g  = 0x55;
    gePalettePat.b  = 0x55;

    gePaletteEmp1.a = 0xff;
    gePaletteEmp1.r = 0xAA;
    gePaletteEmp1.g = 0xAA;
    gePaletteEmp1.b = 0xAA;

    gePaletteEmp2.a = 0xff;
    gePaletteEmp2.r = 0xff;
    gePaletteEmp2.g = 0xff;
    gePaletteEmp2.b = 0xff;

    msAPI_MpegSP_CmdQueue_push(qeCur.u32PTS, 0x01, NULL, 0);
    msAPI_MpegSP_CmdQueue_push(u32ClearTs, 0x02, NULL, 0);

    return TRUE;
}

static void msAPI_DivXTTF_ResetPixelBuffer(U16 _u16VideoHSize, U16 _u16VideoVSize)
{
    _u16VideoVSize = _u16VideoVSize; // for complier happy

    if(_u16VideoHSize <= 720)
    {
        _u16FullPixelBuffer_Width = 640;
        _u16FullPixelBuffer_Height = 480;
    }
    else if(_u16VideoHSize <= 1280)
    {
        _u16FullPixelBuffer_Width = 960;
        _u16FullPixelBuffer_Height = 720;
    }
    else
    {
        _u16FullPixelBuffer_Width = 1440;
        _u16FullPixelBuffer_Height = 1080;
    }

}

static BOOLEAN msAPI_DivXTTF_Decode_RLE(U32 u32RldOutputAddr, U8 u8TransPaletteIdx)
{
    pstSpRld->u32OutputAddress  = u32RldOutputAddr;
    SBTL_TRACE(printf("\n RLD output at pixelbuf :%lx", pstSpRld->u32OutputAddress););

    SW_TTF_RLDI2(u8TransPaletteIdx);

    return TRUE;
}

static BOOLEAN msAPI_DivXTTF_Renderer_Display( void )
{
    GEPoint st_point;
    GEBitmapFmt bmpfmt;
    U32 u32RldOutputAddr;
    U8 u8AlignmentGap;
    U8 u8TransPaletteIdx;

    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    SBTL_TRACE(printf("\n================== DISPLAY ======================="););

    SBTL_TRACE(printf("\nRegion(X:%x,Y:%x,W:%x,H:%x)",
            pstDisplayParam->u16AreaLeft,
            pstDisplayParam->u16AreaTop,
            pstDisplayParam->u16Width,
            pstDisplayParam->u16Height
            ););

    ///////////// fine tune subtitle off screen pixel buffer size
    //_u16FullPixelBuffer_Width= pstDisplayParam->u16AreaLeft+pstDisplayParam->u16AreaRight> _u16FullPixelBuffer_Width? pstDisplayParam->u16AreaLeft+pstDisplayParam->u16AreaRight : _u16FullPixelBuffer_Width;
    //_u16FullPixelBuffer_Height= pstDisplayParam->u16AreaBottom+20>_u16FullPixelBuffer_Height ?  pstDisplayParam->u16AreaBottom+20: _u16FullPixelBuffer_Height; // it should be smaller than +27 for divx H01 korean language
    _u16FullPixelBuffer_Pitch =  ROUND_UP(_u16FullPixelBuffer_Width, 32);
    u8AlignmentGap = 0;
    SBTL_TRACE(printf("\n Finetune PixelBufer to Width:%x Pitch:%x Height:%x", _u16FullPixelBuffer_Width, _u16FullPixelBuffer_Pitch, _u16FullPixelBuffer_Height););
    //SBTL_TRACE(printf("\n orig X,Y:(%x,%x) capHstart:%x capVstart:%x  Cap (%x, %x), PixelWin(%x, %x)",gop_parameters.u16_GWIN_left,gop_parameters.u16_GWIN_top, g_SrcInfo.u16H_CapStart, g_SrcInfo.u16V_CapStart,g_SrcInfo.u16H_CapSize, g_SrcInfo.u16V_CapSize, _u16FullPixelBuffer_Pitch, _u16FullPixelBuffer_Height);)


    // fine tune subtitle position when the height of the subtitle is bigger than the height of the video
    if(_u8YPosScale==0xFF && _u16FullPixelBuffer_Height/2 > gop_parameters.u16_GWIN_height)
    {
        _u8YPosScale = (U8)(((U32)gop_parameters.u16_GWIN_height*100)/(_u16FullPixelBuffer_Height/2));
        SBTL_TRACE(printf("\nYScale=%x, Height=%x, PixBuffer=%x", _u8YPosScale, gop_parameters.u16_GWIN_height, _u16FullPixelBuffer_Height);)
    }

    ///////////// fine tune subtitle position by u8XPosScale, u8YPosScale
    if(_u8XPosScale != 0xFF)
    {
        U16 u16tmpAreaRight = (U32)_u16FullPixelBuffer_Pitch*_u8XPosScale/100;
        pstDisplayParam->u16AreaLeft = u16tmpAreaRight > pstDisplayParam->u16Width?  u16tmpAreaRight - pstDisplayParam->u16Width: 0;
    }
    u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR + ((U32) pstDisplayParam->u16AreaTop*_u16FullPixelBuffer_Pitch + pstDisplayParam->u16AreaLeft)/4;

    if(_u8YPosScale != 0xFF)
    {
        _u16FinetunedBot= (U32)_u16FullPixelBuffer_Height*_u8YPosScale/100;

        if( pstDisplayParam->u16Height > _u16FinetunedBot )   // move ahead the rld ouput in front of the pixelbuffer
        {
            U16 u16OffsetLines = pstDisplayParam->u16Height - _u16FinetunedBot;
            u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR - ((U32) u16OffsetLines *_u16FullPixelBuffer_Pitch - pstDisplayParam->u16AreaLeft)/4;
            pstDisplayParam->u16AreaTop = 0;
            if(u32RldOutputAddr < SP_PIXELBUFFER_OFFSET_ADR)
            {
                U16 u16GapLines = (U32)(SP_PIXELBUFFER_OFFSET_ADR - u32RldOutputAddr) / (_u16FullPixelBuffer_Pitch/4);
                u32RldOutputAddr = u32RldOutputAddr + (U32) _u16FullPixelBuffer_Pitch * (u16GapLines+1) /4;
                _u16FinetunedBot += (u16GapLines+1);
            }
        }
        else    //cropped subtitle
        {
            if(_u16FinetunedBot < pstDisplayParam->u16AreaBottom)
            {
                pstDisplayParam->u16AreaTop= _u16FinetunedBot - pstDisplayParam->u16Height;
                u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR + ((U32) pstDisplayParam->u16AreaTop*_u16FullPixelBuffer_Pitch + pstDisplayParam->u16AreaLeft)/4;
            }
            else
                _u16FinetunedBot = pstDisplayParam->u16AreaBottom;
        }
    }
    else
        _u16FinetunedBot= pstDisplayParam->u16AreaBottom;

    SBTL_TRACE(printf("\n Finetune subtitle Pos: Xscale:%x, XNewpos:%x, Yscale:%x, YNewpos:%x", _u8XPosScale,pstDisplayParam->u16AreaLeft, _u8YPosScale, pstDisplayParam->u16AreaTop););

    u8TransPaletteIdx = msAPI_MpegSP_SetGopPalette();

    msAPI_MpegSP_Clear_OffScreenBuffer(u8TransPaletteIdx);
    if(msAPI_DivXTTF_Decode_RLE(u32RldOutputAddr, u8TransPaletteIdx) == FALSE)
        return FALSE;

    msAPI_OSD_SetClipWindow(0,0, gop_parameters.u16_GWIN_width-1, gop_parameters.u16_GWIN_height -1);
    if(u8TransPaletteIdx  == 0xff)
    {
        U16 u16AreaLeft8Gwin = (U32)pstDisplayParam->u16AreaLeft* gop_parameters.u16_GWIN_width/_u16FullPixelBuffer_Pitch;
        U16 u16AreaTop8Gwin = (U32)pstDisplayParam->u16AreaTop* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
        U16 u16AreaRight8Gwin = (U32)pstDisplayParam->u16AreaRight* gop_parameters.u16_GWIN_width/_u16FullPixelBuffer_Pitch;
        U16 u16AreaBot8Gwin = (U32)_u16FinetunedBot* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
        msAPI_MpegSP_Renderer_ClearDisplayBlock(gop_parameters.u8_GWIN_id, 0, 0, gop_parameters.u16_GWIN_width-1, gop_parameters.u16_GWIN_height-1);
        msAPI_OSD_SetClipWindow(u16AreaLeft8Gwin,u16AreaTop8Gwin,u16AreaRight8Gwin,u16AreaBot8Gwin);
    }

    bmpfmt.bBmpColorKeyEnable = FALSE;
    bmpfmt.bScale = TRUE;

    bmpfmt.width = ROUND_DOWN(gop_parameters.u16_GWIN_width, 8);
    bmpfmt.height = gop_parameters.u16_GWIN_height;

    st_point.x =  u8AlignmentGap;
    st_point.y =  0;
    SBTL_TRACE(printf("\nBmp At Gwin(X:%x,Y:%x,W:%x,H:%x) gwin( id:%x w:%x, h:%x)",
            st_point.x, st_point.y,
            bmpfmt.width, bmpfmt.height, gop_parameters.u8_GWIN_id,gop_parameters.u16_GWIN_width,gop_parameters.u16_GWIN_height););

    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
        MApi_GFX_SetNearestMode(FALSE);
    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        MApi_GFX_SetNearestMode(TRUE);
    MApi_GFX_SetPatchMode(TRUE);
    //MDrv_GE_DrawBitmap(hBMP, &st_point, &bmpfmt);


    // use Bitblt method to replace GE Draw Bitmap
    U32 u32Faddr;
    U8 fid = MApi_GOP_GWIN_GetFBfromGWIN(gop_parameters.u8_GWIN_id);
    MApi_GOP_GWIN_GetFBAddr(fid, &u32Faddr);

    /* x y */
    BitbltInfo.BitbltCoordinate.v0_x = 0;
    BitbltInfo.BitbltCoordinate.v0_y = 0;
    BitbltInfo.BitbltCoordinate.v2_x = 0;
    BitbltInfo.BitbltCoordinate.v2_y = 0;

    /* dst dimension */
    BitbltInfo.BitbltCoordinate.height = bmpfmt.height;
    BitbltInfo.BitbltCoordinate.width  = bmpfmt.width;

    /* src dimension */
    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    BitbltInfo.src_height     = _u16FullPixelBuffer_Height;
    BitbltInfo.src_width      = _u16FullPixelBuffer_Width;

    /* src base */
    BitbltInfo.src_fm   = GFX_FMT_I2;
    PitBaseInfo.sb_base = _VA2PA(SP_PIXELBUFFER_ADR);
    PitBaseInfo.sb_pit  = _u16FullPixelBuffer_Pitch/4;

    /* dst base */
    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB1555;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB4444;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else
    {
        BitbltInfo.dst_fm   = GFX_FMT_I8;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width;
    }

    msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
    MApi_GFX_FlushQueue();
    SBTL_TRACE(printf("\nbitblt to  Gwin addr:%lx", u32Faddr););

    //MDrv_GE_SetNearestMode(FALSE);

    MApi_GFX_SetPatchMode(FALSE);
    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, TRUE);
    return TRUE;
}

static void msAPI_DivXTTF_DrawBitmap( FT_Bitmap *pbitmap, U32 u32Position_x, U32 u32Position_y, U16 u16Left, U16 u16Top, U16 u16Rows, U16 u16Width)
{
    U16 i,j;
    U32 u32Start_X;
    U32 u32Start_Y;
    U8 *ptargByte;
    U32 u32TarBit;
    U8 u8PaletteIdx = 0;

    //printf("Width:%d Height:%d\n",u16Width,u16Rows);
    //printf("X:%d Y:%d\n",u32Position_x,u32Position_y);

    u32Start_X = u32Position_x + u16Left;
    u32Start_Y = u32Position_y + (TTF_BITMAP_HEIGHT-u16Top);

    for(i = 0 ; i < u16Rows ; i++)
    {
        for(j = 0 ; j < u16Width ; j++)
        {
            ptargByte = (U8*) (pstSpRld->u32OutputAddress +(((u32Start_Y+i)*_u16FullPixelBuffer_Pitch/4)+(u32Start_X+j)/4));
            u32TarBit = (u32Start_X+j)%4;


            u8PaletteIdx = pbitmap->buffer[i * u16Width + j]/(255/(PALETTE_UNIT-1));
            *ptargByte |= ((u8PaletteIdx & 0x3) << ((3-u32TarBit)*2));

            //  if it has gray>0 we set show it as 1, o otherwise
            //printf("%d" , pbitmap->buffer[i * u16Width + j]?1:0);
        }
        //printf("_\n");
    }
}

static U16 msapi_DivxTTF_UTF82UNICODE(U8 *pu8Char,U8 *pu8Offset)
{
    U16 u16Char = 0;

    if (pu8Char[0] < 0x80)
    {
        u16Char = (pu8Char[0] & 0x7F);
        *pu8Offset = 1;
    }
    else if (((pu8Char[0] >= 0xC0) && (pu8Char[0] < 0xE0)) && (pu8Char[1] >= 0x80))
    {
        //UTF8 to UNICODE
        memset((U8*)&u16Char,((pu8Char[1] & 0x3F) | ((pu8Char[0] & 0x3) << 6)),1);
        memset(((U8*)&u16Char)+1,((pu8Char[0] & 0x1C) >> 2),1);
        *pu8Offset = 2;
    }
    else if ((pu8Char[0] >= 0xE0) && (pu8Char[1] >= 0x80) && (pu8Char[2] >= 0x80))
    {
        //UTF8 to UNICODE
        memset((U8*)&u16Char,((pu8Char[2] & 0x3F) | ((pu8Char[1] & 3) << 6)),1);
        memset(((U8*)&u16Char)+1,(((pu8Char[1] & 0x3C) >> 2) | ((pu8Char[0] & 0xF) << 4)),1);
        *pu8Offset = 3;
    }
    else
    {
        *pu8Offset = 1;
        printf("UTF8 to UNICODE error!!\n");
    }

    return u16Char;
}

static void SW_TTF_RLDI2(U8 u8TransPaletteIdx)
{
    U8 u8Line;
    U16 n;
    U8 *pSrcByte,*pDesByte;
    U8 *pu8data;
    U8 u8Offset = 0;
    U16 u16Char;
    U32 u32Position_x = START_X_OFFSET;
    U32 u32Position_y = START_Y_OFFSET;
    S32 s32PositionTemp;
    S32 s32LineInfo[LINE_LIMIT][3];   //[0]: line max width. [1]: line start_y. [2]: line end_y
    U8 u8TotalLine = 0;
    FT_UInt  glyph_index;
    FT_GlyphSlot  slot = _pFTFace->glyph;
    FT_Error error = 0;

    //init line info
    for(n = 0; n < LINE_LIMIT; n++)
    {
        s32LineInfo[n][0] = 0;                                         //[0]: line max width.
        s32LineInfo[n][1] = _u16FullPixelBuffer_Height;   //[1]: line start_y.
        s32LineInfo[n][2] = 0;                                         //[2]: line end_y
    }

    //printf("Width:%u Height:%u u8TransPaletteIdx:%u\n",_u16FullPixelBuffer_Width,_u16FullPixelBuffer_Height,u8TransPaletteIdx);
    //printf("TypeID:0x%x , address:0x%lx , Len:0x%x\n",(U16)qeCur.enSubType,qeCur.u32Address,qeCur.u16Len);
    pu8data=(U8 *)(qeCur.u32Address);

    //printf("Data dump: Len:0x%x\n",qeCur.u16Len);
    //for(n=0;n<0x4;n++)
    //{
    //    printf("%02x ",pu8data[n]);
    //}
    //printf("\nEnd----\n");

    //Step I: Bitmap rendering
    for(n = 0 ; n < qeCur.u16Len ; n += u8Offset) //index loop
    {
        //avoid memory overflow
        if(u8TotalLine > LINE_LIMIT-1)
        {
            u8TotalLine = LINE_LIMIT-1;
            break;
        }

        /* retrieve glyph index from character code */
        u16Char = msapi_DivxTTF_UTF82UNICODE(&pu8data[n],&u8Offset);

        //Next Line
        if(u16Char == 0x0A)
        {
            u8TotalLine++;
            u32Position_x = START_X_OFFSET;
            u32Position_y += TTF_BITMAP_HEIGHT;
            continue;
        }
        else if(u16Char == 0x5C)     // "\N" for new line!
        {
            U16 u16TempChar;
            U8 u8TempOffset;
            u16TempChar = msapi_DivxTTF_UTF82UNICODE(&pu8data[n+1],&u8TempOffset);
            if(u16TempChar == 0x4E)     //  'N'
            {
                u8Offset += u8TempOffset;
                u8TotalLine++;
                u32Position_x = START_X_OFFSET;
                u32Position_y += TTF_BITMAP_HEIGHT;
                continue;
            }
        }
        else if(u16Char == 0)  //UNICODE error!
        {
            break;
        }

        /* retrieve glyph index from character code */
        glyph_index = FT_Get_Char_Index( _pFTFace, u16Char );

        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Glyph( _pFTFace, glyph_index, FT_LOAD_DEFAULT );
        if ( error )
          continue;  /* ignore errors */

        /* convert to an anti-aliased bitmap */
        error = FT_Render_Glyph( _pFTFace->glyph, FT_RENDER_MODE_NORMAL );
        if ( error )
          continue;

        /* Bitmap top position protect. */
        if(slot->bitmap_top > TTF_BITMAP_HEIGHT)
        {
            slot->bitmap_top = TTF_BITMAP_HEIGHT;
        }

        /* Bitmap left position protect. */
        if(slot->bitmap_left < 0)
        {
            slot->bitmap_left = 0;
        }

        /* now, draw to our target surface */
        msAPI_DivXTTF_DrawBitmap( &slot->bitmap, u32Position_x, u32Position_y, slot->bitmap_left, slot->bitmap_top, slot->bitmap.rows, slot->bitmap.width);
        //printf("X:%u, Y:%u,  L:%d,  T:%d, W:%u, H:%u, \n",u32Position_x,u32Position_y,slot->bitmap_left, slot->bitmap_top, slot->bitmap.rows, slot->bitmap.width);

        /* increment position */
        if(slot->bitmap.width>0)
        {
            u32Position_x += (slot->bitmap.width + slot->bitmap_left);
            s32LineInfo[u8TotalLine][0] = u32Position_x;
        }
        else
        {
            u32Position_x += SPACE_OFFSET;
        }

        s32PositionTemp = (S32)(u32Position_y + (TTF_BITMAP_HEIGHT-slot->bitmap_top));
        if(  s32PositionTemp < s32LineInfo[u8TotalLine][1])
        {
            s32LineInfo[u8TotalLine][1] = s32PositionTemp;
        }

        s32PositionTemp = (S32)(u32Position_y + (TTF_BITMAP_HEIGHT - slot->bitmap_top) + slot->bitmap.rows);
        if( s32PositionTemp > s32LineInfo[u8TotalLine][2])
        {
            s32LineInfo[u8TotalLine][2] = s32PositionTemp;
        }
    }

    //For end of line
    if(u8TotalLine > LINE_LIMIT-1)
    {
        u8TotalLine = LINE_LIMIT-1;
    }

    //Step II: Line position.
    for(u8Line = 0; u8Line <= u8TotalLine ; u8Line++)
    {
        if(s32LineInfo[u8TotalLine][0] == 0)
        {
            continue;
        }

        u32Position_x = START_X_OFFSET;
        u32Position_y = START_Y_OFFSET + s32LineInfo[u8Line][1];
        pSrcByte = (U8*) (pstSpRld->u32OutputAddress +(((u32Position_y)*_u16FullPixelBuffer_Pitch/4)+u32Position_x/4));

        u32Position_x = (START_X_OFFSET + ((_u16FullPixelBuffer_Width-s32LineInfo[u8Line][0])/2));
        u32Position_y = (START_Y_OFFSET + (_u16FullPixelBuffer_Height - ((u8TotalLine+2)*TTF_BITMAP_HEIGHT)) + s32LineInfo[u8Line][1]);
        pDesByte = (U8*) (pstSpRld->u32OutputAddress + ((u32Position_y)*_u16FullPixelBuffer_Pitch/4)+u32Position_x/4);

        for(n=s32LineInfo[u8Line][1]; n<s32LineInfo[u8Line][2] ; n++)
        {
            if((U32)(pDesByte + (s32LineInfo[u8Line][0]/4 + 1)) > (U32)(pstSpRld->u32OutputAddress + ((_u16FullPixelBuffer_Height)*_u16FullPixelBuffer_Pitch/4)))
            {
                //printf("Memory address overflow!\n");
                memset(pSrcByte,u8TransPaletteIdx,(s32LineInfo[u8Line][0]/4 + 1));
                continue;
            }
            memcpy(pDesByte,pSrcByte,(s32LineInfo[u8Line][0]/4 + 1));
            memset(pSrcByte,u8TransPaletteIdx,(s32LineInfo[u8Line][0]/4 + 1));
            pSrcByte += (_u16FullPixelBuffer_Pitch/4);
            pDesByte += (_u16FullPixelBuffer_Pitch/4);
        }
        //printf("Line:%u, srcByte:0x%lx desByte:0x%lx total pixels:%lu _u16FullPixelBuffer_Height:%u u32Position_y:%u\n",u8Line,pSrcByte,pDesByte,(s32LineInfo[u8Line][0]/4 + 1),_u16FullPixelBuffer_Height,u32Position_y);
    }
}

#endif

void msAPI_DivXSP_ResetPixelBuffer(U16 _u16VideoHSize, U16 _u16VideoVSize)
{
    _u16VideoVSize = _u16VideoVSize; // for complier happy

    if(_u16VideoHSize <= 720)
    {
        _u16FullPixelBuffer_Width = 640;
        _u16FullPixelBuffer_Height = 480;
    }
    else if(_u16VideoHSize <= 1280)
    {
        _u16FullPixelBuffer_Width = 960;
        _u16FullPixelBuffer_Height = 720;
    }
    else
    {
        _u16FullPixelBuffer_Width = 1440;
        _u16FullPixelBuffer_Height = 1080;
    }

}

void msAPI_MpegSP_ResetPixelBuffer(U16 _u16VideoHSize, U16 _u16VideoVSize)
{
    _u16FullPixelBuffer_Width=_u16VideoHSize<GWIN_WIDTH_LIMIT ? _u16VideoHSize: GWIN_WIDTH_LIMIT;
    _u16FullPixelBuffer_Height=_u16VideoVSize<GWIN_HEIGHT_LIMIT ? _u16VideoVSize: GWIN_HEIGHT_LIMIT;;
}


BOOLEAN msAPI_MpegSP_Decoder_SPU(void)
{
    msAPI_MpegSP_CmdQueue_init();
    msAPI_MpegSP_Decoder_Header();
    if(FALSE ==msAPI_MpegSP_Decoder_DCSQT() )
        msAPI_MpegSP_CmdQueue_init();  // parse error, reset cmd queue , to avoid show garbage
    return TRUE;
}

BOOLEAN msAPI_MpegSP_Decoder_Header(void)
{
    U32 u32ReadAddr =  qeCur.u32Address;
    SBTL_TRACE(printf("\n Spu Queue addr:%lx", u32ReadAddr););
    msAPI_MpegSP_SPU_GetWord(u32ReadAddr, &_u16_SPU_length);
    u32ReadAddr+=2;
    msAPI_MpegSP_SPU_GetWord(u32ReadAddr, &_u16_DCSQCT_addr);
    u32ReadAddr+=2;

    return TRUE;
}


BOOLEAN msAPI_MpegSP_Decoder_DCSQT(void)
{
    U16 u16_parse_DCSQ_addr = _u16_DCSQCT_addr;
    U16 u16_next_DCSQ_addr;

    memset(pstDisplayParam, 0x00, sizeof(StDisplayParam));
    while(1)
    {
        SBTL_TRACE(printf("\n Start Pasrse DCSQ offset :%x", u16_parse_DCSQ_addr););
        u16_next_DCSQ_addr = msAPI_MpegSP_Decoder_DCSQ(u16_parse_DCSQ_addr) ;
        if(0 == u16_next_DCSQ_addr)  // fail to parse
            return FALSE;
        else if(u16_next_DCSQ_addr == u16_parse_DCSQ_addr)
            break;  // no more next DCSQ
        else    //got next DCSQ
            u16_parse_DCSQ_addr = u16_next_DCSQ_addr;
    }
    return TRUE;
}

U16 msAPI_MpegSP_Decoder_DCSQ(U16 addr)
{
    U16 u16_SPU_STM;
    U16 u16_Next_SBTL_DCSQ_Addr = 0;
    U32 u32ReadAddr =  qeCur.u32Address + addr;
    SBTL_TRACE(printf("\n decde dcsq: %lx, start :%lx, offset :%x",  u32ReadAddr ,qeCur.u32Address , addr););

    msAPI_MpegSP_SPU_GetWord(u32ReadAddr, &u16_SPU_STM);
    u32ReadAddr+=2;

    msAPI_MpegSP_SPU_GetWord(u32ReadAddr, &u16_Next_SBTL_DCSQ_Addr);
    u32ReadAddr+=2;

    if(FALSE == msAPI_MpegSP_Decoder_DCCMDs(u32ReadAddr, u16_SPU_STM))
        return 0;

    return u16_Next_SBTL_DCSQ_Addr;
}

BOOLEAN msAPI_MpegSP_Decoder_DCCMDs(U32 pu32ReadAddr, U32 u32CmdStm)
{
    U8 u8Extendfield[MPEG_SUB_CMD_EX_FIELD_LEN] = {0,0,0,0,0,0};
    U8 u8ExtendLen=0;
    U8 u8CmdCode;
    BOOLEAN bEndCmd = FALSE;

    while(1)
    {
        msAPI_MpegSP_SPU_GetByte(pu32ReadAddr++, &u8CmdCode);

        switch(u8CmdCode)
        {
        case 0x00:  //FSTA_DSP
        case 0x01:  //  STA_DSP
        case 0x02:  //STP_DSP
            u8ExtendLen = 0;
            break;
        case 0x03:  //SET_COLOR
        case 0x04:  // SET_CONTR
            u8ExtendLen = 2;
            break;
        case 0x05:  //SET_DAREA
            u8ExtendLen = 6;
            break;
        case 0x06:  //SET_DSPXA
            u8ExtendLen = 4;
            break;
        case 0x07:  //CHG_COLCON
            // not yet support now
        case 0xFF:  // CMD_END
            u8ExtendLen = 0;
            bEndCmd = TRUE;
                break;
        default:
            return FALSE;   // error parsing
        }

        if(bEndCmd)
            break;

        msAPI_MpegSP_SPU_GetBuf(pu32ReadAddr, u8Extendfield, u8ExtendLen);
        pu32ReadAddr+=u8ExtendLen;

        if(TRUE == msAPI_MpegSP_CmdQueue_push(qeCur.u32PTS + (u32CmdStm<<10), u8CmdCode, u8Extendfield, u8ExtendLen))
        {
             SBTL_TRACE(printf("\n Push Cmd:%02x, extend:%02x %02x %02x %02x %02x %02x ", u8CmdCode, u8Extendfield[0],u8Extendfield[1],u8Extendfield[2],u8Extendfield[3],u8Extendfield[4],u8Extendfield[5]););
        }
        else
        {
            SBTL_TRACE(printf("\n Failed to push cmd to cmdQueue"););
            return FALSE;
        }
    }

    return TRUE;
}

void msAPI_MpegSP_CmdQueue_init(void)
{
    pstCmdQueue->u8Count = pstCmdQueue->u8Front = 0;
}

BOOLEAN msAPI_MpegSP_CmdQueue_push(U32 u32Stm, U8 cmdCode, U8 *extendfield, U8 extendLen)
{
    U8 u8NewElementIndex;
    U8 u8_i;

    if(pstCmdQueue->u8Count >= MAX_CMD_QUEUE_SIZE)
    {
        SBTL_ERR(printf("\nERR : Queue overflow!"););
        return FALSE;
    }

    if( extendLen > MPEG_SUB_CMD_EX_FIELD_LEN )
    {
        SBTL_ERR( printf("\nERR : extendLen=%u > %u\n", extendLen, MPEG_SUB_CMD_EX_FIELD_LEN); );
        return FALSE;
    }

    u8NewElementIndex = (pstCmdQueue->u8Front + pstCmdQueue->u8Count)  % MAX_CMD_QUEUE_SIZE;

    //SBTL_TRACE(printf("\nqueue[%x] : (%lx, %x, %lx)", u8NewElementIndex, u32Address, u16Len, u32PTS););

    pstCmdQueue->cmd[u8NewElementIndex].u32Pts = u32Stm; // qeCur.u32PTS + (u32Stm<<10);
    pstCmdQueue->cmd[u8NewElementIndex].u8cmdCode = cmdCode;

    if( (extendLen > 0) && (extendfield != NULL) )
    {
        for(u8_i=0; u8_i< extendLen; u8_i++)
        {
            pstCmdQueue->cmd[u8NewElementIndex].extendField[u8_i] = *(extendfield+u8_i);
        }
    }

    pstCmdQueue->u8Count ++;
    return TRUE;
}

BOOLEAN msAPI_MpegSP_CmdQueue_pop(StCmd* pCmd)
{
    U8 u8_i;

    if (pstCmdQueue->u8Count == 0)
    {
        SBTL_ERR(printf("\nERR : Empty Queue when trying to pop the first element!"););
        return FALSE;
    }

    pCmd->u32Pts = pstCmdQueue->cmd[pstCmdQueue->u8Front].u32Pts;
    pCmd->u8cmdCode = pstCmdQueue->cmd[pstCmdQueue->u8Front].u8cmdCode;
    for(u8_i = 0; u8_i<6; u8_i++)
    {
        pCmd->extendField[u8_i] = pstCmdQueue->cmd[pstCmdQueue->u8Front].extendField[u8_i];
    }

    pstCmdQueue->u8Front++;
    pstCmdQueue->u8Front %= MAX_CMD_QUEUE_SIZE;
    pstCmdQueue->u8Count --;

    return TRUE;
}


U8 msAPI_MpegSP_CmdQueue_Size(void)
{
    return pstCmdQueue->u8Count;
}

void msAPI_MpegSP_CmdQueue_Exec(U32 u32Stc)
{
    StCmd cmd;

    while(msAPI_MpegSP_CmdQueue_CheckStm(u32Stc))    // stc larger than first cmd stm
    {
        if(FALSE ==msAPI_MpegSP_CmdQueue_pop(&cmd))
            break;

        switch(cmd.u8cmdCode)
        {
            case 0x00:  //FSTA_DSP
            case 0x01:  //STA_DSP
                pstDisplayParam->bDisplayFlag = TRUE;
                SBTL_TRACE(printf("\nexecmd: 01 disbplay:%x", pstDisplayParam->bDisplayFlag););
                break;
            case 0x02:  //STP_DSP
                pstDisplayParam->bDisplayFlag = FALSE;
                SBTL_TRACE(printf("\nexecmd: 02 disbplay:%x", pstDisplayParam->bDisplayFlag););
                break;
            case 0x03:  //SET_COLOR
                if(_bVobSubPaletteSetted)
                {
                    pstDisplayParam->u8Emp2Color = (cmd.extendField[0] & 0xF0) >>4;
                    pstDisplayParam->u8Emp1Color = (cmd.extendField[0] & 0x0F);
                    pstDisplayParam->u8PatternColor = (cmd.extendField[1] & 0xF0) >>4;
                    pstDisplayParam->u8BkgrdColor = (cmd.extendField[1] & 0x0F);
                }
                else
                {   // use default palette table
                    pstDisplayParam->u8Emp2Color = 3;
                    pstDisplayParam->u8Emp1Color = 2;
                    pstDisplayParam->u8PatternColor = 1;
                    pstDisplayParam->u8BkgrdColor = 0;
                }
                SBTL_TRACE(printf("\nexecmd: 03 Palette index: E2:%02x E1:%02x P:%02x B:%02x", pstDisplayParam->u8Emp2Color,pstDisplayParam->u8Emp1Color, pstDisplayParam->u8PatternColor,pstDisplayParam->u8BkgrdColor););
                break;
            case 0x04:  // SET_CONTR
                pstDisplayParam->u8Emp2Contrast = (cmd.extendField[0] & 0xF0) >>4;
                pstDisplayParam->u8Emp1Contrast = (cmd.extendField[0] & 0x0F);
                pstDisplayParam->u8PatternContrast = (cmd.extendField[1] & 0xF0) >>4;
                pstDisplayParam->u8BkgrdContrast = (cmd.extendField[1] & 0x0F);
                SBTL_TRACE(printf("\nexecmd: 04 contrast: %02x %02x %02x %02x", pstDisplayParam->u8Emp2Contrast,pstDisplayParam->u8Emp1Contrast, pstDisplayParam->u8PatternContrast,pstDisplayParam->u8BkgrdContrast););
                break;
            case 0x05:  //SET_DAREA
                pstDisplayParam->u16AreaLeft = (cmd.extendField[0] <<4) + (cmd.extendField[1] >>4);
                pstDisplayParam->u16AreaRight = ((cmd.extendField[1] & 0x0F) <<8) + cmd.extendField[2] + 1;
                pstDisplayParam->u16AreaTop = (cmd.extendField[3] <<4) + (cmd.extendField[4] >>4);
                pstDisplayParam->u16AreaBottom = ((cmd.extendField[4] & 0x0F) <<8) + cmd.extendField[5] + 1;

                if((pstDisplayParam->u16AreaRight - pstDisplayParam->u16AreaLeft) > 0)
                {
                    pstDisplayParam->u16Width = pstDisplayParam->u16AreaRight - pstDisplayParam->u16AreaLeft;
                }
                else
                {
                    pstDisplayParam->u16Width = 0;
                }
                if((pstDisplayParam->u16AreaBottom - pstDisplayParam->u16AreaTop) > 0)
                {
                    pstDisplayParam->u16Height= pstDisplayParam->u16AreaBottom - pstDisplayParam->u16AreaTop;
                    if(pstDisplayParam->u16Height %2 == 1)
                    pstDisplayParam->u16Height--;
                }
                else
                {
                    pstDisplayParam->u16Height= 0;
                }

                SBTL_TRACE(printf("\nexecmd: 05 region: L:%x R:%x T:%x B:%x", pstDisplayParam->u16AreaLeft,pstDisplayParam->u16AreaRight, pstDisplayParam->u16AreaTop,pstDisplayParam->u16AreaBottom););
                SBTL_TRACE(printf("\nexecmd: 05 region: X:%x Y:%x W:%x H:%x", pstDisplayParam->u16AreaLeft,pstDisplayParam->u16AreaTop, pstDisplayParam->u16Width, pstDisplayParam->u16Height););
                break;
            case 0x06:  //SET_DSPXA
                pstDisplayParam->u16RLTopField = (cmd.extendField[0] << 8) + (cmd.extendField[1] );
                pstDisplayParam->u16RLBottomField = (cmd.extendField[2] << 8) + (cmd.extendField[3] );
                if(pstDisplayParam->u16RLBottomField > pstDisplayParam->u16RLTopField &&
                    _u16_DCSQCT_addr > pstDisplayParam->u16RLBottomField)
                {
                    pstDisplayParam->u16RLTopLen = pstDisplayParam->u16RLBottomField - pstDisplayParam->u16RLTopField;
                    pstDisplayParam->u16RLBottomLen = _u16_DCSQCT_addr - pstDisplayParam->u16RLBottomField;
                }
                SBTL_TRACE(printf("\nexecmd: 06 pixeladr: %x %x %x %x", pstDisplayParam->u16RLTopField,pstDisplayParam->u16RLBottomField, pstDisplayParam->u16RLTopLen,pstDisplayParam->u16RLBottomLen););
                break;
            case 0x07:  //CHG_COLCON
                // not yet support now
                break;
        }
    }


    if(pstDisplayParam->bDisplayFlag && pstDisplayParam->u16RLTopLen>0)
    {
        _u8OrigGwinId = MApi_GOP_GWIN_GetCurrentWinId();
        msAPI_OSD_GetClipWindow(&_u16ClipLeft,&_u16ClipTop,&_u16ClipRight,&_u16ClipBottom);
        SBTL_TRACE(printf("\n Get osd gwinid:%x cliptwindow x:%x, y:%x, x1:%x, y1:%x", _u8OrigGwinId, _u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom););

        MApi_GOP_GWIN_SwitchGOP( E_GOP_APP );
        MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);

        switch(qeCur.enSubType)
        {
            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                msAPI_MpegSP_Renderer_Display();
                break;

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                msAPI_DivXTTF_Renderer_Display();
                break;
#endif

            default:
                break;
        }

        _u32_SPU_Display_Pts = u32Stc;

        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        msAPI_OSD_SetClipWindow(_u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom);
        MApi_GOP_GWIN_Switch2Gwin(_u8OrigGwinId);
        SBTL_TRACE(printf("\n Set osd gwinid:%x cliptwindow x:%x, y:%x, x1:%x, y1:%x", _u8OrigGwinId, _u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom););
    }
    else
    {
        SBTL_TRACE(printf("\n Clear Subtitle"););
        MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
        _u32_SPU_Display_Pts = 0;
    }


}

BOOLEAN msAPI_MpegSP_Decode_RLE(U32 u32RldOutputAddr, U8 u8TransPaletteIdx)
{
    pstSpRld->u32OutputAddress  = u32RldOutputAddr;
    SBTL_TRACE(printf("\n RLD output at pixelbuf :%lx", pstSpRld->u32OutputAddress););

    SW_RLDI2(u8TransPaletteIdx);

    return TRUE;
}

BOOLEAN msAPI_MpegSP_CmdQueue_CheckStm(U32 u32STC)
{

    if(_u32_SPU_Display_Pts >0 && u32STC < _u32_SPU_Display_Pts) // current time less than display time
    {                                                            // usually caused by player seek to prior time
        SBTL_TRACE(printf("\n cur STC:%lx less than display pts:%lx", u32STC, _u32_SPU_Display_Pts););
        SBTL_TRACE(printf("\n Clear Subtitle"););
        if(_b_MpegSP_Gwin_created)
            MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
        _u32_SPU_Display_Pts = 0;
    }

    if( msAPI_MpegSP_CmdQueue_Size() == 0)
        return FALSE;

    if(u32STC >= pstCmdQueue->cmd[pstCmdQueue->u8Front].u32Pts )
    {
        SBTL_TRACE(printf("\n cur STC:%lx larger than cmd pts:%lx", u32STC, pstCmdQueue->cmd[pstCmdQueue->u8Front].u32Pts););
        return TRUE;
    }
    else
        return FALSE;
}

BOOLEAN msAPI_MpegSP_SPU_GetByte(U32 u32ReadAddr, U8 *pu8buf )
{
    //msAPI_MIU_Copy(u32ReadAddr,XD2PHY(pu8buf),1,MIU_SDRAM2SDRAM);
    *pu8buf = *((U8*)u32ReadAddr);
    SBTL_TRACE(printf("\n Getbyte:%x", *pu8buf););
    return TRUE;
}

BOOLEAN msAPI_MpegSP_SPU_GetWord(U32 u32ReadAddr, U16 *pu16buf )
{
    *pu16buf = (*((U8*)u32ReadAddr)<<8) | *((U8*)u32ReadAddr+1);
    SBTL_TRACE(printf("\n GetWord:%x", *pu16buf););
    return TRUE;
}
/*BOOLEAN msAPI_MpegSP_SPU_GetWordLsbf(U32 u32ReadAddr, U16 *pu16buf )
{
    U8 u8ValBuf[2];
    U16 u16Addr = u8ValBuf;


    msAPI_MIU_Copy(u32ReadAddr,msAPI_MIU_XData2SDRAMAddr((U16)u16Addr),2,MIU_SDRAM2SDRAM);
    *pu16buf = (u8ValBuf[1] <<8) | u8ValBuf[0];
    SBTL_TRACE(printf("\n GetWord:%x", *pu16buf););
    return TRUE;
}*/

BOOLEAN msAPI_MpegSP_SPU_GetBuf(U32 u32ReadAddr, U8 *pu8buf, U16 u16Size )
{
    if(u16Size >0)
    {
        //msAPI_MIU_Copy(_VA2PA(u32ReadAddr),_VA2PA(XD2PHY(pu8buf)), u16Size, MIU_SDRAM2SDRAM);
        memcpy(pu8buf, (U8*)u32ReadAddr, u16Size);
        SBTL_TRACE(printf("\n Getbyte:%x", *pu8buf););
    }
    return TRUE;
}

void msAPI_MpegSP_SetMemoryLayout( void )
{
    U32 SP_PIXELBUFFER_OFFSET;
    U32 SP_PIXELBUFFER_LEN;
    U32 SP_RL_FIELD_LEN;


// The queue buffer to store the SPU payloads
#if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
    U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
    msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
    SP_STREAM_BUF_ADR = _PA2VA(u32SubtitleBufAddr);
#else
    SP_STREAM_BUF_ADR = _PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR)));   //(SP_RL_FIELD_ADR + SP_RL_FIELD_LEN);
#endif

#if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_M10) || \
     (CHIP_FAMILY_TYPE==CHIP_FAMILY_EDEN) || \
     (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA))
    SP_STREAM_BUF_LEN          =   0x60000;                                      // 131K
#else
    SP_STREAM_BUF_LEN          =   0xC0000;
#endif

    SBTL_TRACE(printf("\nsp_stram_buf:%lx", SP_STREAM_BUF_ADR););

// Memory pool for decoded pixel buffer
    SP_PIXELBUFFER_OFFSET_ADR = SP_STREAM_BUF_ADR + SP_STREAM_BUF_LEN;
    SP_PIXELBUFFER_OFFSET       = 0x25000;

    SP_PIXELBUFFER_ADR        =   MemAlign((SP_PIXELBUFFER_OFFSET_ADR +SP_PIXELBUFFER_OFFSET), 0x1000);
    SP_PIXELBUFFER_LEN        =   0x82000;  // 1956*1088/4 =0x7E900
    SBTL_TRACE(printf("\n sp_pixelbuf:%lx", SP_PIXELBUFFER_ADR););

    SP_RL_FIELD_ADR          =   (SP_PIXELBUFFER_ADR + SP_PIXELBUFFER_LEN); //(SP_STREAM_BUF_ADR+SP_STREAM_BUF_LEN);
    SP_RL_FIELD_LEN          =   0x10000;                                      // 64K
    SBTL_TRACE(printf("\n TOP field addr:%lx", SP_RL_FIELD_ADR););
}

void msAPI_MpegSP_SpuQueue_DeInit(void)
{
    if(pstCmdQueue !=NULL)
        msAPI_Memory_Free(pstCmdQueue, BUF_ID_SUBTITLE_SEC);
    pstCmdQueue = NULL;

    if(pstSpuQueue !=NULL)
        msAPI_Memory_Free(pstSpuQueue, BUF_ID_SUBTITLE_SEC);
    pstSpuQueue = NULL;

    if(pstDisplayParam !=NULL)
        msAPI_Memory_Free(pstDisplayParam, BUF_ID_SUBTITLE_SEC);
    pstDisplayParam = NULL;

    if(pstSpRld !=NULL)
        msAPI_Memory_Free(pstSpRld, BUF_ID_SUBTITLE_SEC);
    pstSpRld= NULL;

    if(pPaletteTable !=NULL)
        msAPI_Memory_Free(pPaletteTable, BUF_ID_SUBTITLE_SEC);
    pPaletteTable = NULL;

}


BOOLEAN msAPI_MpegSP_SpuQueue_Init( void )
{
    /* Set the memory layout here */
    msAPI_MpegSP_SetMemoryLayout();

    do
    {
        if(pstCmdQueue == NULL)
        {
            pstCmdQueue = (StCmdQueue *)msAPI_Memory_Allocate(sizeof(StCmdQueue), BUF_ID_SUBTITLE_SEC);
            if(pstCmdQueue == NULL)
            {
                __ASSERT(0);
                return FALSE;
            }
        }

        if(pstSpuQueue == NULL)
        {
            pstSpuQueue = (StSpuQueue *)msAPI_Memory_Allocate(sizeof(StSpuQueue), BUF_ID_SUBTITLE_SEC);
            if(pstSpuQueue == NULL)
            {
                __ASSERT(0);
                return FALSE;
            }
        }

        if(pstDisplayParam == NULL)
        {
            pstDisplayParam = (StDisplayParam *)msAPI_Memory_Allocate(sizeof(StDisplayParam), BUF_ID_SUBTITLE_SEC);
            if(pstDisplayParam == NULL)
            {
                __ASSERT(0);
                return FALSE;
            }
        }

        if(pstSpRld == NULL)
        {
            pstSpRld = (stRLDParameters *)msAPI_Memory_Allocate(sizeof(stRLDParameters), BUF_ID_SUBTITLE_SEC);
            if(pstSpRld == NULL)
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        if(pPaletteTable == NULL)
        {
            pPaletteTable = (GERGBColor *)msAPI_Memory_Allocate(sizeof(GERGBColor)*PALETTE_TABLE_SIZE, BUF_ID_SUBTITLE_SEC);
            if(pPaletteTable == NULL)
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        // successfully created all
        return TRUE;

    }while(0);

    // failed to create all
    //msAPI_MpegSP_SpuQueue_DeInit();
    return FALSE;
}


void msAPI_MpegSP_Clear_OffScreenBuffer(U8 u8TransPaletteIdx)
{
    MApi_GFX_ClearFrameBuffer(_VA2PA(SP_PIXELBUFFER_ADR),
            (U32)_u16FullPixelBuffer_Pitch* (U32)_u16FullPixelBuffer_Height/4,
            (u8TransPaletteIdx<<6) |(u8TransPaletteIdx<<4) | (u8TransPaletteIdx<<2) | u8TransPaletteIdx);// 0xff);
    MApi_GFX_FlushQueue();
}
void msAPI_MpegSP_Renderer_DeInit( void )
{
    if(_b_MpegSP_Gwin_created)
    {
        SBTL_TRACE(printf("\n mpegSP render deinit"););

        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT1, TRUE);

        MApi_GOP_GWIN_DeleteWin(gop_parameters.u8_GWIN_id);
        MApi_GOP_GWIN_SetGOPDst( E_GOP_APP, E_GOP_DST_OP0);
        _b_MpegSP_Gwin_created = FALSE;

      #if(UI_SKIN_SEL == UI_SKIN_960X540X565 || UI_SKIN_SEL == UI_SKIN_960X540XI8)
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0, 0, 0, 960, 540);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,960, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, g_IPanel.Height());
	  #elif(UI_SKIN_SEL == UI_SKIN_1920X1080X565)
	    MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0, 0, 0, 1920, 1080);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,1920, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 1080, g_IPanel.Height());
      #else
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0, 0, 0, 1360, 768);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,1360, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, g_IPanel.Height());
      #endif
    }
}

U16 msAPI_MpegSP_GetGopGwinFormat(void)
{
    switch (_u8SetGwinFormat)
    {
        case 0:
            return GFX_FMT_I8;
        case 1:
            return GFX_FMT_ARGB4444;
        case 2:
            return GFX_FMT_ARGB1555;
        default:
            return GFX_FMT_ARGB4444;
    }
}

BOOLEAN msAPI_MpegSP_Renderer_Init(void)
{
    U16 _u16VideoHSize=0;
    U16 _u16VideoVSize=0;
    GOP_PaletteEntry transPalEntry;

    XC_ApiStatus stXCStatus;

#if(ENABLE_MIU_1)
    #ifdef GOP_GWIN_RB2_ADR
    #if(GOP_GWIN_RB2_MEMORY_TYPE&MIU1)
        MApi_GOP_MIUSel(E_GOP_APP, E_GOP_SEL_MIU1);
    #else
        MApi_GOP_MIUSel(E_GOP_APP, E_GOP_SEL_MIU0);
    #endif
    #endif
#endif

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        MS_DEBUG_MSG(printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n"));
    }
#if ENABLE_DIVX_SUBTITLE_OP
    if(qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
    {
        _bEnableSubtitleOP = TRUE;
    }
    else
#endif
#if ENABLE_VOB_SUBTITLE_OP
    if(qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB)
    {
        _bEnableSubtitleOP = TRUE;
    }
    else
#endif
    {
        _bEnableSubtitleOP = FALSE;
    }
    SBTL_TRACE(printf("\nrend init qeCur.enSubType:%d _bEnableSubtitleOP:%d\n",qeCur.enSubType,_bEnableSubtitleOP););
    _u16VideoHSize = stXCStatus.stCapWin.width;
    _u16VideoVSize = stXCStatus.stCapWin.height;
    _u16VideoWidth = _u16VideoHSize;
    _u16VideoHeight = _u16VideoVSize;

    if(  _u16VideoHSize ==0 || _u16VideoVSize == 0)
        return FALSE;

#if DISABLE_HD_BMPSUB
    // Disable HD subtitle
    if(_u16VideoHSize > 720 || _u16VideoVSize > 576)
    {
        return FALSE;
    }
#endif

    if(_u16FullPixelBuffer_Width==0 || _u16FullPixelBuffer_Height==0)  // not specified then use video size
    {
        switch(qeCur.enSubType)
        {
            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                    SBTL_TRACE(printf("\nMpeg2 set pixel buffer"););
                    msAPI_MpegSP_ResetPixelBuffer(0, 0);
                break;
            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:    // For Divx setting pixel buffer
                    SBTL_TRACE(printf("\nDivX set pixel buffer"););
                    msAPI_DivXSP_ResetPixelBuffer(_u16VideoHSize, _u16VideoVSize);
                break;

        #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                    SBTL_TRACE(printf("\nDivXTTF set pixel buffer"););
                    msAPI_DivXTTF_ResetPixelBuffer(_u16VideoHSize, _u16VideoVSize);
                break;
        #endif

            default:
                break;
        }
     }
     _u16FullPixelBuffer_Pitch =  ROUND_UP(_u16FullPixelBuffer_Width+1, 32);

    SBTL_TRACE(printf("\n Reinit Video H: 0x%x, V: 0x%x \n", _u16VideoHSize, _u16VideoVSize));//, bRet));

    // Get Gwin format dynamically
    GOP_GWIN_FORMAT = msAPI_MpegSP_GetGopGwinFormat();

    _u8OrigGwinId = MApi_GOP_GWIN_GetCurrentWinId();
    msAPI_OSD_GetClipWindow(&_u16ClipLeft,&_u16ClipTop,&_u16ClipRight,&_u16ClipBottom);
    SBTL_TRACE(printf("\n Get osd gwinid:%x cliptwindow x:%x, y:%x, x1:%x, y1:%x", _u8OrigGwinId, _u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom););

    if(hBMP ==0)
        hBMP = msAPI_OSD_RESOURCE_LoadBitmap(0x0, (U32)_u16FullPixelBuffer_Pitch*_u16FullPixelBuffer_Height/4, _u16FullPixelBuffer_Pitch/4, _u16FullPixelBuffer_Height, BMP_FMT_ARGB1555);

    if(_bEnableSubtitleOP)
    {
        gop_parameters.u16_GWIN_width = GWIN_WIDTH;
        gop_parameters.u16_GWIN_height = GWIN_HEIGHT;
    }
    else
    {
        gop_parameters.u16_GWIN_width = ROUND_DOWN(_u16VideoHSize, 8) < GWIN_WIDTH_LIMIT ? ROUND_DOWN(_u16VideoHSize, 8) : GWIN_WIDTH_LIMIT;
        gop_parameters.u16_GWIN_height = _u16VideoVSize < GWIN_HEIGHT_LIMIT ? _u16VideoVSize: GWIN_HEIGHT_LIMIT;  // fine tune gwin bottom
    }
    gop_parameters.u16_GWIN_left = 0;
    gop_parameters.u16_GWIN_top = 0;

    MApi_GOP_GWIN_OutputLayerSwitch(E_GOP_OSD);

    if(_bEnableSubtitleOP)
    {
        MApi_GOP_GWIN_SetGOPDst( E_GOP_APP, E_GOP_DST_OP0);
    }
    else
    {
        MApi_GOP_GWIN_SetGOPDst( E_GOP_APP, E_GOP_DST_IP0);
    }

    MApi_GOP_GWIN_SwitchGOP( E_GOP_APP ); //sw to GOP1

    if(!_bEnableSubtitleOP)
    {
        if(REDUCE_GWIN)
        {
            // If HD reduce gwin to 1/2 video width
            if(_u16VideoHSize >= 1280)
            {
                gop_parameters.u16_GWIN_width = gop_parameters.u16_GWIN_width/2;
                SBTL_TRACE(printf("\nReduce Gwin width:%x", gop_parameters.u16_GWIN_width);)
            }
#if (CHIP_FAMILY_TYPE==CHIP_FAMILY_M10)
            gop_parameters.u16_GWIN_height = gop_parameters.u16_GWIN_height/2;
#endif
        }
    }

    gop_parameters.u8_GWIN_id =MApi_GOP_GWIN_CreateWin2( gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height, GOP_GWIN_FORMAT, E_GOP_FB_SUBTITLE);
    if(gop_parameters.u8_GWIN_id == GWIN_ID_INVALID)
    {
        // create frame buffer fails, do nothing
        SBTL_ERR(printf("\nFail to create gwin (W:%x, H:%x)", gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height););
        return FALSE;
    }
    SBTL_TRACE(printf("\nRinit get Video  (W:%x, H:%x)", _u16VideoHSize, _u16VideoVSize););
    SBTL_TRACE(printf("\nRinit created gwin id: %x (W:%x, H:%x)", gop_parameters.u8_GWIN_id, gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height););

    // MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);

    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
    {
        transPalEntry.RGB.u8A = transPalEntry.RGB.u8R = transPalEntry.RGB.u8G = transPalEntry.RGB.u8B = 0x00;

        // the different GOP use different GOP api
        if(E_GOP_APP == 0)
        {
            MApi_GOP_GWIN_SetPaletteOpt(&transPalEntry, 0x04, 0x04, E_GOP_PAL_ARGB8888);  // set 4th palette entry as transparent bg
        }
        if(E_GOP_APP == 1)
        {
            MApi_GOP_GWIN_2GSetPaletteOpt(&transPalEntry, 0x04, 0x04);  // set 4th palette entry as transparent bg
        }
    }

    // clear the frame buffer
    msAPI_MpegSP_Renderer_ClearDisplayBlock(gop_parameters.u8_GWIN_id, 0, 0, gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height);

    MApi_GOP_GWIN_SetBlending(gop_parameters.u8_GWIN_id, TRUE, 0xFF); // 255

    if(_bEnableSubtitleOP)
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height);
    }
    else
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_IP0, 0, 0, gop_parameters.u16_GWIN_width, gop_parameters.u16_GWIN_height);
    }

    if(_bEnableSubtitleOP)
    {
        MApi_GOP_GWIN_Set_HSCALE(TRUE,GWIN_WIDTH, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, GWIN_HEIGHT, g_IPanel.Height());
    }
    else
    {
        if(REDUCE_GWIN)
        {
            if(_u16VideoHSize >= 1280)
            {
                MApi_GOP_GWIN_Set_HSCALE(TRUE,1,2);
            }
            else
            {
                MApi_GOP_GWIN_Set_HSCALE(TRUE,1,1);
            }
        }
        else
        {
            MApi_GOP_GWIN_Set_HSCALE(TRUE,1,1);
        }
        MApi_GOP_GWIN_Set_VSCALE(TRUE,1,1);
    }

    MApi_GOP_GWIN_SetWinPosition(gop_parameters.u8_GWIN_id, gop_parameters.u16_GWIN_left, gop_parameters.u16_GWIN_top);
    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);

    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, TRUE);
    else if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
    else
        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT1, FALSE);      // disable transparent color

    //MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_IP0);
    MApi_GOP_GWIN_SetFieldInver(TRUE); //set file inverse for interlace mode
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    msAPI_OSD_SetClipWindow(_u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom);
    MApi_GOP_GWIN_Switch2Gwin(_u8OrigGwinId);
    _b_MpegSP_Gwin_created = TRUE;
    SBTL_TRACE(printf("\n Set osd gwinid:%x cliptwindow x:%x, y:%x, x1:%x, y1:%x", _u8OrigGwinId, _u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom););

    return TRUE;

}

static void msAPI_MpegSP_Renderer_ClearDisplayBlock(U8 u8_GWID, U16 u16_x, U16 u16_y, U16 u16_width, U16 u16_height )
{
    OSDClrBtn clrBtn;

    MApi_GOP_GWIN_Switch2Gwin(u8_GWID);
    msAPI_OSD_SetClipWindow(u16_x, u16_y, u16_x + u16_width, u16_y + u16_height);

    clrBtn.x = u16_x;
    clrBtn.y = u16_y;
    clrBtn.width = u16_width;
    clrBtn.height = u16_height;
    clrBtn.u8Gradient = CONSTANT_COLOR;
    clrBtn.fHighLight = FALSE;

    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        clrBtn.b_clr = 0x04;    // let 0x04 as transparent color index
    else
        clrBtn.b_clr = 0x00;
    MApi_GFX_SetAlpha(FALSE, COEF_ONE, ABL_FROM_ASRC, 0xFF);//Disable Alpha Blending
    msAPI_OSD_DrawBlock(&clrBtn);

}

static U8 msAPI_MpegSP_SetGopPalette(void)  //GOP_PaletteEntry *PaletteArray)
{
    U8 u8_i;
    GERGBColor   *pst_gePalette=NULL;
    U8 u8TransPaletteIdx=0xff;
    GOP_PaletteEntry PaletteArray[4];

    if( (qeCur.enSubType != E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
      #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
        && (qeCur.enSubType != E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8)
        && (qeCur.enSubType != E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS)
        && (qeCur.enSubType != E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA)
      #endif
      )  //not divx
    {
        if( !_bVobSubPaletteSetted)
        {   // reset emp, pattern color by image detection
            if(_u8IdxInnerCheck== 0xFF || _u8IdxInnerCheck < 8)
                maAPI_MpegSP_SetPaletteIdx();
        }
        memcpy(&gePaletteBkg, pPaletteTable + pstDisplayParam->u8BkgrdColor, 4);
        memcpy(&gePalettePat, pPaletteTable + pstDisplayParam->u8PatternColor, 4);
        memcpy(&gePaletteEmp1, pPaletteTable + pstDisplayParam->u8Emp1Color, 4);
        memcpy(&gePaletteEmp2, pPaletteTable + pstDisplayParam->u8Emp2Color, 4);

        // map 16 level transparency to 256 level
        gePaletteBkg.a = (pstDisplayParam->u8BkgrdContrast << 4) +pstDisplayParam->u8BkgrdContrast;
        gePalettePat.a = (pstDisplayParam->u8PatternContrast << 4) +pstDisplayParam->u8PatternContrast;
        gePaletteEmp1.a = (pstDisplayParam->u8Emp1Contrast << 4) +pstDisplayParam->u8Emp1Contrast;
        gePaletteEmp2.a = (pstDisplayParam->u8Emp2Contrast << 4) +pstDisplayParam->u8Emp2Contrast;
    }

    for(u8_i = 0; u8_i < PALETTE_UNIT; u8_i ++)
    {
        switch(u8_i)
        {
            case 0x00:
                pst_gePalette = &gePaletteBkg;
                break;
            case 0x01:
                pst_gePalette = &gePalettePat;
                break;
            case 0x02:
                pst_gePalette = &gePaletteEmp1;
                break;
            case 0x03:
                pst_gePalette = &gePaletteEmp2;
                break;
        }

        if(u8TransPaletteIdx == 0xff && pst_gePalette->a == 0x00)
        {
            if(GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
            {
                U16 u16TransKey = 0;

                // Use backgrand color as transparent color, set transparent color to ARGB1555 mode
                u16TransKey |= (pst_gePalette->r >> 3) << 10;
                u16TransKey |= (pst_gePalette->g >> 3) << 5;
                u16TransKey |= (pst_gePalette->b >> 3);

                MApi_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT0, u16TransKey);
            }
            if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
            {
                //U16 u16TransKey = 0;

                // set background as black for avoid bilinear add some other color
                pst_gePalette->r = pst_gePalette->g = pst_gePalette->b = 0x00;

                // Use backgrand color as transparent color, set transparent color to ARGB4444 mode
                //u16TransKey |= (pst_gePalette->r >> 4) << 8;
                //u16TransKey |= (pst_gePalette->g >> 4) << 4;
                //u16TransKey |= (pst_gePalette->b >> 4);

                //MApi_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT0, u16TransKey);
            }
            u8TransPaletteIdx = u8_i;
        }

        if( (qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
          #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
            || (qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8)
            || (qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS)
            || (qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA)
          #endif
          )  //divx may have non-transparent color
        {  // palette table changed , to avoid subtitle color update on screen
            if(pst_gePalette->a != pPaletteTable[u8_i].a ||pst_gePalette->r != pPaletteTable[u8_i].r ||
               pst_gePalette->g != pPaletteTable[u8_i].g ||pst_gePalette->b != pPaletteTable[u8_i].b )
            {
                MApi_GOP_GWIN_Enable( gop_parameters.u8_GWIN_id, FALSE);
                pPaletteTable[u8_i].b =  pst_gePalette->b;
                pPaletteTable[u8_i].g =  pst_gePalette->g;
                pPaletteTable[u8_i].r  = pst_gePalette->r;
                pPaletteTable[u8_i].a = pst_gePalette->a;
            }
        }

        if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        {
            U32 u32tmpPalette= u8_i;

            PaletteArray[u8_i].RGB.u8B = pst_gePalette->b;
            PaletteArray[u8_i].RGB.u8G = pst_gePalette->g;
            PaletteArray[u8_i].RGB.u8R = pst_gePalette->r;
            PaletteArray[u8_i].RGB.u8A = pst_gePalette->a;
            MApi_GFX_SetIntensity(u8_i, GFX_FMT_ARGB8888, (U32 *)&u32tmpPalette);
        }
        else if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444 || GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
        {
            MApi_GFX_SetIntensity(u8_i, GFX_FMT_ARGB8888, (U32 *)(void *)pst_gePalette);
        }
        SBTL_TRACE(printf("\n SetPalette idx:%x, argb: %02x %02x %02x %02x", u8_i, pst_gePalette->a, pst_gePalette->r ,pst_gePalette->g,pst_gePalette->b););

    }

    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
    {
        // the different GOP use different GOP api
        if(E_GOP_APP == 0)
        {
            MApi_GOP_GWIN_SetPaletteOpt(PaletteArray, 0, PALETTE_UNIT-1, E_GOP_PAL_ARGB8888);
        }
        if(E_GOP_APP == 1)
        {
            MApi_GOP_GWIN_2GSetPaletteOpt(PaletteArray, 0, PALETTE_UNIT-1);
        }
    }
    return  u8TransPaletteIdx;  // return 0xff if not found transparent idx

}

//////////////////////////////////////////////////////////////////////////////////////
///Set DVD highlight palette table : set only for highlight subtitle
///@param None
///@return u8TransPaletteIdx \b OUT transparent palette index
//////////////////////////////////////////////////////////////////////////////////////
static U8 msAPI_MpegSP_SetGopPaletteHighlight(void)
{
    U8 u8_i;
    GERGBColor   *pst_gePalette=NULL;
    U8 u8TransPaletteIdx=0xff;
    GOP_PaletteEntry PaletteArray[4];

    if(qeCur.enSubType !=E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)  //not divx
    {
        U8 BgIdx, PatternIdx, Emp1Idx, Emp2Idx;
        U8 Bg, Pat, E1, E2;

        if( !_bVobSubPaletteSetted)
        {   // reset emp, pattern color by image detection
            if(_u8IdxInnerCheck== 0xFF || _u8IdxInnerCheck < 8)
                maAPI_MpegSP_SetPaletteIdx();
        }

        Emp2Idx = (_u32Highlight_Palette >> 28) & 0x0F;
        Emp1Idx = (_u32Highlight_Palette >> 24) & 0x0F;
        PatternIdx = (_u32Highlight_Palette >> 20) & 0x0F;
        BgIdx = (_u32Highlight_Palette >> 16) & 0x0F;

        memcpy(&gePaletteBkg, pPaletteTable + BgIdx, 4);
        memcpy(&gePalettePat, pPaletteTable + PatternIdx, 4);
        memcpy(&gePaletteEmp1, pPaletteTable + Emp1Idx, 4);
        memcpy(&gePaletteEmp2, pPaletteTable + Emp2Idx, 4);

        // map 16 level transparency to 256 level
        E2 = (_u32Highlight_Palette >> 12) & 0x0F;
        E1 = (_u32Highlight_Palette >> 8) & 0x0F;
        Pat = (_u32Highlight_Palette >> 4) & 0x0F;
        Bg = (_u32Highlight_Palette >> 0) & 0x0F;

        gePaletteBkg.a = ((Bg << 4) | Bg);
        gePalettePat.a = ((Pat << 4) | Pat);
        gePaletteEmp1.a = ((E1 << 4) | E1);
        gePaletteEmp2.a = ((E2 << 4) | E2);
    }

    for(u8_i = 0; u8_i < PALETTE_UNIT; u8_i ++)
    {
         switch(u8_i)
         {
            case 0x00:
                pst_gePalette = &gePaletteBkg;
                break;
            case 0x01:
                pst_gePalette = &gePalettePat;
                break;
            case 0x02:
                pst_gePalette = &gePaletteEmp1;
                break;
            case 0x03:
                pst_gePalette = &gePaletteEmp2;
                break;
         }

         if(u8TransPaletteIdx == 0xff && pst_gePalette->a == 0x00)
         {
            if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
            {
                U16 u16TransKey = 0;

                // Use backgrand color as transparent color, set transparent color to ARGB1555 mode
                u16TransKey |= (pst_gePalette->r >> 4) << 8;
                u16TransKey |= (pst_gePalette->g >> 4) << 4;
                u16TransKey |= (pst_gePalette->b >> 4);

                MApi_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT0, u16TransKey);
            }

            u8TransPaletteIdx = u8_i;
         }

         if(qeCur.enSubType ==E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)  //divx may have non-transparent color
         {  // palette table changed , to avoid subtitle color update on screen
            if(pst_gePalette->a != pPaletteTable[u8_i].a ||pst_gePalette->r != pPaletteTable[u8_i].r ||
               pst_gePalette->g != pPaletteTable[u8_i].g ||pst_gePalette->b != pPaletteTable[u8_i].b )
            {
                MApi_GOP_GWIN_Enable( gop_parameters.u8_GWIN_id, FALSE);
                pPaletteTable[u8_i].b =  pst_gePalette->b;
                pPaletteTable[u8_i].g =  pst_gePalette->g;
                pPaletteTable[u8_i].r  = pst_gePalette->r;
                pPaletteTable[u8_i].a = pst_gePalette->a;
            }
         }

        if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        {
            U32 u32tmpPalette= u8_i;

            PaletteArray[u8_i].RGB.u8B = pst_gePalette->b;
            PaletteArray[u8_i].RGB.u8G = pst_gePalette->g;
            PaletteArray[u8_i].RGB.u8R = pst_gePalette->r;
            PaletteArray[u8_i].RGB.u8A = pst_gePalette->a;
            MApi_GFX_SetIntensity(u8_i, GFX_FMT_ARGB8888, (U32 *)&u32tmpPalette);
        }
        else if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444 || GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
        {
            MApi_GFX_SetIntensity(u8_i, GFX_FMT_ARGB8888, (U32 *)(void *)pst_gePalette);
        }
        SBTL_TRACE(printf("\n SetPalette idx:%x, argb: %02x %02x %02x %02x", u8_i, pst_gePalette->a, pst_gePalette->r ,pst_gePalette->g,pst_gePalette->b););
    }

    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        MApi_GOP_GWIN_SetPaletteOpt(PaletteArray, 0, PALETTE_UNIT-1, E_GOP_PAL_ARGB8888);

    return  u8TransPaletteIdx;  // return 0xff if not found transparent idx

}


static BOOLEAN msAPI_MpegSP_Renderer_Display( void )
{
    GEPoint st_point;
    GEBitmapFmt bmpfmt;
    U32 u32RldOutputAddr;
    U8 u8AlignmentGap;
    U8 u8TransPaletteIdx;
    U16 u16DstTop = 0;
    U16 u16Ratio = 0;

    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    SBTL_TRACE(printf("\n================== DISPLAY ======================="););


    SBTL_TRACE(printf("\nRegion(X:%x,Y:%x,W:%x,H:%x)",
            pstDisplayParam->u16AreaLeft,
            pstDisplayParam->u16AreaTop,
            pstDisplayParam->u16Width,
            pstDisplayParam->u16Height
            ););

    // check off screen buffer based on subtitle info and then refine to video size
    if((_u16FullPixelBuffer_Width == 0) || (_u16FullPixelBuffer_Height == 0))
    {
        _u16FullPixelBuffer_Width = 2 * pstDisplayParam->u16AreaLeft + pstDisplayParam->u16Width;
        _u16FullPixelBuffer_Height = pstDisplayParam->u16AreaTop + pstDisplayParam->u16Height + 20;

        // refine off screen height to video width, SUBTITLE_DIFF_VIDEO_SCREEN is temp define
       if(_u16FullPixelBuffer_Width <= _u16VideoWidth)
       {
            if((_u16VideoWidth - _u16FullPixelBuffer_Width) < SUBTITLE_DIFF_VIDEO_SCREEN)
            {
                _u16FullPixelBuffer_Width = _u16VideoWidth;
            }
        }
        else
        {
            if((_u16FullPixelBuffer_Width - _u16VideoWidth) < SUBTITLE_DIFF_VIDEO_SCREEN)
            {
                _u16FullPixelBuffer_Width = _u16VideoWidth;
            }
        }

        // refine off screen height to video height
        if(_u16FullPixelBuffer_Height <= _u16VideoHeight)
        {
            if((_u16VideoHeight - _u16FullPixelBuffer_Height) < SUBTITLE_DIFF_VIDEO_SCREEN)
            {
                _u16FullPixelBuffer_Height = _u16VideoHeight;
            }
        }
        else
        {
            if((_u16FullPixelBuffer_Height - _u16VideoHeight) < SUBTITLE_DIFF_VIDEO_SCREEN)
            {
                _u16FullPixelBuffer_Height = _u16VideoHeight;
            }
        }

        u16Ratio = _u16FullPixelBuffer_Width / _u16FullPixelBuffer_Height;
        if(u16Ratio > SUBTITLE_MAX_SEREEN_RATIO)
        {
            _u16FullPixelBuffer_Height = _u16FullPixelBuffer_Width * g_IPanel.Height() / g_IPanel.Width();
        }
    }

    ///////////// fine tune subtitle off screen pixel buffer size
    _u16FullPixelBuffer_Width= pstDisplayParam->u16AreaRight - pstDisplayParam->u16AreaLeft> _u16FullPixelBuffer_Width? pstDisplayParam->u16AreaRight - pstDisplayParam->u16AreaLeft : _u16FullPixelBuffer_Width;
    #if ENABLE_DIVX_SUBTITLE_OP
    // divx subtitle not need to do fine tune
    if(qeCur.enSubType != E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
    {
        _u16FullPixelBuffer_Height = (pstDisplayParam->u16AreaBottom) + SUBTL_ABOVE_BOTTOM > _u16FullPixelBuffer_Height ? (pstDisplayParam->u16AreaBottom) + SUBTL_ABOVE_BOTTOM: _u16FullPixelBuffer_Height; // it should be smaller than +27 for divx H01 korean language
    }
    else
    {
        _u16FullPixelBuffer_Height = (pstDisplayParam->u16AreaBottom) > _u16FullPixelBuffer_Height ? (pstDisplayParam->u16AreaBottom): _u16FullPixelBuffer_Height;
    }
    #else
    {
        _u16FullPixelBuffer_Height = (pstDisplayParam->u16AreaBottom) + SUBTL_ABOVE_BOTTOM > _u16FullPixelBuffer_Height ? (pstDisplayParam->u16AreaBottom) + SUBTL_ABOVE_BOTTOM: _u16FullPixelBuffer_Height; // it should be smaller than +27 for divx H01 korean language
    }
    #endif
    _u16FullPixelBuffer_Pitch =  ROUND_UP(_u16FullPixelBuffer_Width, 32);
    u8AlignmentGap = 0;
    SBTL_TRACE(printf("\n Finetune PixelBufer to Width:%x Pitch:%x Height:%x", _u16FullPixelBuffer_Width, _u16FullPixelBuffer_Pitch, _u16FullPixelBuffer_Height););
    //SBTL_TRACE(printf("\n orig X,Y:(%x,%x) capHstart:%x capVstart:%x  Cap (%x, %x), PixelWin(%x, %x)",gop_parameters.u16_GWIN_left,gop_parameters.u16_GWIN_top, g_SrcInfo.u16H_CapStart, g_SrcInfo.u16V_CapStart,g_SrcInfo.u16H_CapSize, g_SrcInfo.u16V_CapSize, _u16FullPixelBuffer_Pitch, _u16FullPixelBuffer_Height);)


    // fine tune subtitle position when the height of the subtitle is bigger than the height of the video
    if(_u8YPosScale==0xFF && _u16FullPixelBuffer_Height/2 > gop_parameters.u16_GWIN_height)
    {
        _u8YPosScale = (U8)(((U32)gop_parameters.u16_GWIN_height*100)/(_u16FullPixelBuffer_Height/2));
        SBTL_TRACE(printf("\nYScale=%x, Height=%x, PixBuffer=%x", _u8YPosScale, gop_parameters.u16_GWIN_height, _u16FullPixelBuffer_Height);)
    }

    ///////////// fine tune subtitle position by u8XPosScale, u8YPosScale
    if(_u8XPosScale != 0xFF)
    {
        U16 u16tmpAreaRight = (U32)_u16FullPixelBuffer_Pitch*_u8XPosScale/100;
        pstDisplayParam->u16AreaLeft = u16tmpAreaRight > pstDisplayParam->u16Width?  u16tmpAreaRight - pstDisplayParam->u16Width: 0;
    }
    else if(pstDisplayParam->u16AreaLeft != 0)
    {
        U16 u16tmpAreaRight = pstDisplayParam->u16AreaLeft + pstDisplayParam->u16Width;
        U16 u16tmpAreaLeft = pstDisplayParam->u16AreaLeft;

        if(u16tmpAreaRight > _u16FullPixelBuffer_Width)
        {
            pstDisplayParam->u16AreaLeft =
                ((_u16FullPixelBuffer_Width >  pstDisplayParam->u16Width) ? (_u16FullPixelBuffer_Width -  pstDisplayParam->u16Width) / 2 : 0);
        }
        else
        {

            pstDisplayParam->u16AreaLeft =
                ((_u16FullPixelBuffer_Width >  pstDisplayParam->u16Width) ? (_u16FullPixelBuffer_Width -  pstDisplayParam->u16Width) / 2 : pstDisplayParam->u16AreaLeft );
            //if new  pstDisplayParam->u16AreaLeft  > orginal pstDisplayParam->u16AreaLeft subtitle may lost data
            pstDisplayParam->u16AreaLeft =  (pstDisplayParam->u16AreaLeft >u16tmpAreaLeft) ? u16tmpAreaLeft : pstDisplayParam->u16AreaLeft;
        }
    }

    u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR + ((U32) pstDisplayParam->u16AreaTop*_u16FullPixelBuffer_Pitch + pstDisplayParam->u16AreaLeft)/4;

    if(_u8YPosScale != 0xFF)
    {
        _u16FinetunedBot= (U32)_u16FullPixelBuffer_Height*_u8YPosScale/100;
        _u16FullPixelBuffer_Height= pstDisplayParam->u16AreaBottom;
        u16DstTop = (U16)_u16FullPixelBuffer_Height*_u8YPosScale/100/20;

        if( pstDisplayParam->u16Height > _u16FinetunedBot )   // move ahead the rld ouput in front of the pixelbuffer
        {
            U16 u16OffsetLines = pstDisplayParam->u16Height - _u16FinetunedBot;
            u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR - ((U32) u16OffsetLines *_u16FullPixelBuffer_Pitch - pstDisplayParam->u16AreaLeft)/4;
            pstDisplayParam->u16AreaTop = 0;
            if(u32RldOutputAddr < SP_PIXELBUFFER_OFFSET_ADR)
            {
                U16 u16GapLines = (U32)(SP_PIXELBUFFER_OFFSET_ADR - u32RldOutputAddr) / (_u16FullPixelBuffer_Pitch/4);
                u32RldOutputAddr = u32RldOutputAddr + (U32) _u16FullPixelBuffer_Pitch * (u16GapLines+1) /4;
                _u16FinetunedBot += (u16GapLines+1);
            }
        }
        else    //cropped subtitle
        {
            if(_u16FinetunedBot < pstDisplayParam->u16AreaBottom)
            {
                pstDisplayParam->u16AreaTop= _u16FinetunedBot - pstDisplayParam->u16Height;
                u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR + ((U32) pstDisplayParam->u16AreaTop*_u16FullPixelBuffer_Pitch + pstDisplayParam->u16AreaLeft)/4;
            }
            else
                _u16FinetunedBot = pstDisplayParam->u16AreaBottom;
        }
    }
    else
        _u16FinetunedBot= pstDisplayParam->u16AreaBottom;

    SBTL_TRACE(printf("\n Finetune subtitle Pos: Xscale:%x, XNewpos:%x, Yscale:%x, YNewpos:%x", _u8XPosScale,pstDisplayParam->u16AreaLeft, _u8YPosScale, pstDisplayParam->u16AreaTop););

    u8TransPaletteIdx = msAPI_MpegSP_SetGopPalette();

    msAPI_MpegSP_Clear_OffScreenBuffer(u8TransPaletteIdx);
    if(msAPI_MpegSP_Decode_RLE(u32RldOutputAddr, u8TransPaletteIdx) == FALSE)
        return FALSE;

    msAPI_OSD_SetClipWindow(0,0, gop_parameters.u16_GWIN_width-1, gop_parameters.u16_GWIN_height -1);

    bmpfmt.bBmpColorKeyEnable = FALSE;
    bmpfmt.bScale = TRUE;

    bmpfmt.width = ROUND_DOWN(gop_parameters.u16_GWIN_width, 8);
    bmpfmt.height = gop_parameters.u16_GWIN_height;

    st_point.x =  u8AlignmentGap;
    st_point.y =  0;
    SBTL_TRACE(printf("\nBmp At Gwin(X:%x,Y:%x,W:%x,H:%x) gwin( id:%x w:%x, h:%x)",
            st_point.x, st_point.y,
            bmpfmt.width, bmpfmt.height, gop_parameters.u8_GWIN_id,gop_parameters.u16_GWIN_width,gop_parameters.u16_GWIN_height););

    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
        MApi_GFX_SetNearestMode(FALSE);
    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        MApi_GFX_SetNearestMode(TRUE);
    MApi_GFX_SetPatchMode(TRUE);
    //MDrv_GE_DrawBitmap(hBMP, &st_point, &bmpfmt);


    // use Bitblt method to replace GE Draw Bitmap
    U32 u32Faddr;
    U8 fid = MApi_GOP_GWIN_GetFBfromGWIN(gop_parameters.u8_GWIN_id);
    MApi_GOP_GWIN_GetFBAddr(fid, &u32Faddr);

    if(_bEnableSubtitleOP)
    {
        /* dst dimension */
        BitbltInfo.BitbltCoordinate.height = bmpfmt.height;
        BitbltInfo.BitbltCoordinate.width  = _u16FullPixelBuffer_Width * bmpfmt.height/_u16FullPixelBuffer_Height;//bmpfmt.width;
        /* x y */
        BitbltInfo.BitbltCoordinate.v0_x = GWIN_WIDTH > BitbltInfo.BitbltCoordinate.width ? (GWIN_WIDTH-BitbltInfo.BitbltCoordinate.width)/2 : 0;
        BitbltInfo.BitbltCoordinate.v0_y = u16DstTop;
        BitbltInfo.BitbltCoordinate.v2_x = 0;
        BitbltInfo.BitbltCoordinate.v2_y = 0;
    }
    else
    {
        /* dst dimension */
        BitbltInfo.BitbltCoordinate.height = bmpfmt.height;
        BitbltInfo.BitbltCoordinate.width  = bmpfmt.width;
        BitbltInfo.BitbltCoordinate.v0_x = 0;
        BitbltInfo.BitbltCoordinate.v0_y = u16DstTop;
        BitbltInfo.BitbltCoordinate.v2_x = 0;
        BitbltInfo.BitbltCoordinate.v2_y = 0;
    }
    if(u8TransPaletteIdx  == 0xff)
    {
        U16 u16AreaLeft8Gwin, u16AreaTop8Gwin, u16AreaRight8Gwin, u16AreaBot8Gwin;

        if(_bEnableSubtitleOP)
        {
            u16AreaLeft8Gwin = (U32)pstDisplayParam->u16AreaLeft* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height + BitbltInfo.BitbltCoordinate.v0_x;
            u16AreaTop8Gwin = (U32)pstDisplayParam->u16AreaTop* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
            u16AreaRight8Gwin = (U32)pstDisplayParam->u16AreaRight* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height + BitbltInfo.BitbltCoordinate.v0_x;
            u16AreaBot8Gwin = (U32)pstDisplayParam->u16AreaBottom* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
            msAPI_MpegSP_Renderer_ClearDisplayBlock(gop_parameters.u8_GWIN_id, 0, 0, gop_parameters.u16_GWIN_width - 1, gop_parameters.u16_GWIN_height - 1);
        }
        else
        {
            u16AreaLeft8Gwin = (U32)pstDisplayParam->u16AreaLeft* gop_parameters.u16_GWIN_width/_u16FullPixelBuffer_Pitch;
            u16AreaTop8Gwin = (U32)pstDisplayParam->u16AreaTop* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
            u16AreaRight8Gwin = (U32)pstDisplayParam->u16AreaRight* gop_parameters.u16_GWIN_width/_u16FullPixelBuffer_Pitch;
            u16AreaBot8Gwin = (U32)_u16FinetunedBot* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
            msAPI_MpegSP_Renderer_ClearDisplayBlock(gop_parameters.u8_GWIN_id, 0, 0, gop_parameters.u16_GWIN_width - 1, gop_parameters.u16_GWIN_height - 1);
        }

        if(qeCur.enSubType != E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
        {
            msAPI_OSD_SetClipWindow(u16AreaLeft8Gwin,u16AreaTop8Gwin,u16AreaRight8Gwin,u16AreaBot8Gwin);
        }
        else
        {
            BitbltInfo.BitbltCoordinate.height = u16AreaBot8Gwin - u16AreaTop8Gwin +1;
            BitbltInfo.BitbltCoordinate.width =  u16AreaRight8Gwin - u16AreaLeft8Gwin+1;

            BitbltInfo.BitbltCoordinate.v0_x = u16AreaLeft8Gwin;
            BitbltInfo.BitbltCoordinate.v0_y = u16AreaTop8Gwin;
            BitbltInfo.BitbltCoordinate.v2_x = pstDisplayParam->u16AreaLeft;
            BitbltInfo.BitbltCoordinate.v2_y = pstDisplayParam->u16AreaTop;
        }
    }

    /* src dimension */
    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;

    if((u8TransPaletteIdx  == 0xff) &&  (qeCur.enSubType == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP))
    {

        BitbltInfo.src_height = pstDisplayParam->u16AreaBottom- pstDisplayParam->u16AreaTop+1;
        BitbltInfo.src_width = pstDisplayParam->u16AreaRight - pstDisplayParam->u16AreaLeft+1;
    }
    else
    {
        BitbltInfo.src_height     = _u16FullPixelBuffer_Height;
        BitbltInfo.src_width      = _u16FullPixelBuffer_Width;
    }

    /* src base */
    BitbltInfo.src_fm   = GFX_FMT_I2;
    PitBaseInfo.sb_base = _VA2PA(SP_PIXELBUFFER_ADR);
    PitBaseInfo.sb_pit  = _u16FullPixelBuffer_Pitch/4;

    /* dst base */
    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB1555;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB4444;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else
    {
        BitbltInfo.dst_fm   = GFX_FMT_I8;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width;
    }

    msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
    MApi_GFX_FlushQueue();
    SBTL_TRACE(printf("\nbitblt to  Gwin addr:%lx", u32Faddr););

    //MDrv_GE_SetNearestMode(FALSE);

    MApi_GFX_SetPatchMode(FALSE);
    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, TRUE);
    memcpy(&qePreDisp,&qeCur,sizeof(StQueueElement));
    return TRUE;
}

void msAPI_MpegSP_SetVideoDimension(U16 u16Width, U16 u16Height)
{
    //SBTL_TRACE(printf("\n Mpeg sub set dimension :%x, %x", u16Width, u16Height);)
    // abandoned
    // Added it by coverity_0478
    UNUSED(u16Width);
    UNUSED(u16Height);
}

void msAPI_MpegSP_SetSubtitleDimension(U16 u16Width, U16 u16Height)
{
    SBTL_TRACE(printf("\n Mpeg sub set subtitle dimension :%x, %x", u16Width, u16Height);)
    _u16FullPixelBuffer_Width = u16Width;
    _u16FullPixelBuffer_Height = u16Height;
}

void msAPI_MpegSP_SetPalette(U32 *u32PaletteArray, U8 u8ArraySize)
{
    U8 u8PaletteSize = u8ArraySize < PALETTE_TABLE_SIZE? u8ArraySize : PALETTE_TABLE_SIZE;

    if(pPaletteTable == NULL)
        pPaletteTable = (GERGBColor *)msAPI_Memory_Allocate(sizeof(GERGBColor)*PALETTE_TABLE_SIZE, BUF_ID_SUBTITLE_SEC);
    if (pPaletteTable == NULL)
    {
        ASSERT(pPaletteTable);
        return;
    }
    SBTL_TRACE(printf("\n msAPI_MpegSP_SetPalette first argb: %02x %02x %02x %02x", pPaletteTable->a, pPaletteTable->r, pPaletteTable->g, pPaletteTable->b););

    memcpy(pPaletteTable, u32PaletteArray, u8PaletteSize*4);

    _bVobSubPaletteSetted = TRUE;
}

U32 msAPI_MpegSP_SpuQueue_GetSDRAM_BaseAddress(void)
{
    return SP_STREAM_BUF_ADR;
}

U32 msAPI_MpegSP_SpuQueue_GetSDRAM_Size(void)
{
    return SP_STREAM_BUF_LEN;
}

void msAPI_MpegSP_SetPositionScale(U8 u8XPosScale, U8 u8YPosScale)
{
    if(u8XPosScale== 0xff || u8XPosScale<= 100 )
        _u8XPosScale= u8XPosScale;
    if(u8YPosScale== 0xff || u8YPosScale<= 100 )
        _u8YPosScale= u8YPosScale;

    if(_b_MpegSP_Gwin_created)
    {
        U16 u16tmpAreaBot = (U32)_u16FullPixelBuffer_Height*_u8YPosScale/100;

        if(  ((_u8YPosScale == 0xFF) && (_u16FinetunedBot != pstDisplayParam->u16AreaBottom)) || // currently finetuned
              ((_u8YPosScale != 0xFF) && (u16tmpAreaBot < _u16FinetunedBot) )   // need to shift upper
          )
        {
            MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
            msAPI_Decode_SPU();   // re decode current qe again.
        }
    }
}




void msAPI_MpegSP_GetPositionScale(U8 *u8XPosScale, U8 *u8YPosScale)
{
    *u8XPosScale = _u8XPosScale;
    *u8YPosScale = _u8YPosScale;
}

void maAPI_MpegSP_SetPaletteIdx( void )
{
    U16 temp, i, j;
    U8 PxlData;
    U8 idxBgk = 0xff;
    U8 idxBorder = 0xff;
    U8 idxInner = 0xff;
    U8 idxShade = 0xff;
    U16 idxCount[4];

    _u32RLBuffAddr = qeCur.u32Address+ pstDisplayParam->u16RLTopField;
    _u16RleLeftLen = pstDisplayParam->u16RLTopLen;
    temp = 0;

    idxBgk = idxInner = idxShade = 0xff;
    for(i=0;i<4;i++)
        idxCount[i] = 0;
    for( j=0; j < (pstDisplayParam->u16Height)/2; j++)
    {
        for( i=0; i < pstDisplayParam->u16Width && _u16RleLeftLen>0; temp=0)
        {
            temp = subPicGetBit(2);
            //printf("temp1= %X\n", temp);
            if( temp ) //rule 1
            {
                PxlData = subPicGetBit(2);
                //printf("PxlData= %x  Num= %d\n", PxlData, temp);
                if(PxlData == idxBgk)
                    ;
                else if(idxBgk == 0xff)
                    idxBgk = PxlData;
                else if(PxlData == idxBorder)
                    ;
                else if(idxBorder == 0xff)
                    idxBorder = PxlData;
                else
                    idxCount[PxlData] += temp;
                i+= temp;
                //printf("\n idxBgk:%02x, idxBorder:%02x, idxCount[%02x]= %x", idxBgk, idxBorder, PxlData, idxCount[PxlData]);
            }
            else
            {
                temp = subPicGetBit(2);
                //printf("temp2= %X\n", temp);
                if( temp )  //rule 2
                {
                    temp = (temp<<2) | subPicGetBit(2);
                    PxlData = subPicGetBit(2);
                    // printf("PxlData= %x  Num= %d\n", PxlData, temp);
                    if(PxlData == idxBgk)
                        ;
                    else if(idxBgk == 0xff)
                        idxBgk = PxlData;
                    else if(PxlData == idxBorder)
                        ;
                    else if(idxBorder == 0xff)
                        idxBorder = PxlData;
                    else
                        idxCount[PxlData] += temp;
                    i+= temp;
                    //printf("\n idxBgk:%02x, idxBorder:%02x, idxCount[%02x]= %x", idxBgk, idxBorder, PxlData, idxCount[PxlData]);
                }
                else
                {
                    temp = subPicGetBit(2);
                    //printf("temp3= %X\n", temp);
                    if( temp )  //rule 3
                    {
                        temp = (temp<<4) | subPicGetBit(4);
                        PxlData = subPicGetBit(2);
                        //printf("PxlData= %x  Num= %d\n", PxlData, temp);
                        if(PxlData == idxBgk)
                            ;
                        else if(idxBgk == 0xff)
                            idxBgk = PxlData;
                        else if(PxlData == idxBorder)
                            ;
                        else if(idxBorder == 0xff)
                            idxBorder = PxlData;
                        else
                            idxCount[PxlData] += temp;
                        i+= temp;
                        //printf("\n idxBgk:%02x, idxBorder:%02x, idxCount[%02x]= %x", idxBgk, idxBorder, PxlData, idxCount[PxlData]);
                    }
                    else
                    {
                        temp = subPicGetBit(8);
                        // printf("temp4= %X\n", temp);
                        PxlData = subPicGetBit(2);
                        // printf("PxlData= %x  Num= %d\n", PxlData, temp);
                        if(PxlData == idxBgk)
                            ;
                        else if(idxBgk == 0xff)
                            idxBgk = PxlData;
                        else if(PxlData == idxBorder)
                            ;
                        else if(idxBorder == 0xff)
                            idxBorder = PxlData;
                        else
                            idxCount[PxlData] += (pstDisplayParam->u16Width-i);
                        i= pstDisplayParam->u16Width;
                        //printf("\n idxBgk:%02x, idxBorder:%02x, idxCount[%02x]= %x", idxBgk, idxBorder, PxlData, idxCount[PxlData]);
                           }
                }
            }
        }
        _u8LeftBit=0;

    }

    for(i=0;i<4;i++)
    {
        if(idxCount[i] >0)
        {
            if(idxInner == 0xff)
                idxInner = i;
            else if(idxCount[i] > idxCount[idxInner])
            {
                idxShade = idxInner;
                idxInner = i;
            }
            else
                idxShade = i;
        }
    }


    if( idxBorder != 0xff)
        pPaletteTable[idxBorder].r = pPaletteTable[idxBorder].g = pPaletteTable[idxBorder].b = 0x00;
    if( idxInner != 0xff)
        pPaletteTable[idxInner].r = pPaletteTable[idxInner].g = pPaletteTable[idxInner].b = 0xee;
    if( idxShade != 0xff)
        pPaletteTable[idxShade].r = pPaletteTable[idxShade].g = pPaletteTable[idxShade].b = 0x77;
    SBTL_TRACE(printf("\n idxCount[0]:%x, idxCount[1]:%x, idxCount[2]:%x, idxCount[3]:%x",idxCount[0], idxCount[1], idxCount[2], idxCount[3]););
    SBTL_TRACE(printf("\n idxBorder:%02x, idxShade:%02x, idxInner:%02x", idxBorder, idxShade, idxInner););
    if(_u8IdxInnerCheck== 0xFF || _u8IdxInnerCheck%4 != idxInner)
    {
        _u8IdxInnerCheck = idxInner;
        SBTL_TRACE(printf("\n Reset _u8IdxInnerCheck to %02x", _u8IdxInnerCheck););
    }
    else
        _u8IdxInnerCheck +=4;

}

/////////////////////////////////////////////////////for test///////////////////////////
U8 subPicGetBit(U8 Num)
{
    U8 BitVal=0;

    //printf("\n");
    if( _u8LeftBit == 0)
    {
        if(_u16RleLeftLen ==0)
            return 0xff;
        else
            _u16RleLeftLen--;
        _u8container = *((U8*)_u32RLBuffAddr);
        _u32RLBuffAddr++;
        _u8LeftBit = 8;
        //printf("container= %X  LeftBit= %x\n", container, LeftBit);
    }

    //printf("Num= %X  LeftBit= %x\n", Num, LeftBit);
    if( Num <= _u8LeftBit )
    {
        BitVal = _u8container >> (_u8LeftBit-Num);
        //printf("\n1BitVal= %X\n", BitVal);
        BitVal &= ((1<<Num)-1);
        //printf("1BitVal= %X  mask= %X\n", BitVal, ((1<<Num)-1));
        _u8LeftBit -= Num;
    }
    else
    {
        //printf("\n2Num= %X  LeftBit= %x\n", Num, LeftBit);
        BitVal = _u8container & ((1<<_u8LeftBit)-1);
        //printf("2BitVal= %X  mask= %X\n", BitVal, ((1<<LeftBit)-1));
        BitVal <<= (Num-_u8LeftBit);
        //printf("2BitVal= %X\n", BitVal);
        if(_u16RleLeftLen ==0)
        {
            _u8LeftBit = 0;
            return 0xff;
        }
        else
            _u16RleLeftLen--;
        _u8container = *((U8*)_u32RLBuffAddr);
        //printf("container= %X\n", container);
        _u32RLBuffAddr++;
        _u8LeftBit = 8 + _u8LeftBit - Num;
        BitVal |= (_u8container >> _u8LeftBit);
    }

    //printf("\npRLBuff= 0x%X  BitVal= %x  LeftBit= %x\n", pRLBuff, BitVal, LeftBit);
    return BitVal;
}

void DUMP_SW_RLD_DATA(U16 i, U8 PxlData)
{
    if(i < RAWDATA_WIDTH)
    {
        if(PxlData==1)
        {
            SBTL_DATA(printf("%d", PxlData);)
        }
        else
        {
            SBTL_DATA(printf("%d", 0);)
        }
    }

}


void SW_RLDI2(U8 u8TransPaletteIdx)
{
    U16 temp, i, j, u16SkipBytes;
    U8 PxlData;
    U8 k;
    U16 targBit;
    U8 *targByte;
    U8 bitShit;
    U8 u8Out;
    U16 l;

    _u32RLBuffAddr = qeCur.u32Address+ pstDisplayParam->u16RLTopField;
    _u16RleLeftLen = pstDisplayParam->u16RLTopLen;
    SBTL_TRACE(printf("\npRLBuff addr = 0x%x\n", _u32RLBuffAddr););
    temp = 0;

    k=0;
    while( k<2 )
    {
        for( j=0; j < (pstDisplayParam->u16Height)/2; j++)
        {
            targByte = (U8*) (pstSpRld->u32OutputAddress + (k+j*2)*_u16FullPixelBuffer_Pitch /4);
            targBit = 0;
            u8Out = 0;
            SBTL_DATA(printf("\n"););

            for( i=0; i < pstDisplayParam->u16Width && _u16RleLeftLen >0; temp=0)
            {
                temp = subPicGetBit(2);
                // printf("temp1= %X\n", temp);
                if( temp ) //rule 1
                {
                    PxlData = subPicGetBit(2);
                    if(PxlData >3) break;
                    for( ; temp > 0; temp--, i++ )
                    {
                       DUMP_SW_RLD_DATA(i,PxlData);
                       bitShit = targBit %8;
                       u8Out |= (PxlData << (6-bitShit));
                       targBit += 2;
                       if(targBit %8 ==0)
                       {
                           *targByte = u8Out;
                           u8Out = 0;
                           targByte++;
                       }

                    }
                }
                else
                {
                    temp = (temp<<2) | subPicGetBit(2);
                    // printf("temp2= %X\n", temp);
                    if( temp )  //rule 2
                    {
                        temp = (temp<<2) | subPicGetBit(2);
                        PxlData = subPicGetBit(2);
                        if(PxlData >3) break;
                        for( ; temp > 0; temp--, i++ )
                        {
                            DUMP_SW_RLD_DATA(i,PxlData);
                            bitShit = targBit %8;
                            u8Out |= (PxlData << (6-bitShit));
                            targBit += 2;
                            if(targBit %8 ==0)
                            {
                                *targByte = u8Out;
                                u8Out = 0;
                                targByte++;
                                if(PxlData == u8TransPaletteIdx && temp > 4)
                                {
                                    u16SkipBytes = (temp%4==0)? (temp/4)-1 : temp/4;
                                    targByte += u16SkipBytes;
                                    targBit = 0;
                                    i += (u16SkipBytes*4);
                                    temp -= (u16SkipBytes*4);
                                    for(l=u16SkipBytes*4; l>0;l--)
                                    {
                                        if(i+l<RAWDATA_WIDTH)
                                        {
                                            SBTL_DATA(printf("%d", 0);)
                                        }
                                    }
                                }
                            }
                        }

                    }
                    else
                    {
                        temp = (temp<<2) | subPicGetBit(2);
                         // printf("temp3= %X\n", temp);
                        if( temp )  //rule 3
                        {
                            temp = (temp<<4) | subPicGetBit(4);
                            PxlData = subPicGetBit(2);
                            if(PxlData >3) break;

                            for( ; temp > 0; temp--, i++ )
                            {
                                DUMP_SW_RLD_DATA(i,PxlData);
                                bitShit = targBit %8;
                                u8Out |= (PxlData << (6-bitShit));
                                targBit += 2;
                                if(targBit %8 ==0)
                                {
                                    *targByte = u8Out;
                                    u8Out = 0;
                                    targByte++;
                                    if(PxlData == u8TransPaletteIdx && temp > 4)
                                    {
                                        u16SkipBytes = (temp%4==0)? (temp/4)-1 : temp/4;
                                        targByte += u16SkipBytes;
                                        targBit = 0;
                                        i += (u16SkipBytes*4);
                                        temp -= (u16SkipBytes*4);
                                        for(l=u16SkipBytes*4; l>0;l--)
                                        {
                                            if(i+l<RAWDATA_WIDTH)
                                            {
                                                SBTL_DATA(printf("%d", 0);)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            temp = (temp<<8) | subPicGetBit(8);
                           // printf("temp4= %X\n", temp);
                            PxlData = subPicGetBit(2);
                            if(PxlData >3) break;
                           // color_convert(&PxlData);
                             //printf("PxlData= %x  Num= %d\n", PxlData, temp);
                            if( temp )  //rule 4
                            {
                                for( ; temp > 0; temp--, i++ )
                                {
                                    DUMP_SW_RLD_DATA(i,PxlData);
                                    bitShit = targBit %8;
                                    u8Out |= (PxlData << (6-bitShit));
                                    targBit += 2;
                                    if(targBit %8 ==0)
                                    {
                                        *targByte = u8Out;
                                        u8Out = 0;
                                        targByte++;
                                        if(PxlData == u8TransPaletteIdx && temp > 4)
                                        {
                                            u16SkipBytes = (temp%4==0)? (temp/4)-1 : temp/4;
                                            targByte += u16SkipBytes;
                                            targBit = 0;
                                            i += (u16SkipBytes*4);
                                            temp -= (u16SkipBytes*4);
                                            for(l=u16SkipBytes*4; l>0;l--)
                                            {
                                                if(i+l<RAWDATA_WIDTH)
                                                {
                                                    SBTL_DATA(printf("%d", 0);)
                                                }
                                            }
                                        }
                                    }
                                 }
                            }
                            else
                            {
                                for( ; i < (pstDisplayParam->u16Width); i++ )
                                {
                                    DUMP_SW_RLD_DATA(i,PxlData);
                                    bitShit = targBit %8;
                                    u8Out |= (PxlData << (6-bitShit));
                                    targBit += 2;
                                    if(targBit %8 ==0)
                                    {
                                        *targByte = u8Out;
                                        u8Out = 0;
                                        targByte++;

                                        if(PxlData == u8TransPaletteIdx)
                                            i = pstDisplayParam->u16Width;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //printf("pRLBuff= 0x%X\n", pRLBuff);

            _u8LeftBit=0;
            //*targByte = u8Out;
            while(targBit %8 !=0 && u8TransPaletteIdx != 0xff)
            {
                 bitShit = targBit %8;
                 u8Out |= (u8TransPaletteIdx << (6-bitShit));
                 targBit +=2;
                 if(targBit %8 ==0)
                    *targByte = u8Out;
            }

        }
        //printf("\npRLBuff= 0x%X\n", pRLBuff);

        _u32RLBuffAddr = qeCur.u32Address+ pstDisplayParam->u16RLBottomField;
        _u16RleLeftLen = pstDisplayParam->u16RLBottomLen;

        SBTL_TRACE(printf("Bottom pRLBuff= 0x%X\n", _u32RLBuffAddr););
        k++;
        temp = 0;
    }
}


//////////////////////////////////////////////////////////////////////////////////////
///DVD Enable highlight  : API for setting highlight part
///@param bHighLight \b IN: Enable highlight
///@return None
//////////////////////////////////////////////////////////////////////////////////////
void msAPI_MpegSP_Enable_Highlight(BOOLEAN bHighLight)
{
    // Enable subtitle highlight
    _bEnableHighLight = bHighLight;
}

//////////////////////////////////////////////////////////////////////////////////////
///DVD Subtitle Draw Highlight : Draw DVD Highlight subtitle
///@param u16x \b IN: Highlight in x coordinate
///@param u16y \b IN: Highlight in y coordinate
///@param u16w \b IN: Highlight width
///@param u16h \b IN: Highlight hight
///@param u16w \b IN: Highlight width
///@param u32palette \b IN: Highlight palette index and alpha
///@param u32PTS \b IN: Highlight PTS
///@return None
//////////////////////////////////////////////////////////////////////////////////////
void msAPI_MpegSP_Draw_Highlight(U16 u16x, U16 u16y, U16 u16w, U16 u16h, U32 u32palette, U32 u32PTS)
{
    GEPoint st_point;
    Bitmap_Info BitmapInfo;
    GEBitmapFmt bmpfmt;
    U32 u32RldOutputAddr;
    U8 u8AlignmentGap;
    U8 u8TransPaletteIdx;
    GEBitBltInfo  BitbltInfo;
    GEPitBaseInfo PitBaseInfo;

    _u16Highlight_X = u16x;
    _u16Highlight_Y = u16y;
    _u16Highlight_W = u16w;
    _u16Highlight_H = u16h;
    _u32Highlight_Palette = u32palette;
    _u32Highlight_Pts = u32PTS;

    if (!_bEnableHighLight)
    {
        SBTL_TRACE(printf("highlight not enabled\n");)
        return;
    }

    if (!_b_MpegSP_Gwin_created)
    {
        return;
    }

    SBTL_TRACE(printf("\n================== DRAW HIGHLIGHT ======================="););

    SBTL_TRACE(printf("\nRegion(X:%x,Y:%x,W:%x,H:%x)",
            pstDisplayParam->u16AreaLeft,
            pstDisplayParam->u16AreaTop,
            pstDisplayParam->u16Width,
            pstDisplayParam->u16Height
            ););

    // When drawing subtitle highlight, it needs to switch subtitle gwin first
    _u8OrigGwinId = MApi_GOP_GWIN_GetCurrentWinId();
    msAPI_OSD_GetClipWindow(&_u16ClipLeft,&_u16ClipTop,&_u16ClipRight,&_u16ClipBottom);

    MApi_GOP_GWIN_SwitchGOP( E_GOP_APP );
    MApi_GOP_GWIN_Switch2Gwin(gop_parameters.u8_GWIN_id);

    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);

    SBTL_TRACE(printf("\nCurrent ID:%x, Clip L:%x, T:%x, R:%x, B:%x", _u8OrigGwinId, _u16ClipLeft, _u16ClipTop, _u16ClipRight, _u16ClipBottom);)

    ///////////// fine tune subtitle off screen pixel buffer size
    _u16FullPixelBuffer_Width= pstDisplayParam->u16AreaLeft+pstDisplayParam->u16AreaRight> _u16FullPixelBuffer_Width? pstDisplayParam->u16AreaLeft+pstDisplayParam->u16AreaRight : _u16FullPixelBuffer_Width;
    _u16FullPixelBuffer_Height= pstDisplayParam->u16AreaBottom+32>_u16FullPixelBuffer_Height ?  pstDisplayParam->u16AreaBottom+32: _u16FullPixelBuffer_Height;
    _u16FullPixelBuffer_Pitch =  ROUND_UP(_u16FullPixelBuffer_Width, 32);
    u8AlignmentGap = 0;
    SBTL_TRACE(printf("\n Finetune PixelBufer to Width:%x Pitch:%x Height:%x", _u16FullPixelBuffer_Width, _u16FullPixelBuffer_Pitch, _u16FullPixelBuffer_Height););

    // fine tune subtitle position when the height of the subtitle is bigger than the height of the video
    if(_u8YPosScale==0xFF && _u16FullPixelBuffer_Height/2 > gop_parameters.u16_GWIN_height)
    {
        _u8YPosScale = (U8)(((U32)gop_parameters.u16_GWIN_height*100)/(_u16FullPixelBuffer_Height/2));
        SBTL_TRACE(printf("\nYScale=%x, Height=%x, PixBuffer=%x", _u8YPosScale, gop_parameters.u16_GWIN_height, _u16FullPixelBuffer_Height);)
    }

    ///////////// fine tune subtitle position by u8XPosScale, u8YPosScale
    if(_u8XPosScale != 0xFF)
    {
        U16 u16tmpAreaRight = (U32)_u16FullPixelBuffer_Pitch*_u8XPosScale/100;
        pstDisplayParam->u16AreaLeft = u16tmpAreaRight > pstDisplayParam->u16Width?  u16tmpAreaRight - pstDisplayParam->u16Width: 0;
    }
    u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR + ((U32) pstDisplayParam->u16AreaTop*_u16FullPixelBuffer_Pitch + pstDisplayParam->u16AreaLeft)/4;

    if(_u8YPosScale != 0xFF)
    {
        _u16FinetunedBot= (U32)_u16FullPixelBuffer_Height*_u8YPosScale/100;

        if( pstDisplayParam->u16Height > _u16FinetunedBot )   // move ahead the rld ouput in front of the pixelbuffer
        {
            U16 u16OffsetLines = pstDisplayParam->u16Height - _u16FinetunedBot;
            u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR - ((U32) u16OffsetLines *_u16FullPixelBuffer_Pitch - pstDisplayParam->u16AreaLeft)/4;
            pstDisplayParam->u16AreaTop = 0;
            if(u32RldOutputAddr < SP_PIXELBUFFER_OFFSET_ADR)
            {
                U16 u16GapLines = (U32)(SP_PIXELBUFFER_OFFSET_ADR - u32RldOutputAddr) / (_u16FullPixelBuffer_Pitch/4);
                u32RldOutputAddr = u32RldOutputAddr + (U32) _u16FullPixelBuffer_Pitch * (u16GapLines+1) /4;
                _u16FinetunedBot += (u16GapLines+1);
            }
        }
        else    //cropped subtitle
        {
            if(_u16FinetunedBot < pstDisplayParam->u16AreaBottom)
            {
                pstDisplayParam->u16AreaTop= _u16FinetunedBot - pstDisplayParam->u16Height;
                u32RldOutputAddr = (U32) SP_PIXELBUFFER_ADR + ((U32) pstDisplayParam->u16AreaTop*_u16FullPixelBuffer_Pitch + pstDisplayParam->u16AreaLeft)/4;
            }
            else
                _u16FinetunedBot = pstDisplayParam->u16AreaBottom;
        }
    }
    else
        _u16FinetunedBot= pstDisplayParam->u16AreaBottom;

    SBTL_TRACE(printf("\n Finetune subtitle Pos: Xscale:%x, XNewpos:%x, Yscale:%x, YNewpos:%x", _u8XPosScale,pstDisplayParam->u16AreaLeft, _u8YPosScale, pstDisplayParam->u16AreaTop););

    u8TransPaletteIdx = msAPI_MpegSP_SetGopPalette();

    // It needs to clear offscreen buffer and redecode buffer if enable highlight
    msAPI_MpegSP_Clear_OffScreenBuffer(u8TransPaletteIdx);
    if(msAPI_MpegSP_Decode_RLE(u32RldOutputAddr, u8TransPaletteIdx) == FALSE)
        return;

    msAPI_OSD_SetClipWindow(0,0, gop_parameters.u16_GWIN_width-1, gop_parameters.u16_GWIN_height -1);

    if(u8TransPaletteIdx  == 0xff)
    {
        U16 u16AreaLeft8Gwin = (U32)pstDisplayParam->u16AreaLeft* gop_parameters.u16_GWIN_width/_u16FullPixelBuffer_Pitch;
        U16 u16AreaTop8Gwin = (U32)pstDisplayParam->u16AreaTop* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
        U16 u16AreaRight8Gwin = (U32)pstDisplayParam->u16AreaRight* gop_parameters.u16_GWIN_width/_u16FullPixelBuffer_Pitch;
        U16 u16AreaBot8Gwin = (U32)_u16FinetunedBot* gop_parameters.u16_GWIN_height/_u16FullPixelBuffer_Height;
        msAPI_MpegSP_Renderer_ClearDisplayBlock(gop_parameters.u8_GWIN_id, 0, 0, gop_parameters.u16_GWIN_width-1, gop_parameters.u16_GWIN_height-1);
        msAPI_OSD_SetClipWindow(u16AreaLeft8Gwin,u16AreaTop8Gwin,u16AreaRight8Gwin,u16AreaBot8Gwin);
    }

    BitmapInfo.addr = _VA2PA(SP_PIXELBUFFER_ADR);
    BitmapInfo.dstloc = MIU_SDRAM;
    BitmapInfo.width =  _u16FullPixelBuffer_Pitch;     // it has to be pitch (pixel)
    BitmapInfo.pitch =  _u16FullPixelBuffer_Pitch/4;   // it has to be pitch (bytes)
    BitmapInfo.height = _u16FullPixelBuffer_Height;//pstDisplayParam->u16Height;
    BitmapInfo.fmt = DMA_GE_FMT_I2;

    bmpfmt.bBmpColorKeyEnable = FALSE;
    bmpfmt.bScale = TRUE;

    bmpfmt.width = ROUND_DOWN(gop_parameters.u16_GWIN_width, 8);
    bmpfmt.height = gop_parameters.u16_GWIN_height;

    st_point.x =  u8AlignmentGap;
    st_point.y =  0;
    SBTL_TRACE(printf("\nBmp At Gwin(X:%x,Y:%x,W:%x,H:%x) gwin( id:%x w:%x, h:%x)",
            st_point.x, st_point.y,
            bmpfmt.width, bmpfmt.height, gop_parameters.u8_GWIN_id,gop_parameters.u16_GWIN_width,gop_parameters.u16_GWIN_height););

    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
        MApi_GFX_SetNearestMode(FALSE);
    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        MApi_GFX_SetNearestMode(TRUE);
    MApi_GFX_SetPatchMode(TRUE);

    // use Bitblt method to replace GE Draw Bitmap
    U32 u32Faddr;
    U8 fid = MApi_GOP_GWIN_GetFBfromGWIN(gop_parameters.u8_GWIN_id);
    MApi_GOP_GWIN_GetFBAddr(fid, &u32Faddr);

    /* x y */
    BitbltInfo.BitbltCoordinate.v0_x = 0;
    BitbltInfo.BitbltCoordinate.v0_y = 0;
    BitbltInfo.BitbltCoordinate.v2_x = 0;
    BitbltInfo.BitbltCoordinate.v2_y = 0;

    /* dst dimension */
    BitbltInfo.BitbltCoordinate.height = bmpfmt.height;
    BitbltInfo.BitbltCoordinate.width  = bmpfmt.width;

    /* src dimension */
    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    BitbltInfo.src_height     = _u16FullPixelBuffer_Height;
    BitbltInfo.src_width      = _u16FullPixelBuffer_Width;

    /* src base */
    BitbltInfo.src_fm   = GFX_FMT_I2;
    PitBaseInfo.sb_base = _VA2PA(SP_PIXELBUFFER_ADR);
    PitBaseInfo.sb_pit  = _u16FullPixelBuffer_Pitch/4;

    /* dst base */
    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB1555)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB1555;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB4444;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else
    {
        BitbltInfo.dst_fm   = GFX_FMT_I8;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width;
    }

    msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
    MApi_GFX_FlushQueue();
    SBTL_TRACE(printf("\nbitblt to Gwin addr:%lx", u32Faddr););

    // Set highlight palette table and bitblt to gwin
    msAPI_MpegSP_SetGopPaletteHighlight();

    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
        MApi_GFX_SetNearestMode(FALSE);
    if(GOP_GWIN_FORMAT == GFX_FMT_I8)
        MApi_GFX_SetNearestMode(TRUE);
    MApi_GFX_SetPatchMode(TRUE);

    /* x y */
    BitbltInfo.BitbltCoordinate.v0_x = _u16Highlight_X; // dst
    BitbltInfo.BitbltCoordinate.v0_y = _u16Highlight_Y;
    BitbltInfo.BitbltCoordinate.v2_x = _u16Highlight_X; // src
    BitbltInfo.BitbltCoordinate.v2_y = _u16Highlight_Y;

    /* dst dimension */
    BitbltInfo.BitbltCoordinate.height = _u16Highlight_H; //bmpfmt.height;
    BitbltInfo.BitbltCoordinate.width  = ROUND_DOWN(_u16Highlight_W, 8); //bmpfmt.width;

    /* src dimension */
    BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    BitbltInfo.src_height     = _u16Highlight_H;
    BitbltInfo.src_width      = _u16Highlight_W;

    /* src base */
    BitbltInfo.src_fm   = GFX_FMT_I2;
    PitBaseInfo.sb_base = _VA2PA(u32RldOutputAddr);
    PitBaseInfo.sb_pit  = _u16FullPixelBuffer_Pitch/4;

    /* dst base */
    if(GOP_GWIN_FORMAT == GFX_FMT_ARGB4444)
    {
        BitbltInfo.dst_fm   = GFX_FMT_ARGB4444;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width*2;
    }
    else
    {
        BitbltInfo.dst_fm   = GFX_FMT_I8;
        PitBaseInfo.db_base = u32Faddr;
        PitBaseInfo.db_pit  = gop_parameters.u16_GWIN_width;
    }

    msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
    MApi_GFX_FlushQueue();
    SBTL_TRACE(printf("\nbitblt to  Gwin addr:%lx", u32Faddr););

    //MDrv_GE_SetNearestMode(FALSE);
    MApi_GFX_SetPatchMode(FALSE);
    MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, TRUE);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    msAPI_OSD_SetClipWindow(_u16ClipLeft,_u16ClipTop,_u16ClipRight,_u16ClipBottom);
    MApi_GOP_GWIN_Switch2Gwin(_u8OrigGwinId);
}


//////////////////////////////////////////////////////////////////////////////////////
///Clear highlight subtitle : API for clear highlight
///@param None
///@return None
//////////////////////////////////////////////////////////////////////////////////////
void msAPI_MpegSP_Clear_Highlight(void)
{
    // Disable Gwin for Clear highlight
    if(_b_MpegSP_Gwin_created == TRUE)
    {
        MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, FALSE);
    }
}

//////////////////////////////////////////////////////////////////////////////////////
///Enable highlight subtitle : API for enable suubtitle Gwin highlight
///@param u32Stc \b IN: current system time
///@return None
//////////////////////////////////////////////////////////////////////////////////////
void msAPI_MpegSP_Enable_Subtitle_Gwin(U32 u32Stc)
{
    // Enable Gwin for enable subtitle  highlight only when subtitle is not show completly
    if((_b_MpegSP_Gwin_created == TRUE)  &&  (qePreDisp.u32Duration > 0)
        && ((qePreDisp.u32PTS + qePreDisp.u32Duration) > u32Stc)
        && (qePreDisp.u32PTS <= u32Stc))
    {
        if(qePreDisp.enSubType == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
        {
            MApi_GOP_GWIN_Enable(gop_parameters.u8_GWIN_id, TRUE);
        }
    }
}
#endif

