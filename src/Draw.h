#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include "common.h"
#include "App.h"

typedef struct {
    std::string filename;
    int index;
} cacheNode;

class Draw {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        
        cacheNode textureCacheTable[TEXTURE_CACHE_SIZE];
        SDL_Texture *textureCache[TEXTURE_CACHE_SIZE];
        int cacheSize;
        int cachePointer;
        void removeFromCache(int index);
        int searchTexture(const char *filename);
        void addCacheIndex(const char *filename, int index);
        SDL_Texture *addTextureToCache(const char *filename);
        SDL_Texture *getTextureFromCache(int index) { return textureCache[index]; }
    public:
        Draw();
        ~Draw();
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