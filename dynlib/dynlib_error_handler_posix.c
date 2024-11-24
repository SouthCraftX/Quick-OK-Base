#include "dynlib.h"

// for debug
#include <dlfcn.h>

qo_stat_t
__qoeam_dynamic_library_error()
{
    dlerror
}