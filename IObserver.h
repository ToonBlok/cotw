#ifndef OBSERVER_H
#define OBSERVER_H

namespace cotw {

class IObserver
{
	public:
		virtual void on_notify(sf::Event) = 0;
};

}

#endif
