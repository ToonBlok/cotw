#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "GameState.h"
#include "MainMenuState.h"
#include "InGameState.h"
#include "IObserver.h"

namespace cotw {


class GameStateManager
{
	public:
		GameStateManager(sf::Vector2u);
		~GameStateManager();

		std::array<cotw::GameState*, 2> states;
		cotw::GameState *current_state;

		void set_state(cotw::State);
};

}

#endif
