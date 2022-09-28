#include "player.h"

void handle_player_event(t_player *player, SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_UP && e->key.repeat == 0) {
            if (player->jumps < player->max_jumps) {
                player->velocity_y = -1000;
                player->jumps++;
            }
        }
        if (e->key.keysym.sym == SDLK_LEFT) {
            player->velocity_x = -500;
        }
        if (e->key.keysym.sym == SDLK_RIGHT) {
            player->velocity_x = 500;
        }
    }
    if (e->type == SDL_KEYUP) {
        if (e->key.keysym.sym == SDLK_LEFT) {
            player->velocity_x = 0;
        }
        if (e->key.keysym.sym == SDLK_RIGHT) {
            player->velocity_x = 0;
        }
    }
}

void update_player(t_player *player, float dt) {
    player->x += player->velocity_x * dt;
    player->y += player->velocity_y * dt;
    player->rect.x = (int)player->x;
    player->rect.y = (int)player->y;
    player->velocity_y += SDL_STANDARD_GRAVITY;
}

t_player *new_player(SDL_Texture *texture) {
    t_player *player = malloc(sizeof(t_player));

    player->jumps = 0;
    player->max_jumps = 2;

    player->rect.w = 64;
    player->rect.h = 64;
    player->texture = texture;
    player->x = 0;
    player->y = player->rect.h;
    player->velocity_x = 0;
    player->velocity_y = 0;
    
    return player;
}

void render_player(t_player *player, SDL_Renderer *renderer) {
    SDL_Rect src;

    src.w = 32;
    src.h = 32;
    src.x = 0;
    src.y = 0;
    
    SDL_RenderCopy(renderer, player->texture, &src, &player->rect);
}

void handle_intersect(t_player *player, SDL_Rect *rect) {
    int player_bottom = player->rect.y + player->rect.h - 1;

    if (player_bottom > rect->y) {
        player->velocity_y = 0;
        player->y = rect->y - player->rect.h;
        player->jumps = 0;
    }
}


