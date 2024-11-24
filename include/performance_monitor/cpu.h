#pragma once
#define __QO_PERFORMANCE_MONITOR_CPU_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @remark All members of the structure represent the percentage of CPU time
///         spent in kernel and user mode. They ranges from 0.0 to 100.0.
struct _QO_CPUTime 
{
    qo_fp32_t kernel;
    qo_fp32_t user;
};
typedef struct _QO_CPUTime QO_CPUTime;

/// @brief Start measuring CPU time.
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_cpu_time_measurer_start)();

/// @brief  Stop measuring CPU time.
/// @param  p_cpu_time Pointer to the CPU time structure that represents the 
///         average CPU time during the measurement period.
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_cpu_time_measurer_stop)(
    QO_CPUTime *   p_cpu_time
);

qo_stat_t
QO_INTERFACE(qo_cpu_time_get)(
    QO_CPUTime *   p_cpu_time
) QO_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/performance_monitor/cpu.h"
#else
#   include "internal/platform_spec/posix/performance_monitor/cpu.h"
#endif // QO_PLATFORM(WINDOWS)

#define qo_cpu_time_measurer_start XINF
