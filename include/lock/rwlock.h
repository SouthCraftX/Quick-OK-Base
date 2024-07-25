#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "../base.h"
#include "../memory.h"

struct xocRWLock;
typedef struct xocRWLock XOCRWLock;

XOCRWLock * xoc_rwlock_new();
XOCRWLock * xoc_rwlock_new_ex(
    xoc_stat_t * stat
);
void xoc_rwlock_delete(
    XOCRWLock * lock
);

xoc_stat_t xoc_rwlock_init(
    XOCRWLock * lock
);

void xoc_rwlock_rdlock(
    XOCRWLock * lock
);

void xoc_rwlock_wrlock(
    XOCRWLock * lock
);

void xoc_rwlock_unlock(
    XOCRWLock * lock
);

void xoc_rwlock_destroy(
    XOCRWLock * lock
);

 
XOCRWLock * xoc_rwlock_new()
{
    xoc_stat_t stat;
    return xoc_rwlock_new_ex(&stat);
}

 
XOCRWLock * xoc_rwlock_new_ex(xoc_stat_t * stat)
{
    XOC_ASSERT(stat);
    XOCRWLock * ret = (XOCRWLock*)mi_malloc_small(sizeof(XOCRWLock));
    if (XOC_LIKELY(ret))
    {
        *stat = xoc_rwlock_init(ret);
        return ret;
    }
    *stat = XOC_OUT_OF_MEMORY;
    return NULL;
}


void xoc_rwlock_delete(XOCRWLock * lock)
{
    xoc_rwlock_destroy(lock);
    mi_free(lock);
}

#if XOC_PLATFORM(POSIX)
#   include <pthread.h>
struct xocRWLock
{
    XOCeanClassBase     base;
    pthread_rwlock_t    rwlock;
};


xoc_stat_t xoc_rwlock_init(XOCRWLock * lock)
{
    int ret = pthread_rwlock_init(&lock->rwlock, NULL);
    if (XOC_UNLIKELY(ret))
    {
        switch(ret)
        {
            case EAGAIN:
                return XOC_NO_RESOURCE;
            case EINVAL:
                return XOC_INVALID_ARGUMENT;
            case ENOMEM:
                return XOC_OUT_OF_MEMORY;
            default:
                return XOC_ERR_UNKNOWN;
        }
    }
    return XOC_OK;
}


void xoc_rwlock_rdlock(XOCRWLock * lock)
{
    int ret = pthread_rwlock_rdlock(&lock->rwlock);
    XOC_ASSERT(ret == 0); // Deadly lock, too many lock acquire or invaild argument
    (void)ret;
}


void xoc_rwlock_wrlock(XOCRWLock * lock)
{
    int ret = pthread_rwlock_wrlock(&lock->rwlock);
    XOC_ASSERT(ret == 0); // Deadly lock or invaild argument
    (void)ret;
}


void xoc_rwlock_unlock(XOCRWLock * lock)
{
    int ret = pthread_rwlock_unlock(&lock->rwlock);
    XOC_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}


void xoc_rwlock_destroy(XOCRWLock * lock)
{
    int ret = pthread_rwlock_destroy(&lock->rwlock);
    XOC_ASSERT(ret == 0); // Trying to destroy a locked lock or invaild argument
    (void)ret;
}
#elif XOC_PLATFORM(WINDOWS)
#   include <synchapi.h>

struct xocRWLock
{
    XOCClassBase base;
    SRWLOCK         lock;
    (void       )(* fn_unlock   )(PSRWLOCK);
}; // xocRWLock
// Expected size: 16 bytes(on 64-bit) / 8bytes(on 32-bit)


xoc_stat_t xoc_rwlock_init(XOCRWLock * lock)
{
    XOC_ASSERT(lock != NULL);
    InitializeSRWLock(&lock->lock);
#   if defined(XOC_DEBUG)
    lock->fn_unlock = NULL;
#   endif
    return XOC_OK;
}


void xoc_rwlock_rdlock(XOCRWLock * lock)
{
    XOC_ASSERT(lock != NULL);
    XOC_ASSERT(lock->fn_unlock == NULL)
    lock->fn_unlock = AcquireSRWLockShared;
    AcquireSRWLockShared(&lock->lock);
}


void xoc_rwlock_wrlock(XOCRWLock * lock)
{
    XOC_ASSERT(lock != NULL);
    XOC_ASSERT(lock->fn_unlock == NULL);   
    lock->fn_unlock = ReleaseSRWLockExclusive;
    AcquireSRWLockExclusive(&lock->lock);
}


void xoc_rwlock_unlock(XOCRWLock * lock)
{
    XOC_ASSERT(lock != NULL);
    (*lock->fn_unlock)(&lock->lock);
#   ifdef XOC_DEBUG
    lock->fn_unlock = NULL;
#   endif // XOC_DEBUG
}


void xoc_rwlock_destory(XOCRWLock * lock)
{
    XOC_ASSERT(lock != NULL);
    (void)lock;
    return;
}


#endif

#if defined(__cplusplus)
}
#endif // __cplusplus
