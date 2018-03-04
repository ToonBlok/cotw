#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "player.h"

namespace cotw {

struct Point
{
	float x;
	float y;

	Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

class Game
{
	const std::string filename_texture_grass = "textures/tile_grass.png";
	const std::string filename_texture_hero = "textures/entity_hero.png";

	public:
		Game();
		~Game();
	private:
        sf::RenderWindow window;
		sf::Image img_tile_grass;
		sf::Image img_hero;
		std::vector<sf::Drawable*> entities;
		//cotw::Player *player;
		cotw::Player *player;


		void handle_key(sf::Event);
		void make_map(int, int);
		void setup();
		int game_loop();
};

}
#endif
