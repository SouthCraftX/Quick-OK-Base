#pragma once
#define __XOC_DRAGONBOX_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @brief  Change 
/// @param  
/// @return 
xoc_stat_t
XOC_INTERFACE(xoc_dragonbox_set_table)(
    xoc_size_t fp32_table_size ,
    xoc_size_t fp64_table_size 
);



#if defined(__cplusplus)
}
#endif // __cplusplus