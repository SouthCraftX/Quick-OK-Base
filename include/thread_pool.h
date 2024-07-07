#pragma once

#include "../thread/thread.h"

#define XOC_THREAD_POOL_FORCE_EXIT       (1)
#define XOC_THREAD_POOL_EXIT_NONBLOCK    (1 << 1)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_ThreadPool;
typedef struct _XOC_ThreadPool XOC_ThreadPool;

typedef void (*xoc_task_f)(void*);

struct _XOC_ThreadPoolTask
{
    xoc_task_f       func;
    xoc_pointer_t    arg;
    xoc_stat_t *     p_ret;
};
typedef struct _XOC_ThreadPoolTask XOC_ThreadPoolTask;


xoc_stat_t
XOC_INTERFACE(xoc_thread_pool_init)(
    XOC_ThreadPool *  thread_pool ,
    const xoc_size_t max_thread_num 
);

void
XOC_INTERFACE(xoc_thread_pool_destroy)(
    XOC_ThreadPool *  thread_pool ,
    xoc_flag32_t     mode
);

xoc_stat_t
XOC_INTERFACE(xoc_thread_pool_add_task)(
    XOC_ThreadPool *      thread_pool ,
    XOC_ThreadPoolTask    task
);

void
XOC_INTERFACE(xoc_thread_pool_wait)(
    XOC_ThreadPool *  thread_pool
);

void
XOC_INTERFACE(xoc_thread_pool_resume)(
    XOC_ThreadPool *  thread_pool
);

void
XOC_INTERFACE(xoc_thread_pool_suspend)(
    XOC_ThreadPool *  thread_pool
);

xoc_size_t
XOC_INTERFACE(xoc_thread_pool_get_task_count)(
    XOC_ThreadPool *  thread_pool
);

xoc_size_t
XOC_INTERFACE(xoc_thread_pool_get_working_thread_count)(
    XOC_ThreadPool *  thread_pool
);

xoc_size_t
XOC_INTERFACE(xoc_thread_pool_get_idle_thread_count)(
    XOC_ThreadPool *  thread_pool
);

xoc_size_t
XOC_INTERFACE(xoc_thread_pool_get_max_thread_count)(
    XOC_ThreadPool *  thread_pool
);

xoc_stat_t
XOC_INTERFACE(xoc_thread_pool_adjust_max_thread_num)(
    XOC_ThreadPool *  thread_pool ,
    xoc_size_t       max_thread_num ,
    xoc_flag32_t     mode
);

xoc_stat_t
XOC_INTERFACE(xoc_thread_pool_adjust_priority)(
    XOC_ThreadPool *  thread_pool ,
    xoc_priority_t   priority ,
    xoc_size_t       to_adjust_thread_count
);

#if defined(__cplusplus)
}
#endif // __cplusplus