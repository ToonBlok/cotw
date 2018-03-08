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
		cotw::Player *player;
		cotw::Texture_manager texture_manager;

		void handle_key(sf::Event);
		void make_map();
		void setup();
		bool valid_move(sf::Vector2f);
		void create_random_tile(int, int);
		void create_texture(sf::Texture&, std::string);
		sf::Texture create_texture2(std::string);
		sf::Texture random_rotate_tile(sf::Image&);
		int game_loop();
};

}
#endif
