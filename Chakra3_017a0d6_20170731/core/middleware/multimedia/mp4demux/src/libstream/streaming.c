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


#include <string.h>
#include <assert.h>
#include "ms_io.h"
#include "ms_input.h"
#include "ms_dprintf.h"
#include "mvc_demuxer.h"
#include "streaming.h"
#include "streaming_app.h"
#include "sys_thread.h"
#include "../sys_common.h"
#include "../libringbuf/ringbuffer_api.h"

//#define ENABLE_PUSH_MODEL
//#define SIMU_PUSH_THREAD
#ifdef ENABLE_PUSH_MODEL
#include "push_input.h"
extern struct sys_ringbuffer *streaming_rbuf;
#endif

enum {
    STATE_STOP,
    STATE_PLAY,
    STATE_PAUSE,
    STATE_ERROR
};

#if defined (MIPSDEV) || defined(ECOS)
#define STM_DBG1     diag_printf
#define STM_ERR1     diag_printf
#elif defined(__RTK_OS__)
#include "player_util.h"
#define STM_DBG1     diag_printf
#define STM_ERR1     diag_printf
#else
#define STM_DBG1     //printf
#define STM_ERR1     printf
#endif

/*lint -e528*/
#ifdef __ARMCC_VERSION
#pragma diag_suppress 177
#endif

#define PARSER_THREAD_STACK_SIZE (6*1024)

//#define DUMP_STREAMING  // affect performance if enabling this

#ifdef DUMP_STREAMING
int dump_streaming_len;
int dump_streaming_rptr;
#define DUMP_BLOCK_SIZE (16*1024)  // total ring buffer size is 192KB
MSFILE dump_streaming;
#define MAX_DUMP_STREAMING_LEN (2*1024*1024)
static cyg_tick_count_t start_time, end_time;
#ifdef MIPSDEV
#define STREAMING_FILE_DUMP "/\0C\0A\0R\0D\0/\0a\0.\0t\0s\0"
char dump_streaming_fname1[20];
char dump_streaming_fname2[40];
#else
#define STREAMING_FILE_DUMP "dump_channel.mfs"
char dump_streaming_fname1[64] = "dump_channel.mfs";
#endif
#endif

static void reset_fs_cache(fs_cache_st *cache)
{
    cache->base_pos = 0;
    cache->avail_size = 0;
}

static void init_fs_cache(fs_cache_st *cache, void* cache_buffer, uint32_t buffer_length)
{
    cache->buffer_length = buffer_length;
    cache->buffer = cache_buffer;
    reset_fs_cache(cache);
}

static size_t read_data_from_fs(cb_buffer_st *cbuf, fs_cache_st *cache, void *output_buffer, size_t read_size, cb_fpos file_pos)
{
    // there must be such n that n * cache->cache->buffer_length < read_size <= (n + 1) * cache->cache->buffer_length
    // for the data within [0, n * cache->cache->buffer_length], we will read them directly from fs to output_buffer
    // for the data within [n * cache->cache->buffer_length + 1, read_size], we will read them in cache first, then copy to output_buffer
    size_t buffer_count, totalread;
    size_t size_direct_from_fs, size_from_cache;

    buffer_count = read_size / cache->buffer_length;
    size_direct_from_fs = buffer_count * cache->buffer_length;
    totalread = cbuf->input->read(cbuf->input, output_buffer, size_direct_from_fs);

    if (totalread != size_direct_from_fs)
    {
        // invalid cache since actual file pos is no longer the end of cache
        reset_fs_cache(cache);
        return totalread;
    }

    // read the data to fs cache
    cache->avail_size = cbuf->input->read(cbuf->input, cache->buffer, cache->buffer_length);
    cache->base_pos = file_pos + size_direct_from_fs;
    size_from_cache = SYS_MIN(cache->avail_size, read_size - size_direct_from_fs);
    memcpy((uint8_t *)output_buffer + size_direct_from_fs, cache->buffer, size_from_cache);
    totalread += size_from_cache;

    return totalread;
}

static int out_of_fs_cache(fs_cache_st *cache, cb_fpos file_pos)
{
    return (file_pos < cache->base_pos) || (file_pos >= cache->base_pos + cache->avail_size);
}

static size_t read_data_from_cache(fs_cache_st *cache, void *output_buffer, size_t read_size, cb_fpos file_pos)
{
    size_t skip_size; // the data size prior to file_pos, these are useless here
    size_t actual_read_size;

    if (out_of_fs_cache(cache, file_pos))
        return 0;

    skip_size = file_pos - cache->base_pos;
    actual_read_size = SYS_MIN(read_size, cache->avail_size - skip_size);
    memcpy(output_buffer, cache->buffer + skip_size, actual_read_size);

    return actual_read_size;
}

static size_t read_fs_cache(cb_buffer_st *cbuf, fs_cache_st *cache, void *output_buffer, size_t read_size, cb_fpos file_pos)
{
    size_t totalread;

    totalread = read_data_from_cache(cache, output_buffer, read_size, file_pos);

    if (totalread < read_size)
    {
        totalread += read_data_from_fs(cbuf, cache, (uint8_t *)output_buffer + totalread, read_size - totalread, file_pos + totalread);
    }

    return totalread;
}

