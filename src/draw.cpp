#include "draw.h"

void draw::prepareScene() {
	App& app = App::instance();
	SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(app.getRenderer());
}

void draw::presentScene() {
	SDL_RenderPresent(App::instance().getRenderer());
}

Texture *draw::loadTexture(const char *filename) {
	Texture *texture = new Texture;

	//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	// load SDL_Texture
	texture->image = IMG_LoadTexture(App::instance().getRenderer(), filename);
	// get image width and height and store it in SDL_Rect
	SDL_QueryTexture(texture->image, NULL, NULL, &(texture->rect.w), &(texture->rect.h));
	
	return texture;
}

void draw::blit(Texture *texture, int x, int y) {
	
	texture->rect.x = x;
	texture->rect.y = y;
	
	SDL_RenderCopy(App::instance().getRenderer(), texture->image, NULL, &(texture->rect));
}