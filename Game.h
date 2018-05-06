#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Map.h"
#include "Player.h"
#include "items/Item.h"
#include "Input.h"
#include "GameStateManager.h"

namespace cotw {

//enum class game_state { GAME, GAME_SETUP, MAIN_MENU };

class Game
{

	public:
		Game();
		~Game();

	private:
        sf::RenderWindow window;
		cotw::TextureManager texture_manager;
		cotw::Map map;
		std::array<cotw::Drawable*, 1> ui_elements;
		//cotw::Input input;
		cotw::GameStateManager *game_state_manager;

		void game_loop();
		bool valid_move(sf::Vector2<unsigned int>);
		void draw(sf::RenderTarget&, sf::RenderStates render_states) ;//const;
		void update();
};

}
#endif
