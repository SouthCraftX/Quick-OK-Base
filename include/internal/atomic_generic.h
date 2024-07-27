#pragma once
#define __XOC_ATOMIC_GENERIC_H__

#if !(defined(__XOC_STDC_ATOMIC_H__) || defined(__XOC_GNUC_ATOMIC_H__))
#   error "Never include this header file directly. Use <xoc/atomic.h> instead."
#endif

// Generic macro tricks refer to:
// https://blog.csdn.net/fshngrmng/article/details/119572189

#define __XOC_ATOMIC_2OR3_ARGS_SELECT(ptr , val , order , target , ...) target
#define __XOC_ATOMIC_CAS_SELECT(ptr , expected , desired , success , \ 
                                   failure , target , ...) target

#define xoc_atomic_add_fetch(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_add_fetch_explicit ,                      \
            xoc_atomic_add_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_sub_fetch(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_sub_fetch_explicit ,                      \
            xoc_atomic_sub_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_and_fetch(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_and_fetch_explicit ,                      \
            xoc_atomic_and_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_or_fetch(...)                                 \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_or_fetch_explicit ,                       \
            xoc_atomic_or_fetch_implicit                       \
        ) (__VA_ARGS__)         

#define xoc_atomic_xor_fetch(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_xor_fetch_explicit ,                      \
            xoc_atomic_xor_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_nand_fetch(...)                               \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_nand_fetch_explicit ,                     \
            xoc_atomic_nand_fetch_implicit                     \
        ) (__VA_ARGS__)         

#define xoc_atomic_max_fetch(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_max_fetch_explicit ,                      \
            xoc_atomic_max_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_min_fetch(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_min_fetch_explicit ,                      \
            xoc_atomic_min_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_add(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_add_explicit ,                      \
            xoc_atomic_fetch_add_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_sub(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_sub_explicit ,                      \
            xoc_atomic_fetch_sub_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_and(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_and_explicit ,                      \
            xoc_atomic_fetch_and_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_or(...)                                 \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_or_explicit ,                       \
            xoc_atomic_fetch_or_implicit                       \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_xor(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_xor_explicit ,                      \
            xoc_atomic_fetch_xor_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_nand(...)                               \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_nand_explicit ,                     \
            xoc_atomic_fetch_nand_implicit                     \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_max(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_max_explicit ,                      \
            xoc_atomic_fetch_max_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_fetch_min(...)                                \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_fetch_min_explicit ,                      \
            xoc_atomic_fetch_min_implicit                      \
        ) (__VA_ARGS__)         

#define xoc_atomic_exchange(...)                                 \
        __XOC_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_exchange_explicit ,                       \
            xoc_atomic_exchange_implicit                       \
        ) (__VA_ARGS__)

#define xoc_atomic_cas_weak(...)                                 \
        __XOC_ATOMIC_CAS_SELECT                                  \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_cas_weak_explicit ,                       \
            __NULL_REDIRECT__ ,                                      \
            xoc_atomic_cas_weak_implicit                       \
        ) (__VA_ARGS__)

#define xoc_atomic_cas_strong(...)                               \
        __XOC_ATOMIC_CAS_SELECT                                  \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xoc_atomic_cas_strong_explicit ,                     \
            __NULL_REDIRECT__ ,                                      \
            xoc_atomic_cas_strong_implicit                     \
        ) (__VA_ARGS__)

#define xoc_atomic_cas xoc_atomic_cas_strong

