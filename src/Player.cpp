#include "Player.h"

Player::Player() : Entity() {
    setTexture(draw::loadTexture("graphics/player.png"));
    lives = 3;
}

Player::~Player() {}

void Player::update() {
    App& app = App::instance();
    
    setXSpeed(0);
    setYSpeed(0);

    if (app.getKey(SDL_SCANCODE_UP)) {
        setYSpeed(-PLAYER_SPEED);
    }
    if (app.getKey(SDL_SCANCODE_DOWN)) {
        setYSpeed(PLAYER_SPEED);
    }  
    if (app.getKey(SDL_SCANCODE_LEFT)) {
        setXSpeed(-PLAYER_SPEED);
    }
    if (app.getKey(SDL_SCANCODE_RIGHT)) {
        setXSpeed(PLAYER_SPEED);
    }
    if ((app.getKey(SDL_SCANCODE_LCTRL)) || (app.getKey(SDL_SCANCODE_RCTRL))) {
        toggleFire();
    }

    if (shooting) {
        if (reload == 0) {
            shoot();
            reload = PLAYER_SHOOT_SPEED;
        } else {
            reload--;
        }
    }

    Entity::move();    
}

void Player::toggleFire() {
    shooting = !shooting;
    reload = PLAYER_SHOOT_SPEED;
}

void Player::shoot() {
    Bullet *bullet = new Bullet(BULLETTYPE_PLAYER);
    bullet->setPos(this->getX() + 16, this->getY());
    reload = PLAYER_SHOOT_SPEED;
    App::instance().getStage()->addEntity(bullet);
}