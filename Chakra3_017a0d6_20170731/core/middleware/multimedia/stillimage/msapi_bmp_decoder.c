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
/// @file   msAPI_BMP_Decoder.c
/// @author MStar Semiconductor Inc.
/// @brief  API of BMP decoder
///////////////////////////////////////////////////////////////////////////////
#define _MSAPI_BMP_DECODER_C_

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
//#include "mm_common.h"           // Every source code should include this in the first line
#include <string.h>

// NOTE: DO NOT include "mapp_stillimage_sharememcfg.h" in decoder/encoder modules
// and make sure it be included in only one file, "msapi_stillimage.h"
#include "msapi_stillimage.h"
#include "msapi_stillimage_bm.h"
#include "msapi_bmp_decoder.h"

#include "msapi_stillimage_dlmalloc.h"

#include "math.h"

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
// SCAN_LINE_MARKER_NEEDED defines if scan line marker (0x00, 0x00) is needed or not for every row.
// If SCAN_LINE_MARKER_NEEDED is 1, then it will violate the rule stated in
// http://www.fileformat.info/format/bmp/. "If an end-of-scan-line marker is not present in the
// encoded data, then the pixels will automatically wrap from the end of one scan line to the start
// of the next."
// However, if SCAN_LINE_MARKER_NEEDED is 1, output of 4bpp-rle.bmp will "looked" as the one displayed
// by other window's tool (ACDsee, Photo Impact 10, etc.)
#define SCAN_LINE_MARKER_NEEDED 1
#define RLE_DEBUG   0

// OS2_V2_PALETTE_SIZE_IS_3 defines the size of palette entry size is 3 or 4. If it's 3, this
// definition should set to 1. In http://netghost.narod.ru/gff/graphics/summary/os2bmp.htm
// and http://www.fileformat.info/format/os2bmp/egff.htm, they state that os2/v2 BMPs should
// store 4 bytes of color (for Blue, Green, Red, Reserved respectively) in each palette entry.
// But the test file, 11Bbos20.bmp violates this rule. It is os2/v2 BMP file but has only
// 3 bytes for each palette entry. However, test4os2v2.bmp has 4 bytes for each palette entry.
#define OS2_V2_PALETTE_ENTRY_SIZE_IS_3 0

// DECODE_ALL_DATA_IMMEDIATELY defines if BMP task will decode all data before leaving BMP task.
// It should be enabled only for debugging purpose.
#define DECODE_ALL_DATA_IMMEDIATELY 0

#define BMP_ALIGNMENT   8

#define BMP_SIGNATURE   0X4D42 // "BM"

#define BMP_MS_V2_or_OS2_V1_HEADER_SIZE   12
#define BMP_MS_V3_HEADER_SIZE   40
#define BMP_MS_V4_HEADER_SIZE   108
#define BMP_MS_V5_HEADER_SIZE   124
#define BMP_OS2_V2_HEADER_SIZE  64

#define _1_BITS_PER_PIXEL   1
#define _4_BITS_PER_PIXEL   4
#define _8_BITS_PER_PIXEL   8
#define _16_BITS_PER_PIXEL  16
#define _24_BITS_PER_PIXEL  24
#define _32_BITS_PER_PIXEL  32

#define _3_BYTE_PALETTE 3
#define _4_BYTE_PALETTE 4

#define BYTES_PER_PIXEL(bits_per_pixel) (bits_per_pixel / 8)

#define BMP_MAX_PALETTE_SIZE    256 // 1 << _8_BITS_PER_PIXEL
#define SCAN_LINE_ALIGNMENT     4 // DWORD

#define VALID_BITS_PER_PIXEL(BitsPerPixel) \
        (BitsPerPixel == _1_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _4_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _8_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _16_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _24_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _32_BITS_PER_PIXEL ? TRUE : FALSE))))))

#define BMP_WITH_PALETTE(BitsPerPixel) \
        (BitsPerPixel == _1_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _4_BITS_PER_PIXEL ? TRUE : \
        (BitsPerPixel == _8_BITS_PER_PIXEL ? TRUE : FALSE)))

enum
{
    E_BMP_COMP_RGB          = 0,
    E_BMP_COMP_RLE8         = 1,
    E_BMP_COMP_RLE4         = 2,
    E_BMP_COMP_BIT_FIELD    = 3,
    E_BMP_COMP_JPEG         = 4,
    E_BMP_COMP_PNG          = 5,
} eBMPCompressionMethod;

#define SUPPORTTED_COMPRESSION(compression) \
        (compression == E_BMP_COMP_RGB ? TRUE : \
        (compression == E_BMP_COMP_RLE8 ? TRUE : \
        (compression == E_BMP_COMP_RLE4 ? TRUE : \
        (compression == E_BMP_COMP_BIT_FIELD ? TRUE : FALSE))))

#define RLE_ENCODED(compression) \
        (compression == E_BMP_COMP_RLE8 ? TRUE : \
        (compression == E_BMP_COMP_RLE4 ? TRUE : FALSE))

enum
{
    E_BMP_CS_CALIBRATED_RGB         = 0,
    E_BMP_CS_DEVICE_DEPENDENT_RGB   = 1,
    E_BMP_CS_DEVICE_DEPENDENT_CMYK  = 2,
    E_BMP_CS_PROFILE_LINKED         = 3,
    E_BMP_CS_PROFILE_EMBEDDED       = 4,
} eBMPColorSpaceType;

typedef struct BMPFileHeader
{
    U16 u16FileType;        // File type, always 4D42h ("BM")
    U32 u32FileSize;        // Size of the file in bytes
    U16 u16Reserved1;       // Always 0
    U16 u16Reserved2;       // Always 0
    U32 u32BitmapOffset;    // Starting position of image data in bytes from the beginning of the file
} stBMPFileHeader, *pstBMPFileHeader;
#define BMP_FILE_HEADER_SIZE    14 // can't use sizeof(stBMPFileHeader) because of some 32-bit CPU.

#define RLE_MARKER_PREFIX   0x00
#define RLE_MARKER_END_SL   0x00 // End of Scan-Line
#define RLE_MARKER_END_RLE  0x01 // End of RLE
#define RLE_MARKER_VECTOR   0x02 // Run Offset, next 2 bytes indicate X and Y offset

#define CALC_BIT_SHIFT(mask, result)    \
        while (!(mask & 0x1))           \
        {                               \
            result++;                   \
            mask >>= 1;                 \
        }

typedef union BMPInfoHeader
{
    struct
    {
        U32 u32Size;    // Size of this header in bytes
    } COMMON;

    struct
    {
        U32 u32Size;            // Size of this header in bytes
        S16 s16Width;           // Image width in pixels
        S16 s16Height;          // Image height in pixels
        U16 u16Planes;          // Number of color planes
        U16 u16BitsPerPixel;    // Number of bits per pixel
    } MS_V2;

    struct
    {
        U32 u32Size;            // Size of this header in bytes
        U16 u16Width;           // Image width in pixels
        U16 u16Height;          // Image height in pixels
        U16 u16Planes;          // Number of color planes
        U16 u16BitsPerPixel;    // Number of bits per pixel
    } OS2_V1;

    struct
    {
        U32 u32Size;            // Size of this header in bytes
        S32 s32Width;           // Image width in pixels
        S32 s32Height;          // Image height in pixels
        U16 u16Planes;          // Number of color planes
        U16 u16BitsPerPixel;    // Number of bits per pixel
        U32 u32Compression;     // Compression methods used
        U32 u32ImageSize;       // Size of bitmap in bytes
        U32 u32HorzResolution;  // Horizontal resolution in pixels per meter
        U32 u32VertResolution;  // Vertical resolution in pixels per meter
        U32 u32ColorsUsed;      // Number of colors in the image
        U32 u32ColorsImportant; // Minimum number of important colors
    } MS_V3;

    struct
    {
        U32 u32Size;            // Size of this header in bytes
        S32 s32Width;           // Image width in pixels
        S32 s32Height;          // Image height in pixels
        U16 u16Planes;          // Number of color planes
        U16 u16BitsPerPixel;    // Number of bits per pixel
        U32 u32Compression;     // Compression methods used
        U32 u32ImageSize;       // Size of bitmap in bytes
        U32 u32HorzResolution;  // Horizontal resolution in pixels per meter
        U32 u32VertResolution;  // Vertical resolution in pixels per meter
        U32 u32ColorsUsed;      // Number of colors in the image
        U32 u32ColorsImportant; // Minimum number of important colors

        U16 u16ResolutionUnit;      // Type of units used to measure resolution
        U16 u16Reserved;            // reserved
        U16 u16RecordingAlgorithm;  // Recording algorithm
        U16 u16HalftoningAlgorithm; // Halftoning algorithm used
        U32 u32Size1;               // Size 1, reserved for halftoning algorithm use
        U32 u32Size2;               // Size 2, reserved for halftoning algorithm use
        U32 u32ColorEnding;         // Color encoding, color model used in bitmap
        U32 u32Identifier;          // Identifier, reserved for application use
    } OS2_V2;

    struct
    {
        U32 u32Size;            // Size of this header in bytes
        S32 s32Width;           // Image width in pixels
        S32 s32Height;          // Image height in pixels
        U16 u16Planes;          // Number of color planes
        U16 u16BitsPerPixel;    // Number of bits per pixel
        U32 u32Compression;     // Compression methods used
        U32 u32ImageSize;       // Size of bitmap in bytes
        U32 u32HorzResolution;  // Horizontal resolution in pixels per meter
        U32 u32VertResolution;  // Vertical resolution in pixels per meter
        U32 u32ColorsUsed;      // Number of colors in the image
        U32 u32ColorsImportant; // Minimum number of important colors

        U32 u32RedMask;         // Mask identifying bits of red component
        U32 u32GreenMask;       // Mask identifying bits of green component
        U32 u32BlueMask;        // Mask identifying bits of blue component
        U32 u32AlphaMask;       // Mask identifying bits of alpha component
        U32 u32CSType;          // Color space type
        S32 s32RedX;            // X coordinate of red endpoint
        S32 s32RedY;            // Y coordinate of red endpoint
        S32 s32RedZ;            // Z coordinate of red endpoint
        S32 s32GreenX;          // X coordinate of green endpoint
        S32 s32GreenY;          // Y coordinate of green endpoint
        S32 s32GreenZ;          // Z coordinate of green endpoint
        S32 s32BlueX;           // X coordinate of blue endpoint
        S32 s32BlueY;           // Y coordinate of blue endpoint
        S32 s32BlueZ;           // Z coordinate of blue endpoint
        U32 u32GammaRed;        // Gamma red coordinate scale value
        U32 u32GammaGreen;      // Gamma green coordinate scale value
        U32 u32GammaBlue;       // Gamma blue coordinate scale value
    } MS_V4;

    struct
    {
        U32 u32Size;            // Size of this header in bytes
        S32 s32Width;           // Image width in pixels
        S32 s32Height;          // Image height in pixels
        U16 u16Planes;          // Number of color planes
        U16 u16BitsPerPixel;    // Number of bits per pixel
        U32 u32Compression;     // Compression methods used
        U32 u32ImageSize;       // Size of bitmap in bytes
        U32 u32HorzResolution;  // Horizontal resolution in pixels per meter
        U32 u32VertResolution;  // Vertical resolution in pixels per meter
        U32 u32ColorsUsed;      // Number of colors in the image
        U32 u32ColorsImportant; // Minimum number of important colors

        U32 u32RedMask;         // Mask identifying bits of red component
        U32 u32GreenMask;       // Mask identifying bits of green component
        U32 u32BlueMask;        // Mask identifying bits of blue component
        U32 u32AlphaMask;       // Mask identifying bits of alpha component
        U32 u32CSType;          // Color space type
        S32 s32RedX;            // X coordinate of red endpoint
        S32 s32RedY;            // Y coordinate of red endpoint
        S32 s32RedZ;            // Z coordinate of red endpoint
        S32 s32GreenX;          // X coordinate of green endpoint
        S32 s32GreenY;          // Y coordinate of green endpoint
        S32 s32GreenZ;          // Z coordinate of green endpoint
        S32 s32BlueX;           // X coordinate of blue endpoint
        S32 s32BlueY;           // Y coordinate of blue endpoint
        S32 s32BlueZ;           // Z coordinate of blue endpoint
        U32 u32GammaRed;        // Gamma red coordinate scale value
        U32 u32GammaGreen;      // Gamma green coordinate scale value
        U32 u32GammaBlue;       // Gamma blue coordinate scale value

        U32 u32Intent;          // Rendering intent for bitmap
        U32 u32ProfileData;     // Offset to profile data
        U32 u32ProfileSize;     // Size of embedded profile data
        U32 u32Reserved;        // Should be zero
    } MS_V5;
} stBMPInfoHeader, *pstBMPInfoHeader;

