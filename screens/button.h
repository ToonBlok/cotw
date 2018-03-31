#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../texture_manager.h"

namespace cotw {

class Button: public sf::Drawable
{
	public:
		Button();
		~Button();

		void draw(sf::RenderTarget&, sf::RenderStates) const;
		sf::Image image;

};

}

#endif
