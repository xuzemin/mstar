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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MAPP_STILLIMAGE_SHAREMENCFG_H
#define __MAPP_STILLIMAGE_SHAREMENCFG_H

#define STILLIMAGE_SHAREMEM_VERSION_NUM     0x0000000N // 00.000.00N
#define STILLIMAGE_SHAREMEM_MAGICKEY        (0x5A5AA5A5)

//size of ST_STILLIMAGE_JPEG_EXIF: 8*6+4+32+128+4=216, 216/4=54,  define 64 for future extension use
#define E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_DATASIZE  (64)
//#define STILLIMAGE_MEM_MIU1_USED      (0x20000000UL)

#define EXIF_CAMERA_MAKER_SIZE  32
#define EXIF_CAMERA_MODEL_SIZE  128

#define E_STILLIMAGE_SHAREMEM_SIZE                                     (255)

typedef enum
{
    /****************************************
        General parameters
    ****************************************/
    E_STILLIMAGE_SHAREMEM_VERSION_NUM,
    E_STILLIMAGE_SHAREMEM_MIU,
    E_STILLIMAGE_SHAREMEM_CMD,
    E_STILLIMAGE_SHAREMEM_WDT_LOOP,

    /****************************************
        Decoder related
    ****************************************/
    /****************************************
        Decoder input options
    ****************************************/
    // general min supported width/height
    E_STILLIMAGE_SHAREMEM_MIN_WIDTH,
    E_STILLIMAGE_SHAREMEM_MIN_HEIGHT,

    // max supported width/height for baseline JPEG
    E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_HEIGHT,

    // max supported width/height of progressive jpeg
    E_STILLIMAGE_SHAREMEM_JPEG_PROGRESSIVE_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_JPEG_PROGRESSIVE_MAX_HEIGHT,

    // max supported width/height for BMP
    E_STILLIMAGE_SHAREMEM_BMP_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_BMP_MAX_HEIGHT,

    // max supported width/height for PNG
    E_STILLIMAGE_SHAREMEM_PNG_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_PNG_MAX_HEIGHT,

    // max supported width/height for TIFF
    E_STILLIMAGE_SHAREMEM_TIFF_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_TIFF_MAX_HEIGHT,

    // max supported width/height for TIFF
    E_STILLIMAGE_SHAREMEM_GIF_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_GIF_MAX_HEIGHT,

    // max supported width/height for MPO with subjpeg is baseline
    E_STILLIMAGE_SHAREMEM_MPO_BASELINE_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_MPO_BASELINE_MAX_HEIGHT,

    // max supported width/height for MPO with subjpeg is progressive
    E_STILLIMAGE_SHAREMEM_MPO_PROGRESSIVE_MAX_WIDTH,
    E_STILLIMAGE_SHAREMEM_MPO_PROGRESSIVE_MAX_HEIGHT,

    // if decode thumbnail
    E_STILLIMAGE_SHAREMEM_DECODE_THUMBNAIL,

    // buffer for input data
    E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_ADDR,
    E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_LEN,

    // buffer for output data
    E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_ADDR,
    E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_LEN,

    // buffer for progressive jpeg
    E_STILLIMAGE_SHAREMEM_PROGRESSIVE_BUFF_ADDR,
    E_STILLIMAGE_SHAREMEM_PROGRESSIVE_BUFF_LEN,

    // buffer for memory pool
    E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_ADDR,
    E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_LEN,

    // how input data is accessed, eg, mailbox, network or storage direct access
    E_STILLIMAGE_SHAREMEM_DATA_ACCESS_METHOD,


    /****************************************
        Decoder output results
    ****************************************/
    // the error code
    E_STILLIMAGE_SHAREMEM_ERROR,

    // the progress of current job, 0 ~ 1000
    E_STILLIMAGE_SHAREMEM_PROGRESS,

    // input data format, JPEG/BMP/PNG or something else
    E_STILLIMAGE_SHAREMEM_INPUT_DATA_FORMAT,

    // output image width/height/pitch/size
    E_STILLIMAGE_SHAREMEM_OUTPUT_PITCH,
    E_STILLIMAGE_SHAREMEM_OUTPUT_WIDTH,
    E_STILLIMAGE_SHAREMEM_OUTPUT_HEIGHT,
    E_STILLIMAGE_SHAREMEM_OUTPUT_SIZE,

    // original image width/height
    E_STILLIMAGE_SHAREMEM_IMAGE_WIDTH,
    E_STILLIMAGE_SHAREMEM_IMAGE_HEIGHT,

    // output image format, YUV422/ARGB8888 or something else
    E_STILLIMAGE_SHAREMEM_OUTPUT_IMAGE_FORMAT,

    // if input data contains thumbnail
    E_STILLIMAGE_SHAREMEM_HAS_THUMBNAIL,

    // the scale down factor performed by decoder
    E_STILLIMAGE_SHAREMEM_SCALE_DOWN_FACTOR,

    // the orientation specified in image info
    E_STILLIMAGE_SHAREMEM_OIRENTATION,

    // the date time in image info
    E_STILLIMAGE_SHAREMEM_HAS_DATE_TIME,
    E_STILLIMAGE_SHAREMEM_DATE_TIME_YEAR,
    E_STILLIMAGE_SHAREMEM_DATE_TIME_MONTH,
    E_STILLIMAGE_SHAREMEM_DATE_TIME_DAY,
    E_STILLIMAGE_SHAREMEM_DATE_TIME_HOUR,
    E_STILLIMAGE_SHAREMEM_DATE_TIME_MINUTE,
    E_STILLIMAGE_SHAREMEM_DATE_TIME_SECOND,

    //if it is stream mode
    E_STILLIMAGE_SHAREMEM_IS_STREAM_MODE,
    E_STILLIMAGE_SHAREMEM_STREAM_MODE_READ_TIME_OUT,    // milli-second

    //gif relate
    E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX,
    E_STILLIMAGE_SHAREMEM_DISPLAYED_FRAME_INDEX,
    E_STILLIMAGE_SHAREMEM_FRAME_INFO_ARRAY_ADDR,
    E_STILLIMAGE_SHAREMEM_FRAME_INFO_ARRAY_SIZE,
    E_STILLIMAGE_SHAREMEM_SLOT_NUM,
    E_STILLIMAGE_SHAREMEM_FRAME_SIZE,
    E_STILLIMAGE_SHAREMEM_ONLY_DECODE_FIRST_FRAME,
    E_STILLIMAGE_SHAREMEM_ONLY_PLAY_FIRST_LOOP_FOR_ANIMATION,
    E_STILLIMAGE_SHAREMEM_GIF_ANIMATION_LOOP_TIMES,

    //Jpeg exif width and height
    E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_WIDTH,
    E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_HEIGHT,
    //jpeg exif data, ref ST_STILLIMAGE_JPEG_EXIF
    E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_DATA,
    E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_DATA_END = E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_DATA + E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_DATASIZE,

    /****************************************
        Encoder related
    ****************************************/

    /****************************************
        Functionality control
    ****************************************/
    E_STILLIMAGE_SHAREMEM_CONTORL_FLAGS,

    /****************************************
        External options
    ****************************************/
    // output image max width/height
    E_STILLIMAGE_SHAREMEM_MAX_OUTPUT_WIDTH,
    E_STILLIMAGE_SHAREMEM_MAX_OUTPUT_HEIGHT,

    // jpeg full image info
    E_STILLIMAGE_SHAREMEM_JPEG_FULL_IMAGE_WIDTH,
    E_STILLIMAGE_SHAREMEM_JPEG_FULL_IMAGE_HEIGHT,
    E_STILLIMAGE_SHAREMEM_JPEG_FULL_IMAGE_PROGRESSIVE,

    // mpo internal buffer info
    E_STILLIMAGE_SHAREMEM_MPO_INTERNAL_BUFF_ADDR,
    E_STILLIMAGE_SHAREMEM_MPO_INTERNAL_BUFF_LEN,

    // disable debug info
    E_STILLIMAGE_SHAREMEM_DISABLE_DBGINFO,

    /****************************************
        max
    ****************************************/
    E_STILLIMAGE_SHAREMEM_NUM = E_STILLIMAGE_SHAREMEM_SIZE,
} EN_STILLIMAGE_SHAREMEMORY;

