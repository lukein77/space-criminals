#include "Bullet.h"

Bullet::Bullet(int type) : Entity() {
    bulletType = type;
    switch (bulletType) {
        case BULLETTYPE_PLAYER:
            setTexture(draw::loadTexture("graphics/b0.png"));
            setSpeed(BULLETSPEED_PLAYER);
            setMovement(DIRECTION_UP, true);
            break;
        default:
            setTexture(draw::loadTexture("graphics/b1.png"));
            setSpeed(BULLETSPEED_ENEMY);
            setMovement(DIRECTION_DOWN, true);
            break;
    }
}

Bullet::~Bullet() {}

void Bullet::update() {
    std::list <Enemy*> enemies = App::instance().getStage()->getEnemies();
    std::list <Enemy*> :: iterator it;

    SDL_Rect myRect = getTexture()->rect;

    Enemy *enemy = nullptr;

    for (it = enemies.begin(); it != enemies.end(); it++) {
        if ((*it)->isAlive()) {
            SDL_Rect enemyRect = (*it)->getTexture()->rect;
            if (Entity::checkCollision(&myRect, &enemyRect)) {
                enemy = *it;
                break;
            }
        }
    }

    if (!enemy) {
        Entity::move();
        if (getY() < 0) {
            setHealth(0);
        }
    } else {
        setHealth(0);
        enemy->takeDamage(10);
    }

}