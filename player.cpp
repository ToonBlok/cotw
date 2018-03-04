#include <iostream>
#include "player.h"

using namespace std;

namespace cotw {

Player::Player() {}

Player::Player(sf::Texture _texture, int _x, int _y, int _width, int _height) 
{
	width = _width;
	height = _height;
	texture = _texture;

	sprite.setPosition(sf::Vector2f(_x, _y)); 
	sprite.setTexture(texture);
}

Player::~Player(){}

void Player::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite);
}

void Player::set_texture(sf::Texture _texture)
{
	// If this is really a texture then:
	// if ...?
	texture = _texture;
	sprite.setTexture(texture);
}

}
