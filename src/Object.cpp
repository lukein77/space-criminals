#include "Object.h"

Object::Object() {
    setSpeed(1);
    setHealth(1);
}

Object::Object(int objType) : Object() {
    objectType = objType;
    switch (objectType) {
        case OBJTYPE_SCORE:
            score = 1000;
            animation = new Animation("powerup.png", 4, 24, 24, true);
            getTexture()->rect.w = animation->getTexture()->rect.w;
            getTexture()->rect.h = animation->getTexture()->rect.h;
            break;
        case OBJTYPE_LIFE:
            score = 2500;
            animation = new Animation("powerup2.png", 4, 24, 24, true);
            getTexture()->rect.w = animation->getTexture()->rect.w;
            getTexture()->rect.h = animation->getTexture()->rect.h;
            break;
        default:
            score = 0;
            animation = nullptr;
            setTexture(App::instance().getDrawingManager()->loadTexture("object.png"));
            break;

    }
}

Object::~Object() {}

void Object::update() {
    
    if (animation) {
        animation->update();
    }

    move();

    Player *player = App::instance().getStage()->getPlayer();
    if (Entity::checkCollision(&(getTexture()->rect), &(player->getTexture()->rect))) {
        player->pickUpObject(this);
        setHealth(0);
    }
}

void Object::move() {
    setY(getY() + getSpeed());
    if (getY() > SCREEN_HEIGHT) {
        setHealth(0);
    }
}

void Object::draw() {
    if (animation) {
        App::instance().getDrawingManager()->blit(animation->getTexture(), animation->getClip());
    } else {
        App::instance().getDrawingManager()->blit(getTexture());
    }
}
