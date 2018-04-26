#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "rect.h"

namespace cotw {

class Console: public cotw::Drawable
{
	public:
		Console(sf::Texture&, std::string, sf::Vector2f, unsigned int, unsigned int);
		~Console();

		int x;
		int y;
		int width;
		int height;
		std::array<sf::Text, 6> texts;
		sf::Font font;
		std::vector<std::string> messages;

		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);
};

}

#endif