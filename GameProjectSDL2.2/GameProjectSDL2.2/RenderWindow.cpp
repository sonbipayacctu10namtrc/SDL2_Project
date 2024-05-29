#include "RenderWindow.h"

void logErrorAndExit(const char* msg, const char* error)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
	SDL_Quit();
}


SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logErrorAndExit("SDL_Init", SDL_GetError());

	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//full screen
	//window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		logErrorAndExit("SDL_image error:", IMG_GetError());

	if (TTF_Init() == -1)
		logErrorAndExit("SDL_ttf error:", TTF_GetError());
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		logErrorAndExit("SDL_ttf error:", Mix_GetError());
	return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	//Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
	//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

	if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return renderer;
}

void renderTexture(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer) {
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

void renderText(SDL_Renderer* renderer, float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}



void imagerotated(SDL_Texture* img, SDL_Renderer* renderer, int x, int y, double angle) {
	SDL_Rect destR = { x, y, 0, 0 };
	SDL_QueryTexture(img, NULL, NULL, &destR.w, &destR.h);
	destR.w /= 1.5;
	destR.h /= 1.5;
	SDL_Point ss = { destR.w / 2, 0 };
	SDL_RenderCopyEx(renderer, img, NULL, &destR, angle, &ss, SDL_FLIP_NONE);

}

void imagerotatedF(SDL_Texture* img, SDL_Renderer* renderer, double x, double y, double angle) {
	SDL_Rect destR = { 5, 5, 0, 0 };
	SDL_QueryTexture(img, NULL, NULL, &destR.w, &destR.h);
	destR.w /= 1.5;
	destR.h /= 1.5;
	SDL_FRect destRF = { x , y, (double)destR.w, (double)destR.h };
	SDL_FPoint ss = { 1.0 * destR.w / 2, 0 };
	SDL_RenderDrawRectF(renderer, &destRF);

	SDL_RenderCopyExF(renderer, img, NULL, &destRF, angle, &ss, SDL_FLIP_NONE);
	//std::cout << x << ' ' << y << std::endl;
}

void clearWin(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
}

void freeTexture(SDL_Texture* tex) {
	SDL_DestroyTexture(tex);
	tex = nullptr;
}
