#pragma once


#include "base.h"

#if defined(__cplusplus)
extern "C"{
#endif // __cplusplus

struct _XOceanErrorDescriptor
{
    xocean_flag32_t     ref_count;  /* Read-only */
    xocean_stat_t       error_code; /* Read-only */
    xocean_ccstring_t   where_err;  /* Read-only*/

    xocean_ccstring_t
    (*fn_what)(
        XOceanErrorDescriptor *
    );


    XOceanErrorDescriptor * next_error;
    xocean_intmax_t private_data[];
};
typedef struct _XOceanErrorDescriptor XOceanErrorDescriptor;

void
XOCEAN_IMPL(xocean_error_descriptor_unref)(
    XOceanErrorDescriptor *
);

XOceanErrorDescriptor *
XOCEAN_IMPL(xocean_error_descriptor_ref)(
    XOceanErrorDescriptor *
);




#if defined(__cplusplus)
}
#endif // __cplusplus