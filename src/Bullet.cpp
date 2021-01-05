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
    Entity::move();
    if (getY() < 0) {
        setHealth(0);
    }
}