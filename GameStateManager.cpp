#include <iostream>
#include "GameStateManager.h"

using namespace std;

namespace cotw {

GameStateManager::GameStateManager()
{ 
	state = new cotw::MainMenuState(this);	
	//set_state(new MainMenuState(this));

}

GameStateManager::~GameStateManager(){ }


void GameStateManager::set_state(cotw::GameState* new_state)
{
	state = new_state;
}

void GameStateManager::push_state(cotw::GameState*)
{
}

void GameStateManager::pop_state()
{
}

void GameStateManager::on_notify(cotw::Event)
{
}

}
