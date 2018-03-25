#include "tile.h"

using namespace std;

namespace cotw {

Tile::Tile(sf::Texture& _texture, int _x, int _y, bool _blocking)
{
	texture = _texture;
	blocking = _blocking;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(_x, _y)); 
}


Tile::~Tile(){}

void Tile::update()
{

}

void Tile::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite, render_states);
}


void Tile::set_texture(sf::Texture& _texture)
{
	// If this is really a texture then:
	// if ...?
	texture = _texture;
}

}
