#include "shared_memory.h"
#include "memalloc.h"
#include "random.h"
#include "common.h"
#include "mmap.h"
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

#define DEFAULT_MAP_NAME_SIZE 8

QO_PURE
qo_stat_t
__fd_truncating_error()
{
    switch (errno)
    {
        case EACCES:    return QO_PERMISSION_DENIED;
        default:        return QO_OUT_OF_MEMORY;
    }
}

QO_PURE
qo_stat_t
__shm_opening_error()
{
    switch (errno)
    {
        case EACCES:        return QO_PERMISSION_DENIED;
        case EEXIST:        return QO_ALREADY_EXISTS;
        case EINVAL:        return QO_INVALID_ARG;     // name invalid
        case ENAMETOOLONG:  return QO_TOO_LONG;
        case ENFILE:
        case EMFILE:        return QO_NO_RESOURCE;
        case ENOENT:        return QO_NOT_FOUND;
    }
}

qo_stat_t
QO_IMPL(qo_shared_mempry_create)(
    QO_SharedMemory ** p_shared_memory ,
    qo_cstring_t *     p_name ,
    qo_flag32_t        access_mode ,
    qo_flag32_t        security_flags ,
    qo_pointer_t *     p_memory ,
    qo_size_t          memory_size ,
    qo_size_t *        p_name_size
){
    qo_cstring_t name;
    qo_size_t    name_size = p_name_size ? *p_name_size : DEFAULT_MAP_NAME_SIZE;
    char name_vla[name_size];

    if(!p_name) // // Generate a name
    {
        qo_rand_string(name_vla , name_size - 1 , QO_CHAR_SET_ULN , QO_CHAR_SET_ULN_LEN);
        name = name_vla;
    }
    else
    {
        name = *p_name;
    }
    
    int fd = shm_open(name , access_mode , security_flags);
    if (fd == -1)
        return __shm_opening_error();

    qo_size_t memory_size = memory_size + name_size;
    // We use the head of the shared memory to store the name of it because we
    // need to close the shared memory with the name.
    const int ftrun_ret =  ftruncate(fd , memory_size);
    close(fd);  // We don't need the file descriptor anymore.
    if (ftrun_ret == -1)
    {
        shm_unlink(name);
        return __fd_truncating_error();
    }

    qo_pointer_t memory = mmap(
        NULL , memory_size , access_mode , MAP_SHARED , fd , 0
    );

    if (memory == MAP_FAILED)
    {
        shm_unlink(name);
        return __qo_mmap_error();
    }
    memcpy(memory , name , name_size);
    *p_memory = memory + name_size;
    *p_shared_memory = (QO_SharedMemory *)memory;
    
    return QO_OK;
}

