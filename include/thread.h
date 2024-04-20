#pragma once
#define __XOCEAN_THREAD_H__

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanThread;
typedef struct _XOceanThread XOceanThread;

typedef xocean_flag8_t xocean_priority_t;

enum XOceanThreadPriority{
    XOCEAN_THREAD_PRIORITY_LOWEST = 0,
    XOCEAN_THREAD_PRIORITY_LOW,
    XOCEAN_THREAD_PRIORITY_NORMAL,
    XOCEAN_THREAD_PRIORITY_HIGH,
    XOCEAN_THREAD_PRIORITY_HIGHEST,
    XOCEAN_THREAD_PRIORITY_CRAZY
};

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_create)(
    XOceanThread*       thread ,
    const xocean_pointer_t    func , 
    const xocean_pointer_t    arg ,
    const xocean_size_t       stack_size
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_join)(
    XOceanThread   thread 
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_multijoin)(
    XOceanThread *  thread_array ,
    xocean_size_t   count    
);

void
XOCEAN_INTERFACE(xocean_thread_exit)(
    xocean_stat_t exit_code
);

XOceanThread
XOCEAN_INTERFACE(xocean_thread_self)();

void
XOCEAN_INTERFACE(xocean_thread_yield)();

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_suspend)(
    XOceanThread   thread
);

void
XOCEAN_INTERFACE(xocean_thread_sleep_milliseconds)(
    const xocean_uint32_t milliseconds
);

void
XOCEAN_INTERFACE(xocean_thread_sleep_microseconds)(
    const xocean_size_t microseconds
);

void
XOCEAN_INTERFACE(xocean_thread_sleep_nanoseconds)(
    const xocean_size_t nanoseconds
);

void
XOCEAN_INTERFACE(xocean_thread_destory)(
    XOceanThread * thread
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_kill)(

);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_get_exit_code)(
    XOceanThread  thread 
);

bool
XOCEAN_INTERFACE(xocean_thread_is_equal)(
    const XOceanThread    x ,
    const XOceanThread    y
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOCEAN_PLATFORM(WINDOWS)
#   include "platform_spec/win32/thread.h"
#elif XOCEAN_PLATFORM(POSIX)
#   include "platform_spec/posix/thread.h"
#endif // XOCEAN_PLATFORM
