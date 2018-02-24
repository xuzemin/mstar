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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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
/// @file   msAPI_GIF_Decoder.c
/// @author MStar Semiconductor Inc.
/// @brief  API of GIF decoder
///////////////////////////////////////////////////////////////////////////////
#define _MSAPI_GIF_DECODER_C_

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
//#include "mm_common.h"           // Every source code should include this in the first line
#include <string.h>
#include <MsOS.h>

// NOTE: DO NOT include "mapp_stillimage_sharememcfg.h" in decoder/encoder modules
// and make sure it be included in only one file, "msapi_stillimage.h"
#include "msapi_stillimage.h"

#if ENABLE_HK_GIF

#include "msapi_stillimage_bm.h"
#include "msapi_gif_decoder.h"
#include "msapi_stillimage_dlmalloc.h"


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define GIF_DBG(x)             //x
#define GIF_INFO(x)            //x
#define GIF_INFO_MUST(x)       //x
#define GIF_ERR(x)             //x

#define MAXCOLORTABLESIZE  256
#define MAX_LZW_BITS     12
#define INTERLACE          0x40
#define LOCALCOLORTABLE      0x80
#define CHECK_BIT_SET(byte, bit)  (((byte) & (bit)) == (bit))
#define MERGE_BYTE_LE(a,b)         (((b)<<8)|(a))
#define RGB8888_TO_1555(a,r, g, b) ((U16)((a==1)?0x8000:0x000)|((U16)((r)>>3)<<10) | ((U16)((g)>>3)<<5) | ((U16)(b)>>3))
#define ARGB8888PACK(a,r, g, b) ((U32)((a==1)?0xFF000000:0x00000000)|((U32)(r)<<16) | ((U32)(g)<<8) | ((U32)(b)))

// Definitions relating to underlying gif decoder
// It is hard coded in gif decoder, DO NOT change this value.
#define GIF_ALIGNMENT       (16)

// gif decoder will collect up to this number of rows before we can do our job.
// It is hard coded in gif decoder, DO NOT change this value.
#define GIF_OUTPUT_ROW      (8)

// Only ask gif decoder to output ARGB8888 format. It's up to us to packed to any format we real want.
#define GIF_PIXEL_PER_BYTE  (4)

// The size of data needed for gif decoder to check if data is GIF packed.
// It is hard coded in gif decoder, DO NOT change this value.
#define GIF_HEADER_SIZE     3

//------------------------------------------------------------------------------
// Definitions relating to this shell
#define GIF_OUTPUT_ALIGNMENT    (8)

//define max frames for animation
#define GIF_MAX_FRAMES  (64)

#define _U32_MAX (0xffffffff)
//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
typedef enum
{
    E_GIF_ARGB8888  = 0,
    E_GIF_ARGB1555,
} E_GIF_OUTPUT_FORMAT;

typedef struct
{
    U8 u8Blue;      // Blue component
    U8 u8Green;     // Green component
    U8 u8Red;       // Red component
    U8 u8Alpha;     // Alpha component
} stPixel, stPixel_ARGB8888;

typedef struct _GIFPIXEL_INFO GIFPIXEL_INFO;
struct _GIFPIXEL_INFO
{
    S32 n_channels;
    S32 width, height;
    S32 rowstride;
    U8* pixels;
    BOOLEAN has_alpha;
};
typedef U8 GIF_RGB[3][MAXCOLORTABLESIZE];
typedef enum
{
    RETAIN,
    DISPOSE,
    REVERT
} GIF_FRAME_ACTION;
struct _GIF_FRAME
{
    GIFPIXEL_INFO* pixbuf;
    S32 x_offset;
    S32 y_offset;
    S32 delay_time;
    S32 elapsed;
    GIF_FRAME_ACTION action;
    BOOLEAN bg_transparent;
};
typedef struct _GIF_FRAME GIF_FRAME;
struct _GIF_ANIM
{
    U8 bg_red;
    U8 bg_green;
    U8 bg_blue;
    S32 n_frames;
    S32 total_time;
    GIF_FRAME *frames[GIF_MAX_FRAMES];
    S32 width, height;
    S32 loop;

};
typedef struct _GIF_ANIM GIF_ANIM;
struct _GIF89
{
    S32 transparent;
    S32 delay_time;
    S32 input_flag;
    S32 disposal;
};
typedef struct _GIF89 GIF89;

struct _STGIF
{
    U8 u8Header[GIF_HEADER_SIZE];
    U32 u32DataProcessed;

    U32 u32Width;
    U32 u32Height;
    U32 u32Pitch;
    U32 u32BytePerOutputRow;

    E_GIF_OUTPUT_FORMAT eOutputFormat;
    U8 u8OutputPixelSize;
    U32 u32OutputWidth;
    U32 u32OutputHeight;
    U32 u32OutputPitch;
    U8 u8FreeSlotNum;
    U8 u8DecodeSlotIndex;
    U32 u32DisplayFrameIndex;
    U32 u32FrameBuffSize;
    U32 u32FrameInfoArrayBuffAddr;
    U32 u32FrameInfoArrayBuffSize;

    U8 u8Factor;
    U8 *pu8OutputBuffer;

    U32 u32TotalRowProcessed;
    U32 u32TotalRowOutputted;
    U32 u32LoopNumber;
    U32 u32TotalFramesInOneLoop;

    BOOL bStop;

    GIF_ANIM* animation;
    GIF_FRAME* frame;
    GIF89 gif89;

    S32 state;

    GIF_RGB global_color_table;
    S32 global_colortable_size;
    U32 global_bit_pixel;
    U32 global_color_resolution;
    U32 background_index;
    BOOLEAN has_global_colortable;
    BOOLEAN stop_after_first_frame;
    BOOLEAN has_local_colortable;
    BOOLEAN ZeroDataBlock;
    GIF_RGB frame_color_map;
    S32 frame_colormap_size;
    U32 frame_bit_pixel;
    U32 aspect_ratio;

    S32 frame_len;
    S32 frame_height;
    S32 frame_interlace;
    S32 x_offset;
    S32 y_offset;

    U8* buf;
    U8 extension_label;
    U8 extension_flag;
    U8 block_count;
    U8 block_buf[280];
    S32 block_ptr;
    S32 old_state;
    U32 ptr;
    U32 size;
    U32 amount_needed;
    BOOLEAN in_loop_extension;

    S32 code_curbit;
    S32 code_lastbit;
    S32 code_done;
    S32 code_last_byte;
    S32 lzw_code_pending;

    U8 lzw_set_code_size;
    S32 lzw_fresh;
    S32 lzw_code_size;
    S32 lzw_max_code;
    S32 lzw_max_code_size;
    S32 lzw_firstcode;
    S32 lzw_oldcode;
    S32 lzw_clear_code;
    S32 lzw_end_code;
    S32* lzw_sp;
    S32 lzw_table[2][4096];   //[(1 << MAX_LZW_BITS)];
    S32 lzw_stack[8193];       //[(1 << (MAX_LZW_BITS))* 2+1];
    S32 draw_xpos;
    S32 draw_ypos;
    S32 draw_pass;
};
typedef struct _STGIF stGIF;

enum
{
    GIF_GET_NEXT_STEP,
    GIF_LZW_FILL_BUFFER,
    GIF_LZW_CLEAR_CODE,
    GIF_GET_LZW,
    GIF_DECODE_ROWS,
    GIF_WAIT_FREE_SLOT,
    GIF_DECODE_ONE_FRAME_DONE,
    GIF_DONE
};


//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
static stGIF *pstGIFInfo = NULL;

//------------------------------------------------------------------------------
// Local Function Prototypes
//------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_GifDecoder_ReadHeader(void);
EN_STILLIMAGE_RET msAPI_GifDecoder_Decode(void);
EN_STILLIMAGE_RET msAPI_GifDecoder_Stop(void);

static void _msAPI_GifDecoder_Reset(void);
static void _msAPI_GifDecoder_FreeResource(void);
static U32 _msAPI_GifDecoder_DataRequest(U8* pBuffer, U32 u32Size);
static BOOLEAN _msAPI_GifDecoder_ResetForNextLoopPlay(void);

//------------------------------------------------------------------------------
// Global Function Implementation
//------------------------------------------------------------------------------
static BOOLEAN _msAPI_GifDecoder_HasFreeSlotBuf(void)
{
    if(g_stStillImage.u32DecodedFrameIndex == _U32_MAX ||
        g_stStillImage.u32DisplayedFrameIndex == _U32_MAX ||
        (g_stStillImage.u32DecodedFrameIndex - g_stStillImage.u32DisplayedFrameIndex) < pstGIFInfo->u8FreeSlotNum)
    {

        return TRUE;
    }
    else
    {
        GIF_INFO(printf("[GIF]:no free slot!\n"));
        return FALSE;
    }
}

static U8* _msAPI_GifDecoder_GetNextFreeBuf(U32 u32Size)
{
    UNUSED(u32Size);
    U8* ret = NULL;

    if(_msAPI_GifDecoder_HasFreeSlotBuf())
    {
        pstGIFInfo->u8DecodeSlotIndex = pstGIFInfo->u8DecodeSlotIndex%pstGIFInfo->u8FreeSlotNum;
        GIF_INFO(printf("[GIF]:Get next free slot:0x%x\n",pstGIFInfo->u8DecodeSlotIndex));
        ret = (pstGIFInfo->pu8OutputBuffer + pstGIFInfo->u8DecodeSlotIndex*pstGIFInfo->u32FrameBuffSize);
        pstGIFInfo->u8DecodeSlotIndex++;
    }
    return ret;
}

static void _msAPI_GifDecoder_UpdateDecodedFrameInfo(void)
{
    U32 u32MaxIndex;
    U32* pDelayTime;
    g_stStillImage.u32DecodedFrameIndex = pstGIFInfo->animation->n_frames - 1 + pstGIFInfo->u32TotalFramesInOneLoop*pstGIFInfo->u32LoopNumber;
    //update delay time in minisecond for HK to get
    u32MaxIndex = pstGIFInfo->u32FrameInfoArrayBuffSize/4;
    pDelayTime = (U32*)MsOS_PA2KSEG1(pstGIFInfo->u32FrameInfoArrayBuffAddr + (g_stStillImage.u32DecodedFrameIndex%u32MaxIndex)*4);
    *pDelayTime = (U32)(pstGIFInfo->gif89.delay_time*10);
}

