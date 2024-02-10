#include "inputSystem.h"
#include "inputSystem.h"

void InputSystem::update() {
	Button_state b;
	while (game_input->front > 0) {
		b = game_input->pop();
		if (b.keyCode == 0) {
			break;
		}
		for (std::shared_ptr<Entity >e : entities) {
			if (e && e->isActive) {
				InputComponent* i = e->getComponent<InputComponent>();
				if (i && i->isActive) {
					i->handle(b);
				}
		
			}
		}


	}
	for (std::shared_ptr<Entity > e : entities) {
		if (e && e->isActive) {
			InputComponent* i = e->getComponent<InputComponent>();
			if (i && i->isActive) {
				i->update();
			}

		}
	}
	
}


InputSystem::InputSystem() {

}


InputSystem is;