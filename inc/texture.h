#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *loadTexture(char *texturePath, SDL_Renderer *renderer);  //function for creating texture
void render_func(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, float w, float h); //fun that render textures blocks
void build_platform(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, int len);  //fun that build a platform or ground witn custom len and coord