static size_t peek_fs_cache(cb_buffer_st *cbuf, fs_cache_st *cache, void *output_buffer, size_t read_size, cb_fpos file_pos)
{
    // 2 cases, 1 the data we need is cached in buffer
    //          2 the data we need is not all cached in buffer
    size_t totalread;

    // unable to do peek, use original read
    if (read_size > cache->buffer_length)
    {
        totalread = read_fs_cache(cbuf, cache, output_buffer, read_size, file_pos);
        cbuf->input->seek(cbuf->input, file_pos, SEEK_SET);
        reset_fs_cache(cache);
        return totalread;
    }

    totalread = read_data_from_cache(cache, output_buffer, read_size, file_pos);

    if (totalread != read_size)
    {
        // if totalread == 0, it means there is no useful data in cache page and memmove does nothing
        memmove(cache->buffer, cache->buffer + file_pos - cache->base_pos, totalread);
        cache->avail_size = totalread + cbuf->input->read(cbuf->input, cache->buffer + totalread, cache->buffer_length - totalread);
        cache->base_pos = file_pos;
        read_size = SYS_MIN(cache->avail_size, read_size);
        assert(read_size >= totalread);
        // the minimum size of cache->avail_sizeis totalread(fread return 0)
        memcpy((uint8_t *)output_buffer + totalread, cache->buffer + totalread, read_size - totalread);
    }

    return read_size;
}

#ifdef SYS_IO_PLUGIN
#include "hwdemux_input.h"
#include "isdbt_n_input.h"
#include "isdbt_s_input.h"
#include "file_input.h"

pCbIOInit               fnIOInit;
pCbGetStreamingData     fnGetStreamingData;
pCbIODeinit             fnIODeinit;
pCbStartStreaming       fnStartStreaming;
pCbStopStreaming        fnStopStreaming;
pCbIOSeek               fnIOSeek;
pCbGetExtraRbufSize     fnGetExtraRbufSize;

#ifdef EVAL_IO_COUNT
static int64_t total_unused_size;
static int io_read_count;
static int prefetch_count;
#endif

#ifdef SUPPORT_ASYNCIO
static int prefetched_size[2];
static int curr_prefetch_idx;
static int pre_prefetch_idx;
static int fread_size[2];

static void init_non_blocked_status(void)
{
    prefetched_size[0]  = 0;
    prefetched_size[1]  = 0;
    fread_size[0]       = 0;
    fread_size[1]       = 0;
    curr_prefetch_idx   = 1;
    pre_prefetch_idx    = -1;
}
#endif

int streaming_input_plugin(int type)
{
    if (type == FILE_INPUT) {
        return streaming_file_input_plugin();
    }
    #ifdef CARINA_DRIVER
    else if (type == HWDEMUX_INPUT) {
        return streaming_hwdemux_input_plugin();
    }
    #endif
    #ifdef MONTAGE_DRV_NMI_ISDBT
    else if (type == ISDBT_N_INPUT) {
        return streaming_isdbt_n_input_plugin();
    }
    #endif
    #ifdef MONTAGE_DRV_SIANO_ISDBT
    else if (type == ISDBT_S_INPUT) {
        return streaming_isdbt_s_input_plugin();
    }
    #endif
    else {
        return -1;
    }
}
#endif

ATTR_UNUSED static void *StreamingData(void *arg)
{
    cb_buffer_st *cbuf = (cb_buffer_st *) arg;
    struct sys_ringbuffer *srbuf = cbuf->srbuf;
#ifndef SYS_IO_PLUGIN
    long  dwCopy;
#endif
    int32_t  readsize;
    int    breakloop = 0;

#ifdef DUMP_STREAMING
    dump_streaming_len = 0;
    dump_streaming_rptr = 0;
#ifdef MIPSDEV
    int i, j;
    diag_sprintf(dump_streaming_fname1, "/CARD/DUMP_%04x.ts", cyg_current_time()&0xffff);
    diag_printf("dump_streaming_fname1 = %s\n", dump_streaming_fname1);
    j = 0;
    for(i = 0; i < strlen(dump_streaming_fname1); i++)
    {
        dump_streaming_fname2[j++] = dump_streaming_fname1[i];
        dump_streaming_fname2[j++] = '\0';
    }
    dump_streaming_fname2[j++] = '\0';
    dump_streaming_fname2[j++] = '\0';
#endif
    dump_streaming = ms_open(dump_streaming_fname2, MS_FO_WB);
#endif

#ifdef SYS_IO_PLUGIN
    fnStartStreaming();
#endif

    while (!breakloop)
    {
#ifdef SIM_DATA_GEN
        start = sys_current_time();
#endif
        switch (cbuf->state)
        {
        case STATE_STOP:
            breakloop = 1;
            break;
        case STATE_PAUSE:
            assert(0);
            break;
        case STATE_ERROR:
            assert(0);
            break;
        case STATE_PLAY:
#ifdef SYS_IO_PLUGIN
            CheckCmdBuffer();
            GetStatistics();
            CheckDemodReset();
            readsize = fnGetStreamingData(srbuf, cbuf->base);
#ifdef DUMP_STREAMING
            int32 avail;
            avail = srbuf->pwrite - dump_streaming_rptr;
            if (avail < 0)
                avail += srbuf->size;

            if (avail > DUMP_BLOCK_SIZE) {
                start_time = cyg_current_time();
                ms_write(srbuf->data+dump_streaming_rptr, 1, DUMP_BLOCK_SIZE, dump_streaming);
                end_time = cyg_current_time()-start_time;
                diag_printf("dp=%lld\n", end_time);
                dump_streaming_rptr += DUMP_BLOCK_SIZE;
                if (dump_streaming_rptr >= srbuf->size)
                    dump_streaming_rptr = 0;
                dump_streaming_len += DUMP_BLOCK_SIZE;
                ms_flush(dump_streaming);
            }
            if (dump_streaming_len > MAX_DUMP_STREAMING_LEN) {
                diag_printf("fclose!!!!\n");
                ms_close(dump_streaming);
                ms_sync();
                // reopen to overwrite this file
                dump_streaming = ms_open(dump_streaming_fname2, MS_FO_WB);
                dump_streaming_len = 0;
            }
#endif
            if (readsize == -1) {
#ifdef LOOP_PLAY
                STM_DBG1("EOF, fseek to start !!!!\n");
                fnIOSeek(0);
#else
                srbuf->buf_eos = 1;
                sys_thread_delay(1);
#endif
                continue;
            } else if (readsize == 0) {
                sys_thread_delay(1);
            }
            RecordWrite(srbuf->data + srbuf->pwrite, readsize);
#else // callback
            dwCopy = cbuf->input->block_size;
            srbuf->wlock = 1;
            rb_mutex_lock(&srbuf->ring_mutex);

            readsize = cbuf->input->read(cbuf->input, cbuf->base, dwCopy);

            srbuf->wlock = 0;
            rb_mutex_unlock(&srbuf->ring_mutex);

            if (readsize == 0) {
                srbuf->buf_eos = 1;
                continue;
            }

            /* Record */
            RecordWrite(cbuf->base, readsize);

            sys_ringbuffer_alloc(cbuf->srbuf, readsize);
            sys_ringbuffer_byte_write(cbuf->srbuf, cbuf->base, readsize);
#endif // ~ callback test
            break;
        default:
            assert(0);
        } // end of switch
#ifdef SIM_DATA_GEN
        end = sys_current_time();
        cpu_time_used = (end - start);  // millisecond
        //STM_DBG1("%f %f\n", cpu_time_used, DELAY_MS);
        if (cpu_time_used < DELAY_MS)
            sys_thread_delay((int)(DELAY_MS-cpu_time_used)); // millisecond
#endif
    }
#ifdef SYS_IO_PLUGIN
    fnStopStreaming();
#endif
#ifdef DUMP_STREAMING
    ms_close(dump_streaming);
    ms_sync();
#endif
    sys_thread_exit(cbuf->thread);

    return 0;
}

