#pragma once
#include "types.h"
#include "attribute.h"

#if defined(__cplusplus)
extern "C" {
#endif 

#if defined(XOC_DEBUG)

#   define XOC_ASSERT(expr)  ((expr) ? 0 : __xoc_assert_fail(#expr , NULL ,\
           __FILE__ , __func__ , __LINE__))

#   define XOC_REPORT_BUG(message) __xoc_report_bug(message , __FILE__ , \
           __func__ , __LINE__)

#   define XOC_NULLPTR_ASSERT(ptr) ((ptr) ? 0 : __xoc_nullptr_assert_fail( \
           __FILE__ , __func__ , __LINE__))

XOC_NORETURN 
void 
__xoc_assert_fail(
    xoc_ccstring     expr ,
    xoc_ccstring_t   reason , 
    xoc_ccstring_t   source_file ,
    xoc_ccstring_t   func_name ,
    xoc_int32_t      line
){
    XOC_ERRPRINT("Assertion failed: %s, reason: %s, source file %s, "
                    "function %s, line %d\n",    
                    expr , reason , source_file , func_name ,line);
    XOC_ABORT();
}

XOC_NORETURN
void
__xoc_nullptr_assert_fail(
    xoc_ccstring_t   source_file ,
    xoc_ccstring_t   func_name ,
    xoc_int32_t      line
){
    XOC_ERRPRINT("Null pointer assertion failed, source file %s, "
                    "function %s, line %d\n",    
                    source_file , func_name , line);
    XOC_ABORT(); 
}

XOC_NORETURN
void 
__xoc_report_bug(
    xoc_ccstring_t   message ,
    xoc_ccstring_t   source_file ,
    xoc_ccstring_t   func_name ,
    xoc_int32_t      line
){
    XOC_ERRPRINT("Bug report: %s, source file %s, function %s, line %d\n",    
                    message , source_file , func_name , line);
    XOC_ABORT();
}

#else
#   define XOC_ASSERT(expr)
#   define XOC_REPORT_BUG(message)
#   define XOC_NULLPTR_ASSERT(ptr)

#endif // XOC_DEBUG



#if defined(__cplusplus)
}
#endif


