#include "include/process.h"
#include "include/memalloc.h"

QO_FORCE_INLINE
qo_size_t
__calculate_wide_string_size(
    qo_ccstring_t      command_line ,
    qo_ccstring_t      environment ,
    qo_ccstring_t      working_directory ,
    qo_uint16_t *        p_command_line_length ,     //< In: length ; Out:size
    qo_uint16_t *        p_environment_length ,      //< In: length ; Out:size
    qo_uint16_t *        p_working_directory_length  //< In: length ; Out:size
){
    const qo_uint16_t command_line_size = (*p_command_line_length ? 
        *p_command_line_length : strlen(command_line)) + sizeof(CHAR); 
        // sizeof(CHAR) for the null-terminator
    *p_command_line_length = command_line_size;

    qo_uint16_t environment_size;
    if (*p_environment_length)
    {
        environment_size = environment ? (*p_environment_length + 1) : 0;
    }
    else
    {
        environment_size = environment ? strlen(environment) + 1 : 0;
    }
    *p_environment_length = environment_size;

    qo_uint16_t working_directory_size;
    if (working_directory)
    {
        working_directory_size = working_directory ? (*p_working_directory_length + 1) : 0;
    }
    else
    {
        working_directory_size = working_directory ? strlen(working_directory) + 1 : 0;
    }
    *p_working_directory_length = working_directory_size;

    return (command_line_size + environment_size + working_directory_size) * 2;
}


qo_stat_t
QO_IMPL(qo_process_create)(
    QO_Process **      p_process ,
    qo_ccstring_t      command_line ,
    qo_ccstring_t      environment ,
    qo_ccstring_t      working_directory ,
    qo_uint16_t        command_line_length ,
    qo_uint16_t        environment_length ,
    qo_uint16_t        working_directory_length ,
    QO_ProcessStdio *  stdio
){
    qo_size_t  wcstring_size = __calculate_wide_string_size(
        command_line , environment , working_directory ,
        &command_line_length , &environment_length , &working_directory_length
    );
    PWSTR   wide_string = qo_alloc(wcstring_size) ,
            wc_cmdline  = wide_string , 
            wc_env      = environment_length ? 
                          (wc_cmdline + command_line_length) : NULL ,
            wc_workdir  = working_directory_length ?
                          (wc_env + environment_length) : NULL;
    // Lengths are written in size
#define command_line_size       command_line_length
#define environment_size        environment_length
#define working_directory_size  working_directory_length

    if(QO_UNLIKELY(!wide_string))
        return QO_OUT_OF_MEMORY;

    PROCESS_INFORMATION proc_info;
    STARTUPINFOW        startup_info;

    MultiByteToWideChar(
        CP_UTF8 , 0 , command_line , command_line_size ,
        wc_cmdline , command_line_size
    );
    if (environment)
    {
        MultiByteToWideChar(
            CP_UTF8 , 0 , environment , environment_size / 2 ,
            wc_env , environment_size
        );
    }
    if (working_directory) 
    {
        MultiByteToWideChar(
            CP_UTF8 , 0 , working_directory , working_directory_size / 2 ,
            wc_workdir , working_directory_size
        );
    }

    ZeroMemory(&proc_info , sizeof(PROCESS_INFORMATION));
    ZeroMemory(&startup_info , sizeof(STARTUPINFOW));
    startup_info.cb = sizeof(STARTUPINFO);

    CreateProcessW(NULL , wc_cmdline , NULL , NULL , FALSE , 0 , wc_env , wc_workdir , &startup_info , &proc_info);
     
    CloseHandle(proc_info.hThread);

    if (stdio)
    {
        stdio->stdin  = (QO_SysFileStream *)startup_info.hStdInput;
        stdio->stdout = (QO_SysFileStream *)startup_info.hStdOutput;
        stdio->stderr = (QO_SysFileStream *)startup_info.hStdError;
    }
    else
    {
        CloseHandle(startup_info.hStdError);
        CloseHandle(startup_info.hStdOutput);
        CloseHandle(startup_info.hStdInput);
    }

    *p_process = (QO_Process*)proc_info.hProcess;
}

#undef command_line_size
#undef environment_size
#undef working_directory_size