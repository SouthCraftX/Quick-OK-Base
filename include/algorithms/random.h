#pragma once
#define __QO_ALGORITHMS_RANDOM_H__

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// U -> Upper case  L -> lower case  N -> Number  S -> Special
#define QO_CHAR_SET_ULN "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define QO_CHAR_SET_ULNS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|\\:;\"'<>,.?/`~"

#define QO_CHAR_SET_ULN_LEN 63
#define QO_CHAR_SET_ULNS_LEN 93

qo_int32_t
QO_INTERFACE(qo_rand32)(
    qo_int32_t min ,
    qo_int32_t max
);

qo_int64_t
QO_INTERFACE(qo_rand64)(
    qo_int64_t min ,
    qo_int64_t max
);

void
QO_INTERFACE(qo_rand_string)(
    qo_cstring_t    target_str ,
    qo_size_t       target_str_len ,
    qo_ccstring_t   char_set ,
    qo_size_t       char_set_len
);

void
QO_INTERFACE(qo_sys_rand_buf)(
    qo_pointer_t    buf , 
    qo_size_t       len
);

void
QO_INTERFACE(qo_rand_string_utf8)(
    qo_cstring_t    target_str ,
    qo_size_t       target_str_len ,
    qo_ccstring_t   char_set ,
    qo_size_t       char_set_len
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#define qo_rand32 QO_INTERFACE(qo_rand32)
#define qo_rand64 QO_INTERFACE(qo_rand64)
#define qo_rand_string QO_INTERFACE(qo_rand_string)
#define qo_sys_rand_buf QO_INTERFACE(qo_sys_rand_buf)
