#include "include/thread.h"
#include <sched.h>
#include <pthread.h>


int
__qo_thread_adjust_high_priority(
    QO_Thread                thread ,
    enum QO_ThreadPriority   priority
){
    const int crazy = sched_get_priority_max(SCHED_RR) ,
              highest = crazy * .8 ,
              high = highest >> 1;
    int priority_value;
    
    switch (priority)
    {   
        case QO_THREAD_PRIORITY_CRAZY:      
            priority_value = crazy; 
            break;

        case QO_THREAD_PRIORITY_HIGHEST:    
            priority_value = highest; 
            break;

        case QO_THREAD_PRIORITY_HIGH:
            priority_value = high; 
            break;
    }
    int ret = pthread_setschedparam(thread.thread_handle , SCHED_RR , priority_value);

}

qo_stat_t
QO_IMPL(qo_thread_adjust_priority)(
    QO_Thread                thread ,
    enum QO_ThreadPriority   priority
){
    
}