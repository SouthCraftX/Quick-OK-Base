#pragma once
#define __QO_BASE_LIMIT_H__

#include "platform.h"

#define QO_INT8_MIN (0xffUL)
#define QO_INT8_MAX (0x7fUL)
#define QO_INT16_MIN (0xffffUL)
#define QO_INT16_MAX (0x7fffUL)
#define QO_INT32_MIN (0xffffffffUL)
#define QO_INT32_MAX (0x7fffffffUL)
#define QO_INT64_MIN (0xffffffffffffffffUL)
#define QO_INT64_MAX (0x7fffffffffffffffUL)

#define QO_UINT8_MAX (0xffUL)
#define QO_UINT16_MAX (0xffffUL)
#define QO_UINT32_MAX (0xffffffffUL)
#define QO_UINT64_MAX (0xffffffffffffffffUL)

#define QO_INT8_SIGN (0x80UL)
#define QO_INT16_SIGN (0x8000UL)
#define QO_INT32_SIGN (0x80000000UL)
#define QO_INT64_SIGN (0x8000000000000000UL)

#if QO_SYSTEM_BIT(64)
#   define QO_INTMAX_MAX QO_UINT64_MAX
#   define QO_INTMAX_MIN QO_INT64_MIN
#   define QO_SIZE_T_MAX QO_UINT64_MAX
#else 
#   define QO_INTMAX_MAX QO_UINT32_MAX
#   define QO_INTMAX_MIN QO_INT32_MIN
#   define QO_SIZE_T_MAX QO_UINT32_MAX
#endif 
