#include "draw.h"

void draw::prepareScene() {
	App& app = App::instance();
	SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(app.getRenderer());
}

void draw::presentScene() {
	SDL_RenderPresent(App::instance().getRenderer());
}

SDL_Texture *draw::loadTexture(const char *filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(App::instance().getRenderer(), filename);

	return texture;
}

void draw::blit(SDL_Texture *texture, int x, int y) {
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(App::instance().getRenderer(), texture, NULL, &dest);
}