typedef enum
{
    E_STILLIMAGE_DECODE     = 0,
    E_STILLIMAGE_ENCODE,
} EN_STILLIMAGE_CMD_TYPE;

typedef enum
{
    E_STILLIMAGE_DATA_ACCESS_METHOD_MIN     = 0,

    E_STILLIMAGE_VIA_MAILBOX                = E_STILLIMAGE_DATA_ACCESS_METHOD_MIN,
    E_STILLIMAGE_VIA_NETWORK,
    E_STILLIMAGE_VIA_FILE_SYS,

    E_STILLIMAGE_IN_MEMORY,

    E_STILLIMAGE_DATA_ACCESS_METHOD_MAX,
} EN_STILLIMAGE_DATA_ACCESS_METHOD;

#define STILLIMAGE_ERR_CODE_ST  0xE000
typedef enum
{
    E_STILLIMAGE_ERR_NONE               = 0,

    E_STILLIMAGE_NORMAL_STOPPED,
    E_STILLIMAGE_USER_STOPPED,

    /****************************************
        error code
    ****************************************/
    E_STILLIMAGE_GENERAL_ERR            = STILLIMAGE_ERR_CODE_ST,

    E_STILLIMAGE_INIT_FAILED,
    E_STILLIMAGE_WRONG_PARAMETERS,

    E_STILLIMAGE_START_FAILED,

    E_STILLIMAGE_DATA_FORMAT_NOT_SUPPORTED,   // for the format of the data
    E_STILLIMAGE_IMAGE_FORMAT_NOT_SUPPORTED,  // for detail image format in file

    E_STILLIMAGE_NO_THUMBNAIL,

    E_STILLIMAGE_IMAGE_RESOLUTION_TOO_BIG,
    E_STILLIMAGE_IMAGE_RESOLUTION_TOO_SAMLL,

    E_STILLIMAGE_INPUT_BUFF_TOO_SMALL,
    E_STILLIMAGE_OUTPUT_BUFF_TOO_SMALL,
    E_STILLIMAGE_INTERNAL_BUFF_TOO_SMALL,

    // resource
    E_STILLIMAGE_WRONG_DATA                 = STILLIMAGE_ERR_CODE_ST + 0x40,
    E_STILLIMAGE_WRONG_SIZE,
    E_STILLIMAGE_OPEN_ERR,
    E_STILLIMAGE_READ_ERR,

    // JPEG decoder specific
    E_STILLIMAGE_JPEG_HARDWARE_ERR          = STILLIMAGE_ERR_CODE_ST + 0x80,
    E_STILLIMAGE_JPEG_HARDWARE_TIME_OUT,

    E_STILLIMAGE_JPEG_BAD_DHT_COUNTS        = STILLIMAGE_ERR_CODE_ST + 0x90,
    E_STILLIMAGE_JPEG_BAD_DHT_INDEX,
    E_STILLIMAGE_JPEG_BAD_DHT_MARKER,
    E_STILLIMAGE_JPEG_BAD_DQT_MARKER,
    E_STILLIMAGE_JPEG_BAD_DQT_TABLE,
    E_STILLIMAGE_JPEG_BAD_PRECISION,
    E_STILLIMAGE_JPEG_BAD_HEIGHT,
    E_STILLIMAGE_JPEG_BAD_WIDTH,
    E_STILLIMAGE_JPEG_TOO_MANY_COMPONENTS,
    E_STILLIMAGE_JPEG_BAD_SOF_LENGTH,
    E_STILLIMAGE_JPEG_BAD_VARIABLE_MARKER,
    E_STILLIMAGE_JPEG_BAD_DRI_LENGTH,
    E_STILLIMAGE_JPEG_BAD_SOS_LENGTH,
    E_STILLIMAGE_JPEG_BAD_SOS_COMP_ID,
    E_STILLIMAGE_JPEG_W_EXTRA_BYTES_BEFORE_MARKER,
    E_STILLIMAGE_JPEG_NO_ARITHMITIC_SUPPORT,
    E_STILLIMAGE_JPEG_UNEXPECTED_MARKER,
    E_STILLIMAGE_JPEG_NOT_JPEG,
    E_STILLIMAGE_JPEG_UNSUPPORTED_MARKER,
    E_STILLIMAGE_JPEG_BAD_DQT_LENGTH,
    E_STILLIMAGE_JPEG_TOO_MANY_BLOCKS,
    E_STILLIMAGE_JPEG_UNDEFINED_QUANT_TABLE,
    E_STILLIMAGE_JPEG_UNDEFINED_HUFF_TABLE,
    E_STILLIMAGE_JPEG_NOT_SINGLE_SCAN,
    E_STILLIMAGE_JPEG_UNSUPPORTED_COLORSPACE,
    E_STILLIMAGE_JPEG_UNSUPPORTED_SAMP_FACTORS,
    E_STILLIMAGE_JPEG_DECODE_ERROR,
    E_STILLIMAGE_JPEG_BAD_RESTART_MARKER,
    E_STILLIMAGE_JPEG_ASSERTION_ERROR,
    E_STILLIMAGE_JPEG_BAD_SOS_SPECTRAL,
    E_STILLIMAGE_JPEG_BAD_SOS_SUCCESSIVE,
    E_STILLIMAGE_JPEG_STREAM_READ,
    E_STILLIMAGE_JPEG_NOTENOUGHMEM,
    E_STILLIMAGE_JPEG_STOP_DECODE,
    E_STILLIMAGE_JPEG_BAD_APP1_MARKER,
    E_STILLIMAGE_JPEG_NO_THUMBNAIL,
    E_STILLIMAGE_JPEG_UNSUPPORTED_HUFF_DECODE,
    E_STILLIMAGE_JPEG_READBUFFER_TOOSMALL,
    E_STILLIMAGE_JPEG_NOT_ENOUGH_HEADER_INFO,
    E_STILLIMAGE_JPEG_JPD_DECODE_ERROR,
    E_STILLIMAGE_JPEG_WRONG_STATE,

    // BMP decoder specific
    E_STILLIMAGE_BMP_WRONG_STATE            = STILLIMAGE_ERR_CODE_ST + 0xC0,
    E_STILLIMAGE_BMP_PALETTE_MEM_ERR,
    E_STILLIMAGE_BMP_HEADER_SIZE_NOT_SUPPORT,
    E_STILLIMAGE_BMP_WxH_0x0,
    E_STILLIMAGE_BMP_PIXEL_PER_BYTE_NOT_SUPPORT,
    E_STILLIMAGE_BMP_COMPRESSION_NOT_SUPPORT,
    E_STILLIMAGE_BMP_OUTPUT_BUFFER_NULL,
    E_STILLIMAGE_BMP_SCALE_DOWN_FACTOR_NOT_SUPPORT,
    E_STILLIMAGE_BMP_TRANSITIONAL_MEM_ERR,
    E_STILLIMAGE_BMP_DECOMPRESSION_ERROR,
    E_STILLIMAGE_BMP_NO_THUMBNAIL,

    // PNG decoder specific
    E_STILLIMAGE_PNG_BAD_RESOLUTION         = STILLIMAGE_ERR_CODE_ST + 0x100,
    E_STILLIMAGE_PNG_NO_THUMBNAIL,
    E_STILLIMAGE_PNG_RESOLUTION_NOT_SUPPORTED,
    E_STILLIMAGE_PNG_SCALE_DOWN_FACTOR_NOT_SUPPORT,
    E_STILLIMAGE_PNG_TRANSITIONAL_MEM_ERR,
    E_STILLIMAGE_PNG_DECODER_INIT_FAILED,

    // JPEG encoder specific
    E_STILLIMAGE_JPE_FREE_MEM_TOO_LOW       = STILLIMAGE_ERR_CODE_ST + 0x140,
    E_STILLIMAGE_JPE_INIT_FAILED,
    E_STILLIMAGE_JPE_WIDTH_NOT_ALIGNED,
    E_STILLIMAGE_JPE_HEIGHT_NOT_ALIGNED,
    E_STILLIMAGE_JPE_WRONG_STATE,
    E_STILLIMAGE_JPE_OUTPUT_BUFFER_TOO_SMALL,

    //TIFF decode specific
    E_STILLIMAGE_TIFF_WRONG_STATE            = STILLIMAGE_ERR_CODE_ST + 0x180,
    E_STILLIMAGE_TIFF_RESOLUTION_NOT_SUPPORTED,
    E_STILLIMAGE_TIFF_PIXEL_PER_BYTE_NOT_SUPPORT,
    E_STILLIMAGE_TIFF_COMPRESSION_NOT_SUPPORT,
    E_STILLIMAGE_TIFF_OUTPUT_BUFFER_NULL,
    E_STILLIMAGE_TIFF_SCALE_DOWN_FACTOR_NOT_SUPPORT,
    E_STILLIMAGE_TIFF_TRANSITIONAL_MEM_ERR,
    E_STILLIMAGE_TIFF_DECOMPRESSION_ERROR,
    E_STILLIMAGE_TIFF_NO_THUMBNAIL,

    //GIF decode specific
    E_STILLIMAGE_GIF_WRONG_STATE            = STILLIMAGE_ERR_CODE_ST + 0x1c0,
    E_STILLIMAGE_GIF_RESOLUTION_NOT_SUPPORTED,
    E_STILLIMAGE_GIF_PIXEL_PER_BYTE_NOT_SUPPORT,
    E_STILLIMAGE_GIF_OUTPUT_BUFFER_NULL,
    E_STILLIMAGE_GIF_SCALE_DOWN_FACTOR_NOT_SUPPORT,
    E_STILLIMAGE_GIF_TRANSITIONAL_MEM_ERR,
    E_STILLIMAGE_GIF_DECOMPRESSION_ERROR,
    E_STILLIMAGE_GIF_NO_THUMBNAIL,
} EN_STILLIMAGE_ERR_CODE;

