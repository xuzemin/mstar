#ifndef HCOMMON_H
#define HCOMMON_H


///////////////////////////////////////////////////////////

#if defined(MIPSDEV) || defined(ECOS)
#include <cyg/kernel/kapi.h>
#include <cyg/infra/diag.h>
#include <cyg/hal/plf_intr.h>
#define USE_CYG_THREAD
#elif !defined(NO_THREAD)
#include <semaphore.h>
#include <pthread.h>
#endif

/************************************************************************/
/*   thread between demux and file input                                */
/************************************************************************/
#if defined(USE_CYG_THREAD)

#define rb_mutex_init(a, b)         cyg_mutex_init(a)
#define rb_mutex_lock               cyg_mutex_lock
#define rb_mutex_unlock             cyg_mutex_unlock
#define rb_mutex_destroy            cyg_mutex_destroy
#define rb_cond_init                cyg_cond_init
#define rb_cond_signal              cyg_cond_signal
#define rb_cond_wait(a, b)          cyg_cond_wait(a)
#define rb_cond_timed_wait(cond, mutex, difftime)  \
                                    cyg_cond_timed_wait(cond, cyg_current_time()+(difftime))
#define rb_cond_destroy             cyg_cond_destroy
#define rb_thread_join(a, b)
#define rb_sem_init                 cyg_semaphore_init
#define rb_sem_post                 cyg_semaphore_post
#define rb_sem_wait                 cyg_semaphore_wait
#define rb_sem_destroy              cyg_semaphore_destroy
typedef cyg_mutex_t                 rb_mutex_t;
typedef cyg_sem_t                   rb_sem_t;
typedef cyg_cond_t                  rb_cond_t;

#elif defined(NO_THREAD) // ex: Carina Project. only support interrupt

#define rb_mutex_init(a, b)         ((void) 0)
#define rb_mutex_lock(a)            ((void) 0)
#define rb_mutex_unlock(a)          ((void) 0)
#define rb_mutex_destroy(a)         ((void) 0)
#define rb_sem_init(a, b)           ((void) 0)
#define rb_sem_post(a)              ((void) 0)
#define rb_sem_wait(a)              ((void) 0)
#define rb_sem_destroy(a)           ((void) 0)
#define rb_cond_init(a, b)          ((void) 0)
#define rb_cond_signal(a)           ((void) 0)
#define rb_cond_wait(a, b)          ((void) 0)
#define rb_cond_timed_wait(a, b, c) 1
#define rb_cond_destroy(a)          ((void) 0)
#define rb_mutex_t                  void*
#define rb_sem_t                    void*
#define rb_cond_t                   void*

#else
#define rb_mutex_init               pthread_mutex_init
#define rb_mutex_lock               pthread_mutex_lock
#define rb_mutex_unlock             pthread_mutex_unlock
#define rb_mutex_destroy            pthread_mutex_destroy
#define rb_cond_init(a, b)          pthread_cond_init(a, NULL)
#define rb_cond_signal              pthread_cond_signal
#define rb_cond_wait                pthread_cond_wait


#if defined (WINCE)

// convert FILETIME expressed in 100 nanoseconds from 1601/01/01 into TIMESPEC expressed in seconds and nanoseconds from 1970/01/01
#define TIMESPEC_TO_FILETIME_OFFSET ((27111902I64 << 32) +  3577643008I64)
#define convert_filetime2timespec(ft, ts) \
{ \
    ULARGE_INTEGER ul_integer; \
    ul_integer.LowPart = ft.dwLowDateTime; \
    ul_integer.HighPart = ft.dwHighDateTime; \
    ts.tv_sec = (time_t)((ul_integer.QuadPart - TIMESPEC_TO_FILETIME_OFFSET) / 10000000); \
    ts.tv_nsec = (long)((ul_integer.QuadPart - TIMESPEC_TO_FILETIME_OFFSET - (ts.tv_sec * 10000000I64)) * 100); \
}

#define MMP_GetSysTime(ts) \
{ \
    FILETIME ft; \
    SYSTEMTIME st; \
    \
    GetSystemTime(&st); \
    SystemTimeToFileTime(&st, &ft);  \
    convert_filetime2timespec(ft, ts); \
}
#elif defined(WIN32)
#include <sys/timeb.h>
#define MMP_GetSysTime(ts) \
{ \
    struct _timeb currSysTime; \
    \
    _ftime(&currSysTime); \
    ts.tv_sec = currSysTime.time; \
    ts.tv_nsec = currSysTime.millitm * 1000000; \
}
#else
#define MMP_GetSysTime(ts) \
{ \
    ts.tv_sec = time(NULL); \
    ts.tv_nsec = 0;\
}
#endif

static __inline int rb_cond_timed_wait(pthread_cond_t *cond, pthread_mutex_t *mutex, const int difftime)
{
    struct timespec ts;
    int ret;
    MMP_GetSysTime(ts);
    ts.tv_sec += difftime / 1000;
    ts.tv_nsec += (difftime % 1000) * 1000000;
    if (ts.tv_nsec >= 1000000000)
    {
        ts.tv_nsec -= 1000000000;
        ts.tv_sec++;
    }
    ret = pthread_cond_timedwait(cond, mutex, &ts);
    return !ret;
}

#define rb_cond_destroy             pthread_cond_destroy
#define rb_thread_join              pthread_join
#define rb_sem_init(a, b)           sem_init(a, 0, b)
#define rb_sem_post                 sem_post
#define rb_sem_wait                 sem_wait
#define rb_sem_destroy              sem_destroy
typedef pthread_mutex_t             rb_mutex_t;
typedef sem_t                       rb_sem_t;
typedef pthread_cond_t              rb_cond_t;
#endif

#endif // HCOMMON_H
