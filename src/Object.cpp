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
            setAnimation("powerup.png", 4, 24, 24);
            //getTexture()->rect.w = animation->getTexture()->rect.w;
            //getTexture()->rect.h = animation->getTexture()->rect.h;
            break;
        case OBJTYPE_LIFE:
            score = 2500;
            setAnimation("powerup2.png", 4, 24, 24);
            break;
        default:
            score = 0;
            animation = nullptr;
            setTexture(App::instance().getDrawingManager()->loadTexture("object.png"));
            break;

    }
}

Object::~Object() {}

void Object::setAnimation(const char *filename, int frames, int w, int h) {
    this->animation = new Animation(filename, frames, w, h, true);
    this->setW(animation->getW());
    this->setH(animation->getH());
}

void Object::update() {
    
    if (animation) {
        animation->update();
    }

    move();

    if (getY() > SCREEN_HEIGHT) {
        setHealth(0);
    }

    Player *player = App::instance().getStage()->getPlayer();
    if (checkCollision(player->getRect())) {
        player->pickUpObject(this);
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
