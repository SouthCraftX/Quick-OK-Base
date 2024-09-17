#pragma once
#define __XOC_SHARED_MEMORY_POSIX_H__

// for debug
#include "include/shared_memory.h"

#if !defined(__XOC_SHARED_MEMORY_H__)
#   error Never include this header file directly. Use <xoc/shared_memory.h> \
          instead.
#endif

#include <sys/stat.h> // for S_IRUSR, S_IWUSR, etc.

#undef XOC_SM_OWNER_READ
#define XOC_SM_OWNER_READ S_IRUSR

#undef XOC_SM_OWNER_WRITE
#define XOC_SM_OWNER_WRITE S_IWUSR

#undef XOC_SM_OWNER_EXEC
#define XOC_SM_OWNER_EXEC S_IXUSR

#undef XOC_SM_GRUOP_READ
#define XOC_SM_GROUP_READ S_IRGRP

#undef XOC_SM_GROUP_WRITE
#define XOC_SM_GROUP_WRITE S_IWGRP

#undef XOC_SM_GROUP_EXEC
#define XOC_SM_GROUP_EXEC S_IXGRP

#undef XOC_SM_OTHER_READ
#define XOC_SM_OTHER_READ S_IROTH

#undef XOC_SM_OTHER_WRITE
#define XOC_SM_OTHER_WRITE S_IWOTH

#undef XOC_SM_OTHER_EXEC
#define XOC_SM_OTHER_EXEC S_IXOTH

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_shared_memory_close)(
    XOC_SharedMemory * shared_memory
){
    if (shared_memory)
        shm_unlink((xoc_ccstring_t)shared_memory);
}
