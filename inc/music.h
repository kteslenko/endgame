#pragma once

#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    Mix_Music* m_arr;
} t_mus;

bool init_music(t_mus* m);
void del_music(t_mus* m );
Mix_Music* load_music(const char* str);
void play_music(t_mus* m);
