////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define SCA_TOOL_VERSION            "Chakra SCA V1.1.0 "

////////////////////////////////////////////////////////////////////////////////
// DRAM memory map
//
// Every Module Memory Mapping need 4 define,
// and check code in "msAPI_Memory_DumpMemoryMap"
// 1. XXX_AVAILABLE : For get avaialble memory start address
// 2. XXX_ADR       : Real Address with Alignment
// 3. XXX_GAP_CHK   : For Check Memory Gap, for avoid memory waste
// 4. XXX_LEN       : For the Memory size of this Module usage
////////////////////////////////////////////////////////////////////////////////
#define MIU_DRAM_LEN                0x0004000000
#define MIU_DRAM_LEN0               0x0004000000

#define MIU_DRAM_LEN1               0x0000000000

#define ENABLE_MIU_1                0
#define MIU_INTERVAL                0x0000000000

#define MIU0_MMAP_BOUNDARY                0x0000000000
#define MIU1_MMAP_BOUNDARY                0x0000000000
////////////////////////////////////////////////////////////////////////////////
//MEMORY TYPE
////////////////////////////////////////////////////////////////////////////////
#define MIU0                        (0x0000)
#define MIU1                        (0x0001)

#define SW                          (0x0000 << 1)
#define HW                          (0x0001 << 1)
#define SW_HW                       (0x0002 << 1)

#define UNCACHED                    (0x0000 << 3)
#define WRITE_THROUGH               (0x0001 << 3)
#define WRITE_COMBINING             (0x0002 << 3)
#define WRITE_PROTECT               (0x0003 << 3)
#define WRITE_BACK                  (0x0004 << 3)

#define CO_BUF_OFFSET               (6)
#define CO_BUF_L0                   (0x0000 << CO_BUF_OFFSET)
#define CO_BUF_L1                   (0x0001 << CO_BUF_OFFSET)
#define CO_BUF_L2                   (0x0002 << CO_BUF_OFFSET)
#define CO_BUF_L3                   (0x0003 << CO_BUF_OFFSET)
#define CO_BUF_L4                   (0x0004 << CO_BUF_OFFSET)
#define CO_BUF_L5                   (0x0005 << CO_BUF_OFFSET)
#define CO_BUF_L6                   (0x0006 << CO_BUF_OFFSET)
#define CO_BUF_L7                   (0x0007 << CO_BUF_OFFSET)
#define CO_BUF_L8                   (0x0008 << CO_BUF_OFFSET)
#define CO_BUF_L9                   (0x0009 << CO_BUF_OFFSET)
#define CO_BUF_L10                  (0x000A << CO_BUF_OFFSET)
#define CO_BUF_L11                  (0x000B << CO_BUF_OFFSET)
#define MIU0_LAYER_COUNT            (8)
#define MIU1_LAYER_COUNT            (0)

