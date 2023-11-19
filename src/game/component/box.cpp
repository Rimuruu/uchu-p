#include "box.h"
#include "graphic.h"

void Box::render() {
	Position2D* p = this->e->getComponent<Position2D>();
	if (p) {
		drawRectangle(p->x, p->y, p->x + w, p->y+ h, 0x00FF00FF);
	}
	
	}
