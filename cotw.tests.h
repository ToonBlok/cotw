#ifndef COTW_TESTS_H
#define COTW_TESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include <SFML/Graphics.hpp>
#include "map.h"

class Cotwtests: public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( Cotwtests ); // Note 3 
	CPPUNIT_TEST( test_misc );
	CPPUNIT_TEST( test_fill_empty );
	CPPUNIT_TEST( test_create_room );
	CPPUNIT_TEST( test_create_tunnel );
	CPPUNIT_TEST( test_create_random_tunnel );
	CPPUNIT_TEST_SUITE_END();

	public:
		cotw::Map map;

		void setUp();
		void tearDown();

		void test_misc();
		void test_fill_empty();
		void test_create_room();
		void test_create_tunnel();
		void test_create_random_tunnel();
};

#endif
