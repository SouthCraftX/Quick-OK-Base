/*******************************************************************************
 *  @headerfile condlock.h
 *  @addtogroup Headers under the MIT License
 *  @brief      Condition lock and interfaces
 *  @author     XOcean <https://github.com/SouthCraftX>
 *  
 *  @version    Alpha 0.0.0
 *  
 *  @addtogroup Synchronization
 *  @addtogroup Condition Lock
 *  @addtogroup Simple System-API Redirecting Layer
 * 
 *  Changelog:
 *  ----------------------------------------------------------------------------
 *  Who     | When           | What
 *  XOcean  | ?              | First created this file.
 *  XOcean  | Jul 21st, 2024 | Add comments to this header file.
 *  ----------------------------------------------------------------------------
*******************************************************************************/

#pragma once
#define __QO_CONDLOCK_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

// @brief Condition lock
// @remark This structure is designed not to exposed to user.
struct _QO_CondLock;
typedef struct _QO_CondLock QO_CondLock;

// @brief Initialize condition lock
// @param lock Condition lock
void 
QO_INTERFACE(qo_condlock_init)(
    QO_CondLock * lock
);

// @brief Aquire condition lock
// @param lock Condition lock
void 
QO_INTERFACE(qo_condlock_lock)(
    QO_CondLock * lock
);

// @brief Release condition lock
// @param lock Condition lock
// @note To reduce context switches, it is recommanded to call this function 
// before calling `qo_condlock_wake` or `qo_condlock_wake_all`.
void 
QO_INTERFACE(qo_condlock_unlock)(
    QO_CondLock * lock
);

// @brief Wait for condition lock until other thread wake caller up.
// @param lock Condition lock
void
QO_INTERFACE(qo_condlock_wait)(
    QO_CondLock * lock
);

// @brief   Wake up one thread waiting for condition lock.
// @param   `lock` Condition lock
// @note    To reduce context switches, it is recommanded to call 
// `qo_condlock_unlock` before calling this function.
void 
QO_INTERFACE(qo_condlock_wake)(
    QO_CondLock * lock
);

// @brief Wake up all threads waiting for condition lock.
// @param lock Condition lock
// @note To reduce context switches, it is recommanded to call 
// `qo_condlock_unlock` before calling this function.
void 
QO_INTERFACE(qo_condlock_wake_all)(
    QO_CondLock * lock
);

// @brief Destroy condition lock
// @param lock Condition lock
void 
QO_INTERFACE(qo_condlock_destroy)(
    QO_CondLock * lock
);


#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "platform_spec/win32/condlock.h"
#elif QO_PLATFORM(POSIX)
#   include "platform_spec/posix/condlock.h"
#endif 

#define qo_condlock_init        QO_INTERFACE(qo_condlock_init)
#define qo_condlock_lock        QO_INTERFACE(qo_condlock_lock)
#define qo_condlock_unlock      QO_INTERFACE(qo_condlock_unlock)
#define qo_condlock_wait        QO_INTERFACE(qo_condlock_wait)
#define qo_condlock_wake        QO_INTERFACE(qo_condlock_wake)
#define qo_condlock_wake_all    QO_INTERFACE(qo_condlock_wake_all)
#define qo_condlock_destroy     QO_INTERFACE(qo_condlock_destroy)