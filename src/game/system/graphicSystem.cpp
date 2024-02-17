#include "graphicSystem.h"
#include "component/box.h"
#include "component/sprite.h"

GraphicSystem::GraphicSystem() {

}


void GraphicSystem::render() {
	for (std::shared_ptr<Entity>e : entities) {
		if (e && e->isActive) {
			Box* b = e->getComponent<Box>();
			SpriteComponent* s = e->getComponent<SpriteComponent>();
			if (b && b->isActive) {
				b->render();
			}

			if (s && s->isActive) {
				s->render();
			}
		}
	}
}


GraphicSystem gs;
