#include <iostream>
#include "GameStateManager.h"

using namespace std;

namespace cotw {

GameStateManager::GameStateManager(sf::Vector2u window_size)
{ 
	states[0] = new cotw::MainMenuState(this, window_size);
	states[1] = new cotw::InGameState(this, window_size);
	current_state = states[0];
}

GameStateManager::~GameStateManager(){ }


void GameStateManager::set_state(cotw::State state)
{
	current_state = states[state];
}

}