static S32 _msAPI_GifDecoder_GetDataBlock(
        U8* buf,
        S32* empty_block)
{
    if (pstGIFInfo->block_count == 0)
    {
        if (_msAPI_GifDecoder_DataRequest(&pstGIFInfo->block_count, 1) == 0)
        {
            return  - 1;
        }
    }
    if (pstGIFInfo->block_count == 0)
    {
        if (empty_block)
        {
            *empty_block = TRUE;
            return 0;
        }
    }

    if (_msAPI_GifDecoder_DataRequest(buf, pstGIFInfo->block_count) == 0)
    {
        return  - 1;
    }
    return 0;
}

static GIFPIXEL_INFO* _msAPI_GifDecoder_GifPixbufNew(
        BOOLEAN has_alpha,
        S32 width,
        S32 height)
{

    U8* buf;
    S32 channels;
    S32 rowstride;
    GIFPIXEL_INFO* pbuf;
    if (width <= 0 || height <= 0)
    {
        GIF_ERR(printf("size problem\n"));
        return NULL;
    }
    channels = has_alpha ? 4 : 3;
    if(pstGIFInfo->eOutputFormat == E_GIF_ARGB8888)
        rowstride = width * 4; //save as 4 byte
    else
        rowstride = width * 2; //save as 2 byte
    if (rowstride + 3 < 0)
    {

        GIF_ERR(printf("overflow\n"));
        return NULL;
    }
    rowstride = (rowstride + 7) &~7;

    buf = _msAPI_GifDecoder_GetNextFreeBuf(rowstride* height);
    if (buf == NULL)
    {
        pstGIFInfo->state = GIF_WAIT_FREE_SLOT;
        GIF_ERR(printf(" alloc free slot buffer fail,need wait\n"));
        return NULL;
    }
    pbuf = msAPI_StillImage_Dlmalloc_Malloc(sizeof(GIFPIXEL_INFO));
    if(pbuf!=NULL)
    {
        pbuf->pixels = buf;
        pbuf->has_alpha = has_alpha;
        pbuf->rowstride = rowstride;
        pbuf->width = width;
        pbuf->height = height;
        pbuf->n_channels = channels;
    }
    return pbuf;
}

///////////////////////////////////////////////////////////////
//static S32 ZeroDataBlock = FALSE;
#if 0
static S32 _msAPI_GifDecoder_GetDataBlock2(U8* buf)
{
    if (!_msAPI_GifDecoder_DataRequest(&pstGIFInfo->block_count, 1))
    {
        return  - 1;
    }
    pstGIFInfo->ZeroDataBlock = pstGIFInfo->block_count == 0;
    if ((pstGIFInfo->block_count != 0) && (!_msAPI_GifDecoder_DataRequest(buf,
        pstGIFInfo->block_count)))
    {
        return  - 1;
    }
    return pstGIFInfo->block_count;
}
#endif

static S32 _msAPI_GifDecoder_LzwFillBuffer(void)
{

    S32 retval;
    if (pstGIFInfo->code_done)
    {
        if (pstGIFInfo->code_curbit >= pstGIFInfo->code_lastbit)
        {
            GIF_ERR(printf(
                "GIF file was missing some data (perhaps it was truncated somehow?)"));
            return  - 2;
        }
        return  - 2;
    }
    pstGIFInfo->block_buf[0] = pstGIFInfo->block_buf[pstGIFInfo->code_last_byte - 2];
    pstGIFInfo->block_buf[1] = pstGIFInfo->block_buf[pstGIFInfo->code_last_byte - 1];
    retval = _msAPI_GifDecoder_GetDataBlock(&pstGIFInfo->block_buf[2], NULL);
    if (retval ==  - 1)
    {
        return  - 1;
    }
    if (pstGIFInfo->block_count == 0)
    {
        pstGIFInfo->code_done = TRUE;
    }
    pstGIFInfo->code_last_byte = 2+pstGIFInfo->block_count;
    pstGIFInfo->code_curbit = (pstGIFInfo->code_curbit - pstGIFInfo->code_lastbit) + 16;
    pstGIFInfo->code_lastbit = (2+pstGIFInfo->block_count)* 8;
    pstGIFInfo->state = pstGIFInfo->old_state;
    return 0;
}

static S32 _msAPI_GifDecoder_GetCode(S32 code_size)
{
    S32 i, j, ret;

    if ((pstGIFInfo->code_curbit + code_size) >= pstGIFInfo->code_lastbit)
    {
        pstGIFInfo->block_count = 0;
        pstGIFInfo->old_state = pstGIFInfo->state;
        pstGIFInfo->state = GIF_LZW_FILL_BUFFER;

        return  - 3;
    }
    ret = 0;
    for (i = pstGIFInfo->code_curbit, j = 0; j < code_size; ++i, ++j)
    {
        ret |= ((pstGIFInfo->block_buf[i / 8] &(1 << (i % 8))) != 0) << j;
    }
    pstGIFInfo->code_curbit += code_size;
    return ret;
}

static S32 _msAPI_GifDecoder_LzwClearCode(void)
{
    S32 s32Code;

    s32Code = _msAPI_GifDecoder_GetCode(pstGIFInfo->lzw_code_size);
    if (s32Code ==  - 3)
    {
        return  - 0;
    }
    pstGIFInfo->lzw_firstcode = pstGIFInfo->lzw_oldcode = s32Code;
    pstGIFInfo->lzw_code_pending = s32Code;
    pstGIFInfo->state = GIF_GET_LZW;
    return 0;
}

static S32 _msAPI_GifDecoder_LzwReadbyte(void)
{
    S32 s32Code, incode;
    S32 retval;
    S32 my_retval;
    S32 i;

    if (pstGIFInfo->lzw_code_pending !=  - 1)
    {
        retval = pstGIFInfo->lzw_code_pending;
        pstGIFInfo->lzw_code_pending =  - 1;
        return retval;
    }
    if (pstGIFInfo->lzw_fresh)
    {
        pstGIFInfo->lzw_fresh = FALSE;
        do
        {
            retval = _msAPI_GifDecoder_GetCode(pstGIFInfo->lzw_code_size);
            if (retval < 0)
            {
                return retval;
            }
            pstGIFInfo->lzw_firstcode = pstGIFInfo->lzw_oldcode = retval;
        }

        while (pstGIFInfo->lzw_firstcode == pstGIFInfo->lzw_clear_code);
        return pstGIFInfo->lzw_firstcode;
    }
    if (pstGIFInfo->lzw_sp > pstGIFInfo->lzw_stack)
    {
        my_retval = * --(pstGIFInfo->lzw_sp);
        return my_retval;
    }
    //---------------------------------------------------------------------------
    while ((s32Code = _msAPI_GifDecoder_GetCode(pstGIFInfo->lzw_code_size)) >= 0)
    {
        if (s32Code == pstGIFInfo->lzw_clear_code)
        {
            memset(pstGIFInfo->lzw_table[0], 0, (1<<MAX_LZW_BITS)*4);
            memset(pstGIFInfo->lzw_table[1], 0, (1<<MAX_LZW_BITS)*4);
            //assert(pstGIFInfo->lzw_clear_code <= (1<<MAX_LZW_BITS));
            if(pstGIFInfo->lzw_clear_code > (1<<MAX_LZW_BITS))
            {
                GIF_ERR(printf("[GIF]:pstGIFInfo->lzw_clear_code wrong:%x",pstGIFInfo->lzw_clear_code));
                return -2;
            }
            //MApi_DateTime_DelayMs(10);
            for (i = 0; i < pstGIFInfo->lzw_clear_code; ++i)
            {
                pstGIFInfo->lzw_table[0][i] = 0;
            }
            for (i = 0; i < pstGIFInfo->lzw_clear_code; ++i)
            {
                pstGIFInfo->lzw_table[1][i] = i;
            }
            pstGIFInfo->lzw_code_size = pstGIFInfo->lzw_set_code_size + 1;
            pstGIFInfo->lzw_max_code_size = 2 * pstGIFInfo->lzw_clear_code;
            pstGIFInfo->lzw_max_code = pstGIFInfo->lzw_clear_code + 2;
            pstGIFInfo->lzw_sp = pstGIFInfo->lzw_stack;
            pstGIFInfo->state = GIF_LZW_CLEAR_CODE;
            pstGIFInfo->lzw_code_pending =  - 1;
            return  - 3;
        }
        else if (s32Code == pstGIFInfo->lzw_end_code)
        {
            //S32 count;
            //U8 buf[260];

            GIF_ERR(printf("GIF image loader cannot understand this image."));
            return  - 2;
#if 0
            if (pstGIFInfo->ZeroDataBlock)
            {
                return  - 2;
            }
            while ((count = _msAPI_GifDecoder_GetDataBlock2(buf)) > 0);

            if (count != 0)
            {
                GIF_ERR(printf("GIF: missing EOD"));
                return  - 2;
            }
#endif
        }
        incode = s32Code;
        if (s32Code >= pstGIFInfo->lzw_max_code)
        {
            *(pstGIFInfo->lzw_sp)++ = pstGIFInfo->lzw_firstcode;
            s32Code = pstGIFInfo->lzw_oldcode;
        }
        while (s32Code >= pstGIFInfo->lzw_clear_code)
        {
            if (s32Code >= (1 << MAX_LZW_BITS))
            {
                GIF_ERR(printf("Bad s32Code encountered"));
                return  - 2;
            }
            *(pstGIFInfo->lzw_sp)++ = pstGIFInfo->lzw_table[1][s32Code];
            if (s32Code == pstGIFInfo->lzw_table[0][s32Code])
            {
                GIF_ERR(printf("Circular table  in GIF file"));
                return  - 2;
            }
            s32Code = pstGIFInfo->lzw_table[0][s32Code];
        }
        *(pstGIFInfo->lzw_sp)++ = pstGIFInfo->lzw_firstcode = pstGIFInfo->lzw_table[1][s32Code];
        if ((s32Code = pstGIFInfo->lzw_max_code) < (1 << MAX_LZW_BITS))
        {
            pstGIFInfo->lzw_table[0][s32Code] = pstGIFInfo->lzw_oldcode;
            pstGIFInfo->lzw_table[1][s32Code] = pstGIFInfo->lzw_firstcode;
            ++pstGIFInfo->lzw_max_code;
            if ((pstGIFInfo->lzw_max_code >= pstGIFInfo->lzw_max_code_size) &&
                (pstGIFInfo->lzw_max_code_size < (1 << MAX_LZW_BITS)))
            {
                pstGIFInfo->lzw_max_code_size *= 2;
                ++pstGIFInfo->lzw_code_size;
            }
        }
        pstGIFInfo->lzw_oldcode = incode;
        if (pstGIFInfo->lzw_sp > pstGIFInfo->lzw_stack)
        {
            my_retval = * --(pstGIFInfo->lzw_sp);
            return my_retval;
        }
    }
    if ((pstGIFInfo->lzw_sp - pstGIFInfo->lzw_stack)>( (1 << (MAX_LZW_BITS))* 2+1))
    {
         GIF_ERR(printf("lzw_sp is overflow:%x,",(pstGIFInfo->lzw_sp - pstGIFInfo->lzw_stack)));
         return  - 2;
    }
    return s32Code;
}

