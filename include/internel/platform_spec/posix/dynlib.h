#pragma once

// for debug
#include "dynlib.h"

#if !defined(XOC_DYNAMIC_LIBRARY_INCLUDED)
#   error Do not include this file directly. Use dynlib.h instead
#endif 

#if (POSIX < 200809L) || ! XOC_PLATFORM(LINUX)
#   error This requires at least POSIX 1003.1-2008 
#endif 

#include <dlfcn.h>

XOC_IMPORT
xoc_stat_t
__xoc_dynamic_library_error();

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_dynamic_library_open)(
    XOC_DynamicLibrary *  library ,
    xoc_ccstring_t       path
){
    xoc_pointer_t lib =  dlopen(path , 0);
    if(lib)
    {
        *library = lib;
        return XOC_OK;
    }
    return __xoc_dynamic_library_error();
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_dynamic_library_search_symbol)(
    XOC_DynamicLibrary    library ,
    xoc_ccstring_t       symbol_name ,
    xoc_pointer_t *      symbol
){
    xoc_pointer_t sym = dlsym(library , symbol_name);
    if (sym)
    {
        /* code */
    }
    
}