static int OpenStream(cb_buffer_st *cbuf, const mvc_callback_st *cb)
{
    cbuf->stream_thread_stack = cb->malloc(cb->context, PARSER_THREAD_STACK_SIZE);
    if (!cbuf->stream_thread_stack)
        return -1;
    cbuf->state = STATE_PLAY;
    sys_thread_create(cbuf->thread, StreamingData, cbuf, "STREAM_THD", SYSTH_PRIORITY_NORMAL,
                      cbuf->stream_thread_stack, PARSER_THREAD_STACK_SIZE);

    return MVC_OK;
}

static int CloseStream(cb_buffer_st *cbuf, const mvc_callback_st *cb)
{
    cbuf->state = STATE_STOP;
    sys_thread_join(cbuf->thread);
    cb->freep(cb->context, &cbuf->stream_thread_stack);
    return MVC_OK;
}

/************************************************************************/
/*  For single thread                                                   */
/************************************************************************/

#ifdef SUPPORT_ASYNCIO

static int non_blocked_read(cb_io_st *cbio, uint8_t *buf, int size)
{
    int read_size;

    //printf("cur_NB_idx:%d,pre_NB_idx:%d,buf:0x%x\n",curr_prefetch_idx,pre_prefetch_idx, buf);
#ifdef WIN32
    read_size = cbio->read(cbio, buf, size);
    fread_size[curr_prefetch_idx] = read_size;
    if (pre_prefetch_idx == -1)
        return 0;
    else
        return fread_size[pre_prefetch_idx];
#else
    //use wait_prefetch_done to get previous prefetch size
    read_size = c51_nonblock_read(cbio->context, buf, size);
    return read_size;
#endif
}

static int wait_prefetch_done(cb_io_st *cbio, uint8_t **pre_prefetched_buf)
{
    int prefetch_size;
#ifdef WIN32
    prefetch_size = fread_size[pre_prefetch_idx];
#else
    prefetch_size = c51_wait_read(cbio->context);
#endif
    *pre_prefetched_buf = base+pre_prefetch_idx*cbio->block_size;
    assert(prefetch_size <= cbio->block_size);
    return prefetch_size;
}

static int prefetch_next_buf(cb_io_st *cbio, uint8_t **pre_prefetched_buf, int *pre_prefetched_size)
{
    int size;
    if (pre_prefetch_idx == -1)
    {
        size = cbio->read(cbio, base, cbio->block_size);
#ifdef EVAL_IO_COUNT
        io_read_count++;
#endif
        *pre_prefetched_buf  = base;
        *pre_prefetched_size = size;
        non_blocked_read(cbio, base+curr_prefetch_idx*cbio->block_size, cbio->block_size);
        pre_prefetch_idx   = curr_prefetch_idx;
        curr_prefetch_idx ^= 1;
#ifdef EVAL_IO_COUNT
        prefetch_count++;
#endif

        return 0;
    }
    *pre_prefetched_size = wait_prefetch_done(cbio, pre_prefetched_buf);
    non_blocked_read(cbio, base+curr_prefetch_idx*cbio->block_size,  cbio->block_size);
    pre_prefetch_idx     = curr_prefetch_idx;
    curr_prefetch_idx   ^= 1;
#ifdef EVAL_IO_COUNT
    prefetch_count++;
#endif

    return 0;
}
#endif /* SUPPORT_ASYNCIO */

