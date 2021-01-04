#include "Bullet.h"

Bullet::Bullet(int type) : Entity() {
    bulletType = type;
    switch (bulletType) {
        case BULLETTYPE_PLAYER:
            setTexture(draw::loadTexture("graphics/b0.png"));
            setYSpeed(-BULLETSPEED_PLAYER);
            break;
        default:
            setTexture(draw::loadTexture("graphics/b1.png"));
            setYSpeed(BULLETSPEED_ENEMY);
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