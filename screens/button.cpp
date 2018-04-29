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
	//cout << text_coords.y << endl;
	text.setPosition(text_coords);

	sprite.setTexture(texture);
	sprite.setPosition(coords); 
}

Button::~Button() {}

//void Button::notify(sf::Event event) 
//{
//}
//
//void Button::add_observer(IObserver *observer)
//{
//	observers.push_back(observer);
//}
//
//void Button::remove_observer()
//{
//}

void Button::on_notify(sf::Event event)
{
	//sf::Vector2f coords = get_position();
	//if ((event.mouseButton.y > coords.y) && (event.mouseButton.y < coords.y + height) && (event.mouseButton.x > coords.x) && (event.mouseButton.x < coords.x + width))
	//{
	//	activated = true;
	//	//std::string label = p_button->text.getString();
	//	//if (label == "Start")
	//	//	state = cotw::game_state::GAME_SETUP;
	//	//else if (label == "Quit")
	//	//	window.close();
	//}
	//cout << "I am button, copy." << endl;

}

void Button::update()
{
	cout << "A" << endl;
}

void Button::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite, render_states);
	render_target.draw(text, render_states);
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
