#pragma once
#define __XOC_STRINGSET_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif

/// @brief  Calculate the length of a string.
/// @param  string  The string to calculate the length of
/// @return The length of the string.
xoc_size_t
XOC_INTERFACE(xoc_string_length)(
    xoc_ccstring_t  string
) XOC_NONNULL(1);

/// @brief  Copy a string to another
/// @param  source  The source string
/// @param  destination  The destination string
/// @param  count  The number of characters to copy. 0 is allowed, in that case,
///         the string is copied until the null terminator is reached.
/// @return 
xoc_size_t
XOC_INTERFACE(xoc_string_copy)(
    xoc_ccstring_t  source ,
    xoc_cstring_t   destination ,
    xoc_size_t      count
) XOC_NONNULL(1 , 2);

/// @brief  Duplicate a string using xoc_alloc()
/// @param  string  The string to duplicate
/// @param  p_count Pointer to the count of characters to duplicate. 
///         If NULL,
///         the function will duplicate until the null terminator is reached.
///         If not NULL, 
///         *p_count indicates the number of characters to
///         duplicate. If *p_count is 0, the function will duplicate until the
///         null terminator is reached. *p_count will be written with the
///         number of characters duplicated.
/// @return The duplicated string. NULL if no enough memory to handle this
///         operation.
xoc_cstring_t
XOC_INTERFACE(xoc_string_duplicate)(
    xoc_ccstring_t  string ,
    xoc_size_t *    p_count
) XOC_NONNULL(1);

/// @brief  Find a character in a string
/// @param  string  The string to search
/// @param  character  The character to find 
/// @param  length  The length of the string to search
/// @return Pointer to the first occurrence of the character in the string.
xoc_cstring_t
XOC_INTERFACE(xoc_string_find_char)(
    xoc_ccstring_t  string ,
    xoc_int32_t     character ,
    xoc_size_t      length
) XOC_NONNULL(1);

xoc_ccstring_t
XOC_INTERFACE(xoc_string_find_substring)(
    xoc_ccstring_t  string ,
    xoc_ccstring_t  substring ,
    xoc_size_t      length
) XOC_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif

#define xoc_string_length       XOC_INTERFACE(xoc_string_length)
#define xoc_string_copy         XOC_INTERFACE(xoc_string_copy)
#define xoc_string_duplicate    XOC_INTERFACE(xoc_string_duplicate)
#define xoc_string_find_char    XOC_INTERFACE(xoc_string_find_char)
#define xoc_string_find_substring XOC_INTERFACE(xoc_string_find_substring)