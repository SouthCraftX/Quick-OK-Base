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

struct _XOC_ErrDescPrivData
{
    xoc_size_t      size;       
    xoc_intmax_t    context[];
};
typedef struct _XOC_ErrDescPrivData XOC_ErrDescPrivData;

/// @remark Mostly, sizeof(_XOC_ErrorDescriptor) == 32 bytes (without private area)
/// in 64-bit platforms, sizeof(_XOC_ErrorDescriptor) == 20 bytes (without 
/// private area) in 32-bit platforms.
struct _XOC_ErrorDescriptor
{
    xoc_flag32_t     ref_count;  
    xoc_stat_t       error_code; 

    /// @brief Get the error message.
    /// @param `self` The error descriptor.
    /// @param `message_buffer_size` The size of the message buffer. Set it null if
    /// you don't want this information.
    /// @note This messager is implemented by user
    xoc_cstring_t
    (* messager)(
        XOC_ErrDesc * ,
        xoc_size_t *   
    );

    /// @brief Destructor of the error descriptor.
    /// @param `self` The error descriptor.
    void
    (* destructor)(
        XOC_ErrDesc *  
    );

    /// @brief The suberror of the error descriptor. NULL if there is no suberror.
    XOC_ErrDesc *           suberror;

    /// @brief The private data of the error descriptor.
    /// @note  It is managed by error descriptor creator.
    XOC_ErrDescPrivData     priv_data;
};

XOC_EXPORT
void
XOC_IMPL(xoc_errdesc_ref)(
    XOC_ErrDesc *   error_descriptor
){
    error_descriptor->ref_count++;
}

XOC_EXPORT
void
XOC_IMPL(xoc_errdesc_unref)(
    XOC_ErrDesc *   error_descriptor
){
    if (error_descriptor && ((--error_descriptor->ref_count) == 0))
        error_descriptor->destructor(error_descriptor);
}

XOC_EXPORT
XOC_ErrDesc *
XOC_IMPL(xoc_errdesc_warp)(
    XOC_ErrDesc *   suberror ,
    xoc_size_t      private_data_size
){
    XOC_ErrDesc * new_errdesc = (XOC_ErrDesc *)xoc_alloc(
        sizeof(XOC_ErrDesc) + private_data_size
    );

    if (XOC_LIKELY(new_errdesc)){
        new_errdesc->suberror = suberror;
    }
    return new_errdesc;
}

