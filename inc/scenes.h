#pragma once

#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include "player.h"
#include "map.h"

enum e_scene {
    GAME_SCENE
};

typedef struct s_scene {
    void (*handle_event)(struct s_scene *scene, SDL_Event *e);
    void (*update)(struct s_scene *scene, float dt);
    void (*render)(struct s_scene *scene, t_renderer *renderer);
} t_scene;

typedef struct {
    t_scene scene;
    t_map *map;
    t_player *player;

    t_block *coins[19];
    int score;

    SDL_Texture *sky;
    TTF_Font* font;
} t_game_scene;

typedef struct {
    t_scene scene;
} t_menu_scene;

t_game_scene *new_game_scene(t_renderer *renderer);

