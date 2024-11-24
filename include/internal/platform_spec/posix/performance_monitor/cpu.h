#pragma once
#define __QO_POSIX_PERFORMANCE_MONITOR_CPU_H__

// for debug
#include "include/performance_monitor/cpu.h"

#if !defined(__QO_PERFORMANCE_MONITOR_CPU_H__)
#   error Never include this file directly, include "qo/performance_monitor/cpu.h" instead.
#endif

#include <sys/resource.h>

struct rusage __qo_last_usage;

qo_stat_t
QO_IMPL(qo_cpu_time_get)(
    QO_CPUTime *   p_cpu_time
){
    struct rusage resource_usage;

    // We do not handle error there, because we're sure that `who` and `usage` 
    // are valid.
    getrusage(RUSAGE_SELF, &resource_usage); 

    p_cpu_time->user_time = (resource_usage.ru_utime.tv_sec)
}

