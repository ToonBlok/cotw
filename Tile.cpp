#include "Tile.h"

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

void Tile::update() {}

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
