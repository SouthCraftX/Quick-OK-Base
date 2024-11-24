#pragma once

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

// Thanks to SodiumCl10
qo_int32_t 
qo_find_contigous_zeros64(
    qo_uint64_t x,
    qo_size_t len
){
    qo_uint16_t tmp[6];
    --len;
    tmp[1] = tmp[0] | (tmp[0] << 1);
    tmp[2] = tmp[1] | (tmp[1] << 2);
    tmp[3] = tmp[2] | (tmp[2] << 4);
    tmp[4] = tmp[3] | (tmp[3] << 8);
    tmp[5] = tmp[4] | (tmp[4] << 16);
    qo_int32_t mxw = 31 - __builtin_clz(len);
    x = (tmp[mxw] << (len - (1 << mxw))) | tmp[mxw];
    return __builtin_clzll(~x);
}

    

#if defined(__cplusplus)
}
#endif // __cplusplus