static void WriteData(cb_buffer_st *cbuf, unsigned int len)
{
    int readsize;
    uint8_t *buf;
    cb_io_st *cbio = cbuf->input;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    while (active_rbuf->pkt_cnt < len && !active_rbuf->buf_eos) {
#ifdef  SYS_IO_PLUGIN
        if (get_app_status(TIMESHIFT_ENABLE)) {
            if (get_app_status(TIMESHIFT_BYTECNT) <= cbio->block_size) {
                //STM_DBG1("!!!!!!!!!!!!!!!!!!!!! rpos = 0x%x, wpos = 0x%x, bytecnt = 0x%x\n", get_app_status(TIMESHIFT_RPOS), get_app_status(TIMESHIFT_WPOS), get_app_status(TIMESHIFT_BYTECNT));
                sys_thread_delay(10);
                continue;
            }
        }
#endif
        if (cbio->block_size > sys_ringbuffer_free(active_rbuf))
            break;
#ifdef SUPPORT_ASYNCIO
        prefetch_next_buf(cbio, &buf, &readsize);
#else
        readsize = cbio->read(cbio, cbuf->base, cbio->block_size);
        buf = cbuf->base;
#ifdef EVAL_IO_COUNT
        io_read_count++;
#endif
#endif
#ifdef SUPPORT_ASYNCIO
        if (get_app_status(TIMESHIFT_ENABLE)) {
            TimeShiftReadPos(cbuf, readsize);
        }
#endif
        if (readsize <= 0) {
#ifdef LOOP_PLAY
            cbio->seek(cbio, 0, SEEK_SET);
            cbuf->curpos = 0;
#else
            active_rbuf->buf_eos = 1;
#endif
            break;
        }
        sys_ringbuffer_byte_write(active_rbuf, buf, readsize);
    }
}

int cb_status(cb_buffer_st *cbuf)
{
    return cbuf->cb_errcode;
}

// if "buf" is NULL, it means dummy read.
static int32_t cb_read_multi(cb_buffer_st *cbuf, void *buf, int32_t size)
{
    int totalread = 0;
    int readsize;
    long dwCopy;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    dwCopy = active_rbuf->size;

    ms_dprintf(2, "cb_read_multi: ptr %p size %u data %lu\n", buf, size, active_rbuf->pkt_cnt);

    assert(size <= active_rbuf->size);
    dwCopy = (size % active_rbuf->size);
    if (dwCopy != 0)
    {
        readsize = sys_ringbuffer_byte_read_peek(active_rbuf, buf, dwCopy);
        sys_ringbuffer_byte_release(active_rbuf, readsize);
        if (readsize < dwCopy) {
            if (active_rbuf->buf_eos)
                cbuf->cb_errcode = CB_ERR_EOF;
            else
                cbuf->cb_errcode = CB_ERR_TIMEDOUT;
        } else
            cbuf->cb_errcode = CB_ERR_OK;
        cbuf->curpos += readsize;
        totalread += readsize;
        while (active_rbuf->slock) {
            sys_thread_delay(1);
        }
    }
    return totalread;
}

static int32_t cb_peek_multi(cb_buffer_st *cbuf, void *buf, int32_t size)
{
    int totalread = 0;
    int readsize;
    long dwCopy;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    assert(size >= 0);

    ms_dprintf(2, "cb_peek_multi: ptr %p size %u data %lu\n", buf, size, active_rbuf->pkt_cnt);

    assert(size <= active_rbuf->size);
    dwCopy = size;
    if (dwCopy != 0) {
        readsize = sys_ringbuffer_byte_read_peek(active_rbuf, buf, dwCopy);
        if (readsize < dwCopy) {
            if (active_rbuf->buf_eos)
                cbuf->cb_errcode = CB_ERR_EOF;
            else
                cbuf->cb_errcode = CB_ERR_TIMEDOUT;
        } else
            cbuf->cb_errcode = CB_ERR_OK;
        totalread += readsize;
        active_rbuf->srlock = 0;
        while (active_rbuf->slock) {
            sys_thread_delay(1);
        }
    }
    return totalread;
}

static int seek_out_of_buffer(cb_buffer_st *cbuf, cb_off_t offset, int whence)
{
    CB_BufferType buffer_type = cbuf->buffer_type;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    if (buffer_type == CB_STREAM_RBUF)
    {
        switch (whence)
        {
        case CB_SEEK_SET:
            return (((cb_fpos)offset < cbuf->curpos) || (offset - cbuf->curpos > active_rbuf->pkt_cnt));
        case CB_SEEK_CUR:
            return (offset < 0 || offset > active_rbuf->pkt_cnt);
        case CB_SEEK_END:
            return 1;
        default:
            assert(0);
            return 1;
        }
    }
    else if (buffer_type == CB_FS_CACHE)
    {
        switch (whence)
        {
        case CB_SEEK_SET:
            return out_of_fs_cache(&cbuf->fs_cache, offset);
        case CB_SEEK_CUR:
            return out_of_fs_cache(&cbuf->fs_cache, cbuf->curpos + offset);
        case CB_SEEK_END:
            return 1;
        default:
            assert(0);
            return 1;
        }
    }
    else
        return 1;
}

