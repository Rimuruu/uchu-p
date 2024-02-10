#include "input.h"
#include "box.h"


void InputComponent::setMove(int dir, int state) {
	m[dir] = state;
}



void InputComponent::handle(Button_state b) {
	switch (b.keyCode) {
	case K_UP:
		printFormat(INFO, "UP %hu", b.state);
		this->setMove(0, b.state);
		break;
	case K_RIGHT:
		printFormat(INFO, "RIGHT %hu", b.state);
		this->setMove(2, b.state);
		break;
	case K_DOWN:
		printFormat(INFO, "DOWN %hu", b.state);
		this->setMove(1, b.state);
		break;
	case K_LEFT:
		printFormat(INFO, "LEFT %hu", b.state);
		this->setMove(3, b.state);
		break;
	case K_SPACE:
		printFormat(INFO, "SPACE %hu", b.state);
		if (b.state) {
			Position2D* p = this->e->getComponent<Position2D>();
			Box* b = this->e->getComponent<Box>();
			playSound("./assets/sound/shoot.wav");
			if(b && p) spawnBullet(p->x+(b->w/2), p->y +(b->h/2), 0, 1);
		}
		break;
	}


}

InputComponent::InputComponent(Entity* e) {
	this->e = e;
}

void InputComponent::update() {
	Velocity* v = this->e->getComponent<Velocity>();
	if (v ) {
		v->Vy = (this->m[0] ^ -this->m[1]) != 0xFFFFFFFE ? this->m[0] ^ -this->m[1] : 0;
		v->Vx = (this->m[2] ^ -this->m[3]) != 0xFFFFFFFE ? this->m[2] ^ -this->m[3] : 0;
		printFormat(INFO, "player %d %d", v->Vy, v->Vx);
	}
}