#define MAJOR_FORMAT(format)    (format & 0xffffff00)
typedef enum
{
    E_STILLIMAGE_INPUT_DATA_FORMAT_NONE         = 0x0,

    E_STILLIMAGE_INPUT_DATA_JPEG                = 0x100,
    E_STILLIMAGE_INPUT_DATA_BMP                 = 0x200,
    E_STILLIMAGE_INPUT_DATA_PNG                 = 0x400,
    E_STILLIMAGE_INPUT_DATA_TIFF                = 0x800,
    E_STILLIMAGE_INPUT_DATA_GIF                 = 0x1000,
    E_STILLIMAGE_INPUT_DATA_RAW                 = 0x10000,

    // detail format of JPEG
    E_STILLIMAGE_INPUT_DATA_JPEG_BASELINE       = E_STILLIMAGE_INPUT_DATA_JPEG,
    E_STILLIMAGE_INPUT_DATA_JPEG_PROGRESSIVE,
    E_STILLIMAGE_INPUT_DATA_MPO_BASELINE_SUBJPEG_BASELINE,
    E_STILLIMAGE_INPUT_DATA_MPO_PANORAMA_SUBJPEG_BASELINE,
    E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_BASELINE,
    E_STILLIMAGE_INPUT_DATA_MPO_MULTI_ANGLE_SUBJPEG_BASELINE,
    E_STILLIMAGE_INPUT_DATA_MPO_BASELINE_SUBJPEG_PROGRESSIVE,
    E_STILLIMAGE_INPUT_DATA_MPO_PANORAMA_SUBJPEG_PROGRESSIVE,
    E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_PROGRESSIVE,
    E_STILLIMAGE_INPUT_DATA_MPO_MULTI_ANGLE_SUBJPEG_PROGRESSIVE,

    // detail format of BMP
    E_STILLIMAGE_INPUT_DATA_BMP_1_BITS          = E_STILLIMAGE_INPUT_DATA_BMP,
    E_STILLIMAGE_INPUT_DATA_BMP_4_BITS,
    E_STILLIMAGE_INPUT_DATA_BMP_8_BITS,
    E_STILLIMAGE_INPUT_DATA_BMP_16_BITS,
    E_STILLIMAGE_INPUT_DATA_BMP_24_BITS,
    E_STILLIMAGE_INPUT_DATA_BMP_32_BITS,
    E_STILLIMAGE_INPUT_DATA_BMP_RLE_4_BITS,
    E_STILLIMAGE_INPUT_DATA_BMP_RLE_8_BITS,

    // detail format of PNG
    E_STILLIMAGE_INPUT_DATA_PNG_NON_INTERLACED  = E_STILLIMAGE_INPUT_DATA_PNG,
    E_STILLIMAGE_INPUT_DATA_PNG_INTERLACED,

    // detail format of TIFF
    E_STILLIMAGE_INPUT_DATA_TIFF_1_BITS = E_STILLIMAGE_INPUT_DATA_TIFF,
    E_STILLIMAGE_INPUT_DATA_TIFF_4_BITS,
    E_STILLIMAGE_INPUT_DATA_TIFF_8_BITS,
    E_STILLIMAGE_INPUT_DATA_TIFF_16_BITS,
    E_STILLIMAGE_INPUT_DATA_TIFF_24_BITS,
    E_STILLIMAGE_INPUT_DATA_TIFF_32_BITS,

    // detail format of GIF
    E_STILLIMAGE_INPUT_DATA_GIF_NOT_ANIMATION = E_STILLIMAGE_INPUT_DATA_GIF,
    E_STILLIMAGE_INPUT_DATA_GIF_ANIMATION,
} EN_STILLIMAGE_INPUT_DATA_FORMAT;