static cb_off_t cb_seek_multi64(cb_buffer_st *cbuf, cb_off_t offset, int whence)
{
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;
#ifndef SYS_IO_PLUGIN
    cb_off_t pos = cbuf->curpos;
#endif
    ms_dprintf(2, "cb_seek_multi (offset %ld, whence %d)\n", offset, whence);
    assert(whence == CB_SEEK_SET || whence == CB_SEEK_CUR);

    if (!cbuf->input->use_thread && cbuf->input->rbuf_mode)
    {
        while (seek_out_of_buffer(cbuf, offset, whence))
        {
            if (active_rbuf->buf_eos)
                return -1;
            sys_thread_delay(1);
        }
    }

    switch (whence)
    {
    case CB_SEEK_SET:
        // data is out of buffer
        if (((cb_fpos)offset < cbuf->curpos) || (offset - cbuf->curpos > active_rbuf->pkt_cnt)) {
            active_rbuf->buf_eos = 0;
            rb_mutex_lock(&active_rbuf->ring_mutex);
#ifdef SYS_IO_PLUGIN
            cbuf->curpos = offset;
            fnIOSeek(offset);
#else
            pos = cbuf->input->seek(cbuf->input, offset, SEEK_SET);
            if (pos != -1) cbuf->curpos = pos;
#endif
            if (active_rbuf->wlock == 0)
                active_rbuf->rlock = 1;
            rb_mutex_unlock(&active_rbuf->ring_mutex);
            sys_ringbuffer_reset(active_rbuf);
        } else {        // data is in buffer, and not be read yet.
            cbuf->cb_read(cbuf, NULL, offset - cbuf->curpos);
        }
        break;
    case CB_SEEK_CUR:
        //assert(offset >= 0);
        // data is out of buffer
        if ((offset < 0) || (offset > active_rbuf->pkt_cnt)) {
            active_rbuf->buf_eos = 0;
            rb_mutex_lock(&active_rbuf->ring_mutex);
#ifdef SYS_IO_PLUGIN
            cbuf->curpos += offset;
            fnIOSeek(cbuf->curpos);
#else
            pos = cbuf->input->seek(cbuf->input, cbuf->curpos + offset, SEEK_SET);
            if (pos != -1) cbuf->curpos = pos;
#endif
            if (active_rbuf->wlock == 0)
                active_rbuf->rlock = 1;
            rb_mutex_unlock(&active_rbuf->ring_mutex);
            sys_ringbuffer_reset(active_rbuf);
        } else {        // data is in buffer, and not be read yet.
            cbuf->cb_read(cbuf, NULL, offset);
        }
        break;
    case CB_SEEK_END:
        assert(0); // does not support SEEK_END
        break;
    default:
        return -1;
    }

#ifdef SYS_IO_PLUGIN
    return (cb_off_t) cbuf->curpos;
#else
    return pos == -1 ? -1 : (cb_off_t) cbuf->curpos;
#endif
}

static int32_t cb_seek_multi(cb_buffer_st *cbuf, int32_t offset, int whence)
{
    // when cb_off_t is int32_t, cb_seek_multi64 is actually 32bit version
    return (int32_t) cb_seek_multi64(cbuf, offset, whence);
}

static int read_rbuf_remain_data(cb_buffer_st *cbuf, void *buf, int size, int peek)
{
    int data_size, readsize, cp_size;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;
    data_size = sys_ringbuffer_avail(active_rbuf);
    cp_size = SYS_MIN(data_size, size);

    readsize = sys_ringbuffer_byte_read_peek_single_thread(active_rbuf, buf, cp_size);
    if (!peek)
        sys_ringbuffer_byte_release(active_rbuf, readsize);
    return readsize;
}

static int read_rbuf_data(cb_buffer_st *cbuf, uint8_t *buf, int size, int peek)
{
    int needed_size, total_readsize, readsize;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;
    total_readsize = read_rbuf_remain_data(cbuf, buf, size, peek);
    needed_size = size - total_readsize;
    if (needed_size > 0)
    {
        WriteData(cbuf, needed_size);
        if (buf != NULL)
            readsize = sys_ringbuffer_byte_read_peek_single_thread(active_rbuf, buf + total_readsize, needed_size);
        else
            readsize = sys_ringbuffer_byte_read_peek_single_thread(active_rbuf, NULL, needed_size);
        if (!peek)
            sys_ringbuffer_byte_release(active_rbuf, readsize);
        total_readsize += readsize;
    }
    return total_readsize;
}

static void seek_reset_buffer(cb_buffer_st *cbuf, cb_off_t pos)
{
    if (pos == -1)
        cbuf->curpos = cbuf->input->tell(cbuf->input);
    else
        cbuf->curpos = pos;

    if (cbuf->active_rbuf)
        sys_ringbuffer_reset(cbuf->active_rbuf);
    else if (cbuf->fs_cache.buffer)
        reset_fs_cache(&cbuf->fs_cache);
}

// if "buf" is NULL, it means dummy read.
static int32_t cb_read_single(cb_buffer_st *cbuf, void *buf, int32_t size)
{
    int totalread = 0;
    int readsize;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    //ms_dprintf(2, "cb_read_single: ptr %p size %u data %lu\n", buf, size, active_rbuf->pkt_cnt);
    //ms_dprintf(2, "cb_read_single: ptr %p size %u, curpos = 0x%llx, actual pos = 0x%llx, base = 0x%llx, cache data = %d\n", buf, size, cbuf->curpos, cbuf->input->tell(cbuf->input), cbuf->fs_cache.base_pos, cbuf->fs_cache.avail_size);

    if (cbuf->buffer_type == CB_STREAM_RBUF)
    {
        while(size > 0)
        {
            active_rbuf->srlock = 1;

            readsize = read_rbuf_data(cbuf, (uint8_t *)buf + totalread, size, 0);
            cbuf->curpos += readsize;
            totalread += readsize;
            size -= readsize;
            active_rbuf->srlock = 0;
            while (active_rbuf->slock)
            {
                sys_thread_delay(1);
            }
#ifdef SYS_IO_PLUGIN
            if (get_app_status(TIMESHIFT_ENABLE))
            {
                int filesize = get_app_status(TIMESHIFT_FILESIZE);
                if (cbuf->curpos >= filesize)
                    cbuf->curpos -= filesize;
            }
#endif
            if (readsize < size && active_rbuf->buf_eos)
            {
                cbuf->cb_errcode = CB_ERR_EOF;
                break;
            }
            else
                cbuf->cb_errcode = CB_ERR_OK;
        }
    }
    else
    {
        if (cbuf->buffer_type == CB_FS_CACHE)
            totalread = read_fs_cache(cbuf, &cbuf->fs_cache, buf, size, cbuf->curpos);
        else
            totalread = cbuf->input->read(cbuf->input, buf, size);

        if (totalread < size)
            cbuf->cb_errcode = CB_ERR_EOF;
        else
            cbuf->cb_errcode = CB_ERR_OK;
        cbuf->curpos += totalread;
    }
    return totalread;
}

