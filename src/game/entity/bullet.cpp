#include "bullet.h"



Bullet::Bullet(int x, int y, int w, int h, int speed, int Vx, int Vy) {
	this->addComponent<Velocity>( Vx, Vy, speed);
	this->addComponent<Position2D>( x,y);
	this->addComponent<Box>( w, h);
}

void Bullet::update() {
	Velocity* v = this->getComponent<Velocity>();
	Position2D* p = this->getComponent<Position2D>();
	if (v && p) {
		p->x = p->x + (v->Vx * v->speed);
		p->y = p->y + (v->Vy * v->speed);
	}

}

