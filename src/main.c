#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

void createWindow(SDL_Window **window, SDL_Renderer **renderer) { //function that creates window
	*window = SDL_CreateWindow("SDL2",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	1280, 720, 0); //size of the window

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

}

SDL_Texture *loadTexture(char *texturePath, SDL_Renderer *renderer) { //function for creating texture
	SDL_Texture *texture = NULL;
	texture = IMG_LoadTexture(renderer, texturePath);

	if (texture == NULL) {
		printf("Loading texture has fialed: Error: %s\n", SDL_GetError());
	}
	return texture;
}

void render_func(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, float w, float h) { //fun that render textures blocks
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

void build_platform(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, int len) { //fun that build a platform or ground witn custom len and coord
	for (int i = 1; i <= len; i++) {
			render_func(renderer, texture, x, y, 64, 64);
			x += 64;
	}
}


int main() {

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) { //init the vindow
		printf("SDL could not initialize: Error %s\n", SDL_GetError());
		return 1;
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		printf("IMG_Init has failed. Error: %s\n", SDL_GetError());
	}
	
	createWindow(&window, &renderer);

	if (window == NULL) { //check if window exists 
		printf("Unable to create window. Error %s\n", SDL_GetError());
		return 1;
	}

	
	SDL_Event e;
	bool quit = false;
	
	SDL_Texture *groundTex = NULL;
	groundTex = loadTexture("src/ground.png", renderer);

	while (quit == false) {
		while (SDL_PollEvent (&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		SDL_RenderClear(renderer);
		
		build_platform(renderer, groundTex, 0, 60, 5);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(groundTex); //free memory of texture
	SDL_DestroyRenderer(renderer); //free memory of renderer

	SDL_DestroyWindow(window); //shut down the window
	SDL_Quit(); //free memory

	return 0;
}

