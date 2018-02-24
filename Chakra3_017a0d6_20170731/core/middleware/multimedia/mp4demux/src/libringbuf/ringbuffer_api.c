#include <string.h>
#include <assert.h>
#include "ms_dprintf.h"
#include "ringbuffer_api.h"
#include "sys_thread.h"
#include "../sys_common.h"

/* advance read ptr by <num> bytes */
#define RINGBUFFER_SKIP(rbuf,num)   \
{ \
    (rbuf)->pread += (num); \
    if ((rbuf)->pread >= (rbuf)->size) \
        (rbuf)->pread -= (rbuf)->size; \
}

void sys_ringbuffer_init(struct sys_ringbuffer *rbuf, void *data, uint32_t len)
{
    ms_dprintf(1, "rbuf id = 0x%0x\n", rbuf);
    rbuf->pread = rbuf->pwrite = 0;
    assert(data != NULL);
    assert(len != 0);
    rbuf->data = data;
    rbuf->size = len;
    rbuf->pkt_cnt = 0;
    rbuf->buf_eos = 0;
    rbuf->wsize_req = 0;
    rbuf->rsize_req = 0;
    rbuf->error = 0;
    rbuf->rlock = 0;
    rbuf->wlock = 0;
    rbuf->slock = 0;
    rbuf->srlock = 0;

    rb_mutex_init(&rbuf->ring_mutex, NULL);
    rb_cond_init(&rbuf->ring_avail_cond, &rbuf->ring_mutex);
    rb_cond_init(&rbuf->ring_free_cond, &rbuf->ring_mutex);
}

// if NO_THREAD is defined, condition var and mutex are mapped to void
void sys_ringbuffer_destroy(ATTR_UNUSED struct sys_ringbuffer *rbuf)
{
    rb_cond_destroy(&rbuf->ring_avail_cond);
    rb_cond_destroy(&rbuf->ring_free_cond);
    rb_mutex_destroy(&rbuf->ring_mutex);
}

void sys_ringbuffer_close(struct sys_ringbuffer *rbuf)
{
    rb_mutex_lock(&rbuf->ring_mutex);

    rbuf->buf_eos = 1;

    rbuf->pkt_cnt = 0;
    rbuf->pread   = rbuf->pwrite;
    rbuf->error   = 0;

    rb_cond_signal(&rbuf->ring_avail_cond);
    rb_cond_signal(&rbuf->ring_free_cond);

    rb_mutex_unlock(&rbuf->ring_mutex);
}

int sys_ringbuffer_empty(struct sys_ringbuffer *rbuf)
{
    return (rbuf->pread==rbuf->pwrite);
}

static int32_t sys_ringbuffer_free_internal(struct sys_ringbuffer *rbuf)
{
    int32_t free_size;

    if (rbuf->pread > rbuf->pwrite)
        free_size = rbuf->pread - rbuf->pwrite;
    else
        free_size = rbuf->size - rbuf->pwrite + rbuf->pread;

    return free_size - 1;
}

static int32_t sys_ringbuffer_avail_internal(struct sys_ringbuffer *rbuf)
{
    int32_t avail;

    if (rbuf->pwrite >= rbuf->pread)
        avail = rbuf->pwrite - rbuf->pread;
    else
        avail = rbuf->size - rbuf->pread + rbuf->pwrite;

    return avail;
}

int32_t sys_ringbuffer_free(struct sys_ringbuffer *rbuf)
{
    int32_t free_size;

    rb_mutex_lock(&rbuf->ring_mutex);

    free_size = sys_ringbuffer_free_internal(rbuf);

    rb_mutex_unlock(&rbuf->ring_mutex);

    return free_size;
}

int32_t sys_ringbuffer_avail(struct sys_ringbuffer *rbuf)
{
    int32_t avail;

    rb_mutex_lock(&rbuf->ring_mutex);

    avail = sys_ringbuffer_avail_internal(rbuf);

    rb_mutex_unlock(&rbuf->ring_mutex);

    return avail;
}

void sys_ringbuffer_flush(struct sys_ringbuffer *rbuf)
{
    rb_mutex_lock(&rbuf->ring_mutex);

    rbuf->pkt_cnt = 0;
    rbuf->pread   = rbuf->pwrite;
    rbuf->error   = 1;

    rb_cond_signal(&rbuf->ring_avail_cond);
    rb_cond_signal(&rbuf->ring_free_cond);

    rb_mutex_unlock(&rbuf->ring_mutex);
}


