#ifndef _ENEMY_H_INCLUDED_
#define _ENEMY_H_INCLUDED_

#include "Entity.h"
#include "App.h"

class Enemy : public Entity {
    private:
        int enemyType;
        int reload;
    public:
        Enemy(int type);
        ~Enemy();
        void update();
        void move();
        void shoot();
};

#endif