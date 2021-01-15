#include "Draw.h"

Draw::Draw() {
	cacheSize = cachePointer = 0;
}

Draw::~Draw() {}

bool Draw::setWindow(SDL_Window *window) {
    this->window = window;
    return this->window != nullptr;
}

bool Draw::setRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
    return this->renderer != nullptr;
}

void Draw::prepareScene() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Draw::presentScene() {
	SDL_RenderPresent(renderer);
}

void Draw::addCacheIndex(const char *filename, int index) {
	cacheNode node;
	node.filename.assign(filename);
	node.index = index;
	
	int i = 0;
	while ((i < cacheSize) && (textureCacheTable[i].filename < node.filename)) {
		i++;
	}
	for (int j = cacheSize - 1; j >= i; j--) { 
		textureCacheTable[j+1] = textureCacheTable[j]; 
	}
	textureCacheTable[i] = node;
}

void Draw::removeFromCache(int index) {
	// delete table entry
	int i = 0;
	while (textureCacheTable[i].index != index) {
		i++;
	}
	for (int j = i; j < cacheSize - 1; j++) {
		textureCacheTable[j] = textureCacheTable[j+1];
	}
	cacheSize--;
}

SDL_Texture *Draw::addTextureToCache(const char *filename) {
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);

	if (cacheSize < TEXTURE_CACHE_SIZE) {
		cacheSize++;
	} else {
		removeFromCache(cachePointer);
	}
	addCacheIndex(filename, cachePointer);
	textureCache[cachePointer] = texture;
	if (++cachePointer == TEXTURE_CACHE_SIZE) cachePointer = 0;
	
	return texture;
}

int Draw::searchTexture(const char *filename) {
	int l = 0;
	int r = cacheSize - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;

		int compare = textureCacheTable[m].filename.compare(filename);
		if (compare == 0) {
			return textureCacheTable[m].index;
		}
		if (compare < 0) {
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	return -1;
}



Texture *Draw::loadTexture(const char *filename) {
	
	Texture *texture = new Texture;

	int index = searchTexture(filename);
	if (index != -1) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s from cache", filename);
		texture->image = getTextureFromCache(index);
	} else {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s from disk", filename);
		texture->image = addTextureToCache(filename);
	}

	// get image width and height and store it in SDL_Rect
	SDL_QueryTexture(texture->image, NULL, NULL, &(texture->rect.w), &(texture->rect.h));
	
	return texture;
}

void Draw::blit(Texture *texture, int x, int y) {
	
	texture->rect.x = x;
	texture->rect.y = y;
	
	SDL_RenderCopy(renderer, texture->image, NULL, &(texture->rect));
}