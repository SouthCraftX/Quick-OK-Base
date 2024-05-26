#pragma once
#define __XOCEAN_GNUC_TYPES__

typedef int xocean_int8_t __attribute__((__mode__(__QI__)));
typedef int xocean_int16_t __attribute__((__mode__(__HI__)));
typedef int xocean_int32_t __attribute__((__mode__(__SI__)));
typedef int xocean_int64_t __attribute__((__mode__(__DI__)));

typedef unsigned int xocean_uint8_t __attribute__((__mode__(__QI__)));
typedef unsigned int xocean_uint16_t __attribute__((__mode__(__HI__)));
typedef unsigned int xocean_uint32_t __attribute__((__mode__(__SI__)));
typedef unsigned int xocean_uint64_t __attribute__((__mode__(__DI__)));

typedef float xocean_fp32_t __attribute__((__mode__(__SF__)));
typedef double xocean_fp64_t __attribute__((__mode__(__DF__)));