#include <iostream>
#include "MainMenuState.h"
//#include "GameStateManager.h"

using namespace std;

namespace cotw {

MainMenuState::MainMenuState(cotw::GameStateManager* _game_state_manager) 
{
	game_state_manager = _game_state_manager;
	float smx = 480;
	float smy = 480;

	sf::Texture *bg_texture = new sf::Texture(texture_manager.get_texture("textures/screens/background.png"));
	background.setTexture(*bg_texture);
	background.setPosition(sf::Vector2f(0, 0)); 

	sf::Texture tex_button = texture_manager.get_texture("textures/screens/button3.png");
    cotw::Button *button_start = new cotw::Button(tex_button, "Start", sf::Vector2f((smx - tex_button.getSize().x / 2), ((smy - tex_button.getSize().y / 2) - tex_button.getSize().y) - 5), tex_button.getSize().x, tex_button.getSize().y);
	ui_elements[0] = button_start;

    cotw::Button *button_settings = new cotw::Button(tex_button, "Settings", sf::Vector2f((smx - tex_button.getSize().x / 2), (smy - tex_button.getSize().y / 2)), tex_button.getSize().x, tex_button.getSize().y);
	ui_elements[1] = button_settings;

    cotw::Button *button_quit = new cotw::Button(tex_button, "Quit", sf::Vector2f((smx - tex_button.getSize().x / 2), ((smy - tex_button.getSize().y / 2) + tex_button.getSize().y) + 5), tex_button.getSize().x, tex_button.getSize().y);
	ui_elements[2] = button_quit;
}

MainMenuState::~MainMenuState() {}

void MainMenuState::change_state(cotw::GameStateManager* game_state_manager, cotw::GameState* state)
{
	//game->set_state(state);
}

void MainMenuState::on_notify(sf::Event)
{
}

void MainMenuState::handle_events()
{
}

void MainMenuState::init()
{
}

void MainMenuState::cleanup()
{
}

void MainMenuState::pause()
{
}

void MainMenuState::resume()
{
}


void MainMenuState::update(sf::RenderWindow& window) 
{
	sf::Event event;

	while (window.pollEvent(event))
		handle_key(window, event);
}

void MainMenuState::handle_key(sf::RenderWindow& window, sf::Event event)
{
	sf::Vector2f new_move;

	switch (event.type) 
	{
		case sf::Event::KeyPressed:
		{
			switch (event.key.code) 
			{
				case sf::Keyboard::Return:
					cout << "Return" << endl;
					//change_state(new InGameState);

					//state = cotw::game_state::GAME;
					break;
					
				case sf::Keyboard::Q:
					std::cout << "Bye." << std::endl;
					window.close();
					break;

				default:
					//std::cout << "Unhandled key." << std::endl;
					break;
			}
			break;
			case sf::Event::MouseButtonPressed:
			{

			}
			break;

			default:
				// nothing
				break;
		}
	}
}


void MainMenuState::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(background, render_states);

	for (unsigned int i = 0; i < ui_elements.size(); i++)
		static_cast<cotw::Button*>(ui_elements[i])->draw(render_target, render_states);
}

}
