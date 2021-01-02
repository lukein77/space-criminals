#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include "Entity.h"
#include "draw.h"


class Player : public Entity {
    private:
        int lives;
    public:
        Player();
        ~Player() {}
        void update();
};

#endif