#pragma once

#include <assert.h>

#if defined(__GNUC__)
#   include "internel/gnuc_spec/types.h"
#elif defined(_MSC_VER)
#   include "internel/msvc_spec/types.h"
#else
#   include "internel/stdc_spec/types.h"
#endif 

#if XOCEAN_SYSTEM_BIT(64)
typedef     xocean_uint64_t xocean_uintmax_t;
typedef     xocean_int64_t  xocean_intmax_t;
typedef     xocean_uint64_t xocean_size_t;
typedef     xocean_int64_t  xocean_ssize_t;
#else
typedef     xocean_int32_t          xocean_intmax_t;
typedef     xocean_uint32_t         xocean_size_t;
typedef     xocean_int32_t          xocean_ssize_t;
#endif // XOCEAN_SYSTEM_BIT(64)

typedef     xocean_uint8_t  xocean_byte_t;

typedef     void*           xocean_pointer_t;
typedef     xocean_int8_t   xocean_bool_t;
typedef     xocean_uint32_t xocean_ref_count_t;

#define     xocean_true     ((xocean_bool_t)1)
#define     xocean_false    ((xocean_bool_t)0)

#if defined(XOCEAN_WANT_HALF_LEN_STAT_T)
typedef     xocean_int16_t  xocean_stat_t;
#else
typedef     xocean_int32_t  xocean_stat_t;
#endif 

typedef     xocean_ssize_t  xocean_offset_t;

typedef     xocean_int8_t   xocean_flag8_t;
typedef     xocean_int16_t  xocean_flag16_t;
typedef     xocean_int32_t  xocean_flag32_t;
typedef     xocean_int64_t  xocean_flag64_t;

typedef     char*                   xocean_cstring_t;
typedef     const xocean_cstring_t  xocean_ccstring_t;


