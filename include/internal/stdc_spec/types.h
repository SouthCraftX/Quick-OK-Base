#pragma once
#define __QO_STDC_ATOMIC__

#if __STDC_VERSION__ < 199901L
#    error QOLib: C99 or later is required to define basic types
#endif // __STDC_VERSION__ < 199901L

#include <stdint.h>

typedef int8_t  qo_int8_t;
typedef int16_t qo_int16_t;
typedef int32_t qo_int32_t;
typedef int64_t qo_int64_t;

typedef uint8_t  qo_uint8_t;
typedef uint16_t qo_uint16_t;
typedef uint32_t qo_uint32_t;
typedef uint64_t qo_uint64_t;
