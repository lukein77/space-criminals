#ifndef _STAGE_H_INCLUDED_
#define _STAGE_H_INCLUDED_

#include "common.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Draw.h"
#include <list>
#include <iterator>

class Player;

class Enemy;

class Stage {
    private:
        std::list <Entity*> entities;
        std::list <Enemy*> enemies;
        Player *player;
        Uint32 spawnTime;
    public:
        Stage();
        ~Stage();
        void initStage();
        void initPlayer();
        void addEntity(Entity *entity);
        const std::list <Enemy*> &getEnemies();
        void removeEnemy(Enemy *enemy);
        void updateEntities();
        void drawEntities();
        void handleSpawn();
        void spawnEnemy(int enemyType);
        Player *getPlayer() { return player; }
};

#endif