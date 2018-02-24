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

#define SCA_TOOL_VERSION            "Chakra SCA V1.0.4 "

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
#define MIU_DRAM_LEN                0x0008000000
#define MIU_DRAM_LEN0               0x0008000000

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
#define MIU0_LAYER_COUNT            (7)
#define MIU1_LAYER_COUNT            (0)

//MIU_0_START
/* AEON_MEM   */
//co_buffer L0
#define AEON_MEM_AVAILABLE                                     0x0000000000
#define AEON_MEM_ADR                                           0x0000000000  //Alignment 0
#define AEON_MEM_GAP_CHK                                       0x0000000000
#define AEON_MEM_LEN                                           0x0000A00000
#define AEON_MEM_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* AEON_MM_MEM   */
//co_buffer L1
#define AEON_MM_MEM_AVAILABLE                                  0x0000000000
#define AEON_MM_MEM_ADR                                        0x0000000000  //Alignment 0x00008
#define AEON_MM_MEM_GAP_CHK                                    0x0000000000
#define AEON_MM_MEM_LEN                                        0x000023F000
#define AEON_MM_MEM_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_FILE_BUFFER   */
//co_buffer L1
#define MPLAYER_FILE_BUFFER_AVAILABLE                          0x000023F000
#define MPLAYER_FILE_BUFFER_ADR                                0x000023F000  //Alignment 0
#define MPLAYER_FILE_BUFFER_GAP_CHK                            0x0000000000
#define MPLAYER_FILE_BUFFER_LEN                                0x0000100000
#define MPLAYER_FILE_BUFFER_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_SUBTITLE_BITSTREAM_BUFF   */
//co_buffer L1
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_AVAILABLE             0x000033F000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR                   0x000033F000  //Alignment 0x01000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_GAP_CHK               0x0000000000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN                   0x0000200000
#define VDPLAYER_SUBTITLE_BITSTREAM_BUFF_MEMORY_TYPE           (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_MUSIC_FILE_BUFFER   */
//co_buffer L1
#define MPLAYER_MUSIC_FILE_BUFFER_AVAILABLE                    0x000053F000
#define MPLAYER_MUSIC_FILE_BUFFER_ADR                          0x000053F000  //Alignment 0x01000
#define MPLAYER_MUSIC_FILE_BUFFER_GAP_CHK                      0x0000000000
#define MPLAYER_MUSIC_FILE_BUFFER_LEN                          0x0000080000
#define MPLAYER_MUSIC_FILE_BUFFER_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* HDCP_MBX_BUFFER   */
//co_buffer L0
#define HDCP_MBX_BUFFER_AVAILABLE                              0x0000A00000
#define HDCP_MBX_BUFFER_ADR                                    0x0000A00000  //Alignment 0x10000
#define HDCP_MBX_BUFFER_GAP_CHK                                0x0000000000
#define HDCP_MBX_BUFFER_LEN                                    0x0000010000
#define HDCP_MBX_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* HDCP_KEY_BUFFER   */
//co_buffer L0
#define HDCP_KEY_BUFFER_AVAILABLE                              0x0000A10000
#define HDCP_KEY_BUFFER_ADR                                    0x0000A10000  //Alignment 0x10000
#define HDCP_KEY_BUFFER_GAP_CHK                                0x0000000000
#define HDCP_KEY_BUFFER_LEN                                    0x0000010000
#define HDCP_KEY_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* HDCP_DECRYPT_BUFFER   */
//co_buffer L0
#define HDCP_DECRYPT_BUFFER_AVAILABLE                          0x0000A20000
#define HDCP_DECRYPT_BUFFER_ADR                                0x0000A20000  //Alignment 0x10000
#define HDCP_DECRYPT_BUFFER_GAP_CHK                            0x0000000000
#define HDCP_DECRYPT_BUFFER_LEN                                0x0000010000
#define HDCP_DECRYPT_BUFFER_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* SECURITY_R2   */
//co_buffer L0
#define SECURITY_R2_AVAILABLE                                  0x0000A30000
#define SECURITY_R2_ADR                                        0x0000A30000  //Alignment 0x10000
#define SECURITY_R2_GAP_CHK                                    0x0000000000
#define SECURITY_R2_LEN                                        0x0000100000
#define SECURITY_R2_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* BEON_MEM   */
//co_buffer L0
#define BEON_MEM_AVAILABLE                                     0x0000B30000
#define BEON_MEM_ADR                                           0x0000B30000  //Alignment 0x10000
#define BEON_MEM_GAP_CHK                                       0x0000000000
#define BEON_MEM_LEN                                           0x0000500000
#define BEON_MEM_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* SECBUF_START   */
//co_buffer L0
#define SECBUF_START_AVAILABLE                                 0x0001030000
#define SECBUF_START_ADR                                       0x0001030000  //Alignment 0x10000
#define SECBUF_START_GAP_CHK                                   0x0000000000
#define SECBUF_START_LEN                                       0x0000023000
#define SECBUF_START_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* SCHEDULE_LIST   */
//co_buffer L0
#define SCHEDULE_LIST_AVAILABLE                                0x0001053000
#define SCHEDULE_LIST_ADR                                      0x0001053000  //Alignment 0x00010
#define SCHEDULE_LIST_GAP_CHK                                  0x0000000000
#define SCHEDULE_LIST_LEN                                      0x0000001000
#define SCHEDULE_LIST_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* USB_BUFFER_START   */
//co_buffer L0
#define USB_BUFFER_START_AVAILABLE                             0x0001054000
#define USB_BUFFER_START_ADR                                   0x0001054000  //Alignment 0x01000
#define USB_BUFFER_START_GAP_CHK                               0x0000000000
#define USB_BUFFER_START_LEN                                   0x0000001000
#define USB_BUFFER_START_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* USB_BUFFER2_START   */
//co_buffer L0
#define USB_BUFFER2_START_AVAILABLE                            0x0001055000
#define USB_BUFFER2_START_ADR                                  0x0001055000  //Alignment 0x01000
#define USB_BUFFER2_START_GAP_CHK                              0x0000000000
#define USB_BUFFER2_START_LEN                                  0x0000001000
#define USB_BUFFER2_START_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE   */
//co_buffer L0
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_AVAILABLE      0x0001056000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR            0x0001056000  //Alignment 0x01000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_GAP_CHK        0x0000000000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_LEN            0x0000001000
#define MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_MEMORY_TYPE    (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* FILE_SYSTEM_POOL   */
//co_buffer L0
#define FILE_SYSTEM_POOL_AVAILABLE                             0x0001057000
#define FILE_SYSTEM_POOL_ADR                                   0x0001057000  //Alignment 0x01000
#define FILE_SYSTEM_POOL_GAP_CHK                               0x0000000000
#define FILE_SYSTEM_POOL_LEN                                   0x0000060000
#define FILE_SYSTEM_POOL_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* TSP_VQ_BUFFER   */
//co_buffer L0
#define TSP_VQ_BUFFER_AVAILABLE                                0x00010B7000
#define TSP_VQ_BUFFER_ADR                                      0x00010B7000  //Alignment 0x00010
#define TSP_VQ_BUFFER_GAP_CHK                                  0x0000000000
#define TSP_VQ_BUFFER_LEN                                      0x0000018000
#define TSP_VQ_BUFFER_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* TSP_VQ_BUFFER_CHECK   */
//co_buffer L0
#define TSP_VQ_BUFFER_CHECK_AVAILABLE                          0x00010CF000
#define TSP_VQ_BUFFER_CHECK_ADR                                0x00010CF000  //Alignment 0x00010
#define TSP_VQ_BUFFER_CHECK_GAP_CHK                            0x0000000000
#define TSP_VQ_BUFFER_CHECK_LEN                                0x0000004000
#define TSP_VQ_BUFFER_CHECK_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* DATABASE_START   */
//co_buffer L0
#define DATABASE_START_AVAILABLE                               0x00010D3000
#define DATABASE_START_ADR                                     0x00010D3000  //Alignment 0x00020
#define DATABASE_START_GAP_CHK                                 0x0000000000
#define DATABASE_START_LEN                                     0x00000C1000
#define DATABASE_START_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* MAD_BASE_BUFFER   */
//co_buffer L0
#define MAD_BASE_BUFFER_AVAILABLE                              0x0001194000
#define MAD_BASE_BUFFER_ADR                                    0x0001194000  //Alignment 0x01000
#define MAD_BASE_BUFFER_GAP_CHK                                0x0000000000
#define MAD_BASE_BUFFER_LEN                                    0x000049B800
#define MAD_BASE_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* GOP_REGDMABASE   */
//co_buffer L0
#define GOP_REGDMABASE_AVAILABLE                               0x000162F800
#define GOP_REGDMABASE_ADR                                     0x0001630000  //Alignment 0x04000
#define GOP_REGDMABASE_GAP_CHK                                 0x0000000800
#define GOP_REGDMABASE_LEN                                     0x0000002000
#define GOP_REGDMABASE_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* GE_FRAMEBUFFER   */
//co_buffer L0
#define GE_FRAMEBUFFER_AVAILABLE                               0x0001632000
#define GE_FRAMEBUFFER_ADR                                     0x0001632000  //Alignment 0x00020
#define GE_FRAMEBUFFER_GAP_CHK                                 0x0000000000
#define GE_FRAMEBUFFER_LEN                                     0x0000A23000
#define GE_FRAMEBUFFER_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* GOP_GWIN_RB   */
//co_buffer L1
#define GOP_GWIN_RB_AVAILABLE                                  0x0001632000
#define GOP_GWIN_RB_ADR                                        0x0001632000  //Alignment 0x00020
#define GOP_GWIN_RB_GAP_CHK                                    0x0000000000
#define GOP_GWIN_RB_LEN                                        0x0000A23000
#define GOP_GWIN_RB_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* CAPTURE_VIDEO_BUFFER   */
//co_buffer L2
#define CAPTURE_VIDEO_BUFFER_AVAILABLE                         0x0001632000
#define CAPTURE_VIDEO_BUFFER_ADR                               0x0001632000  //Alignment 0x00020
#define CAPTURE_VIDEO_BUFFER_GAP_CHK                           0x0000000000
#define CAPTURE_VIDEO_BUFFER_LEN                               0x0000180000
#define CAPTURE_VIDEO_BUFFER_MEMORY_TYPE                       (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* BMP_START   */
//co_buffer L0
#define BMP_START_AVAILABLE                                    0x0002055000
#define BMP_START_ADR                                          0x0002055000  //Alignment 0x00020
#define BMP_START_GAP_CHK                                      0x0000000000
#define BMP_START_LEN                                          0x0000100000
#define BMP_START_MEMORY_TYPE                                  (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* STRING_START   */
//co_buffer L0
#define STRING_START_AVAILABLE                                 0x0002155000
#define STRING_START_ADR                                       0x0002155000  //Alignment 0x00800
#define STRING_START_GAP_CHK                                   0x0000000000
#define STRING_START_LEN                                       0x000007C000
#define STRING_START_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* FONT_START   */
//co_buffer L0
#define FONT_START_AVAILABLE                                   0x00021D1000
#define FONT_START_ADR                                         0x00021D1000  //Alignment 0x00008
#define FONT_START_GAP_CHK                                     0x0000000000
#define FONT_START_LEN                                         0x000012C000
#define FONT_START_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* MENULOAD_BUFFER   */
//co_buffer L0
#define MENULOAD_BUFFER_AVAILABLE                              0x00022FD000
#define MENULOAD_BUFFER_ADR                                    0x00022FD000  //Alignment 0x00008
#define MENULOAD_BUFFER_GAP_CHK                                0x0000000000
#define MENULOAD_BUFFER_LEN                                    0x0000004000
#define MENULOAD_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* PQ_MAIN   */
//co_buffer L0
#define PQ_MAIN_AVAILABLE                                      0x0002301000
#define PQ_MAIN_ADR                                            0x0002301000  //Alignment 0x00008
#define PQ_MAIN_GAP_CHK                                        0x0000000000
#define PQ_MAIN_LEN                                            0x0000000000
#define PQ_MAIN_MEMORY_TYPE                                    (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* PQ_MAIN_EX   */
//co_buffer L0
#define PQ_MAIN_EX_AVAILABLE                                   0x0002301000
#define PQ_MAIN_EX_ADR                                         0x0002301000  //Alignment 0x00008
#define PQ_MAIN_EX_GAP_CHK                                     0x0000000000
#define PQ_MAIN_EX_LEN                                         0x0000000000
#define PQ_MAIN_EX_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* PQ_TEXT_MAIN   */
//co_buffer L0
#define PQ_TEXT_MAIN_AVAILABLE                                 0x0002301000
#define PQ_TEXT_MAIN_ADR                                       0x0002301000  //Alignment 0x00008
#define PQ_TEXT_MAIN_GAP_CHK                                   0x0000000000
#define PQ_TEXT_MAIN_LEN                                       0x0000000000
#define PQ_TEXT_MAIN_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* VE_FRAMEBUFFER   */
//co_buffer L0
#define VE_FRAMEBUFFER_AVAILABLE                               0x0002301000
#define VE_FRAMEBUFFER_ADR                                     0x0002301000  //Alignment 0x00010
#define VE_FRAMEBUFFER_GAP_CHK                                 0x0000000000
#define VE_FRAMEBUFFER_LEN                                     0x0000000000
#define VE_FRAMEBUFFER_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* AUDIO_DSPBIN_DECOMPRESS_TEMP_BUFFER   */
//co_buffer L0
#define AUDIO_DSPBIN_DECOMPRESS_TEMP_BUFFER_AVAILABLE          0x0002301000
#define AUDIO_DSPBIN_DECOMPRESS_TEMP_BUFFER_ADR                0x0002301000  //Alignment 0x01000
#define AUDIO_DSPBIN_DECOMPRESS_TEMP_BUFFER_GAP_CHK            0x0000000000
#define AUDIO_DSPBIN_DECOMPRESS_TEMP_BUFFER_LEN                0x000003B000
#define AUDIO_DSPBIN_DECOMPRESS_TEMP_BUFFER_MEMORY_TYPE        (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* POOL_BUFFER   */
//co_buffer L0
#define POOL_BUFFER_AVAILABLE                                  0x000233C000
#define POOL_BUFFER_ADR                                        0x000233C000  //Alignment 0x01000
#define POOL_BUFFER_GAP_CHK                                    0x0000000000
#define POOL_BUFFER_LEN                                        0x0005CC4000
#define POOL_BUFFER_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L0 | WRITE_BACK)