#ifdef SUPPORT_ASYNCIO
static int handle_over_size_seek(cb_buffer_st *cbuf, cb_off_t offset, int whence)
{
    cb_off_t over_size;
    cb_off_t seek_size;
    cb_off_t prefetch_size = 0;
    uint8_t *buf;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    if (whence == CB_SEEK_SET)
    {
        over_size = (cb_off_t)(offset - cbuf->curpos) - active_rbuf->pkt_cnt;
        seek_size = offset - cbuf->curpos;
    }
    else if (whence == CB_SEEK_CUR)
    {
        over_size = offset - active_rbuf->pkt_cnt;
        seek_size = offset;
    }
    else
        assert(0);


    if (pre_prefetch_idx != -1)
    {
        prefetch_size     = wait_prefetch_done(cbuf->input, &buf);
        pre_prefetch_idx  = -1;
        curr_prefetch_idx = 1;
    }

    if (over_size > 0 && over_size <= prefetch_size)
    {
        int free_size;

        free_size = sys_ringbuffer_free(active_rbuf);
        assert(free_size>=prefetch_size);

        sys_ringbuffer_byte_write(active_rbuf, buf, prefetch_size);
        sys_ringbuffer_byte_release(active_rbuf, seek_size);
        cbuf->curpos += seek_size;
        return 0;
    }

    init_non_blocked_status();
    return -1;
}
#endif

static cb_off_t cb_seek_single64(cb_buffer_st *cbuf, cb_off_t offset, int whence)
{
#ifdef SUPPORT_ASYNCIO
    int ret;
#endif
    cb_off_t pos = cbuf->curpos;
#ifdef EVAL_IO_COUNT
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;
#endif
    ms_dprintf(2, "cb_seek_single (offset %llx, whence %d)\n", offset, whence);
    assert(whence == CB_SEEK_SET || whence == CB_SEEK_CUR || whence == CB_SEEK_END);

    switch (whence)
    {
    case CB_SEEK_SET:
        // data is out of buffer or not use stream rbuf
        if (seek_out_of_buffer(cbuf, offset, whence))
        {
#ifdef SUPPORT_ASYNCIO
            ret = handle_over_size_seek(cbuf, offset, whence);
            if (ret == 0)
                break;
#endif
#ifdef SYS_IO_PLUGIN
            if (get_app_status(TIMESHIFT_ENABLE))
                TimeShiftSeekPos(offset);
#endif
            pos = cbuf->input->seek(cbuf->input, offset, SEEK_SET);
            // no matter seek success or not, cache buffer is no longer available
            seek_reset_buffer(cbuf, pos);

#ifdef EVAL_IO_COUNT
            total_unused_size += active_rbuf->pkt_cnt;
#endif
        } else {        // data is in buffer, and not be read yet.
            assert(cbuf->buffer_type != CB_NO_BUF);
            if (cbuf->buffer_type == CB_FS_CACHE)
                cbuf->curpos = offset;
            else
                cbuf->cb_read(cbuf, NULL, offset - cbuf->curpos);
        }
        break;
    case CB_SEEK_CUR:
        // data is out of buffer or not use stream rbuf
        if (seek_out_of_buffer(cbuf, offset, whence))
        {
#ifdef SUPPORT_ASYNCIO
            ret = handle_over_size_seek(cbuf, offset, whence);
            if (ret==0)
                break;
#endif
#ifdef SYS_IO_PLUGIN
            if (get_app_status(TIMESHIFT_ENABLE)) {
                assert(0); // not support
            }
#endif
            pos = cbuf->input->seek(cbuf->input, cbuf->curpos + offset, SEEK_SET);
            // no matter seek success or not, cache buffer is no longer available
            seek_reset_buffer(cbuf, pos);

#ifdef EVAL_IO_COUNT
            total_unused_size += active_rbuf->pkt_cnt;
#endif
        } else {        // data is in buffer, and not be read yet.
            assert(cbuf->buffer_type != CB_NO_BUF);
            if (cbuf->buffer_type == CB_FS_CACHE)
                cbuf->curpos += offset;
            else
                cbuf->cb_read(cbuf, NULL, offset); // this is CB_STREAM_RBUF mode, the size of streaming rbuf should be small than 2G
        }
        break;
    case CB_SEEK_END:

#ifdef SUPPORT_ASYNCIO
        init_non_blocked_status();
#endif

        pos = cbuf->input->seek(cbuf->input, offset, SEEK_END);
        // no matter seek success or not, cache buffer is no longer available
        seek_reset_buffer(cbuf, pos);
#ifdef EVAL_IO_COUNT
        total_unused_size += active_rbuf->pkt_cnt;
#endif
        break;
    default:
        return -1;
    }

    if (pos == -1)
        return -1;
    else
        return cbuf->curpos;
}

