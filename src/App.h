#ifndef _APP_H_INCLUDED_
#define _APP_H_INCLUDED_

#include "common.h"
#include "Stage.h"
#include "Draw.h"
#include "Audio.h"
#include "Menu.h"

class Stage;
class Draw;
class Menu; // ver si funca sacando esto

class App {
    private:
        int state;
        Stage *stage;
        Draw *drawingManager;
        Audio *audioManager;
        Menu *menu;

        App();
        ~App();
        void handleKeyDown(SDL_KeyboardEvent *event);
        void handleKeyUp(SDL_KeyboardEvent *event);
    public:
        static App& instance() {
            static App *instance_ = new App();
            return *instance_;
        }

        bool initSDL();
        void createStage();
        
        void handleInput();

        Stage *getStage() { return stage; }
        Draw *getDrawingManager() { return drawingManager; }
        Audio *getAudioManager() { return audioManager; }

        void handleState();
        void changeState(int newState);
        int getState() { return state; }
};

#endif