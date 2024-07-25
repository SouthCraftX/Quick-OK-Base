#include "thread_pool.h"
#include "../container/queue.h"
#include "../lock/condlock.h"

#define XOC_THREAD_POOL_EXIT     0
#define XOC_THREAD_POOL_WORKING  1

struct _XoceanThreadPool
{
    XOC_CondLock  cond_lock;
    XOC_Queue     task_queue;
    XOC_Thread *  threads;

    xoc_aflag32_t    working_flag;
    xoc_asize_t      all_thread_count;
    xoc_asize_t      working_thread_count;
};

XOC_FORCE_INLINE XOC_GLOBAL_LOCAL
void
__xoc_pooled_thread_run_task(
    XOC_ThreadPoolTask * task
){
    xoc_stat_t ret = (*task->func)(task->arg);
    if (task->p_ret)
        *p_ret = ret;
}

XOC_GLOBAL_LOCAL
xoc_stat_t
__xoc_pooled_thread_routine(
    XOC_ThreadPool * thread_pool
){
    while(thread_pool->working_flag)
    {
        // 获取任务
        // 执行任务
        // 返回
    }
    return XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_thread_pool_init)(
    XOC_ThreadPool *  thread_pool ,
    const xoc_size_t max_thread_num
){
    
    XOC_Thread * threads = mi_malloc(sizeof(XOC_Thread) * max_thread_num);
    
    if (XOC_UNLIKELY(!threads))
        return XOC_OUT_OF_MEMORY;
    
    const xoc_stat_t queue_init_ret = xoc_queue_init(
        &thread_pool->task_queue , 
        max_thread_num ,
        0
    );

    if (XOC_UNLIKELY(queue_init_ret))
    {
        mi_free(threads);
        return queue_init_ret;
    }

    xoc_condlock_init(&thread_pool->cond_lock);
    thread_pool->working_flag = XOC_THREAD_POOL_WORKING;
    thread_pool->working_thread_count = 0;
    thread_pool->threads = threads;
    thread_pool->all_thread_count = max_thread_num;
    
    
}


