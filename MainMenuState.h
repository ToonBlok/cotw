#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

namespace cotw {

class MainMenuState: public cotw::GameState
{
	public:
		MainMenuState();
		~MainMenuState();
		void update();
};

}

#endif
