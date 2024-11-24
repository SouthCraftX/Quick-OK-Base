#pragma once
#define __QO_GNUC_TYPES__

typedef int qo_int8_t __attribute__((__mode__(__QI__)));
typedef int qo_int16_t __attribute__((__mode__(__HI__)));
typedef int qo_int32_t __attribute__((__mode__(__SI__)));
typedef int qo_int64_t __attribute__((__mode__(__DI__)));

typedef unsigned int qo_uint8_t __attribute__((__mode__(__QI__)));
typedef unsigned int qo_uint16_t __attribute__((__mode__(__HI__)));
typedef unsigned int qo_uint32_t __attribute__((__mode__(__SI__)));
typedef unsigned int qo_uint64_t __attribute__((__mode__(__DI__)));

typedef float qo_fp32_t __attribute__((__mode__(__SF__)));
typedef double qo_fp64_t __attribute__((__mode__(__DF__)));