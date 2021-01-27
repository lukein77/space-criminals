#ifndef _STAGE_H_INCLUDED_
#define _STAGE_H_INCLUDED_

#include "common.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Draw.h"
#include "Animation.h"
#include "Object.h"
#include <list>
#include <iterator>

class Player;
class Enemy;
class Animation;

class Stage {
    private:
        std::list <Entity*> entities;
        std::list <Enemy*> enemies;
        std::list <Animation*> animations;
        Player *player;
        Uint32 spawnTime;
        long time;
    public:
        Stage();
        ~Stage();
        void initStage();
        void initPlayer();
        void addEntity(Entity *entity);
        void addAnimation(Animation *animation);
        const std::list <Enemy*> &getEnemies();
        void removeEnemy(Enemy *enemy);
        void updateEntities();
        void updateAnimations();
        void drawEntities();
        void drawAnimations();
        void handleSpawn();
        void spawnEnemy(int enemyType);
        void gameOver(long time);
        Player *getPlayer() { return player; }
};

#endif