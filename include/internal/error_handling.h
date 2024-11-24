#pragma once
#define __QO_WIN32_ERROR_HANDLING_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/* ======== File Stream ======== */
QO_IMPORT
qo_stat_t
__qo_file_opening_error();

QO_IMPORT
qo_stat_t
__qo_file_reading_error();

QO_IMPORT
qo_stat_t
__qo_file_writing_error();

QO_IMPORT
qo_stat_t
__qo_file_pos_setting_error();

QO_IMPORT
qo_stat_t
__qo_file_seeking_error();

QO_IMPORT
qo_stat_t
__qo_file_size_getting_error();

QO_IMPORT
qo_stat_t
__qo_file_allocating_error();

/* ======== Multithreading ======== */
QO_IMPORT
qo_stat_t
__qo_thread_creating_error();



#if defined(__cplusplus)
}
#endif // __cplusplus