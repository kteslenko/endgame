#include "geometry.h"

SDL_FPoint ftop_left(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x, rect->y};
}

SDL_FPoint ftop_right(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x + rect->w, rect->y};
}

SDL_FPoint fbottom_left(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x, rect->y + rect->h};
}

SDL_FPoint fbottom_right(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x + rect->w, rect->y + rect->h};
}

SDL_Point top_left(SDL_Rect *rect) {
    return (SDL_Point){rect->x, rect->y};
}

SDL_Point top_right(SDL_Rect *rect) {
    return (SDL_Point){rect->x + rect->w - 1, rect->y};
}

SDL_Point bottom_left(SDL_Rect *rect) {
    return (SDL_Point){rect->x, rect->y + rect->h - 1};
}

SDL_Point bottom_right(SDL_Rect *rect) {
    return (SDL_Point){rect->x + rect->w - 1, rect->y + rect->h - 1};
}

SDL_Rect frect_to_rect(SDL_FRect *rect) {
    return (SDL_Rect){roundf(rect->x), roundf(rect->y), roundf(rect->w), roundf(rect->h)};
}

SDL_FRect rect_to_frect(SDL_Rect *rect) {
    return (SDL_FRect){rect->x, rect->y, rect->w, rect->h};
}
