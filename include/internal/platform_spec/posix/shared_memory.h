#pragma once
#define __QO_SHARED_MEMORY_POSIX_H__

// for debug
#include "include/shared_memory.h"

#if !defined(__QO_SHARED_MEMORY_H__)
#   error Never include this header file directly. Use <qo/shared_memory.h> \
          instead.
#endif

#include <sys/stat.h> // for S_IRUSR, S_IWUSR, etc.

#undef QO_SM_OWNER_READ
#define QO_SM_OWNER_READ S_IRUSR

#undef QO_SM_OWNER_WRITE
#define QO_SM_OWNER_WRITE S_IWUSR

#undef QO_SM_OWNER_EXEC
#define QO_SM_OWNER_EXEC S_IXUSR

#undef QO_SM_GRUOP_READ
#define QO_SM_GROUP_READ S_IRGRP

#undef QO_SM_GROUP_WRITE
#define QO_SM_GROUP_WRITE S_IWGRP

#undef QO_SM_GROUP_EXEC
#define QO_SM_GROUP_EXEC S_IXGRP

#undef QO_SM_OTHER_READ
#define QO_SM_OTHER_READ S_IROTH

#undef QO_SM_OTHER_WRITE
#define QO_SM_OTHER_WRITE S_IWOTH

#undef QO_SM_OTHER_EXEC
#define QO_SM_OTHER_EXEC S_IXOTH

QO_FORCE_INLINE
void
QO_IMPL(qo_shared_memory_close)(
    QO_SharedMemory * shared_memory
){
    if (shared_memory)
        shm_unlink((qo_ccstring_t)shared_memory);
}
