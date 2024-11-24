#pragma once

// for debug
#include "algorithms/crc32.h"

#if !defined(__QO_ALGORITHMS_CRC32_H__)
#   error "Never include this header file directly. Use crc32.h instead."
#endif 

#include <aws/checksums/crc.h>

#if QO_ARCH(x86) && (defined(__SSE4_2__) || defined(__AVX2__))
#   define __QO_CAN_USE_CRC32_4K_FUSION

QO_IMPORT
__qo_crc32c_4k_fusion(
    const qo_byte_t *   buffer ,
    const qo_size_t     size
);

#endif

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

qo_int32_t
QO_IMPL(qo_crc32c_4k)(
    const qo_byte_t *   buffer ,
    const qo_size_t     size
){
#if __QO_CAN_USE_CRC32_4K_FUSION
    return __qo_crc32c_4k_fusion(buffer , size , 0);
#   undef __QO_CAN_USE_CRC32_4K_FUSION  
    // Remove the macro because it's no longer used.
#else
    // aws crc32c provides an implementation for all architectures that may
    // be slower than the former one.
    return aws_checksums_crc32c(buffer , size , 0);
#endif
}

#if defined(__cplusplus)
}
#endif // __cplusplus