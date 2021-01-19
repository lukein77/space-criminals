#include "App.h"

App::App() {}

App::~App() {
    SDL_Quit();
}

bool App::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    drawingManager = new Draw();
    if (!drawingManager->initialize()) {
        return false;
    }

    return true;
}

void App::setKey(int key, bool value) {
    keyboard[key] = value;
}

void App::createStage() {
    stage = new Stage();
    stage->initStage();
}