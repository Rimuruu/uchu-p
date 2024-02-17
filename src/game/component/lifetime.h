#include "ecs/ecs.h"

#ifndef LIFETIME_H
#define LIFETIME_H
struct LifetimeComponent : Component {
	int lifetime;
	LifetimeComponent(Entity* e, int lifetime);
	void update();
};


#endif // !LIFETIME_H
