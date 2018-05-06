#include "Game.h"

using namespace std;

namespace cotw {

Game::Game()
{
	sf::VideoMode video_mode(960, 960, 32);
	window.create(video_mode, "Castle of the winds 2018", sf::Style::Titlebar); 
	game_state_manager = new cotw::GameStateManager(window.getSize());
	game_loop();
}

Game::~Game()
{

}

void Game::update() 
{
	game_state_manager->current_state->update(window);
}

void Game::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) //const
{
	sf::RenderTexture& bitmap = static_cast<sf::RenderTexture&>(render_target);

	bitmap.clear(sf::Color::Black);
	game_state_manager->current_state->draw(render_target, render_states);
	bitmap.display();

	// Clear(delete) the contents of the previous frame.
	window.clear();
	window.draw(sf::Sprite(bitmap.getTexture()));
	// Display what has been drawn to the window so far.
	window.display();
}

void Game::game_loop()
{
	sf::RenderTexture bitmap;
	sf::Vector2u window_size = window.getSize();

	if (!bitmap.create(window_size.x, window_size.y))
	{
		cout << "COTW error: Could not create bitmap" << endl;
		return;
	}

    while (window.isOpen())
    {
		update();
		sf::RenderStates render_state;
		draw(bitmap, render_state);
    }
}


}
