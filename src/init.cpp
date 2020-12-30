#include "init.h"

void initSDL() {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (!app.setWindow(SDL_CreateWindow("SPACE CRIMINALS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags))) {
        printf("Failed to open window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (!app.setRenderer(SDL_CreateRenderer(app.getWindow(), -1, rendererFlags))) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void cleanup()
{
	SDL_DestroyRenderer(app.getRenderer());
	
	SDL_DestroyWindow(app.getWindow());
	
	SDL_Quit();
}