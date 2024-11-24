#pragma once
#define __QO_WIN32_ATOMIC_I32_H__

#include "atomic.h" // for debug


QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_add)(
    qo_int32_t *    x ,
    qo_int32_t      y
){
    return InterlockedExchangeAdd((LONG volatile *)x , y);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_sub)(
    qo_int32_t *    x ,
    qo_int32_t      y
){
    return InterlockedExchangeAdd((LONG volatile *)x , -y);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_and)(
    qo_int32_t *    x ,
    qo_int32_t      y
){
    return InterlockedAnd((LONG volatile *)x , y);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_or)(
    qo_int32_t *    x ,
    qo_int32_t      y
){
    return InterlockedOr((LONG volatile *)x , y);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_xor)(
    qo_int32_t *    x ,
    qo_int32_t      y
){
    return InterlockedXor((LONG volatile *)x , y);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_cas)(
    qo_int32_t *    x ,
    qo_int32_t      old_val ,
    qo_int32_t      new_val
){
    return InterlockedCompareExchange((LONG volatile *)x , old_val , new_val);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_inc)(
    qo_int32_t *    x
){
    return InterlockedIncrement((LONG volatile *)x);
}

QO_FORCE_INLINE
qo_int32_t
QO_IMPL(qo_atomic_int32_dec)(
    qo_int32_t *    x
){
    return InterlockedDecrement((LONG volatile *)x);
}