static  S32  _msAPI_GifDecoder_DecodeRows(void)
{
    U8* dest;
    S32 lower_bound;
    S32 first_pass;
    S32 v = 0;
    U16* temp1555;
    S32 xpos, ypos;
    U8(*color_table)[MAXCOLORTABLESIZE];
    U8 u8Loop = 0;

    lower_bound = pstGIFInfo->draw_ypos;
    first_pass = pstGIFInfo->draw_pass;


    if (pstGIFInfo->has_local_colortable)
    {
        color_table = pstGIFInfo->frame_color_map;
    }
    else
    {
        color_table = pstGIFInfo->global_color_table;
    }

    if(pstGIFInfo->u8Factor == 1)
    {
        dest = pstGIFInfo->frame->pixbuf->pixels + (pstGIFInfo->draw_ypos + pstGIFInfo->y_offset)* pstGIFInfo->u32BytePerOutputRow;

        while (u8Loop < 8)
        {

            v = _msAPI_GifDecoder_LzwReadbyte();
            if ((v < 0) || (v >= (S32) MAXCOLORTABLESIZE) )
            {
                goto finish;
            }
            xpos = pstGIFInfo->draw_xpos + pstGIFInfo->x_offset;
            ypos = pstGIFInfo->draw_ypos + pstGIFInfo->y_offset;
            if(pstGIFInfo->eOutputFormat == E_GIF_ARGB1555)
            {
                temp1555 = (U16*)(U32)(dest + xpos * 2);
                if (v != pstGIFInfo->gif89.transparent)
                {
                    *temp1555 = RGB8888_TO_1555(1, (color_table[0][(U8)v]), (color_table[1][
                        (U8)v]), (color_table[2][(U8)v]));
                }
            }
            else
            {
                U32 *tempARGB = (U32*)(U32)(dest + xpos * 4);
                if (v != pstGIFInfo->gif89.transparent)
                {
                    *tempARGB = ARGB8888PACK(1, (color_table[0][(U8)v]), (color_table[1][
                        (U8)v]), (color_table[2][(U8)v]));
                }
            }

            pstGIFInfo->draw_xpos++;

            if (pstGIFInfo->draw_xpos == pstGIFInfo->frame_len)
            {
                pstGIFInfo->draw_xpos = 0;
                u8Loop++;
                if (pstGIFInfo->frame_interlace)
                {
                    switch (pstGIFInfo->draw_pass)
                    {
                        case 0:
                        case 1:
                            pstGIFInfo->draw_ypos += 8;
                            break;
                        case 2:
                            pstGIFInfo->draw_ypos += 4;
                            break;
                        case 3:
                            pstGIFInfo->draw_ypos += 2;
                            break;
                    }
                    if (pstGIFInfo->draw_ypos >= pstGIFInfo->frame_height)
                    {
                        pstGIFInfo->draw_pass++;
                        switch (pstGIFInfo->draw_pass)
                        {
                            case 1:
                                pstGIFInfo->draw_ypos = 4;
                                break;
                            case 2:
                                pstGIFInfo->draw_ypos = 2;
                                break;
                            case 3:
                                pstGIFInfo->draw_ypos = 1;
                                break;
                            default:
                                goto done;
                        }
                    }
                }
                else
                {
                    pstGIFInfo->draw_ypos++;
                }

                dest = pstGIFInfo->frame->pixbuf->pixels + (pstGIFInfo->draw_ypos + pstGIFInfo->y_offset)* pstGIFInfo->u32BytePerOutputRow;

                if (pstGIFInfo->draw_pass != first_pass)
                {
                    if (pstGIFInfo->draw_ypos > lower_bound)
                    {
                        lower_bound = 0;
                    }
                }
            }
            if (pstGIFInfo->draw_ypos >= pstGIFInfo->frame_height)
            {
                goto done;

            }
        }
    }
    else
    {
        dest = pstGIFInfo->frame->pixbuf->pixels +
            (pstGIFInfo->draw_ypos + pstGIFInfo->y_offset) /pstGIFInfo->u8Factor * pstGIFInfo->u32BytePerOutputRow;

        while (u8Loop < 8)
        {

            v = _msAPI_GifDecoder_LzwReadbyte();
            if ((v < 0) || (v >= (S32) MAXCOLORTABLESIZE) )
            {
                goto finish;
            }
            xpos = pstGIFInfo->draw_xpos + pstGIFInfo->x_offset;
            ypos = pstGIFInfo->draw_ypos + pstGIFInfo->y_offset;
            if(ypos%pstGIFInfo->u8Factor == 0 && xpos%pstGIFInfo->u8Factor == 0)
            {
                if(pstGIFInfo->eOutputFormat == E_GIF_ARGB1555)
                {
                    temp1555 = (U16*)(U32)(dest + xpos/pstGIFInfo->u8Factor* 2);
                    if (v != pstGIFInfo->gif89.transparent)
                    {
                        *temp1555 = RGB8888_TO_1555(1, (color_table[0][(U8)v]), (color_table[1][
                            (U8)v]), (color_table[2][(U8)v]));
                    }
                }
                else
                {
                    U32 *tempARGB = (U32*)(U32)(dest + xpos/pstGIFInfo->u8Factor * 4);
                    if (v != pstGIFInfo->gif89.transparent)
                    {
                        *tempARGB = ARGB8888PACK(1, (color_table[0][(U8)v]), (color_table[1][
                            (U8)v]), (color_table[2][(U8)v]));
                    }
                }
            }

            pstGIFInfo->draw_xpos++;

            if (pstGIFInfo->draw_xpos == pstGIFInfo->frame_len)
            {
                pstGIFInfo->draw_xpos = 0;
                u8Loop++;
                if (pstGIFInfo->frame_interlace)
                {
                    switch (pstGIFInfo->draw_pass)
                    {
                        case 0:
                        case 1:
                            pstGIFInfo->draw_ypos += 8;
                            break;
                        case 2:
                            pstGIFInfo->draw_ypos += 4;
                            break;
                        case 3:
                            pstGIFInfo->draw_ypos += 2;
                            break;
                    }
                    if (pstGIFInfo->draw_ypos >= pstGIFInfo->frame_height)
                    {
                        pstGIFInfo->draw_pass++;
                        switch (pstGIFInfo->draw_pass)
                        {
                            case 1:
                                pstGIFInfo->draw_ypos = 4;
                                break;
                            case 2:
                                pstGIFInfo->draw_ypos = 2;
                                break;
                            case 3:
                                pstGIFInfo->draw_ypos = 1;
                                break;
                            default:
                                goto done;
                        }
                    }
                }
                else
                {
                    pstGIFInfo->draw_ypos++;
                }
                dest = pstGIFInfo->frame->pixbuf->pixels +
                    (pstGIFInfo->draw_ypos + pstGIFInfo->y_offset)/pstGIFInfo->u8Factor* pstGIFInfo->u32BytePerOutputRow;

                if (pstGIFInfo->draw_pass != first_pass)
                {
                    if (pstGIFInfo->draw_ypos > lower_bound)
                    {
                        lower_bound = 0;
                    }
                }
            }
            if (pstGIFInfo->draw_ypos >= pstGIFInfo->frame_height)
            {
                goto done;

            }
        }
    }

    pstGIFInfo->state = GIF_DECODE_ROWS;
    return 0;

done:
    pstGIFInfo->state = GIF_DECODE_ONE_FRAME_DONE;
    v = 0;
finish:
    if ( pstGIFInfo->state == GIF_DECODE_ONE_FRAME_DONE)
    {
         pstGIFInfo->frame = NULL;
         pstGIFInfo->has_local_colortable = FALSE;
    }
    return v;
}
static void _msAPI_GifDecoder_FillPixbuf(GIFPIXEL_INFO* pixbuf, U32 pixel)
{
    U8* pixels;
    U32 r, g, b;
    U32 w, h, u32PackColor = 0;
    U16* p = NULL;
    U32* p2 = NULL;
    U16 u16PackColor = 0;

    GIF_INFO(printf("[GIF]:fill pixel buffer color:0x%x , addr:0x%x\n",pixel,(U32)pixbuf->pixels));

    if (pixbuf->width == 0 || pixbuf->height == 0)
    {
        return ;
    }
    pixels = pixbuf->pixels;
    r = (pixel &0xff000000) >> 24;
    g = (pixel &0x00ff0000) >> 16;
    b = (pixel &0x0000ff00) >> 8;
    // a = (pixel &0x000000ff);
    h = pixbuf->height  / pstGIFInfo->u8Factor;
    if(pstGIFInfo->eOutputFormat == E_GIF_ARGB8888)
    {
        switch (pixbuf->n_channels)
            {
                case 3:
                    u32PackColor = ARGB8888PACK(1, r, g, b);
                    break;
                case 4:
                    u32PackColor = ARGB8888PACK(0, r, g, b);
                    break;
                default:
                    break;
            }
    }
    else
    {
        switch (pixbuf->n_channels)
            {
                case 3:
                    u16PackColor = RGB8888_TO_1555(1, r, g, b);
                    break;
                case 4:
                    u16PackColor = RGB8888_TO_1555(0, r, g, b);
                    break;
                default:
                    break;
            }
    }

    if(pstGIFInfo->eOutputFormat == E_GIF_ARGB8888)
    {
        while (h--)
        {
            p2 = (U32*)(U32)pixels;
            w = pstGIFInfo->u32BytePerOutputRow;
            while (w--)
            {
                (*p2++) = u32PackColor;
            }
            pixels += ( pstGIFInfo->u32BytePerOutputRow);
        }
    }
    else
    {
        while (h--)
        {
            p = (U16*)(U32)pixels;
            w = pstGIFInfo->u32BytePerOutputRow;
            while (w--)
            {
                (*p++) = u16PackColor;
            }
            pixels += ( pstGIFInfo->u32BytePerOutputRow);
        }
    }

}

