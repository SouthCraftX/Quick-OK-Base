#pragma once
#define __XOC_PERFORMANCE_MONITOR_CPU_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @remark All members of the structure represent the percentage of CPU time
///         spent in kernel and user mode. They ranges from 0.0 to 100.0.
struct _XOC_CPUTime 
{
    xoc_fp32_t kernel;
    xoc_fp32_t user;
};
typedef struct _XOC_CPUTime XOC_CPUTime;

/// @brief Start measuring CPU time.
/// @return The status of the operation.
xoc_stat_t
XOC_INTERFACE(xoc_cpu_time_measurer_start)();

/// @brief  Stop measuring CPU time.
/// @param  p_cpu_time Pointer to the CPU time structure that represents the 
///         average CPU time during the measurement period.
/// @return The status of the operation.
xoc_stat_t
XOC_INTERFACE(xoc_cpu_time_measurer_stop)(
    XOC_CPUTime *   p_cpu_time
);

xoc_stat_t
XOC_INTERFACE(xoc_cpu_time_get)(
    XOC_CPUTime *   p_cpu_time
) XOC_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/performance_monitor/cpu.h"
#else
#   include "internal/platform_spec/posix/performance_monitor/cpu.h"
#endif // XOC_PLATFORM(WINDOWS)

#define xoc_cpu_time_measurer_start XINF