void sys_ringbuffer_reset(struct sys_ringbuffer *rbuf)
{
    rb_mutex_lock(&rbuf->ring_mutex);

    rbuf->pkt_cnt = 0;
    rbuf->pread   = 0;
    rbuf->pwrite  = 0;
    rbuf->buf_eos = 0;
    rbuf->slock   = 0;

    rb_cond_signal(&rbuf->ring_avail_cond);
    rb_cond_signal(&rbuf->ring_free_cond);

    rb_mutex_unlock(&rbuf->ring_mutex);
}

int32_t sys_ringbuffer_walloc(struct sys_ringbuffer *rbuf, uint32_t len)
{
    int32_t free_size;

    rb_mutex_lock(&rbuf->ring_mutex);

    assert(len < rbuf->size);
    rbuf->wsize_req = len;

    free_size = sys_ringbuffer_free_internal(rbuf);

    ms_dprintf(2, "alloc::%d, %d, %d, %d\n", free_size, rbuf->wsize_req, rbuf->pread, rbuf->pwrite);

    while (free_size < rbuf->wsize_req && !rbuf->buf_eos) {
        int ret;
        ms_dprintf(1, "WARNING: rbuf id 0x%x full\n", rbuf);
        ret = rb_cond_timed_wait(&rbuf->ring_free_cond, &rbuf->ring_mutex, 10000);
        if (ret != 1) {
            rb_mutex_unlock(&rbuf->ring_mutex);
            return -2;
        }
        if (rbuf->error) {
            rbuf->error = 0;
            if (rbuf->pkt_cnt == 0 && rbuf->pread == rbuf->pwrite) {
                ms_dprintf(1, "rbuf alocate error");
                rb_mutex_unlock(&rbuf->ring_mutex);
                return -1;
            }
        }

        ms_dprintf(2, "allocated\n");

        free_size = sys_ringbuffer_free_internal(rbuf);
    }

    rbuf->wsize_req = 0;

    rb_mutex_unlock(&rbuf->ring_mutex);

    return free_size;
}

void sys_ringbuffer_byte_release(struct sys_ringbuffer *rbuf, uint32_t release_len)
{
    rb_mutex_lock(&rbuf->ring_mutex);

    assert(rbuf->pkt_cnt >= release_len);

    RINGBUFFER_SKIP(rbuf, release_len);

    rbuf->pkt_cnt -= release_len;

    if (rbuf->wsize_req) {
        // signal only if the free space is larger than requested
        int32_t free_size;
        free_size = sys_ringbuffer_free_internal(rbuf);
        if (free_size >= rbuf->wsize_req)
            rb_cond_signal(&rbuf->ring_free_cond);
    }

    rbuf->srlock = 0;
    rb_mutex_unlock(&rbuf->ring_mutex);
}

int32_t sys_ringbuffer_read_peek(struct sys_ringbuffer *rbuf, uint8_t *buf, uint32_t len, uint32_t skip_len)
{
    uint32_t todo = len;
    uint32_t split;
    uint32_t curr_pread = rbuf->pread;

    // skip pktt buffer
    if (skip_len)
    {
        curr_pread += skip_len;
        if (curr_pread >= rbuf->size)
            curr_pread -= rbuf->size;
    }

    split = (curr_pread + len > rbuf->size) ? rbuf->size - curr_pread : 0;
    if (split > 0) {
        memcpy(buf, rbuf->data+curr_pread, split);

        buf += split;
        todo -= split;
        curr_pread = 0;
    }
    memcpy(buf, rbuf->data + curr_pread, todo);

    return len;
}

int32_t sys_ringbuffer_byte_read_peek(struct sys_ringbuffer *rbuf, uint8_t *buf, int32_t len)
{
    int32_t avail;

    rb_mutex_lock(&rbuf->ring_mutex);
    rbuf->srlock = 1;

    assert(len < rbuf->size);
    rbuf->rsize_req = len;

    avail = sys_ringbuffer_avail_internal(rbuf);

    while (avail < len && !rbuf->buf_eos) {
        int ret;
        ms_dprintf(1, "WARNING: rbuf id 0x%x empty\n", rbuf);
        ret = rb_cond_timed_wait(&rbuf->ring_avail_cond, &rbuf->ring_mutex, 10000);
        if (ret != 1)
            break;

        avail = sys_ringbuffer_avail_internal(rbuf);
    }

    if (rbuf->pkt_cnt < (uint32_t)len) {
        ms_dprintf(1, "No more data, (remaining, want) = (%d, %d)\n", rbuf->pkt_cnt, len);
        len = rbuf->pkt_cnt;
    }

    if (buf != NULL)
        sys_ringbuffer_read_peek(rbuf, buf, len, 0);

    ms_dprintf(2, "pktt_read::%d, %d\n", rbuf->pread, rbuf->pwrite);

    rbuf->rsize_req = 0;

    rb_mutex_unlock(&rbuf->ring_mutex);

    return len;
}