//MIU_0_START
/* AEON_MEM   */
//co_buffer L0
#define AEON_MEM_AVAILABLE                                     0x0000000000
#define AEON_MEM_ADR                                           0x0000000000  //Alignment 0
#define AEON_MEM_GAP_CHK                                       0x0000000000
#define AEON_MEM_LEN                                           0x0000113000
#define AEON_MEM_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* AEON_MM_MEM   */
//co_buffer L1
#define AEON_MM_MEM_AVAILABLE                                  0x0000000000
#define AEON_MM_MEM_ADR                                        0x0000000000  //Alignment 0x00008
#define AEON_MM_MEM_GAP_CHK                                    0x0000000000
#define AEON_MM_MEM_LEN                                        0x0000113000
#define AEON_MM_MEM_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* SECBUF_START   */
//co_buffer L0
#define SECBUF_START_AVAILABLE                                 0x0000113000
#define SECBUF_START_ADR                                       0x0000113000  //Alignment 0x00100
#define SECBUF_START_GAP_CHK                                   0x0000000000
#define SECBUF_START_LEN                                       0x0000004000
#define SECBUF_START_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* BEON_MEM   */
//co_buffer L0
#define BEON_MEM_AVAILABLE                                     0x0000117000
#define BEON_MEM_ADR                                           0x0000120000  //Alignment 0x10000
#define BEON_MEM_GAP_CHK                                       0x0000009000
#define BEON_MEM_LEN                                           0x000028A000
#define BEON_MEM_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* SCHEDULE_LIST   */
//co_buffer L0
#define SCHEDULE_LIST_AVAILABLE                                0x00003AA000
#define SCHEDULE_LIST_ADR                                      0x00003AA000  //Alignment 0x00010
#define SCHEDULE_LIST_GAP_CHK                                  0x0000000000
#define SCHEDULE_LIST_LEN                                      0x0000001000
#define SCHEDULE_LIST_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* USB_BUFFER_START   */
//co_buffer L0
#define USB_BUFFER_START_AVAILABLE                             0x00003AB000
#define USB_BUFFER_START_ADR                                   0x00003AB000  //Alignment 0x01000
#define USB_BUFFER_START_GAP_CHK                               0x0000000000
#define USB_BUFFER_START_LEN                                   0x0000001000
#define USB_BUFFER_START_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* USB_BUFFER2_START   */
//co_buffer L0
#define USB_BUFFER2_START_AVAILABLE                            0x00003AC000
#define USB_BUFFER2_START_ADR                                  0x00003AC000  //Alignment 0x01000
#define USB_BUFFER2_START_GAP_CHK                              0x0000000000
#define USB_BUFFER2_START_LEN                                  0x0000001000
#define USB_BUFFER2_START_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* TSP_VQ_BUFFER   */
//co_buffer L0
#define TSP_VQ_BUFFER_AVAILABLE                                0x00003AD000
#define TSP_VQ_BUFFER_ADR                                      0x00003AD000  //Alignment 0x00010
#define TSP_VQ_BUFFER_GAP_CHK                                  0x0000000000
#define TSP_VQ_BUFFER_LEN                                      0x0000001000
#define TSP_VQ_BUFFER_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE   */
//co_buffer L0
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_AVAILABLE      0x00003AE000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR            0x00003AE000  //Alignment 0x01000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_GAP_CHK        0x0000000000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_LEN            0x0000001000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_MEMORY_TYPE    (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* FILE_SYSTEM_POOL   */
//co_buffer L0
#define FILE_SYSTEM_POOL_AVAILABLE                             0x00003AF000
#define FILE_SYSTEM_POOL_ADR                                   0x00003AF000  //Alignment 0x01000
#define FILE_SYSTEM_POOL_GAP_CHK                               0x0000000000
#define FILE_SYSTEM_POOL_LEN                                   0x0000039800
#define FILE_SYSTEM_POOL_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* MAD_BASE_BUFFER   */
//co_buffer L0
#define MAD_BASE_BUFFER_AVAILABLE                              0x00003E8800
#define MAD_BASE_BUFFER_ADR                                    0x00003E9000  //Alignment 0x01000
#define MAD_BASE_BUFFER_GAP_CHK                                0x0000000800
#define MAD_BASE_BUFFER_LEN                                    0x0000100000
#define MAD_BASE_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* GE_FRAMEBUFFER   */
//co_buffer L0
#define GE_FRAMEBUFFER_AVAILABLE                               0x00004E9000
#define GE_FRAMEBUFFER_ADR                                     0x00004E9000  //Alignment 0x00020
#define GE_FRAMEBUFFER_GAP_CHK                                 0x0000000000
#define GE_FRAMEBUFFER_LEN                                     0x0000102000
#define GE_FRAMEBUFFER_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* GOP_GWIN_RB   */
//co_buffer L1
#define GOP_GWIN_RB_AVAILABLE                                  0x00004E9000
#define GOP_GWIN_RB_ADR                                        0x00004E9000  //Alignment 0x00020
#define GOP_GWIN_RB_GAP_CHK                                    0x0000000000
#define GOP_GWIN_RB_LEN                                        0x0000102000
#define GOP_GWIN_RB_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* CAPTURE_VIDEO_BUFFER   */
//co_buffer L2
#define CAPTURE_VIDEO_BUFFER_AVAILABLE                         0x00004E9000
#define CAPTURE_VIDEO_BUFFER_ADR                               0x00004E9000  //Alignment 0x00020
#define CAPTURE_VIDEO_BUFFER_GAP_CHK                           0x0000000000
#define CAPTURE_VIDEO_BUFFER_LEN                               0x0000102000
#define CAPTURE_VIDEO_BUFFER_MEMORY_TYPE                       (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* GOP_REGDMABASE   */
//co_buffer L0
#define GOP_REGDMABASE_AVAILABLE                               0x00005EB000
#define GOP_REGDMABASE_ADR                                     0x00005EB000  //Alignment 0x00800
#define GOP_REGDMABASE_GAP_CHK                                 0x0000000000
#define GOP_REGDMABASE_LEN                                     0x0000001000
#define GOP_REGDMABASE_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* BMP_START   */
//co_buffer L0
#define BMP_START_AVAILABLE                                    0x00005EC000
#define BMP_START_ADR                                          0x00005EC000  //Alignment 0x00020
#define BMP_START_GAP_CHK                                      0x0000000000
#define BMP_START_LEN                                          0x000004B000
#define BMP_START_MEMORY_TYPE                                  (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* DATABASE_START   */
//co_buffer L0
#define DATABASE_START_AVAILABLE                               0x0000637000
#define DATABASE_START_ADR                                     0x0000637000  //Alignment 0x00020
#define DATABASE_START_GAP_CHK                                 0x0000000000
#define DATABASE_START_LEN                                     0x0000011000
#define DATABASE_START_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* STRING_START   */
//co_buffer L0
#define STRING_START_AVAILABLE                                 0x0000648000
#define STRING_START_ADR                                       0x0000648000  //Alignment 0x00800
#define STRING_START_GAP_CHK                                   0x0000000000
#define STRING_START_LEN                                       0x000005A000
#define STRING_START_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* FONT_START   */
//co_buffer L0
#define FONT_START_AVAILABLE                                   0x00006A2000
#define FONT_START_ADR                                         0x00006A2000  //Alignment 0x00008
#define FONT_START_GAP_CHK                                     0x0000000000
#define FONT_START_LEN                                         0x0000078000
#define FONT_START_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* MENULOAD_BUFFER   */
//co_buffer L0
#define MENULOAD_BUFFER_AVAILABLE                              0x000071A000
#define MENULOAD_BUFFER_ADR                                    0x000071A000  //Alignment 0x00008
#define MENULOAD_BUFFER_GAP_CHK                                0x0000000000
#define MENULOAD_BUFFER_LEN                                    0x0000004000
#define MENULOAD_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* PQ_MAIN   */
//co_buffer L0
#define PQ_MAIN_AVAILABLE                                      0x000071E000
#define PQ_MAIN_ADR                                            0x000071E000  //Alignment 0x00008
#define PQ_MAIN_GAP_CHK                                        0x0000000000
#define PQ_MAIN_LEN                                            0x0000000000
#define PQ_MAIN_MEMORY_TYPE                                    (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* PQ_MAIN_EX   */
//co_buffer L0
#define PQ_MAIN_EX_AVAILABLE                                   0x000071E000
#define PQ_MAIN_EX_ADR                                         0x000071E000  //Alignment 0x00008
#define PQ_MAIN_EX_GAP_CHK                                     0x0000000000
#define PQ_MAIN_EX_LEN                                         0x0000000000
#define PQ_MAIN_EX_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* PQ_TEXT_MAIN   */
//co_buffer L0
#define PQ_TEXT_MAIN_AVAILABLE                                 0x000071E000
#define PQ_TEXT_MAIN_ADR                                       0x000071E000  //Alignment 0x00008
#define PQ_TEXT_MAIN_GAP_CHK                                   0x0000000000
#define PQ_TEXT_MAIN_LEN                                       0x0000000000
#define PQ_TEXT_MAIN_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* POOL_BUFFER   */
//co_buffer L0
#define POOL_BUFFER_AVAILABLE                                  0x000071E000
#define POOL_BUFFER_ADR                                        0x0000720000  //Alignment 0x10000
#define POOL_BUFFER_GAP_CHK                                    0x0000002000
#define POOL_BUFFER_LEN                                        0x000187C400
#define POOL_BUFFER_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* NONE9   */
//co_buffer L3
#define NONE9_AVAILABLE                                        0x0000720000
#define NONE9_ADR                                              0x0000720000  //Alignment 0x00200
#define NONE9_GAP_CHK                                          0x0000000000
#define NONE9_LEN                                              0x0000153000
#define NONE9_MEMORY_TYPE                                      (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* COMB_3D_BUF   */
//co_buffer L6
#define COMB_3D_BUF_AVAILABLE                                  0x0000720000
#define COMB_3D_BUF_ADR                                        0x0000720000  //Alignment 0x00008
#define COMB_3D_BUF_GAP_CHK                                    0x0000000000
#define COMB_3D_BUF_LEN                                        0x0000400000
#define COMB_3D_BUF_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* SCALER_DNR_BUF   */
//co_buffer L6
#define SCALER_DNR_BUF_AVAILABLE                               0x0000B20000
#define SCALER_DNR_BUF_ADR                                     0x0000B20000  //Alignment 0x00020
#define SCALER_DNR_BUF_GAP_CHK                                 0x0000000000
#define SCALER_DNR_BUF_LEN                                     0x0000C00000
#define SCALER_DNR_BUF_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* TTX_POOL   */
//co_buffer L6
#define TTX_POOL_AVAILABLE                                     0x0001720000
#define TTX_POOL_ADR                                           0x0001720000  //Alignment 0x00010
#define TTX_POOL_GAP_CHK                                       0x0000000000
#define TTX_POOL_LEN                                           0x0000499800
#define TTX_POOL_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* CCVBI_RINGBUFFER_START   */
//co_buffer L6
#define CCVBI_RINGBUFFER_START_AVAILABLE                       0x0001BB9800
#define CCVBI_RINGBUFFER_START_ADR                             0x0001BB9800  //Alignment 0x00020
#define CCVBI_RINGBUFFER_START_GAP_CHK                         0x0000000000
#define CCVBI_RINGBUFFER_START_LEN                             0x0000000100
#define CCVBI_RINGBUFFER_START_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* CC608_DISPBUFFER_START   */
//co_buffer L6
#define CC608_DISPBUFFER_START_AVAILABLE                       0x0001BB9900
#define CC608_DISPBUFFER_START_ADR                             0x0001BB9900  //Alignment 0x00020
#define CC608_DISPBUFFER_START_GAP_CHK                         0x0000000000
#define CC608_DISPBUFFER_START_LEN                             0x0000002000
#define CC608_DISPBUFFER_START_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* DTVCC_BLOCK0_START   */
//co_buffer L6
#define DTVCC_BLOCK0_START_AVAILABLE                           0x0001BBB900
#define DTVCC_BLOCK0_START_ADR                                 0x0001BBB900  //Alignment 0x00020
#define DTVCC_BLOCK0_START_GAP_CHK                             0x0000000000
#define DTVCC_BLOCK0_START_LEN                                 0x000000C000
#define DTVCC_BLOCK0_START_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* DTVCC_BLOCK1_START   */
//co_buffer L6
#define DTVCC_BLOCK1_START_AVAILABLE                           0x0001BC7900
#define DTVCC_BLOCK1_START_ADR                                 0x0001BC7900  //Alignment 0x00020
#define DTVCC_BLOCK1_START_GAP_CHK                             0x0000000000
#define DTVCC_BLOCK1_START_LEN                                 0x0000001000
#define DTVCC_BLOCK1_START_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* CC608MVD_RINGBUFFER_START   */
//co_buffer L6
#define CC608MVD_RINGBUFFER_START_AVAILABLE                    0x0001BC8900
#define CC608MVD_RINGBUFFER_START_ADR                          0x0001BC8900  //Alignment 0x00010
#define CC608MVD_RINGBUFFER_START_GAP_CHK                      0x0000000000
#define CC608MVD_RINGBUFFER_START_LEN                          0x0000000010
#define CC608MVD_RINGBUFFER_START_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* CC708MVD_RINGBUFFER_START   */
//co_buffer L6
#define CC708MVD_RINGBUFFER_START_AVAILABLE                    0x0001BC8910
#define CC708MVD_RINGBUFFER_START_ADR                          0x0001BC8910  //Alignment 0x00010
#define CC708MVD_RINGBUFFER_START_GAP_CHK                      0x0000000000
#define CC708MVD_RINGBUFFER_START_LEN                          0x0000000010
#define CC708MVD_RINGBUFFER_START_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* CCMVD_CACHE_BUFFER   */
//co_buffer L6
#define CCMVD_CACHE_BUFFER_AVAILABLE                           0x0001BC8920
#define CCMVD_CACHE_BUFFER_ADR                                 0x0001BC8920  //Alignment 0x00010
#define CCMVD_CACHE_BUFFER_GAP_CHK                             0x0000000000
#define CCMVD_CACHE_BUFFER_LEN                                 0x0000000010
#define CCMVD_CACHE_BUFFER_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* MAD_THUMBNAIL_FB_BUF   */
//co_buffer L5
#define MAD_THUMBNAIL_FB_BUF_AVAILABLE                         0x0000720000
#define MAD_THUMBNAIL_FB_BUF_ADR                               0x0000720000  //Alignment 0x00020
#define MAD_THUMBNAIL_FB_BUF_GAP_CHK                           0x0000000000
#define MAD_THUMBNAIL_FB_BUF_LEN                               0x0000204000
#define MAD_THUMBNAIL_FB_BUF_MEMORY_TYPE                       (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_OUT   */
//co_buffer L5
#define MAD_JPEG_OUT_AVAILABLE                                 0x0000924000
#define MAD_JPEG_OUT_ADR                                       0x0000924000  //Alignment 0x00008
#define MAD_JPEG_OUT_GAP_CHK                                   0x0000000000
#define MAD_JPEG_OUT_LEN                                       0x0000400000
#define MAD_JPEG_OUT_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_DISPLAY   */
//co_buffer L5
#define MAD_JPEG_DISPLAY_AVAILABLE                             0x0000D24000
#define MAD_JPEG_DISPLAY_ADR                                   0x0000D24000  //Alignment 0
#define MAD_JPEG_DISPLAY_GAP_CHK                               0x0000000000
#define MAD_JPEG_DISPLAY_LEN                                   0x0000400000
#define MAD_JPEG_DISPLAY_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_INTERBUFF   */
//co_buffer L5
#define MAD_JPEG_INTERBUFF_AVAILABLE                           0x0001124000
#define MAD_JPEG_INTERBUFF_ADR                                 0x0001124000  //Alignment 0x01000
#define MAD_JPEG_INTERBUFF_GAP_CHK                             0x0000000000
#define MAD_JPEG_INTERBUFF_LEN                                 0x0000630000
#define MAD_JPEG_INTERBUFF_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_READBUFF   */
//co_buffer L5
#define MAD_JPEG_READBUFF_AVAILABLE                            0x0001754000
#define MAD_JPEG_READBUFF_ADR                                  0x0001754000  //Alignment 0x01000
#define MAD_JPEG_READBUFF_GAP_CHK                              0x0000000000
#define MAD_JPEG_READBUFF_LEN                                  0x0000050000
#define MAD_JPEG_READBUFF_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* TEXT_DATA_READ   */
//co_buffer L5
#define TEXT_DATA_READ_AVAILABLE                               0x00017A4000
#define TEXT_DATA_READ_ADR                                     0x00017A4000  //Alignment 0x01000
#define TEXT_DATA_READ_GAP_CHK                                 0x0000000000
#define TEXT_DATA_READ_LEN                                     0x0000010000
#define TEXT_DATA_READ_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* VDEC_AEON   */
//co_buffer L1
#define VDEC_AEON_AVAILABLE                                    0x0000720000
#define VDEC_AEON_ADR                                          0x0000720000  //Alignment 0x00200
#define VDEC_AEON_GAP_CHK                                      0x0000000000
#define VDEC_AEON_LEN                                          0x0000090000
#define VDEC_AEON_MEMORY_TYPE                                  (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_DATA   */
//co_buffer L1
#define VDPLAYER_DATA_AVAILABLE                                0x00007B0000
#define VDPLAYER_DATA_ADR                                      0x00007B0000  //Alignment 0x10000
#define VDPLAYER_DATA_GAP_CHK                                  0x0000000000
#define VDPLAYER_DATA_LEN                                      0x00000C3000
#define VDPLAYER_DATA_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_BITSTREAM_BUFF   */
//co_buffer L3
#define VDPLAYER_BITSTREAM_BUFF_AVAILABLE                      0x0000873000
#define VDPLAYER_BITSTREAM_BUFF_ADR                            0x0000873000  //Alignment 0x00010
#define VDPLAYER_BITSTREAM_BUFF_GAP_CHK                        0x0000000000
#define VDPLAYER_BITSTREAM_BUFF_LEN                            0x0000300000
#define VDPLAYER_BITSTREAM_BUFF_MEMORY_TYPE                    (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* VDEC_BITSTREAM   */
//co_buffer L1
#define VDEC_BITSTREAM_AVAILABLE                               0x0000873000
#define VDEC_BITSTREAM_ADR                                     0x0000873000  //Alignment 0x00008
#define VDEC_BITSTREAM_GAP_CHK                                 0x0000000000
#define VDEC_BITSTREAM_LEN                                     0x0000300000
#define VDEC_BITSTREAM_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDEC_FRAMEBUFFER   */
//co_buffer L1
#define VDEC_FRAMEBUFFER_AVAILABLE                             0x0000B73000
#define VDEC_FRAMEBUFFER_ADR                                   0x0000B73000  //Alignment 0x00200
#define VDEC_FRAMEBUFFER_GAP_CHK                               0x0000000000
#define VDEC_FRAMEBUFFER_LEN                                   0x00013EC000
#define VDEC_FRAMEBUFFER_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_PHOTO_PLAYLIST   */
//co_buffer L1
#define MPLAYER_PHOTO_PLAYLIST_AVAILABLE                       0x0001F5F000
#define MPLAYER_PHOTO_PLAYLIST_ADR                             0x0001F5F000  //Alignment 0
#define MPLAYER_PHOTO_PLAYLIST_GAP_CHK                         0x0000000000
#define MPLAYER_PHOTO_PLAYLIST_LEN                             0x0000006400
#define MPLAYER_PHOTO_PLAYLIST_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_MUSIC_PLAYLIST   */
//co_buffer L1
#define MPLAYER_MUSIC_PLAYLIST_AVAILABLE                       0x0001F65400
#define MPLAYER_MUSIC_PLAYLIST_ADR                             0x0001F65400  //Alignment 0
#define MPLAYER_MUSIC_PLAYLIST_GAP_CHK                         0x0000000000
#define MPLAYER_MUSIC_PLAYLIST_LEN                             0x0000006400
#define MPLAYER_MUSIC_PLAYLIST_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_BITSTREAM_BUFF_EXT   */
//co_buffer L1
#define VDPLAYER_BITSTREAM_BUFF_EXT_AVAILABLE                  0x0001F6B800
#define VDPLAYER_BITSTREAM_BUFF_EXT_ADR                        0x0001F6B800  //Alignment 0x00010
#define VDPLAYER_BITSTREAM_BUFF_EXT_GAP_CHK                    0x0000000000
#define VDPLAYER_BITSTREAM_BUFF_EXT_LEN                        0x0000000000
#define VDPLAYER_BITSTREAM_BUFF_EXT_MEMORY_TYPE                (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_FILE_BUFFER   */
//co_buffer L1
#define MPLAYER_FILE_BUFFER_AVAILABLE                          0x0001F6B800
#define MPLAYER_FILE_BUFFER_ADR                                0x0001F6B800  //Alignment 0
#define MPLAYER_FILE_BUFFER_GAP_CHK                            0x0000000000
#define MPLAYER_FILE_BUFFER_LEN                                0x0000019000
#define MPLAYER_FILE_BUFFER_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_MUSIC_FILE_BUFFER   */
//co_buffer L1
#define MPLAYER_MUSIC_FILE_BUFFER_AVAILABLE                    0x0001F84800
#define MPLAYER_MUSIC_FILE_BUFFER_ADR                          0x0001F84800  //Alignment 0
#define MPLAYER_MUSIC_FILE_BUFFER_GAP_CHK                      0x0000000000
#define MPLAYER_MUSIC_FILE_BUFFER_LEN                          0x000000C800
#define MPLAYER_MUSIC_FILE_BUFFER_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_EMU_PLAYLIST   */
//co_buffer L1
#define MPLAYER_EMU_PLAYLIST_AVAILABLE                         0x0001F91000
#define MPLAYER_EMU_PLAYLIST_ADR                               0x0001F91000  //Alignment 0
#define MPLAYER_EMU_PLAYLIST_GAP_CHK                           0x0000000000
#define MPLAYER_EMU_PLAYLIST_LEN                               0x0000000000
#define MPLAYER_EMU_PLAYLIST_MEMORY_TYPE                       (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MUSIC_LYRIC_BUFFER   */
//co_buffer L5
#define MUSIC_LYRIC_BUFFER_AVAILABLE                           0x00017B4000
#define MUSIC_LYRIC_BUFFER_ADR                                 0x00017B4000  //Alignment 0x00010
#define MUSIC_LYRIC_BUFFER_GAP_CHK                             0x0000000000
#define MUSIC_LYRIC_BUFFER_LEN                                 0x0000006400
#define MUSIC_LYRIC_BUFFER_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MUSIC_LYRIC_TAG   */
//co_buffer L5
#define MUSIC_LYRIC_TAG_AVAILABLE                              0x00017BA400
#define MUSIC_LYRIC_TAG_ADR                                    0x00017BA400  //Alignment 0
#define MUSIC_LYRIC_TAG_GAP_CHK                                0x0000000000
#define MUSIC_LYRIC_TAG_LEN                                    0x0000001000
#define MUSIC_LYRIC_TAG_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MP3_INFO_READ   */
//co_buffer L5
#define MP3_INFO_READ_AVAILABLE                                0x00017BB400
#define MP3_INFO_READ_ADR                                      0x00017BB400  //Alignment 0
#define MP3_INFO_READ_GAP_CHK                                  0x0000000000
#define MP3_INFO_READ_LEN                                      0x0000001000
#define MP3_INFO_READ_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* M4A_BUFFER   */
//co_buffer L5
#define M4A_BUFFER_AVAILABLE                                   0x00017BC400
#define M4A_BUFFER_ADR                                         0x00017BC400  //Alignment 0
#define M4A_BUFFER_GAP_CHK                                     0x0000000000
#define M4A_BUFFER_LEN                                         0x0000004000
#define M4A_BUFFER_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* M4A_STCO   */
//co_buffer L5
#define M4A_STCO_AVAILABLE                                     0x00017C0400
#define M4A_STCO_ADR                                           0x00017C0400  //Alignment 0
#define M4A_STCO_GAP_CHK                                       0x0000000000
#define M4A_STCO_LEN                                           0x0000018000
#define M4A_STCO_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* M4A_STSZ   */
//co_buffer L5
#define M4A_STSZ_AVAILABLE                                     0x00017D8400
#define M4A_STSZ_ADR                                           0x00017D8400  //Alignment 0x00010
#define M4A_STSZ_GAP_CHK                                       0x0000000000
#define M4A_STSZ_LEN                                           0x0000023000
#define M4A_STSZ_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* TEXT_FILE   */
//co_buffer L5
#define TEXT_FILE_AVAILABLE                                    0x00017FB400
#define TEXT_FILE_ADR                                          0x00017FB400  //Alignment 0
#define TEXT_FILE_GAP_CHK                                      0x0000000000
#define TEXT_FILE_LEN                                          0x0000002000
#define TEXT_FILE_MEMORY_TYPE                                  (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* PHOTO_SHARE_MEM   */
//co_buffer L1
#define PHOTO_SHARE_MEM_AVAILABLE                              0x0001F91000
#define PHOTO_SHARE_MEM_ADR                                    0x0001F91000  //Alignment 0
#define PHOTO_SHARE_MEM_GAP_CHK                                0x0000000000
#define PHOTO_SHARE_MEM_LEN                                    0x0000000400
#define PHOTO_SHARE_MEM_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* FILE_OPERATION_INFO_BUFFER   */
//co_buffer L1
#define FILE_OPERATION_INFO_BUFFER_AVAILABLE                   0x0001F91400
#define FILE_OPERATION_INFO_BUFFER_ADR                         0x0001F91400  //Alignment 0
#define FILE_OPERATION_INFO_BUFFER_GAP_CHK                     0x0000000000
#define FILE_OPERATION_INFO_BUFFER_LEN                         0x0000000C00
#define FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE                 (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_SUBTITLE_BITSTREAM_BUFF   */
//co_buffer L1
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_AVAILABLE             0x0001F92000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR                   0x0001F92000  //Alignment 0x01000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_GAP_CHK               0x0000000000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN                   0x0000000000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_MEMORY_TYPE           (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MP4_SUBTITLE_BUFFER   */
//co_buffer L1
#define MP4_SUBTITLE_BUFFER_AVAILABLE                          0x0001F92000
#define MP4_SUBTITLE_BUFFER_ADR                                0x0001F92000  //Alignment 0x01000
#define MP4_SUBTITLE_BUFFER_GAP_CHK                            0x0000000000
#define MP4_SUBTITLE_BUFFER_LEN                                0x000000A000
#define MP4_SUBTITLE_BUFFER_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MP4_SUBTITLE_TAG   */
//co_buffer L1
#define MP4_SUBTITLE_TAG_AVAILABLE                             0x0001F9C000
#define MP4_SUBTITLE_TAG_ADR                                   0x0001F9C000  //Alignment 0x01000
#define MP4_SUBTITLE_TAG_GAP_CHK                               0x0000000000
#define MP4_SUBTITLE_TAG_LEN                                   0x0000000000
#define MP4_SUBTITLE_TAG_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* PATH_INFO_BUFFER   */
//co_buffer L1
#define PATH_INFO_BUFFER_AVAILABLE                             0x0001F9C000
#define PATH_INFO_BUFFER_ADR                                   0x0001F9C000  //Alignment 0
#define PATH_INFO_BUFFER_GAP_CHK                               0x0000000000
#define PATH_INFO_BUFFER_LEN                                   0x0000000400
#define PATH_INFO_BUFFER_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* SUBTITLE   */
//co_buffer L1
#define SUBTITLE_AVAILABLE                                     0x0001F9C400
#define SUBTITLE_ADR                                           0x0001F9C400  //Alignment 0
#define SUBTITLE_GAP_CHK                                       0x0000000000
#define SUBTITLE_LEN                                           0x0000000000
#define SUBTITLE_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* NONE3   */
//co_buffer L4
#define NONE3_AVAILABLE                                        0x0000720000
#define NONE3_ADR                                              0x0000720000  //Alignment 0x00200
#define NONE3_GAP_CHK                                          0x0000000000
#define NONE3_LEN                                              0x0000100000
#define NONE3_MEMORY_TYPE                                      (MIU0 | SW | CO_BUF_L4 | WRITE_BACK)

