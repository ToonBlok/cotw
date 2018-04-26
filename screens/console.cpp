#include "console.h"

using namespace std;

namespace cotw {

Console::Console(sf::Texture& _texture, std::string _text, sf::Vector2f coords, unsigned int _width, unsigned int _height)
{
	texture = _texture;
	width = _width;
	height = _height;

	font.loadFromFile("DejaVuSans.ttf");

	sf::Vector2f text_coords = coords;
	//text_coords.y -= height / 2;
	text_coords.y += 8;
	//text_coords.y += ((height / 2) - height / 3);
	text_coords.x += 10;

	for (unsigned int i = 0; i < texts.size(); i++)
	{
		texts[i].setFont(font);
		texts[i].setCharacterSize(12);
		texts[i].setStyle(sf::Text::Bold);
		texts[i].setColor(sf::Color::White);
		texts[i].setString("foo" + std::to_string(i));
		if (i != 0)
			text_coords.y += 13;
		texts[i].setPosition(text_coords);
	}
	//text.setCharacterSize(50);
	//text.setStyle(sf::Text::Bold);
	//text.setColor(sf::Color::White);
	//text.setString(_text);
	//
	//
//	texts[0] = new sf::Text;
//	texts[1] = new sf::Text;
//	texts[2] = new sf::Text;

	//texts[0].setPosition(text_coords);
	//text_coords.y += 30;
	//texts[1].setPosition(text_coords);
	//text_coords.y += 30;
	//texts[2].setPosition(text_coords);

	//cout << text_coords.y << endl;
	sprite.setTexture(texture);
	sprite.setPosition(coords); 
}

Console::~Console() {}

void Console::update() 
{
	for (unsigned int i = 0; i < texts.size(); i++)
	{
		//	// klopt want voor bericht 1 moet er 1 size zijn, voor bericht 2 moet er ten minste 2 size zijn..
		//	// If there are enough messages to let a message get taken and placed in console
		//	//cout << "TRIGGERED" << endl;
		if (messages.size() >= (i + 1))
		{
			//cout << messages.at(i) << endl;
			texts[i].setString(messages.at(i));
		}
		else
		{
			cout << "No message to display" << endl;
		}
	}
}

void Console::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(sprite, render_states);
	for (unsigned int i = 0; i < texts.size(); i++)
	{
		render_target.draw(texts[i], render_states);
	}
}

void Console::overlay_texture(sf::Image& new_img)
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
