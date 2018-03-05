#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

namespace cotw {

class Player: public Entity
{
	public:
		Player();
		Player(sf::Texture, int, int);
		~Player();

		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture);

		int speed = 10;
};

}

#endif
