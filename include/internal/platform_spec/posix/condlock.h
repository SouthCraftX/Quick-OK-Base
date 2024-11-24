#pragma once
#define __QO_CONDLOCK_POSIX_H__

#include "include/condlock.h"

#if !defined(__QO_CONDLOCK_H__)
#   error "Never include condlock.h directly! Include condlock.h instead"
#endif 

#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_CondLock
{
    pthread_cond_t  cond_var;
    pthread_mutex_t lock;
};

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_init)(
    QO_CondLock * lock
){
    lock->cond_var = PTHREAD_COND_INITIALIZER;
    lock->lock     = PTHREAD_MUTEX_INITIALIZER;
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_lock)(
    QO_CondLock * lock
){
    pthread_mutex_lock(&lock->lock);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_condlock_unlock)(
    QO_CondLock * lock
){
    int ret = pthread_mutex_unlock(&lock->lock);
    // QO_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_condlock_wake)(
    QO_CondLock * lock
){
    pthread_cond_signal(&lock->cond_var);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_condlock_wake_all)(
    QO_CondLock * lock
){
    pthread_cond_broadcast(&lock->cond_var);
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_condlock_destroy)(QO_CondLock *lock)
{
    pthread_mutex_destroy(&lock->lock);
    pthread_cond_destroy(&lock->cond_var);
}

#if defined(__cplusplus)
}
#endif // __cplusplus

