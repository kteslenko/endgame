#pragma once

#include "renderer.h"

typedef struct {
    bool collider;
    SDL_FRect rect;
    SDL_Texture *texture;
} t_block;

typedef struct {
    t_block *blocks;
    int size;
} t_map;

t_map *new_map(int max_blocks);
void push_block(t_map *map, t_block block);
void build_platform(t_map *map, SDL_Texture *texture, float x, float y, int len);
void build_block(t_map *map, SDL_Texture *texture, float x, float y, float w, float h);
t_map *build_level(SDL_Texture **textures);
