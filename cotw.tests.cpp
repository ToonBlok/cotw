#include <cppunit/config/SourcePrefix.h>
#include "cotw.tests.h"

void Cotwtests::setUp()
{
}

void Cotwtests::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( Cotwtests ); 

void Cotwtests::test_misc()
{  
	// Arrange
	
	// Act
	map.fill_empty();

	// Assert

	// Are there 30 arrays in map.tiles
	CPPUNIT_ASSERT(map.tiles.size() == 30);
	
	// Are there 30 * 30 arrays in map.tiles
	for (int i = 0; i < map.tiles.size(); i++)
		CPPUNIT_ASSERT(map.tiles[i].size() == 30);
}

void Cotwtests::test_fill_empty()
{  
	// Arrange
	
	// Act
	map.fill_empty();

	// Assert
	// Is the tile at [5][5] a blocking wall, as it should be?
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[5][5])->blocking == true);

	return;
}

// Create a room and test 
void Cotwtests::test_create_room()
{
    //    0  1  2  3  4  5  6  7
	// 0 [ ][ ][ ][ ][ ][ ][ ][ ]
	// 1 [ ][ ][ ][ ][ ][ ][ ][ ]
	// 2 [ ][ ][ ][ ][ ][x][x][ ]
	// 3 [ ][ ][ ][ ][ ][x][x][ ]
	// 4 [ ][ ][ ][ ][ ][x][x][?] ? is also tested
	
	// Arrange
	
	// Act
	map.fill_empty();
	sf::IntRect room(5, 2, 2, 3);
	map.create_room(room, 0);
	//get_visual_feedback();

	// Assert
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][5])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][6])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][5])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][6])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[4][5])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[4][6])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[4][7])->blocking == true);

	return;
}

void Cotwtests::get_visual_feedback()
{
	std::cout << std::endl;
	for (int i = 0; i < map.tiles.size(); i++)
	{
		if (i == 0)
		{
			std::cout << "  ";
			for (int x = 0; x < map.tiles.size(); x++)
			{
				if (x < 10)
					std::cout << "0" << x << " ";
				else
					std::cout << x << " ";
			}
			std::cout << std::endl;

		}

		for (int h = 0; h < map.tiles[i].size(); h++)
		{
			if (h == 0)
			{
				if (i < 10)
					std::cout << "0" << i;
				else
					std::cout << i;
			}

			if (static_cast<cotw::Tile*>(map.tiles[i][h])->blocking)
				std::cout << "[ ]";
			else
				std::cout << "[x]";
		}
		std::cout << std::endl;

	}

	std::cout << std::endl;
}

void Cotwtests::test_create_tunnel()
{
	// Expected result:
    //    0  1  2  3  4  5  6  7  8
	// 0 [ ][ ][ ][ ][ ][ ][ ][ ][ ]
	// 1 [ ][x][x][ ][ ][ ][x][x][ ]
	// 2 [ ][x][x][x][x][x][x][x][ ]
	// 3 [ ][x][x][ ][ ][ ][x][x][ ]
	// 4 [ ][ ][ ][ ][ ][ ][ ][ ][ ] 
	
	// Arrange
	sf::IntRect room_west(1, 1, 2, 3);
	sf::IntRect room_east(6, 1, 2, 3);
	
	// Act
	map.fill_empty();

	map.create_room(room_west, 0);
	map.create_room(room_east, 1);

//void Map::create_h_tunnel(int r1_left, int r1_width, int r2_left, int rand_tunnel_entrance) 
	map.create_h_tunnel(room_west.left, room_west.width, room_east.left, 2);

	// Assert
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[1][3])->blocking == true);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[1][4])->blocking == true);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[1][4])->blocking == true);

	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][3])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][4])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][5])->blocking == false);

	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][3])->blocking == true);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][4])->blocking == true);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][4])->blocking == true);
	//create_tunnel(rooms[i], rooms[h], h + 1);

	return;
}

// Create a horizontal tunnel at a random place between two rooms. Check if tunnel is made and if all the 
// other possible places where a tunnel could have been created were left untouched.
void Cotwtests::test_create_random_tunnel()
{
	// Expected result:
	// At one row a tunnel is created
    //    0  1  2  3  4  5  6  7  8
	// 0 [ ][ ][ ][ ][ ][ ][ ][ ][ ]
	// 1 [ ][x][x][?][?][?][x][x][ ]
	// 2 [ ][x][x][?][?][?][x][x][ ]
	// 3 [ ][x][x][?][?][?][x][x][ ]
	// 4 [ ][ ][ ][ ][ ][ ][ ][ ][ ] 
	
	// Arrange
	sf::IntRect room_west(1, 1, 2, 3);
	sf::IntRect room_east(6, 1, 2, 3);
	bool passed = false;
	int tunnel_created_at;
	
	// Act
	map.fill_empty();

	map.create_room(room_west, 0);
	map.create_room(room_east, 1);

	map.create_tunnel(room_west, room_east, 0);


	for (int i = 1; i < 4; i++)
	{
		if ( (static_cast<cotw::Tile*>(map.tiles[i][3])->blocking == false) &&
			 (static_cast<cotw::Tile*>(map.tiles[i][4])->blocking == false) &&
			 (static_cast<cotw::Tile*>(map.tiles[i][5])->blocking == false) )
		{
			//std::cout << "found tunnel at " << i << std::endl;
			passed = true;
			tunnel_created_at = i;
		}
	}

	for (int i = 1; i < 4; i++)
	{
		if (i != tunnel_created_at)
		{
			//std::cout << "testing for walls at " << i << std::endl;
			if ( (static_cast<cotw::Tile*>(map.tiles[i][3])->blocking == true) &&
				 (static_cast<cotw::Tile*>(map.tiles[i][4])->blocking == true) &&
				 (static_cast<cotw::Tile*>(map.tiles[i][5])->blocking == true) )
			{
				passed = true;
			}
			else
			{
				passed = false;
			}
		}
	}

	// Assert
	CPPUNIT_ASSERT(passed == true);
	//get_visual_feedback();

}
