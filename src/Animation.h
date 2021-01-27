#ifndef _ANIMATION_H_DEFINED_
#define _ANIMATION_H_DEFINED_

#include "common.h"
#include "App.h"

class Animation {
    private:
        int x, y;                           // position on screen
        struct { int w, h; } textureSize;   // full image size
        int frames;                         // total amount of frames
        int currentFrame;
        int frameRate;                      // in milliseconds
        long oldTime;
        bool finished;           
        bool repeat;        
        SDL_Rect rect;                      // clip
        Texture texture;
    public:
        Animation();
        Animation(const char *filename, int frames, int w, int h, bool repeat=false);
        ~Animation();
        void update();
        void setTexture(const char *filename, int w, int h);
        void setFrames(int frames);
        void setFrameRate(int frameRate);
        void setX(int x);
        void setY(int y);
        void setPos(int x, int y);
        Texture *getTexture() { return &texture; }
        SDL_Rect *getClip() { return &rect; }
        int getFrames() { return frames; }
        int getCurrentFrame() { return currentFrame; }
        int getFrameRate() { return frameRate; }
        int getX() { return x; }
        int getY() { return y; }
        bool hasFinished() { return finished; }

};

#endif