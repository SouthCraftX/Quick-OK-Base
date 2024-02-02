#include "thread.h"
#include <processthreadsapi.h>
#include <synchapi.h>

struct _XOceanThread
{
    HANDLE thread_handle;
};

XOCEAN_FORCE_INLINE
xocean_stat_t
xocean_thread_handle_init_error()
{
    switch (GetLastError())
    {
        case ERROR_NO_ENOUGH_MEMORY:    return XOCEAN_OUT_OF_MEMORY; 
        case ERROR_INVALID_PARAMETER:   return XOCEAN_INVALID_ARG;
        default:                        return XOCEAN_UNKNOWN;
    }
}

XOCEAN_FORCE_INLINE 
xocean_stat_t
xocean_thread_handle_kill_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOCEAN_INVALID_HANDLE;
        default:                    return XOCEAN_UNKNOWN;
    }
}

XOCEAN_FORCE_INLINE
xocean_stat_t
xocean_thread_handle_suspend_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOCEAN_INVALID_HANDLE;
        default:                    return XOCEAN_UNKNOWN;
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
        return xocean_thread_handle_init_error();
    
    thread->thread_handle = thread_handle;
    return XOCEAN_OK;
}

void
XOCEAN_IMPL(xocean_thread_exit)(
    xocean_stat_t exit_code
){
    ExitThread((DWORD)exit_code);
}

void
XOCEAN_IMPL(xocean_thread_destory)(
    XOceanThread * thread
){
    CloseHandle(thread->thread_handle);
}

bool
XOCEAN_IMPL(xocean_thread_is_alive)(
    XOceanThread * thread
){
    return (WaitForSingleObject(thread->thread_handle , 0) == WAIT_TIMEOUT); 
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_get_exit_code)(
    XOceanThread * thread 
){
    DWORD exit_code;
    return GetExitCodeThread(thread->thread_handle , (LPDWORD)&exit_code) ?
           exit_code : -1; 
}

XOceanThread
XOCEAN_IMPL(xocean_thread_self)()
{
    return (XOceanThread){ GetCurrentThread() };
}



xocean_stat_t
XOCEAN_IMPL(xocean_thread_kill)(
    XOceanThread * thread 
){
    return TerminateThread(thread->thread_handle , -1) ? XOCEAN_OK :
           xocean_thread_handle_kill_error();
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_suspend)(
    XOceanThread * thread
){
    return SuspendThread(thread->thread_handle) == -1 ? 
           xocean_thread_handle_suspend_error() : XOCEAN_OK;
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_resume)(
    XOceanThread * thread
){
    switch (ResumeThread(thread->thread_handle))
    {
        case 0:     return XOCEAN_THREAD_NOT_SUSPENDED;
        case 1:     return XOCEAN_OK;
        default:    return XOCEAN_THREAD_RESUME_FAILED;
    }
}

void
XOCEAN_IMPL(xocean_thread_sleep_milliseconds)(
    const xocean_uint32_t milliseconds
){
    Sleep(milliseconds);
}

void
XOCEAN_IMPL(xocean_thread_sleep_microseconds)(
    const xocean_size_t microseconds
){
    HANDLE timer = CreateWaitableTimer(NULL , TRUE , NULL);
#if XOCEAN_SYSTEM_BIT(64)
    LARGE_INTEGER ft = { .QuadPart = -(10 * microseconds) }; 
#else
    LARGE_INTEGER ft = { .LowPart = -(10 * microseconds) , .HighPart = -1 };
#endif
    SetWaitableTimer(timer , &ft , 0 , NULL , FALSE , 0);
    WaitForSingleObject(timer , INFINITE);
    CloseHandle(timer);
}



xocean_stat_t
XOCEAN_IMPL(xocean_thread_join)(
    XOceanThread * thread
){
    return WaitForSingleObject(thread->thread_handle , INFINITE) ?
           XOCEAN_OK : xocean_thread_handle_join_error();
}



void
XOCEAN_IMPL(xocean_thread_yield)
{
    SwitchToThread();
}

