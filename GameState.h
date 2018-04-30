#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

namespace cotw {

class GameState: public sf::Drawable
{
	public:
		GameState() {};
		~GameState() {};
		virtual void draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const { /*render_target.draw(sprite, render_states);*/ } ;
		virtual void update() = 0;
};

}

#endif
