#pragma once
#define __QO_PERFORMANCE_MONITOR_IO_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cpluplus

struct _QO_IOStatus
{
    qo_size_t  read_operations;
    qo_size_t  write_operations;
    qo_size_t  read_bytes;
    qo_size_t  write_bytes;
};
typedef struct _QO_IOStatus QO_IOStatus;

/// @brief  Initializes the IO measurer.  
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_io_measurer_init)();

/// @brief  Gets the current IO status.
/// @param p_status The pointer to the IO status.
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_io_measurer_get)(
    QO_IOStatus * p_status
) QO_NONNULL(1);

/// @brief  Finishes the IO measurer.
void
QO_INTERFACE(qo_io_measurer_finish)();

#if defined(__cplusplus)
}
#endif // __cpluplus