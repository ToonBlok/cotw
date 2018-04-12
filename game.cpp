#include "game.h"

using namespace std;

namespace cotw {

Game::Game()
{
	setup();
	game_loop();
}

Game::~Game()
{
	if (state != cotw::game_state::MAIN_MENU)
		for (unsigned int y = 0; y < map.tiles.size(); y++)
			for (unsigned int x = 0; x < map.tiles.size(); x++)
				delete map.tiles[y][x];

	delete player;
}

void Game::setup() 
{
	sf::VideoMode video_mode(960, 960, 32);
	window.create(video_mode, "Castle of the winds", sf::Style::Titlebar); 
}

void Game::handle_key(sf::Event event)
{
	sf::Vector2f new_coords;

	switch (event.type) 
	{
		case sf::Event::KeyPressed:
		{
			if (state == cotw::game_state::MAIN_MENU)
			{
				switch (event.key.code) 
				{
					case sf::Keyboard::Return:
						state = cotw::game_state::GAME;
						break;
						
					case sf::Keyboard::Q:
						std::cout << "Bye." << std::endl;
						window.close();
						break;

					default:
						//std::cout << "Unhandled key." << std::endl;
						break;
				}
			}
			else
			{
				switch (event.key.code) 
				{
					case sf::Keyboard::Numpad8:
						if(valid_move(sf::Vector2<unsigned int>(player->col, player->row - 1)))
						{
							player->row -= 1;
							new_coords.x = 0;
							new_coords.y = 32;
						}

						break;

					case sf::Keyboard::Numpad9:
						if(valid_move(sf::Vector2<unsigned int>(player->col + 1, player->row - 1)))
						{
							player->col += 1;
							player->row -= 1;

							new_coords.x = -32;
							new_coords.y = 32;
						}
						break;

					case sf::Keyboard::Numpad4:
						if(valid_move(sf::Vector2<unsigned int>(player->col - 1, player->row)))
						{
							player->col -= 1;

							new_coords.x = 32;
							new_coords.y = 0;
						}
						break;

					case sf::Keyboard::Numpad3:
						if(valid_move(sf::Vector2<unsigned int>(player->col + 1, player->row + 1)))
						{
							player->col += 1;
							player->row += 1;

							new_coords.x = -32;
							new_coords.y = -32;
						}
						break;

					case sf::Keyboard::Numpad2:
						if(valid_move(sf::Vector2<unsigned int>(player->col, player->row + 1)))
						{
							player->row += 1;

							new_coords.x = 0;
							new_coords.y = -32;
						}
						break;

					case sf::Keyboard::Numpad1:
						if(valid_move(sf::Vector2<unsigned int>(player->col - 1, player->row + 1)))
						{
							player->col -= 1;
							player->row += 1;

							new_coords.x = 32;
							new_coords.y = -32;
						}
							
						break;

					case sf::Keyboard::Numpad6:
						if(valid_move(sf::Vector2<unsigned int>(player->col + 1, player->row)))
						{
							player->col += 1;

							new_coords.x = -32;
							new_coords.y = 0;
						}
						break;

					case sf::Keyboard::Numpad7:
						if(valid_move(sf::Vector2<unsigned int>(player->col - 1, player->row - 1)))
						{
							player->col -= 1;
							player->row -= 1;

							new_coords.x = 32;
							new_coords.y = 32;
						}
						break;

					case sf::Keyboard::Numpad5:
						// so its in the inventory... but how to draw? give item its own coords? Make add_to_inv method and force to merge image??? hmmmm
						cout << "Loot: ";
						if (static_cast<cotw::Tile*>(map.tiles[player->row][player->col])->inventory.size() == 0)
						{
							cout << "nothing of interest." << endl;
						}
						else
						{
							cotw::Item *p_item = static_cast<cotw::Tile*>(map.tiles[player->row][player->col])->inventory.front();
							cout << p_item->name << endl;
						}
						break;

					case sf::Keyboard::Q:
						std::cout << "Bye." << std::endl;
						window.close();
						break;

					case sf::Keyboard::I:
						cout << "Player at [" << player->row << "][" << player->col << "]." << endl;
						//player->set_position(sf::Vector2f(rand_row * 32, rand_column * 32));
						break;

					case sf::Keyboard::Return:
						std::cout << "Bye." << std::endl;
						window.close();
						break;

					default:
						//std::cout << "Unhandled key." << std::endl;
						break;
				}

				for (unsigned int y = 0; y < map.tiles.size(); y++) 
					for (unsigned int x = 0; x < map.tiles.size(); x++) 
						static_cast<cotw::Tile*>(map.tiles[y][x])->move(new_coords);
			}
		}


			break;
		default:
			break;
	}

}

bool Game::valid_move(sf::Vector2<unsigned int> new_pos)
{
	//cout << new_pos.y << ", " << new_pos.x << ".blocked = " << static_cast<cotw::Tile*>(map.tiles[new_pos.y][new_pos.x])->blocking << endl;
	//Grant wall phasing super power
	//return true;
	if ((new_pos.x < 0) || (new_pos.y < 0) || (new_pos.x >= map.tiles.size()) || (new_pos.y >= map.tiles.size()))
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
	bool setup_done = false;
	cotw::Main_menu menu(size);

	if (!bitmap.create(screen_width, screen_height))
		return -1;

    while (window.isOpen())
    {
		sf::Event event;

        while (window.pollEvent(event))
			handle_key(event);

		bitmap.clear(sf::Color::Black);

		switch (state) 
		{
			case cotw::game_state::MAIN_MENU:
			{
				if (event.type == sf::Event::MouseButtonReleased)
					menu.update(event.mouseButton.x, event.mouseButton.y);

				for (unsigned int y = 0; y < menu.ui_elements.size(); y++)
				{
					cotw::Button *p_button = static_cast<cotw::Button*>(menu.ui_elements[y]);
					cotw::button_state _button_state = p_button->state;
					if (_button_state == cotw::button_state::PRESSED)
					{
						std::string label = p_button->text.getString();
						if (label == "Start")
							state = cotw::game_state::GAME;
						else if (label == "Quit")
							window.close();

					}

				}

				sf::RenderStates render_states;
				menu.draw(bitmap, render_states);
			}
			break;

			case cotw::game_state::GAME:
			{
				if (!setup_done)
				{
					//player = new cotw::Player(texture_manager.get_texture("textures/entity_hero.png"), ((map.tiles.size() / 2) * 32), ((map.tiles.size() / 2) * 32));
					sf::Vector2u size = window.getSize();
					float screen_width = size.x;
					float screen_height = size.y;
					player = new cotw::Player(texture_manager.get_texture("textures/entity_hero.png"), screen_width / 2, screen_height / 2);


					map.create(false);
					map.texture_manager.set_texture("foo");

					//map.enter_dungeon();
					setup_done = true;
				}

				for (unsigned int y = 0; y < map.tiles.size(); y++)
				{
					for (unsigned int x = 0; x < map.tiles.size(); x++)
					{
						sf::RenderStates render_states;
						static_cast<cotw::Tile*>(map.tiles[y][x])->draw(bitmap, render_states);
					}
				}

				sf::Image item_image;
				item_image.loadFromFile("textures/item_flail.png");
				cotw::Item flail("flail", item_image, false);
				static_cast<cotw::Tile*>(map.tiles[14][15])->overlay_texture(flail.image);
				static_cast<cotw::Tile*>(map.tiles[14][15])->inventory.push_back(new cotw::Item("flail", item_image, false));

				sf::RenderStates render_states;
				player->draw(bitmap, render_states);

			}
			break;

			default:
				break;
		}

		bitmap.display();
		sf::Sprite sprite(bitmap.getTexture());
		window.draw(sprite);
		//window.draw(hole);
		window.display();

    }


	return 0;
}


}
