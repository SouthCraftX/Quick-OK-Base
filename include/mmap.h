#pragma once
#define __QO_MMAP_H__

#include "fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define QO_MMAP_READ            (0)
#define QO_MMAP_READ_WRITE      (1)
#define QO_MMAP_EXEC            (1 << 2)

#define QO_MMAP_SHARED          (1 << 8)
#define QO_MMAP_PRIVATE         (2 << 8)

#define QO_MMAP_HUGEPAGE        (4 << 16)


struct _QO_MemMap;
typedef struct _QO_MemMap QO_MemMap;

/// @brief  Create a memory map for a file.
/// @param  p_memmap Pointer to the memory map object.
/// @param  file File object created by qo_sysfile_open()
/// @param  offset Offset in the file.
/// @param  length Length of the memory map.
/// @param  p_address If *p_address is not NULL, it serves as the hint for the
///         memory map address. The actual address is then written in p_address,
///         if no error occurs.
///         Special note: If you don't want to hint the address, set *p_address 
///         to NULL. p_address cannot be NULL in anycase.
/// @return The status of the operation.
/// @retval QO_OK The operation was successful.
/// @retval QO_INVALID_HANDLE file is invalid.
/// @retval QO_OUT_OF_MEMORY No enough memory to handle the operation.
/// @retval QO_INVALID_ARG Argument (like offset, length) is invalid.
/// @retval QO_NO_RESOURCE No enough resource (except memory) to handle 
///         the operation.
/// @retval QO_PERMISSION_DENIED No permission to handle the operation.
/// @retval QO_BAD_TYPE The file type (like pipe, socket) is not supported.
/// @retval QO_UNKNOWN_ERROR Other error that isn't identified by XOceanLib API.
/// @sa     qo_memmap_close()
/// @note   The memory map APIs are designed to map a file into memory and not 
///         to create a shared memory because in some platforms (such as Linux),
///         shared memory APIs may not be same as memory map APIs.
///         If you desire shared memory, see qo_shared_memory_create().
qo_stat_t
QO_INTERFACE(qo_memmap_create)(
    QO_MemMap **           p_memmap ,
    QO_SysFileStream *              file ,
    qo_offset_t            offset ,
    qo_size_t              length ,
    qo_flag32_t            mode ,
    qo_pointer_t *         p_address
);

/// @brief  Close a memory map created by qo_memmap_create().
/// @param  memmap Memory map object. NULL is allowed, in that case, the 
///         function does nothing.
void
QO_INTERFACE(qo_memmap_close)(
    QO_MemMap *   memmap
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "platform_spec/win32/mmap.h"
#elif QO_PLATFORM(POSIX)
#   include "platform_spec/posix/mmap.h"
#else
#   error "Unsupported platform"
#endif