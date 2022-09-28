#ifndef MUSIC_H
#define MUSIC_H
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct{
	Mix_Music* m_arr;
}t_mus;
bool init_music(t_mus* m);
void del_music(t_mus* m );
Mix_Music* load_music(const char* str);
void play_music(t_mus* m);
#endif
