/*******************************************************************************
 * @headerfile  include/internal/win32/thread.h
 * @addtogroup  Headers under the MIT License
 * @note        This header is part of XOceanLib
 * @brief       
 * @author      XOcean <https://github.com/SouthCraftX>
 * 
 * @version     Alpha 0.0.0
 * 
 * @addtogroup  Thread
 * @addtogroup  Simple System-API Redirecting Layer
 */

#pragma once

#if !defined(__XOC_THREAD_H__)
#   error Never include this header directly, include thread.h instead.
#endif // __XOC_THREAD_H__#pragma once
#define __XOC_WIN32_THREAD_H__

#include "../thread.h"
#include <processthreadsapi.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

// ---------------------------- Error Code Translator --------------------------
XOC_PURE
xoc_stat_t
__xoc_thread_resuming_error()
{
    switch (GetLastError())
    {
        case 0:     return XOC_THREAD_NOT_SUSPENDED;
        case 1:     return XOC_OK;
        default:    return XOC_THREAD_RESUME_FAILED;
    }
}

XOC_PURE
xoc_stat_t
__xoc_thread_priority_setting_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_PARAMETER:   return XOC_INVALID_ARG;
        case ERROR_INVALID_HANDLE:      return XOC_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return XOC_PERMISSION_DENIED;
        case ERROR_INVALID_OPERATION:   return XOC_ACCESS_VIOLATED;
        default:                        return XOC_UNKNOWN_ERROR;
    }
}

XOC_FORCE_INLINE XOC_PURE
xoc_stat_t
__xoc_thread_terminating_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;
        default:                    return XOC_UNKNOWN_ERROR;
    }
}

XOC_PURE
xoc_stat_t
__xoc_thread_joining_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;
        default:                    return XOC_UNKNOWN_ERROR;
    }
}

XOC_PURE
xoc_stat_t
__xoc_thread_suspending_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;
        default:                    return XOC_UNKNOWN_ERROR;
    }
}
// -----------------------------------------------------------------------------

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_thread_exit)(
    xoc_stat_t exit_code
){
    ExitThread((DWORD)exit_code);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_thread_terminate)(
    XOC_Thread *    thread
){  
    TerminateThread((HANDLE)thread , -1);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_thread_destory)(
    XOC_Thread *    thread
){
    CloseHandle((HANDLE)thread);
}

xoc_stat_t
XOC_IMPL(xoc_thread_set_priority)(
    XOC_Thread *              thread ,
    enum XOC_ThreadPriority   priority
){
    static
    const xoc_int8_t priority_level[] = {
        THREAD_PRIORITY_LOWEST ,
        THREAD_PRIORITY_BELOW_NORMAL ,
        THREAD_PRIORITY_NORMAL ,
        THREAD_PRIORITY_ABOVE_NORMAL ,
        THREAD_PRIORITY_HIGHEST ,
        THREAD_PRIORITY_TIME_CRITICAL   
    };
    return SetThreadPriority((HANDLE)thread , priority_level[priority]) ?
           XOC_OK : __xoc_thread_priority_setting_error();
}


XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_thread_is_alive)(
    XOC_Thread * thread
){
    return (WaitForSingleObject((HANDLE)thread , 0) == WAIT_TIMEOUT); 
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_get_exit_code)(
    XOC_Thread *    thread ,
    xoc_bool_t *    has_finsished
){
    DWORD   exit_code;
    return  GetExitCodeThread((HANDLE)thread , (LPDWORD)&exit_code) ?
            exit_code : -1; 
}

XOC_FORCE_INLINE
XOC_Thread *
XOC_IMPL(xoc_thread_self)()
{
    return (XOC_Thread *)GetCurrentThread();
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_terminate)(
    XOC_Thread * thread 
){
    return  TerminateThread((HANDLE)thread , -1) ? XOC_OK :
            __xoc_thread_terminating_error();
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_suspend)(
    XOC_Thread * thread
){
    return  (SuspendThread((HANDLE)thread) == -1) ? 
            __xoc_thread_suspending_error() : XOC_OK;
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_resume)(
    XOC_Thread * thread
){
    return  ResumeThread((HANDLE)thread) ? 
            __xoc_thread_resuming_error() : XOC_OK;
}

XOC_FORCE_INLINE
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
    XOC_Thread *     thread
){
    return WaitForSingleObject((HANDLE)thread , INFINITE) ?
           XOC_OK : __xoc_thread_joining_error();
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_multijoin)(
    XOC_Thread **   thread_array ,
    xoc_size_t      count
){
    return  (WaitForMultipleObjects(count , (HANDLE *)thread_array , TRUE , 
            INFINITE) == WAIT_FAILED) ?
            __xoc_thread_joining_error() : XOC_OK;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_thread_yield)()
{
    SwitchToThread();
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_thread_is_active)(
    XOC_Thread * thread
){
    switch (WaitForSingleObject((HANDLE)thread , 0))
    {
        case WAIT_TIMEOUT:  return xoc_true;    // active
        case WAIT_OBJECT_0: return xoc_false;   // finished
        default:            return __xoc_thread_joining_error();
    }
}

XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_thread_is_equal)(
    XOC_Thread *    x ,
    XOC_Thread *    y
){
    return x == y;
}

#if defined(__cplusplus)
}
#endif // __cplusplus