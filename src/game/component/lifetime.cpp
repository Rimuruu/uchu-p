#include "lifetime.h"



LifetimeComponent::LifetimeComponent(Entity* e, int lifetime) {
	this->lifetime = lifetime;
	this->e = e;
}
void LifetimeComponent::update() {
	lifetime -= 1;
	if (lifetime <= 0) this->e->isDestroyed = 2;
}
