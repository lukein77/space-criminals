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
	if (!setWindow(SDL_CreateWindow("SPACE CRIMINALS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS))) {
        printf("Failed to open window: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (!setRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) { 
		printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
		return false;
	} else {
		defaultFont = TTF_OpenFont("graphics/PressStart2P.ttf", 18);
		smallFont = TTF_OpenFont("graphics/PressStart2P.ttf", 12);
		largeFont = TTF_OpenFont("graphics/PressStart2P.ttf", 48);
	}

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
	renderUI();
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
	} else {
		printf("Done\n");
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

void Draw::renderText(const char *text, int x, int y, SDL_Color color, int size, bool centered) {
	TTF_Font *font;
	switch (size) {
		case FONTSIZE_SMALL:
			font = smallFont;
			break;
		case FONTSIZE_LARGE:
			font = largeFont;
			break;
		default:
			font = defaultFont;
			break;
	}

	SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);

	if (surface) {
		Texture texture;
		texture.image = SDL_CreateTextureFromSurface(renderer, surface);
		texture.rect.w = surface->w;
		texture.rect.h = surface->h;

		if (centered) {
			x = x - surface->w / 2;
			y = y - surface->h / 2;
		}

		blit(&texture, x, y);
	} else {
		printf("Error rendering text: %s\n", TTF_GetError());
	}
}

void Draw::renderUI() {
	SDL_Color white = {255, 255, 255, 255};

	renderText("SCORE", 10, SCREEN_HEIGHT - 40, white, FONTSIZE_SMALL);
	int score = App::instance().getStage()->getPlayer()->getScore();
	renderText(std::to_string(score).c_str(), 10, SCREEN_HEIGHT - 24, white);
}

void Draw::renderGameOver() {
	SDL_Color white = {255, 255, 255, 255};
	renderText("GAME OVER", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, white, FONTSIZE_LARGE, true);
}