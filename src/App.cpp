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

/* App::handleInput() 
 *
 * Processes key input
 */
void App::handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                changeState(GAME_EXIT);
                break;
            case SDL_KEYDOWN:
                handleKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                handleKeyUp(&event.key);
                break;
            default:
                break;
        }
    }
}

/* App::handleKeyDown
 * 
 * Processes KEY_DOWN events, mainly player movement
 * 
 * Parameters:
 * SDL_KeyboardEvent *event: the key that is being held down
 */
void App::handleKeyDown(SDL_KeyboardEvent *event) {
    if (state == GAME_RUNNING) {
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
}

/* App::handleKeyUp
 * 
 * Processes KEY_UP events
 * 
 * Parameters:
 * SDL_KeyboardEvent *event: the key that is being released
 * 
 */
void App::handleKeyUp(SDL_KeyboardEvent *event) {

	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		switch (event->keysym.scancode) { 
            case SDL_SCANCODE_ESCAPE:
                changeState(GAME_EXIT);
                break;
            case SDL_SCANCODE_RETURN:
                if (state == GAME_MAINMENU) {
                    menu->choose();
                }
                break;
            case SDL_SCANCODE_UP:
                if (state == GAME_RUNNING) {
                    Player *player = App::instance().getStage()->getPlayer();
                    player->setMovement(DIRECTION_UP, false);
                } else if (state == GAME_MAINMENU) {
                    menu->selectPrevious();
                    printf("%d\n", menu->getCurrentOption());
                }
                break;
            case SDL_SCANCODE_DOWN:
                if (state == GAME_RUNNING) {
                    Player *player = App::instance().getStage()->getPlayer();
                    player->setMovement(DIRECTION_DOWN, false);
                } else if (state == GAME_MAINMENU) {
                    menu->selectNext();
                    printf("%d\n", menu->getCurrentOption());
                }
                break;
            case SDL_SCANCODE_LEFT:
                if (state == GAME_RUNNING) {
                    Player *player = App::instance().getStage()->getPlayer();
                    player->setMovement(DIRECTION_LEFT, false);
                }
                break;
            case SDL_SCANCODE_RIGHT:
                if (state == GAME_RUNNING) {
                    Player *player = App::instance().getStage()->getPlayer();
                    player->setMovement(DIRECTION_RIGHT, false);
                }
                break;
            case SDL_SCANCODE_LCTRL:
            case SDL_SCANCODE_RCTRL:
                if (state == GAME_RUNNING) {
                    Player *player = App::instance().getStage()->getPlayer();
                    player->toggleFire();
                }
                break;
            default:
                break;
        }
	}
}

/* App::changeState
 * 
 * Sets up a new state.
 * 
 * Parameters:
 * int state: new state
 */
void App::changeState(int newState) {
    switch (newState) {
        case GAME_MAINMENU:
            menu = new MainMenu();
            getAudioManager()->loadMusic("02 - Space Delinquents.mp3");
            getAudioManager()->playMusic();
            break;
        case GAME_RUNNING:
            createStage();
            getStage()->initStage();
            getAudioManager()->loadMusic("01 - Criminals from Space.mp3");
            getAudioManager()->playMusic();
            break;
        default:
            break;
    }
    this->state = newState;
}

/* App::createStage()
 * 
 * Creates and initializes the Stage.
 */
void App::createStage() {
    stage = new Stage();
    stage->initStage();
}

/* App::handleState()
 *
 * Handles the app's current state. 
*/
void App::handleState() {
    switch(this->state) {
        case GAME_RUNNING:
            getDrawingManager()->clearScene();
            
            handleInput();
            
            getStage()->updateAndDraw();

            getDrawingManager()->renderUI();
            getDrawingManager()->renderScene();
            break;
        case GAME_MAINMENU:
            getDrawingManager()->clearScene();

            getDrawingManager()->renderMenu(menu);
            handleInput();

            getDrawingManager()->renderScene();
            break;
            
        case GAME_GAMEOVER:
            getDrawingManager()->clearScene();
            
            handleInput();
            
            getStage()->updateAndDraw();
            getStage()->drawGameOver();

            getDrawingManager()->renderUI();
            getDrawingManager()->renderScene();
            break;
        default:
            break;
    }
}