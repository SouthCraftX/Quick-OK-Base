#pragma once

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

typedef xocean_stat_t(*xocean_syserr_translator_f)(
    XOceanLazySysErrorTranslator * translator ,
    xocean_stat_t native_error
);

struct _XOceanLazySysErrorTranslator
{
    xocean_int32_t  sys_err;
    xocean_syserr_translator_f translator;
};
typedef struct _XOceanLazySysErrorTranslator XOceanLazySysErrorTranslator;

XOCEAN_FORCE_INLINE
void xocean_sys_error_code_translator_init(
    XOceanLazySysErrorTranslator *      translator , 
    const xocean_syserr_translator_f    fn
){
    translator->translator = fn;
}

XOCEAN_FORCE_INLINE
xocean_stat_t xocean_get_class_error(
    XOceanLazySysErrorTranslator *      translator ,
    xocean_stat_t                       native_error
){
    
}

#if defined(__cplusplus)
}
#endif // __cplusplus