/* SCALER_DNR_BUF_PREV   */
//co_buffer L5
#define SCALER_DNR_BUF_PREV_AVAILABLE                          0x00017FD400
#define SCALER_DNR_BUF_PREV_ADR                                0x00017FD400  //Alignment 0x00100
#define SCALER_DNR_BUF_PREV_GAP_CHK                            0x0000000000
#define SCALER_DNR_BUF_PREV_LEN                                0x0000280000
#define SCALER_DNR_BUF_PREV_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* VDEC_AEON_MMSD   */
//co_buffer L2
#define VDEC_AEON_MMSD_AVAILABLE                               0x0000720000
#define VDEC_AEON_MMSD_ADR                                     0x0000720000  //Alignment 0x00200
#define VDEC_AEON_MMSD_GAP_CHK                                 0x0000000000
#define VDEC_AEON_MMSD_LEN                                     0x0000090000
#define VDEC_AEON_MMSD_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* VDPLAYER_DATA_SD   */
//co_buffer L2
#define VDPLAYER_DATA_SD_AVAILABLE                             0x00007B0000
#define VDPLAYER_DATA_SD_ADR                                   0x00007B0000  //Alignment 0x00200
#define VDPLAYER_DATA_SD_GAP_CHK                               0x0000000000
#define VDPLAYER_DATA_SD_LEN                                   0x00000C3000
#define VDPLAYER_DATA_SD_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* VDEC_BITSTREAM_SD   */
//co_buffer L2
#define VDEC_BITSTREAM_SD_AVAILABLE                            0x0000873000
#define VDEC_BITSTREAM_SD_ADR                                  0x0000873000  //Alignment 0x00008
#define VDEC_BITSTREAM_SD_GAP_CHK                              0x0000000000
#define VDEC_BITSTREAM_SD_LEN                                  0x0000300000
#define VDEC_BITSTREAM_SD_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* VDEC_FRAMEBUFFER_SD   */
//co_buffer L2
#define VDEC_FRAMEBUFFER_SD_AVAILABLE                          0x0000B73000
#define VDEC_FRAMEBUFFER_SD_ADR                                0x0000B73000  //Alignment 0x00200
#define VDEC_FRAMEBUFFER_SD_GAP_CHK                            0x0000000000
#define VDEC_FRAMEBUFFER_SD_LEN                                0x0000B00000
#define VDEC_FRAMEBUFFER_SD_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* SCALER_DNR_BUF_SDMM   */
//co_buffer L2
#define SCALER_DNR_BUF_SDMM_AVAILABLE                          0x0001673000
#define SCALER_DNR_BUF_SDMM_ADR                                0x0001673000  //Alignment 0x00010
#define SCALER_DNR_BUF_SDMM_GAP_CHK                            0x0000000000
#define SCALER_DNR_BUF_SDMM_LEN                                0x00008EC000
#define SCALER_DNR_BUF_SDMM_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* MPLAYER_TEXT_PLAYLIST   */
//co_buffer L2
#define MPLAYER_TEXT_PLAYLIST_AVAILABLE                        0x0001F5F000
#define MPLAYER_TEXT_PLAYLIST_ADR                              0x0001F5F000  //Alignment 0
#define MPLAYER_TEXT_PLAYLIST_GAP_CHK                          0x0000000000
#define MPLAYER_TEXT_PLAYLIST_LEN                              0x0000006400
#define MPLAYER_TEXT_PLAYLIST_MEMORY_TYPE                      (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* MPLAYER_MOVIE_PLAYLIST   */
//co_buffer L2
#define MPLAYER_MOVIE_PLAYLIST_AVAILABLE                       0x0001F65400
#define MPLAYER_MOVIE_PLAYLIST_ADR                             0x0001F65400  //Alignment 0
#define MPLAYER_MOVIE_PLAYLIST_GAP_CHK                         0x0000000000
#define MPLAYER_MOVIE_PLAYLIST_LEN                             0x0000006400
#define MPLAYER_MOVIE_PLAYLIST_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* SCALER_DNR_UC_BUF   */
//co_buffer L7
#define SCALER_DNR_UC_BUF_AVAILABLE                            0x0000720000
#define SCALER_DNR_UC_BUF_ADR                                  0x0000720000  //Alignment 0x00100
#define SCALER_DNR_UC_BUF_GAP_CHK                              0x0000000000
#define SCALER_DNR_UC_BUF_LEN                                  0x0001000000
#define SCALER_DNR_UC_BUF_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L7 | WRITE_BACK)

