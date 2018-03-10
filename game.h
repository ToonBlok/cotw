#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "player.h"
#include "texture_manager.h"

namespace cotw {

class Game
{

	public:
		Game();
		~Game();
	private:
		std::vector<sf::Texture> TEXTURES;
        sf::RenderWindow window;
		sf::Image img_hero;
		std::vector< std::vector<sf::Drawable*> > entities;
		sf::Drawable* tiles [30][30];
		cotw::Player *player;
		cotw::Texture_manager texture_manager;

		void handle_key(sf::Event);
		void enter_dungeon();
		void make_map(bool);
		void setup();
		bool valid_move(sf::Vector2<int>);
		void create_random_tile(int, int, bool&, bool);
		sf::Texture random_rotate_tile(sf::Image&);
		int game_loop();
};

}
#endif
