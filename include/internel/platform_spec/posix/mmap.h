#include "mmap.h"
#include <sys/mman.h>

struct _XOceanMemmap
{
    xocean_pointer_t begin;
    xocean_size_t    len;
};

XOCEAN_IMPORT
xocean_stat_t
__xocean_mmap_error();

XOCEAN_FORCE_INLINE
int __xocean_mmap_mode_to_prot(
    xocean_flag32_t mode
){
    mode & 0xFF;
}

xocean_stat_t
XOCEAN_IMPL(xocean_memmap_init)(
    XOceanMemmap *  memmap ,
    XOceanFile *    file ,
    xocean_offset_t offset ,
    xocean_size_t   len ,
    xocean_flag32_t mode
){
    xocean_pointer_t map = mmap(NULL , len , __xocean_mmap_mode_to_prot(mode) , 
                                MAP_SHARED , file->handle , 0);
    return (map == MAP_FAILED) ? __xocean_mmap_error : XOCEAN_OK;
}


xocean_pointer_t
XOCEAN_IMPL(xocean_memmap_get)(
    XOceanMemmap *  memmap 
){
    return memmap->begin;
}

void
XOCEAN_IMPL(xocean_memmap_close)(
    XOceanMemmap *  memmap
){
    munmap(memmap->begin , memmap->len);
}

MAP_PRIVATE;