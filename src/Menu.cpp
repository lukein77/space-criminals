#include "Menu.h"

void Menu::selectPrevious() { 
    currentOption = (currentOption > 0) ? currentOption - 1 : numOptions - 1; 
    App::instance().getAudioManager()->playSound("select.wav");
}
void Menu::selectNext() {
    currentOption = (currentOption + 1) % numOptions; 
    App::instance().getAudioManager()->playSound("select.wav");
}


MainMenu::MainMenu() {
    currentOption = 0;
    numOptions = 3;
    background = *(App::instance().getDrawingManager()->loadTexture("main_menu.png"));

    labels[0] = "START";
    labels[1] = "OPTIONS";
    labels[2] = "EXIT";
}

void MainMenu::choose() {
    switch (currentOption) {
        case 0:
            // start game
            App::instance().changeState(GAME_RUNNING);
            break;
        case 1:
            printf("Options screen not implemented yet. Come back later.\n");
            break;
        case 2:
            App::instance().changeState(GAME_EXIT);
            break;
        default:
            currentOption = 0;
            break;
    }
}