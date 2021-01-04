#include "Enemy.h"
#include "draw.h"

Enemy::Enemy(int type) : Entity() {
    enemyType = type;
    switch (enemyType) {
        case ENEMYTYPE_COMMON:
            setTexture(draw::loadTexture("graphics/enemy.png"));
            setYSpeed(ENEMY_SPEED_COMMON);
            setHealth(10);
            break;
        case ENEMYTYPE_DIAGONAL:
            setTexture(draw::loadTexture("graphics/enemy2.png"));
            setHealth(20);
            break;
    }
}

Enemy::~Enemy() {}

void Enemy::update() {
    Entity::move();

    if (getY() > SCREEN_HEIGHT + 30) {
        setHealth(0);
    }
}