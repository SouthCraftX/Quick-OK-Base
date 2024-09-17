#include "process.h"
#include "memalloc.h"
#include <spawn.h>
#include <string.h>

#define FIRST_ENV_PTR_COUNT 8
#define FIRST_ENV_PTRS_SIZE (sizeof(xoc_ccstring_t) * FIRST_ENV_PTR_COUNT)

XOC_PURE
xoc_stat_t
__changing_cwd_error()
{
    switch (errno)
    {
        case EACCES:        return XOC_PERMISSION_DENIED;
        case EFAULT:        return XOC_ACCESS_VIOLATED;
        case EIO:           return XOC_BAD_IO;
        case ELOOP:
        case ENOENT:
        case ENOTDIR:       return XOC_BAD_PATH;
        case ENOMEM:        return XOC_OUT_OF_MEMORY;
        case ENAMETOOLONG:  return XOC_TOO_LONG;
    }
}

// True for allocation failure
xoc_bool_t
__auto_realloc(
    xoc_size_t *        p_cur_size ,
    xoc_ccstring_t **   p_env_str_ptrs ,
    xoc_ccstring_t **   p_cur_env_str ,
    xoc_ccstring_t **   p_env_ptrs_end
){
    if (*p_cur_env_str == *p_env_ptrs_end)
    {
        
    }
    
}

xoc_ccstring_t *
__envl_to_envp(
    xoc_ccstring_t      envl 
){
    xoc_size_t          cur_size = FIRST_ENV_PTRS_SIZE;
    xoc_ccstring_t *    env_str_ptrs = xoc_alloc(FIRST_ENV_PTRS_SIZE) ,
                   *    cur_env_ptr = env_str_ptrs ,
                   *    env_ptrs_end;
    char * null_char = envl;
    while (xoc_true)
    {
        char * null_char = strchr(envl , '\0');
        if (*(++null_char))
        {
            __auto_realloc(&cur_size , &env_str_ptrs , &cur_env_ptr , &env_ptrs_end);
            *cur_env_ptr = null_char;
            envl += 
        }
        else
        {
            break;
        }
        
    }
    
}

xoc_stat_t
XOC_IMPL(xoc_process_create)(
    XOC_Process **      p_process ,
    xoc_ccstring_t      application_path ,
    xoc_ccstring_t      arguments_line ,
    xoc_ccstring_t      environment ,
    xoc_ccstring_t      working_directory ,
    xoc_uint16_t        command_line_length ,
    xoc_uint16_t        environment_length ,
    xoc_uint16_t        working_directory_length ,
    XOC_ProcessStdio *  p_stdio
){
    posix_spawnattr_t spawn_attr;
    posix_spawn_file_actions_t file_actions;

    posix_spawnattr_init(&spawn_attr);
    posix_spawn_file_actions_init(&file_actions);

    // Error occurs when changing the working directory
    if (working_directory && chdir(working_directory)) 
        return __changing_cwd_error();
    
    pid_t child_pid;
    int stat = posix_spawn(
        &child_pid , application_path, &file_actions, &spawn_attr ,);
}