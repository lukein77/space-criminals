#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include "Entity.h"
#include "Bullet.h"
#include "draw.h"


class Player : public Entity {
    private:
        int lives;
        bool shooting;
        int reload;
    public:
        Player();
        ~Player();
        void update();
        void shoot();
        void toggleFire();
};

#endif