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
	int max_spawn_chance = 100;
	int rand_num_tile = rand() % (max_spawn_chance - 1 + 1) + 1;
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
	else if ((rand_num_tile >= 20) && (rand_num_tile < 21)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant5.png");
		//blocking = true;
	}
	else if ((rand_num_tile >= 21) && (rand_num_tile < 22)) 
	{
		texture = texture_manager.get_texture("textures/tile_plant6.png");
		blocking = true;
	}
	else if ((rand_num_tile >= 22) && (rand_num_tile < 25)) 
	{
		if (rand_num_tile >= 22 && rand_num_tile <= 23)
			texture = texture_manager.get_texture("textures/tile_rock.png");
		else
			texture = texture_manager.get_texture("textures/tile_rock2.png");

		blocking = true;
	}
	else if ((rand_num_tile >= 25) && (rand_num_tile < 26)) 
	{
		texture = texture_manager.get_texture("textures/tile_grass_mushrooms.png");
		blocking = true;
	}
	else if (rand_num_tile >= 26)
	{
		texture = texture_manager.get_texture("textures/tile_grass.png");
		if (rand_num_tile > 50)
		{
			sf::Image image = texture.copyToImage();
			image.flipVertically();
			if (!texture.loadFromImage(image))
				cout << "texture was not found!" << endl; 
		}
	}

	int flip = rand() % (1 - 0 + 1) + 0;
	if (flip == 0)
		flip_tile_h(texture);

	tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, blocking);
}

void Map::flip_tile_h(sf::Texture& texture) 
{
    // int rand_num_tile_rotation = (rand() % 2);

	// if (rand_num_tile_rotation == 0)
	// 	image.flipHorizontally();
	// else if (rand_num_tile_rotation == 1)
	// 	image.flipVertically();

	sf::Image image = texture.copyToImage();
	image.flipHorizontally();
	if (!texture.loadFromImage(image))
		cout << "texture was not found!" << endl; 

}

void Map::create(bool in_dungeon) 
{
	bool dungeon_placed = false;
	if (in_dungeon)
	{
		fill_empty();
		create_rooms();
		//std::vector<sf::IntRect> unconnected_rooms = get_unconnected_rooms();
		//for (unsigned int i = 0; i < unconnected_rooms.size(); i++) 
		//	create_tunnel(unconnected_rooms[i]);
		for (unsigned int i = 0; i < rooms.size(); i++) 
		{
			cout << i << " going into create tunnel" << endl;
			create_tunnel(rooms[i]);
		}
	}
	else
	{

		for (unsigned int y = 0; y < tiles.size(); y++) 
			for (unsigned int x = 0; x < tiles.size(); x++) 
				create_random_tile(x, y, dungeon_placed, false);

		overlay_special_tiles();

		// if true is present then overlay the image using copyToImage() method
		//static_cast<cotw::Tile*>(tiles[14][15])->set_texture(texture_manager.get_texture("textures/copper.png"));

	}
}

void Map::overlay_special_tiles() 
{
	std::vector<sf::IntRect> all_clusters;
	tile_clusters tile_cluster = tile_clusters::tree;
	create_tile_clusters(tile_cluster, all_clusters);

	tile_cluster = tile_clusters::thintree;
	create_tile_clusters(tile_cluster, all_clusters);
	
	tile_cluster = tile_clusters::log;
	create_tile_clusters(tile_cluster, all_clusters);
}


