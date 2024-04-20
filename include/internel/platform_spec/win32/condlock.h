// For debug
#include "../../condlock.h"

#if !defined(__XOCEAN_CONDLOCK_H__)
#   error "Never include this header directly, use <xocean/condlock.h> instead!"
#endif

#pragma once

#include <winbase.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C"{
#endif // __cplusplus

struct _XOceanCondLock
{
    CONDITION_VARIABLE  cond_var;
    CRITICAL_SECTION    lock;
}; 


XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_init)(XOceanCondLock * lock)
{
    InitializeCriticalSection(&lock->lock);
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_lock)(
    XOceanCondLock * lock
){
    EnterCriticalSection(&lock->lock);
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_unlock)(
    XOceanCondLock * lock
){
    LeaveCriticalSection(&lock->lock);
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_condlock_wait)(
    XOceanCondLock * lock
){
    SleepConditionVariableCS(&lock->cond_var, &lock->lock, INFINITE);
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_wake)(
    XOceanCondLock * lock
){
    WakeConditionVariable(&lock->cond_var);
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_wake_all)(
    XOceanCondLock * lock
){
    WakeAllConditionVariable(&lock->cond_var);
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_destory)(
    XOceanCondLock * lock
){}

#if defined(__cplusplus)
}
#endif // __cplusplus