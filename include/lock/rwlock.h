#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "../base.h"
#include "../memory.h"

struct qoRWLock;
typedef struct qoRWLock QORWLock;

QORWLock * qo_rwlock_new();
QORWLock * qo_rwlock_new_ex(
    qo_stat_t * stat
);
void qo_rwlock_delete(
    QORWLock * lock
);

qo_stat_t qo_rwlock_init(
    QORWLock * lock
);

void qo_rwlock_rdlock(
    QORWLock * lock
);

void qo_rwlock_wrlock(
    QORWLock * lock
);

void qo_rwlock_unlock(
    QORWLock * lock
);

void qo_rwlock_destroy(
    QORWLock * lock
);

 
QORWLock * qo_rwlock_new()
{
    qo_stat_t stat;
    return qo_rwlock_new_ex(&stat);
}

 
QORWLock * qo_rwlock_new_ex(qo_stat_t * stat)
{
    QO_ASSERT(stat);
    QORWLock * ret = (QORWLock*)mi_malloc_small(sizeof(QORWLock));
    if (QO_LIKELY(ret))
    {
        *stat = qo_rwlock_init(ret);
        return ret;
    }
    *stat = QO_OUT_OF_MEMORY;
    return NULL;
}


void qo_rwlock_delete(QORWLock * lock)
{
    qo_rwlock_destroy(lock);
    mi_free(lock);
}

#if QO_PLATFORM(POSIX)
#   include <pthread.h>
struct qoRWLock
{
    QOeanClassBase     base;
    pthread_rwlock_t    rwlock;
};


qo_stat_t qo_rwlock_init(QORWLock * lock)
{
    int ret = pthread_rwlock_init(&lock->rwlock, NULL);
    if (QO_UNLIKELY(ret))
    {
        switch(ret)
        {
            case EAGAIN:
                return QO_NO_RESOURCE;
            case EINVAL:
                return QO_INVALID_ARGUMENT;
            case ENOMEM:
                return QO_OUT_OF_MEMORY;
            default:
                return QO_ERR_UNKNOWN;
        }
    }
    return QO_OK;
}


void qo_rwlock_rdlock(QORWLock * lock)
{
    int ret = pthread_rwlock_rdlock(&lock->rwlock);
    QO_ASSERT(ret == 0); // Deadly lock, too many lock acquire or invaild argument
    (void)ret;
}


void qo_rwlock_wrlock(QORWLock * lock)
{
    int ret = pthread_rwlock_wrlock(&lock->rwlock);
    QO_ASSERT(ret == 0); // Deadly lock or invaild argument
    (void)ret;
}


void qo_rwlock_unlock(QORWLock * lock)
{
    int ret = pthread_rwlock_unlock(&lock->rwlock);
    QO_ASSERT(ret == 0); // Trying to unlock a not-locked lock or invaild argument
    (void)ret;
}


void qo_rwlock_destroy(QORWLock * lock)
{
    int ret = pthread_rwlock_destroy(&lock->rwlock);
    QO_ASSERT(ret == 0); // Trying to destroy a locked lock or invaild argument
    (void)ret;
}
#elif QO_PLATFORM(WINDOWS)
#   include <synchapi.h>

struct qoRWLock
{
    QOClassBase base;
    SRWLOCK         lock;
    (void       )(* fn_unlock   )(PSRWLOCK);
}; // qoRWLock
// Expected size: 16 bytes(on 64-bit) / 8bytes(on 32-bit)


qo_stat_t qo_rwlock_init(QORWLock * lock)
{
    QO_ASSERT(lock != NULL);
    InitializeSRWLock(&lock->lock);
#   if defined(QO_DEBUG)
    lock->fn_unlock = NULL;
#   endif
    return QO_OK;
}


void qo_rwlock_rdlock(QORWLock * lock)
{
    QO_ASSERT(lock != NULL);
    QO_ASSERT(lock->fn_unlock == NULL)
    lock->fn_unlock = AcquireSRWLockShared;
    AcquireSRWLockShared(&lock->lock);
}


void qo_rwlock_wrlock(QORWLock * lock)
{
    QO_ASSERT(lock != NULL);
    QO_ASSERT(lock->fn_unlock == NULL);   
    lock->fn_unlock = ReleaseSRWLockExclusive;
    AcquireSRWLockExclusive(&lock->lock);
}


void qo_rwlock_unlock(QORWLock * lock)
{
    QO_ASSERT(lock != NULL);
    (*lock->fn_unlock)(&lock->lock);
#   ifdef QO_DEBUG
    lock->fn_unlock = NULL;
#   endif // QO_DEBUG
}


void qo_rwlock_destory(QORWLock * lock)
{
    QO_ASSERT(lock != NULL);
    (void)lock;
    return;
}


#endif

#if defined(__cplusplus)
}
#endif // __cplusplus
