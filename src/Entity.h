#ifndef _ENTITY_H_INCLUDED_
#define _ENTITY_H_INCLUDED_

#include "common.h"

class Entity {
    private:
        int speed;
        int health;
        vector direction;
        Texture texture;

        void normalizeDirection();
    public:
        Entity();
        Entity(int x, int y, Texture *texture);
        void setX(int x);
        void setY(int y);
        void setPos(int x, int y);
        void setW(int w);
        void setH(int h);
        void setSpeed(int speed);
        void setDirection(double x, double y);
        void setDirectionX(double x);
        void setDirectionY(double y);
        void setDirectionTowardsPoint(int x1, int y1, int x2, int y2);
        void move();
        
        void setTexture(Texture *texture);
        void setHealth(int health);
        void takeDamage(int damage);

        int getX() { return texture.rect.x; }
        int getY() { return texture.rect.y; }
        int getW() { return texture.rect.w; }
        int getH() { return texture.rect.h; }
        SDL_Rect getRect() { return texture.rect; }

        int getSpeed() { return speed; }
        vector getDirection() { return direction; }
        int getHealth() { return health; }
        bool isAlive() { return (health > 0); }
        Texture *getTexture() { return &texture; }

        bool checkCollision(SDL_Rect other);
        vector getVector(int x1, int y1, int x2, int y2);

        virtual void update() {}
        virtual void draw() {}
        virtual void die() {}
        virtual ~Entity() {}
};

#endif