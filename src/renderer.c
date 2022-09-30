#include "renderer.h"

void load_textures(t_renderer *renderer) {
    renderer->textures = malloc(sizeof(SDL_Texture*) * 11);

    renderer->textures[GROUND] = loadTexture("resource/images/ground.png", renderer->renderer);
    renderer->textures[DIRT] = loadTexture("resource/images/dirt.png", renderer->renderer);
    renderer->textures[FIRE] = loadTexture("resource/images/fire.png", renderer->renderer);
    renderer->textures[BUSH] = loadTexture("resource/images/bush1.png", renderer->renderer);
    renderer->textures[TREE1] = loadTexture("resource/images/tree1.png", renderer->renderer);
    renderer->textures[TREE2] = loadTexture("resource/images/tree2.png", renderer->renderer);
    renderer->textures[ROCK] = loadTexture("resource/images/rock1.png", renderer->renderer);
    renderer->textures[BENCH] = loadTexture("resource/images/bench.png", renderer->renderer);
    renderer->textures[LOGS] = loadTexture("resource/images/logs.png", renderer->renderer);
    renderer->textures[POOL] = loadTexture("resource/images/pool.png", renderer->renderer);
    renderer->textures[COIN] = loadTexture("resource/images/coin2_20x20.png", renderer->renderer);
}

void render_clear(t_renderer *renderer) {
    SDL_RenderClear(renderer->renderer);
}

void render_present(t_renderer *renderer) {
    SDL_RenderPresent(renderer->renderer);
}

void mode_screen(t_renderer *renderer) {
    renderer->active = &renderer->screen;
}

void mode_camera(t_renderer *renderer) {
    renderer->active = &renderer->camera;
}

void render_texturef(t_renderer *renderer, SDL_Texture *texture, SDL_Rect *src, SDL_FRect *frect) {
    SDL_Rect rect = frect_to_rect(frect);
    render_texture(renderer, texture, src, &rect);
}

void render_texture(t_renderer *renderer, SDL_Texture *texture, SDL_Rect *src, SDL_Rect *rect) {
    SDL_Rect dst = *rect;
    dst.x -= renderer->active->x;
    dst.y -= renderer->active->y;
    SDL_RenderCopy(renderer->renderer, texture, src, &dst);
}

void render_text(t_renderer *renderer, const char *text, TTF_Font *font, SDL_Point pos, SDL_Color color) {
    SDL_Surface* surface_text = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->renderer, surface_text);
    SDL_Rect text_rect = {pos.x, pos.y, 0, 0};

    SDL_QueryTexture(texture, NULL, NULL, &text_rect.w, &text_rect.h);
    render_texture(renderer, texture, NULL, &text_rect);
    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture);
}