XOC_EXPORT
xoc_cstring_t
XOC_IMPL(xoc_errdesc_get_message)(
    XOC_ErrDesc *   error_descriptor ,
    xoc_cstring_t   message_buffer ,
    xoc_size_t *    message_buffer_size
){
    xoc_size_t size;
    xoc_cstring_t message = error_descriptor->messager(
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

xoc_size_t
__calculate_message_total_size(
    XOC_ErrDesc *   error_descriptor ,
    xoc_size_t      separator_length 
){
    xoc_size_t size = 0;
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
    xoc_cstring_t   message_buffer ,
    xoc_cstring_t   current_message , 
    xoc_size_t      current_message_length ,
    xoc_size_t      remain_message_buffer_size
){

}

// @return The size of message
// @note To make writing unlimited, `remain_message_buffer_size` can be set to
// `SIZE_T_MAX - message_buffer` 
xoc_size_t
__write_message_to_existing_buffer(
    XOC_ErrDesc *   error_descriptor ,
    xoc_cstring_t   message_buffer ,
    xoc_cstring_t   separator ,
    xoc_size_t      separator_length , 
    xoc_size_t      remain_message_buffer_size // cannot be 0
){
    xoc_size_t      current_message_length , 
                    initial_message_size = remain_message_buffer_size;
    xoc_cstring_t   current_message;
    // // `buffer_end` points next to the last byte of the buffer
    do
    {
        current_message = error_descriptor->messager(
            error_descriptor , &current_message_length
        );
        current_message_length--; // remove '\0'

        // Deal with message itself
        if (XOC_UNLIKELY(current_message_length >= remain_message_buffer_size))
        {
            memcpy(message_buffer , current_message , remain_message_buffer_size);
            message_buffer += current_message_length - 1;
            break;
        }
        memcpy(message_buffer , current_message , current_message_length);
        message_buffer += current_message_length;
        remain_message_buffer_size -= current_message_length;

        // Deal with separator
        if (XOC_UNLIKELY(separator_length >= remain_message_buffer_size))
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
xoc_bool_t
__auto_realloc_message(
    xoc_cstring_t * message_buffer ,
    xoc_size_t *    message_buffer_size ,
    xoc_size_t      current_message_size ,
    xoc_size_t *    remain_message_buffer_size 
){
    xoc_size_t      initial_message_buffer_size = *message_buffer_size;

    // Make it a loop, in case that simply once reallocation is not enough
    while (current_message_size >= remain_message_buffer_size)
    {
        xoc_size_t      new_buffer_size     = REALLOC_RATE(message_buffer_size);
        xoc_cstring_t   new_message_buffer  = (xoc_cstring_t)xoc_realloc(
            message_buffer , new_buffer_size
        );
        if (XOC_UNLIKELY(!new_message_buffer)) 
        {
            return xoc_true;
        }
        *message_buffer_size = new_buffer_size;
        *message_buffer = new_message_buffer;
    }
    *remain_message_buffer_size = *message_buffer_size - initial_message_buffer_size;
    return xoc_false;
}

xoc_size_t
__write_message_to_dynamic_buffer(
    XOC_ErrDesc *   error_descriptor ,
    xoc_cstring_t   separator ,
    xoc_size_t      separator_length ,
    xoc_size_t      first_alloc_size ,
    xoc_bool_t      shrink_unused ,
    xoc_cstring_t * target_message
){
    xoc_cstring_t   message_buffer = (xoc_cstring_t)xoc_alloc(first_alloc_size),
                    current_message , message_begin = message_buffer;
    xoc_size_t      current_message_length ,
                    buffer_size = first_alloc_size ,
                    remain_message_buffer_size = first_alloc_size;

    if (XOC_UNLIKELY(!message_buffer)) 
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
        xoc_realloc(message_buffer , buffer_size - remain_message_buffer_size);
    }

J_WRITE_FINISHED:
    *target_message = message_begin;
    return buffer_size;
}

XOC_FORCE_INLINE
xoc_size_t
__calculate_remain_buffer_size(
    xoc_cstring_t   message_buffer ,
    xoc_size_t *    message_buffer_size
){
    return (message_buffer_size ? *message_buffer_size : (XOC_SIZE_T_MAX - message_buffer));
}

xoc_cstring_t
__do_no_allocation_writing(
    XOC_ErrDesc *           error_descriptor ,
    xoc_cstring_t           message_buffer ,
    xoc_size_t *            message_buffer_size ,
    xoc_cstring_t           separator ,
    xoc_size_t              separator_length 
){
    xoc_size_t  remain_message_buffer_size = __calculate_remain_buffer_size(
            message_buffer , message_buffer_size
    );
    xoc_size_t  message_size = __write_message_to_existing_buffer(
        error_descriptor , message_buffer ,
        separator , separator_length , remain_message_buffer_size
    );
    if (message_buffer_size)
    {
        *message_buffer_size = message_size;
    }
    return message_buffer;
}

xoc_cstring_t
__do_allcation_writing(
    XOC_ErrDesc *           error_descriptor ,
    xoc_cstring_t           separator ,
    xoc_size_t              separator_length ,
    xoc_size_t *            message_buffer_size ,
    enum XOC_ErrDescMsgAllocStrategy alloc_strategy
){
    xoc_bool_t shrink_unused = xoc_false;
    switch (alloc_strategy)
    {
        case XOC_ERRDESC_MSG_PREALLOC_SHRINK:
            shrink_unused = xoc_true;

        case XOC_ERRDESC_MSG_PREALLOC:
            xoc_cstring_t * target_message;
            xoc_size_t message_size = __write_message_to_dynamic_buffer(
                error_descriptor , separator , 
                separator_length , FIRST_ALLOC_SIZE , 
                shrink_unused , target_message
            );
            return *target_message;
        
        case XOC_ERRDESC_MSG_CONSERVATIVE:
            xoc_size_t message_size = __calculate_message_total_size(
                error_descriptor , separator_length
            );
            xoc_cstring_t message_buffer = xoc_alloc(message_size);
            if (XOC_UNLIKELY(!message_buffer))
            {
                return NULL;
            }
            return __do_no_allocation_writing(
                error_descriptor , message_buffer , message_buffer_size , 
                separator , separator_length
            );

        default:
            return XOC_INVALID_ADDRESS;
    }
}

XOC_EXPORT
xoc_cstring_t
XOC_IMPL(xoc_errdesc_get_message_rescursively)(
    XOC_ErrDesc *           error_descriptor ,
    xoc_cstring_t           message_buffer ,
    xoc_cstring_t           separator ,
    xoc_size_t *            message_buffer_size ,
    xoc_size_t              separator_length ,
    enum XOC_ErrDescMsgAllocStrategy alloc_strategy
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