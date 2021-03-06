#include "MainMenu.h"

using namespace std;

namespace cotw {

MainMenu::MainMenu(sf::Vector2u screen_size)
{
//	float smx = screen_size.x / 2;
//	float smy = screen_size.y / 2;

	sf::Texture *bg_texture = new sf::Texture(texture_manager.get_texture("textures/screens/background.png"));
	background.setTexture(*bg_texture);
	background.setPosition(sf::Vector2f(0, 0)); 

	sf::Texture tex_button = texture_manager.get_texture("textures/screens/button3.png");

//    cotw::Button *button_start = new cotw::Button(tex_button, "Start", sf::Vector2f((smx - tex_button.getSize().x / 2), ((smy - tex_button.getSize().y / 2) - tex_button.getSize().y) - 5), tex_button.getSize().x, tex_button.getSize().y);
//	ui_elements[0] = button_start;
//
    //cotw::Button *button_settings = new cotw::Button(tex_button, "Settings", sf::Vector2f((smx - tex_button.getSize().x / 2), (smy - tex_button.getSize().y / 2)), tex_button.getSize().x, tex_button.getSize().y);
	//ui_elements[1] = button_settings;

    //cotw::Button *button_quit = new cotw::Button(tex_button, "Quit", sf::Vector2f((smx - tex_button.getSize().x / 2), ((smy - tex_button.getSize().y / 2) + tex_button.getSize().y) + 5), tex_button.getSize().x, tex_button.getSize().y);
	//ui_elements[2] = button_quit;
}

MainMenu::~MainMenu(){}

void MainMenu::update()
{
//	for (unsigned int i = 0; i < ui_elements.size(); i++)
//		static_cast<cotw::Button*>(ui_elements[i])->update();
}

void MainMenu::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	//render_target.draw(background, render_states);

//	for (unsigned int i = 0; i < ui_elements.size(); i++)
//		static_cast<cotw::Button*>(ui_elements[i])->draw(render_target, render_states);

}

void MainMenu::overlay_texture(sf::Image& new_img)
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
