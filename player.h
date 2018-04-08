#ifndef PLAYER_H
#define PLAYER_H

#include "cotw_drawable.h"
#include "items/item.h"

namespace cotw {

class Player: public cotw_drawable
{
	public:
		Player();
		Player(sf::Texture, int, int);
		~Player();

		std::vector<cotw::Item*> inventory;
		int speed = 32;
		int row;
		int col;

		void update(int, int);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture&);
};

}

#endif
