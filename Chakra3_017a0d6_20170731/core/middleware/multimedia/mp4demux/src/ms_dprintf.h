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


#ifndef MS_DPRINTF_H
#define MS_DPRINTF_H

#if !defined(DEBUG_LEVEL)
#define DEBUG_LEVEL 0
#endif

#ifdef _MSC_VER

#if DEBUG_LEVEL == 0

static __inline void ms_dprintf(int level, const char *fmt, ...) {}

#else /* DEBUG_LEVEL */

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

static __inline void ms_dprintf(int level, const char *fmt, ...)
{
    va_list ap;
    char msg[2048];

    if (level > DEBUG_LEVEL)
        return;

    va_start(ap, fmt);
    vsprintf(msg, fmt, ap);
#ifdef WINCE
    fprintf(stderr, "%s", msg);
#else
    OutputDebugStringA(msg);
#endif
    va_end(ap);
}

#endif /* DEBUG_LEVEL */

#else /* _MSC_VER */

#if DEBUG_LEVEL == 0

#define ms_dprintf(arg...) ((void) 0)

#else /* DEBUG_LEVEL */

#if defined __I_SW__
#include <stdio.h>
#include <stdarg.h>
//#pragma import(__use_c99_library)
static __inline void ms_dprintf(int level, const char *fmt, ...)
{
    va_list ap;
    char msg[2048];

    if (level > DEBUG_LEVEL)
        return;

    va_start(ap, fmt);
    vsprintf(msg, fmt, ap);
    send_trace(msg);
    va_end(ap);
}

#else /* __I_SW__ */

#define ms_dprintf(level, fmt, arg...) \
    do { \
        if (level <= DEBUG_LEVEL) diag_printf(fmt, ##arg); \
    } while (0)

#endif /* __I_SW__ */

#endif /* DEBUG_LEVEL */

#endif /* _MSC_VER */


#if defined(__I_SW__)
#  include "sys_sys_isw_uart.h"
#  define _CUSAVP                 (_CUS2 | LEVEL_30)
#  define diag_printf             send_trace
#elif defined(__RTK_OS__)
#  include "sys_vm_dbg.ho"
#  define _CUSAVP                 (_CUS2 | LEVEL_30)
#  define diag_printf(fmt, ...)   vm_dbgTrace(_CUSAVP, fmt, ##__VA_ARGS__)
#elif defined(ECOS)
#  include <cyg/infra/diag.h>
#elif defined(AEONDEV)
#  include "utl.h"
#  define diag_printf             UTL_printf
#elif defined(__ANDROID__)
#  define LOG_NDEBUG 0
#  define LOG_TAG "[MMP]"
#  include <utils/Log.h>
#  define diag_printf(fmt, ...)   ALOGV("[%d] "fmt, gettid(), ##__VA_ARGS__)
#elif defined(_MSC_VER)
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

static __inline void diag_printf(const char *fmt, ...)
{
    va_list ap;
    char msg[2048];

    va_start(ap, fmt);
    vsprintf_s(msg, 2048, fmt, ap);
#ifdef WINCE
    fprintf(stderr, "%s", msg);
#else
    OutputDebugStringA(msg);
#endif
    va_end(ap);
}
#else
#  include <stdio.h>
#  define diag_printf             printf
#endif
#endif /* MS_DPRINTF_H */