typedef enum
{
    E_STILLIMAGE_OUTPU_FORMAT_NONE  = 0x0,

    // decode
    E_STILLIMAGE_OUTPU_RAW_YUV422,
    E_STILLIMAGE_OUTPU_RAW_ARGB8888,
    E_STILLIMAGE_OUTPU_ARGB1555,

    // encode
    E_STILLIMAGE_OUTPU_JPEG,
} EN_STILLIMAGE_OUTPUT_DATA_FORMAT;

typedef enum
{
    E_STILLIMAGE_ORIENT_RESERVED            = 0, // reserved, all rotation below is clockwise
    E_STILLIMAGE_ORIENT_ROTATE_0            = 1, // rotate 0
    E_STILLIMAGE_ORIENT_MIRROR_LR           = 2, // mirror left/right
    E_STILLIMAGE_ORIENT_ROTATE_180          = 3, // rotate 180
    E_STILLIMAGE_ORIENT_MIRROR_TB           = 4, // mirror top/bottom
    E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_LR = 5, // rotate 90 then mirror left/right
    E_STILLIMAGE_ORIENT_E_ORIENT_ROTATE_90  = 6, // rotate 90
    E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_TB = 7, // rotate 90 then mirror top/bottom
    E_STILLIMAGE_ORIENT_ROTATE_270          = 8, // rotate 270
    E_STILLIMAGE_ORIENT_NOT_FOUND           = 9,
    E_STILLIMAGE_ORIENT_UNDEFINE            = 10,
} EN_STILLIMAGE_ORIENTATION;

