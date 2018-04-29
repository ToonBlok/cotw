#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../drawable.h"
#include "../observer.h"

namespace cotw {

class Rect: public cotw::Drawable, public cotw::IObserver
{
	public:
		Rect() {};
		~Rect() {};

		int width;
		int height;
		bool activated = false;

		virtual void update() = 0;
		//virtual void notify(sf::Event) = 0;
		//virtual void add_observer(IObserver*) = 0;
		//virtual void remove_observer() = 0;
		virtual void on_notify(sf::Event) = 0;
};

}

#endif
