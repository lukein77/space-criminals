#include "Enemy.h"
#include "Draw.h"

Enemy::Enemy(int type) : Entity() {
    enemyType = type;
    reload = 20;
    switch (enemyType) {
        case ENEMYTYPE_COMMON:
        /* Simplest enemy. Only travels in one direction and shoots occasionally. */
            setTexture(App::instance().getDrawingManager()->loadTexture("enemy.png"));
            setPos(rand() % (SCREEN_WIDTH - getW()), -getH());
            setDirection(0, 1);
            setSpeed(ENEMY_SPEED_COMMON);
            setScore(100);
            setHealth(10);
            break;
        case ENEMYTYPE_DIAGONAL:
        /* Moves diagonally and bounces off the edges of the screen. Harder to kill.*/
            setTexture(App::instance().getDrawingManager()->loadTexture("enemy2.png"));
            setPos(rand() % (SCREEN_WIDTH - getW()), -getH());
            setDirection((rand() % 2) ? 1 : -1, 0.5);
            setSpeed(ENEMY_SPEED_FAST);
            setHealth(20);
            setScore(250);
            break;
        case ENEMYTYPE_KAMIKAZE:
        /* Tries to move directly towards the player at high speed.*/
            setTexture(App::instance().getDrawingManager()->loadTexture("enemy3.png"));
            setPos(rand() % (SCREEN_WIDTH - getW()), -getH());
            setSpeed(ENEMY_SPEED_SUPERFAST);
            setHealth(10);
            setScore(200);

            // get player's position and draw a vector towards him
            Player *player = App::instance().getStage()->getPlayer();
            int player_x = (player->getX() + player->getW() / 2);
            int player_y = (player->getY() + player->getH() / 2);
            setDirectionTowardsPoint(getX(), getY(), player_x, player_y);

            break;
    }
}


Enemy::~Enemy() {}

void Enemy::update() {
    // First move the enemy
    move();

    // Check collisions with player
    Player *player = App::instance().getStage()->getPlayer();
    if (checkCollision(player->getRect()) && (!player->isImmune()) && (player->isAlive())) {
        takeDamage(getHealth());
        player->takeDamage(player->getHealth());
    }

    if (enemyType == ENEMYTYPE_DIAGONAL) {
        // Check if it is on either edge of the screen
        if ((getX() <= 0) || (getX() >= SCREEN_WIDTH - getW())) {
            setDirectionX(-getDirection().x);
        }
    }

    // Check if it has left the screen
    if (getY() > SCREEN_HEIGHT + getH()) {
        setHealth(0);
    }

    // If dead, remove from stage
    if (!isAlive()) {
        App::instance().getStage()->removeEnemy(this);
    }

    // Check if it has to shoot
    if (reload == 0 && App::instance().getState() != GAME_GAMEOVER) {
        shoot();
    } else {
        reload--;
    }
}

void Enemy::draw() {
    App::instance().getDrawingManager()->blit(getTexture());
}


void Enemy::shoot() {
    Bullet *bullet;
    int bullet_x = getX() + getW() / 2 - 8; // 8 = bullet width / 2
    int bullet_y = getY() + getH();

    switch (enemyType) {
        case ENEMYTYPE_COMMON:
            bullet = new Bullet(BULLETTYPE_ENEMY_FOLLOW, bullet_x, bullet_y);
            break;
        default:
            bullet = new Bullet(BULLETTYPE_ENEMY_COMMON, bullet_x, bullet_y);
            break;
    }

    reload = rand() % 100 + 50;
    App::instance().getStage()->addEntity(bullet);
}

void Enemy::die() {
    Animation *explosion = new Animation("explosion.png", 8, 96, 96);
    explosion->setPos(getX() + getW() / 2 - 48, getY() + getH() / 2 - 48);
    App::instance().getStage()->addAnimation(explosion);
    App::instance().getAudioManager()->playSound("explode.wav");
}

void Enemy::setScore(unsigned int score) {
    this->score = score;
}