#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL could not initialize: Error %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("SDL2",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280, 720, 0);

	if (window == NULL) {
		printf("Unable to create window. Error %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(2000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
