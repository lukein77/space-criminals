#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include "common.h"
#include "App.h"
#include <map>

typedef struct {
    std::string filename;
    int index;
} cacheNode;

class Draw {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        
        std::map <std::string, SDL_Texture*> textureCache;

        void clearTextureCache();
        SDL_Texture *addTextureToCache(std::string filename);
    public:
        Draw();
        ~Draw();
        bool initialize();
        bool setRenderer(SDL_Renderer *renderer);
        bool setWindow(SDL_Window *window);
        SDL_Renderer *getRenderer() { return renderer; }
        SDL_Window *getWindow() { return window; }

        void prepareScene();
        void presentScene();
        Texture *loadTexture(const char *filename);
        void blit(Texture *texture, int x, int y);
};

#endif