#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>



void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);

SDL_Renderer* createRenderer(SDL_Window* window);

void renderTexture(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer);

void renderText(SDL_Renderer* renderer, float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);

void imagerotated(SDL_Texture* img, SDL_Renderer* renderer, int x, int y, double angle);

void imagerotatedF(SDL_Texture* img, SDL_Renderer* renderer, double x, double y, double angle);

void clearWin(SDL_Window* window, SDL_Renderer* renderer);

void freeTexture(SDL_Texture* tex);





