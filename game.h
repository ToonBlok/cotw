#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "map.h"
#include "player.h"

namespace cotw {

struct dungeon_room
{
	int row;
	int column;
	int width; 
	int height;
};

class Game
{

	public:
		Game();
		~Game();

	private:
        sf::RenderWindow window;
		cotw::Player *player;
		cotw::Texture_manager texture_manager;
		cotw::Map map;

		void handle_key(sf::Event);
		bool valid_move(sf::Vector2<int>);
		int game_loop();

		void setup();
};

}
#endif
