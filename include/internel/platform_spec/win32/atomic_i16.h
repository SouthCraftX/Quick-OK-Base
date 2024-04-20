#pragma once

#define __XOCEAN_WIN32_ATOMIC_I16_H__

#include "atomic.h" // for debug

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_add)(
    xocean_int16_t *    x ,
    xocean_int16_t      y
){
    register xocean_int32_t tmp = *x;
    return InterlockedAdd(&tmp , y);
    *x = tmp;
    return tmp;
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_set)(
    xocean_int16_t *    x ,
    xocean_int16_t      y
){
    return InterlockedExchange16(x, y);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_inc)(
    xocean_int16_t *    x
){
    return InterlockedIncrement16(x);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_dec)(
    xocean_int16_t *    x
){
    return InterlockedDecrement16(x);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_sub)(
    xocean_int16_t *    x ,
    xocean_int16_t      y
){
    return InterlockedExchangeAdd16(x, -y);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_cas)(
    xocean_int16_t *    x ,
    xocean_int16_t      oldval ,
    xocean_int16_t      newval
){
    return InterlockedCompareExchange16(x, oldval, newval);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_and)(
    xocean_int16_t *    x ,
    xocean_int16_t      y
){
    return InterlockedAnd16(x, y);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_or)(
    xocean_int16_t *    x ,
    xocean_int16_t      y
){
    return InterlockedOr16(x , y);
}

XOCEAN_FORCE_INLINE
xocean_int16_t
XOCEAN_IMPL(xocean_int16_xor)(
    xocean_int16_t *    x ,
    xocean_int16_t      y
){
    return InterlockedXor16(x, y);
}

