#include "Enemy.h"
#include "draw.h"

Enemy::Enemy(int type) : Entity() {
    enemyType = type;
    switch (enemyType) {
        case ENEMYTYPE_COMMON:
            setTexture(draw::loadTexture("graphics/enemy.png"));
            setSpeed(ENEMY_SPEED_COMMON);
            setMovement(DIRECTION_DOWN, true);
            setHealth(10);
            break;
        case ENEMYTYPE_DIAGONAL:
            setTexture(draw::loadTexture("graphics/enemy2.png"));
            setSpeed(ENEMY_SPEED_COMMON);
            setHealth(20);
            break;
    }
}

Enemy::~Enemy() {}

void Enemy::update() {
    Entity::move();

    SDL_Rect *playerRect = &(App::instance().getStage()->getPlayer()->getTexture()->rect);
    SDL_Rect *myRect = &(getTexture()->rect);

    /*if (Entity::checkCollision(myRect, playerRect)) {
        printf("collision\n");
    }*/

    if (getY() > SCREEN_HEIGHT + getH()) {
        setHealth(0);
    }

    if (!isAlive()) {
        App::instance().getStage()->removeEnemy(this);
    }
}