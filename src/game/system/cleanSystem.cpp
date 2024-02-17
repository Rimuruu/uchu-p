#include "cleanSystem.h"


CleanSystem::CleanSystem() {

}

void CleanSystem::update() {
	for (std::shared_ptr<Entity>e : entities) {
		if (e && e->isDestroyed > 1) {
			e->end();

	
		}
	}
}

CleanSystem cl;