#pragma once
#define __XOC_ABSTRACT_FILE_H__

#include "fstream.h"

struct _XOC_AbstractFile;
typedef struct _XOC_AbstractFile XOC_AbstractFile;

xoc_stat_t
XOC_INTERFACE(xoc_abstract_file_open)(
    XOC_AbstractFile ** p_file ,
    xoc_ccstring_t      path 
    
);