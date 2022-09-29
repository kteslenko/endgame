#include "scenes.h"

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    handle_player_event(game_scene->player, e);
}

static void update(t_scene *scene, float dt) {
    t_game_scene *game_scene = (t_game_scene*)scene;

    update_player(game_scene->player, dt);
    for (int i = 0; i < 15; i++) {
        if (SDL_HasIntersectionF(&game_scene->blocks[i].rect,
                                &game_scene->player->rect)) {
            handle_intersect(game_scene->player, &game_scene->blocks[i].rect);
        }
    }
}

static void render(t_scene *scene, SDL_Renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    
    for (int i = 0; i < 15; i++) {
        SDL_Rect dst = frect_to_rect(&game_scene->blocks[i].rect);
        SDL_RenderCopy(renderer, game_scene->blocks[i].texture, NULL, &dst);
    }
    render_player(game_scene->player, renderer);
}

t_game_scene *new_game_scene(SDL_Renderer *renderer) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;
    game_scene->ground = loadTexture("resource/images/ground.png", renderer);
    game_scene->blocks = malloc(sizeof(t_block) * 15);

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
