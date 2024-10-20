#pragma once
#define __XOC_PERFORMANCE_MONITOR_IO_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cpluplus

struct _XOC_IOStatus
{
    xoc_size_t  read_operations;
    xoc_size_t  write_operations;
    xoc_size_t  read_bytes;
    xoc_size_t  write_bytes;
};
typedef struct _XOC_IOStatus XOC_IOStatus;

/// @brief  Initializes the IO measurer.  
/// @return The status of the operation.
xoc_stat_t
XOC_INTERFACE(xoc_io_measurer_init)();

/// @brief  Gets the current IO status.
/// @param p_status The pointer to the IO status.
/// @return The status of the operation.
xoc_stat_t
XOC_INTERFACE(xoc_io_measurer_get)(
    XOC_IOStatus * p_status
) XOC_NONNULL(1);

/// @brief  Finishes the IO measurer.
void
XOC_INTERFACE(xoc_io_measurer_finish)();

#if defined(__cplusplus)
}
#endif // __cpluplus