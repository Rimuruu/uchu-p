#include "player.h"
#include "sound.h"

void Player::update() {
	this->move();
	Velocity* v = this->getComponent<Velocity>();
	Position2D* p = this->getComponent<Position2D>();
	if (v && p) {
		p->x = p->x + (v->Vx * v->speed);
		p->y = p->y + (v->Vy * v->speed);
	}

}




void Player::setMove(int dir, int state) {
	m[dir] = state;
}

void Player::handleInput(u_int32 keyCode, short state) {
	switch (keyCode) {
	case K_UP:
		printFormat(INFO, "UP %hu", state);
		this->setMove(0, state);
		break;
	case K_RIGHT:
		printFormat(INFO, "RIGHT %hu", state);
		this->setMove(2, state);
		break;
	case K_DOWN:
		printFormat(INFO, "DOWN %hu", state);
		this->setMove(1, state);
		break;
	case K_LEFT:
		printFormat(INFO, "LEFT %hu", state);
		this->setMove(3, state);
		break;
	case K_SPACE:
		printFormat(INFO, "SPACE %hu", state);
		playSound("test.wav");
		break;
	}

}

void Player::move() {
	Velocity* v = this->getComponent<Velocity>();
	if (v) {
		v->Vy = (m[0] ^ -m[1]) != 0xFFFFFFFE ? m[0] ^ -m[1] : 0;
		v->Vx = (m[2] ^ -m[3]) != 0xFFFFFFFE ? m[2] ^ -m[3] : 0;
		printFormat(INFO, "player %d %d", v->Vy, v->Vx);
	}


}


Player::Player(int x, int y, int w, int h, int speed) {

	this->addComponent<Position2D>(x,y);
	this->addComponent<Box>(w, h);
	this->addComponent<Velocity>(0, 0, speed);
}