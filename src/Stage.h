#ifndef _STAGE_H_INCLUDED_
#define _STAGE_H_INCLUDED_

#include "common.h"
#include "Entity.h"
#include "Player.h"
#include "draw.h"
#include <list>
#include <iterator>

class Player;

class Stage {
    private:
        std::list <Entity*> entities;
        Player *player;
    public:
        ~Stage();
        void initStage();
        void initPlayer();
        void addEntity(Entity *entity);
        void removeEntity(Entity *entity);
        void updateEntities();
        void drawEntities();
        Player *getPlayer() { return player; }
};

#endif