////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2013 MStar Semiconductor, Inc.
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
#include "ms_open_input.h"
#include "ms_malloc.h"
#include "ms_dprintf.h"
#define CB_MIN(a, b)    ((a) < (b) ?  (a) : (b))

//#define FUZZ_TEST

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define ATTR_PACK __attribute__ ((packed))
#define ATTR_UNUSED __attribute__((unused))
#else
#define ATTR_PACK
#define ATTR_UNUSED
#endif

#ifdef FUZZ_TEST
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int      init_errpos;

// global random seed
static unsigned random_seed;

// file size truncation
static int      enable_truncate; // set to 1 to cut the file at random position uniformly
                                 // note that not all positions are possible due to rounding
static cb_fpos  truncate_pos;

// bit inverse error
static int      biterr_span;     // the next error bit will occur uniformly within [1, biterr_span)
static cb_fpos  biterr_pos;      // set this to large value to prevent header from corrupted
                                 // the count is in bit unit therefore pos should be at least
                                 // (header length * 8)

// block error (zero or random)
static float    blkerr_rate = 0.0f;
static int      blkerr_size;     // read chunk size
static int      blkerr_pattern;  // 0 for zero, 1 for random [TBD] block drop may be necessary
static int      block_remain;    // how many bytes remain from previous block read
static int      block_error;     // whether the last block has error

static void init_random_pattern(cb_io_st *cbio)
{
    if (!random_seed)
    {
        random_seed = (unsigned) time(0);
        ms_dprintf(1, "[FUZZ] seed = %u\n", random_seed);
        srand(random_seed);
    }

    if (enable_truncate && !truncate_pos)
    {
        cb_fpos fsize = ms_seek(cbio->context, 0, SEEK_END);
        ms_seek(cbio->context, 0, SEEK_SET);
        truncate_pos = (cb_fpos) ((float) fsize * rand() / (RAND_MAX + 1));
        ms_dprintf(1, "[FUZZ] truncate at %d / %d\n", truncate_pos, fsize);
    }

    if (init_errpos) biterr_pos = init_errpos;
}

static void generate_bit_error(uint8_t *buf, cb_fpos size)
{
    if (!biterr_pos && biterr_span)
    {
        biterr_pos = 1 + (cb_fpos) ((float) biterr_span * rand() / (RAND_MAX + 1));
        ms_dprintf(1, "[FUZZ] toggle bit at = %u\n", biterr_pos);
    }
    if (biterr_pos >= size << 3)
        biterr_pos -= size << 3;
    else if (biterr_pos)
    {
        buf[(biterr_pos >> 3)] ^= 1 << (biterr_pos & 7);
        biterr_pos = 0;
    }
}

static void corrupt_block(uint8_t *buf, cb_fpos len)
{
    if (!blkerr_pattern)
        memset(buf, 0, len);
    else
        while (len--) *buf++ = (uint8_t) (256.0 * rand() / (RAND_MAX + 1.0));
}

static void generate_block_error(uint8_t *buf, cb_fpos size)
{
    static int count = 0, total = 0;

    if (!blkerr_size) return;

    if (size <= block_remain)
        goto LAST_BLOCK;

    if (!block_remain)
        goto INIT_BLOCK;

    do
    {
        if (block_error)
            corrupt_block(buf, block_remain);
        size -= block_remain;
        buf  += block_remain;

INIT_BLOCK:
        block_remain = blkerr_size;
        block_error = (float) rand() / (RAND_MAX + 1) < blkerr_rate;

        total++;
        count += block_error;
        if (block_error) ms_dprintf(1, "[FUZZ] corrupt block %d/%d\n", count, total);
    } while (size > block_remain);

LAST_BLOCK:
    if (block_error)
        corrupt_block(buf, size);
    block_remain -= size;
}
#endif /* FUZZ_TEST */

#ifdef HAVE_FCC_SUPPORT
#define FCC_MEMORY_SIZE (20 * 1024)
#endif

#ifndef NDEBUG
static int seek_beyond_eof;
#endif

#if defined(IO_USE_WINAPI)
DWORD _s, _ret, _err, _t;
OVERLAPPED _ovlap;
#endif

static void common_get_new_cmd(struct cb_io_s *ctx)
{
#ifndef NDEBUG
    if (ctx->disable_operation)
        diag_printf("[IO] reset disable_operation\n");
#endif
    ctx->disable_operation = 0;
}

