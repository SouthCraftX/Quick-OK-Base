#pragma once
#define __XOC_THREAD_H__

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_Thread;
typedef struct _XOC_Thread XOC_Thread;

typedef xoc_flag8_t xoc_priority_t;

enum XOC_ThreadPriority{
    XOC_THREAD_PRIORITY_LOWEST = 0,
    XOC_THREAD_PRIORITY_LOW,
    XOC_THREAD_PRIORITY_NORMAL,
    XOC_THREAD_PRIORITY_HIGH,
    XOC_THREAD_PRIORITY_HIGHEST,
    XOC_THREAD_PRIORITY_CRAZY
};

xoc_stat_t
XOC_INTERFACE(xoc_thread_create)(
    XOC_Thread **         thread ,
    xoc_pointer_t        func , 
    xoc_pointer_t        arg ,
    xoc_size_t           stack_size
) XOC_NONNULL(1 , 2);

xoc_stat_t
XOC_INTERFACE(xoc_thread_join)(
    XOC_Thread * thread 
) XOC_NONNULL(1);

xoc_stat_t
XOC_INTERFACE(xoc_thread_multijoin)(
    XOC_Thread *  thread_array ,
    xoc_size_t   count    
);

void
XOC_INTERFACE(xoc_thread_exit)(
    xoc_stat_t exit_code
);

XOC_Thread
XOC_INTERFACE(xoc_thread_self)();

void
XOC_INTERFACE(xoc_thread_yield)();

xoc_stat_t
XOC_INTERFACE(xoc_thread_suspend)(
    XOC_Thread *  thread
);

void
XOC_INTERFACE(xoc_thread_sleep_milliseconds)(
    xoc_uint32_t milliseconds
);

void
XOC_INTERFACE(xoc_thread_sleep_microseconds)(
    const xoc_size_t microseconds
);

void
XOC_INTERFACE(xoc_thread_sleep_nanoseconds)(
    const xoc_size_t nanoseconds
);

void
XOC_INTERFACE(xoc_thread_destory)(
    XOC_Thread * thread
);

xoc_stat_t
XOC_INTERFACE(xoc_thread_kill)(

);

xoc_stat_t
XOC_INTERFACE(xoc_thread_get_exit_code)(
    XOC_Thread *  thread 
) XOC_NONNULL(1);

bool
XOC_INTERFACE(xoc_thread_is_equal)(
    const XOC_Thread *    x ,
    const XOC_Thread *    y
) XOC_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "platform_spec/win32/thread.h"
#elif XOC_PLATFORM(POSIX)
#   include "platform_spec/posix/thread.h"
#endif // XOC_PLATFORM
