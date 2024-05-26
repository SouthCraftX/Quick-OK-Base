#pragma once

#include "../thread/thread.h"

#define XOCEAN_THREAD_POOL_FORCE_EXIT       (1)
#define XOCEAN_THREAD_POOL_EXIT_NONBLOCK    (1 << 1)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanThreadPool;
typedef struct _XOceanThreadPool XOceanThreadPool;

typedef void (*xocean_task_f)(void*);

struct _XOceanThreadPoolTask
{
    xocean_task_f       func;
    xocean_pointer_t    arg;
    xocean_stat_t *     p_ret;
};
typedef struct _XOceanThreadPoolTask XOceanThreadPoolTask;


xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_pool_init)(
    XOceanThreadPool *  thread_pool ,
    const xocean_size_t max_thread_num 
);

void
XOCEAN_INTERFACE(xocean_thread_pool_destroy)(
    XOceanThreadPool *  thread_pool ,
    xocean_flag32_t     mode
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_pool_add_task)(
    XOceanThreadPool *      thread_pool ,
    XOceanThreadPoolTask    task
);

void
XOCEAN_INTERFACE(xocean_thread_pool_wait)(
    XOceanThreadPool *  thread_pool
);

void
XOCEAN_INTERFACE(xocean_thread_pool_resume)(
    XOceanThreadPool *  thread_pool
);

void
XOCEAN_INTERFACE(xocean_thread_pool_suspend)(
    XOceanThreadPool *  thread_pool
);

xocean_size_t
XOCEAN_INTERFACE(xocean_thread_pool_get_task_count)(
    XOceanThreadPool *  thread_pool
);

xocean_size_t
XOCEAN_INTERFACE(xocean_thread_pool_get_working_thread_count)(
    XOceanThreadPool *  thread_pool
);

xocean_size_t
XOCEAN_INTERFACE(xocean_thread_pool_get_idle_thread_count)(
    XOceanThreadPool *  thread_pool
);

xocean_size_t
XOCEAN_INTERFACE(xocean_thread_pool_get_max_thread_count)(
    XOceanThreadPool *  thread_pool
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_pool_adjust_max_thread_num)(
    XOceanThreadPool *  thread_pool ,
    xocean_size_t       max_thread_num ,
    xocean_flag32_t     mode
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_thread_pool_adjust_priority)(
    XOceanThreadPool *  thread_pool ,
    xocean_priority_t   priority ,
    xocean_size_t       to_adjust_thread_count
);

#if defined(__cplusplus)
}
#endif // __cplusplus