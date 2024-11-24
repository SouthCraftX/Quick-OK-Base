#include "filesystem.h"

qo_ccstring_t
QO_IMPL(qo_path_find_traversal)(
    qo_ccstring_t  path , 
    qo_size_t      length
){
    qo_ccstring_t traversal = qo_string_find_substring(path , ".." , length);
    if (traversal)
    {
        if ( 
            (length == 2 ) ||                                   // Just ".."
            (traversal[2] == '/') || (traversal[2] == '\\') ||  // find frontward
            ((traversal != path ) && (                          // find backward
                (traversal[-1] == '/') || (traversal[-1] == '\\')
                )
            )
        ) 
        return traversal;
    }
    return NULL;
}