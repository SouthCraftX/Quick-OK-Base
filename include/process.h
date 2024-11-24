#pragma once
#define __QO_PROCESS_H__

#include "thread.h"
#include "fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Process;
typedef struct _QO_Process QO_Process;

struct _QO_ProcessStdio
{
    QO_File *  stdin;
    QO_File *  stdout;
    QO_File *  stderr;
};
typedef struct _QO_ProcessStdio QO_ProcessStdio;

/// @remark In most of platforms, a 32-bit integer is enough to represent a
///         process ID.
typedef qo_flag32_t    qo_pid_t;

/// @brief  Create a new process.
/// @param  process A pointer to a new process. If error occurs, the process 
///         object will not be written.
/// @param  command_line The command line to execute.
/// @param  environment The environment of the process. Separate each
///         environment variable with a null character, and terminate the string
///         with doublele null characters. NULL is allowed, in that case, new
///         process will inherit the environment of the current process.
/// @note   To avoid capability issues, do not use '=' in the name of environment
///         variables.
/// @param  working_directory The working directory of the process. NULL is 
///         allowed, in that case, new process will inherit the working 
///         directory of the current process.
/// @note   All input strings should be encoded in UTF-8.
/// @param  command_line_length The length of the command line. Set it 0 to use
///         the length of the command line string.
/// @param  environment_length The length of the environment string. Set it 0 to
///         use the length of the environment string. If environment is NULL,
///         this parameter is ignored.
/// @param  working_directory_length The length of the working directory string.
///         Set it 0 to use the length of the working directory string. If
///         working_directory is NULL, this parameter is ignored.
/// @param  p_stdio A pointer to the standard input/output/error streams of the
///         new process. NULL is allowed if you don't want this infomation.
///         Caller must close the file objects in the stdio structure if they're
///         no longer needed. @sa qo_file_close().
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_process_create)(
    QO_Process **      p_process ,
    qo_ccstring_t      application_path ,
    qo_ccstring_t      arguments_line ,
    qo_ccstring_t      environment ,
    qo_ccstring_t      working_directory ,
    qo_uint16_t        command_line_length ,
    qo_uint16_t        environment_length ,
    qo_uint16_t        working_directory_length ,
    QO_ProcessStdio *  p_stdio
) QO_NONNULL(1 , 2);

/// @brief  Get the current process.
QO_Process *
QO_INTERFACE(qo_process_get_current)();

/// @brief  Get the process ID of a process.
/// @param  process The process object
/// @return The process ID of the process.
qo_pid_t
QO_INTERFACE(qo_process_get_pid)(
    QO_Process *           process
) QO_NONNULL(1);

/// @brief  Get the current process ID.
/// @return The current process ID.
qo_pid_t
QO_INTERFACE(qo_process_get_current_pid)();


qo_stat_t
QO_INTERFACE(qo_process_adjust_priority)(
    QO_Process *           process ,
    enum QO_ThreadPriority priority
);

qo_stat_t
QO_INTERFACE(qo_process_get_priority)(
    QO_Process *           process 
);

/// @brief  Get the exit code of a process.
/// @param  process The process object.
/// @param  exit_code A pointer to a variable to store the exit code of the 
///         process.
/// @return The status of the operation.
qo_stat_t
QO_INTERFACE(qo_process_get_exit_code)(
    QO_Process *           process ,
    qo_stat_t *            exit_code
) QO_NONNULL(1 , 2);

/// @brief Exit the current process.
/// @param exit_code The exit code of the process.
/// @note  Before you call this function, you should do some clean up work, such
///        as freeing resources.
QO_NORETURN
void 
QO_INTERFACE(qo_process_exit_current)(
    qo_stat_t  exit_code
);

/// @brief      Kill a process.
/// @param      process The process object. If process is caller itself, this
///             function will behave like qo_process_exit_current().
/// @param      wait If true and no error occurs, the caller will wait for the 
///             process to exit.
/// @param      p_exit_code A pointer to a variable to store the exit code of 
///             the process. If wait is false or error occurs, this parameter is
///             not written. NULL is allowed, if you don't want this infomation.
/// @return     The status of the operation.
/// @retval     QO_OK The operation succeeds.
/// @retval     QO_INVALID_HANDLE The process object is invalid.
/// @retval     QO_PERMISSION_DENIED The caller does not have permission to 
///             kill the process.
/// @retval     QO_UNKNOWN_ERROR Other error occurred 
/// @warning    If operation succeeds, the process object will be invalid and
///             should not be used anymore, or undefined behavior will occur.
qo_stat_t
QO_INTERFACE(qo_process_kill)(
    QO_Process *   process ,
    qo_bool_t      wait ,
    qo_stat_t *    p_exit_code
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#    include "internal/platform_spec/win32/process.h"
#else
#    include "internal/platform_spec/posix/process.h"
#endif