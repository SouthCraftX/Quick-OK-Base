#pragma once

// for debug
#include "algorithms/crc32.h"

#if !defined(__XOC_ALGORITHMS_CRC32_H__)
#   error "Never include this header file directly. Use crc32.h instead."
#endif 

#include <aws/checksums/crc.h>

#if XOC_ARCH(x86) && (defined(__SSE4_2__) || defined(__AVX2__))
#   define __XOC_CAN_USE_CRC32_4K_FUSION

XOC_IMPORT
__xoc_crc32c_4k_fusion(
    const xoc_byte_t *   buffer ,
    const xoc_size_t     size
);

#endif

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

xoc_int32_t
XOC_IMPL(xoc_crc32c_4k)(
    const xoc_byte_t *   buffer ,
    const xoc_size_t     size
){
#if __XOC_CAN_USE_CRC32_4K_FUSION
    return __xoc_crc32c_4k_fusion(buffer , size , 0);
#   undef __XOC_CAN_USE_CRC32_4K_FUSION  
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