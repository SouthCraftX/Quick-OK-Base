#pragma once
#define __QO_ALGORITHMS_CRC32_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

QO_IMPORT
qo_int32_t
__qo_crc32c_4k_fusion(
    qo_int32_t  acc_a ,
    qo_byte_t * buffer
);

qo_int32_t
__qo_crc32c_4k_fusion_n(
    qo_byte_t * buffer ,
    qo_size_t   chunk_count ,
){
    qo_int32_t crc = 0;
    while (chunk_count)
    {
        crc = __qo_crc32c_4k_fusion(crc , buffer);
        buffer += 4096;
        chunk_count--;
    }
    
}

qo_int32_t
QO_INTERFACE(qo_crc32c_4k)(
    const qo_byte_t * buffer ,
    const qo_size_t   size
);

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)
