#pragma

#include "platform.h"

#define XOC_INT8_MIN (0xff)
#define XOC_INT8_MAX (0x7f)
#define XOC_INT16_MIN (0xffff)
#define XOC_INT16_MAX (0x7fff)
#define XOC_INT32_MIN (0xffffffff)
#define XOC_INT32_MAX (0x7fffffff)
#define XOC_INT64_MIN (0xffffffffffffffff)
#define XOC_INT64_MAX (0x7fffffffffffffff)

#define XOC_UINT8_MAX (0xff)
#define XOC_UINT16_MAX (0xffff)
#define XOC_UINT32_MAX (0xffffffff)
#define XOC_UINT64_MAX (0xffffffffffffffff)

#if XOC_SYSTEM_BIT(64)
#   define XOC_INTMAX_MAX XOC_UINT64_MAX
#   define XOC_INTMAX_MIN XOC_INT64_MIN
#   define XOC_SIZE_T_MAX XOC_UINT64_MAX
#else 
#   define XOC_INTMAX_MAX XOC_UINT32_MAX
#   define XOC_INTMAX_MIN XOC_INT32_MIN
#   define XOC_SIZE_T_MAX XOC_UINT32_MAX
#endif 
