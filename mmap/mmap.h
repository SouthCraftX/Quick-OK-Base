#pragma once
#define __XOC_MMAP_H__

#include "../fstream/fstream.h"

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

xoc_stat_t
XOC_INTERFACE(xoc_memmap_init)(
    XOC_MemMap *              memmap ,
    XOC_File *                file ,
    const xoc_offset_t       offset ,
    const xoc_size_t         len ,
    const xoc_flag32_t       mode ,
    const xoc_pointer_t      suggested_addr
);

xoc_pointer_t
XOC_INTERFACE(xoc_memmap_get)(
    XOC_MemMap *   memmap 
);

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