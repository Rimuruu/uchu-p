#include "inputSystem.h"
#include "uchu.h"

void InputSystem::update() {
	Button_state b;
	while (game_input->front > 0) {
		b = game_input->pop();
		if (b.keyCode == 0) {
			break;
		}
		for (Entity* e : entities) {
			if (e && e->isActive) {
				e->handleInput(b.keyCode,b.state);

			}
		}


	}
	
}


InputSystem::InputSystem() {

}
