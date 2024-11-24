#pragma once
#define __QO_WIN32_PROCESS_H__


#if !defined(__QO_PROCESS_H__)
#error "Do not include this file directly. Use <qo/process.h> instead."
#endif

#include <process.h>
#include <wincon.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

QO_PURE
qo_stat_t
__qo_process_killing_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:      return  QO_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return  QO_PERMISSION_DENIED;
        default:                        return  QO_UNKNOWN_ERROR;
    }
}

/// @author XOcean
/// @remark I placed qo_proces_create() in ".c" file because it is a big 
/// function and unlikely to be called often. Thus, it is not suitable to make 
/// it inline.

qo_stat_t
QO_IMPL(qo_process_adjust_priority)(
    QO_Process *             process ,
    enum QO_ThreadPriority   priority
){
    QO_GLOBAL_LOCAL
    const DWORD priority_table[] = {
        IDEL_PRIORITY_CLASS,
        BELOW_NORMAL_PRIORITY_CLASS,
        NORMAL_PRIORITY_CLASS,
        ABOVE_NORMAL_PRIORITY_CLASS,
        HIGH_PRIORITY_CLASS,
        REALTIME_PRIORITY_CLASS
    };


}

QO_FORCE_INLINE
QO_Process *
QO_IMPL(qo_process_get_current)()
{
    return (QO_Process *)GetCurrentProcess();
}

QO_FORCE_INLINE
qo_pid_t
QO_IMPL(qo_process_get_pid)(
    QO_Process *   process
){
    return GetProcessId((HANDLE)process);
}

QO_FORCE_INLINE
qo_pid_t
QO_IMPL(qo_process_get_current_pid)()
{
    return GetCurrentProcessId();
}

QO_FORCE_INLINE QO_NORETURN
void
QO_IMPL(qo_process_exit_current)(
    qo_stat_t   exit_code
){
    ExitProcess((DWORD)exit_code);
}

qo_stat_t
QO_IMPL(qo_process_kill)(
    QO_Process *   process ,
    qo_bool_t      wait ,
    qo_stat_t *    exit_code
){
    const HANDLE process_handle = (HANDLE)process;
    TerminateProcess(process_handle , exit_code ? (DWORD)*exit_code : 0);
    WaitForSingleObject(process_handle , wait ? INFINITE : 0);
    CloseHandle(process_handle);
}

#if defined(__cplusplus)
}
#endif // __cplusplus