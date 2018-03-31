#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "cotw_drawable.h"
#include "items/item.h"

namespace cotw {

class Tile: public cotw_drawable 
{
	public:
		Tile(sf::Texture&, int, int, bool);
		~Tile();

		std::vector<cotw::Item*> inventory;

		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture&);
		void overlay_texture(sf::Image&);

};

}

#endif