/* TTXBUF_START   */
//co_buffer L7
#define TTXBUF_START_AVAILABLE                                 0x0001720000
#define TTXBUF_START_ADR                                       0x0001720000  //Alignment 0x00010
#define TTXBUF_START_GAP_CHK                                   0x0000000000
#define TTXBUF_START_LEN                                       0x0000240000
#define TTXBUF_START_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L7 | WRITE_BACK)

/* TTX_FONT_START   */
//co_buffer L7
#define TTX_FONT_START_AVAILABLE                               0x0001960000
#define TTX_FONT_START_ADR                                     0x0001960000  //Alignment 0x00010
#define TTX_FONT_START_GAP_CHK                                 0x0000000000
#define TTX_FONT_START_LEN                                     0x0000040000
#define TTX_FONT_START_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L7 | WRITE_BACK)

/* GOP_GWIN_TTX   */
//co_buffer L7
#define GOP_GWIN_TTX_AVAILABLE                                 0x00019A0000
#define GOP_GWIN_TTX_ADR                                       0x00019A0000  //Alignment 0x00010
#define GOP_GWIN_TTX_GAP_CHK                                   0x0000000000
#define GOP_GWIN_TTX_LEN                                       0x0000219800
#define GOP_GWIN_TTX_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L7 | WRITE_BACK)

/* NONE_FOR_COMB   */
//co_buffer L3
#define NONE_FOR_COMB_AVAILABLE                                0x0000B73000
#define NONE_FOR_COMB_ADR                                      0x0000B73000  //Alignment 0x00200
#define NONE_FOR_COMB_GAP_CHK                                  0x0000000000
#define NONE_FOR_COMB_LEN                                      0x0000400000
#define NONE_FOR_COMB_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* DOWNLOAD_BUFFER   */
//co_buffer L3
#define DOWNLOAD_BUFFER_AVAILABLE                              0x0000F73000
#define DOWNLOAD_BUFFER_ADR                                    0x0000F73000  //Alignment 0x00010
#define DOWNLOAD_BUFFER_GAP_CHK                                0x0000000000
#define DOWNLOAD_BUFFER_LEN                                    0x0000400000
#define DOWNLOAD_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

//MIU_1_START
//MIU_END
#define MIU0_END_ADR                                           0x0001F9C400