/* NONE9   */
//co_buffer L3
#define NONE9_AVAILABLE                                        0x000233C000
#define NONE9_ADR                                              0x000233C000  //Alignment 0x00200
#define NONE9_GAP_CHK                                          0x0000000000
#define NONE9_LEN                                              0x0000200000
#define NONE9_MEMORY_TYPE                                      (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* NONE10   */
//co_buffer L3
#define NONE10_AVAILABLE                                       0x000253C000
#define NONE10_ADR                                             0x000253C000  //Alignment 0x00020
#define NONE10_GAP_CHK                                         0x0000000000
#define NONE10_LEN                                             0x00003A0000
#define NONE10_MEMORY_TYPE                                     (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* DOWNLOAD_BUFFER   */
//co_buffer L3
#define DOWNLOAD_BUFFER_AVAILABLE                              0x00028DC000
#define DOWNLOAD_BUFFER_ADR                                    0x00028DC000  //Alignment 0x00020
#define DOWNLOAD_BUFFER_GAP_CHK                                0x0000000000
#define DOWNLOAD_BUFFER_LEN                                    0x0000800000
#define DOWNLOAD_BUFFER_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* NONE5   */
//co_buffer L3
#define NONE5_AVAILABLE                                        0x00030DC000
#define NONE5_ADR                                              0x00030DC000  //Alignment 0
#define NONE5_GAP_CHK                                          0x0000000000
#define NONE5_LEN                                              0x0001700000
#define NONE5_MEMORY_TYPE                                      (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* MHEG5_BUFFER   */
//co_buffer L3
#define MHEG5_BUFFER_AVAILABLE                                 0x00047DC000
#define MHEG5_BUFFER_ADR                                       0x00047DC000  //Alignment 0x00100
#define MHEG5_BUFFER_GAP_CHK                                   0x0000000000
#define MHEG5_BUFFER_LEN                                       0x0000880000
#define MHEG5_BUFFER_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* MHEG5_JPEG   */
//co_buffer L3
#define MHEG5_JPEG_AVAILABLE                                   0x000505C000
#define MHEG5_JPEG_ADR                                         0x000505C000  //Alignment 0x00100
#define MHEG5_JPEG_GAP_CHK                                     0x0000000000
#define MHEG5_JPEG_LEN                                         0x0000500000
#define MHEG5_JPEG_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* NONE_ALIGN_WITH_TTX   */
//co_buffer L3
#define NONE_ALIGN_WITH_TTX_AVAILABLE                          0x000555C000
#define NONE_ALIGN_WITH_TTX_ADR                                0x000555C000  //Alignment 0x01000
#define NONE_ALIGN_WITH_TTX_GAP_CHK                            0x0000000000
#define NONE_ALIGN_WITH_TTX_LEN                                0x0000F07000
#define NONE_ALIGN_WITH_TTX_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* CCVBI_RINGBUFFER_START   */
//co_buffer L3
#define CCVBI_RINGBUFFER_START_AVAILABLE                       0x0006463000
#define CCVBI_RINGBUFFER_START_ADR                             0x0006463000  //Alignment 0x00008
#define CCVBI_RINGBUFFER_START_GAP_CHK                         0x0000000000
#define CCVBI_RINGBUFFER_START_LEN                             0x0000000100
#define CCVBI_RINGBUFFER_START_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* DTVCC_BLOCK0_START   */
//co_buffer L3
#define DTVCC_BLOCK0_START_AVAILABLE                           0x0006463100
#define DTVCC_BLOCK0_START_ADR                                 0x0006463100  //Alignment 0x00008
#define DTVCC_BLOCK0_START_GAP_CHK                             0x0000000000
#define DTVCC_BLOCK0_START_LEN                                 0x000000C000
#define DTVCC_BLOCK0_START_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* DTVCC_BLOCK1_START   */
//co_buffer L3
#define DTVCC_BLOCK1_START_AVAILABLE                           0x000646F100
#define DTVCC_BLOCK1_START_ADR                                 0x000646F100  //Alignment 0x00008
#define DTVCC_BLOCK1_START_GAP_CHK                             0x0000000000
#define DTVCC_BLOCK1_START_LEN                                 0x0000001000
#define DTVCC_BLOCK1_START_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* DTVCC_PES_START   */
//co_buffer L3
#define DTVCC_PES_START_AVAILABLE                              0x0006470100
#define DTVCC_PES_START_ADR                                    0x0006470100  //Alignment 0x00008
#define DTVCC_PES_START_GAP_CHK                                0x0000000000
#define DTVCC_PES_START_LEN                                    0x0000001000
#define DTVCC_PES_START_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* DTVCC_QUEUE_START   */
//co_buffer L3
#define DTVCC_QUEUE_START_AVAILABLE                            0x0006471100
#define DTVCC_QUEUE_START_ADR                                  0x0006471100  //Alignment 0x00008
#define DTVCC_QUEUE_START_GAP_CHK                              0x0000000000
#define DTVCC_QUEUE_START_LEN                                  0x00000A0000
#define DTVCC_QUEUE_START_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* CC608MVD_RINGBUFFER_START   */
//co_buffer L3
#define CC608MVD_RINGBUFFER_START_AVAILABLE                    0x0006511100
#define CC608MVD_RINGBUFFER_START_ADR                          0x0006511100  //Alignment 0x00020
#define CC608MVD_RINGBUFFER_START_GAP_CHK                      0x0000000000
#define CC608MVD_RINGBUFFER_START_LEN                          0x0000004000
#define CC608MVD_RINGBUFFER_START_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* CC708MVD_RINGBUFFER_START   */
//co_buffer L3
#define CC708MVD_RINGBUFFER_START_AVAILABLE                    0x0006515100
#define CC708MVD_RINGBUFFER_START_ADR                          0x0006515100  //Alignment 0x00020
#define CC708MVD_RINGBUFFER_START_GAP_CHK                      0x0000000000
#define CC708MVD_RINGBUFFER_START_LEN                          0x0000004800
#define CC708MVD_RINGBUFFER_START_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* CCMVD_CACHE_BUFFER   */
//co_buffer L3
#define CCMVD_CACHE_BUFFER_AVAILABLE                           0x0006519900
#define CCMVD_CACHE_BUFFER_ADR                                 0x0006519900  //Alignment 0x00008
#define CCMVD_CACHE_BUFFER_GAP_CHK                             0x0000000000
#define CCMVD_CACHE_BUFFER_LEN                                 0x0000002000
#define CCMVD_CACHE_BUFFER_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* CC608_DISPBUFFER_START   */
//co_buffer L3
#define CC608_DISPBUFFER_START_AVAILABLE                       0x000651B900
#define CC608_DISPBUFFER_START_ADR                             0x000651B900  //Alignment 0x00008
#define CC608_DISPBUFFER_START_GAP_CHK                         0x0000000000
#define CC608_DISPBUFFER_START_LEN                             0x0000002000
#define CC608_DISPBUFFER_START_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* TCVT_BUFFER_START   */
//co_buffer L3
#define TCVT_BUFFER_START_AVAILABLE                            0x000651D900
#define TCVT_BUFFER_START_ADR                                  0x000651D900  //Alignment 0x00020
#define TCVT_BUFFER_START_GAP_CHK                              0x0000000000
#define TCVT_BUFFER_START_LEN                                  0x0000001000
#define TCVT_BUFFER_START_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* CVCT_BUFFER_START   */
//co_buffer L3
#define CVCT_BUFFER_START_AVAILABLE                            0x000651E900
#define CVCT_BUFFER_START_ADR                                  0x000651E900  //Alignment 0x00020
#define CVCT_BUFFER_START_GAP_CHK                              0x0000000000
#define CVCT_BUFFER_START_LEN                                  0x0000001000
#define CVCT_BUFFER_START_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L3 | WRITE_BACK)

