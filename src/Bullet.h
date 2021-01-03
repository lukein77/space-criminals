#ifndef _BULLET_H_DEFINED_
#define _BULLET_H_DEFINED_

#include "common.h"
#include "Entity.h"
#include "draw.h"

class Bullet : public Entity {
    private:
        int bulletType;
    public:
        Bullet(int bulletType);
        ~Bullet();
        void update();
};

#endif