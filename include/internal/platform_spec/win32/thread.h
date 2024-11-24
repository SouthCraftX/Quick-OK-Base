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

#if !defined(__QO_THREAD_H__)
#   error Never include this header directly, include thread.h instead.
#endif // __QO_THREAD_H__#pragma once
#define __QO_WIN32_THREAD_H__

#include "../thread.h"
#include <processthreadsapi.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

// ---------------------------- Error Code Translator --------------------------
QO_PURE
qo_stat_t
__qo_thread_resuming_error()
{
    switch (GetLastError())
    {
        case 0:     return QO_THREAD_NOT_SUSPENDED;
        case 1:     return QO_OK;
        default:    return QO_THREAD_RESUME_FAILED;
    }
}

QO_PURE
qo_stat_t
__qo_thread_priority_setting_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_PARAMETER:   return QO_INVALID_ARG;
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        case ERROR_INVALID_OPERATION:   return QO_ACCESS_VIOLATED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_FORCE_INLINE QO_PURE
qo_stat_t
__qo_thread_terminating_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return QO_INVALID_HANDLE;
        default:                    return QO_UNKNOWN_ERROR;
    }
}

QO_PURE
qo_stat_t
__qo_thread_joining_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return QO_INVALID_HANDLE;
        default:                    return QO_UNKNOWN_ERROR;
    }
}

QO_PURE
qo_stat_t
__qo_thread_suspending_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return QO_INVALID_HANDLE;
        default:                    return QO_UNKNOWN_ERROR;
    }
}
// -----------------------------------------------------------------------------

QO_FORCE_INLINE
void
QO_IMPL(qo_thread_exit)(
    qo_stat_t exit_code
){
    ExitThread((DWORD)exit_code);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_thread_terminate)(
    QO_Thread *    thread
){  
    TerminateThread((HANDLE)thread , -1);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_thread_destory)(
    QO_Thread *    thread
){
    CloseHandle((HANDLE)thread);
}

qo_stat_t
QO_IMPL(qo_thread_set_priority)(
    QO_Thread *              thread ,
    enum QO_ThreadPriority   priority
){
    static
    const qo_int8_t priority_level[] = {
        THREAD_PRIORITY_LOWEST ,
        THREAD_PRIORITY_BELOW_NORMAL ,
        THREAD_PRIORITY_NORMAL ,
        THREAD_PRIORITY_ABOVE_NORMAL ,
        THREAD_PRIORITY_HIGHEST ,
        THREAD_PRIORITY_TIME_CRITICAL   
    };
    return SetThreadPriority((HANDLE)thread , priority_level[priority]) ?
           QO_OK : __qo_thread_priority_setting_error();
}


QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_thread_is_alive)(
    QO_Thread * thread
){
    return (WaitForSingleObject((HANDLE)thread , 0) == WAIT_TIMEOUT); 
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_get_exit_code)(
    QO_Thread *    thread ,
    qo_bool_t *    has_finsished
){
    DWORD   exit_code;
    return  GetExitCodeThread((HANDLE)thread , (LPDWORD)&exit_code) ?
            exit_code : -1; 
}

QO_FORCE_INLINE
QO_Thread *
QO_IMPL(qo_thread_self)()
{
    return (QO_Thread *)GetCurrentThread();
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_terminate)(
    QO_Thread * thread 
){
    return  TerminateThread((HANDLE)thread , -1) ? QO_OK :
            __qo_thread_terminating_error();
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_suspend)(
    QO_Thread * thread
){
    return  (SuspendThread((HANDLE)thread) == -1) ? 
            __qo_thread_suspending_error() : QO_OK;
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_resume)(
    QO_Thread * thread
){
    return  ResumeThread((HANDLE)thread) ? 
            __qo_thread_resuming_error() : QO_OK;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_thread_sleep_milliseconds)(
    const qo_uint32_t milliseconds
){
    Sleep(milliseconds);
}

void
QO_IMPL(qo_thread_sleep_microseconds)(
    const qo_size_t microseconds
){
    HANDLE timer = CreateWaitableTimer(NULL , TRUE , NULL);
#if QO_SYSTEM_BIT(64)
    LARGE_INTEGER ft = { .QuadPart = -(10 * microseconds) }; 
#else
    LARGE_INTEGER ft = { .LowPart = -(10 * microseconds) , .HighPart = -1 };
#endif
    SetWaitableTimer(timer , &ft , 0 , NULL , FALSE , 0);
    WaitForSingleObject(timer , INFINITE);
    CloseHandle(timer);
}

qo_stat_t
QO_IMPL(qo_thread_join)(
    QO_Thread *     thread
){
    return WaitForSingleObject((HANDLE)thread , INFINITE) ?
           QO_OK : __qo_thread_joining_error();
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_multijoin)(
    QO_Thread **   thread_array ,
    qo_size_t      count
){
    return  (WaitForMultipleObjects(count , (HANDLE *)thread_array , TRUE , 
            INFINITE) == WAIT_FAILED) ?
            __qo_thread_joining_error() : QO_OK;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_thread_yield)()
{
    SwitchToThread();
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_thread_is_active)(
    QO_Thread * thread
){
    switch (WaitForSingleObject((HANDLE)thread , 0))
    {
        case WAIT_TIMEOUT:  return qo_true;    // active
        case WAIT_OBJECT_0: return qo_false;   // finished
        default:            return __qo_thread_joining_error();
    }
}

QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_thread_is_equal)(
    QO_Thread *    x ,
    QO_Thread *    y
){
    return x == y;
}

#if defined(__cplusplus)
}
#endif // __cplusplus