#ifndef _ENEMY_H_INCLUDED_
#define _ENEMY_H_INCLUDED_

#include "Entity.h"
#include "App.h"
#include "Animation.h"

class Enemy : public Entity {
    private:
        int enemyType;
        vector direction;
        int reload;
        unsigned int score;
    public:
        Enemy(int type);
        ~Enemy();
        void update();
        void draw();
        void move();
        void shoot();
        void die();
        void setScore(unsigned int score);
        void setDirection(int x, int y);
        vector &getDirection() { return direction; };
        unsigned int getScore() { return score; }
};

#endif