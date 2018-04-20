#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../drawable.h"

namespace cotw {

enum class rect_state { PRESSED, NORMAL };

class Rect: public cotw::Drawable
{
	public:
		Rect(sf::Texture&, std::string, sf::Vector2f, unsigned int, unsigned int);
		~Rect();

		int x;
		int y;
		int width;
		int height;
		sf::Text text;
		sf::Font font;
		

		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);
};

}

#endif
