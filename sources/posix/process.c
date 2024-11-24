#include "process.h"
#include "memalloc.h"
#include <spawn.h>
#include <string.h>

#define FIRST_ENV_PTR_COUNT 8
#define FIRST_ENV_PTRS_SIZE (sizeof(qo_ccstring_t) * FIRST_ENV_PTR_COUNT)

QO_PURE
qo_stat_t
__changing_cwd_error()
{
    switch (errno)
    {
        case EACCES:        return QO_PERMISSION_DENIED;
        case EFAULT:        return QO_ACCESS_VIOLATED;
        case EIO:           return QO_BAD_IO;
        case ELOOP:
        case ENOENT:
        case ENOTDIR:       return QO_BAD_PATH;
        case ENOMEM:        return QO_OUT_OF_MEMORY;
        case ENAMETOOLONG:  return QO_TOO_LONG;
    }
}

// True for allocation failure
qo_bool_t
__auto_realloc(
    qo_size_t *        p_cur_size ,
    qo_ccstring_t **   p_env_str_ptrs ,
    qo_ccstring_t **   p_cur_env_str ,
    qo_ccstring_t **   p_env_ptrs_end
){
    if (*p_cur_env_str == *p_env_ptrs_end)
    {
        
    }
    
}

qo_ccstring_t *
__envl_to_envp(
    qo_ccstring_t      envl 
){
    qo_size_t          cur_size = FIRST_ENV_PTRS_SIZE;
    qo_ccstring_t *    env_str_ptrs = qo_alloc(FIRST_ENV_PTRS_SIZE) ,
                   *    cur_env_ptr = env_str_ptrs ,
                   *    env_ptrs_end;
    char * null_char = envl;
    while (qo_true)
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

qo_stat_t
QO_IMPL(qo_process_create)(
    QO_Process **      p_process ,
    qo_ccstring_t      application_path ,
    qo_ccstring_t      arguments_line ,
    qo_ccstring_t      environment ,
    qo_ccstring_t      working_directory ,
    qo_uint16_t        command_line_length ,
    qo_uint16_t        environment_length ,
    qo_uint16_t        working_directory_length ,
    QO_ProcessStdio *  p_stdio
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