#pragma once

#include <SDL2/SDL_mixer.h>
#include "texture.h"

typedef struct {
    float x;
    float y;
    float velocity_x;
    float velocity_y;
   
    int jumps;
    int max_jumps;

    SDL_Rect rect;
    SDL_Texture *texture;
    Mix_Chunk **jumpEffect;
} t_player;

t_player *new_player(SDL_Texture *texture);
void handle_player_event(t_player *player, SDL_Event *e);
void update_player(t_player *player, float dt);
void render_player(t_player *player, SDL_Renderer *renderer);
