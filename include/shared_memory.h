#pragma once
#define __QO_SHARED_MEMORY_H__

#include "base.h"

struct _QO_SharedMemory;
typedef struct _QO_SharedMemory QO_SharedMemory;

// --------- Security control flags -----------
// Their values are implementation-defined

/// @brief The owner of the shared memory object can read
#define QO_SM_OWNER_READ   

/// @brief The owner of the shared memory object can write
#define QO_SM_OWNER_WRITE  

/// @brief The owner of the shared memory object can execute
#define QO_SM_OWNER_EXEC   

/// @brief Users in the same group as the owner of the shared memory object can read
#define QO_SM_GROUP_READ 

/// @brief Users in the same group as the owner of the shared memory object can write
#define QO_SM_GROUP_WRITE  

/// @brief Users in the same group as the owner of the shared memory object can execute
#define QO_SM_GROUP_EXEC   

/// @brief Users in groups other than the owner of the shared memory object can read
#define QO_SM_OTHER_READ   

/// @brief Users in groups other than the owner of the shared memory object can write
#define QO_SM_OTHER_WRITE  

/// @brief Users in groups other than the owner of the shared memory object can execute
#define QO_SM_OTHER_EXEC   

/// @brief All users can read
#define QO_SM_ALL_READ     (QO_SM_OWNER_READ | QO_SM_GROUP_READ | \
                            QO_SM_OTHER_READ)

/// @brief All users can write
#define QO_SM_ALL_WRITE    (QO_SM_OWNER_WRITE | QO_SM_GROUP_WRITE | \
                             QO_SM_OTHER_WRITE)

/// @brief All users can execute
#define QO_SM_ALL_EXEC     (QO_SM_OWNER_EXEC | QO_SM_GROUP_EXEC | \
                            QO_SM_OTHER_EXEC)

/// @brief      All users can read, write and execute
/// @warning    It is strongly recommended to avoid using this flag. All users 
///             having all access means that security and privacy are not 
///             guaranteed. The better practice is to use the nessessary 
///             security flags only.
#define QO_SM_ALL_ACCESS   (QO_SM_ALL_READ | QO_SM_ALL_WRITE | \
                            QO_SM_ALL_EXEC)
// --------------------------------------------

/// @brief      Open a shared memory object.
/// @param      p_shared_memory Pointer to a shared memory object.
/// @param      p_name Pointer to the name of the shared memory object. NULL is 
///             allowed, in this case, a unique name will be generated and will 
///             be written to the name parameter.
/// @param      access_mode The access mode of the shared memory object.
/// @param      security The security flags of the shared memory object.
/// @param      p_memory_size Pointer to the size of the shared memory object.
/// @param      p_name_length Pointer to the length of the name of the shared 
///             memory object. If p_name is not NULL, *p_name_length will be
///             taken as the length of the name. Otherwise, *p_name_length will
///             written with the length of the generated name if p_name_length 
///             is not NULL.
/// @details    - If p_name is NULL, 
///             which indicates the function to generate a unique name and write
///             it to the name parameter, with the size of the name written to 
///             *p_name_length parameter if p_name_length is not NULL. 
///             Otherwise, 
///             *p_name will be taken as the name of the shared memory object, 
///             and the *p_name_length tells the length of the name.
///             If error occurs, nothing will be written.
///             For capability consideration, the length of the name is limited
///             between 5 and 255 characters.
/// @return     The status of the operation.
/// @retval     QO_OK The operation was successful.
/// @retval     QO_OUT_OF_MEMORY No enough memory to allocate the shared memory
///             object.
/// @retval     QO_PERMISSION_DENIED No permission to open the shared memory 
///             object.
/// @sa         qo_shared_memory_get_address() , qo_shared_memory_close()
qo_stat_t
QO_INTERFACE(qo_shared_memory_open)(
    QO_SharedMemory ** p_shared_memory ,
    qo_cstring_t *     p_name ,
    qo_flag32_t        access_mode ,
    qo_flag32_t        security_flags ,
    qo_pointer_t *     p_memory ,
    qo_size_t          memory_size ,
    qo_size_t *        p_name_length
) QO_NONNULL(1);

/// @brief  Close the shared memory object.
/// @param  shared_memory The shared memory object to close. NULL is allowed,
///         in this case, nothing will be done.
void
QO_INTERFACE(qo_shared_memory_close)(
    QO_SharedMemory * shared_memory
);

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/shared_memory.h"
#else
#   include "internal/platform_spec/posix/shared_memory.h"
#endif // QO_PLATFORM(WINDOWS)
