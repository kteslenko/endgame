#include "scenes.h"

static void push_switch_event(t_scene *scene, enum e_scene type) {
    SDL_Event event;

    SDL_zero(event);
    event.type = scene->event_number + ACTIVE_SCENE_CHANGED;
    event.user.code = type;
    SDL_PushEvent(&event);
}

static void handle_event(t_scene *scene, SDL_Event *e) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    handle_player_event(game_scene->player, e);
}

static void update(t_scene *scene, float dt) {
    t_game_scene *game_scene = (t_game_scene*)scene;

    update_player(game_scene->player, dt);
    for (int i = 0; i < game_scene->map->size; i++) {
        if (!game_scene->map->blocks[i].collider) {
            continue;
        }
    	SDL_Rect player = frect_to_rect(&game_scene->player->rect);
    	SDL_Rect block = frect_to_rect(&game_scene->map->blocks[i].rect);
        if (SDL_HasIntersection(&player, &block)) {
            handle_intersect(game_scene->player, &game_scene->map->blocks[i].rect);
        }
    }
    for (int i = 0; i < game_scene->map->coins_count; i++) {
        if (!game_scene->map->coins[i].collected) {
            SDL_Rect player = frect_to_rect(&game_scene->player->rect);
            SDL_Rect coin = frect_to_rect(&game_scene->map->coins[i].rect);
            if (SDL_HasIntersection(&player, &coin)) {
                game_scene->score++;
                Mix_PlayChannel(-1, game_scene->coinEffect[rand() % 3], 0);
                if (game_scene->score > 30) {
                    game_scene->player->max_jumps = 2;
                }
                game_scene->map->coins[i].collected = true;
            }
        }
    }
    update_animation(game_scene->coin_animation, dt);

    if (count_coins(game_scene->map) == 0) {
        push_switch_event(scene, WIN_MENU_SCENE);
    }
}

static void render_sky(t_renderer *renderer) {
    SDL_Rect dst = {0, 0, 0, 0};

    SDL_QueryTexture(renderer->textures[SKY], NULL, NULL, &dst.w, &dst.h);
    dst.w *= (float)renderer->camera.h / dst.h;
    dst.h = renderer->camera.h;

    mode_screen(renderer);
    while (dst.x < renderer->camera.w) {
        render_texture(renderer, renderer->textures[SKY], NULL, &dst);
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
    if (renderer->camera.y > 2000) {
        renderer->camera.y = 2000;
    }
}

static void render(t_scene *scene, t_renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    SDL_Rect player = frect_to_rect(&game_scene->player->rect);

    move_camera(game_scene, renderer);
    if (!SDL_HasIntersection(&player, &renderer->camera)) {
        push_switch_event(scene, LOSING_MENU_SCENE);
    }

    render_sky(renderer);

    mode_camera(renderer);
    for (int i = 0; i < game_scene->map->size; i++) {
        render_texturef(renderer, game_scene->map->blocks[i].texture, NULL, &game_scene->map->blocks[i].rect);
    }
    for (int i = 0; i < game_scene->map->coins_count; i++) {
        if (!game_scene->map->coins[i].collected) {
            render_animation(game_scene->coin_animation, renderer, &game_scene->map->coins[i].rect);
        }
    }
    render_player(game_scene->player, renderer);

    mode_screen(renderer);
    render_scene_text(game_scene, renderer);
}

static void clean_game(struct s_scene *scene) {
    t_game_scene *game_scene = (t_game_scene*)scene;

    clean_map(game_scene->map);
    clean_player(game_scene->player);
    clean_animation(game_scene->coin_animation);
    TTF_CloseFont(game_scene->font);
    for (int i = 0; i < 3; i++) {
        Mix_FreeChunk(game_scene->coinEffect[i]);
    }
    free(game_scene);
}

void reset_level(t_game_scene *game_scene) {
    for (int i = 0; i < game_scene->map->coins_count; i++) {
        game_scene->map->coins[i].collected = false;
    }
    reset_player(game_scene->player);
    game_scene->score = 0;
}

t_game_scene *new_game_scene(t_renderer *renderer, uint32_t event_number) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.event_number = event_number;
    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;
    game_scene->scene.clean = clean_game;
    game_scene->map = build_level(renderer->textures);
    game_scene->score = 0;
    game_scene->font = TTF_OpenFont("resource/text/PixelMiddle.ttf", 48);
    game_scene->coin_animation = coin_animation(renderer);
    game_scene->player = new_player(renderer);

    game_scene->coinEffect = malloc (sizeof(Mix_Chunk*) * 3);
    game_scene->coinEffect[0] = Mix_LoadWAV("resource/sounds/coin1.wav");
    game_scene->coinEffect[1] = Mix_LoadWAV("resource/sounds/coin2.wav");
    game_scene->coinEffect[2] = Mix_LoadWAV("resource/sounds/coin3.wav");

    return game_scene;
}
