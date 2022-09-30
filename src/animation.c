#include "animation.h"

t_animation *new_animation(SDL_Texture *texture, int fps, int count) {
    t_animation *animation = malloc(sizeof(t_animation));

    animation->time = 0;
    animation->fps = fps;
    animation->count = 0;
    animation->current = 0;
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
    render_texturef(renderer, animation->texture, frame, rect);
}

t_animation *coin_animation(t_renderer *renderer) {
    t_animation *animation = new_animation(renderer->textures[COIN], 12, 9);

    for (int i = 0; i < 9; i++) {
        push_frame(animation, (SDL_Rect){i * 20, 0, 20, 20});
    }

    return animation;
}
