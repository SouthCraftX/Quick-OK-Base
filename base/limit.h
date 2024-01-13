#pragma

#include "platform.h"

#define XOCEAN_INT8_MIN (0xff)
#define XOCEAN_INT8_MAX (0x7f)
#define XOCEAN_INT16_MIN (0xffff)
#define XOCEAN_INT16_MAX (0x7fff)
#define XOCEAN_INT32_MIN (0xffffffff)
#define XOCEAN_INT32_MAX (0x7fffffff)
#define XOCEAN_INT64_MIN (0xffffffffffffffff)
#define XOCEAN_INT64_MAX (0x7fffffffffffffff)

#define XOCEAN_UINT8_MAX (0xff)
#define XOCEAN_UINT16_MAX (0xffff)
#define XOCEAN_UINT32_MAX (0xffffffff)
#define XOCEAN_UINT64_MAX (0xffffffffffffffff)

#if XOCEAN_SYSTEM_BIT(64)
#   define XOCEAN_INTMAX_MAX XOCEAN_UINT64_MAX
#   define XOCEAN_INTMAX_MIN XOCEAN_INT64_MIN
#   define XOCEAN_SIZE_T_MAX XOCEAN_UINT64_MAX
#else 
#   define XOCEAN_INTMAX_MAX XOCEAN_UINT32_MAX
#   define XOCEAN_INTMAX_MIN XOCEAN_INT32_MIN
#   define XOCEAN_SIZE_T_MAX XOCEAN_UINT32_MAX
#endif 
