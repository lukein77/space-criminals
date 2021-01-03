#include "main.h"

int main(int argc, char *argv[]) {
    
    App& app = App::instance();

    initSDL();

    app.createStage();
    app.getStage()->initStage();

    Player *player = app.getStage()->getPlayer();

    atexit(cleanup);

    while (true) {
        draw::prepareScene();
        
        doInput();
        
        app.getStage()->updateEntities();
        app.getStage()->drawEntities();

        draw::presentScene();

        SDL_Delay(16);
    }

    return 0;
}