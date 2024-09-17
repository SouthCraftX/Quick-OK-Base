#pragma once

// for debug
#include "include/filesystem.h"

#if !defined(__XOC_FILESYSTEM_H__)
#   error Never include this header file directly. Use filesystem.h instead.
#endif

#include <sys/statvfs.h>

xoc_stat_t
XOC_IMPL(xoc_get_disk_space_info)(
    
)
