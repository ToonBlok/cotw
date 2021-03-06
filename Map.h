#ifndef MAP_H
#define MAP_H

#include <algorithm>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <vector>

namespace cotw {

enum class tile_clusters { tree, thintree, grassfield, log };

class Map
{
	public:
		Map();
		~Map();
		// Access with [row][column]
		std::array<std::array<cotw::Drawable*, 90>, 90> tiles;
		// Room left = room.row, room.right = room.column
		std::array<sf::IntRect, 10> rooms;
		cotw::TextureManager texture_manager;

		void create(bool);
		void create_rooms();
		void create_room(sf::IntRect, int);
		void fill_empty();
		void overlay_special_tiles();
		void create_tile_clusters(cotw::tile_clusters, std::vector<sf::IntRect>&);
		void create_thintree(sf::IntRect);
		void create_tree(sf::IntRect);
		void create_log(sf::IntRect);
		void create_grassfields();
		void create_tunnel(sf::IntRect);
		void create_h_tunnel(int, int, int);
		void create_v_tunnel(int, int, int);
		std::vector<sf::IntRect> get_unconnected_rooms();
		void enter_dungeon();
		void create_random_tile(int, int, bool&, bool);
		void flip_tile_h(sf::Texture&);
};

}

#endif
