#include "app.h"

void psdlerror(const char *desc) {
	fprintf(stderr, "%s: %s\n", desc, SDL_GetError());
}

bool init_libs() {
	return SDL_Init(SDL_INIT_VIDEO) == 0
		   && IMG_Init(IMG_INIT_PNG) != 0;
}

static void createWindow(SDL_Window **window, SDL_Renderer **renderer) { //function that creates window
	*window = SDL_CreateWindow("SDL2",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	1280, 720, 0); //size of the window

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

static void create_scenes(t_app *app) {
    app->scenes = malloc(sizeof(t_scene*));
    app->scenes[GAME_SCENE] = (t_scene*)new_game_scene(app->renderer);
	app->active_scene = app->scenes[GAME_SCENE];
}

t_app *new_app() {
	t_app *app = malloc(sizeof(t_app));

	app->quit = false;
	createWindow(&app->window, &app->renderer);
	if (app->window == NULL || app->renderer == NULL) {
		del_app(app);
		app = NULL;
	}
    create_scenes(app);

	return app;
}

void del_app(t_app *app) {
	if (app == NULL) {
		return;
	}
	if (app->renderer != NULL) {
		SDL_DestroyRenderer(app->renderer);
	}
	if (app->window != NULL) {
		SDL_DestroyWindow(app->window);
	}
	free(app);
}

static void handle_event(t_app *app, SDL_Event *e) {
	if (e->type == SDL_QUIT) {
		app->quit = true;
	}
    if (app->active_scene != NULL) {
        app->active_scene->handle_event(app->active_scene, e);
    }
}

static void update(t_app *app, float dt) {
    if (app->active_scene != NULL) {
        app->active_scene->update(app->active_scene, dt);
    }
}

static void render(t_app *app) {
	if (app->active_scene != NULL) {
		app->active_scene->render(app->active_scene, app->renderer);
	}
}

static float dt(uint64_t *last) {
    uint64_t now = SDL_GetTicks64();
    float dt = (float)(now - *last) / 1000;

    *last = now;
    return dt;
}

void event_loop(t_app *app) {
	SDL_Event e;
    uint64_t last = SDL_GetTicks64();

	while (!app->quit) {
		while (SDL_PollEvent (&e) != 0) {
			handle_event(app, &e);
		}
        update(app, dt(&last));
		
		SDL_RenderClear(app->renderer);
		render(app);
        SDL_RenderPresent(app->renderer);
	}
}
