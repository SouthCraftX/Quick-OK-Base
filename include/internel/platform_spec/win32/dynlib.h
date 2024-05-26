#pragma once

// for debug
#include "include/dynlib.h"

#if !defined(XOCEAN_DYNAMIC_LIBRARY_INCLUDED)
#   error "Never include this header file directly. Use dynlib.h instead."
#endif 

#include <libloaderapi.h>

XOCEAN_FORCE_INLINE
xocean_stat_t
XOCEAN_IMPL(xocean_dynamic_library_open)(
    XOceanDynamicLibrary *  library ,
    xocean_ccstring_t       path
){
    wchar_t wc_path[MAX_PATH];
    __xocean_win32_utf8_path_to_wcpath(path, wc_path);

    HMODULE lib = LoadLibraryW(wc_path);
    if(lib)
    {
        *library = lib;
        return XOCEAN_OK;
    }

}