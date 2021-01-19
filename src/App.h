#ifndef _APP_H_INCLUDED_
#define _APP_H_INCLUDED_

#include "common.h"
#include "Stage.h"
#include "Draw.h"

class Stage;
class Draw;

class App {
    private:
        bool keyboard[MAX_KEYBOARD_KEYS];
        Stage *stage;
        Draw *drawingManager;

        App();
        ~App();
    public:
        static App& instance() {
            static App *instance_ = new App();
            return *instance_;
        }

        bool initSDL();
        void createStage();
        void setKey(int key, bool value);

        bool getKey(int key) { return keyboard[key]; }
        Stage *getStage() { return stage; }
        Draw *getDrawingManager() { return drawingManager; }
};

#endif