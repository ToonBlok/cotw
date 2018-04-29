#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "main_menu.h"
#include "../subject.h"

using namespace std;

namespace cotw {

class Gui: public sf::Drawable, public cotw::ISubject
{
	public:
		Gui(sf::Vector2u);
		~Gui();

		void update();
		void draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const;
		void notify(sf::Event);
		void add_observer(IObserver*);
		void remove_observer();

	private:
		sf::Vector2u screen_size;
};

}

#endif
