#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "tile.h"
#include <SFML/Graphics/RenderStates.hpp>

// For random

using namespace sf;
using namespace std;

namespace cotw {

void Game::handle_key(Event event)
{
	sf::Vector2f current_position = player->get_position();

	switch (event.type) 
	{
		case Event::KeyPressed:
			switch (event.key.code) 
			{
				case Keyboard::W:
					player->set_position(sf::Vector2f(current_position.x, (current_position.y - player->speed)));
					break;

				case Keyboard::A:
					player->set_position(sf::Vector2f((current_position.x - player->speed), current_position.y));
					break;

				case Keyboard::S:
					player->set_position(sf::Vector2f(current_position.x, (current_position.y + player->speed)));
					break;

				case Keyboard::D:
					player->set_position(sf::Vector2f((current_position.x + player->speed), current_position.y));
					break;

				case Keyboard::Q:
					cout << "Bye." << endl;
					window.close();
					break;

				case Keyboard::I:
					player->set_position(sf::Vector2f(10, 10));
					//srand(time(NULL));
					//int num;
					//num = rand() % 10;
					//cout << num << endl;
					break;

				case Keyboard::Return:
					cout << "Bye." << endl;
					window.close();
					break;

				default:
					cout << "Unhandled key." << endl;
					break;
			}
			break;
		default:
			break;
	}
}

int Game::game_loop()
{
	sf::RenderTexture bitmap;

	Vector2u size = window.getSize();
	float screen_width = size.x;
	float screen_height = size.y;
	if (!bitmap.create(screen_width, screen_height))
		return -1;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
			handle_key(event);

		bitmap.clear(Color::Black);

		sf::RenderStates render_states;
		//tile.draw(bitmap, render_states);
		//p_tile->draw(bitmap, render_states);

		for (int x = 0; x < entities.size(); x++)
			static_cast<cotw::Tile*>(entities[x])->draw(bitmap, render_states);

		player->draw(bitmap, render_states);

		// START Temporary test code
		// END Temporary test code
		// We are done drawing to the bitmap.
		bitmap.display();
		// Create a sprite from the bitmap.
	    sf::Sprite sprite(bitmap.getTexture());
		// Draw the sprite.
		window.draw(sprite);
		// We are done drawing to the window.
        window.display();
    }

}

// Remove later with get value directly
void Game::make_map(int screen_width, int screen_height) {
	img_tile_grass.loadFromFile(filename_texture_grass);


	int h_tiles_size = screen_width / 32;
	int v_tiles_size = screen_height / 32;

	for (int y = 0; y < v_tiles_size; y++) 
	{
		for (int x = 0; x < h_tiles_size; x++) 
		{
			if ((rand() % 3) + 1 == 2)
				img_tile_grass.flipHorizontally();
			else if ((rand() % 3) + 1 == 3)
				img_tile_grass.flipVertically();

			sf::Texture texture;
			if (!texture.loadFromImage(img_tile_grass))
				cout << "Texture \"" + filename_texture_grass + "\" was not found!" << endl; // Apparentely not even called when not found...

			entities.push_back(new cotw::Tile(texture, x * 32, y * 32, 32, 32));
		}
	}
}

void Game::setup() 
{
	int screen_width = 960;
	int screen_height = 960;
	VideoMode video_mode(screen_width, screen_height, 32);
	window.create(video_mode, "Jets", Style::Titlebar); 

	img_hero.loadFromFile(filename_texture_hero);

	sf::Texture texture_hero;
	if (!texture_hero.loadFromImage(img_hero))
		cout << "Texture \"" + filename_texture_hero + "\" was not found!" << endl; // Apparentely not even called when not found...

	// Now to assign a new player to the pointer obj....
	player = new cotw::Player(texture_hero, 32, 32, 32, 32);

	make_map(screen_width, screen_height);
}

Game::Game()// : player(50, 50, 32, 32)
{
	srand(time(0));
	setup();
	game_loop();

	for (int i = 0; i < entities.size(); i++)
		delete entities[i];

	delete player;
}


Game::~Game(){ }

}
