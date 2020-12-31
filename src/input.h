#ifndef _INPUT_H_INCLUDED_
#define _INPUT_H_INCLUDED_

#include "common.h"
#include "App.h"

void doInput();
void doKeyDown(SDL_KeyboardEvent *event);
void doKeyUp(SDL_KeyboardEvent *event);

#endif