static int dummy_open_done(ATTR_UNUSED struct cb_io_s *ctx, ATTR_UNUSED int a_bitrate, ATTR_UNUSED int v_bitrate, ATTR_UNUSED uint32_t file_duration)
{
    return CBIO_OK;
}

static void dummy_discontinuity(ATTR_UNUSED struct cb_io_s *ctx, ATTR_UNUSED cb_off_t end_pos)
{
}

static int common_stop_wait_input(struct cb_io_s *ctx)
{
#ifndef NDEBUG
    diag_printf("[IO] disable operation\n");
#endif
    ctx->disable_operation = 1;
    return 0;
}

typedef struct cb_memory_io_s
{
    cb_io_st        cbio;
    const uint8_t   *bstream;
    int             bstream_len;
    cb_fpos         bstream_pos;
} cb_memory_io_st;

static size_t msmem_read(struct cb_io_s *ctx, void *buf, size_t size)
{
    cb_memory_io_st *cbio = (cb_memory_io_st *) ctx;
    size_t copy = CB_MIN(size, cbio->bstream_len - cbio->bstream_pos);

    if (ctx->disable_operation || copy <= 0) return 0;
    memcpy(buf, cbio->bstream + cbio->bstream_pos, copy);
    cbio->bstream_pos += copy;

    return copy;
}

static cb_off_t msmem_tell(struct cb_io_s *ctx)
{
    return ((cb_memory_io_st *) ctx)->bstream_pos;
}

static cb_off_t msmem_seek(struct cb_io_s *ctx, cb_off_t offset, int whence)
{
    cb_memory_io_st *cbio = (cb_memory_io_st *) ctx;
    cb_off_t pos = -1;

    switch (whence)
    {
    case SEEK_SET:
        pos = offset; break;
    case SEEK_CUR:
        pos = cbio->bstream_pos + offset; break;
    case SEEK_END:
        pos = cbio->bstream_len + offset; break;
    }

    if (pos < 0) return -1;

    cbio->bstream_pos = pos;

    return pos;
}

static void msmem_close(struct cb_io_s **ctx)
{
    ms_heap_freep((void **) ctx);
}

static size_t msmem_aread(ATTR_UNUSED struct cb_io_s *ctx, ATTR_UNUSED void *buf, ATTR_UNUSED size_t size)
{
    assert(0);
    return 0;
}

int open_memory_input(cb_io_st **pcbio, const void *data, const int len, int read_buf_size)
{
    cb_memory_io_st *memio;

    *pcbio = 0;
    memio = ms_heap_malloc(sizeof(cb_memory_io_st));

    if (!memio)
    {
        return CBIO_MallocFailed;
    }

    *pcbio = &memio->cbio;
    memset(memio, 0, sizeof(cb_memory_io_st));

    memio->cbio.read            = msmem_read;
    memio->cbio.seek            = msmem_seek;
    memio->cbio.tell            = msmem_tell;
    memio->cbio.close           = msmem_close;
    memio->cbio.aread           = msmem_aread;
    memio->cbio.open_done       = dummy_open_done;
    memio->cbio.get_new_cmd     = common_get_new_cmd;
    memio->cbio.stop_wait_input = common_stop_wait_input;
    memio->cbio.discontinuity   = dummy_discontinuity;
    memio->cbio.block_size      = read_buf_size;
    memio->cbio.seekable        = 1;
    memio->cbio.context         = 0;
    memio->cbio.filename        = 0;
    memio->bstream              = data;
    memio->bstream_len          = len;

    return CBIO_OK;
}

static size_t msio_read(struct cb_io_s *ctx, void *buf, size_t size)
{
    size_t read_size;

#ifdef FUZZ_TEST
    cb_fpos pos = ms_seek((MSFILE) ctx->context, 0, SEEK_CUR);
    if (pos > truncate_pos)
        return 0;
    if (enable_truncate && pos + size > truncate_pos)
        size = truncate_pos - pos;
#endif
    if (ctx->disable_operation)
        return 0;

#ifndef NDEBUG
    assert(!seek_beyond_eof);
#endif

    read_size = ms_read(buf, 1, size, (MSFILE) ctx->context);

#ifdef FUZZ_TEST
    generate_bit_error(buf, read_size);
    generate_block_error(buf, read_size);
#endif

    return read_size;
}

static cb_off_t msio_tell(struct cb_io_s *ctx)
{
    return ms_seek((MSFILE) ctx->context, 0, SEEK_CUR);
}

