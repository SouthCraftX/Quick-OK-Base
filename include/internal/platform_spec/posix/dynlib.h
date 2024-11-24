#pragma once

// for debug
#include "dynlib.h"

#if !defined(QO_DYNAMIC_LIBRARY_INCLUDED)
#   error Do not include this file directly. Use dynlib.h instead
#endif 

#if (POSIX < 200809L) || ! QO_PLATFORM(LINUX)
#   error This requires at least POSIX 1003.1-2008 
#endif 

#include <dlfcn.h>

QO_IMPORT
qo_stat_t
__qo_dynamic_library_error();

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_dynamic_library_open)(
    QO_DynamicLibrary *  library ,
    qo_ccstring_t       path
){
    qo_pointer_t lib =  dlopen(path , 0);
    if (lib)
    {
        *library = lib;
        return QO_OK;
    }
    return __qo_dynamic_library_error();
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_dynamic_library_search_symbol)(
    QO_DynamicLibrary    library ,
    qo_ccstring_t       symbol_name ,
    qo_pointer_t *      symbol
){
    qo_pointer_t sym = dlsym(library , symbol_name);
    if (sym)
    {
        /* code */
    }
    
}