/* MAD_JPEG_READBUFF   */
//co_buffer L5
#define MAD_JPEG_READBUFF_AVAILABLE                            0x000233C000
#define MAD_JPEG_READBUFF_ADR                                  0x000233C000  //Alignment 0x00020
#define MAD_JPEG_READBUFF_GAP_CHK                              0x0000000000
#define MAD_JPEG_READBUFF_LEN                                  0x0000100000
#define MAD_JPEG_READBUFF_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* NONE20   */
//co_buffer L5
#define NONE20_AVAILABLE                                       0x000243C000
#define NONE20_ADR                                             0x000243C000  //Alignment 0x00020
#define NONE20_GAP_CHK                                         0x0000000000
#define NONE20_LEN                                             0x0000100000
#define NONE20_MEMORY_TYPE                                     (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_THUMBNAIL_FB_BUF   */
//co_buffer L5
#define MAD_THUMBNAIL_FB_BUF_AVAILABLE                         0x000253C000
#define MAD_THUMBNAIL_FB_BUF_ADR                               0x000253C000  //Alignment 0x00020
#define MAD_THUMBNAIL_FB_BUF_GAP_CHK                           0x0000000000
#define MAD_THUMBNAIL_FB_BUF_LEN                               0x0000400000
#define MAD_THUMBNAIL_FB_BUF_MEMORY_TYPE                       (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* NONE21   */
//co_buffer L5
#define NONE21_AVAILABLE                                       0x000293C000
#define NONE21_ADR                                             0x000293C000  //Alignment 0x00020
#define NONE21_GAP_CHK                                         0x0000000000
#define NONE21_LEN                                             0x0000000000
#define NONE21_MEMORY_TYPE                                     (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_INTERBUFF   */
//co_buffer L5
#define MAD_JPEG_INTERBUFF_AVAILABLE                           0x000293C000
#define MAD_JPEG_INTERBUFF_ADR                                 0x000293C000  //Alignment 0x00020
#define MAD_JPEG_INTERBUFF_GAP_CHK                             0x0000000000
#define MAD_JPEG_INTERBUFF_LEN                                 0x0001600000
#define MAD_JPEG_INTERBUFF_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_OUT   */
//co_buffer L5
#define MAD_JPEG_OUT_AVAILABLE                                 0x0003F3C000
#define MAD_JPEG_OUT_ADR                                       0x0003F3C000  //Alignment 0x00008
#define MAD_JPEG_OUT_GAP_CHK                                   0x0000000000
#define MAD_JPEG_OUT_LEN                                       0x0001000000
#define MAD_JPEG_OUT_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MAD_JPEG_DISPLAY   */
//co_buffer L5
#define MAD_JPEG_DISPLAY_AVAILABLE                             0x0004F3C000
#define MAD_JPEG_DISPLAY_ADR                                   0x0004F3C000  //Alignment 0
#define MAD_JPEG_DISPLAY_GAP_CHK                               0x0000000000
#define MAD_JPEG_DISPLAY_LEN                                   0x0001000000
#define MAD_JPEG_DISPLAY_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MPO_DISPLAY_BUFFER   */
//co_buffer L5
#define MPO_DISPLAY_BUFFER_AVAILABLE                           0x0005F3C000
#define MPO_DISPLAY_BUFFER_ADR                                 0x0005F3C000  //Alignment 0x00020
#define MPO_DISPLAY_BUFFER_GAP_CHK                             0x0000000000
#define MPO_DISPLAY_BUFFER_LEN                                 0x0000000000
#define MPO_DISPLAY_BUFFER_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* SCALER_DNR_4K_PHOTO_BUF   */
//co_buffer L5
#define SCALER_DNR_4K_PHOTO_BUF_AVAILABLE                      0x0005F3C000
#define SCALER_DNR_4K_PHOTO_BUF_ADR                            0x0005F3C000  //Alignment 0x00020
#define SCALER_DNR_4K_PHOTO_BUF_GAP_CHK                        0x0000000000
#define SCALER_DNR_4K_PHOTO_BUF_LEN                            0x0002000000
#define SCALER_DNR_4K_PHOTO_BUF_MEMORY_TYPE                    (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* VDEC_AEON   */
//co_buffer L1
#define VDEC_AEON_AVAILABLE                                    0x000233C000
#define VDEC_AEON_ADR                                          0x000233C000  //Alignment 0x00200
#define VDEC_AEON_GAP_CHK                                      0x0000000000
#define VDEC_AEON_LEN                                          0x0000200000
#define VDEC_AEON_MEMORY_TYPE                                  (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* SUBTITLE   */
//co_buffer L1
#define SUBTITLE_AVAILABLE                                     0x000253C000
#define SUBTITLE_ADR                                           0x000253C000  //Alignment 0x00020
#define SUBTITLE_GAP_CHK                                       0x0000000000
#define SUBTITLE_LEN                                           0x00003A0000
#define SUBTITLE_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDEC_FRAMEBUFFER   */
//co_buffer L1
#define VDEC_FRAMEBUFFER_AVAILABLE                             0x00028DC000
#define VDEC_FRAMEBUFFER_ADR                                   0x00028DC000  //Alignment 0x00200
#define VDEC_FRAMEBUFFER_GAP_CHK                               0x0000000000
#define VDEC_FRAMEBUFFER_LEN                                   0x0001900000
#define VDEC_FRAMEBUFFER_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDEC_BITSTREAM   */
//co_buffer L1
#define VDEC_BITSTREAM_AVAILABLE                               0x00041DC000
#define VDEC_BITSTREAM_ADR                                     0x00041DC000  //Alignment 0x00008
#define VDEC_BITSTREAM_GAP_CHK                                 0x0000000000
#define VDEC_BITSTREAM_LEN                                     0x0000600000
#define VDEC_BITSTREAM_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_BITSTREAM_BUFF   */
//co_buffer L1
#define VDPLAYER_BITSTREAM_BUFF_AVAILABLE                      0x00047DC000
#define VDPLAYER_BITSTREAM_BUFF_ADR                            0x00047DC000  //Alignment 0x00010
#define VDPLAYER_BITSTREAM_BUFF_GAP_CHK                        0x0000000000
#define VDPLAYER_BITSTREAM_BUFF_LEN                            0x0000400000
#define VDPLAYER_BITSTREAM_BUFF_MEMORY_TYPE                    (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_BITSTREAM_BUFF_EXT   */
//co_buffer L1
#define VDPLAYER_BITSTREAM_BUFF_EXT_AVAILABLE                  0x0004BDC000
#define VDPLAYER_BITSTREAM_BUFF_EXT_ADR                        0x0004BDC000  //Alignment 0x00010
#define VDPLAYER_BITSTREAM_BUFF_EXT_GAP_CHK                    0x0000000000
#define VDPLAYER_BITSTREAM_BUFF_EXT_LEN                        0x0000400000
#define VDPLAYER_BITSTREAM_BUFF_EXT_MEMORY_TYPE                (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* VDPLAYER_DATA   */
//co_buffer L1
#define VDPLAYER_DATA_AVAILABLE                                0x0004FDC000
#define VDPLAYER_DATA_ADR                                      0x0004FDC000  //Alignment 0x01000
#define VDPLAYER_DATA_GAP_CHK                                  0x0000000000
#define VDPLAYER_DATA_LEN                                      0x0000500000
#define VDPLAYER_DATA_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* SCALER_DNR_BUF   */
//co_buffer L1
#define SCALER_DNR_BUF_AVAILABLE                               0x00054DC000
#define SCALER_DNR_BUF_ADR                                     0x00054DC000  //Alignment 0x00100
#define SCALER_DNR_BUF_GAP_CHK                                 0x0000000000
#define SCALER_DNR_BUF_LEN                                     0x0001200000
#define SCALER_DNR_BUF_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L1 | WRITE_BACK)

