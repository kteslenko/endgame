#include "scenes.h"

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED) {
        game_scene->camera.w = e->window.data1;
        game_scene->camera.h = e->window.data2;
    }
    handle_player_event(game_scene->player, e);
}

static void update_camera(t_game_scene *scene) {
    scene->camera.x = roundf(scene->player->rect.x + scene->player->rect.w / 2) - scene->camera.w / 2;
    scene->camera.y = roundf(scene->player->rect.y + scene->player->rect.h / 2) - scene->camera.h / 2;
}

static void update(t_scene *scene, float dt) {
    t_game_scene *game_scene = (t_game_scene*)scene;

    update_player(game_scene->player, dt);
    for (int i = 0; i < 15; i++) {
    	SDL_Rect player = frect_to_rect(&game_scene->player->rect);
    	SDL_Rect block = frect_to_rect(&game_scene->blocks[i].rect);
        if (SDL_HasIntersection(&player, &block)) {
            handle_intersect(game_scene->player, &game_scene->blocks[i].rect);
        }
    }
    update_camera(game_scene);
}

static void render(t_scene *scene, SDL_Renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    
    for (int i = 0; i < 15; i++) {
        SDL_Rect dst = frect_to_rect(&game_scene->blocks[i].rect);
        dst.x -= game_scene->camera.x;
        dst.y -= game_scene->camera.y;
        SDL_RenderCopy(renderer, game_scene->blocks[i].texture, NULL, &dst);
    }
    render_player(game_scene->player, renderer, &game_scene->camera);
}

t_game_scene *new_game_scene(SDL_Renderer *renderer) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;
    game_scene->ground = loadTexture("resource/images/ground.png", renderer);
    game_scene->blocks = malloc(sizeof(t_block) * 15);
    SDL_RenderGetViewport(renderer, &game_scene->camera);
    update_camera(game_scene);

    SDL_Texture *player_texture = loadTexture("resource/images/ghost-Sheet.png", renderer);
    
    game_scene->player = new_player(player_texture);
    
    for (int i = 0; i < 10; i++) {
        game_scene->blocks[i].texture = game_scene->ground;
        game_scene->blocks[i].rect.x = i * 64.0f;
        game_scene->blocks[i].rect.y = 656.0f;
        game_scene->blocks[i].rect.w = 64.0f;
        game_scene->blocks[i].rect.h = 64.0f;
    }
    for (int i = 10; i < 15; i++) {
        game_scene->blocks[i].texture = game_scene->ground;
        game_scene->blocks[i].rect.x = (i - 5) * 64.0f;
        game_scene->blocks[i].rect.y = 292.0f;
        game_scene->blocks[i].rect.w = 64.0f;
        game_scene->blocks[i].rect.h = 64.0f;
    }

    return game_scene;
}
