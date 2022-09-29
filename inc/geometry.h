#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_FPoint top_left(SDL_FRect *rect);
SDL_FPoint top_right(SDL_FRect *rect);
SDL_FPoint bottom_left(SDL_FRect *rect);
SDL_FPoint bottom_right(SDL_FRect *rect);
SDL_Rect frect_to_rect(SDL_FRect *rect);
bool approx_eq(float a, float b);
bool in_rect(SDL_FPoint *point, SDL_FRect *rect);
