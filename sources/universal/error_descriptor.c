/*******************************************************************************
    @file       source/generic/error_descriptor.c
    @addtogroup Source Codes under the MIT License
    @brief      Implements error descriptor APIs.
    @author     XOcean <https://github.com/SouthCraftX>
    
    @addtogroup Error Descriptor

    Changelog:
    ----------------------------------------------------------------------------
    Who     | When       | What
    XOcean  | ?          | First created this file.
    ----------------------------------------------------------------------------   

*******************************************************************************/

#include "error_descriptor.h"
#include "memalloc.h"

#include <string.h>

#define REALLOC_RATE(n) ((n) * 3 / 2) // Avoid floating point 1.5
#define FIRST_ALLOC_SIZE (64)

struct _QO_ErrDescPrivData
{
    qo_size_t      size;       
    qo_intmax_t    context[];
};
typedef struct _QO_ErrDescPrivData QO_ErrDescPrivData;

/// @remark Mostly, sizeof(_QO_ErrorDescriptor) == 32 bytes (without private area)
/// in 64-bit platforms, sizeof(_QO_ErrorDescriptor) == 20 bytes (without 
/// private area) in 32-bit platforms.
struct _QO_ErrorDescriptor
{
    qo_flag32_t     ref_count;  
    qo_stat_t       error_code; 

    /// @brief Get the error message.
    /// @param `self` The error descriptor.
    /// @param `message_buffer_size` The size of the message buffer. Set it null if
    /// you don't want this information.
    /// @note This messager is implemented by user
    qo_cstring_t
    (* messager)(
        QO_ErrDesc * ,
        qo_size_t *   
    );

    /// @brief Destructor of the error descriptor.
    /// @param `self` The error descriptor.
    void
    (* destructor)(
        QO_ErrDesc *  
    );

    /// @brief The suberror of the error descriptor. NULL if there is no suberror.
    QO_ErrDesc *           suberror;

    /// @brief The private data of the error descriptor.
    /// @note  It is managed by error descriptor creator.
    QO_ErrDescPrivData     priv_data;
};

QO_EXPORT
void
QO_IMPL(qo_errdesc_ref)(
    QO_ErrDesc *   error_descriptor
){
    error_descriptor->ref_count++;
}

QO_EXPORT
void
QO_IMPL(qo_errdesc_unref)(
    QO_ErrDesc *   error_descriptor
){
    if (error_descriptor && ((--error_descriptor->ref_count) == 0))
        error_descriptor->destructor(error_descriptor);
}

QO_EXPORT
QO_ErrDesc *
QO_IMPL(qo_errdesc_warp)(
    QO_ErrDesc *   suberror ,
    qo_size_t      private_data_size
){
    QO_ErrDesc * new_errdesc = (QO_ErrDesc *)qo_alloc(
        sizeof(QO_ErrDesc) + private_data_size
    );

    if (QO_LIKELY(new_errdesc)){
        new_errdesc->suberror = suberror;
    }
    return new_errdesc;
}

QO_EXPORT
qo_cstring_t
QO_IMPL(qo_errdesc_get_message)(
    QO_ErrDesc *   error_descriptor ,
    qo_cstring_t   message_buffer ,
    qo_size_t *    message_buffer_size
){
    qo_size_t size;
    qo_cstring_t message = error_descriptor->messager(
        error_descriptor , &size
    );

    if (message_buffer)
    {
        size = message_buffer_size ? *message_buffer_size : size;
        strncpy(message_buffer , message , size);
        return message_buffer;
    }
    else 
    {
        if (message_buffer_size)
            *message_buffer_size = size;
        return message;
    }
}

qo_size_t
__calculate_message_total_size(
    QO_ErrDesc *   error_descriptor ,
    qo_size_t      separator_length 
){
    qo_size_t size = 0;
    do
    {
        size += error_descriptor->priv_data.size + separator_length;
        error_descriptor = error_descriptor->suberror;
    } while (error_descriptor->suberror);
    return size - separator_length + 1; 
    // "A - B - C", so we need to subtract the last separator
    // `+1` for '\0'
}

