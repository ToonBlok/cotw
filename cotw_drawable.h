#ifndef COTW_DRAWABLE_H
#define COTW_DRAWABLE_H

#include <SFML/Graphics.hpp>

namespace cotw {

class cotw_drawable: public sf::Drawable
{
	public:
		cotw_drawable() {};
		~cotw_drawable() {};

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
		virtual void update() = 0;
		virtual void set_texture(sf::Texture&) = 0;
		virtual void set_position(sf::Vector2f coordinates) { sprite.setPosition(coordinates); };
		virtual void move(sf::Vector2f coordinates) { sprite.move(coordinates); };
		virtual sf::Vector2f get_position() const { return sprite.getPosition(); };

		bool blocking = false;
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
};

}

#endif
