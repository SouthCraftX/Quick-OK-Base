#pragma once
#define __QO_FILESYSTEM_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @brief  Get disk space information.
/// @param  path The path of the disk. It can be a directory in the file system.
/// @param  p_total_size Pointer to the total size of the disk. NULL is allowed
///         if you don't need this information.
/// @param  p_free_size Pointer to the free size of the disk. NULL is allowed
///         if you don't need this information.
/// @param  p_available_total_size Pointer to the available total size of the disk.
///         NULL is allowed if you don't need this information.
/// @param  p_available_free_size Pointer to the available free size of the disk.
///         NULL is allowed if you don't need this information.
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_get_disk_space_info)(
    qo_ccstring_t  path ,
    qo_size_t *    p_total_size ,
    qo_size_t *    p_free_size ,
    qo_size_t *    p_available_total_size ,
    qo_size_t *    p_available_free_size
) QO_NONNULL(1);

/// @brief  Find traversal character in the path.
/// @param  path The path to find traversal character.
/// @param  length The length of the path. 0 is allowed, in that case, the
///
/// @return Pointer to the traversal character in the path. NULL if not found.
qo_ccstring_t
QO_INTERFACE(qo_path_find_traversal)(
    qo_ccstring_t path ,
    qo_size_t     length
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#include "internal/universal/filesystem.h"

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/filesystem.h"
#else
#   include "internal/platform_spec/posix/filesystem.h"
#endif 