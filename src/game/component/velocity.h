#include "ecs/ecs.h"

#ifndef VELOCITY_H
#define VELOCITY_H

struct Velocity : public Component {
	int Vx, Vy,speed;

	Velocity(Entity* e, int Vx, int Vy,int speed);

	








};

#endif // !VELOCITY_H


