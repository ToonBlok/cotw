#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "map.h"
#include "player.h"
#include "items/item.h"
#include "screens/main_menu.h"

namespace cotw {

enum class game_state { GAME, GAME_SETUP, MAIN_MENU };

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

		game_state state = game_state::MAIN_MENU;
		void handle_key(sf::Event);
		bool valid_move(sf::Vector2<unsigned int>);
		int game_loop();

		void setup();
};

}
#endif
