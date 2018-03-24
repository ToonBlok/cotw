#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "cotw_drawable.h"

namespace cotw {

class Tile: public cotw_drawable 
{
	public:
		Tile(sf::Texture, int, int, bool);
		~Tile();

		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture);
};

}

#endif
