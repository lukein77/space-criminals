#include "Bullet.h"

Bullet::Bullet(int type, int x, int y) : Entity() {
    bulletType = type;
    switch (bulletType) {
        case BULLETTYPE_PLAYER:
            setTexture(App::instance().getDrawingManager()->loadTexture("b0.png"));
            setSpeed(BULLETSPEED_PLAYER);
            break;
        default:
            setTexture(App::instance().getDrawingManager()->loadTexture("b1.png"));
            setSpeed(BULLETSPEED_ENEMY);
            break;
    }
    setPos(x, y);
    setTrajectory();
}

Bullet::~Bullet() {}

void Bullet::setTrajectory() {
    if (bulletType == BULLETTYPE_PLAYER) {
        setDirection(0, -1);
    } else if (bulletType == BULLETTYPE_ENEMY_COMMON) {
        setDirection(0, 1);
    } else if (bulletType == BULLETTYPE_ENEMY_FOLLOW) {
        Player *player = App::instance().getStage()->getPlayer();
        int player_x = (player->getX() + player->getW() / 2);
        int player_y = (player->getY() + player->getH() / 2);
        setDirectionTowardsPoint(getX(), getY(), player_x, player_y);
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
                if (checkCollision((*it)->getRect())) {
                    enemy = *it;
                    break;
                }
            }
        }

        // if there are no collisions, move
        if (!enemy) {
            Entity::move();
            if (getY() < 0) {
                setHealth(0);
            }
        } else {
            // player killed an enemy
            setHealth(0);
            enemy->takeDamage(PLAYER_DAMAGE);
            if (!enemy->isAlive()) {
                App::instance().getStage()->getPlayer()->addScore(enemy->getScore());
            } else {
                App::instance().getAudioManager()->playSound("hurt.wav");
            }
        }
    } else {
        // enemy bullets
        // check collision with player

        Player *player = App::instance().getStage()->getPlayer();

        move();

        if (checkCollision(player->getRect())) {
            if (!player->isImmune()) {
                setHealth(0);
                player->takeDamage(ENEMY_DAMAGE);
            }
        }
    }
}

void Bullet::draw() {
    App::instance().getDrawingManager()->blit(getTexture());
}
