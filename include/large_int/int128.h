#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOCInt128;
typedef struct _XOCInt128 XOCInt128;
typedef XOCInt128 xoc_int128_t;

#define XOC_INT128(x)  ((xoc_int128_t){x})
#define XOC_INT128_MIN XOC_INT128(0x80000000000000000000000000000000)
#define XOC_INT128_MAX XOC_INT128(0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)

#if defined(__GNUC__) && XOC_SYSTEM_BIT(64) 
typedef __int128 __xoc_sys_int128_t;
#elif __STDC_VERSION__ > 202300
typedef int128_t __xoc_sys_int128_t;
#endif 

#if defined(__GNUC__) && XOC_SYSTEM_BIT(64) 
XOC_ALIGNAS(16)      // SIMD requires align as that
struct _XOCInt128
{
    __xoc_sys_int128_t  i;
};

XOC_FORCE_INLINE
bool
xoc_int128_equal(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return a.i == b.i;
}

XOC_FORCE_INLINE
bool
xoc_int128_not(
    xoc_int128_t a
){
    return !a.i;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_add(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i + b.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_sub(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i - b.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_mul(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i * b.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_div(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i / b.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_mod(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i % b.i };
}

XOC_FORCE_INLINE
xoc_int64_t
xoc_int128_trunl64(
    xoc_int128_t a
){
    return (xoc_int64_t)a.i;
}

XOC_FORCE_INLINE
xoc_int64_t
xoc_int128_trunh64(
    xoc_int128_t a
){
    return (xoc_int64_t)((a.i) >> 63);
}

XOC_FORCE_INLINE
bool
xoc_int128_or(
    xoc_int128_t a , 
    xoc_int128_t b
){
    return  a.i || b.i ;
}


XOC_FORCE_INLINE
bool
xoc_int128_and(
    xoc_int128_t a, 
    xoc_int128_t b
){
    return a.i && b.i ;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_nor(
    xoc_int128_t a ,
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i | b.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_xor(
    xoc_int128_t a ,
    xoc_int128_t b
){
    return (xoc_int128_t){ a.i ^ b.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_rs(
    xoc_int128_t a ,
    xoc_uint8_t  n
){
    return (xoc_int128_t){ a.i >> n };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_ls(
    xoc_int128_t a ,
    xoc_uint8_t  n
){
    return (xoc_int128_t){ a.i << n };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_rseq(
    xoc_int128_t *   a,
    xoc_uint8_t      n
){
    *a = xoc_int128_rs(*a, n);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_lseq(
    xoc_int128_t *   a ,
    xoc_uint8_t      n
){
    *a = xoc_int128_ls(*a, n);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_addeq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_add(*a, b);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_bnot(
    xoc_int128_t a
){
    return (xoc_int128_t){ ~a.i };
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_bnoteq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_bnot(xoc_int128_sub(*a, b));
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_addeq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_add(*a, b);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_subeq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_sub(*a, b);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_muleq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_mul(*a, b);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_diveq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_div(*a, b);
    return *a;
}

XOC_FORCE_INLINE
bool
xoc_int128_noteq(
    xoc_int128_t     a ,
    xoc_int128_t     b
){
    return a.i != b.i;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_xoreq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_xor(*a, b);
    return *a;
}

XOC_FORCE_INLINE
xoc_int128_t
xoc_int128_noreq(
    xoc_int128_t *   a ,
    xoc_int128_t     b
){
    *a = xoc_int128_nor(*a, b);
    return *a;
}

#endif // gcc

#if defined(__cplusplus)
}
#endif // __cplusplus
