#include "bullet.h"
#include "system/system.h"


Bullet::Bullet(int x, int y, int w, int h, int speed, int Vx, int Vy) {
	this->addComponent<Velocity>( Vx, Vy, speed);
	this->addComponent<Position2D>( x,y);
	this->addComponent<Box>( w, h);
	printFormat(INFO, "bullet created");
}

void Bullet::update() {
	Velocity* v = this->getComponent<Velocity>();
	Position2D* p = this->getComponent<Position2D>();
	if (v && p) {
		p->x = p->x + (v->Vx * v->speed);
		p->y = p->y + (v->Vy * v->speed);
	}

}

Bullet::~Bullet() {
	printFormat(INFO, "bullet deleted");
}

void spawnBullet(int x, int y, int Vx, int Vy) {
	Bullet * b = new Bullet(x, y, 10, 10, 10, Vx, Vy);
	
	ms.pushEntity(b);
	gs.pushEntity(b);
}