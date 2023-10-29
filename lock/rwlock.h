#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "base.h"

struct _XOceanRWLock;
typedef struct _XOceanRWLock XOceanRWLock;

XOCEAN_INTERNAL xocean_stat_t __xocean_rwlock_init(XOceanRWLock *lock);
XOCEAN_INTERNAL void __xocean_rwlock_rdlock(XOceanRWLock *lock);
XOCEAN_INTERNAL void __xocean_rwlock_wrlock(XOceanRWLock *lock);
XOCEAN_INTERNAL void __xocean_rwlock_unlock(XOceanRWLock *lock);


#if XOCEAN_PLATFORM(POSIX)
#   include <pthread.h>
struct _XOceanRWLock
{
    pthread_rwlock_t rwlock;
};

XOCEAN_INTERNAL xocean_stat_t __xocean_rwlock_init(XOceanRWLock *lock)
{
    pthread_rwlockattr_t attr;
    pthread_rwlock_attr_init(&attr);
    pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_rwlock_init(&lock->rwlock, NULL);
}

#endif

#if defined(__cplusplus)
}
#endif // __cplusplus
