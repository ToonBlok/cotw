#include <iostream>
#include "player.h"

using namespace std;

namespace cotw {

Player::Player() {}

Player::Player(sf::Texture _texture, int _x, int _y) 
{
	texture = _texture;

	row = _x / 32;
	col = _y / 32;
	sprite.setPosition(sf::Vector2f(_x, _y)); 
	sprite.setTexture(texture);
}

Player::~Player(){}

void Player::update()
{

}

void Player::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite, render_states);
}

void Player::set_texture(sf::Texture& _texture)
{
	sprite.setTexture(texture);
	texture = _texture;
}

}
