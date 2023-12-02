#pragma once 
#include "ecs/ecs.h"


struct Velocity : public Component {
	int Vx, Vy,speed;

	Velocity(Entity* e, int Vx, int Vy,int speed);

	








};
