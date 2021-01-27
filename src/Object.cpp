#include "Object.h"

Object::Object() {
    setSpeed(5);
    setHealth(1);
    animation = new Animation("powerup.png", 4, 24, 24, true);
}

Object::~Object() {}

void Object::update() {
    setTexture(animation->getTexture());
    animation->update();

    move();

    Player *player = App::instance().getStage()->getPlayer();
    if (Entity::checkCollision(&(getTexture()->rect), &(player->getTexture()->rect))) {
        player->addScore(1000);
        printf("COLLIDED\n");
        setHealth(0);
    }
}

void Object::move() {
    setY(getY() + getSpeed());
    if (getY() > SCREEN_HEIGHT) {
        setHealth(0);
    }
}


