#include "Player.h"

Player::Player() : Entity() {
    setTexture(draw::loadTexture("graphics/player.png"));
    setHealth(100);
    setSpeed(PLAYER_SPEED);
    for (int i = 0; i < 4; i++) {
        direction[i] = false;
    }
    lives = 3;
    score = 0;
    shooting = false;
}

Player::~Player() {}

void Player::update() {
    App& app = App::instance();

    if (shooting) {
        if (reload == 0) {
            shoot();
            reload = PLAYER_RELOAD_SPEED;
        } else {
            reload--;
        }
    }

    move();    
    checkBoundaries();
}

void Player::move() {
    
    struct { int x, y; } dir;
    dir.x = 0;
    dir.y = 0;

    if (direction[DIRECTION_UP]) {
        dir.y = -1;
    }
    if (direction[DIRECTION_DOWN]) {
        dir.y = 1;
    }
    if (direction[DIRECTION_LEFT]) {
        dir.x = -1;
    }
    if (direction[DIRECTION_RIGHT]) {
        dir.x = 1;
    }

    float dx, dy;
    double n;

    n = sqrt(pow(dir.x, 2) + pow(dir.y, 2));

    if (n != 0) {    
        dx = dir.x / n;
        dy = dir.y / n;

        setX(getX() + dx * getSpeed());
        setY(getY() + dy * getSpeed());
    }
}

void Player::setMovement(int direction, bool value) {
    this->direction[direction] = value;
}

void Player::checkBoundaries() {
    float x = getX();
    float y = getY();
    int w = getTexture()->rect.w;
    int h = getTexture()->rect.h;

    if (x < 0) {
        setX(0);
    }
    if (x > SCREEN_WIDTH - w) {
        setX(SCREEN_WIDTH - w);
    }
    if (y < 0) {
        setY(0);
    }
    if (y > SCREEN_HEIGHT - h) {
        setY(SCREEN_HEIGHT - h);
    }
}

void Player::toggleFire() {
    shooting = !shooting;
    reload = PLAYER_RELOAD_SPEED;
}

void Player::shoot() {
    Bullet *bullet = new Bullet(BULLETTYPE_PLAYER);
    bullet->setPos(this->getX() + this->getW() / 2 - bullet->getW() / 2, this->getY());
    bullet->setTrajectory();
    reload = PLAYER_RELOAD_SPEED;
    App::instance().getStage()->addEntity(bullet);
}

void Player::addScore(unsigned int score) {
    this->score += score;
}