typedef struct
{
    U8 u8Blue;      // Blue component
    U8 u8Green;     // Green component
    U8 u8Red;       // Red component
    U8 u8Alpha;     // Alpha component
} ST_PIXEL, stPixel_ARGB8888;

typedef struct
{
    U32 u32Red;     // Red
    U32 u32Green;   // Green
    U32 u32Blue;    // Blue
    U32 u32Alpha;   // Alpha
} stPixel_Mask;

typedef enum
{
    E_BMP_ARGB8888  = 0,
} E_BMP_OUTPUT_FORMAT;

typedef enum
{
    E_DECODER_STANDBY           = 0,
    E_DECODER_DECODING          = 1,

    E_DECODER_STOP_NO_DATA      = 10,
    E_DECODER_STOP_ASKED        = 11,

    E_DECODER_ERR_WRONG_STATUS  = 20,
    E_DECODER_ERR_COMPRESSION   = 21,
    E_DECODER_ERR_CORRUPT_FILE  = 22,
} E_BMP_DECODER_STATUS;

typedef struct
{
    U32 u32FileSize;
    U32 u32FirstPixelPos;   // the offset of 1st pixel from the beginning of the file

    S32 s32Width;           // Image width in pixels
    S32 s32Height;          // Image height in pixels
    U16 u16BitsPerPixel;    // Number of bits per pixel
    U32 u32Compression;     // Compression methods used

    ST_PIXEL *pstPalette;

    stPixel_Mask stPixelMask;

    ST_PIXEL stPixelRightShift;
    ST_PIXEL stPixelOutputShift; // the shift when output pixel data, >= 0 means right shift and < 0 means left shift

    BOOL bTopDown;
    BOOL bWithPalette;
    BOOL bWithMask;
    BOOL bRLEEncoded;
    U8 u8MinByteToRead; // the min size to read for processing pixels
    U8 u8PixelPerByte;  // how many pixels/byte if u16BitsPerPixel is 1, 4 or 8

    E_BMP_DECODER_STATUS eDecoderStatus;    // the status of decoder

    U32 u32RowProcessed;    // how many rows are decoded
    U32 u32PixelProcessed;  // how many pixels are decoded of current row

#if SCAN_LINE_MARKER_NEEDED
    BOOL bOutOfRowWarning;  // a warning message flag
#endif //#if SCAN_LINE_MARKER_NEEDED

    S32 s32AlignedWidth;    // the alignment of image width after scale down factor is calculated

    U8 u8Factor;
    U8 u8OutputWidthAlighment;    // how many bytes alignment at the width

    S32 s32AlignedOutputWidth;
    S32 s32OutputWidth;
    S32 s32OutputHeight;

    E_BMP_OUTPUT_FORMAT eOutputFormat;
    U8 u8PixelOutputSize;   // the size of each output pixel

    U8 *pu8OutputBuffer;
    U32 u32OutputRows;
    U32 u32BytePerOutputRow;

    // Following variables are relative to transitional buffer
    // This buffer is needed because we need to down scale the
    // original image to fit into the output buffer assigned.
    U8 *pu8TransBuff_Addr;
    U32 u32TransBuff_Rows;
    U32 u32TransBuff_PixelInCurrRow;
    U8 *pu8TransBuff_NextPixelPos;
} stBMP;

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define BMP_DBG(x)             //x
#define BMP_INFO(x)            //x
#define BMP_INFO_MUST(x)       //x
#define BMP_ERR(x)             //x

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
static stBMP stBMPInfo;

static stPixel_Mask stBmpBackGroundColor; // the background color

//------------------------------------------------------------------------------
// Local Function Prototypes
//------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_BmpDecoder_ReadHeader(void);
EN_STILLIMAGE_RET msAPI_BmpDecoder_Decode(void);
EN_STILLIMAGE_RET msAPI_BmpDecoder_Stop(void);

static void _msAPI_BmpDecoder_Reset(void);
static void _msAPI_BmpDecoder_DecodeRLE(U32 u32UnProcessData);
static void _msAPI_BmpDecoder_DecodeRGB(U32 u32UnProcessData);
static void _msAPI_BmpDecoder_OutputPixel(stPixel_Mask *pstPixel);
static void _msAPI_BmpDecoder_OutputRow(void);
static void _msAPI_BmpDecoder_FreeResource(void);

//------------------------------------------------------------------------------
// Global Function Implementation
//------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_BmpDecoder_Probe(void)
{
    stBMPFileHeader stFileHeader;

    // Initialize variable
    _msAPI_BmpDecoder_Reset();

    msAPI_StillImage_BMFile_Seek(0, E_BM_FILEPOS_SEEK_SET);
    msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());

    stFileHeader.u16FileType = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
    stFileHeader.u32FileSize = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
    stFileHeader.u16Reserved1 = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
    stFileHeader.u16Reserved2 = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
    stFileHeader.u32BitmapOffset = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);

    stBMPInfo.u32FirstPixelPos = stFileHeader.u32BitmapOffset;
    if ((U32)msAPI_StillImage_BMFile_Size() == DATA_SIZE_UNKNOWN)
    {
        if (stFileHeader.u32FileSize > BMP_FILE_HEADER_SIZE)
        {
            stBMPInfo.u32FileSize = BMP_FILE_HEADER_SIZE;
        }
        else
        {
            // TODO: what to do?
            stBMPInfo.u32FileSize = (U32)msAPI_StillImage_BMFile_Size();
        }
    }
    else
    {
        stBMPInfo.u32FileSize = (U32)msAPI_StillImage_BMFile_Size();
    }

    if (stFileHeader.u16FileType != BMP_SIGNATURE)
    {
        BMP_ERR(printf("[BMP] Not BMP, %04x, %04x\n", stFileHeader.u16FileType, BMP_SIGNATURE));
        return E_STILLIMAGE_RET_FAIL;
    }

    g_stStillImage.pfStillImage_ReadHeader = msAPI_BmpDecoder_ReadHeader;
    g_stStillImage.pfStillImage_Task = msAPI_BmpDecoder_Decode;
    g_stStillImage.pfStillImage_Stop = msAPI_BmpDecoder_Stop;

    return E_STILLIMAGE_RET_OK;
}