static int32_t cb_seek_single(cb_buffer_st *cbuf, int32_t offset, int whence)
{
    // when cb_off_t is int32_t, cb_seek_singlei64 is actually 32bit version
    return (int32_t) cb_seek_single64(cbuf, offset, whence);
}

static int32_t cb_peek_single(cb_buffer_st *cbuf, void *buf, int32_t size)
{
    int totalread = 0;
    int readsize;
    long dwCopy;
    struct sys_ringbuffer *active_rbuf = cbuf->active_rbuf;

    assert(size >= 0);

    //ms_dprintf(2, "cb_peek_single: ptr %x size %u data %lu\n", buf, size, active_rbuf->pkt_cnt);
    //ms_dprintf(2, "cb_peek_single: ptr %p size %u, curpos = 0x%x, actual pos = 0x%x, base = 0x%x, cache data = %d\n", buf, size, cbuf->curpos, cbuf->input->tell(cbuf->input), cbuf->fs_cache.base_pos, cbuf->fs_cache.avail_size);

    if (cbuf->buffer_type == CB_STREAM_RBUF)
    {
        assert(size <= active_rbuf->size);
        dwCopy = size;
        if (dwCopy != 0) {
            active_rbuf->srlock = 1;
            WriteData(cbuf, dwCopy);
            readsize = sys_ringbuffer_byte_read_peek_single_thread(active_rbuf, (uint8_t *)buf, dwCopy);

            if (readsize < dwCopy)
                cbuf->cb_errcode = CB_ERR_EOF;
            else
                cbuf->cb_errcode = CB_ERR_OK;
            totalread += readsize;
            active_rbuf->srlock = 0;
            while (active_rbuf->slock) {
                sys_thread_delay(1);
            }
        }
    }
    else if (cbuf->buffer_type == CB_FS_CACHE)
    {
        totalread = peek_fs_cache(cbuf, &cbuf->fs_cache, buf, size, cbuf->curpos);
        if (totalread < size)
            cbuf->cb_errcode = CB_ERR_EOF;
        else
            cbuf->cb_errcode = CB_ERR_OK;
    }
    else
    {
        totalread = cb_read_single(cbuf, buf, size);
        assert(totalread >=0);
        cb_seek_single(cbuf, -totalread, CB_SEEK_CUR);
    }
    return totalread;
}

int cb_tell(cb_buffer_st *cbuf)
{
    return (int) cbuf->curpos;
}

cb_fpos cb_tell64(cb_buffer_st *cbuf)
{
    return cbuf->curpos;
}

cb_fpos cb_get_file_size(cb_buffer_st *cbuf)
{
    cb_fpos file_size = 0;

    if (cbuf->input->streaming)
        file_size = cbuf->input->input_size;
    else
    {
        cb_off_t seek_ret;
        seek_ret = cbuf->cb_seek64(cbuf, 0, CB_SEEK_END);
        if (seek_ret != -1)
            file_size = seek_ret;
        seek_ret = cbuf->cb_seek64(cbuf, 0, CB_SEEK_SET);
        assert(seek_ret != -1);
    }

    return file_size;
}

static void init_single_thread_plugin(cb_buffer_st *cbuf)
{
    cbuf->cb_seek   = cb_seek_single;
    cbuf->cb_seek64 = cb_seek_single64;
    cbuf->cb_read   = cb_read_single;
    cbuf->cb_peek   = cb_peek_single;
}

static void init_multi_thread_plugin(cb_buffer_st *cbuf)
{
    cbuf->cb_seek   = cb_seek_multi;
    cbuf->cb_seek64 = cb_seek_multi64;
    cbuf->cb_read   = cb_read_multi;
    cbuf->cb_peek   = cb_peek_multi;
}

static void init_thread_plugin(cb_buffer_st *cbuf, int rbuf_mode)
{
    if (rbuf_mode) {
        init_multi_thread_plugin(cbuf);
    } else {
        init_single_thread_plugin(cbuf);
    }
}

void changeThreadType(cb_buffer_st *cbuf, int useRingBuf)
{
    if (useRingBuf) {
        init_multi_thread_plugin(cbuf);
    } else {
        init_single_thread_plugin(cbuf);
    }
}

