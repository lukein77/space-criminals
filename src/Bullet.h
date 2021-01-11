#ifndef _BULLET_H_DEFINED_
#define _BULLET_H_DEFINED_

#include "common.h"
#include "App.h"
#include "Entity.h"
#include "Enemy.h"
#include "draw.h"

class Bullet : public Entity {
    private:
        int bulletType;
    public:
        Bullet(int type);
        ~Bullet();
        void update();
};

#endif