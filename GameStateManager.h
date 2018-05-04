#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "GameState.h"
#include "MainMenuState.h"
#include "InGameState.h"

namespace cotw {

//class GameState;

class GameStateManager
{
	public:
		GameStateManager();
		~GameStateManager();
		cotw::GameState *state;

		void push_state(cotw::GameState*);
		void pop_state();
		void set_state(cotw::GameState*);
};

}

#endif
