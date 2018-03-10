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
					if(valid_move(sf::Vector2<int>(x, y - 1)))
						player->move(sf::Vector2f(0, -player->speed));
					break;

				case Keyboard::Numpad9:
					if(valid_move(sf::Vector2<int>(x + 1, y - 1)))
						player->move(sf::Vector2f(player->speed, -player->speed));
					break;

				case Keyboard::Numpad4:
					if(valid_move(sf::Vector2<int>(x - 1, y)))
						player->move(sf::Vector2f(-player->speed, 0));
					break;

				case Keyboard::Numpad3:
					if(valid_move(sf::Vector2<int>(x + 1, y + 1)))
						player->move(sf::Vector2f(player->speed, player->speed));
					break;

				case Keyboard::Numpad2:
					if(valid_move(sf::Vector2<int>(x, y + 1)))
						player->move(sf::Vector2f(0, player->speed));
					break;

				case Keyboard::Numpad1:
					if(valid_move(sf::Vector2<int>(x - 1, y + 1)))
						player->move(sf::Vector2f(-player->speed, player->speed));
					break;

				case Keyboard::Numpad6:
					if(valid_move(sf::Vector2<int>(x + 1, y)))
						player->move(sf::Vector2f(player->speed, 0));
					break;

				case Keyboard::Numpad7:
					if(valid_move(sf::Vector2<int>(x - 1, y - 1)))
						player->move(sf::Vector2f(-player->speed, -player->speed));
					break;

				// Interact with environment.
				case Keyboard::Numpad5:
					cout << "There is nothing here to interact with!" << endl;
					break;

				case Keyboard::Q:
					cout << "Bye." << endl;
					window.close();
					break;

				case Keyboard::I:
					//player->set_position(sf::Vector2f(10, 10));
					cout << "I am at x: " << x << " and y: " << y << endl;
					//cout << "This block I am standing on is blocking yes or no: " << static_cast<cotw::Tile*>(entities[y][x])->blocking << endl;
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

bool Game::valid_move(sf::Vector2<int> pos)
{
	if(static_cast<cotw::Tile*>(tiles[pos.y][pos.x])->blocking)
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

		for (int y = 0; y < 30; y++)
			for (int x = 0; x < 30; x++)
				static_cast<cotw::Tile*>(tiles[y][x])->draw(bitmap, render_states);

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



void Game::create_random_tile(int x, int y, bool& dungeon_placed, bool in_dungeon) 
{
	int rand_num_tile = (rand() % 100) + 1;
	sf::Texture texture;
	//int rand_num_tile_rotation = (rand() % 2);
	
	
	bool blocking = 0;
	if (in_dungeon)
	{
		//if ((y == 0) & (x == 0))
		//{
		//	create_room(y, x, 5, 5);
		//}
		//else
		//{
		//	blocking = 1;
		//	texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_wall1.png");
		//	tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, blocking);
		//}
	
		//if ((rand_num_tile >= 0) && (rand_num_tile < 50)) 
		//{
		//	texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png");
		//}
		//else if ((rand_num_tile >= 50) && (rand_num_tile <= 100)) 
		//{
		//	blocking = 1;
		//	texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_wall1.png");
		//}
	}
	else
	{

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
			if (!dungeon_placed)
			{
				texture = texture_manager.get_texture("textures/tile_dungeon_entrance.png");
				dungeon_placed = true;
			}
			else 
			{
				texture = texture_manager.get_texture("textures/tile_plant6.png");
				blocking = 1;
			}

			//texture = texture_manager.get_texture("textures/tile_tree_p1.png");
			//entities[y].push_back(new cotw::Tile(texture, x * 32, y * 32, blocking));
			//texture = texture_manager.get_texture("textures/tile_tree_p1.png");
			//entities[y + 1].push_back(new cotw::Tile(texture, ((x + 1) * 32), ((y + 1) * 32), blocking));
		//std::cout << "tree method" << std::endl;
			//return;
			//std::cout << "x" << std::endl;
			//blocking = 1;
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

		tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, blocking);
	}

}

void Game::fill_empty_map() 
{
	sf::Texture texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_wall1_test.png");

	for (int y = 0; y < 30; y++) 
	{
		for (int x = 0; x < 30; x++) 
		{
			tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, 1);
		}
	}
}

