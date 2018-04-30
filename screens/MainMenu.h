#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Drawable.h"
#include "../TextureManager.h"
#include "Rect.h"
#include "Button.h"

namespace cotw {

class Main_menu: public cotw::Drawable
{
	public:
		Main_menu(sf::Vector2u);
		~Main_menu();

		cotw::TextureManager texture_manager;
		std::array<cotw::IObserver*, 1> ui_elements;
		sf::Sprite background;
		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);

};

}

#endif
