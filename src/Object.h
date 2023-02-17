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
        int objectType;
        int score;
    public:
        Object();
        Object(int objType);
        ~Object();
        void update();
        void draw();
        int getObjectType() { return objectType; }
        int getScore() { return score; }
        
        void setAnimation(const char *filename, int frames, int w, int h);
};

#endif