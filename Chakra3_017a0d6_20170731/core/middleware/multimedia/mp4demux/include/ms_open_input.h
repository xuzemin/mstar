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


#ifndef MS_OPEN_INPUT_H
#define MS_OPEN_INPUT_H

#include "ms_io.h"
#include "ms_input.h"

#ifndef READSIZE
#define READSIZE (128 * 1024)
#endif

/* pull mode input source */
int open_memory_input(cb_io_st **cbio, const void *data, const int len, int read_buf_size);
int open_file_input(cb_io_st **cbio, const ms_fnchar *filename, int read_buf_size, cbio_open_mode_et mode, int enable_fcc);
int open_fd_input(cb_io_st **cbio, const int fd, int read_buf_size, cbio_open_mode_et mode);
int open_aync_file_input(cb_io_st *cbio, const ms_fnchar *filename);
int open_pcm_file_input(cb_io_st **cbio, cb_io_st *raw, void *wfex, int wfex_len);

/* push mode input source */
int open_file_stream(cb_io_st **cbio, const ms_fnchar *filename, int read_buf_size);
int open_push_input(cb_io_st **cbio, const ms_fnchar *filename, int read_buf_size);

#endif /* MS_OPEN_INPUT_H */
