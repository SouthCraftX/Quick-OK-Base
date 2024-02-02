#pragma once

#include "../fstream/fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define XOCEAN_MMAP_READ            (0)
#define XOCEAN_MMAP_READ_WRITE      (1)
#define XOCEAN_MMAP_EXEC            (1 << 2)

#define XOCEAN_MMAP_SHARED          (1 << 8)
#define XOCEAN_MMAP_PRIVATE         (2 << 8)

#define XOCEAN_MMAP_HUGEPAGE        (4 << 16)


struct _XOceanMemmap;
typedef struct _XOceanMemmap XOceanMemmap;

xocean_stat_t
XOCEAN_INTERFACE(xocean_memmap_init)(
    XOceanMemmap *      memmap ,
    XOceanFile *        file ,
    const xocean_offset_t     offset ,
    const xocean_size_t       len ,
    const xocean_flag32_t     mode ,
    const xocean_pointer_t    suggested_addr
);

xocean_pointer_t
XOCEAN_INTERFACE(xocean_memmap_get)(
    XOceanMemmap *   memmap 
);

void
XOCEAN_INTERFACE(xocean_memmap_close)(
    XOceanMemmap *   memmap
);

#if defined(__cplusplus)
}
#endif // __cplusplus