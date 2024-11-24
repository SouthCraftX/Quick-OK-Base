#include "thread_pool.h"
#include "../container/queue.h"
#include "../lock/condlock.h"

#define QO_THREAD_POOL_EXIT     0
#define QO_THREAD_POOL_WORKING  1

struct _XoceanThreadPool
{
    QO_CondLock  cond_lock;
    QO_Queue     task_queue;
    QO_Thread *  threads;

    qo_aflag32_t    working_flag;
    qo_asize_t      all_thread_count;
    qo_asize_t      working_thread_count;
};

QO_FORCE_INLINE QO_GLOBAL_LOCAL
void
__qo_pooled_thread_run_task(
    QO_ThreadPoolTask * task
){
    qo_stat_t ret = (*task->func)(task->arg);
    if (task->p_ret)
        *p_ret = ret;
}

QO_GLOBAL_LOCAL
qo_stat_t
__qo_pooled_thread_routine(
    QO_ThreadPool * thread_pool
){
    while(thread_pool->working_flag)
    {
        // 获取任务
        // 执行任务
        // 返回
    }
    return QO_OK;
}

qo_stat_t
QO_IMPL(qo_thread_pool_init)(
    QO_ThreadPool *  thread_pool ,
    const qo_size_t max_thread_num
){
    
    QO_Thread * threads = mi_malloc(sizeof(QO_Thread) * max_thread_num);
    
    if (QO_UNLIKELY(!threads))
        return QO_OUT_OF_MEMORY;
    
    const qo_stat_t queue_init_ret = qo_queue_init(
        &thread_pool->task_queue , 
        max_thread_num ,
        0
    );

    if (QO_UNLIKELY(queue_init_ret))
    {
        mi_free(threads);
        return queue_init_ret;
    }

    qo_condlock_init(&thread_pool->cond_lock);
    thread_pool->working_flag = QO_THREAD_POOL_WORKING;
    thread_pool->working_thread_count = 0;
    thread_pool->threads = threads;
    thread_pool->all_thread_count = max_thread_num;
    
    
}


