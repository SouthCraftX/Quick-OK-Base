#pragma once

#define __XOCEAN_STDC_ATOMIC_H__

#if __STDC_VERSION__ < 201112L
#    error XOceanLib: C++11 or later is required to implement atomic operations.
#endif

#include <stdatomic.h>

typedef _Atomic(xocean_fp32_t)          xocean_afp32_t;
typedef _Atomic(xocean_fp64_t)          xocean_afp64_t;
        
typedef atomic_int_least8_t             xocean_aint8_t;
typedef atomic_int_least16_t            xocean_aint16_t;
typedef atomic_int_least32_t            xocean_aint32_t;
typedef atomic_int_least64_t            xocean_aint64_t;

typedef atomic_uint_least8_t           xocean_auint8_t;
typedef atomic_uint_least16_t          xocean_auint16_t;
typedef atomic_uint_least32_t          xocean_auint32_t;
typedef atomic_uint_least64_t          xocean_auint64_t;

typedef _Atomic(xocean_flag8_t)         xocean_aflag8_t;
typedef _Atomic(xocean_flag16_t)        xocean_aflag16_t;
typedef _Atomic(xocean_flag32_t)        xocean_aflag32_t;
typedef _Atomic(xocean_flag64_t)        xocean_aflag64_t;

typedef _Atomic(xocean_size_t)          xocean_asize_t;
typedef _Atomic(xocean_ssize_t)         xocean_assize_t;

#define XOCEAN_ATOMIC_RELEXED  memory_order_relaxed
#define XOCEAN_ATOMIC_CONSUME  memory_order_consume
#define XOCEAN_ATOMIC_ACQUIRE  memory_order_acquire
#define XOCEAN_ATOMIC_RELEASE  memory_order_release
#define XOCEAN_ATOMIC_ACQ_REL  memory_order_acq_rel
#define XOCEAN_ATOMIC_SEQ_CST  memory_order_seq_cst

#define xocean_atomic_load_explicit(ptr , order) \
        atomic_load_explicit(ptr , order)
#define xocean_atomic_store_explicit(ptr , val , order) \
        atomic_store_explicit(ptr , val , order)

#define xocean_atomic_exchange_explicit(ptr , val , order) \
        atomic_exchange_explicit(ptr , val , order)
#define xocean_atomic_cas_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \  
        atomic_compare_exchange_strong_explicit(ptr , expected , desired , success , failure)

#define xocean_atomic_cas_weak_explicit(/* ptr */ ptr , /* ptr */ expected , \
                               /* ptr */ desired , /* flag */ success_order , \
                               /* flag */ failure_order)  \
        atomic_compare_exchange_weak_explicit(ptr , expected , desired , success , failure)

#define xocean_atomic_fetch_add_explicit(ptr , val , order) \
        atomic_fetch_add_explicit(ptr , val , order)
#define xocean_atomic_fetch_sub_explicit(ptr , val , order) \
        atomic_fetch_sub_explicit(ptr , val , order)
#define xocean_atomic_fetch_or_explicit(ptr , val , order) \
        atomic_fetch_or_explicit(ptr , val , order)
#define xocean_atomic_fetch_and_explicit(ptr , val , order) \
        atomic_fetch_and_explicit(ptr , val , order)
#define xocean_atomic_fetch_xor_explicit(ptr , val , order) \
        atomic_fetch_xor_explicit(ptr , val , order)
#define xocean_atomic_fetch_nand_explicit(ptr , val , order) \
        atomic_fetch_nand_explicit(ptr , val , order)
#define xocean_atomic_fetch_min_explicit(ptr , val , order) \
        atomic_fetch_min_explicit(ptr , val , order)
#define xocean_atomic_fetch_max_explicit(ptr , val , order) \
        atomic_fetch_max_explicit(ptr , val , order)

#define xocean_is_lock_free(ptr)    atomic_is_lock_free(ptr)