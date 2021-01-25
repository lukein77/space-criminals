#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include "Entity.h"
#include "Bullet.h"
#include "Draw.h"
#include "App.h"
#include "Animation.h"

class Player : public Entity {
    private:
        long oldTime;
        int lives;
        unsigned int score;
        bool shooting;
        bool immune;
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
        void respawn();
        void die();
        unsigned int getScore() { return score; }
        bool isAlive() { return !(getHealth() == 0 && lives == 0); }
        bool isImmune() { return immune; }
};

#endif