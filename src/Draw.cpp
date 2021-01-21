#include "Draw.h"

Draw::Draw() {
	textureCache.clear();
}

Draw::~Draw() {
	clearTextureCache();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Draw::initialize() {
	if (!setWindow(SDL_CreateWindow("SPACE CRIMINALS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN))) {
        printf("Failed to open window: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (!setRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	return true;
}

bool Draw::setWindow(SDL_Window *window) {
    this->window = window;
    return this->window != nullptr;
}

bool Draw::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
    return this->renderer != nullptr;
}

void Draw::clearScene() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Draw::renderScene() {
	SDL_RenderPresent(renderer);
}

void Draw::clearTextureCache() {
	std::map <std::string, SDL_Texture*> :: iterator it;
	for (it = textureCache.begin(); it != textureCache.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	textureCache.clear();
}

SDL_Texture *Draw::addTextureToCache(std::string filename) {

	SDL_Texture *texture = IMG_LoadTexture(renderer, ("graphics/"+filename).c_str());
	if (!texture) {
		printf("Error: %s\n", IMG_GetError());
	}

	textureCache.insert(std::pair<std::string, SDL_Texture*>(filename, texture));

	return texture;
}

Texture *Draw::loadTexture(const char *filename) {

	// searches for texture in cache, if not found loads from disk
	
	Texture *texture = new Texture;

	std::string strFilename;
	strFilename.assign(filename);

	std::map <std::string, SDL_Texture*> :: iterator it;
	it = textureCache.find(strFilename);

	if (it != textureCache.end()) {
		texture->image = it->second;
	} else {
		printf("Loading %s from disk... ", filename);
		texture->image = addTextureToCache(strFilename);
		if (texture->image) printf("Done\n");
	}

	// get image width and height and store it in SDL_Rect
	SDL_QueryTexture(texture->image, NULL, NULL, &(texture->rect.w), &(texture->rect.h));
	
	return texture;
}

void Draw::blit(Texture *texture, int x, int y, SDL_Rect *clip) {
	
	texture->rect.x = x;
	texture->rect.y = y;

	if (clip != NULL) {
		texture->rect.w = clip->w;
		texture->rect.h = clip->h;
	}
	
	SDL_RenderCopy(renderer, texture->image, clip, &(texture->rect));
}