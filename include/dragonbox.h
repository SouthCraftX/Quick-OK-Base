#pragma once
#define __QO_DRAGONBOX_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @brief  Change 
/// @param  
/// @return 
qo_stat_t
QO_INTERFACE(qo_dragonbox_set_table)(
    qo_size_t fp32_table_size ,
    qo_size_t fp64_table_size 
);



#if defined(__cplusplus)
}
#endif // __cplusplus