#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Drawable.h"
#include "TextureManager.h"
#include "screens/Rect.h"
#include "screens/Button.h"
//#include "InGameState.h"
//#include "GameStateManager.h"

namespace cotw {

class MainMenuState: public cotw::GameState
{
	public:
		MainMenuState(cotw::GameStateManager*);
		~MainMenuState();
		cotw::GameStateManager* game_state_manager;
		std::string foo = "foo";
		cotw::TextureManager texture_manager;
		std::array<cotw::IObserver*, 3> ui_elements;
		sf::Sprite background;
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void update(sf::RenderWindow&);
		void handle_key(sf::RenderWindow&, sf::Event);
		void on_notify(sf::Event);

		void handle_events();
		void init();
		void cleanup();
		void pause();
		void resume();
		void change_state(cotw::GameStateManager*, cotw::GameState*);
};

}

#endif
