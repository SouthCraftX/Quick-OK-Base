#include "mmap.h"
#include <winbase.h>

extern 
xoc_stat_t xoc_access_mode_list[4];

struct _XOC_MemMap 
{
    HANDLE              map;
    xoc_pointer_t    begin;
};

XOC_FORCE_INLINE
void
xoc_mmap_translate_mode(
    xoc_flag32_t     mode ,
    PDWORD              fl_prot ,
    PDWORD              desired_access
){
    
    xoc_flag8_t low3 = mode & 0x3;
    *desired_access = xoc_access_mode_list[low3];
    switch(low3)
    {
        case XOC_FILE_READ:
            *fl_prot = PAGE_READONLY;   break;
        case XOC_FILE_READ_WRITE:
            *fl_prot = PAGE_READWRITE;  break;
        default:
            *fl_prot = 0;  break;
    }
    
}

XOC_FORCE_INLINE
xoc_stat_t
xoc_mmap_handle_create_error()
{
    switch(GetLastError())
    {
        case ERROR_ACCESS_DENIED:   return XOC_PERMISSION_DENIED;
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;

    }
}

XOC_FORCE_INLINE
xoc_stat_t
xoc_mmap_handle_map_error()
{
    switch(GetLastError())
    {
        
    }
}

xoc_stat_t
XOC_IMPL(xoc_memmap_init)(
    XOC_MemMap *          memmap ,
    XOC_File *            file ,
    const xoc_offset_t   offset ,
    const xoc_size_t     len ,
    const xoc_flag32_t   mode ,
    const xoc_pointer_t  suggested_addr
){
    const xoc_uint32_t     offset_low  = (xoc_uint32_t)offset;
    const xoc_uint32_t     offset_high = (xoc_uint32_t)(offset >> 32);
    DWORD                     fl_prot , desired_access;
    HANDLE                    map_handle;
    xoc_pointer_t          begin;

    xoc_mmap_translate_mode(mode , &fl_prot , &desired_access);

    map_handle = CreateFileMappingW(XOC_SNULL(file , handle) , NULL , 
                                    fl_prot , 0 , 0 , NULL);

    if (!map_handle)
        return xoc_mmap_handle_create_error();

    begin = MapViewOfFileEx(memmap->map , desired_access , offset_high , offset_low , 
                            len , suggested_addr);
    if (begin)
    {
        memmap->map = map_handle;
        memmap->begin = begin;
        return XOC_OK;
    }
    CloseHandle(map_handle);
    return xoc_mmap_handle_map_error();
}

xoc_pointer_t
XOC_IMPL(xoc_memmap_get)(
    XOC_MemMap *  memmap 
){
    return memmap->begin;
}

void
XOC_IMPL(xoc_memap_close)(
    XOC_MemMap *  memmap
){
    UnmapViewOfFile(memmap->begin);
    CloseHandle(memmap->map);
}