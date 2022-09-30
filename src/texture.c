#include "texture.h"

SDL_Texture *loadTexture(char *texturePath, SDL_Renderer *renderer) {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, texturePath);

    if (texture == NULL) {
        printf("Loading texture has fialed: Error: %s\n", SDL_GetError());
    }
    return texture;
}

void render_func(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, float w, float h) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 64;
    src.h = 64;

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(renderer, texture, &src, &dst);
}
