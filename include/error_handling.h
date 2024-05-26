#pragma once
#define __XOCEAN_WIN32_ERROR_HANDLING_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/* ======== File Stream ======== */
XOCEAN_IMPORT
xocean_stat_t
__xocean_file_opening_error();

XOCEAN_IMPORT
xocean_stat_t
__xocean_file_reading_error();

XOCEAN_IMPORT
xocean_stat_t
__xocean_file_writing_error();

XOCEAN_IMPORT
xocean_stat_t
__xocean_file_pos_setting_error();

XOCEAN_IMPORT
xocean_stat_t
__xocean_file_seeking_error();

XOCEAN_IMPORT
xocean_stat_t
__xocean_file_size_getting_error();

XOCEAN_IMPORT
xocean_stat_t
__xocean_file_allocating_error();

/* ======== Multithreading ======== */
XOCEAN_IMPORT
xocean_stat_t
__xocean_thread_creating_error();



#if defined(__cplusplus)
}
#endif // __cplusplus