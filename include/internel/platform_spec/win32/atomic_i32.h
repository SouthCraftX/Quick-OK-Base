#pragma once
#define __XOC_WIN32_ATOMIC_I32_H__

#include "atomic.h" // for debug


XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_add)(
    xoc_int32_t *    x ,
    xoc_int32_t      y
){
    return InterlockedExchangeAdd((LONG volatile *)x , y);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_sub)(
    xoc_int32_t *    x ,
    xoc_int32_t      y
){
    return InterlockedExchangeAdd((LONG volatile *)x , -y);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_and)(
    xoc_int32_t *    x ,
    xoc_int32_t      y
){
    return InterlockedAnd((LONG volatile *)x , y);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_or)(
    xoc_int32_t *    x ,
    xoc_int32_t      y
){
    return InterlockedOr((LONG volatile *)x , y);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_xor)(
    xoc_int32_t *    x ,
    xoc_int32_t      y
){
    return InterlockedXor((LONG volatile *)x , y);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_cas)(
    xoc_int32_t *    x ,
    xoc_int32_t      old_val ,
    xoc_int32_t      new_val
){
    return InterlockedCompareExchange((LONG volatile *)x , old_val , new_val);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_inc)(
    xoc_int32_t *    x
){
    return InterlockedIncrement((LONG volatile *)x);
}

XOC_FORCE_INLINE
xoc_int32_t
XOC_IMPL(xoc_atomic_int32_dec)(
    xoc_int32_t *    x
){
    return InterlockedDecrement((LONG volatile *)x);
}

