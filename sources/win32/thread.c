#include "include/platform_spec/win32/thread.h"

XOC_FORCE_INLINE
xoc_stat_t
__xoc_thread_creating_error()
{
    switch (GetLastError())
    {
        case ERROR_NO_ENOUGH_MEMORY:    return XOC_OUT_OF_MEMORY; 
        case ERROR_INVALID_PARAMETER:   return XOC_INVALID_ARG;
        default:                        return XOC_UNKNOWN_ERROR;
    }
}

xoc_stat_t
XOC_IMPL(xoc_thread_init)(
    XOC_Thread *          thread ,
    const xoc_pointer_t  func ,
    const xoc_pointer_t  arg ,
    const xoc_size_t     stack_size 
){
    HANDLE thread_handle;
    thread_handle =  CreateThread(NULL , stack_size , 
                                  (LPTHREAD_START_ROUTINE)func , arg , 
                                  0 , NULL);

    if(!thread_handle)
        return __xoc_thread_creating_error();
    
    thread->thread_handle = thread_handle;
    return XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_thread_get_priority)(
    XOC_Thread        thread ,
    xoc_flag32_t *   priority
){
    // @todo Support REALTIME_PRIORITY_CLASS
    switch (GetThreadPriority(thread.thread_handle))
    {
        case THREAD_PRIORITY_IDLE:
        case THREAD_PRIORITY_LOWEST:  
            *priority = XOC_THREAD_PRIORITY_LOWEST;
            return XOC_OK;

        case THREAD_PRIORITY_BELOW_NORMAL: 
            *priority = XOC_THREAD_PRIORITY_LOW;
            return XOC_OK;
        
        case THREAD_PRIORITY_NORMAL:
            *priority = XOC_THREAD_PRIORITY_NORMAL;
            return XOC_OK;

        case THREAD_PRIORITY_ABOVE_NORMAL:
            *priority = XOC_THREAD_PRIORITY_HIGH;
            return XOC_OK;

        case THREAD_PRIORITY_HIGHEST:
            *priority = XOC_THREAD_PRIORITY_HIGHEST;
            return XOC_OK;

        case THREAD_PRIORITY_TIME_CRITICAL:
        case 31:    // REALTIME_PRIORITY_CLASS
            *priority = XOC_THREAD_PRIORITY_CRAZY;
            return XOC_OK;

        default:
            return __xoc_thread_priority_error();
    }
}