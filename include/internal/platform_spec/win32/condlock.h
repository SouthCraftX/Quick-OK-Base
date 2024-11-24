// For debug
#include "../../condlock.h"

#if !defined(__QO_CONDLOCK_H__)
#   error "Never include this header directly, use <qo/condlock.h> instead!"
#endif

#pragma once

#include <winbase.h>
#include <synchapi.h>

#if defined(__cplusplus)
extern "C"{
#endif // __cplusplus

struct _QO_CondLock
{
    CONDITION_VARIABLE  cond_var;
    CRITICAL_SECTION    lock;
}; 


QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_init)(QO_CondLock * lock)
{
    InitializeCriticalSection(&lock->lock);
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_lock)(
    QO_CondLock * lock
){
    EnterCriticalSection(&lock->lock);
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_unlock)(
    QO_CondLock * lock
){
    LeaveCriticalSection(&lock->lock);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_condlock_wait)(
    QO_CondLock * lock
){
    SleepConditionVariableCS(&lock->cond_var, &lock->lock, INFINITE);
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_wake)(
    QO_CondLock * lock
){
    WakeConditionVariable(&lock->cond_var);
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_wake_all)(
    QO_CondLock * lock
){
    WakeAllConditionVariable(&lock->cond_var);
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_destory)(
    QO_CondLock * lock
){}

#if defined(__cplusplus)
}
#endif // __cplusplus