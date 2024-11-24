#pragma once
#define __QO_ABSTRACT_FILE_H__

#include "fstream.h"

struct _QO_AbstractFile;
typedef struct _QO_AbstractFile QO_AbstractFile;

qo_stat_t
QO_INTERFACE(qo_abstract_file_open)(
    QO_AbstractFile ** p_file ,
    qo_ccstring_t      path 
    
);