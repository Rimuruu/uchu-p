#include "player.h"
#include "asset.h"


Player::Player(int x, int y, int w, int h, int speed) {

	this->addComponent<Position2D>(x,y);
	this->addComponent<Box>(w, h);
	this->addComponent<Velocity>(0, 0, speed);
	this->addComponent<InputComponent>();
	this->addComponent<SpriteComponent>(TEST);
}