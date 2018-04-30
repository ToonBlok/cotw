#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Map.h"
#include "Player.h"
#include "items/Item.h"
#include "screens/MainMenu.h"
#include "screens/Console.h"
#include "screens/Rect.h"
#include "screens/Button.h"
#include "ISubject.h"
#include "IObserver.h"
#include "MainMenuState.h"


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
		cotw::TextureManager texture_manager;
		cotw::Map map;
		cotw::Console *console;
		std::array<sf::Drawable*, 1> ui_elements;
		game_state state = game_state::MAIN_MENU;
		cotw::GameState* gstate;

		void setup();
		int game_loop();
		void set_state(cotw::GameState*);
		void handle_key(sf::Event);
		bool valid_move(sf::Vector2<unsigned int>);
		void notify(sf::Event);
		void add_observer(IObserver*);
		void remove_observer();
};

}
#endif
