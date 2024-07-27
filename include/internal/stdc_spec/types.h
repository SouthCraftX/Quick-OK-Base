#pragma once
#define __XOC_STDC_ATOMIC__

#if __STDC_VERSION__ < 199901L
#    error XOCLib: C99 or later is required to define basic types
#endif // __STDC_VERSION__ < 199901L

#include <stdint.h>

typedef int8_t  xoc_int8_t;
typedef int16_t xoc_int16_t;
typedef int32_t xoc_int32_t;
typedef int64_t xoc_int64_t;

typedef uint8_t  xoc_uint8_t;
typedef uint16_t xoc_uint16_t;
typedef uint32_t xoc_uint32_t;
typedef uint64_t xoc_uint64_t;
