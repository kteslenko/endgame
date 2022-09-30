#pragma once

#include <SDL2/SDL_mixer.h>
#include "animation.h"

enum e_state {
    IDLE_STATE,
    JUMP_STATE,
    WALK_STATE,
};

typedef struct { 
    int jumps;
    int max_jumps;
    SDL_FRect prev;
    SDL_FRect rect;
    SDL_FPoint velocity;
    enum e_state state;
    t_animation **animations;
    Mix_Chunk **jumpEffect;
} t_player;

t_player *new_player(t_renderer *renderer);
void reset_player(t_player *player);
void clean_player(t_player *player);
void handle_player_event(t_player *player, SDL_Event *e);
void update_player(t_player *player, float dt);
void render_player(t_player *player, t_renderer *renderer);
void handle_intersect(t_player *player, SDL_FRect *rect);
