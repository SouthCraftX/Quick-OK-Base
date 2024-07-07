#pragma once
#define __XOC_ALGORITHMS_CRC32_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

XOC_IMPORT
xoc_int32_t
__xoc_crc32c_4k_fusion(
    xoc_int32_t  acc_a ,
    xoc_byte_t * buffer
);

xoc_int32_t
__xoc_crc32c_4k_fusion_n(
    xoc_byte_t * buffer ,
    xoc_size_t   chunk_count ,
){
    xoc_int32_t crc = 0;
    while (chunk_count)
    {
        crc = __xoc_crc32c_4k_fusion(crc , buffer);
        buffer += 4096;
        chunk_count--;
    }
    
}

xoc_int32_t
XOC_INTERFACE(xoc_crc32c_4k)(
    const xoc_byte_t * buffer ,
    const xoc_size_t   size
);

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)
