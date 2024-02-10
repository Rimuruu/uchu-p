
#include "uchu.h"
#include <memory>
#include "ecs/ecs.h"
#include "component/input.h"

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

struct InputSystem : System {
	Game_input* game_input;
	InputSystem(Game_input game_input);
	InputSystem();
	
	void update();



};

#endif // !INPUTSYSTEM_H


