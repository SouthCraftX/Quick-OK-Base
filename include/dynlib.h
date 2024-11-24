#pragma once
#define QO_DYNAMIC_LIBRARY_INCLUDED

#include "../base.h"

#ifdef defined(__cplusplus)
extern "C" {
#endif // __cplusplus

typedef qo_pointer_t QO_DynamicLibrary;  

qo_stat_t
QO_INTERFACE(qo_dynamic_library_open)(
    QO_DynamicLibrary *  library ,
    qo_ccstring_t       path
);

qo_stat_t
QO_INTERFACE(qo_dynamic_library_search_symbol)(
    QO_DynamicLibrary    library ,
    qo_ccstring_t       symbol_name ,
    qo_pointer_t *      symbol    
);

qo_stat_t
QO_INTERFACE(qo_dynamic_library_close)(
    QO_DynamicLibrary    library
);



#ifdef defined(__cplusplus)
}
#endif // __cplusplus