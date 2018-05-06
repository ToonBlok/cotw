#include <iostream>
#include "InGameState.h"
#include "GameStateManager.h"

using namespace std;

namespace cotw {

InGameState::InGameState(cotw::GameStateManager* _game_state_manager, sf::Vector2u window_size) 
{
	game_state_manager = _game_state_manager;
	float smx = window_size.x / 2;
	float smy = window_size.y / 2;

	//sf::Vector2u size = window.getSize();
	//float screen_width = size.x;
	//float screen_height = size.y;
	player = new cotw::Player(texture_manager.get_texture("textures/entity_hero.png"), smx, smy);
	map.create(false);

	sf::Texture tex_console(texture_manager.get_texture("textures/screens/console.png"));
	console = new cotw::Console
	(
		tex_console, 
		"", 
		sf::Vector2f(0, window_size.y - tex_console.getSize().y), 
		tex_console.getSize().x + 500, 
		tex_console.getSize().y
	);

	ui_elements[0] = console;

	// ## DEBUG: Clear starting area and add test items ##
	for (unsigned int x = 10; x < 21; x++)
	{
		for (unsigned int y = 10; y < 21; y++)
		{
			static_cast<cotw::Tile*>(map.tiles[y][x])->blocking = false;
			static_cast<cotw::Tile*>(map.tiles[y][x])->set_texture(texture_manager.get_texture("textures/tile_grass.png"));
		}
	}
	sf::Image item_image;
	item_image.loadFromFile("textures/item_flail.png");
	cotw::Item flail("flail", item_image, false);
	static_cast<cotw::Tile*>(map.tiles[14][15])->overlay_texture(flail.image);
	static_cast<cotw::Tile*>(map.tiles[14][15])->inventory.push_back(new cotw::Item("flail", item_image, false));

	sf::Image item_image2;
	item_image2.loadFromFile("textures/chest_closed.png");
	cotw::Item chest("chest", item_image2, false);
	static_cast<cotw::Tile*>(map.tiles[14][16])->overlay_texture(chest.image);
	static_cast<cotw::Tile*>(map.tiles[14][16])->inventory.push_back(new cotw::Item("chest", item_image2, false));

	sf::Image item_image3;
	item_image3.loadFromFile("textures/treasure.png");
	cotw::Item treasure("chest", item_image3, false);
	static_cast<cotw::Tile*>(map.tiles[14][14])->overlay_texture(treasure.image);
	static_cast<cotw::Tile*>(map.tiles[14][14])->inventory.push_back(new cotw::Item("treasure", item_image3, false));
	// ## END DEBUG ##

}

InGameState::~InGameState() 
{
	for (unsigned int y = 0; y < map.tiles.size(); y++)
		for (unsigned int x = 0; x < map.tiles.size(); x++)
			delete map.tiles[y][x];
}

bool InGameState::valid_move(sf::Vector2<unsigned int> new_pos)
{
	//Grant wall phasing super power
	//return true;
	if ((new_pos.x < 0) || (new_pos.y < 0) || (new_pos.x >= map.tiles.size()) || (new_pos.y >= map.tiles.size()))
		return false;
	else if (static_cast<cotw::Tile*>(map.tiles[new_pos.y][new_pos.x])->blocking)
		return false;
	else
		return true;
}

void InGameState::on_notify(cotw::Event)
{
}

void InGameState::change_state(cotw::GameStateManager* game_state_manager, cotw::State state)
{
	game_state_manager->set_state(state);
}


void InGameState::update(sf::RenderWindow& window) 
{
	sf::Event event;

	while (window.pollEvent(event))
		handle_key(window, event);

	console->update();
}

void InGameState::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
	for (unsigned int y = 0; y < map.tiles.size(); y++)
	{
		for (unsigned int x = 0; x < map.tiles.size(); x++)
		{
			sf::RenderStates render_states;
			static_cast<cotw::Tile*>(map.tiles[y][x])->draw(render_target, render_states);
		}
	}

