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

#ifndef MSAPI_OSD_RESOURCE_H
#define MSAPI_OSD_RESOURCE_H

/*************************************************************************************************************/

#include "datatype.h"
#include "Board.h"
#include "msAPI_Font.h"
#include "apiGFX.h"

#include "msAPI_BDMA.h"
#include "OSDcp_Bitmap_EnumIndex.h"

#define GE_DRIVER_TEST              0
#define SUPPORT_S4_OVERLAY_FONT     1

/********************************************************************************/
/*                                 Macro                                        */
/********************************************************************************/
#define BTN_TEXT_GAP                3

#define MAX_FONT                    30  //MAX_FONTTABLE_NUM_CC + MAX_FONTTABLE_NUM_OSD
#define MAX_BITMAP                  E_ZUI_BMP_MAX

#define INVALID_ADDR                0xffffffff

#define DEFAULT_BMP_FMT             BMP_FMT_ARGB1555

#define XD2PHY(xadr)                ((U32)(xadr))
#ifndef MIU_ALIGN_UNIT
#define MIU_ALIGN_UNIT              (8)
#endif
#ifndef MAU_MIU1_BASE
#define MAU_MIU1_BASE               (0x8000000)
#endif

/********************************************************************************/
/*                                 Enum                                         */
/********************************************************************************/
// return code
/// OSD RESOURCE API return value
typedef enum
{
    OSDSRC_SUCCESS                     = 0,
    OSDSRC_FAIL                        ,
    OSDSRC_NON_ALIGN_ADDRESS           ,
    OSDSRC_NON_ALIGN_PITCH             ,

    OSDSRC_INVALID_BUFF_INFO           ,
    OSDSRC_INVALID_FONT_HANDLE,
    OSDSRC_INVALID_BMP_HANDLE,
    OSDSRC_INVALID_PARAMETERS,
} OSDSRC_Result;

typedef enum
{
    OSDSRC_CHAR_IDX_1BYTE,
    OSDSRC_CHAR_IDX_2BYTE
} EN_OSDSRC_CHAR_IDX_LENGTH;

typedef enum
{
    EN_OSDSRC_ALIGNMENT_DEFAULT,           ///< Alignment default
    EN_OSDSRC_ALIGNMENT_LEFT,              ///< Alignment left
    EN_OSDSRC_ALIGNMENT_RIGHT,             ///< Alignment right
    EN_OSDSRC_ALIGNMENT_CENTER             ///< Alignment center
} EN_OSDSRC_ALIGNMENT_TYPE;

typedef enum
{
    EN_OSDSRC_STRING_ENDING_NONE,
    EN_OSDSRC_STRING_ENDING_1_DOT,
    EN_OSDSRC_STRING_ENDING_2_DOT,
    EN_OSDSRC_STRING_ENDING_3_DOT,
} EN_OSDSRC_STRING_ENDING_TYPE;

#if 1 // Refine by Daniel

/// font mode I1
#define BMP_FMT_I1          GFX_FMT_I1 // E_MS_FMT_I1,//0x0,
/// font mode I2
#define BMP_FMT_I2          GFX_FMT_I2 // E_MS_FMT_I2//0x1,
/// font mode I4
#define BMP_FMT_I4          GFX_FMT_I4 //E_MS_FMT_I4//0x2,
/// color format palette 256(I8)
#define BMP_FMT_I8          GFX_FMT_I8 // E_MS_FMT_I8, //0x4,
/// color format RGB565
//BMP_FMT_RGB565      = 0x8,
/// color format ORGB1555
#define BMP_FMT_ARGB1555    GFX_FMT_ARGB1555 // E_MS_FMT_ARGB1555 0x9,
/// color format ARGB4444
/// color format ARGB8888
//BMP_FMT_ARGB8888    = 0xf

#define BMP_Buffer_Format   GFX_Buffer_Format

#else
// GE buffer format
typedef enum
{
    /// font mode I1
    BMP_FMT_I1          = 0x0,
    /// font mode I2
    BMP_FMT_I2          = 0x1,
    /// font mode I4
    BMP_FMT_I4          = 0x2,
    /// color format palette 256(I8)
    BMP_FMT_I8          = 0x4,
    /// color format blinking display
    BMP_FMT_FaBaFgBg2266  = 0x6,
    /// color format blinking display
    BMP_FMT_1ABFgBg12355  = 0x7,
    /// color format RGB565
    BMP_FMT_RGB565      = 0x8,
    /// color format ORGB1555
    BMP_FMT_ARGB1555    = 0x9,
    /// color format ARGB4444
    BMP_FMT_ARGB4444    = 0xa,
    /// color format for blinking display (will be obsoleted)
    BMP_FMT_1BAAFGBG123433= 0xb,
    /// color format YUV422
    BMP_FMT_YUV422       = 0xe,
    /// color format ARGB8888
    BMP_FMT_ARGB8888    = 0xf
} BMP_Buffer_Format;
#endif