static cb_off_t msio_seek(struct cb_io_s *ctx, cb_off_t offset, int whence)
{
#ifdef FUZZ_TEST
    if (enable_truncate && whence == SEEK_END)
    {
        cb_off_t fsize = ms_seek((MSFILE) ctx->context, 0, SEEK_END);
        offset -= fsize - truncate_pos;
    }
#endif

#ifndef NDEBUG
    {
        cb_off_t curpos = ms_seek((MSFILE) ctx->context, 0, SEEK_CUR);
        cb_off_t fsize  = ms_seek((MSFILE) ctx->context, 0, SEEK_END);

        // seek to EOF is a common technique to get file size, treat it as legal
        ms_seek((MSFILE) ctx->context, curpos, SEEK_SET);
        seek_beyond_eof = (whence == SEEK_SET && offset > fsize)                  ||
                          (whence == SEEK_CUR && offset + msio_tell(ctx) > fsize) ||
                          (whence == SEEK_END && offset > 0);
        if (seek_beyond_eof)
            return -1;
    }
#endif

    return ms_seek((MSFILE) ctx->context, offset, whence);
}

static void msio_close(struct cb_io_s **ctx)
{
#ifdef HAVE_FCC_SUPPORT
    ms_heap_freep(&(*ctx)->fcc_buf);
#endif

    ms_close((MSFILE) (*ctx)->context);

#ifndef NDEBUG
    seek_beyond_eof = 0;
#endif

#ifdef FUZZ_TEST
    random_seed = 0;
#endif

    ms_heap_freep((void **) ctx);
}

static size_t msio_aread(ATTR_UNUSED struct cb_io_s *ctx, ATTR_UNUSED void *buf, ATTR_UNUSED size_t size)
{
#if defined(IO_USE_WINAPI) || (defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 3))
    size_t read_size;
    if (ctx->disable_operation)
        return 0;

    read_size = ms_aread_mstar(buf, 1, size, (MSFILE) ctx->context);
    return read_size;
#else
    assert(0);
    return 0;
#endif
}

static size_t msio_write(struct cb_io_s *ctx, void *buf, size_t size)
{
    size_t write_size;

    if (ctx->disable_operation)
        return 0;

    write_size = ms_write(buf, 1, size, (MSFILE) ctx->context); /* parasoft-suppress  BD-PB-NOTINIT "suppress by Ernie, Parasoft mis-judge" */
    return write_size;
}

int open_file_input(cb_io_st **pcbio, const ms_fnchar *filename, int read_buf_size, cbio_open_mode_et mode, ATTR_UNUSED int enable_fcc)
{
    cb_io_st *cbio;

    *pcbio = cbio = ms_heap_malloc(sizeof(cb_io_st));

    if (!cbio)
    {
        return CBIO_MallocFailed;
    }

    memset(cbio, 0, sizeof(cb_io_st));

    cbio->read       = msio_read;
    cbio->write      = msio_write;
    cbio->seek       = msio_seek;
    cbio->tell       = msio_tell;
    cbio->close      = msio_close;
    cbio->aread      = msio_aread;
    cbio->open_done       = dummy_open_done;
    cbio->get_new_cmd     = common_get_new_cmd;
    cbio->stop_wait_input = common_stop_wait_input;
    cbio->discontinuity   = dummy_discontinuity;
    cbio->open_mode  = mode;
    cbio->seekable   = 1;

#ifdef SUPPORT_ASYNCIO
    cbio->block_size = read_buf_size >> 1;
#else
    cbio->block_size = read_buf_size;
#endif

    if (mode == CBIO_FO_WB)
        cbio->context    = (void *) ms_open(filename, MS_FO_WB);
    else if (mode == CBIO_FO_AB)
        cbio->context    = (void *) ms_open(filename, MS_FO_AB);
    else
    {
#ifdef HAVE_FCC_SUPPORT
        if (enable_fcc)
        {
            cbio->fcc_buf = ms_heap_malloc(FCC_MEMORY_SIZE);
            if (!cbio->fcc_buf)
                return CBIO_MallocFailed;
            cbio->context    = (void *) ms_open_fcc(filename, MS_FO_RB, cbio->fcc_buf, FCC_MEMORY_SIZE);
        }
        else
#endif
            cbio->context    = (void *) ms_open(filename, MS_FO_RB);
    }

    cbio->filename   = filename;

    if (ms_open_fail((MSFILE) cbio->context))
    {
#ifdef HAVE_FCC_SUPPORT
        if (cbio->fcc_buf)
            ms_heap_freep(&cbio->fcc_buf);
#endif
        ms_heap_freep((void**) pcbio);
        return CBIO_OpenFailed;
    }

#ifdef FILE_FAKE_STREAMING
    cbio->streaming  = 1;
    cbio->input_size = ms_seek(cbio->context, 0, SEEK_END);
    ms_seek(cbio->context, 0, SEEK_SET);
#endif
#ifdef FUZZ_TEST
    init_random_pattern(cbio);
#endif

    return CBIO_OK;
}