void Map::create_tile_clusters(cotw::tile_clusters tile_cluster, std::vector<sf::IntRect>& all_clusters) 
{
	int height;
	int width;
	int max_spawn_chance = 1000;
	int spawn_chance;

	if (tile_cluster == tile_clusters::tree)
	{
		height = 2;
		width = 2;
		spawn_chance = 10;
	}
	else if (tile_cluster == tile_clusters::thintree)
	{
		height = 2;
		width = 1;
		spawn_chance = 1;
	}
	else if (tile_cluster == tile_clusters::log)
	{
		height = 1;
		width = 2;
		spawn_chance = 1;
	}

	// Change from user readable 1% to 10 which is 1% of 1000.
	// noooo then dev cant enter below 1%
	//spawn_chance *= 10;

	// no.... if grass field must redetermine size each time not once here...
	//else if (tile_cluster == tile_clusters::grassfield)
	//{
	//	int rand_num = rand() % (100 - 1 + 1) + 1;
	//	int rand_num = rand() % (100 - 1 + 1) + 1;
	//	height = 2;
	//	width = 2;
	//	spawn_chance = 100 - 30;
	//}

	std::vector<sf::IntRect> clusters;

	for (unsigned int row = 0; row < tiles.size(); row++) 
	{
		for (unsigned int col = 0; col < tiles.size(); col++) 
		{
			if (row + height - 1 < tiles.size() && col + width - 1 < tiles.size())
			{
				int rand_num = rand() % (max_spawn_chance - 1 + 1) + 1;
				if (rand_num <= spawn_chance)
				{
					// col, row, width, height
					//cout << "eternal" << endl;

					sf::IntRect special(col, row, width, height);
					//cout << "Made special:" << col << ", " << row << " 2, 2" << endl;

					if (clusters.size() == 0)
					{
						clusters.push_back(special);
						all_clusters.push_back(special);
					}
					else
					{
						bool intersects = false;
						for (unsigned int i = 0; i < all_clusters.size(); i++) 
						{
							//cout << "special.left = " << special.left << ", special.top = " << special.top << endl;
							//cout << "tile_clusters[" << i << "].left = " << tile_clusters[i].left << ", tile_clusters[" << i << "].top = " << tile_clusters[i].top << endl;
							if (special.intersects(all_clusters[i]))
							{
								//cout << "INTERSECTS!!" << endl;
								intersects = true;
							}
						}
						if (!intersects)
						{
							clusters.push_back(special);
							all_clusters.push_back(special);
						}

					}

				}
			}
		}
	}

	for (unsigned int i = 0; i < clusters.size(); i++) 
	{
		if (tile_cluster == tile_clusters::tree)
			create_tree(clusters[i]);
		else if (tile_cluster == tile_clusters::thintree)
			create_thintree(clusters[i]);
		else if (tile_cluster == tile_clusters::log)
			create_log(clusters[i]);
	}

	cout << "tile_clusters: " << clusters.size() << endl;

}

void Map::create_thintree(sf::IntRect tree) 
{
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->set_texture(texture_manager.get_texture("textures/tile_tree_thin_n2.png"));
	static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left])->set_texture(texture_manager.get_texture("textures/tile_tree_thin_s2.png"));

	static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->blocking = false;
	static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left])->blocking = false;
}

void Map::create_log(sf::IntRect tree) 
{
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->set_texture(texture_manager.get_texture("textures/tile_log_w.png"));
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left + 1])->set_texture(texture_manager.get_texture("textures/tile_log_e.png"));

	static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->blocking = true;
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left + 1])->blocking = true;
}

void Map::create_tree(sf::IntRect tree) 
{
	                            // row      col
	// Light green tree
	//static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->set_texture(texture_manager.get_texture("textures/tile_tree_nw.png"));
	//static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left])->set_texture(texture_manager.get_texture("textures/tile_tree_sw.png"));
	//static_cast<cotw::Tile*>(tiles[tree.top][tree.left + 1])->set_texture(texture_manager.get_texture("textures/tile_tree_ne.png"));
	//static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left + 1])->set_texture(texture_manager.get_texture("textures/tile_tree_se.png"));

	// Dark green tree
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->set_texture(texture_manager.get_texture("textures/tile_darktree_nw.png"));
	static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left])->set_texture(texture_manager.get_texture("textures/tile_darktree_sw.png"));
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left + 1])->set_texture(texture_manager.get_texture("textures/tile_darktree_ne.png"));
	static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left + 1])->set_texture(texture_manager.get_texture("textures/tile_darktree_se.png"));

	static_cast<cotw::Tile*>(tiles[tree.top][tree.left])->blocking = true;
	static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left])->blocking = true;
	static_cast<cotw::Tile*>(tiles[tree.top][tree.left + 1])->blocking = true;
	static_cast<cotw::Tile*>(tiles[tree.top + 1][tree.left + 1])->blocking = true;
}

