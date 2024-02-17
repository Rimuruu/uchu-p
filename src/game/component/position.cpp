#include "position.h"
#include "velocity.h"
#include "lifetime.h"
	
	Position2D::Position2D(Entity* e, int x, int y) {
		this->x = x;
		this->y = y;
		this->e = e;
	}

	void Position2D::init() {

	}
	void Position2D::update() {
		Velocity* v = this->e->getComponent<Velocity>();
		Position2D* p = this;
		LifetimeComponent* l = this->e->getComponent<LifetimeComponent>();
		if (v && p) {
			p->x = p->x + (v->Vx * v->speed);
			p->y = p->y + (v->Vy * v->speed);
		}
		if (l) {
			l->update();
		}
	}
	void Position2D::render() {

	}
	void Position2D::end() {

	}
