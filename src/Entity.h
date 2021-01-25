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
        int speed;
        int health;
        Texture texture;
    public:
        Entity();
        Entity(int x, int y, Texture *texture);
        void setX(int x);
        void setY(int y);
        void setPos(int x, int y);
        void setSpeed(int speed);
        
        void setTexture(Texture *texture);
        void setHealth(int health);
        void takeDamage(int damage);

        float getX() { return x; }
        float getY() { return y; }
        int getW() { return texture.rect.w; }
        int getH() { return texture.rect.h; }
        int getSpeed() { return speed; }
        int getHealth() { return health; }
        bool isAlive() { return (health > 0); }
        Texture *getTexture() { return &texture; }

        bool checkCollision(SDL_Rect *a, SDL_Rect *b);

        virtual void update() {}
        virtual void move() {}
        virtual void die() {}
        virtual ~Entity() {}
};

#endif