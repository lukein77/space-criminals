#ifndef _APP_H_INCLUDED_
#define _APP_H_INCLUDED_

#include "common.h"
#include "Stage.h"

class Stage;

class App {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        bool keyboard[MAX_KEYBOARD_KEYS];
        Stage *stage;

        App() {}
    public:
        static App& instance() {
            static App *instance_ = new App();
            return *instance_;
        }

        void createStage();
        bool setRenderer(SDL_Renderer *renderer);
        bool setWindow(SDL_Window *window);
        void setKey(int key, bool value);

        SDL_Renderer *getRenderer() { return renderer; }
        SDL_Window *getWindow() { return window; }
        bool getKey(int key) { return keyboard[key]; }
        Stage *getStage() { return stage; }
};

#endif