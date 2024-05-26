#pragma once

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

xocean_int32_t
XOCEAN_INTERFACE(xocean_rand32)(
    xocean_int32_t min ,
    xocean_int32_t max
);

xocean_int64_t
XOCEAN_INTERFACE(xocean_rand64)(
    xocean_int64_t min ,
    xocean_int64_t max
);

void
XOCEAN_INTERFACE(xocean_rand_string)(
    xocean_cstring_t    target_str ,
    xocean_size_t       target_str_len ,
    xocean_ccstring_t   char_set ,
    xocean_size_t       char_set_len
);

void
XOCEAN_INTERFACE(xocean_sys_rand_buf)(
    xocean_pointer_t    buf , 
    xocean_size_t       len
);

void
XOCEAN_INTERFACE(xocean_rand_string_utf8)(
    xocean_cstring_t    target_str ,
    xocean_size_t       target_str_len ,
    xocean_ccstring_t   char_set ,
    xocean_size_t       char_set_len
);

#if defined(__cplusplus)
}
#endif // __cplusplus
