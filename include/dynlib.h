#pragma once
#define XOCEAN_DYNAMIC_LIBRARY_INCLUDED

#include "../base.h"

#ifdef defined(__cplusplus)
extern "C" {
#endif // __cplusplus

typedef xocean_pointer_t XOceanDynamicLibrary;  

xocean_stat_t
XOCEAN_INTERFACE(xocean_dynamic_library_open)(
    XOceanDynamicLibrary *  library ,
    xocean_ccstring_t       path
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_dynamic_library_search_symbol)(
    XOceanDynamicLibrary    library ,
    xocean_ccstring_t       symbol_name ,
    xocean_pointer_t *      symbol    
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_dynamic_library_close)(
    XOceanDynamicLibrary    library
);



#ifdef defined(__cplusplus)
}
#endif // __cplusplus