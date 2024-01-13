#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "../base.h"
#include "../memory.h"

struct xoceanRWLock;
typedef struct xoceanRWLock XOceanRWLock;

XOceanRWLock * xocean_rwlock_new();
XOceanRWLock * xocean_rwlock_new_ex(
    xocean_stat_t * stat
);
void xocean_rwlock_delete(
    XOceanRWLock * lock
);

xocean_stat_t xocean_rwlock_init(
    XOceanRWLock * lock
);

void xocean_rwlock_rdlock(
    XOceanRWLock * lock
);

void xocean_rwlock_wrlock(
    XOceanRWLock * lock
);

void xocean_rwlock_unlock(
    XOceanRWLock * lock
);

void xocean_rwlock_destroy(
    XOceanRWLock * lock
);

 
XOceanRWLock * xocean_rwlock_new()
{
    xocean_stat_t stat;
    return xocean_rwlock_new_ex(&stat);
}

 
XOceanRWLock * xocean_rwlock_new_ex(xocean_stat_t * stat)
{
    XOCEAN_ASSERT(stat);
    XOceanRWLock * ret = (XOceanRWLock*)mi_malloc_small(sizeof(XOceanRWLock));
    if(XOCEAN_LIKELY(ret))
    {
        *stat = xocean_rwlock_init(ret);
        return ret;
    }
    *stat = XOCEAN_OUT_OF_MEMORY;
    return NULL;
}


void xocean_rwlock_delete(XOceanRWLock * lock)
{
    xocean_rwlock_destroy(lock);
    mi_free(lock);
}

#if XOCEAN_PLATFORM(POSIX)
#   include <pthread.h>
struct xoceanRWLock
{
    XOCeanClassBase     base;
    pthread_rwlock_t    rwlock;
};


xocean_stat_t xocean_rwlock_init(XOceanRWLock * lock)
{
    int ret = pthread_rwlock_init(&lock->rwlock, NULL);
    if(XOCEAN_UNLIKELY(ret))
    {
        switch(ret)
        {
            case EAGAIN:
                return XOCEAN_NO_RESOURCE;
            case EINVAL:
                return XOCEAN_INVALID_ARGUMENT;
            case ENOMEM:
                return XOCEAN_OUT_OF_MEMORY;
            default:
                return XOCEAN_ERR_UNKNOWN;
        }
    }
    return XOCEAN_OK;
}


void xocean_rwlock_rdlock(XOceanRWLock * lock)
{
    int ret = pthread_rwlock_rdlock(&lock->rwlock);
    XOCEAN_ASSERT(ret == 0); // Deadly lock, too many lock acquire or invaild argument
    (void)ret;
}


void xocean_rwlock_wrlock(XOceanRWLock * lock)
{
    int ret = pthread_rwlock_wrlock(&lock->rwlock);
    XOCEAN_ASSERT(ret == 0); // Deadly lock or invaild argument
    (void)ret;
}


void xocean_rwlock_unlock(XOceanRWLock * lock)
{
    int ret = pthread_rwlock_unlock(&lock->rwlock);
    XOCEAN_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}


void xocean_rwlock_destroy(XOceanRWLock * lock)
{
    int ret = pthread_rwlock_destroy(&lock->rwlock);
    XOCEAN_ASSERT(ret == 0); // Trying to destroy a locked lock or invaild argument
    (void)ret;
}
#elif XOCEAN_PLATFORM(WINDOWS)
#   include <synchapi.h>

struct xoceanRWLock
{
    XOceanClassBase base;
    SRWLOCK         lock;
    (void       )(* fn_unlock   )(PSRWLOCK);
}; // xoceanRWLock
// Expected size: 16 bytes(on 64-bit) / 8bytes(on 32-bit)


xocean_stat_t xocean_rwlock_init(XOceanRWLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    InitializeSRWLock(&lock->lock);
#   if defined(XOCEAN_DEBUG)
    lock->fn_unlock = NULL;
#   endif
    return XOCEAN_OK;
}


void xocean_rwlock_rdlock(XOceanRWLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    XOCEAN_ASSERT(lock->fn_unlock == NULL)
    lock->fn_unlock = AcquireSRWLockShared;
    AcquireSRWLockShared(&lock->lock);
}


void xocean_rwlock_wrlock(XOceanRWLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    XOCEAN_ASSERT(lock->fn_unlock == NULL);   
    lock->fn_unlock = ReleaseSRWLockExclusive;
    AcquireSRWLockExclusive(&lock->lock);
}


void xocean_rwlock_unlock(XOceanRWLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    (*lock->fn_unlock)(&lock->lock);
#   ifdef XOCEAN_DEBUG
    lock->fn_unlock = NULL;
#   endif // XOCEAN_DEBUG
}


void xocean_rwlock_destory(XOceanRWLock * lock)
{
    XOCEAN_ASSERT(lock != NULL);
    (void)lock;
    return;
}


#endif

#if defined(__cplusplus)
}
#endif // __cplusplus
