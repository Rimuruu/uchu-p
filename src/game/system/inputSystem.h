#pragma once 

#include "ecs/ecs.h"

struct Game_input;
struct Button_state;

struct InputSystem : System {
	Game_input* game_input;
	InputSystem(Game_input* game_input);
	InputSystem();
	
	void update();



};