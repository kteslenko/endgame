#pragma once

#include "renderer.h"

typedef struct {
    float time;
    int fps;
    int count;
    int current;
    SDL_Rect *frames;
    SDL_Texture *texture;
} t_animation;

t_animation *new_animation(SDL_Texture *texture, int fps, int count);
void push_frame(t_animation *animation, SDL_Rect frame);
void update_animation(t_animation *animation, float dt);
void render_animation(t_animation *animation, t_renderer *renderer, SDL_FRect *rect);

t_animation *coin_animation(t_renderer *renderer);
