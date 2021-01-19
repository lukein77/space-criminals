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
        app.getDrawingManager()->prepareScene();
        
        app.doInput();
        
        app.getStage()->updateEntities();
        app.getStage()->drawEntities();

        app.getDrawingManager()->presentScene();
    }

    return 0;
}