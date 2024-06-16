#pragma once
#define __XOCEAN_ALGORITHMS_CRC32_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

XOCEAN_IMPORT
xocean_int32_t
__xocean_crc32c_4k_fusion(
    xocean_int32_t  acc_a ,
    xocean_byte_t * buffer
);

xocean_int32_t
__xocean_crc32c_4k_fusion_n(
    xocean_byte_t * buffer ,
    xocean_size_t   chunk_count ,
){
    xocean_int32_t crc = 0;
    while (chunk_count)
    {
        crc = __xocean_crc32c_4k_fusion(crc , buffer);
        buffer += 4096;
        chunk_count--;
    }
    
}

xocean_int32_t
XOCEAN_INTERFACE(xocean_crc32c_4k)(
    const xocean_byte_t * buffer ,
    const xocean_size_t   size
);

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)
