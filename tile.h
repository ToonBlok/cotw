#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "drawable.h"
#include "items/item.h"

namespace cotw {

class Tile: public cotw::Drawable 
{
	public:
		Tile(sf::Texture&, int, int, bool);
		~Tile();

		bool blocking = false;

		std::vector<cotw::Item*> inventory;

		void update(int, int);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);

};

}

#endif
