#include "box.h"


#ifndef POSITION_H
#define POSITION_H

struct Position2D : public Component {
	int x, y;

	Position2D(Entity* e, int x, int y);

	void init();
	void update();
	void render();
	void end();

};


#endif // !1