typedef enum
{
    E_STILLIMAGE_CONTROL_FLAG_ENABLE_NONE           = 0x00000000,
    E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_DECODER   = 0x00000001,

    // JPEG YUV is supported as default
    //E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_YUV     = 0x00000002,
    E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_CMYK    = 0x00000004,
    E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_RGB     = 0x00000008,

    E_STILLIMAGE_CONTROL_FLAG_STOP_WHEN_RST_ERROR   = 0x00000010,

    E_STILLIMAGE_CONTROL_FLAG_ENABLE_DO_ALPHA_BLEND_PNG   = 0x00000100,
    E_STILLIMAGE_CONTROL_FLAG_ENABLE_ONLY_DECODE_ONE_FRAME_MPO   = 0x00000200,

    E_STILLIMAGE_CONTROL_FLAG_ENABLE_BMP_DECODER    = 0x00010000,
    E_STILLIMAGE_CONTROL_FLAG_ENABLE_PNG_DECODER    = 0x00020000,
    E_STILLIMAGE_CONTROL_FLAG_ENABLE_GIF_DECODER    = 0x00040000,
    E_STILLIMAGE_CONTROL_FLAG_ENABLE_TIFF_DECODER   = 0x00080000,

    E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_ENCODER   = 0x01000000,
} EN_STILLIMAGE_CONTROL_FLAGS;

