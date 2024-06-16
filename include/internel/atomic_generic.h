#pragma once
#define __XOCEAN_ATOMIC_GENERIC_H__

#if !(defined(__XOCEAN_STDC_ATOMIC_H__) || defined(__XOCEAN_GNUC_ATOMIC_H__))
#   error "Never include this header file directly. Use <xocean/atomic.h> instead."
#endif

// Generic macro tricks refer to:
// https://blog.csdn.net/fshngrmng/article/details/119572189

#define __XOCEAN_ATOMIC_2OR3_ARGS_SELECT(ptr , val , order , target , ...) target
#define __XOCEAN_ATOMIC_CAS_SELECT(ptr , expected , desired , success , \ 
                                   failure , target , ...) target

#define xocean_atomic_add_fetch(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_add_fetch_explicit ,                      \
            xocean_atomic_add_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_sub_fetch(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_sub_fetch_explicit ,                      \
            xocean_atomic_sub_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_and_fetch(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_and_fetch_explicit ,                      \
            xocean_atomic_and_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_or_fetch(...)                                 \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_or_fetch_explicit ,                       \
            xocean_atomic_or_fetch_implicit                       \
        ) (__VA_ARGS__)         

#define xocean_atomic_xor_fetch(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_xor_fetch_explicit ,                      \
            xocean_atomic_xor_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_nand_fetch(...)                               \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_nand_fetch_explicit ,                     \
            xocean_atomic_nand_fetch_implicit                     \
        ) (__VA_ARGS__)         

#define xocean_atomic_max_fetch(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_max_fetch_explicit ,                      \
            xocean_atomic_max_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_min_fetch(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_min_fetch_explicit ,                      \
            xocean_atomic_min_fetch_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_add(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_add_explicit ,                      \
            xocean_atomic_fetch_add_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_sub(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_sub_explicit ,                      \
            xocean_atomic_fetch_sub_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_and(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_and_explicit ,                      \
            xocean_atomic_fetch_and_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_or(...)                                 \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_or_explicit ,                       \
            xocean_atomic_fetch_or_implicit                       \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_xor(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_xor_explicit ,                      \
            xocean_atomic_fetch_xor_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_nand(...)                               \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_nand_explicit ,                     \
            xocean_atomic_fetch_nand_implicit                     \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_max(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_max_explicit ,                      \
            xocean_atomic_fetch_max_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_fetch_min(...)                                \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_fetch_min_explicit ,                      \
            xocean_atomic_fetch_min_implicit                      \
        ) (__VA_ARGS__)         

#define xocean_atomic_exchange(...)                                 \
        __XOCEAN_ATOMIC_2OR3_ARGS_SELECT                            \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_exchange_explicit ,                       \
            xocean_atomic_exchange_implicit                       \
        ) (__VA_ARGS__)

#define xocean_atomic_cas_weak(...)                                 \
        __XOCEAN_ATOMIC_CAS_SELECT                                  \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_cas_weak_explicit ,                       \
            __NULL_REDIRECT__ ,                                      \
            xocean_atomic_cas_weak_implicit                       \
        ) (__VA_ARGS__)

#define xocean_atomic_cas_strong(...)                               \
        __XOCEAN_ATOMIC_CAS_SELECT                                  \
        (                                                           \
            __VA_ARGS__ ,                                           \
            xocean_atomic_cas_strong_explicit ,                     \
            __NULL_REDIRECT__ ,                                      \
            xocean_atomic_cas_strong_implicit                     \
        ) (__VA_ARGS__)

#define xocean_atomic_cas xocean_atomic_cas_strong

