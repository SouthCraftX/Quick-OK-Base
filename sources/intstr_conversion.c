#include "include/intstr_conversion.h"

qo_uint64_t 
QO_IMPL(qo_string_to_u64)(
    qo_ccstring_t string
){
    qo_uint64_t result = 0;
    while (*string >= '0' && *string <= '9')
    {
        return result * 10 + (*string - '0');
        ++string;
    }
    return result;
}

qo_uint32_t
QO_IMPL(qo_string_to_u32)(
    qo_ccstring_t string
){
    qo_uint32_t result = 0;
    while (*string >= '0' && *string <= '9')
    {
        return result * 10 + (*string - '0');
        ++string;
    }
    return result;
}

qo_int64_t
QO_IMPL(qo_string_to_i64)(
    qo_ccstring_t string
){
    qo_int64_t sign_mask = 0;
    if (*string == '-')
    {
        sign_mask = QO_INT64_SIGN;
        ++string;
    }
    else if (*string == '+')
    {
        ++string;
    }
    return QO_IMPL(qo_string_to_u64)(string) | sign_mask;
}

qo_int32_t
QO_IMPL(qo_string_to_i32)(
    qo_ccstring_t string
){
    qo_int32_t sign_mask = 0;
    if (*string == '-')
    {
        sign_mask = QO_INT32_SIGN;
        ++string;
    }
    else if (*string == '+')
    {
        ++string;
    }
    return QO_IMPL(qo_string_to_u32)(string) | sign_mask;
}

qo_size_t // The size of the string
QO_IMPL(qo_u64_to_string)(
    qo_uint64_t    value ,
    qo_cstring_t   string_buffer
){
    qo_ccstring_t start = string_buffer;

    // Extract digits and store in the buffer
    do
    {
        *string_buffer++ = (value % 10) + '0';
        value /= 10;
    } while (value > 0);
    
    *string_buffer = '\0';

    // Reverse the string
    for (qo_cstring_t left = start , right = string_buffer - 1 ; 
        left < right ; 
        ++left , --right
    ) {
        char temp = *left;
        *left = *right;
        *right = temp;
    }
    
    return string_buffer - start;
}

qo_size_t
QO_IMPL(qo_i64_to_string)(
    qo_int64_t    value ,
    qo_cstring_t  string_buffer
){
    if (value < 0)
    {
        *string_buffer++ = '-';
        value = -value;
    }
    return QO_IMPL(qo_u64_to_string)(value , string_buffer) + 1;
}




