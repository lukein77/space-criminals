#include "input.h"

void doInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
            default:
                break;
        }
    }
}

void doKeyDown(SDL_KeyboardEvent *event) {
    Player *player = App::instance().getStage()->getPlayer();
	if (event->repeat == 0)
	{
		switch (event->keysym.scancode) { 
            case SDL_SCANCODE_UP:
                player->setMovement(DIRECTION_UP, true);
                player->setMovement(DIRECTION_DOWN, false);
                break;
            case SDL_SCANCODE_DOWN:
                player->setMovement(DIRECTION_UP, false);
                player->setMovement(DIRECTION_DOWN, true);
                break;
            case SDL_SCANCODE_LEFT:
                player->setMovement(DIRECTION_LEFT, true);
                player->setMovement(DIRECTION_RIGHT, false);
                break;
            case SDL_SCANCODE_RIGHT:
                player->setMovement(DIRECTION_LEFT, false);
                player->setMovement(DIRECTION_RIGHT, true);
                break;
            default:
                break;
        }

	}
}

void doKeyUp(SDL_KeyboardEvent *event) {
    Player *player = App::instance().getStage()->getPlayer();

	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		switch (event->keysym.scancode) { 
            case SDL_SCANCODE_UP:
                player->setMovement(DIRECTION_UP, false);
                break;
            case SDL_SCANCODE_DOWN:
                player->setMovement(DIRECTION_DOWN, false);
                break;
            case SDL_SCANCODE_LEFT:
                player->setMovement(DIRECTION_LEFT, false);
                break;
            case SDL_SCANCODE_RIGHT:
                player->setMovement(DIRECTION_RIGHT, false);
                break;
            case SDL_SCANCODE_LCTRL:
            case SDL_SCANCODE_RCTRL:
                player->toggleFire();
                break;
            default:
                break;
        }
	}
}
