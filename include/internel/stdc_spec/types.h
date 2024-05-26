#pragma once
#define __XOCEAN_STDC_ATOMIC__

#if __STDC_VERSION__ < 199901L
#    error XOceanLib: C99 or later is required to define basic types
#endif // __STDC_VERSION__ < 199901L

#include <stdint.h>

typedef int8_t  xocean_int8_t;
typedef int16_t xocean_int16_t;
typedef int32_t xocean_int32_t;
typedef int64_t xocean_int64_t;

typedef uint8_t  xocean_uint8_t;
typedef uint16_t xocean_uint16_t;
typedef uint32_t xocean_uint32_t;
typedef uint64_t xocean_uint64_t;
