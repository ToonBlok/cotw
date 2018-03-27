#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "map.h"
#include "player.h"
#include "item.h"

namespace cotw {

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
		bool valid_move(sf::Vector2<unsigned int>);
		int game_loop();

		void setup();
};

}
#endif
