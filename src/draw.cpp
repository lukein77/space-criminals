#include "draw.h"

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(app.getRenderer());
}

void presentScene(void)
{
	SDL_RenderPresent(app.getRenderer());
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.getRenderer(), filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(app.getRenderer(), texture, NULL, &dest);
}