EN_STILLIMAGE_RET msAPI_BmpDecoder_ReadHeader(void)
{
    stBMPInfoHeader stInfoHeader;
    ST_PIXEL *pstPalette;
    stPixel_Mask *pstPixelMask = &stBMPInfo.stPixelMask;
    U16 u16PaletteIdx, u16Palettes;
    U64 u64FilePos;
    U32 u32OutputBuffLen;

    if (stBMPInfo.eDecoderStatus != E_DECODER_STANDBY)
    {
        BMP_ERR(printf("[BMP] Header parsing, wrong status (%d)\n", stBMPInfo.eDecoderStatus));
        g_stStillImage.enError = E_STILLIMAGE_BMP_WRONG_STATE;
        return E_STILLIMAGE_RET_FAIL;
    }

    stBMPInfo.pstPalette = (ST_PIXEL *)msAPI_StillImage_Dlmalloc_Malloc(sizeof(ST_PIXEL) * BMP_MAX_PALETTE_SIZE);
    if (stBMPInfo.pstPalette == NULL)
    {
        BMP_ERR(printf("[BMP] No space for palettes\n"));
        g_stStillImage.enError = E_STILLIMAGE_BMP_PALETTE_MEM_ERR;
        return E_STILLIMAGE_RET_FAIL;
    }
    pstPalette = stBMPInfo.pstPalette;
    for (u16PaletteIdx = 0; u16PaletteIdx < BMP_MAX_PALETTE_SIZE; u16PaletteIdx++)
    {
        pstPalette[u16PaletteIdx].u8Blue    = (U8)stBmpBackGroundColor.u32Blue;
        pstPalette[u16PaletteIdx].u8Green   = (U8)stBmpBackGroundColor.u32Green;
        pstPalette[u16PaletteIdx].u8Red     = (U8)stBmpBackGroundColor.u32Red;
        pstPalette[u16PaletteIdx].u8Alpha   = (U8)stBmpBackGroundColor.u32Alpha;
    }

    msAPI_StillImage_BMFile_Seek(BMP_FILE_HEADER_SIZE, E_BM_FILEPOS_SEEK_SET);
    msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());

    stInfoHeader.COMMON.u32Size = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
    switch (stInfoHeader.COMMON.u32Size)
    {
        case BMP_MS_V2_or_OS2_V1_HEADER_SIZE:
            stInfoHeader.MS_V2.s16Width = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
            stInfoHeader.MS_V2.s16Height = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
            stInfoHeader.MS_V2.u16Planes = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
            stInfoHeader.MS_V2.u16BitsPerPixel = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);

            stBMPInfo.s32Width = stInfoHeader.MS_V2.s16Width;
            stBMPInfo.s32Height = stInfoHeader.MS_V2.s16Height;
            stBMPInfo.u16BitsPerPixel = stInfoHeader.MS_V2.u16BitsPerPixel;
            stBMPInfo.u32Compression = E_BMP_COMP_RGB;
            stBMPInfo.bWithPalette = BMP_WITH_PALETTE(stInfoHeader.MS_V2.u16BitsPerPixel);

            u16Palettes = (1 << stInfoHeader.MS_V2.u16BitsPerPixel);
            u64FilePos = msAPI_StillImage_BMFile_Tell();
            if (stBMPInfo.bWithPalette)
            {
                for (u16PaletteIdx = 0;
                        (u16PaletteIdx < u16Palettes) && (u32u64_0(u64FilePos) < stBMPInfo.u32FirstPixelPos);
                        u16PaletteIdx++)
                {
                    pstPalette[u16PaletteIdx].u8Blue = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                    pstPalette[u16PaletteIdx].u8Green = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                    pstPalette[u16PaletteIdx].u8Red = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                    pstPalette[u16PaletteIdx].u8Alpha = 0x0;
                    u64FilePos += _3_BYTE_PALETTE;
                }

                u16Palettes = u16PaletteIdx;
            }

            BMP_INFO_MUST(printf("[BMP] MS V2/OS2 V1\n"));
            BMP_INFO_MUST(printf("\tWidth: %d (%04x)\n", stInfoHeader.MS_V2.s16Width, stInfoHeader.MS_V2.s16Width));
            BMP_INFO_MUST(printf("\tHeight: %d (%04x)\n", stInfoHeader.MS_V2.s16Height, stInfoHeader.MS_V2.s16Height));
            BMP_INFO(printf("\tPlanes: %d\n", stInfoHeader.MS_V2.u16Planes));
            BMP_INFO_MUST(printf("\tBits/Pixel: %d\n", stInfoHeader.MS_V2.u16BitsPerPixel));

            if (stBMPInfo.bWithPalette)
            {
                for (u16PaletteIdx = 0; u16PaletteIdx < u16Palettes; u16PaletteIdx++)
                {
                    BMP_INFO(printf("\tPalette [%03d], B: (%02x), G: (%02x), R: (%02x)\n",
                            u16PaletteIdx,
                            pstPalette[u16PaletteIdx].u8Blue,
                            pstPalette[u16PaletteIdx].u8Green,
                            pstPalette[u16PaletteIdx].u8Red));
                }
            }
            BMP_INFO_MUST(printf("\tPalette Cnt: %d\n", u16Palettes));
            break;

        case BMP_MS_V3_HEADER_SIZE:
        case BMP_MS_V4_HEADER_SIZE:
        case BMP_MS_V5_HEADER_SIZE:
        case BMP_OS2_V2_HEADER_SIZE:
            stInfoHeader.MS_V3.s32Width = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.s32Height = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.u16Planes = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
            stInfoHeader.MS_V3.u16BitsPerPixel = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
            stInfoHeader.MS_V3.u32Compression = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.u32ImageSize = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.u32HorzResolution = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.u32VertResolution = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.u32ColorsUsed = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V3.u32ColorsImportant = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);

            stBMPInfo.s32Width = stInfoHeader.MS_V3.s32Width;
            stBMPInfo.s32Height = stInfoHeader.MS_V3.s32Height;
            stBMPInfo.u16BitsPerPixel = stInfoHeader.MS_V3.u16BitsPerPixel;
            stBMPInfo.u32Compression = stInfoHeader.MS_V3.u32Compression;
            stBMPInfo.bRLEEncoded = RLE_ENCODED(stInfoHeader.MS_V3.u32Compression);
            stBMPInfo.bWithPalette = BMP_WITH_PALETTE(stInfoHeader.MS_V3.u16BitsPerPixel);

            BMP_INFO_MUST(printf("[BMP] MS V3(%d)/V4(%d)/V5(%d) or OS2 V2(%d). %d\n",
                    BMP_MS_V3_HEADER_SIZE,
                    BMP_MS_V4_HEADER_SIZE,
                    BMP_MS_V5_HEADER_SIZE,
                    BMP_OS2_V2_HEADER_SIZE,
                    stInfoHeader.COMMON.u32Size));
            BMP_INFO_MUST(printf("\tWidth: %d\n", stInfoHeader.MS_V3.s32Width));
            BMP_INFO_MUST(printf("\tHeight: %d\n", stInfoHeader.MS_V3.s32Height));
            BMP_INFO(printf("\tPlanes: %d\n", stInfoHeader.MS_V3.u16Planes));
            BMP_INFO_MUST(printf("\tBits/Pixel: %d\n", stInfoHeader.MS_V3.u16BitsPerPixel));
            BMP_INFO_MUST(printf("\tCompression: %d, RLE: %d\n", stInfoHeader.MS_V3.u32Compression, stBMPInfo.bRLEEncoded));
            BMP_INFO(printf("\tImageSize: %d\n", stInfoHeader.MS_V3.u32ImageSize));
            BMP_INFO(printf("\tH Resolution: %d\n", stInfoHeader.MS_V3.u32HorzResolution));
            BMP_INFO(printf("\tV Resolution: %d\n", stInfoHeader.MS_V3.u32VertResolution));
            BMP_INFO_MUST(printf("\tPalette #: %d\n", stInfoHeader.MS_V3.u32ColorsUsed));
            BMP_INFO(printf("\tImportant Color #: %d\n", stInfoHeader.MS_V3.u32ColorsImportant));

            if ((stInfoHeader.COMMON.u32Size == BMP_MS_V3_HEADER_SIZE)
                    || (stInfoHeader.COMMON.u32Size == BMP_OS2_V2_HEADER_SIZE))
            {
                if (stInfoHeader.COMMON.u32Size == BMP_OS2_V2_HEADER_SIZE)
                {
                    // OS2 V2
                    stInfoHeader.OS2_V2.u16ResolutionUnit = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
                    stInfoHeader.OS2_V2.u16Reserved = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
                    stInfoHeader.OS2_V2.u16RecordingAlgorithm = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
                    stInfoHeader.OS2_V2.u16HalftoningAlgorithm = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(2);
                    stInfoHeader.OS2_V2.u32Size1 = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
                    stInfoHeader.OS2_V2.u32Size2 = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
                    stInfoHeader.OS2_V2.u32ColorEnding = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
                    stInfoHeader.OS2_V2.u32Identifier = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);

                    BMP_INFO(printf("OS2 V2 Info ----------\n"));
                    BMP_INFO(printf("\tResolution Unit: %d\n", stInfoHeader.OS2_V2.u16ResolutionUnit));
                    BMP_INFO(printf("\tRecording Algorithm: %d\n", stInfoHeader.OS2_V2.u16RecordingAlgorithm));
                    BMP_INFO(printf("\tHalftoning Algorithm: %d\n", stInfoHeader.OS2_V2.u16HalftoningAlgorithm));
                    BMP_INFO(printf("\tSize1: %d\n", stInfoHeader.OS2_V2.u32Size1));
                    BMP_INFO(printf("\tSize2: %d\n", stInfoHeader.OS2_V2.u32Size2));
                    BMP_INFO(printf("\tColor Ending: %d\n", stInfoHeader.OS2_V2.u32ColorEnding));
                    BMP_INFO(printf("\tIdentifier: %d\n", stInfoHeader.OS2_V2.u32Identifier));
                }

                if (stInfoHeader.MS_V3.u32Compression == E_BMP_COMP_BIT_FIELD)
                {
                    pstPixelMask->u32Red = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
                    pstPixelMask->u32Green = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
                    pstPixelMask->u32Blue = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
                    pstPixelMask->u32Alpha = 0x0;
                    stBMPInfo.bWithMask = TRUE;

                    BMP_INFO_MUST(printf("\tV3 Mask, R: (%08x), G: (%08x), B: (%08x)\n",
                            pstPixelMask->u32Red,
                            pstPixelMask->u32Green,
                            pstPixelMask->u32Blue));
                }
                else if (stBMPInfo.bWithPalette)
                {
                    goto get_palette;
                }

                break;
            }

            // MS V4/V5
            stInfoHeader.MS_V4.u32RedMask = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32GreenMask = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32BlueMask = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32AlphaMask = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32CSType = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32RedX = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32RedY = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32RedZ = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32GreenX = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32GreenY = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32GreenZ = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32BlueX = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32BlueY = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.s32BlueZ = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32GammaRed = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32GammaGreen = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V4.u32GammaBlue = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);

            pstPixelMask->u32Red = stInfoHeader.MS_V4.u32RedMask;
            pstPixelMask->u32Green = stInfoHeader.MS_V4.u32GreenMask;
            pstPixelMask->u32Blue = stInfoHeader.MS_V4.u32BlueMask;
            pstPixelMask->u32Alpha = stInfoHeader.MS_V4.u32AlphaMask;
            stBMPInfo.bWithMask = TRUE;

            BMP_INFO(printf("MS M4/V5 Info --------_-\n"));
            BMP_INFO_MUST(printf("\tMask, R: (%08x), G: (%08x), B: (%08x), A: (%08x)\n",
                    pstPixelMask->u32Red,
                    pstPixelMask->u32Green,
                    pstPixelMask->u32Blue,
                    pstPixelMask->u32Alpha));

            BMP_INFO(printf("\tCS Type: %d\n", stInfoHeader.MS_V4.u32CSType));
            BMP_INFO(printf("\tRed X: %d\n", stInfoHeader.MS_V4.s32RedX));
            BMP_INFO(printf("\tRed Y: %d\n", stInfoHeader.MS_V4.s32RedY));
            BMP_INFO(printf("\tRed Z: %d\n", stInfoHeader.MS_V4.s32RedZ));
            BMP_INFO(printf("\tGreen X: %d\n", stInfoHeader.MS_V4.s32GreenX));
            BMP_INFO(printf("\tGreen Y: %d\n", stInfoHeader.MS_V4.s32GreenY));
            BMP_INFO(printf("\tGreen Z: %d\n", stInfoHeader.MS_V4.s32GreenZ));
            BMP_INFO(printf("\tBlue X: %d\n", stInfoHeader.MS_V4.s32BlueX));
            BMP_INFO(printf("\tBlue Y: %d\n", stInfoHeader.MS_V4.s32BlueY));
            BMP_INFO(printf("\tBlue Z: %d\n", stInfoHeader.MS_V4.s32BlueZ));
            BMP_INFO(printf("\tGamma Red: %d\n", stInfoHeader.MS_V4.u32GammaRed));
            BMP_INFO(printf("\tGamma Green: %d\n", stInfoHeader.MS_V4.u32GammaGreen));
            BMP_INFO(printf("\tGamma Blue: %d\n", stInfoHeader.MS_V4.u32GammaBlue));

            if (stInfoHeader.COMMON.u32Size == BMP_MS_V4_HEADER_SIZE)
            {
                if (stBMPInfo.bWithPalette)
                {
                    goto get_palette;
                }

                break;
            }

            // MS V5
            stInfoHeader.MS_V5.u32Intent = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V5.u32ProfileData = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V5.u32ProfileSize = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);
            stInfoHeader.MS_V5.u32Reserved = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(4);

            BMP_INFO(printf("MS V5 Info -------_--\n"));
            BMP_INFO(printf("\tIntent: %d\n", stInfoHeader.MS_V5.u32Intent));
            BMP_INFO(printf("\tProfile Data: %d\n", stInfoHeader.MS_V5.u32ProfileData + BMP_FILE_HEADER_SIZE));
            BMP_INFO(printf("\tProfile Size: %d\n", stInfoHeader.MS_V5.u32ProfileSize));

