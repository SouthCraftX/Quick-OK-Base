#pragma once

#include "../../atomic.h" // for debug

#if !defined(__XOC_ATOMIC_H__)
#   error "Never include this header file directly. Use <xoc/atomic.h> instead."
#endif

#define  __XOC_GNUC_ATOMIC_H__

typedef volatile xoc_int8_t  xoc_aint8_t;
typedef volatile xoc_int16_t xoc_aint16_t;
typedef volatile xoc_int32_t xoc_aint32_t;
typedef volatile xoc_int64_t xoc_aint64_t;

typedef volatile xoc_uint8_t  xoc_uint8_t;
typedef volatile xoc_uint16_t xoc_uint16_t;
typedef volatile xoc_uint32_t xoc_uint32_t;
typedef volatile xoc_uint64_t xoc_uint64_t;

typedef volatile xoc_intmax_t  xoc_aintmax_t;
typedef volatile xoc_uintmax_t xoc_auintmax_t;


#define XOC_ATOMIC_RELEXED   __ATOMIC_RELAXED
#define XOC_ATOMIC_CONSUME   __ATOMIC_CONSUME
#define XOC_ATOMIC_ACQUIRE   __ATOMIC_ACQUIRE
#define XOC_ATOMIC_RELEASE   __ATOMIC_RELEASE
#define XOC_ATOMIC_ACQ_REL   __ATOMIC_ACQ_REL
#define XOC_ATOMIC_SEQ_CST   __ATOMIC_SEQ_CST


#define xoc_atomic_load_explicit(ptr , order)  \
        __atomic_load(ptr , order)
#define xoc_atomic_store_explicit(ptr , val , order)  \
        __atomic_store(ptr , val , order)

#define xoc_atomic_add_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_add(ptr , val , order)
#define xoc_atomic_sub_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_sub(ptr , val , order)
#define xoc_atomic_and_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_and(ptr , val , order)
#define xoc_atomic_or_fetch_explicit(ptr , val , order)   \
        __atomic_fetch_or(ptr , val , order)
#define xoc_atomic_xor_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_xor(ptr , val , order)
#define xoc_atomic_nand_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_nand(ptr , val , order)
#define xoc_atomic_max_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_max(ptr , val , order)
#define xoc_atomic_min_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_min(ptr , val , order)

#define xoc_atomic_fetch_add_explicit(ptr , val , order)  \
        __atomic_fetch_add(ptr , val , order)
#define xoc_atomic_fetch_sub_explicit(ptr , val , order)  \
        __atomic_fetch_sub(ptr , val , order)
#define xoc_atomic_fetch_and_explicit(ptr , val , order)  \
        __atomic_fetch_and(ptr , val , order)
#define xoc_atomic_fetch_or_explicit(ptr , val , order)   \
        __atomic_fetch_or(ptr , val , order)
#define xoc_atomic_fetch_xor_explicit(ptr , val , order)  \
        __atomic_fetch_xor(ptr , val , order)
#define xoc_atomic_fetch_nand_explicit(ptr , val , order)  \
        __atomic_fetch_nand(ptr , val , order)
#define xoc_atomic_fetch_max_explicit(ptr , val , order)  \
        __atomic_fetch_max(ptr , val , order)
#define xoc_atomic_fetch_min_explicit(ptr , val , order)  \
        __atomic_fetch_min(ptr , val , order)

#define xoc_atomic_exchange_explicit(ptr , val , order)  \
        __atomic_exchange(ptr , val , order)

#define xoc_atomic_cas_weak_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        __atomic_compare_exchange_n(ptr , expected , desired , success_order , \
                                    failure_order)

#define xoc_atomic_cas_strong_explicit(/* ptr */ ptr , /* ptr */ expected , \
                              /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        __atomic_compare_exchange_strong(ptr , expected , desired , \
                                         success_order , failure_order)

#define xoc_atomic_cas_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        xoc_atomic_cas_strong(ptr , expected , desired , success_order , \
                                 failure_order)

#define xoc_atomic_load_implicit(ptr)  \
        __atomic_load(ptr , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_store_implicit(ptr , val)  \
        __atomic_store(ptr , val , XOC_ATOMIC_SEQ_CST)

#define xoc_atomic_add_fetch_implicit(ptr , val)  \
        __atomic_fetch_add(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_sub_fetch_implicit(ptr , val)  \
        __atomic_fetch_sub(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_and_fetch_implicit(ptr , val)  \
        __atomic_fetch_and(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_or_fetch_implicit(ptr , val)   \
        __atomic_fetch_or(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_xor_fetch_implicit(ptr , val)  \
        __atomic_fetch_xor(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_nand_fetch_implicit(ptr , val)  \
        __atomic_fetch_nand(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_max_fetch_implicit(ptr , val)  \
        __atomic_fetch_max(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_min_fetch_implicit(ptr , val)  \
        __atomic_fetch_min(ptr , val , XOC_ATOMIC_SEQ_CST)

#define xoc_atomic_fetch_add_implicit(ptr , val)  \
        __atomic_fetch_add(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_sub_implicit(ptr , val)  \
        __atomic_fetch_sub(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_and_implicit(ptr , val)  \
        __atomic_fetch_and(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_or_implicit(ptr , val)   \
        __atomic_fetch_or(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_xor_implicit(ptr , val)  \
        __atomic_fetch_xor(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_nand_implicit(ptr , val)  \
        __atomic_fetch_nand(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_max_implicit(ptr , val)  \
        __atomic_fetch_max(ptr , val , XOC_ATOMIC_SEQ_CST)
#define xoc_atomic_fetch_min_implicit(ptr , val)  \
        __atomic_fetch_min(ptr , val , XOC_ATOMIC_SEQ_CST)

#define xoc_atomic_exchange_implicit(ptr , val)  \
        __atomic_exchange(ptr , val , XOC_ATOMIC_SEQ_CST)

#define xoc_atomic_cas_weak_implicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired)  \
        xoc_atomic_cas_weak_explicit(ptr , expected , desired , \
                                        XOC_ATOMIC_SEQ_CST , \
                                        XOC_ATOMIC_SEQ_CST)

#define xoc_atomic_cas_strong_implicit(/* ptr */ ptr , /* ptr */ expected , \
                              /* ptr */ desired)  \
        xoc_atomic_cas_strong_explicit(ptr , expected , desired , \
                                          XOC_ATOMIC_SEQ_CST , \
                                          XOC_ATOMIC_SEQ_CST)

#define xoc_atomic_cas_implicit(/* ptr */ ptr , /* ptr */ expected , \
                                     /* ptr */ desired)  \
        xoc_atomic_cas_strong(ptr , expected , desired , \
                                 XOC_ATOMIC_SEQ_CST , XOC_ATOMIC_SEQ_CST)

#define xoc_is_lock_free(ptr)    __atomic_is_lock_free(sizeof(*ptr) , ptr)


