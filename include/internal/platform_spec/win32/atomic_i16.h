#pragma once

#define __XOC_WIN32_ATOMIC_I16_H__

#include "atomic.h" // for debug

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_add)(
    xoc_int16_t *    x ,
    xoc_int16_t      y
){
    register xoc_int32_t tmp = *x;
    return InterlockedAdd(&tmp , y);
    *x = tmp;
    return tmp;
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_set)(
    xoc_int16_t *    x ,
    xoc_int16_t      y
){
    return InterlockedExchange16(x, y);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_inc)(
    xoc_int16_t *    x
){
    return InterlockedIncrement16(x);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_dec)(
    xoc_int16_t *    x
){
    return InterlockedDecrement16(x);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_sub)(
    xoc_int16_t *    x ,
    xoc_int16_t      y
){
    return InterlockedExchangeAdd16(x, -y);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_cas)(
    xoc_int16_t *    x ,
    xoc_int16_t      oldval ,
    xoc_int16_t      newval
){
    return InterlockedCompareExchange16(x, oldval, newval);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_and)(
    xoc_int16_t *    x ,
    xoc_int16_t      y
){
    return InterlockedAnd16(x, y);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_or)(
    xoc_int16_t *    x ,
    xoc_int16_t      y
){
    return InterlockedOr16(x , y);
}

XOC_FORCE_INLINE
xoc_int16_t
XOC_IMPL(xoc_int16_xor)(
    xoc_int16_t *    x ,
    xoc_int16_t      y
){
    return InterlockedXor16(x, y);
}

