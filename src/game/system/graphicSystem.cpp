#include "graphicSystem.h"
#include "component/box.h"

GraphicSystem::GraphicSystem() {

}


void GraphicSystem::render() {
	for (std::shared_ptr<Entity>e : entities) {
		printFormat(INFO, "bullet %p", e);
		if (e && e->isActive) {
			Box* b = e->getComponent<Box>();
			if (b && b->isActive) {
				b->render();
			}
		}
	}
}


GraphicSystem gs;
