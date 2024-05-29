#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <string>
#include <utility>
#include "RenderWindow.h"
#include "stat.h"
#include "MapObject.h"
#include "HomeMenu.h"
#include "mouseInside.h"

#define PI 3.14159

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Gold Miner!";

const double MAX_ANGLE = 60;
const int MAX_RANGE_CAN_REACH = 50;
const double HOOK_SPAWN = 80;

const int WALKING_ANIMATION_FRAMES = 7;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

bool loadCharacter() {
	bool success = true;
	for (int i = 0; i < 7; ++i) {
		gSpriteClips[i].x = 80 * i;
		gSpriteClips[i].y = 0;
		gSpriteClips[i].w = 80;
		gSpriteClips[i].h = 120;
	}

	return success;
}

bool mouseInside(SDL_Point mouse, SDL_Rect area)
{
	if (mouse.x >= area.x && mouse.x <= area.x + area.w && mouse.y >= area.y && mouse.y <= area.y + area.h)
		return true;
	return false;
}

bool checkCollision(SDL_FRect a, SDL_Rect b) {
	float leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}
	return true;
}


int main(int argc, char* args[]) {

	SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	SDL_Renderer* renderer = createRenderer(window);

	for (int i = 0; i < numOfPath; ++i) {
		texture[i] = loadTexture(path[i].c_str(), renderer);
	}
	//TTF_Font* gameFont = NULL;

	TTF_Font* font32 = TTF_OpenFont("Font/Font.ttf", 32);
	TTF_Font* font60 = TTF_OpenFont("Font/Font.ttf", 60);
	TTF_Font* font48 = TTF_OpenFont("Font/Font.ttf", 48);
	TTF_Font* font24 = TTF_OpenFont("Font/Font.ttf", 24);

	Mix_Music* musik = Mix_LoadMUS("Sounds/BackgroundMusic.ogg");

	SDL_Event e;
	bool quit = false;
	double angle = 0;
	bool m_direction = true;
	bool isReleased = false;
	float mVel = 3;
	//int xm = w, ym = h;
	float xmf1 = 1.0 * SCREEN_WIDTH / 2 /*- w*/, ymf1 = (float)HOOK_SPAWN;
	float xmf = xmf1, ymf = ymf1;
	//std::cout << w << ' ' << h << std::endl;
	bool nonee = false;
	int frame = 0;
	bool character = loadCharacter();
	bool grab = false;
	bool paused = false;
	bool win = false;
	STATUS status = STATUS::Home_Menu;
	mapLevel mapLevel = mapLevel::Level1;
	int z = -1;
	Uint32 time = -1;
	Uint32 tmp;
	int point = 0;
	int timeInFile = 0;

	MapObject mapLoad(map[Level1]);
	mapLoad.add();
	MapObject mapLoad2(map[Level2]);
	mapLoad2.add();
	MapObject mapLoad3(map[Level3]);
	mapLoad3.add();

	std::vector<std::pair<char, SDL_FRect>> map1 = mapLoad.getBoard();
	map1 = mapLoad.getBoard();
	timeInFile = mapLoad.getTime();

	Mix_PlayMusic(musik, -1);

	//HomeMenu HomeMenu;

	std::string s = "";
	std::string pts = "";

	bool mouseOver = false;

	while (!quit) {
		switch (status) {
		case STATUS::Home_Menu:
			//HomeMenu.handleHomeMenu(e, quit, status);
			while (SDL_PollEvent(&e)) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				SDL_Point mouse = { x, y };
				switch (e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (e.button.button == SDL_BUTTON_LEFT) {

						if (mouseInside(mouse, buttonHCN[RquitButton_HomeMenu])) {
							quit = true;
						}
						if (mouseInside(mouse, buttonHCN[RMusicButton_HomeMenu])) {
							if (Mix_PausedMusic() == 1) {
								Mix_ResumeMusic();
							}
							else {
								Mix_PauseMusic();
							}
						}
						if (mouseInside(mouse, buttonHCN[RSinglePlayerBtn])) {
							status = STATUS::Summary_Menu;
							/*SDL_DestroyTexture(texture[LIGHT]);
							SDL_DestroyTexture(texture[HOMEMENU]);
							SDL_DestroyTexture(texture[SINGLEPLAYERBTN]);*/
						}
					}
					break;
				case SDL_MOUSEMOTION:
					if (mouseInside(mouse, buttonHCN[RSinglePlayerBtn])) {
						mouseOver = true;
					}
					else mouseOver = false;
					break;
				}
			}
			//HomeMenu.draw(renderer, texture, musicButton);
			SDL_RenderClear(renderer); //clear screen

			SDL_RenderCopy(renderer, texture[HOMEMENU], nullptr, nullptr);
			SDL_RenderCopy(renderer, texture[SINGLEPLAYERBTN], nullptr, &buttonHCN[RSinglePlayerBtn]);

			SDL_RenderCopy(renderer, texture[EXITBUTTON], nullptr, &buttonHCN[RquitButton_HomeMenu]);
			if (Mix_PausedMusic() == 1)
				SDL_RenderCopy(renderer, texture[UNMUTEBUTTON], nullptr, &buttonHCN[RMusicButton_HomeMenu]);
			else
				SDL_RenderCopy(renderer, texture[MUTEBUTTON], nullptr, &buttonHCN[RMusicButton_HomeMenu]);
			if (mouseOver)
				SDL_RenderCopy(renderer, texture[LIGHT], NULL, &buttonHCN[RSinglePlayerBtn]);
			break;

		case STATUS::Summary_Menu:
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, texture[SUMMARYMENU], nullptr, nullptr);
			switch (mapLevel) {
			case mapLevel::Level1:
				renderText(renderer, 500, 100, "1", font60, color[YELLOW]);
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 300, "Target: 5000", font60, color[BLACK]);
				map1 = mapLoad.getBoard();
				timeInFile = mapLoad.getTime();
				break;
			case mapLevel::Level2:
				renderText(renderer, 500, 100, "2", font60, color[YELLOW]);
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 300, "Target: 10000", font60, color[BLACK]);
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 360, "Keep going!", font60, color[BLACK]);
				map1 = mapLoad2.getBoard();
				timeInFile = mapLoad2.getTime();
				break;
			case mapLevel::Level3:
				renderText(renderer, 500, 100, "3", font60, color[YELLOW]);
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 300, "Target: 15000", font32, color[BLACK]);
				map1 = mapLoad3.getBoard();
				timeInFile = mapLoad3.getTime();
				break;
			}
			/*renderText(renderer, 500, 100, "1", font60, color[YELLOW]);
			renderText(renderer, SCREEN_WIDTH / 2 - 150, 300, "Target: 1000", font32, color[BLACK]);*/

			SDL_RenderPresent(renderer);
			status = STATUS::Play;

			SDL_Delay(2000);

			//SDL_DestroyTexture(summaryMenu);
			//summaryMenu == nullptr;

			break;

		case STATUS::Play:
			if (time == -1) time = SDL_GetTicks();

			tmp = (Uint32)timeInFile * 1000 + time - SDL_GetTicks();
			while (SDL_PollEvent(&e)) {
				//just handle event , don't resolve any logic here
				if (e.type == SDL_QUIT) quit = true;
				else if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
					case SDLK_DOWN:
						isReleased = true;
						break;
					}
				}
				else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					SDL_Point mouse = { x, y };
					if (e.button.button == SDL_BUTTON_LEFT) {
						if (mouseInside(mouse, buttonHCN[RquitButton])) {
							quit = true;
						}
						if (mouseInside(mouse, buttonHCN[RMusicButton])) {
							if (Mix_PausedMusic() == 1) {
								Mix_ResumeMusic();
							}
							else {
								Mix_PauseMusic();
							}

						}
						if (mouseInside(mouse, buttonHCN[RPauseButton])) {
							paused = true;

						}
						if (mouseInside(mouse, buttonHCN[RResumeButton])) {
							paused = false;

						}
						if (mouseInside(mouse, buttonHCN[RHomeButton]))
							status = STATUS::Home_Menu;

					}
				}
			}


			if ((int)tmp < 0) {
				//if (!map1.size()) break;
				switch (mapLevel) {
				case mapLevel::Level1:
					if (point < 5000) {
						status = STATUS::Game_Over;
						break;
					}
					else {
						status = STATUS::Summary_Menu;
						time = -1;
						mapLevel = mapLevel::Level2;
						angle = 0;
						nonee = false;
						m_direction = true;
						isReleased = false;
						xmf = xmf1;
						ymf = ymf1;
					}

					break;
				case mapLevel::Level2:
					if (point < 10000) {
						status = STATUS::Game_Over;

					}
					else {
						status = STATUS::Summary_Menu;
						time = -1;
						mapLevel = mapLevel::Level3;
						angle = 0;
						nonee = false;
						m_direction = true;
						isReleased = false;
						xmf = xmf1;
						ymf = ymf1;
					}

					break;
				case mapLevel::Level3:
					if (point < 15000) {
						win = false;
					}
					else {
						win = true;
					}
					status = STATUS::Game_Over;
					break;
				}

			}
			s = std::to_string((int)tmp / 1000);
			pts = std::to_string(point);

			if (mapLevel == mapLevel::Level1) pts += " / 5000";
			else if (mapLevel == mapLevel::Level2) pts += " / 10000";
			else pts += " / 15000";


			SDL_RenderClear(renderer); //clear screen
			SDL_RenderCopy(renderer, texture[LEVELBACKGROUND], nullptr, nullptr);

			SDL_RenderCopy(renderer, texture[CLOCK], nullptr, &buttonHCN[RClock]);
			SDL_RenderCopy(renderer, texture[COIN], nullptr, &buttonHCN[RCoin]);

			renderText(renderer, 720, 0, s.c_str(), font24, color[GREEN]);

			renderText(renderer, 230, 0, pts.c_str(), font24, color[GREEN]);

			if (paused) {

				SDL_RenderCopy(renderer, texture[EXITBUTTON], nullptr, &buttonHCN[RquitButton]);
				if (Mix_PausedMusic() == 1)
					SDL_RenderCopy(renderer, texture[UNMUTEBUTTON], nullptr, &buttonHCN[RMusicButton]);
				else
					SDL_RenderCopy(renderer, texture[MUTEBUTTON], nullptr, &buttonHCN[RMusicButton]);
				SDL_RenderCopy(renderer, texture[RESUMEBUTTON], nullptr, &buttonHCN[RResumeButton]);
				SDL_RenderCopy(renderer, texture[HOMEBUTTON], nullptr, &buttonHCN[RHomeButton]);
			}
			else {
				SDL_RenderCopy(renderer, texture[PAUSEBUTTON], nullptr, &buttonHCN[RPauseButton]);
			}

			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
			//SDL_RenderDrawPoint(renderer, 410, 80);


			for (int i = 0; i < (int)map1.size(); ++i) {
				if (i == z) continue;
				if (map1[i].first == '3' || map1[i].first == '2' || map1[i].first == '1') {
					SDL_RenderCopyF(renderer, texture[GOLD], nullptr, &map1[i].second);
				}
				else if (map1[i].first == '#')
					SDL_RenderCopyF(renderer, texture[DIAMOND], nullptr, &map1[i].second);
				else if (map1[i].first == 'B')
					SDL_RenderCopyF(renderer, texture[BARREL], nullptr, &map1[i].second);
				else if (map1[i].first == '?')
					SDL_RenderCopyF(renderer, texture[SURPRISEBAG], nullptr, &map1[i].second);
				else SDL_RenderCopyF(renderer, texture[ROCK], nullptr, &map1[i].second);

			}
			//return 0;
			if (!character) {
				quit = true;
			}

			// resolve logic and update something

			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
			//SDL_RenderDrawPointF(renderer,  xmf - 57 * sin(angle * PI / 180) + 25, ymf + 32 * cos(angle * PI / 180));

			if (!isReleased) {
				if (angle == MAX_ANGLE) // most left angle
				{
					m_direction = true;
				}
				else if (angle == -MAX_ANGLE) // most right angle
				{
					m_direction = false;
				}

				if (m_direction) // move right
				{
					--angle;
				}

				else
				{
					++angle;
				}
				SDL_Rect renderQuad = { (SCREEN_WIDTH) / 2, 0, 80, 120 };
				SDL_RenderCopy(renderer, texture[PLAYER], &gSpriteClips[0], &renderQuad);
				imagerotated(texture[HOOK], renderer, SCREEN_WIDTH / 2 + 10, HOOK_SPAWN, angle);
			}
			else {
				SDL_Rect rect = { xmf - 57 * sin(angle * PI / 180) + 15, ymf + 15, 15, 15 };
				//SDL_RenderDrawRect(renderer, &rect);
				if (!nonee) {
					xmf -= mVel * sin(angle * PI / 180) * 4;
					ymf += mVel * cos(angle * PI / 180) * 4;
					for (int i = 0; i < (int)map1.size(); ++i) {
						if (checkCollision(map1[i].second, rect)) {
							nonee = true;
							grab = true;
							z = i;
							if (map1[i].first == 'B') {
								SDL_Rect bomb = { map1[i].second.x - 40, map1[i].second.y - 40, map1[i].second.w + 80, map1[i].second.h + 80 };
								for (int j = 0; j < (int)map1.size(); ++j) {
									if (checkCollision(map1[j].second, bomb) && j != i) {
										map1.erase(map1.begin() + j);
									}
								}
							}
							else if (map1[i].first == '1' || map1[i].first == '4' || map1[i].first == '#') {
								mVel = 1.5;
							}
							else if (map1[i].first == '2' || map1[i].first == '5' || map1[i].first == '?') {
								mVel = 1;
							}
							else mVel = 0.5;

							break;
						}
					}

					SDL_Rect renderQuad = { (SCREEN_WIDTH) / 2, 0, 80, 120 };
					SDL_RenderCopy(renderer, texture[PLAYER], &gSpriteClips[0], &renderQuad);

				}
				else {
					xmf += mVel * sin(angle * PI / 180) * 4;
					ymf -= mVel * cos(angle * PI / 180) * 4;
					SDL_Rect* currentClip = &gSpriteClips[frame];
					SDL_Rect renderQuad = { (SCREEN_WIDTH) / 2, 0, 80, 120 };
					SDL_RenderCopy(renderer, texture[PLAYER], &gSpriteClips[frame / WALKING_ANIMATION_FRAMES], &renderQuad);

				}
				if (xmf > SCREEN_WIDTH - 5 || ymf > SCREEN_HEIGHT - 25 || xmf < 10) {
					nonee = true;
					mVel = 3;
				}
				else if ((abs(xmf1 - xmf) < 0.01) && (abs(ymf1 - ymf) < 0.01)) {
					nonee = false;
					ymf = (float)HOOK_SPAWN;
					xmf = 1.0 * SCREEN_WIDTH / 2;
					isReleased = false;
					mVel = 3;
					grab = false;
					if (z != -1) {
						switch (map1[z].first) {
						case '1':
							point += 100;
							break;
						case '2':
							point += 200;
							break;
						case '3':
							point += 400;
							break;
						case '4':
							point += 10;
							break;
						case '5':
							point += 20;
							break;
						case '6':
							point += 30;
							break;
						case '#':
							point += 1000;
							break;
						case '?':
							int t = rand() % 3;
							switch (t) {
							case 1:
								point += 1000;
								break;
							case 2:
								point += 1500;
								break;
							case 3:
								point += 2000;
								break;
							}
						}
						map1.erase(map1.begin() + z);
						z = -1;
					}
				}
				imagerotated(texture[HOOK], renderer, (int)xmf + 10, (int)ymf, angle);
				if (z != -1) {
					SDL_FRect currentObject = { 0 /*+ 15*/, 0, map1[z].second.w, map1[z].second.h };
					if (angle < 0) {
						currentObject.x = xmf - 57 * sin(angle * PI / 180);
						currentObject.y = ymf + 15;
					}
					else {
						currentObject.x = xmf - 57 * sin(angle * PI / 180) + 15;
						currentObject.y = ymf + 15;
					}
					if (map1[z].first == '3' || map1[z].first == '2' || map1[z].first == '1') {
						SDL_RenderCopyF(renderer, texture[GOLD], nullptr, &currentObject);
					}
					else if (map1[z].first == '#')
						SDL_RenderCopyF(renderer, texture[DIAMOND], nullptr, &currentObject);
					else if (map1[z].first == 'B') {
						continue;
					}
					else if (map1[z].first == '?')
						SDL_RenderCopyF(renderer, texture[SURPRISEBAG], nullptr, &currentObject);
					else SDL_RenderCopyF(renderer, texture[ROCK], nullptr, &currentObject);
				}
				float lineLength = sqrt((SCREEN_WIDTH / 2 - xmf) * (SCREEN_WIDTH / 2 - xmf) + ymf * ymf) - 60;
				SDL_FRect lineF = { SCREEN_WIDTH / 2 - 1.5 + 30, HOOK_SPAWN, 3.0, lineLength }; // Assuming line width is 3.0
				SDL_FPoint ss = { lineF.w / 2, 0 };


				// Render the line
				SDL_RenderCopyExF(renderer, texture[LINE], NULL, &lineF, angle, &ss, SDL_FLIP_NONE);

			}
			++frame;


			if (frame / 7 >= WALKING_ANIMATION_FRAMES) {
				frame = 0;
			}

			break;

		case STATUS::Game_Over:
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) quit = true;
				else if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_RETURN:
						status = STATUS::Home_Menu;
						mapLevel = mapLevel::Level1;
						map1 = mapLoad.getBoard();
						angle = 0;
						m_direction = true;
						isReleased = false;
						point = 0;
						xmf = xmf1;
						ymf = ymf1;
						break;
					}
				}
			}
			time = -1;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture[GAMEOVERMENU], nullptr, nullptr);
			if (!win) {
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 300, "Game Over, You Lose", font32, color[BLACK]);
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 350, "Press ESC to quit", font32, color[BLACK]);
				renderText(renderer, SCREEN_WIDTH / 2 - 150, 400, "Press ENTER to play again", font32, color[BLACK]);
			}
			else {
				SDL_RenderCopy(renderer, texture[GAMEOVERBACK], nullptr, &buttonHCN[RGameOverBack]);
			}
			renderText(renderer, SCREEN_WIDTH / 2 - 150, 450, ("Score: " + std::to_string(point)).c_str(), font32, color[BLACK]);
			break;

		}
		//present
		SDL_RenderPresent(renderer);
	}

	Mix_FreeMusic(musik);
	musik = nullptr;
	for (int i = 0; i < (int)texture.size(); ++i) {
		freeTexture(texture[i]);
	}

	clearWin(window, renderer);
	//done
	return 0;
}