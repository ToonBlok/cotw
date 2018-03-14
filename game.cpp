#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
#include "game.h"
#include "tile.h"
#include <SFML/Graphics/Rect.hpp>

using namespace sf;
using namespace std;

namespace cotw {

void Game::handle_key(Event event)
{
	sf::Vector2f current_location = player->get_position();
	int x = current_location.x / 32;
	int y = current_location.y / 32;
	int rand_row = (rand() % 30) + 1;
	int rand_column = (rand() % 30) + 1;

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
					player->set_position(sf::Vector2f(rand_row * 32, rand_column * 32));
					break;

				case Keyboard::Return:
					cout << "Bye." << endl;
					window.close();
					break;

				default:
					//cout << "Unhandled key." << endl;
					break;
			}
			break;
		default:
			break;
	}
}

bool Game::valid_move(sf::Vector2<int> new_pos)
{
	if ((new_pos.x == -1) || (new_pos.y == -1) || (new_pos.x > 30) || (new_pos.y > 30))
		return false;
	else if(static_cast<cotw::Tile*>(tiles[new_pos.y][new_pos.x])->blocking)
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

void Game::create_room(sf::IntRect room, int index) 
{
	//cout << "Started room creation" << endl;
	for (int iy = 0; iy < room.width; iy++)
	{
		for (int ix = 0; ix < room.height; ix++)
		{
			if (((room.left + iy) < 30) && ((room.top + ix) < 30))
			{
				static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->set_texture(texture_manager.get_texture("textures/dungeon/" + std::to_string(index + 1) + "tile_dungeon_floor1.png"));
				static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->blocking = 0;
			}

		}
	}
}
void Game::create_h_tunnel(int r1_left, int r1_width, int r2_left, int rand_tunnel_entrance) 
{
	cout << "create_h_tunnel triggered" << endl;
	cout << r1_left + r1_width << endl;
	cout << r2_left << endl;
	for (int i = (r1_left + r1_width); i < r2_left; i++)
	{
		cout << "making tunnel... " << i << ", " << rand_tunnel_entrance << endl;
		static_cast<cotw::Tile*>(tiles[rand_tunnel_entrance][i])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
		static_cast<cotw::Tile*>(tiles[rand_tunnel_entrance][i])->blocking = 0;
	}
}

void Game::create_v_tunnel(sf::IntRect room1, sf::IntRect room2) 
{

}

void Game::create_tunnel(sf::IntRect r1, sf::IntRect r2, int index) 
{

	std::vector<int> test;

	// Loop through the entire height of the first rectangle square by square.
	// int i = 5; i < 8. So 5, 6, 7
	for (int i = r1.top; i < (r1.top + r1.height); i++)
	{
		std::cout << "index: " <<  i << std::endl;

		// If a square is bigger than the top of room 2 and smaller than the height of room 2.
		std::cout << " if ( (" << i << " >= " << r2.top << ") && (" << i << " <= " << r2.top + r2.height << ") )" << std::endl;
		if ((i >= r2.top) && (i < (r2.top + r2.height)))
		{
			test.push_back(i);
			//std::cout << "yes" << std::endl;
		}
		else
		{
			std::cout << "no" << std::endl;
		}
	}

	//for (int i = 0; i < test.size(); i++)
	//{
	//	std::cout << "Can make tunnel at: " << test[i] << std::endl;
	//}


	if (test.size() != 0)
	{
		int highest = test.back();
		int lowest = test.front();
		int rand_tunnel_entrance = rand() % (highest - lowest + 1) + lowest;

		cout << "Before create tunnel: " << rand_tunnel_entrance << endl;
		cout << "r2.left:" << r2.left << endl;
		cout << "r2.top:" << r2.top << endl;
		cout << endl;
		create_h_tunnel(r1.left, r1.width, r2.left, rand_tunnel_entrance);
	}

}

// Remove later with get value directly
void Game::make_map(bool in_dungeon) 
{
	if (in_dungeon)
	{
		fill_empty_map();

		int max_rooms = 10;
		int min_room_width = 3;
		int min_room_height = 3;
		int max_room_width = 10;
		int max_room_height = 10;

		bool does_not_intersect;
		int count = 0;
		for (int i = 0; i < max_rooms; i++) 
		{
			int rand_row;
			int rand_column;
			int rand_height;
			int rand_width; 
			// Do 1 time, but if dni becomes false keep doing it.
			do
			{
				does_not_intersect = true;
				rand_row = (rand() % 30) + 1;
				rand_column = (rand() % 30) + 1;
				rand_height = rand() % (max_room_height - min_room_height + 1) + min_room_height;
				rand_width = rand() % (max_room_width - min_room_width + 1) + min_room_width;
				sf::IntRect room(rand_column, rand_row, rand_height, rand_width);

				for (int h = 0; h < count; h++)  
				{
					if (room.intersects(roomsf[h]))
					{
						//cout << "Room " << i + 1 << " failed inspection: " << room.left << ", " << room.top << ", " << endl;
						//cout << "Room " << i + 1 << " intersects with room " << endl;
						does_not_intersect = false;
					}
					if ( ((room.left + room.width) > 30) || ((room.top + room.height) > 30) )
					{
						does_not_intersect = false;
					}
				}
			}
			while (!does_not_intersect);
			//cout << "Room " << i + 1 << " passed inspection: " << rand_row << ", " << rand_column << ", " << endl;

			//cout << "Made with: " << rand_row << ", " << rand_column << ", " << rand_width << ", " << rand_height << endl;
			
			// For testing
		//	rand_width = 5; 
		//	rand_height = 5;
		//	rand_row = 0;
		//	rand_column = i * 10;

			roomsf[i] = sf::IntRect(rand_column, rand_row, rand_height, rand_width);
			create_room(roomsf[i], i);

			cout << "roomsf[" << i << "] = " << roomsf[i].left << endl;

			++count;
		}

		//roomsf[0] = sf::IntRect(4, 16, 5, 5);
		//create_room(roomsf[0], 2);
		//roomsf[1] = sf::IntRect(0, 20, 5, 5);
		//create_room(roomsf[1], 3);

		if (roomsf[0].intersects(roomsf[1]))
			cout << "INTERSECTS!!" << endl;

		//cout << "[1] TT r2.left:" << roomsf[1].left << endl;
		//for (int i = 0; i < max_rooms; i++) 
		//	for (int h = 0; h < max_rooms; h++) 
		//	{
		//		// if we are not talking about the same room AND
		//		// if the room we are evaluating is NOT to the right of the second room
		//		if ((h != i) ) 
		//		{
		//			cout << "if (" << roomsf[i].left << " > " << roomsf[h].left << endl;
		//			// Smaller because 0 is left side 10 is right side
		//			if (roomsf[i].left < roomsf[h].left)
		//			{
		//				//cout << "before create_tunnel method: " << endl;
		//				//cout << "[" << h << "] r2.left:" << roomsf[i].left << endl;
		//				create_tunnel(roomsf[i], roomsf[h], h + 1);
		//			}
		//		}
		//	}


		//for (int i = 0; i < max_rooms; i++) 
		//{
		//	cout << "Room " << i + 1 << ": row: " << roomsf[i].left << ", column: " << roomsf[i].top << ", width: " << roomsf[i].width << ", height: " << roomsf[i].height << endl;
		//}

		//                     row, column
		//roomsf[1] = sf::IntRect(0, 5, 5, 5);
		
		//roomsf[0] = sf::IntRect(12, 4, 8, 5);
		//create_room(roomsf[0], 0);
		//roomsf[1] = sf::IntRect(14, 2, 2, 7);
		//create_room(roomsf[1], 1);
		//if (roomsf[0].intersects(roomsf[1]))
		//	cout << "2 Test room intersects!" << endl;

		//if (roomsf[1].intersects(roomsf[0]))
		//	cout << "1 Test room intersects!" << endl;



	}

	//for (int h = 0; h < 10; h++)  
	//{
	//	cout << roomsf[h].left << endl;
	//}



//
//		int max_rooms = 10; // this is also declared in header..
//		int min_room_width = 2;
//		int min_room_height = 2;
//		int max_room_width = 8;
//		int max_room_height = 8;
//
//		for (int i = 0; i < max_rooms; i++) 
//		{
//			int rand_row = (rand() % 30) + 1;
//			int rand_column = (rand() % 30) + 1;
//			int rand_height = rand() % (max_room_height - min_room_height + 1) + min_room_height;
//			int rand_width = rand() % (max_room_width - min_room_width + 1) + min_room_width;
//
//			while (((rand_row + rand_height) > 29))
//				rand_row = (rand() % 30) + 1;
//
//			while (((rand_column + rand_width) > 29))
//				rand_column = (rand() % 30) + 1;
//
//			//cout << "rand_height: " << rand_height << endl;
//			//cout << "rand_width: " << rand_width << endl;
//
//	        //                        row     column  
//
//			// test code to prevent annoyance
//			//rand_width = 5;
//			//rand_height = 5;
//			//rand_row = 0;
//			//if (i == 0)
//			//	rand_row = 4;
//			//rand_column = i * 15;
//			//rand_column = i * 10;
//			//rooms[i] = dungeon_room { rand_row, rand_column, rand_width, rand_height };
//
//			roomsf[i] = sf::IntRect(rand_row, rand_column, rand_width, rand_height); 
//
//			create_room(roomsf[i]);
//			bool does_not_intersect = true;
//			while (!does_not_intersect)
//			{
//				int rand_row = (rand() % 30) + 1;
//				int rand_column = (rand() % 30) + 1;
//				int rand_height = rand() % (max_room_height - min_room_height + 1) + min_room_height;
//				int rand_width = rand() % (max_room_width - min_room_width + 1) + min_room_width;
//
//				while (((rand_row + rand_height) > 29))
//					rand_row = (rand() % 30) + 1;
//
//				while (((rand_column + rand_width) > 29))
//					rand_column = (rand() % 30) + 1;
//
//				for (int ii = 0; ii < max_rooms - 1; ii++)  
//				{
//					if (roomsf[i].intersects(roomsf[ii]))
//					{
//						does_not_intersect = false;
//					}
//				}
//			}
//			//dungeon_room room1 =
//			//{
//			//	0,
//			//	5,
//			//	5
//			//};
//
//
//		}
//
//	}
//	else 
//	{
//		bool dungeon_placed = false;
//		for (int y = 0; y < 30; y++) 
//			for (int x = 0; x < 30; x++) 
//				create_random_tile(x, y, dungeon_placed, false);
//	}
}

void Game::enter_dungeon() 
{
	//for (int y = 0; y < 30; y++)
	//	for (int x = 0; x < 30; x++)
	//		delete tiles[y][x];

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
