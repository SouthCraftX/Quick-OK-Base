#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#include <static_assert.h>
#include <stdint.h>     // uint32_t , ...
#include <stddef.h>     // NULL , ...
#include <stdbool.h>    // bool

#if __STDC_VERSION__ >= 201112L
#   include <stdatomic.h>  // _Atomic
#endif // __STDC_VERSION__

_Static_assert(sizeof(double) == 8 , "The size of double is not 8 byte");
_Static_assert(sizeof(float) == 4 , "The size of float is not 4 byte");

typedef float xocean_fp32_t;
typedef double xocean_fp64_t;

typedef int8_t xocean_int8_t;
typedef int16_t xocean_int16_t;
typedef int32_t xocean_int32_t;
typedef int64_t xocean_int64_t;

typedef uint8_t xocean_uint8_t;
typedef uint16_t xocean_uint16_t;
typedef uint32_t xocean_uint32_t;
typedef uint64_t xocean_uint64_t;



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