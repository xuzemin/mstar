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

//-------------------------------------------------------------------------------------------------
// File Name:
//        msAPI_MPEG_Subtitle.h
// Description:
//        This file is a header file that defines the types, structures and functions of Mpeg2, Mpeg4 sub picture decode engine
// Note:
//        MStar Semi.
//-------------------------------------------------------------------------------------------------

#ifndef MSAPI_MPEG_SUBTITLE_H
#define MSAPI_MPEG_SUBTITLE_H

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------
#include "mapp_vdplayer_sharememcfg.h"

//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------
#ifdef MSAPI_MPEG_SUBTITLE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

////////////////////////////////////////////////////////////////////////////////
// Structure
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    U8  u8OutputFormat;
    U8  u8EnlargeRaio;
    U8  u8TransparentKey;
    U16 u16TopFieldLength;
    U16 u16BottomFieldLength;
    U32 u32TopFieldAddress;
    U32 u32BottomFieldAddress;
    U32 u32OutputAddress;
    U16 u16RegionWidth;
    U16 u16RegionHeight;
    U16 u16RegionPitch;     // 16 byte alignment;
    U16 u16ObjectXOffset;
    U16 u16ObjectYOffset;
    U8  u8RegionOffset;
    U8  u8RegionDepth;
    U8  u8RegionColorKeyBG;
    U8  u8RegionColorKeyFG;
    U8  u8Table2to4[4];
    U8  u8Table2to8[4];
    U8  u8Table4to8[16];
    U8  u8NonModifying;
    U16 u16MappingTable_2To4;
} stRLDParameters, *PstRLDParameters;

/// remove it , instead of subtitle type
/// Specify the video type
/*typedef enum
{
    E_SUBTITLE_VIDEO_TYPE_MPEG2,         /// MPEG2
    E_SUBTITLE_VIDEO_TYPE_MPEG4,         /// MPEG4
    E_SUBTITLE_VIDEO_TYPE_DIVX,          /// DIVX
    E_SUBTITLE_VIDEO_TYPE_MKV,
    E_SUBTITLE_VIDEO_TYPE_XVID,          /// XVID
    E_SUBTITLE_VIDEO_TYPE_RM,          ///
    E_SUBTITLE_VIDEO_TYPE_NUM,           /// Specify the number of video type
} enumSubtitleVideoType;*/

#define MAX_SPU_QUEUE_SIZE        120

#define ENABLE_DIVX_TTF 0

#define ENABLE_DIVX_SUBTITLE_OP 1
#define ENABLE_VOB_SUBTITLE_OP  1

// Subtitle memory allocation function, it could be called before video play
INTERFACE BOOLEAN msAPI_MpegSP_Init(void);

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
// Subtitle True Type Font table init, it could be called before video play
INTERFACE BOOLEAN msAPI_DivXTTF_InitTTF(U32 u32addr, U32 u32size);
#endif

// Subtitle memory destory function, it should be called after each video stopped
INTERFACE void msAPI_MpegSP_Dinit(void);

// Subtitle display function, it should be called after init().
INTERFACE void msAPI_MpegSP_Show(void);

// Subtitle stop display function, it should be called after init().
INTERFACE void msAPI_MpegSP_Unshow(void);

// Subtitle set show status, FALSE to free gwin memory, in order not to coexist with OSD
INTERFACE void msAPI_MpegSP_SetShowStatus(BOOLEAN bShowStatus);

// Get current subtitle display status().
INTERFACE BOOLEAN msAPI_MpegSP_Get_Show_Status(void);

INTERFACE BOOLEAN msAPI_MpegSP_Get_Render_Status(void);

// Reset pushed spu elements in spu queue, it used for subtitle stop, subtitle lang change.
INTERFACE void msAPI_MpegSP_Reset_SpuQueue(void);

// Subtitle display polling function, it should be frequently called when video is playing.
INTERFACE void msAPI_MpegSP_Main(U32 u32Stc);

// Get available dram address to store incoming spu element, it should be called before Push().
INTERFACE U32 msAPI_MpegSP_SpuQueue_GetSDRAMAddress( U16 u16Len );

// Push spu element to subtitle spu queue
INTERFACE BOOLEAN msAPI_MpegSP_SpuQueue_Push(EN_VDP_CODECID enSubType, U32 u32Address, U16 u16Len, U32 u32PTS, U32 u32Duration);

// Get current spu queue element count
INTERFACE U8 msAPI_MpegSP_SpuQueue_GetCount(void);

// Abandoned function, Set current video dimension
INTERFACE void msAPI_MpegSP_SetVideoDimension(U16 u16Width, U16 u16Height);

// Set current subtitle display window dimension
INTERFACE void msAPI_MpegSP_SetSubtitleDimension(U16 u16Width, U16 u16Height);

// Subtitle Palette settting, max palette number is 16
INTERFACE void msAPI_MpegSP_SetPalette(U32 *u32PaletteArray, U8 u8ArraySize);

// Get spu bitstream memory pool base address
INTERFACE U32 msAPI_MpegSP_SpuQueue_GetSDRAM_BaseAddress(void);

// Get spu bitstream memory pool size
INTERFACE U32 msAPI_MpegSP_SpuQueue_GetSDRAM_Size(void);

// Set subtitle position scale of video size, range: 0~100, the percentage of video size, 0xff means decided by header
INTERFACE void msAPI_MpegSP_SetPositionScale(U8 u8XPosScale, U8 u8YPosScale);

// Get subtitle position scale of video size, range: 0~100, the percentage of video size, 0xff means decided by header
INTERFACE void msAPI_MpegSP_GetPositionScale(U8 *u8XPosScale, U8 *u8YPosScale);

// Enable subtitle highlight
INTERFACE void msAPI_MpegSP_Enable_Highlight(BOOLEAN bHighLight);

// Draw subtitle highlight for rectangle x, y, width, height and palette
INTERFACE void msAPI_MpegSP_Draw_Highlight(U16 u16x, U16 u16y, U16 u16w, U16 u16h, U32 u32palette, U32 u32PTS);

// Clear subtitle highlight
INTERFACE void msAPI_MpegSP_Clear_Highlight(void);

// enable subtitle Gwin when subtitle not show completly
INTERFACE void  msAPI_MpegSP_Enable_Subtitle_Gwin(U32 u32STC);
//-------------------------------------------------------------------------------------------------

#undef INTERFACE

#endif // MSAPI_MPEG_SP_DECODER_H

