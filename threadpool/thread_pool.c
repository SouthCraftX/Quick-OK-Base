#include "thread_pool.h"
#include "../container/queue.h"
#include "../lock/condlock.h"

#define XOCEAN_THREAD_POOL_EXIT     0
#define XOCEAN_THREAD_POOL_WORKING  1

struct _XoceanThreadPool
{
    XOceanCondLock  cond_lock;
    XOceanQueue     task_queue;
    XOceanThread *  threads;

    xocean_aflag32_t    working_flag;
    xocean_asize_t      all_thread_count;
    xocean_asize_t      working_thread_count;
};

XOCEAN_FORCE_INLINE XOCEAN_GLOBAL_LOCAL
void
__xocean_pooled_thread_run_task(
    XOceanThreadPoolTask * task
){
    xocean_stat_t ret = (*task->func)(task->arg);
    if(task->p_ret)
        *p_ret = ret;
}

XOCEAN_GLOBAL_LOCAL
xocean_stat_t
__xocean_pooled_thread_routine(
    XOceanThreadPool * thread_pool
){
    while(thread_pool->working_flag)
    {
        // 获取任务
        // 执行任务
        // 返回
    }
    return XOCEAN_OK;
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_pool_init)(
    XOceanThreadPool *  thread_pool ,
    const xocean_size_t max_thread_num
){
    
    XOceanThread * threads = mi_malloc(sizeof(XOceanThread) * max_thread_num);
    
    if(XOCEAN_UNLIKELY(!threads))
        return XOCEAN_OUT_OF_MEMORY;
    
    const xocean_stat_t queue_init_ret = xocean_queue_init(
        &thread_pool->task_queue , 
        max_thread_num ,
        0
    );

    if(XOCEAN_UNLIKELY(queue_init_ret))
    {
        mi_free(threads);
        return queue_init_ret;
    }

    xocean_condlock_init(&thread_pool->cond_lock);
    thread_pool->working_flag = XOCEAN_THREAD_POOL_WORKING;
    thread_pool->working_thread_count = 0;
    thread_pool->threads = threads;
    thread_pool->all_thread_count = max_thread_num;
    
    
}