static S32 _msAPI_GifDecoder_GetLzw(void)
{
    U8* dest, * dest_prev_prev_frame, * dest_context_frame;
    S32 rowstride;
    S32 xpos, ypos, xpos_prev_prev_frame, ypos_prev_prev_frame,
        xpos_context_frame, ypos_context_frame;
    U16* temp1555;
    U16* source1555;

    if (pstGIFInfo->frame == NULL)
    {
        pstGIFInfo->frame = msAPI_StillImage_Dlmalloc_Malloc(sizeof(GIF_FRAME));
        if (pstGIFInfo->frame == NULL)
        {
            GIF_ERR(printf("no memory for frame\n"));
            return  - 1;
        }

        if (pstGIFInfo->animation == NULL)
        {
            GIF_ERR(printf("no memory for animation\n"));
            return  - 1;
        }

        if (pstGIFInfo->frame_len == 0 || pstGIFInfo->frame_height == 0)
        {

            pstGIFInfo->x_offset = 0;
            pstGIFInfo->y_offset = 0;
            pstGIFInfo->frame_len = 1;
            pstGIFInfo->frame_height = 1;
            pstGIFInfo->frame->pixbuf = _msAPI_GifDecoder_GifPixbufNew(TRUE,  1, 1);
            if (pstGIFInfo->frame->pixbuf)
            {
                U8* pixels;
                pixels = (pstGIFInfo->frame->pixbuf->pixels);
                pixels[0] = 0;
                pixels[1] = 0;
                pixels[2] = 0;
                pixels[3] = 0;
            }
        }
        else
        {
            pstGIFInfo->frame->pixbuf = _msAPI_GifDecoder_GifPixbufNew(pstGIFInfo->gif89.transparent !=  - 1,  pstGIFInfo->u32Width,  //buffer size
            pstGIFInfo->u32Height);
            if (pstGIFInfo->frame->pixbuf == NULL)
            {
                return  - 1;
            }
            pstGIFInfo->frame->pixbuf->width = pstGIFInfo->frame_len; // resize
            pstGIFInfo->frame->pixbuf->height = pstGIFInfo->frame_height;
        }

        if (!pstGIFInfo->frame->pixbuf)
        {
            msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->frame);

            if(pstGIFInfo->state == GIF_WAIT_FREE_SLOT)
            {
                GIF_ERR(printf("state-->wait free slot\n"));
                return  0;
            }
            else
            {
                GIF_ERR(printf("Not enough memory to load GIF file\n"));
                return  - 2;
            }
        }
        pstGIFInfo->frame->x_offset = pstGIFInfo->x_offset;
        pstGIFInfo->frame->y_offset = pstGIFInfo->y_offset;
        pstGIFInfo->frame->delay_time = pstGIFInfo->gif89.delay_time;
        if (pstGIFInfo->frame->delay_time < 20)
        {
            pstGIFInfo->frame->delay_time = 20;
        }

        pstGIFInfo->frame->elapsed = pstGIFInfo->animation->total_time;
        pstGIFInfo->animation->total_time += pstGIFInfo->frame->delay_time;
        switch (pstGIFInfo->gif89.disposal)
        {
            case 0:
            case 1:
                pstGIFInfo->frame->action = RETAIN;
                break;
            case 2:
                pstGIFInfo->frame->action = DISPOSE;
                break;
            case 3:
                pstGIFInfo->frame->action = REVERT;
                break;
            default:
                pstGIFInfo->frame->action = RETAIN;
                break;
        }
        if (pstGIFInfo->animation)
        {
            S32 w, h;
            pstGIFInfo->frame->bg_transparent = ((U32)(pstGIFInfo->gif89.transparent) ==
                pstGIFInfo->background_index);
            pstGIFInfo->animation->n_frames++;

            if(pstGIFInfo->animation->n_frames < GIF_MAX_FRAMES)
            {
                pstGIFInfo->animation->frames[pstGIFInfo->animation->n_frames - 1] = pstGIFInfo->frame;
            }
            else
            {
                GIF_ERR(printf("Frame number is bigger than max %d, not support now\n", GIF_MAX_FRAMES));
                return -2;
            }
            //printf("prev_frame->x_offset:%d\n", pstGIFInfo->frame->x_offset);
          //  printf("prev_frame->y_offset:%d\n", pstGIFInfo->frame->y_offset);
            w = (pstGIFInfo->frame->pixbuf->width);
            h = (pstGIFInfo->frame->pixbuf->height);
            if (w > pstGIFInfo->animation->width)
            {
                pstGIFInfo->animation->width = w;
            }
            if (h > pstGIFInfo->animation->height)
            {
                pstGIFInfo->animation->height = h;
            }
            //conposited
            GIF_FRAME* prev_frame;
            GIF_FRAME* prev_prev_frame;

            if (pstGIFInfo->animation->n_frames >= 2)
            {
                prev_frame = (GIF_FRAME*)pstGIFInfo->animation->frames[
                    (pstGIFInfo->animation->n_frames) - 2];
                GIF_DBG(printf("n_frame=%d, preframe action:%x\n", pstGIFInfo->animation->n_frames, prev_frame->action));
                //memcpy(pstGIFInfo->frame->pixbuf->pixels,
                    //prev_frame->pixbuf->pixels, pstGIFInfo->u32FrameBuffSize);
                if (prev_frame->action == RETAIN)
                {
                     memcpy(pstGIFInfo->frame->pixbuf->pixels,
                              prev_frame->pixbuf->pixels, pstGIFInfo->u32FrameBuffSize);
                }
                else if (prev_frame->action == DISPOSE)
                {
                    //2.Restore to Background
                    xpos = prev_frame->x_offset / pstGIFInfo->u8Factor;
                    ypos = prev_frame->y_offset / pstGIFInfo->u8Factor;
                    if(xpos!=0 || ypos != 0 || (U32)(prev_frame->pixbuf->width) != pstGIFInfo->u32Pitch
                        || (U32)(prev_frame->pixbuf->height) != pstGIFInfo->u32Height)
                    {
                        memcpy(pstGIFInfo->frame->pixbuf->pixels,
                              prev_frame->pixbuf->pixels, pstGIFInfo->u32FrameBuffSize);
                    }

                    rowstride = pstGIFInfo->u32BytePerOutputRow;
                    dest = pstGIFInfo->frame->pixbuf->pixels;
                    U16 u16bgColor = RGB8888_TO_1555(((pstGIFInfo->gif89.transparent !=  - 1) ? 0 : 1),
                            pstGIFInfo->animation->bg_red,
                            pstGIFInfo->animation->bg_green,
                            pstGIFInfo->animation->bg_blue);
                    while (TRUE)
                    {

                        temp1555 = (U16*)(U32)(dest + ypos * rowstride + xpos * 2);
                        *temp1555 = u16bgColor;
                        //index
                        xpos++; //pixel
                        if (xpos == (prev_frame->pixbuf->width / pstGIFInfo->u8Factor + prev_frame
                            ->x_offset / pstGIFInfo->u8Factor))
                        {
                            xpos = prev_frame->x_offset / pstGIFInfo->u8Factor;
                            ypos++;
                            if (ypos >= (prev_frame->pixbuf->height / pstGIFInfo->u8Factor +
                                prev_frame->y_offset / pstGIFInfo->u8Factor))
                            {

                                break;
                            }
                        }
                    }
                }
                 else if (prev_frame->action == REVERT)
                {
                    //copy the same area fram prepreframe to prepreframe
                    GIF_DBG(printf("REVERT...\n"));
                    memcpy(pstGIFInfo->frame->pixbuf->pixels,
                              prev_frame->pixbuf->pixels, pstGIFInfo->u32FrameBuffSize); //refine later

                    // Coverity: CID-165320
                    if( pstGIFInfo->animation->n_frames < 3 )
                    {
                        GIF_ERR( printf("\nError: pstGIFInfo->animation->n_frames=%u!\n", pstGIFInfo->animation->n_frames); );
                        return -4;
                    }
                    else
                    {
                        prev_prev_frame = pstGIFInfo->animation->frames[(pstGIFInfo->animation->n_frames) - 3];
                    }

                    S32 rowstride_prev_prev_frame = 0;
                    S32 rowstride_context_frame = 0;
                    //2.revert  to pre pre frame on preframe position
                    xpos_prev_prev_frame = prev_frame->x_offset / pstGIFInfo->u8Factor;
                    ypos_prev_prev_frame = prev_frame->y_offset / pstGIFInfo->u8Factor;
                    xpos_context_frame = prev_frame->x_offset / pstGIFInfo->u8Factor;
                    ypos_context_frame = prev_frame->y_offset / pstGIFInfo->u8Factor;
                    //rowstride used for change line
                    rowstride_prev_prev_frame = pstGIFInfo->u32BytePerOutputRow;

                    rowstride_context_frame = pstGIFInfo->u32BytePerOutputRow;

                    dest_prev_prev_frame = prev_prev_frame->pixbuf->pixels;
                    dest_context_frame = pstGIFInfo->frame->pixbuf->pixels;

                    while (TRUE)
                    {
                        temp1555 = (U16*)(U32)(dest_context_frame +
                            (ypos_context_frame* rowstride_context_frame) +
                            xpos_context_frame * 2);
                        source1555 = (U16*)(U32)(dest_prev_prev_frame +
                            (ypos_prev_prev_frame* rowstride_prev_prev_frame) +
                            xpos_prev_prev_frame * 2);

                        *temp1555 = * source1555;
                        xpos_prev_prev_frame++;
                        xpos_context_frame++;
                        if (xpos_prev_prev_frame == (prev_prev_frame->pixbuf
                            ->width / pstGIFInfo->u8Factor + prev_prev_frame->x_offset / pstGIFInfo->u8Factor))
                        {
                            xpos_prev_prev_frame = prev_frame->x_offset / pstGIFInfo->u8Factor;
                            xpos_context_frame = prev_frame->x_offset / pstGIFInfo->u8Factor;
                            ypos_prev_prev_frame++;
                            ypos_context_frame++;
                        }
                        if (ypos_prev_prev_frame >= (prev_prev_frame->pixbuf
                            ->height / pstGIFInfo->u8Factor + prev_prev_frame->y_offset / pstGIFInfo->u8Factor))
                        {
                            break;
                        }
                    }
                }
            }
            else
            //first frame
            {
                GIF_INFO(printf("[GIF]:first frame\n"));
                _msAPI_GifDecoder_FillPixbuf(pstGIFInfo->frame->pixbuf, (pstGIFInfo->animation
                    ->bg_red << 24) | (pstGIFInfo->animation->bg_green << 16) |
                    (pstGIFInfo->animation->bg_blue << 8));
            }

        }

    }
    pstGIFInfo->state = GIF_DECODE_ROWS;
    return 0;
}

