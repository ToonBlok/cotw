#ifndef SUBJECT_H
#define SUBJECT_H

#include "screens/rect.h"

namespace cotw {

class ISubject
{
	public:
		//std::vector<Rect*> observers;
		virtual void notify(sf::Event) = 0;
		virtual void add_observer() = 0;
		virtual void remove_observer() = 0;
};

}

#endif
