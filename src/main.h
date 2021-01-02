#ifndef _MAIN_H_DEFINED_
#define _MAIN_H_DEFINED_

#include "App.h"
#include "Entity.h"
#include "Player.h"
#include "draw.h"

extern void initSDL();
extern void cleanup();

extern void prepareScene();
extern void presentScene();
extern SDL_Texture *loadTexture(const char *filename);
extern void blit(SDL_Texture *texture, int x, int y);

extern void doInput();

Player player;
Entity bullet;

#endif