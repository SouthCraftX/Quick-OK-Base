//#include "../thread.h"

#include "base.h"

#include <errno.h>
#include <unistd.h>
#include <pthread.h> 
#include <time.h>


XOC_PURE
xoc_stat_t
__xoc_thread_creating_error()
{
    switch (errno)
    {
        case ENOMEM:    return XOC_OUT_OF_MEMORY;
        case EAGAIN:    return XOC_NO_RESOURCE;
        case EPERM:     return XOC_PERMISSION_DENIED;
        case EINVAL:    return XOC_INVALID_ARG;
        default:        return XOC_UNKNOWN_ERROR;
    }
}

XOC_PURE
xoc_stat_t
__xoc_thread_join_error()
{
    switch (errno)
    {
        case EDEADLOCK:     return XOC_ACCESS_VIOLATED;
        case EINVAL:        return XOC_INVALID_ARG;
        case ESRCH:         return XOC_INVALID_HANDLE;
    }
}

XOC_FORCE_INLINE
void
__xoc_thread_full_sleep(
    struct timespec * ts
){
    while ((nanosleep(&ts , &ts) == -1) && (errno == EINTR));
}

xoc_stat_t
XOC_IMPL(xoc_thread_init)(
    XOC_Thread **   thread ,
    xoc_pointer_t   function ,
    xoc_pointer_t   arguments ,
    xoc_size_t      stack_size
){
    pthread_attr_t attr , * p_attr = NULL;
    if(stack_size)
    {
        int attr_init_ret = pthread_attr_init(&attr);
#if !XOC_PLATFORM(LINUX) // Linux guarantee that all init will succeed
        if (attr_init_ret)
            return XOC_OUT_OF_MEMORY; // ENOMEM is the only possible error
#endif
        if (pthread_attr_setstacksize(&attr, stack_size))
            return XOC_INVALID_ARG; 
            // stack_size too small or not multiple of system page size
        p_attr = &attr;
    }

    if (pthread_create((pthread_t *)thread , p_attr , 
       (void *(*)(void *))function, arguments))
        return __xoc_thread_creating_error(); 

    pthread_attr_destroy(p_attr);
}

void
XOC_IMPL(xoc_thread_exit)(
    xoc_stat_t exit_code
){
    pthread_exit((void*)exit_code); 
}

xoc_stat_t
XOC_IMPL(xoc_thread_join)(
    XOC_Thread * thread 
){
    return  pthread_join((pthread_t)thread , NULL) ?
            __xoc_thread_join_error() : XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_thread_mutiljoin)(
    XOC_Thread **   thread_array ,
    xoc_size_t      count
){
    xoc_stat_t ret = XOC_OK;
    for (XOC_Thread** p_thread = thread_array; 
         (thread != thread_array + count) && !ret ; p_thread ++)
    {
        ret = XOC_IMPL(xoc_thread_join)(*p_thread);
    }
    return ret;
}

XOC_FORCE_INLINE
XOC_Thread *
XOC_IMPL(xoc_thread_self)()
{
    return  (XOC_Thread *)pthread_self();
}

void
XOC_IMPL(xoc_thread_sleep_milliseconds)(
    const xoc_size_t milliseconds
){
    struct timespec ts = {
        .tv_sec  = milliseconds / 1000 ,
        .tv_nsec = milliseconds % 1000 * 1000000
    };
    __xoc_thread_full_sleep(&ts);
}

void
XOC_IMPL(xoc_thread_sleep_microseconds)(
    const xoc_size_t microseconds
){
    struct timespec ts = {
        .tv_sec  = microseconds / 1000000 ,
        .tv_nsec = microseconds % 1000000 * 1000
    };
    __xoc_thread_full_sleep(&ts);
}


void
XOC_IMPL(_xoc_thread_sleep_nanoseconds)(
    const xoc_size_t nanoseconds
){
    struct timespec ts = { 
        .tv_sec  = nanoseconds / 1000000000 ,
        .tv_nsec = nanoseconds % 1000000000 ,
    };
    __xoc_thread_full_sleep(&ts);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_thread_yield)()
{
    // pthread_yield() is deprecated in POSIX.1-2008
    sched_yield();
}

XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_thread_is_equal)(
    const XOC_Thread *    x ,
    const XOC_Thread *    y
){
    return pthread_equal((pthread_t)x , (pthread_t)y);
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_terminate)(
    XOC_Thread * thread
){
    // ESRCH is the only possible error
    return pthread_cancel((pthread_t)thread) ? XOC_INVALID_HANDLE : XOC_OK; 
}