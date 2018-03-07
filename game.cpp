#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "tile.h"
#include <SFML/Graphics/RenderStates.hpp>

using namespace sf;
using namespace std;

namespace cotw {

void Game::handle_key(Event event)
{
	sf::Vector2f current_location = player->get_position();
	int pos_x = current_location.x / 32;
	int pos_y = current_location.y / 32;

	switch (event.type) 
	{
		case Event::KeyPressed:
			switch (event.key.code) 
			{
				case Keyboard::Numpad8:
					player->move(sf::Vector2f(0, -player->speed));
					break;

				case Keyboard::Numpad9:
					player->move(sf::Vector2f(player->speed, -player->speed));
					break;

				case Keyboard::Numpad4:
					player->move(sf::Vector2f(-player->speed, 0));
					break;

				case Keyboard::Numpad3:
					player->move(sf::Vector2f(player->speed, player->speed));
					break;

				case Keyboard::Numpad2:
					player->move(sf::Vector2f(0, player->speed));
					break;

				case Keyboard::Numpad1:
					player->move(sf::Vector2f(-player->speed, player->speed));
					break;

				case Keyboard::Numpad6:
					player->move(sf::Vector2f(player->speed, 0));
					break;

				case Keyboard::Numpad7:
					player->move(sf::Vector2f(-player->speed, -player->speed));
					break;

				case Keyboard::Q:
					cout << "Bye." << endl;
					window.close();
					break;

				case Keyboard::I:
					//player->set_position(sf::Vector2f(10, 10));
					cout << "I am at x: " << current_location.x << " and y: " << current_location.y << endl;
					//cout << "This block is " << entities
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

		for (int y = 0; y < entitiesf.size(); y++)
			for (int x = 0; x < entitiesf[y].size(); x++)
				static_cast<cotw::Tile*>(entitiesf[y][x])->draw(bitmap, render_states);

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

sf::Texture Game::random_rotate_tile(sf::Image& image) 
{
	int rand_num_tile_rotation = (rand() % 2);

	if (rand_num_tile_rotation == 0)
		image.flipHorizontally();
	else if (rand_num_tile_rotation == 1)
		image.flipVertically();
}

cotw::Tile* Game::create_tile(int x, int y) 
{
	int rand_num_tile = (rand() % 100) + 1;

	sf::Texture texture;
	sf::Image image;
	int rand_num_tile_rotation = (rand() % 2);
	bool blocking = 0;

	if (rand_num_tile_rotation == 0)
		image.flipHorizontally();
	else if (rand_num_tile_rotation == 1)
		image.flipVertically();
	

	if ((rand_num_tile >= 0) && (rand_num_tile < 5)) // plain grass
	{
		image.loadFromFile(filename_texture_plant1);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 
	}
	else if ((rand_num_tile >= 5) && (rand_num_tile < 10)) // plain grass
	{
		image.loadFromFile(filename_texture_plant2);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 
	}
	else if ((rand_num_tile >= 10) && (rand_num_tile < 15)) // plain grass
	{
		image.loadFromFile(filename_texture_plant3);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 
	}
	else if ((rand_num_tile >= 15) && (rand_num_tile < 20)) // plain grass
	{
		image.loadFromFile(filename_texture_plant4);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 
	}
	else if ((rand_num_tile >= 20) && (rand_num_tile < 25)) // plain grass
	{
		image.loadFromFile(filename_texture_plant5);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 

		blocking = 1;
	}
	else if ((rand_num_tile >= 25) && (rand_num_tile < 30)) // plain grass
	{
		image.loadFromFile(filename_texture_plant6);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 

		blocking = 1;
	}
	else if ((rand_num_tile >= 30) && (rand_num_tile < 35)) // plain grass
	{
		image.loadFromFile(filename_texture_hole);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "Texture \"" + filename_texture_hole + "\" was not found!" << endl;

		blocking = 1;
	}
	else if (rand_num_tile >= 35) // plain grass
	{
		image.loadFromFile(filename_texture_grass);
		//random_rotate_tile(image);
		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename_texture_grass + "\" was not found!" << endl; 
	}
	
	return new cotw::Tile(texture, x * 32, y * 32, blocking);
}

// Remove later with get value directly
void Game::make_map(int screen_width, int screen_height) 
{

	int h_tiles_size = screen_width / 32;
	int v_tiles_size = screen_height / 32;

	for (int y = 0; y < v_tiles_size; y++) 
	{
		entitiesf.push_back(std::vector<sf::Drawable*>());
		for (int x = 0; x < h_tiles_size; x++) 
		{
			entitiesf[y].push_back(create_tile(x, y));
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

	player = new cotw::Player(texture_hero, 0, 0);

	make_map(screen_width, screen_height);
}

Game::Game()// : player(50, 50, 32, 32)
{
	srand(time(0));
	setup();
	game_loop();

	//std::vector<Tile*> bla;
	//std::vector<sf::Drawable*> bla;
	//entitiesf.push_back(bla);

	for (int y = 0; y < entitiesf.size(); y++)
		for (int x = 0; x < entitiesf[y].size(); x++)
			delete entitiesf[y][x];

	delete player;
}


Game::~Game(){ }

}
