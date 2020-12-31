#include "main.h"

int main(int argc, char *argv[]) {
    
    App& app = App::instance();
    memset(&player, 0, sizeof(Player));

    initSDL();

    player.setX(500);
    player.setY(400);
    player.setTexture(loadTexture("graphics/player.png"));

    atexit(cleanup);

    while (true) {
        prepareScene();
        
        doInput();
        
        player.update();

		blit(player.getTexture(), player.getX(), player.getY());

        presentScene();

        SDL_Delay(16);
    }

    return 0;
}