#pragma once
#define __QO_ATOMIC_GENERIC_H__

#if !(defined(__QO_STDC_ATOMIC_H__) || defined(__QO_GNUC_ATOMIC_H__))
#   error "Never include this header file directly. Use <qo/atomic.h> instead."
#endif

// Generic macro tricks refer to:
// https://blog.csdn.net/fshngrmng/article/details/119572189

#define __QO_ATOMIC_2OR3_ARGS_SELECT(ptr , val , order , target , ...) target
#define __QO_ATOMIC_CAS_SELECT(ptr , expected , desired , success , \ 
                                   failure , target , ...) target

#define qo_atomic_add_fetch(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_add_fetch_explicit ,                      \
            qo_atomic_add_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_sub_fetch(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_sub_fetch_explicit ,                      \
            qo_atomic_sub_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_and_fetch(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_and_fetch_explicit ,                      \
            qo_atomic_and_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_or_fetch(...)                                 \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_or_fetch_explicit ,                       \
            qo_atomic_or_fetch_implicit                       \
        ) (__VA_ARGS__)         

#define qo_atomic_xor_fetch(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_xor_fetch_explicit ,                      \
            qo_atomic_xor_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_nand_fetch(...)                               \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_nand_fetch_explicit ,                     \
            qo_atomic_nand_fetch_implicit                     \
        ) (__VA_ARGS__)         

#define qo_atomic_max_fetch(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_max_fetch_explicit ,                      \
            qo_atomic_max_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_min_fetch(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_min_fetch_explicit ,                      \
            qo_atomic_min_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_add(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_add_explicit ,                      \
            qo_atomic_fetch_add_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_sub(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_sub_explicit ,                      \
            qo_atomic_fetch_sub_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_and(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_and_explicit ,                      \
            qo_atomic_fetch_and_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_or(...)                                 \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_or_explicit ,                       \
            qo_atomic_fetch_or_implicit                       \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_xor(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_xor_explicit ,                      \
            qo_atomic_fetch_xor_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_nand(...)                               \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_nand_explicit ,                     \
            qo_atomic_fetch_nand_implicit                     \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_max(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_max_explicit ,                      \
            qo_atomic_fetch_max_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_fetch_min(...)                                \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_fetch_min_explicit ,                      \
            qo_atomic_fetch_min_implicit                      \
        ) (__VA_ARGS__)         

#define qo_atomic_exchange(...)                                 \
        __QO_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_exchange_explicit ,                       \
            qo_atomic_exchange_implicit                       \
        ) (__VA_ARGS__)

#define qo_atomic_cas_weak(...)                                 \
        __QO_ATOMIC_CAS_SELECT                                  \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_cas_weak_explicit ,                       \
            __NULL_REDIRECT__ ,                                      \
            qo_atomic_cas_weak_implicit                       \
        ) (__VA_ARGS__)

#define qo_atomic_cas_strong(...)                               \
        __QO_ATOMIC_CAS_SELECT                                  \
        (                                                           \
            __VA_ARGS__ ,                                           \
            qo_atomic_cas_strong_explicit ,                     \
            __NULL_REDIRECT__ ,                                      \
            qo_atomic_cas_strong_implicit                     \
        ) (__VA_ARGS__)

#define qo_atomic_cas qo_atomic_cas_strong

