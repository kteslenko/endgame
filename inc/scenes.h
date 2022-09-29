#pragma once

#include <stdbool.h>

#include "player.h"

enum e_scene {
    GAME_SCENE
};

typedef struct s_scene {
    void (*handle_event)(struct s_scene *scene, SDL_Event *e);
    void (*update)(struct s_scene *scene, float dt);
    void (*render)(struct s_scene *scene, SDL_Renderer *renderer);
} t_scene;

typedef struct {
    SDL_FRect rect;
    SDL_Texture *texture;
} t_block;

typedef struct {
    t_scene scene;
    t_block *blocks;
    t_player *player;
    SDL_Rect camera;
    SDL_Texture *ground;
} t_game_scene;

typedef struct {
    t_scene scene;
} t_menu_scene;

t_game_scene *new_game_scene(SDL_Renderer *renderer);
