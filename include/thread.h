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
#define __XOC_THREAD_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @note The thread structure is not exposed to the user.
struct _XOC_Thread;
typedef struct _XOC_Thread XOC_Thread;

typedef xoc_flag8_t xoc_priority_t;

enum XOC_ThreadPriority{
    XOC_THREAD_PRIORITY_LOWEST = 0,
    XOC_THREAD_PRIORITY_LOW,
    XOC_THREAD_PRIORITY_NORMAL,
    XOC_THREAD_PRIORITY_HIGH,
    XOC_THREAD_PRIORITY_HIGHEST,
    XOC_THREAD_PRIORITY_CRAZY
};

/// @brief  Create a new thread.
/// @param  p_thread The pointer to the thread.
/// @param  arguments The arguments to the thread function.
/// @param  stack_size The stack size of the thread. Set it 0 if you desire 
///         default stack size.
/// @return The status of the operation.
/// @retval XOC_OK if successful.
/// @retval XOC_OUT_OF_MEMORY if no enough memory to create the thread.
/// @retval XOC_INVALID_ARGUMENT if the arguments are invalid.
/// @retval XOC_UNKNOWN_ERROR if an unknown error occurred.
/// @sa     xoc_thread_destroy()
xoc_stat_t
XOC_INTERFACE(xoc_thread_create)(
    XOC_Thread **        p_thread ,
    xoc_pointer_t        function , 
    xoc_pointer_t        arguments ,
    xoc_size_t           stack_size
) XOC_NONNULL(1 , 2);


/// @brief      Wait for the thread to finish execution.
/// @param      thread The thread to wait for
/// @return     The status of the operation
/// @retval     XOC_OK   if successful.
/// @retval     XOC_INVALID_HANDLE if the thread is invalid.
/// @retval     XOC_INVALID_ARG if the thread is not joinable or another thread 
///             is already waiting for it (in POSIX platforms).
/// @retval     XOC_ACCESS_VIOLATED if the specified thread is caller itself or 
///             two threads tried to wait for each other.
/// @warning    Don't try to destroy the target thread while waiting, in that 
///             case, the function's behavior is undefined.
/// @note       If you intend to join multiple threads, consider xoc_thread_multijoin()
/// @sa         xoc_thread_mutiljoin()   
xoc_stat_t
XOC_INTERFACE(xoc_thread_join)(
    XOC_Thread *        thread 
) XOC_NONNULL(1);

/// @brief      Wait for the threads to finish execution.
/// @param      thread_array The array of threads to wait for
/// @param      count The number of threads to wait for
/// @return     The status of the operation. See xoc_thread_join for more details.
/// @warning    Don't try to destroy the target threads while waiting, in that 
///             case, the function's behavior is undefined.
/// @note       The function will return in advance if errors occurred when 
///             trying to wait for a thread.
/// @sa         xoc_thread_join
xoc_stat_t
XOC_INTERFACE(xoc_thread_multijoin)(
    XOC_Thread **       thread_array ,
    xoc_size_t          count    
) XOC_NONNULL(1);

/// @brief  Exit current thread.
/// @param  exit_code The exit code of the thread.
XOC_NORETURN
void
XOC_INTERFACE(xoc_thread_exit)(
    xoc_stat_t          exit_code
);

/// @brief  Get the current thread.
/// @return The current thread.
XOC_Thread *
XOC_INTERFACE(xoc_thread_self)();

/// @brief  Yield the current thread.
void
XOC_INTERFACE(xoc_thread_yield)();

/// @brief  Suspend the specified thread.
/// @param  thread The thread to suspend.
xoc_stat_t
XOC_INTERFACE(xoc_thread_suspend)(
    XOC_Thread *    thread
);

/// @brief  Suspend the current thread for specified milliseconds.
/// @param  milliseconds The number of milliseconds to sleep.
/// @note   The precision of the sleep is platform dependent.
void
XOC_INTERFACE(xoc_thread_sleep_milliseconds)(
    xoc_uint32_t milliseconds
);

/// @brief  Destroy the thread object.
/// @param  thread The thread object to destroy. NULL is allowed, in that case,
///         the function does nothing.
void
XOC_INTERFACE(xoc_thread_destory)(
    XOC_Thread * thread
);

/// @brief      Terminate the specified thread.
/// @param      thread The thread to terminate.
/// @warning    Terminating a thread is not recommanded, as it may cause 
///             unpredictable results. Avoid using this function if possible.
/// @sa         xoc_thread_exit()
void
XOC_INTERFACE(xoc_thread_terminate)(
    XOC_Thread *    thread
);

/// @brief  Get the exit code of the specified thread.
/// @param  thread The thread to get the exit code from.
/// @param  has_finished A pointer to a boolean value to indicate whether the
///         thread has finished execution.
/// @return The exit code of the thread. If the thread has not finished execution,
///         the return value is undefined.
xoc_stat_t
XOC_INTERFACE(xoc_thread_get_exit_code)(
    XOC_Thread *    thread ,
    xoc_bool_t *    has_finished
) XOC_NONNULL(1 , 2);

/// @brief  Check if the specified thread is active.
/// @param  thread The thread to check.
/// @return 0 or 1 indicates whether the thread is active. Otherwise, an error
///         code is returned.
/// @retval XOC_INVALID_HANDLE The specified thread is invalid.
xoc_stat_t
XOC_INTERFACE(xoc_thread_is_active)(
    XOC_Thread *    thread
) XOC_NONNULL(1);

/// @brief  Check if two threads are equal.
/// @return true if the two threads are equal, false otherwise.
xoc_bool_t
XOC_INTERFACE(xoc_thread_is_equal)(
    const XOC_Thread *    x ,
    const XOC_Thread *    y
) XOC_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "internel/platform_spec/win32/thread.h"
#elif XOC_PLATFORM(POSIX)
#   include "internel/platform_spec/posix/thread.h"
#endif // XOC_PLATFORM
