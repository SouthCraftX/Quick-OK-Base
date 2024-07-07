#pragma once

// for debug
#include "include/dynlib.h"

#if !defined(XOC_DYNAMIC_LIBRARY_INCLUDED)
#   error "Never include this header file directly. Use dynlib.h instead."
#endif 

#include <libloaderapi.h>

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_dynamic_library_open)(
    XOC_DynamicLibrary *  library ,
    xoc_ccstring_t       path
){
    wchar_t wc_path[MAX_PATH];
    __xoc_win32_utf8_path_to_wcpath(path, wc_path);

    HMODULE lib = LoadLibraryW(wc_path);
    if(lib)
    {
        *library = lib;
        return XOC_OK;
    }

}