// for E_STILLIMAGE_SHAREMEM_MIU use
typedef enum
{
    E_STILLIMAGE_MIU_FLAG_NONE                      = 0x00000000,
    E_STILLIMAGE_MIU_FLAG_INPUT_DATA_BUFF_ON_MIU1   = 0x00000001,
} EN_STILLIMAGE_MIU_FLAGS;

// MAILBOX relative
//-------------------------------
// E_MBX_CLASS_STILLIMAGE_CMD_IO
//-------------------------------
typedef enum
{
    MB_STILLIMAGE_CMD_NONE      = 0x00,

    // CMD: HK --> CP
    MB_STILLIMAGE_INIT_CMD      = 0x10,
    MB_STILLIMAGE_START_CMD     = 0x11,
    MB_STILLIMAGE_STOP_CMD      = 0x12,
    MB_STILLIMAGE_DISABLE_DBGINFO   = 0x13,

    // ACK: CP --> HK
    MB_STILLIMAGE_INIT_ACK      = 0x80,
    MB_STILLIMAGE_START_ACK     = 0x81,
    MB_STILLIMAGE_STOP_ACK      = 0x82,

    MB_STILLIMAGE_CMD_NUM,
} MB_STILLIMAGE_CMD_IO;

//-------------------------------
// E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST & E_MBX_CLASS_STILLIMAGE_DATA_IO
//-------------------------------
typedef enum
{
    MB_STILLIMAGE_DATA_IO_NONE      = 0x00,
    MB_STILLIMAGE_DATA_REQ,
    MB_STILLIMAGE_DATA_REQ_ACK,

    // stop any further data operation
    MB_STILLIMAGE_STOP_DATA_OPERATION,

    // file operations
    MB_STILLIMAGE_DATA_IO_FILE_OPEN,
    MB_STILLIMAGE_DATA_IO_FILE_CLOSE,
    MB_STILLIMAGE_DATA_IO_FILE_READ,
    MB_STILLIMAGE_DATA_IO_FILE_NONBLOCKING_READ,
    MB_STILLIMAGE_DATA_IO_FILE_SEEK,
    MB_STILLIMAGE_DATA_IO_FILE_NONBLOCKING_SEEK,

    // data in memory
    MB_STILLIMAGE_DATA_IO_MEMORY_GET_TOTAL_SIZE,
    MB_STILLIMAGE_DATA_IO_MEMORY_REQUIRE_DATA,
    MB_STILLIMAGE_DATA_IO_MEMORY_REQUIRE_DATA_NONBLOCKING,
    MB_STILLIMAGE_DATA_IO_MEMORY_SEEK,
    MB_STILLIMAGE_DATA_IO_MEMORY_NONBLOCKING_SEEK,

    MB_STILLIMAGE_DATA_IO_NUM,
} MB_STILLIMAGE_DATA_IO;

typedef struct
{
    union
    {
        struct
        {
            unsigned long u32Numerator;
            unsigned long u32Denominator;
        };

        struct
        {
            signed long s32Numerator;
            signed long s32Denominator;
        };
    };
} ST_STILLIMAGE_RATIONAL;

typedef struct
{
    ST_STILLIMAGE_RATIONAL stExposureBias;
    ST_STILLIMAGE_RATIONAL stExposureTime;
    ST_STILLIMAGE_RATIONAL stF_Stop;
    ST_STILLIMAGE_RATIONAL stFocalLength;
    ST_STILLIMAGE_RATIONAL stShutterSpeedValue;
    ST_STILLIMAGE_RATIONAL stApertureValue;
    unsigned long u32ISOSpeed;
    unsigned char au8CameraMaker[EXIF_CAMERA_MAKER_SIZE];
    unsigned char au8CameraModel[EXIF_CAMERA_MODEL_SIZE];
    unsigned long u32FlashMode;
    unsigned long u32ExposureProgram;
}ST_STILLIMAGE_JPEG_EXIF;

#endif //#ifndef __MAPP_STILLIMAGE_SHAREMENCFG_H

///*** please do not remove change list tag ***///
///***$Change: 1324550 $***///
