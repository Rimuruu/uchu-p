#include "ecs/ecs.h"
#include <memory>
#include "component/position.h"
#include "component/velocity.h"


#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H
struct MovementSystem : System {
	MovementSystem();
	void update();

};





#endif // !MOVEMENTSYSTEM_H
