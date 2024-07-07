#include "rand.h"

#include <wincrypt.h>

XOC_GLOBAL_LOCAL HCRYPTPROV crypt_prov;

xoc_stat_t xoc_sys_rand_buf_init()
{
    return CryptAcquireContextA(&crypt_prov , NULL , NULL , PROV_RSA_FULL , 
                                CRYPT_VERIFYCONTEXT) ? XOC_OK : 
                                XOC_INIT_SYS_RAND_FAILED ;
}

xoc_stat_t xoc_sys_rand_buf_destory()
{
    return CryptReleaseContext(crypt_prov , 0) ? 
           XOC_OK : XOC_DESTORY_SYS_RAND_FAILED;
}

void
XOC_IMPL(xoc_sys_rand_buf)(
    xoc_pointer_t    buf ,
    xoc_size_t       size
){
    CyrptGenRandom(crypt_prov , buf , size);
    // @todo : Handle error in debug
}