/* MPLAYER_PHOTO_PLAYLIST   */
//co_buffer L5
#define MPLAYER_PHOTO_PLAYLIST_AVAILABLE                       0x0007F3C000
#define MPLAYER_PHOTO_PLAYLIST_ADR                             0x0007F3C000  //Alignment 0
#define MPLAYER_PHOTO_PLAYLIST_GAP_CHK                         0x0000000000
#define MPLAYER_PHOTO_PLAYLIST_LEN                             0x0000006400
#define MPLAYER_PHOTO_PLAYLIST_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MPLAYER_MUSIC_PLAYLIST   */
//co_buffer L5
#define MPLAYER_MUSIC_PLAYLIST_AVAILABLE                       0x0007F42400
#define MPLAYER_MUSIC_PLAYLIST_ADR                             0x0007F42400  //Alignment 0
#define MPLAYER_MUSIC_PLAYLIST_GAP_CHK                         0x0000000000
#define MPLAYER_MUSIC_PLAYLIST_LEN                             0x0000006400
#define MPLAYER_MUSIC_PLAYLIST_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MPLAYER_MOVIE_PLAYLIST   */
//co_buffer L5
#define MPLAYER_MOVIE_PLAYLIST_AVAILABLE                       0x0007F48800
#define MPLAYER_MOVIE_PLAYLIST_ADR                             0x0007F48800  //Alignment 0
#define MPLAYER_MOVIE_PLAYLIST_GAP_CHK                         0x0000000000
#define MPLAYER_MOVIE_PLAYLIST_LEN                             0x0000006400
#define MPLAYER_MOVIE_PLAYLIST_MEMORY_TYPE                     (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MPLAYER_TEXT_PLAYLIST   */
//co_buffer L5
#define MPLAYER_TEXT_PLAYLIST_AVAILABLE                        0x0007F4EC00
#define MPLAYER_TEXT_PLAYLIST_ADR                              0x0007F4EC00  //Alignment 0
#define MPLAYER_TEXT_PLAYLIST_GAP_CHK                          0x0000000000
#define MPLAYER_TEXT_PLAYLIST_LEN                              0x0000006400
#define MPLAYER_TEXT_PLAYLIST_MEMORY_TYPE                      (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MPLAYER_EMU_PLAYLIST   */
//co_buffer L5
#define MPLAYER_EMU_PLAYLIST_AVAILABLE                         0x0007F55000
#define MPLAYER_EMU_PLAYLIST_ADR                               0x0007F55000  //Alignment 0
#define MPLAYER_EMU_PLAYLIST_GAP_CHK                           0x0000000000
#define MPLAYER_EMU_PLAYLIST_LEN                               0x0000006400
#define MPLAYER_EMU_PLAYLIST_MEMORY_TYPE                       (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MUSIC_LYRIC_BUFFER   */
//co_buffer L5
#define MUSIC_LYRIC_BUFFER_AVAILABLE                           0x0007F5B400
#define MUSIC_LYRIC_BUFFER_ADR                                 0x0007F5B400  //Alignment 0
#define MUSIC_LYRIC_BUFFER_GAP_CHK                             0x0000000000
#define MUSIC_LYRIC_BUFFER_LEN                                 0x0000010000
#define MUSIC_LYRIC_BUFFER_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MUSIC_LYRIC_TAG   */
//co_buffer L5
#define MUSIC_LYRIC_TAG_AVAILABLE                              0x0007F6B400
#define MUSIC_LYRIC_TAG_ADR                                    0x0007F6B400  //Alignment 0
#define MUSIC_LYRIC_TAG_GAP_CHK                                0x0000000000
#define MUSIC_LYRIC_TAG_LEN                                    0x0000001000
#define MUSIC_LYRIC_TAG_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MP3_INFO_READ   */
//co_buffer L5
#define MP3_INFO_READ_AVAILABLE                                0x0007F6C400
#define MP3_INFO_READ_ADR                                      0x0007F6C400  //Alignment 0
#define MP3_INFO_READ_GAP_CHK                                  0x0000000000
#define MP3_INFO_READ_LEN                                      0x0000001000
#define MP3_INFO_READ_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* M4A_BUFFER   */
//co_buffer L5
#define M4A_BUFFER_AVAILABLE                                   0x0007F6D400
#define M4A_BUFFER_ADR                                         0x0007F6D400  //Alignment 0
#define M4A_BUFFER_GAP_CHK                                     0x0000000000
#define M4A_BUFFER_LEN                                         0x0000004000
#define M4A_BUFFER_MEMORY_TYPE                                 (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* M4A_STCO   */
//co_buffer L5
#define M4A_STCO_AVAILABLE                                     0x0007F71400
#define M4A_STCO_ADR                                           0x0007F71400  //Alignment 0
#define M4A_STCO_GAP_CHK                                       0x0000000000
#define M4A_STCO_LEN                                           0x0000018000
#define M4A_STCO_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* TEXT_FILE   */
//co_buffer L5
#define TEXT_FILE_AVAILABLE                                    0x0007F89400
#define TEXT_FILE_ADR                                          0x0007F89400  //Alignment 0
#define TEXT_FILE_GAP_CHK                                      0x0000000000
#define TEXT_FILE_LEN                                          0x0000002000
#define TEXT_FILE_MEMORY_TYPE                                  (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* PHOTO_SHARE_MEM   */
//co_buffer L5
#define PHOTO_SHARE_MEM_AVAILABLE                              0x0007F8B400
#define PHOTO_SHARE_MEM_ADR                                    0x0007F8B400  //Alignment 0
#define PHOTO_SHARE_MEM_GAP_CHK                                0x0000000000
#define PHOTO_SHARE_MEM_LEN                                    0x0000000400
#define PHOTO_SHARE_MEM_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* FILE_OPERATION_INFO_BUFFER   */
//co_buffer L5
#define FILE_OPERATION_INFO_BUFFER_AVAILABLE                   0x0007F8B800
#define FILE_OPERATION_INFO_BUFFER_ADR                         0x0007F8B800  //Alignment 0
#define FILE_OPERATION_INFO_BUFFER_GAP_CHK                     0x0000000000
#define FILE_OPERATION_INFO_BUFFER_LEN                         0x0000000C00
#define FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE                 (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* PATH_INFO_BUFFER   */
//co_buffer L5
#define PATH_INFO_BUFFER_AVAILABLE                             0x0007F8C400
#define PATH_INFO_BUFFER_ADR                                   0x0007F8C400  //Alignment 0
#define PATH_INFO_BUFFER_GAP_CHK                               0x0000000000
#define PATH_INFO_BUFFER_LEN                                   0x0000000400
#define PATH_INFO_BUFFER_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* MP4_SUBTITLE_BUFFER   */
//co_buffer L5
#define MP4_SUBTITLE_BUFFER_AVAILABLE                          0x0007F8C800
#define MP4_SUBTITLE_BUFFER_ADR                                0x0007F8C800  //Alignment 0x00100
#define MP4_SUBTITLE_BUFFER_GAP_CHK                            0x0000000000
#define MP4_SUBTITLE_BUFFER_LEN                                0x000000A000
#define MP4_SUBTITLE_BUFFER_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* NONE1   */
//co_buffer L2
#define NONE1_AVAILABLE                                        0x000233C000
#define NONE1_ADR                                              0x000233C000  //Alignment 0x00200
#define NONE1_GAP_CHK                                          0x0000000000
#define NONE1_LEN                                              0x0000200000
#define NONE1_MEMORY_TYPE                                      (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* NONE2   */
//co_buffer L2
#define NONE2_AVAILABLE                                        0x000253C000
#define NONE2_ADR                                              0x000253C000  //Alignment 0x00020
#define NONE2_GAP_CHK                                          0x0000000000
#define NONE2_LEN                                              0x00003A0000
#define NONE2_MEMORY_TYPE                                      (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* VDEC_FRAMEBUFFER_SD   */
//co_buffer L2
#define VDEC_FRAMEBUFFER_SD_AVAILABLE                          0x00028DC000
#define VDEC_FRAMEBUFFER_SD_ADR                                0x00028DC000  //Alignment 0x00200
#define VDEC_FRAMEBUFFER_SD_GAP_CHK                            0x0000000000
#define VDEC_FRAMEBUFFER_SD_LEN                                0x0001900000
#define VDEC_FRAMEBUFFER_SD_MEMORY_TYPE                        (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* VDEC_BITSTREAM_SD   */
//co_buffer L2
#define VDEC_BITSTREAM_SD_AVAILABLE                            0x00041DC000
#define VDEC_BITSTREAM_SD_ADR                                  0x00041DC000  //Alignment 0x00008
#define VDEC_BITSTREAM_SD_GAP_CHK                              0x0000000000
#define VDEC_BITSTREAM_SD_LEN                                  0x0000600000
#define VDEC_BITSTREAM_SD_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_TRICK_MODE   */
//co_buffer L2
#define PVR_TRICK_MODE_AVAILABLE                               0x00047DC000
#define PVR_TRICK_MODE_ADR                                     0x00047DC000  //Alignment 0x00010
#define PVR_TRICK_MODE_GAP_CHK                                 0x0000000000
#define PVR_TRICK_MODE_LEN                                     0x0000300000
#define PVR_TRICK_MODE_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_READ_SDRAM   */
//co_buffer L2
#define PVR_READ_SDRAM_AVAILABLE                               0x0004ADC000
#define PVR_READ_SDRAM_ADR                                     0x0004ADC000  //Alignment 0x00010
#define PVR_READ_SDRAM_GAP_CHK                                 0x0000000000
#define PVR_READ_SDRAM_LEN                                     0x00001B0000
#define PVR_READ_SDRAM_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_READ_METADATA_BUFFER   */
//co_buffer L2
#define PVR_READ_METADATA_BUFFER_AVAILABLE                     0x0004C8C000
#define PVR_READ_METADATA_BUFFER_ADR                           0x0004C8C000  //Alignment 0x00010
#define PVR_READ_METADATA_BUFFER_GAP_CHK                       0x0000000000
#define PVR_READ_METADATA_BUFFER_LEN                           0x0000000C00
#define PVR_READ_METADATA_BUFFER_MEMORY_TYPE                   (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_BROWSER_BUFFER   */
//co_buffer L2
#define PVR_BROWSER_BUFFER_AVAILABLE                           0x0004C8CC00
#define PVR_BROWSER_BUFFER_ADR                                 0x0004C8CC00  //Alignment 0x00010
#define PVR_BROWSER_BUFFER_GAP_CHK                             0x0000000000
#define PVR_BROWSER_BUFFER_LEN                                 0x0000200000
#define PVR_BROWSER_BUFFER_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_WRITE_METADATA_BUFFER   */
//co_buffer L2
#define PVR_WRITE_METADATA_BUFFER_AVAILABLE                    0x0004E8CC00
#define PVR_WRITE_METADATA_BUFFER_ADR                          0x0004E8CC00  //Alignment 0x00010
#define PVR_WRITE_METADATA_BUFFER_GAP_CHK                      0x0000000000
#define PVR_WRITE_METADATA_BUFFER_LEN                          0x0000060000
#define PVR_WRITE_METADATA_BUFFER_MEMORY_TYPE                  (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_WRITE_SDRAM   */
//co_buffer L2
#define PVR_WRITE_SDRAM_AVAILABLE                              0x0004EECC00
#define PVR_WRITE_SDRAM_ADR                                    0x0004EED000  //Alignment 0x01000
#define PVR_WRITE_SDRAM_GAP_CHK                                0x0000000400
#define PVR_WRITE_SDRAM_LEN                                    0x0000360000
#define PVR_WRITE_SDRAM_MEMORY_TYPE                            (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* PVR_IO_BUFFER   */
//co_buffer L2
#define PVR_IO_BUFFER_AVAILABLE                                0x000524D000
#define PVR_IO_BUFFER_ADR                                      0x000524D000  //Alignment 0x01000
#define PVR_IO_BUFFER_GAP_CHK                                  0x0000000000
#define PVR_IO_BUFFER_LEN                                      0x0000010000
#define PVR_IO_BUFFER_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* BULK_FILE_SYSTEM   */
//co_buffer L2
#define BULK_FILE_SYSTEM_AVAILABLE                             0x000525D000
#define BULK_FILE_SYSTEM_ADR                                   0x000525D000  //Alignment 0x01000
#define BULK_FILE_SYSTEM_GAP_CHK                               0x0000000000
#define BULK_FILE_SYSTEM_LEN                                   0x0000006000
#define BULK_FILE_SYSTEM_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* NONE_ALIGN_MHEG5   */
//co_buffer L2
#define NONE_ALIGN_MHEG5_AVAILABLE                             0x0005263000
#define NONE_ALIGN_MHEG5_ADR                                   0x0005263000  //Alignment 0x01000
#define NONE_ALIGN_MHEG5_GAP_CHK                               0x0000000000
#define NONE_ALIGN_MHEG5_LEN                                   0x0000300000
#define NONE_ALIGN_MHEG5_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* EVENTDB_SDRAM   */
//co_buffer L2
#define EVENTDB_SDRAM_AVAILABLE                                0x0005563000
#define EVENTDB_SDRAM_ADR                                      0x0005563000  //Alignment 0x00010
#define EVENTDB_SDRAM_GAP_CHK                                  0x0000000000
#define EVENTDB_SDRAM_LEN                                      0x0000500000
#define EVENTDB_SDRAM_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* EPGEXTDB_SDRAM   */
//co_buffer L2
#define EPGEXTDB_SDRAM_AVAILABLE                               0x0005A63000
#define EPGEXTDB_SDRAM_ADR                                     0x0005A63000  //Alignment 0x00010
#define EPGEXTDB_SDRAM_GAP_CHK                                 0x0000000000
#define EPGEXTDB_SDRAM_LEN                                     0x0000A00000
#define EPGEXTDB_SDRAM_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* TTXBUF_START   */
//co_buffer L2
#define TTXBUF_START_AVAILABLE                                 0x0006463000
#define TTXBUF_START_ADR                                       0x0006463000  //Alignment 0x00008
#define TTXBUF_START_GAP_CHK                                   0x0000000000
#define TTXBUF_START_LEN                                       0x00000D4800
#define TTXBUF_START_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* SI_MONITOR_DB   */
//co_buffer L2
#define SI_MONITOR_DB_AVAILABLE                                0x0006537800
#define SI_MONITOR_DB_ADR                                      0x0006537800  //Alignment 0x00008
#define SI_MONITOR_DB_GAP_CHK                                  0x0000000000
#define SI_MONITOR_DB_LEN                                      0x000000E000
#define SI_MONITOR_DB_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* SRV_NAME_BUF   */
//co_buffer L2
#define SRV_NAME_BUF_AVAILABLE                                 0x0006545800
#define SRV_NAME_BUF_ADR                                       0x0006545800  //Alignment 0x00008
#define SRV_NAME_BUF_GAP_CHK                                   0x0000000000
#define SRV_NAME_BUF_LEN                                       0x0000001000
#define SRV_NAME_BUF_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* EIT_PF_STRING_BUF   */
//co_buffer L2
#define EIT_PF_STRING_BUF_AVAILABLE                            0x0006546800
#define EIT_PF_STRING_BUF_ADR                                  0x0006546800  //Alignment 0x00008
#define EIT_PF_STRING_BUF_GAP_CHK                              0x0000000000
#define EIT_PF_STRING_BUF_LEN                                  0x0000004000
#define EIT_PF_STRING_BUF_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* MMI_TEXTSTRING   */
//co_buffer L2
#define MMI_TEXTSTRING_AVAILABLE                               0x000654A800
#define MMI_TEXTSTRING_ADR                                     0x000654A800  //Alignment 0x00010
#define MMI_TEXTSTRING_GAP_CHK                                 0x0000000000
#define MMI_TEXTSTRING_LEN                                     0x0000001000
#define MMI_TEXTSTRING_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* OADSEC_BUFFER   */
//co_buffer L2
#define OADSEC_BUFFER_AVAILABLE                                0x000654B800
#define OADSEC_BUFFER_ADR                                      0x000654B800  //Alignment 0x00010
#define OADSEC_BUFFER_GAP_CHK                                  0x0000000000
#define OADSEC_BUFFER_LEN                                      0x0000014000
#define OADSEC_BUFFER_MEMORY_TYPE                              (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* SCALER_DNR_BUF_DTV   */
//co_buffer L2
#define SCALER_DNR_BUF_DTV_AVAILABLE                           0x000655F800
#define SCALER_DNR_BUF_DTV_ADR                                 0x000655F800  //Alignment 0x00100
#define SCALER_DNR_BUF_DTV_GAP_CHK                             0x0000000000
#define SCALER_DNR_BUF_DTV_LEN                                 0x0000C00000
#define SCALER_DNR_BUF_DTV_MEMORY_TYPE                         (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* RRT5_DIM_START   */
//co_buffer L2
#define RRT5_DIM_START_AVAILABLE                               0x000715F800
#define RRT5_DIM_START_ADR                                     0x000715F800  //Alignment 0x00008
#define RRT5_DIM_START_GAP_CHK                                 0x0000000000
#define RRT5_DIM_START_LEN                                     0x0000010000
#define RRT5_DIM_START_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

