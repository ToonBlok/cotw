#include <iostream>
#include "map.h"

using namespace std;

namespace cotw {

Map::Map()
{
	srand(time(0));
}

Map::~Map()
{

}

void Map::create_random_tile(int x, int y, bool& dungeon_placed, bool in_dungeon) 
{
	int rand_num_tile = (rand() % 100) + 1;
	sf::Texture texture;
	
	bool blocking = false;
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
		blocking = true;
	}
	else if ((rand_num_tile >= 25) && (rand_num_tile < 30)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant6.png");
		blocking = true;
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
			blocking = true;
		}
	}
	else if ((rand_num_tile >= 31) && (rand_num_tile < 37)) 
	{
		texture = texture_manager.get_texture("textures/tile_hole2.png");
		blocking = true;
	}
	else if (rand_num_tile >= 37) 
	{
		texture = texture_manager.get_texture("textures/tile_grass.png");
	}

	tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, blocking);
}

sf::Texture Map::random_rotate_tile(sf::Image& image) 
{
	int rand_num_tile_rotation = (rand() % 2);

	if (rand_num_tile_rotation == 0)
		image.flipHorizontally();
	else if (rand_num_tile_rotation == 1)
		image.flipVertically();
}


void Map::create_tunnels() 
{
	for (int i = 0; i < rooms.size(); i++) 
		for (int h = 0; h < rooms.size(); h++) 
			if ((h != i) ) 
				if (rooms[i].left < rooms[h].left)
					  create_tunnel(rooms[i], rooms[h], h + 1);
}

void Map::create(bool in_dungeon) 
{
	if (in_dungeon)
	{
		fill_empty();
		create_rooms();
		std::vector<sf::IntRect> connected_rooms = get_connected_rooms();
	}
}

void Map::fill_empty() 
{
	sf::Texture texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_wall1_test.png");

	for (int y = 0; y < 30; y++) 
		for (int x = 0; x < 30; x++) 
			tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, 1);
}

void Map::create_rooms() 
{
	int min_room_width = 2;
	int min_room_height = 2;
	int max_room_width = 5;
	int max_room_height = 5;

	bool does_not_intersect;
	for (int i = 0; i < rooms.size(); i++) 
	{
		int rand_row;
		int rand_column;
		int rand_height;
		int rand_width; 

		do
		{
			does_not_intersect = true;
			rand_row = (rand() % 30) + 1;
			rand_column = (rand() % 30) + 1;
			rand_height = rand() % (max_room_height - min_room_height + 1) + min_room_height;
			rand_width = rand() % (max_room_width - min_room_width + 1) + min_room_width;
			sf::IntRect room(rand_column, rand_row, rand_width, rand_height);

			for (int h = 0; h < rooms.size(); h++)  
			{
				if (room.intersects(rooms[h]))
					does_not_intersect = false;
				if ( ((room.left + room.width) > 30) || ((room.top + room.height) > 30) )
					does_not_intersect = false;
			}
		}
		while (!does_not_intersect);
		
	//	rand_width = 5; 
	//	rand_height = 5;
	//	rand_row = 0;
	//	rand_column = i * 10;

		//cout << "Adding room " << i + 1 << " at: [" << rand_row << "][" << rand_column << "] with width: " << rand_width << " and height: " << rand_height << endl;
		rooms[i] = sf::IntRect(rand_column, rand_row, rand_width, rand_height);
		create_room(rooms[i], i);
	}
}

void Map::create_room(sf::IntRect room, int index) 
{
	for (int iy = 0; iy < room.width; iy++)
	{
		for (int ix = 0; ix < room.height; ix++)
		{
			if (((room.left + iy) < 30) && ((room.top + ix) < 30))
			{
				//cout << "Creating room " << index + 1 << " at: [" << room.top + ix << "][" << room.left + iy << "]" << endl;
				static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->set_texture(texture_manager.get_texture("textures/dungeon/" + std::to_string(index + 1) + "tile_dungeon_floor1.png"));
				//static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
				static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->blocking = 0;
			}

		}
	}
}

std::vector<sf::IntRect> Map::get_connected_rooms() 
{
	std::vector<sf::IntRect> connected_rooms;
	std::vector<int> test_connected_rooms;

	for (int i = 0; i < rooms.size(); i++) 
	{
		if ((i + 1) < rooms.size())
		{
			sf::IntRect room = rooms[i];
			room.left -= 1;
			room.top -= 1;
			room.width += 2;
			room.height += 2;

			for (int h = 0; h < rooms.size(); h++) 
				if (h != i)
					if (room.intersects(rooms[h]))
					{
						connected_rooms.push_back(rooms[i]);
						test_connected_rooms.push_back(i);
						
						// If room [i] happens to connect with the last room in the array, go ahead and add the last room in the array too.
						// This is done because we don't check if the last room is connected, but it must be in the array anyway.
						if (h == (rooms.size() - 1))
						{
							connected_rooms.push_back(rooms[h]);
							test_connected_rooms.push_back(h);
						}

						++h;
					}

		}
	}

	cout << "In get method:" << endl;
	for (int i = 0; i < test_connected_rooms.size(); i++) 
		cout << "Room " << test_connected_rooms[i] + 1 << " is connected somewhere." << endl;

	cout << test_connected_rooms.size() << endl;

	return connected_rooms;

}

void Map::create_h_tunnel(int r1_left, int r1_width, int r2_left, int rand_tunnel_entrance) 
{
	for (int i = (r1_left + r1_width); i < r2_left; i++)
	{
		static_cast<cotw::Tile*>(tiles[rand_tunnel_entrance][i])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
		static_cast<cotw::Tile*>(tiles[rand_tunnel_entrance][i])->blocking = 0;
	}
}

void Map::create_v_tunnel(sf::IntRect room1, sf::IntRect room2) 
{

}

void Map::create_tunnel(sf::IntRect r1, sf::IntRect r2, int index) 
{
	std::vector<int> possible_entrances;

	for (int i = r1.top; i < (r1.top + r1.height); i++)
	{
		if ((i >= r2.top) && (i < (r2.top + r2.height)))
			possible_entrances.push_back(i);
	}

	if (possible_entrances.size() != 0)
	{
		int highest = possible_entrances.back();
		int lowest = possible_entrances.front();
		int rand_tunnel_entrance = rand() % (highest - lowest + 1) + lowest;

		create_h_tunnel(r1.left, r1.width, r2.left, rand_tunnel_entrance);
	}
}

void Map::enter_dungeon() 
{
	//for (int y = 0; y < 30; y++)
	//	for (int x = 0; x < 30; x++)
	//		delete map.tiles[y][x];

	create(true);
}

}
