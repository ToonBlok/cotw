#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Drawable.h"
#include "../ISubject.h"

namespace cotw {

class Rect: public cotw::Drawable, public cotw::ISubject
{
	public:
		Rect() {};
		~Rect() {};

		int width;
		int height;
		bool activated = false;

		virtual void update() = 0;
		virtual void notify(cotw::Event) = 0;
		virtual void add_observer(IObserver*) = 0;
		virtual void remove_observer() = 0;
};

}

#endif
