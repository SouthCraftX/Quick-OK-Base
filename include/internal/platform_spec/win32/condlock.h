// For debug
#include "../../condlock.h"

#if !defined(__XOC_CONDLOCK_H__)
#   error "Never include this header directly, use <xoc/condlock.h> instead!"
#endif

#pragma once

#include <winbase.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C"{
#endif // __cplusplus

struct _XOC_CondLock
{
    CONDITION_VARIABLE  cond_var;
    CRITICAL_SECTION    lock;
}; 


XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_init)(XOC_CondLock * lock)
{
    InitializeCriticalSection(&lock->lock);
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_lock)(
    XOC_CondLock * lock
){
    EnterCriticalSection(&lock->lock);
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_unlock)(
    XOC_CondLock * lock
){
    LeaveCriticalSection(&lock->lock);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_condlock_wait)(
    XOC_CondLock * lock
){
    SleepConditionVariableCS(&lock->cond_var, &lock->lock, INFINITE);
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_wake)(
    XOC_CondLock * lock
){
    WakeConditionVariable(&lock->cond_var);
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_wake_all)(
    XOC_CondLock * lock
){
    WakeAllConditionVariable(&lock->cond_var);
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_destory)(
    XOC_CondLock * lock
){}

#if defined(__cplusplus)
}
#endif // __cplusplus