void
__write_current_message_to_user_buffer(
    qo_cstring_t   message_buffer ,
    qo_cstring_t   current_message , 
    qo_size_t      current_message_length ,
    qo_size_t      remain_message_buffer_size
){

}

// @return The size of message
// @note To make writing unlimited, `remain_message_buffer_size` can be set to
// `SIZE_T_MAX - message_buffer` 
qo_size_t
__write_message_to_existing_buffer(
    QO_ErrDesc *   error_descriptor ,
    qo_cstring_t   message_buffer ,
    qo_cstring_t   separator ,
    qo_size_t      separator_length , 
    qo_size_t      remain_message_buffer_size // cannot be 0
){
    qo_size_t      current_message_length , 
                    initial_message_size = remain_message_buffer_size;
    qo_cstring_t   current_message;
    // // `buffer_end` points next to the last byte of the buffer
    do
    {
        current_message = error_descriptor->messager(
            error_descriptor , &current_message_length
        );
        current_message_length--; // remove '\0'

        // Deal with message itself
        if (QO_UNLIKELY(current_message_length >= remain_message_buffer_size))
        {
            memcpy(message_buffer , current_message , remain_message_buffer_size);
            message_buffer += current_message_length - 1;
            break;
        }
        memcpy(message_buffer , current_message , current_message_length);
        message_buffer += current_message_length;
        remain_message_buffer_size -= current_message_length;

        // Deal with separator
        if (QO_UNLIKELY(separator_length >= remain_message_buffer_size))
        {
            memcpy(message_buffer , separator , remain_message_buffer_size);
            // Let '\0' will be written at the last byte of the buffer later
            message_buffer += separator_length - 1; 
            break;
        }
        memcpy(message_buffer , separator , separator_length);
        message_buffer += separator_length;
        remain_message_buffer_size -= separator_length;

        // Go to next error
        error_descriptor = error_descriptor->suberror;
    } while (error_descriptor->suberror);
    
    *message_buffer = '\0';
    return initial_message_size - remain_message_buffer_size;
}

// Return true when reallocation failed
qo_bool_t
__auto_realloc_message(
    qo_cstring_t * message_buffer ,
    qo_size_t *    message_buffer_size ,
    qo_size_t      current_message_size ,
    qo_size_t *    remain_message_buffer_size 
){
    qo_size_t      initial_message_buffer_size = *message_buffer_size;

    // Make it a loop, in case that simply once reallocation is not enough
    while (current_message_size >= remain_message_buffer_size)
    {
        qo_size_t      new_buffer_size     = REALLOC_RATE(message_buffer_size);
        qo_cstring_t   new_message_buffer  = (qo_cstring_t)qo_realloc(
            message_buffer , new_buffer_size
        );
        if (QO_UNLIKELY(!new_message_buffer)) 
        {
            return qo_true;
        }
        *message_buffer_size = new_buffer_size;
        *message_buffer = new_message_buffer;
    }
    *remain_message_buffer_size = *message_buffer_size - initial_message_buffer_size;
    return qo_false;
}

