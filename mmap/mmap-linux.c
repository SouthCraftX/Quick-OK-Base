#include "mmap.h"
#include <sys/mman.h>

struct _XOceanMemmap
{
    xocean_pointer_t begin;
    xocean_size_t    len;
};



XOCEAN_FORCE_INLINE
int xocean_mmap_mode_to_prot(
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
    xocean_pointer_t map = mmap(NULL , len , xocean_mmap_mode_to_prot(mode) , 
                                MAP_SHARED , file->handle , 0);
    if(map == MAP_FAILED){
        switch (errno)
        {
            case EBADF:     return XOCEAN_INVALID_HANDLE;
            case ENOMEM:    return XOCEAN_OUT_OF_MEMORY;
            case EINVAL:
            case EOVERFLOW: return XOCEAN_INVALID_ARG;
            case ENFILE:    return XOCEAN_NO_RESOURCE;
            case EACCES:    return XOCEAN_BAD_TYPE;
            case EPERM:     return XOCEAN_PERMISSION_DENIED;
            default:        return XOCEAN_UNKNOWN_ERROR;
        }
    }
    return XOCEAN_OK;
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