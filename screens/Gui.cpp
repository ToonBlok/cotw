#include "Gui.h"

namespace cotw {

Gui::Gui(sf::Vector2u _screen_size)
{
	screen_size = _screen_size;
	cotw::MainMenu menu();

	//add_observer(menu);
}

Gui::~Gui() {}

void Gui::update()
{
	cout << "A" << endl;
}

void Gui::notify(sf::Event event) 
{
}

void Gui::add_observer(IObserver *observer)
{
	observers.push_back(observer);
}

void Gui::remove_observer()
{
}

void Gui::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	//render_target.draw(sprite, render_states);
}

//void Gui::overlay_texture(sf::Image& new_img)
//{
//	//sf::Image tile_img = texture.copyToImage();
//	//sf::IntRect a;
//	//tile_img.copy(new_img, 0, 0, a, true);
//
//	//sf::Texture new_tex;
//
//	//if (!new_tex.loadFromImage(tile_img))
//	//	cout << "texture was not found!" << endl; 
//
//	//texture = new_tex;
//}

}
