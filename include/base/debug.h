#pragma once
#include "types.h"
#include "attribute.h"

#if defined(__cplusplus)
extern "C" {
#endif 

#if defined(QO_DEBUG)

#   define QO_ASSERT(expr)  ((expr) ? 0 : __qo_assert_fail(#expr , NULL ,\
           __FILE__ , __func__ , __LINE__))

#   define QO_REPORT_BUG(message) __qo_report_bug(message , __FILE__ , \
           __func__ , __LINE__)

#   define QO_NULLPTR_ASSERT(ptr) ((ptr) ? 0 : __qo_nullptr_assert_fail( \
           __FILE__ , __func__ , __LINE__))

QO_NORETURN 
void 
__qo_assert_fail(
    qo_ccstring     expr ,
    qo_ccstring_t   reason , 
    qo_ccstring_t   source_file ,
    qo_ccstring_t   func_name ,
    qo_int32_t      line
){
    QO_ERRPRINT("Assertion failed: %s, reason: %s, source file %s, "
                    "function %s, line %d\n",    
                    expr , reason , source_file , func_name ,line);
    QO_ABORT();
}

QO_NORETURN
void
__qo_nullptr_assert_fail(
    qo_ccstring_t   source_file ,
    qo_ccstring_t   func_name ,
    qo_int32_t      line
){
    QO_ERRPRINT("Null pointer assertion failed, source file %s, "
                    "function %s, line %d\n",    
                    source_file , func_name , line);
    QO_ABORT(); 
}

QO_NORETURN
void 
__qo_report_bug(
    qo_ccstring_t   message ,
    qo_ccstring_t   source_file ,
    qo_ccstring_t   func_name ,
    qo_int32_t      line
){
    QO_ERRPRINT("Bug report: %s, source file %s, function %s, line %d\n",    
                    message , source_file , func_name , line);
    QO_ABORT();
}

#else
#   define QO_ASSERT(expr)
#   define QO_REPORT_BUG(message)
#   define QO_NULLPTR_ASSERT(ptr)

#endif // QO_DEBUG



#if defined(__cplusplus)
}
#endif


