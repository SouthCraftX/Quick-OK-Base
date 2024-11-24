#include "rand.h"

#include <wincrypt.h>

QO_GLOBAL_LOCAL HCRYPTPROV crypt_prov;

qo_stat_t qo_sys_rand_buf_init()
{
    return CryptAcquireContextA(&crypt_prov , NULL , NULL , PROV_RSA_FULL , 
                                CRYPT_VERIFYCONTEXT) ? QO_OK : 
                                QO_INIT_SYS_RAND_FAILED ;
}

qo_stat_t qo_sys_rand_buf_destory()
{
    return CryptReleaseContext(crypt_prov , 0) ? 
           QO_OK : QO_DESTORY_SYS_RAND_FAILED;
}

void
QO_IMPL(qo_sys_rand_buf)(
    qo_pointer_t    buf ,
    qo_size_t       size
){
    CyrptGenRandom(crypt_prov , buf , size);
    // @todo : Handle error in debug
}