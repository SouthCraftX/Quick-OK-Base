#pragma once
#define __XOC_POSIX_PERFORMANCE_MONITOR_CPU_H__

// for debug
#include "include/performance_monitor/cpu.h"

#if !defined(__XOC_PERFORMANCE_MONITOR_CPU_H__)
#   error Never include this file directly, include "xoc/performance_monitor/cpu.h" instead.
#endif

#include <sys/resource.h>

struct rusage __xoc_last_usage;

xoc_stat_t
XOC_IMPL(xoc_cpu_time_get)(
    XOC_CPUTime *   p_cpu_time
){
    struct rusage resource_usage;

    // We do not handle error there, because we're sure that `who` and `usage` 
    // are valid.
    getrusage(RUSAGE_SELF, &resource_usage); 

    p_cpu_time->user_time = (resource_usage.ru_utime.tv_sec)
}

