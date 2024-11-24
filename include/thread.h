/*******************************************************************************
 * @headerfile  include/thread.h
 * @addtogroup  Headers under the MIT License
 * @note        This header is part of XOceanLib
 * @brief       The thread and interfaces.
 * @author      XOcean <https://github.com/SouthCraftX>
 * 
 * @version     Alpha 0.0.0
 * 
 * @addtogroup  Parallelization
 * @addtogroup  Simple System-API Redirecting Layer
 * 
 * Changelogs:
 * -----------------------------------------------------------------------------
 * Who      | When       | What
 * XOcean   | ?          | First created this file
 * 
 * -----------------------------------------------------------------------------
 */

#pragma once
#define __QO_THREAD_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @note The thread structure is not exposed to the user.
struct _QO_Thread;
typedef struct _QO_Thread QO_Thread;

typedef qo_flag8_t qo_priority_t;

enum QO_ThreadPriority{
    QO_THREAD_PRIORITY_LOWEST = 0,
    QO_THREAD_PRIORITY_LOW,
    QO_THREAD_PRIORITY_NORMAL,
    QO_THREAD_PRIORITY_HIGH,
    QO_THREAD_PRIORITY_HIGHEST,
    QO_THREAD_PRIORITY_CRAZY
};

/// @brief  Create a new thread.
/// @param  p_thread The pointer to the thread.
/// @param  arguments The arguments to the thread function.
/// @param  stack_size The stack size of the thread. Set it 0 if you desire 
///         default stack size.
/// @return The status of the operation.
/// @retval QO_OK if successful.
/// @retval QO_OUT_OF_MEMORY if no enough memory to create the thread.
/// @retval QO_INVALID_ARGUMENT if the arguments are invalid.
/// @retval QO_UNKNOWN_ERROR if an unknown error occurred.
/// @sa     qo_thread_destroy()
qo_stat_t
QO_INTERFACE(qo_thread_create)(
    QO_Thread **        p_thread ,
    qo_pointer_t        function , 
    qo_pointer_t        arguments ,
    qo_size_t           stack_size
) QO_NONNULL(1 , 2);


/// @brief      Wait for the thread to finish execution.
/// @param      thread The thread to wait for
/// @return     The status of the operation
/// @retval     QO_OK   if successful.
/// @retval     QO_INVALID_HANDLE if the thread is invalid.
/// @retval     QO_INVALID_ARG if the thread is not joinable or another thread 
///             is already waiting for it (in POSIX platforms).
/// @retval     QO_ACCESS_VIOLATED if the specified thread is caller itself or 
///             two threads tried to wait for each other.
/// @warning    Don't try to destroy the target thread while waiting, in that 
///             case, the function's behavior is undefined.
/// @note       If you intend to join multiple threads, consider qo_thread_multijoin()
/// @sa         qo_thread_mutiljoin()   
qo_stat_t
QO_INTERFACE(qo_thread_join)(
    QO_Thread *        thread 
) QO_NONNULL(1);

/// @brief      Wait for the threads to finish execution.
/// @param      thread_array The array of threads to wait for
/// @param      count The number of threads to wait for
/// @return     The status of the operation. See qo_thread_join for more details.
/// @warning    Don't try to destroy the target threads while waiting, in that 
///             case, the function's behavior is undefined.
/// @note       The function will return in advance if errors occurred when 
///             trying to wait for a thread.
/// @sa         qo_thread_join
qo_stat_t
QO_INTERFACE(qo_thread_multijoin)(
    QO_Thread **       thread_array ,
    qo_size_t          count    
) QO_NONNULL(1);

/// @brief  Exit current thread.
/// @param  exit_code The exit code of the thread.
QO_NORETURN
void
QO_INTERFACE(qo_thread_exit)(
    qo_stat_t          exit_code
);

/// @brief  Get the current thread.
/// @return The current thread.
QO_Thread *
QO_INTERFACE(qo_thread_self)();

/// @brief  Yield the current thread.
void
QO_INTERFACE(qo_thread_yield)();

/// @brief  Suspend the specified thread.
/// @param  thread The thread to suspend.
qo_stat_t
QO_INTERFACE(qo_thread_suspend)(
    QO_Thread *    thread
);

/// @brief  Suspend the current thread for specified milliseconds.
/// @param  milliseconds The number of milliseconds to sleep.
/// @note   The precision of the sleep is platform dependent.
void
QO_INTERFACE(qo_thread_sleep_milliseconds)(
    qo_uint32_t milliseconds
);

/// @brief  Destroy the thread object.
/// @param  thread The thread object to destroy. NULL is allowed, in that case,
///         the function does nothing.
void
QO_INTERFACE(qo_thread_destory)(
    QO_Thread * thread
);

/// @brief      Terminate the specified thread.
/// @param      thread The thread to terminate.
/// @warning    Terminating a thread is not recommanded, as it may cause 
///             unpredictable results. Avoid using this function if possible.
/// @sa         qo_thread_exit()
void
QO_INTERFACE(qo_thread_terminate)(
    QO_Thread *    thread
);

/// @brief  Get the exit code of the specified thread.
/// @param  thread The thread to get the exit code from.
/// @param  has_finished A pointer to a boolean value to indicate whether the
///         thread has finished execution.
/// @return The exit code of the thread. If the thread has not finished execution,
///         the return value is undefined.
qo_stat_t
QO_INTERFACE(qo_thread_get_exit_code)(
    QO_Thread *    thread ,
    qo_bool_t *    has_finished
) QO_NONNULL(1 , 2);

/// @brief  Check if the specified thread is active.
/// @param  thread The thread to check.
/// @return 0 or 1 indicates whether the thread is active. Otherwise, an error
///         code is returned.
/// @retval QO_INVALID_HANDLE The specified thread is invalid.
qo_stat_t
QO_INTERFACE(qo_thread_is_active)(
    QO_Thread *    thread
) QO_NONNULL(1);

/// @brief  Check if two threads are equal.
/// @return true if the two threads are equal, false otherwise.
qo_bool_t
QO_INTERFACE(qo_thread_is_equal)(
    const QO_Thread *    x ,
    const QO_Thread *    y
) QO_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/thread.h"
#elif QO_PLATFORM(POSIX)
#   include "internal/platform_spec/posix/thread.h"
#endif // QO_PLATFORM
