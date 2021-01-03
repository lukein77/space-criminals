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

void Stage::addEntity(Entity *entity) {
    entities.push_back(entity);
}

void Stage::removeEntity(Entity *entity) {
    entities.remove(entity);
    delete entity;
}

void Stage::updateEntities() {
    std::list <Entity*> :: iterator it = entities.begin();
    while (it != entities.end()) {
        (*it)->update();
        if (!(*it)->isAlive()) {
            // if entity.health == 0, then remove entity
            delete *it;
            entities.erase(it++);
        } else {
            it++;
        }
    }
    printf("entities: %ld\n", entities.size());
}

void Stage::drawEntities() {
    std::list <Entity*> :: iterator it;
    for (it = entities.begin(); it != entities.end(); it++) {
        if ((*it)->isAlive()) {
            draw::blit((*it)->getTexture(), (*it)->getX(), (*it)->getY());
        }
    }
}