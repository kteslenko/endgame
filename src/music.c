#include "music.h"
bool init_music(t_mus* mus){
//Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
			return false;
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                }
	mus = malloc(sizeof(t_mus*));
	mus->m_arr = (Mix_Music*)load_music("resources/music/spirit-blossom-15285.wav");
	return true;
}
Mix_Music* load_music(const char* str){
		 //Load music
	Mix_Music*    gMusic = Mix_LoadMUS(str);
    if( gMusic == NULL )
    {
	    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            return NULL;
    }

        printf( "Not failed to load beat music! SDL_mixer Error: \n" );
    return gMusic;
}
void play_music(t_mus* m){
	if(m==NULL){

	    printf( "Failed to play beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            return;
	}
	if( Mix_PlayingMusic() == 0 )
                            {
                             //Play the music
                                Mix_PlayMusic(m->m_arr, -1 );
			    }
}

void del_music(t_mus* mus){

		Mix_FreeMusic( (mus->m_arr) );
    		(mus->m_arr) = NULL;
    Mix_Quit();
}
