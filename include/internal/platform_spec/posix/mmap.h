#pragma once
#define __XOC_MMAP_POSIX_H__

// for debug
#include "include/mmap.h" 

#if !defined(__XOC_MMAP_H__)
#   error Never include this header file direcly. Use <xoc/mmap.h> instead.
#endif // !defined(__XOC_MMAP_H__)

#include <sys/mman.h>
#include <errno.h>

XOC_PURE
xoc_stat_t
__xoc_mmap_error()
{
    switch (errno)
    {
        case EBADF:     return XOC_INVALID_HANDLE;
        case ENOMEM:    return XOC_OUT_OF_MEMORY;
        case EINVAL:
        case EOVERFLOW: return XOC_INVALID_ARG;
        case ENFILE:    return XOC_NO_RESOURCE;
        case EACCES:    return XOC_BAD_TYPE;
        case EPERM:     return XOC_PERMISSION_DENIED;
        default:        return XOC_UNKNOWN_ERROR;
    }
}

struct _XOC_MemMap
{
    xoc_pointer_t begin;
    xoc_size_t    len;
};


XOC_FORCE_INLINE
int __xoc_mmap_mode_to_prot(
    xoc_flag32_t mode
){
    mode & 0xFF;
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_memmap_init)(
    XOC_MemMap *    memmap ,
    XOC_File *      file ,
    xoc_offset_t    offset ,
    xoc_size_t      len ,
    xoc_flag32_t    mode
){
    xoc_pointer_t map = mmap(NULL , len , __xoc_mmap_mode_to_prot(mode) , 
                                MAP_SHARED , file->handle , 0);
    return (map == MAP_FAILED) ? __xoc_mmap_error() : XOC_OK;
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
    if (memmap)
        munmap(memmap->begin , memmap->len);
}

MAP_PRIVATE;