#ifdef IO_USE_UNISTD
int open_fd_input(cb_io_st **pcbio, const int fd, int read_buf_size, cbio_open_mode_et mode)
{
    cb_io_st *cbio;

    *pcbio = cbio = ms_heap_malloc(sizeof(cb_io_st));

    if (!cbio)
    {
        return CBIO_MallocFailed;
    }

    memset(cbio, 0, sizeof(cb_io_st));

    cbio->read       = msio_read;
    cbio->write      = msio_write;
    cbio->seek       = msio_seek;
    cbio->tell       = msio_tell;
    cbio->close      = msio_close;
    cbio->aread      = msio_aread;
    cbio->open_done       = dummy_open_done;
    cbio->get_new_cmd     = common_get_new_cmd;
    cbio->stop_wait_input = common_stop_wait_input;
    cbio->discontinuity   = dummy_discontinuity;
    cbio->open_mode  = mode;
    cbio->seekable   = 1;
    cbio->filename   = 0;

#ifdef SUPPORT_ASYNCIO
    cbio->block_size = read_buf_size >> 1;
#else
    cbio->block_size = read_buf_size;
#endif

    cbio->context = (void *) ms_fdopen(fd, mode);

    if (ms_open_fail((MSFILE) cbio->context))
    {
        ms_heap_freep((void**) pcbio);
        return CBIO_OpenFailed;
    }

#ifdef FILE_FAKE_STREAMING
    cbio->streaming  = 1;
    cbio->input_size = ms_seek(cbio->context, 0, SEEK_END);
    ms_seek(cbio->context, 0, SEEK_SET);
#endif
#ifdef FUZZ_TEST
    init_random_pattern(cbio);
#endif

    return CBIO_OK;
}
#endif

typedef struct cb_pcm_io_s
{
    cb_io_st    cbio;
    cb_io_st    *raw;
    cb_off_t    file_len;
    cb_off_t    header_len;
    cb_off_t    file_pos;
    uint8_t     header[];
} cb_pcm_io_st;

static size_t pcmf_read(struct cb_io_s *ctx, void *buf, size_t size)
{
    cb_pcm_io_st *pcmio = (cb_pcm_io_st *) ctx;
    size_t copy_size = 0;

    if (pcmio->file_pos < pcmio->header_len)
    {
        copy_size = CB_MIN(size, (size_t)(pcmio->header_len - pcmio->file_pos));
        memcpy(buf, pcmio->header + pcmio->file_pos, copy_size);
        pcmio->file_pos += copy_size;
        size            -= copy_size;
    }

    if (size)
    {
        copy_size += pcmio->raw->read(pcmio->raw, (uint8_t *) buf + copy_size, size);
    }

    return copy_size;
}

static cb_off_t pcmf_seek(struct cb_io_s *ctx, cb_off_t offset, int whence)
{
    cb_pcm_io_st *pcmio = (cb_pcm_io_st *) ctx;
    cb_off_t pos = -1;

    switch (whence)
    {
    case SEEK_SET:
        pos = offset; break;
    case SEEK_CUR:
        pos = pcmio->file_pos + offset; break;
    case SEEK_END:
        pos = pcmio->file_len + offset; break;
    }

    if (pos < 0) return -1;

    if (pos <= pcmio->header_len)
    {
        if (pcmio->raw->seek(pcmio->raw, 0, SEEK_SET) == -1)
            return -1;
    }
    else
    {
        if (pcmio->raw->seek(pcmio->raw, pos - pcmio->header_len, SEEK_SET) == -1)
            return -1;
    }

    return pcmio->file_pos = pos;
}

static cb_off_t pcmf_tell(struct cb_io_s *ctx)
{
    cb_pcm_io_st *pcmio = (cb_pcm_io_st *) ctx;
    return pcmio->file_pos;
}

static void pcmf_close(struct cb_io_s **ctx)
{
    cb_pcm_io_st *pcmio = (cb_pcm_io_st *) *ctx;
    pcmio->raw->close(&pcmio->raw);
    ms_heap_freep((void **) ctx);
}

