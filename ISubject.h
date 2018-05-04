#ifndef SUBJECT_H
#define SUBJECT_H

#include "IObserver.h"

namespace cotw {

class ISubject
{
	public:
		std::vector<cotw::IObserver*> observers;
		virtual void notify(sf::Event) = 0;
		virtual void add_observer(IObserver*) = 0;
		virtual void remove_observer() = 0;
};

}

#endif
