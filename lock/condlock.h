#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "../base.h"
#include "../memory.h"

struct _XOceanCondLock;
typedef struct _XOceanCondLock XOceanCondLock;

XOceanCondLock * xocean_condlock_new();

XOceanCondLock * xocean_condlock_new_ex(
    xocean_stat_t * stat
);

void xocean_condlock_delete(
    XOceanCondLock * lock
);

xocean_stat_t xocean_condlock_init(
    XOceanCondLock * lock
);

void xocean_condlock_lock(
    XOceanCondLock * lock
);

void xocean_condlock_unlock(
    XOceanCondLock * lock
);

void xocean_condlock_signal(
    XOceanCondLock * lock
);

void xocean_condlock_signal_all(
    XOceanCondLock * lock
);
    
void xocean_condlock_destroy(
    XOceanCondLock * lock
);

 
XOceanCondLock * xocean_condlock_new()
{
    xocean_stat_t stat;
    return xocean_condlock_new_ex(&stat);
}

 
XOceanCondLock * xocean_condlock_new_ex(xocean_stat_t * stat)
{
    XOCEAN_ASSERT(stat);
    XOceanCondLock * ret = (XOceanCondLock*)mi_malloc_small(sizeof(XOceanCondLock));
    if(XOCEAN_LIKELY(ret))
    {
        *stat = xocean_condlock_init(ret);
        return ret;
    }
    *stat = XOCEAN_OUT_OF_MEMORY;
    return NULL;
}


void xocean_condlock_delete(XOceanCondLock *lock)
{
    xocean_condlock_destroy(lock);
    mi_free(lock);
}

#if XOCEAN_PLATFORM(POSIX)
#   include <pthread.h>
struct _XOceanCondLock
{
    XOceanClassBase base;
    pthread_cond_t  cond_var;
    pthread_mutex_t lock;
};


void xocean_condlock_init(XOceanCondLock *lock)
{
    lock->cond_var = PTHREAD_COND_INITIALIZER;
    lock->lock = PTHREAD_MUTEX_INITIALIZER;
}


void xocean_condlock_rdlock(XOceanCondLock *lock)
{
    int ret = pthread_condlock_rdlock(&lock->condlock);
    XOCEAN_ASSERT(ret == 0); // Deadly lock, too many lock acquire or invaild argument
    (void)ret;
}


void xocean_condlock_wrlock(XOceanCondLock *lock)
{
    int ret = pthread_condlock_wrlock(&lock->condlock);
    XOCEAN_ASSERT(ret == 0); // Deadly lock or invaild argument
    (void)ret;
}


void xocean_condlock_unlock(XOceanCondLock *lock)
{
    int ret = pthread_condlock_unlock(&lock->condlock);
    XOCEAN_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}


void xocean_condlock_destroy(XOceanCondLock *lock)
{
    int ret = pthread_condlock_destroy(&lock->condlock);
    XOCEAN_ASSERT(ret == 0); // Trying to destroy a locked lock or invaild argument
    (void)ret;
}
#elif XOCEAN_PLATFORM(WINDOWS)
#   include <synchapi.h>

struct _XOceanCondLock
{
    CONDITION_VARIABLE cond_var;
    CRITICAL_SECTION lock;
}; // _XOceanCondLock



xocean_stat_t xocean_condlock_init(XOceanCondLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    InitializeCriticalSection(&lock->lock);
    return XOCEAN_OK;
}


void xocean_condlock_lock(XOceanCondLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    EnterCriticalSection(&lock->lock);
}


void xocean_condlock_unlock(XOceanCondLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    LeaveCriticalSection(&lock->lock);
}


void xocean_condlock_signal(XOceanCondLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    WakeConditionVariable(&lock->cond_var);
}


void xocean_condlock_signal_all(XOceanCondLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    WakeAllConditionVariable(&lock->cond_var);
}


void xocean_condlock_destory(XOceanCondLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    (void)lock;
    return;
}


#endif

#if defined(__cplusplus)
}
#endif // __cplusplus
