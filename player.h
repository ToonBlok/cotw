#ifndef PLAYER_H
#define PLAYER_H

#include "cotw_drawable.h"

namespace cotw {

class Player: public cotw_drawable
{
	public:
		Player();
		Player(sf::Texture, int, int);
		~Player();

		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture&);

		int speed = 32;
		int row;
		int col;
};

}

#endif
