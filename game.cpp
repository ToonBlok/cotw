#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
#include "game.h"
#include "tile.h"

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
					cout << "This block I am standing on is blocking yes or no: " << static_cast<cotw::Tile*>(entities[y][x])->blocking << endl;
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
	if(static_cast<cotw::Tile*>(entities[pos.y][pos.x])->blocking)
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

		for (int y = 0; y < entities.size(); y++)
			for (int x = 0; x < entities[y].size(); x++)
				static_cast<cotw::Tile*>(entities[y][x])->draw(bitmap, render_states);

		player->draw(bitmap, render_states);

		bitmap.display();
	    sf::Sprite sprite(bitmap.getTexture());
		window.draw(sprite);
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

void Game::create_texture(sf::Texture& texture, std::string filename) 
{
	sf::Image image;
	image.loadFromFile(filename);

	if (!texture.loadFromImage(image))
		cout << "texture \"" + filename + "\" was not found!" << endl; 
}

void Game::create_random_tile(int x, int y) 
{
	int rand_num_tile = (rand() % 100) + 1;

	// if there are more elements than there should be with the double for loop system, then there is a tree placed... but
	// we dont know where and when to skip, so check the pos of the last added element
	//if (entities[y][x]) 
	//{
	//	cout << "There is something here!" << endl;
	//}

	sf::Texture texture;
	//int rand_num_tile_rotation = (rand() % 2);
	bool blocking = 0;

	if ((rand_num_tile >= 0) && (rand_num_tile < 5)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant1.png");
	}
	else if ((rand_num_tile >= 5) && (rand_num_tile < 10)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant2.png");
	}
	else if ((rand_num_tile >= 10) && (rand_num_tile < 15)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant3.png");
	}
	else if ((rand_num_tile >= 15) && (rand_num_tile < 20)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant4.png");
	}
	else if ((rand_num_tile >= 20) && (rand_num_tile < 25)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant5.png");
		blocking = 1;
	}
	else if ((rand_num_tile >= 25) && (rand_num_tile < 30)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant6.png");
		blocking = 1;
	}
	else if ((rand_num_tile >= 30) && (rand_num_tile < 31)) 
	{
		texture = texture_manager.get_texture("textures/tile_tree_p1.png");
		blocking = 1;
	}
	else if ((rand_num_tile >= 31) && (rand_num_tile < 37)) 
	{
		texture = texture_manager.get_texture("textures/tile_hole2.png");
		blocking = 1;
	}
	else if (rand_num_tile >= 37) 
	{
		texture = texture_manager.get_texture("textures/tile_grass.png");
	}

	entities[y].push_back(new cotw::Tile(texture, x * 32, y * 32, blocking));
}

// Remove later with get value directly
void Game::make_map() 
{
	Vector2u screen_size = window.getSize();
	int h_tiles_size = screen_size.x / 32;
	int v_tiles_size = screen_size.y / 32;

	for (int y = 0; y < v_tiles_size; y++) 
		for (int x = 0; x < h_tiles_size; x++) 
			entities.push_back(std::vector<sf::Drawable*>());

	for (int y = 0; y < v_tiles_size; y++) 
		for (int x = 0; x < h_tiles_size; x++) 
			create_random_tile(x, y);

}

sf::Texture Game::create_texture2(std::string filename)
{
	sf::Texture texture;
	sf::Image image;
	image.loadFromFile(filename);

	if (!texture.loadFromImage(image))
		cout << "texture \"" + filename + "\" was not found!" << endl; 

	return texture;
}


void Game::setup() 
{
	srand(time(0));

	VideoMode video_mode(960, 960, 32);
	window.create(video_mode, "Jets", Style::Titlebar); 

	img_hero.loadFromFile("textures/entity_hero.png");

	sf::Texture texture;
	if (!texture.loadFromImage(img_hero))
		cout << "Texture \"textures/entity_hero.png\" was not found!" << endl; // Apparentely not even called when not found...

	player = new cotw::Player(texture, 0, 0);

	make_map();
}

Game::Game()
{
	setup();
	game_loop();
}

Game::~Game()
{
	for (int y = 0; y < entities.size(); y++)
		for (int x = 0; x < entities[y].size(); x++)
			delete entities[y][x];

	delete player;
}

}
