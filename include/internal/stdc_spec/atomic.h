#pragma once

#define __XOC_STDC_ATOMIC_H__

#if __STDC_VERSION__ < 201112L
#    error XOCLib: C++11 or later is required to implement atomic operations.
#endif

#include <stdatomic.h>

typedef _Atomic(xoc_fp32_t)          xoc_afp32_t;
typedef _Atomic(xoc_fp64_t)          xoc_afp64_t;
        
typedef atomic_int_least8_t             xoc_aint8_t;
typedef atomic_int_least16_t            xoc_aint16_t;
typedef atomic_int_least32_t            xoc_aint32_t;
typedef atomic_int_least64_t            xoc_aint64_t;

typedef atomic_uint_least8_t           xoc_auint8_t;
typedef atomic_uint_least16_t          xoc_auint16_t;
typedef atomic_uint_least32_t          xoc_auint32_t;
typedef atomic_uint_least64_t          xoc_auint64_t;

typedef _Atomic(xoc_flag8_t)         xoc_aflag8_t;
typedef _Atomic(xoc_flag16_t)        xoc_aflag16_t;
typedef _Atomic(xoc_flag32_t)        xoc_aflag32_t;
typedef _Atomic(xoc_flag64_t)        xoc_aflag64_t;

typedef _Atomic(xoc_size_t)          xoc_asize_t;
typedef _Atomic(xoc_ssize_t)         xoc_assize_t;

#define XOC_ATOMIC_RELEXED  memory_order_relaxed
#define XOC_ATOMIC_CONSUME  memory_order_consume
#define XOC_ATOMIC_ACQUIRE  memory_order_acquire
#define XOC_ATOMIC_RELEASE  memory_order_release
#define XOC_ATOMIC_ACQ_REL  memory_order_acq_rel
#define XOC_ATOMIC_SEQ_CST  memory_order_seq_cst

#define xoc_atomic_load_explicit(ptr , order) \
        atomic_load_explicit(ptr , order)
#define xoc_atomic_store_explicit(ptr , val , order) \
        atomic_store_explicit(ptr , val , order)

#define xoc_atomic_exchange_explicit(ptr , val , order) \
        atomic_exchange_explicit(ptr , val , order)
#define xoc_atomic_cas_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \  
        atomic_compare_exchange_strong_explicit(ptr , expected , desired , success , failure)

#define xoc_atomic_cas_weak_explicit(/* ptr */ ptr , /* ptr */ expected , \
                               /* ptr */ desired , /* flag */ success_order , \
                               /* flag */ failure_order)  \
        atomic_compare_exchange_weak_explicit(ptr , expected , desired , success , failure)

#define xoc_atomic_fetch_add_explicit(ptr , val , order) \
        atomic_fetch_add_explicit(ptr , val , order)
#define xoc_atomic_fetch_sub_explicit(ptr , val , order) \
        atomic_fetch_sub_explicit(ptr , val , order)
#define xoc_atomic_fetch_or_explicit(ptr , val , order) \
        atomic_fetch_or_explicit(ptr , val , order)
#define xoc_atomic_fetch_and_explicit(ptr , val , order) \
        atomic_fetch_and_explicit(ptr , val , order)
#define xoc_atomic_fetch_xor_explicit(ptr , val , order) \
        atomic_fetch_xor_explicit(ptr , val , order)
#define xoc_atomic_fetch_nand_explicit(ptr , val , order) \
        atomic_fetch_nand_explicit(ptr , val , order)
#define xoc_atomic_fetch_min_explicit(ptr , val , order) \
        atomic_fetch_min_explicit(ptr , val , order)
#define xoc_atomic_fetch_max_explicit(ptr , val , order) \
        atomic_fetch_max_explicit(ptr , val , order)

#define xoc_is_lock_free(ptr)    atomic_is_lock_free(ptr)