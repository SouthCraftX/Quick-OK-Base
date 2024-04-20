#include "dynlib.h"

// for debug
#include <dlfcn.h>

xocean_stat_t
__xoceam_dynamic_library_error()
{
    dlerror
}