get_palette:
            u16Palettes = (1 << stInfoHeader.MS_V3.u16BitsPerPixel);
            u64FilePos = msAPI_StillImage_BMFile_Tell();
            for (u16PaletteIdx = 0;
                    (u16PaletteIdx < u16Palettes) && (u32u64_0(u64FilePos) < stBMPInfo.u32FirstPixelPos);
                    u16PaletteIdx++)
            {
                pstPalette[u16PaletteIdx].u8Blue = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                pstPalette[u16PaletteIdx].u8Green = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                pstPalette[u16PaletteIdx].u8Red = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                pstPalette[u16PaletteIdx].u8Alpha = 0x0;
#if OS2_V2_PALETTE_ENTRY_SIZE_IS_3
                if (stInfoHeader.COMMON.u32Size == BMP_OS2_V2_HEADER_SIZE)
                {
                    pstPalette[u16PaletteIdx].u8Alpha = 0;
                    u64FilePos += _3_BYTE_PALETTE;
                }
                else
#endif // #if OS2_V2_PALETTE_ENTRY_SIZE_IS_3
                {
                    pstPalette[u16PaletteIdx].u8Alpha = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                    u64FilePos += _4_BYTE_PALETTE;
                }

                BMP_INFO(printf("\tPalette [%03d], B: (%02x), G: (%02x), R: (%02x), Rev: (%02x)\n",
                        u16PaletteIdx,
                        pstPalette[u16PaletteIdx].u8Blue,
                        pstPalette[u16PaletteIdx].u8Green,
                        pstPalette[u16PaletteIdx].u8Red,
                        pstPalette[u16PaletteIdx].u8Alpha));
            }

            u16Palettes = u16PaletteIdx;
            BMP_INFO_MUST(printf("\tPalette Cnt: %d\n", u16Palettes));
            break;

        default:
            BMP_ERR(printf("[BMP] Un-supported BMP info size, %d\n", stInfoHeader.COMMON.u32Size));
            g_stStillImage.enError = E_STILLIMAGE_BMP_HEADER_SIZE_NOT_SUPPORT;
            goto fail;
    }

    if (stBMPInfo.s32Height < 0)
    {
        stBMPInfo.s32Height = -stBMPInfo.s32Height;
        stBMPInfo.bTopDown = TRUE;
    }

    if (stBMPInfo.s32Width < 0)
    {
        BMP_ERR(printf("[BMP] Wrong width, %d(0x%x)\n", stBMPInfo.s32Width, stBMPInfo.s32Width));
        goto fail;
    }

    if ((stBMPInfo.s32Width == 0) && (stBMPInfo.s32Height == 0))
    {
        BMP_ERR(printf("[BMP] Wrong resolution, %dx%d\n", stBMPInfo.s32Width, stBMPInfo.s32Height));
        g_stStillImage.enError = E_STILLIMAGE_BMP_WxH_0x0;
        goto fail;
    }

    if (!VALID_BITS_PER_PIXEL(stBMPInfo.u16BitsPerPixel))
    {
        BMP_ERR(printf("[BMP] Wrong Bits/Pixel, %d\n", stBMPInfo.u16BitsPerPixel));
        g_stStillImage.enError = E_STILLIMAGE_BMP_PIXEL_PER_BYTE_NOT_SUPPORT;
        goto fail;
    }

    if (!SUPPORTTED_COMPRESSION(stBMPInfo.u32Compression))
    {
        BMP_ERR(printf("[BMP] Un-supportted compression, %d\n", stBMPInfo.u32Compression));
        g_stStillImage.enError = E_STILLIMAGE_BMP_COMPRESSION_NOT_SUPPORT;
        goto fail;
    }

    // Input parameters adjustment
    // change _16_BITS_PER_PIXEL/_24_BITS_PER_PIXEL/_32_BITS_PER_PIXEL with E_BMP_COMP_RGB to E_BMP_COMP_BIT_FIELD
    if (stBMPInfo.u32Compression == E_BMP_COMP_RGB)
    {
        if (stBMPInfo.bWithMask == TRUE)
        {
            stBMPInfo.u32Compression = E_BMP_COMP_BIT_FIELD;
        }
        else
        {
            if (stBMPInfo.u16BitsPerPixel == _16_BITS_PER_PIXEL)
            {
                stBMPInfo.stPixelMask.u32Red    = 0x7c00;
                stBMPInfo.stPixelMask.u32Green  = 0x03e0;
                stBMPInfo.stPixelMask.u32Blue   = 0x001f;
                stBMPInfo.stPixelMask.u32Alpha  = 0x8000;
                stBMPInfo.u32Compression = E_BMP_COMP_BIT_FIELD;
            }
            else if ((stBMPInfo.u16BitsPerPixel == _24_BITS_PER_PIXEL)
                    || (stBMPInfo.u16BitsPerPixel == _32_BITS_PER_PIXEL))
            {
                stBMPInfo.stPixelMask.u32Red    = 0x00ff0000;
                stBMPInfo.stPixelMask.u32Green  = 0x0000ff00;
                stBMPInfo.stPixelMask.u32Blue   = 0x000000ff;
                stBMPInfo.stPixelMask.u32Alpha  = 0xff000000;
                stBMPInfo.u32Compression = E_BMP_COMP_BIT_FIELD;
            }
        }
    }

    // calculate how many right shifts are needed for each color when E_BMP_COMP_BIT_FIELD is used
    if (stBMPInfo.u32Compression == E_BMP_COMP_BIT_FIELD)
    {
        if ((stBMPInfo.u16BitsPerPixel == _16_BITS_PER_PIXEL)
                || (stBMPInfo.u16BitsPerPixel == _24_BITS_PER_PIXEL)
                || (stBMPInfo.u16BitsPerPixel == _32_BITS_PER_PIXEL))
        {
            U32 u32Mask;

            // Red
            u32Mask = stBMPInfo.stPixelMask.u32Red;
            stBMPInfo.stPixelRightShift.u8Red = 0;
            stBMPInfo.stPixelOutputShift.u8Red = 0;
            if (u32Mask)
            {
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelRightShift.u8Red);
                u32Mask += 1;
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelOutputShift.u8Red);
            }

            // Green
            u32Mask = stBMPInfo.stPixelMask.u32Green;
            stBMPInfo.stPixelRightShift.u8Green = 0;
            stBMPInfo.stPixelOutputShift.u8Green = 0;
            if (u32Mask)
            {
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelRightShift.u8Green);
                u32Mask += 1;
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelOutputShift.u8Green);
            }

            // Blue
            u32Mask = stBMPInfo.stPixelMask.u32Blue;
            stBMPInfo.stPixelRightShift.u8Blue = 0;
            stBMPInfo.stPixelOutputShift.u8Blue = 0;
            if (u32Mask)
            {
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelRightShift.u8Blue);
                u32Mask += 1;
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelOutputShift.u8Blue);
            }

            // Alpha
            u32Mask = stBMPInfo.stPixelMask.u32Alpha;
            stBMPInfo.stPixelRightShift.u8Alpha = 0;
            stBMPInfo.stPixelOutputShift.u8Alpha = 0;
            if (u32Mask)
            {
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelRightShift.u8Alpha);
                u32Mask += 1;
                CALC_BIT_SHIFT(u32Mask, stBMPInfo.stPixelOutputShift.u8Alpha);
            }
        }
        else
        {
            BMP_ERR(printf("[BMP] Wrong compression(%d) with Bits/Pixel(%d)\n", stBMPInfo.u32Compression, stBMPInfo.u16BitsPerPixel));
            goto fail;
        }
    }
    else
    {
        // when using palette, all output shift for each component is 8
        stBMPInfo.stPixelOutputShift.u8Alpha    = 8;
        stBMPInfo.stPixelOutputShift.u8Red      = 8;
        stBMPInfo.stPixelOutputShift.u8Green    = 8;
        stBMPInfo.stPixelOutputShift.u8Blue     = 8;
    }

    // calculate how many bytes to read for processing data
    // and how many pixels in a byte if bits/pixel is _1_BITS_PER_PIXEL/_4_BITS_PER_PIXEL/_8_BITS_PER_PIXEL
    switch (stBMPInfo.u16BitsPerPixel)
    {
        case _1_BITS_PER_PIXEL:
            // every row is 4-byte aligned, treat it as 1 atomic block when bits/pixel is _1_BITS_PER_PIXEL
            stBMPInfo.u8MinByteToRead = SCAN_LINE_ALIGNMENT;
            stBMPInfo.u8PixelPerByte = 8;
            break;

        case _4_BITS_PER_PIXEL:
            // every row is 4-byte aligned, treat it as 1 atomic block when bits/pixel is _4_BITS_PER_PIXEL
            stBMPInfo.u8MinByteToRead = SCAN_LINE_ALIGNMENT;
            stBMPInfo.u8PixelPerByte = 2;
            break;

        case _8_BITS_PER_PIXEL:
            // every row is 4-byte aligned, treat it as 1 atomic block when bits/pixel is _8_BITS_PER_PIXEL
            stBMPInfo.u8MinByteToRead = SCAN_LINE_ALIGNMENT;
            stBMPInfo.u8PixelPerByte = 1;
            break;

        case _16_BITS_PER_PIXEL:
            stBMPInfo.u8MinByteToRead = 2;
            break;

        case _24_BITS_PER_PIXEL:
            stBMPInfo.u8MinByteToRead = 3;
            break;

        case _32_BITS_PER_PIXEL:
            stBMPInfo.u8MinByteToRead = 4;
            break;

        default:
            break;
    }

    // setup output parameters
    switch (stBMPInfo.eOutputFormat)
    {
        default:
        case E_BMP_ARGB8888:
            // calculate how many right/left shifts are needed for output data
            stBMPInfo.stPixelOutputShift.u8Red      -= 8;
            stBMPInfo.stPixelOutputShift.u8Green    -= 8;
            stBMPInfo.stPixelOutputShift.u8Blue     -= 8;
            stBMPInfo.stPixelOutputShift.u8Alpha    -= 8;

            stBMPInfo.u8PixelOutputSize = 4;    // 4 bytes
            break;
    }

    stBMPInfo.pu8OutputBuffer = (U8 *)g_stStillImage.stInputCfgParams.u32OutputBuffAddr;
    if (stBMPInfo.pu8OutputBuffer == NULL)
    {
        BMP_ERR(printf("[BMP] No output buffer\n"));
        g_stStillImage.enError = E_STILLIMAGE_BMP_OUTPUT_BUFFER_NULL;
        goto fail;
    }

    // calculate scale down factor
    u32OutputBuffLen = _ALIGNMENT_(g_stStillImage.stInputCfgParams.u32BmpMaxWidth, stBMPInfo.u8OutputWidthAlighment)
            * g_stStillImage.stInputCfgParams.u32BmpMaxHeight * stBMPInfo.u8PixelOutputSize;
    u32OutputBuffLen = u32OutputBuffLen < g_stStillImage.stInputCfgParams.u32OutputBuffLen ?
            u32OutputBuffLen : g_stStillImage.stInputCfgParams.u32OutputBuffLen;

    for (stBMPInfo.u8Factor = 1; stBMPInfo.u8Factor <= BMP_MAX_SCALE_DOWN_FACTOR; stBMPInfo.u8Factor <<= 1)
    {
        stBMPInfo.s32OutputWidth = _ALIGNMENT_(stBMPInfo.s32Width, stBMPInfo.u8Factor) / stBMPInfo.u8Factor;
        stBMPInfo.s32OutputHeight = _ALIGNMENT_(stBMPInfo.s32Height, stBMPInfo.u8Factor) / stBMPInfo.u8Factor;
        stBMPInfo.s32AlignedOutputWidth = _ALIGNMENT_(stBMPInfo.s32OutputWidth, stBMPInfo.u8OutputWidthAlighment);

        if (((U32)stBMPInfo.s32AlignedOutputWidth * stBMPInfo.s32OutputHeight * stBMPInfo.u8PixelOutputSize)
                <= u32OutputBuffLen)
        {
            break;
        }
    }

    if (stBMPInfo.u8Factor > BMP_MAX_SCALE_DOWN_FACTOR)
    {
        BMP_ERR(printf("[BMP] Output buffer too small, size: %d, Image: %dx%d, Output: %d(%d)x%d\n",
                g_stStillImage.stInputCfgParams.u32OutputBuffLen,
                stBMPInfo.s32Width, stBMPInfo.s32Height,
                stBMPInfo.s32OutputWidth, stBMPInfo.s32AlignedOutputWidth, stBMPInfo.s32OutputHeight));
        g_stStillImage.enError = E_STILLIMAGE_BMP_SCALE_DOWN_FACTOR_NOT_SUPPORT;
        goto fail;
    }

    // misc
    stBMPInfo.s32AlignedWidth = stBMPInfo.s32AlignedOutputWidth * stBMPInfo.u8Factor;
    stBMPInfo.u32BytePerOutputRow = stBMPInfo.s32AlignedOutputWidth * stBMPInfo.u8PixelOutputSize;

    if (g_stStillImage.stInputCfgParams.bDecodeThumbnail == TRUE)
    {
        BMP_ERR(printf("[BMP] No thumbnail\n"));
        g_stStillImage.enError = E_STILLIMAGE_BMP_NO_THUMBNAIL;
        goto fail;
    }

    // allocate transitional buffer
    stBMPInfo.pu8TransBuff_Addr = (U8 *)msAPI_StillImage_Dlmalloc_Malloc(stBMPInfo.s32AlignedWidth * stBMPInfo.u8Factor * stBMPInfo.u8PixelOutputSize);
    if (stBMPInfo.pu8TransBuff_Addr == NULL)
    {
        BMP_ERR(printf("[BMP] No space for transitional buffer\n"));
        g_stStillImage.enError = E_STILLIMAGE_BMP_TRANSITIONAL_MEM_ERR;
        goto fail;
    }

    stBMPInfo.pu8TransBuff_NextPixelPos = stBMPInfo.pu8TransBuff_Addr;
    stBMPInfo.u32TransBuff_Rows = stBMPInfo.u32TransBuff_PixelInCurrRow = 0;

