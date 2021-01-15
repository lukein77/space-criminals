#include "Bullet.h"

Bullet::Bullet(int type) : Entity() {
    bulletType = type;
    switch (bulletType) {
        case BULLETTYPE_PLAYER:
            setTexture(App::instance().getDrawingManager()->loadTexture("graphics/b0.png"));
            setSpeed(BULLETSPEED_PLAYER);
            break;
        default:
            setTexture(App::instance().getDrawingManager()->loadTexture("graphics/b1.png"));
            setSpeed(BULLETSPEED_ENEMY);
            break;
    }
}

Bullet::~Bullet() {}

void Bullet::setTrajectory() {
    if (bulletType == BULLETTYPE_PLAYER) {
        dx = 0;
        dy = -1;
    } else if (bulletType == BULLETTYPE_ENEMY_COMMON) {
        dx = 0;
        dy = 1;
    } else if (bulletType == BULLETTYPE_ENEMY_FOLLOW) {
        Player *player = App::instance().getStage()->getPlayer();
        dx = (player->getX() + player->getW() / 2) - getX();
        dy = (player->getY() + player->getH() / 2) - getY();
        float n = sqrt(pow(dx, 2) + pow(dy, 2));
        dx = dx / n;
        dy = dy / n;
    }
}

void Bullet::update() {

    if (bulletType == BULLETTYPE_PLAYER) {
        // first check for collisions with enemies

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

        // if there are no collisions, move
        if (!enemy) {
            move();
            if (getY() < 0) {
                setHealth(0);
            }
        } else {
            setHealth(0);
            enemy->takeDamage(PLAYER_DAMAGE);
            if (!enemy->isAlive()) {
                App::instance().getStage()->getPlayer()->addScore(enemy->getScore());
                printf("score: %d\n", App::instance().getStage()->getPlayer()->getScore());
            }
        }
    } else {
        // enemy bullets
        // check collision with player

        Player *player = App::instance().getStage()->getPlayer();

        if (!Entity::checkCollision(&getTexture()->rect, &player->getTexture()->rect)) {
            move();
        } else {
            setHealth(0);
            player->takeDamage(5);
        }
    }
}

void Bullet::move() {
    if (dx != 0) setX(getX() + dx * getSpeed());
    setY(getY() + dy * getSpeed());
}