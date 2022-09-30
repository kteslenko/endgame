#pragma once

#include "renderer.h"

typedef struct {
    bool collider;
    SDL_FRect rect;
    SDL_Texture *texture;
} t_block;

typedef struct {
    bool collected;
    SDL_FRect rect;
} t_coin;

typedef struct {
    t_block *blocks;
    int size;
    t_coin *coins;
    int coins_count;
} t_map;

t_map *new_map(int max_blocks, int coins_count);
int count_coins(t_map *map);
void push_block(t_map *map, t_block block);
void push_coin(t_map *map, SDL_Rect coin);
void build_platform(t_map *map, SDL_Texture *texture, float x, float y, int len);
void build_block(t_map *map, SDL_Texture *texture, float x, float y, float w, float h);
t_map *build_level(SDL_Texture **textures);
