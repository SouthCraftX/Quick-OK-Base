#pragma once

#include "../base.h"
#include <SDL2/SDL.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus    

struct _XOCCanvas
{
    SDL_Surface * surface;
};
typedef struct _XOCCanvas XOCCanvas;

XOC_FORCE_INLINE
xoc_size_t
xoc_canvas_get_width(
    XOCCanvas * canvas
){
    return canvas->surface->w;
}

XOC_FORCE_INLINE
xoc_size_t
xoc_canvas_get_height(
    XOCCanvas * canvas
){
    return canvas->surface->h;
}



#if defined(__cplusplus)
}
#endif // __cplusplus