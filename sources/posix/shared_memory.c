#include "shared_memory.h"
#include "memalloc.h"
#include "random.h"
#include "common.h"
#include "mmap.h"
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

#define DEFAULT_MAP_NAME_SIZE 8

XOC_PURE
xoc_stat_t
__fd_truncating_error()
{
    switch (errno)
    {
        case EACCES:    return XOC_PERMISSION_DENIED;
        default:        return XOC_OUT_OF_MEMORY;
    }
}

XOC_PURE
xoc_stat_t
__shm_opening_error()
{
    switch (errno)
    {
        case EACCES:        return XOC_PERMISSION_DENIED;
        case EEXIST:        return XOC_ALREADY_EXISTS;
        case EINVAL:        return XOC_INVALID_ARG;     // name invalid
        case ENAMETOOLONG:  return XOC_TOO_LONG;
        case ENFILE:
        case EMFILE:        return XOC_NO_RESOURCE;
        case ENOENT:        return XOC_NOT_FOUND;
    }
}

xoc_stat_t
XOC_IMPL(xoc_shared_mempry_create)(
    XOC_SharedMemory ** p_shared_memory ,
    xoc_cstring_t *     p_name ,
    xoc_flag32_t        access_mode ,
    xoc_flag32_t        security_flags ,
    xoc_pointer_t *     p_memory ,
    xoc_size_t          memory_size ,
    xoc_size_t *        p_name_size
){
    xoc_cstring_t name;
    xoc_size_t    name_size = p_name_size ? *p_name_size : DEFAULT_MAP_NAME_SIZE;
    char name_vla[name_size];

    if(!p_name) // // Generate a name
    {
        xoc_rand_string(name_vla , name_size - 1 , XOC_CHAR_SET_ULN , XOC_CHAR_SET_ULN_LEN);
        name = name_vla;
    }
    else
    {
        name = *p_name;
    }
    
    int fd = shm_open(name , access_mode , security_flags);
    if (fd == -1)
        return __shm_opening_error();

    xoc_size_t memory_size = memory_size + name_size;
    // We use the head of the shared memory to store the name of it because we
    // need to close the shared memory with the name.
    const int ftrun_ret =  ftruncate(fd , memory_size);
    close(fd);  // We don't need the file descriptor anymore.
    if (ftrun_ret == -1)
    {
        shm_unlink(name);
        return __fd_truncating_error();
    }

    xoc_pointer_t memory = mmap(
        NULL , memory_size , access_mode , MAP_SHARED , fd , 0
    );

    if (memory == MAP_FAILED)
    {
        shm_unlink(name);
        return __xoc_mmap_error();
    }
    memcpy(memory , name , name_size);
    *p_memory = memory + name_size;
    *p_shared_memory = (XOC_SharedMemory *)memory;
    
    return XOC_OK;
}

