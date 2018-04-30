#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

namespace cotw {

class Drawable: public sf::Drawable
{
	public:
		Drawable() {};
		~Drawable() {};

		virtual void draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const { render_target.draw(sprite, render_states); } ;
		virtual void update() = 0;
		virtual void set_texture(sf::Texture& _texture) { texture = _texture; };
		virtual void set_position(sf::Vector2f coordinates) { sprite.setPosition(coordinates); };
		virtual void move(sf::Vector2f coordinates) { sprite.move(coordinates); };
		virtual sf::Vector2f get_position() const { return sprite.getPosition(); };

	protected:
		sf::Sprite sprite;
		sf::Texture texture;
};

}

#endif
