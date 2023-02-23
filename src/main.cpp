#include "main.h"

int main(int argc, char *argv[]) {
    App& app = App::instance();

    if (!app.initSDL()) {
        exit(1);
    }

    app.changeState(GAME_MAINMENU);
    
    //Player *player = app.getStage()->getPlayer();

    while (app.getState() != GAME_EXIT) {

        app.handleState();

        // long time = SDL_GetTicks();

        /*
        long timePassed = SDL_GetTicks() - time;
        if (timePassed < 1000 / 60.0) {
            SDL_Delay(1000 / 60.0 - timePassed);
        }
        */
    }

    return 0;
}