//For multi bitmap resources
typedef enum
{
    E_RES_GROUP_1ST,
    E_RES_GROUP_MAX,
} E_RES_GROUP;

#if (SUPPORT_S4_OVERLAY_FONT)
typedef struct
{
    S8 s8Xoffset;         ///
    S8 s8Yoffset;
}GLYPH_OVERLAP_INFO;
#endif

/// Glyph display information
typedef struct
{
    U8  u8X0;               ///< Left position to display
    U8  u8Width;            ///< Width of the glyph to display
    U16 u16Index;           ///< Glyph index in the font table
    #if (SUPPORT_S4_OVERLAY_FONT)
    GLYPH_OVERLAP_INFO overlap_info;
    #endif
} GLYPH_DISP_INFO;

/// Glyph display information
typedef struct
{
    U8  u8X0;               ///< Left position to display
    U8  u8Width;            ///< Width of the glyph to display
    U16 u16Index;           ///< Glyph index in the font table
    #if (SUPPORT_S4_OVERLAY_FONT)
    GLYPH_OVERLAP_INFO overlap_info;
    #endif
} OSDSRC_GLYPH_DISP_INFO;


/// Bounding box (BBox) of a glyph
typedef struct
{
    U8  u8X0;       ///< Position of the left edge of the bounding box
    U8  u8Width;    ///< Width of the bounding box
    U8  u8Y0;       ///< Position of the top edge of the bounding box
    U8  u8Height;   ///< Height of the bounding box
} __attribute__((__packed__)) OSDSRC_GLYPH_BBOX;

/// X-direction information of the bounding box of a glyph
typedef struct
{
    U8  u8X0;       ///< Position of the left edge of the bounding box
    U8  u8Width;    ///< Width of the bounding box
} __attribute__((__packed__)) OSDSRC_GLYPH_BBOX_X;

/// Y-direction information of the bounding box of a glyph
typedef struct
{
    U8  u8Y0;       ///< Position of the top edge of the bounding box
    U8  u8Height;   ///< Height of the bounding box
} __attribute__((__packed__)) OSDSRC_GLYPH_BBOX_Y;




typedef struct
{
    U16  u16StartCode;      ///< Start code of this block
    U16  u16EndCode;        ///< End code of this block
    U16  u16StartIndex;     ///< Glyph start index of this block
} __attribute__((__packed__)) CHAR_CODEMAP_BLOCK;



/// Define font table information
typedef struct
{
    U32 start_addr;         ///< start address of glyph data. For the use of reload font.
    U32 glyph_addr;         ///< address of glyph data
    U32 codemap_addr;       ///< address of codemap block data. Each codemap block is a tuple of (start code, end code, glyph start index)
    U16 char_num;           ///< Character number
    U16 codemap_block_num;  ///< number of codemap block.
    U8  width;              ///< font size: width
    U8  pitch;              ///< pitch
    U8  hw_pitch;           ///< pitch
    U8  height;             ///< font size: height
    U8  bpp;                ///< bits per pixel: I1 and I2 are currently supported.
    U32 bbox_addr;            ///< glyph bounding box address. BBox is in tuple of (x, width, y, height).
    U16 char_glyph_bytes;   ///< Size of each character glyph including possible paddings. Value 0 indicates to be calculated by driver.
    U8  memory_type;        ///< Memory type: MIU_FLASH and MIU_SDRAM
    BMP_Buffer_Format fmt;
    U32 inUsed;
} OSD_RESOURCE_FONT_INFO;

// GE buffer format
typedef enum
{
    /// font mode I1
    DMA_GE_FMT_I1          = 0x0,
    /// font mode I2
    DMA_GE_FMT_I2          = 0x1,
    /// font mode I4
    DMA_GE_FMT_I4          = 0x2,
    /// color format palette 256(I8)
    DMA_GE_FMT_I8          = 0x4,
    /// color format blinking display
    DMA_GE_FMT_FaBaFgBg2266  = 0x6,
    /// color format blinking display
    DMA_GE_FMT_1ABFgBg12355  = 0x7,
    /// color format RGB565
    DMA_GE_FMT_RGB565      = 0x8,
    /// color format ORGB1555
    DMA_GE_FMT_ARGB1555    = 0x9,
    /// color format ARGB4444
    DMA_GE_FMT_ARGB4444    = 0xa,
    /// color format for blinking display (will be obsoleted)
    DMA_GE_FMT_1BAAFGBG123433= 0xb,
    /// color format YUV422
    DMA_GE_FMT_YUV422       = 0xe,
    /// color format ARGB8888
    DMA_GE_FMT_ARGB8888    = 0xf
}DMA_GE_Buffer_Format;


