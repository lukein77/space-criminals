#include "Player.h"

Player::Player() : Entity() {
    setTexture(draw::loadTexture("graphics/player.png"));
    setSpeed(PLAYER_SPEED);
    lives = 3;
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

    Entity::move();    
}

void Player::toggleFire() {
    shooting = !shooting;
    reload = PLAYER_RELOAD_SPEED;
}

void Player::shoot() {
    Bullet *bullet = new Bullet(BULLETTYPE_PLAYER);
    bullet->setPos(this->getX() + 16, this->getY());
    reload = PLAYER_RELOAD_SPEED;
    App::instance().getStage()->addEntity(bullet);
}