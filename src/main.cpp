#include "main.h"

int main(int argc, char *argv[]) {
    
    App& app = App::instance();

    initSDL();

    app.createStage();
    app.getStage()->initStage();

    Player *player = app.getStage()->getPlayer();

    atexit(cleanup);

    while (true) {
        app.getDrawingManager()->prepareScene();
        
        doInput();
        
        app.getStage()->updateEntities();
        app.getStage()->drawEntities();

        app.getDrawingManager()->presentScene();

        SDL_Delay(16);
    }

    return 0;
}