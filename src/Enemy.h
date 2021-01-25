#ifndef _ENEMY_H_INCLUDED_
#define _ENEMY_H_INCLUDED_

#include "Entity.h"
#include "App.h"
#include "Animation.h"

class Enemy : public Entity {
    private:
        int enemyType;
        int reload;
        unsigned int score;
    public:
        Enemy(int type);
        ~Enemy();
        void update();
        void move();
        void shoot();
        void die();
        void setScore(unsigned int score);
        unsigned int getScore() { return score; }
};

#endif