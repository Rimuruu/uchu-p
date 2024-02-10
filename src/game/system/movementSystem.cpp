#include "movementSystem.h"
MovementSystem::MovementSystem() {


}


void MovementSystem::update() {


	for (std::shared_ptr<Entity>e : entities) {
		if (e && e->isActive) {
			Position2D* p = e->getComponent<Position2D>();
			//Velocity* v = e->getComponent<Velocity>();
			if (p && p->isActive) {
				p->update();
			}

		}
	}




}

MovementSystem ms;