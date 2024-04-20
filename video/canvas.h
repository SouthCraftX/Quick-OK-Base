#pragma once

#include "../base.h"
#include <SDL2/SDL.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus    

struct _XOceanCanvas
{
    SDL_Surface * surface;
};
typedef struct _XOceanCanvas XOceanCanvas;

XOCEAN_FORCE_INLINE
xocean_size_t
xocean_canvas_get_width(
    XOceanCanvas * canvas
){
    return canvas->surface->w;
}

XOCEAN_FORCE_INLINE
xocean_size_t
xocean_canvas_get_height(
    XOceanCanvas * canvas
){
    return canvas->surface->h;
}



#if defined(__cplusplus)
}
#endif // __cplusplus