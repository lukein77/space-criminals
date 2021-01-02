#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include "common.h"
#include "App.h"

namespace draw {
    extern void prepareScene();
    extern void presentScene();
    extern SDL_Texture *loadTexture(const char *filename);
    extern void blit(SDL_Texture *texture, int x, int y);
}

#endif