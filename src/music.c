#include "music.h"

bool init_music(t_mus *mus) {
    *mus = (t_mus){NULL};
    mus->m_arr = (Mix_Music *)load_music("resource/music/spirit-blossom-15285.wav");
    return true;
}

Mix_Music *load_music(const char *str) {
    Mix_Music *gMusic = Mix_LoadMUS(str);
    if (gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return NULL;
    }
    return gMusic;
}

void play_music(t_mus *m) {
    if (m == NULL) {
        printf("Failed to play beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(m->m_arr, -1);
    }
}

void del_music(t_mus *mus) {
    Mix_FreeMusic((mus->m_arr));
    (mus->m_arr) = NULL;
    Mix_Quit();
}
