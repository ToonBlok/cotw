#ifndef ISTATECHANGER_H
#define ISTATECHANGER_H

//#include "GameState.h"

namespace cotw {

class GameState;

class IStateChanger
{
	public:
		IStateChanger() {};
		~IStateChanger() {};

		virtual void set_state(cotw::GameState*) = 0;
};

}

#endif
