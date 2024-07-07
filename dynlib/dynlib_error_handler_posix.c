#include "dynlib.h"

// for debug
#include <dlfcn.h>

xoc_stat_t
__xoceam_dynamic_library_error()
{
    dlerror
}