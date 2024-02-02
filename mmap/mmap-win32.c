#include "mmap.h"
#include <winbase.h>

extern 
xocean_stat_t xocean_access_mode_list[4];

struct _XOceanMemmap 
{
    HANDLE              map;
    xocean_pointer_t    begin;
};

XOCEAN_FORCE_INLINE
void
xocean_mmap_translate_mode(
    xocean_flag32_t     mode ,
    PDWORD              fl_prot ,
    PDWORD              desired_access
){
    
    xocean_flag8_t low3 = mode & 0x3;
    *desired_access = xocean_access_mode_list[low3];
    switch(low3)
    {
        case XOCEAN_FILE_READ:
            *fl_prot = PAGE_READONLY;   break;
        case XOCEAN_FILE_READ_WRITE:
            *fl_prot = PAGE_READWRITE;  break;
    }
    
}

XOCEAN_FORCE_INLINE
xocean_stat_t
xocean_mmap_handle_create_error()
{
    switch(GetLastError())
    {
        case ERROR_ACCESS_DENIED:   return XOCEAN_PERMISSION_DENIED;
        case ERROR_INVALID_HANDLE:  return XOCEAN_INVALID_HANDLE;

    }
}

XOCEAN_FORCE_INLINE
xocean_stat_t
xocean_mmap_handle_map_error()
{
    switch(GetLastError())
    {
        
    }
}

xocean_stat_t
XOCEAN_IMPL(xocean_memmap_init)(
    XOceanMemmap *          memmap ,
    XOceanFile *            file ,
    const xocean_offset_t   offset ,
    const xocean_size_t     len ,
    const xocean_flag32_t   mode ,
    const xocean_pointer_t  suggested_addr
){
    const xocean_uint32_t     offset_low  = (xocean_uint32_t)offset;
    const xocean_uint32_t     offset_high = (xocean_uint32_t)(offset >> 32);
    DWORD                     fl_prot , desired_access;
    HANDLE                    map_handle;
    xocean_pointer_t          begin;

    xocean_mmap_translate_mode(mode , &fl_prot , &desired_access);

    map_handle = CreateFileMappingW(XOCEAN_SNULL(file , handle) , NULL , 
                                    fl_prot , 0 , 0 , NULL);

    if(!map_handle)
        return xocean_mmap_handle_create_error();

    begin = MapViewOfFileEx(memmap->map , desired_access , offset_high , offset_low , 
                            len , suggested_addr);
    if(begin)
    {
        memmap->map = map_handle;
        memmap->begin = begin;
        return XOCEAN_OK;
    }
    CloseHandle(map_handle);
    return xocean_mmap_handle_map_error();
}

xocean_pointer_t
XOCEAN_IMPL(xocean_memmap_get)(
    XOceanMemmap *  memmap 
){
    return memmap->begin;
}

void
XOCEAN_IMPL(xocean_memap_close)(
    XOceanMemmap *  memmap
){
    UnmapViewOfFile(memmap->begin);
    CloseHandle(memmap->map);
}