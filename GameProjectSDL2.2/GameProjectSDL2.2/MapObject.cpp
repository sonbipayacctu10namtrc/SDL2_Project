#include "MapObject.h"

MapObject::MapObject(std::string path) {
	this->path = path;
}

void MapObject::add() {
	file.open(path.c_str());
	file >> time;
	file.ignore();
	SDL_FPoint position;
	char kindOfObject;
	for (size_t row = 0; row < 25; ++row)
	{
		position.y = 150 + (row * 20);
		for (size_t col = 0; col < 50; ++col)
		{
			position.x = 0 + (col * 16);
			file.get(kindOfObject);
			SDL_FRect object = { position.x, position.y, 0, 0 };
			if (isdigit(kindOfObject)) {

				switch (kindOfObject) {
				case '1':
					object.w = 20;
					object.h = 20;
					break;
				case '2':
					object.w = 40;
					object.h = 40;
					break;
				case '3':
					object.w = 80;
					object.h = 80;
					break;
				case '4':
					object.w = 20;
					object.h = 20;
					break;
				case '5':
					object.w = 40;
					object.h = 40;
					break;
				case '6':
					object.w = 80;
					object.h = 80;
					break;
				}
				std::pair<char, SDL_FRect> p = std::make_pair(kindOfObject, object);
				m_board.push_back(p);

			}
			else if (kindOfObject == '#') {

				object.w = 20;
				object.h = 20;
				std::pair<char, SDL_FRect> p = std::make_pair(kindOfObject, object);
				m_board.push_back(p);
			}
			else if (kindOfObject == 'B') {
				object.w = 40;
				object.h = 40;
				std::pair<char, SDL_FRect> p = std::make_pair(kindOfObject, object);
				m_board.push_back(p);
			}
			else if (kindOfObject == '?') {
				object.w = 30;
				object.h = 30;
				std::pair<char, SDL_FRect> p = std::make_pair(kindOfObject, object);
				m_board.push_back(p);
			}
		}

		file.get(kindOfObject); // for /n
	}
}

void MapObject::deleteMember(int x) {
	m_board.erase(m_board.begin() + x);
}

void MapObject::close() {
	file.close();
}

std::vector<std::pair<char, SDL_FRect>> MapObject::getBoard() {
	return m_board;
}

int MapObject::getTime() {
	return time;
}

int MapObject::getSizeOfBoard() {
	return m_board.size();
}
