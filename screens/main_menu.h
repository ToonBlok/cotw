#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../texture_manager.h"

namespace cotw {

class Main_menu: public sf::Drawable
{
	public:
		Main_menu();
		~Main_menu();

		cotw::Texture_manager texture_manager;
		std::array<sf::Sprite, 1> ui_elements;
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		sf::Image image;

};

}

#endif
