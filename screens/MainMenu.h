#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Drawable.h"
#include "../TextureManager.h"
#include "Rect.h"
#include "Button.h"

namespace cotw {

class MainMenu: public cotw::Drawable
{
	public:
		MainMenu(sf::Vector2u);
		~MainMenu();

		cotw::TextureManager texture_manager;
		//std::array<cotw::IObserver*, 1> ui_elements;
		sf::Sprite background;
		void update();
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void overlay_texture(sf::Image&);

};

}

#endif