// Bitmap information
typedef struct
{
    U32 addr;         // flat address of whole memory map
    U32 size;
    U8 dstloc;        // flash, sram or sdram
    U16 width;
    U16 height;
    U16 pitch;
    DMA_GE_Buffer_Format fmt;
} Bitmap_Info;


// Font table information
typedef struct
{
    U32 start_addr;         ///< start address of glyph data. For the use of reload font.
    U32 glyph_addr;         ///< address of glyph data
    U32 codemap_addr;       ///< address of codemap block data. Each codemap block is a tuple of (start code, end code, glyph start index)
    U16 char_num;           ///< Character number
    U16 codemap_block_num;  ///< number of codemap block.
    U8  width;              ///< font size: width
    U8  pitch;              ///< pitch
    U8  hw_pitch;           ///< pitch
    U8  height;             ///< font size: height
    U32 bbox_addr;          ///< glyph bounding box address. BBox is in tuple of (x, width, y, height).
    U16 char_glyph_bytes;   ///< Size of each character glyph including possible paddings. Value 0 indicates to be calculated by driver.
    U8  memory_type;        ///< Memory type: MIU_FLASH and MIU_SDRAM
    U8  bpp;                ///< bits per pixel: I1 and I2 are currently supported.
} FONT_INFO;

//=============================================================================
// Bitmap information
//=============================================================================
typedef struct
{
    U32 addr;               // flat address of whole memory map
    U32 len;
    U16 pitch;
    U16 height;
    U16 width;
    U8  fmt;
    U8  inUsed;
} OSD_RESOURCE_BITMAP_INFO;

#ifdef MSAPI_OSD_RESOURCE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

// Functions
INTERFACE MS_U16 msAPI_OSD_RESOURCE_GetFontHeight(FONTHANDLE font_handle);
INTERFACE FONTHANDLE msAPI_OSD_RESOURCE_LoadFont (MS_U32 start_addr, MS_U32 glyph_addr, MS_U32 bbox_addr, MS_U32 codemap_addr, MS_U16 u16char_num, MS_U16 codemap_block_num, MS_U8 width, MS_U8 height, MS_U8 bpp, MS_U16 char_glyph_bytes, MS_U32 pitch, MEMTYPE memory_type);
INTERFACE FONTHANDLE msAPI_OSD_RESOURCE_LoadTTF(void);
INTERFACE OSDSRC_Result msAPI_OSD_RESOURCE_FreeFont(FONTHANDLE handle);
INTERFACE OSDSRC_Result msAPI_OSD_RESOURCE_GetFontInfo(FONTHANDLE handle, OSD_RESOURCE_FONT_INFO* pinfo);
INTERFACE OSDSRC_Result msAPI_OSD_RESOURCE_GetBitmapInfo(BMPHANDLE handle, OSD_RESOURCE_BITMAP_INFO* pinfo);
INTERFACE OSDSRC_Result msAPI_OSD_RESOURCE_GetBBox_X(FONTHANDLE handle, MS_U16 u16Unicode, OSDSRC_GLYPH_BBOX_X *pGlyphBBox_X);
INTERFACE MS_U16 msAPI_OSD_RESOURCE_UnicodeToIndex(FONTHANDLE handle, MS_U16 u16Unicode);
INTERFACE BMPHANDLE msAPI_OSD_RESOURCE_LoadBitmap(MS_U32 addr, MS_U32 len, MS_U32 width, MS_U32 height, BMP_Buffer_Format fmt);
INTERFACE OSDSRC_Result msAPI_OSD_RESOURCE_FreeBitmap(BMPHANDLE handle);
INTERFACE void msAPI_OSD_RESOURCE_GetGlyphDispInfo(FONTHANDLE handle, MS_U16 u16Unicode, OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo);

INTERFACE OSDSRC_Result MDrv_GE_GetFontInfo(FONTHANDLE handle, FONT_INFO* pinfo);

INTERFACE MS_U32 msAPI_OSD_RESOURCE_GetFontInfoGFX(FONTHANDLE handle, GFX_FontInfo* pinfo);
INTERFACE MS_U32 msAPI_OSD_RESOURCE_GetBitmapInfoGFX(BMPHANDLE handle, GFX_BitmapInfo* pinfo);
INTERFACE MS_U32 msAPI_OSD_RESOURCE_SetFBFmt(MS_U16 pitch,MS_U32 addr , MS_U16 fmt );
#if ((MARLON_SUPPORT_STR) &&(STR_ENABLE == ENABLE))
INTERFACE void msAPI_FONT_STANDBY_STRBackup(void);
INTERFACE void msAPI_FONT_ACon_STRBackup(void);
INTERFACE void msAPI_FONT_STRRecover(void);
#endif

#undef INTERFACE

// Optional special drawing function

#undef INTERFACE

// end Optional special drawing function


/*************************************************************************************************************/
#endif /* MSAPI_OSD_RESOURCE_H */

