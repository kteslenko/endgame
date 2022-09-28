#include "scenes.h"

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_game_scene *game_scene = (t_game_scene*)scene;

    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE) {
        game_scene->moving = !game_scene->moving;
    }
}

static void update(t_scene *scene, float dt) {
    t_game_scene *game_scene = (t_game_scene*)scene;

    if (game_scene->moving) {
        game_scene->time += dt;
    }
}

static void render(t_scene *scene, SDL_Renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    float pos_y = sinf(game_scene->time * 200) * 100 + 100;

    build_platform(renderer, game_scene->ground, 100, pos_y, 5);
}

t_game_scene *new_game_scene(SDL_Renderer *renderer) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;

    game_scene->time = 0;
    game_scene->moving = true;
    game_scene->ground = loadTexture("resources/images/ground.png", renderer);

    return game_scene;
}
