#ifndef _ENEMY_H_INCLUDED_
#define _ENEMY_H_INCLUDED_

#include "Entity.h"

class Enemy : public Entity {
    private:
        int enemyType;
    public:
        Enemy(int type);
        ~Enemy();
        void update();
        void shoot();
};

#endif