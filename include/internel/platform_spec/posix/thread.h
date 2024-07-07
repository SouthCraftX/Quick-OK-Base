//#include "../thread.h"
#include <errno.h>
#include <unistd.h>
#include <pthread.h> 
#include <time.h>


XOC_FORCE_INLINE
xoc_stat_t
__xoc_thread_creating_error()
{
    switch (errno)
    {
        case ENOMEM:    return XOC_OUT_OF_MEMORY;
        case EAGAIN:    return XOC_NO_RESOURCE;
        case EPERM:     return XOC_PERMISSION_DENIED;
        case EINVAL:    return XOC_INVALID_ARG;
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
    xoc_pointer_t  func ,
    xoc_pointer_t  arg ,
    xoc_size_t     stack_size
){
    pthread_attr_t attr;
    int attr_init_ret = pthread_attr_init(&attr);

#   if !XOC_PLATFORM(LINUX) // Linux guarantee that all init will succeed
    if (attr_init_ret)
        return XOC_THREAD_CREATE_FAILED;
#   endif

    // When stack_size is 0, then pthread_attr_setstacksize() won't be called
    if(stack_size && pthread_attr_setstacksize(&attr, stack_size))
        return XOC_INVALID_ARG; 
        // stack_size too small or not multiple of system page size

    if(pthread_create((thread_t *)thread , &attr , 
       (void *(*)(void *))func, arg))
        return __xoc_thread_creating_error(); 

    pthread_attr_destroy(&attr);
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
    pthread_join((pthread_t)thread , NULL);
}

XOC_Thread *
XOC_IMPL(xoc_thread_self)()
{
    return (XOC_Thread *)pthread_self();
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

void
XOC_IMPL(xoc_thread_yield)()
{
    pthread_yield();
}

XOC_FORCE_INLINE
bool
XOC_IMPL(xoc_thread_is_equal)(
    const XOC_Thread *    x ,
    const XOC_Thread *    y
){
    return pthread_equal((pthread_t)x , (pthread_t)y);
}
