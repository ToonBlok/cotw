#include <iostream>
#include "Player.h"

using namespace std;

namespace cotw {

Player::Player() {}

Player::Player(sf::Texture& _texture, int _x, int _y) 
{
	texture = _texture;

	row = _x / 32;
	col = _y / 32;
	sprite.setPosition(sf::Vector2f(_x, _y)); 
	sprite.setTexture(texture);
}

Player::~Player(){}

void Player::update() {}

}
