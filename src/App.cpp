#include "App.h"

bool App::setWindow(SDL_Window *window) {
    this->window = window;
    return this->window != nullptr;
}

bool App::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
    return this->renderer != nullptr;
}

void App::setKey(int key, bool value) {
    keyboard[key] = value;
}

void App::createStage() {
    stage = new Stage();
    stage->initStage();
}