void Map::create_grassfields() 
{
	// needs to be dynamic... can be big sometimes and sometimes small

}

void Map::fill_empty() 
{
	sf::Texture texture = texture_manager.get_texture("textures/dungeon/tile_dungeon_wall1_test.png");

	for (unsigned int y = 0; y < tiles.size(); y++) 
		for (unsigned int x = 0; x < tiles.size(); x++) 
			tiles[y][x] = new cotw::Tile(texture, x * 32, y * 32, 1);
}

void Map::create_rooms() 
{
	int min_room_width = 2;
	int min_room_height = 2;
	int max_room_width = 5;
	int max_room_height = 5;

	bool does_not_intersect;
	for (unsigned int i = 0; i < rooms.size(); i++) 
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

			for (unsigned int h = 0; h < rooms.size(); h++)  
			{
				if (room.intersects(rooms[h]))
					does_not_intersect = false;
				if ( ((room.left + room.width) > 30) || ((room.top + room.height) > 30) )
					does_not_intersect = false;
			}
		}
		while (!does_not_intersect);
		
		rand_width = 5; 
		rand_height = 5;

		if (i == 0)
		{
			rand_row = 1;
			rand_column = 1;
		}
		else if (i == 1)
		{
			rand_row = 1;
			rand_column = 10;
			//rand_row = 10;
			//rand_column = 1;
		}
		else if (i == 2)
		{
			rand_row = 10;
			rand_column = 10;
		}
		else if (i == 3)
		{
			rand_row = 10;
			rand_column = 1;
		}
		else if (i == 4)
		{
			rand_row = 10;
			rand_column = 20;
			//rand_row = 20;
			//rand_column = 20;
		}
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
			// replaced from < 30..
			if (((unsigned int)(room.left + iy) < tiles.size()) && ((unsigned int)(room.top + ix) < tiles.size()))
			{
				//cout << "Creating room " << index + 1 << " at: [" << room.top + ix << "][" << room.left + iy << "]" << endl;
				//static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->set_texture(texture_manager.get_texture("textures/dungeon/" + std::to_sing(index + 1) + "tile_dungeon_floor1.png"));
				static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
				static_cast<cotw::Tile*>(tiles[room.top + ix][room.left + iy])->blocking = 0;
			}

		}
	}
}

std::vector<sf::IntRect> Map::get_unconnected_rooms() 
{
	std::vector<int> connected_rooms;

	for (unsigned int i = 0; i < rooms.size(); i++) 
	{
		if ((i + 1) < rooms.size())
		{
			sf::IntRect room = rooms[i];
			room.left -= 1;
			room.top -= 1;
			room.width += 2;
			room.height += 2;

			for (unsigned int h = 0; h < rooms.size(); h++) 
				if (h != i)
					if (room.intersects(rooms[h]))
					{
						//connected_rooms.push_back(rooms[i]);
						connected_rooms.push_back(i);
						
						// If room [i] happens to connect with the last room in the array, go ahead and add the last room in the array too.
						// This is done because we don't check if the last room is connected, but it must be in the array anyway.
						if (h == (rooms.size() - 1))
						{
							//connected_rooms.push_back(rooms[h]);
							connected_rooms.push_back(h);
						}

						++h;
					}

		}
	}

	std::vector<sf::IntRect> unconnected_rooms;

//	cout << "In get method:" << endl;
	for (unsigned int i = 0; i < rooms.size(); i++) 
	{
		if (!(std::find(connected_rooms.begin(), connected_rooms.end(), i) != connected_rooms.end()))
		{
			//cout << "Added room " << i + 1 << " to list of unconnected rooms" << endl;
			unconnected_rooms.push_back(rooms[i]);
		}
	}

	for (unsigned int i = 0; i < connected_rooms.size(); i++) 
		cout << "Room " << connected_rooms[i] + 1 << " is connected somewhere." << endl;

	return unconnected_rooms;

}