int open_pcm_file_input(cb_io_st **cbio, cb_io_st *raw, void *wfex, int wfex_len)
{
    cb_pcm_io_st *pcmio;
    int32_t raw_size, file_size, wfex_size;
    uint8_t *p;

    raw_size = raw->seek(raw, 0, SEEK_END);
    wfex_size = wfex_len;
    file_size = 20 + wfex_size + 8 + raw_size;
    raw->seek(raw, 0, SEEK_SET);

    pcmio = ms_heap_malloc(sizeof(cb_pcm_io_st) + file_size - raw_size);

    if (!pcmio)
    {
        return CBIO_MallocFailed;
    }

    *cbio = &pcmio->cbio;
    memset(pcmio, 0, sizeof(cb_pcm_io_st));

    pcmio->cbio.context           = 0;
    pcmio->cbio.read              = pcmf_read;
    pcmio->cbio.seek              = pcmf_seek;
    pcmio->cbio.tell              = pcmf_tell;
    pcmio->cbio.close             = pcmf_close;
    pcmio->cbio.open_done         = dummy_open_done;
    pcmio->cbio.get_new_cmd       = common_get_new_cmd;
    pcmio->cbio.stop_wait_input   = common_stop_wait_input;
    pcmio->cbio.discontinuity     = dummy_discontinuity;
    pcmio->cbio.open_mode         = raw->open_mode;
    pcmio->cbio.seekable          = raw->seekable;
    pcmio->cbio.block_size        = raw->block_size;

    // write WAV file
    pcmio->raw           = raw;
    pcmio->file_pos      = 0;
    pcmio->file_len      = file_size;
    pcmio->header_len    = file_size - raw_size;

    p = pcmio->header;
    file_size -= 8;
    memcpy(p, "RIFF", 4);       p += 4;
    memcpy(p, &file_size, 4);   p += 4;
    memcpy(p, "WAVEfmt ", 8);   p += 8;
    memcpy(p, &wfex_size, 4);   p += 4;
    memcpy(p, wfex, wfex_size); p += wfex_size;
    memcpy(p, "data", 4);       p += 4;
    memcpy(p, &raw_size, 4);

    return CBIO_OK;
}

int open_file_stream(cb_io_st **pcbio, const ms_fnchar *filename, int read_buf_size)
{
    cb_io_st *cbio;

    *pcbio = cbio = ms_heap_malloc(sizeof(cb_io_st));

    if (!cbio)
    {
        return CBIO_MallocFailed;
    }

    memset(cbio, 0, sizeof(cb_io_st));

    cbio->read       = msio_read;
    cbio->write      = msio_write;
    cbio->seek       = msio_seek;
    cbio->tell       = msio_tell;
    cbio->close      = msio_close;
    cbio->aread      = msio_aread;
    cbio->open_done       = dummy_open_done;
    cbio->get_new_cmd     = common_get_new_cmd;
    cbio->stop_wait_input = common_stop_wait_input;
    cbio->discontinuity   = dummy_discontinuity;

    cbio->block_size = read_buf_size;
    cbio->seekable   = 1;
    cbio->streaming  = 1;
    cbio->use_thread = 1;
    cbio->rbuf_mode  = 1;
    cbio->context    = (void *) ms_open(filename, MS_FO_RB);
    cbio->filename   = filename;

    if (ms_open_fail((MSFILE) cbio->context))
    {
        ms_heap_freep((void**) pcbio);
        return CBIO_OpenFailed;
    }

#ifdef FUZZ_TEST
    init_random_pattern(cbio);
#endif

    return CBIO_OK;
}

static void msio_push_close(struct cb_io_s **ctx)
{
    ms_heap_freep((void **) ctx);
}

int open_push_input(cb_io_st **pcbio, const ms_fnchar *filename, int read_buf_size)
{
    cb_io_st *cbio;

    *pcbio = cbio = ms_heap_malloc(sizeof(cb_io_st));

    if (!cbio)
    {
        return CBIO_MallocFailed;
    }

    memset(cbio, 0, sizeof(cb_io_st));

    cbio->read       = 0;
    cbio->seek       = 0;
    cbio->tell       = 0;
    cbio->close      = msio_push_close;
    cbio->aread      = 0;
    cbio->open_done       = dummy_open_done;
    cbio->get_new_cmd     = common_get_new_cmd;
    cbio->stop_wait_input = common_stop_wait_input;
    cbio->discontinuity   = dummy_discontinuity;
    cbio->block_size = read_buf_size;
    cbio->streaming  = 1;
    cbio->rbuf_mode  = 1;
    cbio->filename   = filename;

    return CBIO_OK;
}
