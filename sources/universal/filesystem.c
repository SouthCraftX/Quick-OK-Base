#include "filesystem.h"

xoc_ccstring_t
XOC_IMPL(xoc_path_find_traversal)(
    xoc_ccstring_t  path , 
    xoc_size_t      length
){
    xoc_ccstring_t traversal = xoc_string_find_substring(path , ".." , length);
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