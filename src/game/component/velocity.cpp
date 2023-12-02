#include "velocity.h"



Velocity::Velocity(Entity* e, int Vx, int Vy,int speed) {
	this->e = e;
	this->Vx = Vx;
	this->Vy = Vy;
	this->speed = speed;

}