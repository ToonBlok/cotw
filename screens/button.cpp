#include "button.h"

using namespace std;

namespace cotw {

Button::Button()
{
	sf::Sprite sprite;
	sf::Texture texture = texture_manager.get_texture("textures/tile_plant1.png");
	sprite.setTexture(texture);

	sprite.setPosition(sf::Vector2f(50, 50)); 
	ui_elements[0] = sprite;
}

Button::~Button()
{
}

void Button::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	for (unsigned int i = 0; i < ui_elements.size(); i++)
	{
		render_target.draw(ui_elements[i], render_states);
	}
}

}
