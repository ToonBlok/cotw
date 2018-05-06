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
#include "Map.h"
#include "Player.h"

namespace cotw {

class InGameState: public cotw::GameState
{
	public:
		InGameState(cotw::GameStateManager*, sf::Vector2u);
		~InGameState();
		cotw::GameStateManager* game_state_manager;
		std::string foo = "foo";
		cotw::TextureManager texture_manager;
		std::array<cotw::Rect*, 1> ui_elements;
		cotw::Player *player;
		cotw::Map map;
		cotw::Console *console;

		bool valid_move(sf::Vector2<unsigned int>);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void update(sf::RenderWindow&);
		void handle_key(sf::RenderWindow&, sf::Event);
		void on_notify(cotw::Event);

		void change_state(cotw::GameStateManager*, cotw::State);
};

}

#endif
