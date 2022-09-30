#include "animation.h"

t_animation *new_animation(SDL_Texture *texture, int fps, int count) {
    t_animation *animation = malloc(sizeof(t_animation));

    animation->time = 0;
    animation->fps = fps;
    animation->count = 0;
    animation->current = 0;
    animation->flipped = false;
    animation->frames = malloc(sizeof(SDL_Rect) * count);
    animation->texture = texture;

    return animation;
}

void push_frame(t_animation *animation, SDL_Rect frame) {
    animation->frames[animation->count] = frame;
    animation->count++;
}

void update_animation(t_animation *animation, float dt) {
    float frametime = 1.0f / animation->fps;
    int frames;
    
    animation->time += dt;
    frames = animation->time / frametime;
    animation->time -= frametime * frames;
    animation->current += frames;
    animation->current %= animation->count;
}

void render_animation(t_animation *animation, t_renderer *renderer, SDL_FRect *rect) {
    SDL_Rect *frame = &animation->frames[animation->current];
    render_texturef_ex(renderer, animation->texture, frame, rect, animation->flipped);
}

t_animation *coin_animation(t_renderer *renderer) {
    t_animation *animation = new_animation(renderer->textures[COIN], 12, 9);

    for (int i = 0; i < 9; i++) {
        push_frame(animation, (SDL_Rect){i * 20, 0, 20, 20});
    }

    return animation;
}

t_animation *idle_animation(t_renderer *renderer) {
    t_animation *animation = new_animation(renderer->textures[IDLE], 12, 10);

    for (int i = 0; i < 10; i++) {
        push_frame(animation, (SDL_Rect){i * 120 + 45, 43, 19, 38});
    }

    return animation;
}

t_animation *jump_animation(t_renderer *renderer) {
    t_animation *animation = new_animation(renderer->textures[JUMP], 12, 3);

    for (int i = 0; i < 3; i++) {
        push_frame(animation, (SDL_Rect){i * 120 + 45, 43, 23, 38});
    }

    return animation;
}

t_animation *walk_animation(t_renderer *renderer) {
    t_animation *animation = new_animation(renderer->textures[WALK], 12, 10);

    push_frame(animation, (SDL_Rect){42, 43, 28, 38});
    push_frame(animation, (SDL_Rect){165, 43, 28, 38});
    push_frame(animation, (SDL_Rect){288, 43, 28, 38});
    push_frame(animation, (SDL_Rect){407, 43, 28, 38});
    push_frame(animation, (SDL_Rect){523, 40, 28, 38});
    push_frame(animation, (SDL_Rect){640, 43, 28, 38});
    push_frame(animation, (SDL_Rect){763, 43, 28, 38});
    push_frame(animation, (SDL_Rect){886, 43, 28, 38});
    push_frame(animation, (SDL_Rect){1005, 43, 28, 38});
    push_frame(animation, (SDL_Rect){1122, 40, 28, 38});

    return animation;
}
