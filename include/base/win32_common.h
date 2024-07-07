#pragma once

#include "types.h"
#include "attribute.h" 

#include <stringapiset.h>

#if defined(__cplusplus)
extern "C" {
#endif // __forceinline

XOC_FORCE_INLINE
bool
__xoc_win32_utf8_path_to_wcpath(
    xoc_ccstring_t   source ,
    wchar_t *           target 
){
    return MultiByteToWideChar(CP_UTF8 , 0 , source , -1 , target , 0);
}

#if defined(__cplusplus)
}
#endif // __cplusplus