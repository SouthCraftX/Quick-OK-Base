#pragma once


#include "base.h"

#if defined(__cplusplus)
extern "C"{
#endif // __cplusplus

// This structure is designed not to be exposed to the user.
struct _XOC_ErrorDescriptor
{
    xoc_flag32_t     ref_count;  
    xoc_stat_t       error_code; 
    xoc_ccstring_t   where_err;

    xoc_ccstring_t
    (*fn_what)(
        XOC_ErrorDescriptor *
    );


    XOC_ErrorDescriptor * next_error;
    xoc_intmax_t private_data[];
};
typedef struct _XOC_ErrorDescriptor XOC_ErrorDescriptor;

void
XOC_IMPL(xoc_error_descriptor_unref)(
    XOC_ErrorDescriptor *
);

XOC_ErrorDescriptor *
XOC_IMPL(xoc_error_descriptor_ref)(
    XOC_ErrorDescriptor *
);




#if defined(__cplusplus)
}
#endif // __cplusplus