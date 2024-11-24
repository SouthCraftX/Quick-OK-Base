#pragma once
#define __QO_ABSTRACT_FILE_H__

#include "fstream.h"

struct _QO_AbstractFile;
typedef struct _QO_AbstractFile QO_AbstractFile;

/// @brief  Create a new abstract file from 
/// @param  
/// @return 
qo_stat_t
QO_INTERFACE(qo_abstract_file_open)(
    QO_AbstractFile ** pp_abs_file ,
    QO_File * p_file
);