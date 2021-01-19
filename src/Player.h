#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include "Entity.h"
#include "Bullet.h"
#include "Draw.h"
#include "App.h"

class Player : public Entity {
    private:
        int lives;
        unsigned int score;
        bool shooting;
        int reload;
        bool direction[4];
    public:
        Player();
        ~Player();
        void update();
        void move();
        void checkBoundaries();
        void setMovement(int direction, bool value);
        void shoot();
        void toggleFire();
        void addScore(unsigned int score);
        unsigned int getScore() { return score; }
};

#endif