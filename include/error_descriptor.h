/*******************************************************************************
 * @headerfile  include/error_descriptor.h
 * @addtogroup  Headers under the MIT License
 * @brief       Error descriptor and related interfaces
 * @author      XOcean <https://github.com/SouthCraftX>
 * 
 * @addtogroup  Error Descriptor
 * 
 */
#pragma once
#define __QO_ERROR_DESCRIPTOR_H__

#include "base.h"

#if defined(__cplusplus)
extern "C"{
#endif // __cplusplus

// This structure is designed not to be exposed to the user.
struct _QO_ErrorDescriptor;
typedef struct _QO_ErrorDescriptor QO_ErrDesc;

/// @brief The strategy to allocate memory for the error message used in 
/// function `qo_errdesc_get_message_rescursively`.
enum QO_ErrDescMsgAllocStrategy
{
    /// @brief Preallocate at first, and extend it halfway if needed.
    /// The unused space at the end of message will not be shrinked.
    QO_ERRDESC_MSG_PREALLOC = 0,

    /// @brief Preallocate at first, and extend it halfway if needed.
    /// The unused space at end of message will be shrinked.
    /// It is slower than `QO_ERRDESC_MSG_PREALLOC`.
    QO_ERRDESC_MSG_PREALLOC_SHRINK,

    /// @brief Never overallocate. 
    /// @note To achieve this, `qo_errdesc_get_message_rescursively`
    /// will iterate over the error descriptor chain to calculate the message size.
    /// Then, go to the beginning of the chain and allocate the memory to fit the
    /// message, followed by copying the message from error descriptors.
    /// It could be slow as it may leads to low cache hit rate while moving from
    /// one to another error descriptor.
    QO_ERRDESC_MSG_CONSERVATIVE       
};

/// @brief Reduce the reference count of the error descriptor and destrory the 
/// error descriptor if the reference count is zero. 
/// @param `error_descriptor` The error descriptor. Can be null, in that case,
/// the function will do nothing.
void
QO_INTERFACE(qo_errdesc_unref)(
    QO_ErrDesc *   error_descriptor
);

/// @brief Increase the reference count of the error descriptor.
/// @param `error_descriptor` The error descriptor.
/// @sa `qo_errdesc_unref`
void
QO_INTERFACE(qo_errdesc_ref)(
    QO_ErrDesc *   error_descriptor
);

/// @brief Create a new error descriptor with `suberror` (can be null) as its 
/// suberror and `private_data_size` as the size of the private data.
/// @param `suberror` The suberror of the new error descriptor. Can be null if
/// you desire a individual error descriptor.
/// @param `private_data_size` The size of the private data.
/// @return The new error descriptor. NULL if no more memory is available.
QO_ErrDesc *
QO_INTERFACE(qo_errdesc_wrap)(
    QO_ErrDesc *   suberror ,
    qo_size_t      private_data_size
);

/// @brief Rescurively get the message of the error descriptor and its suberror.
///
/// @param `error_descriptor` The error descriptor.
/// @param `message_buffer` The buffer to store the message. Can be null, see
/// the following description for more.
/// @param `seperator` The seperator between each error message. Set it null if
/// you don't want to add seperator.
/// @param `message_buffer_size` The size of the buffer. Can be null, see the
/// following description for more.
/// @param `alloc_strategy` The allocation strategy. Will be ignored in some case,
/// see the following description for more.
///
/// @if `message_buffer` is null, the function will return the message string, with
/// `message_buffer_size` written with the message size if `message_buffer_size` 
/// is not null. The return string can be freed by `qo_free` later. 
/// @ifnot The function will write the message into `message_buffer` at required
/// size if `message_buffer_size` is not null, and return `message_buffer`. In this 
/// case, `alloc_strategy` will be ignored.
///
/// @warning You should ensure the buffer is large enough if `message_buffer` is 
/// null, when the function will write until messages are reached.
///
/// @return The message string if no error occurred. 
/// @retval NULL if no more memory is available, in this case, `message_buffer_size`
/// will not be written.
/// @retval QO_INVALID_ADDRESS if `alloc_stragy` is invalid.
qo_cstring_t
QO_INTERFACE(qo_errdesc_get_message_rescursively)(
    QO_ErrDesc *           error_descriptor ,
    qo_cstring_t           message_buffer ,
    qo_cstring_t           seperator ,
    qo_size_t *            message_buffer_size ,
    qo_size_t              seperator_length ,
    enum QO_ErrDescMsgAllocStrategy alloc_strategy
) QO_NONNULL(1);

/// @brief Get the message of the error descriptor.
/// @param error_descriptor The error descriptor.
/// @param message_buffer The buffer to store the message. Set it null if you
/// don't want to provide your own buffer.
/// @param message_buffer_size The size of the buffer. Set it null if you don't
/// want to get this infomation or hint that message buffer is large enough.
/// @if `message_buffer` is null, the function will return the message string, with 
/// `message_buffer_size` written with the message size if `message_buffer_size` is not
/// null. There is no need to free the returned string, as it will be freed when
/// `error_descriptor` is freed. @note Modifying the string is not allowed. To get a 
/// modifiable string, consider the following case.
/// @ifnot the function will write the message into `message_buffer` at required
/// size if `message_buffer_size` is not null, and return `message_buffer`. The error 
/// descriptor or this function does not possess the ownership of the buffer.
/// @warning You should ensure the buffer is large enough if `message_buffer_size` 
/// is null, when the function will write until all messages are reached.
qo_cstring_t
QO_INTERFACE(qo_errdesc_get_message)(
    QO_ErrDesc *           error_descriptor ,
    qo_cstring_t           message_buffer ,
    qo_size_t *            message_buffer_size
) QO_NONNULL(1);

/// @brief Get the size of the message of the error descriptor.
/// @param error_descriptor The error descriptor.
/// @return The size of the message of the error descriptor.
qo_size_t
QO_INTERFACE(qo_errdesc_get_message_size)(
    QO_ErrDesc *   error_descriptor
) QO_NONNULL(1);

/// @brief Get the suberror of the error descriptor.
/// @param error_descriptor The error descriptor.
/// @return The suberror of the error descriptor.
/// @retval NULL if no suberror.
QO_ErrDesc *
QO_INTERFACE(qo_errdesc_get_suberror)(
    QO_ErrDesc *   error_descriptor
) QO_NONNULL(1);

/// @brief Get the error id of the error descriptor.
/// @param error_descriptor The error descriptor.
/// @return The error id of the error descriptor.
qo_stat_t
QO_INTERFACE(qo_errdesc_get_errid)(
    QO_ErrDesc *   error_descriptor
) QO_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus

#define qo_errdesc_ref QO_IMPL(qo_errdesc_ref)
#define qo_errdesc_unref QO_IMPL(qo_errdesc_unref)
#define qo_errdesc_get_message_rescursively QO_IMPL(qo_errdesc_get_message_rescursively)
#define qo_errdesc_get_message QO_IMPL(qo_errdesc_get_message)
#define qo_errdesc_get_message_size QO_IMPL(qo_errdesc_get_message_size)
#define qo_errdesc_get_suberror QO_IMPL(qo_errdesc_get_suberror)
#define qo_errdesc_get_errid QO_IMPL(qo_errdesc_get_errid)