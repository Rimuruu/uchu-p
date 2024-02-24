#include "player.h"
#include "asset.h"


Player::Player(int x, int y, int w, int h, int speed) {

	this->addComponent<Position2D>(x,y);
	this->addComponent<Box>(w, h);
	this->addComponent<Velocity>(0, 0, speed);
	this->addComponent<InputComponent>();
	this->addComponent<SpriteComponent>(TEST);
}

std::shared_ptr<Entity> spawnPlayer(int x,int y) {
	Player * p = new Player(x, y, 100, 100, 10);
	p->isActive = 1;
	auto pp = is.pushEntity(p);
	ms.pushEntity(pp);
	gs.pushEntity(pp);
	cl.pushEntity(pp);

	return pp;

}


void Player::end() {
	is.removedEntity(this);
	ms.removedEntity(this);
	gs.removedEntity(this);
	cl.removedEntity(this);
}