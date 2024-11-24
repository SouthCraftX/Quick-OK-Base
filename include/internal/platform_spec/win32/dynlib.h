#pragma once

// for debug
#include "include/dynlib.h"

#if !defined(QO_DYNAMIC_LIBRARY_INCLUDED)
#   error "Never include this header file directly. Use dynlib.h instead."
#endif 

#include <libloaderapi.h>

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_dynamic_library_open)(
    QO_DynamicLibrary *  library ,
    qo_ccstring_t       path
){
    wchar_t wc_path[MAX_PATH];
    __qo_win32_utf8_path_to_wcpath(path, wc_path);

    HMODULE lib = LoadLibraryW(wc_path);
    if (lib)
    {
        *library = lib;
        return QO_OK;
    }

}