static S32 _msAPI_GifDecoder_Get_Extension(void)
{
    S32 retval;
    S32 empty_block = FALSE;

    if (pstGIFInfo->extension_flag)
    {
        if (pstGIFInfo->extension_label == 0)
        {

            if (_msAPI_GifDecoder_DataRequest(&pstGIFInfo->extension_label, 1) == 0)
            {
                return  - 1;
            }
        }
        switch (pstGIFInfo->extension_label)
        {
            case 0xf9:

                retval = _msAPI_GifDecoder_GetDataBlock((U8*)pstGIFInfo->block_buf, NULL);
                if (retval != 0)
                {
                    return retval;
                }
                if (pstGIFInfo->frame == NULL)
                {

                    pstGIFInfo->gif89.disposal = (pstGIFInfo->block_buf[0] >> 2) &0x7;
                    pstGIFInfo->gif89.input_flag = (pstGIFInfo->block_buf[0] >> 1)
                        &0x1;
                    pstGIFInfo->gif89.delay_time = MERGE_BYTE_LE(pstGIFInfo->block_buf[1], pstGIFInfo->block_buf[2]);
                    if ((pstGIFInfo->block_buf[0] &0x1) != 0)
                    {
                        pstGIFInfo->gif89.transparent = pstGIFInfo->block_buf[3];
                    }
                    else
                    {
                        pstGIFInfo->gif89.transparent =  - 1;
                    }
                }

                pstGIFInfo->block_count = 0;
                pstGIFInfo->extension_flag = FALSE;
                break;
            case 0xff:

                if (!pstGIFInfo->in_loop_extension)
                {
                    retval = _msAPI_GifDecoder_GetDataBlock((U8*)pstGIFInfo->block_buf, NULL);
                    if (retval != 0)
                    {
                        return retval;
                    }
                    if (!memcmp(pstGIFInfo->block_buf,
                        "NETSCAPE2.0", 11) || !memcmp(pstGIFInfo->block_buf, "ANIMEXTS1.0", 11))
                    {
                        pstGIFInfo->in_loop_extension = TRUE;
                        GIF_INFO(printf("[GIF]: APP block.\n"));
                    }
                    pstGIFInfo->block_count = 0;
                }
                if (pstGIFInfo->in_loop_extension)
                {
                    do
                    {
                        retval = _msAPI_GifDecoder_GetDataBlock((U8*)
                            pstGIFInfo->block_buf, &empty_block);
                        if (retval != 0)
                        {
                            return retval;
                        }
                        if (pstGIFInfo->block_buf[0] == 0x01)
                        {
                            pstGIFInfo->animation->loop = pstGIFInfo->block_buf[1] +
                                (pstGIFInfo->block_buf[2] << 8);
                        }
                        pstGIFInfo->block_count = 0;
                    }
                    while (!empty_block);
                    pstGIFInfo->in_loop_extension = FALSE;
                    pstGIFInfo->extension_flag = FALSE;
                    return 0;
                }
                break;
            default:

                break;
        }
    }

    do
    {
        retval = _msAPI_GifDecoder_GetDataBlock((U8*)pstGIFInfo->block_buf,
            &empty_block);
        if (retval != 0)
        {
            return retval;
        }
        pstGIFInfo->block_count = 0;
    } while (!empty_block);
    return 0;
}

static S32 _msAPI_GifDecoder_GetFrameInfo(void)
{
    //image descriptor
    U8 rgb[3] = {0};
    U8 buf[9] = {0};

    if (_msAPI_GifDecoder_DataRequest(buf, 9) == 0)
    {
        return  - 1;
    }

    pstGIFInfo->frame_len = MERGE_BYTE_LE(buf[4], buf[5]);
    pstGIFInfo->frame_height = MERGE_BYTE_LE(buf[6], buf[7]);
    pstGIFInfo->x_offset = MERGE_BYTE_LE(buf[0], buf[1]);
    pstGIFInfo->y_offset = MERGE_BYTE_LE(buf[2], buf[3]);
    if (pstGIFInfo->animation->frames == NULL && pstGIFInfo->gif89.disposal == 3)
    {

        pstGIFInfo->gif89.disposal = 0;
    }
    pstGIFInfo->frame_interlace = CHECK_BIT_SET(buf[8], INTERLACE);
    GIF_INFO(printf(
        ">width: %d height: %d xoffset: %d yoffset: %d disposal: %d delay: %d transparent: %d interlace: %d\n",
        pstGIFInfo->frame_len, pstGIFInfo->frame_height, pstGIFInfo->x_offset, pstGIFInfo->y_offset,
        pstGIFInfo->gif89.disposal, pstGIFInfo->gif89.delay_time, pstGIFInfo->gif89.transparent, pstGIFInfo->frame_interlace));
    if (CHECK_BIT_SET(buf[8], LOCALCOLORTABLE))//has local color table
    {

        pstGIFInfo->has_local_colortable = TRUE;
        pstGIFInfo->frame_bit_pixel = 1 << ((buf[8] & 0x07) + 1);
        pstGIFInfo->frame_colormap_size = 0;


        while ((U32)(pstGIFInfo->frame_colormap_size) < pstGIFInfo->frame_bit_pixel)
        {
            if (_msAPI_GifDecoder_DataRequest(rgb, sizeof(rgb)) == 0)
            {
                return  - 1;
            }
            pstGIFInfo->frame_color_map[0][pstGIFInfo->frame_colormap_size] = rgb[0];
            pstGIFInfo->frame_color_map[1][pstGIFInfo->frame_colormap_size] = rgb[1];
            pstGIFInfo->frame_color_map[2][pstGIFInfo->frame_colormap_size] = rgb[2];
            pstGIFInfo->frame_colormap_size++;
        }


    }
    if ((!pstGIFInfo->has_global_colortable) && ((CHECK_BIT_SET(buf[8], LOCALCOLORTABLE)==0)))
    {
        pstGIFInfo->state = GIF_DONE;
        GIF_ERR(printf(
            "GIF image has no global colormap, and a frame inside it has no local colormap."));
        return  - 2;
    }

    pstGIFInfo->lzw_code_pending =  - 1;

    S32 i;
    if (_msAPI_GifDecoder_DataRequest(&(pstGIFInfo->lzw_set_code_size), 1) == 0)
    {

        return  - 1;
    }
    if (pstGIFInfo->lzw_set_code_size > MAX_LZW_BITS)
    {
        GIF_ERR(printf("GIF image is corrupt (incorrect LZW compression)"));
        return  - 2;
    }
    pstGIFInfo->lzw_code_size = pstGIFInfo->lzw_set_code_size + 1;
    pstGIFInfo->lzw_clear_code = 1 << pstGIFInfo->lzw_set_code_size;
    pstGIFInfo->lzw_end_code = pstGIFInfo->lzw_clear_code + 1;
    pstGIFInfo->lzw_max_code_size = 2 * pstGIFInfo->lzw_clear_code;
    pstGIFInfo->lzw_max_code = pstGIFInfo->lzw_clear_code + 2;
    pstGIFInfo->lzw_fresh = TRUE;
    pstGIFInfo->code_curbit = 0;
    pstGIFInfo->code_lastbit = 0;
    pstGIFInfo->code_last_byte = 0;
    pstGIFInfo->code_done = FALSE;


    for (i = 0; i < pstGIFInfo->lzw_clear_code; ++i)
    {
        pstGIFInfo->lzw_table[0][i] = 0;
    }
    for (i = 0; i < pstGIFInfo->lzw_clear_code; ++i)
    {
        pstGIFInfo->lzw_table[1][i] = i;
    }
    pstGIFInfo->lzw_table[1][0] = 0;
    for (; i < (1 << MAX_LZW_BITS); ++i)
    {
        pstGIFInfo->lzw_table[0][i] = 0;
    }
    pstGIFInfo->lzw_sp = pstGIFInfo->lzw_stack;

    pstGIFInfo->state = GIF_GET_LZW;
    pstGIFInfo->draw_xpos = 0;
    pstGIFInfo->draw_ypos = 0;
    pstGIFInfo->draw_pass = 0;

    return 0;
}

static S32 _msAPI_GifDecoder_GetNextStep(void)
{
    S32 retval;
    U8 c = 0;

    while (TRUE)
    {
        if (_msAPI_GifDecoder_DataRequest(&c, 1) == 0)
        {
            return  - 1;
        }
        switch(c)
        {
        case  ';':

            //0x3B :terminal

            pstGIFInfo->state = GIF_DONE;
            return 0;

        case '!':

            //0x21 :extension

            pstGIFInfo->extension_flag = TRUE;
            pstGIFInfo->extension_label = 0;
            pstGIFInfo->block_count = 0;
            pstGIFInfo->block_ptr = 0;

            retval = _msAPI_GifDecoder_Get_Extension();
            if (retval == 0)
           {

                continue;
             }

            return retval;

        }

        if (c != ',')
        {
            //0x2c frame_info

            continue;
        }

        retval = _msAPI_GifDecoder_GetFrameInfo();

        return retval;
    }
}