/* SCALER_FB_NO_VDEC   */
//co_buffer L4
#define SCALER_FB_NO_VDEC_AVAILABLE                            0x000233C000
#define SCALER_FB_NO_VDEC_ADR                                  0x000233C000  //Alignment 0x00020
#define SCALER_FB_NO_VDEC_GAP_CHK                              0x0000000000
#define SCALER_FB_NO_VDEC_LEN                                  0x0001200000
#define SCALER_FB_NO_VDEC_MEMORY_TYPE                          (MIU0 | SW | CO_BUF_L4 | WRITE_BACK)

/* NONE13   */
//co_buffer L6
#define NONE13_AVAILABLE                                       0x000233C000
#define NONE13_ADR                                             0x000233C000  //Alignment 0x00200
#define NONE13_GAP_CHK                                         0x0000000000
#define NONE13_LEN                                             0x0000000000
#define NONE13_MEMORY_TYPE                                     (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* SCALER_HDMI_4K   */
//co_buffer L6
#define SCALER_HDMI_4K_AVAILABLE                               0x000233C000
#define SCALER_HDMI_4K_ADR                                     0x000233C000  //Alignment 0x00200
#define SCALER_HDMI_4K_GAP_CHK                                 0x0000000000
#define SCALER_HDMI_4K_LEN                                     0x0004800000
#define SCALER_HDMI_4K_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L6 | WRITE_BACK)

