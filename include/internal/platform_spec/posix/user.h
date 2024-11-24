#pragma once
#define __QO_USER_POSIX_H__

#include "include/user.h" // for debug

#if !defined(__QO_USER_H__)
#   error Never include this header file directly. Use <qo/user.h> instead.std
#endif

#include <unistd.h>

qo_bool_t
QO_IMPL(qo_is_high_privileged)()
{
    return !getuid(); // getuid() returns 0 if running as root
}