fail:
    // information about this image
    g_stStillImage.u32FirstPixelPos     = stBMPInfo.u32FirstPixelPos;
    g_stStillImage.u32OutputPitch       = (U32)stBMPInfo.s32AlignedOutputWidth;
    g_stStillImage.u32OutputWidth       = (U32)stBMPInfo.s32OutputWidth;
    g_stStillImage.u32OutputHeight      = (U32)stBMPInfo.s32OutputHeight;
    g_stStillImage.u32OutputSize        = (U32)(g_stStillImage.u32OutputPitch * g_stStillImage.u32OutputHeight * stBMPInfo.u8PixelOutputSize);
    g_stStillImage.u32ImageWidth        = (U32)stBMPInfo.s32Width;
    g_stStillImage.u32ImageHeight       = (U32)stBMPInfo.s32Height;
    g_stStillImage.bHasThumbnail        = FALSE;
    g_stStillImage.u8DownScaleFactor    = stBMPInfo.u8Factor;
    g_stStillImage.enOutputFormat       = E_STILLIMAGE_OUTPU_RAW_ARGB8888;
    g_stStillImage.bHasDateTime         = FALSE;
    g_stStillImage.enOrientation        = E_STILLIMAGE_ORIENT_UNDEFINE;

    if (g_stStillImage.enError == E_STILLIMAGE_ERR_NONE)
    {
        stBMPInfo.eDecoderStatus = E_DECODER_DECODING;
        return E_STILLIMAGE_RET_OK;
    }

    _msAPI_BmpDecoder_FreeResource();
    return E_STILLIMAGE_RET_FAIL;
}

EN_STILLIMAGE_RET msAPI_BmpDecoder_Decode(void)
{
    U64 u64UnProcessData;
    EN_STILLIMAGE_RET bRet = E_STILLIMAGE_RET_WORKING;
    U8 u8Loop = 0;

    //process more lines in every call msAPI_BmpDecoder_Decode to improve performance.
    while (stBMPInfo.eDecoderStatus == E_DECODER_DECODING && u8Loop++ < 32)
    {
    #if DECODE_ALL_DATA_IMMEDIATELY
    again:
    #endif //#if DECODE_ALL_DATA_IMMEDIATELY

        u64UnProcessData = stBMPInfo.u32FileSize - msAPI_StillImage_BMFile_Tell();

        if (u64UnProcessData == 0)
        {
            stBMPInfo.eDecoderStatus = E_DECODER_STOP_NO_DATA;
        }
        else if (u64UnProcessData < stBMPInfo.u8MinByteToRead)
        {
            stBMPInfo.eDecoderStatus = E_DECODER_ERR_CORRUPT_FILE;
        }
        else
        {
            if (stBMPInfo.bRLEEncoded)
            {
                _msAPI_BmpDecoder_DecodeRLE(u32u64_0(u64UnProcessData));
            }
            else
            {
                _msAPI_BmpDecoder_DecodeRGB(u32u64_0(u64UnProcessData));
            }

            msAPI_StillImage_BMBuffer_UpdateBase();
        }

        // check decode status
        switch (stBMPInfo.eDecoderStatus)
        {
            case E_DECODER_STANDBY:
                BMP_ERR(printf("[BMP] Decode, wrong status (%d)\n", stBMPInfo.eDecoderStatus));
                return E_STILLIMAGE_RET_FAIL;

            case E_DECODER_STOP_NO_DATA:
            case E_DECODER_STOP_ASKED:
            case E_DECODER_ERR_CORRUPT_FILE:
                bRet = E_STILLIMAGE_RET_DONE;
                break;

            case E_DECODER_ERR_COMPRESSION:
                bRet = E_STILLIMAGE_RET_FAIL;
                g_stStillImage.enError = E_STILLIMAGE_BMP_DECOMPRESSION_ERROR;
                break;

            case E_DECODER_DECODING:
            default:
                bRet = E_STILLIMAGE_RET_WORKING;
                break;
        }

        if (stBMPInfo.eDecoderStatus != E_DECODER_DECODING)
        {
            // TBD: this while depends on the nature of _msAPI_BmpDecoder_OutputRow()
            // because _msAPI_BmpDecoder_OutputRow() will fill at least 1 row in
            // transitional buffer
            while (stBMPInfo.u32OutputRows != (U32)stBMPInfo.s32OutputHeight)
            {
                _msAPI_BmpDecoder_OutputRow();
            }
            _msAPI_BmpDecoder_FreeResource();
        }

    #if DECODE_ALL_DATA_IMMEDIATELY
        if (bRet == E_STILLIMAGE_RET_WORKING)
        {
            msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());
            goto again;
        }
    #endif //#if DECODE_ALL_DATA_IMMEDIATELY
    }

    return bRet;
}

EN_STILLIMAGE_RET msAPI_BmpDecoder_Stop(void)
{
    _msAPI_BmpDecoder_FreeResource();
    _msAPI_BmpDecoder_Reset();

    return E_STILLIMAGE_RET_OK;
}