	player->draw(render_target, render_states);

	for (unsigned int i = 0; i < ui_elements.size(); i++)
		static_cast<cotw::Button*>(ui_elements[i])->draw(render_target, render_states);

}

void InGameState::handle_key(sf::RenderWindow& window, sf::Event event)
{
	sf::Vector2f new_move;

	switch (event.type) 
	{
		case sf::Event::KeyPressed:
		{
			switch (event.key.code) 
			{
				case sf::Keyboard::Numpad8:
					if(valid_move(sf::Vector2<unsigned int>(player->col, player->row - 1)))
					{
						player->row -= 1;
						new_move.x = 0;
						new_move.y = 32;
					}
					break;

				case sf::Keyboard::Numpad9:
					if(valid_move(sf::Vector2<unsigned int>(player->col + 1, player->row - 1)))
					{
						player->col += 1;
						player->row -= 1;
						new_move.x = -32;
						new_move.y = 32;
					}
					break;

				case sf::Keyboard::Numpad4:
					if(valid_move(sf::Vector2<unsigned int>(player->col - 1, player->row)))
					{
						player->col -= 1;
						new_move.x = 32;
						new_move.y = 0;
					}
					break;

				case sf::Keyboard::Numpad3:
					if(valid_move(sf::Vector2<unsigned int>(player->col + 1, player->row + 1)))
					{
						player->col += 1;
						player->row += 1;
						new_move.x = -32;
						new_move.y = -32;
					}
					break;

				case sf::Keyboard::Numpad2:
					if(valid_move(sf::Vector2<unsigned int>(player->col, player->row + 1)))
					{
						player->row += 1;
						new_move.x = 0;
						new_move.y = -32;
					}
					break;

				case sf::Keyboard::Numpad1:
					if(valid_move(sf::Vector2<unsigned int>(player->col - 1, player->row + 1)))
					{
						player->col -= 1;
						player->row += 1;
						new_move.x = 32;
						new_move.y = -32;
					}
						
					break;

				case sf::Keyboard::Numpad6:
					if(valid_move(sf::Vector2<unsigned int>(player->col + 1, player->row)))
					{
						player->col += 1;
						new_move.x = -32;
						new_move.y = 0;
					}
					break;

				case sf::Keyboard::Numpad7:
					if(valid_move(sf::Vector2<unsigned int>(player->col - 1, player->row - 1)))
					{
						player->col -= 1;
						player->row -= 1;
						new_move.x = 32;
						new_move.y = 32;
					}
					break;

				case sf::Keyboard::Numpad5:
					// so its in the inventory... but how to draw? give item its own coords? Make add_to_inv method and force to merge image??? hmmmm
					cout << "Loot: ";
					if (static_cast<cotw::Tile*>(map.tiles[player->row][player->col])->inventory.size() == 0)
					{
						cout << "nothing of interest." << endl;
						console->log(("Nothing to interact with here."), sf::Color::White);
					}
					else
					{
						cotw::Item *p_item = static_cast<cotw::Tile*>(map.tiles[player->row][player->col])->inventory.front();
						cout << p_item->name << endl;
						console->log(("You receive item [" + p_item->name + "]."), sf::Color::White);
					}
					break;

				case sf::Keyboard::Q:
					std::cout << "Bye." << std::endl;
					window.close();
					break;

				case sf::Keyboard::I:
					cout << "Player at [" << player->row << "][" << player->col << "]." << endl;
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
			case sf::Event::MouseButtonPressed:
			{
				cout << event.mouseButton.x << ", " << event.mouseButton.y << endl;

			}
			break;

			default:
				// nothing
				break;
		}
	}

	for (unsigned int y = 0; y < map.tiles.size(); y++) 
		for (unsigned int x = 0; x < map.tiles.size(); x++) 
			static_cast<cotw::Tile*>(map.tiles[y][x])->move(new_move);
}



}
