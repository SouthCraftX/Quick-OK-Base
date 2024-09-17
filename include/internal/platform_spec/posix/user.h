#pragma once
#define __XOC_USER_POSIX_H__

#include "include/user.h" // for debug

#if !defined(__XOC_USER_H__)
#   error Never include this header file directly. Use <xoc/user.h> instead.std
#endif

#include <unistd.h>

xoc_bool_t
XOC_IMPL(xoc_is_high_privileged)()
{
    return !getuid(); // getuid() returns 0 if running as root
}