#ifndef _DRAW_H_INCLUDED_
#define _DRAW_H_INCLUDED_

#include "common.h"
#include "App.h"

namespace draw {
    extern void prepareScene();
    extern void presentScene();
    extern Texture *loadTexture(const char *filename);
    extern void blit(Texture *texture, int x, int y);
}

#endif