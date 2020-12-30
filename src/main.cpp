#include "main.h"

int main(int argc, char *argv[]) {
    
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    initSDL();

    player.setX(500);
    player.setY(400);
    player.setTexture(loadTexture("graphics/player.png"));

    atexit(cleanup);

    while (true) {
        prepareScene();
        
        doInput();

        if (app.up) {
            player.setY(player.getY() - 4);
        }
        if (app.down) {
            player.setY(player.getY() + 4);
        }  
        if (app.left) {
            player.setX(player.getX() - 4);
        }
        if (app.right) {
            player.setX(player.getX() + 4);
        }

        blit(player.getTexture(), player.getX(), player.getY());

        presentScene();

        SDL_Delay(16);
    }

    return 0;
}