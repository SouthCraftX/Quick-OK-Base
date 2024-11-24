#pragma once

#include "../thread/thread.h"

#define QO_THREAD_POOL_FORCE_EXIT       (1)
#define QO_THREAD_POOL_EXIT_NONBLOCK    (1 << 1)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_ThreadPool;
typedef struct _QO_ThreadPool QO_ThreadPool;

typedef void (*qo_task_f)(void*);

struct _QO_ThreadPoolTask
{
    qo_task_f       func;
    qo_pointer_t    arg;
    qo_stat_t *     p_ret;
};
typedef struct _QO_ThreadPoolTask QO_ThreadPoolTask;


qo_stat_t
QO_INTERFACE(qo_thread_pool_init)(
    QO_ThreadPool *  thread_pool ,
    const qo_size_t max_thread_num 
);

void
QO_INTERFACE(qo_thread_pool_destroy)(
    QO_ThreadPool *  thread_pool ,
    qo_flag32_t     mode
);

qo_stat_t
QO_INTERFACE(qo_thread_pool_add_task)(
    QO_ThreadPool *      thread_pool ,
    QO_ThreadPoolTask    task
);

void
QO_INTERFACE(qo_thread_pool_wait)(
    QO_ThreadPool *  thread_pool
);

void
QO_INTERFACE(qo_thread_pool_resume)(
    QO_ThreadPool *  thread_pool
);

void
QO_INTERFACE(qo_thread_pool_suspend)(
    QO_ThreadPool *  thread_pool
);

qo_size_t
QO_INTERFACE(qo_thread_pool_get_task_count)(
    QO_ThreadPool *  thread_pool
);

qo_size_t
QO_INTERFACE(qo_thread_pool_get_working_thread_count)(
    QO_ThreadPool *  thread_pool
);

qo_size_t
QO_INTERFACE(qo_thread_pool_get_idle_thread_count)(
    QO_ThreadPool *  thread_pool
);

qo_size_t
QO_INTERFACE(qo_thread_pool_get_max_thread_count)(
    QO_ThreadPool *  thread_pool
);

qo_stat_t
QO_INTERFACE(qo_thread_pool_adjust_max_thread_num)(
    QO_ThreadPool *  thread_pool ,
    qo_size_t       max_thread_num ,
    qo_flag32_t     mode
);

qo_stat_t
QO_INTERFACE(qo_thread_pool_adjust_priority)(
    QO_ThreadPool *  thread_pool ,
    qo_priority_t   priority ,
    qo_size_t       to_adjust_thread_count
);

#if defined(__cplusplus)
}
#endif // __cplusplus