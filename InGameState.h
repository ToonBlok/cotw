#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "GameState.h"
#include "MainMenuState.h"

namespace cotw {

class InGameState: public cotw::GameState
{
	public:
		InGameState(cotw::GameStateManager*);
		~InGameState();
		cotw::GameStateManager* game_state_manager;
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void update();
		void change_state(cotw::GameStateManager*, cotw::GameState*);
};

}

#endif