int OpenURL(cb_buffer_st *cbuf, cb_io_st *input, uint32_t ringbuf_size, const mvc_callback_st *cb)
{
    int alloc_rbuf_size = ringbuf_size;
    int alloc_read_buf_size;
    CB_ThreadType thread_type;

    memset(cbuf, 0, sizeof(cb_buffer_st));
#ifdef EVAL_IO_COUNT
    io_read_count = 0;
    prefetch_count = 0;
    total_unused_size = 0;
#endif

#ifdef SUPPORT_ASYNCIO
    init_non_blocked_status();
    alloc_read_buf_size = input->block_size<<1;
#else
    alloc_read_buf_size = input->block_size;
#endif

    assert(ringbuf_size >= alloc_read_buf_size);

#ifdef SIMU_PUSH_THREAD
    create_push_thread(input->filename);
#endif

    cbuf->input = input;
#ifdef SYS_IO_PLUGIN
    if (input->use_thread)
    {
        int extra_rbuf_size;
        fnIOInit(input);
        extra_rbuf_size = fnGetExtraRbufSize();
        alloc_rbuf_size += extra_rbuf_size;
        thread_type = CB_MULTI_THREAD;
    }
    else
#endif /* SYS_IO_PLUGIN */
    {
        thread_type = CB_SINGLE_THREAD;
    }

    cbuf->thread_type = thread_type;

    init_thread_plugin(cbuf, input->rbuf_mode);

    if (input->rbuf_mode)
        cbuf->buffer_type = CB_STREAM_RBUF;
    else
        cbuf->buffer_type = CB_FS_CACHE;

    if (cbuf->buffer_type != CB_NO_BUF)
    {
        cbuf->base = cb->malloc(cb->context, alloc_read_buf_size);
        if (!cbuf->base)
            goto STREAM_MALLOC_FAIL;
        if (cbuf->buffer_type == CB_STREAM_RBUF)
        {
#if defined(MONTAGE_APP_MDTV)
            if (input->use_thread)
                cbuf->stream_ringbuf = cb->malloc(cb->context, alloc_rbuf_size);
            else
#endif
                cbuf->stream_ringbuf = cb->malloc(cb->context, alloc_rbuf_size);

            if (!cbuf->stream_ringbuf)
                goto STREAM_MALLOC_FAIL;

            cbuf->srbuf = cb->malloc(cb->context, sizeof(struct sys_ringbuffer));
            if (!cbuf->srbuf)
                goto STREAM_MALLOC_FAIL;

            cbuf->thread = cb->malloc(cb->context, sizeof(sys_thread_st));
            if (!cbuf->thread)
                goto STREAM_MALLOC_FAIL;

            sys_ringbuffer_init(cbuf->srbuf, cbuf->stream_ringbuf, ringbuf_size);
            cbuf->active_rbuf = cbuf->srbuf;
        }
        else if (cbuf->buffer_type == CB_FS_CACHE)
            init_fs_cache(&cbuf->fs_cache, cbuf->base, cbuf->input->block_size);
    }

    cbuf->curpos = 0;
    cbuf->cb_errcode = CB_ERR_OK;

#ifdef SYS_IO_PLUGIN
    init_app_status();
#endif

#ifdef ENABLE_PUSH_MODEL
    if (!input->use_thread && input->rbuf_mode)
    {
        init_mvc_push_input();
        streaming_rbuf = cbuf->srbuf;
    }
#endif

    if (input->use_thread)
        if (OpenStream(cbuf, cb) != MVC_OK)
        {
            CloseURL(cbuf, cb);
            return -1;
        }

    return MVC_OK;


STREAM_MALLOC_FAIL:
    cb->freep(cb->context, &cbuf->thread);
    cb->freep(cb->context, &cbuf->srbuf);
#if defined(MONTAGE_APP_MDTV)
    if (thread_type == CB_MULTI_THREAD)
        cb->freep(cb->context, &cbuf->stream_ringbuf);
    else
#endif
        cb->freep(cb->context, &cbuf->stream_ringbuf);
    cb->freep(cb->context, &cbuf->base);

#ifdef SYS_IO_PLUGIN
    if (thread_type == CB_MULTI_THREAD)
        fnIODeinit();
#endif // ~callback

    return -1;
}

int CloseURL(cb_buffer_st *cbuf, const mvc_callback_st *cb)
{
    CB_ThreadType thread_type = cbuf->thread_type;
#ifdef ENABLE_PUSH_MODEL
    if (!cbuf->input->use_thread && cbuf->input->rbuf_mode)
        close_mvc_push_input();
#endif

    if (cbuf->srbuf)
        sys_ringbuffer_close(cbuf->srbuf);

    if (thread_type == CB_MULTI_THREAD)
        CloseStream(cbuf, cb);
#ifdef SYS_IO_PLUGIN
    init_app_status();
#endif
    if (cbuf->srbuf)
        sys_ringbuffer_destroy(cbuf->srbuf);
    #if defined(MONTAGE_APP_MDTV)
    if (thread_type == CB_MULTI_THREAD)
        cb->freep(cb->context, &cbuf->stream_ringbuf);
    else
    #endif
    cb->freep(cb->context, &cbuf->stream_ringbuf);
    cb->freep(cb->context, &cbuf->base);
    cb->freep(cb->context, &cbuf->srbuf);
    cb->freep(cb->context, &cbuf->thread);

#ifdef SYS_IO_PLUGIN
    if (thread_type == CB_MULTI_THREAD)
        fnIODeinit();
#endif // ~callback

#ifdef SIMU_PUSH_THREAD
    destroy_push_thread();
#endif

#ifdef EVAL_IO_COUNT
    STM_DBG1("fread_count:%d,prefetch_count:%d\n",io_read_count, prefetch_count);
#endif
    return MVC_OK;
}

void cb_reset_cache(cb_buffer_st *cbuf)
{
    if (cbuf->active_rbuf)
    {
        cbuf->buffer_type = CB_STREAM_RBUF;
        sys_ringbuffer_reset(cbuf->active_rbuf);
    }
    else if (cbuf->fs_cache.buffer)
    {
        cbuf->buffer_type = CB_FS_CACHE;
        reset_fs_cache(&cbuf->fs_cache);
    }

    cbuf->curpos = cbuf->input->tell(cbuf->input);
}

int cb_set_buffer_mode(cb_buffer_st *cbuf, int enable)
{
    cb_off_t pos;

    pos = cbuf->input->seek(cbuf->input, cbuf->curpos, SEEK_SET);
    if (pos == -1)
        return -1;

    if (!enable)
        cbuf->buffer_type = CB_NO_BUF;
    else
    {
        if (cbuf->active_rbuf)
        {
            cbuf->buffer_type = CB_STREAM_RBUF;
            sys_ringbuffer_reset(cbuf->active_rbuf);
        }
        else if (cbuf->fs_cache.buffer)
        {
            cbuf->buffer_type = CB_FS_CACHE;
            reset_fs_cache(&cbuf->fs_cache);
        }
        else
            assert(0);
    }

    return 0;
}
