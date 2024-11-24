#pragma once

// for debug
#include "include/filesystem.h"

#if !defined(__QO_FILESYSTEM_H__)
#   error Never include this header file directly. Use filesystem.h instead.
#endif

#include <sys/statvfs.h>

qo_stat_t
QO_IMPL(qo_get_disk_space_info)(
    
)
