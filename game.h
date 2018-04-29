#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "map.h"
#include "player.h"
#include "items/item.h"
#include "screens/main_menu.h"
#include "screens/console.h"
#include "screens/rect.h"
#include "screens/button.h"
#include "subject.h"


namespace cotw {

enum class game_state { GAME, GAME_SETUP, MAIN_MENU };

class Game: public cotw::ISubject
{

	public:
		Game();
		~Game();

	private:
        sf::RenderWindow window;
		cotw::Player *player;
		cotw::Texture_manager texture_manager;
		cotw::Map map;
		cotw::Console *console;
		std::array<sf::Drawable*, 1> ui_elements;
		game_state state = game_state::MAIN_MENU;

		void setup();
		int game_loop();
		void handle_key(sf::Event);
		bool valid_move(sf::Vector2<unsigned int>);
		void notify(sf::Event);
		void add_observer(IObserver*);
		void remove_observer();
};

}
#endif
