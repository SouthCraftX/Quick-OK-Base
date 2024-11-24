#pragma once

#include "../../atomic.h" // for debug

#if !defined(__QO_ATOMIC_H__)
#   error "Never include this header file directly. Use <qo/atomic.h> instead."
#endif

#define  __QO_GNUC_ATOMIC_H__

typedef volatile qo_int8_t  qo_aint8_t;
typedef volatile qo_int16_t qo_aint16_t;
typedef volatile qo_int32_t qo_aint32_t;
typedef volatile qo_int64_t qo_aint64_t;

typedef volatile qo_uint8_t  qo_uint8_t;
typedef volatile qo_uint16_t qo_uint16_t;
typedef volatile qo_uint32_t qo_uint32_t;
typedef volatile qo_uint64_t qo_uint64_t;

typedef volatile qo_intmax_t  qo_aintmax_t;
typedef volatile qo_uintmax_t qo_auintmax_t;


#define QO_ATOMIC_RELEXED   __ATOMIC_RELAXED
#define QO_ATOMIC_CONSUME   __ATOMIC_CONSUME
#define QO_ATOMIC_ACQUIRE   __ATOMIC_ACQUIRE
#define QO_ATOMIC_RELEASE   __ATOMIC_RELEASE
#define QO_ATOMIC_ACQ_REL   __ATOMIC_ACQ_REL
#define QO_ATOMIC_SEQ_CST   __ATOMIC_SEQ_CST


#define qo_atomic_load_explicit(ptr , order)  \
        __atomic_load(ptr , order)
#define qo_atomic_store_explicit(ptr , val , order)  \
        __atomic_store(ptr , val , order)

#define qo_atomic_add_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_add(ptr , val , order)
#define qo_atomic_sub_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_sub(ptr , val , order)
#define qo_atomic_and_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_and(ptr , val , order)
#define qo_atomic_or_fetch_explicit(ptr , val , order)   \
        __atomic_fetch_or(ptr , val , order)
#define qo_atomic_xor_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_xor(ptr , val , order)
#define qo_atomic_nand_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_nand(ptr , val , order)
#define qo_atomic_max_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_max(ptr , val , order)
#define qo_atomic_min_fetch_explicit(ptr , val , order)  \
        __atomic_fetch_min(ptr , val , order)

#define qo_atomic_fetch_add_explicit(ptr , val , order)  \
        __atomic_fetch_add(ptr , val , order)
#define qo_atomic_fetch_sub_explicit(ptr , val , order)  \
        __atomic_fetch_sub(ptr , val , order)
#define qo_atomic_fetch_and_explicit(ptr , val , order)  \
        __atomic_fetch_and(ptr , val , order)
#define qo_atomic_fetch_or_explicit(ptr , val , order)   \
        __atomic_fetch_or(ptr , val , order)
#define qo_atomic_fetch_xor_explicit(ptr , val , order)  \
        __atomic_fetch_xor(ptr , val , order)
#define qo_atomic_fetch_nand_explicit(ptr , val , order)  \
        __atomic_fetch_nand(ptr , val , order)
#define qo_atomic_fetch_max_explicit(ptr , val , order)  \
        __atomic_fetch_max(ptr , val , order)
#define qo_atomic_fetch_min_explicit(ptr , val , order)  \
        __atomic_fetch_min(ptr , val , order)

#define qo_atomic_exchange_explicit(ptr , val , order)  \
        __atomic_exchange(ptr , val , order)

#define qo_atomic_cas_weak_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        __atomic_compare_exchange_n(ptr , expected , desired , success_order , \
                                    failure_order)

#define qo_atomic_cas_strong_explicit(/* ptr */ ptr , /* ptr */ expected , \
                              /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        __atomic_compare_exchange_strong(ptr , expected , desired , \
                                         success_order , failure_order)

#define qo_atomic_cas_explicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired , /* flag */ success_order , \
                          /* flag */ failure_order)  \
        qo_atomic_cas_strong(ptr , expected , desired , success_order , \
                                 failure_order)

#define qo_atomic_load_implicit(ptr)  \
        __atomic_load(ptr , QO_ATOMIC_SEQ_CST)
#define qo_atomic_store_implicit(ptr , val)  \
        __atomic_store(ptr , val , QO_ATOMIC_SEQ_CST)

#define qo_atomic_add_fetch_implicit(ptr , val)  \
        __atomic_fetch_add(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_sub_fetch_implicit(ptr , val)  \
        __atomic_fetch_sub(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_and_fetch_implicit(ptr , val)  \
        __atomic_fetch_and(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_or_fetch_implicit(ptr , val)   \
        __atomic_fetch_or(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_xor_fetch_implicit(ptr , val)  \
        __atomic_fetch_xor(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_nand_fetch_implicit(ptr , val)  \
        __atomic_fetch_nand(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_max_fetch_implicit(ptr , val)  \
        __atomic_fetch_max(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_min_fetch_implicit(ptr , val)  \
        __atomic_fetch_min(ptr , val , QO_ATOMIC_SEQ_CST)

#define qo_atomic_fetch_add_implicit(ptr , val)  \
        __atomic_fetch_add(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_sub_implicit(ptr , val)  \
        __atomic_fetch_sub(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_and_implicit(ptr , val)  \
        __atomic_fetch_and(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_or_implicit(ptr , val)   \
        __atomic_fetch_or(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_xor_implicit(ptr , val)  \
        __atomic_fetch_xor(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_nand_implicit(ptr , val)  \
        __atomic_fetch_nand(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_max_implicit(ptr , val)  \
        __atomic_fetch_max(ptr , val , QO_ATOMIC_SEQ_CST)
#define qo_atomic_fetch_min_implicit(ptr , val)  \
        __atomic_fetch_min(ptr , val , QO_ATOMIC_SEQ_CST)

#define qo_atomic_exchange_implicit(ptr , val)  \
        __atomic_exchange(ptr , val , QO_ATOMIC_SEQ_CST)

#define qo_atomic_cas_weak_implicit(/* ptr */ ptr , /* ptr */ expected , \
                          /* ptr */ desired)  \
        qo_atomic_cas_weak_explicit(ptr , expected , desired , \
                                        QO_ATOMIC_SEQ_CST , \
                                        QO_ATOMIC_SEQ_CST)

#define qo_atomic_cas_strong_implicit(/* ptr */ ptr , /* ptr */ expected , \
                              /* ptr */ desired)  \
        qo_atomic_cas_strong_explicit(ptr , expected , desired , \
                                          QO_ATOMIC_SEQ_CST , \
                                          QO_ATOMIC_SEQ_CST)

#define qo_atomic_cas_implicit(/* ptr */ ptr , /* ptr */ expected , \
                                     /* ptr */ desired)  \
        qo_atomic_cas_strong(ptr , expected , desired , \
                                 QO_ATOMIC_SEQ_CST , QO_ATOMIC_SEQ_CST)

#define qo_is_lock_free(ptr)    __atomic_is_lock_free(sizeof(*ptr) , ptr)


