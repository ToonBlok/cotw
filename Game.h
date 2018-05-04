#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Map.h"
#include "Player.h"
#include "items/Item.h"
#include "Input.h"
#include "GameStateManager.h"

//#include "screens/MainMenu.h"
//#include "screens/Console.h"
//#include "screens/Rect.h"
//#include "screens/Button.h"
//#include "ISubject.h"
//#include "IObserver.h"
//#include "GameState.h"
//#include "MainMenuState.h"
//#include "InGameState.h"


namespace cotw {

enum class game_state { GAME, GAME_SETUP, MAIN_MENU };

class Game//: public cotw::ISubject
{

	public:
		Game();
		~Game();

	private:
        sf::RenderWindow window;
		cotw::Player *player;
		cotw::TextureManager texture_manager;
		cotw::Map map;
		//cotw::Console *console;
		std::array<cotw::Drawable*, 1> ui_elements;
		game_state state = game_state::MAIN_MENU;
		//cotw::GameState* gstate;
		std::vector<cotw::GameState*> states;
		cotw::Input input;
		cotw::GameStateManager *game_state_manager;

		void setup();
		int game_loop();
		void handle_key(sf::Event);
		bool valid_move(sf::Vector2<unsigned int>);

		//void notify(sf::Event);
		//void add_observer(IObserver*);
		//void remove_observer();
		
		void draw(sf::RenderTarget&, sf::RenderStates render_states) ;//const;
		void update();
		void handle_events();
};

}
#endif
