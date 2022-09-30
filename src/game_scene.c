#include "scenes.h"

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    handle_player_event(game_scene->player, e);
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
    for (int i = 0; i < 19; i++) {
        if (game_scene->coins[i] != NULL) {
            SDL_Rect player = frect_to_rect(&game_scene->player->rect);
            SDL_Rect coin = frect_to_rect(&game_scene->coins[i]->rect);
            if (SDL_HasIntersection(&player, &coin)) {
                game_scene->score++;
                free(game_scene->coins[i]);
                game_scene->coins[i] = NULL;
            }
        }
    }
}

static void render_sky(t_game_scene *game_scene, t_renderer *renderer) {
    SDL_Rect dst = {0, 0, 0, 0};

    SDL_QueryTexture(game_scene->sky, NULL, NULL, &dst.w, &dst.h);
    dst.w *= (float)renderer->camera.h / dst.h;
    dst.h = renderer->camera.h;

    mode_screen(renderer);
    while (dst.x < renderer->camera.w) {
        render_texture(renderer, game_scene->sky, NULL, &dst);
        dst.x += dst.w;
    }
}

static void render_scene_text(t_game_scene *game_scene, t_renderer *renderer) {
    char count_score[30] = "SCORE: ";
    SDL_Point pos = {20, 12};
    SDL_Color color = {0, 0, 0, 255};

    SDL_itoa(game_scene->score, count_score + 7, 10);
    render_text(renderer, count_score, game_scene->font, pos, color);
}

static void move_camera(t_game_scene *scene, t_renderer *renderer) {
    renderer->camera.w = renderer->screen.w;
    renderer->camera.h = renderer->screen.h;
    renderer->camera.x = roundf(scene->player->rect.x + scene->player->rect.w / 2) - renderer->camera.w / 2;
    renderer->camera.y = roundf(scene->player->rect.y + scene->player->rect.h / 2) - renderer->camera.h / 2;
}

static void render(t_scene *scene, t_renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    move_camera(game_scene, renderer);
    render_sky(game_scene, renderer);

    mode_camera(renderer);
    for (int i = 0; i < 15; i++) {
        render_texturef(renderer,  game_scene->blocks[i].texture, NULL, &game_scene->blocks[i].rect);
    }
    for (int i = 0; i < 19; i++) {
        if (game_scene->coins[i] != NULL) {
            render_texturef(renderer,  game_scene->coins[i]->texture, NULL, &game_scene->coins[i]->rect);
        }
    }
    render_player(game_scene->player, renderer);

    mode_screen(renderer);
    render_scene_text(game_scene, renderer);
}

t_game_scene *new_game_scene(t_renderer *renderer) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;
    game_scene->sky = loadTexture("resource/images/sky.png", renderer->renderer);
    game_scene->blocks = malloc(sizeof(t_block) * 15);
    game_scene->score = 0;
    game_scene->font = TTF_OpenFont("resource/text/PixelMiddle.ttf", 48);
    SDL_Texture *coin_texture = loadTexture("resource/images/coin.png", renderer->renderer);
    SDL_Texture *player_texture = loadTexture("resource/images/ghost-Sheet.png", renderer->renderer);
    SDL_Texture *ground_texture = loadTexture("resource/images/ground.png", renderer->renderer);
    
    game_scene->player = new_player(player_texture);

    for (int i = 0; i < 10; i++) {
        game_scene->blocks[i].texture = ground_texture;
        game_scene->blocks[i].rect.x = i * 64.0f;
        game_scene->blocks[i].rect.y = 656.0f;
        game_scene->blocks[i].rect.w = 64.0f;
        game_scene->blocks[i].rect.h = 64.0f;
    }

    for (int i = 10; i < 15; i++) {
        game_scene->blocks[i].texture = ground_texture;
        game_scene->blocks[i].rect.x = (i - 5) * 64.0f;
        game_scene->blocks[i].rect.y = 292.0f;
        game_scene->blocks[i].rect.w = 64.0f;
        game_scene->blocks[i].rect.h = 64.0f;
    }
    
    for (int i = 0; i < 19; i++) {
        game_scene->coins[i] = malloc(sizeof(t_block));
        game_scene->coins[i]->texture = coin_texture;
        game_scene->coins[i]->rect.x = i * 64.0f;
        game_scene->coins[i]->rect.y = 600.0f;
        game_scene->coins[i]->rect.w = 64.0f;
        game_scene->coins[i]->rect.h = 64.0f;
    }
    return game_scene;
}
