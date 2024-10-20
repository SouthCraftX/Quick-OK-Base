#pragma once
#define __XOC_WIN32_PERFORMANCE_MONITOR_CPU_H__

// for debug
#include "include/performance_monitor/cpu.h"

#if !defined(__XOC_PERFORMANCE_MONITOR_CPU_H__)
#   error Never include this file directly, include xoc/performance_monitor/cpu.h instead.
#endif

#include <winbase.h>

FILETIME __xoc_cpu_time_user , __xoc_cpu_time_kernel , __xoc_process_creation_time;

XOC_FORCE_INLINE
ULONGLONG
__xoc_filetime_to_ull(
    FILETIME *   filetime
){
    return (((ULONGLONG)filetime->dwHighDateTime) << 32) | filetime->dwLowDateTime;
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_cpu_time_measurer_start)()
{
    FILETIME _; // unused
    return GetProcessTimes(
        GetCurrentProcess() , 
        &__xoc_process_creation_time ,
        &_ , 
        &__xoc_cpu_time_kernel , 
        &__xoc_cpu_time_user
    ) ? XOC_OK : XOC_UNKNOWN_ERROR;
}

xoc_stat_t
XOC_IMPL(xoc_cpu_time_measurer_stop)(
    XOC_CPUTime *   p_cpu_time
){
    FILETIME kernel_end , user_end , now_creation_time , _; 
    if( !GetProcessTimes(
            GetCurrentProcess() , 
            &now_creation_time , 
            &_ , 
            &kernel_end , 
            &user_end
        )
    ) {
        return XOC_UNKNOWN_ERROR;
    }
    const ULONGLONG 
        period_times =  __xoc_filetime_to_ull(&now_creation_time) - 
                        __xoc_filetime_to_ull(&__xoc_process_creation_time) ,
        kernel_times =  __xoc_filetime_to_ull(&kernel_end) - 
                        __xoc_filetime_to_ull(&__xoc_cpu_time_kernel) ,
        user_times =    __xoc_filetime_to_ull(&user_end) -
                        __xoc_filetime_to_ull(&__xoc_cpu_time_user);
    p_cpu_time->kernel = (xoc_fp32_t)kernel_times / period_times * 100.0f;
    p_cpu_time->user = (xoc_fp32_t)user_times / period_times * 100.0f;
    return XOC_OK;
}

/*
xoc_stat_t
XOC_IMPL(xoc_cpu_time_get)(
    XOC_CPUTime *   cpu_time
){
    FILETIME idel_time , kernel_time , user_time;
    GetSystemTimes(&idel_time , &kernel_time , &user_time);
    const ULONGLONG idel_u64 = __xoc_filetime_to_ull(&idel_time) ,
                    kernel_u64 = __xoc_filetime_to_ull(&kernel_time) ,
                    user_u64 = __xoc_filetime_to_ull(&user_time) ,
                    total_u64 = kernel_u64 + user_u64 + idel_u64;
    cpu_time->kernel = (xoc_fp32_t)kernel_u64 / total_u64 * 100.0f;
    cpu_time->user = (xoc_fp32_t)user_u64 / total_u64 * 100.0f;
} 
*/