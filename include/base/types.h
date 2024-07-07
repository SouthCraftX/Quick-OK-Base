#pragma once

#include <assert.h>

#if defined(__GNUC__)
#   include "internel/gnuc_spec/types.h"
#elif defined(_MSC_VER)
#   include "internel/msvc_spec/types.h"
#else
#   include "internel/stdc_spec/types.h"
#endif 

#if XOC_SYSTEM_BIT(64)
typedef     xoc_uint64_t xoc_uintmax_t;
typedef     xoc_int64_t  xoc_intmax_t;
typedef     xoc_uint64_t xoc_size_t;
typedef     xoc_int64_t  xoc_ssize_t;
#else
typedef     xoc_int32_t          xoc_intmax_t;
typedef     xoc_uint32_t         xoc_size_t;
typedef     xoc_int32_t          xoc_ssize_t;
#endif // XOC_SYSTEM_BIT(64)

typedef     xoc_uint8_t  xoc_byte_t;

typedef     void*        xoc_pointer_t;
typedef     xoc_int8_t   xoc_bool_t;
typedef     xoc_uint32_t xoc_ref_count_t;

#define     xoc_true     ((xoc_bool_t)1)
#define     xoc_false    ((xoc_bool_t)0)

#if defined(XOC_WANT_HALF_LEN_STAT_T)
typedef     xoc_int16_t  xoc_stat_t;
#else
typedef     xoc_int32_t  xoc_stat_t;
#endif 

typedef     xoc_ssize_t  xoc_offset_t;

typedef     xoc_int8_t   xoc_flag8_t;
typedef     xoc_int16_t  xoc_flag16_t;
typedef     xoc_int32_t  xoc_flag32_t;
typedef     xoc_int64_t  xoc_flag64_t;

typedef     char*               xoc_cstring_t;
typedef     const xoc_cstring_t xoc_ccstring_t;


