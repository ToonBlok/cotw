#include <iostream>
#include "InGameState.h"
//#include "GameStateManager.h"

using namespace std;

namespace cotw {

InGameState::InGameState(cotw::GameStateManager* _game_state_manager) 
{
	game_state_manager = _game_state_manager;
}

InGameState::~InGameState() {}

void InGameState::update() {}

void InGameState::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const
{
}

void InGameState::change_state(cotw::GameStateManager* game_state_manager, cotw::GameState* state) 
{
	//game->set_state(state);
}

}
