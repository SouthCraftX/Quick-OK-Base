#pragma once

#define __XOCEAN_STDC_ATOMIC_H__

#include <stdatomic.h>

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