#include <iostream>
#include "tile.h"

using namespace std;

namespace cotw {

Tile::Tile(sf::Texture _texture, int _x, int _y)
{
	texture = _texture;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(_x, _y)); 
}


Tile::~Tile(){}

void Tile::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite);
}

void Tile::set_texture(sf::Texture _texture)
{
	// If this is really a texture then:
	// if ...?
	texture = _texture;
}

}
