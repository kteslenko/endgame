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
    update_camera(game_scene);
}

static void render_text(t_game_scene *game_scene, SDL_Renderer *renderer) {
    TTF_Init();
    TTF_Font* PixelMiddle = TTF_OpenFont("resource/text/PixelMiddle.ttf", 24);
    char count_score[30] = "SCORE: ";
    SDL_itoa(game_scene->score, count_score + 7, 10);

    SDL_Color White = {255, 255, 255, 255};
    SDL_Surface* surface_text = TTF_RenderText_Solid(PixelMiddle, count_score, White);
    
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface_text);

    SDL_Rect text_rect; 
    text_rect.x = 0;  
    text_rect.y = 0; 
    text_rect.w = 80; 
    text_rect.h = 80;
    SDL_RenderCopy(renderer, text, NULL, &text_rect);

    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(text);

}

static void render(t_scene *scene, SDL_Renderer *renderer) {
    t_game_scene *game_scene = (t_game_scene*)scene;
    
    for (int i = 0; i < 15; i++) {
        SDL_Rect dst = frect_to_rect(&game_scene->blocks[i].rect);
        dst.x -= game_scene->camera.x;
        dst.y -= game_scene->camera.y;
        SDL_RenderCopy(renderer, game_scene->blocks[i].texture, NULL, &dst);
    }
    for (int i = 0; i < 19; i++) {
        if (game_scene->coins[i] != NULL) {
            SDL_Rect dst = frect_to_rect(&game_scene->coins[i]->rect);
            dst.x -= game_scene->camera.x;
            dst.y -= game_scene->camera.y;
            SDL_RenderCopy(renderer, game_scene->coins[i]->texture, NULL, &dst);
        }
    }
    render_player(game_scene->player, renderer, &game_scene->camera);
    render_text(game_scene, renderer);
}

t_game_scene *new_game_scene(SDL_Renderer *renderer) {
    t_game_scene *game_scene = malloc(sizeof(t_game_scene));

    game_scene->scene.handle_event = handle_event;
    game_scene->scene.update = update;
    game_scene->scene.render = render;
    game_scene->ground = loadTexture("resource/images/ground.png", renderer);
    game_scene->blocks = malloc(sizeof(t_block) * 15);
    game_scene->score = 0;
    SDL_Texture *coin_texture = loadTexture("resource/images/coin.png", renderer);
    SDL_Texture *player_texture = loadTexture("resource/images/ghost-Sheet.png", renderer);

    game_scene->player = new_player(player_texture);
    SDL_RenderGetViewport(renderer, &game_scene->camera);
    update_camera(game_scene);
    
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
