#pragma once
#define __XOC_WIN32_FILESYSTEM_H__

// for debug
#include "include/filesystem.h"

#if !defined(__XOC_FILESYSTEM_H__)
#   error Never include this file directly. Use filesystem.h instead.
#endif 

#include <fileapi.h>

xoc_stat_t
XOC_IMPL(xoc_get_disk_space_info)(
    xoc_ccstring_t  path ,
    xoc_size_t *    p_total_size ,
    xoc_size_t *    p_free_size ,
    xoc_size_t *    p_available_free_size ,
    xoc_size_t *    p_available_total_size
){
#if XOC_STSTEM_BIT(32)
    return XOC_NOT_SUPPORTED;
#else
    GetDiskFreeSpaceExA(path , p_available_free_size , p_total_size , p_free_size);
#endif
}
