#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "player.h"
#include "texture_manager.h"

namespace cotw {

struct dungeon_room
{
	int row;
	int column;
	int width; 
	int height;
};

class Game
{

	public:
		Game();
		~Game();
	private:
		std::vector<sf::Texture> TEXTURES;
        sf::RenderWindow window;
		sf::Image img_hero;
		//std::vector< std::vector<sf::Drawable*> > entities;
		dungeon_room rooms[1];
		sf::IntRect roomsf[10];
		//std::vector<dungeon_room> rooms;
		sf::Drawable* tiles [30][30];
		cotw::Player *player;
		cotw::Texture_manager texture_manager;

		void handle_key(sf::Event);
		bool valid_move(sf::Vector2<int>);
		int game_loop();

		void enter_dungeon();
		void fill_empty_map();
		void create_room(sf::IntRect, int);
		void create_tunnel(sf::IntRect, sf::IntRect, int);
		void create_h_tunnel(int, int, int, int);
		void create_v_tunnel(sf::IntRect, sf::IntRect);

		void make_map(bool);
		void setup();
		void create_random_tile(int, int, bool&, bool);
		sf::Texture random_rotate_tile(sf::Image&);
};

}
#endif
