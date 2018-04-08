#include "main_menu.h"

using namespace std;

namespace cotw {

Main_menu::Main_menu(sf::Vector2u screen_size)
{
	float smx = screen_size.x / 2;
	float smy = screen_size.y / 2;

	sf::Texture tex_button = texture_manager.get_texture("textures/screens/button2.png");

    cotw::Button *button_start = new cotw::Button(tex_button, "Start", sf::Vector2f((smx - tex_button.getSize().x / 2), ((smy - tex_button.getSize().y / 2) - tex_button.getSize().y) - 5), tex_button.getSize().x, tex_button.getSize().y);
	ui_elements[0] = button_start;

    cotw::Button *button_settings = new cotw::Button(tex_button, "Settings", sf::Vector2f((smx - tex_button.getSize().x / 2), (smy - tex_button.getSize().y / 2)), tex_button.getSize().x, tex_button.getSize().y);
	ui_elements[1] = button_settings;

    cotw::Button *button_quit = new cotw::Button(tex_button, "Quit", sf::Vector2f((smx - tex_button.getSize().x / 2), ((smy - tex_button.getSize().y / 2) + tex_button.getSize().y) + 5), tex_button.getSize().x, tex_button.getSize().y);
	ui_elements[2] = button_quit;



//    cotw::Button *button_settings = new cotw::Button(texture_manager.get_texture("textures/screens/button2.png"), smx, smy, "Settings");
//	button_settings->set_position(sf::Vector2f((smx - button_settings->width / 2), (smy - button_settings->height / 2)));
//	ui_elements[1] = button_settings;
//
//    cotw::Button *button_exit = new cotw::Button(texture_manager.get_texture("textures/screens/button2.png"), smx, smy, "Exit");
//	button_exit->set_position(sf::Vector2f((smx - button_exit->width / 2), ((smy - button_exit->height / 2) + button_start->height) + 5));
//	ui_elements[2] = button_exit;
}

Main_menu::~Main_menu(){}

void Main_menu::update(int mouse_x, int mouse_y)
{
	for (unsigned int i = 0; i < ui_elements.size(); i++)
		static_cast<cotw::Button*>(ui_elements[i])->update(mouse_x, mouse_y);
}

void Main_menu::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	for (unsigned int i = 0; i < ui_elements.size(); i++)
		static_cast<cotw::Button*>(ui_elements[i])->draw(render_target, render_states);
}

void Main_menu::set_texture(sf::Texture& _texture)
{
	// If this is really a texture then:
	// if ...?
	texture = _texture;
}

void Main_menu::overlay_texture(sf::Image& new_img)
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
