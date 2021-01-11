#include "Stage.h"

Stage::Stage() {
    spawnTime = 0;
}

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

void Stage::removeEnemy(Enemy *enemy) {
    enemies.remove(enemy);
}

const std::list <Enemy*> &Stage::getEnemies() {
    return enemies;
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
    
    handleSpawn();
}

void Stage::handleSpawn() {
    if (spawnTime < UINT32_MAX) {
        spawnTime++;
        if (spawnTime % 100 == 0) {
            spawnEnemy(ENEMYTYPE_COMMON);
        }
    } else {
        spawnTime = 0;
    }
}

void Stage::spawnEnemy(int enemyType) {
    Enemy *enemy = new Enemy(enemyType);
    enemy->setPos(rand() % (SCREEN_WIDTH - enemy->getW()), -enemy->getH());
    addEntity(enemy);
    enemies.push_back(enemy);
}

void Stage::drawEntities() {
    std::list <Entity*> :: iterator it;
    for (it = entities.begin(); it != entities.end(); it++) {
        if ((*it)->isAlive()) {
            draw::blit((*it)->getTexture(), (*it)->getX(), (*it)->getY());
        }
    }
}