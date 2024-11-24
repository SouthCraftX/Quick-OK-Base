#pragma once
#define __QO_WIN32_PERFORMANCE_MONITOR_CPU_H__

// for debug
#include "include/performance_monitor/cpu.h"

#if !defined(__QO_PERFORMANCE_MONITOR_CPU_H__)
#   error Never include this file directly, include qo/performance_monitor/cpu.h instead.
#endif

#include <winbase.h>

FILETIME __qo_cpu_time_user , __qo_cpu_time_kernel , __qo_process_creation_time;

QO_FORCE_INLINE
ULONGLONG
__qo_sysfiletime_to_ull(
    FILETIME *   filetime
){
    return (((ULONGLONG)filetime->dwHighDateTime) << 32) | filetime->dwLowDateTime;
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_cpu_time_measurer_start)()
{
    FILETIME _; // unused
    return GetProcessTimes(
        GetCurrentProcess() , 
        &__qo_process_creation_time ,
        &_ , 
        &__qo_cpu_time_kernel , 
        &__qo_cpu_time_user
    ) ? QO_OK : QO_UNKNOWN_ERROR;
}

qo_stat_t
QO_IMPL(qo_cpu_time_measurer_stop)(
    QO_CPUTime *   p_cpu_time
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
        return QO_UNKNOWN_ERROR;
    }
    const ULONGLONG 
        period_times =  __qo_sysfiletime_to_ull(&now_creation_time) - 
                        __qo_sysfiletime_to_ull(&__qo_process_creation_time) ,
        kernel_times =  __qo_sysfiletime_to_ull(&kernel_end) - 
                        __qo_sysfiletime_to_ull(&__qo_cpu_time_kernel) ,
        user_times =    __qo_sysfiletime_to_ull(&user_end) -
                        __qo_sysfiletime_to_ull(&__qo_cpu_time_user);
    p_cpu_time->kernel = (qo_fp32_t)kernel_times / period_times * 100.0f;
    p_cpu_time->user = (qo_fp32_t)user_times / period_times * 100.0f;
    return QO_OK;
}

/*
qo_stat_t
QO_IMPL(qo_cpu_time_get)(
    QO_CPUTime *   cpu_time
){
    FILETIME idel_time , kernel_time , user_time;
    GetSystemTimes(&idel_time , &kernel_time , &user_time);
    const ULONGLONG idel_u64 = __qo_sysfiletime_to_ull(&idel_time) ,
                    kernel_u64 = __qo_sysfiletime_to_ull(&kernel_time) ,
                    user_u64 = __qo_sysfiletime_to_ull(&user_time) ,
                    total_u64 = kernel_u64 + user_u64 + idel_u64;
    cpu_time->kernel = (qo_fp32_t)kernel_u64 / total_u64 * 100.0f;
    cpu_time->user = (qo_fp32_t)user_u64 / total_u64 * 100.0f;
} 
*/