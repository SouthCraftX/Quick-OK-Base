//#include "../thread.h"

#include "base.h"

#include <errno.h>
#include <unistd.h>
#include <pthread.h> 
#include <time.h>


QO_PURE
qo_stat_t
__qo_thread_creating_error()
{
    switch (errno)
    {
        case ENOMEM:    return QO_OUT_OF_MEMORY;
        case EAGAIN:    return QO_NO_RESOURCE;
        case EPERM:     return QO_PERMISSION_DENIED;
        case EINVAL:    return QO_INVALID_ARG;
        default:        return QO_UNKNOWN_ERROR;
    }
}

QO_PURE
qo_stat_t
__qo_thread_join_error()
{
    switch (errno)
    {
        case EDEADLOCK:     return QO_ACCESS_VIOLATED;
        case EINVAL:        return QO_INVALID_ARG;
        case ESRCH:         return QO_INVALID_HANDLE;
    }
}

QO_FORCE_INLINE
void
__qo_thread_full_sleep(
    struct timespec * ts
){
    while ((nanosleep(&ts , &ts) == -1) && (errno == EINTR));
}

qo_stat_t
QO_IMPL(qo_thread_init)(
    QO_Thread **   thread ,
    qo_pointer_t   function ,
    qo_pointer_t   arguments ,
    qo_size_t      stack_size
){
    pthread_attr_t attr , * p_attr = NULL;
    if(stack_size)
    {
        int attr_init_ret = pthread_attr_init(&attr);
#if !QO_PLATFORM(LINUX) // Linux guarantee that all init will succeed
        if (attr_init_ret)
            return QO_OUT_OF_MEMORY; // ENOMEM is the only possible error
#endif
        if (pthread_attr_setstacksize(&attr, stack_size))
            return QO_INVALID_ARG; 
            // stack_size too small or not multiple of system page size
        p_attr = &attr;
    }

    if (pthread_create((pthread_t *)thread , p_attr , 
       (void *(*)(void *))function, arguments))
        return __qo_thread_creating_error(); 

    pthread_attr_destroy(p_attr);
}

void
QO_IMPL(qo_thread_exit)(
    qo_stat_t exit_code
){
    pthread_exit((void*)exit_code); 
}

qo_stat_t
QO_IMPL(qo_thread_join)(
    QO_Thread * thread 
){
    return  pthread_join((pthread_t)thread , NULL) ?
            __qo_thread_join_error() : QO_OK;
}

qo_stat_t
QO_IMPL(qo_thread_mutiljoin)(
    QO_Thread **   thread_array ,
    qo_size_t      count
){
    qo_stat_t ret = QO_OK;
    for (QO_Thread** p_thread = thread_array; 
         (thread != thread_array + count) && !ret ; p_thread ++)
    {
        ret = QO_IMPL(qo_thread_join)(*p_thread);
    }
    return ret;
}

QO_FORCE_INLINE
QO_Thread *
QO_IMPL(qo_thread_self)()
{
    return  (QO_Thread *)pthread_self();
}

void
QO_IMPL(qo_thread_sleep_milliseconds)(
    const qo_size_t milliseconds
){
    struct timespec ts = {
        .tv_sec  = milliseconds / 1000 ,
        .tv_nsec = milliseconds % 1000 * 1000000
    };
    __qo_thread_full_sleep(&ts);
}

void
QO_IMPL(qo_thread_sleep_microseconds)(
    const qo_size_t microseconds
){
    struct timespec ts = {
        .tv_sec  = microseconds / 1000000 ,
        .tv_nsec = microseconds % 1000000 * 1000
    };
    __qo_thread_full_sleep(&ts);
}


void
QO_IMPL(_qo_thread_sleep_nanoseconds)(
    const qo_size_t nanoseconds
){
    struct timespec ts = { 
        .tv_sec  = nanoseconds / 1000000000 ,
        .tv_nsec = nanoseconds % 1000000000 ,
    };
    __qo_thread_full_sleep(&ts);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_thread_yield)()
{
    // pthread_yield() is deprecated in POSIX.1-2008
    sched_yield();
}

QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_thread_is_equal)(
    const QO_Thread *    x ,
    const QO_Thread *    y
){
    return pthread_equal((pthread_t)x , (pthread_t)y);
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_terminate)(
    QO_Thread * thread
){
    // ESRCH is the only possible error
    return pthread_cancel((pthread_t)thread) ? QO_INVALID_HANDLE : QO_OK; 
}