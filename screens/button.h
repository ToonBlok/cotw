#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "rect.h"

namespace cotw {

class Button: public cotw::Rect
{
	public:
		Button(sf::Texture&, std::string, sf::Vector2f, unsigned int, unsigned int);
		~Button();

		int width;
		int height;
		sf::Text text;
		sf::Font font;

		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);
		void notify(sf::Event);
		void add_observer();
		void remove_observer();
		//void on_notify(sf::Event);
};

}

#endif
