#pragma once
#define __XOCEAN_ALGORITHMS_CRC32_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

xocean_int32_t
XOCEAN_INTERFACE(xocean_crc32c_4k)(
    const xocean_byte_t * buffer ,
    const xocean_size_t   size
);

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)
