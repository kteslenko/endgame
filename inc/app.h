#pragma once

#include "music.h"
#include "scenes.h"
#include "renderer.h"

typedef struct {
    bool quit;
    t_mus mus;
    t_scene **scenes;
    t_scene *active_scene;
    SDL_Window *window;
    t_renderer *renderer;
    uint32_t event_number;
} t_app;

void psdlerror(const char *desc);
bool init_libs();
t_app *new_app();
void del_app(t_app *app);
void event_loop(t_app *app);
