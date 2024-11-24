#pragma once
#define __QO_WIN32_FILESYSTEM_H__

// for debug
#include "include/filesystem.h"

#if !defined(__QO_FILESYSTEM_H__)
#   error Never include this file directly. Use filesystem.h instead.
#endif 

#include <fileapi.h>

qo_stat_t
QO_IMPL(qo_get_disk_space_info)(
    qo_ccstring_t  path ,
    qo_size_t *    p_total_size ,
    qo_size_t *    p_free_size ,
    qo_size_t *    p_available_free_size ,
    qo_size_t *    p_available_total_size
){
#if QO_STSTEM_BIT(32)
    return QO_NOT_SUPPORTED;
#else
    GetDiskFreeSpaceExA(path , p_available_free_size , p_total_size , p_free_size);
#endif
}
