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
#define __XOC_CONDLOCK_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

// @brief Condition lock
// @remark This structure is designed not to exposed to user.
struct _XOC_CondLock;
typedef struct _XOC_CondLock XOC_CondLock;

// @brief Initialize condition lock
// @param lock Condition lock
void 
XOC_INTERFACE(xoc_condlock_init)(
    XOC_CondLock * lock
);

// @brief Aquire condition lock
// @param lock Condition lock
void 
XOC_INTERFACE(xoc_condlock_lock)(
    XOC_CondLock * lock
);

// @brief Release condition lock
// @param lock Condition lock
// @note To reduce context switches, it is recommanded to call this function 
// before calling `xoc_condlock_wake` or `xoc_condlock_wake_all`.
void 
XOC_INTERFACE(xoc_condlock_unlock)(
    XOC_CondLock * lock
);

// @brief Wait for condition lock until other thread wake caller up.
// @param lock Condition lock
void
XOC_INTERFACE(xoc_condlock_wait)(
    XOC_CondLock * lock
);

// @brief   Wake up one thread waiting for condition lock.
// @param   `lock` Condition lock
// @note    To reduce context switches, it is recommanded to call 
// `xoc_condlock_unlock` before calling this function.
void 
XOC_INTERFACE(xoc_condlock_wake)(
    XOC_CondLock * lock
);

// @brief Wake up all threads waiting for condition lock.
// @param lock Condition lock
// @note To reduce context switches, it is recommanded to call 
// `xoc_condlock_unlock` before calling this function.
void 
XOC_INTERFACE(xoc_condlock_wake_all)(
    XOC_CondLock * lock
);

// @brief Destroy condition lock
// @param lock Condition lock
void 
XOC_INTERFACE(xoc_condlock_destroy)(
    XOC_CondLock * lock
);


#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "platform_spec/win32/condlock.h"
#elif XOC_PLATFORM(POSIX)
#   include "platform_spec/posix/condlock.h"
#endif 

#define xoc_condlock_init        XOC_INTERFACE(xoc_condlock_init)
#define xoc_condlock_lock        XOC_INTERFACE(xoc_condlock_lock)
#define xoc_condlock_unlock      XOC_INTERFACE(xoc_condlock_unlock)
#define xoc_condlock_wait        XOC_INTERFACE(xoc_condlock_wait)
#define xoc_condlock_wake        XOC_INTERFACE(xoc_condlock_wake)
#define xoc_condlock_wake_all    XOC_INTERFACE(xoc_condlock_wake_all)
#define xoc_condlock_destroy     XOC_INTERFACE(xoc_condlock_destroy)