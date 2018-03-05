#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

namespace cotw {

class Entity: public sf::Drawable
{
	public:
		Entity() {};
		~Entity() {};

		virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
		virtual void set_texture(sf::Texture) = 0;
		virtual void set_position(sf::Vector2f coordinates) { sprite.setPosition(coordinates); };
		virtual sf::Vector2f get_position() const { return sprite.getPosition(); };
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
};

}

#endif
