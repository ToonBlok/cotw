#ifndef OBSERVER_H
#define OBSERVER_H

namespace cotw {

enum class Event { START_CLICKED, SETTINGS_CLICKED, EXIT_CLICKED };

class IObserver
{
	public:
		virtual void on_notify(cotw::Event) = 0;
};

}

#endif
