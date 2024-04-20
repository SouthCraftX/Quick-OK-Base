#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanInt128;
typedef struct _XOceanInt128 XOceanInt128;
typedef XOceanInt128 xocean_int128_t;

#define XOCEAN_INT128(x)  ((xocean_int128_t){x})
#define XOCEAN_INT128_MIN XOCEAN_INT128(0x80000000000000000000000000000000)
#define XOCEAN_INT128_MAX XOCEAN_INT128(0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)

#if defined(__GNUC__) && XOCEAN_SYSTEM_BIT(64) 
typedef __int128 __xocean_sys_int128_t;
#elif __STDC_VERSION__ > 202300
typedef int128_t __xocean_sys_int128_t;
#endif 

#if defined(__GNUC__) && XOCEAN_SYSTEM_BIT(64) 
XOCEAN_ALIGNAS(16)      // SIMD requires align as that
struct _XOceanInt128
{
    __xocean_sys_int128_t  i;
};

XOCEAN_FORCE_INLINE
bool
xocean_int128_equal(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return a.i == b.i;
}

XOCEAN_FORCE_INLINE
bool
xocean_int128_not(
    xocean_int128_t a
){
    return !a.i;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_add(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i + b.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_sub(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i - b.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_mul(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i * b.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_div(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i / b.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_mod(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i % b.i };
}

XOCEAN_FORCE_INLINE
xocean_int64_t
xocean_int128_trunl64(
    xocean_int128_t a
){
    return (xocean_int64_t)a.i;
}

XOCEAN_FORCE_INLINE
xocean_int64_t
xocean_int128_trunh64(
    xocean_int128_t a
){
    return (xocean_int64_t)((a.i) >> 63);
}

XOCEAN_FORCE_INLINE
bool
xocean_int128_or(
    xocean_int128_t a , 
    xocean_int128_t b
){
    return  a.i || b.i ;
}


XOCEAN_FORCE_INLINE
bool
xocean_int128_and(
    xocean_int128_t a, 
    xocean_int128_t b
){
    return a.i && b.i ;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_nor(
    xocean_int128_t a ,
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i | b.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_xor(
    xocean_int128_t a ,
    xocean_int128_t b
){
    return (xocean_int128_t){ a.i ^ b.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_rs(
    xocean_int128_t a ,
    xocean_uint8_t  n
){
    return (xocean_int128_t){ a.i >> n };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_ls(
    xocean_int128_t a ,
    xocean_uint8_t  n
){
    return (xocean_int128_t){ a.i << n };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_rseq(
    xocean_int128_t *   a,
    xocean_uint8_t      n
){
    *a = xocean_int128_rs(*a, n);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_lseq(
    xocean_int128_t *   a ,
    xocean_uint8_t      n
){
    *a = xocean_int128_ls(*a, n);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_addeq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_add(*a, b);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_bnot(
    xocean_int128_t a
){
    return (xocean_int128_t){ ~a.i };
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_bnoteq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_bnot(xocean_int128_sub(*a, b));
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_addeq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_add(*a, b);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_subeq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_sub(*a, b);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_muleq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_mul(*a, b);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_diveq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_div(*a, b);
    return *a;
}

XOCEAN_FORCE_INLINE
bool
xocean_int128_noteq(
    xocean_int128_t     a ,
    xocean_int128_t     b
){
    return a.i != b.i;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_xoreq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_xor(*a, b);
    return *a;
}

XOCEAN_FORCE_INLINE
xocean_int128_t
xocean_int128_noreq(
    xocean_int128_t *   a ,
    xocean_int128_t     b
){
    *a = xocean_int128_nor(*a, b);
    return *a;
}

#endif // gcc

#if defined(__cplusplus)
}
#endif // __cplusplus
