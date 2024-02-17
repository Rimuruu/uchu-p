#include "bullet.h"
#include "system/system.h"


Bullet::Bullet(int x, int y, int w, int h, int speed, int Vx, int Vy) {
	this->addComponent<Velocity>( Vx, Vy, speed);
	this->addComponent<Position2D>( x,y);
	this->addComponent<Box>( w, h);
	this->addComponent <LifetimeComponent>(30);
	printFormat(INFO, "bullet created");
}

void Bullet::update() {

	

}

void Bullet::end() {
	ms.removedEntity(this);
	gs.removedEntity(this);
	cl.removedEntity(this);
}

Bullet::~Bullet() {
	printFormat(INFO, "bullet deleted");
}

void spawnBullet(int x, int y, int Vx, int Vy) {
	Bullet * b = new Bullet(x, y, 10, 10, 10, Vx, Vy);
	
	auto bp = ms.pushEntity(b);
	gs.pushEntity(bp);
	cl.pushEntity(bp);
}