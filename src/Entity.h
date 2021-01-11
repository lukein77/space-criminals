#ifndef _ENTITY_H_INCLUDED_
#define _ENTITY_H_INCLUDED_

#include "common.h"

/*  
An Entity is an object that can be drawed on the screen.
Therefore, it has a position and a texture.
*/

class Entity {
    private:
        float x, y;
        int w, h;
        bool direction[4];
        int speed;
        int health;
        Texture texture;
    public:
        Entity();
        Entity(int x, int y, Texture *texture);
        void setX(int x);
        void setY(int y);
        void setPos(int x, int y);

        void setMovement(int direction, bool value);
        void setSpeed(int speed);
        
        void setTexture(Texture *texture);
        void setHealth(int health);
        void takeDamage(int damage);

        int getX() { return x; }
        int getY() { return y; }
        int getW() { return texture.rect.w; }
        int getH() { return texture.rect.h; }
        int getHealth() { return health; }
        bool isAlive() { return (health > 0); }
        Texture *getTexture() { return &texture; }

        void move();
        void checkBoundaries();
        bool checkCollision(SDL_Rect *a, SDL_Rect *b);

        virtual void update() {}
        virtual ~Entity() {}
};

#endif