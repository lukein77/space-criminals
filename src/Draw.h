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
        TTF_Font *defaultFont;
        TTF_Font *smallFont;
        TTF_Font *largeFont;
        
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

        void clearScene();
        void renderScene();
        Texture *loadTexture(const char *filename);
        void blit(Texture *texture, int x, int y, SDL_Rect *clip = NULL);
        void renderText(const char *text, int x, int y, SDL_Color color, int size=FONTSIZE_DEFAULT);
        void renderUI();
};

#endif