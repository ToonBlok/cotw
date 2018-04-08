#include "button.h"

using namespace std;

namespace cotw {

Button::Button(sf::Texture& _texture, std::string _text, sf::Vector2f coords, unsigned int _width, unsigned int _height)
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

Button::~Button()
{
}

void Button::update(int mouse_x, int mouse_y)
{
	//sf::Vector2f bla = sprite.getPosition();
	if ((mouse_y > sprite.getPosition().y) && (mouse_y < sprite.getPosition().y + height) && (mouse_x > sprite.getPosition().x) && (mouse_x < sprite.getPosition().x + width))
	{
		std::string bt_text = text.getString();
		cout << bt_text << " was pressed" << endl;
		state = button_state::PRESSED;


		//cout << mouse_x << endl;
		//cout << mouse_y << endl;
	}

	state = button_state::NORMAL;
}

void Button::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite, render_states);
	render_target.draw(text, render_states);
}


void Button::set_texture(sf::Texture& _texture)
{
	// If this is really a texture then:
	// if ...?
	texture = _texture;
}

void Button::overlay_texture(sf::Image& new_img)
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
