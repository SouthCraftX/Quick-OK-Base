//#include "../thread.h"
#include <errno.h>
#include <unistd.h>
#include <pthread.h> 
#include <time.h>

struct _XOceanThread
{
    pthread_t thread_handle;
};

XOCEAN_FORCE_INLINE
xocean_stat_t
__xocean_thread_creating_error()
{
    switch (errno)
    {
        case ENOMEM:    return XOCEAN_OUT_OF_MEMORY;
        case EAGAIN:    return XOCEAN_NO_RESOURCE;
        case EPERM:     return XOCEAN_PERMISSION_DENIED;
        case EINVAL:    return XOCEAN_INVALID_ARG;
    }
}

XOCEAN_FORCE_INLINE
void
__xocean_thread_full_sleep(
    struct timespec * ts
){
    while ((nanosleep(&ts , &ts) == -1) && (errno == EINTR));
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_init)(
    XOceanThread *          thread ,
    const xocean_pointer_t  func ,
    const xocean_pointer_t  arg ,
    const xocean_size_t     stack_size
){
    pthread_attr_t attr;
    int attr_init_ret = pthread_attr_init(&attr);

#   if !XOCEAN_PLATFORM(LINUX) // Linux guarantee that all init will succeed
    if (attr_init_ret)
        return XOCEAN_THREAD_CREATE_FAILED;
#   endif

    // When stack_size is 0, then pthread_attr_setstacksize() won't be called
    if(stack_size && pthread_attr_setstacksize(&attr, stack_size))
        return XOCEAN_INVALID_ARG; 
        // stack_size too small or not multiple of system page size

    if(pthread_create(&thread->thread_handle , &attr , 
       (void *(*)(void *))func, arg))
        return __xocean_thread_creating_error(); 

    pthread_attr_destroy(&attr);
}

void
XOCEAN_IMPL(xocean_thread_exit)(
    xocean_stat_t exit_code
){
    pthread_exit((void*)exit_code); 
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_join)(
    XOceanThread * thread 
){
    pthread_join(thread->thread_handle, NULL);
}

XOceanThread
XOCEAN_IMPL(xocean_thread_self)()
{
    return (XOceanThread){ pthread_self() };
}

void
XOCEAN_IMPL(xocean_thread_sleep_milliseconds)(
    const xocean_size_t milliseconds
){
    struct timespec ts = {
        .tv_sec  = milliseconds / 1000 ,
        .tv_nsec = milliseconds % 1000 * 1000000
    };
    __xocean_thread_full_sleep(&ts);
}

void
XOCEAN_IMPL(xocean_thread_sleep_microseconds)(
    const xocean_size_t microseconds
){
    struct timespec ts = {
        .tv_sec  = microseconds / 1000000 ,
        .tv_nsec = microseconds % 1000000 * 1000
    };
    __xocean_thread_full_sleep(&ts);
}


void
XOCEAN_IMPL(_xocean_thread_sleep_nanoseconds)(
    const xocean_size_t nanoseconds
){
    struct timespec ts = { 
        .tv_sec  = nanoseconds / 1000000000 ,
        .tv_nsec = nanoseconds % 1000000000 ,
    };
    __xocean_thread_full_sleep(&ts);
}

void
XOCEAN_IMPL(xocean_thread_yield)()
{
    pthread_yield();
}

XOCEAN_FORCE_INLINE
bool
XOCEAN_IMPL(xocean_thread_is_equal)(
    const XOceanThread x ,
    const XOceanThread y
){
    return x.thread_handle == y.thread_handle;
}
