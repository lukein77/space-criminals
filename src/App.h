#ifndef _APP_H_INCLUDED_
#define _APP_H_INCLUDED_

#include "common.h"
#include "Stage.h"
#include "Draw.h"

class Stage;
class Draw;

class App {
    private:
        int state;
        Stage *stage;
        Draw *drawingManager;

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

        void setState(int state);
        int getState() { return state; }
};

#endif