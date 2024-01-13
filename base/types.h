#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#include <assert.h>
#include <stdint.h>     // uint32_t , ...
#include <stddef.h>     // NULL , ...
#include <stdbool.h>    // bool

#if __STDC_VERSION__ >= 201112L
#   include <stdatomic.h>  // _Atomic
#endif // __STDC_VERSION__

static_assert(sizeof(double) == 8 , "The size of double is not 8 byte");
static_assert(sizeof(float)  == 4 , "The size of float is not 4 byte");

typedef     float           xocean_fp32_t;
typedef     double          xocean_fp64_t;

typedef     int8_t          xocean_int8_t;
typedef     int16_t         xocean_int16_t;
typedef     int32_t         xocean_int32_t;
typedef     int64_t         xocean_int64_t;

typedef     uint8_t         xocean_uint8_t;
typedef     uint16_t        xocean_uint16_t;
typedef     uint32_t        xocean_uint32_t;
typedef     uint64_t        xocean_uint64_t;

typedef     intmax_t        xocean_intmax_t;

typedef     uint8_t         xocean_byte_t;

typedef     void*           xocean_pointer_t;
typedef     bool            xocean_bool_t;

#if defined(XOCEAN_WANT_HALF_LEN_STAT_T)
typedef     xocean_int16_t  xocean_stat_t;
#else
typedef     xocean_int32_t  xocean_stat_t;
#endif 

#if XOCEAN_SYSTEM_BIT(64)
typedef     xocean_uint64_t xocean_size_t;
typedef     xocean_int64_t  xocean_ssize_t;
#else
typedef     xocean_uint32_t xocean_size_t;
typedef     xocean_int32_t  xocean_ssize_t;
#endif // XOCEAN_SYSTEM_BIT(64)


typedef     xocean_int8_t   xocean_flag8_t;
typedef     xocean_int16_t  xocean_flag16_t;
typedef     xocean_int32_t  xocean_flag32_t;
typedef     xocean_int64_t  xocean_flag64_t;

typedef     char*           xocean_cstring_t;
typedef     const xocean_cstring_t xocean_ccstring_t;

#   if __STDC_VERSION__ >= 201112L
typedef _Atomic(xocean_fp32_t) xocean_afp32_t;
typedef _Atomic(xocean_fp64_t) xocean_afp64_t;

typedef _Atomic(xocean_int8_t) xocean_aint8_t;
typedef _Atomic(xocean_int16_t) xocean_aint16_t;
typedef _Atomic(xocean_int32_t) xocean_aint32_t;
typedef _Atomic(xocean_int64_t) xocean_aint64_t;

typedef _Atomic(xocean_uint8_t) xocean_auint8_t;
typedef _Atomic(xocean_uint16_t) xocean_auint16_t;
typedef _Atomic(xocean_uint32_t) xocean_auint32_t;
typedef _Atomic(xocean_uint64_t) xocean_auint64_t;
#   endif // __STDC_VERSION__

#if defined(__cplusplus)
}
#endif 