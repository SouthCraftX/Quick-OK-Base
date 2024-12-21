#pragma once
#define __QO_SEMAPHORE_H__

#include "base.h"
#include <semaphore.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Semaphore;
typedef struct _QO_Semaphore QO_Semaphore;

/// @brief Open or create a named semaphore
/// @param p_semaphore Pointer to the semaphore object
/// @param name Name of the semaphore
/// @return The status of the operation
/// @retval QO_OK The operation was successful
/// @retval 
qo_stat_t
QO_INTERFACE(qo_semaphore_open)(
    QO_Semaphore *  p_semaphore ,
    qo_ccstring_t   name ,
    qo_flag32_t     flags
)QO_NONNULL(1 , 2);

/// @brief Create a unnamed semaphore 
/// @param p_semaphore Pointer to the semaphore object
/// @param initial_count Initial count of the semaphore
/// @return The status of the operation
qo_stat_t
QO_INTERFACE(qo_semaphora_init)(
    QO_Semaphore *  p_semaphora ,
    qo_size_t       initial_count
) QO_NONNULL(1);

void
QO_INTERFACE(qo_semaphora_destroy)(
    QO_Semaphore *  p_semaphora 
);

qo_stat_t
QO_INTERFACE(qo_semaphora_post)(
    QO_Semaphore *  p_semaphora 
) QO_NONNULL(1);

qo_stat_t
QO_INTERFACE(qo_semaphora_wait)(
    QO_Semaphore *  p_semaphora 
) QO_NONNULL(1);

qo_stat_t
QO_INTERFACE(qo_semaphora_wait_timeout)(
    QO_Semaphore *  p_semaphora , 
    qo_size_t       million_seconds
) QO_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)

#else
#   include "internal/platform_spec/posix/semaphore.h"
#endif