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
	const std::string filename_texture_plant1 = "textures/tile_plant1.png";
	const std::string filename_texture_plant2 = "textures/tile_plant2.png";
	const std::string filename_texture_plant3 = "textures/tile_plant3.png";
	const std::string filename_texture_plant4 = "textures/tile_plant4.png";
	const std::string filename_texture_plant5 = "textures/tile_plant5.png";
	const std::string filename_texture_plant6 = "textures/tile_plant6.png";
	const std::string filename_texture_tree_p1 = "textures/tile_tree_p1.png";
	const std::string filename_texture_tree_p2 = "textures/tile_tree_p2.png";
	const std::string filename_texture_tree_p3 = "textures/tile_tree_p3.png";
	const std::string filename_texture_tree_p4 = "textures/tile_tree_p4.png";
	const std::string filename_texture_hole = "textures/tile_hole2.png";
	const std::string filename_texture_hero = "textures/entity_hero.png";

	public:
		Game();
		~Game();
	private:
        sf::RenderWindow window;
		//sf::Image img_tile_plant1;
		//sf::Image img_tile_plant2;
		//sf::Image img_tile_grass;
		//sf::Image img_tile_hole;
		sf::Image img_hero;
		std::vector<sf::Drawable*> entities;
		std::vector< std::vector<sf::Drawable*> > entitiesf;
		//cotw::Player *player;
		cotw::Player *player;


		void handle_key(sf::Event);
		void make_map(int, int);
		void setup();
		bool valid_move(sf::Vector2f);
		cotw::Tile* create_tile(int, int);
		void get_texture(sf::Texture&, std::string);
		sf::Texture random_rotate_tile(sf::Image&);
		int game_loop();
};

}
#endif
