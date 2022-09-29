#include "geometry.h"

SDL_FPoint top_left(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x, rect->y};
}

SDL_FPoint top_right(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x + rect->w, rect->y};
}

SDL_FPoint bottom_left(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x, rect->y + rect->h};
}

SDL_FPoint bottom_right(SDL_FRect *rect) {
    return (SDL_FPoint){rect->x + rect->w, rect->y + rect->h};
}

SDL_Rect frect_to_rect(SDL_FRect *rect) {
    return (SDL_Rect){rect->x, rect->y, rect->w, rect->h};
}

bool approx_eq(float a, float b) {
    return fabs(a - b) < 2;
}

bool in_rect(SDL_FPoint *point, SDL_FRect *rect) {
    return point->x > rect->x
           && point->y > rect->y
           && point->x < rect->x + rect->w
           && point->y < rect->y + rect->h;
}
