#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../drawable.h"
#include "../texture_manager.h"
#include "rect.h"

namespace cotw {

class Main_menu: public cotw::Drawable
{
	public:
		Main_menu(sf::Vector2u);
		~Main_menu();

		cotw::Texture_manager texture_manager;
		std::array<sf::Drawable*, 3> ui_elements;
		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);

};

}

#endif
