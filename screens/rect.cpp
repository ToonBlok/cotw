#include "rect.h"

using namespace std;

namespace cotw {

Rect::Rect(sf::Texture& _texture, std::string _text, sf::Vector2f coords, unsigned int _width, unsigned int _height)
{
	texture = _texture;
	width = _width;
	height = _height;

	font.loadFromFile("DejaVuSans.ttf");
	text.setFont(font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setString(_text);
	sf::Vector2f text_coords = coords;
	//text_coords.y += ((height / 2) - (text.getCharacterSize() / 2));
	text_coords.y += ((height / 2) - height / 3);
	text_coords.x += 60;
	cout << text_coords.y << endl;
	text.setPosition(text_coords);

	sprite.setTexture(texture);
	sprite.setPosition(coords); 
}

Rect::~Rect() {}

void Rect::update() {}

void Rect::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite, render_states);
	render_target.draw(text, render_states);
}

void Rect::overlay_texture(sf::Image& new_img)
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
