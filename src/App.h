#ifndef _APP_H_INCLUDED_
#define _APP_H_INCLUDED_

#include "common.h"
#include "Stage.h"
#include "Draw.h"
#include "Audio.h"

class Stage;
class Draw;

class App {
    private:
        int state;
        Stage *stage;
        Draw *drawingManager;
        Audio *audioManager;

        App();
        ~App();
        void doKeyDown(SDL_KeyboardEvent *event);
        void doKeyUp(SDL_KeyboardEvent *event);
    public:
        static App& instance() {
            static App *instance_ = new App();
            return *instance_;
        }

        bool initSDL();
        void createStage();
        
        void doInput();

        Stage *getStage() { return stage; }
        Draw *getDrawingManager() { return drawingManager; }
        Audio *getAudioManager() { return audioManager; }

        void setState(int state);
        int getState() { return state; }
};

#endif