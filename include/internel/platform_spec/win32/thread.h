#pragma once
#define __XOCEAN_WIN32_THREAD_H__

#include "../thread.h"
#include <processthreadsapi.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanThread
{
    HANDLE thread_handle;
};

XOCEAN_IMPORT
xocean_stat_t
__xocean_thread_priority_error();

XOCEAN_FORCE_INLINE 
xocean_stat_t
__xocean_thread_killing_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOCEAN_INVALID_HANDLE;
        default:                    return XOCEAN_UNKNOWN_ERROR;
    }
}

XOCEAN_FORCE_INLINE
xocean_stat_t
__xocean_thread_suspending_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOCEAN_INVALID_HANDLE;
        default:                    return XOCEAN_UNKNOWN_ERROR;
    }
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

xocean_stat_t
XOCEAN_IMPL(xocean_thread_set_priority)(
    XOceanThread                thread ,
    enum XOceanThreadPriority   priority
){
    XOCEAN_GLOBAL_LOCAL
    const xocean_int8_t priority_level[] = {
        THREAD_PRIORITY_LOWEST ,
        THREAD_PRIORITY_BELOW_NORMAL ,
        THREAD_PRIORITY_NORMAL ,
        THREAD_PRIORITY_ABOVE_NORMAL ,
        THREAD_PRIORITY_HIGHEST ,
        THREAD_PRIORITY_TIME_CRITICAL   
    };
    return SetThreadPriority(thread.thread_handle , priority_level[priority]) ?
           XOCEAN_OK : __xocean_thread_priority_error();
}


XOCEAN_FORCE_INLINE
bool
XOCEAN_IMPL(xocean_thread_is_alive)(
    XOceanThread * thread
){
    return (WaitForSingleObject(thread->thread_handle , 0) == WAIT_TIMEOUT); 
}

XOCEAN_FORCE_INLINE
xocean_stat_t
XOCEAN_IMPL(xocean_thread_get_exit_code)(
    XOceanThread * thread 
){
    DWORD exit_code;
    return GetExitCodeThread(thread->thread_handle , (LPDWORD)&exit_code) ?
           exit_code : -1; 
}

XOCEAN_FORCE_INLINE
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
           __xocean_thread_killing_error();
}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_suspend)(
    XOceanThread * thread
){
    return SuspendThread(thread->thread_handle) == -1 ? 
           __xocean_thread_suspending_error() : XOCEAN_OK;
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
    XOceanThread  thread
){
    return WaitForSingleObject(thread.thread_handle , INFINITE) ?
           XOCEAN_OK : xocean_thread_handle_join_error();
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_thread_yield)
{
    SwitchToThread();
}

XOCEAN_FORCE_INLINE
bool
XOCEAN_IMPL(xocean_thread_is_equal)(
    XOceanThread  x ,
    XOceanThread  y
){
    return x.thread_handle == y.thread_handle;
}

#if defined(__cplusplus)
}
#endif // __cplusplus