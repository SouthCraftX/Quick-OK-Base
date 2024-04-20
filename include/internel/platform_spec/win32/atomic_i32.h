#pragma once
#define __XOCEAN_WIN32_ATOMIC_I32_H__

#include "atomic.h" // for debug


XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_add)(
    xocean_int32_t *    x ,
    xocean_int32_t      y
){
    return InterlockedExchangeAdd((LONG volatile *)x , y);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_sub)(
    xocean_int32_t *    x ,
    xocean_int32_t      y
){
    return InterlockedExchangeAdd((LONG volatile *)x , -y);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_and)(
    xocean_int32_t *    x ,
    xocean_int32_t      y
){
    return InterlockedAnd((LONG volatile *)x , y);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_or)(
    xocean_int32_t *    x ,
    xocean_int32_t      y
){
    return InterlockedOr((LONG volatile *)x , y);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_xor)(
    xocean_int32_t *    x ,
    xocean_int32_t      y
){
    return InterlockedXor((LONG volatile *)x , y);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_cas)(
    xocean_int32_t *    x ,
    xocean_int32_t      old_val ,
    xocean_int32_t      new_val
){
    return InterlockedCompareExchange((LONG volatile *)x , old_val , new_val);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_inc)(
    xocean_int32_t *    x
){
    return InterlockedIncrement((LONG volatile *)x);
}

XOCEAN_FORCE_INLINE
xocean_int32_t
XOCEAN_IMPL(xocean_atomic_int32_dec)(
    xocean_int32_t *    x
){
    return InterlockedDecrement((LONG volatile *)x);
}

