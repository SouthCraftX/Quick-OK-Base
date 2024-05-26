#pragma once

// for debug
#include "dynlib.h"

#if !defined(XOCEAN_DYNAMIC_LIBRARY_INCLUDED)
#   error Do not include this file directly. Use dynlib.h instead
#endif 

#if (POSIX < 200809L) || ! XOCEAN_PLATFORM(LINUX)
#   error This requires at least POSIX 1003.1-2008 
#endif 

#include <dlfcn.h>

XOCEAN_IMPORT
xocean_stat_t
__xocean_dynamic_library_error();

XOCEAN_FORCE_INLINE
xocean_stat_t
XOCEAN_IMPL(xocean_dynamic_library_open)(
    XOceanDynamicLibrary *  library ,
    xocean_ccstring_t       path
){
    xocean_pointer_t lib =  dlopen(path , 0);
    if(lib)
    {
        *library = lib;
        return XOCEAN_OK;
    }
    return __xocean_dynamic_library_error();
}

XOCEAN_FORCE_INLINE
xocean_stat_t
XOCEAN_IMPL(xocean_dynamic_library_search_symbol)(
    XOceanDynamicLibrary    library ,
    xocean_ccstring_t       symbol_name ,
    xocean_pointer_t *      symbol
){
    xocean_pointer_t sym = dlsym(library , symbol_name);
    if (sym)
    {
        /* code */
    }
    
}