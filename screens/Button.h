#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rect.h"

namespace cotw {

class Button: public cotw::Rect
{
	public:
		Button(sf::Texture&, std::string, sf::Vector2f, unsigned int, unsigned int);
		~Button();

		sf::Text text;
		sf::Font font;
		bool activated = false;

		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);
		//void notify(sf::Event);
		//void add_observer(IObserver*);
		//void remove_observer();
		void on_notify(sf::Event);
};

}

#endif
