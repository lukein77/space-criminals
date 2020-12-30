#ifndef _MAIN_HEADER_DEFINED_
#define _MAIN_HEADER_DEFINED_

#include "App.h"
#include "Entity.h"

extern void initSDL();
extern void cleanup();

extern void prepareScene();
extern void presentScene();
extern SDL_Texture *loadTexture(char *filename);
extern void blit(SDL_Texture *texture, int x, int y);

extern void doInput();

App app;
Entity player;

#endif