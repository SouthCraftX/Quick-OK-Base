#pragma once
#define __XOC_GNUC_TYPES__

typedef int xoc_int8_t __attribute__((__mode__(__QI__)));
typedef int xoc_int16_t __attribute__((__mode__(__HI__)));
typedef int xoc_int32_t __attribute__((__mode__(__SI__)));
typedef int xoc_int64_t __attribute__((__mode__(__DI__)));

typedef unsigned int xoc_uint8_t __attribute__((__mode__(__QI__)));
typedef unsigned int xoc_uint16_t __attribute__((__mode__(__HI__)));
typedef unsigned int xoc_uint32_t __attribute__((__mode__(__SI__)));
typedef unsigned int xoc_uint64_t __attribute__((__mode__(__DI__)));

typedef float xoc_fp32_t __attribute__((__mode__(__SF__)));
typedef double xoc_fp64_t __attribute__((__mode__(__DF__)));