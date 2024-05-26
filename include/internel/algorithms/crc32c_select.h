#pragma once

// for debug
#include "algorithms/crc32.h"

#if !defined(__XOCEAN_ALGORITHMS_CRC32_H__)
#   error "Never include this header file directly. Use crc32.h instead."
#endif 

#include <aws/checksums/crc.h>

#if XOCEAN_ARCH(x86) && (defined(__SSE4_2__) || defined(__AVX2__))
#   define __XOCEAN_CAN_USE_CRC32_4K_FUSION

XOCEAN_IMPORT
__xocean_crc32c_4k_fusion(
    const xocean_byte_t *   buffer ,
    const xocean_size_t     size
);

#endif

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

xocean_int32_t
XOCEAN_IMPL(xocean_crc32c_4k)(
    const xocean_byte_t *   buffer ,
    const xocean_size_t     size
){
#if __XOCEAN_CAN_USE_CRC32_4K_FUSION
    return __xocean_crc32c_4k_fusion(buffer , size , 0);
#   undef __XOCEAN_CAN_USE_CRC32_4K_FUSION  
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