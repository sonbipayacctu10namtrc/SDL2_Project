#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

class MapObject
{
private:
	int time;
	std::vector<std::pair<char, SDL_FRect>> m_board;
	std::string path;
	std::ifstream file;
public:
	MapObject() {}
	MapObject(std::string path);

	void add();

	void close();

	void deleteMember(int x);

	std::vector<std::pair<char, SDL_FRect>> getBoard();

	int getTime();

	int getSizeOfBoard();
};

