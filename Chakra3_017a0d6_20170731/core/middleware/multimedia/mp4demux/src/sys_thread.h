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


#ifndef SYS_THREAD_H
#define SYS_THREAD_H

#if defined(MIPSDEV) || defined(ECOS)
#define USE_CYG_THREAD
#endif

typedef void * (* thread_function)(void *);

#ifdef USE_CYG_THREAD
#include <cyg/kernel/kapi.h>

#define SYSTH_PRIORITY_NORMAL 15
#if defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM==3)
#define SYSTH_PRIORITY_HIGH    3
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM==4)
#define SYSTH_PRIORITY_HIGH    10
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM==5)
#define SYSTH_PRIORITY_HIGH    5
#else
#define SYSTH_PRIORITY_HIGH    10
#endif

typedef struct sys_thread_s {
    cyg_handle_t handle;
    cyg_thread   thread;
    cyg_sem_t    semaphore;
} sys_thread_st;

#define sys_thread_create(t, thread_routine, thread_data, name, priority, stack_pointer, stack_size) \
do { \
    cyg_thread_create(priority, \
                      (cyg_thread_entry_t *) &thread_routine, \
                      (cyg_addrword_t) thread_data, \
                      name, \
                      stack_pointer, \
                      stack_size, \
                      &((sys_thread_st *) t)->handle, \
                      &((sys_thread_st *) t)->thread); \
    cyg_thread_resume(((sys_thread_st *) t)->handle); \
    cyg_semaphore_init(&((sys_thread_st *) t)->semaphore, 0); \
} while (0)

#define sys_thread_exit(t) do { \
    cyg_semaphore_post(&((sys_thread_st *) t)->semaphore); \
    cyg_thread_exit(); \
} while (0)

#define sys_thread_join(t) do { \
    cyg_semaphore_wait(&((sys_thread_st *) t)->semaphore); \
    cyg_semaphore_destroy(&((sys_thread_st *) t)->semaphore); \
    cyg_thread_delete(((sys_thread_st *) t)->handle); \
} while (0)

#define sys_thread_delay(t) cyg_thread_delay(t)
#define sys_current_time()  cyg_current_time()

#elif defined(__RTK_OS__)
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_Rtk_Ho.h" // need this header for RTK_TICK_TO_MS

#define sys_thread_st   void *
#define sys_thread_create(t, thread_routine, thread_data, name, priority, stack_pointer, stack_size)
#define sys_thread_exit(t)
#define sys_thread_join(t)

#define sys_thread_delay(t) do { \
    uint32_t tick; \
    tick = RTK_TICK_TO_MS(t); \
    MsSleep(tick); \
} while (0)

#define sys_current_time()

#elif defined(NO_THREAD) /* USE_CYG_THREAD */
#define sys_thread_st   void *
#define sys_thread_create(t, thread_routine, thread_data, name, priority, stack_pointer, stack_size)
#define sys_thread_exit(t)
#define sys_thread_join(t)
#define sys_thread_delay(t)
#define sys_current_time()

#else

#include <semaphore.h>
#include <pthread.h>

typedef struct sys_thread_s {
    pthread_t handle;
} sys_thread_st;

#define sys_thread_create(t, thread_routine, thread_data, name, priority, stack_pointer, stack_size) \
do { \
    pthread_attr_t attr; \
    pthread_attr_init(&attr); \
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); \
    /* pthread_attr_setstackaddr(&attr, stack_pointer); */ \
    /* pthread_attr_setstacksize(&attr, stack_size); */ \
    pthread_create(&((sys_thread_st *) t)->handle, NULL, thread_routine, thread_data); \
    pthread_attr_destroy(&attr); \
} while (0)

#define sys_thread_exit(t) pthread_exit(NULL)

#define sys_thread_join(t) pthread_join(((sys_thread_st *) t)->handle, NULL)

#if defined(_MSC_VER)
#include <windows.h>
#define sys_thread_delay(t) Sleep(t)
#define sys_current_time()  GetTickCount()
#else
#define sys_thread_delay(t) usleep(t * 1000)
#define sys_current_time()  (clock() * 1000 / CLOCKS_PER_SEC)
#endif

#endif /* USE_CYG_THREAD */

#endif /* SYS_THREAD_H */
