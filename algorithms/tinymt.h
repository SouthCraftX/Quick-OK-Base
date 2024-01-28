#pragma once

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

// Specially thanks: https://github.com/MersenneTwister-Lab/TinyMT

#define XOCEAN_TINYMT64_MEXP    127
#define XOCEAN_TINYMT64_SH0     12
#define XOCEAN_TINYMT64_SH1     11
#define XOCEAN_TINYMT64_SH8     8
#define XOCEAN_TINYMT64_MASK    UINT64_C(0x7fffffffffffffff)
#define XOCEAN_TINYMT64_MUL     (1.0 / 9007199254740992.0)

struct _XOceanTinyMT64
{
    xocean_uint64_t status[2];
    xocean_uint32_t mat1 , mat2;
    xocean_uint64_t tmat;
};
typedef struct _XOceanTinyMT64 XOceanTinyMT64;

void
XOCEAN_INTERFACE(xocean_tinymt64_init)(
    XOceanTinyMT64 *    tinymt64 , 
    xocean_uint64_t     seed
);

void
XOCEAN_INTERFACE(xocean_tinymt64_init_by_array)(
    XOceanTinyMT64 *    tinymt64 ,
    xocean_pointer_t    buf ,
    xocean_size_t       len
);

#if defined(__cplusplus)
}
#endif // __cplusplus