/* MP4_SUBTITLE_TAG   */
//co_buffer L5
#define MP4_SUBTITLE_TAG_AVAILABLE                             0x0007F96800
#define MP4_SUBTITLE_TAG_ADR                                   0x0007F96800  //Alignment 0
#define MP4_SUBTITLE_TAG_GAP_CHK                               0x0000000000
#define MP4_SUBTITLE_TAG_LEN                                   0x0000000000
#define MP4_SUBTITLE_TAG_MEMORY_TYPE                           (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* TEXT_DATA_READ   */
//co_buffer L5
#define TEXT_DATA_READ_AVAILABLE                               0x0007F96800
#define TEXT_DATA_READ_ADR                                     0x0007F96800  //Alignment 0
#define TEXT_DATA_READ_GAP_CHK                                 0x0000000000
#define TEXT_DATA_READ_LEN                                     0x0000000800
#define TEXT_DATA_READ_MEMORY_TYPE                             (MIU0 | SW | CO_BUF_L5 | WRITE_BACK)

/* COMB_3D_BUF   */
//co_buffer L4
#define COMB_3D_BUF_AVAILABLE                                  0x000353C000
#define COMB_3D_BUF_ADR                                        0x000353C000  //Alignment 0x00020
#define COMB_3D_BUF_GAP_CHK                                    0x0000000000
#define COMB_3D_BUF_LEN                                        0x0000400000
#define COMB_3D_BUF_MEMORY_TYPE                                (MIU0 | SW | CO_BUF_L4 | WRITE_BACK)

/* GOP_GWIN_RB2   */
//co_buffer L2
#define GOP_GWIN_RB2_AVAILABLE                                 0x000716F800
#define GOP_GWIN_RB2_ADR                                       0x000716F800  //Alignment 0x00020
#define GOP_GWIN_RB2_GAP_CHK                                   0x0000000000
#define GOP_GWIN_RB2_LEN                                       0x000017BBB0
#define GOP_GWIN_RB2_MEMORY_TYPE                               (MIU0 | SW | CO_BUF_L2 | WRITE_BACK)

//MIU_1_START
//MIU_END
#define MIU0_END_ADR                                           0x0008000000
