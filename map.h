#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "texture_manager.h"
#include "tile.h"

namespace cotw {

class Map
{
	public:
		Map();
		~Map();
		// Access with [row][column]
		std::array<std::array<sf::Drawable*, 30>, 30> tiles;
		std::array<sf::IntRect, 30> rooms;
		cotw::Texture_manager texture_manager;

		void create(bool);
		void create_rooms();
		void create_tunnels();
		void fill_empty();
		void create_room(sf::IntRect, int);
		void create_tunnel(sf::IntRect, sf::IntRect, int);
		void create_h_tunnel(int, int, int, int);
		void create_v_tunnel(sf::IntRect, sf::IntRect);

		void enter_dungeon();

		void create_random_tile(int, int, bool&, bool);
		sf::Texture random_rotate_tile(sf::Image&);
};

}

#endif
