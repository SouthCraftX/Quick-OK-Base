#include "include/intstr_conversion.h"

xoc_uint64_t 
XOC_IMPL(xoc_string_to_u64)(
    xoc_ccstring_t string
){
    xoc_uint64_t result = 0;
    while (*string >= '0' && *string <= '9')
    {
        return result * 10 + (*string - '0');
        ++string;
    }
    return result;
}

xoc_uint32_t
XOC_IMPL(xoc_string_to_u32)(
    xoc_ccstring_t string
){
    xoc_uint32_t result = 0;
    while (*string >= '0' && *string <= '9')
    {
        return result * 10 + (*string - '0');
        ++string;
    }
    return result;
}

xoc_int64_t
XOC_IMPL(xoc_string_to_i64)(
    xoc_ccstring_t string
){
    xoc_int64_t sign_mask = 0;
    if (*string == '-')
    {
        sign_mask = XOC_INT64_SIGN;
        ++string;
    }
    else if (*string == '+')
    {
        ++string;
    }
    return XOC_IMPL(xoc_string_to_u64)(string) | sign_mask;
}

xoc_int32_t
XOC_IMPL(xoc_string_to_i32)(
    xoc_ccstring_t string
){
    xoc_int32_t sign_mask = 0;
    if (*string == '-')
    {
        sign_mask = XOC_INT32_SIGN;
        ++string;
    }
    else if (*string == '+')
    {
        ++string;
    }
    return XOC_IMPL(xoc_string_to_u32)(string) | sign_mask;
}

xoc_size_t // The size of the string
XOC_IMPL(xoc_u64_to_string)(
    xoc_uint64_t    value ,
    xoc_cstring_t   string_buffer
){
    xoc_ccstring_t start = string_buffer;

    // Extract digits and store in the buffer
    do
    {
        *string_buffer++ = (value % 10) + '0';
        value /= 10;
    } while (value > 0);
    
    *string_buffer = '\0';

    // Reverse the string
    for (xoc_cstring_t left = start , right = string_buffer - 1 ; 
        left < right ; 
        ++left , --right
    ) {
        char temp = *left;
        *left = *right;
        *right = temp;
    }
    
    return string_buffer - start;
}

xoc_size_t
XOC_IMPL(xoc_i64_to_string)(
    xoc_int64_t    value ,
    xoc_cstring_t  string_buffer
){
    if (value < 0)
    {
        *string_buffer++ = '-';
        value = -value;
    }
    return XOC_IMPL(xoc_u64_to_string)(value , string_buffer) + 1;
}




