#pragma once

#include "../../atomic.h" // for debug

#if !defined(__XOCEAN_ATOMIC_H__)
#   error "Never include this header file directly. Use <xocean/atomic.h> instead."
#endif

#define  __XOCEAN_GNUC_ATOMIC_H__

typedef volatile xocean_int8_t  xocean_aint8_t;
typedef volatile xocean_int16_t xocean_aint16_t;
typedef volatile xocean_int32_t xocean_aint32_t;
typedef volatile xocean_int64_t xocean_aint64_t;

typedef volatile xocean_uint8_t  xocean_uint8_t;
typedef volatile xocean_uint16_t xocean_uint16_t;
typedef volatile xocean_uint32_t xocean_uint32_t;
typedef volatile xocean_uint64_t xocean_uint64_t;

typedef volatile xocean_intmax_t  xocean_aintmax_t;
typedef volatile xocean_uintmax_t xocean_auintmax_t;


#define XOCEAN_ATOMIC_RELEXED   __ATOMIC_RELAXED
#define XOCEAN_ATOMIC_CONSUME   __ATOMIC_CONSUME
#define XOCEAN_ATOMIC_ACQUIRE   __ATOMIC_ACQUIRE
#define XOCEAN_ATOMIC_RELEASE   __ATOMIC_RELEASE
#define XOCEAN_ATOMIC_ACQ_REL   __ATOMIC_ACQ_REL
#define XOCEAN_ATOMIC_SEQ_CST   __ATOMIC_SEQ_CST


#define xocean_atomic_load_explicit(ptr , order)  \
        __atomic_load(ptr, order)
#define xocean_atomic_store_explicit(ptr , val , order)  \
        __atomic_store(ptr, val, order)

#define xocean_atomic_add_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_add(ptr, val, order)
#define xocean_atomic_sub_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_sub(ptr, val, order)
#define xocean_atomic_and_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_and(ptr, val, order)
#define xocean_atomic_or_fetch_explicit(ptr , val , order)   \
        __atomic_fetch_or(ptr, val, order)
#define xocean_atomic_xor_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_xor(ptr, val, order)
#define xocean_atomic_nand_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_nand(ptr, val, order)
#define xocean_atomic_max_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_max(ptr, val, order)
#define xocean_atomic_min_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_min(ptr, val, order)

#define xocean_atomic_fetch_add_explicit(ptr , val , order)  \
        __atomic_fetch_add(ptr, val, order)
#define xocean_atomic_fetch_sub_explicit(ptr , val , order)  \
        __atomic_fetch_sub(ptr, val, order)
#define xocean_atomic_fetch_and_explicit(ptr , val , order)  \
        __atomic_fetch_and(ptr, val, order)
#define xocean_atomic_fetch_or_explicit(ptr , val , order)   \
        __atomic_fetch_or(ptr, val, order)
#define xocean_atomic_fetch_xor_explicit(ptr , val , order)  \
        __atomic_fetch_xor(ptr, val, order)
#define xocean_atomic_fetch_nand_explicit(ptr , val , order)  \
        __atomic_fetch_nand(ptr, val, order)
#define xocean_atomic_fetch_max_explicit(ptr , val , order)  \
        __atomic_fetch_max(ptr, val, order)
#define xocean_atomic_fetch_min_explicit(ptr , val , order)  \
        __atomic_fetch_min(ptr, val, order)

#define xocean_atomic_exchange_explicit(ptr , val , order)  \
        __atomic_exchange(ptr, val, order)

#define xocean_atomic_cas_weak_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        __atomic_compare_exchange_n(ptr, expected, desired, success, failure)

#define xocean_atomic_cas_strong_explicit(/* ptr */ ptr , /* ptr */ expected , \
                              /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        __atomic_compare_exchange_strong(ptr, expected, desired, success, failure)

#define xocean_atomic_cas_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        xocean_atomic_cas_strong(ptr, expected, desired, success_order, failure_order)

#define xocean_atomic_load_noexplicit(ptr)  \
        __atomic_load(ptr, XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_store_noexplicit(ptr , val)  \
        __atomic_store(ptr , val , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_atomic_add_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_add(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_sub_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_sub(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_and_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_and(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_or_fetch_noexplicit(ptr , val)   \
        __atomic_fetch_or(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_xor_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_xor(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_nand_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_nand(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_max_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_max(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_min_fetch_noexplicit(ptr , val)  \
        __atomic_fetch_min(ptr , val , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_atomic_fetch_add_noexplicit(ptr , val)  \
        __atomic_fetch_add(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_sub_noexplicit(ptr , val)  \
        __atomic_fetch_sub(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_and_noexplicit(ptr , val)  \
        __atomic_fetch_and(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_or_noexplicit(ptr , val)   \
        __atomic_fetch_or(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_xor_noexplicit(ptr , val)  \
        __atomic_fetch_xor(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_nand_noexplicit(ptr , val)  \
        __atomic_fetch_nand(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_max_noexplicit(ptr , val)  \
        __atomic_fetch_max(ptr , val , XOCEAN_ATOMIC_SEQ_CST)
#define xocean_atomic_fetch_min_noexplicit(ptr , val)  \
        __atomic_fetch_min(ptr , val , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_atomic_exchange_noexplicit(ptr , val)  \
        __atomic_exchange(ptr , val , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_atomic_cas_weak_noexplicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired)  \
        xocean_atomic_cas_weak_explicit(ptr , expected , desired , XOCEAN_ATOMIC_SEQ_CST , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_atomic_cas_strong_noexplicit(/* ptr */ ptr , /* ptr */ expected , \
                              /* ptr */ desired)  \
        xocean_atomic_cas_strong_explicit(ptr , expected , desired , XOCEAN_ATOMIC_SEQ_CST , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_atomic_cas_noexplicit(/* ptr */ ptr , /* ptr */ expected , \
                                     /* ptr */ desired)  \
        xocean_atomic_cas_strong(ptr , expected , desired , XOCEAN_ATOMIC_SEQ_CST , XOCEAN_ATOMIC_SEQ_CST)

#define xocean_is_lock_free(ptr)    __atomic_is_lock_free(sizeof(*ptr) , ptr)


