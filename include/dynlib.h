#pragma once
#define XOC_DYNAMIC_LIBRARY_INCLUDED

#include "../base.h"

#ifdef defined(__cplusplus)
extern "C" {
#endif // __cplusplus

typedef xoc_pointer_t XOC_DynamicLibrary;  

xoc_stat_t
XOC_INTERFACE(xoc_dynamic_library_open)(
    XOC_DynamicLibrary *  library ,
    xoc_ccstring_t       path
);

xoc_stat_t
XOC_INTERFACE(xoc_dynamic_library_search_symbol)(
    XOC_DynamicLibrary    library ,
    xoc_ccstring_t       symbol_name ,
    xoc_pointer_t *      symbol    
);

xoc_stat_t
XOC_INTERFACE(xoc_dynamic_library_close)(
    XOC_DynamicLibrary    library
);



#ifdef defined(__cplusplus)
}
#endif // __cplusplus