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

void Tile::update(int a, int b)
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

void Tile::overlay_texture(sf::Image& new_img)
{
	sf::Image tile_img = texture.copyToImage();
	sf::IntRect a;
	tile_img.copy(new_img, 0, 0, a, true);

	sf::Texture new_tex;

	if (!new_tex.loadFromImage(tile_img))
		cout << "texture was not found!" << endl; 

	texture = new_tex;
}

}
