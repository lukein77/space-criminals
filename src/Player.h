#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include "Entity.h"
#include "App.h"

class Player : public Entity {
    private:
        int lives = 3;
    public:
        Player();
        void update();
};

#endif