#pragma once

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanThread;
typedef struct _XOceanThread XOceanThread;

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_create)(
    XOceanThread*       thread ,
    const xocean_pointer_t    func , 
    const xocean_pointer_t    arg ,
    const xocean_size_t       stack_size
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_join)(
    XOceanThread * thread 
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
    XOceanThread * thread
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
    XOceanThread * thread 
);

#if defined(__cplusplus)
}
#endif // __cplusplus