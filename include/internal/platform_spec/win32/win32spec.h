#pragma once
#define __XOC_WIN32_WIN32SEPC_H__

// for debug
#include "include/win32spec.h"

#if !defined(__XOC_WIN32_SPEC_H__)
#   error Never include this header file directly. Use <xoc/win32spec.h> instead.
#endif 

#include <wincon.h>
#include <winuser.h>

// tested work
xoc_bool_t
XOC_IMPL(xoc_is_opened_via_double_clicked)()
{
    DWORD pid;
    GetWindowThreadProcessId(GetConsoleWindow(), &pid);
    return (pid == GetCurrentProcessId());
}