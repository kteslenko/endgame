#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "geometry.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Rect *active;
    SDL_Rect camera;
    SDL_Rect screen;
} t_renderer;

void render_clear(t_renderer *renderer);
void render_present(t_renderer *renderer);
void mode_screen(t_renderer *renderer);
void mode_camera(t_renderer *renderer);
void render_texturef(t_renderer *renderer, SDL_Texture *texture, SDL_Rect *src, SDL_FRect *frect);
void render_texture(t_renderer *renderer, SDL_Texture *texture, SDL_Rect *src, SDL_Rect *rect);
void render_text(t_renderer *renderer, const char *text, TTF_Font *font, SDL_Point pos, SDL_Color color);