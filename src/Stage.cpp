#include "Stage.h"

Stage::~Stage() {
    delete player;
}

void Stage::initStage() {
    entities.clear();
    initPlayer();
}

void Stage::initPlayer() {
    player = new Player();
    player->setPos(500, 400);
    entities.push_back(player);
}

void Stage::updateEntities() {
    std::list <Entity*> :: iterator it;
    for (it = entities.begin(); it != entities.end(); it++) {
        (*it)->update();
    }
}