#ifndef RINGBUFFER_API_H
#define RINGBUFFER_API_H

#include "../hcommon.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct sys_ringbuffer {
    uint8_t  *data;                 // ringbuf
    uint32_t size;                  // ringbuf size
    uint32_t pread;                 // offset of read pointer
    uint32_t pwrite;                // offset of write pointer
    volatile uint32_t  pkt_cnt;     // number of packets inside
    int16_t  buf_eos;               // 0: Not EOS, 1: EOS, 2: EOS temporarily
    int32_t  wsize_req;             // write size requested
    int32_t  rsize_req;             // read size requested
    int32_t  error;
    int8_t  rlock;                  // for multi-thread seek protection: read side
    int8_t  wlock;                  // for multi-thread seek protection: write side
    volatile int8_t  slock;         // for switch ring buffer protection
    int8_t  srlock;                 // for switch ring buffer protection, make sure read is completed.
    rb_mutex_t ring_mutex;          // critical section protector
    rb_cond_t  ring_avail_cond;     // signal from empty to non-empty
    rb_cond_t  ring_free_cond;      // signal from full to non-full
};

/* initialize ring buffer, lock and queue */
void sys_ringbuffer_init(struct sys_ringbuffer *rbuf, void *data, uint32_t len);

/* delete ring buffer, lock and cond */
void sys_ringbuffer_destroy(struct sys_ringbuffer *rbuf);

/* close ring buffer, will set EOS */
void sys_ringbuffer_close(struct sys_ringbuffer *rbuf);

/* test whether buffer is empty */
int sys_ringbuffer_empty(struct sys_ringbuffer *rbuf);

/* return the number of free bytes in the buffer */
int32_t sys_ringbuffer_free(struct sys_ringbuffer *rbuf);

/* return the number of bytes available in the buffer */
int32_t sys_ringbuffer_avail(struct sys_ringbuffer *rbuf);

/* alloc the required size from buffer, would wait if not available */
#define sys_ringbuffer_alloc sys_ringbuffer_walloc
int32_t sys_ringbuffer_walloc(struct sys_ringbuffer *rbuf, uint32_t alloc_len);

void sys_ringbuffer_reset(struct sys_ringbuffer *rbuf);

/* read routines & macros */
/* ---------------------- */

/* flush buffer */
void sys_ringbuffer_flush(struct sys_ringbuffer *rbuf);

int32_t sys_ringbuffer_read_peek(struct sys_ringbuffer *rbuf, uint8_t *buf, uint32_t len, uint32_t skip_len);

/* write routines & macros */
/* ----------------------- */

void sys_ringbuffer_byte_release(struct sys_ringbuffer *rbuf, uint32_t release_len);
int32_t sys_ringbuffer_byte_read_peek(struct sys_ringbuffer *rbuf, uint8_t *buf, int32_t len);
int32_t sys_ringbuffer_byte_read_peek_single_thread(struct sys_ringbuffer *rbuf, uint8_t *buf, int32_t len);
int32_t sys_ringbuffer_byte_write(struct sys_ringbuffer *rbuf, const uint8_t *buf, uint32_t len);
int32_t sys_ringbuffer_byte_write2(struct sys_ringbuffer *rbuf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
