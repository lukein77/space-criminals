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
    loadBackground();
}

void Stage::initPlayer() {
    player = new Player();
    player->setPos(SCREEN_WIDTH / 2 - player->getW() / 2, SCREEN_HEIGHT - player->getH() * 2);
    entities.push_back(player);
}

void Stage::loadBackground() {
    background = App::instance().getDrawingManager()->loadTexture("background01.png");
    background->rect.h *= SCREEN_WIDTH / (background->rect.w);
    background->rect.w = SCREEN_WIDTH;
    background->rect.x = 0;
    background->rect.y = SCREEN_HEIGHT - background->rect.h;
}

void Stage::updateBackground() {
    if (background->rect.y < -5) {
        background->rect.y += BACKGROUND_SPEED;
    }
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

void Stage::updateAndDraw() {
    updateBackground();
    updateEntities();
    handleSpawn();

    drawEntities();
    drawAnimations();
    
    updateAnimations();
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
    if (SDL_GetTicks() - spawnTime >= 1500) {
        spawnTime = SDL_GetTicks();
        spawnEnemy(rand() % 3);
    }
}

void Stage::spawnEnemy(int enemyType) {
    Enemy *enemy = new Enemy(enemyType);
    addEntity(enemy);
    enemies.push_back(enemy);
}

void Stage::drawEntities() {

    App::instance().getDrawingManager()->blit(background);

    std::list <Entity*> :: iterator it;
    for (it = entities.begin(); it != entities.end(); it++) {
        if ((*it)->isAlive()) {
            (*it)->draw();
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

void Stage::drawGameOver() {
    if (SDL_GetTicks() - time < 3000) {
        App::instance().getDrawingManager()->renderGameOver();
    } else {
        App::instance().changeState(GAME_MAINMENU);
    }
}

void Stage::gameOver(long time) {
    this->time = time;
    App::instance().changeState(GAME_GAMEOVER);
}