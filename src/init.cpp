#include "init.h"

void initSDL() {

    App& app = App::instance();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (!app.setWindow(SDL_CreateWindow("SPACE CRIMINALS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN))) {
        printf("Failed to open window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (!app.setRenderer(SDL_CreateRenderer(app.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void cleanup()
{
    App& app = App::instance();
    
	SDL_DestroyRenderer(app.getRenderer());
	
	SDL_DestroyWindow(app.getWindow());
	
	SDL_Quit();
}