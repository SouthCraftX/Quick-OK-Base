#pragma once
#define __XOC_WIN32_PROCESS_H__


#if !defined(__XOC_PROCESS_H__)
#error "Do not include this file directly. Use <xoc/process.h> instead."
#endif

#include <process.h>
#include <wincon.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

XOC_PURE
xoc_stat_t
__xoc_process_killing_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:      return  XOC_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return  XOC_PERMISSION_DENIED;
        default:                        return  XOC_UNKNOWN_ERROR;
    }
}

/// @author XOcean
/// @remark I placed xoc_proces_create() in ".c" file because it is a big 
/// function and unlikely to be called often. Thus, it is not suitable to make 
/// it inline.

xoc_stat_t
XOC_IMPL(xoc_process_adjust_priority)(
    XOC_Process *             process ,
    enum XOC_ThreadPriority   priority
){
    XOC_GLOBAL_LOCAL
    const DWORD priority_table[] = {
        IDEL_PRIORITY_CLASS,
        BELOW_NORMAL_PRIORITY_CLASS,
        NORMAL_PRIORITY_CLASS,
        ABOVE_NORMAL_PRIORITY_CLASS,
        HIGH_PRIORITY_CLASS,
        REALTIME_PRIORITY_CLASS
    };


}

XOC_FORCE_INLINE
XOC_Process *
XOC_IMPL(xoc_process_get_current)()
{
    return (XOC_Process *)GetCurrentProcess();
}

XOC_FORCE_INLINE
xoc_pid_t
XOC_IMPL(xoc_process_get_pid)(
    XOC_Process *   process
){
    return GetProcessId((HANDLE)process);
}

XOC_FORCE_INLINE
xoc_pid_t
XOC_IMPL(xoc_process_get_current_pid)()
{
    return GetCurrentProcessId();
}

XOC_FORCE_INLINE XOC_NORETURN
void
XOC_IMPL(xoc_process_exit_current)(
    xoc_stat_t   exit_code
){
    ExitProcess((DWORD)exit_code);
}

xoc_stat_t
XOC_IMPL(xoc_process_kill)(
    XOC_Process *   process ,
    xoc_bool_t      wait ,
    xoc_stat_t *    exit_code
){
    const HANDLE process_handle = (HANDLE)process;
    TerminateProcess(process_handle , exit_code ? (DWORD)*exit_code : 0);
    WaitForSingleObject(process_handle , wait ? INFINITE : 0);
    CloseHandle(process_handle);
}

#if defined(__cplusplus)
}
#endif // __cplusplus