#include "Stage.h"

Stage::Stage() {
    spawnTime = 0;
}

Stage::~Stage() {
    delete player;
}

void Stage::initStage() {
    entities.clear();
    enemies.clear();
    animations.clear();

    initPlayer();

    Object *powerup = new Object(OBJTYPE_LIFE);
    powerup->setPos(200, 200);
    entities.push_back(powerup);
}

void Stage::initPlayer() {
    player = new Player();
    player->setPos(SCREEN_WIDTH / 2 - player->getW() / 2, SCREEN_HEIGHT - player->getH() * 2);
    entities.push_back(player);
}

void Stage::addEntity(Entity *entity) {
    entities.push_back(entity);
}

void Stage::addAnimation(Animation *animation) {
    animations.push_back(animation);
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

void Stage::updateAnimations() {
    std::list <Animation*> :: iterator it = animations.begin();
    while (it != animations.end()) {
        (*it)->update();
        if ((*it)->hasFinished()) {
            delete *it;
            animations.erase(it++);
        } else {
            it++;
        }
    }
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
            (*it)->draw();
        }
    }

    if (App::instance().getState() == GAME_GAMEOVER) {
        if (SDL_GetTicks() - time < 3000) {
            App::instance().getDrawingManager()->renderGameOver();
        } else {
            App::instance().setState(GAME_EXIT);
        }
    }
}

void Stage::drawAnimations() {
    std::list <Animation*> :: iterator it;
    for (it = animations.begin(); it != animations.end(); it++) {
        if (!(*it)->hasFinished()) {
            App::instance().getDrawingManager()->blit((*it)->getTexture(), (*it)->getX(), (*it)->getY(), (*it)->getClip());
        }
    }
}

void Stage::gameOver(long time) {
    this->time = time;
    App::instance().setState(GAME_GAMEOVER);
}