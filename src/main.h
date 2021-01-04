#ifndef _MAIN_H_DEFINED_
#define _MAIN_H_DEFINED_

#include "App.h"
#include "Entity.h"
#include "Player.h"
#include "draw.h"

extern void initSDL();
extern void cleanup();

extern void doInput();

Player player;
Entity bullet;

#endif