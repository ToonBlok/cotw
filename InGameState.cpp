#include <iostream>
#include "InGameState.h"
#include "GameStateManager.h"

using namespace std;

namespace cotw {

InGameState::InGameState(cotw::GameStateManager* _game_state_manager) 
{
	game_state_manager = _game_state_manager;
	float smx = 480;
	float smy = 480;

	sf::Texture tex_console(texture_manager.get_texture("textures/screens/console.png"));
	cotw::Console *console = new cotw::Console
	(
		tex_console, 
		"", 
		sf::Vector2f(0, smy - tex_console.getSize().y), 
		tex_console.getSize().x + 500, 
		tex_console.getSize().y
	);

	ui_elements[0] = console;
}

InGameState::~InGameState() {}

void InGameState::on_notify(cotw::Event)
{
}

void InGameState::handle_events()
{
}

void InGameState::init()
{
}

void InGameState::cleanup()
{
}

void InGameState::pause()
{
}

void InGameState::resume()
{
}

void InGameState::change_state(cotw::GameStateManager* game_state_manager, cotw::GameState* state)
{
	game_state_manager->set_state(state);
}


void InGameState::update(sf::RenderWindow& window) 
{
	sf::Event event;

	while (window.pollEvent(event))
		handle_key(window, event);
}

void InGameState::handle_key(sf::RenderWindow& window, sf::Event event)
{
	sf::Vector2f new_move;

	switch (event.type) 
	{
		case sf::Event::KeyPressed:
		{
			switch (event.key.code) 
			{
				case sf::Keyboard::Return:
					cout << "InGameState" << endl;
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
				cout << event.mouseButton.x << ", " << event.mouseButton.y << endl;

			}
			break;

			default:
				// nothing
				break;
		}
	}
}


void InGameState::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	render_target.draw(background, render_states);

	for (unsigned int i = 0; i < ui_elements.size(); i++)
		static_cast<cotw::Button*>(ui_elements[i])->draw(render_target, render_states);
}

}
