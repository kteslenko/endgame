#include "player.h"

void handle_player_event(t_player *player, SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_UP && e->key.repeat == 0) {
            if (player->jumps < player->max_jumps) {
                player->velocity.y = -750;
                player->jumps++;
                Mix_PlayChannel(-1, player->jumpEffect[rand() % 3], 0);
            }
        }
    }
}

static void update_state(t_player *player) {
    bool flipped = player->animations[player->state]->flipped;

    if (player->jumps > 0) {
        player->state = JUMP_STATE;
    }
    else if (player->velocity.x != 0) {
        player->state = WALK_STATE;
    }
    else {
        player->state = IDLE_STATE;
    }

    player->animations[player->state]->flipped = flipped;
    if (player->velocity.x < 0) {
        player->animations[player->state]->flipped = true;
    }
    else if (player->velocity.x > 0) {
        player->animations[player->state]->flipped = false;
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

    update_state(player);
    update_animation(player->animations[player->state], dt);
}

static t_animation **player_animations(t_renderer *renderer) {
    t_animation **animations = malloc(sizeof(t_animation*) * 3);

    animations[IDLE_STATE] = idle_animation(renderer);
    animations[JUMP_STATE] = jump_animation(renderer);
    animations[WALK_STATE] = walk_animation(renderer);

    return animations;
}

t_player *new_player(t_renderer *renderer) {
    t_player *player = malloc(sizeof(t_player));
    player->jumpEffect = malloc (sizeof(Mix_Chunk*) * 3);
    player->jumpEffect[0] = Mix_LoadWAV("resource/sounds/jump1.wav");
    player->jumpEffect[1] = Mix_LoadWAV("resource/sounds/jump2.wav");
    player->jumpEffect[2] = Mix_LoadWAV("resource/sounds/jump3.wav");
    player->jumps = 0;
    player->max_jumps = 2;
    player->prev = (SDL_FRect){0, 0, 32, 64};
    player->rect = (SDL_FRect){0, 0, 32, 64};
    player->velocity = (SDL_FPoint){0, 0};
    player->state = IDLE_STATE;
    player->animations = player_animations(renderer);
    
    return player;
}

void render_player(t_player *player, t_renderer *renderer) {
    t_animation *animation = player->animations[player->state];
    SDL_Rect frame = animation->frames[animation->current];
    SDL_FRect rect;

    frame.w *= player->rect.h / frame.h;
    frame.h = player->rect.h;
    rect = rect_to_frect(&frame);
    rect.x = player->rect.x - (rect.w - player->rect.w) / 2;
    rect.y = player->rect.y;
    
    render_animation(animation, renderer, &rect);
}

void handle_intersect(t_player *player, SDL_FRect *rect) {
    SDL_Rect iprev = frect_to_rect(&player->prev);
    SDL_Rect iplayer = frect_to_rect(&player->rect);
    SDL_Rect irect = frect_to_rect(rect);

    SDL_Point prev[] = {
        top_left(&iprev),
        top_right(&iprev),
        bottom_left(&iprev),
        bottom_right(&iprev),
    };
    SDL_Point corners[] = {
        top_left(&iplayer),
        top_right(&iplayer),
        bottom_left(&iplayer),
        bottom_right(&iplayer),
    };
    
    for (int i = 0; i < 4; i++) {
        SDL_Point inter = {prev[i].x, prev[i].y};
        if (!SDL_IntersectRectAndLine(&irect, &inter.x, &inter.y, &corners[i].x, &corners[i].y)) {
            continue;
        }
        if (inter.x == rect->x && (i == 1 || i == 3)) {
            player->rect.x = rect->x - player->rect.w;
            player->velocity.x = 0;
        }
        if (inter.x == rect->x + rect->w - 1 && (i == 0 || i == 2)) {
            player->rect.x = rect->x + rect->w;
            player->velocity.x = 0;
        }
        if (inter.y == rect->y && (i == 2 || i == 3)) {
            player->rect.y = rect->y - player->rect.h;
            player->jumps = 0;
            player->velocity.y = 0;
        }
        if (inter.y == rect->y + rect->h - 1 && (i == 0 || i == 1)) {
            player->rect.y = rect->y + rect->h;
            player->velocity.y = 0;
        }
    }
}