/************************************************************************/
/*  No need mutex lock when single thread                               */
/************************************************************************/
int32_t sys_ringbuffer_byte_read_peek_single_thread(struct sys_ringbuffer *rbuf, uint8_t *buf, int32_t len)
{
    //rb_mutex_lock(&rbuf->ring_mutex);

    if (buf != NULL) {
        if (rbuf->pkt_cnt < (uint32_t)len) {
            ms_dprintf(1, "No more data, (remaining, want) = (%d, %d)\n", rbuf->pkt_cnt, len);
            len = rbuf->pkt_cnt;
        }
        sys_ringbuffer_read_peek(rbuf, buf, len, 0);
    }
    ms_dprintf(2, "pktt_read::%d, %d\n", rbuf->pread, rbuf->pwrite);

    //rb_mutex_unlock(&rbuf->ring_mutex);

    return len;
}

static int32_t sys_ringbuffer_write(struct sys_ringbuffer *rbuf, const uint8_t *buf, uint32_t len)
{
    uint32_t todo = len;
    uint32_t split;

    split = (rbuf->pwrite + len > rbuf->size) ? rbuf->size - rbuf->pwrite : 0;

    if (split > 0) {
        memcpy(rbuf->data + rbuf->pwrite, buf, split);
        buf  += split;
        todo -= split;
        rbuf->pwrite = 0;
    }

    assert(rbuf->pwrite + todo <= rbuf->size);
    memcpy(rbuf->data + rbuf->pwrite, buf, todo);

    rbuf->pwrite += todo;
    if (rbuf->pwrite == rbuf->size)
        rbuf->pwrite = 0;

    assert(rbuf->pwrite != rbuf->pread);

    return len;
}

/************************************************************************/
/*  no extra temp buffer required to do memcpy into ring buffer            */
/*  since we enlarge the ring buffer.                                   */
/*  But remember to copy the tail back to the head.                     */
/************************************************************************/

int32_t sys_ringbuffer_byte_write2(struct sys_ringbuffer *rbuf, uint32_t len)
{
    uint32_t todo = len;
    uint32_t split;

    rb_mutex_lock(&rbuf->ring_mutex);

    if (rbuf->rlock == 0) {
        rbuf->pkt_cnt+=len;
        split = (rbuf->pwrite + len > rbuf->size) ? rbuf->size - rbuf->pwrite : 0;
        if (split > 0) {
            todo -= split;
            rbuf->pwrite = 0;
            memcpy(rbuf->data, rbuf->data+rbuf->size, todo);
        }

        rbuf->pwrite += todo;
        if (rbuf->pwrite >= rbuf->size)
            rbuf->pwrite = 0;
    }
    rbuf->rlock = 0;

    ms_dprintf(2, "pktt_write::%d, %d\n", rbuf->pread, rbuf->pwrite);

    if (rbuf->rsize_req) {
        // signal only if the avail space is larger than requested
        int32_t avail;
        avail = sys_ringbuffer_avail_internal(rbuf);
        if (avail >= rbuf->wsize_req)
            rb_cond_signal(&rbuf->ring_avail_cond);
    }

    rb_mutex_unlock(&rbuf->ring_mutex);

    return len;
}


int32_t sys_ringbuffer_byte_write(struct sys_ringbuffer *rbuf, const uint8_t *buf, uint32_t len)
{
    rb_mutex_lock(&rbuf->ring_mutex);

    if (rbuf->rlock == 0) {
        if (buf != NULL) {
            sys_ringbuffer_write(rbuf, buf, len);
        }
        rbuf->pkt_cnt+=len;
    }
    rbuf->rlock = 0;
    //ms_dprintf(2, "pktt_write::%d, %d, %d\n", rbuf->pread, rbuf->pwrite, len);

    if (rbuf->rsize_req) {
        // signal only if the avail space is larger than requested
        int32_t avail;
        avail = sys_ringbuffer_avail_internal(rbuf);
        if (avail >= rbuf->wsize_req)
            rb_cond_signal(&rbuf->ring_avail_cond);
    }

    rb_mutex_unlock(&rbuf->ring_mutex);

    return len;
}
