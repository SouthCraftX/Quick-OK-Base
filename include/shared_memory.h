#pragma once
#define __XOC_SHARED_MEMORY_H__

#include "base.h"

struct _XOC_SharedMemory;
typedef struct _XOC_SharedMemory XOC_SharedMemory;

// --------- Security control flags -----------

/// @brief The owner of the shared memory object can read
#define XOC_SM_OWNER_READ   

/// @brief The owner of the shared memory object can write
#define XOC_SM_OWNER_WRITE  

/// @brief The owner of the shared memory object can execute
#define XOC_SM_OWNER_EXEC   

/// @brief Users in the same group as the owner of the shared memory object can read
#define XOC_SM_GROUP_READ 

/// @brief Users in the same group as the owner of the shared memory object can write
#define XOC_SM_GROUP_WRITE  

/// @brief Users in the same group as the owner of the shared memory object can execute
#define XOC_SM_GROUP_EXEC   

/// @brief Users in groups other than the owner of the shared memory object can read
#define XOC_SM_OTHER_READ   

/// @brief Users in groups other than the owner of the shared memory object can write
#define XOC_SM_OTHER_WRITE  

/// @brief Users in groups other than the owner of the shared memory object can execute
#define XOC_SM_OTHER_EXEC   

/// @brief All users can read
#define XOC_SM_ALL_READ     (XOC_SM_OWNER_READ | XOC_SM_GROUP_READ | \
                            XOC_SM_OTHER_READ)

/// @brief All users can write
#define XOC_SM_ALL_WRITE    (XOC_SM_OWNER_WRITE | XOC_SM_GROUP_WRITE | \
                             XOC_SM_OTHER_WRITE)

/// @brief All users can execute
#define XOC_SM_ALL_EXEC     (XOC_SM_OWNER_EXEC | XOC_SM_GROUP_EXEC | \
                            XOC_SM_OTHER_EXEC)
// --------------------------------------------


/// @brief      All users can read, write and execute
/// @warning    It is strongly recommended to avoid using this flag. All users 
///             having all access means that security and privacy are not 
///             guaranteed. The better practice is to use the nessessary 
///             security flags only.
#define XOC_SM_ALL_ACCESS   (XOC_SM_ALL_READ | XOC_SM_ALL_WRITE | \
                            XOC_SM_ALL_EXEC)

/// @brief      Open a shared memory object.
/// @param      p_shared_memory Pointer to a shared memory object.
/// @param      p_name Pointer to the name of the shared memory object. NULL is 
///             allowed, in this case, a unique name will be generated and will 
///             be written to the name parameter.
/// @param      access_mode The access mode of the shared memory object.
/// @param      security The security flags of the shared memory object.
/// @param      p_memory_size Pointer to the size of the shared memory object.
/// @param      p_name_length The length of the name of the shared memory object.
/// @details    If p_name is NULL, 
///             which indicates the function to generate a unique name and write
///             it to the name parameter, with the size of the name written to 
///             *p_name_length parameter if p_name_length is not NULL. 
///             Otherwise, 
///             *p_name will be taken as the name of the shared memory object, 
///             and the *p_name_length tells the length of the name.
///             If error occurs, nothing will be written.
/// @return     The status of the operation.
/// @retval     XOC_OK The operation was successful.
/// @retval     XOC_OUT_OF_MEMORY No enough memory to allocate the shared memory object.
/// @retval     XOC_PERMISSION_DENIED No permission to open the shared memory object.
/// @sa         xoc_shared_memory_get_address() , xoc_shared_memory_close()
xoc_stat_t
XOC_INTERFACE(xoc_shared_memory_open)(
    XOC_SharedMemory ** p_shared_memory ,
    xoc_cstring_t *     p_name ,
    xoc_flag32_t        access_mode ,
    xoc_flag32_t        security_flags ,
    xoc_size_t *        p_memory_size ,
    xoc_size_t          name_length
) XOC_NONNULL(1);

/// @brief  Get the address of the shared memory object.
/// @return The address of the shared memory object. 
xoc_pointer_t
XOC_INTERFACE(xoc_shared_memory_get_address)(
    XOC_SharedMemory * shared_memory
) XOC_NONNULL(1);

/// @brief  Close the shared memory object.
/// @param  shared_memory The shared memory object to close. NULL is allowed,
///         in this case, nothing will be done.
void
XOC_INTERFACE(xoc_shared_memory_close)(
    XOC_SharedMemory * shared_memory
);

#if XOC_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/shared_memory.h"
#else
#   include "internal/platform_spec/posix/shared_memory.h"
#endif // XOC_PLATFORM(WINDOWS)
