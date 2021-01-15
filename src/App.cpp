#include "App.h"

App::App() {
    drawingManager = new Draw();
}

void App::setKey(int key, bool value) {
    keyboard[key] = value;
}

void App::createStage() {
    stage = new Stage();
    stage->initStage();
}