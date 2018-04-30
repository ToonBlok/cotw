#ifndef PLAYER_H
#define PLAYER_H

#include "Drawable.h"
#include "items/Item.h"

namespace cotw {

class Player: public cotw::Drawable
{
	public:
		Player();
		Player(sf::Texture&, int, int);
		~Player();

		std::vector<cotw::Item*> inventory;
		int speed = 32;
		int row;
		int col;

		void update();
};

}

#endif
