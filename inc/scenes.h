#pragma once

#include <stdbool.h>

#include "texture.h"

enum e_scene {
    GAME_SCENE
};

typedef struct s_scene {
    void (*handle_event)(struct s_scene *scene, SDL_Event *e);
    void (*update)(struct s_scene *scene, float dt);
    void (*render)(struct s_scene *scene, SDL_Renderer *renderer);
} t_scene;

typedef struct {
    t_scene scene;
    float time;
    bool moving;
    SDL_Texture *ground;
} t_game_scene; // Just example scene

t_game_scene *new_game_scene(SDL_Renderer *renderer);
