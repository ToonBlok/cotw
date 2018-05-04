#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Drawable.h"
#include "TextureManager.h"
#include "screens/Rect.h"
#include "screens/Button.h"
#include "MainMenuState.h"
#include "screens/Console.h"
//#include "GameStateManager.h"

namespace cotw {

class InGameState: public cotw::GameState
{
	public:
		InGameState(cotw::GameStateManager*);
		~InGameState();
		cotw::GameStateManager* game_state_manager;
		std::string foo = "foo";
		cotw::TextureManager texture_manager;
		std::array<cotw::Rect*, 1> ui_elements;
		sf::Sprite background;
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void update(sf::RenderWindow&);
		void handle_key(sf::RenderWindow&, sf::Event);
		void on_notify(cotw::Event);

		void handle_events();
		void init();
		void cleanup();
		void pause();
		void resume();
		void change_state(cotw::GameStateManager*, cotw::GameState*);
};

}

#endif
