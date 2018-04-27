#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "rect.h"

namespace cotw {

class Console: public cotw::Rect
{
	public:
		Console(sf::Texture&, std::string, sf::Vector2f, unsigned int, unsigned int);
		~Console();

		std::array<sf::Text, 6> texts;
		sf::Font font;
		std::vector<std::string> messages;

		void update();
		void log(std::string, sf::Color);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);
		//void on_notify(sf::Event);
		void notify(sf::Event);
		void add_observer(IObserver*);
		void remove_observer();
};

}

#endif
