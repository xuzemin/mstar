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


#ifndef STREAMING_H
#define STREAMING_H

#include <stdint.h>
#include "mvc_demuxer.h"
#include "ms_input.h"

#ifdef CARINA_DRIVER
#define _HWDEMUX_
#endif

#ifndef READSIZE
#define READSIZE (128 * 1024)
#endif

enum
{
    CB_SEEK_SET,
    CB_SEEK_CUR,
    CB_SEEK_END,
};

typedef enum
{
    CB_MULTI_THREAD,
    CB_SINGLE_THREAD,
    CB_NO_THREAD
} CB_ThreadType;

typedef enum
{
    CB_ERR_OK,
    CB_ERR_EOF,
    CB_ERR_TIMEDOUT,
} CB_ErrCode;

typedef enum
{
    CB_NO_BUF,
    CB_STREAM_RBUF,
    CB_FS_CACHE,
} CB_BufferType;

typedef struct fs_cache_s
{
    uint8_t *buffer;
    uint32_t buffer_length;
    cb_fpos  base_pos;
    uint32_t avail_size; // total useful data in cache
} fs_cache_st;

typedef struct cb_buffer_s cb_buffer_st;

struct cb_buffer_s
{
    int32_t (*cb_read)(cb_buffer_st *cbuf, void *buf, int32_t size);
    int32_t (*cb_peek)(cb_buffer_st *cbuf, void *buf, int32_t size);
    int32_t (*cb_seek)(cb_buffer_st *cbuf, int32_t offset, int whence);
    cb_off_t (*cb_seek64)(cb_buffer_st *cbuf, cb_off_t offset, int whence);

    cb_fpos curpos;
    cb_io_st *input;
    CB_ThreadType thread_type;
    CB_BufferType buffer_type;
    CB_ErrCode cb_errcode;
    uint8_t *stream_ringbuf;
    uint8_t *base;
    void *srbuf;
    void *active_rbuf; // indicate which ring buffer demuxer uses
    fs_cache_st fs_cache;
    int state;
    void *thread;
    void *stream_thread_stack;
};

#ifdef __cplusplus
extern "C" {
#endif

int OpenURL(cb_buffer_st *cbuf, cb_io_st *input, uint32_t ringbuf_size, const mvc_callback_st *cb);
int CloseURL(cb_buffer_st *cbuf, const mvc_callback_st *cb);

#define MAX_RINGBUF_SIZE_LARGE (400 * 1024)
#define MAX_RINGBUF_SIZE_SMALL (160 * 1024)

int cb_tell(cb_buffer_st *cbuf);
cb_fpos cb_tell64(cb_buffer_st *cbuf);
int cb_status(cb_buffer_st *cbuf);
int cb_set_buffer_mode(cb_buffer_st *cbuf, int enable);
cb_fpos cb_get_file_size(cb_buffer_st *cbuf);
void cb_reset_cache(cb_buffer_st *cbuf);

void changeThreadType(cb_buffer_st *cbuf, int threadType);

//#define LOOP_PLAY

//#define SYS_IO_PLUGIN
#ifdef SYS_IO_PLUGIN
typedef enum
{
    FILE_INPUT,
    HWDEMUX_INPUT,
    ISDBT_N_INPUT,
    ISDBT_S_INPUT
} CB_InputType;

typedef int (*pCbIOInit)(const void *pArg);
typedef int (*pCbGetStreamingData)(void *hdl, void *base);
typedef void(*pCbIODeinit)(void);
typedef void(*pCbStartStreaming)(void);
typedef void(*pCbStopStreaming)(void);
typedef void(*pCbIOSeek)(cb_off_t offset);
typedef int (*pCbGetExtraRbufSize)(void);

extern pCbIOInit            fnIOInit;
extern pCbGetStreamingData  fnGetStreamingData;
extern pCbIODeinit          fnIODeinit;
extern pCbStartStreaming    fnStartStreaming;
extern pCbStopStreaming     fnStopStreaming;
extern pCbIOSeek            fnIOSeek;
extern pCbGetExtraRbufSize  fnGetExtraRbufSize;
int streaming_input_plugin(int type);

#endif

#ifdef __cplusplus
}
#endif

#endif /* STREAMING_H */
