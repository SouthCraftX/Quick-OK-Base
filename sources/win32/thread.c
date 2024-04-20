#include "include/platform_spec/win32/thread.h"

XOCEAN_FORCE_INLINE
xocean_stat_t
__xocean_thread_creating_error()
{
    switch (GetLastError())
    {
        case ERROR_NO_ENOUGH_MEMORY:    return XOCEAN_OUT_OF_MEMORY; 
        case ERROR_INVALID_PARAMETER:   return XOCEAN_INVALID_ARG;
        default:                        return XOCEAN_UNKNOWN_ERROR;
    }
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_init)(
    XOceanThread *          thread ,
    const xocean_pointer_t  func ,
    const xocean_pointer_t  arg ,
    const xocean_size_t     stack_size 
){
    HANDLE thread_handle;
    thread_handle =  CreateThread(NULL , stack_size , 
                                  (LPTHREAD_START_ROUTINE)func , arg , 
                                  0 , NULL);

    if(!thread_handle)
        return __xocean_thread_creating_error();
    
    thread->thread_handle = thread_handle;
    return XOCEAN_OK;
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_get_priority)(
    XOceanThread        thread ,
    xocean_flag32_t *   priority
){
    // @todo Support REALTIME_PRIORITY_CLASS
    switch (GetThreadPriority(thread.thread_handle))
    {
        case THREAD_PRIORITY_IDLE:
        case THREAD_PRIORITY_LOWEST:  
            *priority = XOCEAN_THREAD_PRIORITY_LOWEST;
            return XOCEAN_OK;

        case THREAD_PRIORITY_BELOW_NORMAL: 
            *priority = XOCEAN_THREAD_PRIORITY_LOW;
            return XOCEAN_OK;
        
        case THREAD_PRIORITY_NORMAL:
            *priority = XOCEAN_THREAD_PRIORITY_NORMAL;
            return XOCEAN_OK;

        case THREAD_PRIORITY_ABOVE_NORMAL:
            *priority = XOCEAN_THREAD_PRIORITY_HIGH;
            return XOCEAN_OK;

        case THREAD_PRIORITY_HIGHEST:
            *priority = XOCEAN_THREAD_PRIORITY_HIGHEST;
            return XOCEAN_OK;

        case THREAD_PRIORITY_TIME_CRITICAL:
        case 31:    // REALTIME_PRIORITY_CLASS
            *priority = XOCEAN_THREAD_PRIORITY_CRAZY;
            return XOCEAN_OK;

        default:
            return __xocean_thread_priority_error();
    }
}