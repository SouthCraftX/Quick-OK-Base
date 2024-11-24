

QO_FORCE_INLINE
qo_stat_t
__qo_thread_creating_error()
{
    switch (GetLastError())
    {
        case ERROR_NO_ENOUGH_MEMORY:    return QO_OUT_OF_MEMORY; 
        case ERROR_INVALID_PARAMETER:   return QO_INVALID_ARG;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

qo_stat_t
QO_IMPL(qo_thread_init)(
    QO_Thread **           thread ,
    const qo_pointer_t     func ,
    const qo_pointer_t     arg ,
    const qo_size_t        stack_size 
){
    HANDLE thread_handle = CreateThread(
        NULL , stack_size , (LPTHREAD_START_ROUTINE)func , arg , 0 , NULL
    );

    if (!thread_handle)
        return __qo_thread_creating_error();
    
    (HANDLE)(*thread) = thread_handle;
    return QO_OK;
}

qo_stat_t
QO_IMPL(qo_thread_get_priority)(
    QO_Thread        thread ,
    qo_flag32_t *   priority
){
    // @todo Support REALTIME_PRIORITY_CLASS
    switch (GetThreadPriority(thread.thread_handle))
    {
        case THREAD_PRIORITY_IDLE:
        case THREAD_PRIORITY_LOWEST:  
            *priority = QO_THREAD_PRIORITY_LOWEST;
            return QO_OK;

        case THREAD_PRIORITY_BELOW_NORMAL: 
            *priority = QO_THREAD_PRIORITY_LOW;
            return QO_OK;
        
        case THREAD_PRIORITY_NORMAL:
            *priority = QO_THREAD_PRIORITY_NORMAL;
            return QO_OK;

        case THREAD_PRIORITY_ABOVE_NORMAL:
            *priority = QO_THREAD_PRIORITY_HIGH;
            return QO_OK;

        case THREAD_PRIORITY_HIGHEST:
            *priority = QO_THREAD_PRIORITY_HIGHEST;
            return QO_OK;

        case THREAD_PRIORITY_TIME_CRITICAL:
        case 31:    // REALTIME_PRIORITY_CLASS
            *priority = QO_THREAD_PRIORITY_CRAZY;
            return QO_OK;

        default:
            return __qo_thread_priority_setting_error();
    }
}