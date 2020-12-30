#include "common.h"

class Entity {
    private:
        int x;
        int y;
        SDL_Texture *texture;
    public:
        Entity();
        Entity(int x, int y, SDL_Texture *texture);
        void setX(int x);
        void setY(int y);
        void setPos(int x, int y);
        void setTexture(SDL_Texture *texture);
        int getX() { return x; }
        int getY() { return y; }
        SDL_Texture *getTexture() { return texture; }
};