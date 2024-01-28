#include "rand.h"

#include <wincrypt.h>

XOCEAN_GLOBAL_LOCAL HCRYPTPROV crypt_prov;

xocean_stat_t xocean_sys_rand_buf_init()
{
    return CryptAcquireContextA(&crypt_prov , NULL , NULL , PROV_RSA_FULL , 
                                CRYPT_VERIFYCONTEXT) ? XOCEAN_OK : 
                                XOCEAN_INIT_SYS_RAND_FAILED ;
}

xocean_stat_t xocean_sys_rand_buf_destory()
{
    return CryptReleaseContext(crypt_prov , 0) ? 
           XOCEAN_OK : XOCEAN_DESTORY_SYS_RAND_FAILED;
}

void
XOCEAN_IMPL(xocean_sys_rand_buf)(
    xocean_pointer_t    buf ,
    xocean_size_t       size
){
    CyrptGenRandom(crypt_prov , buf , size);
    // @todo : Handle error in debug
}