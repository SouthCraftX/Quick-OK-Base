#pragma once
#define __XOC_MMAP_H__

#include "fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define XOC_MMAP_READ            (0)
#define XOC_MMAP_READ_WRITE      (1)
#define XOC_MMAP_EXEC            (1 << 2)

#define XOC_MMAP_SHARED          (1 << 8)
#define XOC_MMAP_PRIVATE         (2 << 8)

#define XOC_MMAP_HUGEPAGE        (4 << 16)


struct _XOC_MemMap;
typedef struct _XOC_MemMap XOC_MemMap;

/// @brief  Create a memory map for a file.
/// @param  p_memmap Pointer to the memory map object.
/// @param  file File object created by xoc_file_open()
/// @param  offset Offset in the file.
/// @param  length Length of the memory map.
/// @param  p_address If *p_address is not NULL, it serves as the hint for the
///         memory map address. The actual address is then written in p_address,
///         if no error occurs.
///         Special note: If you don't want to hint the address, set *p_address 
///         to NULL. p_address cannot be NULL in anycase.
/// @return The status of the operation.
/// @retval XOC_OK The operation was successful.
/// @retval XOC_INVALID_HANDLE file is invalid.
/// @retval XOC_OUT_OF_MEMORY No enough memory to handle the operation.
/// @retval XOC_INVALID_ARG Argument (like offset, length) is invalid.
/// @retval XOC_NO_RESOURCE No enough resource (except memory) to handle 
///         the operation.
/// @retval XOC_PERMISSION_DENIED No permission to handle the operation.
/// @retval XOC_BAD_TYPE The file type (like pipe, socket) is not supported.
/// @retval XOC_UNKNOWN_ERROR Other error that isn't identified by XOceanLib API.
/// @sa     xoc_memmap_close()
/// @note   The memory map APIs are designed to map a file into memory and not 
///         to create a shared memory because in some platforms (such as Linux),
///         shared memory APIs may not be same as memory map APIs.
///         If you desire shared memory, see xoc_shared_memory_create().
xoc_stat_t
XOC_INTERFACE(xoc_memmap_create)(
    XOC_MemMap **           p_memmap ,
    XOC_File *              file ,
    xoc_offset_t            offset ,
    xoc_size_t              length ,
    xoc_flag32_t            mode ,
    xoc_pointer_t *         p_address
);

/// @brief  Close a memory map created by xoc_memmap_create().
/// @param  memmap Memory map object. NULL is allowed, in that case, the 
///         function does nothing.
void
XOC_INTERFACE(xoc_memmap_close)(
    XOC_MemMap *   memmap
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "platform_spec/win32/mmap.h"
#elif XOC_PLATFORM(POSIX)
#   include "platform_spec/posix/mmap.h"
#else
#   error "Unsupported platform"
#endif