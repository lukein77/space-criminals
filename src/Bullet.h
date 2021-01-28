#ifndef _BULLET_H_DEFINED_
#define _BULLET_H_DEFINED_

#include "common.h"
#include "App.h"
#include "Entity.h"
#include "Enemy.h"
#include "Draw.h"

class Bullet : public Entity {
    private:
        int bulletType;
        float dx, dy;
    public:
        Bullet(int type);
        ~Bullet();
        void setTrajectory();
        void update();
        void draw();
        void move();
};

#endif