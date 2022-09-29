#pragma once

#include "texture.h"
#include "geometry.h"

typedef struct { 
    int jumps;
    int max_jumps;
    SDL_FRect prev;
    SDL_FRect rect;
    SDL_FPoint velocity;
    SDL_Texture *texture;
} t_player;

t_player *new_player(SDL_Texture *texture);
void handle_player_event(t_player *player, SDL_Event *e);
void update_player(t_player *player, float dt);
void render_player(t_player *player, SDL_Renderer *renderer);
void handle_intersect(t_player *player, SDL_FRect *rect);
