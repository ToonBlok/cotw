#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "IObserver.h"

namespace cotw {

class GameStateManager;

enum State { MAINMENU, INGAME };

class GameState: public sf::Drawable, public cotw::IObserver
{
	public:
		GameState() {};
		~GameState() {};

		virtual void update(sf::RenderWindow&) = 0;
		virtual void draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const = 0;
		virtual void change_state(cotw::GameStateManager*, cotw::State) = 0;
	protected:
		virtual void handle_key(sf::RenderWindow&, sf::Event) = 0;
		virtual void on_notify(cotw::Event) = 0;
};

}

#endif
