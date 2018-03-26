#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace cotw {

class Item
{
	public:
		Item(std::string, sf::Image&, bool);
		~Item();

		std::string name;
		sf::Image image;
		bool collected;
		void set_texture(sf::Texture&);

};

}

#endif
