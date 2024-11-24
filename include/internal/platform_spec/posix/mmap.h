#pragma once
#define __QO_MMAP_POSIX_H__

// for debug
#include "include/mmap.h" 

#if !defined(__QO_MMAP_H__)
#   error Never include this header file direcly. Use <qo/mmap.h> instead.
#endif // !defined(__QO_MMAP_H__)

#include <sys/mman.h>
#include <errno.h>

QO_PURE
qo_stat_t
__qo_mmap_error()
{
    switch (errno)
    {
        case EBADF:     return QO_INVALID_HANDLE;
        case ENOMEM:    return QO_OUT_OF_MEMORY;
        case EINVAL:
        case EOVERFLOW: return QO_INVALID_ARG;
        case ENFILE:    return QO_NO_RESOURCE;
        case EACCES:    return QO_BAD_TYPE;
        case EPERM:     return QO_PERMISSION_DENIED;
        default:        return QO_UNKNOWN_ERROR;
    }
}

struct _QO_MemMap
{
    qo_pointer_t begin;
    qo_size_t    len;
};


QO_FORCE_INLINE
int __qo_mmap_mode_to_prot(
    qo_flag32_t mode
){
    mode & 0xFF;
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_memmap_init)(
    QO_MemMap *    memmap ,
    QO_SysFileStream *      file ,
    qo_offset_t    offset ,
    qo_size_t      len ,
    qo_flag32_t    mode
){
    qo_pointer_t map = mmap(NULL , len , __qo_mmap_mode_to_prot(mode) , 
                                MAP_SHARED , file->handle , 0);
    return (map == MAP_FAILED) ? __qo_mmap_error() : QO_OK;
}


qo_pointer_t
QO_IMPL(qo_memmap_get)(
    QO_MemMap *  memmap 
){
    return memmap->begin;
}

void
QO_IMPL(qo_memmap_close)(
    QO_MemMap *  memmap
){
    if (memmap)
        munmap(memmap->begin , memmap->len);
}

MAP_PRIVATE;