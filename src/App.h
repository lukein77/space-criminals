#include "common.h"

class App {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
    public:
        bool up, down, left, right;
        bool setRenderer(SDL_Renderer *renderer);
        bool setWindow(SDL_Window *window);
        SDL_Renderer *getRenderer() { return renderer; }
        SDL_Window *getWindow() { return window; }
};