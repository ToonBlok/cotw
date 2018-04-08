#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../cotw_drawable.h"

namespace cotw {

enum class button_state { PRESSED, NORMAL };

class Button: public cotw_drawable
{
	public:
		Button(sf::Texture&, std::string, sf::Vector2f, unsigned int, unsigned int);
		~Button();

		int x;
		int y;
		int width;
		int height;
		sf::Text text;
		sf::Font font;
		button_state state = button_state::NORMAL;
		

		void update(int, int);
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void set_texture(sf::Texture&);
		void overlay_texture(sf::Image&);

};

}

#endif
