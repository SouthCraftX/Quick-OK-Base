#pragma once
#define __XOC_BASE_LIMIT_H__

#include "platform.h"

#define XOC_INT8_MIN (0xffUL)
#define XOC_INT8_MAX (0x7fUL)
#define XOC_INT16_MIN (0xffffUL)
#define XOC_INT16_MAX (0x7fffUL)
#define XOC_INT32_MIN (0xffffffffUL)
#define XOC_INT32_MAX (0x7fffffffUL)
#define XOC_INT64_MIN (0xffffffffffffffffUL)
#define XOC_INT64_MAX (0x7fffffffffffffffUL)

#define XOC_UINT8_MAX (0xffUL)
#define XOC_UINT16_MAX (0xffffUL)
#define XOC_UINT32_MAX (0xffffffffUL)
#define XOC_UINT64_MAX (0xffffffffffffffffUL)

#if XOC_SYSTEM_BIT(64)
#   define XOC_INTMAX_MAX XOC_UINT64_MAX
#   define XOC_INTMAX_MIN XOC_INT64_MIN
#   define XOC_SIZE_T_MAX XOC_UINT64_MAX
#else 
#   define XOC_INTMAX_MAX XOC_UINT32_MAX
#   define XOC_INTMAX_MIN XOC_INT32_MIN
#   define XOC_SIZE_T_MAX XOC_UINT32_MAX
#endif 