//------------------------------------------------------------------------------
// Local Function Implementation
//------------------------------------------------------------------------------
static void _msAPI_BmpDecoder_Reset(void)
{
    memset(&stBMPInfo, 0, sizeof(stBMPInfo));

    stBMPInfo.pstPalette = NULL;

    stBMPInfo.bTopDown = FALSE;
    stBMPInfo.bWithPalette = FALSE;
    stBMPInfo.bWithMask = FALSE;
    stBMPInfo.bRLEEncoded = FALSE;

    stBMPInfo.eDecoderStatus = E_DECODER_STANDBY;

#if SCAN_LINE_MARKER_NEEDED
    stBMPInfo.bOutOfRowWarning = FALSE;
#endif //#if SCAN_LINE_MARKER_NEEDED

    stBMPInfo.u8OutputWidthAlighment = BMP_ALIGNMENT;

    stBMPInfo.eOutputFormat = E_BMP_ARGB8888;   // currently, only E_BMP_ARGB8888 is supported

    stBMPInfo.pu8OutputBuffer = NULL;

    stBMPInfo.pu8TransBuff_Addr = NULL;
    stBMPInfo.pu8TransBuff_NextPixelPos = NULL;

    // set ARGB default background color to black
    stBmpBackGroundColor.u32Alpha = 0;
    stBmpBackGroundColor.u32Red = 0;
    stBmpBackGroundColor.u32Green = 0;
    stBmpBackGroundColor.u32Blue = 0;
}

static void _msAPI_BmpDecoder_DecodeRLE(U32 u32UnProcessData)
{
    U8 u8PaletteIdx[2], u8PeekMin;
    U32 u32Remainder, u32Size, u32RowProcessed;
    stPixel_Mask stPixel;

    while (stBMPInfo.eDecoderStatus == E_DECODER_DECODING)
    {
#if RLE_DEBUG
        U64 u64Pos = msAPI_StillImage_BMFile_Tell();
        U8 u8Idx;
#endif //#if RLE_DEBUG

        u8PeekMin = 2;
        u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
        if (u32Remainder < u8PeekMin)
        {
            if (u32UnProcessData < u8PeekMin)
            {
                stBMPInfo.eDecoderStatus = E_DECODER_ERR_CORRUPT_FILE;
            }

            return;
        }

        u32RowProcessed = stBMPInfo.u32RowProcessed;

        u32Size = msAPI_StillImage_BMBuffer_PeekNthByte(0);
        u8PaletteIdx[0] = msAPI_StillImage_BMBuffer_PeekNthByte(1);
        if (u32Size == RLE_MARKER_PREFIX)
        {
            switch (u8PaletteIdx[0])
            {
                case RLE_MARKER_END_SL:
                    // remove 2 peeked bytes
                    msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(u8PeekMin);

#if RLE_DEBUG
                    BMP_INFO_MUST(printf("[BMP] RLE  (%08x): end scan line (%05dth)\n",
                            u32u64_0(u64Pos),
                            stBMPInfo.u32RowProcessed));
#endif //#if RLE_DEBUG

                    _msAPI_BmpDecoder_OutputRow();
                    stBMPInfo.u32PixelProcessed = 0;
                    stBMPInfo.u32RowProcessed++;
                    break;

                case RLE_MARKER_END_RLE:
                    // remove 2 peeked bytes
                    msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(u8PeekMin);

#if RLE_DEBUG
                    BMP_INFO_MUST(printf("[BMP] RLE  (%08x): end RLE\n",
                            u32u64_0(u64Pos)));
#endif //#if RLE_DEBUG

                    stBMPInfo.eDecoderStatus = E_DECODER_STOP_ASKED;
                    break;

                case RLE_MARKER_VECTOR:
                    if (u32UnProcessData < 4)
                    {
                        stBMPInfo.eDecoderStatus = E_DECODER_ERR_CORRUPT_FILE;
                        return;
                    }
                    else if (u32Remainder >= 4)
                    {
                        U8 u32XOffset, u32YOffset;

                        // remove 2 peeked bytes
                        msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(u8PeekMin);

                        u32XOffset = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                        u32YOffset = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);

#if RLE_DEBUG
                        BMP_INFO_MUST(printf("[BMP] RLE  (%08x): vector (%d, %d)\n",
                                u32u64_0(u64Pos),
                                u32XOffset,
                                u32YOffset));
#endif //#if RLE_DEBUG

                        while (u32YOffset)
                        {
                            _msAPI_BmpDecoder_OutputRow();
                            stBMPInfo.u32RowProcessed++;
                            u32YOffset--;
                        }

                        u32XOffset += stBMPInfo.u32PixelProcessed;
                        stBMPInfo.u32PixelProcessed = 0;
                        while (u32XOffset)
                        {
                            // fill background color
                            stPixel.u32Alpha = stBmpBackGroundColor.u32Alpha;
                            stPixel.u32Red   = stBmpBackGroundColor.u32Red;
                            stPixel.u32Green = stBmpBackGroundColor.u32Green;
                            stPixel.u32Blue  = stBmpBackGroundColor.u32Blue;

                            _msAPI_BmpDecoder_OutputPixel(&stPixel);
                            stBMPInfo.u32PixelProcessed++;
                            u32XOffset--;

#if (!SCAN_LINE_MARKER_NEEDED)
                            if (stBMPInfo.u32PixelProcessed == (U32)stBMPInfo.s32Width)
                            {
                                _msAPI_BmpDecoder_OutputRow();
                                stBMPInfo.u32PixelProcessed = 0;
                                stBMPInfo.u32RowProcessed++;
                            }
#endif // #if (!SCAN_LINE_MARKER_NEEDED)
                        }
                    }
                    else
                    {
                        // insufficient data for this run, wait for next run
                        return;
                    }
                    break;

                default: // uncoded data
                    // u32Size presents pixel count
                    u32Size = u8PaletteIdx[0];

                    u8PaletteIdx[0] = (u32Size + (stBMPInfo.u8PixelPerByte - 1)) / stBMPInfo.u8PixelPerByte;
                    if (u32UnProcessData < u8PaletteIdx[0])
                    {
                        stBMPInfo.eDecoderStatus = E_DECODER_ERR_CORRUPT_FILE;
                        return;
                    }
                    else if (u32Remainder > u8PaletteIdx[0])
                    {
                        BOOL bPadding = (EVEN_ALIGN(u8PaletteIdx[0]) > u8PaletteIdx[0]);

                        // remove 2 peeked bytes
                        msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(u8PeekMin);

#if RLE_DEBUG
                        u8Idx = u32Size;
#endif //#if RLE_DEBUG

#if SCAN_LINE_MARKER_NEEDED
                        // the pixel count of coded data can't exceed the pixels left in this scan line
                        if (u32Size > (stBMPInfo.s32Width - stBMPInfo.u32PixelProcessed))
                        {
                            if (stBMPInfo.bOutOfRowWarning == FALSE)
                            {
                                BMP_ERR(printf("[BMP] RLE decode, un-compressed data out of row (%d > %d)\n",
                                        u32Size + stBMPInfo.u32PixelProcessed,
                                        stBMPInfo.s32Width));
                                stBMPInfo.bOutOfRowWarning = TRUE;
                            }
                        }
#endif //#if SCAN_LINE_MARKER_NEEDED

                        if (stBMPInfo.u32Compression == E_BMP_COMP_RLE8)
                        {
#if RLE_DEBUG
                            BMP_INFO_MUST(printf("[BMP] RLE8 (%08x): uncoded (%d)\n",
                                    u32u64_0(u64Pos),
                                    u8Idx));
                            u8Idx = 0;
#endif //#if RLE_DEBUG

                            while (u32Size)
                            {
                                u8PaletteIdx[0] = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);

#if RLE_DEBUG
                                if ((u8Idx != 0) && (u8Idx % 16 == 0))
                                {
                                    BMP_INFO_MUST(printf("\n"));
                                }

                                BMP_INFO_MUST(printf("%02X ", u8PaletteIdx[0]));
                                u8Idx++;
#endif //#if RLE_DEBUG

                                stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Alpha;
                                stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Red;
                                stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Green;
                                stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Blue;

                                _msAPI_BmpDecoder_OutputPixel(&stPixel);
                                stBMPInfo.u32PixelProcessed++;
                                u32Size--;

#if (!SCAN_LINE_MARKER_NEEDED)
                                if (stBMPInfo.u32PixelProcessed == (U32)stBMPInfo.s32Width)
                                {
                                    _msAPI_BmpDecoder_OutputRow();
                                    stBMPInfo.u32PixelProcessed = 0;
                                    stBMPInfo.u32RowProcessed++;
                                }
#endif // #if (!SCAN_LINE_MARKER_NEEDED)
                            }

#if RLE_DEBUG
                            BMP_INFO_MUST(printf("\n"));
#endif //#if RLE_DEBUG
                        }
                        else if (stBMPInfo.u32Compression == E_BMP_COMP_RLE4)
                        {
                            U8 u8Latch = 0;

#if RLE_DEBUG
                            BMP_INFO_MUST(printf("[BMP] RLE4 (%08x): uncoded (%d)\n",
                                    u32u64_0(u64Pos),
                                    u8Idx));
                            u8Idx = 0;
#endif //#if RLE_DEBUG

                            while (u32Size)
                            {
                                if (u8Latch == 0)
                                {
                                    u8PaletteIdx[0] = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                                    u8PaletteIdx[1] = u8PaletteIdx[0] & 0xf;
                                    u8PaletteIdx[0] >>= 4;
                                }

#if RLE_DEBUG
                                if ((u8Idx != 0) && (u8Idx % 16 == 0))
                                {
                                    BMP_INFO_MUST(printf("\n"));
                                }

                                BMP_INFO_MUST(printf("%01X ", u8PaletteIdx[u8Latch]));
                                u8Idx++;
#endif //#if RLE_DEBUG

                                stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Alpha;
                                stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Red;
                                stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Green;
                                stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Blue;
                                u8Latch ^= 1;

                                _msAPI_BmpDecoder_OutputPixel(&stPixel);
                                stBMPInfo.u32PixelProcessed++;
                                u32Size--;

#if (!SCAN_LINE_MARKER_NEEDED)
                                if (stBMPInfo.u32PixelProcessed == (U32)stBMPInfo.s32Width)
                                {
                                    _msAPI_BmpDecoder_OutputRow();
                                    stBMPInfo.u32PixelProcessed = 0;
                                    stBMPInfo.u32RowProcessed++;
                                }
#endif // #if (!SCAN_LINE_MARKER_NEEDED)
                            }

#if RLE_DEBUG
                            BMP_INFO_MUST(printf("\n"));
#endif //#if RLE_DEBUG
                        }
                        else
                        {
                            BMP_ERR(printf("[BMP] RLE decode, un-compressed data format (%d) not supported\n", stBMPInfo.u32Compression));
                            stBMPInfo.eDecoderStatus = E_DECODER_ERR_COMPRESSION;
                            break;
                        }

                        if (bPadding)
                        {
                            // for even byte alignment
                            msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                        }
                    }
                    else
                    {
                        // insufficient data for this run, wait for next run
                        return;
                    }
                    break;
            }
        }
        else
        {
            // remove 2 peeked bytes
            msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(u8PeekMin);

#if RLE_DEBUG
            u8Idx = u32Size;
#endif //#if RLE_DEBUG

#if SCAN_LINE_MARKER_NEEDED
            // the pixel count of coded data can't exceed the pixels left in this scan line
            if (u32Size > (stBMPInfo.s32Width - stBMPInfo.u32PixelProcessed))
            {
                if (stBMPInfo.bOutOfRowWarning == FALSE)
                {
                    BMP_ERR(printf("[BMP] RLE decode, compressed data out of row (%d > %d)\n",
                            u32Size + stBMPInfo.u32PixelProcessed,
                            stBMPInfo.s32Width));
                    stBMPInfo.bOutOfRowWarning = TRUE;
                }
            }
#endif //#if SCAN_LINE_MARKER_NEEDED

            if (stBMPInfo.u32Compression == E_BMP_COMP_RLE8)
            {
#if RLE_DEBUG
                BMP_INFO_MUST(printf("[BMP] RLE8 (%08x): coded (%d, %02X)\n",
                        u32u64_0(u64Pos),
                        u8Idx,
                        u8PaletteIdx[0]));
#endif //#if RLE_DEBUG

                stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Alpha;
                stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Red;
                stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Green;
                stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx[0]].u8Blue;

                while (u32Size)
                {
                    _msAPI_BmpDecoder_OutputPixel(&stPixel);
                    stBMPInfo.u32PixelProcessed++;
                    u32Size--;

#if (!SCAN_LINE_MARKER_NEEDED)
                    if (stBMPInfo.u32PixelProcessed == (U32)stBMPInfo.s32Width)
                    {
                        _msAPI_BmpDecoder_OutputRow();
                        stBMPInfo.u32PixelProcessed = 0;
                        stBMPInfo.u32RowProcessed++;
                    }
#endif // #if (!SCAN_LINE_MARKER_NEEDED)
                }
            }
            else if (stBMPInfo.u32Compression == E_BMP_COMP_RLE4)
            {
                U8 u8Latch = 0;

                u8PaletteIdx[1] = u8PaletteIdx[0] & 0xf;
                u8PaletteIdx[0] >>= 4;

#if RLE_DEBUG
                BMP_INFO_MUST(printf("[BMP] RLE4 (%08x): coded (%d, %01X, %01X)\n",
                        u32u64_0(u64Pos),
                        u8Idx,
                        u8PaletteIdx[0],
                        u8PaletteIdx[1]));
#endif //#if RLE_DEBUG

                while (u32Size)
                {
                    stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Alpha;
                    stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Red;
                    stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Green;
                    stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx[u8Latch]].u8Blue;
                    u8Latch ^= 1;

                    _msAPI_BmpDecoder_OutputPixel(&stPixel);
                    stBMPInfo.u32PixelProcessed++;
                    u32Size--;

#if (!SCAN_LINE_MARKER_NEEDED)
                    if (stBMPInfo.u32PixelProcessed == (U32)stBMPInfo.s32Width)
                    {
                        _msAPI_BmpDecoder_OutputRow();
                        stBMPInfo.u32PixelProcessed = 0;
                        stBMPInfo.u32RowProcessed++;
                    }
#endif // #if (!SCAN_LINE_MARKER_NEEDED)
                }
            }
            else
            {
                BMP_ERR(printf("[BMP] RLE decode, compressed data format (%d) not supported\n", stBMPInfo.u32Compression));
                stBMPInfo.eDecoderStatus = E_DECODER_ERR_COMPRESSION;
            }
        }

        if (stBMPInfo.u32RowProcessed >= (U32)stBMPInfo.s32Height)
            stBMPInfo.eDecoderStatus = E_DECODER_STOP_NO_DATA;

        if (u32RowProcessed != stBMPInfo.u32RowProcessed)
        {
            // 1 or more rows are decoded, give other system a chance
            return;
        }
    }

    return;
}

