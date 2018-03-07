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
	int x = current_location.x / 32;
	int y = current_location.y / 32;

	switch (event.type) 
	{
		case Event::KeyPressed:
			switch (event.key.code) 
			{
				case Keyboard::Numpad8:
					if(valid_move(sf::Vector2f(x, y - 1)))
						player->move(sf::Vector2f(0, -player->speed));
					break;

				case Keyboard::Numpad9:
					if(valid_move(sf::Vector2f(x + 1, y - 1)))
						player->move(sf::Vector2f(player->speed, -player->speed));
					break;

				case Keyboard::Numpad4:
					if(valid_move(sf::Vector2f(x - 1, y)))
						player->move(sf::Vector2f(-player->speed, 0));
					break;

				case Keyboard::Numpad3:
					if(valid_move(sf::Vector2f(x + 1, y + 1)))
						player->move(sf::Vector2f(player->speed, player->speed));
					break;

				case Keyboard::Numpad2:
					if(valid_move(sf::Vector2f(x, y + 1)))
						player->move(sf::Vector2f(0, player->speed));
					break;

				case Keyboard::Numpad1:
					if(valid_move(sf::Vector2f(x - 1, y + 1)))
						player->move(sf::Vector2f(-player->speed, player->speed));
					break;

				case Keyboard::Numpad6:
					if(valid_move(sf::Vector2f(x + 1, y)))
						player->move(sf::Vector2f(player->speed, 0));
					break;

				case Keyboard::Numpad7:
					if(valid_move(sf::Vector2f(x - 1, y - 1)))
						player->move(sf::Vector2f(-player->speed, -player->speed));
					break;

				case Keyboard::Q:
					cout << "Bye." << endl;
					window.close();
					break;

				case Keyboard::I:
					//player->set_position(sf::Vector2f(10, 10));
					cout << "I am at x: " << x << " and y: " << y << endl;
					cout << "This block I am standing on is blocking yes or no: " << static_cast<cotw::Tile*>(entitiesf[y][x])->blocking << endl;
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

bool Game::valid_move(sf::Vector2f pos)
{
	if(static_cast<cotw::Tile*>(entitiesf[pos.y][pos.x])->blocking)
		return false;
	else
		return true;
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

void Game::get_texture(sf::Texture& texture, std::string filename) 
{
	sf::Image image;
	image.loadFromFile(filename);
	//random_rotate_tile(image);
	if (!texture.loadFromImage(image))
		cout << "texture \"" + filename + "\" was not found!" << endl; 
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
	

	if ((rand_num_tile >= 0) && (rand_num_tile < 5)) 
	{
		get_texture(texture, filename_texture_plant1);
	}
	else if ((rand_num_tile >= 5) && (rand_num_tile < 10)) 
	{
		get_texture(texture, filename_texture_plant2);
	}
	else if ((rand_num_tile >= 10) && (rand_num_tile < 15)) 
	{
		get_texture(texture, filename_texture_plant3);
	}
	else if ((rand_num_tile >= 15) && (rand_num_tile < 20)) 
	{
		get_texture(texture, filename_texture_plant4);
	}
	else if ((rand_num_tile >= 20) && (rand_num_tile < 25)) 
	{
		get_texture(texture, filename_texture_plant5);
		blocking = 1;
	}
	else if ((rand_num_tile >= 25) && (rand_num_tile < 30)) 
	{
		get_texture(texture, filename_texture_plant6);
		blocking = 1;
	}
	else if ((rand_num_tile >= 30) && (rand_num_tile < 35)) 
	{
		get_texture(texture, filename_texture_hole);
		blocking = 1;
	}
	else if ((rand_num_tile >= 35) && (rand_num_tile < 37)) 
	{
		get_texture(texture, filename_texture_tree_p1);
	}
	else if (rand_num_tile >= 37) 
	{
		get_texture(texture, filename_texture_grass);
	}

	return new cotw::Tile(texture, x * 32, y * 32, blocking);
}

// Remove later with get value directly
void Game::make_map(int screen_width, int screen_height) 
{
	//bool tree = 0;

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
