#include "game.h"

namespace cotw {

Game::Game()
{
	setup();
	game_loop();
}

Game::~Game()
{
	for (int y = 0; y < 30; y++)
		for (int x = 0; x < 30; x++)
			delete map.tiles[y][x];

	delete player;
}

void Game::handle_key(sf::Event event)
{
	sf::Vector2f current_location = player->get_position();
	int x = current_location.x / 32;
	int y = current_location.y / 32;
	int rand_row = (rand() % 30) + 1;
	int rand_column = (rand() % 30) + 1;

	switch (event.type) 
	{
		case sf::Event::KeyPressed:
			switch (event.key.code) 
			{
				case sf::Keyboard::Numpad8:
					if(valid_move(sf::Vector2<int>(x, y - 1)))
						player->move(sf::Vector2f(0, -player->speed));
					break;

				case sf::Keyboard::Numpad9:
					if(valid_move(sf::Vector2<int>(x + 1, y - 1)))
						player->move(sf::Vector2f(player->speed, -player->speed));
					break;

				case sf::Keyboard::Numpad4:
					if(valid_move(sf::Vector2<int>(x - 1, y)))
						player->move(sf::Vector2f(-player->speed, 0));
					break;

				case sf::Keyboard::Numpad3:
					if(valid_move(sf::Vector2<int>(x + 1, y + 1)))
						player->move(sf::Vector2f(player->speed, player->speed));
					break;

				case sf::Keyboard::Numpad2:
					if(valid_move(sf::Vector2<int>(x, y + 1)))
						player->move(sf::Vector2f(0, player->speed));
					break;

				case sf::Keyboard::Numpad1:
					if(valid_move(sf::Vector2<int>(x - 1, y + 1)))
						player->move(sf::Vector2f(-player->speed, player->speed));
					break;

				case sf::Keyboard::Numpad6:
					if(valid_move(sf::Vector2<int>(x + 1, y)))
						player->move(sf::Vector2f(player->speed, 0));
					break;

				case sf::Keyboard::Numpad7:
					if(valid_move(sf::Vector2<int>(x - 1, y - 1)))
						player->move(sf::Vector2f(-player->speed, -player->speed));
					break;

				case sf::Keyboard::Numpad5:
					std::cout << "There is nothing here to interact with!" << std::endl;
					break;

				case sf::Keyboard::Q:
					std::cout << "Bye." << std::endl;
					window.close();
					break;

				case sf::Keyboard::I:
					player->set_position(sf::Vector2f(rand_row * 32, rand_column * 32));
					break;

				case sf::Keyboard::Return:
					std::cout << "Bye." << std::endl;
					window.close();
					break;

				default:
					//std::cout << "Unhandled key." << std::endl;
					break;
			}
			break;
		default:
			break;
	}
}

bool Game::valid_move(sf::Vector2<int> new_pos)
{
	// Grant wall phasing super power
	//return true;
	if ((new_pos.x == -1) || (new_pos.y == -1) || (new_pos.x > 30) || (new_pos.y > 30))
		return false;
	else if(static_cast<cotw::Tile*>(map.tiles[new_pos.y][new_pos.x])->blocking)
		return false;
	else
		return true;
}

int Game::game_loop()
{
	sf::RenderTexture bitmap;
	sf::Vector2u size = window.getSize();
	float screen_width = size.x;
	float screen_height = size.y;

	if (!bitmap.create(screen_width, screen_height))
		return -1;

    while (window.isOpen())
    {
		sf::Event event;

        while (window.pollEvent(event))
			handle_key(event);

		bitmap.clear(sf::Color::Black);

		sf::RenderStates render_states;

		for (unsigned int y = 0; y < map.tiles.size(); y++)
			for (unsigned int x = 0; x < map.tiles.size(); x++)
				static_cast<cotw::Tile*>(map.tiles[y][x])->draw(bitmap, render_states);

		player->draw(bitmap, render_states);

		bitmap.display();
	    sf::Sprite sprite(bitmap.getTexture());
		window.draw(sprite);
        window.display();
    }

	return 0;
}

void Game::setup() 
{
	sf::VideoMode video_mode(960, 960, 32);
	window.create(video_mode, "Castle of the winds", sf::Style::Titlebar); 

	player = new cotw::Player(texture_manager.get_texture("textures/entity_hero.png"), 0, 0);

	map.create(false);

	//map.enter_dungeon();
}

}