static void _msAPI_BmpDecoder_DecodeRGB(U32 u32UnProcessData)
{
    U8 u8BitMask, u8PaletteIdx, u8Loop;
    U32 u32Data, u32MinByteToRead;
    stPixel_Mask stPixel;

    while (stBMPInfo.eDecoderStatus == E_DECODER_DECODING)
    {
        u32MinByteToRead = msAPI_StillImage_BMBuffer_Remainder();
        if (u32MinByteToRead < SCAN_LINE_ALIGNMENT)
        {
            if (u32UnProcessData == stBMPInfo.u8MinByteToRead)
            {
                u32MinByteToRead = stBMPInfo.u8MinByteToRead;
                stBMPInfo.eDecoderStatus = E_DECODER_ERR_CORRUPT_FILE;
            }
            else if(((U32)msAPI_StillImage_BMFile_Size() == DATA_SIZE_UNKNOWN)&&
                (stBMPInfo.u32PixelProcessed >= (U32)(stBMPInfo.s32Width -1)) &&
                (stBMPInfo.u32RowProcessed >= (U32)( stBMPInfo.s32OutputHeight -1)))
            {
                //for bad file length, u32UnProcessData is incorrect. Need process specially.
                u32MinByteToRead = stBMPInfo.u8MinByteToRead;
                stBMPInfo.eDecoderStatus = E_DECODER_STOP_NO_DATA;
            }
            else
            {
                // insufficient data for BMP decoder, do nothing
                return;
            }
        }
        else
        {
            u32MinByteToRead = SCAN_LINE_ALIGNMENT;
        }

        u32MinByteToRead = (U32)stBMPInfo.u8MinByteToRead;
        if ((stBMPInfo.u16BitsPerPixel == (U16)_1_BITS_PER_PIXEL)
                 || (stBMPInfo.u16BitsPerPixel == (U16)_4_BITS_PER_PIXEL)
                 || (stBMPInfo.u16BitsPerPixel == (U16)_8_BITS_PER_PIXEL))
        {
            while (u32MinByteToRead)
            {
                u32MinByteToRead--;

                switch (stBMPInfo.u16BitsPerPixel)
                {
                    case _1_BITS_PER_PIXEL:
                        u32Data = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                        for (u8Loop = 0, u8BitMask = 0x80; u8Loop < stBMPInfo.u8PixelPerByte; u8Loop++, u8BitMask >>= _1_BITS_PER_PIXEL)
                        {
                            u8PaletteIdx = ((U8)u32Data & u8BitMask ? 1 : 0);
                            stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx].u8Alpha;
                            stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx].u8Red;
                            stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx].u8Green;
                            stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx].u8Blue;

                            _msAPI_BmpDecoder_OutputPixel(&stPixel);
                        }
                        stBMPInfo.u32PixelProcessed += stBMPInfo.u8PixelPerByte;
                        break;

                    case _4_BITS_PER_PIXEL:
                        u32Data = msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                        for (u8Loop = 0, u8BitMask = 0xf0; u8Loop < stBMPInfo.u8PixelPerByte; u8Loop++, u8BitMask >>= _4_BITS_PER_PIXEL)
                        {
                            u8PaletteIdx = (U8)u32Data & u8BitMask;
                            if (u8Loop == 0)
                            {
                                u8PaletteIdx >>= _4_BITS_PER_PIXEL;
                            }
                            stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx].u8Alpha;
                            stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx].u8Red;
                            stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx].u8Green;
                            stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx].u8Blue;

                            _msAPI_BmpDecoder_OutputPixel(&stPixel);
                        }
                        stBMPInfo.u32PixelProcessed += stBMPInfo.u8PixelPerByte;
                        break;

                    case _8_BITS_PER_PIXEL:
                        u8PaletteIdx = (U8)msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(1);
                        stPixel.u32Alpha    = stBMPInfo.pstPalette[u8PaletteIdx].u8Alpha;
                        stPixel.u32Red      = stBMPInfo.pstPalette[u8PaletteIdx].u8Red;
                        stPixel.u32Green    = stBMPInfo.pstPalette[u8PaletteIdx].u8Green;
                        stPixel.u32Blue     = stBMPInfo.pstPalette[u8PaletteIdx].u8Blue;
                        stBMPInfo.u32PixelProcessed++;

                        _msAPI_BmpDecoder_OutputPixel(&stPixel);
                        break;
                }
            }
        }
        else if ((stBMPInfo.u16BitsPerPixel == (U16)_16_BITS_PER_PIXEL)
                || (stBMPInfo.u16BitsPerPixel == (U16)_24_BITS_PER_PIXEL)
                || (stBMPInfo.u16BitsPerPixel == (U16)_32_BITS_PER_PIXEL))
        {
            if (u32MinByteToRead < (U32)stBMPInfo.u8MinByteToRead)
            {
                // give up last pixel because it's not a complete pixel in data
                msAPI_StillImage_BMBuffer_FlushBytes(u32MinByteToRead);
                return;
            }
            u32Data = (U32)msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(stBMPInfo.u8MinByteToRead);
            stPixel.u32Alpha    = (u32Data & stBMPInfo.stPixelMask.u32Alpha) >> stBMPInfo.stPixelRightShift.u8Alpha;
            stPixel.u32Red      = (u32Data & stBMPInfo.stPixelMask.u32Red) >> stBMPInfo.stPixelRightShift.u8Red;
            stPixel.u32Green    = (u32Data & stBMPInfo.stPixelMask.u32Green) >> stBMPInfo.stPixelRightShift.u8Green;
            stPixel.u32Blue     = (u32Data & stBMPInfo.stPixelMask.u32Blue) >> stBMPInfo.stPixelRightShift.u8Blue;

            stBMPInfo.u32PixelProcessed++;
            _msAPI_BmpDecoder_OutputPixel(&stPixel);

            if (stBMPInfo.u32PixelProcessed == (U32)stBMPInfo.s32Width)
            {
                U8 u8Left = (stBMPInfo.s32Width * BYTES_PER_PIXEL(stBMPInfo.u16BitsPerPixel)) % SCAN_LINE_ALIGNMENT;

                if ((u8Left) && (stBMPInfo.eDecoderStatus != E_DECODER_ERR_CORRUPT_FILE))
                {
                    // every scan line is 4-byte alignment
                    msAPI_StillImage_BMBuffer_FlushBytes(SCAN_LINE_ALIGNMENT - u8Left);
                }
            }
        }

        if (stBMPInfo.u32PixelProcessed >= (U32)stBMPInfo.s32Width)
        {
            _msAPI_BmpDecoder_OutputRow();
            stBMPInfo.u32RowProcessed++;
            stBMPInfo.u32PixelProcessed = 0;

            if (stBMPInfo.u32RowProcessed >= (U32)stBMPInfo.s32Height)
                stBMPInfo.eDecoderStatus = E_DECODER_STOP_NO_DATA;

            // 1 row is decoded, give other system a chance
            return;
        }
    }

    return;
}

