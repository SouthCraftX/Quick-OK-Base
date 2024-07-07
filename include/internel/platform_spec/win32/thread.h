#pragma once
#define __XOC_WIN32_THREAD_H__

#include "../thread.h"
#include <processthreadsapi.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_Thread
{
    HANDLE thread_handle;
};

XOC_IMPORT
xoc_stat_t
__xoc_thread_priority_error();

XOC_FORCE_INLINE 
xoc_stat_t
__xoc_thread_killing_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;
        default:                    return XOC_UNKNOWN_ERROR;
    }
}

XOC_FORCE_INLINE
xoc_stat_t
__xoc_thread_suspending_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;
        default:                    return XOC_UNKNOWN_ERROR;
    }
}


void
XOC_IMPL(xoc_thread_exit)(
    xoc_stat_t exit_code
){
    ExitThread((DWORD)exit_code);
}

void
XOC_IMPL(xoc_thread_destory)(
    XOC_Thread * thread
){
    CloseHandle(thread->thread_handle);
}

xoc_stat_t
XOC_IMPL(xoc_thread_set_priority)(
    XOC_Thread                thread ,
    enum XOC_ThreadPriority   priority
){
    XOC_GLOBAL_LOCAL
    const xoc_int8_t priority_level[] = {
        THREAD_PRIORITY_LOWEST ,
        THREAD_PRIORITY_BELOW_NORMAL ,
        THREAD_PRIORITY_NORMAL ,
        THREAD_PRIORITY_ABOVE_NORMAL ,
        THREAD_PRIORITY_HIGHEST ,
        THREAD_PRIORITY_TIME_CRITICAL   
    };
    return SetThreadPriority(thread.thread_handle , priority_level[priority]) ?
           XOC_OK : __xoc_thread_priority_error();
}


XOC_FORCE_INLINE
bool
XOC_IMPL(xoc_thread_is_alive)(
    XOC_Thread * thread
){
    return (WaitForSingleObject(thread->thread_handle , 0) == WAIT_TIMEOUT); 
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_get_exit_code)(
    XOC_Thread * thread 
){
    DWORD exit_code;
    return GetExitCodeThread(thread->thread_handle , (LPDWORD)&exit_code) ?
           exit_code : -1; 
}

XOC_FORCE_INLINE
XOC_Thread
XOC_IMPL(xoc_thread_self)()
{
    return (XOC_Thread){ GetCurrentThread() };
}


xoc_stat_t
XOC_IMPL(xoc_thread_kill)(
    XOC_Thread * thread 
){
    return TerminateThread(thread->thread_handle , -1) ? XOC_OK :
           __xoc_thread_killing_error();
}

xoc_stat_t
XOC_IMPL(xoc_thread_suspend)(
    XOC_Thread * thread
){
    return SuspendThread(thread->thread_handle) == -1 ? 
           __xoc_thread_suspending_error() : XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_thread_resume)(
    XOC_Thread * thread
){
    switch (ResumeThread(thread->thread_handle))
    {
        case 0:     return XOC_THREAD_NOT_SUSPENDED;
        case 1:     return XOC_OK;
        default:    return XOC_THREAD_RESUME_FAILED;
    }
}

void
XOC_IMPL(xoc_thread_sleep_milliseconds)(
    const xoc_uint32_t milliseconds
){
    Sleep(milliseconds);
}

void
XOC_IMPL(xoc_thread_sleep_microseconds)(
    const xoc_size_t microseconds
){
    HANDLE timer = CreateWaitableTimer(NULL , TRUE , NULL);
#if XOC_SYSTEM_BIT(64)
    LARGE_INTEGER ft = { .QuadPart = -(10 * microseconds) }; 
#else
    LARGE_INTEGER ft = { .LowPart = -(10 * microseconds) , .HighPart = -1 };
#endif
    SetWaitableTimer(timer , &ft , 0 , NULL , FALSE , 0);
    WaitForSingleObject(timer , INFINITE);
    CloseHandle(timer);
}



xoc_stat_t
XOC_IMPL(xoc_thread_join)(
    XOC_Thread  thread
){
    return WaitForSingleObject(thread.thread_handle , INFINITE) ?
           XOC_OK : xoc_thread_handle_join_error();
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_thread_yield)
{
    SwitchToThread();
}

XOC_FORCE_INLINE
bool
XOC_IMPL(xoc_thread_is_equal)(
    XOC_Thread  x ,
    XOC_Thread  y
){
    return x.thread_handle == y.thread_handle;
}

#if defined(__cplusplus)
}
#endif // __cplusplus