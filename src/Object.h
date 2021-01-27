#ifndef _OBJECT_H_DEFINED_
#define _OBJECT_H_DEFINED_

#include "common.h"
#include "App.h"
#include "Entity.h"
#include "Animation.h"

class Animation;

class Object : public Entity {
    private:
        Animation *animation;
    public:
        Object();
        ~Object();
        void update();
        void move();
};

#endif