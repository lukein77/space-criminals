#include "Animation.h"

Animation::Animation() {
    rect.x = rect.y = 0;
    currentFrame = 0;
    frameRate = 100;
    oldTime = 0;
    frames = 0;
    repeat = false;
    finished = false;
}

Animation::Animation(const char *filename, int frames, int w, int h, bool repeat) : Animation() {
    this->frames = frames;
    this->repeat = repeat;
    setTexture(filename, w, h);
}

Animation::~Animation() {}

void Animation::update() {

    if (oldTime + frameRate <= SDL_GetTicks()) {
        if (!finished) {

            oldTime = SDL_GetTicks();

            rect.x += rect.w;

            if (rect.x >= textureSize.w) {
                rect.x = 0;
                rect.y += rect.h;
            }

            if (++currentFrame > frames) {
                if (!repeat) {
                    finished = true;
                } else {
                    currentFrame = 0;
                    rect.x = 0;
                    rect.y = 0;
                }
            }
        }
    }
}

void Animation::setFrames(int frames) {
    this->frames = frames;
}

void Animation::setX(int x) {
    this->x = x;
}

void Animation::setY(int y) {
    this->y = y;
}

void Animation::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Animation::setTexture(const char *filename, int w, int h) {
    texture = *(App::instance().getDrawingManager()->loadTexture(filename));
    rect.w = w;
    rect.h = h;
    textureSize.w = texture.rect.w;
    textureSize.h = texture.rect.h;
}