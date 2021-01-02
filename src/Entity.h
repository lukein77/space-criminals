#ifndef _ENTITY_H_INCLUDED_
#define _ENTITY_H_INCLUDED_

#include "common.h"

/*  
An Entity is an object that can be drawed on the screen.
Therefore, it has a position and a texture.
*/

class Entity {
    private:
        int x, y;
        int dx, dy;
        int health;
        SDL_Texture *texture;
    public:
        Entity();
        Entity(int x, int y, SDL_Texture *texture);
        void setX(int x);
        void setY(int y);
        void setXSpeed(int dx);
        void setYSpeed(int dy);
        void setPos(int x, int y);
        void setTexture(SDL_Texture *texture);
        int getX() { return x; }
        int getY() { return y; }
        int getHealth() { return health; }
        bool isAlive() { return (health > 0); }
        SDL_Texture *getTexture() { return texture; }
        void move();

        virtual void update() {}
        virtual ~Entity() {}
};

#endif