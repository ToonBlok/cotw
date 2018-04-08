#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../cotw_drawable.h"
#include "../texture_manager.h"
#include "button.h"

namespace cotw {

class Main_menu: public cotw_drawable
{
	public:
		Main_menu(sf::Vector2u);
		~Main_menu();

		cotw::Texture_manager texture_manager;
		std::array<sf::Drawable*, 3> ui_elements;
		void update(int, int);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture&);
		void overlay_texture(sf::Image&);

};

}

#endif