void Map::create_h_tunnel(int start_col, int end_col, int row) 
{
	for (int col = start_col; col < end_col + 1; col++) 
	{
		static_cast<cotw::Tile*>(tiles[row][col])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
		static_cast<cotw::Tile*>(tiles[row][col])->blocking = 0;
	}
}

void Map::create_v_tunnel(int start_row, int end_row, int col) 
{
	for (int row = start_row; row < end_row; row++) 
	{
		static_cast<cotw::Tile*>(tiles[row][col])->set_texture(texture_manager.get_texture("textures/dungeon/tile_dungeon_floor1.png"));
		static_cast<cotw::Tile*>(tiles[row][col])->blocking = 0;
	}
}

// Sole responsibility of this method is to connect this room to ANY other room
void Map::create_tunnel(sf::IntRect room) 
{
	// Scanning algorithm NORTH
	// --------------------------------------------------------------
	room.top -= 1;
	for (int i = room.left; i < (room.left + room.width); i++) 
	{
		for (int h = room.top; h > 0; h--) 
		{
			for (unsigned int g = 0; g < tiles.size(); g++) 
			{
				if (static_cast<cotw::Tile*>(tiles[h][g])->blocking == 0)
				{
					//cout << "At tiles[" << h << "][" << g << "] there is a open room." << endl;
				}
			}

			//cout << "Checking tiles[" << h << "][" << i << "]." << endl;
			if (static_cast<cotw::Tile*>(tiles[h - 1][i])->blocking == 0)
			{
				cout << "Making tunnel NORTH" << endl;
				create_v_tunnel(h, room.top + 1, i);
				return;
			}
		}
	}
	// Fix changes from first changes
	room.top += 1;
	// --------------------------------------------------------------

	cout << endl;

	// Scanning algorithm EAST
	// --------------------------------------------------------------
	for (int row = room.top; row < (room.top + room.height); row++) 
	{
		for (unsigned int col = (room.left + room.width); col < tiles.size(); col++) 
		{
			//cout << "Checking tiles[" << row << "][" << col << "]." << endl;
			if ((col + 1) > tiles.size() - 1)
			{
				row = room.top + room.height;
				col = tiles.size();
			}
			else if (static_cast<cotw::Tile*>(tiles[row][col + 1])->blocking == 0)
			{
				cout << "Making tunnel EAST" << endl;
				create_h_tunnel(room.left + room.width, col, row);
				return;
			}

		}
	}
	// --------------------------------------------------------------

	// Scanning algorithm WEST
	// --------------------------------------------------------------
	room.left -= 1;
	for (int row = room.top; row < (room.left + room.height); row++) 
	{
		for (int col = room.left; col > 0; col--) 
		{
			if (static_cast<cotw::Tile*>(tiles[row][col - 1])->blocking == 0)
			{
				cout << "Making tunnel WEST" << endl;
				create_h_tunnel(col, room.left, row);
				return;
			}

		}
	}
	// --------------------------------------------------------------
	// Scanning algorithm SOUTH
	// --------------------------------------------------------------
	cout << room.left << " to " << room.left + room.width << endl;
	for (int i = room.left; i < room.left + room.width; i++) 
	{
		for (unsigned int h = room.top + room.height; h < tiles.size(); h++) 
		{
			//cout << "Checking tiles[" << h << "][" << i << "]." << endl;
			if ((h + 1) == tiles.size())
			{
				i = room.left + room.width;
				h = tiles.size();
			}
			else if (static_cast<cotw::Tile*>(tiles[h + 1][i])->blocking == 0)
			{
				cout << "Making tunnel SOUTH" << endl;
				create_v_tunnel(room.top + room.height, h + 1, i);
				return;
			}
		}
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
