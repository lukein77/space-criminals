#include "App.h"

/* App constructor */
App::App() {}

/* App destructor */
App::~App() {
    SDL_Quit();
}

/* App::initSDL()
 * 
 * Initializes SDL and the managers for the SDL libraries (SDL_image, SDL_mixer, etc.)
 *
 * Returns:
 * true if initialization was successful, false if there were errors
 */
bool App::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    drawingManager = new Draw();
    if (!drawingManager->initialize()) {
        return false;
    }

    audioManager = new Audio();
    if (!audioManager->initialize()) {
        return false;
    }

    return true;
}

/* App::doInput() 
 *
 * Processes key input
 */
void App::doInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state = GAME_EXIT;
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

/* App::doKeyDown
 * 
 * Processes KEY_DOWN events, mainly player movement
 * 
 * Parameters:
 * SDL_KeyboardEvent *event: the key that is being held down
 */
void App::doKeyDown(SDL_KeyboardEvent *event) {
    Player *player = getStage()->getPlayer();
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

/* App::doKeyUp
 * 
 * Processes KEY_UP events
 * 
 * Parameters:
 * SDL_KeyboardEvent *event: the key that is being released
 * 
 */
void App::doKeyUp(SDL_KeyboardEvent *event) {
    Player *player = App::instance().getStage()->getPlayer();

	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		switch (event->keysym.scancode) { 
            case SDL_SCANCODE_ESCAPE:
                state = GAME_EXIT;
                break;
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

/* App::setState
 * 
 * Changes the app's current state.
 * 
 * Parameters:
 * int state: new state
 */
void App::setState(int state) {
    this->state = state;
}

/* App::createStage()
 * 
 * Creates and initializes the Stage.
 */
void App::createStage() {
    stage = new Stage();
    stage->initStage();
}