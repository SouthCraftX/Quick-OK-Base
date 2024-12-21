#pragma once
#define __QO_POSIX_SEMAPHORA_H__

// for debug
#include "include/semaphore.h"

#if !defined(__QO_SEMAPHORA_H__)
#   error Never include this header directly. Use semaphore.h instead.
#endif

#include <semaphore.h>
#include <errno.h>

struct _QO_Semaphora
{
    sem_t sem;
};

QO_PURE
qo_stat_t
__qo_sem_opening_error()
{
    switch (errno)
    {
        case EACCES:
            return QO_PERMISSION_DENIED;
        case EEXIST:
            return QO_ALREADY_EXISTS;
        case ENAMETOOLONG:
            return QO_TOO_LONG;
        case EINVAL:
            return QO_INVALID_ARG;
        case EMFILE:
        case ENFILE:
            return QO_NO_RESOURCE;
        case ENOENT:
            return QO_NOT_FOUND;
        case ENOMEM:
            return QO_OUT_OF_MEMORY;
        default:
            return QO_UNKNOWN_ERROR;    
    }
}

QO_PURE
qo_stat_t
__qo_sem_posting_error()
{
    switch (errno) {
        case EINVAL:
            return QO_INVALID_HANDLE;
        case EOVERFLOW:
            return QO_LIMIT_REACHED;
        default:
            return QO_UNKNOWN_ERROR;    
    }
}

QO_PURE
qo_stat_t
__qo_sem_waiting_error()
{
    switch (errno)
    {
        case EAGAIN:
            return 
        case EINTR:
            return QO_SIGNAL_INTERRUPTED;
        case EINVAL:
            return QO_INVALID_ARG;
        case ETIMEDOUT:
            return QO_TIMEDOUT;    
        default:
            return QO_UNKNOWN_ERROR;    
    }
}

qo_stat_t
QO_IMPL(qo_semaphora_init)(
    QO_Semaphore *  p_semphora ,
    qo_size_t       count
){
    sem_init(&p_semphora->sem , 0 , count);
}

void
QO_IMPL(qo_semaphora_destroy)(
    QO_Semaphore *  p_semphora
){
    sem_destroy(&p_semphora->sem);
}

qo_stat_t
QO_IMPL(qo_semaphora_wait)(
    QO_Semaphore *  p_semphora
){
    sem_wait(&p_semphora->sem);
}

void
QO_IMPL(qo_semaphora_post)(
    QO_Semaphore *  p_semphora
){
    sem_post(&p_semphora->sem);
}

