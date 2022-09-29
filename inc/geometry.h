#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_FPoint ftop_left(SDL_FRect *rect);
SDL_FPoint ftop_right(SDL_FRect *rect);
SDL_FPoint fbottom_left(SDL_FRect *rect);
SDL_FPoint fbottom_right(SDL_FRect *rect);
SDL_Point top_left(SDL_Rect *rect);
SDL_Point top_right(SDL_Rect *rect);
SDL_Point bottom_left(SDL_Rect *rect);
SDL_Point bottom_right(SDL_Rect *rect);
SDL_Rect frect_to_rect(SDL_FRect *rect);
SDL_FRect rect_to_frect(SDL_Rect *rect);