EN_STILLIMAGE_RET msAPI_GifDecoder_Probe(void)
{
    U32 u32i;
    EN_STILLIMAGE_RET enRet = E_STILLIMAGE_RET_FAIL;
    U8 u8Header[GIF_HEADER_SIZE];

    msAPI_StillImage_BMFile_Seek(0, E_BM_FILEPOS_SEEK_SET);
    msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());

    _msAPI_GifDecoder_Reset();

    // make sure there is enough data for header parsing
    if (msAPI_StillImage_BMBuffer_Remainder() < GIF_HEADER_SIZE)
    {
        msAPI_StillImage_BMBuffer_CustomFill(GIF_HEADER_SIZE);
    }

    for (u32i = 0; u32i < GIF_HEADER_SIZE; u32i++)
    {
        u8Header[u32i] = msAPI_StillImage_BMBuffer_PeekNthByte(u32i);
    }

    if(u8Header[0] == 'G' && u8Header[1] == 'I' && u8Header[2] == 'F')
    {
        enRet = E_STILLIMAGE_RET_OK;
    }

    if (enRet == E_STILLIMAGE_RET_OK)
    {
        g_stStillImage.pfStillImage_ReadHeader = msAPI_GifDecoder_ReadHeader;
        g_stStillImage.pfStillImage_Task = msAPI_GifDecoder_Decode;
        g_stStillImage.pfStillImage_Stop = msAPI_GifDecoder_Stop;
    }

    return enRet;
}