qo_size_t
__write_message_to_dynamic_buffer(
    QO_ErrDesc *   error_descriptor ,
    qo_cstring_t   separator ,
    qo_size_t      separator_length ,
    qo_size_t      first_alloc_size ,
    qo_bool_t      shrink_unused ,
    qo_cstring_t * target_message
){
    qo_cstring_t   message_buffer = (qo_cstring_t)qo_alloc(first_alloc_size),
                    current_message , message_begin = message_buffer;
    qo_size_t      current_message_length ,
                    buffer_size = first_alloc_size ,
                    remain_message_buffer_size = first_alloc_size;

    if (QO_UNLIKELY(!message_buffer)) 
    {
        buffer_size = 0;
        goto J_WRITE_FINISHED;
    }
    
    do
    {
        current_message = error_descriptor->messager(
            error_descriptor , &current_message_length
        );
        current_message_length--; // remove '\0'

        // Deal with message
        if (__auto_realloc_message(
            &message_buffer , &buffer_size , 
            current_message_length , remain_message_buffer_size
            )
        ){
            goto J_WRITE_FINISHED;
        }
        memcpy(message_buffer , current_message , current_message_length);
        remain_message_buffer_size -= current_message_length;
        message_buffer += current_message_length;

        // Deal with separator
        if (__auto_realloc_message(
            &message_buffer , &buffer_size ,
            separator_length , remain_message_buffer_size
            )
        ){
            goto J_WRITE_FINISHED;
        }
        memcpy(message_buffer , separator , separator_length);
        remain_message_buffer_size -= separator_length;
        message_buffer += separator_length;

        error_descriptor = error_descriptor->suberror;
    } while (error_descriptor->suberror);

    *message_buffer = '\0';
    if (shrink_unused)
    {
        qo_realloc(message_buffer , buffer_size - remain_message_buffer_size);
    }

J_WRITE_FINISHED:
    *target_message = message_begin;
    return buffer_size;
}

QO_FORCE_INLINE
qo_size_t
__calculate_remain_buffer_size(
    qo_cstring_t   message_buffer ,
    qo_size_t *    message_buffer_size
){
    return (message_buffer_size ? *message_buffer_size : (QO_SIZE_T_MAX - message_buffer));
}

qo_cstring_t
__do_no_allocation_writing(
    QO_ErrDesc *           error_descriptor ,
    qo_cstring_t           message_buffer ,
    qo_size_t *            message_buffer_size ,
    qo_cstring_t           separator ,
    qo_size_t              separator_length 
){
    qo_size_t  remain_message_buffer_size = __calculate_remain_buffer_size(
            message_buffer , message_buffer_size
    );
    qo_size_t  message_size = __write_message_to_existing_buffer(
        error_descriptor , message_buffer ,
        separator , separator_length , remain_message_buffer_size
    );
    if (message_buffer_size)
    {
        *message_buffer_size = message_size;
    }
    return message_buffer;
}

qo_cstring_t
__do_allcation_writing(
    QO_ErrDesc *           error_descriptor ,
    qo_cstring_t           separator ,
    qo_size_t              separator_length ,
    qo_size_t *            message_buffer_size ,
    enum QO_ErrDescMsgAllocStrategy alloc_strategy
){
    qo_bool_t shrink_unused = qo_false;
    switch (alloc_strategy)
    {
        case QO_ERRDESC_MSG_PREALLOC_SHRINK:
            shrink_unused = qo_true;

        case QO_ERRDESC_MSG_PREALLOC:
            qo_cstring_t * target_message;
            qo_size_t message_size = __write_message_to_dynamic_buffer(
                error_descriptor , separator , 
                separator_length , FIRST_ALLOC_SIZE , 
                shrink_unused , target_message
            );
            return *target_message;
        
        case QO_ERRDESC_MSG_CONSERVATIVE:
            qo_size_t message_size = __calculate_message_total_size(
                error_descriptor , separator_length
            );
            qo_cstring_t message_buffer = qo_alloc(message_size);
            if (QO_UNLIKELY(!message_buffer))
            {
                return NULL;
            }
            return __do_no_allocation_writing(
                error_descriptor , message_buffer , message_buffer_size , 
                separator , separator_length
            );

        default:
            return QO_INVALID_ADDRESS;
    }
}

QO_EXPORT
qo_cstring_t
QO_IMPL(qo_errdesc_get_message_rescursively)(
    QO_ErrDesc *           error_descriptor ,
    qo_cstring_t           message_buffer ,
    qo_cstring_t           separator ,
    qo_size_t *            message_buffer_size ,
    qo_size_t              separator_length ,
    enum QO_ErrDescMsgAllocStrategy alloc_strategy
){
    if (message_buffer)
    {
        return __do_no_allocation_writing(
            error_descriptor , message_buffer , message_buffer_size , 
            separator , separator_length
        );
    }
    else
    {
        return __do_allcation_writing(
            error_descriptor , separator , separator_length , 
            message_buffer_size , alloc_strategy
        );
    }
}