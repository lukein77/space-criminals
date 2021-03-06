#include "Enemy.h"
#include "Draw.h"

Enemy::Enemy(int type) : Entity() {
    enemyType = type;
    reload = 100;
    switch (enemyType) {
        case ENEMYTYPE_COMMON:
            setTexture(App::instance().getDrawingManager()->loadTexture("enemy.png"));
            setSpeed(ENEMY_SPEED_COMMON);
            setScore(100);
            setHealth(10);
            break;
        case ENEMYTYPE_DIAGONAL:
            setTexture(App::instance().getDrawingManager()->loadTexture("enemy2.png"));
            setSpeed(ENEMY_SPEED_COMMON);
            setHealth(20);
            break;
    }
}

Enemy::~Enemy() {}

void Enemy::update() {
    move();

    Player *player = App::instance().getStage()->getPlayer();
    if (Entity::checkCollision(&(getTexture()->rect), &(player->getTexture()->rect))) {
        takeDamage(getHealth());
        player->takeDamage(player->getHealth());
    }

    if (getY() > SCREEN_HEIGHT + getH()) {
        setHealth(0);
    }

    if (!isAlive()) {
        App::instance().getStage()->removeEnemy(this);
    }

    if (reload == 0 && App::instance().getState() != GAME_GAMEOVER) {
        shoot();
    } else {
        reload--;
    }
}

void Enemy::draw() {
    App::instance().getDrawingManager()->blit(getTexture());
}

void Enemy::move() {
    if (enemyType == ENEMYTYPE_COMMON) {
        setY(getY() + getSpeed());
    }
}

void Enemy::shoot() {
    Bullet *bullet;
    if (enemyType == ENEMYTYPE_COMMON) {
        bullet = new Bullet(BULLETTYPE_ENEMY_FOLLOW);
    }
    bullet->setPos(getX() + getW() / 2 - bullet->getW() /  2, getY() + getH());
    bullet->setTrajectory();
    reload = rand() % 100 + 100;
    App::instance().getStage()->addEntity(bullet);
}

void Enemy::die() {
    Animation *explosion = new Animation("explosion.png", 8, 96, 96);
    explosion->setPos(getX() + getW() / 2 - 48, getY() + getH() / 2 - 48);
    App::instance().getStage()->addAnimation(explosion);
}

void Enemy::setScore(unsigned int score) {
    this->score = score;
}