EN_STILLIMAGE_RET msAPI_GifDecoder_ReadHeader(void)
{
    U32 u32OutputBuffLen;
    U8 rgb[3] = {0};
    U8 buf[16] = {0};

    pstGIFInfo= (stGIF*)msAPI_StillImage_Dlmalloc_Malloc(sizeof(stGIF));
    if (pstGIFInfo == NULL)
    {
        GIF_ERR(printf("[GIF] No space for pstGIFInfo->lzw_table[0]\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_TRANSITIONAL_MEM_ERR;
        goto fail;
    }

    if (_msAPI_GifDecoder_DataRequest(buf, 13) == 0)
    {
        g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;
        GIF_ERR(printf("[GIF]: no data!\n"));

        goto fail;
    }

    if(!(buf[3] == '8' && buf[4] == '7' && buf[5] == 'a') &&
        !(buf[3] == '8' && buf[4] == '9' && buf[5] == 'a'))
    {
        g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;
        GIF_ERR(printf("[GIF]: version is not supported!\n"));

        goto fail;
    }
    _msAPI_GifDecoder_Reset();

    pstGIFInfo->animation = msAPI_StillImage_Dlmalloc_Malloc(sizeof(GIF_ANIM));
    if (pstGIFInfo->animation == NULL)
    {
        GIF_ERR(printf("[GIF] No space for pstGIFInfo->animation\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_TRANSITIONAL_MEM_ERR;
        goto fail;
    }
    memset(pstGIFInfo->animation, 0, sizeof(GIF_ANIM));

     // Logical Screen descriptor
    pstGIFInfo->u32Width = MERGE_BYTE_LE(buf[6], buf[7]);
    pstGIFInfo->u32Height = MERGE_BYTE_LE(buf[8], buf[9]);
    pstGIFInfo->global_bit_pixel = 2<<((buf[10] &0x07));
    pstGIFInfo->global_color_resolution = (((buf[10] &0x70) >> 3) + 1);
    pstGIFInfo->has_global_colortable = (buf[10] &0x80) != 0;
    pstGIFInfo->background_index = buf[11];
    pstGIFInfo->aspect_ratio = buf[12];

    pstGIFInfo->animation->bg_red = 0;
    pstGIFInfo->animation->bg_green = 0;
    pstGIFInfo->animation->bg_blue = 0;
    pstGIFInfo->animation->width = pstGIFInfo->u32Width;
    pstGIFInfo->animation->height = pstGIFInfo->u32Height;

    pstGIFInfo->u32TotalRowOutputted = 0;
    pstGIFInfo->u32TotalRowProcessed = 0;
    pstGIFInfo->frame = NULL;
    pstGIFInfo->state = GIF_GET_NEXT_STEP;
    pstGIFInfo->has_local_colortable = FALSE;
    pstGIFInfo->buf = NULL;
    pstGIFInfo->gif89.transparent =  - 1;
    pstGIFInfo->gif89.delay_time =  - 1;
    pstGIFInfo->gif89.input_flag =  - 1;
    pstGIFInfo->gif89.disposal =  - 1;
    pstGIFInfo->animation->loop = 1;
    pstGIFInfo->in_loop_extension = FALSE;
    pstGIFInfo->amount_needed = 0;
    pstGIFInfo->animation->n_frames = 0;
    pstGIFInfo->stop_after_first_frame = g_stStillImage.stInputCfgParams.bOnlyDecodeFirstFrame;

    // GIF contains no thumbnail
    if (g_stStillImage.stInputCfgParams.bDecodeThumbnail == TRUE)
    {
        GIF_ERR(printf("[GIF] No thumbnail\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_NO_THUMBNAIL;

        goto fail;
    }

    GIF_INFO(printf("[GIF] width:%d:height:%d\n",pstGIFInfo->u32Width,pstGIFInfo->u32Height));
    // read header failed
    if ((pstGIFInfo->u32Width == 0) || (pstGIFInfo->u32Height == 0))
    {
        GIF_ERR(printf("[GIF] Header parsing, bad width(%d) or height(%d)\n", pstGIFInfo->u32Width, pstGIFInfo->u32Height));
        g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;

        goto fail;
    }
   // printf("pstGIFInfo->global_bit_pixel :%d\n", (buf[4] &0x07));
   // printf(
   //     "Image width: %d height: %d global_cmap: %d background: %d global_bit_pixel: %d\n", pstGIFInfo->u32Width, pstGIFInfo->u32Height, pstGIFInfo->has_global_colortable, pstGIFInfo->background_index, pstGIFInfo->global_bit_pixel);
    if (pstGIFInfo->has_global_colortable)
    {

        pstGIFInfo->global_colortable_size = 0;

        while ((U32)(pstGIFInfo->global_colortable_size) < pstGIFInfo->global_bit_pixel)
        {
            if (_msAPI_GifDecoder_DataRequest(rgb, sizeof(rgb)) == 0)
            {
                // 3byte a time
                g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;
                GIF_ERR(printf("[GIF]: no data!\n"));

                goto fail;
            }
            pstGIFInfo->global_color_table[0][pstGIFInfo->global_colortable_size] = rgb[0];
            pstGIFInfo->global_color_table[1][pstGIFInfo->global_colortable_size] = rgb[1];
            pstGIFInfo->global_color_table[2][pstGIFInfo->global_colortable_size] = rgb[2];
            if ((U32)(pstGIFInfo->global_colortable_size) == pstGIFInfo->background_index)
            {
                pstGIFInfo->animation->bg_red = rgb[0];
                pstGIFInfo->animation->bg_green = rgb[1];
                pstGIFInfo->animation->bg_blue = rgb[2];
            }
            pstGIFInfo->global_colortable_size++;
        }


    }


    // setup output parameters
    if(pstGIFInfo->stop_after_first_frame)
    {
        pstGIFInfo->eOutputFormat = E_GIF_ARGB8888;
        pstGIFInfo->u8OutputPixelSize = 4;     // 4 bytes
        GIF_INFO(printf("[GIF] Only decode first frame. output format is ARGB8888\n"));
    }
    else
    {
        pstGIFInfo->eOutputFormat = E_GIF_ARGB1555;
        pstGIFInfo->u8OutputPixelSize = 2;     // 2 bytes
        GIF_INFO(printf("[GIF] decode all frames. output format is ARGB1555\n"));
    }

    // calculate decode output pitch
    pstGIFInfo->u32Pitch = pstGIFInfo->u32Width;

    pstGIFInfo->pu8OutputBuffer = (U8 *)g_stStillImage.stInputCfgParams.u32OutputBuffAddr;
    if (pstGIFInfo->pu8OutputBuffer == NULL)
    {
        GIF_ERR(printf("[GIF] No output buffer\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_OUTPUT_BUFFER_NULL;
        goto fail;
    }

    // calculate down scale factor
    {

        u32OutputBuffLen = _ALIGNMENT_(g_stStillImage.stInputCfgParams.u32GifMaxWidth, GIF_OUTPUT_ALIGNMENT)
                * g_stStillImage.stInputCfgParams.u32GifMaxHeight * pstGIFInfo->u8OutputPixelSize;
        u32OutputBuffLen = u32OutputBuffLen < g_stStillImage.stInputCfgParams.u32OutputBuffLen ?
                u32OutputBuffLen : g_stStillImage.stInputCfgParams.u32OutputBuffLen;

        for (pstGIFInfo->u8Factor = 1; pstGIFInfo->u8Factor <= GIF_MAX_SCALE_DOWN_FACTOR; pstGIFInfo->u8Factor <<= 1)
        {
            pstGIFInfo->u32OutputWidth = _ALIGNMENT_(pstGIFInfo->u32Width, pstGIFInfo->u8Factor) / pstGIFInfo->u8Factor;
            pstGIFInfo->u32OutputHeight = _ALIGNMENT_(pstGIFInfo->u32Height, pstGIFInfo->u8Factor) / pstGIFInfo->u8Factor;
            pstGIFInfo->u32OutputPitch = _ALIGNMENT_(pstGIFInfo->u32OutputWidth, GIF_OUTPUT_ALIGNMENT);

            if (((U32)pstGIFInfo->u32OutputPitch * pstGIFInfo->u32OutputHeight * pstGIFInfo->u8OutputPixelSize)
                    <= u32OutputBuffLen)
            {
                break;
            }
        }
        pstGIFInfo->u32BytePerOutputRow = pstGIFInfo->u32OutputPitch * pstGIFInfo->u8OutputPixelSize;

        if (pstGIFInfo->u8Factor > GIF_MAX_SCALE_DOWN_FACTOR)
        {
            u32OutputBuffLen = _ALIGNMENT_(g_stStillImage.stInputCfgParams.u32GifMaxWidth, GIF_OUTPUT_ALIGNMENT)
                    * g_stStillImage.stInputCfgParams.u32GifMaxHeight * pstGIFInfo->u8OutputPixelSize;
            if (u32OutputBuffLen < pstGIFInfo->u32Pitch * pstGIFInfo->u32Height * pstGIFInfo->u8Factor * pstGIFInfo->u8OutputPixelSize)
            {
                GIF_ERR(printf("[GIF] out of max resolution. Supported: %d(%d)x%d, Image: %d(%d)x%d\n",
                        g_stStillImage.stInputCfgParams.u32GifMaxWidth,
                        _ALIGNMENT_(g_stStillImage.stInputCfgParams.u32GifMaxWidth, GIF_OUTPUT_ALIGNMENT),
                        g_stStillImage.stInputCfgParams.u32GifMaxHeight,
                        pstGIFInfo->u32Width,
                        pstGIFInfo->u32Pitch,
                        pstGIFInfo->u32Height));
                g_stStillImage.enError = E_STILLIMAGE_GIF_RESOLUTION_NOT_SUPPORTED;
                goto fail;
            }

            u32OutputBuffLen = u32OutputBuffLen < g_stStillImage.stInputCfgParams.u32OutputBuffLen ?
                    u32OutputBuffLen : g_stStillImage.stInputCfgParams.u32OutputBuffLen;
            if (u32OutputBuffLen < pstGIFInfo->u32Pitch * pstGIFInfo->u32Height * pstGIFInfo->u8Factor * pstGIFInfo->u8OutputPixelSize)
            {
                GIF_ERR(printf("[GIF] Output buffer too small, size: %d, Image: %dx%d, Output: %d(%d)x%d\n",
                        g_stStillImage.stInputCfgParams.u32OutputBuffLen,
                        pstGIFInfo->u32Width, pstGIFInfo->u32Pitch, pstGIFInfo->u32Height));
                g_stStillImage.enError = E_STILLIMAGE_GIF_SCALE_DOWN_FACTOR_NOT_SUPPORT;
                goto fail;
            }
        }

        GIF_INFO(printf("[GIF] Scale Factor:%x\n",pstGIFInfo->u8Factor));

    }

    pstGIFInfo->u32FrameBuffSize = pstGIFInfo->u32BytePerOutputRow*pstGIFInfo->u32OutputHeight;
    pstGIFInfo->u8FreeSlotNum = g_stStillImage.stInputCfgParams.u32OutputBuffLen/pstGIFInfo->u32FrameBuffSize;
    pstGIFInfo->u32FrameInfoArrayBuffAddr = g_stStillImage.stInputCfgParams.u32FrameInfoArrayAddr;
    pstGIFInfo->u32FrameInfoArrayBuffSize = g_stStillImage.stInputCfgParams.u32FrameInfoArraySize;
    GIF_INFO(printf("[GIF] Free slot:0x%x, framebuffer size:0x%x, frameInfoArrayAddr:0x%x, size:0x%x\n",
    pstGIFInfo->u8FreeSlotNum,pstGIFInfo->u32FrameBuffSize,pstGIFInfo->u32FrameInfoArrayBuffAddr, pstGIFInfo->u32FrameInfoArrayBuffSize));
    g_stStillImage.u32DecodedFrameIndex = _U32_MAX;
    g_stStillImage.u32DisplayedFrameIndex = _U32_MAX;
    //if support animation , it need at least three frame buffers.
    if(!pstGIFInfo->stop_after_first_frame && pstGIFInfo->u8FreeSlotNum < 3)
    {
        GIF_ERR(printf("[GIF] Output buffer size is not enough for animation.\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_TRANSITIONAL_MEM_ERR;
        goto fail;
    }

    if(_msAPI_GifDecoder_GetNextStep() < 0)
    {
        GIF_ERR(printf("[GIF]: decode header fail\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_DECOMPRESSION_ERROR;
    }
     //fill first frame backgroud
    _msAPI_GifDecoder_GetLzw();
    if(pstGIFInfo->state != GIF_DECODE_ROWS)
    {
        GIF_ERR(printf("[GIF] decode header fail\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_DECOMPRESSION_ERROR;
    }


    // update information about this image
    g_stStillImage.u32FirstPixelPos     = (U32)msAPI_StillImage_BMFile_Tell();
    g_stStillImage.u32OutputPitch       = pstGIFInfo->u32OutputPitch;
    g_stStillImage.u32OutputWidth       = pstGIFInfo->u32OutputWidth;
    g_stStillImage.u32OutputHeight      = pstGIFInfo->u32OutputHeight;
    g_stStillImage.u32OutputSize        = (U32)(g_stStillImage.u32OutputPitch * g_stStillImage.u32OutputHeight * pstGIFInfo->u8OutputPixelSize);
    g_stStillImage.u32ImageWidth        = pstGIFInfo->u32Width;
    g_stStillImage.u32ImageHeight       = pstGIFInfo->u32Height;
    g_stStillImage.u8DownScaleFactor    = pstGIFInfo->u8Factor;
    g_stStillImage.bHasThumbnail        = FALSE;
    g_stStillImage.enInputFormat        = pstGIFInfo->gif89.delay_time == -1 ? E_STILLIMAGE_INPUT_DATA_GIF_NOT_ANIMATION : E_STILLIMAGE_INPUT_DATA_GIF_ANIMATION;
    g_stStillImage.u32LoopTotalNumber = pstGIFInfo->animation->loop;
    if(pstGIFInfo->eOutputFormat == E_GIF_ARGB8888)
    {
        g_stStillImage.enOutputFormat       = E_STILLIMAGE_OUTPU_RAW_ARGB8888;
    }
    else
    {
        g_stStillImage.enOutputFormat       = E_STILLIMAGE_OUTPU_ARGB1555;
    }
    g_stStillImage.bHasDateTime         = FALSE;
    g_stStillImage.enOrientation        = E_STILLIMAGE_ORIENT_UNDEFINE;
    g_stStillImage.u32SlotTotalNum = pstGIFInfo->u8FreeSlotNum;
    g_stStillImage.u32OutputFrameSize = pstGIFInfo->u32FrameBuffSize;

fail:
    if (g_stStillImage.enError != E_STILLIMAGE_ERR_NONE)
    {
        _msAPI_GifDecoder_FreeResource();
        GIF_ERR(printf("[GIF]:parse header fail\n"));
        return E_STILLIMAGE_RET_FAIL;
    }

    pstGIFInfo->bStop = FALSE;
    pstGIFInfo->u32DataProcessed = 0;
    return E_STILLIMAGE_RET_OK;
}


EN_STILLIMAGE_RET msAPI_GifDecoder_Decode(void)
{
    EN_STILLIMAGE_RET enRet = E_STILLIMAGE_RET_WORKING;
    S32 retval = 0;;

    if (pstGIFInfo->bStop == FALSE)
    {
        switch (pstGIFInfo->state)
        {
            case GIF_GET_NEXT_STEP:
                GIF_INFO(printf("[GIF]:state: -->NEXT STEP\n"));
                retval = _msAPI_GifDecoder_GetNextStep();
                break;

            case GIF_LZW_FILL_BUFFER:
                GIF_DBG(printf("[GIF]:state: -->FILL BUFFER\n"));
                retval = _msAPI_GifDecoder_LzwFillBuffer();
                if((retval !=  - 3) && (retval != 0))
                {
                    enRet = E_STILLIMAGE_RET_FAIL;
                    GIF_INFO(printf("return :%x\n", retval));
                }
                break;
            case GIF_LZW_CLEAR_CODE:
                GIF_DBG(printf("[GIF]:state: -->CLEAR CODE\n"));
                retval = _msAPI_GifDecoder_LzwClearCode();
                break;
            case GIF_GET_LZW:
                GIF_INFO(printf("[GIF]:state: -->GET LZW\n"));
                retval = _msAPI_GifDecoder_GetLzw();
                if((retval !=  - 3) && (retval != 0))
                {
                    enRet = E_STILLIMAGE_RET_FAIL;
                    GIF_INFO(printf("return :%x\n", retval));
                }
                break;
            case GIF_DECODE_ROWS:
                GIF_DBG(printf("[GIF]:state: -->DECODE ROWS\n"));
                retval = _msAPI_GifDecoder_DecodeRows();
                if((retval !=  - 3) && (retval != 0))
                {
                    enRet = E_STILLIMAGE_RET_FAIL;
                    GIF_INFO(printf("return :%x\n", retval));
                }
                break;
            case GIF_WAIT_FREE_SLOT:
                if(_msAPI_GifDecoder_HasFreeSlotBuf())
                {
                    GIF_INFO(printf("[GIF]:state: WAIT FREE SLOT-->GET LZW\n"));
                    pstGIFInfo->state = GIF_GET_LZW;
                }
                break;

            case GIF_DECODE_ONE_FRAME_DONE:
                GIF_INFO(printf("[GIF]:state: -->DECODE ONE FRAME DONE\n"));
                _msAPI_GifDecoder_UpdateDecodedFrameInfo();
                if (pstGIFInfo->stop_after_first_frame || g_stStillImage.u32DecodedFrameIndex == _U32_MAX)
                {
                    pstGIFInfo->state = GIF_DONE;
                }
                else
                {
                    pstGIFInfo->state = GIF_GET_NEXT_STEP;
                }
                enRet = E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE;
                break;

            case GIF_DONE:
                GIF_INFO(printf("[GIF]:state: -->DONE\n"));
                if(!g_stStillImage.stInputCfgParams.bOnlyPlayFirstLoopForLoopAnimation &&
                     (pstGIFInfo->animation->n_frames > pstGIFInfo->u8FreeSlotNum) &&   //if all frames in buffer, let ap to loop, otherwise, codec continue decode
                     (pstGIFInfo->animation->loop == 0 ||(pstGIFInfo->u32LoopNumber + 1) < (U32)(pstGIFInfo->animation->loop)) && //loop forever or not finish loop all
                     (g_stStillImage.u32DecodedFrameIndex != _U32_MAX))
                {
                    if(_msAPI_GifDecoder_ResetForNextLoopPlay() == TRUE)
                    {
                        GIF_INFO(printf("[GIF]:state: -->GIF_GET_NEXT_STEP(Loop play)\n"));
                        pstGIFInfo->state = GIF_GET_NEXT_STEP;
                    }
                    else
                    {
                        enRet = E_STILLIMAGE_RET_FAIL;
                        GIF_INFO(printf("[GIF]: gif reset loop play fail\n"));
                    }
                }
                else
                {
                    GIF_INFO(printf("[GIF]:state: -->EXIT LOOP\n"));
                    enRet = E_STILLIMAGE_RET_DONE;
                }
                break;

            default:
                GIF_INFO(printf("[GIF]:state: -->EXIT LOOP\n"));
                enRet = E_STILLIMAGE_RET_DONE;
        };
    }

    // update progress here
    g_stStillImage.u16Progress = (U16)((U64)pstGIFInfo->u32DataProcessed * 1000 / (U32)msAPI_StillImage_BMFile_Size());

    if (enRet == E_STILLIMAGE_RET_DONE)
    {
        g_stStillImage.u16Progress = 1000;
        pstGIFInfo->bStop = TRUE;
    }
    else if (enRet != E_STILLIMAGE_RET_WORKING && enRet != E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE)
    {
        // release resourse when done or error
        _msAPI_GifDecoder_FreeResource();
        pstGIFInfo->bStop = TRUE;
    }

    return enRet;
}


EN_STILLIMAGE_RET msAPI_GifDecoder_Stop(void)
{
    _msAPI_GifDecoder_FreeResource();
    _msAPI_GifDecoder_Reset();

    return E_STILLIMAGE_RET_OK;
}

//------------------------------------------------------------------------------
// Local Function Implementation
//------------------------------------------------------------------------------
static void _msAPI_GifDecoder_Reset(void)
{
    if(pstGIFInfo)
    {
        memset(pstGIFInfo, 0, sizeof(stGIF));

        pstGIFInfo->eOutputFormat = E_GIF_ARGB8888;
        pstGIFInfo->u8OutputPixelSize = 4;
        pstGIFInfo->bStop = TRUE;
    }
}

static BOOLEAN _msAPI_GifDecoder_ResetForNextLoopPlay(void)
{
    U8 rgb[3] ={0};
    U8 buf[16] ={0};

    pstGIFInfo->u32LoopNumber++;
    pstGIFInfo->u32TotalFramesInOneLoop = pstGIFInfo->animation->n_frames;
    msAPI_StillImage_BMFile_Seek(0, E_BM_FILEPOS_SEEK_SET);

    if (pstGIFInfo->animation != NULL)
    {
        U32 i;

        for(i = 0; i < (U32)(pstGIFInfo->animation->n_frames); i++)
        {
            if(pstGIFInfo->animation->frames[i]->pixbuf->pixels)
            {
                msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->animation->frames[i]->pixbuf);
                msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->animation->frames[i]);
            }
        }
        msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->animation);
        pstGIFInfo->animation = NULL;
    }


    if (_msAPI_GifDecoder_DataRequest(buf, 13) == 0)
    {
        g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;
        GIF_ERR(printf("[GIF]: no data!\n"));

        goto fail;
    }

    if(!(buf[3] == '8' && buf[4] == '7' && buf[5] == 'a') &&
        !(buf[3] == '8' && buf[4] == '9' && buf[5] == 'a'))
    {
        g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;
        GIF_ERR(printf("[GIF]: version is not supported!\n"));

        goto fail;
    }

    pstGIFInfo->animation = msAPI_StillImage_Dlmalloc_Malloc(sizeof(GIF_ANIM));
    if (pstGIFInfo->animation == NULL)
    {
        GIF_ERR(printf("[GIF] No space for pstGIFInfo->animation\n"));
        g_stStillImage.enError = E_STILLIMAGE_GIF_TRANSITIONAL_MEM_ERR;
        goto fail;
    }
    memset(pstGIFInfo->animation, 0, sizeof(GIF_ANIM));

     // Logical Screen descriptor
    pstGIFInfo->u32Width = MERGE_BYTE_LE(buf[6], buf[7]);
    pstGIFInfo->u32Height = MERGE_BYTE_LE(buf[8], buf[9]);
    pstGIFInfo->global_bit_pixel = 2<<((buf[10] &0x07));
    pstGIFInfo->global_color_resolution = (((buf[10] &0x70) >> 3) + 1);
    pstGIFInfo->has_global_colortable = (buf[10] &0x80) != 0;
    pstGIFInfo->background_index = buf[11];
    pstGIFInfo->aspect_ratio = buf[12];

    pstGIFInfo->animation->bg_red = 0;
    pstGIFInfo->animation->bg_green = 0;
    pstGIFInfo->animation->bg_blue = 0;
    pstGIFInfo->animation->width = pstGIFInfo->u32Width;
    pstGIFInfo->animation->height = pstGIFInfo->u32Height;

    pstGIFInfo->u32TotalRowOutputted = 0;
    pstGIFInfo->u32TotalRowProcessed = 0;
    pstGIFInfo->frame = NULL;
    pstGIFInfo->state = GIF_GET_NEXT_STEP;
    pstGIFInfo->has_local_colortable = FALSE;
    pstGIFInfo->buf = NULL;
    pstGIFInfo->gif89.transparent =  - 1;
    pstGIFInfo->gif89.delay_time =  - 1;
    pstGIFInfo->gif89.input_flag =  - 1;
    pstGIFInfo->gif89.disposal =  - 1;
    pstGIFInfo->in_loop_extension = FALSE;
    pstGIFInfo->amount_needed = 0;
    pstGIFInfo->animation->n_frames = 0;
    pstGIFInfo->stop_after_first_frame = g_stStillImage.stInputCfgParams.bOnlyDecodeFirstFrame;

    GIF_INFO(printf("[GIF] width:%d:height:%d\n",pstGIFInfo->u32Width,pstGIFInfo->u32Height));
    // read header failed
    if ((pstGIFInfo->u32Width == 0) || (pstGIFInfo->u32Height == 0))
    {
        GIF_ERR(printf("[GIF] Header parsing, bad width(%d) or height(%d)\n", pstGIFInfo->u32Width, pstGIFInfo->u32Height));
        g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;

        goto fail;
    }

    if (pstGIFInfo->has_global_colortable)
    {

        pstGIFInfo->global_colortable_size = 0;

        while ((U32)(pstGIFInfo->global_colortable_size) < pstGIFInfo->global_bit_pixel)
        {
            if (!_msAPI_GifDecoder_DataRequest(rgb, sizeof(rgb)))
            {
                // 3byte a time
                g_stStillImage.enError = E_STILLIMAGE_GIF_WRONG_STATE;
                GIF_ERR(printf("[GIF]: no data!\n"));

                goto fail;
            }
            pstGIFInfo->global_color_table[0][pstGIFInfo->global_colortable_size] = rgb[0];
            pstGIFInfo->global_color_table[1][pstGIFInfo->global_colortable_size] = rgb[1];
            pstGIFInfo->global_color_table[2][pstGIFInfo->global_colortable_size] = rgb[2];
            if ((U32)(pstGIFInfo->global_colortable_size) == pstGIFInfo->background_index)
            {
                pstGIFInfo->animation->bg_red = rgb[0];
                pstGIFInfo->animation->bg_green = rgb[1];
                pstGIFInfo->animation->bg_blue = rgb[2];
            }
            pstGIFInfo->global_colortable_size++;
        }


    }
    return TRUE;
fail:
    GIF_ERR(printf("[GIF]:_msAPI_GifDecoder_ResetForNextLoopPlay fail.\n"));
    return FALSE;
}

static void _msAPI_GifDecoder_FreeResource(void)
{
    if(pstGIFInfo)
    {
        if (pstGIFInfo->animation != NULL)
        {
            U32 i;

            for(i = 0; i < (U32)(pstGIFInfo->animation->n_frames); i++)
            {
                if(pstGIFInfo->animation->frames[i]->pixbuf->pixels)
                {
                    msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->animation->frames[i]->pixbuf);
                    msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->animation->frames[i]);
                }
            }
            msAPI_StillImage_Dlmalloc_Free(pstGIFInfo->animation);
            pstGIFInfo->animation = NULL;
        }

        msAPI_StillImage_Dlmalloc_Free(pstGIFInfo);
        pstGIFInfo = NULL;
    }
}

static U32 _msAPI_GifDecoder_DataRequest(U8* pBuffer, U32 u32Size)
{
    U32 u32Remainder, u32Copied = 0;;

    while (u32Copied < u32Size)
    {
        u32Remainder = msAPI_StillImage_BMBuffer_Remainder();

        // short path
        if (((u32Size - u32Copied) == 1)
            && (u32Remainder == 1))
        {
            *(U8 *)pBuffer = msAPI_StillImage_BMBuffer_ReadBytes(1);
            msAPI_StillImage_BMBuffer_UpdateBase();
            u32Copied += 1;
            break;
        }

        // check how many bytes to copy
        u32Remainder = u32Remainder < (u32Size - u32Copied) ? u32Remainder : (u32Size - u32Copied);

        // copy remaind data
        msAPI_StillImage_BMBuffer_CopyNByte((U8 *)((U32)pBuffer + u32Copied), u32Remainder);
        msAPI_StillImage_BMBuffer_UpdateBase();
        u32Copied += u32Remainder;

        // check if EOF or all data is copied
        if ((msAPI_StillImage_BMFile_EOF() == TRUE)
                || (u32Copied == u32Size))
        {
            break;
        }

        if ((u32Size - u32Copied) > msAPI_StillImage_BM_GetPreloadSize())
        {
            msAPI_StillImage_BMBuffer_CustomFill(u32Size - u32Copied);
        }
        else
        {
            msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());
        }
    }

    pstGIFInfo->u32DataProcessed += u32Copied;
    GIF_DBG(printf("read size:%d\n",u32Size));
    return u32Size;
}

#endif// #if ENABLE_HK_GIF

#undef _MSAPI_GIF_DECODER_C_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
