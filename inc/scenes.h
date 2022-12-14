#pragma once

#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#include "animation.h"
#include "player.h"
#include "events.h"
#include "map.h"

enum e_scene {
    GAME_SCENE,
    MENU_SCENE,
    LOSING_MENU_SCENE,
    WIN_MENU_SCENE
};

typedef struct s_scene {
    uint32_t event_number;
    void (*handle_event)(struct s_scene *scene, SDL_Event *e);
    void (*update)(struct s_scene *scene, float dt);
    void (*render)(struct s_scene *scene, t_renderer *renderer);
    void (*clean)(struct s_scene *scene);
} t_scene;

typedef struct {
    t_scene scene;
    t_map *map;
    t_player *player;

    t_animation *coin_animation;
    int score;

    TTF_Font* font;
    Mix_Chunk **coinEffect;
} t_game_scene;

typedef struct {
    t_scene scene;

    t_block start_game;
    t_block exit_game;

    TTF_Font *font;
    TTF_Font *name_font;
    enum e_scene type;
} t_menu_scene;

t_game_scene *new_game_scene(t_renderer *renderer, uint32_t event_number);
void reset_level(t_game_scene *game_scene);
t_menu_scene *new_menu_scene(t_renderer *renderer, uint32_t event_number, enum e_scene type);
