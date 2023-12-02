#include "box.h"
#include "graphic.h"

void Box::render() {
	Position2D* p = this->e->getComponent<Position2D>();
	printFormat(INFO, "player %d %d %d %D", w,h,p->x,p->y);
	if (p) {
		drawRectangle(p->x, p->y, p->x + w, p->y+ h, 0x00123456);
	}
	
	}
