#include "scenes.h"

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    handle_player_event(game_scene->player, e);
}

static void update(t_scene *scene, float dt) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    update_player(game_scene->player, dt);
    SDL_Rect result;
    for (int i = 0; i < 10; i++) {
        if (SDL_IntersectRect(&game_scene->blocks[i].rect,
                              &game_scene->player->rect,
                              &result)) {
            handle_intersect(game_scene->player, &result);
        }
    }
}

static void render(t_scene *scene, SDL_Renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    
    for (int i = 0; i < 10; i++) {
       SDL_RenderCopy(renderer, game_scene->blocks[i].texture, NULL, &game_scene->blocks[i].rect);
    }
    render_player(game_scene->player, renderer);
}

t_game_scene *new_game_scene(SDL_Renderer *renderer) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;
    game_scene->ground = loadTexture("resources/images/ground.png", renderer);
    game_scene->blocks = malloc(sizeof(t_block) * 10);

    SDL_Texture *player_texture = loadTexture("resources/images/ghost-Sheet.png", renderer);
    
    game_scene->player = new_player(player_texture);
    
    for (int i = 0; i < 10; i++) {
        game_scene->blocks[i].texture = game_scene->ground;
        game_scene->blocks[i].rect.x = i * 64;
        game_scene->blocks[i].rect.y = 656;
        game_scene->blocks[i].rect.w = 64;
        game_scene->blocks[i].rect.h = 64;
    }

    return game_scene;
}
