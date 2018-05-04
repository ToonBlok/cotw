#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "IObserver.h"
//#include "GameStateManager.h"
//#include "Game.h"
//#include "IStateChanger.h"

namespace cotw {

class GameStateManager;

class GameState: public sf::Drawable, public IObserver
{
	public:
		GameState() {};
		~GameState() {};

		virtual void draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const = 0;
		virtual void update(sf::RenderWindow&) = 0;
		virtual void handle_events() = 0;
		virtual void init() = 0;
		virtual void cleanup() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;
		virtual void change_state(cotw::GameStateManager*, cotw::GameState*) = 0;
	protected:
		virtual void handle_key(sf::RenderWindow&, sf::Event) = 0;
		virtual void on_notify(sf::Event) = 0;
};

}

#endif
