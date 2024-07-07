#include "mmap.h"
#include <sys/mman.h>

struct _XOC_MemMap
{
    xoc_pointer_t begin;
    xoc_size_t    len;
};

XOC_IMPORT
xoc_stat_t
__xoc_mmap_error();

XOC_FORCE_INLINE
int __xoc_mmap_mode_to_prot(
    xoc_flag32_t mode
){
    mode & 0xFF;
}

xoc_stat_t
XOC_IMPL(xoc_memmap_init)(
    XOC_MemMap *  memmap ,
    XOC_File *    file ,
    xoc_offset_t offset ,
    xoc_size_t   len ,
    xoc_flag32_t mode
){
    xoc_pointer_t map = mmap(NULL , len , __xoc_mmap_mode_to_prot(mode) , 
                                MAP_SHARED , file->handle , 0);
    return (map == MAP_FAILED) ? __xoc_mmap_error : XOC_OK;
}


xoc_pointer_t
XOC_IMPL(xoc_memmap_get)(
    XOC_MemMap *  memmap 
){
    return memmap->begin;
}

void
XOC_IMPL(xoc_memmap_close)(
    XOC_MemMap *  memmap
){
    munmap(memmap->begin , memmap->len);
}

MAP_PRIVATE;