#pragma once

#define __QO_STDC_ATOMIC_H__

#if __STDC_VERSION__ < 201112L
#    error QOLib: C++11 or later is required to implement atomic operations.
#endif

#include <stdatomic.h>

typedef _Atomic(qo_fp32_t)          qo_afp32_t;
typedef _Atomic(qo_fp64_t)          qo_afp64_t;
        
typedef atomic_int_least8_t             qo_aint8_t;
typedef atomic_int_least16_t            qo_aint16_t;
typedef atomic_int_least32_t            qo_aint32_t;
typedef atomic_int_least64_t            qo_aint64_t;

typedef atomic_uint_least8_t           qo_auint8_t;
typedef atomic_uint_least16_t          qo_auint16_t;
typedef atomic_uint_least32_t          qo_auint32_t;
typedef atomic_uint_least64_t          qo_auint64_t;

typedef _Atomic(qo_flag8_t)         qo_aflag8_t;
typedef _Atomic(qo_flag16_t)        qo_aflag16_t;
typedef _Atomic(qo_flag32_t)        qo_aflag32_t;
typedef _Atomic(qo_flag64_t)        qo_aflag64_t;

typedef _Atomic(qo_size_t)          qo_asize_t;
typedef _Atomic(qo_ssize_t)         qo_assize_t;

#define QO_ATOMIC_RELEXED  memory_order_relaxed
#define QO_ATOMIC_CONSUME  memory_order_consume
#define QO_ATOMIC_ACQUIRE  memory_order_acquire
#define QO_ATOMIC_RELEASE  memory_order_release
#define QO_ATOMIC_ACQ_REL  memory_order_acq_rel
#define QO_ATOMIC_SEQ_CST  memory_order_seq_cst

#define qo_atomic_load_explicit(ptr , order) \
        atomic_load_explicit(ptr , order)
#define qo_atomic_store_explicit(ptr , val , order) \
        atomic_store_explicit(ptr , val , order)

#define qo_atomic_exchange_explicit(ptr , val , order) \
        atomic_exchange_explicit(ptr , val , order)
#define qo_atomic_cas_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \  
        atomic_compare_exchange_strong_explicit(ptr , expected , desired , success , failure)

#define qo_atomic_cas_weak_explicit(/* ptr */ ptr , /* ptr */ expected , \
                               /* ptr */ desired , /* flag */ success_order , \
                               /* flag */ failure_order)  \
        atomic_compare_exchange_weak_explicit(ptr , expected , desired , success , failure)

#define qo_atomic_fetch_add_explicit(ptr , val , order) \
        atomic_fetch_add_explicit(ptr , val , order)
#define qo_atomic_fetch_sub_explicit(ptr , val , order) \
        atomic_fetch_sub_explicit(ptr , val , order)
#define qo_atomic_fetch_or_explicit(ptr , val , order) \
        atomic_fetch_or_explicit(ptr , val , order)
#define qo_atomic_fetch_and_explicit(ptr , val , order) \
        atomic_fetch_and_explicit(ptr , val , order)
#define qo_atomic_fetch_xor_explicit(ptr , val , order) \
        atomic_fetch_xor_explicit(ptr , val , order)
#define qo_atomic_fetch_nand_explicit(ptr , val , order) \
        atomic_fetch_nand_explicit(ptr , val , order)
#define qo_atomic_fetch_min_explicit(ptr , val , order) \
        atomic_fetch_min_explicit(ptr , val , order)
#define qo_atomic_fetch_max_explicit(ptr , val , order) \
        atomic_fetch_max_explicit(ptr , val , order)

#define qo_is_lock_free(ptr)    atomic_is_lock_free(ptr)