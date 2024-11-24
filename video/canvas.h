#pragma once

#include "../base.h"
#include <SDL2/SDL.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus    

struct _QOCanvas
{
    SDL_Surface * surface;
};
typedef struct _QOCanvas QOCanvas;

QO_FORCE_INLINE
qo_size_t
qo_canvas_get_width(
    QOCanvas * canvas
){
    return canvas->surface->w;
}

QO_FORCE_INLINE
qo_size_t
qo_canvas_get_height(
    QOCanvas * canvas
){
    return canvas->surface->h;
}



#if defined(__cplusplus)
}
#endif // __cplusplus