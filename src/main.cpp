#include "main.h"

int main(int argc, char *argv[]) {
    App& app = App::instance();

    if (!app.initSDL()) {
        exit(1);
    }

    app.setState(GAME_RUNNING);

    app.createStage();
    app.getStage()->initStage();

    Player *player = app.getStage()->getPlayer();

    while (app.getState() != GAME_EXIT) {

        // long time = SDL_GetTicks();

        app.getDrawingManager()->clearScene();
        
        app.doInput();
        
        app.getStage()->updateAndDraw();

        app.getDrawingManager()->renderScene();

        /*
        long timePassed = SDL_GetTicks() - time;
        if (timePassed < 1000 / 60.0) {
            SDL_Delay(1000 / 60.0 - timePassed);
        }
        */
    }

    return 0;
}