#include "app.h"

void psdlerror(const char *desc) {
    fprintf(stderr, "%s: %s\n", desc, SDL_GetError());
}

bool init_libs() {
    return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0
           && IMG_Init(IMG_INIT_PNG) != 0
           && Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0
           && TTF_Init() == 0;
}

static void createWindow(SDL_Window **window, t_renderer **renderer) { //function that creates window
    *window = SDL_CreateWindow("SDL2",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    1280, 720, SDL_WINDOW_RESIZABLE); //size of the window

    *renderer = malloc(sizeof(t_renderer));
    (*renderer)->renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    (*renderer)->screen = (SDL_Rect){0, 0, 1280, 720};
    (*renderer)->camera = (SDL_Rect){0, 0, 1280, 720};
    (*renderer)->active = &(*renderer)->screen;
}

static void create_scenes(t_app *app) {
    app->event_number = SDL_RegisterEvents(2);
    app->scenes = malloc(sizeof(t_scene*) * 2);
    app->scenes[GAME_SCENE] = (t_scene*)new_game_scene(app->renderer, app->event_number);
    app->scenes[MENU_SCENE] = (t_scene*)new_menu_scene(app->renderer, app->event_number);
    app->active_scene = app->scenes[MENU_SCENE];
}

t_app *new_app() {
    t_app *app = malloc(sizeof(t_app));

    app->quit = false;
    createWindow(&app->window, &app->renderer);
    if (app->window == NULL || app->renderer == NULL) {
        del_app(app);
        app = NULL;
    }
    load_textures(app->renderer);
    create_scenes(app);
    init_music(&app->mus);

    return app;
}

void del_app(t_app *app) {
    if (app == NULL) {
        return;
    }
    if (app->renderer != NULL) {
        SDL_DestroyRenderer(app->renderer->renderer);
        free(app->renderer);
    }
    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }
    del_music(&app->mus);
    free(app);
}

static void handle_event(t_app *app, SDL_Event *e) {
    if (e->type == SDL_QUIT) {
        app->quit = true;
    }
    if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED) {
        app->renderer->screen.w = e->window.data1;
        app->renderer->screen.h = e->window.data2;
    }
    if (e->type == app->event_number + ACTIVE_SCENE_CHANGED) {
        app->active_scene = app->scenes[e->user.code];
    }
    if (app->active_scene != NULL) {
        app->active_scene->handle_event(app->active_scene, e);
    }
}

static void update(t_app *app, float dt) {
    if (app->active_scene != NULL && app->active_scene->update != NULL) {
        app->active_scene->update(app->active_scene, dt);
    }
}

static void render(t_app *app) {
    if (app->active_scene != NULL) {
        app->active_scene->render(app->active_scene, app->renderer);
    }
}

static float dt(uint32_t *last) {
    uint32_t now = SDL_GetTicks();
    float dt = (float)(now - *last) / 1000;

    *last = now;
    return dt;
}

void event_loop(t_app *app) {
    SDL_Event e;
    uint32_t last = SDL_GetTicks();

    while (!app->quit) {
        while (SDL_PollEvent (&e) != 0) {
            play_music(&(app->mus));
            handle_event(app, &e);
        }
        update(app, dt(&last));
        
        render_clear(app->renderer);
        render(app);
        render_present(app->renderer);
    }
}