void Game::create_room(cotw::dungeon_room room) 
{
	//cout << "Started room creation" << endl;
	for (int iy = 0; iy < room.height; iy++)
	{
		for (int ix = 0; ix < room.width; ix++)
		{
			if (((room.row + iy) < 30) && ((room.column + ix) < 30))
			{
				//cout << "Tried to change tile of: y: " << (y + iy) << " and x: " << (x + ix) << endl;
				try {
					static_cast<cotw::Tile*>(tiles[room.row + iy][room.column + ix])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
					static_cast<cotw::Tile*>(tiles[room.row + iy][room.column + ix])->blocking = 0;
				}
				catch (const std::out_of_range& oor) {
					std::cerr << "Out of Range error: " << oor.what() << '\n';
				}
			}

		}
	}
}

void Game::create_tunnel(cotw::dungeon_room room1, cotw::dungeon_room room2) 
{
	//int r1_column = room1.x;
	//int r1_row = room1.y;
	//int r2_column = room2.x;
	//int r2_row = room2.x;
	//// the rooms we must connect
	cout << "room1 column: " << room1.column << ", row: " << room1.row << ". Width: " << room1.width << ", height: " << room1.height << endl;
	cout << "room2 column: " << room2.column << ", row " << room2.row << ". Width: " << room2.width << ", height: " << room2.height << endl;

	//// Decide whether H or V tunnel
	//int r1_nw = r1_row;
	//int r1_sw = r1_nw + room1.height;

	//int r2_nw = r2_row;
	//int r2_sw = r2_nw + room2.height;

	//cout << "r2_nw: " << r2_nw << endl;
	//cout << "r1_nw: " << r1_nw << endl;
	//cout << "r1_sw: " << r1_sw << endl;
	//if (((r2_nw >= r1_nw) && (r2_nw <= r1_sw)) || ((r1_nw >= r2_nw) && (r1_nw <= r2_sw)))
	//{
	//	cout << "Room 1 can be H matched with room 2" << endl;
	//}
	//	cout << endl;

	// r1 starts at x 8

	// Call method for H or V tunnel

}

// Remove later with get value directly
void Game::make_map(bool in_dungeon) 
{
	if (in_dungeon)
	{
		fill_empty_map();

		int max_rooms = 2; // this is also declared in header..
		int min_room_width = 2;
		int min_room_height = 2;
		int max_room_width = 8;
		int max_room_height = 8;

		for (int i = 0; i < max_rooms; i++) 
		{
			int rand_row = (rand() % 30) + 1;
			int rand_column = (rand() % 30) + 1;
			int rand_height = rand() % (max_room_height - min_room_height + 1) + min_room_height;
			int rand_width = rand() % (max_room_width - min_room_width + 1) + min_room_width;

			while (((rand_row + rand_height) > 29))
				rand_row = (rand() % 30) + 1;

			while (((rand_column + rand_width) > 29))
				rand_column = (rand() % 30) + 1;

			//cout << "rand_height: " << rand_height << endl;
			//cout << "rand_width: " << rand_width << endl;

	        //                        row     column  
			rooms[i] = dungeon_room { rand_row, rand_column, rand_width, rand_height };
			//dungeon_room room1 =
			//{
			//	0,
			//	5,
			//	5
			//};

			create_room(rooms[i]);

		}

		for (int i = 0; i < max_rooms; i++) 
			if ((i + 1) < max_rooms)
				create_tunnel(rooms[i], rooms[i + 1]);

		//cout << "Dungeon make map triggered" << endl;
		//bool dungeon_placed = true;

		//	blocking = 1;
		//	texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_wall1.png");
		//	tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, blocking);
	}
	else 
	{
		bool dungeon_placed = false;
		for (int y = 0; y < 30; y++) 
			for (int x = 0; x < 30; x++) 
				create_random_tile(x, y, dungeon_placed, false);
	}
}

void Game::enter_dungeon() 
{
	for (int y = 0; y < 30; y++)
		for (int x = 0; x < 30; x++)
			delete tiles[y][x];

	make_map(true);

}

void Game::setup() 
{
	srand(time(0));

	VideoMode video_mode(960, 960, 32);
	window.create(video_mode, "Castle of the winds", Style::Titlebar); 

	img_hero.loadFromFile("textures/entity_hero.png");

	sf::Texture texture;
	if (!texture.loadFromImage(img_hero))
		cout << "Texture \"textures/entity_hero.png\" was not found!" << endl; 

	player = new cotw::Player(texture, 0, 0);

	make_map(false);

	// Temporarily let player spawn in dungeon.
	enter_dungeon();
}

Game::Game()
{
	setup();
	game_loop();
}

Game::~Game()
{
	for (int y = 0; y < 30; y++)
		for (int x = 0; x < 30; x++)
			delete tiles[y][x];

	delete player;
}

}
