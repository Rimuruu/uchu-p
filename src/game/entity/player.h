#include "ecs/ecs.h"
#include "component/velocity.h"
#include "component/position.h"
#include "key_binding.h"
#include "sound.h"
#include "component/input.h"


#ifndef PLAYER_H
#define PLAYER_H

struct Player : public Entity {
	int m[4] = {0};
	Player(int x, int y, int w, int h, int speed);



	

};


#endif // !PLAYER_H


