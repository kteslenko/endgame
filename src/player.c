#include "player.h"

void handle_player_event(t_player *player, SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_UP && e->key.repeat == 0) {
            if (player->jumps < player->max_jumps) {
                player->velocity.y = -750;
                player->jumps++;
            }
        }
    }
}

void update_player(t_player *player, float dt) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    player->velocity.x = 0;
    if (state[SDL_SCANCODE_LEFT]) {
        player->velocity.x -= 500;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        player->velocity.x += 500;
    }

    player->prev = player->rect;
    player->rect.x += player->velocity.x * dt;
    player->rect.y += player->velocity.y * dt;
    player->velocity.y += SDL_STANDARD_GRAVITY * 150 * dt;
}

t_player *new_player(SDL_Texture *texture) {
    t_player *player = malloc(sizeof(t_player));

    player->jumps = 0;
    player->max_jumps = 2;
    player->prev = (SDL_FRect){0, 64, 64, 64};
    player->rect = (SDL_FRect){0, 64, 64, 64};
    player->velocity = (SDL_FPoint){0, 0};
    player->texture = texture;
    
    return player;
}

void render_player(t_player *player, SDL_Renderer *renderer) {
    SDL_Rect src = {0, 0, 32, 32};
    SDL_Rect dst = frect_to_rect(&player->rect);
    SDL_RenderCopy(renderer, player->texture, &src, &dst);
}

void handle_intersect(t_player *player, SDL_FRect *rect) {
    SDL_FPoint prev[] = {
        top_left(&player->prev),
        top_right(&player->prev),
        bottom_left(&player->prev),
        bottom_right(&player->prev),
    };
    SDL_FPoint corners[] = {
        top_left(&player->rect),
        top_right(&player->rect),
        bottom_left(&player->rect),
        bottom_right(&player->rect),
    };
    
    for (int i = 0; i < 4; i++) {
        SDL_FPoint inter = {prev[i].x, prev[i].y};
        if (!SDL_IntersectFRectAndLine(rect, &inter.x, &inter.y, &corners[i].x, &corners[i].y)) {
            continue;
        }
        if ((approx_eq(inter.x, rect->x)) && (i == 1 || i == 3)) {
            player->rect.x = rect->x - player->rect.w;
            player->velocity.x = 0;
        }
        if ((approx_eq(inter.x, rect->x + rect->w)) && (i == 0 || i == 2)) {
            player->rect.x = rect->x + rect->w;
            player->velocity.x = 0;
        }
        if (approx_eq(inter.y, rect->y) && (i == 2 || i == 3)) {
            player->rect.y = rect->y - player->rect.h;
            player->jumps = 0;
            player->velocity.y = 0;
        }
        if (approx_eq(inter.y, rect->y + rect->h) && (i == 0 || i == 1)) {
            player->rect.y = rect->y + rect->h;
            player->velocity.y = 0;
        }
    }
}
