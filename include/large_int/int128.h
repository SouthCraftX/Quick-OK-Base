#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QOInt128;
typedef struct _QOInt128 QOInt128;
typedef QOInt128 qo_int128_t;

#define QO_INT128(x)  ((qo_int128_t){x})
#define QO_INT128_MIN QO_INT128(0x80000000000000000000000000000000)
#define QO_INT128_MAX QO_INT128(0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)

#if defined(__GNUC__) && QO_SYSTEM_BIT(64) 
typedef __int128 __qo_sys_int128_t;
#elif __STDC_VERSION__ > 202300
typedef int128_t __qo_sys_int128_t;
#endif 

#if defined(__GNUC__) && QO_SYSTEM_BIT(64) 
QO_ALIGNAS(16)      // SIMD requires align as that
struct _QOInt128
{
    __qo_sys_int128_t  i;
};

QO_FORCE_INLINE
bool
qo_int128_equal(
    qo_int128_t a , 
    qo_int128_t b
){
    return a.i == b.i;
}

QO_FORCE_INLINE
bool
qo_int128_not(
    qo_int128_t a
){
    return !a.i;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_add(
    qo_int128_t a , 
    qo_int128_t b
){
    return (qo_int128_t){ a.i + b.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_sub(
    qo_int128_t a , 
    qo_int128_t b
){
    return (qo_int128_t){ a.i - b.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_mul(
    qo_int128_t a , 
    qo_int128_t b
){
    return (qo_int128_t){ a.i * b.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_div(
    qo_int128_t a , 
    qo_int128_t b
){
    return (qo_int128_t){ a.i / b.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_mod(
    qo_int128_t a , 
    qo_int128_t b
){
    return (qo_int128_t){ a.i % b.i };
}

QO_FORCE_INLINE
qo_int64_t
qo_int128_trunl64(
    qo_int128_t a
){
    return (qo_int64_t)a.i;
}

QO_FORCE_INLINE
qo_int64_t
qo_int128_trunh64(
    qo_int128_t a
){
    return (qo_int64_t)((a.i) >> 63);
}

QO_FORCE_INLINE
bool
qo_int128_or(
    qo_int128_t a , 
    qo_int128_t b
){
    return  a.i || b.i ;
}


QO_FORCE_INLINE
bool
qo_int128_and(
    qo_int128_t a, 
    qo_int128_t b
){
    return a.i && b.i ;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_nor(
    qo_int128_t a ,
    qo_int128_t b
){
    return (qo_int128_t){ a.i | b.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_xor(
    qo_int128_t a ,
    qo_int128_t b
){
    return (qo_int128_t){ a.i ^ b.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_rs(
    qo_int128_t a ,
    qo_uint8_t  n
){
    return (qo_int128_t){ a.i >> n };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_ls(
    qo_int128_t a ,
    qo_uint8_t  n
){
    return (qo_int128_t){ a.i << n };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_rseq(
    qo_int128_t *   a,
    qo_uint8_t      n
){
    *a = qo_int128_rs(*a, n);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_lseq(
    qo_int128_t *   a ,
    qo_uint8_t      n
){
    *a = qo_int128_ls(*a, n);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_addeq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_add(*a, b);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_bnot(
    qo_int128_t a
){
    return (qo_int128_t){ ~a.i };
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_bnoteq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_bnot(qo_int128_sub(*a, b));
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_addeq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_add(*a, b);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_subeq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_sub(*a, b);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_muleq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_mul(*a, b);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_diveq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_div(*a, b);
    return *a;
}

QO_FORCE_INLINE
bool
qo_int128_noteq(
    qo_int128_t     a ,
    qo_int128_t     b
){
    return a.i != b.i;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_xoreq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_xor(*a, b);
    return *a;
}

QO_FORCE_INLINE
qo_int128_t
qo_int128_noreq(
    qo_int128_t *   a ,
    qo_int128_t     b
){
    *a = qo_int128_nor(*a, b);
    return *a;
}

#endif // gcc

#if defined(__cplusplus)
}
#endif // __cplusplus
