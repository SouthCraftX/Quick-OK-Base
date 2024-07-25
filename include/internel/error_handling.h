#pragma once
#define __XOC_WIN32_ERROR_HANDLING_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/* ======== File Stream ======== */
XOC_IMPORT
xoc_stat_t
__xoc_file_opening_error();

XOC_IMPORT
xoc_stat_t
__xoc_file_reading_error();

XOC_IMPORT
xoc_stat_t
__xoc_file_writing_error();

XOC_IMPORT
xoc_stat_t
__xoc_file_pos_setting_error();

XOC_IMPORT
xoc_stat_t
__xoc_file_seeking_error();

XOC_IMPORT
xoc_stat_t
__xoc_file_size_getting_error();

XOC_IMPORT
xoc_stat_t
__xoc_file_allocating_error();

/* ======== Multithreading ======== */
XOC_IMPORT
xoc_stat_t
__xoc_thread_creating_error();



#if defined(__cplusplus)
}
#endif // __cplusplus