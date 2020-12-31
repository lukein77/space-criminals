#include "Player.h"

Player::Player() : Entity() {}

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

    Entity::update();
}