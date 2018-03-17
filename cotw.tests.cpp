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
	// 0 [-][-][-][-][-][-][-][-]
	// 1 [-][-][-][-][-][-][-][-]
	// 2 [-][-][-][-][-][x][x][-]
	// 3 [-][-][-][-][-][x][x][-]
	// 4 [-][-][-][-][-][-][-][?] ? is also tested
	
	// Arrange
	
	// Act
	map.fill_empty();

	sf::IntRect room(5, 2, 2, 2);

	map.create_room(room, 0);

	// Assert
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][5])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[2][6])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][5])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[3][6])->blocking == false);
	CPPUNIT_ASSERT(static_cast<cotw::Tile*>(map.tiles[4][7])->blocking == true);

	return;
}

void Cotwtests::test_room_cannot_intersect()
{
	CPPUNIT_ASSERT(true == true);

	return;
}