static void _msAPI_BmpDecoder_OutputPixel(stPixel_Mask *pstPixel)
{
    stPixel_ARGB8888 *pstArgb8888;

    if (stBMPInfo.u32TransBuff_PixelInCurrRow >= (U32)stBMPInfo.s32Width)
    {
        return;
    }

    switch (stBMPInfo.eOutputFormat)
    {
        default:
        case E_BMP_ARGB8888:
            pstArgb8888 = (stPixel_ARGB8888 *)(void*)stBMPInfo.pu8TransBuff_NextPixelPos;

            // Alpha
            if ((S8)stBMPInfo.stPixelOutputShift.u8Alpha >= 0)
            {
                pstArgb8888->u8Alpha = (U8)(pstPixel->u32Alpha >> abs((S8)stBMPInfo.stPixelOutputShift.u8Alpha));
            }
            else
            {
                pstArgb8888->u8Alpha = (U8)(pstPixel->u32Alpha << abs((S8)stBMPInfo.stPixelOutputShift.u8Alpha));
            }

            // Red
            if ((S8)stBMPInfo.stPixelOutputShift.u8Red >= 0)
            {
                pstArgb8888->u8Red = (U8)(pstPixel->u32Red >> abs((S8)stBMPInfo.stPixelOutputShift.u8Red));
            }
            else
            {
                pstArgb8888->u8Red = (U8)(pstPixel->u32Red << abs((S8)stBMPInfo.stPixelOutputShift.u8Red));
            }

            // Green
            if ((S8)stBMPInfo.stPixelOutputShift.u8Green >= 0)
            {
                pstArgb8888->u8Green = (U8)(pstPixel->u32Green >> abs((S8)stBMPInfo.stPixelOutputShift.u8Green));
            }
            else
            {
                pstArgb8888->u8Green = (U8)(pstPixel->u32Green << abs((S8)stBMPInfo.stPixelOutputShift.u8Green));
            }

            // Blue
            if ((S8)stBMPInfo.stPixelOutputShift.u8Blue >= 0)
            {
                pstArgb8888->u8Blue = (U8)(pstPixel->u32Blue >> abs((S8)stBMPInfo.stPixelOutputShift.u8Blue));
            }
            else
            {
                pstArgb8888->u8Blue = (U8)(pstPixel->u32Blue << abs((S8)stBMPInfo.stPixelOutputShift.u8Blue));
            }

            stBMPInfo.u32TransBuff_PixelInCurrRow++;
            stBMPInfo.pu8TransBuff_NextPixelPos += stBMPInfo.u8PixelOutputSize;
            break;
    }

    return;
}

static void _msAPI_BmpDecoder_OutputRow(void)
{
    stPixel_ARGB8888 *pstPixel_Argb8888, stPixel_Argb8888;
    U8 *pu8Dest, u8RowCnt, u8ColumnCnt;

    if (stBMPInfo.u32OutputRows >= (U32)stBMPInfo.s32OutputHeight)
    {
        return;
    }

    switch (stBMPInfo.eOutputFormat)
    {
        default:
        case E_BMP_ARGB8888:
            // fill background color
            if (stBMPInfo.u32TransBuff_PixelInCurrRow < (U32)stBMPInfo.s32AlignedWidth)
            {
                stPixel_Argb8888.u8Alpha = stBmpBackGroundColor.u32Alpha;
                stPixel_Argb8888.u8Red   = stBmpBackGroundColor.u32Red;
                stPixel_Argb8888.u8Green = stBmpBackGroundColor.u32Green;
                stPixel_Argb8888.u8Blue  = stBmpBackGroundColor.u32Blue;

                do
                {
                    pstPixel_Argb8888 = (stPixel_ARGB8888 *)(void*)stBMPInfo.pu8TransBuff_NextPixelPos;
                    *pstPixel_Argb8888 = stPixel_Argb8888;

                    stBMPInfo.u32TransBuff_PixelInCurrRow++;
                    stBMPInfo.pu8TransBuff_NextPixelPos += stBMPInfo.u8PixelOutputSize;
                } while (stBMPInfo.u32TransBuff_PixelInCurrRow < (U32)stBMPInfo.s32AlignedWidth);
            }

            stBMPInfo.u32TransBuff_PixelInCurrRow = 0;
            stBMPInfo.u32TransBuff_Rows++;

            u8RowCnt = stBMPInfo.u8Factor;
            if (((stBMPInfo.bTopDown) && (stBMPInfo.u32OutputRows == (U32)(stBMPInfo.s32OutputHeight - 1)))
                    || ((!stBMPInfo.bTopDown) && (stBMPInfo.u32OutputRows == 0)))
            {
                // Since we have to scale down original image,
                // stBMPInfo.s32OutputHeight % stBMPInfo.u8Factor may not equal to 0
                // Therefore, for the last row of scaled down image, we may need
                // only u8RowCnt rows and which may less than stBMPInfo.u8Factor
                if (stBMPInfo.s32Height % stBMPInfo.u8Factor)
                {
                    u8RowCnt = stBMPInfo.s32Height % stBMPInfo.u8Factor;
                }
            }

            if (stBMPInfo.u32TransBuff_Rows == u8RowCnt)
            {
                // scale down when it's needed
                if (stBMPInfo.u8Factor != 1)
                {
                    U32 u32i, u32j, u32k;
                    U32 u32Red, u32Green, u32Blue, u32Alpha;
                    U32 u32Offset, u32PixelPerBlock, u32NextPixelPos;
                    stPixel_ARGB8888 *pstPixel;

                    u32NextPixelPos = 0;

                    for (u32i = 0; u32i < (U32)stBMPInfo.s32AlignedWidth; u32i += stBMPInfo.u8Factor)
                    {
                        u32Red = u32Green = u32Blue = u32Alpha = 0;

                        u8ColumnCnt = stBMPInfo.u8Factor;
                        if ((u32i < (U32)stBMPInfo.s32Width)
                                && ((u32i + stBMPInfo.u8Factor) > (U32)stBMPInfo.s32Width))
                        {
                            // Since we have to scale down original image,
                            // stBMPInfo.s32OutputWidth % stBMPInfo.u8Factor may not equal to 0
                            // Therefore, for the last column of scaled down image, we may need
                            // only u8ColumnCnt columns and which may less than stBMPInfo.u8Factor
                            u8ColumnCnt = (U32)stBMPInfo.s32Width - u32i;
                        }

                        u32PixelPerBlock = u8RowCnt * u8ColumnCnt;

                        for (u32j = 0; u32j < u8RowCnt; u32j++) // height
                        {
                            u32Offset = (u32i + u32j * stBMPInfo.s32AlignedWidth) * stBMPInfo.u8PixelOutputSize;
                            for (u32k = 0; u32k < u8ColumnCnt; u32k++, u32Offset += stBMPInfo.u8PixelOutputSize) // width
                            {
                                pstPixel = (stPixel_ARGB8888 *)(void*)(stBMPInfo.pu8TransBuff_Addr + u32Offset);

                                u32Red      += pstPixel->u8Red;
                                u32Green    += pstPixel->u8Green;
                                u32Blue     += pstPixel->u8Blue;
                                u32Alpha    += pstPixel->u8Alpha;
                            }
                        }

                        // calculate average value
                        stPixel_Argb8888.u8Red   = (U8)(u32Red / u32PixelPerBlock);
                        stPixel_Argb8888.u8Green = (U8)(u32Green / u32PixelPerBlock);
                        stPixel_Argb8888.u8Blue  = (U8)(u32Blue / u32PixelPerBlock);
                        stPixel_Argb8888.u8Alpha = (U8)(u32Alpha / u32PixelPerBlock);

                        // first output the scaled data to transitional buffer
                        pstPixel_Argb8888 = (stPixel_ARGB8888 *)(void*)(stBMPInfo.pu8TransBuff_Addr + u32NextPixelPos);
                        *pstPixel_Argb8888 = stPixel_Argb8888;
                        u32NextPixelPos += stBMPInfo.u8PixelOutputSize;
                    }
                }

                if (stBMPInfo.bTopDown)
                {
                    pu8Dest = stBMPInfo.pu8OutputBuffer
                            + stBMPInfo.u32OutputRows * stBMPInfo.u32BytePerOutputRow;
                }
                else
                {
                    pu8Dest = stBMPInfo.pu8OutputBuffer
                            + (stBMPInfo.s32OutputHeight - stBMPInfo.u32OutputRows - 1) * stBMPInfo.u32BytePerOutputRow;
                }

                memcpy(pu8Dest, stBMPInfo.pu8TransBuff_Addr, stBMPInfo.u32BytePerOutputRow);
                stBMPInfo.u32OutputRows++;

                // reset transitional buffer related variables
                stBMPInfo.pu8TransBuff_NextPixelPos = stBMPInfo.pu8TransBuff_Addr;
                stBMPInfo.u32TransBuff_Rows = stBMPInfo.u32TransBuff_PixelInCurrRow = 0;
            }
            break;
    }

    // update progress here
    g_stStillImage.u16Progress = stBMPInfo.u32OutputRows * 1000 / stBMPInfo.s32OutputHeight;
    return;
}

static void _msAPI_BmpDecoder_FreeResource(void)
{
    if (stBMPInfo.pstPalette != NULL)
    {
        msAPI_StillImage_Dlmalloc_Free(stBMPInfo.pstPalette);
        stBMPInfo.pstPalette = NULL;
    }

    if ((stBMPInfo.pu8TransBuff_Addr != NULL)
            && (stBMPInfo.pu8TransBuff_Addr != stBMPInfo.pu8OutputBuffer))
    {
        msAPI_StillImage_Dlmalloc_Free(stBMPInfo.pu8TransBuff_Addr);
        stBMPInfo.pu8TransBuff_Addr = NULL;
    }
}

#undef _MSAPI_BMP_DECODER_C_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
