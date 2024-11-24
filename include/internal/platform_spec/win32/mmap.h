#include "mmap.h"
#include <winbase.h>

extern 
qo_stat_t qo_access_mode_list[4];

struct _QO_MemMap 
{
    HANDLE              map;
    qo_pointer_t    begin;
};

QO_FORCE_INLINE
void
qo_mmap_translate_mode(
    qo_flag32_t     mode ,
    PDWORD              fl_prot ,
    PDWORD              desired_access
){
    
    qo_flag8_t low3 = mode & 0x3;
    *desired_access = qo_access_mode_list[low3];
    switch(low3)
    {
        case QO_FILE_READ:
            *fl_prot = PAGE_READONLY;   break;
        case QO_FILE_READ_WRITE:
            *fl_prot = PAGE_READWRITE;  break;
        default:
            *fl_prot = 0;  break;
    }
    
}

QO_FORCE_INLINE
qo_stat_t
qo_mmap_handle_create_error()
{
    switch(GetLastError())
    {
        case ERROR_ACCESS_DENIED:   return QO_PERMISSION_DENIED;
        case ERROR_INVALID_HANDLE:  return QO_INVALID_HANDLE;

    }
}

QO_FORCE_INLINE
qo_stat_t
qo_mmap_handle_map_error()
{
    switch(GetLastError())
    {
        
    }
}

qo_stat_t
QO_IMPL(qo_memmap_init)(
    QO_MemMap *          memmap ,
    QO_File *            file ,
    const qo_offset_t   offset ,
    const qo_size_t     len ,
    const qo_flag32_t   mode ,
    const qo_pointer_t  suggested_addr
){
    const qo_uint32_t     offset_low  = (qo_uint32_t)offset;
    const qo_uint32_t     offset_high = (qo_uint32_t)(offset >> 32);
    DWORD                     fl_prot , desired_access;
    HANDLE                    map_handle;
    qo_pointer_t          begin;

    qo_mmap_translate_mode(mode , &fl_prot , &desired_access);

    map_handle = CreateFileMappingW(QO_SNULL(file , handle) , NULL , 
                                    fl_prot , 0 , 0 , NULL);

    if (!map_handle)
        return qo_mmap_handle_create_error();

    begin = MapViewOfFileEx(memmap->map , desired_access , offset_high , offset_low , 
                            len , suggested_addr);
    if (begin)
    {
        memmap->map = map_handle;
        memmap->begin = begin;
        return QO_OK;
    }
    CloseHandle(map_handle);
    return qo_mmap_handle_map_error();
}

qo_pointer_t
QO_IMPL(qo_memmap_get)(
    QO_MemMap *  memmap 
){
    return memmap->begin;
}

void
QO_IMPL(qo_memap_close)(
    QO_MemMap *  memmap
){
    UnmapViewOfFile(memmap->begin);
    CloseHandle(memmap->map);
}