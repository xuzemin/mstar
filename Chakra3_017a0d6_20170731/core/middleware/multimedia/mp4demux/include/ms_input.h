////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2012 MStar Semiconductor, Inc.
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


#ifndef MS_INPUT_H
#define MS_INPUT_H

#include <stdint.h>
#include <stddef.h>

#define CBIO_64BIT
#ifdef CBIO_64BIT
typedef uint64_t cb_fpos;
typedef int64_t cb_off_t;
#else
typedef uint32_t cb_fpos;
typedef int32_t cb_off_t;
#endif

typedef enum cbio_error_e
{
    CBIO_OK,
    CBIO_OpenFailed,
    CBIO_MallocFailed
} cbio_error_et;

typedef enum cbio_open_mode_e
{
    CBIO_FO_RB,
    CBIO_FO_WB,
    CBIO_FO_AB,
} cbio_open_mode_et;

typedef enum
{
    MMP_FILE_UNKNOWN = 0,
    // image
    MMP_FILE_JPEG,
    MMP_FILE_BMP,
    MMP_FILE_GIF,
    MMP_FILE_PNG,
    MMP_FILE_QRCODE,
    // audio
    MMP_FILE_AAC,
    MMP_FILE_AMR,
    MMP_FILE_AWB,
    MMP_FILE_MIDI,
    MMP_FILE_MP3,
    MMP_FILE_PCM,
    MMP_FILE_WAV,
    MMP_FILE_WMA,
    MMP_FILE_AC3,
    MMP_FILE_DRA,
    // video
    MMP_FILE_ASF,
    MMP_FILE_AVI,
    MMP_FILE_FLV,
    MMP_FILE_MKV,
    MMP_FILE_MP4,
    MMP_FILE_MPG,
    MMP_FILE_RM,
    MMP_FILE_CMMB,
    MMP_FILE_TMP4, // TIVC
    MMP_FILE_TS,
    MMP_FILE_TINY,
    MMP_FILE_RTP,
    MMP_FILE_PMP, // playstation portable
    MMP_FILE_SWF,
    MMP_FILE_MPGES,//raw video
    MMP_FILE_PLUGIN,
    // raw video
    MMP_FILE_264,
    MMP_FILE_263,
    MMP_FILE_FLV1,
    MMP_FILE_M4V,
    MMP_FILE_RVC,
    MMP_FILE_YUV,
} MMP_FILE_TYPE;

typedef struct cb_io_s
{
    size_t  (* read)(struct cb_io_s *ctx, void *buf, size_t size);
    size_t  (* write)(struct cb_io_s *ctx, void *buf, size_t size);
    cb_off_t(* seek)(struct cb_io_s *ctx, cb_off_t offset, int whence); /* returns -1 if failed */
    cb_off_t(* tell)(struct cb_io_s *ctx);
    void    (* close)(struct cb_io_s **ctx);
    size_t  (* aread)(struct cb_io_s *ctx, void *buf, size_t size);
    int     (* open_done)(struct cb_io_s *ctx, int a_bitrate, int v_bitrate, uint32_t file_duration);
    void    (* get_new_cmd)(struct cb_io_s *ctx);
    int     (* seek_time)(struct cb_io_s *ctx, int seek_time);
    int     (* stop_wait_input)(struct cb_io_s *ctx);
    void    (* discontinuity)(struct cb_io_s *ctx, cb_off_t end_pos); // for seamless, next input corresponds to different clips

    int     block_size;
    uint8_t seekable;
    uint8_t streaming;   //1: always read data in byte-order. 0: no restriction
    uint8_t use_thread;
    uint8_t rbuf_mode;   //1: read data from stream_ringbuf. 0: read data not from stream_ringbuf
    int     type_hint;
    int     file_type;
    int     programID;
    void   *context;
    const void *filename;
    cbio_open_mode_et open_mode;
    void    *parent;
    int      bitrate;
    cb_fpos  input_size;
    void    *fcc_buf;
    int      disable_operation; // disable_operation only apply for fread since we must let fseek success when demuxer seek fails and wants seeking back to the original fpos
    // for seamless
    int      detect_discontinuity;
} cb_io_st;

#endif /* MS_INPUT_H */
