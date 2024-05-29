#pragma once
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include <iostream>

enum class STATUS {
	Home_Menu,
	Summary_Menu,
	Play,
	Game_Over,
	QUIT
};

std::vector<std::string> path = { "Images/HomeMenu.png",
								"Images/LevelBackground.png",
								"Images/SummaryMenu.png",
								"Images/diaBg.png",
								"D:/ConsoleApplication1/img/hook.png",
								"Images/PlayerMining.png" ,
								"D:/ConsoleApplication1/img/line.png" ,
								"Images/GoldenRock.png" ,
								"Images/RegularRock.png" ,
								"Images/DiamondRock.png" ,
								"Images/ExitButton.png" ,
								"Images/MuteButton.png" ,
								"Images/UnmuteButton.png" ,
								"Images/PauseButton.png" ,
								"Images/ResumeButton.png" ,
								"Images/SinglePlayer.png" ,
								"Images/light.png" ,
								"Images/Clock.png",
								"Images/Coin.png",
								"Images/GameOverBack.png"
};

const int numOfPath = 20;

std::vector<SDL_Texture*> texture(numOfPath);

enum namePic {
	HOMEMENU,
	LEVELBACKGROUND,
	SUMMARYMENU,
	GAMEOVERMENU,
	HOOK,
	PLAYER,
	LINE,
	GOLD,
	ROCK,
	DIAMOND,
	EXITBUTTON,
	MUTEBUTTON,
	UNMUTEBUTTON,
	PAUSEBUTTON,
	RESUMEBUTTON,
	SINGLEPLAYERBTN,
	LIGHT,
	CLOCK,
	COIN,
	GAMEOVERBACK
};

std::vector<SDL_Color> color = { {0x21, 0xd0, 0x1d}, { 255, 255, 0 }, { 0, 0, 0 } };

enum colorType {
	GREEN,
	YELLOW,
	BLACK
};

//map loading

std::vector<std::string> map = { "Levels/Level1.txt",
								 "Levels/Level2.txt",
								 "Levels/Level3.txt"};

const int numOfMap = 3;

enum mapLevel {
	Level1,
	Level2,
	Level3
};

std::vector<SDL_Rect> buttonHCN = { { /*SCREEN_WIDTH / 2*/ 400, 300, 50, 50 },
									{ 745, 20, 45, 45 },
									{ /*SCREEN_WIDTH / 2*/ 400 + 30, 300, 50, 50 },
									{ 700, 20, 45, 45 },
									{ 775, 10, 25, 25 },
									{ 450, 80, 50, 50 },
									{ 100, 170, 410 / 5 * 2, 410 / 5 * 2 },
									{ 675, 0, 100, 129 / 3 },
									{ 10, 10, 10, 10},
									{ 300, 300, 300, 200}
};

const int numOfButtonRect = 8;

enum ButtonType {
	RquitButton,
	RquitButton_HomeMenu,
	RMusicButton,
	RMusicButton_HomeMenu,
	RPauseButton,
	RResumeButton,
	RSinglePlayerBtn,
	RClock,
	Coin,
	RGameOverBack
};

//SDL_Rect RquitButton = { SCREEN_WIDTH / 2, 300, 50, 50 };
//SDL_Rect RquitButton_HomeMenu = { 745, 20, 45, 45 };
//SDL_Rect RMusicButton = { SCREEN_WIDTH / 2 + 30, 300, 50, 50 };
//SDL_Rect RMusicButton_HomeMenu = { 700, 20, 45, 45 };
//SDL_Rect RPauseButton = { 775, 10, 25, 25 };
//SDL_Rect RResumeButton = { 450, 80, 50, 50 };
//SDL_Rect RSinglePlayerBtn = { 100, 170, 410 / 2.5, 410 / 2.5 };
//SDL_Rect RClock = { 675, 0, 100, 129 / 3 };