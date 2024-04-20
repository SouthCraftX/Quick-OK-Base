#pragma once
#define __XOCEAN_CONDLOCK_POSIX_H__

#include "include/condlock.h"

#if !defined(__XOCEAN_CONDLOCK_H__)
#   error "Never include condlock.h directly! Include condlock.h instead"
#endif 

#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanCondLock
{
    pthread_cond_t  cond_var;
    pthread_mutex_t lock;
};

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_init)(
    XOceanCondLock * lock
){
    lock->cond_var = PTHREAD_COND_INITIALIZER;
    lock->lock     = PTHREAD_MUTEX_INITIALIZER;
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_lock)(
    XOceanCondLock * lock
){
    pthread_mutex_lock(&lock->lock);
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_condlock_unlock)(
    XOceanCondLock * lock
){
    int ret = pthread_mutex_unlock(&lock->lock);
    // XOCEAN_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_condlock_wake)(
    XOceanCondLock * lock
){
    pthread_cond_signal(&lock->cond_var);
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_condlock_wake_all)(
    XOceanCondLock * lock
){
    pthread_cond_broadcast(&lock->cond_var);
}

XOCEAN_FORCE_INLINE
void 
XOCEAN_IMPL(xocean_condlock_destroy)(XOceanCondLock *lock)
{
    pthread_mutex_destroy(&lock->lock);
    pthread_cond_destroy(&lock->cond_var);
}

#if defined(__cplusplus)
}
#endif // __cplusplus

