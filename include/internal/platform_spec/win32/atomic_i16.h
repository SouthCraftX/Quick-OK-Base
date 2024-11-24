#pragma once

#define __QO_WIN32_ATOMIC_I16_H__

#include "atomic.h" // for debug

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_add)(
    qo_int16_t *    x ,
    qo_int16_t      y
){
    register qo_int32_t tmp = *x;
    return InterlockedAdd(&tmp , y);
    *x = tmp;
    return tmp;
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_set)(
    qo_int16_t *    x ,
    qo_int16_t      y
){
    return InterlockedExchange16(x, y);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_inc)(
    qo_int16_t *    x
){
    return InterlockedIncrement16(x);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_dec)(
    qo_int16_t *    x
){
    return InterlockedDecrement16(x);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_sub)(
    qo_int16_t *    x ,
    qo_int16_t      y
){
    return InterlockedExchangeAdd16(x, -y);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_cas)(
    qo_int16_t *    x ,
    qo_int16_t      oldval ,
    qo_int16_t      newval
){
    return InterlockedCompareExchange16(x, oldval, newval);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_and)(
    qo_int16_t *    x ,
    qo_int16_t      y
){
    return InterlockedAnd16(x, y);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_or)(
    qo_int16_t *    x ,
    qo_int16_t      y
){
    return InterlockedOr16(x , y);
}

QO_FORCE_INLINE
qo_int16_t
QO_IMPL(qo_int16_xor)(
    qo_int16_t *    x ,
    qo_int16_t      y
){
    return InterlockedXor16(x, y);
}

