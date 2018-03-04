#ifndef TILE_H
#define TILE_H

#include "entity.h"

namespace cotw {

class Tile: public Entity 
{
	public:
		Tile(sf::Texture, int, int, int, int);
		~Tile();

		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture);
};

}

#endif
