#pragma once
#define __XOC_CONDLOCK_POSIX_H__

#include "include/condlock.h"

#if !defined(__XOC_CONDLOCK_H__)
#   error "Never include condlock.h directly! Include condlock.h instead"
#endif 

#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_CondLock
{
    pthread_cond_t  cond_var;
    pthread_mutex_t lock;
};

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_init)(
    XOC_CondLock * lock
){
    lock->cond_var = PTHREAD_COND_INITIALIZER;
    lock->lock     = PTHREAD_MUTEX_INITIALIZER;
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_lock)(
    XOC_CondLock * lock
){
    pthread_mutex_lock(&lock->lock);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_condlock_unlock)(
    XOC_CondLock * lock
){
    int ret = pthread_mutex_unlock(&lock->lock);
    // XOC_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_condlock_wake)(
    XOC_CondLock * lock
){
    pthread_cond_signal(&lock->cond_var);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_condlock_wake_all)(
    XOC_CondLock * lock
){
    pthread_cond_broadcast(&lock->cond_var);
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_condlock_destroy)(XOC_CondLock *lock)
{
    pthread_mutex_destroy(&lock->lock);
    pthread_cond_destroy(&lock->cond_var);
}

#if defined(__cplusplus)
}
#endif // __cplusplus

